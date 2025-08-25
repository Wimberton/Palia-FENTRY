#include "AimDetours.h"
#include "Configuration.h"
#include "ActorHandler.h"
#include "ToolHandler.h"
#include "PaliaOverlay.h"
#include "SDKExt.h"
#include "Utils.h"
#include "OverlayBase.h"

#include "functional"
#include <chrono>

#include <SDK/Palia_parameters.hpp>

using namespace SDK;

void AimDetours::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
    DetourManager::AddInstance(VPC);
	DetourManager::AddFunctionListener("Function Engine.PlayerController.ClientTravelInternal", &ClientTravelInternal, nullptr);
    DetourManager::AddInstance(VPC->MyHUD);
    DetourManager::AddFunctionListener("Function Engine.HUD.ReceiveDrawHUD", &Func_DoInteliAim, nullptr);
    DetourManager::AddFunctionListener("Function Engine.HUD.ReceiveDrawHUD", &Func_DoAimbot, nullptr);
    DetourManager::AddInstance(VC->GetFiringComponent());
	DetourManager::AddFunctionListener("Function Palia.ProjectileFiringComponent.RpcServer_FireProjectile", &Func_DoSilentAim, nullptr);
}

void AimDetours::Func_DoInteliAim(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableInteliAim)
        return;

    const auto PlayerController = GetPlayerController();
    if (!PlayerController)
        return;
    
    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;
    
    auto AimingComponent = ValeriaCharacter->GetAimingComponent();
    if (!AimingComponent)
        return;

    bool isPlayerAiming = AimingComponent->IsAiming();

    FVector CharacterLocation = ValeriaCharacter->K2_GetActorLocation();
    FRotator CharacterRotation = PlayerController->GetControlRotation();
    FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CharacterRotation);

    // Anti-flicker constants
    constexpr double TARGET_HOLD_TIME_MS = 50.0; // Minimum time to hold a target before switching (50ms)
    constexpr double SCORE_IMPROVEMENT_THRESHOLD = 0.15; // Require 15% better score to switch targets
    
    auto currentTime = std::chrono::steady_clock::now();
    auto timeSinceLastChange = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - LastTargetChangeTime).count();
    
    // Check if current target is still valid and within hold time
    bool shouldKeepCurrentTarget = false;
    if (BestTargetActor && IsActorValid(BestTargetActor) && timeSinceLastChange < TARGET_HOLD_TIME_MS) {
        shouldKeepCurrentTarget = true;
        
        // Recalculate current target's score to check if it's still viable
        for (auto& Entry : ActorHandler::GetActors()) {
            if (Entry->Actor == BestTargetActor) {
                bool bShouldConsider = false;
                auto ActorType = Entry->ActorType();
                
                if (isPlayerAiming) {
                    switch (ActorType) {
                    case EType::Animal:
                        bShouldConsider = Entry->ShouldShow(ValeriaCharacter) && (ToolHandler::EquippedTool == ETools::Bow) && CharacterLocation.GetDistanceToInMeters(Entry->WorldPosition) <= 22.0f;
                        break;
                    case EType::Bug:
                        bShouldConsider = Entry->ShouldShow(ValeriaCharacter) && (ToolHandler::EquippedTool == ETools::Belt);
                        break;
                    default:
                        continue;
                    }
                }
                else {
                    bShouldConsider = Entry->ShouldShow(ValeriaCharacter);
                    if (!Configuration::bAvoidTeleportingToPlayers && Entry->ActorType() == EType::Players) bShouldConsider = false;
                }
                
                // If current target is no longer valid, allow switching
                if (!bShouldConsider || Entry->Distance > Configuration::CullDistance) {
                    shouldKeepCurrentTarget = false;
                }
                break;
            }
        }
    }
    
    if (shouldKeepCurrentTarget) {
        return; // Keep current target, don't recalculate
    }

    double currentBestScore = DBL_MAX;

    for (auto& Entry : ActorHandler::GetActors()) {
        if (!IsActorValid(Entry->Actor) || Entry->WorldPosition.IsZero()) {
            continue;
        }

        auto ActorType = Entry->ActorType();

        bool bShouldConsider = false;

        if (isPlayerAiming) {
            switch (ActorType) {
            case EType::Animal:
                bShouldConsider = Entry->ShouldShow(ValeriaCharacter) && (ToolHandler::EquippedTool == ETools::Bow) && CharacterLocation.GetDistanceToInMeters(Entry->WorldPosition) <= 22.0f;
                break;
            case EType::Bug:
                bShouldConsider = Entry->ShouldShow(ValeriaCharacter) && (ToolHandler::EquippedTool == ETools::Belt);
                break;
            default:
                continue;
            }
        }
        else {
            bShouldConsider = Entry->ShouldShow(ValeriaCharacter);
            if (!Configuration::bAvoidTeleportingToPlayers && Entry->ActorType() == EType::Players) bShouldConsider = false;
        }

        if (!bShouldConsider)
            continue;

        FVector ActorLocation = Entry->WorldPosition;
        FVector DirectionToActor = (ActorLocation - CharacterLocation).GetNormalized();
        FVector TargetVelocity = Entry->Actor->GetVelocity();

        FVector RelativeVelocity = TargetVelocity - ValeriaCharacter->GetVelocity();
        FVector RelativeDirection = RelativeVelocity.GetNormalized();

        auto Distance = Entry->Distance;
        float Angle = CustomMath::RadiansToDegrees(acosf(static_cast<float>(ForwardVector.Dot(DirectionToActor))));

        if (ActorLocation.IsZero())
            continue;

        if (Entry->Actor == ValeriaCharacter)
            continue;

        if (Distance > Configuration::CullDistance)
            continue;

        // Weighting factors for different factors
        double AngleWeight, DistanceWeight, MovementWeight;

        // Adjust weighting factors based on EType
        switch (ActorType) {
        case EType::Animal:
            AngleWeight = 0.10;
            DistanceWeight = 0.0;
            MovementWeight = 0.0;
            break;
        case EType::Ore:
            AngleWeight = 0.10;
            DistanceWeight = 0.0;
            MovementWeight = 0.0;
            break;
        case EType::Bug:
            AngleWeight = 0.10;
            DistanceWeight = 0.0;
            MovementWeight = 0.0;
            break;
        default:
            AngleWeight = 0.10;
            DistanceWeight = 0.0;
            MovementWeight = 0.0;
            break;
        }

        // Calculate score based on weighted sum of factors
        if (double Score = AngleWeight * Angle + DistanceWeight * Distance + MovementWeight * RelativeDirection.Magnitude(); Angle <= Configuration::FOVRadius / 2.0 && Score < 50.0f) {
            bool shouldUpdateTarget = false;
            
            if (BestTargetActor == nullptr) {
                // No current target, accept any valid target
                shouldUpdateTarget = (Score < currentBestScore);
            }
            else if (Entry->Actor == BestTargetActor) {
                // Current target found again, update its info but don't trigger change timer
                shouldUpdateTarget = true;
            }
            else {
                // Different target found, apply hysteresis
                // Require significantly better score to switch (must be X% better than current best)
                double requiredImprovement = currentBestScore * (1.0 - SCORE_IMPROVEMENT_THRESHOLD);
                shouldUpdateTarget = (Score < requiredImprovement);
            }
            
            if (shouldUpdateTarget && Score < currentBestScore) {
                bool isTargetChange = (BestTargetActor != Entry->Actor);
                
                currentBestScore = Score;
                BestScore = Score;
                BestTargetActor = Entry->Actor;
                BestTargetActorType = ActorType;
                BestTargetLocation = ActorLocation;
                BestTargetRotation = UKismetMathLibrary::FindLookAtRotation(CharacterLocation, ActorLocation);
                
                // Update change time only if this is actually a different target
                if (isTargetChange) {
                    LastTargetChangeTime = currentTime;
                    PreviousTargetActor = BestTargetActor;
                }
            }
        }
    }
}

void AimDetours::Func_DoSilentAim(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableSilentAimbot || !BestTargetActor || !IsActorValid(BestTargetActor))
        return;

    if (!(BestTargetActorType == EType::Animal || BestTargetActorType == EType::Bug))
        return;

    auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    auto FiringComponent = ValeriaCharacter->GetFiringComponent();
    if (!IsComponentValid(FiringComponent))
        return;

    auto FireProjectile = static_cast<Params::ProjectileFiringComponent_RpcServer_FireProjectile*>(Parms);

    for (auto& [ProjectileId, Pad_22C8, ProjectileActor, HasHit, Pad_22C9] : FiringComponent->FiredProjectiles) {
        if (ProjectileActor && IsActorValid(ProjectileActor) && ProjectileId == FireProjectile->ProjectileId) {
            
            AValeriaProjectile* ValeriaProjectile = ProjectileActor;
            if (!ValeriaProjectile)
                continue;

            FVector TargetLocation = BestTargetActor->K2_GetActorLocation();
            float DistanceToTarget = ValeriaCharacter->K2_GetActorLocation().GetDistanceToInMeters(TargetLocation);

            if (DistanceToTarget <= 23.0f && BestTargetActorType == EType::Animal) {

                FVector DirectionToTarget = (TargetLocation - ValeriaProjectile->K2_GetActorLocation()).GetNormalized();
                FVector NewProjectileLocation = TargetLocation - (DirectionToTarget * 50.0f);

                FHitResult HitResult;

                ValeriaProjectile->K2_SetActorLocation(TargetLocation, false, &HitResult, false);
                ValeriaProjectile->HitActorAccordingToServer = BestTargetActor;
                HasHit = true;

                // FiringComponent->RpcServer_NotifyProjectileHit(FireProjectile->ProjectileId, HUDDetours::BestTargetActor, TargetLocation);
            }
            else if (DistanceToTarget <= 120.0f && BestTargetActorType == EType::Bug) {
                ValeriaProjectile->bInstantCatchTrappedInsects = true;

                FVector DirectionToTarget = (TargetLocation - ValeriaProjectile->K2_GetActorLocation()).GetNormalized();
                FVector NewProjectileLocation = TargetLocation - (DirectionToTarget * 50.0f);

                FHitResult HitResult;

                ValeriaProjectile->K2_SetActorLocation(TargetLocation, false, &HitResult, false);
                ValeriaProjectile->HitActorAccordingToServer = BestTargetActor;
                HasHit = true;
            }
        }
    }
}

void AimDetours::ClientTravelInternal(const UObject* Context, UFunction* Function, void* Parms) {
    BestScore = 0.0f;
    BestTargetActorAnimal = nullptr;
    BestTargetActor = nullptr;
    BestTargetActorType = EType::MAX;
    BestTargetLocation = { 0, 0, 0 };
    BestTargetRotation = { 0, 0, 0 };

    AimOffset = { -1.5, -1.35, 0 };
    
    // Reset anti-flicker variables
    LastTargetChangeTime = std::chrono::steady_clock::now();
    PreviousTargetActor = nullptr;
}

void AimDetours::Func_DoAimbot(const UObject* Context, UFunction* Function, void* Parms) {
    if (!Configuration::bEnableAimbot)
        return;

    const auto PlayerController = GetPlayerController();
    if (!PlayerController || !IsActorValid(PlayerController))
        return;

    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter || !IsActorValid(ValeriaCharacter))
        return;

    // Check if overlay is showing or game window is not active
    auto Overlay = static_cast<PaliaOverlay*>(OverlayBase::Instance);
    if (!Overlay || Overlay->ShowOverlay())
        return;

    // Get target from the existing targeting system
    AActor* TargetActor = BestTargetActor;
    if (!TargetActor || !IsActorValid(TargetActor))
        return;

    // Only target animals if the setting is enabled
    if (BestTargetActorType != EType::Animal)
        return;

    // Check if the target should be shown in ESP (this respects the ESP toggles)
    bool bShouldTarget = false;
    for (auto& Entry : ActorHandler::GetActors()) {
        if (Entry->Actor == TargetActor) {
            bShouldTarget = Entry->ShouldShow(ValeriaCharacter);
            break;
        }
    }
    
    if (!bShouldTarget)
        return;

    FVector BestTargetLocation = AimDetours::BestTargetLocation;

    const auto CameraManager = PlayerController->PlayerCameraManager;
    if (!CameraManager || !IsActorValid(CameraManager))
        return;

    FVector CameraLocation = CameraManager->GetCameraLocation();
    FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, BestTargetLocation);
    FRotator CurrentControlRotation = PlayerController->GetControlRotation();

    // Check if aimbot key is held
    bool bAimbotKeyHeld = (GetAsyncKeyState(Configuration::AimbotKey) & 0x8000) != 0;
    
    if (!bAimbotKeyHeld)
        return;

    // Apply smoothing
    float SmoothingFactor = UKismetMathLibrary::Clamp(Configuration::AimbotSmoothing, 1.0f, 100.0f);
    
    if (SmoothingFactor == 1.0f) {
        // Instant aim
        PlayerController->SetControlRotation(TargetRotation);
    }
    else {
        // Smooth aim
        float InterpSpeed = UKismetMathLibrary::MapRangeClamped(SmoothingFactor, 1.0f, 100.0f, 25.0f, 1.0f);
        float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(SDK::UWorld::GetWorld());
        FRotator SmoothedRotation = UKismetMathLibrary::RInterpTo(CurrentControlRotation, TargetRotation, DeltaTime, InterpSpeed);
        
        PlayerController->SetControlRotation(SmoothedRotation);
    }
}