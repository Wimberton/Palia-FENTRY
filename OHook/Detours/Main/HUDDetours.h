#pragma once

#include "PaliaOverlay.h"
#include "DetourManager.h"
#include <SDK.hpp>

class PaliaOverlay;

using namespace SDK;

class HUDDetours final {
public:
	HUDDetours() = default;

	static void SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC);

	static void ReceiveDrawHUD(const UObject* Context, UFunction* Function, void* Parms);

	static UFont* Roboto;

	static bool Ores[static_cast<int>(FEntryMining::TypeEnum::MAX)][static_cast<int>(FEntryMining::VariantEnum::MAX)];
	static bool Animals[static_cast<int>(FEntryHunting::TypeEnum::MAX)][static_cast<int>(FEntryHunting::VariantEnum::MAX)];
	static bool Bugs[static_cast<int>(FEntryBug::TypeEnum::MAX)][static_cast<int>(FEntryBug::VariantEnum::MAX)][3];
	static bool Trees[static_cast<int>(FEntryLumber::TypeEnum::MAX)][static_cast<int>(FEntryLumber::VariantEnum::MAX)];
	static bool Singles[static_cast<int>(EOneOffs::MAX)];

	static bool Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MAX)][3];
	static int ForageableCommon[8];
	static int ForageableUncommon[12];
	static int ForageableRare[5];
	static int ForageableEpic[3];
};

inline UFont* HUDDetours::Roboto = nullptr;

// Ores[Type][Size]
inline bool HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::MAX)][static_cast<int>(FEntryMining::VariantEnum::MAX)] = {};
// Animals[Type][Size]
inline bool HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::MAX)][static_cast<int>(FEntryHunting::VariantEnum::MAX)] = {};
// Bugs[Type][Size][Starred]
inline bool HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::MAX)][static_cast<int>(FEntryBug::VariantEnum::MAX)][3] = {};
// Trees[Type][Size]
inline bool HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::MAX)][static_cast<int>(FEntryLumber::VariantEnum::MAX)] = {};
// Singles[Type]
inline bool HUDDetours::Singles[static_cast<int>(EOneOffs::MAX)] = {};
// Forageables[Type][Starred]
inline bool HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MAX)][3] = {};

// Forageables[Type][]
inline int HUDDetours::ForageableCommon[8] = {
	static_cast<int>(FEntryGatherable::TypeEnum::Oyster),
	static_cast<int>(FEntryGatherable::TypeEnum::Shell),
	static_cast<int>(FEntryGatherable::TypeEnum::Sundrop),
	static_cast<int>(FEntryGatherable::TypeEnum::MushroomRed),

	static_cast<int>(FEntryGatherable::TypeEnum::StaircaseMushroom),
	static_cast<int>(FEntryGatherable::TypeEnum::FloatfishMushroom),
	static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodOrchid),
	static_cast<int>(FEntryGatherable::TypeEnum::PiksiiBerries),
};
inline int HUDDetours::ForageableUncommon[12] = {
	static_cast<int>(FEntryGatherable::TypeEnum::Coral),
	static_cast<int>(FEntryGatherable::TypeEnum::PoisonFlower),
	static_cast<int>(FEntryGatherable::TypeEnum::WaterFlower),
	static_cast<int>(FEntryGatherable::TypeEnum::EmeraldCarpet),
	static_cast<int>(FEntryGatherable::TypeEnum::SpicedSprouts),
	static_cast<int>(FEntryGatherable::TypeEnum::SweetLeaves),
	static_cast<int>(FEntryGatherable::TypeEnum::Garlic),
	static_cast<int>(FEntryGatherable::TypeEnum::Ginger),
	static_cast<int>(FEntryGatherable::TypeEnum::GreenOnion),
	static_cast<int>(FEntryGatherable::TypeEnum::ElderClamMushroom),
	static_cast<int>(FEntryGatherable::TypeEnum::BatterflyBeans),
	static_cast<int>(FEntryGatherable::TypeEnum::KopaaNut),
};
inline int HUDDetours::ForageableRare[5] = {
	static_cast<int>(FEntryGatherable::TypeEnum::DragonsBeard),
	static_cast<int>(FEntryGatherable::TypeEnum::MushroomBlue),
	static_cast<int>(FEntryGatherable::TypeEnum::HeatRoot),
	static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodLotus),
	static_cast<int>(FEntryGatherable::TypeEnum::FlowTato),
};
inline int HUDDetours::ForageableEpic[3] = {
	static_cast<int>(FEntryGatherable::TypeEnum::Heartdrop),
	static_cast<int>(FEntryGatherable::TypeEnum::DariCloves),
	static_cast<int>(FEntryGatherable::TypeEnum::Elderflower),
};