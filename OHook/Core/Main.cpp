#include "Main.h"
#include "Configuration.h"
#include "HotkeysManager.h"
#include "Utils.h"

#include "ActorHandler.h"
#include "ToolHandler.h"
#include "WidgetHandler.h"
#include "HotkeysManager.h"

#include "AimDetours.h"
#include "FishingDetours.h"
#include "HUDDetours.h"
#include "MovementDetours.h"
#include "PlayerTweaksDetours.h"
#include "TeleportDetours.h"
#include "VillagerDetours.h"
#include "WidgetDetours.h"

#ifdef ENABLE_SUPPORTER_FEATURES
#include "AnimalHunting.h"
#include "BugCatching.h"
#include "Gardening.h"
#include "ToolSwinging.h"
#include "LandscapeDetours.h"
#include "OutfitsDetours.h"
#endif



void Main::Start() {
    // Load Settings
    Configuration::Load();
    HotkeysManager::InitHotkeys();
    ActorHandler::Start();
    SetupDetours();
}

void Main::Stop() {
    DetourManager::RemoveInstances();
    DetourManager::RemoveFunctionDetours();
    ActorHandler::Stop();
}

void Main::SetupDetours() {
    auto VC = GetValeriaCharacter();
    auto VPC = GetValeriaController();
    if (!VPC || !VC) {
        // Small delay per attempt (Needed)
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        SetupDetours();
        return;
    }

    ActorHandler::SetupDetours(VC,VPC);
    ToolHandler::SetupDetours(VC,VPC);
    WidgetHandler::SetupDetours(VC,VPC);
    HotkeysManager::SetupDetours(VC,VPC);

    AimDetours::SetupDetours(VC,VPC);
    FishingDetours::SetupDetours(VC,VPC);
    HUDDetours::SetupDetours(VC,VPC);
    MovementDetours::SetupDetours(VC,VPC);
    PlayerTweaksDetours::SetupDetours(VC,VPC);
    TeleportDetours::SetupDetours(VC,VPC);
    VillagerDetours::SetupDetours(VC,VPC);
    WidgetDetours::SetupDetours(VC,VPC);

    #ifdef ENABLE_SUPPORTER_FEATURES
    AnimalHunting::SetupDetours(VC,VPC);
    BugCatching::SetupDetours(VC,VPC);
    Gardening::SetupDetours(VC,VPC);
    LandscapeDetours::SetupDetours(VC,VPC);
    OutfitsDetours::SetupDetours(VC,VPC);
    ToolSwinging::SetupDetours(VC,VPC);
    #endif
}