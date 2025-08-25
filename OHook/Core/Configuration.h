#pragma once

#include "io/IOManager.h"
#include "ActorHandler.h"
#include <json/json.h>
#include <imgui.h>
#include <map>

struct FCreatureType {
	FEntryHunting::TypeEnum Kind;
	FEntryHunting::VariantEnum Quality;

	bool operator<(const FCreatureType& other) const {
		return std::tie(Kind, Quality) < std::tie(other.Kind, other.Quality);
	}
};

struct FBugType {
	FEntryBug::TypeEnum Kind;
	FEntryBug::VariantEnum Quality;
	bool Starred = false;

	bool operator<(const FBugType& other) const {
		return std::tie(Kind, Quality, Starred) < std::tie(other.Kind, other.Quality, other.Starred);
	}
};

enum ESaveFile {
	NONE,
	OverlaySettings,
	ESPSettings,
	AimSettings,
	MovementSettings,
	ToolSkillsSettings,
	SellItemsSettings,
	ModSettings,
	CustomThemeSettings,
	HotkeySettings,
	SAVE_ALL
};

// Forward declaration of PaliaOverlay class
class PaliaOverlay;

class Configuration : public IOManager {
// private:
	static bool ConfigLoaded;

	static bool LoadOverlaySettings(const std::string& filePath, Json::Value& config);
	static bool LoadESPSettings(const std::string& filePath, Json::Value& config);
	static bool LoadAimSettings(const std::string& filePath, Json::Value& config);
	static bool LoadMovementSettings(const std::string& filePath, Json::Value& config);
	static bool LoadToolSkillsSettings(const std::string& filePath, Json::Value& config);
	static bool LoadSellItemsSettings(const std::string& filePath, Json::Value& config);
	static bool LoadModSettings(const std::string& filePath, Json::Value& config);
	static bool LoadCustomThemeSettings(const std::string& filePath, Json::Value& config);
	static bool LoadHotkeySettings(const std::string& filePath, Json::Value& config);
	
	static void SaveOverlaySettings(Json::Value& config);
	static void SaveESPSettings(Json::Value& config);
	static void SaveAimSettings(Json::Value& config);
	static void SaveMovementSettings(Json::Value& config);
	static void SaveToolSkillsSettings(Json::Value& config);
	static void SaveSellItemsSettings(Json::Value& config);
	static void SaveModSettings(Json::Value& config);
	static void SaveCustomThemeSettings(Json::Value& config);
	static void SaveHotkeySettings(Json::Value& config);
	
public:
	Configuration() = default;
	~Configuration() = default;

	static void Load();
	static void Save(ESaveFile save_file = ESaveFile::SAVE_ALL);
	static void ApplyCustomTheme();
	
#pragma region ConfigVars

	static bool ConfigIsCorrupt;
	static std::vector<std::string> corruptConfigs;
	
	// ESP

	static bool bEnableESP;
	static double CullDistance;
	static float ESPTextScale;
	static bool bEnableESPDistance;
	static bool bEnableESPDespawnTimer;
	static bool bEnableMapESP;
	static bool bEnableESPIcons;
	
	#pragma region ESP

	// ESP Colors
	static std::map<FEntryMining::TypeEnum, ImU32> OreColors;
	static std::map<FCreatureType, ImU32> AnimalColors;
	static std::map<EOneOffs, ImU32> SingleColors;
	static std::map<FEntryLumber::TypeEnum, ImU32> TreeColors;
	static std::map<FEntryGatherable::TypeEnum, ImU32> ForageableColors;
	static std::map<FBugType, ImU32> BugColors;

#pragma endregion

	// Aim

	// InteliAim
	static bool bEnableInteliAim;
	static float FOVRadius;
	static bool bHideFOVCircle;
	static float CircleAlpha;
	static bool bDrawCrosshair;

	// InteliTarget
	static bool bEnableSilentAimbot;
	static bool bTeleportToTargeted;
	static bool bAvoidTeleportingToPlayers;
	static bool bDoRadiusPlayersAvoidance;
	static int TeleportPlayerAvoidanceRadius;
	
	// Classic Aimbot
	static bool bEnableAimbot;
	static float AimbotSmoothing;
	static int AimbotKey;
	static bool bAimbotOnlyAnimals;
	

	
	// Movement
	static float CustomWalkSpeed;
	static float CustomSprintSpeed;
	static float CustomClimbingSpeed;
	static float CustomGlidingSpeed;
	static float CustomGlidingFallSpeed;
	static float CustomJumpVelocity;
	static int CustomMaxJumps;
	static float CustomMaxStepHeight;

	

	// ToolSkills

	// Tool Swinging
	static bool bEnableAutoSwinging;
	static bool bResourceAutoEquipTool;
	static bool bAutoSwingingRequireESP;
	static bool bAvoidSwingingLowDurability;
	static bool bAvoidGroveChopping;
	static bool bAvoidPlotSwinging;
	static bool bAvoidSwingingNearPlayers;
	static float SwingPlayerAvoidDistance;
	
	// Bug Catching
	static bool bEnableBugCatching;
	static bool bBugAutoEquipTool;
	static bool bAutoCatchingRequireESP;
	static bool bAvoidCatchingLowDurability;
	static float BugCatchingDistance;
	static int BugSpeedPreset;
	static int BugCatchingDelay;
	static bool bAvoidCatchingNearPlayers;
	static float CatchingPlayerAvoidDistance;
	
	// Animal Hunting
	static bool bEnableAnimalHunting;
	static bool bAnimalAutoEquipTool;
	static bool bAutoHuntingRequireESP;
	static bool bAvoidHuntingLowDurability;
	static float AnimalHuntingDistance;
	static int AnimalSpeedPreset;
	static int AnimalHuntingDelay;
	static bool bAvoidHuntingNearPlayers;
	static float HuntingPlayerAvoidDistance;

	// Fishing Options
	static bool bFishingNoDurability;
	static bool bFishingMultiplayerHelp;
	static bool bFishingInstantCatch;
	static bool bFishingPerfectCatch;
	static bool bRequireClickFishing;

	// Others
	static bool bEnableAutoGather;
	static bool bEnableCookingMinigameSkip;
	static bool bEnableAutoFocus;
	static int FocusBelowPercent;

	// Gardening
	static bool bGardeningAutoHarvest;
	static bool bGardeningAutoTill;
	static bool bGardeningAutoWeed;
	static bool bGardeningAutoFertilize;
	static int GardeningFertilizerQty;
	static bool bGardeningAutoReplant;
	static bool bGardeningAutoWater;

	// SellItems

	// Buying
	static bool bEnableBuyMultiplier;
	static bool bEnableCtrlClickBuy;
	static int buyMultiplierValue;

	// InventorySelector;
	static int InventoryCount;
	static bool InventorySlot[5][8];
	static bool InventoryAmmo;
	
	// AutoSell
	static bool bFishingSell;
	static bool bFishingSellSQ;
	static bool bFishingSellRarity[7];
	static bool bBugSell;
	static bool bBugSellSQ;
	static bool bBugSellRarity[7];
	static bool bHuntingSell;
	static bool bHuntingSellSQ;
	static bool bHuntingSellRarity[7];
	static bool bFlowerSell;
	static bool bForageableSell;
	static bool bForageableSellSQ;
	static bool bForageableSellRarity[7];
	static bool bTreeSell;
	static bool bTreeSellRarity[5];
	static bool bJunkSell;

	// AutoOpen
	static bool bAutoOpenWaterlogged;
	static bool bAutoOpenOyster;
	static bool bAutoOpenElderClam;

	// AutoStorage
	static bool bAutoStoreDecor;
	

	// Mods

	// Character
	static bool bEnableAntiAfk;
	static bool bEnableUnlimitedWardrobeRespec;
	static bool bEnableInteractionMods;
	static float InteractionDistance;
	static bool bEnableWaypointTeleport;
	static bool bEasyModeActive;
	
	// Fun
	static bool bPlaceAnywhere;
	static double PlacementRotation;
	static bool bEnableOutfitCustomization;
	static bool bEnableContentUnlocker;
	static bool bEnableFreeLandscape;
	static bool bEnableShowWeeklyWants;
	static bool bEnableToolBricker;
	static int32 ToolBrickerMaxSell;
	static bool bEnableRequestMods;
	static bool bEnableUnseenItems;

	static bool bEnablePrizeWheel;
	static bool bPrizeWheelUseLocked;
	static bool PrizeWheelSlots[9];

	// Origin
	static bool bFirstUse;
	static bool bShowWatermark;
	static bool showEnabledFeaturesWindow;
	static bool showPlayerDistancesWindow;
	static int selectedTheme;
	static int cfg_SelectedLanguage;
	static std::map<int, ImVec4> customColors;
	
	// Window configs
	static float windowSizeX;
	static float windowSizeY;
	static float activeWindowPosX;
	static float activeWindowPosY;
	static float playerWindowPosX;
	static float playerWindowPosY;
};

#pragma endregion