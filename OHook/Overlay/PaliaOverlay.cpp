#include "PaliaOverlay.h"
#include "Configuration.h"
#include "LocalizationManager.h"
#include "HotkeysManager.h"
#include "Main.h"
#include "ESP.h"

#include <SDK/Palia_parameters.hpp>

#include "ImGuiExt.h"
#include "SDKExt.h"
#include "Utils.h"

#include <algorithm>
#include <codecvt>
#include <imgui_internal.h>
#include <Fonts.h>

#include "Modules/ESP_VisualSettings.h"
#include "Modules/ESP_AnimalSettings.h"
#include "Modules/ESP_BugSettings.h"
#include "Modules/ESP_ForageableSettings.h"
#include "Modules/ESP_OreSettings.h"
#include "Modules/ESP_SingleSettings.h"
#include "Modules/ESP_TreeSettings.h"
#include "Modules/Aimbots_FunSettings.h"
#include "Modules/Movement_TeleportSettings.h"
#include "Modules/Skills_ToolsSettings.h"
#include "Modules/Selling_PlayerSettings.h"
#include "Modules/Mods_SettingsGlobal.h"

using namespace SDK;

bool waitingForKey = false;
const char* PaliaOverlay::themes[4] = { "Main", "Spectrum Light", "Magma", "Custom Theme" };

void PaliaOverlay::DrawEnabledFeatures() {    
    PaliaESP::DrawEnabledFeatures();
}
void PaliaOverlay::DrawGuiESP() {    
    PaliaESP::DrawGuiESP();
}
void PaliaOverlay::DrawGuiFOVCircle() {
    PaliaESP::DrawGuiFOVCircle();
}

void PaliaOverlay::DrawHUD() {
    //auto Overlay = static_cast<PaliaOverlay*>(Instance);
    static bool bConfigLoaded = false;
    if (!bConfigLoaded) {
        Configuration::Load();
        LocalizationManager::Initialize();
        bConfigLoaded = true;
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 0.35f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

    std::string defaultWatermarkText = "Palia - " + EValeriaLevelString[ActorHandler::CurrentMap];
    bool showWatermark = false;
    if ((ActorHandler::CurrentLevel && (EValeriaLevel::Startup & ActorHandler::CurrentMap)) || Configuration::bShowWatermark) {
        if (EValeriaLevel::Startup & ActorHandler::CurrentMap) {
            defaultWatermarkText = LOC("text.waiting_game_load");
        }
        showWatermark = true;
    }

    if (showWatermark) {
        ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x - ImGui::CalcTextSize(defaultWatermarkText.c_str()).x) * 0.5f, 10.0f));
        ImGui::Begin("Watermark", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
        ImGui::Text("%s", defaultWatermarkText.c_str());
        ImGui::End();
    }
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar();

    if (getTheme) { // Save previousColors here?
        switch (Configuration::selectedTheme) {
        case 0:
            ImGui::StyleColorsDark();
            break;
        case 1:
           ImGui::Spectrum::StyleColorsSpectrum();
           break;
        case 2:
           ImGui::Magma::StyleColorsMagma();
           break;
        case 3:
            // load custom theme logic.
            Configuration::ApplyCustomTheme();
            break;
        default:
            ImGui::StyleColorsDark();
            break;
        }
        getTheme = false;
    }

    /*
     * Notification rendering
     */
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImVec4 windowBg = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_WindowBg));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(windowBg.x, windowBg.y, windowBg.z, 1.00f));
    ImGui::RenderNotifications();
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(1);
    
    /*
     * Notification(s) for first use-case scenario
     */
    static bool displayedFirstUseNotif, displayedCorruptConfigNotif = false;
    if (Configuration::bFirstUse && !displayedFirstUseNotif && !Configuration::ConfigIsCorrupt) {
        ImGui::InsertNotification({ ImGuiToastType::Info, 8000, LOC("notification.first_use").c_str() });
        displayedFirstUseNotif = true;
    }
}

void PaliaOverlay::DrawOverlay() {
    const ImGuiIO& io = ImGui::GetIO();
    constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;

    // Ensure show state is synchronized with overlay visibility
    // This fixes the issue where clicking X breaks hotkey reopening
    if (bShowOverlay && !show) {
        show = true;
    }

    // Calculate the center position for the window
    const auto center_pos = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    const auto window_size = ImVec2(Configuration::windowSizeX, Configuration::windowSizeY);
    const auto window_pos = ImVec2(center_pos.x - window_size.x * 0.5f, center_pos.y - window_size.y * 0.5f);

    // Set the initial window position to the center of the screen
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_FirstUseEver);

    const auto WindowTitle = LOC("window.main_title");
    //auto Overlay = static_cast<PaliaOverlay*>(Instance);

    if (ImGui::Begin(WindowTitle.data(), &show, window_flags)) {

        /*
         * First use case-scenario bool
         */
        if (Configuration::bFirstUse) {
            Configuration::bFirstUse = false;
            Configuration::Save(ESaveFile::OverlaySettings);
        }
        
        static int OpenTab = 0;
        static int previousLanguage = -1;
        static bool needsTabRestore = false;

        // Detect language changes and flag for tab restoration
        int currentLanguage = static_cast<int>(LocalizationManager::GetCurrentLanguage());
        if (previousLanguage != -1 && previousLanguage != currentLanguage) {
            needsTabRestore = true;
        }
        previousLanguage = currentLanguage;

        if (ImGui::IsMouseDragging(0) &&
            (!AreFloatsEqual(Configuration::windowSizeX, ImGui::GetWindowSize().x) || !AreFloatsEqual(Configuration::windowSizeY, ImGui::GetWindowSize().y))) { // dont want to spam save if you're just dragging your mouse.
            Configuration::windowSizeX = ImGui::GetWindowSize().x;
            Configuration::windowSizeY = ImGui::GetWindowSize().y;
            Configuration::Save(ESaveFile::OverlaySettings);
        }

        ImGuiTabItemFlags tabFlags0 = (OpenTab == 0 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags1 = (OpenTab == 1 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags2 = (OpenTab == 2 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags3 = (OpenTab == 3 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags4 = (OpenTab == 4 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;
        ImGuiTabItemFlags tabFlags5 = (OpenTab == 5 && needsTabRestore) ? ImGuiTabItemFlags_SetSelected : 0;

        // Draw tabs
        if (ImGui::BeginTabBar("OverlayTabs")) {
            if (ImGui::BeginTabItem((ICON_FA_EYE " " + LOC("tab.esp_visuals")).c_str(), nullptr, tabFlags0)) {
                OpenTab = 0;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_CROSSHAIRS " " + LOC("tab.aim_assistants")).c_str(), nullptr, tabFlags1)) {
                OpenTab = 1;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_PERSON_WALKING " " + LOC("tab.movements_tps")).c_str(), nullptr, tabFlags2)) {
                OpenTab = 2;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_SCREWDRIVER_WRENCH " " + LOC("tab.skills_tools")).c_str(), nullptr, tabFlags3)) {
                OpenTab = 3;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_BASKET_SHOPPING " " + LOC("tab.stores_inventory")).c_str(), nullptr, tabFlags4)) {
                OpenTab = 4;
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem((ICON_FA_GEAR " " + LOC("tab.mods_settings")).c_str(), nullptr, tabFlags5)) {
                OpenTab = 5;
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        // Reset the flag after applying
        if (needsTabRestore) {
            needsTabRestore = false;
        }

        if (OpenTab == 0) {
            ImGui::Columns(3, nullptr, false);

            ESP_VisualSettings::Show();
            ImGui::NextColumn();
            ESP_AnimalSettings::Show();
            ESP_OreSettings::Show();
            ESP_ForageableSettings::Show();
            ImGui::NextColumn();
            ESP_BugSettings::Show();
            ESP_TreeSettings::Show();
            ESP_SingleSettings::Show();
        }
        else if (OpenTab == 1) {
            ImGui::Columns(2, nullptr, false);

            Aimbots_FunSettings::Show();

        }
        else if (OpenTab == 2) {
            ImGui::Columns(2, nullptr, false);

            Movement_TeleportSettings::Show();
        }
        else if (OpenTab == 3) {
            ImGui::Columns(2, nullptr, false);

            Skills_ToolsSettings::Show();
        }
        else if (OpenTab == 4) {
            ImGui::Columns(2, nullptr, false);

            Selling_PlayerSettings::Show();
        }
        else if (OpenTab == 5) {
            ImGui::Columns(2, nullptr, false);

            Mods_SettingsGlobal::Show();
        }
    }

    ImGui::End();

    // If user clicked X to close the window, hide the overlay
    if (!show) {
        ShowOverlay(false);
    }
}