#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_TreeSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.trees").c_str())) {
            if (ImGui::Button(LOC("button.bush").c_str())) {
                bool newState = !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Bush)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)];
                HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Bush)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)] = newState;
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.sapwood").c_str())) {
                for (int i=0; i < static_cast<int>(FEntryLumber::VariantEnum::MAX); i++) {
                    HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][i] =
                        !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][i];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.heartwood").c_str())) {
                for (int i=0; i < static_cast<int>(FEntryLumber::VariantEnum::MAX); i++) {
                    HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][i] =
                        !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][i];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.flow").c_str())) {
                for (int i=0; i < static_cast<int>(FEntryLumber::VariantEnum::MAX); i++) {
                    HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][i] =
                        !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][i];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.ancient").c_str())) {
                for (int i=0; i < static_cast<int>(FEntryLumber::VariantEnum::MAX); i++) {
                    HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][i] =
                        !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][i];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.infected_trees").c_str())) {
                for (int i=0; i < static_cast<int>(FEntryLumber::VariantEnum::MAX); i++) {
                    HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][i] =
                        !HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][i];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Trees", 6);
            {
                // Create local strings for table column headers and headers
                std::string nameText = LOC("text.name");
                std::string saplingText = LOC("text.sapling");
                std::string smallText = LOC("text.small");
                std::string mediumText = LOC("text.medium");
                std::string largeText = LOC("text.large");
                std::string colorText = LOC("text.color");
                
                ImGui::TableSetupColumn(nameText.c_str(), ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(saplingText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(smallText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(mediumText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(largeText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(colorText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);

                IMGUI_ADD_HEADERS("", saplingText.c_str(), smallText.c_str(), mediumText.c_str(), largeText.c_str(), colorText.c_str())

                    // Bush
                    IMGUI_ADD_ROW(
                        LOC("button.bush").c_str(),
                        IMGUI_CHECKBOX("##BushSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Bush)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)]),
                        IMGUI_TABLENEXTCOLUMN() // these are to separate the ColorPicker 3 more columns.
                        IMGUI_TABLENEXTCOLUMN()
                        IMGUI_TABLENEXTCOLUMN()
                        IMGUI_COLORPICKER("##Bush", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Bush)->second)
                    )
                    // Sapwood
                    IMGUI_ADD_ROW(
                        LOC("button.sapwood").c_str(),
                        IMGUI_CHECKBOX("##SapwoodSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)], true)
                        IMGUI_CHECKBOX("##SapwoodSm", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][static_cast<int>(FEntryLumber::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##SapwoodMed", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][static_cast<int>(FEntryLumber::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##SapwoodLg", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Sapwood)][static_cast<int>(FEntryLumber::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Sapwood", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Sapwood)->second)
                    )
                    // Heartwood
                    IMGUI_ADD_ROW(
                        LOC("button.heartwood").c_str(),
                        IMGUI_CHECKBOX("##HeartwoodSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)], true)
                        IMGUI_CHECKBOX("##HeartwoodSm", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][static_cast<int>(FEntryLumber::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##HeartwoodMed", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][static_cast<int>(FEntryLumber::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##HeartwoodLg", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Heartwood)][static_cast<int>(FEntryLumber::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Heartwood", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Heartwood)->second)
                    )
                    // Flow-Infused
                    IMGUI_ADD_ROW(
                        LOC("text.flow_infused").c_str(),
                        IMGUI_CHECKBOX("##FlowSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)], true)
                        IMGUI_CHECKBOX("##FlowSm", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][static_cast<int>(FEntryLumber::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##FlowMed", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][static_cast<int>(FEntryLumber::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##FlowLg", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Flow)][static_cast<int>(FEntryLumber::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Flow", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Flow)->second)
                    )
                    // Ancient Wood
                    IMGUI_ADD_ROW(
                        LOC("button.ancient").c_str(),
                        IMGUI_CHECKBOX("##AncientSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)], true)
                        IMGUI_CHECKBOX("##AncientSm", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][static_cast<int>(FEntryLumber::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##AncientMed", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][static_cast<int>(FEntryLumber::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##AncientLg", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Ancientwood)][static_cast<int>(FEntryLumber::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Ancient", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Ancientwood)->second)
                    )
                    // Infected Wood
                    IMGUI_ADD_ROW(
                        LOC("button.infected_trees").c_str(),
                        IMGUI_CHECKBOX("##InfectedSap", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][static_cast<int>(FEntryLumber::VariantEnum::Sapling)], true)
                        IMGUI_CHECKBOX("##InfectedSm", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][static_cast<int>(FEntryLumber::VariantEnum::Small)], true)
                        IMGUI_CHECKBOX("##InfectedMed", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][static_cast<int>(FEntryLumber::VariantEnum::Medium)], true)
                        IMGUI_CHECKBOX("##InfectedLg", &HUDDetours::Trees[static_cast<int>(FEntryLumber::TypeEnum::Infected)][static_cast<int>(FEntryLumber::VariantEnum::Large)]),
                        IMGUI_COLORPICKER("##Infected", &Configuration::TreeColors.find(FEntryLumber::TypeEnum::Infected)->second)
                    )
            }
            ImGui::EndTable();
        }
    }
}