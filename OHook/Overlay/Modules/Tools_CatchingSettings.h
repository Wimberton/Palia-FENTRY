#pragma once

#include "Configuration.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace Tools_CatchingSettings {
    inline void Show(const AValeriaCharacter* ValeriaCharacter) {
        // Catching speed settings - update strings each time to reflect current language
        std::string speed_fast = LOC("text.speed_fast");
        std::string speed_medium = LOC("text.speed_medium");
        std::string speed_slow = LOC("text.speed_slow");
        std::string speed_custom = LOC("text.speed_custom");
        const char* speed_items[4] = {speed_fast.c_str(), speed_medium.c_str(), speed_slow.c_str(), speed_custom.c_str()};
        
        if (ImGui::CollapsingHeader(LOC("header.bug_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_catch_bugs").c_str(), &Configuration::bEnableBugCatching, LOC("tooltip.auto_catch_bugs").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                if (Configuration::bEnableBugCatching) {
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_equip_smoke_bombs").c_str(), &Configuration::bBugAutoEquipTool, LOC("tooltip.auto_equip_smoke_bombs").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.require_esp_toggles_catch").c_str(), &Configuration::bAutoCatchingRequireESP, LOC("tooltip.require_esp_toggles_catch").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_catching_low_durability").c_str(), &Configuration::bAvoidCatchingLowDurability, LOC("tooltip.avoid_catching_low_durability").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    ItemLabel(LOC("text.catch_distance").c_str(), LabelLeft, 115);
                    ImGui::SetNextItemWidth(150.0f);
                    IMGUI_SUPPORTER_FEATURE("##CatchDistance", &Configuration::BugCatchingDistance, LOC("tooltip.catch_distance").c_str(), "slider", 2.0f, 25.0f, "%1.0f")
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_catching_near_players").c_str(), &Configuration::bAvoidCatchingNearPlayers, LOC("tooltip.avoid_catching_near_players").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    ItemLabel(LOC("text.catching_speed").c_str(), LabelLeft, 115);
                    ImGui::SetNextItemWidth(150.0f);
                    if (ImGui::Combo("##CatchingPreset", &Configuration::BugSpeedPreset, speed_items, IM_ARRAYSIZE(speed_items))) {
                        if (Configuration::BugSpeedPreset != 3) {
                            Configuration::BugCatchingDelay = 100 * (1 + 4 * Configuration::BugSpeedPreset);
                        }
                        Configuration::Save(ESaveFile::ToolSkillsSettings);
                    }
                    if (Configuration::bAvoidCatchingNearPlayers) {
                        ImGui::SameLine(300);
                        ItemLabel("Avoidance Radius", LabelLeft, 115);
                        ImGui::SetNextItemWidth(150.0f);
                        IMGUI_SUPPORTER_FEATURE("##CatchingAvoidanceRadius", &Configuration::CatchingPlayerAvoidDistance, "The distance to avoid catching bugs when players are nearby.", "slider", 5.0f, 150.0f, "%1.0f");
                    }

                    if (Configuration::BugSpeedPreset == 3) {
                        ItemLabel(LOC("text.custom_speed").c_str(), LabelLeft, 115);
                        ImGui::SetNextItemWidth(150.0f);
                        if (ImGui::InputInt("##CatchingSpeed", &Configuration::BugCatchingDelay, 50)) {
                            Configuration::BugCatchingDelay = std::clamp(Configuration::BugCatchingDelay, 100, 2000);
                            Configuration::Save(ESaveFile::ToolSkillsSettings);
                        }
                    }
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
    }
}
