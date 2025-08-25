#include "OverlayBase.h"
#include "RendererDetector.h"
#include "Windows/WindowsHook.h"
#include "imgui_custom.h"
#include "Fonts.h"
#include <imgui.h>
#include <cmath>
#include <cstdio>

OverlayBase* OverlayBase::Instance = nullptr;

void OverlayBase::HookReady()
{
	if (!bIsReady)
	{
		//ImGuiIO &io = ImGui::GetIO();
		//io.WantSetMousePos = false;
		//io.MouseDrawCursor = false;
		//io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		bIsReady = true;
	}
}

void OverlayBase::OverlayProc()
{
	if (!IsReady()) return;

	ImGuiIO& io = ImGui::GetIO();
	
	// Single font push for the entire overlay
	ImGui::PushFont(FontDefault);

	DrawHUD();
	DrawGuiESP();

	if (bShowOverlay)
	{
		io.ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;
		DrawOverlay();
	}
	else {
		io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	}

	DrawGuiFOVCircle();
	DrawEnabledFeatures();
	
	// Single font pop at the end
	ImGui::PopFont();
}

void OverlayBase::SetupFonts() {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    	
    //define icon ranges
	static constexpr ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

	// Define Chinese glyph ranges for CJK support
	static constexpr ImWchar chinese_ranges[] = {
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x2000, 0x206F, // General Punctuation
		0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
		0xFF00, 0xFFEF, // Half-width characters
		0x4e00, 0x9FAF, // CJK Unified Ideographs
		0,
	};

	// Inter Medium (Default) - Optimized for performance with Chinese support
	ImFontConfig inter_medium_config;
	inter_medium_config.OversampleH = inter_medium_config.OversampleV = 1; // Reduced from 2 to 1
	inter_medium_config.PixelSnapH = true;
	inter_medium_config.GlyphRanges = io.Fonts->GetGlyphRangesDefault(); // Start with Latin characters
	if (inter_medium_config.SizePixels <= 0.0f)
		inter_medium_config.SizePixels = 15.0f * 1.0f;

	FontDefault = io.Fonts->AddFontFromMemoryCompressedBase85TTF(inter_medium_ttf, inter_medium_config.SizePixels, &inter_medium_config, inter_medium_config.GlyphRanges);
	
	// Merge Chinese font support - try multiple fallback fonts
	{
		ImFontConfig chinese_config;
		chinese_config.MergeMode = true;
		chinese_config.PixelSnapH = true;
		chinese_config.GlyphRanges = chinese_ranges;
		chinese_config.OversampleH = chinese_config.OversampleV = 1;
		chinese_config.SizePixels = 15.0f;
		
		// Try multiple Chinese fonts in order of preference
		const char* chinese_fonts[] = {
			"C:\\Windows\\Fonts\\msyh.ttc",      // Microsoft YaHei (preferred)
			"C:\\Windows\\Fonts\\simsun.ttc",   // SimSun
			"C:\\Windows\\Fonts\\simhei.ttf",   // SimHei
			"C:\\Windows\\Fonts\\msjh.ttc",     // Microsoft JhengHei (Traditional)
			nullptr
		};
		
		bool chinese_font_loaded = false;
		for (int i = 0; chinese_fonts[i] != nullptr && !chinese_font_loaded; i++) {
			ImFont* chinese_font = io.Fonts->AddFontFromFileTTF(chinese_fonts[i], chinese_config.SizePixels, &chinese_config, chinese_config.GlyphRanges);
			if (chinese_font != nullptr) {
				chinese_font_loaded = true;
				// Log successful font loading for debugging
				printf("[FONT] Successfully loaded Chinese font: %s\n", chinese_fonts[i]);
			}
		}
		
		// If no system font worked, try ImGui's built-in Chinese ranges with default font
		if (!chinese_font_loaded) {
			io.Fonts->AddFontDefault(&chinese_config);
			printf("[FONT] Fallback: Using default font with Chinese ranges\n");
		}
	}
	{
		// Merge FontAwesome with Default - Optimized
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		icons_config.FontDataOwnedByAtlas = false;
		icons_config.GlyphOffset.y = 2.5f;
		icons_config.GlyphOffset.x = -2.2f;
		icons_config.OversampleH = icons_config.OversampleV = 1; // Reduced from 2 to 1
		if (icons_config.SizePixels <= 0.0f)
			icons_config.SizePixels = 18.0f;
		io.Fonts->AddFontFromMemoryCompressedBase85TTF(fontAwesome, icons_config.SizePixels, &icons_config, icons_ranges);
	}

	// Inter Light - Optimized
	ImFontConfig inter_light_config;
	inter_light_config.OversampleH = inter_light_config.OversampleV = 1; // Reduced from 2 to 1
	inter_light_config.PixelSnapH = true;
	inter_light_config.GlyphRanges = io.Fonts->GetGlyphRangesDefault();
	if (inter_light_config.SizePixels <= 0.0f)
		inter_light_config.SizePixels = 15.0f * 1.0f;

	InterLight = io.Fonts->AddFontFromMemoryCompressedBase85TTF(inter_light_ttf, inter_light_config.SizePixels, &inter_light_config, inter_light_config.GlyphRanges);
	
	// Merge Chinese font support for InterLight
	{
		ImFontConfig chinese_config_light;
		chinese_config_light.MergeMode = true;
		chinese_config_light.PixelSnapH = true;
		chinese_config_light.GlyphRanges = chinese_ranges;
		chinese_config_light.OversampleH = chinese_config_light.OversampleV = 1;
		chinese_config_light.SizePixels = 15.0f;
		
		// Try to load Chinese font for InterLight
		bool chinese_font_loaded = false;
		const char* chinese_fonts[] = {
			"C:\\Windows\\Fonts\\msyh.ttc",      // Microsoft YaHei
			"C:\\Windows\\Fonts\\simsun.ttc",   // SimSun
			"C:\\Windows\\Fonts\\simhei.ttf",   // SimHei
			nullptr
		};
		
		for (int i = 0; chinese_fonts[i] != nullptr && !chinese_font_loaded; i++) {
			ImFont* chinese_font = io.Fonts->AddFontFromFileTTF(chinese_fonts[i], chinese_config_light.SizePixels, &chinese_config_light, chinese_config_light.GlyphRanges);
			if (chinese_font != nullptr) {
				chinese_font_loaded = true;
			}
		}
		
		if (!chinese_font_loaded) {
			io.Fonts->AddFontDefault(&chinese_config_light);
		}
	}
	{
		// Merge FontAwesome with Inter Light
		ImFontConfig icons_config_light;
		icons_config_light.MergeMode = true;
		icons_config_light.PixelSnapH = true;
		icons_config_light.FontDataOwnedByAtlas = false;
		icons_config_light.GlyphOffset.y = 2.4f;
		icons_config_light.GlyphOffset.x = -2.0f;
		icons_config_light.OversampleH = icons_config_light.OversampleV = 1; // Reduced from 2 to 1
		if (icons_config_light.SizePixels <= 0.0f)
			icons_config_light.SizePixels = 18.0f;
		io.Fonts->AddFontFromMemoryCompressedBase85TTF(fontAwesome, icons_config_light.SizePixels, &icons_config_light, icons_ranges);
	}

	// Inter Black - Optimized
	ImFontConfig inter_black_config;
	inter_black_config.OversampleH = inter_black_config.OversampleV = 1; // Reduced from 2 to 1
	inter_black_config.PixelSnapH = true;
	inter_black_config.GlyphRanges = io.Fonts->GetGlyphRangesDefault();
	if (inter_black_config.SizePixels <= 0.0f)
		inter_black_config.SizePixels = 15.0f;

	InterBlack = io.Fonts->AddFontFromMemoryCompressedBase85TTF(inter_black_ttf, inter_black_config.SizePixels, &inter_black_config, inter_black_config.GlyphRanges);
	{
		// Merge FontAwesome with Inter Black
		ImFontConfig icons_config_black;
		icons_config_black.MergeMode = true;
		icons_config_black.PixelSnapH = true;
		icons_config_black.FontDataOwnedByAtlas = false;
		icons_config_black.GlyphOffset.y = 2.4f;
		icons_config_black.GlyphOffset.x = -2.5f;
		icons_config_black.OversampleH = icons_config_black.OversampleV = 1; // Reduced from 2 to 1
		if (icons_config_black.SizePixels <= 0.0f)
			icons_config_black.SizePixels = 18.0f;
		io.Fonts->AddFontFromMemoryCompressedBase85TTF(fontAwesome, icons_config_black.SizePixels, &icons_config_black, icons_ranges);
	}

	// Inter Semi-Bold - Optimized for ESP
	ImFontConfig inter_semibold_config;
	inter_semibold_config.OversampleH = inter_semibold_config.OversampleV = 1; // Reduced from 2 to 1
	inter_semibold_config.PixelSnapH = true;
	inter_semibold_config.GlyphRanges = io.Fonts->GetGlyphRangesDefault();
	if (inter_semibold_config.SizePixels <= 0.0f)
		inter_semibold_config.SizePixels = 14.5f;

	ESPFont = io.Fonts->AddFontFromMemoryCompressedBase85TTF(inter_semibold_ttf, inter_semibold_config.SizePixels, &inter_semibold_config, inter_semibold_config.GlyphRanges);
	{
		// Merge FontAwesome with ESPFont (Inter-Semibold
		ImFontConfig icons_config_semibold;
		icons_config_semibold.MergeMode = true;
		icons_config_semibold.PixelSnapH = true;
		icons_config_semibold.FontDataOwnedByAtlas = false;
		icons_config_semibold.GlyphOffset.y = 2.4f;
		icons_config_semibold.GlyphOffset.x = -2.5f;
		icons_config_semibold.OversampleH = icons_config_semibold.OversampleV = 1; // Reduced from 2 to 1
		if (icons_config_semibold.SizePixels <= 0.0f)
			icons_config_semibold.SizePixels = 16.5f;
		io.Fonts->AddFontFromMemoryCompressedBase85TTF(fontAwesome, icons_config_semibold.SizePixels, &icons_config_semibold, icons_ranges);
	}

	// Add FontHUD - Optimized
	ImFontConfig fontcfg;
	fontcfg.OversampleH = fontcfg.OversampleV = 1; // Reduced from 2 to 1
	fontcfg.PixelSnapH = true;
	fontcfg.GlyphRanges = io.Fonts->GetGlyphRangesDefault();
	fontcfg.SizePixels = std::round(io.DisplaySize.y / 60);
	FontHUD = io.Fonts->AddFontDefault(&fontcfg);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0; // Disable round window

    ImGui::StyleColorsOrigin();
    ImGui::ImGuiCustomStyle();
}

void OverlayBase::ShowOverlay(bool bShow)
{
	if (!IsReady() || bShowOverlay == bShow)
		return;

	ImGuiIO& io = ImGui::GetIO();
	io.MouseDrawCursor = bShow;

	HWND GameHWnd = WindowsHook::Instance()->GetGameHwnd();

	static RECT old_clip;

	if (bShow)
	{
		// Enable interaction with the overlay by removing WS_EX_TRANSPARENT
		LONG_PTR exStyle = GetWindowLongPtr(GameHWnd, GWL_EXSTYLE);
		SetWindowLongPtr(GameHWnd, GWL_EXSTYLE, exStyle & ~WS_EX_TRANSPARENT);

		RECT cliRect, wndRect, clipRect;

		GetClipCursor(&old_clip);
		GetWindowRect(GameHWnd, &wndRect);
		GetClientRect(GameHWnd, &cliRect);

		clipRect = wndRect;

		wndRect.right -= wndRect.left;
		wndRect.bottom -= wndRect.top;
		int borderWidth = (wndRect.right - cliRect.right) / 2;
		clipRect.top += wndRect.bottom - cliRect.bottom - borderWidth;
		clipRect.left += borderWidth;
		clipRect.right -= borderWidth;
		clipRect.bottom -= borderWidth;

		ClipCursor(&clipRect);
	}
	else
	{
		// Disable interaction with the overlay by adding WS_EX_TRANSPARENT
		LONG_PTR exStyle = GetWindowLongPtr(GameHWnd, GWL_EXSTYLE);
		SetWindowLongPtr(GameHWnd, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);

		ClipCursor(&old_clip);
	}

	bShowOverlay = bShow;
}

void OverlayBase::SetupOverlay()
{
	std::lock_guard<std::recursive_mutex> lock(OverlayMutex);
	if (!bSetupOverlayCalled)
	{
		bSetupOverlayCalled = true;
		RendererDetector::Instance().FindRenderer();
	}
}