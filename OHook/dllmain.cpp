#include "Main.h"
#include "HotkeysManager.h"
#include "PaliaOverlay.h"
#include "Core/ConfigManager.h"
#include "Core/LogMacros.h"

#include "console.hpp"
#include "signatures.h"

#include <Windows.h>
#include <thread>
#include <string>
#include <memory>

#ifdef ENABLE_SUPPORTER_FEATURES
#include "SupporterFeatures.h"
#endif

#include "SDK.hpp"


bool AutoOffsetGeneration();

// Forward declaration
DWORD WINAPI OnProcessAttach(LPVOID lpParam);
DWORD WINAPI OnProcessDetach(LPVOID lpParam);

// Global overlay instance for proper cleanup
std::unique_ptr<PaliaOverlay> g_overlayInstance;

BOOL WINAPI DllMain(const HMODULE hModule, const DWORD fdwReason, const LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        HANDLE hHandle = CreateThread(nullptr, 0, OnProcessAttach, hModule, 0, nullptr);
        if (hHandle != nullptr) {
            CloseHandle(hHandle);
        }
    }
    else if (fdwReason == DLL_PROCESS_DETACH && !lpReserved) {
        OnProcessDetach(nullptr);
    }
    return TRUE;
}

DWORD WINAPI OnProcessAttach(const LPVOID lpParam) {
    if (lpParam == nullptr) {
        LOG_ERROR("Invalid module parameter");
        return 1;
    }
    
    auto hModule = static_cast<HMODULE>(lpParam);

    // Allocate Console
    Console::Alloc();

    // Load configuration
    ConfigManager& configManager = ConfigManager::GetInstance();
    if (!configManager.LoadConfig()) {
        LOG_WARN("Failed to load configuration. Using hardcoded fallback values.");
    }
    
    // Generate Offsets
    if (!AutoOffsetGeneration()) {
        LOG_FATAL("Unable to auto generate offsets. Exiting.");
        FreeLibraryAndExitThread(hModule, 0);
    }

    g_overlayInstance = std::make_unique<PaliaOverlay>();
    OverlayBase::Instance = g_overlayInstance.get();
    g_overlayInstance->SetupOverlay();

    Main::Start();

    return 0;
}

DWORD WINAPI OnProcessDetach(const LPVOID lpParam) {
    Main::Stop();
    
    // Clean up overlay instance
    if (g_overlayInstance) {
        OverlayBase::Instance = nullptr;
        g_overlayInstance.reset();
    }
    
    Console::Free();
    return 0;
}

ClientType DetectClientType() {
    char processName[MAX_PATH];
    DWORD size = GetModuleFileNameA(nullptr, processName, MAX_PATH);
    
    if (size == 0) {
        LOG_ERROR("Failed to get process name");
        return ClientType::UNKNOWN;
    }
    
    if (size >= MAX_PATH) {
        LOG_ERROR("Process name buffer overflow detected");
        return ClientType::UNKNOWN;
    }

    std::string processPath(processName);
    ConfigManager& configManager = ConfigManager::GetInstance();
    return configManager.DetectClientTypeFromConfig(processPath);
}

bool AutoOffsetGeneration() {
    // Detect client type and set appropriate offsets
    ClientType clientType = DetectClientType();
    
    ConfigManager& configManager = ConfigManager::GetInstance();
    ClientConfig* config = configManager.GetClientConfig(clientType);
    
    if (config == nullptr) {
        LOG_WARN("Failed to get client config, using fallback");
        // Fallback to hardcoded STANDALONE values
        SDK::Offsets::GObjects = 0x0AA4DDC0;
        SDK::Offsets::AppendString = 0x011D4E30;
        SDK::Offsets::GNames = 0x0A969F80;
        SDK::Offsets::GWorld = 0x0ABCED08;
        SDK::Offsets::ProcessEvent = 0x01421600;
        SDK::Offsets::ProcessEventIdx = 0x0000004F;
    } else {
        const char* typeStr = (clientType == ClientType::STANDALONE) ? "STANDALONE" : 
                            (clientType == ClientType::STEAM) ? "STEAM" : "DEFAULT";
        LOG_INFO("Setting %s client offsets from config", typeStr);
        
        // Load offsets from config with fallback values
        SDK::Offsets::GObjects = config->offsets.count("GObjects") ? 
            config->offsets["GObjects"] : 0x0AA4DDC0;
        SDK::Offsets::AppendString = config->offsets.count("AppendString") ? 
            config->offsets["AppendString"] : 0x011D4E30;
        SDK::Offsets::GNames = config->offsets.count("GNames") ? 
            config->offsets["GNames"] : 0x0A969F80;
        SDK::Offsets::GWorld = config->offsets.count("GWorld") ? 
            config->offsets["GWorld"] : 0x0ABCED08;
        SDK::Offsets::ProcessEvent = config->offsets.count("ProcessEvent") ? 
            config->offsets["ProcessEvent"] : 0x01421600;
        SDK::Offsets::ProcessEventIdx = config->offsets.count("ProcessEventIdx") ? 
            config->offsets["ProcessEventIdx"] : 0x0000004F;
    }

    auto OffsetPtrs = GenerateOffsets();
    
    if (OffsetPtrs.GMallocAddress == NULL) {
        LOG_FATAL("Unable to find GMallocAddress. Exiting.");
        return false;
    }

    // Initialize FMemory
    FMemory::FMalloc::UnrealStaticGMalloc = reinterpret_cast<FMemory::FMalloc**>(OffsetPtrs.GMallocAddress);
    FMemory::GMalloc = *FMemory::FMalloc::UnrealStaticGMalloc;

    const char* clientName = (clientType == ClientType::STANDALONE) ? "STANDALONE" : 
                            (clientType == ClientType::STEAM) ? "STEAM" : "UNKNOWN";
    LOG_INFO("Successfully initialized offsets for %s client", clientName);

    return true;
}
