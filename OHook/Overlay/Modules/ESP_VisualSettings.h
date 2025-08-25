#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_VisualSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.visual_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            IMGUI_CHECKBOX(LOC("checkbox.enable_esp").c_str(), &Configuration::bEnableESP, LOC("tooltip.enable_esp").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);

            if(Configuration::bEnableESP) {
                ImGui::SetNextItemWidth(200.0f);
                IMGUI_SLIDER(LOC("slider.esp_distance").c_str(), &Configuration::CullDistance, 1.0, 1000.0, "%1.0f", LOC("tooltip.esp_distance").c_str())

                ImGui::SetNextItemWidth(200.0f);
                IMGUI_SLIDER(LOC("slider.esp_text_scale").c_str(), &Configuration::ESPTextScale, 0.5f, 2.0f, "%.1f", LOC("tooltip.esp_text_scale").c_str())
                
                IMGUI_CHECKBOX(LOC("checkbox.show_entity_distance").c_str(), &Configuration::bEnableESPDistance, LOC("tooltip.show_entity_distance").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.show_entity_despawn_timers").c_str(), &Configuration::bEnableESPDespawnTimer, LOC("tooltip.show_entity_despawn_timers").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.show_esps_on_world_map").c_str(), &Configuration::bEnableMapESP, LOC("tooltip.show_esps_on_world_map").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.use_native_esp_icons").c_str(), &Configuration::bEnableESPIcons, LOC("tooltip.use_native_esp_icons").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.show_active_mods").c_str(), &Configuration::showEnabledFeaturesWindow, LOC("tooltip.show_active_mods").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                //IMGUI_CHECKBOX("Show Player List", &Configuration::showPlayerDistancesWindow, "Display an overlay window of the names and distances of players around you", ImGui::CheckboxHotkeyFlags::HOTKEY)
            }
        }
    }
}
