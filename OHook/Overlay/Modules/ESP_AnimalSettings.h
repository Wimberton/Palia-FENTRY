#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_AnimalSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.animals").c_str())) {
            if (ImGui::Button(LOC("button.sernuk").c_str())) {
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)];
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.chapaa").c_str())) {
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chase)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chase)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.muujin").c_str())) {
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)];
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.ogopuu").c_str())) {
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)];
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.shmole").c_str())) {
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)];
                HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)] = !HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)];
                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Animals", 3);
            {
                // Create local strings for table column headers and headers
                std::string showText = LOC("text.show");
                std::string colorText = LOC("text.color");
                
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(showText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(colorText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);

                // SERNUKS
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.sernuk").c_str(),
                    IMGUI_CHECKBOX("##Sernuk", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##SernukColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.elder_sernuk").c_str(),
                    IMGUI_CHECKBOX("##ElderSernuk", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##ElderSernukColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.proudhorn_sernuk").c_str(),
                    IMGUI_CHECKBOX("##ProudhornSernuk", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Cearnuk)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##ProudhornSernukColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Cearnuk, FEntryHunting::VariantEnum::Tier3})->second)
                )

                // CHAPAAS
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.chapaa").c_str(),
                    IMGUI_CHECKBOX("##Chapaa", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##ChapaaColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.striped_chapaa").c_str(),
                    IMGUI_CHECKBOX("##StripedChapaa", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##StripedChapaaColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.azure_chapaa").c_str(),
                    IMGUI_CHECKBOX("##AzureChapaa", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chapaa)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##AzureChapaaColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Chapaa, FEntryHunting::VariantEnum::Tier3})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.minigame_chapaa").c_str(),
                    IMGUI_CHECKBOX("##MinigameChapaa", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Chase)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##MinigameChapaaColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Chase, FEntryHunting::VariantEnum::Tier1})->second)
                )

                // MUUJINS
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.muujin").c_str(),
                    IMGUI_CHECKBOX("##Muujin", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##MuujinColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.banded_muujin").c_str(),
                    IMGUI_CHECKBOX("##BandedMuujin", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##BandedMuujinColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.bluebristle_muujin").c_str(),
                    IMGUI_CHECKBOX("##BluebristleMuujin", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::TreeClimber)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##BluebristleMuujinColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::TreeClimber, FEntryHunting::VariantEnum::Tier3})->second)
                )

                // OGOPUU
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.ogopuu").c_str(),
                    IMGUI_CHECKBOX("##Ogopuu", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##OgopuuColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.emerald_ogopuu").c_str(),
                    IMGUI_CHECKBOX("##EmeraldOgopuu", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##EmeraldOgopuuColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.waveback_ogopuu").c_str(),
                    IMGUI_CHECKBOX("##WavebackOgopuu", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Ogopuu)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##WavebackOgopuuColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Ogopuu, FEntryHunting::VariantEnum::Tier3})->second)
                )

                // SHMOLE
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.shmole").c_str(),
                    IMGUI_CHECKBOX("##Shmole", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##ShmoleColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.elder_shmole").c_str(),
                    IMGUI_CHECKBOX("##ElderShmole", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##ElderShmoleColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.piksii_shmole").c_str(),
                    IMGUI_CHECKBOX("##PiksiiShmole", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Shmole)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##PiksiiShmoleColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Shmole, FEntryHunting::VariantEnum::Tier3})->second)
                )

                // BALLOONS
                IMGUI_ADD_HEADERS("", showText.c_str(), colorText.c_str())
                IMGUI_ADD_ROW(
                    LOC("text.chapaa_balloon").c_str(),
                    IMGUI_CHECKBOX("##ChapaaBalloon", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Balloon)][static_cast<int>(FEntryHunting::VariantEnum::Tier1)]),
                    IMGUI_COLORPICKER("##ChapaaBalloonColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier1})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.stripped_chapaa_balloon").c_str(),
                    IMGUI_CHECKBOX("##StrippedChapaaBalloon", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Balloon)][static_cast<int>(FEntryHunting::VariantEnum::Tier2)]),
                    IMGUI_COLORPICKER("##StrippedChapaaBalloonColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier2})->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.azure_chapaa_balloon").c_str(),
                    IMGUI_CHECKBOX("##AzureChapaaBalloon", &HUDDetours::Animals[static_cast<int>(FEntryHunting::TypeEnum::Balloon)][static_cast<int>(FEntryHunting::VariantEnum::Tier3)]),
                    IMGUI_COLORPICKER("##AzureChapaaBalloonColor", &Configuration::AnimalColors.find(FCreatureType{FEntryHunting::TypeEnum::Balloon, FEntryHunting::VariantEnum::Tier3})->second)
                )
            }
            ImGui::EndTable();
        }
    }
}
