#include "Configuration.h"
#include "HotkeysManager.h"
#include "HUDDetours.h"
#include "PaliaOverlay.h"
#include "ImGuiExt.h"
#include "json/json.h"

#include <imgui.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <wrl/internal.h>

#pragma region VarsInit

// Config vars
#pragma region ConfigFiles

bool Configuration::ConfigLoaded = false;

bool Configuration::ConfigIsCorrupt = false;
std::vector<std::string> Configuration::corruptConfigs;

// Path for the configuration file
std::string configDirectory = R"(C:\ProgramData\OriginPalia\config)";
std::string overlayConfigFilePath = configDirectory + "\\Overlay_settings.json";
std::string espConfigFilePath = configDirectory + "\\ESP_settings.json";
std::string aimConfigFilePath = configDirectory + "\\Aim_settings.json";
std::string movementConfigFilePath = configDirectory + "\\Movement_settings.json";
std::string toolskillsConfigFilePath = configDirectory + "\\ToolSkills_settings.json";
std::string sellitemsConfigFilePath = configDirectory + "\\SellItems_settings.json";
std::string modConfigFilePath = configDirectory + "\\Mod_settings.json";
std::string customThemeConfigFilePath = configDirectory + "\\Custom_theme.json";
std::string hotkeysConfigFilePath = configDirectory + "\\Hotkey_settings.json";
Json::Value overlaySettings;
Json::Value espSettings;
Json::Value aimSettings;
Json::Value movementSettings;
Json::Value toolskillsSettings;
Json::Value sellitemsSettings;
Json::Value modSettings;
Json::Value customThemeSettings;
Json::Value hotkeySettings;

#pragma endregion

// ESP-Tab
#pragma region ESP

bool Configuration::bEnableESP = true;
float Configuration::ESPTextScale = 1.0f;
double Configuration::CullDistance = 300.0;
bool Configuration::bEnableESPDistance = true;
bool Configuration::bEnableESPDespawnTimer = false;
bool Configuration::bEnableMapESP = false;
bool Configuration::bEnableESPIcons = true;

// ESP Colors
std::map<FEntryMining::TypeEnum, ImU32> Configuration::OreColors = {
    {FEntryMining::TypeEnum::Unknown, IM_COL32(0xFF, 0xFF, 0xFF, 0xFF)},
    {FEntryMining::TypeEnum::Stone, IM_COL32(0x88, 0x8C, 0x8D, 0xFF)}, // Stone
    {FEntryMining::TypeEnum::Whitestone, IM_COL32(0x88, 0x8C, 0x8D, 0xFF)}, // Whitestone
    {FEntryMining::TypeEnum::Copper, IM_COL32(0xB8, 0x73, 0x33, 0xFF)}, // Copper
    {FEntryMining::TypeEnum::Clay, IM_COL32(0xAD, 0x50, 0x49, 0xFF)}, // Clay
    {FEntryMining::TypeEnum::Iron, IM_COL32(0xA1, 0x9D, 0x94, 0xFF)}, // Iron
    {FEntryMining::TypeEnum::Silver, IM_COL32(0xAA, 0xA9, 0xAD, 0xFF)}, // Silver
    {FEntryMining::TypeEnum::Gold, IM_COL32(0xDB, 0xAC, 0x34, 0xFF)}, // Gold
    {FEntryMining::TypeEnum::Palium, IM_COL32(0x94, 0xA0, 0xE2, 0xFF)}, // Palium
    {FEntryMining::TypeEnum::Platinum, IM_COL32(0xC8, 0xD0, 0xD8, 0xFF) } // Platinum
};

std::map<EOneOffs, ImU32> Configuration::SingleColors = {
    {EOneOffs::Player, IM_COL32(0xFF, 0x63, 0x47, 0xFF)}, // Tomato Red
    {EOneOffs::NPC, IM_COL32(0xDE, 0xB8, 0x87, 0xFF)}, // Burly Wood
    {EOneOffs::FishHook, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)}, // Washed Gray
    {EOneOffs::FishPool, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)}, // Washed Gray
    {EOneOffs::Loot, IM_COL32(0xEE, 0x82, 0xEE, 0xFF)}, // Violet
    {EOneOffs::Quest, IM_COL32(0xFF, 0xA5, 0x00, 0xFF)}, // Orange
    {EOneOffs::RummagePiles, IM_COL32(0xFF, 0x45, 0x00, 0xFF)}, // Orange Red
    {EOneOffs::Treasure, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Bright Gold
    {EOneOffs::Stables, IM_COL32(0x88, 0x45, 0x13, 0xFF)}, // Saddle Brown
    {EOneOffs::TimedDrop, IM_COL32(0xDB, 0xAC, 0x34, 0xFF)}, // Gold
    {EOneOffs::Relic, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)}, // Washed Gray
    {EOneOffs::Others, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)}, // Washed Gray
    {EOneOffs::Decor, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)}, // Washed Gray
};

std::map<FEntryLumber::TypeEnum, ImU32> Configuration::TreeColors = {
    {FEntryLumber::TypeEnum::Unknown, IM_COL32(0xFF, 0xFF, 0xFF, 0xFF)},
    {FEntryLumber::TypeEnum::Flow, IM_COL32(0x67, 0x00, 0xEA, 0xFF)},
    {FEntryLumber::TypeEnum::Heartwood, IM_COL32(0x00, 0xFF, 0x00, 0xFF)},
    {FEntryLumber::TypeEnum::Sapwood, IM_COL32(0x00, 0xFF, 0x00, 0xFF)},
    {FEntryLumber::TypeEnum::Ancientwood, IM_COL32(0x5A, 0x3E, 0x2B, 0xFF)},
    {FEntryLumber::TypeEnum::Bush, IM_COL32(0xFF, 0xFF, 0xFF, 0xFF)},
    {FEntryLumber::TypeEnum::Infected, IM_COL32(0xC0, 0xC0, 0xC0, 0xFF)},
};

std::map<FEntryGatherable::TypeEnum, ImU32> Configuration::ForageableColors = {
    // Commons
    { FEntryGatherable::TypeEnum::Oyster, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::Shell, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::Sundrop, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::MushroomRed, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::StaircaseMushroom, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::FloatfishMushroom, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::ElderwoodOrchid, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::PiksiiBerries, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::EchoEssence, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    { FEntryGatherable::TypeEnum::Honey, IM_COL32(0xCD, 0xCD, 0xCD, 0xFF)}, // Light Gray
    // Uncommons
    { FEntryGatherable::TypeEnum::Coral, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::PoisonFlower, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::WaterFlower, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::EmeraldCarpet, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::SpicedSprouts, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::SweetLeaves, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::Garlic, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::Ginger, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::GreenOnion, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::ElderClamMushroom, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::BatterflyBeans, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    { FEntryGatherable::TypeEnum::KopaaNut, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    // Rare
    { FEntryGatherable::TypeEnum::DragonsBeard, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    { FEntryGatherable::TypeEnum::MushroomBlue, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    { FEntryGatherable::TypeEnum::HeatRoot, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    { FEntryGatherable::TypeEnum::ElderwoodLotus, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    { FEntryGatherable::TypeEnum::FlowTato, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    // Epic
    { FEntryGatherable::TypeEnum::Heartdrop, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    { FEntryGatherable::TypeEnum::DariCloves, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    { FEntryGatherable::TypeEnum::Elderflower, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
};

std::map<FCreatureType, ImU32> Configuration::AnimalColors = {
    {{ FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue

    {{ FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{ FEntryHunting::TypeEnum::Chase, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold

    {{ FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue

    {{ FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue

    {{ FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue

    {{ FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier1 }, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Light Gray
    {{ FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier2 }, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{ FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier3 }, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
};

std::map<FBugType, ImU32> Configuration::BugColors = {
    //Batterfly
    {{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Uncommon2}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    //Bees
    {{FEntryBug::TypeEnum::Bee, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Bee, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Beetles
    {{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Epic}, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    //BeetleAZ2
    {{FEntryBug::TypeEnum::BeetleAZ2, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::BeetleAZ2, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Butterfly
    {{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Epic}, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    //Cicada
    {{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Crab
    {{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Cricket
    {{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Dragonfly
    {{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Epic}, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    //Glowbug
    {{FEntryBug::TypeEnum::Glowbug, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Glowbug, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Ladybug
    {{FEntryBug::TypeEnum::Ladybug, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Ladybug, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Mantis
    {{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Rare2}, IM_COL32(0x00, 0xBF, 0xFF, 0xFF)}, // Deep Sky Blue
    {{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Epic}, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    //Moth
    {{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //Pede
    {{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Rare2}, IM_COL32(0x00, 0xBF, 0xFF, 0xFF)}, // Deep Sky Blue
    //Snail
    {{FEntryBug::TypeEnum::Snail, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
    {{FEntryBug::TypeEnum::Snail, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    //RockHopper
    {{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Rare}, IM_COL32(0x1E, 0x90, 0xFF, 0xFF)}, // Dodger Blue
    {{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Epic}, IM_COL32(0xFF, 0xD7, 0x00, 0xFF)}, // Gold
    //Piksii
    {{FEntryBug::TypeEnum::Piksii, FEntryBug::VariantEnum::Common}, IM_COL32(0x80, 0x80, 0x80, 0xFF)}, // Gray
    {{FEntryBug::TypeEnum::Piksii, FEntryBug::VariantEnum::Uncommon}, IM_COL32(0x32, 0xCD, 0x32, 0xFF)}, // Lime Green
};

#pragma endregion

// Aim-Tab
#pragma region Aim

// InteliAim
bool Configuration::bEnableInteliAim = true;
float Configuration::FOVRadius = 120.0f;
bool Configuration::bHideFOVCircle = false;
float Configuration::CircleAlpha = 1.0f;
bool Configuration::bDrawCrosshair = true;

// InteliTarget
bool Configuration::bEnableSilentAimbot = false;
bool Configuration::bTeleportToTargeted = true;
bool Configuration::bAvoidTeleportingToPlayers = true;
bool Configuration::bDoRadiusPlayersAvoidance = true;
int Configuration::TeleportPlayerAvoidanceRadius = 30;

// Classic Aimbot
bool Configuration::bEnableAimbot = false;
float Configuration::AimbotSmoothing = 5.0f;
int Configuration::AimbotKey = VK_LBUTTON; // Left mouse button
bool Configuration::bAimbotOnlyAnimals = true;

#pragma endregion

// Movement-Tab
#pragma region Movement

float Configuration::CustomWalkSpeed = 565.0f;
float Configuration::CustomSprintSpeed = 1.65f;
float Configuration::CustomClimbingSpeed = 80.0f;
float Configuration::CustomGlidingSpeed = 900.0f;
float Configuration::CustomGlidingFallSpeed = 250.0f;
float Configuration::CustomJumpVelocity = 700.0f;
int Configuration::CustomMaxJumps = 1;
float Configuration::CustomMaxStepHeight = 45.0f;

#pragma endregion

// ToolSkills-Tab
#pragma region ToolSkills

// Auto Tool Swinging
bool Configuration::bEnableAutoSwinging = false;
bool Configuration::bResourceAutoEquipTool = false;
bool Configuration::bAutoSwingingRequireESP = false;
bool Configuration::bAvoidSwingingLowDurability = false;
bool Configuration::bAvoidGroveChopping = true;
bool Configuration::bAvoidPlotSwinging = true;
bool Configuration::bAvoidSwingingNearPlayers = false;
float Configuration::SwingPlayerAvoidDistance = 30.0f;

// Auto Bug Catching
bool Configuration::bEnableBugCatching = false;
bool Configuration::bBugAutoEquipTool = false;
bool Configuration::bAutoCatchingRequireESP = false;
bool Configuration::bAvoidCatchingLowDurability = false;
float Configuration::BugCatchingDistance = 10.0f;
int Configuration::BugSpeedPreset = 1;
int Configuration::BugCatchingDelay = 750;
bool Configuration::bAvoidCatchingNearPlayers = false;
float Configuration::CatchingPlayerAvoidDistance = 30.0f;

// Auto Animal Hunting
bool Configuration::bEnableAnimalHunting = false;
bool Configuration::bAnimalAutoEquipTool = false;
bool Configuration::bAutoHuntingRequireESP = false;
bool Configuration::bAvoidHuntingLowDurability = false;
float Configuration::AnimalHuntingDistance = 10.0f;
int Configuration::AnimalSpeedPreset = 1;
int Configuration::AnimalHuntingDelay = 750;
bool Configuration::bAvoidHuntingNearPlayers = false;
float Configuration::HuntingPlayerAvoidDistance = 30.0f;

// Fishing
bool Configuration::bFishingNoDurability = true;
bool Configuration::bFishingMultiplayerHelp = false;
bool Configuration::bFishingInstantCatch = false;
bool Configuration::bFishingPerfectCatch = true;
bool Configuration::bRequireClickFishing = true;

// Others
bool Configuration::bEnableAutoGather = false;
bool Configuration::bEnableCookingMinigameSkip = false;
bool Configuration::bEnableAutoFocus = false;
int Configuration::FocusBelowPercent = 50;

// Gardening
bool Configuration::bGardeningAutoHarvest = false;
bool Configuration::bGardeningAutoTill = false;
bool Configuration::bGardeningAutoWeed = false;
bool Configuration::bGardeningAutoFertilize = false;
int Configuration::GardeningFertilizerQty = 1;
bool Configuration::bGardeningAutoReplant = false;
bool Configuration::bGardeningAutoWater = false;

#pragma endregion

// SellItems-Tab
#pragma region SellItems

// Buying
bool Configuration::bEnableBuyMultiplier = false;
bool Configuration::bEnableCtrlClickBuy = false;
int Configuration::buyMultiplierValue = 1;

// InventorySelector;
int Configuration::InventoryCount = 1;
bool Configuration::InventorySlot[5][8] = { false };
bool Configuration::InventoryAmmo = false;

// AutoSell
bool Configuration::bFishingSell = false;
bool Configuration::bFishingSellSQ = false;
bool Configuration::bFishingSellRarity[7] = { false, false, false, false, false, false, false };
bool Configuration::bBugSell = false;
bool Configuration::bBugSellSQ = false;
bool Configuration::bBugSellRarity[7] = { false, false, false, false, false, false, false };
bool Configuration::bHuntingSell = false;
bool Configuration::bHuntingSellSQ = false;
bool Configuration::bHuntingSellRarity[7] = { false, false, false, false, false, false, false };
bool Configuration::bFlowerSell = false;
bool Configuration::bForageableSell = false;
bool Configuration::bForageableSellSQ = false;
bool Configuration::bForageableSellRarity[7] = { false, false, false, false, false, false, false };
bool Configuration::bTreeSell = false;
bool Configuration::bTreeSellRarity[5] = { false, false, false, false, false };
bool Configuration::bJunkSell = false;

// AutoOpen
bool Configuration::bAutoOpenWaterlogged = false;
bool Configuration::bAutoOpenOyster = false;
bool Configuration::bAutoOpenElderClam = false;

// AutoStorage
bool Configuration::bAutoStoreDecor = false;

#pragma endregion

// Mods-Tab
#pragma region Mods

// Character
bool Configuration::bEnableAntiAfk = false;
bool Configuration::bEnableUnlimitedWardrobeRespec = false;
bool Configuration::bEnableInteractionMods = false;
float Configuration::InteractionDistance = 500.0f;
bool Configuration::bEnableWaypointTeleport = false;
bool Configuration::bEasyModeActive = false;

// Fun
bool Configuration::bPlaceAnywhere = false;
double Configuration::PlacementRotation = 15.0;
bool Configuration::bEnableOutfitCustomization = false;
bool Configuration::bEnableContentUnlocker = false;
bool Configuration::bEnableFreeLandscape = false;
bool Configuration::bEnableShowWeeklyWants = false;
bool Configuration::bEnableToolBricker = false;
int32 Configuration::ToolBrickerMaxSell = 999999;
bool Configuration::bEnableRequestMods = false;
bool Configuration::bEnableUnseenItems = false;

bool Configuration::bEnablePrizeWheel = false;
bool Configuration::bPrizeWheelUseLocked = false;
bool Configuration::PrizeWheelSlots[9] = { false, false, false, false, false, false, false, false, false };

#pragma endregion

// Origin
bool Configuration::bFirstUse = true;
bool Configuration::bShowWatermark = true;
bool Configuration::showEnabledFeaturesWindow = false;
bool Configuration::showPlayerDistancesWindow = false;
int Configuration::selectedTheme = 0;
int Configuration::cfg_SelectedLanguage = 0;
std::map<int, ImVec4> Configuration::customColors = {};

// Window configs
float Configuration::windowSizeX = 1450.0f;
float Configuration::windowSizeY = 950.0f;
float Configuration::activeWindowPosX = 125.0f;
float Configuration::activeWindowPosY = 5.0f;
float Configuration::playerWindowPosX = 325.0f;
float Configuration::playerWindowPosY = 5.0f;

#pragma endregion

// OVERLAY ~ Loading/Saving
#pragma region OVERLAY_Load_Save

bool Configuration::LoadOverlaySettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load overlay settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("Overlay_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // OVERLAY SETTINGS
    bFirstUse = config["OverlaySettings"]["MainWindow"].get("firstUse", true).asBool();
    windowSizeX = config["OverlaySettings"]["MainWindow"].get("windowSizeX", 1450.0f).asFloat();
    windowSizeY = config["OverlaySettings"]["MainWindow"].get("windowSizeY", 950.0f).asFloat();
    selectedTheme = config["OverlaySettings"]["MainWindow"].get("selectedTheme", 0).asInt();
    cfg_SelectedLanguage = config["OverlaySettings"]["MainWindow"].get("selectedLanguage", 0).asInt();

    activeWindowPosX = config["OverlaySettings"]["ModMenu"]["Position"].get("activeWindowPosX", 125.0f).asFloat();
    activeWindowPosY = config["OverlaySettings"]["ModMenu"]["Position"].get("activeWindowPosY", 5.0f).asFloat();
    playerWindowPosX = config["OverlaySettings"]["ModMenu"]["Position"].get("playerWindowPosX", 325.0f).asFloat();
    playerWindowPosY = config["OverlaySettings"]["ModMenu"]["Position"].get("playerWindowPosY", 5.0f).asFloat();
    showEnabledFeaturesWindow = config["OverlaySettings"]["ModMenu"]["Toggled"].get("showEnabledFeaturesWindow", false).asBool();
    showPlayerDistancesWindow = config["OverlaySettings"]["ModMenu"]["Toggled"].get("showPlayerDistancesWindow", false).asBool();

    bShowWatermark = config["OverlaySettings"]["Settings"].get("bShowWatermark", true).asBool();

    return true;
}

void Configuration::SaveOverlaySettings(Json::Value& config) {
    // OVERLAY SETTINGS
    config["OverlaySettings"]["MainWindow"]["firstUse"] = bFirstUse;
    config["OverlaySettings"]["MainWindow"]["windowSizeX"] = windowSizeX;
    config["OverlaySettings"]["MainWindow"]["windowSizeY"] = windowSizeY;
    config["OverlaySettings"]["MainWindow"]["selectedTheme"] = selectedTheme;
    config["OverlaySettings"]["MainWindow"]["selectedLanguage"] = cfg_SelectedLanguage;

    config["OverlaySettings"]["ModMenu"]["Position"]["activeWindowPosX"] = activeWindowPosX;
    config["OverlaySettings"]["ModMenu"]["Position"]["activeWindowPosY"] = activeWindowPosY;
    config["OverlaySettings"]["ModMenu"]["Position"]["playerWindowPosX"] = playerWindowPosX;
    config["OverlaySettings"]["ModMenu"]["Position"]["playerWindowPosY"] = playerWindowPosY;
    config["OverlaySettings"]["ModMenu"]["Toggled"]["showEnabledFeaturesWindow"] = showEnabledFeaturesWindow;
    config["OverlaySettings"]["ModMenu"]["Toggled"]["showPlayerDistancesWindow"] = showPlayerDistancesWindow;

    config["OverlaySettings"]["Settings"]["bShowWatermark"] = bShowWatermark;

    if (!SaveJsonToFile(overlayConfigFilePath, config)) {
        LogError("Failed to save overlay settings.");
    }
}

#pragma endregion

// ESP ~ Loading/Saving
#pragma region ESP_Load_Save

bool Configuration::LoadESPSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load ESP settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("ESP_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // ESP Settings
    bEnableESP = config["ESPSettings"].get("bEnableESP", true).asBool();
    ESPTextScale = config["ESPSettings"].get("ESPTextScale", 1.0f).asFloat();
    CullDistance = config["ESPSettings"].get("CullDistance", 300.0).asDouble();
    bEnableESPDistance = config["ESPSettings"].get("bEnableESPDistance", true).asBool();
    bEnableESPDespawnTimer = config["ESPSettings"].get("bEnableESPDespawnTimer", false).asBool();
    bEnableMapESP = config["ESPSettings"].get("bEnableMapESP", false).asBool();
    bEnableESPIcons = config["ESPSettings"].get("bEnableESPIcons", true).asBool();

    // Animals
    for (int i = 0; i < static_cast<int>(FEntryHunting::TypeEnum::MAX); i++) {
        for (int j = 0; j < static_cast<int>(FEntryHunting::VariantEnum::MAX); j++) {
            HUDDetours::Animals[i][j] = config["ESPSettings"]["Categories"]["Animals"][FEntryHunting::TypeString[i]][FEntryHunting::VariantString[j]].get("Checked", false).asBool();
            if (config["ESPSettings"]["Categories"]["Animals"][FEntryHunting::TypeString[i]][FEntryHunting::VariantString[j]].isMember("Color")) {
                ImU32 color = config["ESPSettings"]["Categories"]["Animals"][FEntryHunting::TypeString[i]][FEntryHunting::VariantString[j]]["Color"].asUInt();
                AnimalColors[{static_cast<FEntryHunting::TypeEnum>(i), static_cast<FEntryHunting::VariantEnum>(j)}] = color;
            }
        }
    }

    // Ores
    for (int i = 0; i < static_cast<int>(FEntryMining::TypeEnum::MAX); i++) {
        for (int j = 0; j < static_cast<int>(FEntryMining::VariantEnum::MAX); j++) {
            HUDDetours::Ores[i][j] = config["ESPSettings"]["Categories"]["Ores"][FEntryMining::TypeString[i]].get(FEntryMining::VariantString[j], false).asBool();
        }
        if (config["ESPSettings"]["Categories"]["Ores"][FEntryMining::TypeString[i]].isMember("Color")) {
            ImU32 color = config["ESPSettings"]["Categories"]["Ores"][FEntryMining::TypeString[i]]["Color"].asUInt();
            OreColors[static_cast<FEntryMining::TypeEnum>(i)] = color;
        }
    }

    // Forageables
    for (int i = 0; i < static_cast<int>(FEntryGatherable::TypeEnum::MAX); i++) {
        HUDDetours::Forageables[i][0] = config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]].get("Regular", false).asBool();
        HUDDetours::Forageables[i][1] = config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]].get("Star Quality", false).asBool();
        HUDDetours::Forageables[i][2] = config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]].get("Infected", false).asBool();
        if (config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]].isMember("Color")) {
            ImU32 color = config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]]["Color"].asUInt();
            ForageableColors[static_cast<FEntryGatherable::TypeEnum>(i)] = color;
        }
    }

    // Bugs
    for (int i = 0; i < static_cast<int>(FEntryBug::TypeEnum::MAX); i++) {
        for (int j = 0; j < static_cast<int>(FEntryBug::VariantEnum::MAX); j++) {
            HUDDetours::Bugs[i][j][0] = config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]].get("Regular", false).asBool();
            HUDDetours::Bugs[i][j][1] = config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]].get("Star Quality", false).asBool();
            HUDDetours::Bugs[i][j][2] = config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]].get("Infected", false).asBool();
            if (config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]].isMember("Color")) {
                ImU32 color = config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]]["Color"].asUInt();
                BugColors[{static_cast<FEntryBug::TypeEnum>(i), static_cast<FEntryBug::VariantEnum>(j)}] = color;
            }
        }
    }

    // Trees
    for (int i = 0; i < static_cast<int>(FEntryLumber::TypeEnum::MAX); i++) {
        for (int j = 0; j < static_cast<int>(FEntryLumber::VariantEnum::MAX); j++) {
            HUDDetours::Trees[i][j] = config["ESPSettings"]["Categories"]["Trees"][FEntryLumber::TypeString[i]].get(FEntryLumber::VariantString[j], false).asBool();
        }
        if (config["ESPSettings"]["Categories"]["Trees"][FEntryLumber::TypeString[i]].isMember("Color")) {
            ImU32 color = config["ESPSettings"]["Categories"]["Trees"][FEntryLumber::TypeString[i]]["Color"].asUInt();
            TreeColors[static_cast<FEntryLumber::TypeEnum>(i)] = color;
        }
    }

    // Singles
    for (int i = 0; i < static_cast<int>(EOneOffs::MAX); i++) {
        HUDDetours::Singles[i] = config["ESPSettings"]["Categories"]["Singles"][EOneOffsString[i]].get("Checked", false).asBool();
        if (config["ESPSettings"]["Categories"]["Singles"][EOneOffsString[i]].isMember("Color")) {
            ImU32 color = config["ESPSettings"]["Categories"]["Singles"][EOneOffsString[i]]["Color"].asUInt();
            SingleColors[static_cast<EOneOffs>(i)] = color;
        }
    }
    return true;
}

void Configuration::SaveESPSettings(Json::Value& config) {
    // ESP SETTINGS
    config["ESPSettings"]["bEnableESP"] = bEnableESP;
    config["ESPSettings"]["bEnableMapESP"] = bEnableMapESP;
    config["ESPSettings"]["bEnableESPIcons"] = bEnableESPIcons;
    config["ESPSettings"]["bEnableESPDistance"] = bEnableESPDistance;
    config["ESPSettings"]["bEnableESPDespawnTimer"] = bEnableESPDespawnTimer;
    config["ESPSettings"]["ESPTextScale"] = ESPTextScale;
    config["ESPSettings"]["CullDistance"] = CullDistance;

    // Initialize JSON categories to ensure proper structure
    config["ESPSettings"]["Categories"]["Animals"] = Json::Value(Json::objectValue);
    config["ESPSettings"]["Categories"]["Ores"] = Json::Value(Json::objectValue);
    config["ESPSettings"]["Categories"]["Forageables"] = Json::Value(Json::objectValue);
    config["ESPSettings"]["Categories"]["Bugs"] = Json::Value(Json::objectValue);
    config["ESPSettings"]["Categories"]["Trees"] = Json::Value(Json::objectValue);
    config["ESPSettings"]["Categories"]["Singles"] = Json::Value(Json::objectValue);

    // Animals
    for (int i = 1; i < static_cast<int>(FEntryHunting::TypeEnum::MAX); i++) { // skip unknown
        for (int j = 1; j < static_cast<int>(FEntryHunting::VariantEnum::MAX); j++) { // skip unknown
            const auto creatureKind = static_cast<FEntryHunting::TypeEnum>(i);
            const auto creatureQuality = static_cast<FEntryHunting::VariantEnum>(j);

            if (HUDDetours::Animals[i][j]) { // only save if true, since we default to false
                config["ESPSettings"]["Categories"]["Animals"][FEntryHunting::TypeString[i]][FEntryHunting::VariantString[j]]["Checked"] = true;
            }
            if (auto it = AnimalColors.find(FCreatureType{ creatureKind, creatureQuality }); it != AnimalColors.end()) {
                config["ESPSettings"]["Categories"]["Animals"][FEntryHunting::TypeString[i]][FEntryHunting::VariantString[j]]["Color"] = it->second;
            }
        }
    }

    // Ores
    for (int i = 1; i < static_cast<int>(FEntryMining::TypeEnum::MAX); i++) { // skip unknown
        if (auto it = OreColors.find(static_cast<FEntryMining::TypeEnum>(i)); it != OreColors.end()) {
            config["ESPSettings"]["Categories"]["Ores"][FEntryMining::TypeString[i]]["Color"] = it->second;
        }
        else {
            continue;
        }
        for (int j = 1; j < static_cast<int>(FEntryMining::VariantEnum::MAX); j++) { //skip unknown
            if (HUDDetours::Ores[i][j]) { // only save if true, since we default to false
                config["ESPSettings"]["Categories"]["Ores"][FEntryMining::TypeString[i]][FEntryMining::VariantString[j]] = true;
            }
        }
    }

    // Forageables
    for (int i = 1; i < static_cast<int>(FEntryGatherable::TypeEnum::MAX); i++) { // skip unknown
        if (auto it = ForageableColors.find(static_cast<FEntryGatherable::TypeEnum>(i)); it != ForageableColors.end()) {
            config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]]["Color"] = it->second;
        }
        else {
            continue;
        }
        if (HUDDetours::Forageables[i][0]) { // only save if true, since we default to false
            config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]]["Regular"] = true;
        }
        if (HUDDetours::Forageables[i][1]) { // only save if true, since we default to false
            config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]]["Star Quality"] = true;
        }
        if (HUDDetours::Forageables[i][2]) { // only save if true, since we default to false
            config["ESPSettings"]["Categories"]["Forageables"][FEntryGatherable::TypeString[i]]["Infected"] = true;
        }
    }

    // Bugs
    for (int i = 1; i < static_cast<int>(FEntryBug::TypeEnum::MAX); i++) { // skip unknown
        for (int j = 1; j < static_cast<int>(FEntryBug::VariantEnum::MAX); j++) { // skip unknown
            const auto bugKind = static_cast<FEntryBug::TypeEnum>(i);
            const auto bugQuality = static_cast<FEntryBug::VariantEnum>(j);

            // Find color for this bug kind and quality
            if (auto it = BugColors.find({ bugKind, bugQuality }); it != BugColors.end()) {
                config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]]["Color"] = it->second;
            }
            else {
                continue;
            }

            // Only save for regular or starred if true (since defaults are false)
            if (HUDDetours::Bugs[i][j][0]) {
                config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]]["Regular"] = true;
            }
            if (HUDDetours::Bugs[i][j][1]) {
                config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]]["Star Quality"] = true;
            }
            if (HUDDetours::Bugs[i][j][2]) {
                config["ESPSettings"]["Categories"]["Bugs"][FEntryBug::TypeString[i]][FEntryBug::VariantString[j]]["Infected"] = true;
            }
        }
    }

    // Trees
    for (int i = 1; i < static_cast<int>(FEntryLumber::TypeEnum::MAX); i++) { // skip unknown
        for (int j = 1; j < static_cast<int>(FEntryLumber::VariantEnum::MAX); j++) { // skip unknown
            if (HUDDetours::Trees[i][j]) { // only save if true, since we default to false
                config["ESPSettings"]["Categories"]["Trees"][FEntryLumber::TypeString[i]][FEntryLumber::VariantString[j]] = true;
            }
        }
        if (auto it = TreeColors.find(static_cast<FEntryLumber::TypeEnum>(i)); it != TreeColors.end()) {
            config["ESPSettings"]["Categories"]["Trees"][FEntryLumber::TypeString[i]]["Color"] = it->second;
        }
    }

    // Singles
    for (int i = 0; i < static_cast<int>(EOneOffs::MAX); i++) {
        if (HUDDetours::Singles[i]) {
            config["ESPSettings"]["Categories"]["Singles"][EOneOffsString[i]]["Checked"] = true;
        }
        if (auto it = SingleColors.find(static_cast<EOneOffs>(i)); it != SingleColors.end()) {
            config["ESPSettings"]["Categories"]["Singles"][EOneOffsString[i]]["Color"] = it->second;
        }
    }

    if (!SaveJsonToFile(espConfigFilePath, config)) {
        LogError("Failed to save ESP settings.");
    }
}

#pragma endregion

// AIM ~ Loading/Saving
#pragma region AIM_Load_Save

bool Configuration::LoadAimSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load aim settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("Aim_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // INTELIAIM SETTINGS
    bEnableInteliAim = config["AimSettings"]["FOV"].get("bEnableInteliAim", true).asBool();
    FOVRadius = config["AimSettings"]["FOV"].get("FOVRadius", 120.0f).asFloat();
    bHideFOVCircle = config["AimSettings"]["FOV"].get("bHideFOVCircle", false).asBool();
    CircleAlpha = config["AimSettings"]["FOV"].get("CircleAlpha", 1.0f).asFloat();
    bDrawCrosshair = config["AimSettings"]["FOV"].get("bDrawCrosshair", true).asBool();

    // INTELITARGET SETTINGS
    bEnableSilentAimbot = config["AimSettings"]["Target"].get("bEnableSilentAimbot", false).asBool();
    bTeleportToTargeted = config["AimSettings"]["Target"].get("bTeleportToTargeted", false).asBool();
    bAvoidTeleportingToPlayers = config["AimSettings"]["Target"].get("bAvoidTeleportingToPlayers", true).asBool();
    bDoRadiusPlayersAvoidance = config["AimSettings"]["Target"].get("bDoRadiusPlayersAvoidance", true).asBool();
    TeleportPlayerAvoidanceRadius = config["AimSettings"]["Target"].get("TeleportPlayerAvoidanceRadius", 30).asInt();
    
    // CLASSIC AIMBOT SETTINGS
    bEnableAimbot = config["AimSettings"]["Aimbot"].get("bEnableAimbot", false).asBool();
    AimbotSmoothing = config["AimSettings"]["Aimbot"].get("AimbotSmoothing", 5.0f).asFloat();
    AimbotKey = config["AimSettings"]["Aimbot"].get("AimbotKey", VK_RBUTTON).asInt();
    bAimbotOnlyAnimals = config["AimSettings"]["Aimbot"].get("bAimbotOnlyAnimals", true).asBool();

    return true;
}

void Configuration::SaveAimSettings(Json::Value& config) {
    // INTELIAIM SETTINGS
    config["AimSettings"]["FOV"]["bEnableInteliAim"] = bEnableInteliAim;
    config["AimSettings"]["FOV"]["FOVRadius"] = FOVRadius;
    config["AimSettings"]["FOV"]["bHideFOVCircle"] = bHideFOVCircle;
    config["AimSettings"]["FOV"]["CircleAlpha"] = CircleAlpha;
    config["AimSettings"]["FOV"]["bDrawCrosshair"] = bDrawCrosshair;

    // INTELITARGET SETTINGS
    config["AimSettings"]["Target"]["bEnableSilentAimbot"] = bEnableSilentAimbot;
    config["AimSettings"]["Target"]["bTeleportToTargeted"] = bTeleportToTargeted;
    config["AimSettings"]["Target"]["bAvoidTeleportingToPlayers"] = bAvoidTeleportingToPlayers;
    config["AimSettings"]["Target"]["bDoRadiusPlayersAvoidance"] = bDoRadiusPlayersAvoidance;
    config["AimSettings"]["Target"]["TeleportPlayerAvoidanceRadius"] = TeleportPlayerAvoidanceRadius;
    
    // CLASSIC AIMBOT SETTINGS
    config["AimSettings"]["Aimbot"]["bEnableAimbot"] = bEnableAimbot;
    config["AimSettings"]["Aimbot"]["AimbotSmoothing"] = AimbotSmoothing;
    config["AimSettings"]["Aimbot"]["AimbotKey"] = AimbotKey;
    config["AimSettings"]["Aimbot"]["bAimbotOnlyAnimals"] = bAimbotOnlyAnimals;

    if (!SaveJsonToFile(aimConfigFilePath, config)) {
        LogError("Failed to save aim settings.");
    }
}

#pragma endregion

// MOVEMENT ~ Loading/Saving
#pragma region MOVEMENT_Load_Save

bool Configuration::LoadMovementSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load movement settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("Movement_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // MOVEMENT SETTINGS
    CustomWalkSpeed = config["MovementSettings"].get("CustomWalkSpeed", 565.0f).asFloat();
    CustomSprintSpeed = config["MovementSettings"].get("CustomSprintSpeed", 1.65f).asFloat();
    CustomClimbingSpeed = config["MovementSettings"].get("CustomClimbingSpeed", 80.0f).asFloat();
    CustomGlidingSpeed = config["MovementSettings"].get("CustomGlidingSpeed", 900.0f).asFloat();
    CustomGlidingFallSpeed = config["MovementSettings"].get("CustomGlidingFallSpeed", 250.0f).asFloat();
    CustomJumpVelocity = config["MovementSettings"].get("CustomJumpVelocity", 700.0f).asFloat();
    CustomMaxJumps = config["MovementSettings"].get("CustomMaxJumps", 1).asInt();
    CustomMaxStepHeight = config["MovementSettings"].get("CustomMaxStepHeight", 45.0f).asFloat();

    return true;
}

void Configuration::SaveMovementSettings(Json::Value& config) {
    // MOVEMENT SETTINGS
    config["MovementSettings"]["CustomWalkSpeed"] = CustomWalkSpeed;
    config["MovementSettings"]["CustomSprintSpeed"] = CustomSprintSpeed;
    config["MovementSettings"]["CustomClimbingSpeed"] = CustomClimbingSpeed;
    config["MovementSettings"]["CustomGlidingSpeed"] = CustomGlidingSpeed;
    config["MovementSettings"]["CustomGlidingFallSpeed"] = CustomGlidingFallSpeed;
    config["MovementSettings"]["CustomJumpVelocity"] = CustomJumpVelocity;
    config["MovementSettings"]["CustomMaxJumps"] = CustomMaxJumps;
    config["MovementSettings"]["CustomMaxStepHeight"] = CustomMaxStepHeight;

    if (!SaveJsonToFile(movementConfigFilePath, config)) {
        LogError("Failed to save movement settings.");
    }
}

#pragma endregion

// TOOL_SKILLS ~ Loading/Saving
#pragma region TOOLSKILLS_Load_Save

bool Configuration::LoadToolSkillsSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load tools & skills settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("ToolSkills_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // AXE/PICKAXE SETTINGS
    bEnableAutoSwinging = config["ToolSkillsSettings"]["ToolSwinger"].get("bEnableAutoSwinging", false).asBool();
    bResourceAutoEquipTool = config["ToolSkillsSettings"]["ToolSwinger"].get("bResourceAutoEquipTool", false).asBool();
    bAutoSwingingRequireESP = config["ToolSkillsSettings"]["ToolSwinger"].get("bAutoSwingingRequireESP", false).asBool();
    bAvoidSwingingLowDurability = config["ToolSkillsSettings"]["ToolSwinger"].get("bAvoidSwingingLowDurability", false).asBool();
    bAvoidGroveChopping = config["ToolSkillsSettings"]["ToolSwinger"].get("bAvoidGroveChopping", true).asBool();
    bAvoidPlotSwinging = config["ToolSkillsSettings"]["ToolSwinger"].get("bAvoidPlotSwinging", true).asBool();
    bAvoidSwingingNearPlayers = config["ToolSkillsSettings"]["ToolSwinger"].get("bAvoidSwingingNearPlayers", false).asBool();
    SwingPlayerAvoidDistance = config["ToolSkillsSettings"]["ToolSwinger"].get("SwingPlayerAvoidDistance", 30.0).asFloat();

    // BUG CATCHING SETTINGS
    bEnableBugCatching = config["ToolSkillsSettings"]["BugCatching"].get("bEnableBugCatching", false).asBool();
    bBugAutoEquipTool = config["ToolSkillsSettings"]["BugCatching"].get("bBugAutoEquipTool", false).asBool();
    bAutoCatchingRequireESP = config["ToolSkillsSettings"]["BugCatching"].get("bAutoCatchingRequireESP", false).asBool();
    bAvoidCatchingLowDurability = config["ToolSkillsSettings"]["BugCatching"].get("bAvoidCatchingLowDurability", false).asBool();
    BugCatchingDistance = config["ToolSkillsSettings"]["BugCatching"].get("BugCatchingDistance", 10.0f).asFloat();
    BugSpeedPreset = config["ToolSkillsSettings"]["BugCatching"].get("BugSpeedPreset", 1).asInt();
    BugCatchingDelay = config["ToolSkillsSettings"]["BugCatching"].get("BugCatchingDelay", 750).asInt();
    bAvoidCatchingNearPlayers = config["ToolSkillsSettings"]["BugCatching"].get("bAvoidCatchingNearPlayers", false).asBool();
    CatchingPlayerAvoidDistance = config["ToolSkillsSettings"]["BugCatching"].get("CatchingPlayerAvoidDistance", 30.0).asFloat();

    // ANIMAL HUNTING SETTINGS
    bEnableAnimalHunting = config["ToolSkillsSettings"]["AnimalHunting"].get("bEnableAnimalHunting", false).asBool();
    bAnimalAutoEquipTool = config["ToolSkillsSettings"]["AnimalHunting"].get("bAnimalAutoEquipTool", false).asBool();
    bAutoHuntingRequireESP = config["ToolSkillsSettings"]["AnimalHunting"].get("bAutoHuntingRequireESP", false).asBool();
    bAvoidHuntingLowDurability = config["ToolSkillsSettings"]["AnimalHunting"].get("bAvoidHuntingLowDurability", false).asBool();
    AnimalHuntingDistance = config["ToolSkillsSettings"]["AnimalHunting"].get("AnimalHuntingDistance", 10.0f).asFloat();
    AnimalSpeedPreset = config["ToolSkillsSettings"]["AnimalHunting"].get("AnimalSpeedPreset", 1).asInt();
    AnimalHuntingDelay = config["ToolSkillsSettings"]["AnimalHunting"].get("AnimalHuntingDelay", 750).asInt();
    bAvoidHuntingNearPlayers = config["ToolSkillsSettings"]["AnimalHunting"].get("bAvoidHuntingNearPlayers", false).asBool();
    HuntingPlayerAvoidDistance = config["ToolSkillsSettings"]["AnimalHunting"].get("HuntingPlayerAvoidDistance", 30.0).asFloat();

    // OTHER SETTINGS
    bEnableAutoGather = config["ToolSkillsSettings"]["Others"].get("bEnableAutoGather", false).asBool();
    bEnableCookingMinigameSkip = config["ToolSkillsSettings"]["Others"].get("bEnableCookingMinigameSkip", false).asBool();
    bEnableAutoFocus = config["ToolSkillsSettings"]["Others"].get("bEnableAutoFocus", false).asBool();
    FocusBelowPercent = config["ToolSkillsSettings"]["Others"].get("FocusBelowPercent", 50).asInt();

    // FISHING SETTINGS
    bFishingNoDurability = config["ToolSkillsSettings"]["Fishing"].get("bFishingNoDurability", true).asBool();
    bFishingMultiplayerHelp = config["ToolSkillsSettings"]["Fishing"].get("bFishingMultiplayerHelp", false).asBool();
    bFishingPerfectCatch = config["ToolSkillsSettings"]["Fishing"].get("bFishingPerfectCatch", true).asBool();
    bFishingInstantCatch = config["ToolSkillsSettings"]["Fishing"].get("bFishingInstantCatch", false).asBool();
    bRequireClickFishing = config["ToolSkillsSettings"]["Fishing"].get("bRequireClickFishing", true).asBool();

    // Gardening
    bGardeningAutoHarvest = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoHarvest", false).asBool();
    bGardeningAutoTill = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoTill", false).asBool();
    bGardeningAutoWeed = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoWeed", false).asBool();
    bGardeningAutoFertilize = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoFertilize", false).asBool();
    GardeningFertilizerQty = config["ToolSkillsSettings"]["Gardening"].get("GardeningFertilizerQty", 1).asInt();
    bGardeningAutoReplant = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoReplant", false).asBool();
    // bGardeningAutoWater     = config["ToolSkillsSettings"]["Gardening"].get("bGardeningAutoWater", false).asBool();

    return true;
}

void Configuration::SaveToolSkillsSettings(Json::Value& config) {
    // AXE/PICKAXE SETTINGS
    config["ToolSkillsSettings"]["ToolSwinger"]["bEnableAutoSwinging"] = bEnableAutoSwinging;
    config["ToolSkillsSettings"]["ToolSwinger"]["bResourceAutoEquipTool"] = bResourceAutoEquipTool;
    config["ToolSkillsSettings"]["ToolSwinger"]["bAutoSwingingRequireESP"] = bAutoSwingingRequireESP;
    config["ToolSkillsSettings"]["ToolSwinger"]["bAvoidSwingingLowDurability"] = bAvoidSwingingLowDurability;
    config["ToolSkillsSettings"]["ToolSwinger"]["bAvoidGroveChopping"] = bAvoidGroveChopping;
    config["ToolSkillsSettings"]["ToolSwinger"]["bAvoidPlotSwinging"] = bAvoidPlotSwinging;
    config["ToolSkillsSettings"]["ToolSwinger"]["bAvoidSwingingNearPlayers"] = bAvoidSwingingNearPlayers;
    config["ToolSkillsSettings"]["ToolSwinger"]["SwingPlayerAvoidDistance"] = SwingPlayerAvoidDistance;

    // BUG CATCHING SETTINGS
    config["ToolSkillsSettings"]["BugCatching"]["bEnableBugCatching"] = bEnableBugCatching;
    config["ToolSkillsSettings"]["BugCatching"]["bBugAutoEquipTool"] = bBugAutoEquipTool;
    config["ToolSkillsSettings"]["BugCatching"]["bAutoCatchingRequireESP"] = bAutoCatchingRequireESP;
    config["ToolSkillsSettings"]["BugCatching"]["bAvoidCatchingLowDurability"] = bAvoidCatchingLowDurability;
    config["ToolSkillsSettings"]["BugCatching"]["BugCatchingDistance"] = BugCatchingDistance;
    config["ToolSkillsSettings"]["BugCatching"]["BugSpeedPreset"] = BugSpeedPreset;
    config["ToolSkillsSettings"]["BugCatching"]["BugCatchingDelay"] = BugCatchingDelay;
    config["ToolSkillsSettings"]["BugCatching"]["bAvoidCatchingNearPlayers"] = bAvoidCatchingNearPlayers;
    config["ToolSkillsSettings"]["BugCatching"]["CatchingPlayerAvoidDistance"] = CatchingPlayerAvoidDistance;

    // ANIMAL HUNTING SETTINGS
    config["ToolSkillsSettings"]["AnimalHunting"]["bEnableAnimalHunting"] = bEnableAnimalHunting;
    config["ToolSkillsSettings"]["AnimalHunting"]["bAnimalAutoEquipTool"] = bAnimalAutoEquipTool;
    config["ToolSkillsSettings"]["AnimalHunting"]["bAutoHuntingRequireESP"] = bAutoHuntingRequireESP;
    config["ToolSkillsSettings"]["AnimalHunting"]["bAvoidHuntingLowDurability"] = bAvoidHuntingLowDurability;
    config["ToolSkillsSettings"]["AnimalHunting"]["AnimalHuntingDistance"] = AnimalHuntingDistance;
    config["ToolSkillsSettings"]["AnimalHunting"]["AnimalSpeedPreset"] = AnimalSpeedPreset;
    config["ToolSkillsSettings"]["AnimalHunting"]["AnimalHuntingDelay"] = AnimalHuntingDelay;
    config["ToolSkillsSettings"]["AnimalHunting"]["bAvoidHuntingNearPlayers"] = bAvoidHuntingNearPlayers;
    config["ToolSkillsSettings"]["AnimalHunting"]["HuntingPlayerAvoidDistance"] = HuntingPlayerAvoidDistance;

    // OTHER SETTINGS
    config["ToolSkillsSettings"]["Others"]["bEnableAutoGather"] = bEnableAutoGather;
    config["ToolSkillsSettings"]["Others"]["bEnableCookingMinigameSkip"] = bEnableCookingMinigameSkip;
    config["ToolSkillsSettings"]["Others"]["bEnableAutoFocus"] = bEnableAutoFocus;
    config["ToolSkillsSettings"]["Others"]["FocusBelowPercent"] = FocusBelowPercent;

    // FISHING SETTINGS
    config["ToolSkillsSettings"]["Fishing"]["bFishingNoDurability"] = bFishingNoDurability;
    config["ToolSkillsSettings"]["Fishing"]["bFishingMultiplayerHelp"] = bFishingMultiplayerHelp;
    config["ToolSkillsSettings"]["Fishing"]["bFishingInstantCatch"] = bFishingInstantCatch;
    config["ToolSkillsSettings"]["Fishing"]["bFishingPerfectCatch"] = bFishingPerfectCatch;
    config["ToolSkillsSettings"]["Fishing"]["bRequireClickFishing"] = bRequireClickFishing;

    // Gardening
    config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoHarvest"] = bGardeningAutoHarvest;
    config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoTill"] = bGardeningAutoTill;
    config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoWeed"] = bGardeningAutoWeed;
    config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoFertilize"] = bGardeningAutoFertilize;
    config["ToolSkillsSettings"]["Gardening"]["GardeningFertilizerQty"] = GardeningFertilizerQty;
    config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoReplant"] = bGardeningAutoReplant;
    // config["ToolSkillsSettings"]["Gardening"]["bGardeningAutoWater"] = bGardeningAutoWater;

    if (!SaveJsonToFile(toolskillsConfigFilePath, config)) {
        LogError("Failed to save tools & skills settings.");
    }
}

#pragma endregion

// SELL_ITEMS ~ Loading/Saving
#pragma region SELLITEMS_Load_Save

bool Configuration::LoadSellItemsSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load sell items settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("SellItems_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // Manual Settings
    bEnableBuyMultiplier = config["SellItems"]["Manual"].get("bEnableBuyMultiplier", false).asBool();
    bEnableCtrlClickBuy = config["SellItems"]["Manual"].get("bEnableCtrlClickBuy", false).asBool();
    buyMultiplierValue = config["SellItems"]["Manual"].get("buyMultiplierValue", 1).asInt();

    // AutoSell Settings
    bFishingSell = config["SellItems"]["AutoSell"].get("bFishingSell", false).asBool();
    bFishingSellSQ = config["SellItems"]["AutoSell"].get("bFishingSellSQ", false).asBool();
    for (int i = 0; i < 7; i++) {
        bFishingSellRarity[i] = config["SellItems"]["AutoSell"]["bFishingSellRarity"].get(i, false).asBool();
    }

    bBugSell = config["SellItems"]["AutoSell"].get("bBugSell", false).asBool();
    bBugSellSQ = config["SellItems"]["AutoSell"].get("bBugSellSQ", false).asBool();
    for (int i = 0; i < 7; i++) {
        bBugSellRarity[i] = config["SellItems"]["AutoSell"]["bBugSellRarity"].get(i, false).asBool();
    }

    bHuntingSell = config["SellItems"]["AutoSell"].get("bHuntingSell", false).asBool();
    bHuntingSellSQ = config["SellItems"]["AutoSell"].get("bHuntingSellSQ", false).asBool();
    for (int i = 0; i < 7; i++) {
        bHuntingSellRarity[i] = config["SellItems"]["AutoSell"]["bHuntingSellRarity"].get(i, false).asBool();
    }

    bForageableSell = config["SellItems"]["AutoSell"].get("bForageableSell", false).asBool();
    bForageableSellSQ = config["SellItems"]["AutoSell"].get("bForageableSellSQ", false).asBool();
    for (int i = 0; i < 7; i++) {
        bForageableSellRarity[i] = config["SellItems"]["AutoSell"]["bForageableSellRarity"].get(i, false).asBool();
    }

    bTreeSell = config["SellItems"]["AutoSell"].get("bTreeSell", false).asBool();
    for (int i = 0; i < 5; i++) {
        bTreeSellRarity[i] = config["SellItems"]["AutoSell"]["bTreeSellRarity"].get(i, false).asBool();
    }

    bFlowerSell = config["SellItems"]["AutoSell"].get("bFlowerSell", false).asBool();
    bJunkSell = config["SellItems"]["AutoSell"].get("bJunkSell", false).asBool();

    bAutoOpenOyster = config["SellItems"]["AutoOpen"].get("Oyster", false).asBool();
    bAutoOpenWaterlogged = config["SellItems"]["AutoOpen"].get("WaterloggedChest", false).asBool();
    bAutoOpenElderClam = config["SellItems"]["AutoOpen"].get("ElderClam", false).asBool();

    bAutoStoreDecor = config["SellItems"]["AutoStorage"].get("Decor", false).asBool();

    return true;
}

void Configuration::SaveSellItemsSettings(Json::Value& config) {
    // Selling Settings
    config["SellItems"]["Manual"]["bEnableBuyMultiplier"] = bEnableBuyMultiplier;
    config["SellItems"]["Manual"]["bEnableCtrlClickBuy"] = bEnableCtrlClickBuy;
    config["SellItems"]["Manual"]["buyMultiplierValue"] = buyMultiplierValue;

    // AutoSell Settings
    config["SellItems"]["AutoSell"]["bFishingSell"] = bFishingSell;
    config["SellItems"]["AutoSell"]["bFishingSellSQ"] = bFishingSellSQ;
    config["SellItems"]["AutoSell"]["bFishingSellRarity"] = Json::Value(Json::arrayValue);
    for (const bool& i : bFishingSellRarity) {
        config["SellItems"]["AutoSell"]["bFishingSellRarity"].append(i);
    }

    config["SellItems"]["AutoSell"]["bBugSell"] = bBugSell;
    config["SellItems"]["AutoSell"]["bBugSellSQ"] = bBugSellSQ;
    config["SellItems"]["AutoSell"]["bBugSellRarity"] = Json::Value(Json::arrayValue);
    for (const bool& i : bBugSellRarity) {
        config["SellItems"]["AutoSell"]["bBugSellRarity"].append(i);
    }

    config["SellItems"]["AutoSell"]["bHuntingSell"] = bHuntingSell;
    config["SellItems"]["AutoSell"]["bHuntingSellSQ"] = bHuntingSellSQ;
    config["SellItems"]["AutoSell"]["bHuntingSellRarity"] = Json::Value(Json::arrayValue);
    for (const bool& i : bHuntingSellRarity) {
        config["SellItems"]["AutoSell"]["bHuntingSellRarity"].append(i);
    }

    config["SellItems"]["AutoSell"]["bForageableSell"] = bForageableSell;
    config["SellItems"]["AutoSell"]["bForageableSellSQ"] = bForageableSellSQ;
    config["SellItems"]["AutoSell"]["bForageableSellRarity"] = Json::Value(Json::arrayValue);
    for (const bool& i : bForageableSellRarity) {
        config["SellItems"]["AutoSell"]["bForageableSellRarity"].append(i);
    }

    config["SellItems"]["AutoSell"]["bTreeSell"] = bTreeSell;
    config["SellItems"]["AutoSell"]["bTreeSellRarity"] = Json::Value(Json::arrayValue);
    for (const bool& i : bTreeSellRarity) {
        config["SellItems"]["AutoSell"]["bTreeSellRarity"].append(i);
    }

    config["SellItems"]["AutoSell"]["bFlowerSell"] = bFlowerSell;
    config["SellItems"]["AutoSell"]["bJunkSell"] = bJunkSell;

    config["SellItems"]["AutoOpen"]["Oyster"] = bAutoOpenOyster;
    config["SellItems"]["AutoOpen"]["WaterloggedChest"] = bAutoOpenWaterlogged;
    config["SellItems"]["AutoOpen"]["ElderClam"] = bAutoOpenElderClam;

    config["SellItems"]["AutoStorage"]["Decor"] = bAutoStoreDecor;

    if (!SaveJsonToFile(sellitemsConfigFilePath, config)) {
        LogError("Failed to save sell items settings.");
    }
}

#pragma endregion

// MODS ~ Loading/Saving
#pragma region MODS_Load_Save

bool Configuration::LoadModSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load mod settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("Mod_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    // CHARACTER SETTINGS
    bEnableAntiAfk = config["Mods"]["Character"].get("bEnableAntiAfk", false).asBool();
    bEnableUnlimitedWardrobeRespec = config["Mods"]["Character"].get("bEnableUnlimitedWardrobeRespec", false).asBool();
    bEnableInteractionMods = config["Mods"]["Character"].get("bEnableInteractionMods", false).asBool();
    InteractionDistance = config["Mods"]["Character"].get("InteractionDistance", 500.0f).asFloat();
    bEnableWaypointTeleport = config["Mods"]["Character"].get("bEnableWaypointTeleport", false).asBool();
    bEasyModeActive = config["Mods"]["Character"].get("bEasyModeActive", false).asBool();

    // FUN SETTINGS
    bPlaceAnywhere = config["Mods"]["Fun"].get("bPlaceAnywhere", false).asBool();
    PlacementRotation = config["Mods"]["Fun"].get("PlacementRotation", 15.0).asDouble();
    bEnableOutfitCustomization = config["Mods"]["Fun"].get("bEnableOutfitCustomization", false).asBool();
    bEnableContentUnlocker = config["Mods"]["Fun"].get("bEnableContentUnlocker", false).asBool();
    bEnableFreeLandscape = config["Mods"]["Fun"].get("bEnableFreeLandscape", false).asBool();
    bEnableShowWeeklyWants = config["Mods"]["Fun"].get("bEnableShowWeeklyWants", false).asBool();
    bEnableToolBricker = config["Mods"]["Fun"].get("bEnableToolBricker", false).asBool();
    ToolBrickerMaxSell = config["Mods"]["Fun"].get("ToolBrickerMaxSell", 999999).asInt();
    bEnableRequestMods = config["Mods"]["Fun"].get("bEnableRequestMods", false).asBool();
    bEnablePrizeWheel = config["Mods"]["Fun"].get("bEnablePrizeWheel", false).asBool();
    bPrizeWheelUseLocked = config["Mods"]["Fun"].get("bPrizeWheelUseLocked", false).asBool();
    for (int i = 0; i < 9; ++i) {
        std::string key = "PrizeWheelSlot" + std::to_string(i);
        PrizeWheelSlots[i] = config["Mods"]["Fun"]["PrizeWheelSettings"].get(key, false).asBool();
    }

    return true;
}

void Configuration::SaveModSettings(Json::Value& config) {
    // CHARACTER SETTINGS
    config["Mods"]["Character"]["bEnableAntiAfk"] = bEnableAntiAfk;
    config["Mods"]["Character"]["bEnableUnlimitedWardrobeRespec"] = bEnableUnlimitedWardrobeRespec;
    config["Mods"]["Character"]["bEnableInteractionMods"] = bEnableInteractionMods;
    config["Mods"]["Character"]["InteractionDistance"] = InteractionDistance;
    config["Mods"]["Character"]["bEnableWaypointTeleport"] = bEnableWaypointTeleport;
    config["Mods"]["Character"]["bEasyModeActive"] = bEasyModeActive;

    // FUN SETTINGS
    config["Mods"]["Fun"]["bPlaceAnywhere"] = bPlaceAnywhere;
    config["Mods"]["Fun"]["PlacementRotation"] = PlacementRotation;
    config["Mods"]["Fun"]["bEnableOutfitCustomization"] = bEnableOutfitCustomization;
    config["Mods"]["Fun"]["bEnableContentUnlocker"] = bEnableContentUnlocker;
    config["Mods"]["Fun"]["bEnableFreeLandscape"] = bEnableFreeLandscape;
    config["Mods"]["Fun"]["bEnableShowWeeklyWants"] = bEnableShowWeeklyWants;
    config["Mods"]["Fun"]["bEnableRequestMods"] = bEnableRequestMods;
    config["Mods"]["Fun"]["bEnableToolBricker"] = bEnableToolBricker;
    config["Mods"]["Fun"]["ToolBrickerMaxSell"] = ToolBrickerMaxSell;
    config["Mods"]["Fun"]["bEnablePrizeWheel"] = bEnablePrizeWheel;
    config["Mods"]["Fun"]["bPrizeWheelUseLocked"] = bPrizeWheelUseLocked;
    for (int i = 0; i < 9; ++i) {
        std::string key = "PrizeWheelSlot" + std::to_string(i);
        config["Mods"]["Fun"]["PrizeWheelSettings"][key] = PrizeWheelSlots[i];
    }

    if (!SaveJsonToFile(modConfigFilePath, config)) {
        LogError("Failed to save mod settings.");
    }
}

#pragma endregion

// THEME ~ Loading/Saving
#pragma region THEME_Load_Save

bool Configuration::LoadCustomThemeSettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load Custom_theme.json, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("SellItems_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    if (config.isObject() && config.isMember("Custom Theme Settings")) {
        for (const auto& colorIndex : config["Custom Theme Settings"].getMemberNames()) {
            int index = std::stoi(colorIndex);
            Json::Value colorJson = config["Custom Theme Settings"][colorIndex];

            float r = colorJson.get("R", 0.0).asFloat();
            float g = colorJson.get("G", 0.0).asFloat();
            float b = colorJson.get("B", 0.0).asFloat();
            float a = colorJson.get("A", 1.0).asFloat();

            auto color = ImVec4(r, g, b, a);
            customColors[index] = color;
        }
    }
    else {
        LogError("Custom_theme.json could not find member 'Custom Theme Settings'.");
    }

    return true;
}

void Configuration::SaveCustomThemeSettings(Json::Value& config) {
    if (!customColors.empty()) {
        for (const auto& pair : customColors) {
            const int colorIndex = pair.first;
            const ImVec4 colorValue = pair.second;

            Json::Value colorJson;
            colorJson["R"] = colorValue.x;
            colorJson["G"] = colorValue.y;
            colorJson["B"] = colorValue.z;
            colorJson["A"] = colorValue.w;

            config["Custom Theme Settings"][std::to_string(colorIndex)] = colorJson;
        }
    }
    else {
        config["Custom Theme Settings"] = Json::Value(Json::objectValue);
    }

    if (!SaveJsonToFile(customThemeConfigFilePath, config)) {
        LogError("Failed to save custom theme settings.");
    }
}

#pragma endregion

// HOTKEYS ~ Loading/Saving
#pragma region HOTKEYS_Load_Save

bool Configuration::LoadHotkeySettings(const std::string& filePath, Json::Value& config) {
    if (!LoadJsonFromFile(filePath, config)) {
        LogError("Failed to load hotkey settings, attempting to restore from backup.");

        // Attempt backup file restoration
        if (!LoadJsonFromFile(filePath + ".backup", config)) {
            LogError("Failed to restore from backup. Restoring default settings.");

            // Erase content inside to use instantiated declarations.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
            if (!ofs.is_open() || ofs.fail()) {
                LogError("Failed to erase file content.");
                return false; // file could not be opened; return false.
            }
            ofs.close();
            ConfigIsCorrupt = true;
            corruptConfigs.push_back("Hotkey_settings.json");
            return true; // file contained errors but was opened, read and vars reset to defaults; return true.
        }

        if (!RestoreBackup(filePath + ".backup", filePath)) {
            LogError("Failed to replace original file with backup");
            return false; // restoration failed; return false.
        }
    }

    for (auto it = config.begin(); it != config.end(); ++it) {
        std::string actionName = it.name();
        int keyCode = it->asInt();
        HotkeysManager::SetHotkey(actionName, keyCode);
    }

    return true;
}

void Configuration::SaveHotkeySettings(Json::Value& config) {
    for (const auto& [actionName, keyCallbackPair] : HotkeysManager::GetHotkeys()) {
        config[actionName] = keyCallbackPair.first;
    }

    if (!SaveJsonToFile(hotkeysConfigFilePath, config)) {
        LogError("Failed to save hotkey settings.");
    }
}

#pragma endregion

void Configuration::Load() {
    if (ConfigLoaded) return;

    bool allFilesLoaded = true; // assume all files will load successfully.

    // lambda function to check existence of file path
    auto loadConfig = [&](const std::string& filePath, auto&& loadFunc, auto& settings) {
        if (!std::filesystem::exists(filePath)) {
            std::ofstream newFile(filePath);
            if (!newFile.is_open()) {
                LogError("Failed to create new file: " + filePath);
                allFilesLoaded = false;
                return;
            }
            newFile.close();
            settings = Json::Value(Json::objectValue);
            Log("Created a new empty Json file: " + filePath);
        }

        // Load settings from file.
        allFilesLoaded &= loadFunc(filePath, settings);
        };

    loadConfig(overlayConfigFilePath, LoadOverlaySettings, overlaySettings);
    loadConfig(espConfigFilePath, LoadESPSettings, espSettings);
    loadConfig(aimConfigFilePath, LoadAimSettings, aimSettings);
    loadConfig(movementConfigFilePath, LoadMovementSettings, movementSettings);
    loadConfig(toolskillsConfigFilePath, LoadToolSkillsSettings, toolskillsSettings);
    loadConfig(sellitemsConfigFilePath, LoadSellItemsSettings, sellitemsSettings);
    loadConfig(modConfigFilePath, LoadModSettings, modSettings);
    loadConfig(customThemeConfigFilePath, LoadCustomThemeSettings, customThemeSettings);
    loadConfig(hotkeysConfigFilePath, LoadHotkeySettings, hotkeySettings);

    // if (std::filesystem::exists(overlayConfigFilePath))
    //     allFilesLoaded &= LoadOverlaySettings(overlayConfigFilePath, overlaySettings);
    //
    // if (std::filesystem::exists(espConfigFilePath))
    //     allFilesLoaded &= LoadESPSettings(espConfigFilePath, espSettings);
    //
    // if (std::filesystem::exists(aimConfigFilePath))
    //     allFilesLoaded &= LoadAimSettings(aimConfigFilePath, aimSettings);
    //
    // if (std::filesystem::exists(movementConfigFilePath))
    //     allFilesLoaded &= LoadMovementSettings(movementConfigFilePath, movementSettings);
    //
    // if (std::filesystem::exists(toolskillsConfigFilePath))
    //     allFilesLoaded &= LoadToolSkillsSettings(toolskillsConfigFilePath, toolskillsSettings);
    //
    // if (std::filesystem::exists(sellitemsConfigFilePath))
    //     allFilesLoaded &= LoadSellItemsSettings(sellitemsConfigFilePath, sellitemsSettings);
    //
    // if (std::filesystem::exists(modConfigFilePath))
    //     allFilesLoaded &= LoadModSettings(modConfigFilePath, modSettings);
    //
    // if (std::filesystem::exists(customThemeConfigFilePath))
    //     allFilesLoaded &= LoadCustomThemeSettings(customThemeConfigFilePath, customThemeSettings);
    //
    // if (std::filesystem::exists(hotkeysConfigFilePath))
    //     allFilesLoaded &= LoadHotkeySettings(hotkeysConfigFilePath, hotkeySettings);

    if (allFilesLoaded) {
        Log("All files successfully loaded.");
    }

    // Set ConfigLoaded to true after loading all the configurations
    ConfigLoaded = allFilesLoaded;
}

void Configuration::Save(ESaveFile save_file) {
    if (const std::filesystem::path dir(configDirectory); !exists(dir)) {
        create_directories(dir);
    }

    switch (save_file) {
    case NONE:
        // do nothing.
        break;
    case OverlaySettings:
        SaveOverlaySettings(overlaySettings);
        break;
    case ESPSettings:
        SaveESPSettings(espSettings);
        break;
    case AimSettings:
        SaveAimSettings(aimSettings);
        break;
    case MovementSettings:
        SaveMovementSettings(movementSettings);
        break;
    case ToolSkillsSettings:
        SaveToolSkillsSettings(toolskillsSettings);
        break;
    case SellItemsSettings:
        SaveSellItemsSettings(sellitemsSettings);
        break;
    case ModSettings:
        SaveModSettings(modSettings);
        break;
    case CustomThemeSettings:
        SaveCustomThemeSettings(customThemeSettings);
        break;
    case HotkeySettings:
        SaveHotkeySettings(hotkeySettings);
        break;
    case SAVE_ALL:
        SaveOverlaySettings(overlaySettings);
        SaveESPSettings(espSettings);
        SaveAimSettings(aimSettings);
        SaveMovementSettings(movementSettings);
        SaveToolSkillsSettings(toolskillsSettings);
        SaveSellItemsSettings(sellitemsSettings);
        SaveModSettings(modSettings);
        SaveCustomThemeSettings(customThemeSettings);
        SaveHotkeySettings(hotkeySettings);
        break;
    default:
        LogError("Configuration::Save() error: Unknown save type specified.");
        break;
    }
}

void Configuration::ApplyCustomTheme() {
    ImGuiStyle* style = &ImGui::GetStyle();
    style->GrabRounding = 4.0f;

    for (const auto& it : GuiColors) {
        int idx = it.first;
        auto colorIt = customColors.find(idx);
        if (colorIt != customColors.end()) {
            style->Colors[idx] = colorIt->second;
        }
    }
}