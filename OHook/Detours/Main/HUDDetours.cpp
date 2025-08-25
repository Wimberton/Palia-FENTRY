#include "HUDDetours.h"
#include "Configuration.h"
#include "DetourManager.h"
#include "ActorHandler.h"
#include "WidgetHandler.h"
#include "PaliaOverlay.h"
#include "SDKExt.h"
#include "Utils.h"

#include "functional"
#include <format>

#include <SDK/Palia_parameters.hpp>

using namespace SDK;

void HUDDetours::SetupDetours(AValeriaCharacter* VC, AValeriaPlayerController* VPC) {
    DetourManager::AddInstance(VPC->MyHUD);
    DetourManager::AddFunctionListener("Function Engine.HUD.ReceiveDrawHUD", &ReceiveDrawHUD, nullptr);
}

void HUDDetours::ReceiveDrawHUD(const UObject* Context, UFunction* Function, void* Parms) {
    auto HUD = static_cast<const AHUD*>(Context);
    if (!Configuration::bEnableESP || !Configuration::bEnableESPIcons) {
        return;
    }

    if (WidgetHandler::IsWidgetOpen()) return;

    const auto ValeriaCharacter = GetValeriaCharacter();
    if (!ValeriaCharacter)
        return;

    const auto PlayerController = GetPlayerController();
    if (!PlayerController)
        return;
    
    FVector2D CanvasSize = {static_cast<float>(HUD->Canvas->SizeX), static_cast<float>(HUD->Canvas->SizeY)};

    // Draw ESP Names Entities
    // [Actor, WorldPosition, DisplayName, ActorType, Type, Quality, Variant, Distance, Texture, Despawn]
    for (const auto& Entry : ActorHandler::GetActors()) {
        if (!Entry->ShouldShow(ValeriaCharacter))
            continue;

        if (Entry->WorldPosition.IsZero() || !IsActorValid(Entry->Actor)) {
            continue;
        }

        // skip hidden actors from other sub-plots
        if ((ActorHandler::CurrentMap & EValeriaLevel::Home) && !Entry->Actor->bActorEnableCollision) continue;
        
        if (Entry->ActorType() == EType::Players) {
            if (Entry->Actor == ValeriaCharacter)
                continue;
        }
        
        FVector ActorLocation = Entry->WorldPosition;
        
        // Adjust Z coordinate for head-level display
        ActorLocation.Z += 100.0; // Adjust this value based on typical actor height

        if (Entry->Distance > Configuration::CullDistance)
            continue;

        ImU32 Color = IM_COL32(0xFF, 0xFF, 0xFF, 0xFF);

        bool bShouldDrawStar = false;
        bool bIconShouldUseColor = false;
        bool bOverlayText = false;
        std::string OverlayText;

        switch (Entry->ActorType()) {
        case EType::Forage:
            if (auto it = Configuration::ForageableColors.find(static_cast<FEntryGatherable::TypeEnum>(Entry->Type())); it != Configuration::ForageableColors.end())
                Color = it->second;
            if (Entry->Quality() == 1) {
                bShouldDrawStar = true;
            }
            break;
        case EType::Ore:
            if (auto it = Configuration::OreColors.find(static_cast<FEntryMining::TypeEnum>(Entry->Type())); it != Configuration::OreColors.end())
                Color = it->second;
            if (Entry->Type() != static_cast<uint8_t>(FEntryMining::TypeEnum::Clay)) {
                bOverlayText = true;
                OverlayText = GatherableSizeNames[Entry->Variant()+1];
            }
            break;
        case EType::Players:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Player); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::Animal:
            if (auto it = Configuration::AnimalColors.find(FCreatureType(static_cast<FEntryHunting::TypeEnum>(Entry->Type()), static_cast<FEntryHunting::VariantEnum>(Entry->Variant()))); it != Configuration::AnimalColors.end())
                Color = it->second;
            break;
        case EType::Tree:
            if (auto it = Configuration::TreeColors.find(static_cast<FEntryLumber::TypeEnum>(Entry->Type())); it != Configuration::TreeColors.end())
                Color = it->second;
            if (Entry->Type() != static_cast<uint8_t>(FEntryLumber::TypeEnum::Bush)) {
                bOverlayText = true;
                OverlayText = GatherableSizeNames[Entry->Variant()];
            }
            break;
        case EType::Bug:
            if (auto it = Configuration::BugColors.find(FBugType(static_cast<FEntryBug::TypeEnum>(Entry->Type()), static_cast<FEntryBug::VariantEnum>(Entry->Variant()))); it != Configuration::BugColors.end())
                Color = it->second;
            if (Entry->Quality() == 1) {
                bShouldDrawStar = true;
            }
            break;
        case EType::NPCs:
            if (auto it = Configuration::SingleColors.find(EOneOffs::NPC); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::Loot:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Loot); it != Configuration::SingleColors.end())
                Color = it->second;
            bIconShouldUseColor = true;
            break;
        case EType::Quest:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Quest); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::RummagePiles:
            if (auto it = Configuration::SingleColors.find(EOneOffs::RummagePiles); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::Stables:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Stables); it != Configuration::SingleColors.end())
                Color = it->second;
        case EType::Fish:
            if (auto it = Configuration::SingleColors.find(EOneOffs::FishHook); it != Configuration::SingleColors.end())
                Color = it->second;
            bIconShouldUseColor = true;
            break;
        case EType::Pool:
            if (auto it = Configuration::SingleColors.find(EOneOffs::FishPool); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::Treasure:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Treasure); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::TimedDrop:
            if (auto it = Configuration::SingleColors.find(EOneOffs::TimedDrop); it != Configuration::SingleColors.end())
                Color = it->second;
            if (Entry->Variant() > 1) {
                bOverlayText = true;
                OverlayText = std::format("{}", Entry->Variant());
            }
            break;
        case EType::Relic:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Relic); it != Configuration::SingleColors.end())
                Color = it->second;
            break;
        case EType::Shops:
            if (auto it = Configuration::SingleColors.find(EOneOffs::Decor); it != Configuration::SingleColors.end())
                Color = it->second;
            bIconShouldUseColor = true;
            break;
        case EType::Bubble:
            if (auto it = Configuration::AnimalColors.find(FCreatureType{static_cast<FEntryHunting::TypeEnum>(Entry->Type()), static_cast<FEntryHunting::VariantEnum>(Entry->Variant())}); it != Configuration::AnimalColors.end())
                Color = it->second;
            break;
        default:
            break;
        }

        FVector2D ScreenLocation;
        if (PlayerController->ProjectWorldLocationToScreen(ActorLocation, &ScreenLocation, true)) {
            if (ScreenLocation.X < 0.0 || ScreenLocation.Y < 0.0 || ScreenLocation.X > CanvasSize.X || ScreenLocation.Y > CanvasSize.Y) continue;
            if (!Roboto) {
                Roboto = reinterpret_cast<UFont*>(UObject::FindObject("Font Roboto.Roboto", EClassCastFlags::None));
                if (!Roboto)
                    continue;
            }

            // Construct text string
            std::vector<std::wstring> IconText{};
            std::wstring IconAboveText;

            if ((Entry->ActorType() == EType::RummagePiles && Entry->Variant() > 0) || Entry->ActorType() == EType::Fish || Entry->ActorType() == EType::Pool) {
                IconText.push_back(Entry->DisplayName);
            }

            if (Configuration::bEnableESPDistance) {
                if (Entry->ActorType() == EType::Players) {
                    IconAboveText = std::format(L"{} [{:.0f}m]", Entry->DisplayName, Entry->Distance);
                }
                else {
                    IconText.push_back(std::format(L"{:.0f}m", Entry->Distance));
                }
            }
            else if (Entry->ActorType() == EType::Players) {
                IconAboveText = Entry->DisplayName;
            }
            if (Configuration::bEnableESPDespawnTimer && Entry->Despawn > 0) {
                IconText.push_back(std::format(L"{:.0f}s", Entry->Despawn));
            }

            if (ScreenLocation.X - 32.0 < 0.0)
                ScreenLocation.X = 32.0;
            else if (ScreenLocation.X + 32.0 > CanvasSize.X)
                ScreenLocation.X = CanvasSize.X - 32.0;

            if (ScreenLocation.Y - 32.0 < 0.0)
                ScreenLocation.Y = 32.0;
            else if (ScreenLocation.Y + 32.0 > CanvasSize.Y)
                ScreenLocation.Y = CanvasSize.Y - 32.0;

            // ESP TEXT INFO
            double BaseScale = 1.0; // Default scale at a reference distance
            double ReferenceDistance = 100.0; // Distance at which no scaling is applied
            double ScalingFactor = 0.0; // Determines how much the scale changes with distance
            double DistanceScale;
            DistanceScale = BaseScale - ScalingFactor * (Entry->Distance - ReferenceDistance);
            DistanceScale = CustomMath::Clamp(DistanceScale, 0.5, BaseScale); // Clamp the scale to a reasonable range

            const FVector2D TextScale = { DistanceScale * (double)Configuration::ESPTextScale, DistanceScale * (double)Configuration::ESPTextScale };

            ImColor IMC(Color);
            FLinearColor TextColor = { IMC.Value.x, IMC.Value.y, IMC.Value.z, IMC.Value.w };
            
            // Setup shadow properties
            //ImColor IMCS(Color);
            //FLinearColor ShadowColor = { IMCS.Value.x, IMCS.Value.y, IMCS.Value.z, IMCS.Value.w };
            
            if (!Entry->TexturePath().empty()) {
                UTexture2D* ActorTexture = nullptr;
                ActorTexture = ActorHandler::TextureLookup(Entry->TexturePath());
                if (!ActorTexture || !ActorTexture->IsValidLowLevel()) continue;
                double ShadowXY = 36.0;
                double IconXY = 32.0;
                FVector2D TextureSize = { static_cast<double>(ActorTexture->Blueprint_GetSizeX()), static_cast<double>(ActorTexture->Blueprint_GetSizeY()) };

                double ShadowScale = max(TextureSize.X, TextureSize.Y) / ShadowXY / (double)Configuration::ESPTextScale;
                FVector2D ShadowSize = { TextureSize.X / ShadowScale, TextureSize.Y / ShadowScale };
                FVector2D ShadowLocation = { ScreenLocation.X - ShadowSize.X / 2.0, ScreenLocation.Y - ShadowSize.Y / 2.0 };

                // shadow texture
                HUD->Canvas->K2_DrawTexture(ActorTexture, ShadowLocation, ShadowSize, { 0.0,0.0 }, { 1.0, 1.0 }, { 1.0f,1.0f,1.0f,1.0f }, EBlendMode::BLEND_AlphaHoldout, 0.0f, { 0.5,0.5 });
                // normal texture
                double IconScale = max(TextureSize.X, TextureSize.Y) / IconXY / (double)Configuration::ESPTextScale;

                FVector2D IconSize = { TextureSize.X / IconScale, TextureSize.Y / IconScale};
                FVector2D IconLocation = { ScreenLocation.X - IconSize.X / 2.0, ScreenLocation.Y - IconSize.Y / 2.0 };

                FLinearColor IconColor = { 1.0f,1.0f,1.0f,1.0f };
                if (bIconShouldUseColor) {
                    IconColor = TextColor;
                }
                HUD->Canvas->K2_DrawTexture(ActorTexture, IconLocation, IconSize, { 0.0,0.0 }, { 1.0, 1.0 }, IconColor, EBlendMode::BLEND_Translucent, 0.0f, { 0.5,0.5 });
                if (bShouldDrawStar) {
                    if (auto StarTexture = static_cast<UTexture2D*>(LoadAssetPtrFromPath("/Game/UI/Assets_Shared/Icons/Icon_Special_01.Icon_Special_01")); StarTexture != nullptr) {
                        double StarXY = 16.0;
                        double StarScale = max(TextureSize.X, TextureSize.Y) / StarXY / (double)Configuration::ESPTextScale;
                        FVector2D StarSize ={ TextureSize.X / StarScale, TextureSize.Y / StarScale};
                        FVector2D StarLocation = { ScreenLocation.X - IconSize.X / 2.0 - StarSize.X / 2.0, ScreenLocation.Y + IconSize.Y / 2.0 - StarSize.Y / 2.0 };
                        HUD->Canvas->K2_DrawTexture(StarTexture, StarLocation, StarSize, { 0.0,0.0 }, { 1.0, 1.0 }, { 1.0f,0.9f,0.0f,1.0f }, EBlendMode::BLEND_Translucent, 0.0f, { 0.5,0.5 });
                    }
                }
                if (Entry->Infected()) {
                    if (auto InfectedTexture = static_cast<UTexture2D*>(LoadAssetPtrFromPath("/Game/UI/Assets_Shared/Icons/WT_Icon_SparkleSingle_Glow.WT_Icon_SparkleSingle_Glow")); InfectedTexture != nullptr) {
                        double InfectedXY = 16.0;

                        double SInfectedScale = max(TextureSize.X, TextureSize.Y) / (InfectedXY + 4.0) / (double)Configuration::ESPTextScale;
                        FVector2D SInfectedSize ={ TextureSize.X / SInfectedScale, TextureSize.Y / SInfectedScale};
                        FVector2D SInfectedLocation = { ScreenLocation.X + IconSize.X / 2.0 - SInfectedSize.X / 2.0, ScreenLocation.Y + IconSize.Y / 2.0 - SInfectedSize.Y / 2.0 };
                        HUD->Canvas->K2_DrawTexture(InfectedTexture, SInfectedLocation, SInfectedSize, { 0.0,0.0 }, { 1.0, 1.0 }, { 0.02f,0.02f,0.207f,1.0f }, EBlendMode::BLEND_Translucent, 0.0f, { 0.5,0.5 });

                        double InfectedScale = max(TextureSize.X, TextureSize.Y) / InfectedXY / (double)Configuration::ESPTextScale;
                        FVector2D InfectedSize ={ TextureSize.X / InfectedScale, TextureSize.Y / InfectedScale};
                        FVector2D InfectedLocation = { ScreenLocation.X + IconSize.X / 2.0 - InfectedSize.X / 2.0, ScreenLocation.Y + IconSize.Y / 2.0 - InfectedSize.Y / 2.0 };
                        HUD->Canvas->K2_DrawTexture(InfectedTexture, InfectedLocation, InfectedSize, { 0.0,0.0 }, { 1.0, 1.0 }, { 0.67f,0.37f,0.785f,1.0f }, EBlendMode::BLEND_Translucent, 0.0f, { 0.5,0.5 });
                    }
                }
                if (bOverlayText && !OverlayText.empty()) {
                    std::wstring OverlayWText(OverlayText.begin(), OverlayText.end());
                    FVector2D OverlayPosition = ScreenLocation; //{ ScreenLocation.X - IconSize.X / 2, ScreenLocation.Y + IconSize.Y / 2 };
                    HUD->Canvas->K2_DrawText(Roboto, FString(OverlayWText.data()), OverlayPosition, { 0.825 * (double)Configuration::ESPTextScale, 0.825 * (double)Configuration::ESPTextScale }, TextColor, 0.0f, { 1.0f,1.0f,1.0f,1.0f }, { 1.0, 1.0 }, true, true, true, { 0.0f, 0.0f, 0.0f, 1.0f });
                }
                FVector2D Offset = { 0.0, IconSize.Y / 2.0 };
                if (!IconText.empty()) {
                    for (auto line : IconText) {
                        auto DisplayString = FString(line.data());
                        auto textSize = HUD->Canvas->K2_TextSize(Roboto, DisplayString, TextScale);
                        HUD->Canvas->K2_DrawText(Roboto, DisplayString, { ScreenLocation.X, ScreenLocation.Y + Offset.Y }, TextScale, TextColor, 0.0f, { 0.0f,0.0f,0.0f,1.0f }, { 1.0,1.0 }, true, false, true, { 0.0f,0.0f,0.0f,1.0f });
                        Offset.Y += textSize.Y;
                    }
                }
                if (!IconAboveText.empty()) {
                    auto AboveString = FString(IconAboveText.data());
                    auto textSize = HUD->Canvas->K2_TextSize(Roboto, AboveString, TextScale);
                    HUD->Canvas->K2_DrawText(Roboto, AboveString, { ScreenLocation.X, ScreenLocation.Y - IconSize.Y / 2.0 - textSize.Y }, TextScale, TextColor, 0.0f, { 0.0f,0.0f,0.0f,1.0f }, { 1.0,1.0 }, true, false, true, { 0.0f,0.0f,0.0f,1.0f });
                }
            }
        }
    }
}