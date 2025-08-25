#pragma once

#include "Configuration.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace Tools_HuntingSettings {
    inline void Show(const AValeriaCharacter* ValeriaCharacter) {
        // Hunting speed settings - update strings each time to reflect current language
        std::string speed_fast = LOC("text.speed_fast");
        std::string speed_medium = LOC("text.speed_medium");
        std::string speed_slow = LOC("text.speed_slow");
        std::string speed_custom = LOC("text.speed_custom");
        const char* speed_items[4] = {speed_fast.c_str(), speed_medium.c_str(), speed_slow.c_str(), speed_custom.c_str()};
        
        if (ImGui::CollapsingHeader(LOC("header.animal_balloon_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_hunt").c_str(), &Configuration::bEnableAnimalHunting, LOC("tooltip.auto_hunt").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                if (Configuration::bEnableAnimalHunting) {
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_equip_bow").c_str(), &Configuration::bAnimalAutoEquipTool, LOC("tooltip.auto_equip_bow").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
            
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.require_esp_toggles_hunt").c_str(), &Configuration::bAutoHuntingRequireESP, LOC("tooltip.require_esp_toggles_hunt").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_hunting_low_durability").c_str(), &Configuration::bAvoidHuntingLowDurability, LOC("tooltip.avoid_hunting_low_durability").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    ItemLabel(LOC("text.hunt_distance").c_str(), LabelLeft, 115);
                    ImGui::SetNextItemWidth(150.0f);
                    IMGUI_SUPPORTER_FEATURE("##HuntDistance", &Configuration::AnimalHuntingDistance, LOC("tooltip.hunt_distance").c_str(), "slider", 2.0f, 20.0f, "%1.0f")
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_hunting_near_players").c_str(), &Configuration::bAvoidHuntingNearPlayers, LOC("tooltip.avoid_hunting_near_players").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    ItemLabel(LOC("text.hunting_speed").c_str(), LabelLeft, 115);
                    ImGui::SetNextItemWidth(150.0f);
                    if (ImGui::Combo("##HuntingPreset", &Configuration::AnimalSpeedPreset, speed_items, IM_ARRAYSIZE(speed_items))) {
                        if (Configuration::AnimalSpeedPreset != 3) {
                            Configuration::AnimalHuntingDelay = 100 * (1 + 4 * Configuration::AnimalSpeedPreset);
                        }
                        Configuration::Save(ESaveFile::ToolSkillsSettings);
                    }
                    if (Configuration::bAvoidHuntingNearPlayers) {
                        ImGui::SameLine(300);
                        ItemLabel("Avoidance Radius", LabelLeft, 115);
                        ImGui::SetNextItemWidth(150.0f);
                        IMGUI_SUPPORTER_FEATURE("##HuntingAvoidanceRadius", &Configuration::HuntingPlayerAvoidDistance, "The distance to avoid hunting animals when players are nearby.", "slider", 5.0f, 150.0f, "%1.0f");
                    }

                    if (Configuration::AnimalSpeedPreset == 3) {
                        ItemLabel(LOC("text.custom_speed").c_str(), LabelLeft, 115);
                        ImGui::SetNextItemWidth(150.0f);
                        if (ImGui::InputInt("##HuntingSpeed", &Configuration::AnimalHuntingDelay, 50)) {
                            Configuration::AnimalHuntingDelay = std::clamp(Configuration::AnimalHuntingDelay, 100, 2000);
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
