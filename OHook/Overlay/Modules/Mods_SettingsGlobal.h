#pragma once

#include "PaliaOverlay.h"
#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "Utils.h"
#include "imgui.h"

namespace Mods_SettingsGlobal {
    inline void Show() {
        AValeriaCharacter* ValeriaCharacter = GetValeriaCharacter();
        constexpr int i1000 = 1000;
            
        if (ImGui::CollapsingHeader(LOC("header.character_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_CHECKBOX(LOC("checkbox.anti_afk").c_str(), &Configuration::bEnableAntiAfk, LOC("tooltip.anti_afk").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.unlimited_wardrobe_respecs").c_str(), &Configuration::bEnableUnlimitedWardrobeRespec, LOC("tooltip.unlimited_wardrobe_respecs").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();

                IMGUI_CHECKBOX(LOC("checkbox.further_interaction_distance").c_str(), &Configuration::bEnableInteractionMods, LOC("tooltip.further_interaction_distance").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                if (Configuration::bEnableInteractionMods) {
                    float step = 1.0f;
                    float step_fast = 100.0f;
                    ImGui::SetNextItemWidth(200.0f);
                    if (ImGui::InputScalar(LOC("text.interaction_distance").c_str(), ImGuiDataType_Float, &Configuration::InteractionDistance, &step, &step_fast, "%.1f", ImGuiInputTextFlags_None)) {
                        Configuration::InteractionDistance = std::clamp(Configuration::InteractionDistance, 1.0f, 99999.0f);
                        Configuration::Save(ESaveFile::ModSettings);
                    }
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        ImGui::SetTooltip(LOC("tooltip.interaction_distance").c_str());
                }

                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.teleport_to_waypoints").c_str(), &Configuration::bEnableWaypointTeleport, LOC("tooltip.teleport_to_waypoints").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.easy_quest_mode").c_str(), &Configuration::bEasyModeActive, LOC("tooltip.easy_quest_mode").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }

        if (ImGui::CollapsingHeader(LOC("header.ui_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            IMGUI_CHECKBOX(LOC("checkbox.show_watermark").c_str(), &Configuration::bShowWatermark, LOC("tooltip.show_watermark").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
            
            ImGui::Spacing();

            // Language selection dropdown
            static const char* languageNames[] = { "English", "Español", "Português", "中文" };
            int currentLang = static_cast<int>(LocalizationManager::GetCurrentLanguage());
            
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo("##LanguageSelector", &currentLang, languageNames, IM_ARRAYSIZE(languageNames))) {
                LocalizationManager::SetLanguage(static_cast<Language>(currentLang));
            }
            ImGui::SameLine();
            ImGui::Text("%s", LOC("combo.language").c_str());
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("%s", LOC("tooltip.language").c_str());
            }
            
            // Translation feedback note
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f)); // Light gray color
            ImGui::TextWrapped("%s", LOC("note.translation_feedback").c_str());
            ImGui::PopStyleColor();
            
            ImGui::Spacing();

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo("##ThemesCombo", &Configuration::selectedTheme, PaliaOverlay::themes, IM_ARRAYSIZE(PaliaOverlay::themes))) {
                switch (Configuration::selectedTheme) {
                case 0: // Main
                    ImGui::StyleColorsDark();
                    Configuration::Save(ESaveFile::OverlaySettings);
                    break;
                case 1: // Spectrum Light
                    ImGui::Spectrum::StyleColorsSpectrum();
                    Configuration::Save(ESaveFile::OverlaySettings);
                    break;
                case 2: // Magma
                    ImGui::Magma::StyleColorsMagma();
                    Configuration::Save(ESaveFile::OverlaySettings);
                    break;
                case 3: // Custom theme
                    Configuration::ApplyCustomTheme();
                    Configuration::Save(ESaveFile::OverlaySettings);
                    break;
                default:
                    break;
                }
            }
            ImGui::SameLine();
            ImGui::Text(LOC("text.select_theme").c_str());

            ImGuiStyle* style = &ImGui::GetStyle();
            auto guiColor = style->Colors;

            static int selectedColor = -1;
            static std::string currentColorName = "Select a widget";

            static bool openCustomThemePopup = false;

            if (Configuration::selectedTheme != 3) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, (Configuration::selectedTheme == 3));
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, style->Alpha * 0.25f);
                ImGui::Button(LOC("button.edit_custom_theme").c_str());
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();

                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.edit_custom_theme_disabled").c_str());
            }
            else {
                if (ImGui::Button(LOC("button.edit_custom_theme").c_str())) {
                    openCustomThemePopup = true;

                    previousColors.clear(); // Ensuring previousColors is fresh.

                    for (int i = 0; i < ImGuiCol_COUNT; ++i) {
                        ImVec4 col = style->Colors[i];
                        previousColors[i] = col;
                    }
                }
            }

            if (ImGui::BeginPopupModal(LOC("popup.custom_theme_editor").c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
                if (ImGui::BeginCombo(LOC("text.widgets").c_str(), currentColorName.c_str())) {
                    for (const auto& colorPair : GuiColors) {
                        int colorEnum = colorPair.first;
                        const std::string& colorName = colorPair.second;

                        bool isSelected = (selectedColor == colorEnum);
                        if (ImGui::Selectable(colorName.c_str(), isSelected)) {
                            selectedColor = colorEnum;
                            currentColorName = colorName;
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                if (selectedColor != -1) {
                    ImVec4& color = style->Colors[selectedColor];

                    ImGui::Text("%s color", currentColorName.c_str());
                    ImGui::SameLine();
                    if (ImGui::ColorEdit4("##GuiColorPicker", reinterpret_cast<float*>(&color), ImGuiColorEditFlags_NoInputs)) {
                        auto colorIt = Configuration::customColors.find(selectedColor);
                        if (colorIt != Configuration::customColors.end()) { // Check if color already exists in customColors & replace instead of inserting.
                            if (colorIt->second != color) {
                                colorIt->second = color;
                            }
                        }
                        else {
                            Configuration::customColors.insert(std::make_pair(selectedColor, color));
                        }
                        style->Colors[selectedColor] = color;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button(LOC("button.undo").c_str())) {
                        // Undo colour function
                        auto it = previousColors.find(selectedColor);
                        auto colorIt = Configuration::customColors.find(selectedColor);
                        if (it != previousColors.end()) {
                            style->Colors[selectedColor] = it->second;
                            colorIt->second = it->second;
                        }
                    }
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(LOC("text.undo_changes").c_str());

                    ImGui::BeginGroupPanel("Widget Preview");
                    {
                        ImGui::Spacing();

                        // Widget preview
                        GetWidgetForPreview(selectedColor);

                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();
                }

                ImGui::Separator();
                // Calculate the center position buttons
                float windowWidth = ImGui::GetWindowSize().x;
                float buttonWidth = 160.0f * 2 + ImGui::GetStyle().ItemSpacing.x;
                ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

                // Save button
                if (ImGui::Button(LOC("button.save").c_str(), ImVec2(160, 0))) {
                    // Save to config.
                    Configuration::Save(ESaveFile::CustomThemeSettings);
                    openCustomThemePopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();

                // Cancel button
                if (ImGui::Button(LOC("button.close_without_saving").c_str(), ImVec2(160, 0))) {
                    // Restore old colors.
                    auto colorIt = Configuration::customColors.find(selectedColor);
                    for (auto& it : previousColors) {
                        int idx = it.first;
                        ImVec4 col = it.second;
                        style->Colors[idx] = col;
                        colorIt->second = col;
                    }

                    previousColors.clear();
                    openCustomThemePopup = false;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (openCustomThemePopup) {
                ImGui::OpenPopup(LOC("popup.custom_theme_editor").c_str());
            }
        }

        ImGui::NextColumn();

        // Fun Mods - Entities column
        if (ImGui::CollapsingHeader(LOC("header.fun_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                IMGUI_CHECKBOX(LOC("checkbox.advanced_placement").c_str(), &Configuration::bPlaceAnywhere, LOC("tooltip.advanced_placement").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                if (Configuration::bPlaceAnywhere) {
                    ImGui::SetNextItemWidth(200.0f);
                    IMGUI_SLIDER(LOC("text.caps_lock_rotation").c_str(), &Configuration::PlacementRotation, 1.0, 90.0, "%1.0f", LOC("tooltip.caps_lock_rotation").c_str())
                    ImGui::Spacing();
                }
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.temporarily_unlock_outfits").c_str(), &Configuration::bEnableOutfitCustomization, LOC("tooltip.temporarily_unlock_outfits").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                if (Configuration::bEnableOutfitCustomization) {
                    ImGui::Text(LOC("text.outfits_notice").c_str());
                    ImGui::Spacing();
                }
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.temporarily_unlock_decor_tints").c_str(), &Configuration::bEnableContentUnlocker, LOC("tooltip.temporarily_unlock_decor_tints").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                // Disabled until fixed
                IMGUI_SUPPORTER_FEATURE(LOC("checkbox.temporarily_unlock_landscapes").c_str(), &Configuration::bEnableFreeLandscape, LOC("tooltip.temporarily_unlock_landscapes").c_str(), "checkbox", ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.show_villager_weekly_gifts").c_str(), &Configuration::bEnableShowWeeklyWants, LOC("tooltip.show_villager_weekly_gifts").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.unrepair_tool_for_gold").c_str(), &Configuration::bEnableToolBricker, LOC("tooltip.unrepair_tool_for_gold").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                if(Configuration::bEnableToolBricker) {
                    ImGui::Spacing();
                    ImGui::Text(LOC("text.max_unrepair_amount").c_str());
                    ImGui::SetNextItemWidth(325.0f);
                    if (ImGui::InputScalar("##MaxUnrepairAmmount", ImGuiDataType_S32, &Configuration::ToolBrickerMaxSell, &i1000)) {
                        Configuration::ToolBrickerMaxSell = std::clamp(Configuration::ToolBrickerMaxSell, 1, 999999);
                        Configuration::Save(ESaveFile::ModSettings);
                    }
                }
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.fulfill_infinite_player_requests").c_str(), &Configuration::bEnableRequestMods, LOC("tooltip.fulfill_infinite_player_requests").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                //ImGui::Spacing();
                //IMGUI_CHECKBOX("Show Unseen Items For Requests", &Configuration::bEnableUnseenItems, "Show items you haven't seen yet in the Request Panel", ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                IMGUI_CHECKBOX(LOC("checkbox.black_market_prize_wheel").c_str(), &Configuration::bEnablePrizeWheel, LOC("tooltip.black_market_prize_wheel").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                ImGui::Spacing();
                if (Configuration::bEnablePrizeWheel) {
                    IMGUI_CHECKBOX(LOC("checkbox.use_locked_storage").c_str(), &Configuration::bPrizeWheelUseLocked, LOC("tooltip.use_locked_storage").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                    ImGui::BeginGroupPanel(LOC("text.prize_wheel_positions").c_str());
                    {
                        ImGui::Spacing();
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_red_fireworks").c_str(), &Configuration::PrizeWheelSlots[0], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_purple_decor").c_str(), &Configuration::PrizeWheelSlots[1], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_blue_ingredients").c_str(), &Configuration::PrizeWheelSlots[2], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_green_gold").c_str(), &Configuration::PrizeWheelSlots[3], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_red_fireworks2").c_str(), &Configuration::PrizeWheelSlots[4], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_brown_coins").c_str(), &Configuration::PrizeWheelSlots[5], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_blue_ingredients2").c_str(), &Configuration::PrizeWheelSlots[6], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_green_gold2").c_str(), &Configuration::PrizeWheelSlots[7], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        IMGUI_CHECKBOX(LOC("text.prize_wheel_yellow_plushie").c_str(), &Configuration::PrizeWheelSlots[8], ImGui::CheckboxHotkeyFlags::HOTKEY)
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();
                    ImGui::Spacing();
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
    }
}
