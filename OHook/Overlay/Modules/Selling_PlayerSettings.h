#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "StoreDetours.h"
#include "WidgetHandler.h"
#include "LocalizationManager.h"
#include "Modules/Store_AutoSellSettings.h"

#include <imgui_internal.h>

#include "Utils.h"
#include "imgui.h"

namespace Selling_PlayerSettings {
    inline void Show() {
        PaliaOverlay* Overlay = static_cast<PaliaOverlay*>(OverlayBase::Instance);
        AValeriaCharacter* ValeriaCharacter = GetValeriaCharacter();
#ifdef ENABLE_SUPPORTER_FEATURES
        if (ImGui::CollapsingHeader(LOC("header.inventory_actions").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                ImGui::Text(LOC("text.inventory_slot_selector").c_str());
                ImGui::SameLine(0.0f, 150.0f);
                if (ImGui::SmallButton(LOC("button.all").c_str())) {
                    bool state = Configuration::InventorySlot[0][0];
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 8; j++) {
                            Configuration::InventorySlot[i][j] = !state;
                        }
                    }
                }
                for (int i = 4; i >= 0; i--) {
                    for (int j = 0; j < 8; j++) {
                        ImGui::Checkbox(std::format("##InventorySelector{}{}", i,j).c_str(), &Configuration::InventorySlot[i][j]);
                        if (j != 7) {
                            ImGui::SameLine(0.0f,10.0f);
                        }
                    }
                }
                ImGui::Spacing();
                ItemLabel(LOC("text.amount").c_str(), LabelLeft, 55);
                ImGui::SetNextItemWidth(138.0f);
                if (ImGui::InputInt("##InventoryCount", &Configuration::InventoryCount), 1, 10) {
                    Configuration::InventoryCount = std::clamp(Configuration::InventoryCount, 1, 999);
                }
                ImGui::SameLine();
                int RadioState = Configuration::InventoryAmmo ? 1 : 0;
                if (ImGui::RadioButton(LOC("text.backpack").c_str(), &RadioState, 0)) {
                    Configuration::InventoryAmmo = RadioState == 1;
                }
                if (ImGui::Button(LOC("button.sell").c_str())) {
                    StoreDetours::bShouldManualSell = true;
                }
                ImGui::SameLine();
                if (ImGui::Button(LOC("button.discard").c_str())) {
                    StoreDetours::Func_TrashItem();
                }
                ImGui::SameLine();
                if (ImGui::Button(LOC("button.storage").c_str())) {
                    StoreDetours::Func_StoreItem();
                }
                //ImGui::SameLine();
                //if (ImGui::Button(LOC("button.duplicate").c_str())) {
                //    StoreDetours::Func_DuplicateItem();
                //}
                ImGui::SameLine();
                if (ImGui::RadioButton(LOC("text.ammo_pouch").c_str(), &RadioState, 1)) {
                    Configuration::InventoryAmmo = RadioState == 1;
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        if (ImGui::CollapsingHeader(LOC("header.auto_sell").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                Store_AutoSellSettings::Show();
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        ImGui::NextColumn();
#endif

        if (ImGui::CollapsingHeader(LOC("header.stores").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            if (ValeriaCharacter) {
                ImGuiStyle style = ImGui::GetStyle();
                float width = ImGui::CalcItemWidth();
                float spacing = style.ItemInnerSpacing.x;
                float buttonSize = ImGui::GetFrameHeight();

                static int selectedStore = 2;

                IMGUI_CHECKBOX(LOC("checkbox.item_buy_multiplier").c_str(), &Configuration::bEnableBuyMultiplier, LOC("tooltip.item_buy_multiplier").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);
                if (Configuration::bEnableBuyMultiplier) {
                    IMGUI_CHECKBOX(LOC("checkbox.enable_ctrl_click_buy").c_str(), &Configuration::bEnableCtrlClickBuy, LOC("tooltip.enable_ctrl_click_buy").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY);

                    ImGui::SetNextItemWidth(200.0f);
                    IMGUI_SLIDER(LOC("text.amount_to_multiply").c_str(), &Configuration::buyMultiplierValue, 1, 99, "%d", LOC("tooltip.amount_to_multiply").c_str())
                }

                ImGui::Text(LOC("text.open_remote_stores").c_str());

                ImGui::PushItemWidth(width - spacing * 2.0f - buttonSize * 2.0f); //ImGui::PushItemWidth(CalcTextSize(stores[2])).x + style.FramePadding.x * 2.0f);
                ImGui::SetNextItemWidth(250.0f);
                if (ImGui::BeginCombo("##VillagerStores", StoreDetours::GuildStores[selectedStore].c_str())) {
                    for (auto& it : StoreDetours::GuildStores) {
                        const int guildStore = it.first;
                        const bool is_selected = (selectedStore == guildStore);
                        if (ImGui::Selectable(it.second.c_str(), is_selected)) {
                            selectedStore = guildStore;
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::PopItemWidth();

                if (WidgetHandler::GameplayUIManager && WidgetHandler::GameplayUIManager->IsValidLowLevel()) {
                    ImGui::SameLine();
                    IMGUI_BUTTON(LOC("button.open_guild_store").c_str(),
                        StoreDetours::Func_OpenGuildStore(ValeriaCharacter, selectedStore);
                        Overlay->ShowOverlay(false);
                    );
                } else {
                    ImGui::SameLine();
                    ImGui::Text(LOC("text.couldnt_retrieve_stores").c_str());
                    // ======== END OF GUILD STORES
                }

                ImGui::PushItemWidth(width - spacing * 2.0f - buttonSize * 2.0f); //ImGui::PushItemWidth(CalcTextSize(stores[2])).x + style.FramePadding.x * 2.0f);
                ImGui::SetNextItemWidth(250.0f);
                if (ImGui::BeginCombo("##BuildingStores", StoreDetours::ConfigStores[StoreDetours::SelectedStoreConfig].c_str())) {
                    for (auto& it : StoreDetours::ConfigStores) {
                        const std::string configStore = it.first;
                        const bool is_selected = (StoreDetours::SelectedStoreConfig == configStore);
                        if (ImGui::Selectable(it.second.c_str(), is_selected)) {
                            StoreDetours::SelectedStoreConfig = configStore;
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
                ImGui::PopItemWidth();

                if (WidgetHandler::GameplayUIManager && WidgetHandler::GameplayUIManager->IsValidLowLevel()) {
                    ImGui::SameLine();
                    IMGUI_BUTTON(LOC("button.open_building_store").c_str(),
                        StoreDetours::bShouldOpenConfigStore = true;
                        Overlay->ShowOverlay(false);
                    );
                } else {
                    ImGui::SameLine();
                    ImGui::Text(LOC("text.couldnt_retrieve_stores").c_str());
                    // ======== END OF GUILD STORES
                }
                ImGui::Text(LOC("text.stores_night_notice").c_str());
                ImGui::Text(LOC("text.stores_hours_notice").c_str());
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

#ifndef ENABLE_SUPPORTER_FEATURES
        ImGui::NextColumn();
#endif

        if (ImGui::CollapsingHeader(LOC("header.player_features").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                if (WidgetHandler::GameplayUIManager && WidgetHandler::GameplayUIManager->IsValidLowLevel()) {
                    IMGUI_BUTTON(LOC("button.open_player_storage").c_str(),
                        WidgetHandler::GameplayUIManager->Implementation_OpenPlayerStorage();
                        Overlay->ShowOverlay(false);
                    );
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        if (ImGui::CollapsingHeader(LOC("header.auto_open").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_CHECKBOX(LOC("checkbox.waterlogged_chests").c_str(), &Configuration::bAutoOpenWaterlogged, LOC("tooltip.waterlogged_chests").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.unopened_oysters").c_str(), &Configuration::bAutoOpenOyster, LOC("tooltip.unopened_oysters").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.elder_clam_mushrooms").c_str(), &Configuration::bAutoOpenElderClam, LOC("tooltip.elder_clam_mushrooms").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        if (ImGui::CollapsingHeader(LOC("header.auto_storage").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_CHECKBOX(LOC("checkbox.furniture_auto_storage").c_str(), &Configuration::bAutoStoreDecor, LOC("tooltip.furniture_auto_storage").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
    }
}
