#pragma once

#include "Configuration.h"
#include "HUDDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace ESP_SingleSettings {
    inline void Show() {
        if (ImGui::CollapsingHeader(LOC("header.player_entities").c_str())) {
            if (ImGui::Button(LOC("button.toggle_all_misc").c_str())) {
                bool newState = !HUDDetours::Singles[static_cast<int>(EOneOffs::Player)];

                HUDDetours::Singles[static_cast<int>(EOneOffs::Player)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::NPC)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::FishHook)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::FishPool)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Loot)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Quest)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::RummagePiles)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Treasure)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Stables)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::TimedDrop)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Relic)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Others)] = newState;
                HUDDetours::Singles[static_cast<int>(EOneOffs::Decor)] = newState;

                Configuration::Save(ESaveFile::ESPSettings);
            }

            ImGui::BeginTable("Odds", 3);
            {
                // Create local strings for table column headers and headers
                std::string typeText = LOC("text.type");
                std::string showText = LOC("text.show");
                std::string colorText = LOC("text.color");
                
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_None, 0);
                ImGui::TableSetupColumn(showText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                ImGui::TableSetupColumn(colorText.c_str(), ImGuiTableColumnFlags_WidthFixed, 40);
                IMGUI_ADD_HEADERS(typeText.c_str(), showText.c_str(), colorText.c_str())

                IMGUI_ADD_ROW(
                    LOC("text.players").c_str(),
                    IMGUI_CHECKBOX("##Players", &HUDDetours::Singles[static_cast<int>(EOneOffs::Player)]),
                    IMGUI_COLORPICKER("##Players", &Configuration::SingleColors.find(EOneOffs::Player)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.npcs").c_str(),
                    IMGUI_CHECKBOX("##NPC", &HUDDetours::Singles[static_cast<int>(EOneOffs::NPC)]),
                    IMGUI_COLORPICKER("##NPC", &Configuration::SingleColors.find(EOneOffs::NPC)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.fish").c_str(),
                    IMGUI_CHECKBOX("##FishHook", &HUDDetours::Singles[static_cast<int>(EOneOffs::FishHook)]),
                    IMGUI_COLORPICKER("##FishHook", &Configuration::SingleColors.find(EOneOffs::FishHook)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.fish_pools").c_str(),
                    IMGUI_CHECKBOX("##FishPool", &HUDDetours::Singles[static_cast<int>(EOneOffs::FishPool)]),
                    IMGUI_COLORPICKER("##FishPool", &Configuration::SingleColors.find(EOneOffs::FishPool)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.loot").c_str(),
                    IMGUI_CHECKBOX("##Loot", &HUDDetours::Singles[static_cast<int>(EOneOffs::Loot)]),
                    IMGUI_COLORPICKER("##Loot", &Configuration::SingleColors.find(EOneOffs::Loot)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.quests").c_str(),
                    IMGUI_CHECKBOX("##Quest", &HUDDetours::Singles[static_cast<int>(EOneOffs::Quest)]),
                    IMGUI_COLORPICKER("##Quest", &Configuration::SingleColors.find(EOneOffs::Quest)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.rummage_piles").c_str(),
                    IMGUI_CHECKBOX("##RummagePiles", &HUDDetours::Singles[static_cast<int>(EOneOffs::RummagePiles)]),
                    IMGUI_COLORPICKER("##RummagePiles", &Configuration::SingleColors.find(EOneOffs::RummagePiles)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.treasure").c_str(),
                    IMGUI_CHECKBOX("##Treasure", &HUDDetours::Singles[static_cast<int>(EOneOffs::Treasure)]),
                    IMGUI_COLORPICKER("##Treasure", &Configuration::SingleColors.find(EOneOffs::Treasure)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.stables").c_str(),
                    IMGUI_CHECKBOX("##Stables", &HUDDetours::Singles[static_cast<int>(EOneOffs::Stables)]),
                    IMGUI_COLORPICKER("##Stables", &Configuration::SingleColors.find(EOneOffs::Stables)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.timed_drops").c_str(),
                    IMGUI_CHECKBOX("##TimedDrops", &HUDDetours::Singles[static_cast<int>(EOneOffs::TimedDrop)]),
                    IMGUI_COLORPICKER("##TimedDrops", &Configuration::SingleColors.find(EOneOffs::TimedDrop)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.books_lost_relics").c_str(),
                    IMGUI_CHECKBOX("##LostRelics", &HUDDetours::Singles[static_cast<int>(EOneOffs::Relic)]),
                    IMGUI_COLORPICKER("##LostRelics", &Configuration::SingleColors.find(EOneOffs::Relic)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.unpurchased_furniture").c_str(),
                    IMGUI_CHECKBOX("##UnpurchasedDecor", &HUDDetours::Singles[static_cast<int>(EOneOffs::Decor)]),
                    IMGUI_COLORPICKER("##UnpurchasedDecor", &Configuration::SingleColors.find(EOneOffs::Decor)->second)
                )
                IMGUI_ADD_ROW(
                    LOC("text.others").c_str(),
                    IMGUI_CHECKBOX("##Others", &HUDDetours::Singles[static_cast<int>(EOneOffs::Others)]),
                    IMGUI_COLORPICKER("##Others", &Configuration::SingleColors.find(EOneOffs::Others)->second)
                )
            }
            ImGui::EndTable();
        }
    }
}
