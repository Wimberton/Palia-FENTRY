#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_ForageableSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.forageables").c_str())) {
            if (ImGui::Button(LOC("button.common_forage").c_str())) {
                for (int pos : HUDDetours::ForageableCommon) {
                    HUDDetours::Forageables[pos][1] = HUDDetours::Forageables[pos][0] = !HUDDetours::Forageables[pos][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.uncommon_forage").c_str())) {
                for (int pos : HUDDetours::ForageableUncommon) {
                    HUDDetours::Forageables[pos][1] = HUDDetours::Forageables[pos][0] = !HUDDetours::Forageables[pos][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.rare_forage").c_str())) {
                for (int pos : HUDDetours::ForageableRare) {
                    HUDDetours::Forageables[pos][1] = HUDDetours::Forageables[pos][0] = !HUDDetours::Forageables[pos][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.epic_forage").c_str())) {
                for (int pos : HUDDetours::ForageableEpic) {
                    HUDDetours::Forageables[pos][1] = HUDDetours::Forageables[pos][0] = !HUDDetours::Forageables[pos][0];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.star_forage").c_str())) {
                for (auto& Forageable : HUDDetours::Forageables) {
                    Forageable[1] = !Forageable[1];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }
            ImGui::SameLine();
            if (ImGui::Button(LOC("button.infected_forage").c_str())) {
                for (auto& Forageable : HUDDetours::Forageables) {
                    Forageable[2] = !Forageable[2];
                }
                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Forageables", 5);
            {
                // Create local strings for table column headers and headers
                std::string name = LOC("text.name");
                std::string normal = LOC("text.normal");
                std::string star = LOC("text.star");
                std::string infected = LOC("text.infected");
                std::string color = LOC("text.color");
                std::string kilimaForageables = LOC("text.kilima_forageables");
                std::string kilimaBahariForageables = LOC("text.kilima_bahari_forageables");
                std::string bahariForageables = LOC("text.bahari_forageables");
                std::string elderwoodForageables = LOC("text.elderwood_forageables");
                
                ImGui::TableSetupColumn(name.c_str(), ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(normal.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(star.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(infected.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(color.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);

                // + Kilima
                IMGUI_ADD_HEADERS(kilimaForageables.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Crystal Lake Lotus
                IMGUI_ADD_ROW(
                    LOC("text.crystal_lake_lotus").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##WaterFlower", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::WaterFlower)][0], true)
                    IMGUI_CHECKBOX("##WaterFlowerC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::WaterFlower)][1]),
                    IMGUI_COLORPICKER("##WaterFlower", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::WaterFlower)->second)
                )
                // Emerald Carpet Moss
                IMGUI_ADD_ROW(
                    LOC("text.emerald_carpet_moss").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##EmeraldCarpet", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::EmeraldCarpet)][0], true)
                    IMGUI_CHECKBOX("##EmeraldCarpetC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::EmeraldCarpet)][1]),
                    IMGUI_COLORPICKER("##EmeraldCarpet", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::EmeraldCarpet)->second)
                )
                // Spice Sprouts
                IMGUI_ADD_ROW(
                    LOC("text.spice_sprouts").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##SpicedSprouts", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::SpicedSprouts)][0], true)
                    IMGUI_CHECKBOX("##SpicedSproutsC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::SpicedSprouts)][1]),
                    IMGUI_COLORPICKER("##SpicedSprouts", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::SpicedSprouts)->second)
                )
                // Wild Ginger
                IMGUI_ADD_ROW(
                    LOC("text.wild_ginger").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Ginger", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Ginger)][0], true)
                    IMGUI_CHECKBOX("##GingerC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Ginger)][1]),
                    IMGUI_COLORPICKER("##Ginger", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Ginger)->second)
                )
                // Wild Green Onion
                IMGUI_ADD_ROW(
                    LOC("text.wild_green_onion").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##GreenOnion", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::GreenOnion)][0], true)
                    IMGUI_CHECKBOX("##GreenOnionC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::GreenOnion)][1]),
                    IMGUI_COLORPICKER("##GreenOnion", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::GreenOnion)->second)
                )

                // Multiple
                IMGUI_ADD_HEADERS(kilimaBahariForageables.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Mountain Morel
                IMGUI_ADD_ROW(
                    LOC("text.mountain_morel").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##MushroomRed", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MushroomRed)][0], true)
                    IMGUI_CHECKBOX("##MushroomRedC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MushroomRed)][1]),
                    IMGUI_COLORPICKER("##MushroomRed", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::MushroomRed)->second)
                )
                // Sundrop Lily
                IMGUI_ADD_ROW(
                    LOC("text.sundrop_lily").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Sundrop", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Sundrop)][0], true)
                    IMGUI_CHECKBOX("##SundropC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Sundrop)][1]),
                    IMGUI_COLORPICKER("##Sundrop", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Sundrop)->second)
                )
                // Wild Garlic
                IMGUI_ADD_ROW(
                    LOC("text.wild_garlic").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Garlic", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Garlic)][0], true)
                    IMGUI_CHECKBOX("##GarlicC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Garlic)][1]),
                    IMGUI_COLORPICKER("##Garlic", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Garlic)->second)
                )

                // + Bahari
                IMGUI_ADD_HEADERS(bahariForageables.c_str(), "", normal.c_str(), star.c_str(), color.c_str())
                // Briar Daisy
                IMGUI_ADD_ROW(
                    LOC("text.briar_daisy").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##PoisonFlower", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::PoisonFlower)][0], true)
                    IMGUI_CHECKBOX("##PoisonFlowerC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::PoisonFlower)][1]),
                    IMGUI_COLORPICKER("##PoisonFlower", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::PoisonFlower)->second)
                )
                // Brightshroom
                IMGUI_ADD_ROW(
                    LOC("text.brightshroom").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##MushroomBlue", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MushroomBlue)][0], true)
                    IMGUI_CHECKBOX("##MushroomBlueC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::MushroomBlue)][1]),
                    IMGUI_COLORPICKER("##MushroomBlue", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::MushroomBlue)->second)
                )
                // Coral
                IMGUI_ADD_ROW(
                    LOC("text.coral").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Coral", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Coral)][0], true),
                    IMGUI_COLORPICKER("##CoralColor", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Coral)->second)
                )
                // Dari Cloves
                IMGUI_ADD_ROW(
                    LOC("text.dari_cloves").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##DariCloves", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::DariCloves)][0], true)
                    IMGUI_CHECKBOX("##DariClovesC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::DariCloves)][1]),
                    IMGUI_COLORPICKER("##DariCloves", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::DariCloves)->second)
                )
                // Dragon's Beard Peat
                IMGUI_ADD_ROW(
                    LOC("text.dragons_beard_peat").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##DragonsBeard", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::DragonsBeard)][0], true)
                    IMGUI_CHECKBOX("##DragonsBeardC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::DragonsBeard)][1]),
                    IMGUI_COLORPICKER("##DragonsBeard", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::DragonsBeard)->second)
                )
                // Heartdrop Lily
                IMGUI_ADD_ROW(
                    LOC("text.heartdrop_lily").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Heartdrop", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Heartdrop)][0], true)
                    IMGUI_CHECKBOX("##HeartdropC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Heartdrop)][1]),
                    IMGUI_COLORPICKER("##Heartdrop", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Heartdrop)->second)
                )
                // Heat Root
                IMGUI_ADD_ROW(
                    LOC("text.heat_root").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##HeatRoot", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::HeatRoot)][0], true)
                    IMGUI_CHECKBOX("##HeatRootC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::HeatRoot)][1]),
                    IMGUI_COLORPICKER("##HeatRoot", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::HeatRoot)->second)
                )
                // Shell
                IMGUI_ADD_ROW(
                    LOC("text.shell").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Shell", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Shell)][0], true),
                    IMGUI_COLORPICKER("##ShellColor", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Shell)->second)
                )
                // Sweet Leaf
                IMGUI_ADD_ROW(
                    LOC("text.sweet_leaf").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##SweetLeaves", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::SweetLeaves)][0], true)
                    IMGUI_CHECKBOX("##SweetLeavesC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::SweetLeaves)][1]),
                    IMGUI_COLORPICKER("##SweetLeaves", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::SweetLeaves)->second)
                )
                // Oyster
                IMGUI_ADD_ROW(
                    LOC("text.oyster").c_str(),
                    IMGUI_TABLENEXTCOLUMN()
                    IMGUI_CHECKBOX("##Oyster", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Oyster)][0], true),
                    IMGUI_COLORPICKER("##OysterColor", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Oyster)->second)
                )

                // + Elderwood
                IMGUI_ADD_HEADERS(elderwoodForageables.c_str(), normal.c_str(), star.c_str(), infected.c_str(), color.c_str())
                // Batterfly Beans
                IMGUI_ADD_ROW(
                    LOC("text.batterfly_beans").c_str(),
                    IMGUI_CHECKBOX("##BatterflyBeans", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::BatterflyBeans)][0], true)
                    IMGUI_CHECKBOX("##BatterflyBeansC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::BatterflyBeans)][1], true)
                    IMGUI_CHECKBOX("##BatterflyBeansI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::BatterflyBeans)][2]),
                    IMGUI_COLORPICKER("##BatterflyBeans", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::BatterflyBeans)->second)
                )
                // ElderClam Mushroom
                IMGUI_ADD_ROW(
                    LOC("text.elder_clam_mushroom").c_str(),
                    IMGUI_CHECKBOX("##ElderClamMushroom", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderClamMushroom)][0], true)
                    IMGUI_CHECKBOX("##ElderClamMushroomC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderClamMushroom)][1], true)
                    IMGUI_CHECKBOX("##ElderClamMushroomI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderClamMushroom)][2]),
                    IMGUI_COLORPICKER("##ElderClamMushroom", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::ElderClamMushroom)->second)
                )
                // Elderflower
                IMGUI_ADD_ROW(
                    LOC("text.elderflower").c_str(),
                    IMGUI_CHECKBOX("##Elderflower", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Elderflower)][0], true)
                    IMGUI_CHECKBOX("##ElderflowerC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Elderflower)][1], true)
                    IMGUI_CHECKBOX("##ElderflowerI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Elderflower)][2]),
                    IMGUI_COLORPICKER("##Elderflower", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Elderflower)->second)
                )
                // Elderwood Lotus
                IMGUI_ADD_ROW(
                    LOC("text.elderwood_lotus").c_str(),
                    IMGUI_CHECKBOX("##ElderwoodLotus", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodLotus)][0], true)
                    IMGUI_CHECKBOX("##ElderwoodLotusC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodLotus)][1], true)
                    IMGUI_CHECKBOX("##ElderwoodLotusI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodLotus)][2]),
                    IMGUI_COLORPICKER("##ElderwoodLotus", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::ElderwoodLotus)->second)
                )
                // Elderwood Orchid
                IMGUI_ADD_ROW(
                    LOC("text.elderwood_orchid").c_str(),
                    IMGUI_CHECKBOX("##ElderwoodOrchid", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodOrchid)][0], true)
                    IMGUI_CHECKBOX("##ElderwoodOrchidC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodOrchid)][1], true)
                    IMGUI_CHECKBOX("##ElderwoodOrchidI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::ElderwoodOrchid)][2]),
                    IMGUI_COLORPICKER("##ElderwoodOrchid", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::ElderwoodOrchid)->second)
                )
                // Floatfish Mushroom
                IMGUI_ADD_ROW(
                    LOC("text.floatfish_mushroom").c_str(),
                    IMGUI_CHECKBOX("##FloatfishMushroom", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FloatfishMushroom)][0], true)
                    IMGUI_CHECKBOX("##FloatfishMushroomC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FloatfishMushroom)][1], true)
                    IMGUI_CHECKBOX("##FloatfishMushroomI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FloatfishMushroom)][2]),
                    IMGUI_COLORPICKER("##FloatfishMushroom", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::FloatfishMushroom)->second)
                )
                // Flowtato
                IMGUI_ADD_ROW(
                    LOC("text.flowtato").c_str(),
                    IMGUI_CHECKBOX("##Flowtato", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FlowTato)][0], true)
                    IMGUI_CHECKBOX("##FlowtatoC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FlowTato)][1], true)
                    IMGUI_CHECKBOX("##FlowtatoI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::FlowTato)][2]),
                    IMGUI_COLORPICKER("##Flowtato", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::FlowTato)->second)
                )
                // Honey
                IMGUI_ADD_ROW(
                    LOC("text.honey").c_str(),
                    IMGUI_CHECKBOX("##Honey", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Honey)][0], true)
                    IMGUI_CHECKBOX("##HoneyC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Honey)][1], true)
                    IMGUI_CHECKBOX("##HoneyI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::Honey)][2]),
                    IMGUI_COLORPICKER("##HoneyColor", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::Honey)->second)
                )
                // Infected Essence
                IMGUI_ADD_ROW(
                    LOC("text.infected_essence").c_str(),
                    IMGUI_CHECKBOX("##InfectedEssence", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::EchoEssence)][0], true)
                    IMGUI_TABLENEXTCOLUMN(),
                    IMGUI_COLORPICKER("##InfectedEssenceColor", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::EchoEssence)->second)
                )
                // Kopaa Nut
                IMGUI_ADD_ROW(
                    LOC("text.kopaa_nut").c_str(),
                    IMGUI_CHECKBOX("##KopaaNut", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::KopaaNut)][0], true)
                    IMGUI_CHECKBOX("##KopaaNutC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::KopaaNut)][1], true)
                    IMGUI_CHECKBOX("##KopaaNutI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::KopaaNut)][2]),
                    IMGUI_COLORPICKER("##KopaaNut", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::KopaaNut)->second)
                )
                // Piksii Berries
                IMGUI_ADD_ROW(
                    LOC("text.piksii_berries").c_str(),
                    IMGUI_CHECKBOX("##PiksiiBerries", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::PiksiiBerries)][0], true)
                    IMGUI_CHECKBOX("##PiksiiBerriesC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::PiksiiBerries)][1], true)
                    IMGUI_CHECKBOX("##PiksiiBerriesI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::PiksiiBerries)][2]),
                    IMGUI_COLORPICKER("##PiksiiBerries", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::PiksiiBerries)->second)
                )
                // Staircase Mushroom
                IMGUI_ADD_ROW(
                    LOC("text.staircase_mushroom").c_str(),
                    IMGUI_CHECKBOX("##StaircaseMushroom", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::StaircaseMushroom)][0], true)
                    IMGUI_CHECKBOX("##StaircaseMushroomC", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::StaircaseMushroom)][1], true)
                    IMGUI_CHECKBOX("##StaircaseMushroomI", &HUDDetours::Forageables[static_cast<int>(FEntryGatherable::TypeEnum::StaircaseMushroom)][2]),
                    IMGUI_COLORPICKER("##StaircaseMushroom", &Configuration::ForageableColors.find(FEntryGatherable::TypeEnum::StaircaseMushroom)->second)
                )
            }
            ImGui::EndTable();
        }
    }
}
