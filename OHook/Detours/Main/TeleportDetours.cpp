#include "TeleportDetours.h"

#include <algorithm>

#include "Configuration.h"
#include "ActorHandler.h"
#include "PaliaOverlay.h"
#include "Utils.h"

#include "functional"

#include <SDK/Palia_parameters.hpp>

#include "AimDetours.h"
#include "ImGuiNotify.hpp"

using namespace SDK;

void TeleportDetours::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
    DetourManager::AddInstance(VPC->MyHUD);
    DetourManager::AddFunctionListener("Function Engine.HUD.ReceiveDrawHUD", &Func_DoTeleportToTargeted, nullptr);
    DetourManager::AddInstance(VPC->GetTrackingComponent());
    DetourManager::AddFunctionListener("Function Palia.TrackingComponent.RpcServer_SetUserMarker", &TeleportToIngameWaypoint, nullptr);
    DetourManager::AddFunctionListener("Function Palia.TrackingComponent.RpcClient_SetUserMarkerViaWorldMap", &TeleportToMapWaypoint, nullptr);
}

bool TeleportDetours::IsPlayerNearby() {
    return Configuration::bAvoidTeleportingToPlayers && std::ranges::any_of(ActorHandler::GetActorsOfType(EType::Players), [&](const auto& player) {
        return IsWithinRange(Configuration::bDoRadiusPlayersAvoidance, player->Actor);
    });
}

inline FVector GetHighestPointAtLocation(const FVector& Location, float MaxHeight = 3000.0f) {
    const auto World = UWorld::GetWorld();
    if(!World) return Location;

    FVector TraceStart = Location + FVector{0.0f, 0.0f, MaxHeight};
    FVector TraceEnd = Location - FVector{0.0f, 0.0f, MaxHeight};
    FHitResult HitResult;
    
    bool bHit = UKismetSystemLibrary::LineTraceSingle(World, TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, &HitResult, true, {}, {}, 0.0f);
    return bHit ? HitResult.ImpactPoint : Location;
}

void TeleportDetours::Func_DoTeleportToTargeted(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bTeleportToTargeted || !IsGameWindowActive()) return;

    // Avoid teleporting if the Hotkey / Score is not valid
    if (!IsKeyUp(VK_XBUTTON2) || !(std::abs(AimDetours::BestScore - DBL_MAX) > 0.0001f) || !IsActorValid(AimDetours::BestTargetActor)) return;

    // Avoid teleporting to players
    if (Configuration::bAvoidTeleportingToPlayers && AimDetours::BestTargetActorType == EType::Players) {
        ImGui::InsertNotification({ImGuiToastType::Warning, 3000, "Avoided teleporting to a player."});
        return;
    }
    
    // Avoid teleporting to targeted if there are nearby players
    if(IsPlayerNearby()) {
        ImGui::InsertNotification({ImGuiToastType::Warning, 3000, "Cannot teleport because a player is nearby."});
        return;
    }

    // Teleportation logic
    TeleportPlayer(AimDetours::BestTargetLocation, 165.0f, ETeleportDirection::Forward);
}

void TeleportDetours::TeleportToMapWaypoint(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableWaypointTeleport) return;
    
    auto WaypointLocation = static_cast<Params::TrackingComponent_RpcServer_SetUserMarkerViaWorldMap*>(Parms)->WorldMapMarkerLocation;
    if (WaypointLocation.X == 0.0 && WaypointLocation.Y == 0.0) return;

    worldMapTeleported = true;
}

void TeleportDetours::TeleportToIngameWaypoint(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableWaypointTeleport) return;
    
    auto Waypoint_Location = static_cast<Params::TrackingComponent_RpcServer_SetUserMarker*>(Parms)->Location;
    if (Waypoint_Location.IsZero()) return;
    
    FVector TargetLocation = Waypoint_Location;
    if (worldMapTeleported) {
        TargetLocation = GetHighestPointAtLocation(TargetLocation, 3000.0f);
        worldMapTeleported = false;
    }
    
    if (!TargetLocation.IsZero()) {
        TeleportPlayer(TargetLocation, 250.0f, ETeleportDirection::Upwards);
    }
}

void TeleportDetours::TeleportPlayer(const FVector& Destination, float Offset, ETeleportDirection Direction = ETeleportDirection::None) {
    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter) return;

    // Get Character Location & Rotation
    FVector CharacterLocation = ValeriaCharacter->K2_GetActorLocation();
    FRotator CharacterRotation = ValeriaCharacter->K2_GetActorRotation();

    // Calculate new facing direction
    FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, Destination);
    NewRotation = {CharacterRotation.Pitch, NewRotation.Yaw, 0};

    // Directional Offset
    FVector DirectionVector = (Destination - CharacterLocation).GetNormalized();
    FVector Dest = Destination;
    switch (Direction) {
    case ETeleportDirection::Forward:    
        Dest.X -= DirectionVector.X * Offset;    
        Dest.Y -= DirectionVector.Y * Offset;    
        break;
    case ETeleportDirection::Back:    
        Dest.X += DirectionVector.X * Offset;    
        Dest.Y += DirectionVector.Y * Offset;    
        break;
    case ETeleportDirection::Right:    
        Dest.X += DirectionVector.Y * Offset;    
        Dest.Y -= DirectionVector.X * Offset;    
        break;
    case ETeleportDirection::Left:    
        Dest.X -= DirectionVector.Y * Offset;    
        Dest.Y += DirectionVector.X * Offset;    
        break;
    case ETeleportDirection::Upwards:
        Dest.Z += Offset;
        break;
    case ETeleportDirection::Downwards:
        Dest.Z -= Offset;
        break;
    case ETeleportDirection::None:
        break;
    }
    
    if(Direction != ETeleportDirection::Upwards && Direction != ETeleportDirection::Downwards) {
        Dest.Z += 165.0f;
    }

    ValeriaCharacter->MovementComponent->RpcClient_ApplyTeleport(Dest, NewRotation);
    DoGCLogic(ValeriaCharacter);
}

inline int teleportingFlushCounter = 0;
void TeleportDetours::DoGCLogic(const AValeriaCharacter* ValeriaCharacter) {
    teleportingFlushCounter++;
    if (teleportingFlushCounter >= 5) {
        // Helps with frames over time
        ValeriaCharacter->ValeriaPlayerController->ClientFlushLevelStreaming();
        ValeriaCharacter->ValeriaPlayerController->ClientForceGarbageCollection();
        teleportingFlushCounter = 0;
    }
}

void TeleportDetours::ForceTeleportToTarget() {
    if (!IsGameWindowActive()) return;

    // Validate target actor
    if (!(std::abs(AimDetours::BestScore - DBL_MAX) > 0.0001f) || !IsActorValid(AimDetours::BestTargetActor)) {
        ImGui::InsertNotification({ ImGuiToastType::Warning, 2000, "No valid target to teleport to." });
        return;
    }

    if (Configuration::bAvoidTeleportingToPlayers && AimDetours::BestTargetActorType == EType::Players) {
        ImGui::InsertNotification({ ImGuiToastType::Warning, 3000, "Avoided teleporting to a player." });
        return;
    }

    if (IsPlayerNearby()) {
        ImGui::InsertNotification({ ImGuiToastType::Warning, 3000, "Cannot teleport because a player is nearby." });
        return;
    }

    TeleportPlayer(AimDetours::BestTargetLocation, 165.0f, ETeleportDirection::Forward);
}