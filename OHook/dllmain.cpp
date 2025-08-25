#include "Main.h"
#include "HotkeysManager.h"
#include "PaliaOverlay.h"

#include "console.hpp"
#include "signatures.h"

#include <Windows.h>
#include <thread>
#include <string>

#ifdef ENABLE_SUPPORTER_FEATURES
#include "SupporterFeatures.h"
#endif

#include "SDK.hpp"

enum class ClientType {
    STANDALONE,
    STEAM,
    UNKNOWN
};

ClientType DetectClientType();
bool AutoOffsetGeneration();

// Forward declaration
DWORD WINAPI OnProcessAttach(LPVOID lpParam);
DWORD WINAPI OnProcessDetach(LPVOID lpParam);

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
    auto hModule = static_cast<HMODULE>(lpParam);

    // Allocate Console
    Console::Alloc();

    // Generate Offsets
    if (!AutoOffsetGeneration()) {
        LOG("[!] Unable to auto generate offsets. Exiting.\n");
        FreeLibraryAndExitThread(hModule, 0);
    }

    const auto Overlay = new PaliaOverlay();
    OverlayBase::Instance = Overlay;
    Overlay->SetupOverlay();

    Main::Start();

    return 0;
}

DWORD WINAPI OnProcessDetach(const LPVOID lpParam) {
    Main::Stop();
    Console::Free();
    return 0;
}

ClientType DetectClientType() {
    char processName[MAX_PATH];
    DWORD size = GetModuleFileNameA(nullptr, processName, MAX_PATH);
    
    if (size == 0) {
        LOG("[!] Failed to get process name\n");
        return ClientType::UNKNOWN;
    }

    std::string processPath(processName);
    size_t lastSlash = processPath.find_last_of("\\/");
    std::string fileName = processPath.substr(lastSlash + 1);

    LOG("[+] Detected process: %s\n", fileName.c_str());

    if (fileName == "PaliaClient-Win64-Shipping.exe") {
        LOG("[+] Client Type: STANDALONE\n");
        return ClientType::STANDALONE;
    }
    else if (fileName == "PaliaClientSteam-Win64-Shipping.exe") {
        LOG("[+] Client Type: STEAM\n");
        return ClientType::STEAM;
    }
    else {
        LOG("[!] Unknown client type: %s\n", fileName.c_str());
        return ClientType::UNKNOWN;
    }
}

bool AutoOffsetGeneration() {
    // Detect client type and set appropriate offsets
    ClientType clientType = DetectClientType();
    
    switch (clientType) {
        case ClientType::STANDALONE:
            LOG("[+] Setting STANDALONE client offsets\n");
            SDK::Offsets::GObjects = 0x0AA4DDC0;
            SDK::Offsets::AppendString = 0x011D4E30;
            SDK::Offsets::GNames = 0x0A969F80;
            SDK::Offsets::GWorld = 0x0ABCED08;
            SDK::Offsets::ProcessEvent = 0x01421600;
            SDK::Offsets::ProcessEventIdx = 0x0000004F;
            break;
            
        case ClientType::STEAM:
            LOG("[+] Setting STEAM client offsets\n");
            SDK::Offsets::GObjects = 0x0AAC0040;
            SDK::Offsets::AppendString = 0x011D5870;
            SDK::Offsets::GNames = 0x0A9DC200;
            SDK::Offsets::GWorld = 0x0AC40F88;
            SDK::Offsets::ProcessEvent = 0x014222B0;
            SDK::Offsets::ProcessEventIdx = 0x0000004F;
            break;
            
        default:
            LOG("[!] Unknown client type, using default STANDALONE offsets\n");
            SDK::Offsets::GObjects = 0x0AA4DDC0;
            SDK::Offsets::AppendString = 0x011D4E30;
            SDK::Offsets::GNames = 0x0A969F80;
            SDK::Offsets::GWorld = 0x0ABCED08;
            SDK::Offsets::ProcessEvent = 0x01421600;
            SDK::Offsets::ProcessEventIdx = 0x0000004F;
            break;
    }

    auto OffsetPtrs = GenerateOffsets();
    
    if (OffsetPtrs.GMallocAddress == NULL) {
        LOG("[!] Unable to find GMallocAddress. Exiting.\n");
        return false;
    }

    // Initialize FMemory
    FMemory::FMalloc::UnrealStaticGMalloc = reinterpret_cast<FMemory::FMalloc**>(OffsetPtrs.GMallocAddress);
    FMemory::GMalloc = *FMemory::FMalloc::UnrealStaticGMalloc;

    LOG("[+] Successfully initialized offsets for %s client\n", 
        clientType == ClientType::STANDALONE ? "STANDALONE" : 
        clientType == ClientType::STEAM ? "STEAM" : "UNKNOWN");

    return true;
}
