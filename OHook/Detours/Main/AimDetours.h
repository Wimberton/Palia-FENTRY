#pragma once

#include "PaliaOverlay.h"

#include <SDK.hpp>
#include <SDK/Palia_parameters.hpp>

class PaliaOverlay;

using namespace SDK;

class AimDetours final {
public:
	AimDetours() = default;

	static void SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC);

	static void Func_DoInteliAim(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_DoSilentAim(const UObject* Context, UFunction* Function, void* Parms);
	static void Func_DoAimbot(const UObject* Context, UFunction* Function, void* Parms);

	static void ClientTravelInternal(const UObject* Context, UFunction* Function, void* Parms);
	
	static double BestScore;
	static AActor* BestTargetActorAnimal;
	static AActor* BestTargetActor;
	static EType BestTargetActorType;
	static FVector BestTargetLocation;
	static FRotator BestTargetRotation;

	static FVector AimOffset;
	
	// Anti-flicker variables
	static std::chrono::steady_clock::time_point LastTargetChangeTime;
	static AActor* PreviousTargetActor;
};

inline double AimDetours::BestScore = 0.0f;
inline AActor* AimDetours::BestTargetActorAnimal = nullptr;
inline AActor* AimDetours::BestTargetActor = nullptr;
inline EType AimDetours::BestTargetActorType = EType::MAX;
inline FVector AimDetours::BestTargetLocation = { 0, 0, 0 };
inline FRotator AimDetours::BestTargetRotation = { 0, 0, 0 };

inline FVector AimDetours::AimOffset = { -1.5, -1.35, 0 };

// Anti-flicker variables initialization
inline std::chrono::steady_clock::time_point AimDetours::LastTargetChangeTime = std::chrono::steady_clock::now();
inline AActor* AimDetours::PreviousTargetActor = nullptr;