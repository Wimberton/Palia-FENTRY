#pragma once

#include "Configuration.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"
#include "Detours/Supporters/AutoTools/ToolSwinging.h"

#include "imgui.h"

namespace Tools_SwingSettings {
    inline void Show(const AValeriaCharacter* ValeriaCharacter) {
        if (ImGui::CollapsingHeader(LOC("header.axe_pickaxe_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_swing_tool").c_str(), &Configuration::bEnableAutoSwinging, LOC("tooltip.auto_swing_tool").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                if (Configuration::bEnableAutoSwinging) {
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_equip_tool").c_str(), &Configuration::bResourceAutoEquipTool, LOC("tooltip.auto_equip_tool").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.require_esp_toggles_swing").c_str(), &Configuration::bAutoSwingingRequireESP, LOC("tooltip.require_esp_toggles_swing").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_swinging_low_durability").c_str(), &Configuration::bAvoidSwingingLowDurability, LOC("tooltip.avoid_swinging_low_durability").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_chopping_grove").c_str(), &Configuration::bAvoidGroveChopping, LOC("tooltip.avoid_chopping_grove").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                    ImGui::SameLine(300);
                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_swinging_near_players").c_str(), &Configuration::bAvoidSwingingNearPlayers, LOC("tooltip.avoid_swinging_near_players").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)

                    IMGUI_SUPPORTER_FEATURE(LOC("checkbox.avoid_swinging_housing_plots").c_str(), &Configuration::bAvoidPlotSwinging, LOC("tooltip.avoid_swinging_housing_plots").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                    if (Configuration::bAvoidSwingingNearPlayers) {
                        ImGui::SameLine(300);
                        ItemLabel("Avoidance Radius", LabelLeft, 115);
                        ImGui::SetNextItemWidth(150.0f);
                        IMGUI_SUPPORTER_FEATURE("##SwingingAvoidanceRadius", &Configuration::SwingPlayerAvoidDistance, "The distance to avoid swinging tools when players are nearby.", "slider", 5.0f, 150.0f, "%1.0f");
                    }
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
        
        // Gathering System
        //if (ImGui::CollapsingHeader("Gathering System", ImGuiTreeNodeFlags_DefaultOpen)) {
        //    if (ValeriaCharacter) {
        //        // First row: Items to gather input and button
        //        ImGui::Text("Items to Gather:");
        //        ImGui::SameLine();
        //        ImGui::SetNextItemWidth(150.0f);
        //        if (ImGui::InputInt("##GatherCount", &ToolSwinging::GatherTargetCount, 1, 5)) {
        //            ToolSwinging::GatherTargetCount = std::clamp(ToolSwinging::GatherTargetCount, 1, 999);
        //        }
        //        
        //        ImGui::SameLine();
        //        
        //        // Gather button
        //        if (ToolSwinging::bIsGathering) {
        //            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
        //            if (ImGui::Button("Stop Gathering")) {
        //                ToolSwinging::bIsGathering = false;
        //                ToolSwinging::GatherCurrentCount = 0;
        //            }
        //            ImGui::PopStyleColor();
        //            
        //            ImGui::SameLine();
        //            ImGui::Text("Progress: %d/%d", ToolSwinging::GatherCurrentCount, ToolSwinging::GatherTargetCount);
        //        } else {
        //            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
        //            if (ImGui::Button("Start Gathering")) {
        //                ToolSwinging::GatherMultipleItems(ToolSwinging::GatherTargetCount);
        //            }
        //            ImGui::PopStyleColor();
        //        }
        //        
        //        // Second row: Gather radius slider
        //        ImGui::Text("Gather Radius:");
        //        ImGui::SameLine();
        //        ImGui::SetNextItemWidth(200.0f);
        //        if (ImGui::SliderFloat("##GatherRadius", &ToolSwinging::GatherRadius, 5.0f, 200.0f, "%.1f m")) {
        //            ToolSwinging::GatherRadius = std::clamp(ToolSwinging::GatherRadius, 5.0f, 200.0f);
        //        }
        //        
        //        // Show nearby gatherable count with configurable radius
        //        int nearbyGatherables = 0;
        //        if (ValeriaCharacter) {
        //            auto playerLocation = ValeriaCharacter->K2_GetActorLocation();
        //            for (auto& cachedResource : ActorHandler::GetActorsOfType(EType::Forage)) {
        //                if (cachedResource && cachedResource->Actor) {
        //                    auto gatherableActor = static_cast<ABP_ValeriaGatherableLoot_C*>(cachedResource->Actor);
        //                    if (gatherableActor && gatherableActor->IAmAlive) {
        //                        auto gatherableLocation = gatherableActor->K2_GetActorLocation();
        //                        float distance = playerLocation.GetDistanceToInMeters(gatherableLocation);
        //                        if (distance <= ToolSwinging::GatherRadius) {
        //                            nearbyGatherables++;
        //                        }
        //                    }
        //                }
        //            }
        //        }
        //        
        //        ImGui::Text("Available Gatherables: %d (within %.1fm)", nearbyGatherables, ToolSwinging::GatherRadius);
        //        
        //    } else {
        //        ImGui::Text("Waiting for character initialization...");
        //    }
        //}
    }
}
