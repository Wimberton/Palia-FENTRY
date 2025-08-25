#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace Aimbots_FunSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.inteliaim_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            IMGUI_CHECKBOX(LOC("checkbox.enable_inteliaim").c_str(), &Configuration::bEnableInteliAim, LOC("tooltip.enable_inteliaim").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
            if (Configuration::bEnableInteliAim) {
                ImGui::SetNextItemWidth(200.0f);
                IMGUI_SLIDER(LOC("slider.inteliaim_radius").c_str(), &Configuration::FOVRadius, 10.0f, 600.0f, "%1.0f", LOC("tooltip.inteliaim_radius").c_str())
                IMGUI_CHECKBOX(LOC("checkbox.hide_circle").c_str(), &Configuration::bHideFOVCircle, LOC("tooltip.hide_circle").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                if (!Configuration::bHideFOVCircle) {
                    ImGui::SetNextItemWidth(200.0f);
                    IMGUI_SLIDER(LOC("slider.circle_transparency").c_str(), &Configuration::CircleAlpha, 0.25f, 1.0f, "%.2f", LOC("tooltip.circle_transparency").c_str())
                    IMGUI_CHECKBOX(LOC("checkbox.show_crosshair").c_str(), &Configuration::bDrawCrosshair, LOC("tooltip.show_crosshair").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                }
            }
        }

        ImGui::NextColumn();

        // InteliTarget Controls
        if (ImGui::CollapsingHeader(LOC("header.intelitarget_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (Configuration::bEnableInteliAim) {
                // Classic Aimbot checkbox with mutual exclusivity
                if (ImGui::Checkbox(LOC("checkbox.enable_aimbot").c_str(), &Configuration::bEnableAimbot)) {
                    if (Configuration::bEnableAimbot) {
                        Configuration::bEnableSilentAimbot = false; // Disable silent aimbot
                        Configuration::Save(ESaveFile::AimSettings);
                    }
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", LOC("tooltip.enable_aimbot").c_str());
                }
                
                // Silent Aimbot checkbox with mutual exclusivity
                if (ImGui::Checkbox(LOC("checkbox.enable_silent_aimbot").c_str(), &Configuration::bEnableSilentAimbot)) {
                    if (Configuration::bEnableSilentAimbot) {
                        Configuration::bEnableAimbot = false; // Disable classic aimbot
                        Configuration::Save(ESaveFile::AimSettings);
                    }
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", LOC("tooltip.enable_silent_aimbot").c_str());
                }
                
                // Show aimbot settings if classic aimbot is enabled
                if (Configuration::bEnableAimbot) {
                    ImGui::SetNextItemWidth(200.0f);
                    IMGUI_SLIDER("Smoothing", &Configuration::AimbotSmoothing, 1.0f, 100.0f, "%.1f", "Controls how smooth the aimbot is (1.0 = instant, 100.0 = very smooth)")
                }
                
                IMGUI_CHECKBOX(LOC("checkbox.enable_teleporting_to_target").c_str(), &Configuration::bTeleportToTargeted, LOC("tooltip.enable_teleporting_to_target").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                
                if (Configuration::bTeleportToTargeted) {
                    IMGUI_CHECKBOX(LOC("checkbox.avoid_teleporting_to_players").c_str(), &Configuration::bAvoidTeleportingToPlayers, LOC("tooltip.avoid_teleporting_to_players").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                    IMGUI_CHECKBOX(LOC("checkbox.avoid_teleporting_when_players_near").c_str(), &Configuration::bDoRadiusPlayersAvoidance, LOC("tooltip.avoid_teleporting_when_players_near").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                    if (Configuration::bDoRadiusPlayersAvoidance) {
                        ImGui::SetNextItemWidth(200.0f);
                        IMGUI_SLIDER(LOC("slider.avoidance_radius").c_str(), &Configuration::TeleportPlayerAvoidanceRadius, 1, 100, "%d", LOC("tooltip.avoidance_radius").c_str())
                    }
                }
            } else {
                Configuration::bEnableSilentAimbot = false;
                Configuration::bEnableAimbot = false;
                ImGui::Spacing();
                ImGui::Text(LOC("text.enable_inteliaim_notice").c_str());
                ImGui::Spacing();
            }
        }
    }
}