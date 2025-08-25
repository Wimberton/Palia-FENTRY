#pragma once

#include "Configuration.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "imgui.h"

namespace Store_AutoSellSettings {
    inline void Show() {
        ImGui::BeginTable("AutoSellTableRarity", 6);
        {
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Common", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Uncommon", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Rare", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Epic", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("SQ", ImGuiTableColumnFlags_WidthFixed, 60);

            ImGui::TableHeadersRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted(LOC("text.auto_sell_type").c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(LOC("text.auto_sell_common").c_str());
            ImGui::TableSetColumnIndex(2);
            ImGui::TextUnformatted(LOC("text.auto_sell_uncommon").c_str());
            ImGui::TableSetColumnIndex(3);
            ImGui::TextUnformatted(LOC("text.auto_sell_rare").c_str());
            ImGui::TableSetColumnIndex(4);
            ImGui::TextUnformatted(LOC("text.auto_sell_epic").c_str());
            ImGui::TableSetColumnIndex(5);
            ImGui::TextUnformatted(LOC("text.auto_sell_sq").c_str());

            IMGUI_ADD_BLANK_ROW(
                IMGUI_CHECKBOX(LOC("checkbox.bugs_auto_sell").c_str(), &Configuration::bBugSell, true, LOC("tooltip.bugs_auto_sell").c_str())
                IMGUI_CHECKBOX("##RarityBugCommon", &Configuration::bBugSellRarity[static_cast<int>(EItemRarity::Common)], true, "Automatically sell common bugs.")
                IMGUI_CHECKBOX("##RarityBugUncommon", &Configuration::bBugSellRarity[static_cast<int>(EItemRarity::Uncommon)], true, "Automatically sell uncommon bugs.")
                IMGUI_CHECKBOX("##RarityBugRare", &Configuration::bBugSellRarity[static_cast<int>(EItemRarity::Rare)], true, "Automatically sell rare bugs.")
                IMGUI_CHECKBOX("##RarityBugEpic", &Configuration::bBugSellRarity[static_cast<int>(EItemRarity::Epic)], true, "Automatically sell epic bugs.")
                IMGUI_CHECKBOX("##RarityBugSQ", &Configuration::bBugSellSQ, "Automatically sell star quality bugs.")
            )

            IMGUI_ADD_BLANK_ROW(
                IMGUI_CHECKBOX(LOC("checkbox.fish_auto_sell").c_str(), &Configuration::bFishingSell, true, LOC("tooltip.fish_auto_sell").c_str())
                IMGUI_CHECKBOX("##RarityFishCommon", &Configuration::bFishingSellRarity[static_cast<int>(EItemRarity::Common)], true, "Automatically sell common fish.")
                IMGUI_CHECKBOX("##RarityFishUncommon", &Configuration::bFishingSellRarity[static_cast<int>(EItemRarity::Uncommon)], true, "Automatically sell uncommon fish.")
                IMGUI_CHECKBOX("##RarityFishRare", &Configuration::bFishingSellRarity[static_cast<int>(EItemRarity::Rare)], true, "Automatically sell rare fish.")
                IMGUI_CHECKBOX("##RarityFishEpic", &Configuration::bFishingSellRarity[static_cast<int>(EItemRarity::Epic)], true, "Automatically sell epic fish.")
                IMGUI_CHECKBOX("##RarityFishSQ", &Configuration::bFishingSellSQ, "Automatically sell star quality fish.")
            )

            IMGUI_ADD_BLANK_ROW(
                IMGUI_CHECKBOX(LOC("checkbox.forageables_auto_sell").c_str(), &Configuration::bForageableSell, true, LOC("tooltip.forageables_auto_sell").c_str())
                IMGUI_CHECKBOX("##RarityForageableCommon", &Configuration::bForageableSellRarity[static_cast<int>(EItemRarity::Common)], true, "Mountain Morel\nOyster\nShell\nSundrop Lily\nBatterfly Beans\nElderflower\nElder Clam Mushroom\nFloatfish Mushroom\nFlowtato\nHoney\nKopaa Nut\nPiksii Berries")
                IMGUI_CHECKBOX("##RarityForageableUncommon", &Configuration::bForageableSellRarity[static_cast<int>(EItemRarity::Uncommon)], true, "Briar Daisy\nCoral\nCrystal Lake Lotus\nEmerald Carpet Moss\nSpice Sprouts\nSweet Leaf\nWild Garlic\nWild Ginger\nWild Green Onion\nElderwood Lotus\nElderwood Orchid\nStaircase Mushroom")
                IMGUI_CHECKBOX("##RarityForageableRare", &Configuration::bForageableSellRarity[static_cast<int>(EItemRarity::Rare)], true, "Brightshroom\nDragon's Beard Peat\nHeat Root\nPearl\nInfected Essence")
                IMGUI_CHECKBOX("##RarityForageableEpic", &Configuration::bForageableSellRarity[static_cast<int>(EItemRarity::Epic)], true, "Dari Cloves\nGreen Pearl\nHeartdrop Lily")
                IMGUI_CHECKBOX("##RarityForageableSQ", &Configuration::bForageableSellSQ, "Automatically sell star quality forageables.")
            )

            IMGUI_ADD_BLANK_ROW(
                IMGUI_CHECKBOX(LOC("checkbox.hunting_auto_sell").c_str(), &Configuration::bHuntingSell, true, LOC("tooltip.hunting_auto_sell").c_str())
                IMGUI_CHECKBOX("##RarityHuntingCommon", &Configuration::bHuntingSellRarity[static_cast<int>(EItemRarity::Common)], true, "Chapaa Meat\nFur\nMuujin Meat\nSernuk Hide\nSernuk Meat\nShmole Meat")
                IMGUI_CHECKBOX("##RarityHuntingUncommon", &Configuration::bHuntingSellRarity[static_cast<int>(EItemRarity::Uncommon)], true, "Muujin Mane\nSernuk Antlers\nSpotted Chapaa Tail\nShmole Whiskers")
                IMGUI_CHECKBOX("##RarityHuntingRare", &Configuration::bHuntingSellRarity[static_cast<int>(EItemRarity::Rare)], true, "Banded Muujin Mane\nElder Sernuk Antlers\nStriped Chapaa Tail\nElder Shmole Whiskers")
                IMGUI_CHECKBOX("##RarityHuntingEpic", &Configuration::bHuntingSellRarity[static_cast<int>(EItemRarity::Epic)], true, "Azure Chapaa Tail\nBluebristle Muujin Mane\nProudhorned Sernuk Antlers\nPiksii Shmole Whiskers")
                IMGUI_CHECKBOX("##RarityHuntingSQ", &Configuration::bHuntingSellSQ, "Automatically sell star quality hunting loot.")
            )
        }
        ImGui::EndTable();

        ImGui::BeginTable("AutoSellTableTrees", 6);
        {
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_None, 0);
            ImGui::TableSetupColumn("Fiber", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Sapwood", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Heartwood", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Flow", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Ancient", ImGuiTableColumnFlags_WidthFixed, 60);

            ImGui::TableHeadersRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("");
            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(LOC("text.tree_fiber").c_str());
            ImGui::TableSetColumnIndex(2);
            ImGui::TextUnformatted(LOC("text.tree_sapwood").c_str());
            ImGui::TableSetColumnIndex(3);
            ImGui::TextUnformatted(LOC("text.tree_heartwood").c_str());
            ImGui::TableSetColumnIndex(4);
            ImGui::TextUnformatted(LOC("text.tree_flow").c_str());
            ImGui::TableSetColumnIndex(5);
            ImGui::TextUnformatted(LOC("text.tree_ancient").c_str());

            IMGUI_ADD_BLANK_ROW(
                IMGUI_CHECKBOX(LOC("checkbox.trees_auto_sell").c_str(), &Configuration::bTreeSell, true, LOC("tooltip.trees_auto_sell").c_str())
                IMGUI_CHECKBOX("##TreeFiber", &Configuration::bTreeSellRarity[0], true, "Automatically sell plant fiber.")
                IMGUI_CHECKBOX("##TreeSap", &Configuration::bTreeSellRarity[1], true, "Automatically sell sapwood logs.")
                IMGUI_CHECKBOX("##TreeHeart", &Configuration::bTreeSellRarity[2], true, "Automatically sell heartwood logs.")
                IMGUI_CHECKBOX("##TreeFlow", &Configuration::bTreeSellRarity[3], true, "Automatically sell flow-infused logs.")
                IMGUI_CHECKBOX("##TreeAncient", &Configuration::bTreeSellRarity[4], true, "Automatically sell ancient logs.")
            )
        }
        ImGui::EndTable();

        IMGUI_CHECKBOX(LOC("checkbox.flowers_auto_sell").c_str(), &Configuration::bFlowerSell, LOC("tooltip.flowers_auto_sell").c_str())
        IMGUI_CHECKBOX(LOC("checkbox.junk_auto_sell").c_str(), &Configuration::bJunkSell, LOC("tooltip.junk_auto_sell").c_str())
    }
}
