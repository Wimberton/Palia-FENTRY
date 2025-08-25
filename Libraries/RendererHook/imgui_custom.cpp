#include "imgui_custom.h"

#include "imgui.h"
#include "imgui_internal.h"

void ImGui::ImGuiCustomStyle() {
    ImGuiStyle* style = &GetStyle();
    style->Alpha                       = 1.0f;             // Global alpha applies to everything in Dear ImGui.
    style->WindowPadding               = ImVec2(10.0f,10.0f); // Padding within a window
    style->WindowRounding              = 6.0f;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
    style->WindowBorderSize            = 1.0f;             // Thickness of border around windows. Generally set to 0.0f or 1.0f. Other values not well tested.
    style->WindowMinSize               = ImVec2(32,32);    // Minimum window size
    style->WindowTitleAlign            = ImVec2(0.5f,0.5f);// Alignment for title bar text
    style->WindowMenuButtonPosition    = ImGuiDir_None;    // Position of the collapsing/docking button in the title bar (left/right). Defaults to ImGuiDir_Left.
    style->ChildRounding               = 3.0f;             // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
    style->ChildBorderSize             = 0.0f;             // Thickness of border around child windows. Generally set to 0.0f or 1.0f. Other values not well tested.
    style->PopupRounding               = 5.0f;             // Radius of popup window corners rounding. Set to 0.0f to have rectangular child windows
    style->PopupBorderSize             = 0.0f;             // Thickness of border around popup or tooltip windows. Generally set to 0.0f or 1.0f. Other values not well tested.
    style->FramePadding                = ImVec2(10,8);     // Padding within a framed rectangle (used by most widgets)
    style->FrameRounding               = 4.0f;             // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
    style->FrameBorderSize             = 0.0f;             // Thickness of border around frames. Generally set to 0.0f or 1.0f. Other values not well tested.
    style->ItemSpacing                 = ImVec2(10,8);     // Horizontal and vertical spacing between widgets/lines
    style->ItemInnerSpacing            = ImVec2(8,6);      // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
    style->CellPadding                 = ImVec2(10,8);     // Padding within a table cell. Cellpadding.x is locked for entire table. CellPadding.y may be altered between different rows.
    style->TouchExtraPadding           = ImVec2(0,0);      // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    style->IndentSpacing               = 10.0f;            // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    style->ColumnsMinSpacing           = 6.0f;             // Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
    style->ScrollbarSize               = 12.0f;            // Width of the vertical scrollbar, Height of the horizontal scrollbar
    style->ScrollbarRounding           = 12.0f;            // Radius of grab corners rounding for scrollbar
    style->GrabMinSize                 = 10.0f;            // Minimum width/height of a grab box for slider/scrollbar
    style->GrabRounding                = 12.0f;            // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    style->LogSliderDeadzone           = 4.0f;             // The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
    style->TabRounding                 = 4.0f;             // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
    style->TabBorderSize               = 0.0f;             // Thickness of border around tabs.
    style->TabMinWidthForCloseButton   = 0.0f;             // Minimum width for close button to appear on an unselected tab when hovered. Set to 0.0f to always show when hovering, set to FLT_MAX to never show close button unless selected.
    style->ColorButtonPosition         = ImGuiDir_Right;   // Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
    style->ButtonTextAlign             = ImVec2(0.5f,0.5f);// Alignment of button text when button is larger than text.
    style->SelectableTextAlign         = ImVec2(0.0f,0.0f);// Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
    style->DisplayWindowPadding        = ImVec2(19,19);    // Window position are clamped to be visible within the display area or monitors by at least this amount. Only applies to regular windows.
    style->DisplaySafeAreaPadding      = ImVec2(3,3);      // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
    style->MouseCursorScale            = 1.0f;             // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). May be removed later.
    style->AntiAliasedLines            = true;             // Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU.
    style->AntiAliasedLinesUseTex      = true;             // Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering (NOT point/nearest filtering).
    style->AntiAliasedFill             = true;             // Enable anti-aliased filled shapes (rounded rectangles, circles, etc.).
    style->CurveTessellationTol        = 1.25f;            // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    style->CircleTessellationMaxError  = 0.30f;            // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
}


void ImGui::StyleColorsOrigin() {
    ImGuiStyle* style = &GetStyle();
    ImVec4* colors = style->Colors;

    // Main text color
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    // Disabled text color
    colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);

    // Window background color
    colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 0.98f); // 0.98f
    // Child background color
    colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.11f, 0.13f, 1.0f);
    // Popup background color
    colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.11f, 0.13f, 1.0f);

    // Border color
    colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 0.55f);
    // Border shadow color
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);

    // Frame background color
    colors[ImGuiCol_FrameBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    // Frame background color when hovered
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    // Frame background color when active
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);

    // Title background color
    colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    // Title background color when active
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    // Title background color when collapsed
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);

    // Menu bar background color
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);

    // Scrollbar background color
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    // Scrollbar grab color
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    // Scrollbar grab color when hovered
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
    // Scrollbar grab color when active
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);

    // Checkmark color
    colors[ImGuiCol_CheckMark] = ImVec4(0.236078434586525f, 0.2164705926179886f, 0.5850980663299561f, 1.0f);
    // Slider grab color
    colors[ImGuiCol_SliderGrab] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    // Slider grab color when active
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5372549295425415f, 0.5529412031173706f, 1.0f, 1.0f);

    // Button color
    colors[ImGuiCol_Button] = ImVec4(0.376f, 0.356f, 0.706f, 1.0f);
    // Button color when hovered
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.3765f, 0.3412f, 0.8471f, 1.0f);
    // Button color when active
    colors[ImGuiCol_ButtonActive] = ImVec4(0.3765f, 0.3412f, 0.8471f, 1.0f);

    // Header color
    colors[ImGuiCol_Header] = ImVec4(0.1576470592617989f, 0.1733333402872086f, 0.1890196138620377f, 1.0f);
    // Header color when hovered
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.1576470592617989f, 0.1733333402872086f, 0.1890196138620377f, 1.0f);
    // Header color when active
    colors[ImGuiCol_HeaderActive] = ImVec4(0.1576470592617989f, 0.1733333402872086f, 0.1890196138620377f, 1.0f);

    // Separator color
    colors[ImGuiCol_Separator] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    // Separator color when hovered
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
    // Separator color when active
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);

    // Resize grip color
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    // Resize grip color when hovered
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
    // Resize grip color when active
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);

    // Tab color
    colors[ImGuiCol_Tab] = ImVec4(0.0470588244f, 0.0549019608f, 0.0705882353f, 1.0f);
    // Tab color when hovered
    colors[ImGuiCol_TabHovered] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
    // Tab color when active
    colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);
    // Tab color when unfocused
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.0470588244f, 0.0549019608f, 0.0705882353f, 1.0f);
    // Tab color when unfocused and active
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 1.0f);

    // Plot line colors
    colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
    // Plot line color when hovered
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
    // Plot histogram color
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.2901960909366608f, 0.5960784554481506f, 1.0f);
    // Plot histogram color when hovered
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9960784316062927f, 0.4745098054409027f, 0.6980392336845398f, 1.0f);

    // Table header background color
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1f, 0.11f, 0.13f, 1.0f);
    // Strong table border color
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
    // Light table border color
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    // Table row background color
    colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
    // Alternate table row background color
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);

    // Text selection background color
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2352941185235977f, 0.2156862765550613f, 0.5960784554481506f, 1.0f);
    // Drag and drop target color
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    // Navigation highlight color
    colors[ImGuiCol_NavHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    // Window highlight for docking
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
    // Background color for modal windows
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f,
                                               0.501960813999176f);
}
