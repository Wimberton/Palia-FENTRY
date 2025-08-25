#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_BugSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.bugs").c_str())) {
            if (ImGui::Button(LOC("button.common_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Common)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Common)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Common)][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.uncommon_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0];
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.rare_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Rare)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Rare)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Rare)][0];
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Rare2)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Rare2)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Rare2)][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.epic_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    Bug[static_cast<int>(FEntryBug::VariantEnum::Epic)][1] = Bug[static_cast<int>(FEntryBug::VariantEnum::Epic)][0] = !Bug[static_cast<int>(FEntryBug::VariantEnum::Epic)][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.star_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    for (auto& j : Bug) {
                        j[1] = !j[1];
                    }
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.infected_bugs").c_str())) {
                for (auto& Bug : HUDDetours::Bugs) {
                    for (auto& j : Bug) {
                        j[2] = !j[2];
                    }
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Bugs", 5);
            {
                // Create local strings for table column headers and headers
                std::string name = LOC("text.name");
                std::string normal = LOC("text.normal");
                std::string star = LOC("text.star");
                std::string infected = LOC("text.infected");
                std::string color = LOC("text.color");
                std::string kilimaBugs = LOC("text.kilima_bugs");
                std::string kilimaBahariBugs = LOC("text.kilima_bahari_bugs");
                std::string bahariBugs = LOC("text.bahari_bugs");
                std::string elderwoodBugs = LOC("text.elderwood_bugs");
                
                ImGui::TableSetupColumn(name.c_str(), ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(normal.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(star.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(infected.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(color.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);

                // + Kilima
                IMGUI_ADD_HEADERS(kilimaBugs.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Duskwing Butterfly
                IMGUI_ADD_ROW(
                    LOC("text.duskwing_butterfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Duskwing", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##DuskwingC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##Duskwing", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Firebreathing Dragonfly
                IMGUI_ADD_ROW(
                    LOC("text.firebreathing_dragonfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Firebreathing", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##FirebreathingC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##Firebreathing", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Rare})->second)
                )
                // Garden Leafhopper
                IMGUI_ADD_ROW(
                    LOC("text.garden_leafhopper").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Leafhopper", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##LeafhopperC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##Leafhopper", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Garden Mantis U
                IMGUI_ADD_ROW(
                    LOC("text.garden_mantis").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GardenMantis", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##GardenMantisC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##GardenMantis", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Garden Millipede
                IMGUI_ADD_ROW(
                    LOC("text.garden_millipede").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GardenMillipede", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##GardenMillipedeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##GardenMillipede", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Golden Glory Bee
                IMGUI_ADD_ROW(
                    LOC("text.golden_glory_bee").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GoldenGloryBee", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Bee)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##GoldenGloryBeeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Bee)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##GoldenGloryBee", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Bee, FEntryBug::VariantEnum::Rare})->second)
                )
                // Gossamer Veil Moth
                IMGUI_ADD_ROW(
                    LOC("text.gossamer_veil_moth").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GossamerVeilMoth", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##GossamerVeilMothC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##GossamerVeilMoth", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Rare})->second)
                )
                // Princess Ladybug 
                IMGUI_ADD_ROW(
                    LOC("text.princess_ladybug").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##PrincessLadybug", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Ladybug)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##PrincessLadybugC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Ladybug)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##PrincessLadybug", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Ladybug, FEntryBug::VariantEnum::Rare})->second)
                )
                // Proudhorned Stag Beetle
                IMGUI_ADD_ROW(
                    LOC("text.proudhorned_stag_beetle").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##ProudhornedStag", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##ProudhornedStagC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##ProudhornedStag", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Raspberry Beetle
                IMGUI_ADD_ROW(
                    LOC("text.raspberry_beetle").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Raspberry", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##RaspberryC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##Raspberry", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Rare})->second)
                )


                // + Kilima & Bahari
                IMGUI_ADD_HEADERS(kilimaBahariBugs.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Brushtail Dragonfly
                IMGUI_ADD_ROW(
                    LOC("text.brushtail_dragonfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Brushtail", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##BrushtailC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##Brushtail", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Common})->second)
                )
                // Common Blue Butterfly
                IMGUI_ADD_ROW(
                    LOC("text.common_blue_butterfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##CommonBlue", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##CommonBlueC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##CommonBlue", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Common})->second)
                )
                // Common Field Cricket
                IMGUI_ADD_ROW(
                    LOC("text.common_field_cricket").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##CommonField", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##CommonFieldC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##CommonField", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Common})->second)
                )
                // Kilima Night Moth
                IMGUI_ADD_ROW(
                    LOC("text.kilima_night_moth").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##KilimaNightMoth", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##KilimaNightMothC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##KilimaNightMoth", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Common})->second)
                )
                // Spotted Stink Bug
                IMGUI_ADD_ROW(
                    LOC("text.spotted_stink_bug").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##SpottedStinkBug", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##SpottedStinkBugC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##SpottedStinkBug", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Common})->second)
                )
                // Spotted Mantis R
                IMGUI_ADD_ROW(
                    LOC("text.spotted_mantis").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##SpottedMantis", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##SpottedMantisC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##SpottedMantis", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Rare})->second)
                )


                // + Bahari
                IMGUI_ADD_HEADERS(bahariBugs.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Ancient Amber Beetle
                IMGUI_ADD_ROW(
                    LOC("text.ancient_amber_beetle").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##AncientAmber", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Epic)][0], true)
                    IMGUI_CHECKBOX("##AncientAmberC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Beetle)][static_cast<int>(FEntryBug::VariantEnum::Epic)][1]),
                    IMGUI_COLORPICKER("##AncientAmber", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Beetle, FEntryBug::VariantEnum::Epic})->second)
                )
                // Azure Stonehopper
                IMGUI_ADD_ROW(
                    LOC("text.azure_stonehopper").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Stonehopper", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##StonehopperC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cricket)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##Stonehopper", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cricket, FEntryBug::VariantEnum::Rare})->second)
                )
                // Bahari Bee
                IMGUI_ADD_ROW(
                    LOC("text.bahari_bee").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##BahariBee", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Bee)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##BahariBeeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Bee)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##BahariBee", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Bee, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Bahari Crab
                IMGUI_ADD_ROW(
                    LOC("text.bahari_crab").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##BahariCrab", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##BahariCrabC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##BahariCrab", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Common})->second)
                )
                // Bahari Glowbug
                IMGUI_ADD_ROW(
                    LOC("text.bahari_glowbug").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##BahariGlowbug", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Glowbug)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##BahariGlowbugC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Glowbug)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##BahariGlowbug", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Glowbug, FEntryBug::VariantEnum::Rare})->second)
                )
                // Brighteye Butterfly
                IMGUI_ADD_ROW(
                    LOC("text.brighteye_butterfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Brighteye", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##BrighteyeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##Brighteye", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Rare})->second)
                )
                // Cerulean Cicada
                IMGUI_ADD_ROW(
                    LOC("text.cerulean_cicada").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Cerulean", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##CeruleanC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##Cerulean", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Common Bark Cicada
                IMGUI_ADD_ROW(
                    LOC("text.common_bark_cicada").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##CommonBark", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##CommonBarkC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##CommonBark", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Common})->second)
                )
                // Fairy Mantis E
                IMGUI_ADD_ROW(
                    LOC("text.fairy_mantis").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##FairyMantis", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Epic)][0], true)
                    IMGUI_CHECKBOX("##FairyMantisC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Epic)][1]),
                    IMGUI_COLORPICKER("##FairyMantis", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Epic})->second)
                )
                // Garden Ladybug
                IMGUI_ADD_ROW(
                    LOC("text.garden_ladybug").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GardenLadybug", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Ladybug)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##GardenLadybugC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Ladybug)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##GardenLadybug", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Ladybug, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Garden Snail U
                IMGUI_ADD_ROW(
                    LOC("text.garden_snail").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GardenSnail", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Snail)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##GardenSnailC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Snail)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##GardenSnail", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Snail, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Hairy Millipede
                IMGUI_ADD_ROW(
                    LOC("text.hairy_millipede").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##HairyMillipede", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##HairyMillipedeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##HairyMillipede", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Rare})->second)
                )
                // Inky Dragonfly
                IMGUI_ADD_ROW(
                    LOC("text.inky_dragonfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Inky", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##InkyC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##Inky", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Jewelwing Dragonfly
                IMGUI_ADD_ROW(
                    LOC("text.jewelwing_dragonfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Jewelwing", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Epic)][0], true)
                    IMGUI_CHECKBOX("##JewelwingC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Dragonfly)][static_cast<int>(FEntryBug::VariantEnum::Epic)][1]),
                    IMGUI_COLORPICKER("##Jewelwing", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Dragonfly, FEntryBug::VariantEnum::Epic})->second)
                )
                // Leafstalker Mantis R2
                IMGUI_ADD_ROW(
                    LOC("text.leafstalker_mantis").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##LeafstalkerMantis", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Rare2)][0], true)
                    IMGUI_CHECKBOX("##LeafstalkerMantisC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Mantis)][static_cast<int>(FEntryBug::VariantEnum::Rare2)][1]),
                    IMGUI_COLORPICKER("##LeafstalkerMantis", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Mantis, FEntryBug::VariantEnum::Rare2})->second)
                )
                // Lunar Fairy Moth
                IMGUI_ADD_ROW(
                    LOC("text.lunar_fairy_moth").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##LunarFairyMoth", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##LunarFairyMothC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Moth)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##LunarFairyMoth", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Moth, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Paper Lantern Bug
                IMGUI_ADD_ROW(
                    LOC("text.paper_lantern_bug").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##PaperLantern", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Glowbug)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##PaperLanternC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Glowbug)][static_cast<int>(FEntryBug::VariantEnum::Common)][1]),
                    IMGUI_COLORPICKER("##PaperLantern", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Glowbug, FEntryBug::VariantEnum::Common})->second)
                )
                // Rainbow-Tipped Butterfly
                IMGUI_ADD_ROW(
                    LOC("text.rainbow_tipped_butterfly").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Rainbow", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Epic)][0], true)
                    IMGUI_CHECKBOX("##RainbowC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Butterfly)][static_cast<int>(FEntryBug::VariantEnum::Epic)][1]),
                    IMGUI_COLORPICKER("##Rainbow", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Butterfly, FEntryBug::VariantEnum::Epic})->second)
                )
                // Scintillating Centipede
                IMGUI_ADD_ROW(
                    LOC("text.scintillating_centipede").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##ScintillatingCentipede", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Rare2)][0], true)
                    IMGUI_CHECKBOX("##ScintillatingCentipedeC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Pede)][static_cast<int>(FEntryBug::VariantEnum::Rare2)][1]),
                    IMGUI_COLORPICKER("##ScintillatingCentipede", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Pede, FEntryBug::VariantEnum::Rare2})->second)
                )
                // Spineshell Crab
                IMGUI_ADD_ROW(
                    LOC("text.spineshell_crab").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##SpineshellCrab", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##SpineshellCrabC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1]),
                    IMGUI_COLORPICKER("##SpineshellCrab", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Uncommon})->second)
                )
                // Spitfire Cicada
                IMGUI_ADD_ROW(
                    LOC("text.spitfire_cicada").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Spitfire", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##SpitfireC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Cicada)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##Spitfire", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Cicada, FEntryBug::VariantEnum::Rare})->second)
                )
                // Stripeshell Snail R
                IMGUI_ADD_ROW(
                    LOC("text.stripeshell_snail").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##StripeshellSnail", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Snail)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##StripeshellSnailC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Snail)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##StripeshellSnail", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Snail, FEntryBug::VariantEnum::Rare})->second)
                )
                // Vampire Crab
                IMGUI_ADD_ROW(
                    LOC("text.vampire_crab").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##VampireCrab", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##VampireCrabC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Crab)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1]),
                    IMGUI_COLORPICKER("##VampireCrab", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Crab, FEntryBug::VariantEnum::Rare})->second)
                )


                // + Elderwood
                IMGUI_ADD_HEADERS(elderwoodBugs.c_str(), normal.c_str(), star.c_str(), infected.c_str(), color.c_str())
                // Blood Beetle
                IMGUI_ADD_ROW(
                    LOC("text.blood_beetle").c_str(),
                    IMGUI_CHECKBOX("##BloodBeetle", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##BloodBeetleC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1], true)
                    IMGUI_CHECKBOX("##BloodBeetleI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Rare)][2]),
                    IMGUI_COLORPICKER("##BloodBeetle", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::BeetleAZ2, FEntryBug::VariantEnum::Rare })->second)
                )
                // Blushing Batterfly
                IMGUI_ADD_ROW(
                    LOC("text.blushing_batterfly").c_str(),
                    IMGUI_CHECKBOX("##BlushingBatterfly", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##BlushingBatterflyC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][1], true)
                    IMGUI_CHECKBOX("##BlushingBatterflyI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Common)][2]),
                    IMGUI_COLORPICKER("##BlushingBatterfly", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Common })->second)
                )
                // Cave Piksii
                IMGUI_ADD_ROW(
                    LOC("text.cave_piksii").c_str(),
                    IMGUI_CHECKBOX("##CavePiksii", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##CavePiksiiC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1], true)
                    IMGUI_CHECKBOX("##CavePiksiiI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][2]),
                    IMGUI_COLORPICKER("##CavePiksii", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Piksii, FEntryBug::VariantEnum::Uncommon })->second)
                )
                // Draugr Beetle
                IMGUI_ADD_ROW(
                    LOC("text.draugr_beetle").c_str(),
                    IMGUI_CHECKBOX("##DraugrBeetle", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##DraugrBeetleC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1], true)
                    IMGUI_CHECKBOX("##DraugrBeetleI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::BeetleAZ2)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][2]),
                    IMGUI_COLORPICKER("##DraugrBeetle", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::BeetleAZ2, FEntryBug::VariantEnum::Uncommon })->second)
                )
                // Flame-Horned Rockhopper
                IMGUI_ADD_ROW(
                    LOC("text.flame_horned_rockhopper").c_str(),
                    IMGUI_CHECKBOX("##FlameHornedRockhopper", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Rare)][0], true)
                    IMGUI_CHECKBOX("##FlameHornedRockhopperC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Rare)][1], true)
                    IMGUI_CHECKBOX("##FlameHornedRockhopperI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Rare)][2]),
                    IMGUI_COLORPICKER("##FlameHornedRockhopper", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Rare })->second)
                )
                // Grumpy Granite Rockhopper
                IMGUI_ADD_ROW(
                    LOC("text.grumpy_granite_rockhopper").c_str(),
                    IMGUI_CHECKBOX("##GrumpyGraniteRockhopper", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##GrumpyGraniteRockhopperC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Common)][1], true)
                    IMGUI_CHECKBOX("##GrumpyGraniteRockhopperI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Common)][2]),
                    IMGUI_COLORPICKER("##GrumpyGraniteRockhopper", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Common })->second)
                )
                // Nightshadow Batterfly
                IMGUI_ADD_ROW(
                    LOC("text.nightshadow_batterfly").c_str(),
                    IMGUI_CHECKBOX("##NightshadowBatterfly", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][0], true)
                    IMGUI_CHECKBOX("##NightshadowBatterflyC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][1], true)
                    IMGUI_CHECKBOX("##NightshadowBatterflyI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon2)][2]),
                    IMGUI_COLORPICKER("##NightshadowBatterfly", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Uncommon2 })->second)
                )
                // Dayshadow Batterfly
                IMGUI_ADD_ROW(
                    LOC("text.sunburst_batterfly").c_str(),
                    IMGUI_CHECKBOX("##DayshadowBatterfly", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][0], true)
                    IMGUI_CHECKBOX("##DayshadowBatterflyC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][1], true)
                    IMGUI_CHECKBOX("##DayshadowBatterflyI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Batterfly)][static_cast<int>(FEntryBug::VariantEnum::Uncommon)][2]),
                    IMGUI_COLORPICKER("##DayshadowBatterfly", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Batterfly, FEntryBug::VariantEnum::Uncommon })->second)
                )
                // Veil Piksii
                IMGUI_ADD_ROW(
                    LOC("text.veil_piksii").c_str(),
                    IMGUI_CHECKBOX("##VeilPiksii", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Common)][0], true)
                    IMGUI_CHECKBOX("##VeilPiksiiC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Common)][1], true)
                    IMGUI_CHECKBOX("##VeilPiksiiI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::Piksii)][static_cast<int>(FEntryBug::VariantEnum::Common)][2]),
                    IMGUI_COLORPICKER("##VeilPiksii", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::Piksii, FEntryBug::VariantEnum::Common })->second)
                )
                // Will-o-wisp Rockhopper
                IMGUI_ADD_ROW(
                    LOC("text.will_o_wisp_rockhopper").c_str(),
                    IMGUI_CHECKBOX("##WillowispRockhopper", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Epic)][0], true)
                    IMGUI_CHECKBOX("##WillowispRockhopperC", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Epic)][1], true)
                    IMGUI_CHECKBOX("##WillowispRockhopperI", &HUDDetours::Bugs[static_cast<int>(FEntryBug::TypeEnum::RockHopper)][static_cast<int>(FEntryBug::VariantEnum::Epic)][2]),
                    IMGUI_COLORPICKER("##WillowispRockhopper", &Configuration::BugColors.find(FBugType{FEntryBug::TypeEnum::RockHopper, FEntryBug::VariantEnum::Epic })->second)
                )

            }
            ImGui::EndTable();
        }
    }
}
