#pragma once

#include "Configuration.h"
#include "ToolHandler.h"
#include "HUDDetours.h"
#include "FishingDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include <imgui_internal.h>

#include "Modules/Tools_SwingSettings.h"
#include "Modules/Tools_CatchingSettings.h"
#include "Modules/Tools_HuntingSettings.h"

#include "Utils.h"
#include "imgui.h"

namespace Skills_ToolsSettings {
    inline void Show() {
        AValeriaCharacter* ValeriaCharacter = GetValeriaCharacter();
        UFishingComponent* FishingComponent = nullptr;
        auto EquippedTool = ToolHandler::EquippedTool;
        
        if (ValeriaCharacter) FishingComponent = ValeriaCharacter->GetFishing();

        Tools_SwingSettings::Show(ValeriaCharacter);
        Tools_CatchingSettings::Show(ValeriaCharacter);
        Tools_HuntingSettings::Show(ValeriaCharacter);

        if (ImGui::CollapsingHeader(LOC("header.other_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_CHECKBOX(LOC("checkbox.auto_gather_nearby_loot").c_str(), &Configuration::bEnableAutoGather, LOC("tooltip.auto_gather_nearby_loot").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                IMGUI_CHECKBOX(LOC("checkbox.skip_cooking_minigames").c_str(), &Configuration::bEnableCookingMinigameSkip, LOC("tooltip.skip_cooking_minigames").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                IMGUI_CHECKBOX(LOC("checkbox.auto_refill_focus").c_str(), &Configuration::bEnableAutoFocus, LOC("tooltip.auto_refill_focus").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::SameLine(175);
                ItemLabel(LOC("text.when_below").c_str(), LabelLeft, 85);
                ImGui::SetNextItemWidth(150.0f);
                IMGUI_SLIDER("##WhenFocusBelow", &Configuration::FocusBelowPercent, 20, 80, "%d%%", LOC("tooltip.when_below").c_str())
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader(LOC("header.fishing_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (IsComponentValid(FishingComponent)) {
                IMGUI_CHECKBOX(LOC("checkbox.no_rod_durability_loss").c_str(), &Configuration::bFishingNoDurability, LOC("tooltip.no_rod_durability_loss").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.enable_multiplayer_help").c_str(), &Configuration::bFishingMultiplayerHelp, LOC("tooltip.enable_multiplayer_help").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.always_perfect_catch").c_str(), &Configuration::bFishingPerfectCatch, LOC("tooltip.always_perfect_catch").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.instant_catch").c_str(), &Configuration::bFishingInstantCatch, LOC("tooltip.instant_catch").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)

                if (EquippedTool == ETools::FishingRod) {
                    IMGUI_CHECKBOX(LOC("checkbox.auto_fast_fishing").c_str(), &FishingDetours::bEnableAutoFishing, LOC("tooltip.auto_fast_fishing").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                    IMGUI_CHECKBOX(LOC("checkbox.require_holding_left_click").c_str(), &Configuration::bRequireClickFishing, LOC("tooltip.require_holding_left_click").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                } else {
                    ImGui::Spacing();
                    ImGui::Text(LOC("text.equip_fishing_rod_notice").c_str());
                    ImGui::Spacing();
                    Configuration::bRequireClickFishing = true;
                }

                IMGUI_CHECKBOX(LOC("checkbox.force_fishing_pool").c_str(), &FishingDetours::bOverrideFishingSpot, LOC("tooltip.force_fishing_pool").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)

                ImGui::SameLine();
                ImGui::SetNextItemWidth(200.0f);
                if (ImGui::BeginCombo("##FishingSpotsCombo", FishingDetours::FishingSpotNameMap[FishingDetours::OverrideFishingSpot].c_str())) {
                    for (auto& it : FishingDetours::FishingSpotNameMap) {
                        const std::string configStore = it.first;
                        const bool is_selected = (FishingDetours::OverrideFishingSpot == configStore);
                        if (ImGui::Selectable(it.second.c_str(), is_selected)) {
                            FishingDetours::OverrideFishingSpot = configStore;
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            } else {
                if (!ValeriaCharacter) {
                    ImGui::Text(LOC("text.waiting_character_init").c_str());
                } else {
                    ImGui::Text("Fishing component not available.");
                }
            }
        }

        // Gardening
        if (ImGui::CollapsingHeader(LOC("header.gardening_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_till").c_str(), &Configuration::bGardeningAutoTill, LOC("tooltip.auto_till").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_weed").c_str(), &Configuration::bGardeningAutoWeed, LOC("tooltip.auto_weed").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_harvest").c_str(), &Configuration::bGardeningAutoHarvest, LOC("tooltip.auto_harvest").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_replant").c_str(), &Configuration::bGardeningAutoReplant, LOC("tooltip.auto_replant").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.auto_fertilize").c_str(), &Configuration::bGardeningAutoFertilize, LOC("tooltip.auto_fertilize").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::SameLine();
                ImGui::SetNextItemWidth(200.0f);
                IMGUI_SUPPORTER_FEATURE(LOC("text.max_quantity").c_str(), &Configuration::GardeningFertilizerQty, LOC("tooltip.max_quantity").c_str(), "slider", 1, 99, "%d")
                //IMGUI_CHECKBOX("Auto Water", &Configuration::bGardeningAutoWater, "With your watering can equipped, water any seeds that need it.", "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
    }
}
