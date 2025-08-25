#pragma once

#include <imgui.h>
#include <string>
#include <vector>

namespace PaliaESP {
    void DisplayModsCategory(const std::string& title, const std::vector<std::pair<std::string, bool>>& mods);
    void DrawEnabledFeatures();
    void DrawGuiFOVCircle();
    void DrawGuiESP();
}