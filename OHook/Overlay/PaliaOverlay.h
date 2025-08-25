#pragma once
#include "DetourManager.h"
#include "ActorHandler.h"
#include <OverlayBase.h>
#include <imgui.h>
#include <unordered_map>
#include <chrono>
#include <map>
#include <mutex>

#include <SDK.hpp>
using namespace SDK;

extern bool waitingForKey;

inline std::map<int, std::string> GatherableSizeNames = {
    {0, "Unknown"},
    {1, "XS"},
    {2, "S"},
    {3, "M"},
    {4, "L"},
};

enum class ELocation {
    // Home
    Global_Home,

    // Kilima Entrances
    Kilima_HousingPlot,
    Kilima_ToBahariBay,

    // Kilima Stables
    Kilima_CentralStables,
    Kilima_MirrorFields,
    Kilima_LeafhopperHills,
    Kilima_WhisperingBanks,

    // Kilima Others
    Kilima_Fairgrounds_MajiMarket,
    Kilima_GeneralStore,
    Kilima_RepairStation,
    Kilima_TailorStore,
    Kilima_FurnitureStore,
    Kilima_CityHall,
    Kilima_Tavern,
    Kilima_PhoenixFalls,
    Kilima_DragonShrine,
    Kilima_FishermansLagoon,
    Kilima_WimsFishingSpot,

    // Bahari Entrances
    Bahari_HousingPlot,
    Bahari_ToKilimaValley,

    // Bahari Stables
    Bahari_CentralStables,
    Bahari_TheOutskirts,
    Bahari_CoralShores,
    Bahari_PulsewaterPlains,
    Bahari_HideawayBluffs,
    Bahari_BeachcomberCove,

    // Others

    UserDefined
};

// Function to get key name from key code
inline std::string GetKeyName(int key) {
    static std::map<int, std::string> keyNames = {
        {0x01, "Left Button"},
        {0x02, "Right Button"},
        {0x03, "Control-break"},
        {0x04, "Middle Button"},
        {0x05, "X1 Button"},
        {0x06, "X2 Button"},
        {0x08, "Backspace"},
        {0x09, "Tab"},
        {0x0C, "Clear"},
        {0x0D, "Enter"},
        {0x10, "Shift"},
        {0x11, "Ctrl"},
        {0x12, "Alt"},
        {0x13, "Pause"},
        {0x14, "Caps Lock"},
        {0x1B, "Esc"},
        {0x20, "Space"},
        {0x21, "Page Up"},
        {0x22, "Page Down"},
        {0x23, "End"},
        {0x24, "Home"},
        {0x25, "Left Arrow"},
        {0x26, "Up Arrow"},
        {0x27, "Right Arrow"},
        {0x28, "Down Arrow"},
        {0x29, "Select"},
        {0x2A, "Print"},
        {0x2B, "Execute"},
        {0x2C, "Print Screen"},
        {0x2D, "Insert"},
        {0x2E, "Delete"},
        {0x2F, "Help"},
        {0x30, "0"},
        {0x31, "1"},
        {0x32, "2"},
        {0x33, "3"},
        {0x34, "4"},
        {0x35, "5"},
        {0x36, "6"},
        {0x37, "7"},
        {0x38, "8"},
        {0x39, "9"},
        {0x41, "A"},
        {0x42, "B"},
        {0x43, "C"},
        {0x44, "D"},
        {0x45, "E"},
        {0x46, "F"},
        {0x47, "G"},
        {0x48, "H"},
        {0x49, "I"},
        {0x4A, "J"},
        {0x4B, "K"},
        {0x4C, "L"},
        {0x4D, "M"},
        {0x4E, "N"},
        {0x4F, "O"},
        {0x50, "P"},
        {0x51, "Q"},
        {0x52, "R"},
        {0x53, "S"},
        {0x54, "T"},
        {0x55, "U"},
        {0x56, "V"},
        {0x57, "W"},
        {0x58, "X"},
        {0x59, "Y"},
        {0x5A, "Z"},
        {0x60, "Num 0"},
        {0x61, "Num 1"},
        {0x62, "Num 2"},
        {0x63, "Num 3"},
        {0x64, "Num 4"},
        {0x65, "Num 5"},
        {0x66, "Num 6"},
        {0x67, "Num 7"},
        {0x68, "Num 8"},
        {0x69, "Num 9"},
        {0x6A, "Num *"},
        {0x6B, "Num +"},
        {0x6C, "Num Enter"},
        {0x6D, "Num -"},
        {0x6E, "Num ."},
        {0x6F, "Num /"},
        {0x70, "F1"},
        {0x71, "F2"},
        {0x72, "F3"},
        {0x73, "F4"},
        {0x74, "F5"},
        {0x75, "F6"},
        {0x76, "F7"},
        {0x77, "F8"},
        {0x78, "F9"},
        {0x79, "F10"},
        {0x7A, "F11"},
        {0x7B, "F12"},
        {0x7C, "F13"},
        {0x7D, "F14"},
        {0x7E, "F15"},
        {0x7F, "F16"},
        {0x80, "F17"},
        {0x81, "F18"},
        {0x82, "F19"},
        {0x83, "F20"},
        {0x84, "F21"},
        {0x85, "F22"},
        {0x86, "F23"},
        {0x87, "F24"},
        {0x90, "Num Lock"},
        {0x91, "Scroll Lock"},
        {0xA0, "Left Shift"},
        {0xA1, "Right Shift"},
        {0xA2, "Left Ctrl"},
        {0xA3, "Right Ctrl"},
        {0xA4, "Left Alt"},
        {0xA5, "Right Alt"},
        {0xA6, "Browser Back"},
        {0xA7, "Browser Forward"},
        {0xA8, "Browser Refresh"},
        {0xA9, "Browser Stop"},
        {0xAA, "Browser Search"},
        {0xAB, "Browser Favorites"},
        {0xAC, "Browser Home"},
        {0xAD, "Volume Mute"},
        {0xAE, "Volume Down"},
        {0xAF, "Volume Up"},
        {0xB0, "Next Track"},
        {0xB1, "Previous Track"},
        {0xB2, "Stop Media"},
        {0xB3, "Play/Pause Media"},
        {0xB4, "Start Mail"},
        {0xB5, "Select Media"},
        {0xB6, "Start Application 1"},
        {0xB7, "Start Application 2"},
        {0xBA, "OEM 1"},
        {0xBB, "OEM Plus"},
        {0xBC, "OEM Comma"},
        {0xBD, "OEM Minus"},
        {0xBE, "OEM Period"},
        {0xBF, "OEM 2"},
        {0xC0, "OEM 3"},
        {0xDB, "OEM 4"},
        {0xDC, "OEM 5"},
        {0xDD, "OEM 6"},
        {0xDE, "OEM 7"},
        {0xDF, "OEM 8"},
        {0xE2, "OEM 102"},
        {0xE5, "Process"},
        {0xE7, "Packet"},
        {0xF6, "Attn"},
        {0xF7, "CrSel"},
        {0xF8, "ExSel"},
        {0xF9, "Erase EOF"},
        {0xFA, "Play"},
        {0xFB, "Zoom"},
        {0xFE, "PA1"},
        {0xFF, "Clear"}
    };

    return keyNames.count(key) ? keyNames[key] : "Unknown";
}

struct FLocation {
    std::string MapName;
    ELocation Type;
    std::string Name;
    FVector Location;
    FRotator Rotate;
};

class PaliaOverlay final : public OverlayBase {
protected:
    void DrawHUD() override;
    void DrawOverlay() override;
    void DrawGuiESP() override;
    void DrawGuiFOVCircle() override;
    void DrawEnabledFeatures() override;

public:
    static std::map<int, std::string> TypeIcons;
    
    bool show = true;
    bool getTheme = true;
    static const char* themes[4];

};