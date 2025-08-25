#include "PlayerTweaksDetours.h"
#include "Configuration.h"
#include "DetourManager.h"
#include "Utils.h"

#include "SDK/Palia_parameters.hpp"

void PlayerTweaksDetours::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
    DetourManager::AddInstance(VPC);
	DetourManager::AddFunctionListener("Function Engine.PlayerController.ClientRestart", nullptr, &ResetTweaks);
	DetourManager::AddInstance(VC);
	DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Func_DoCharacterTweaks, nullptr);
	DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Func_DoGatherActors, nullptr);
    DetourManager::AddFunctionDetour("Function Palia.VAL_CharacterCustomizationComponent.OnRep_LastCharacterRespecTime", nullptr, &Func_OnRep_LastCharacterRespecTime);
    DetourManager::AddInstance(VC->GetVitals());
    DetourManager::AddFunctionListener("Function Palia.VitalsComponent.OnReplicatedAndNotify", nullptr, &Func_PE_OnReplicatedAndNotify);
}

void PlayerTweaksDetours::Func_DoCharacterTweaks(const UObject* Context, UFunction* Function, void* Parms) {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::minutes>(currentTime - lastAFKPing);
    
    if (elapsedTime.count() < antiAFKInterval &&
        PlayerModsToggle.bUnlimitedWardrobeRespec == Configuration::bEnableUnlimitedWardrobeRespec &&
        PlayerModsToggle.bInteractionsIncrease == Configuration::bEnableInteractionMods &&
        !AreFloatsEqual(PlayerModsToggle.InteractionDistance, Configuration::InteractionDistance) &&
        PlayerModsToggle.bAntiAFK == Configuration::bEnableAntiAfk &&
        PlayerModsToggle.maxJumpModValue == Configuration::CustomMaxJumps) {
        return;
    }
    
    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    const auto ValeriaController = GetValeriaController();
    if (!ValeriaController)
        return;

    // AntiAFK
    if (Configuration::bEnableAntiAfk && elapsedTime.count() >= antiAFKInterval) {
        ValeriaController->Client_InactivityHeartbeat();
        ValeriaController->RpcServer_NotifyInactivityInterrupted();
        lastAFKPing = currentTime;
        antiAFKInterval = RNG(randomEngine);
    }
    
    // Unlimited Wardrobe Respec
    if (PlayerModsToggle.bUnlimitedWardrobeRespec != Configuration::bEnableUnlimitedWardrobeRespec) {
        if(Configuration::bEnableUnlimitedWardrobeRespec) {
            ValeriaController->ValeriaCharacter->CharacterCustomizationComponent->LastCharacterRespecTime = 0;
        }
        PlayerModsToggle.bUnlimitedWardrobeRespec = Configuration::bEnableUnlimitedWardrobeRespec;
    }

    // InteractionMod
    if (PlayerModsToggle.bInteractionsIncrease != Configuration::bEnableInteractionMods || !AreFloatsEqual(PlayerModsToggle.InteractionDistance, Configuration::InteractionDistance)) {
        ValeriaController->InteractableSearchDistanceAhead = Configuration::bEnableInteractionMods ? Configuration::InteractionDistance : 100.0f;
        
        PlayerModsToggle.bInteractionsIncrease = Configuration::bEnableInteractionMods;
        PlayerModsToggle.InteractionDistance = Configuration::InteractionDistance;
    }

    // Jump Mod
    if (PlayerModsToggle.maxJumpModValue != Configuration::CustomMaxJumps) {
        ValeriaCharacter->JumpMaxCount = Configuration::CustomMaxJumps ? Configuration::CustomMaxJumps : 1;
        
        PlayerModsToggle.maxJumpModValue = Configuration::CustomMaxJumps;
    }
}

void PlayerTweaksDetours::ResetTweaks(const UObject* Context, UFunction* Function, void* Parms) {
    PlayerModsToggle = {};
}

void PlayerTweaksDetours::Func_OnRep_LastCharacterRespecTime(void* Context, void* TheStack, void* Result) {
    if(Configuration::bEnableUnlimitedWardrobeRespec) {
        const auto ValeriaController = GetValeriaController();
        if (ValeriaController) {
            ValeriaController->ValeriaCharacter->CharacterCustomizationComponent->LastCharacterRespecTime = 0;
        }
    }
}

bool TeleportToGatherables = false;
void PlayerTweaksDetours::Func_DoGatherActors(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableAutoGather)
        return;

    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;
    
    for (auto& cachedActors : ActorHandler::GetActorsOfType(EType::Forage | EType::Loot)) {
        // Do nothing for unselected ESP animals
        if(!cachedActors->ShouldShow(ValeriaCharacter)) continue;        
        
        const auto ValeriaAnimComponent = ValeriaCharacter->GetAbilityAnimation();
        if (!IsComponentValid(ValeriaAnimComponent))
            return;

        auto ValeriaMovementComponent = ValeriaCharacter->GetValeriaCharacterMovementComponent();
        if (!ValeriaMovementComponent)
            return;

        if (!cachedActors->Actor)
            continue;

        switch (cachedActors->ActorType()) {
        case EType::Forage: {
            auto gatherableActor = static_cast<ABP_ValeriaGatherable_C*>(cachedActors->Actor);
            if(!IsActorValid(gatherableActor))
                continue;
            
            auto* gatherableInteractable = gatherableActor->Interactable;
            if(!IsComponentValid(gatherableInteractable))
                continue;

            gatherableActor->bForceNetAddressable = true;

            if (!TeleportToGatherables && cachedActors->Distance > 0.75f && cachedActors->Distance < 8.0f) {
                gatherableInteractable->bSendTelemetryEventOnServerInteract = false;
                        
                ValeriaCharacter->Interactor->HighlightInteractable(gatherableInteractable);

                FInteractEventParams Params{
                    .Type = EInteractEventType::Pressed,
                    .Index = EInteractEventIndex::Primary,
                    .InputType = EInputType::Keyboard,
                    .Handled = true
                };

                ValeriaCharacter->Interactor->InteractWithHighlighted(Params);
                ValeriaAnimComponent->StopAll(0.0f);
            }
        }
        break;
        default:

            auto lootActor = static_cast<ABP_Loot_C*>(cachedActors->Actor);
            if(!IsActorValid(lootActor))
                continue;
            
            auto* gatherableInteractable = lootActor->Interactable;
            if (TeleportToGatherables || !IsComponentValid(gatherableInteractable))
                continue;

            lootActor->bForceNetAddressable = true;

            if (cachedActors->Distance > 0.75f && cachedActors->Distance < 8.0f) {
                gatherableInteractable->bSendTelemetryEventOnServerInteract = false;
                        
                ValeriaCharacter->Interactor->HighlightInteractable(gatherableInteractable);
                        
                FInteractEventParams Params{
                    .Type = EInteractEventType::Pressed,
                    .Index = EInteractEventIndex::Primary,
                    .InputType = EInputType::Keyboard,
                    .Handled = true
                };

                ValeriaCharacter->Interactor->InteractWithHighlighted(Params);
                ValeriaAnimComponent->StopAll(0.0f);
            }
            break;
        }
    }
}

// Auto Focus
void PlayerTweaksDetours::Func_PE_OnReplicatedAndNotify(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableAutoFocus) 
        return;
    auto VitalsComponent = static_cast<const UVitalsComponent*>(Context);
    auto Focus = VitalsComponent->GetVital(EVitalType::Focus);
    auto FocusMax = VitalsComponent->GetVitalMax(EVitalType::Focus);
    if ((100 * Focus) / FocusMax > Configuration::FocusBelowPercent) 
        return;
    //std::cout << "\n  Focus: " << Focus << "/" << FocusMax << "\n\n";
    auto ValeriaCharacter = static_cast<AValeriaCharacter*>(VitalsComponent->GetOwner());
    auto Inventory = ValeriaCharacter->GetInventory();
    auto ConsumablesTag = UBlueprintGameplayTagLibrary::MakeGameplayTagContainerFromTag(FGameplayTag{ UKismetStringLibrary::Conv_StringToName(L"Item.Consumable") });
    auto Consumables = Inventory->GetItemsWithTags(ConsumablesTag, FGameplayTagContainer{});
    auto QualityConfig = UValeriaBlueprintFunctionLibrary::GetQualityGlobalConfig(ValeriaCharacter);
    FValeriaItem BestItem;
    int32 BestItemFocus = 0;
    bool BestItemSQ = false;
    for (auto Item : Consumables) {
        int32 FocusGained = 0;
        bool ItemSQ = false;
        for (auto Reward : Item.ItemType->ConsumeRewards) {
            if (Reward.VitalType == EVitalType::Focus) {
                FocusGained += Reward.VitalAmount;
            }
        }
        if (Item.MetaData.QualityStars > 0) {
            FocusGained = (int32)((float)FocusGained * QualityConfig->ConsumeRewardFocusQualityMultiplier);
            ItemSQ = true;
        }
        if (FocusGained > BestItemFocus && FocusGained < (FocusMax - Focus)) {
            BestItemFocus = FocusGained;
            BestItem = Item;
            BestItemSQ = ItemSQ;
        }
    }
    if (BestItemFocus > 0 && !UValeriaBlueprintFunctionLibrary::ItemIsEmpty(BestItem)) {
        auto BagSlot = Inventory->FindItemByType(BestItem.ItemType, BestItemSQ);
        if (BagSlot.BagIndex != -1 && BagSlot.SlotIndex != -1) {
            if (auto ValeriaController = ValeriaCharacter->GetValeriaPlayerController()) {
                ValeriaController->ConsumeItem(BagSlot);
            }
        }
    }
}