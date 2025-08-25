#pragma once

#include "PaliaOverlay.h"
#include "Configuration.h"
#include "HUDDetours.h"
#include "MovementDetours.h"
#include "TeleportDetours.h"
#include "ImGuiExt.h"
#include "LocalizationManager.h"

#include "Utils.h"
#include "imgui.h"

std::vector<FLocation> TeleportLocations = {
    // Global Home
    {"UserDefined", ELocation::Global_Home, "[Global] Housing Plot", {00000.000f, 00000.000f, 00000.000}, {0.000f, 0.00f, 0.000f}},
    // Kilima City Spots
    {"Kilima Valley", ELocation::Kilima_GeneralStore, "[Kilima] General Store", {156.193f, -1509.144f, 305.576}, {0.000f, -122.07f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_TailorStore, "[Kilima] Tailor Store", {-1715.341f, 2052.674f, 163.455}, {0.000f, -123.346f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_FurnitureStore, "[Kilima] Furniture Store", {3734.435f, -563.303f, 161.163}, {0.000f, -122.006f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_CityHall, "[Kilima] City Hall", {6344.635f, 2519.250f, 511.920}, {0.000f, 0.451f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_Tavern, "[Kilima] Tavern", {-755.001f, 4102.823f, 330.888}, {0.000f, 120.090f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_RepairStation, "[Kilima] Repair Station", {2465.246f, 6734.343f, 323.050}, {0.000f, 120.89f, 0.000f}},
    // Kilima Entrances
    {"Kilima Valley", ELocation::Kilima_HousingPlot, "[Kilima] Housing Plot Entrance", {20204.810f, -15375.620f, 2272.460}, {0.000f, -6.24f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_ToBahariBay, "[Kilima] Bahari Bay Entrance", {50623.753f, -5403.530f, 1332.610}, {0.000f, -24.72f, 0.000f}},
    // Kilima Stables
    {"Kilima Valley", ELocation::Kilima_CentralStables, "[Kilima] Central Stables", {9746.436f, 11380.740f, -119.406}, {0.000f, 145.62f, -0.000f}},
    {"Kilima Valley", ELocation::Kilima_MirrorFields, "[Kilima] Mirror Fields", {-6586.737f, -24412.872f, 1647.018}, {0.000f, 259.87f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_LeafhopperHills, "[Kilima] Leafhopper Hills", {-21589.245f, 3920.281f, 326.105}, {0.000f, 117.04f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_WhisperingBanks, "[Kilima] Whispering Banks", {38958.433f, 7574.109f, -657.983}, {0.000f, 214.71f, 0.000f}},
    // Kilima Others
    {"Kilima Valley", ELocation::Kilima_Fairgrounds_MajiMarket, "[Kilima] Fairgrounds Entrance (Maji Market)", {54696.812f, 21802.943f, -94.603}, {0.000f, -7.65f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_PhoenixFalls, "[Kilima] Phoenix Falls", {7596.145f, -51226.853f, 4026.341}, {0.000f, -68.64f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_DragonShrine, "[Kilima] Dragon Shrine", {33743.980f, -22253.369f, 1323.870}, {0.000f, -90.211f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_FishermansLagoon, "[Kilima] Fisherman's Lagoon", {25325.044f, 19246.651f, -439.559}, {0.000f, 25.76f, 0.000f}},
    {"Kilima Valley", ELocation::Kilima_WimsFishingSpot, "[Kilima] Wims Secret Fishing Spot", {58217.884f, 41798.154f, -432.593}, {0.000f, 94.089f, 0.000f}},
    // Bahari Entrances 
    {"Bahari Bay", ELocation::Bahari_HousingPlot, "[Bahari] Housing Plot Entrance", {54451.777f, -81603.203f, 962.742}, {0.000f, 2.45f, 0.000f}},
    {"Bahari Bay", ELocation::Bahari_ToKilimaValley, "[Bahari] Kilima Valley Entrance", {59457.644f, -10932.726f, 917.334}, {0.000f, -157.46f, 0.000f}},
    // Bahari Stables
    {"Bahari Bay", ELocation::Bahari_CentralStables, "[Bahari] Central Stables", {103331.330f, -63125.339f, -1928.051}, {0.000f, 148.09f, -0.000f}},
    {"Bahari Bay", ELocation::Bahari_TheOutskirts, "[Bahari] The Outskirts", {55743.927f, -81821.534f, 922.205}, {0.000f, 226.06f, 0.000f}},
    {"Bahari Bay", ELocation::Bahari_CoralShores, "[Bahari] Coral Shores", {143344.052f, -71851.374f, -4353.302}, {0.000f, 352.16f, 0.000f}},
    {"Bahari Bay", ELocation::Bahari_PulsewaterPlains, "[Bahari] Pulsewater Plains", {101257.267f, -23873.064f, -1635.604}, {0.000f, 287.12f, 0.000f}},
    {"Bahari Bay", ELocation::Bahari_HideawayBluffs, "[Bahari] Hideaway Bluffs", {82490.721f, 2994.478f, -694.785}, {0.000f, 14.61f, 0.000f}},
    {"Bahari Bay", ELocation::Bahari_BeachcomberCove, "[Bahari] Beachcomber Cove", {128767.154f, 4163.842f, -4386.759}, {0.000f, 312.00f, 0.000f}}
};

namespace Movement_TeleportSettings {
    inline void Show() {
        AValeriaCharacter* ValeriaCharacter = GetValeriaCharacter();
        UValeriaCharacterMoveComponent* MovementComponent = nullptr;
        if (ValeriaCharacter) {
            MovementComponent = ValeriaCharacter->GetValeriaCharacterMovementComponent();
        }

        // Movement settings column
        if (ImGui::CollapsingHeader(LOC("header.movement_settings").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (IsComponentValid(MovementComponent)) {
                IMGUI_CHECKBOX(LOC("checkbox.enable_noclip").c_str(), &MovementDetours::bEnableNoclip, LOC("tooltip.enable_noclip").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)
                IMGUI_CHECKBOX(LOC("checkbox.enable_spinbot").c_str(), &MovementDetours::bEnableSpinbot, LOC("tooltip.enable_spinbot").c_str(), ImGui::CheckboxHotkeyFlags::HOTKEY)

                if(MovementDetours::bEnableSpinbot) {
                    ImGui::SetNextItemWidth(200.0f);
                    IMGUI_SLIDER(LOC("slider.spinbot_speed").c_str(), &MovementDetours::SpinSpeed, 1.0f, 1000.0f, "%50.0f", LOC("tooltip.spinbot_speed").c_str())
                }

                // Create a combo box for selecting the movement mode - update strings each time to reflect current language
                std::string walking = LOC("text.walking");
                std::string flying = LOC("text.flying");
                std::string flyNoCollision = LOC("text.fly_no_collision");
                const char* movementModes[] = {walking.c_str(), flying.c_str(), flyNoCollision.c_str()};
                ImGui::Text(LOC("text.movement_mode").c_str());
                ImGui::SetNextItemWidth(200.0f);
                if (ImGui::BeginCombo("##MovementMode", movementModes[MovementDetours::currentMovementModeIndex])) {
                    for (int n = 0; n < IM_ARRAYSIZE(movementModes); n++) {
                        const bool isSelected = MovementDetours::currentMovementModeIndex == n;
                        if (ImGui::Selectable(movementModes[n], isSelected)) {
                            MovementDetours::currentMovementModeIndex = n;
                        }
                        // Set the initial focus when opening the combo
                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::SameLine();
                // Button to apply the selected movement mode
                if (ImGui::Button(LOC("button.set_movement").c_str())) {
                    switch (MovementDetours::currentMovementModeIndex) {
                    case 0: // Walking
                        MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking, 1);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
                        break;
                    case 1: // Swimming
                        MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying, 4);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
                        break;
                    case 2: // Noclip
                        MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying, 5);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
                        ValeriaCharacter->CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Destructible, ECollisionResponse::ECR_Ignore);
                        break;
                    default:
                        break;
                    }
                }

                constexpr float f1000 = 1000.0f, f5 = 5.f, f1 = 1.f;
                constexpr int i1 = 1;
                //constexpr int i1000 = 1000, i5 = 5,

                // Global Game Speed with slider
                ImGui::Text(LOC("text.global_game_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##GlobalGameSpeed", ImGuiDataType_Float, &MovementDetours::CustomGameSpeed, &f1, &f1000, "%.2f", ImGuiInputTextFlags_None)) {
                    UWorld* World = UWorld::GetWorld();
                    if (World) {
                        static_cast<UGameplayStatics*>(UGameplayStatics::StaticClass()->DefaultObject)->SetGlobalTimeDilation(World, MovementDetours::CustomGameSpeed);
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("R##GlobalGameSpeed")) {
                    MovementDetours::CustomGameSpeed = MovementDetours::GameSpeed;
                    UWorld* World = UWorld::GetWorld();
                    if (World) {
                        static_cast<UGameplayStatics*>(UGameplayStatics::StaticClass()->DefaultObject)->SetGlobalTimeDilation(World, MovementDetours::GameSpeed);
                    }
                }

                // Walk Speed
                ImGui::Text(LOC("text.walk_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##WalkSpeed", ImGuiDataType_Float, &Configuration::CustomWalkSpeed, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##WalkSpeed")) {
                    Configuration::CustomWalkSpeed = MovementDetours::WalkSpeed;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Sprint Speed
                ImGui::Text(LOC("text.sprint_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##SprintSpeedMultiplier", ImGuiDataType_Float, &Configuration::CustomSprintSpeed, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##SprintSpeedMultiplier")) {
                    Configuration::CustomSprintSpeed = MovementDetours::SprintSpeedMultiplier;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Climbing Speed
                ImGui::Text(LOC("text.climbing_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##ClimbingSpeed", ImGuiDataType_Float, &Configuration::CustomClimbingSpeed, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##ClimbingSpeed")) {
                    Configuration::CustomClimbingSpeed = MovementDetours::ClimbingSpeed;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Gliding Speed
                ImGui::Text(LOC("text.gliding_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##GlidingSpeed", ImGuiDataType_Float, &Configuration::CustomGlidingSpeed, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##GlidingSpeed")) {
                    Configuration::CustomGlidingSpeed = MovementDetours::GlidingSpeed;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Gliding Fall Speed
                ImGui::Text(LOC("text.gliding_fall_speed").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##GlidingFallSpeed", ImGuiDataType_Float, &Configuration::CustomGlidingFallSpeed, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##GlidingFallSpeed")) {
                    Configuration::CustomGlidingFallSpeed = MovementDetours::GlidingFallSpeed;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Jump Velocity
                ImGui::Text(LOC("text.jump_velocity").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##JumpVelocity", ImGuiDataType_Float, &Configuration::CustomJumpVelocity, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##JumpVelocity")) {
                    Configuration::CustomJumpVelocity = MovementDetours::JumpVelocity;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Max Jump Count
                ImGui::Text(LOC("text.max_jumps").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##MaxJumpAmount", ImGuiDataType_S32, &Configuration::CustomMaxJumps, &i1)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##MaxJumpAmount")) {
                    Configuration::CustomMaxJumps = MovementDetours::JumpMaxCount;
                    Configuration::Save(ESaveFile::MovementSettings);
                }

                // Step Height
                ImGui::Text(LOC("text.step_height").c_str());
                ImGui::SetNextItemWidth(325.0f);
                if (ImGui::InputScalar("##MaxStepHeight", ImGuiDataType_Float, &Configuration::CustomMaxStepHeight, &f5)) {
                    Configuration::Save(ESaveFile::MovementSettings);
                }
                ImGui::SameLine();
                if (ImGui::Button("R##MaxStepHeight")) {
                    Configuration::CustomMaxStepHeight = MovementDetours::MaxStepHeight;
                    Configuration::Save(ESaveFile::MovementSettings);
                }
            } else {
                if (!ValeriaCharacter) {
                    ImGui::Text(LOC("text.waiting_character_init").c_str());
                } else {
                    ImGui::Text("Movement component not available.");
                }
            }
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader(LOC("header.locations_coordinates").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ValeriaCharacter) {
                // Locations and exploits column
                ImGui::Text(LOC("text.teleport_list").c_str());
                ImGui::Text(LOC("text.double_click_teleport").c_str());
                if (ImGui::BeginListBox("##TeleportList", ImVec2(-1, 150))) {
                    for (auto& [MapName, Type, Name, Location, Rotate] : TeleportLocations) {
                        if (EValeriaLevelString[ActorHandler::CurrentMap] == MapName || MapName == "UserDefined") {
                            if (ImGui::Selectable(Name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
                                if (ImGui::IsMouseDoubleClicked(0)) {
                                    if (Type == ELocation::Global_Home) {
                                        ValeriaCharacter->GetTeleportComponent()->RpcServerTeleport_Home();
                                    } else {
                                        TeleportDetours::TeleportPlayer(Location);
                                    }
                                    // show = false;
                                }
                            }
                        }
                    }
                    ImGui::EndListBox();
                } else {
                    ImGui::Text("Not enough space to display the list.");
                }

                ImGui::Text("%s: %s", LOC("text.map").c_str(), EValeriaLevelString[ActorHandler::CurrentMap].c_str());
                
                auto [PlayerX, PlayerY, PlayerZ] = ValeriaCharacter->K2_GetActorLocation();
                ImGui::Text("%s: %.3f, %.3f, %.3f", LOC("text.current_coords").c_str(), PlayerX, PlayerY, PlayerZ);
                ImGui::Spacing();

                // Set the width for the labels and inputs
                constexpr float labelWidth = 50.0f;
                constexpr float inputWidth = 200.0f;

                // 
                static FVector TeleportLocation;
                //static FRotator TeleportRotate;

                constexpr double d5 = 5., d1 = 1.;

                // X Coordinate
                ImGui::AlignTextToFramePadding();
                ImGui::Text("X: ");
                ImGui::SameLine(labelWidth);
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::InputScalar("##TeleportLocationX", ImGuiDataType_Double, &TeleportLocation.X, &d5);

                // Y Coordinate
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Y: ");
                ImGui::SameLine(labelWidth);
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::InputScalar("##TeleportLocationY", ImGuiDataType_Double, &TeleportLocation.Y, &d5);

                // Z Coordinate
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Z: ");
                ImGui::SameLine(labelWidth);
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::InputScalar("##TeleportLocationZ", ImGuiDataType_Double, &TeleportLocation.Z, &d5);

                // // Yaw
                // ImGui::AlignTextToFramePadding();
                // ImGui::Text("YAW: ");
                // ImGui::SameLine(labelWidth);
                // ImGui::SetNextItemWidth(inputWidth);
                // ImGui::InputScalar("##TeleportRotateYaw", ImGuiDataType_Double, &TeleportRotate.Yaw, &d1);

                ImGui::Spacing();

                if (ImGui::Button(LOC("button.get_current_coordinates").c_str())) {
                    TeleportLocation = ValeriaCharacter->K2_GetActorLocation();
                    //TeleportRotate = ValeriaCharacter->K2_GetActorRotation();
                }
                ImGui::SameLine();
                if (ImGui::Button(LOC("button.teleport_to_coordinates").c_str())) {
                    TeleportDetours::TeleportPlayer(TeleportLocation);
                }
                // Travel
                ImGui::Text(LOC("text.travel_list").c_str());
                ImGui::Text(LOC("text.double_click_travel").c_str());
                if (ImGui::BeginListBox("##TravelList", ImVec2(-1, 150))) {
                    for (auto& [Name, TeleportActor] : ActorHandler::GetTeleporters(ValeriaCharacter)) {
                        if (ImGui::Selectable(Name.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
                            if (ImGui::IsMouseDoubleClicked(0)) {
                                auto Teleporter = static_cast<AVAL_TeleporterBase*>(TeleportActor);
                                Teleporter->Client_ExecuteTeleport(ValeriaCharacter);
                                // show = false;
                            }
                        }
                    }
                    ImGui::EndListBox();
                } else {
                    ImGui::Text("Not enough space to display the list.");
                }
            } else {
                ImGui::Text(LOC("text.waiting_character_init").c_str());
            }
        }
    }
}
