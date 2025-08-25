#pragma once

#include <SDK.hpp>
#include <SDK/Palia_parameters.hpp>

#include <map>

class PaliaOverlay;

using namespace SDK;

class FishingDetours final {
public:
	FishingDetours() = default;

	static void SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC);

	static void Func_DoFastAutoFishing(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_DoFishingCaptureOverride(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_DoInstantCatch(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_EndFishingDetoured(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_DoFishingCleanup(const UObject* Context, UFunction* Function, void* Parms);

	static void LoadFishingSpots();

	static std::string OverrideFishingSpot;
	static bool bCaptureFishingSpot;
	static bool bOverrideFishingSpot;
	static bool bEnableAutoFishing;
	static bool bFishingSpotsLoaded;

	static inline std::unordered_map<std::string, FSoftObjectPath> FishingSpotMap = {};
	static inline std::map<std::string, std::string> FishingSpotNameMap = {
		{"","- none -"},
		{"DA_Fishing_Water_Village_River","Kilima River"},
		{"DA_Fishing_Water_Village_RiverSQ","Kilima River (Hotspot)"},
		{"DA_Fishing_Water_Village_Pond","Pond"},
		{"DA_Fishing_Water_Village_Pond_SQ","Pond (Hotspot)"},
		{"DA_Fishing_Water_Village_Lake","Kilima Lake"},
		{"DA_Fishing_Water_Village_LakeSQ","Kilima Lake (Hotspot)"},
		{"DA_Fishing_Water_AZ1_Ocean","Bahari Coast"},
		{"DA_Fishing_Water_AZ1_OceanSQ","Bahari Coast (Hotspot)"},
		{"DA_Fishing_Water_AZ1_River","Bahari River"},
		{"DA_Fishing_Water_AZ1_RiverSQ","Bahari River (Hotspot)"},
		{"DA_Fishing_Water_AZ1_Cave","Cave"},
		{"DA_Fishing_Water_AZ1_CaveSQ","Cave (Hotspot)"},
		{"DA_Fishing_Water_AZ2_Bay","Elderwood Saltwater"},
		{"DA_Fishing_Water_AZ2_Bay_SQ","Elderwood Saltwater (Hotspot)"},
		{"DA_Fishing_Water_AZ2_Bay_Echo","Elderwood Saltwater (Infected)"},
		{"DA_Fishing_Water_AZ2_Pond","Elderwood Freshwater"},
		{"DA_Fishing_Water_AZ2_Pond_SQ","Elderwood Freshwater (Hotspot)"},
		{"DA_Fishing_Water_AZ2_Pond_Echo","Elderwood Freshwater (Infected)"}
	};
};

inline std::string FishingDetours::OverrideFishingSpot;
inline bool FishingDetours::bCaptureFishingSpot = false;
inline bool FishingDetours::bOverrideFishingSpot = false;
inline bool FishingDetours::bEnableAutoFishing = false;
inline bool FishingDetours::bFishingSpotsLoaded = false;
