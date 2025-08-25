#include "ActorHandler.h"
#include "Configuration.h"
#include "HUDDetours.h"
#include "SDKExt.h"
#include "Utils.h"
#include <format>
#include <algorithm>
#include <cctype>

using namespace SDK;

struct FActorCreateListener : public SDKExt::FUObjectCreateListener
{
	static FActorCreateListener ActorCreateListener;

	void NotifyUObjectCreated(const UObject* object, int32 index) override
	{
		if (!object || !object->IsValidLowLevel()) return;
		
		if (object->IsA(EClassCastFlags::Class)) {
			ActorHandler::AddClass(std::bit_cast<UClass*>(object));
		}
		if (object->IsA(EClassCastFlags::Actor) && !object->IsDefaultObject()) {
			auto actor = std::bit_cast<AActor*>(object);
			if (actor) {
				ActorHandler::ProcessActor(actor);
			}
		}
	}

	void OnUObjectArrayShutdown() override
	{
		SDKExt::UObjectArray::RemoveUObjectCreateListener(&ActorCreateListener);
	}
};
FActorCreateListener FActorCreateListener::ActorCreateListener{};

struct FActorDeleteListener : public SDKExt::FUObjectDeleteListener
{
	static FActorDeleteListener ActorDeleteListener;

	void NotifyUObjectDeleted(const UObject* object, int32 index) override
	{
		if (!object || !object->IsValidLowLevel()) return;
		
		if (object->IsA(EClassCastFlags::Class)) {
			ActorHandler::RemoveClass(std::bit_cast<UClass*>(object));
		}
		if (object->IsA(EClassCastFlags::Actor)) {
			auto actor = std::bit_cast<AActor*>(object);
			if (actor) {
				ActorHandler::RemoveActor(actor);
			}
		}
	}

	void OnUObjectArrayShutdown() override
	{
		SDKExt::UObjectArray::RemoveUObjectDeleteListener(&ActorDeleteListener);
	}
};
FActorDeleteListener FActorDeleteListener::ActorDeleteListener{};

void ActorHandler::Start() {
	SDKExt::UObjectArray::AddUObjectCreateListener(&FActorCreateListener::ActorCreateListener);
	SDKExt::UObjectArray::AddUObjectDeleteListener(&FActorDeleteListener::ActorDeleteListener);
	// backfill actor/class cache
	for (int i = 0; i < UObject::GObjects->Num(); i++) {
		auto obj = UObject::GObjects->GetByIndex(i);
		if (!obj || !obj->IsValidLowLevel() || obj->IsDefaultObject()) continue;
		FActorCreateListener::ActorCreateListener.NotifyUObjectCreated(obj, i);
	}
	bListenersAdded = true;
	FlowtreeTag = FGameplayTag{ UKismetStringLibrary::Conv_StringToName(L"Variant.FlowInfused") };
	StarQualityTag = FGameplayTag{ UKismetStringLibrary::Conv_StringToName(L"Variant.StarQuality") };
	InfectedTag = FGameplayTag{ UKismetStringLibrary::Conv_StringToName(L"Variant.EchoInfected") };
}

void ActorHandler::Stop() {
	if (!bListenersAdded) return;
	SDKExt::UObjectArray::RemoveUObjectCreateListener(&FActorCreateListener::ActorCreateListener);
	SDKExt::UObjectArray::RemoveUObjectDeleteListener(&FActorDeleteListener::ActorDeleteListener);
	bListenersAdded = false;
}

void ActorHandler::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
	DetourManager::AddInstance(VPC);
	DetourManager::AddFunctionListener("Function Engine.PlayerController.ClientTravelInternal", &ClientTravelInternal, nullptr);
	DetourManager::AddInstance(VC);
	DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Tick, nullptr);
	DetourManager::AddFunctionListener("Function Function Engine.Actor.ReceiveEndPlay", &ClientTravelInternal, nullptr);
	DetourManager::AddFunctionDetour("Function Palia.VariantComponent.OnRep_ActiveVariants", nullptr, &Func_OnRep_ActiveVariants);
}

void ActorHandler::ClientTravelInternal(const UObject* Context, UFunction* Function, void* Parms) {
	ActorCache.clear();
	bIsTraveling = true;
}

void ActorHandler::Tick(const UObject* Context, UFunction* Function, void* Parms) {
	const UWorld* World = UWorld::GetWorld();
	if (CurrentLevel != World->PersistentLevel) {
		CurrentLevel = World->PersistentLevel;
		auto LevelName = UGameplayStatics::GetCurrentLevelName(World, false).ToString();
		if (auto FoundEntry = EValeriaLevelMap.find(LevelName); FoundEntry != EValeriaLevelMap.end()) {
			CurrentMap = FoundEntry->second;
		}
		else {
			CurrentMap = EValeriaLevel::UnknownLvl;
		}
		LastUpdate = 0; // GetTimeSeconds is level based
		LastDormantUpdate = 0;
		bIsTraveling = false;
	}
	if (bIsTraveling) return;
	auto timeNow = UGameplayStatics::GetTimeSeconds(World);
	UpdateActors();
	if (timeNow - LastUpdate > 1) {
		LastUpdate = timeNow;
		UpdateDespawn();
	}
}

/*
	AActor
		AGatherableActor
			ABP_ValeriaGatherableLoot_C
				ABP_ValeriaGatherableLoot_Lumber_C
				ABP_ValeriaGatherableLoot_Mining_Base_C
		APawn
			AValeriaMoveablePawn
				ACreatureCharacter
					ABugCatchingCreatureCharacter
						ABP_ValeriaBugCatchingCreature_C
					ABP_ValeriaHuntingCreature_C
				AValeriaCharacter
					ABP_ValeriaCharacter_C
				AValeriaPetCharacter
					ABP_Pet_Base_C
				AValeriaVillagerCharacter
					ABP_ValeriaVillagerCharacter_C
		AWorldGatherableBase
			ATimedLootPile
				ABP_TimedLootPileBase_C
			AWorldPersistGatherable
				ABP_WorldPersistGatherable_Base_C
					ABP_WorldPersistGatherable_Treasure_Base_C
		ABubble_Base
			ABP_Bubble_Base_C
		AVAL_BreakableActor
		ABP_ConfigurableBook_C
		ABP_Loot_C
		ABP_QuestInspect_Base_C
		ABP_SimpleInspect_Base_C
		ABP_Stables_Sign_C
		ABP_ValeriaGatherable_C
			ABP_Facility_Well_C
			ABP_QuestItem_BASE_C
			ABP_Valeria_Gatherable_Placed_C
*/

#define CHECK_ACTOR_TYPE(className, type)				\
if (IsValidPtr(Actor) && IsActorA(Actor, className)) {	\
	ActorType = type;									\
}

void ActorHandler::ProcessActor(AActor* Actor) {
	// Skip actor processing entirely when on home plots to prevent crashes
	// Even checking actor properties can cause instability on home plots
	// if (CurrentMap == EValeriaLevel::Home) return;
	
	// Validate actor pointer before any processing - basic check only
	if (!Actor || !Actor->IsValidLowLevel()) return;
	
	// Skip actors that might be related to rendering/materials during load
	auto ClassName = Actor->Class->GetName();
	// Convert to lowercase for case-insensitive comparison
	std::transform(ClassName.begin(), ClassName.end(), ClassName.begin(), ::tolower);
	
	if (ClassName.find("material") != std::string::npos || 
	    ClassName.find("rendering") != std::string::npos || 
	    ClassName.find("cinematic") != std::string::npos ||
	    ClassName.find("phoenixshrine") != std::string::npos ||
		ClassName.find("shrine") != std::string::npos ||
	    ClassName.find("movie") != std::string::npos ||
	    ClassName.find("previz") != std::string::npos) {
		return;
	}
	
	// first pass highest superclass possible to clear unwanted actors fast
	auto ActorType = EType::Unknown;

	// Tree, Ore
	if (Actor->IsA(AGatherableActor::StaticClass())) {
		// Tree
		CHECK_ACTOR_TYPE(L"/Game/Gameplay/Skills/Lumberjacking/Felling/BP_ValeriaGatherableLoot_Lumber.BP_ValeriaGatherableLoot_Lumber", EType::Tree)
			// Ore
	else CHECK_ACTOR_TYPE(L"/Game/Gameplay/Skills/Mining/BP_ValeriaGatherableLoot_Mining_Base.BP_ValeriaGatherableLoot_Mining_Base", EType::Ore)
	}
	// Bugs, Animals, Players, NPCs
	else if (Actor->IsA(AValeriaMoveablePawn::StaticClass())) {
		// NPC
		if (Actor->IsA(AValeriaVillagerCharacter::StaticClass())) {
			ActorType = EType::NPCs;
		}
		// Player
		else if (Actor->IsA(AValeriaCharacter::StaticClass())) {
			ActorType = EType::Players;
		}
		// Bug
		else if (Actor->IsA(ABugCatchingCreatureCharacter::StaticClass())) {
			ActorType = EType::Bug;
		}
		// Animal
		else CHECK_ACTOR_TYPE(L"/Game/Gameplay/Skills/Hunting/BP_ValeriaHuntingCreature.BP_ValeriaHuntingCreature", EType::Animal)
	}
	// Rummage, Treaure
	else if (Actor->IsA(AWorldGatherableBase::StaticClass())) {
		// Rummage
		if (Actor->IsA(ATimedLootPile::StaticClass())) {
			ActorType = EType::RummagePiles;
		}
		// Treasure
		else CHECK_ACTOR_TYPE(L"/Game/Core/TreasureTypes/BP_WorldPersistGatherable_Treasure_Base.BP_WorldPersistGatherable_Treasure_Base", EType::Treasure)
	}
	else if (Actor->IsA(AGardenTile::StaticClass())) {
		ActorType = EType::Garden;
	}
	else if (Actor->IsA(AVAL_TeleporterBase::StaticClass())) {
		Teleporters.push_back(Actor);
		return;
	}
	else if (Actor->IsA(ABubble_Base::StaticClass())) {
		ActorType = EType::Animal;
	}
	else if (Actor->IsA(AVAL_BreakableActor::StaticClass())) {
		ActorType = EType::Breakable;
	}
	else if (IsBlueprintClass(Actor->Class)) {
		ProcessBPActor(Actor);
		return;
	}
	if (ActorType == EType::Unknown) return;
	FinishProcessingActor(Actor, ActorType);
}

void ActorHandler::ProcessBPActor(AActor* Actor) {
	// Skip actor processing entirely when on home plots to prevent crashes
	// Even checking actor properties can cause instability on home plots
	// if (CurrentMap == EValeriaLevel::Home) return;
	
	// Validate actor pointer before any processing - basic check only
	if (!Actor || !Actor->IsValidLowLevel()) return;
	
	auto ActorType = EType::Unknown;
	for (auto& BPClass : BPActors) {
		if (IsValidPtr(Actor) && IsActorA(Actor, BPClass.first)) {
			ActorType = BPClass.second;
			break;
		}
	}
	if (ActorType == EType::Unknown) return;
	FinishProcessingActor(Actor, ActorType);
}

bool ActorHandler::IsBlueprintClass(UClass* Class) {
	auto classFlags = *std::bit_cast<EClassFlags*>(std::bit_cast<char*>(Class) + 0xD4);
	return classFlags & EClassFlags::CompiledFromBlueprint;
}

#undef CHECK_ACTOR_TYPE

void ActorHandler::FinishProcessingActor(AActor* Actor, EType ActorType) {
	auto ClassName = Actor->Class->GetName();

	uint8_t Type = 0;
	uint8_t Quality = 0;
	uint8_t Variant = 0;
	std::string Texture;
	std::wstring Name;

	switch (ActorType) {
	case EType::Tree: {
		ActorCacheMutex.lock();
		ActorCache.push_back(std::make_shared<FEntryLumber>(Actor, ClassName));
		ActorCacheMutex.unlock();
		return;
	}
	case EType::Ore: {
		auto OreEntry = std::make_shared<FEntryMining>(Actor, ClassName);
		if (IsActorA(Actor, L"/Game/Gameplay/Skills/Mining/BP_ValeriaGatherableLoot_Mining_MultiHarvest.BP_ValeriaGatherableLoot_Mining_MultiHarvest")) {
			// Differentiate between SingleHarvest and MultiHarvest
			OreEntry->setQuality(1);
		}
		ActorCacheMutex.lock();
		ActorCache.push_back(OreEntry);
		ActorCacheMutex.unlock();
		return;
	}
	case EType::Bug: {
		ActorCacheMutex.lock();
		ActorCache.push_back(std::make_shared<FEntryBug>(Actor, ClassName));
		ActorCacheMutex.unlock();
		return;
	}
	case EType::Animal: {
		ActorCacheMutex.lock();
		ActorCache.push_back(std::make_shared<FEntryHunting>(Actor, ClassName));
		ActorCacheMutex.unlock();
		return;
	}
	case EType::Forage: {
		if (ClassName == "BP_Gatherable_RemembranceGarden_C" || ClassName == "BP_Gatherable_Gravesite_C") {
			// Silly Silly Palia
			ActorType = EType::Quest;
			Type = 4;
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Compass_Quest_01.Icon_Compass_Quest_01";
		} else {
			ActorCacheMutex.lock();
			ActorCache.push_back(std::make_shared<FEntryGatherable>(Actor, ClassName));
			ActorCacheMutex.unlock();
			return;
		}
		break;
	}
	case EType::Loot: {
		if (auto LootType = GetFlagSingle(ClassName, LOOT_TYPE_MAPPINGS); LootType != ELootBagType::Unknown) {
			Type = static_cast<uint8_t>(LootType);
			Texture = "/Game/UI/Assets_Shared/Icons/WT_Icon_Inventory_Bag.WT_Icon_Inventory_Bag";
		}
		break;
	}
	case EType::Players: {
		Type = 1; // doesn't matter, but isn't "unknown"
		Name = static_cast<AValeriaCharacter*>(Actor)->CharacterName.ToWString();
		Texture = "/Game/UI/Clock/Icon_DayClockArrow_01.Icon_DayClockArrow_01";
		break;
	}
	case EType::NPCs: {
		Type = 1; // doesn't matter, but isn't "unknown"
		Texture = VillagerTextures[ClassName];
		break;
	}
	case EType::Quest: {
		if (IsActorA(Actor, L"/Game/Gameplay/QuestItems/baseClass/BP_QuestItem_BASE.BP_QuestItem_BASE")) {
			Type = 1;
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Compass_QuestComplete_01.Icon_Compass_QuestComplete_01";
		}
		else if (IsActorA(Actor, L"/Game/Gameplay/Inspectables/Base/BP_SimpleInspect_Base.BP_SimpleInspect_Base")) {
			Type = 2;
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Quest_02.Icon_Quest_02";
		}
		else if (IsActorA(Actor, L"/Game/Gameplay/Inspectables/Base/BP_QuestInspect_Base.BP_QuestInspect_Base")) {
			Type = 3;
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Compass_Quest_01.Icon_Compass_Quest_01";
		}
		break;
	}
	case EType::RummagePiles: {
		Type = 1;
		Texture = "/Game/UI/Icons/Icon_Deco_Chapaa_Nest.Icon_Deco_Chapaa_Nest";
		break;
	}
	case EType::Stables: {
		Type = 1;
		Texture = "/Game/UI/Assets_Shared/Icons/Icon_Compass_Stable_01.Icon_Compass_Stable_01";
		break;
	}
	case EType::Fish: {
		Type = 1;
		Texture = "/Game/UI/Icons/Icon_ResourceTracker_Fishing.Icon_ResourceTracker_Fishing";
		break;
	}
	case EType::Pool: {
		Type = 1;
		Texture = "/Game/UI/Icons/Icon_Buff_FishingCoOp.Icon_Buff_FishingCoOp";
		break;
	}
	case EType::Treasure: {
		Type = 1;
		Texture = TreasureTextures[ClassName];
		break;
	}
	case EType::TimedDrop: {
		Type = 1;
		break;
	}
	case EType::Gates: {
		if (ClassName.find("FrontGate") != std::string::npos) {
			Type = 1;
		}
		break;
	}
	case EType::Relic: {
		Type = 1;
		Texture = "/Game/UI/Icons/Icon_Quest_AncientTablet.Icon_Quest_AncientTablet";
		Name = L"Book";
		break;
	}
	case EType::Garden:
		Type = 1;
		break;
	case EType::Shops:
		if (ClassName.starts_with("BP_Decor")) {
			Type = 1;
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Skill_Furniture_01.Icon_Skill_Furniture_01";
			Name = L"Furniture";
		}
		else {
			Texture = "/Game/UI/Assets_Shared/Icons/Icon_Store_01.Icon_Store_01";
		}
		break;
	case EType::Breakable:
		if (ClassName.find("Chaos_Root") != std::string::npos) {
			// breakable echo vines in caves
			return;
		} else if (ClassName.find("Elderwood") != std::string::npos) {
			Texture = "/Game/UI/Icons/Icon_ResourceTracker_RummagePile.Icon_ResourceTracker_RummagePile";
			Name = L"Rummage Pile";
			Type = 1;
		}
		break;
	case EType::Other:
		if (ClassName.find("QuestItem") != std::string::npos) {
			Type = 5;
			ActorType = EType::Quest;
		}
		else {
			return;
		}
		break;
	default:
		break;
	}

	const FVector ActorPosition = Actor->K2_GetActorLocation();
	if (Name.empty()) {
		std::string tempName = CLASS_NAME_ALIAS.contains(ClassName) ? CLASS_NAME_ALIAS[ClassName] : ClassName;
		std::wstring tempWName(tempName.begin(), tempName.end());
		Name = tempWName;
	}
	//std::wcout << L"*** Adding Actor: " << Name << L"\n";
	ActorCacheMutex.lock();
	ActorCache.push_back(std::make_shared<FEntryBackwardsCompat>(Actor, ActorPosition, Name, ActorType, Type, Quality, Variant, 0, Texture, 0));
	ActorCacheMutex.unlock();
}

UClass* ActorHandler::ClassLookup(std::wstring clazz) {
	auto SpaceLocation = clazz.find_last_of(L"/");
	auto NameWithoutPath = std::wstring{ clazz.begin() + SpaceLocation + 1, clazz.end() } + L"_C";
	if (auto foundEntry = ClassPtrMap.find(NameWithoutPath); foundEntry == ClassPtrMap.end()) {
		return nullptr;
	}
	else {
		return foundEntry->second;
	}
}

UTexture2D* ActorHandler::TextureLookup(const std::string& texture) {
	/*
	if (auto foundEntry = TexturePtrMap.find(texture); foundEntry == TexturePtrMap.end()) {
		auto TexturePtr = static_cast<UTexture2D*>(LoadAssetPtrFromPath(texture));
		TexturePtrMap.emplace(texture, TexturePtr);
		return TexturePtr;
	}
	else {
		auto TexturePtr = foundEntry->second;
		if (!TexturePtr || !TexturePtr->IsValidLowLevel()) {
			auto TexturePtr = static_cast<UTexture2D*>(LoadAssetPtrFromPath(texture));
			TexturePtrMap.emplace(texture, TexturePtr);
			return TexturePtr;
		}
		if (TexturePtr->Flags & EObjectFlags::BeginDestroyed) {
			auto TexturePtr = static_cast<UTexture2D*>(LoadAssetPtrFromPath(texture));
			TexturePtrMap.emplace(texture, TexturePtr);
			return TexturePtr;
		}
		return TexturePtr;
	}*/
	return static_cast<UTexture2D*>(LoadAssetPtrFromPath(texture));
}



void ActorHandler::UpdateActors() {
	auto ValeriaCharacter = GetValeriaCharacter();
	FVector PlayerLocation = { 0,0,0 };
	if (ValeriaCharacter && ValeriaCharacter->RootComponent && ValeriaCharacter->RootComponent->bComponentToWorldUpdated) {
		PlayerLocation = ValeriaCharacter->K2_GetActorLocation();
	}
	for (auto& entry : ActorCache) {
		if (entry->WorldPosition.IsZero() || (EType::MoveablePawn & entry->ActorType())) {
			if (entry->Actor && entry->Actor->RootComponent && entry->Actor->RootComponent->bComponentToWorldUpdated) {
				entry->WorldPosition = entry->Actor->K2_GetActorLocation();
			}
		}
		if (!PlayerLocation.IsZero()) {
			entry->Distance = PlayerLocation.GetDistanceToInMeters(entry->WorldPosition);
		}
		switch (entry->ActorType()) {
		case EType::Gates:
			entry->Actor->K2_DestroyActor();
			break;
		case EType::TimedDrop:
#ifdef ENABLE_SUPPORTER_FEATURES
			if (entry->Variant() == 0) {
				auto TimedDropComponent = *std::bit_cast<UTimedDropComponent**>(std::bit_cast<char*>(entry->Actor) + 0x2D8); // Updated offset based on SDK dump
				if (!TimedDropComponent) continue;
				if (TimedDropComponent->RolledRewards.Num() == 0) continue;
				auto& Reward = TimedDropComponent->RolledRewards[0]; // should only be one reward
				if (Reward.Items.Num() == 0) continue;
				auto& Item = Reward.Items[0]; // should only be one item

				if (auto ItemInfo = TimedDropLoot.find(Item.ItemPersistId); ItemInfo != TimedDropLoot.end()) {
					auto& found = ItemInfo->second;
					entry->DisplayName = std::format(L"{}x {}", Item.Amount, found.first);
					entry->setTexturePath(found.second);
				}
				else {
					auto ItemDefPtr = static_cast<TSoftObjectPtr<UObject>>(UVAL_ItemTypeDefinitionAsset::GetAssetByPersistId_Cast(Item.ItemPersistId));
					auto ItemDef = static_cast<UVAL_ItemTypeDefinitionAsset*>(UKismetSystemLibrary::LoadAsset_Blocking(ItemDefPtr));
					entry->DisplayName = std::format(L"{}x {}", Item.Amount, ItemDef->DisplayName.GetStringRef().ToWString());
				}
				entry->setVariant(Item.Amount);
			}
#endif
			break;
		case EType::RummagePiles:
#ifdef ENABLE_SUPPORTER_FEATURES
			if (entry->Variant() == 0) {
				auto Rummage = static_cast<ATimedLootPile*>(entry->Actor);
				if (Rummage && Rummage->bActivated) {
					if (auto LootInteractor = Rummage->StaticLootInteractorComponent; LootInteractor) {
						if (LootInteractor->Loot.Num() == 0) continue;
						auto& Reward = LootInteractor->Loot[0]; // should only be one reward
						if (Reward.RecipeConfigIds.Num() > 0) {
							entry->setVariant(1);
							auto Name = UValeriaBlueprintFunctionLibrary::GetRecipeItemDisplayNameFromId(UWorld::GetWorld(), Reward.RecipeConfigIds[0]);
							entry->DisplayName = L"Recipe - " + Name.GetStringRef().ToWString();
						}
						else if (Reward.Items.Num() > 0) {
							auto& Item = Reward.Items[0];  // should only be one item
							auto Name = UValeriaBlueprintFunctionLibrary::GetItemDisplayNameFromId(Item.ItemPersistId);
							entry->DisplayName = std::format(L"{}x {}", Item.Amount, Name.GetStringRef().ToWString());
							entry->setVariant(Item.Amount);
						}
					}
				}
			}
#endif
			break;
		case EType::Players:
			if (entry->DisplayName == L"BP_ValeriaCharacter_C") {
				if (auto Character = static_cast<AValeriaCharacter*>(entry->Actor)) {
					entry->DisplayName = Character->CharacterName.ToWString();
				}
			}
			break;
		default:
			break;
		}
	}
}

void ActorHandler::UpdateDespawn() {
	if (Configuration::bEnableESPDespawnTimer) {
		double timestamp = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		for (auto& entry : ActorCache) {
			if (!(EType::Despawnable & entry->ActorType())) continue;
			switch (entry->ActorType()) {
			case EType::Ore: {
				if (IsActorA(entry->Actor, L"/Game/Gameplay/Skills/Mining/BP_ValeriaGatherableLoot_Mining_MultiHarvest.BP_ValeriaGatherableLoot_Mining_MultiHarvest")) {
					auto GatherableLoot = static_cast<ABP_ValeriaGatherableLoot_Mining_MultiHarvest_C*>(entry->Actor);
					if (IsActorValid(GatherableLoot) && GatherableLoot->IAmAlive) {
						if (GatherableLoot->DespawnTimestamp > 0) {
							// if all else fails, do it manually
							//GatherableLoot->GetSecondsUntilDespawn(&entry.Despawn);
							entry->Despawn = GatherableLoot->DespawnTimestamp - timestamp;
						}
					}
				}
			}
						   break;
			case EType::Forage: {
				auto ForageableLoot = static_cast<ABP_ValeriaGatherable_C*>(entry->Actor);
				if (IsActorValid(ForageableLoot) && ForageableLoot->bActorEnableCollision) {
					if (ForageableLoot->Gatherable && ForageableLoot->Gatherable->IsValidLowLevel() && ForageableLoot->Gatherable->TotalGatherCount > 0) {
						entry->Despawn = ForageableLoot->Gatherable->GetSecondsUntilDespawn();
					}
				}

			}
							  break;
			}
		}
	}
}

std::vector<std::shared_ptr<FEntry>> ActorHandler::GetActors() {
	if (bIsTraveling) return {};
	std::lock_guard<std::mutex> lock(ActorCacheMutex);
	return ActorCache;
}

std::vector<std::shared_ptr<FEntry>> ActorHandler::GetActorsOfType(EType type) {
	if (bIsTraveling) return {};
	auto newActorCache = GetActors();
	std::erase_if(newActorCache, [type](std::shared_ptr<FEntry>& Entry) {
		return !(type & Entry->ActorType());
		});
	return newActorCache;
}

void ActorHandler::RemoveActor(AActor* Actor) {
	ActorCacheMutex.lock();
	std::erase_if(ActorCache, [Actor](std::shared_ptr<FEntry>& Entry) {
		return Entry->Actor == Actor;
		});
	ActorCacheMutex.unlock();
	std::erase_if(Teleporters, [Actor](const AActor* Stored) {
		return Actor == Stored;
		});
}

void ActorHandler::AddClass(UClass* Class) {
	auto FullName = Class->GetFullName();
	auto SpaceLocation = FullName.find(" ");
	auto FullNameWithoutType = std::wstring{ FullName.begin() + SpaceLocation + 1, FullName.end() };
	//std::wcout << L"\nClass Added: " << FullNameWithoutType << L"\n";
	ClassPtrMap[FullNameWithoutType] = Class;
}

void ActorHandler::RemoveClass(UClass* Class) {
	std::erase_if(ClassPtrMap, [Class](const auto& Item) {
		auto const& [stringClass, classPtr] = Item;
		return classPtr == Class;
		});
}

bool ActorHandler::IsActorA(const AActor* Actor, const std::wstring& Class) {
	UStruct* CurrentStruct = Actor->Class;
	do {
		UStruct* Struct = ClassLookup(Class);
		if (Struct && CurrentStruct == Struct)
		{
			return true;
		}
		CurrentStruct = CurrentStruct->Super;
	} while (CurrentStruct && CurrentStruct != AActor::StaticClass());
	return false;
}

std::map<std::string, AActor*> ActorHandler::GetTeleporters(const AValeriaCharacter* ValeriaCharacter)
{
	std::map<std::string, AActor*>TeleMap = {};
	for (auto Actor : Teleporters) {
		auto Teleport = static_cast<AVAL_TeleporterBase*>(Actor);
		if (auto Origin = Teleport->TeleportOrigin; Origin) {
			if (auto Asset = Origin->TargetTravelAsset; Asset) {
				if (Asset->ArePlayerTagRequirementsMet(ValeriaCharacter)) {
					auto TeleName = Asset->GetName();
					if (auto ReadableName = TeleporterMap.find(TeleName); ReadableName != TeleporterMap.end()) {
						TeleName = ReadableName->second;
					}
					if (TeleName == "DO NOT USE") continue;
					TeleMap.emplace(TeleName, Actor);
				}
			}
		}
	}
	return TeleMap;
}

bool FEntry::ShouldShow(const AValeriaCharacter* ValeriaCharacter) {
	bool bShouldDraw = false;
	switch (this->ActorType()) {
	case EType::Forage:
		if (this->Actor->bActorEnableCollision) {
			if (this->Quality() == 0) { 
				if (!this->Infected()) {
					bShouldDraw = HUDDetours::Forageables[this->Type()][0];
				} else {
					bShouldDraw = HUDDetours::Forageables[this->Type()][2];
				}
			} else {
				bShouldDraw = HUDDetours::Forageables[this->Type()][this->Quality()];
			}
		}		
		break;
	case EType::Ore:
		if (HUDDetours::Ores[this->Type()][this->Variant()]) {
			auto Ore = static_cast<ABP_ValeriaGatherableLoot_C*>(this->Actor);
			bShouldDraw = IsActorValid(Ore) && Ore->IAmAlive && (IsComponentValid(Ore->GatherableLoot) && !Ore->GatherableLoot->HasBeenGatheredByPlayer(ValeriaCharacter));
		}
		break;
	case EType::Players:
		if (this->DisplayName.empty()) break;
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::Player)];
		break;
	case EType::Animal:
		bShouldDraw = HUDDetours::Animals[this->Type()][this->Variant()];
		break;
	case EType::Tree:
		if (HUDDetours::Trees[this->Type()][this->Variant()]) {
			auto Tree = static_cast<ABP_ValeriaGatherableLoot_C*>(this->Actor);
			bShouldDraw = IsActorValid(Tree) && Tree->IAmAlive;
		}
		break;
	case EType::Bug:
		if (this->Quality() == 0) { 
			if (!this->Infected()) {
				bShouldDraw = HUDDetours::Bugs[this->Type()][this->Variant()][0];
			} else {
				bShouldDraw = HUDDetours::Bugs[this->Type()][this->Variant()][2];
			}
		} else {
			bShouldDraw = HUDDetours::Bugs[this->Type()][this->Variant()][this->Quality()];
		}
		break;
	case EType::NPCs:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::NPC)];
		break;
	case EType::Loot:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::Loot)];
		break;
	case EType::Quest:
		if (HUDDetours::Singles[static_cast<int>(EOneOffs::Quest)]) {
			if (Distance > 250) break; // quests don't always update collision until within this range
			if (!this->Actor->bActorEnableCollision) {
				break;
			}
			switch (Type()) {
			case 1: // BP_QuestItem_BASE
			{
				if (Distance > 125) break;
				auto Quest = static_cast<ABP_ValeriaGatherable_C*>(this->Actor);
				bShouldDraw = IsActorValid(Quest) && Quest->Gatherable && Quest->Gatherable->CanBeGatheredBy(ValeriaCharacter);
			}
			break;
			case 2: // BP_SimpleInspect_Base
			{
				auto Quest = static_cast<ABP_SimpleInspect_Base_C*>(this->Actor);
				bShouldDraw = IsActorValid(Quest) && Quest->Interactable && Quest->Interactable->InteractableRequirementsMet(ValeriaCharacter);
			}
			break;
			case 3: // BP_QuestInspect_Base
			{
				auto Quest = static_cast<ABP_QuestInspect_Base_C*>(this->Actor);
				bShouldDraw = IsActorValid(Quest) && Quest->Interactable && Quest->Interactable->InteractableRequirementsMet(ValeriaCharacter);
			}
			}
		}
		break;
	case EType::RummagePiles:
		if (HUDDetours::Singles[static_cast<int>(EOneOffs::RummagePiles)]) {
			auto Pile = static_cast<ATimedLootPile*>(this->Actor);
			bShouldDraw = IsActorValid(Pile) && Pile->bActivated && Pile->CanGather(ValeriaCharacter);
		}
		break;
	case EType::Stables:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::Stables)];
		break;
	case EType::Fish:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::FishHook)];
		break;
	case EType::Pool:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::FishPool)];
		break;
	case EType::Treasure:
		if (HUDDetours::Singles[static_cast<int>(EOneOffs::Treasure)]) {
			if (Distance > 150) break; // Chests don't seem to properly setup collision until in update range
			if (!this->Actor->bActorEnableCollision) break;

			auto Treasure = static_cast<AWorldPersistGatherable*>(this->Actor);
			bShouldDraw = IsActorValid(Treasure) && Treasure->CanGather(ValeriaCharacter);
		}
		break;
	case EType::TimedDrop:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::TimedDrop)];
		break;
	case EType::Relic:
		bShouldDraw = HUDDetours::Singles[static_cast<int>(EOneOffs::Relic)];
		break;
	case EType::Shops:
		if (this->Type() == 1 && HUDDetours::Singles[static_cast<int>(EOneOffs::Decor)]) {
			auto Shop = static_cast<ABP_Valeria_Shop_Gatherable_C*>(this->Actor);
			if (IsActorValid(Shop) && Shop->Gatherable && Shop->Gatherable->ItemType) {
				if (auto ValeriaController = ValeriaCharacter->GetValeriaPlayerController()) {
					bShouldDraw = ValeriaController->EncyclopediaManagerComponent && !ValeriaController->EncyclopediaManagerComponent->HasSeenItem(Shop->Gatherable->ItemType, Shop->Gatherable->QualityStars > 0);
				}
			}
		}
		break;
	case EType::Bubble:
		bShouldDraw = HUDDetours::Animals[this->Type()][this->Variant()];
		break;
	case EType::Breakable:
		if (HUDDetours::Singles[static_cast<int>(EOneOffs::RummagePiles)] && Type() == 1) {
			auto Pile = static_cast<ABP_RummagePile_Breakable_Elderwood_C*>(this->Actor);
			bShouldDraw = IsActorValid(Pile) && Pile->IsActive;
		}
		break;
	default:
		break;
	}
	return bShouldDraw || (HUDDetours::Singles[static_cast<int>(EOneOffs::Others)] && Type() == 0);
}

void ActorHandler::Func_OnRep_ActiveVariants(void* Context, void* TheStack, void* Result) {
	std::cout << "OnRep_ActiveVariants\n";
	auto VariantComponent = static_cast<UVariantComponent*>(Context);
	if (VariantComponent->IsActiveVariant(FlowtreeTag)) {
		auto Tree = VariantComponent->GetOwner();
		for (auto& entry : ActorCache) {
			if (entry->Actor == Tree) {
				entry->setQuality(1);
			}
		}
	}
	else if (VariantComponent->IsActiveVariant(StarQualityTag)) {
		auto BugPlant = VariantComponent->GetOwner();
		for (auto& entry : ActorCache) {
			if (entry->Actor == BugPlant) {
				entry->setQuality(1);
				entry->DisplayName += L" *";
			}
		}
	}
	else if (VariantComponent->IsActiveVariant(InfectedTag)) {
		auto InfectedActor = VariantComponent->GetOwner();
		for (auto& entry : ActorCache) {
			if (entry->Actor == InfectedActor) {
				entry->setInfected(true);
			}
		}
	}
}