#pragma once
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <Windows.h>
#include <ShlObj.h>
#include <tchar.h>

#include "Configuration.h"
#include "SDKExt.h"
#include <SDK/AssetRegistry_parameters.hpp>

#include "imgui.h"

// Cached Character Data
inline APlayerController* CachedPlayerController = nullptr;
inline AValeriaPlayerController* CachedValeriaController = nullptr;
inline AValeriaCharacter* CachedValeriaCharacter = nullptr;

//NEW, FAST SEARCH CONTAINER
#define STATIC_CLASS(CName) { SearchClasses.push_back(UObject::FindClassFast(CName)); } \

// Actor Validator
inline bool IsActorValid(const AActor* Actor) {
    return Actor && Actor->IsValidLowLevel() && Actor->RootComponent->IsValidLowLevel() && !Actor->IsActorBeingDestroyed() && !Actor->bActorIsBeingDestroyed;
}

// Component Validator
inline bool IsComponentValid(const UActorComponent* Component) {
    return Component && Component->IsValidLowLevel() && !Component->IsDefaultObject();
}

// Pointer Validator
inline bool IsValidPtr(const void* p) {
    return p != nullptr && p >= reinterpret_cast<void*>(0x10000) && p < reinterpret_cast<void*>(0x000F000000000000);
}

// Distance Validator
inline bool IsWithinRange(float Range, const AActor* Actor) {
    // Actor Validation
    if(!IsActorValid(Actor) || !IsActorValid(CachedValeriaCharacter)) return false;
    if(Actor == CachedValeriaCharacter) return false;
    
    auto ActorLocation = Actor->K2_GetActorLocation();
    if (ActorLocation.IsZero()) return false;

    auto CharacterLocation = CachedValeriaCharacter->K2_GetActorLocation();
    if(CharacterLocation.IsZero()) return false;
    
    // Range Check
    return CharacterLocation.GetDistanceToInMeters(ActorLocation) <= Range;
}

// Player Controller
inline APlayerController* GetPlayerController() {
    if (IsActorValid(CachedPlayerController)) {
        return CachedPlayerController;
    }
    
    const UWorld* World = UWorld::GetWorld();
    if (!World) {
        return nullptr;
    }

    UGameInstance* GameInstance = World->OwningGameInstance;
    if (!GameInstance || !GameInstance->LocalPlayers || GameInstance->LocalPlayers.Num() == 0)
        return nullptr;

    const ULocalPlayer* LocalPlayer = GameInstance->LocalPlayers[0];
    if (!LocalPlayer || !LocalPlayer->PlayerController || !LocalPlayer->PlayerController->Pawn || !LocalPlayer->PlayerController->Pawn->Controller)
        return nullptr;
    
    if (!IsActorValid(LocalPlayer->PlayerController) || !IsActorValid(LocalPlayer->PlayerController->Pawn) || !IsActorValid(LocalPlayer->PlayerController->Pawn->Controller))
        return nullptr;
    
    CachedPlayerController = LocalPlayer->PlayerController;
    return CachedPlayerController;
}

// Valeria Controller
inline AValeriaPlayerController* GetValeriaController() {
    if (IsActorValid(CachedValeriaController)) {
        return CachedValeriaController;
    }

    APlayerController* PlayerController = GetPlayerController();
    if (!PlayerController) {
        return nullptr;
    }

    CachedValeriaController = static_cast<AValeriaPlayerController*>(PlayerController);
    return IsActorValid(CachedValeriaController) ? CachedValeriaController : nullptr;
}

// Valeria Character
inline AValeriaCharacter* GetValeriaCharacter() {
    if (IsActorValid(CachedValeriaCharacter)) {
        return CachedValeriaCharacter;
    }
    
    AValeriaPlayerController* ValeriaController = GetValeriaController();
    if (!ValeriaController) {
        return nullptr;
    }

    CachedValeriaCharacter = ValeriaController->GetValeriaCharacter();
    return IsActorValid(CachedValeriaCharacter) ? CachedValeriaCharacter : nullptr;
}

// Load Asset PTR
inline static UFunction* GetAssetByObjectPath;
inline UObject* LoadAssetPtrFromPath(std::string Path) {
    if (Path.empty()) return nullptr;
    
    std::wstring widePath(Path.begin(), Path.end());
    auto FS_Path = FString(widePath.data());
    auto SoftObjPath = UKismetSystemLibrary::MakeSoftObjectPath(FS_Path);
    
    // Try AssetRegistry first - but with protection against corrupted registry
    auto AssetRegistry = UAssetRegistryHelpers::GetAssetRegistry().GetObjectRef();
    if (AssetRegistry && AssetRegistry->IsValidLowLevel()) {
        if (!GetAssetByObjectPath) {
            GetAssetByObjectPath = UObject::FindObject<UFunction>("Function AssetRegistry.AssetRegistry.K2_GetAssetByObjectPath");
        }
        if (GetAssetByObjectPath) {
            Params::AssetRegistry_K2_GetAssetByObjectPath Parms{};
            Parms.ObjectPath = std::move(SoftObjPath);
            Parms.bIncludeOnlyOnDiskAssets = false;
            Parms.bSkipARFilteredAssets = false;
            AssetRegistry->ProcessEvent(GetAssetByObjectPath, &Parms);
            auto AssetData = Parms.ReturnValue;
            if (UAssetRegistryHelpers::IsValid(AssetData)) {
                auto Asset = UAssetRegistryHelpers::GetAsset(AssetData);
                if (Asset && Asset->IsValidLowLevel()) return Asset;
            }
        }
    }
    // Fall back to kismet - with additional safety checks
    try {
        auto SoftObjRef = UKismetSystemLibrary::Conv_SoftObjPathToSoftObjRef(SoftObjPath);
        UObject* Asset = UKismetSystemLibrary::LoadAsset_Blocking(SoftObjRef);
        return (Asset && Asset->IsValidLowLevel()) ? Asset : nullptr;
    } catch (...) {
        // Catch any exceptions from corrupted asset loading
        return nullptr;
    }
}

#define FENTRY_IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)
#define FENTRY_IsKeyOn(key) (GetKeyState(key) & 0x01)

inline bool IsKeyUp(const int key) {
    static bool wasKeyDown = false;
    bool isKeyDown = GetAsyncKeyState(key) & 0x8000;

    if (wasKeyDown && !isKeyDown) {
        // Key was released
        wasKeyDown = false; // Update the state
        return true;
    }

    // Update the state for the next call
    wasKeyDown = isKeyDown;
    return false;
}

inline bool IsGameWindowActive() {
    const HWND foregroundWindow = GetForegroundWindow();
    TCHAR windowClassName[256];
    GetClassName(foregroundWindow, windowClassName, sizeof(windowClassName) / sizeof(TCHAR));
    return _tcscmp(windowClassName, TEXT("UnrealWindow")) == 0;
}

template <typename SearchType>
SearchType GetFlagSingle(std::string Text, std::map<SearchType, std::vector<std::string>>& map) {
    SearchType T = static_cast<SearchType>(0);
    for (auto& Entry : map) {
        bool bFound = false;

        for (auto& Str : Entry.second) {
            if (Text.find(Str) != std::string::npos) {
                T = Entry.first;
                bFound = true;
                break;
            }
        }

        if (bFound)
            break;
    }
    return T;
}

template <typename SearchType>
SearchType GetFlagSingleEnd(std::string Text, std::map<SearchType, std::vector<std::string>>& map) {
    SearchType T = static_cast<SearchType>(0);
    for (auto& Entry : map) {
        bool bFound = false;

        for (auto& Str : Entry.second) {
            if (Text.ends_with(Str)) {
                T = Entry.first;
                bFound = true;
                break;
            }
        }

        if (bFound)
            break;
    }
    return T;
}

// Float Comparison
inline bool AreFloatsEqual(float a, float b, float epsilon = 1e-5f) {
    return std::abs(a - b) <= epsilon;
}

// Base64 utility
inline std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

inline bool ib64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

inline std::string b64d(const std::string& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0, j = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && ib64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++) {
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            }
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++) {
                ret += char_array_3[i];
            }
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) {
            char_array_4[j] = 0;
        }

        for (j = 0; j < 4; j++) {
            char_array_4[j] = base64_chars.find(char_array_4[j]);
        }

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; j < i - 1; j++) {
            ret += char_array_3[j];
        }
    }

    return ret;
}

// Custom math expressions namespace
namespace CustomMath {
    constexpr float PI = 3.14159265358979323846f;

    template <typename T>
    T Clamp(const T& value, const T& min, const T& max) {
        return value < min ? min : (value > max ? max : value);
    }

    template <typename T>
    T Abs(const T& value) {
        return value < 0 ? -value : value;
    }

    inline float DegreesToRadians(const float degrees) {
        return degrees * (PI / 180.0f);
    }

    // Custom square root function
    inline float Sqrt(const float value) {
        return std::sqrt(value);
    }

    // Custom square function
    template <typename T>
    T Square(const T& value) {
        return value * value;
    }

    // Custom arccosine function
    inline float Acos(const float value) {
        return std::acos(Clamp(value, -1.0f, 1.0f));
    }

    inline float DistanceBetweenPoints(const FVector2D& Point1, const FVector2D& Point2) {
        return sqrt(pow(Point2.X - Point1.X, 2) + pow(Point2.Y - Point1.Y, 2));
    }

    // Custom radians to degrees function
    inline float RadiansToDegrees(const float radians) {
        return radians * (180.0f / PI);
    }

    inline double Fmod(const double Value, const double Mod) {
        return std::fmod(Value, Mod);
    }

    inline FRotator RInterpTo(const FRotator& Current, const FRotator& Target, double DeltaTime, float InterpSpeed) {
        // If no interpolation speed, just return the target
        if (InterpSpeed <= 0.0f) {
            return Target;
        }

        // Calculate the difference in each component
        double DeltaPitch = Target.Pitch - Current.Pitch;
        double DeltaYaw = Target.Yaw - Current.Yaw;
        double DeltaRoll = Target.Roll - Current.Roll;

        // Wrap angles to ensure the shortest path is taken
        DeltaPitch = Fmod(DeltaPitch + 180.0, 360.0) - 180.0;
        DeltaYaw = Fmod(DeltaYaw + 180.0, 360.0) - 180.0;
        DeltaRoll = Fmod(DeltaRoll + 180.0, 360.0) - 180.0;

        // Calculate the step for each component based on the interpolation speed and delta time
        double PitchStep = DeltaPitch * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);
        double YawStep = DeltaYaw * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);
        double RollStep = DeltaRoll * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);

        // Generate the new interpolated rotation
        FRotator InterpolatedRotation;
        InterpolatedRotation.Pitch = Current.Pitch + PitchStep;
        InterpolatedRotation.Yaw = Current.Yaw + YawStep;
        InterpolatedRotation.Roll = Current.Roll + RollStep;

        return InterpolatedRotation;
    }

    inline ImVec2 addImVec2(ImVec2 a, ImVec2 b) {
        return {a.x + b.x, a.y + b.y};
    }
}

inline void drawTextOutlined(ImDrawList* drawList, ImVec2 pos, ImU32 color, const char* text, const ImFont* font) {
    if (!text || !drawList || !font)
        return;

    const float fontSize = font->FontSize * Configuration::ESPTextScale;
    constexpr ImVec2 offsets[] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
    constexpr ImU32 outlineColor = IM_COL32(0, 0, 0, 170);

    for (const auto& offset : offsets) {
        drawList->AddText(font, fontSize, CustomMath::addImVec2(pos, offset), outlineColor, text);
    }

    drawList->AddText(font, fontSize, pos, color, text);
}