#include "ESP.h"
#include "Configuration.h"
#include "ActorHandler.h"
#include "WidgetHandler.h"
#include "AimDetours.h"
#include "Utils.h"
#include "SDKExt.h"
#include "ImGuiExt.h"
#include "PaliaOverlay.h"
#include <OverlayBase.h>
#include <imgui_internal.h>
#include <Fonts.h>
#include <Windows.h>
#include <algorithm>
#include <unordered_set>

#ifdef ENABLE_SUPPORTER_FEATURES
#include "Gardening.h"
#endif

using namespace SDK;

namespace PaliaESP {

    void DisplayModsCategory(const std::string& title, const std::vector<std::pair<std::string, bool>>& mods) {
        bool hasMods = std::ranges::any_of(mods, [](const auto& mod) {
            return mod.second;
        });
        if (hasMods) {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.5f, 0.9f, 1.0f));
            ImGui::Text("%s", title.c_str());
            ImGui::PopStyleColor();
            ImGui::Spacing();
    
            for (const auto& mod : mods) {
                if (mod.second) {
                    ImGui::BulletText("%s", mod.first.c_str());
                }
            }
        }
    }
    
    void DrawEnabledFeatures() {
        if (!Configuration::showEnabledFeaturesWindow)
            return;
    
        AValeriaCharacter* ValeriaCharacter = GetValeriaCharacter();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize;
    
        auto initialPos = ImVec2(Configuration::activeWindowPosX, Configuration::activeWindowPosY);
    
        ImGui::SetNextWindowPos(initialPos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    
        if (ImGui::Begin("Active Mods", &Configuration::showEnabledFeaturesWindow, window_flags)) {
            if (ValeriaCharacter) {
                DisplayModsCategory(ICON_FA_GLOBE "Global Mods", {
                                        {"AntiAFK", Configuration::bEnableAntiAfk},
                                        {"Content Unlocker", Configuration::bEnableOutfitCustomization},
                                        {"Cooking Mods", Configuration::bEnableCookingMinigameSkip},
                                        {"Interaction Mods", Configuration::bEnableInteractionMods},
                                        {"Request Mods", Configuration::bEnableRequestMods},
                                        {"PrizeWheel Mods", Configuration::bEnablePrizeWheel},
                                        {"Auto-Gathering", Configuration::bEnableAutoGather},
                                        {"Auto Refill Focus", Configuration::bEnableAutoFocus}
                                    });
    
                DisplayModsCategory(ICON_FA_EYE "ESP & Visuals", {
                                        {"ESP", Configuration::bEnableESP},
                                        {"ESP Icons", Configuration::bEnableESPIcons},
                                        {"InteliAim Circle", Configuration::bEnableInteliAim}
                                    });
    
                DisplayModsCategory(ICON_FA_CROSSHAIRS "Aiming & Tools", {
                                        {"Silent Aimbot", Configuration::bEnableSilentAimbot},
                                        {"Auto-Hunting", Configuration::bEnableAnimalHunting},
                                        {"Auto-Catching", Configuration::bEnableBugCatching},
                                        {"Fast-Tools", Configuration::bEnableAutoSwinging},
                                    });
    
                DisplayModsCategory(ICON_FA_PERSON_WALKING "Teleport & Move", {
                                        {"TP to Targeted", Configuration::bTeleportToTargeted},
                                        {"TP to Waypoint", Configuration::bEnableWaypointTeleport},
                                        {"TP Avoid Players", Configuration::bAvoidTeleportingToPlayers},
                                    });
    
                DisplayModsCategory(ICON_FA_FISH "Fishing", {
                                        {"No Rod Durability", Configuration::bFishingNoDurability},
                                        {"Fishing MP Help", Configuration::bFishingMultiplayerHelp},
                                        {"Perfect Catch", Configuration::bFishingPerfectCatch},
                                        {"Instant Catch", Configuration::bFishingInstantCatch},
                                        {"Sell All Fish", Configuration::bFishingSell},
                                        {"Left Click Fishing", Configuration::bRequireClickFishing}
                                    });
    
                DisplayModsCategory(ICON_FA_HOUSE "Housing", {
                                        {"Advanced Placement", Configuration::bPlaceAnywhere}
                                    });
                
    #ifdef ENABLE_SUPPORTER_FEATURES
                if (ActorHandler::CurrentMap == EValeriaLevel::Home) {
                    ImGui::Spacing();
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.5f, 0.9f, 1.0f));
                    ImGui::Text(ICON_FA_SEEDLING "Gardening");
                    ImGui::PopStyleColor();
                    ImGui::Spacing();
    
                    try {
                        auto gardenInfo = Gardening::GetInfo();
                        for (const auto& entry : gardenInfo) {
                            if (!entry.empty()) {
                                ImGui::BulletText("%s", entry.c_str());
                            }
                        }
                    } catch (const std::exception& e) {
                        ImGui::BulletText("Error loading garden info: %s", e.what());
                    } catch (...) {
                        ImGui::BulletText("Unknown error loading garden info");
                    }
                }
    #endif
            } else {
                ImGui::Text("Waiting for in-game...");
            }
    
            ImVec2 currentPos = ImGui::GetWindowPos();
            if (!AreFloatsEqual(currentPos.x, Configuration::activeWindowPosX) || !AreFloatsEqual(currentPos.y, Configuration::activeWindowPosY)) {
                Configuration::activeWindowPosX = currentPos.x;
                Configuration::activeWindowPosY = currentPos.y;
                Configuration::Save(ESaveFile::OverlaySettings);
            }
    
            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar();
            ImGui::End();
        }
    }
    
    void DrawGuiFOVCircle() {
        if (!Configuration::bEnableInteliAim || WidgetHandler::IsWidgetOpen()) return;
    
        const auto PlayerController = GetPlayerController();
        if (!PlayerController) return;
    
        if (!PlayerController->K2_GetPawn())
            return;
    
        FVector PawnLocation = PlayerController->K2_GetPawn()->K2_GetActorLocation();
        FVector2D PlayerScreenPosition;
        FVector2D TargetScreenPosition;
    
        if (!PlayerController->ProjectWorldLocationToScreen(PawnLocation, &PlayerScreenPosition, true))
            return;
    
        FVector2D FOVCenter = {ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f};
        if (FOVCenter.X <= 0 || FOVCenter.Y <= 0)
            return;
    
        static auto drawList = ImGui::GetBackgroundDrawList();
        if (!drawList)
            return;
    
        if (!Configuration::bHideFOVCircle) {
            ImU32 CircleColor = IM_COL32(0xff, 0xff, 0xff, static_cast<int>(Configuration::CircleAlpha * 255));
            drawList->AddCircle(ImVec2(static_cast<float>(FOVCenter.X), static_cast<float>(FOVCenter.Y)), Configuration::FOVRadius, CircleColor, 1200, 1.0f);
        }
    
        if (Configuration::bDrawCrosshair) {
            ImU32 CrosshairColor = IM_COL32(0x7e, 0x55, 0xc0, static_cast<int>(Configuration::CircleAlpha * 255));
            drawList->AddCircleFilled(ImVec2(static_cast<float>(FOVCenter.X), static_cast<float>(FOVCenter.Y)), 3.0f, CrosshairColor, 60);
        }
    
        if (AimDetours::BestTargetLocation.IsZero())
            return;
        if (!PlayerController->ProjectWorldLocationToScreen(AimDetours::BestTargetLocation, &TargetScreenPosition, true))
            return;
        if (CustomMath::DistanceBetweenPoints(TargetScreenPosition, FOVCenter) > Configuration::FOVRadius)
            return;
    
        ImU32 TargetLineColor = IM_COL32(0xff, 0xff, 0xff, static_cast<int>(Configuration::CircleAlpha * 255));
        drawList->AddLine(ImVec2(static_cast<float>(FOVCenter.X), static_cast<float>(FOVCenter.Y)), ImVec2(static_cast<float>(TargetScreenPosition.X), static_cast<float>(TargetScreenPosition.Y)), TargetLineColor, 0.5f);
    
        // Drawing a purple circle at the end of the line
        ImU32 EndCircleColor = IM_COL32(0x40, 0x19, 0x80, static_cast<int>(Configuration::CircleAlpha * 255));
        drawList->AddCircleFilled(ImVec2(static_cast<float>(FOVCenter.X), static_cast<float>(FOVCenter.Y)), 2.0f, EndCircleColor, 60);
    }

    void DrawGuiESP() {
        if (!Configuration::bEnableESP || (WidgetHandler::IsWidgetOpen() && !WidgetHandler::IsMapOpen()))
            return;
        
        const auto ValeriaCharacter = GetValeriaCharacter();
        if (!ValeriaCharacter)
            return;
    
        const auto PlayerController = GetPlayerController();
        if (!PlayerController)
            return;
        
        FVector2D CanvasSize = {ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y};
    
        const auto drawList = ImGui::GetBackgroundDrawList();
        
        const auto narrowString = [](const std::wstring& wstr) -> std::string {
            if (wstr.empty())
                return {};
    
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
            std::string strTo(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr.data(), static_cast<int>(wstr.size()), strTo.data(), size_needed, nullptr, nullptr);
            return strTo;
        };
    
        // Draw ESP Names Entities
        for (auto& entry : ActorHandler::GetActors()) {
            PaliaOverlay* Overlay = static_cast<PaliaOverlay*>(OverlayBase::Instance);
            
            // Skip actors with textures if icon esp enabled;
            if (Configuration::bEnableESPIcons && !entry->TexturePath().empty() && !WidgetHandler::IsMapOpen())
                continue;
            // Skip unselected ESP resources
            if (!entry->ShouldShow(ValeriaCharacter))
                continue;
            
            if (!entry->Actor || !IsActorValid(entry->Actor) || entry->WorldPosition.IsZero())
                continue;
            
            // skip hidden actors from other sub-plots
            if ((ActorHandler::CurrentMap & EValeriaLevel::Home) && !entry->Actor->bActorEnableCollision)
                continue;
    
            if (entry->ActorType() == EType::Players) {
                if (entry->Actor == ValeriaCharacter)
                    continue; // Skip local player.
            }
    
            FVector ActorLocation = entry->WorldPosition;
    
            ActorLocation.Z += 100.0; // Adjust this value based on typical actor height
    
            if (entry->Distance > Configuration::CullDistance)
                continue;
    
            ImU32 Color = IM_COL32(0xFF, 0xFF, 0xFF, 0xFF);
    
            std::string FAIconText;
            bool isInfected = entry->Infected();
    
            std::wstring text = entry->DisplayName;
    
            switch (entry->ActorType()) {
            case EType::Forage:
                if (auto it = Configuration::ForageableColors.find(static_cast<FEntryGatherable::TypeEnum>(entry->Type())); it != Configuration::ForageableColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_LEAF;
                break;
            case EType::Ore:
                if (auto it = Configuration::OreColors.find(static_cast<FEntryMining::TypeEnum>(entry->Type())); it != Configuration::OreColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_GEM;
                break;
            case EType::Players:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Player); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_USER;
                break;
            case EType::Animal:
                if (auto it = Configuration::AnimalColors.find(FCreatureType{static_cast<FEntryHunting::TypeEnum>(entry->Type()), static_cast<FEntryHunting::VariantEnum>(entry->Variant())}); it != Configuration::AnimalColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_PAW;
                break;
            case EType::Tree:
                if (auto it = Configuration::TreeColors.find(static_cast<FEntryLumber::TypeEnum>(entry->Type())); it != Configuration::TreeColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_TREE;
                break;
            case EType::Bug:
                if (auto it = Configuration::BugColors.find(FBugType{static_cast<FEntryBug::TypeEnum>(entry->Type()), static_cast<FEntryBug::VariantEnum>(entry->Variant())}); it != Configuration::BugColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_BUG;
                if (entry->Quality() == 1) {
                    FAIconText = ICON_FA_BUG;
                }
                break;
            case EType::NPCs:
                if (auto it = Configuration::SingleColors.find(EOneOffs::NPC); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_PERSON;
                break;
            case EType::Loot:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Loot); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_SACK;
                break;
            case EType::Quest:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Quest); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_LOCATION_DOT;
                break;
            case EType::RummagePiles:
                if (auto it = Configuration::SingleColors.find(EOneOffs::RummagePiles); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_BALL_PILE;
                if (entry->Variant() > 0) {
                    std::wstring prefix = L"Rummage Pile - ";
                    text.insert(0, prefix);
                }
                break;
            case EType::Stables:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Stables); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_TORII_GATE;
                break;
            case EType::Fish:
                if (auto it = Configuration::SingleColors.find(EOneOffs::FishHook); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_FISH;
            case EType::Pool:
                if (auto it = Configuration::SingleColors.find(EOneOffs::FishPool); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_FISHING_ROD;
                break;
            case EType::Treasure:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Treasure); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_TREASURE_CHEST;
                break;
            case EType::TimedDrop:
                if (auto it = Configuration::SingleColors.find(EOneOffs::TimedDrop); it != Configuration::SingleColors.end())
                    Color = it->second;
                if (entry->Variant() > 1) {
                    FAIconText = ICON_FA_SQUARE_QUESTION;
                }
                break;
            case EType::Relic:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Relic); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_BOOK;
                break;
            case EType::Shops:
                if (auto it = Configuration::SingleColors.find(EOneOffs::Decor); it != Configuration::SingleColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_STORE;
            case EType::Bubble:
                if (auto it = Configuration::AnimalColors.find(FCreatureType{static_cast<FEntryHunting::TypeEnum>(entry->Type()), static_cast<FEntryHunting::VariantEnum>(entry->Variant())}); it != Configuration::AnimalColors.end())
                    Color = it->second;
                FAIconText = ICON_FA_BALLOON;
            default:
                break;
            }
    
            FVector2D ScreenLocation;
            if (WidgetHandler::IsMapOpen()) {
                if (!Configuration::bEnableMapESP) continue;
                if ((EType::NPCs | EType::Stables) & entry->ActorType()) continue; // Don't need to draw NPCs/Stables on map, they have their own icons
                if (auto LocationPair = WidgetHandler::GetMapPoint(ActorLocation); LocationPair.first) {
                    float mousePosX;
                    float mousePosY;
                    auto textSize = ImGui::CalcTextSize(FAIconText.c_str());
                    auto TextPosition = ImVec2(static_cast<float>(LocationPair.second.X - textSize.x / 2),
                                               static_cast<float>(LocationPair.second.Y - textSize.y / 2));
    
                    // Use ESPFont directly without push/pop for better performance
                    drawTextOutlined(drawList, TextPosition, Color, FAIconText.c_str(), OverlayBase::Instance->ESPFont);
    
                    std::string shortText = narrowString(text);
    
                    ImVec2 tooltipTextSize = ImGui::CalcTextSize(shortText.c_str());
    
                    ImVec2 textMin = TextPosition;
                    ImVec2 textMax = ImVec2(TextPosition.x + textSize.x, TextPosition.y + textSize.y);
    
                    if (PlayerController->GetMousePosition(&mousePosX, &mousePosY)) {
                        if (mousePosX >= textMin.x && mousePosX <= textMax.x && mousePosY >= textMin.y && mousePosY <= textMax.y) {
                            ImVec2 tooltipPos = ImVec2(mousePosX - tooltipTextSize.x / 2, mousePosY - tooltipTextSize.y - 10.0f);
                            /*drawList->AddRect(ImVec2(tooltipPos.x - 4, tooltipPos.y - 2), ImVec2(tooltipPos.x + tooltipTextSize.x + 4, tooltipPos.y + tooltipTextSize.y + 2), IM_COL32(0x18, 0x18, 0x30, 0x45), 2.0f);
                            drawList->AddRectFilled(ImVec2(tooltipPos.x - 4, tooltipPos.y - 2), ImVec2(tooltipPos.x + tooltipTextSize.x + 4, tooltipPos.y + tooltipTextSize.y + 2), IM_COL32(0x18, 0x18, 0x30, 0x26), 2.0f);*/
                            drawTextOutlined(drawList, tooltipPos, Color, shortText.c_str(), OverlayBase::Instance->FontDefault);
                        }
                    }
                }
            } else {
                try {
                    if (PlayerController->ProjectWorldLocationToScreen(ActorLocation, &ScreenLocation, true)) {
                        if (ScreenLocation.X < 0 || ScreenLocation.Y < 0 || ScreenLocation.X > CanvasSize.X || ScreenLocation.Y > CanvasSize.Y)
                            continue;
                        // Construct text string
    
                        // Prepare text with optional parts depending on the index values
                        if (Configuration::bEnableESPDistance) {
                            text += std::format(L" [{:.0f}m]", entry->Distance);
                        }
                        if (Configuration::bEnableESPDespawnTimer) {
                            if (entry->Despawn > 0) {
                                text += std::format(L" {:.0f}s", entry->Despawn);
                            }
                        }
    
                        std::string shortText = FAIconText + " " + narrowString(text);
                        if (isInfected) {
                            std::string skull = ICON_FA_BIOHAZARD;
                            shortText += "  " + skull;
                        }
    
                        float textScale = Configuration::ESPTextScale;
    
                        ImVec2 textSize = ImGui::CalcTextSize(shortText.c_str());
                        textSize.x *= textScale;
                        textSize.y *= textScale;
    
                        auto TextPosition = ImVec2(static_cast<float>(ScreenLocation.X - textSize.x / 2), static_cast<float>(ScreenLocation.Y - textSize.y / 2));
    
                        // Constrain text to screen before disappearing.
                        if (TextPosition.x < 4.0f) { // left side
                            TextPosition.x = 4.0f;
                        } else if (TextPosition.x + textSize.x > CanvasSize.X) { // right side
                            TextPosition.x = static_cast<float>(CanvasSize.X) - textSize.x;
                        }
                        if (TextPosition.y < 4.0f) { // top side
                            TextPosition.y = 4.0f;
                        } else if (TextPosition.y + textSize.y > CanvasSize.Y - 4.0f) { // bottom side
                            TextPosition.y = static_cast<float>(CanvasSize.Y) - textSize.y - 4.0f;
                        }
    
                        drawTextOutlined(drawList, TextPosition, Color, shortText.c_str(), OverlayBase::Instance->ESPFont);
                    }
                } catch (std::exception& e) {
                    std::cout << "ProjectWorldLocationToScreen exception: " << e.what() << "\n";
                }
            }
        }
    }

} // namespace PaliaESP
