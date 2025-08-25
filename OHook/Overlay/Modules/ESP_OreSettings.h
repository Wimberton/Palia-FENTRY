#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_OreSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.ores").c_str())) {
            if (ImGui::Button(LOC("button.clay").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Clay)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Clay)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.stone").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Stone)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Stone)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.whitestone").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Whitestone)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Whitestone)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.copper").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Copper)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Copper)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            if (ImGui::Button(LOC("button.iron").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Iron)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Iron)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.silver").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Silver)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Silver)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.gold").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Gold)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Gold)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.palium").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Palium)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Palium)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.platinum").c_str())) {
                bool newState = !HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Platinum)][static_cast<int>(FEntryMining::VariantEnum::Large)];
                for (int i=0; i < static_cast<int>(FEntryMining::VariantEnum::MAX); i++) {
                    HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Platinum)][i] = newState;
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Ores", 5);
            {
                // Create local strings for table column headers and headers
                std::string nameText = LOC("text.name");
                std::string smallText = LOC("text.small");
                std::string mediumText = LOC("text.medium");
                std::string largeText = LOC("text.large");
                std::string colorText = LOC("text.color");
                
                ImGui::TableSetupColumn(nameText.c_str(), ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(smallText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(mediumText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(largeText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(colorText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);

                IMGUI_ADD_HEADERS("", smallText.c_str(), mediumText.c_str(), largeText.c_str(), colorText.c_str())

                    // CLAY
                    IMGUI_ADD_ROW(
                        LOC("button.clay").c_str(),
                        IMGUI_TABLENEXTCOLUMN()
                        IMGUI_TABLENEXTCOLUMN()
                        IMGUI_CHECKBOX("##ClayLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Clay)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Clay", &Configuration::OreColors.find(FEntryMining::TypeEnum::Clay)->second)
                    )
                    //Stone
                    IMGUI_ADD_ROW(
                        LOC("button.stone").c_str(),
                        IMGUI_CHECKBOX("##StoneSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Stone)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##StoneMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Stone)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##StoneLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Stone)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Stone", &Configuration::OreColors.find(FEntryMining::TypeEnum::Stone)->second)
                    )
                    //Whitestone
                    IMGUI_ADD_ROW(
                        LOC("button.whitestone").c_str(),
                        IMGUI_CHECKBOX("##WhitestoneSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Whitestone)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##WhitestoneMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Whitestone)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##WhitestoneLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Whitestone)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Whitestone", &Configuration::OreColors.find(FEntryMining::TypeEnum::Whitestone)->second)
                    )
                    //Copper
                    IMGUI_ADD_ROW(
                        LOC("button.copper").c_str(),
                        IMGUI_CHECKBOX("##CopperSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Copper)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##CopperMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Copper)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##CopperLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Copper)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Copper", &Configuration::OreColors.find(FEntryMining::TypeEnum::Copper)->second)
                    )
                    //Iron
                    IMGUI_ADD_ROW(
                        LOC("button.iron").c_str(),
                        IMGUI_CHECKBOX("##IronSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Iron)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##IronMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Iron)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##IronLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Iron)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Iron", &Configuration::OreColors.find(FEntryMining::TypeEnum::Iron)->second)
                    )
                    //Silver
                    IMGUI_ADD_ROW(
                        LOC("button.silver").c_str(),
                        IMGUI_CHECKBOX("##SilverSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Silver)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##SilverMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Silver)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##SilverLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Silver)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Silver", &Configuration::OreColors.find(FEntryMining::TypeEnum::Silver)->second)
                    )
                    //Gold
                    IMGUI_ADD_ROW(
                        LOC("button.gold").c_str(),
                        IMGUI_CHECKBOX("##GoldSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Gold)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##GoldMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Gold)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##GoldLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Gold)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Gold", &Configuration::OreColors.find(FEntryMining::TypeEnum::Gold)->second)
                    )
                    //Palium
                    IMGUI_ADD_ROW(
                        LOC("button.palium").c_str(),
                        IMGUI_CHECKBOX("##PaliumSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Palium)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##PaliumMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Palium)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##PaliumLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Palium)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Palium", &Configuration::OreColors.find(FEntryMining::TypeEnum::Palium)->second)
                    )
                    //Platinum
                    IMGUI_ADD_ROW(
                        LOC("button.platinum").c_str(),
                        IMGUI_CHECKBOX("##PlatinumSm", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Platinum)][static_cast<int>(FEntryMining::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##PlatinumMed", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Platinum)][static_cast<int>(FEntryMining::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##PlatinumLg", &HUDDetours::Ores[static_cast<int>(FEntryMining::TypeEnum::Platinum)][static_cast<int>(FEntryMining::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Platinum", &Configuration::OreColors.find(FEntryMining::TypeEnum::Platinum)->second)
                    )
            }
            ImGui::EndTable();
        }
    }
}