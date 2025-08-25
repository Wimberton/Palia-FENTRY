// ReSharper disable CppClangTidyModernizeMacroToEnum
#pragma once
#include <Windows.h>

#define WINDOW_TITLE "OriginOTG v1.0.0"

#define PROCESS_NAME L"G01Client-Win64-Shipping.exe"
//#define PROCESS_NAME L"TestEnvironmentD3D11.exe"
//#define PROCESS_NAME L"TestEnvironmentD3D12.exe"

#define CONFIG_DIR "C:\\ProgramData\\OriginOTG\\config"

#define OPEN_MENU_KEY VK_INSERT
#define UNINJECT_KEY VK_END

// ========================================
// ~ Tools n libraries n stuff
#define USING_KIERO                   1
#define USING_MINHOOK                 1
#define USING_JSONCPP                 1
#define USING_IMGUI                   1
#define USING_IMGUI_HOTKEYS           1
#define USING_CUSTOM_IMGUI_FONTS      1
#define USING_IMGUI_NOTIF             1

// ========================================
// ~ Define Game Engine:
//      1 = Unreal Engine,
//      2 = Source 2,
//      ...
// add more as we go I guess
#define GAME_ENGINE 1
