#pragma once
#include <windows.h>
#include <tlhelp32.h>

inline auto GMallocSig = "\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x75\x00\x33\xD2";
inline auto GMallocMask = "xxx????xxxx?xx";
inline auto AppendStringSig = "\xE8\x00\x00\x00\x00\x48\x8B\x5D\x00\x48\x63\x45\x00\x48\x8D\x3C\xC3\x48\x3B\xDF\x74\x00\x0F\x1F\x40\x00\x4C\x8B\x03";
inline auto AppendStringMask = "x????xxx?xxx?xxxxxxxx?xxx?xxx";
inline auto GObjectsSig = "\x4C\x8B\x0D\x00\x00\x00\x00\x8B\xD0";
inline auto GObjectsMask = "xxx????xx";

struct sigmod {
    uintptr_t dwBase, dwSize;
};

//struct offsetptrs {
//    uintptr_t GObjectsOffset, AppendStringOffset, GMallocAddress;
//};

struct offsetptrs {
    uintptr_t GMallocAddress;
};

inline bool MemoryCompare(const BYTE* bData, const BYTE* bSig, const char* szMask) {
    for (; *szMask; szMask++, bData++, bSig++) if (*szMask == 'x' && *bData != *bSig) return false;
    return true;
}

inline uintptr_t FindSignature(int procID, sigmod mod, const char* sig, const char* mask) {
    auto data = new BYTE[mod.dwSize];
    SIZE_T bytesRead;

    Toolhelp32ReadProcessMemory(procID, reinterpret_cast<LPVOID>(mod.dwBase), data, mod.dwSize, &bytesRead);

    for (uintptr_t i = 0; i < mod.dwSize; i++) {
        if (MemoryCompare(data + i, reinterpret_cast<const BYTE*>(sig), mask)) {
            delete[] data;
            return i; // returns offset only
        }
    }
    delete[] data;
    return NULL;
}

inline offsetptrs GenerateOffsets() {
    DWORD procID = GetCurrentProcessId();
    HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(mEntry);
    sigmod GameModule = {NULL,NULL};
    do {
        if (!strcmp(mEntry.szModule, "PaliaClientSteam-Win64-Shipping.exe") || !strcmp(mEntry.szModule, "PaliaClient-Win64-Shipping.exe")) {
            GameModule = {reinterpret_cast<uintptr_t>(mEntry.hModule), mEntry.modBaseSize};
        }
    } while (Module32Next(hModule, &mEntry));
    CloseHandle(hModule);

    // offsetptrs Pointers = {NULL, NULL, NULL};
    offsetptrs Pointers = { NULL };

    if (GameModule.dwBase) {
        // GObjects Offset
        //uintptr_t GObjectsPtr = FindSignature(static_cast<int>(procID), GameModule, GObjectsSig, GObjectsMask);
        //if (!GObjectsPtr) {
        //    //throw std::runtime_error("Unable to find GObjects.");
        //    return Pointers;
        //}
        //GObjectsPtr = GameModule.dwBase + GObjectsPtr;
        //uintptr_t GObjectsOffsetAddress = GObjectsPtr + 3;
        //int32_t GObjectsOffsetRelative = *reinterpret_cast<int32_t*>(GObjectsOffsetAddress);
        //uintptr_t GObjectsAddress = GObjectsPtr + 7 + GObjectsOffsetRelative;
        //uintptr_t GObjectsOffset = GObjectsAddress - GameModule.dwBase;
        //std::cout << "Offsets::GObjects = " << std::hex << GObjectsOffset << "\n";
        //Pointers.GObjectsOffset = GObjectsOffset;

        // AppendString Offset
        //uintptr_t AppendStringPtr = FindSignature(static_cast<int>(procID), GameModule, AppendStringSig, AppendStringMask);
        //if (!AppendStringPtr) {
        //    //throw std::runtime_error("Unable to find AppendString.");
        //    return Pointers;
        //}
        //AppendStringPtr = GameModule.dwBase + AppendStringPtr;
        //uintptr_t AppendStringOffsetAddress = AppendStringPtr + 1;
        //int32_t AppendStringOffsetRelative = *reinterpret_cast<int32_t*>(AppendStringOffsetAddress);
        //uintptr_t AppendStringAddress = AppendStringPtr + 5 + AppendStringOffsetRelative;
        //uintptr_t AppendStringOffset = AppendStringAddress - GameModule.dwBase;
        //std::cout << "Offsets::AppendString = " << std::hex << AppendStringOffset << "\n";
        //Pointers.AppendStringOffset = AppendStringOffset;

        // GMalloc
        uintptr_t GMallocPtr = FindSignature(static_cast<int>(procID), GameModule, GMallocSig, GMallocMask);
        if (!GMallocPtr) {
            //throw std::runtime_error("Unable to find GMalloc.");
            return Pointers;
        }
        GMallocPtr = GameModule.dwBase + GMallocPtr;
        uintptr_t GMallocOffsetAddress = GMallocPtr + 3;
        int32_t GMallocOffsetRelative = *reinterpret_cast<int32_t*>(GMallocOffsetAddress);
        uintptr_t GMallocAddress = GMallocPtr + 7 + GMallocOffsetRelative;
        uintptr_t GMallocOffset = GMallocAddress - GameModule.dwBase;
        std::cout << "Offsets::GMalloc = " << std::hex << GMallocOffset << "\n";
        Pointers.GMallocAddress = GMallocAddress;
    }

    return Pointers;
}
