#pragma once

#include <SDK.hpp>
#include <SDK/Palia_parameters.hpp>

class PaliaOverlay;

using namespace SDK;

class TeleportDetours final {
public:
	TeleportDetours() = default;
	
	enum class ETeleportDirection : std::uint8_t {
		None,
		Forward,
		Right,
		Back,
		Left,
		Upwards,
		Downwards
	};

	static void TeleportPlayer(const FVector& Destination, float Offset, ETeleportDirection Direction);
	static void TeleportPlayer(const FVector& Destination) {
		TeleportPlayer(Destination, 0.0f, ETeleportDirection::None);
	}
	
	static void SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC);
	static void Func_DoTeleportToTargeted(const UObject* Context, UFunction* Function, void* Parms);
	static void TeleportToIngameWaypoint(const UObject* Context, UFunction* Function, void* Parms);
	static void TeleportToMapWaypoint(const UObject* Context, UFunction* Function, void* Parms);
	static void ForceTeleportToTarget();
	
private:
	static bool IsPlayerNearby();
	static void DoGCLogic(const AValeriaCharacter* ValeriaCharacter);
};

inline bool worldMapTeleported = false;