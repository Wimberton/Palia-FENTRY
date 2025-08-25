#include "MovementDetours.h"
#include "Configuration.h"
#include "DetourManager.h"
#include "PaliaOverlay.h"
#include "SDKExt.h"
#include "Utils.h"

#include "functional"
#include <fstream>
#include <chrono>

#include <SDK/Palia_parameters.hpp>

using namespace SDK;

std::chrono::steady_clock::time_point MovementDetours::LastTickTime = std::chrono::steady_clock::now();

void MovementDetours::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
    LastTickTime = std::chrono::steady_clock::now();

    DetourManager::AddInstance(VC);
	DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Func_DoNoClip, nullptr);
    DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Func_DoSpinbot, nullptr);
	DetourManager::AddFunctionListener("Function Engine.Actor.ReceiveTick", &Func_DoPersistentMovement, nullptr);
    DetourManager::AddInstance(VC->GetValeriaCharacterMovementComponent());
	DetourManager::AddFunctionListener("Function Palia.ValeriaClientPriMovementComponent.RpcServer_SendMovement", &Func_SendMovement, nullptr);
}

void MovementDetours::Func_DoSpinbot(const UObject* Context, UFunction* Function, void* Parms) {
    if (!bEnableSpinbot)
        return;

    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    ValeriaCharacter->SetActorTickInterval(0.01f);

    UValeriaCharacterMoveComponent* ValeriaMovementComponent = ValeriaCharacter->GetValeriaCharacterMovementComponent();
    if (!IsComponentValid(ValeriaMovementComponent))
        return;

    FRotator CurrentRotation = ValeriaCharacter->K2_GetActorRotation();

    auto Now = std::chrono::steady_clock::now();
    std::chrono::duration<float> ElapsedTime = Now - LastTickTime;
    LastTickTime = Now;
    float DeltaTime = ElapsedTime.count();

    float MaxYawChange = 180.0f;
    float YawChange = SpinSpeed * DeltaTime;

    if (YawChange > MaxYawChange) {
        YawChange = MaxYawChange;
    }

    CurrentRotation.Yaw += YawChange;

    ValeriaCharacter->K2_SetActorRotation(CurrentRotation, false);
}

void MovementDetours::Func_DoNoClip(const UObject* Context, UFunction* Function, void* Parms) {
    if (!bEnableNoclip && bEnableNoclip == bPreviousNoclipState)
        return;

    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    UValeriaCharacterMoveComponent* ValeriaMovementComponent = ValeriaCharacter->GetValeriaCharacterMovementComponent();
    if (!IsComponentValid(ValeriaMovementComponent))
        return;

    FVector ZeroVec(0, 0, 0);

    if (bEnableNoclip != bPreviousNoclipState) {
        if (bEnableNoclip) {
            ValeriaMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying, 5);

            // Not home
            if (ActorHandler::CurrentMap != EValeriaLevel::Home) {
                ValeriaCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
            }
            // At home
            else {
                //ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);     // Collision w/ static objs
                ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);     // Ignore dynamic objs
                ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);             // Ignore pawns actors
                ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);      // Ignore physics bodies
            }
        }
        // Disabled
        else {
            ValeriaMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking, 1);
            ValeriaCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
            ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
        }

        bPreviousNoclipState = bEnableNoclip;
    }

    // Logic for Noclip Camera
    if (bEnableNoclip) {
        if (!IsGameWindowActive())
            return;

        const auto PlayerController = GetPlayerController();
        if (!PlayerController)
            return;

        const FRotator& CameraRot = PlayerController->PlayerCameraManager->GetCameraRotation();

        FVector CameraForward = UKismetMathLibrary::GetForwardVector(CameraRot);
        FVector CameraRight = UKismetMathLibrary::GetRightVector(CameraRot);
        constexpr FVector CameraUp = { 0.f, 0.f, 1.f };

        CameraForward.Normalize();
        CameraRight.Normalize();

        FVector MovementDirection = { 0.f, 0.f, 0.f };
        float FlySpeed = 800.0f;
        bool bIsMoving = false;

        if (FENTRY_IsKeyHeld('W')) {
            MovementDirection += CameraForward;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld('S')) {
            MovementDirection -= CameraForward;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld('D')) {
            MovementDirection += CameraRight;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld('A')) {
            MovementDirection -= CameraRight;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld(VK_SPACE)) {
            MovementDirection += CameraUp;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld(VK_CONTROL)) {
            MovementDirection -= CameraUp;
            bIsMoving = true;
        }
        if (FENTRY_IsKeyHeld(VK_SHIFT)) {
            FlySpeed *= 2.0f;
        }

        if (bIsMoving) {
            MovementDirection.Normalize();
            MovementDirection *= FlySpeed;
        }
        else {
            MovementDirection = ZeroVec;
            ValeriaMovementComponent->Velocity = ZeroVec;
        }

        constexpr float DeltaTime = 1.0f / 60.0f; // 60 FPS
        const FVector MovementDelta = MovementDirection * DeltaTime;

        FHitResult HitResult;
        ValeriaCharacter->K2_SetActorLocation(ValeriaCharacter->K2_GetActorLocation() + MovementDelta, false, &HitResult, false);
    }
}

void MovementDetours::Func_DoPersistentMovement(const UObject* Context, UFunction* Function, void* Parms) {
    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    UValeriaCharacterMoveComponent* ValeriaMovementComponent = ValeriaCharacter->GetValeriaCharacterMovementComponent();
    if (!IsComponentValid(ValeriaMovementComponent))
        return;

    ValeriaMovementComponent->MaxWalkSpeed = Configuration::CustomWalkSpeed;
    ValeriaMovementComponent->SprintSpeedMultiplier = Configuration::CustomSprintSpeed;
    ValeriaMovementComponent->ClimbingSpeed = Configuration::CustomClimbingSpeed;
    ValeriaMovementComponent->GlidingMaxSpeed = Configuration::CustomGlidingSpeed;
    ValeriaMovementComponent->GlidingFallSpeed = Configuration::CustomGlidingFallSpeed;
    ValeriaMovementComponent->JumpZVelocity = Configuration::CustomJumpVelocity;
    ValeriaMovementComponent->MaxStepHeight = Configuration::CustomMaxStepHeight;
}

void MovementDetours::Func_SendMovement(const UObject* Context, UFunction* Function, void* Parms) {
    auto sendMovement = static_cast<Params::ValeriaClientPriMovementComponent_RpcServer_SendMovement*>(Parms);
    sendMovement->MoveInfo.TargetVelocity.X = 0;
    sendMovement->MoveInfo.TargetVelocity.Y = 0;
}