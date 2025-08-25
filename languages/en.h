#pragma once
#include <string>
#include <cstring>

//
// Embedded English translations for Palia Overlay Tool
// Edit this file to update English translations, then rebuild the DLL
//

namespace EmbeddedTranslations {

    // -----------------------------
    // Chunked content (safe sizes)
    // -----------------------------

    // 01 — Main / Tabs / Visual Settings
    static const char* EN_01_MAIN_AND_VISUALS = R"(# English Language File for Palia Overlay Tool
# Format: key=value

# Main Application
window.main_title=Palia Overlay Tool

# Tab Names - from PaliaOverlay.cpp BeginTabItem calls
tab.esp_visuals=ESP & Visuals
tab.aim_assistants=Aim Assistants
tab.movements_tps=Movements & TPs
tab.skills_tools=Skills & Tools
tab.stores_inventory=Stores & Inventory
tab.mods_settings=Mods & Settings

# ESP & Visuals Tab
## Visual Settings - from ESP_VisualSettings.h
header.visual_settings=Visual Settings
checkbox.enable_esp=Enable ESP
tooltip.enable_esp=Enable or disable all ESP features
slider.esp_distance=ESP Distance
tooltip.esp_distance=Change the max rendering distance limitations of your ESP
slider.esp_text_scale=ESP Text Scale
tooltip.esp_text_scale=Adjust the scale of ESP text size
checkbox.show_entity_distance=Show Entity Distance
tooltip.show_entity_distance=Displays the distances to your activated ESP entities
checkbox.show_entity_despawn_timers=Show Entity Despawn Timers
tooltip.show_entity_despawn_timers=Shows the time left in seconds before a resource despawns
checkbox.show_esps_on_world_map=Show ESPs on World Map
tooltip.show_esps_on_world_map=Display ESP elements on the world map
checkbox.use_native_esp_icons=Use Native ESP Icons
tooltip.use_native_esp_icons=Display in-game icons instead of Font-Awesome icons and text on screen
checkbox.show_active_mods=Show Active Mods
tooltip.show_active_mods=Display an overlay window of your currently activated mods
)";

    // 02 — Animals
    static const char* EN_02_ANIMALS = R"(
## Animals - from ESP_AnimalSettings.h
header.animals=Animals
button.sernuk=Sernuk
button.chapaa=Chapaa
button.muujin=Muujin
button.ogopuu=Ogopuu
button.shmole=Shmole
text.sernuk=Sernuk
text.elder_sernuk=Elder Sernuk
text.proudhorn_sernuk=Proudhorn Sernuk
text.chapaa=Chapaa
text.striped_chapaa=Striped Chapaa
text.azure_chapaa=Azure Chapaa
text.minigame_chapaa=Minigame Chapaa
text.muujin=Muujin
text.banded_muujin=Banded Muujin
text.bluebristle_muujin=Bluebristle Muujin
text.ogopuu=Ogopuu
text.emerald_ogopuu=Emerald Ogopuu
text.waveback_ogopuu=Waveback Ogopuu
text.shmole=Shmole
text.elder_shmole=Elder Shmole
text.piksii_shmole=Piksii Shmole
text.chapaa_balloon=Chapaa Balloon
text.stripped_chapaa_balloon=Stripped Chapaa Balloon
text.azure_chapaa_balloon=Azure Chapaa Balloon
)";

    // 03 — Bugs (groups/regions)
    static const char* EN_03_BUGS_META = R"(
## Bugs - from ESP_BugSettings.h
header.bugs=Bugs
button.common_bugs=Common
button.uncommon_bugs=Uncommon
button.rare_bugs=Rare
button.epic_bugs=Epic
button.star_bugs=Star
button.infected_bugs=Infected
text.kilima_bugs=Kilima
text.kilima_bahari_bugs=Kilima & Bahari
text.bahari_bugs=Bahari Bay
text.elderwood_bugs=Elderwood
)";

    // 04 — Individual Bug Names
    static const char* EN_04_BUGS_LIST = R"(
# Individual Bug Names
text.duskwing_butterfly=Duskwing Butterfly
text.firebreathing_dragonfly=Firebreathing Dragonfly
text.garden_leafhopper=Garden Leafhopper
text.garden_mantis=Garden Mantis
text.garden_millipede=Garden Millipede
text.golden_glory_bee=Golden Glory Bee
text.gossamer_veil_moth=Gossamer Veil Moth
text.princess_ladybug=Princess Ladybug
text.proudhorned_stag_beetle=Proudhorned Stag Beetle
text.raspberry_beetle=Raspberry Beetle
text.brushtail_dragonfly=Brushtail Dragonfly
text.common_blue_butterfly=Common Blue Butterfly
text.common_field_cricket=Common Field Cricket
text.kilima_night_moth=Kilima Night Moth
text.spotted_stink_bug=Spotted Stink Bug
text.spotted_mantis=Spotted Mantis
text.ancient_amber_beetle=Ancient Amber Beetle
text.azure_stonehopper=Azure Stonehopper
text.bahari_bee=Bahari Bee
text.bahari_crab=Bahari Crab
text.bahari_glowbug=Bahari Glowbug
text.brighteye_butterfly=Brighteye Butterfly
text.cerulean_cicada=Cerulean Cicada
text.common_bark_cicada=Common Bark Cicada
text.fairy_mantis=Fairy Mantis
text.garden_ladybug=Garden Ladybug
text.garden_snail=Garden Snail
text.hairy_millipede=Hairy Millipede
text.inky_dragonfly=Inky Dragonfly
text.jewelwing_dragonfly=Jewelwing Dragonfly
text.leafstalker_mantis=Leafstalker Mantis
text.lunar_fairy_moth=Lunar Fairy Moth
text.paper_lantern_bug=Paper Lantern Bug
text.rainbow_tipped_butterfly=Rainbow-Tipped Butterfly
text.scintillating_centipede=Scintillating Centipede
text.spineshell_crab=Spineshell Crab
text.spitfire_cicada=Spitfire Cicada
text.stripeshell_snail=Stripeshell Snail
text.vampire_crab=Vampire Crab
text.blood_beetle=Blood Beetle
text.blushing_batterfly=Blushing Batterfly
text.cave_piksii=Cave Piksii
text.draugr_beetle=Draugr Beetle
text.flame_horned_rockhopper=Flame-Horned Rockhopper
text.grumpy_granite_rockhopper=Grumpy Granite Rockhopper
text.nightshadow_batterfly=Nightshadow Batterfly
text.sunburst_batterfly=Sunburst Batterfly
text.veil_piksii=Veil Piksii
text.will_o_wisp_rockhopper=Will-o-wisp Rockhopper
)";

    // 05 — Forageables (meta)
    static const char* EN_05_FORAGE_META = R"(
## Forageables - from ESP_ForageableSettings.h
header.forageables=Forageables
button.common_forage=Common
button.uncommon_forage=Uncommon
button.rare_forage=Rare
button.epic_forage=Epic
button.star_forage=Star
button.infected_forage=Infected
text.kilima_forageables=Kilima
text.kilima_bahari_forageables=Kilima & Bahari
text.bahari_forageables=Bahari Bay
text.elderwood_forageables=Elderwood
)";

    // 06 — Forageables (names)
    static const char* EN_06_FORAGE_LIST = R"(
# Individual Forageable Names
# Kilima Region
text.crystal_lake_lotus=Crystal Lake Lotus
text.emerald_carpet_moss=Emerald Carpet Moss
text.spice_sprouts=Spice Sprouts
text.wild_ginger=Wild Ginger
text.wild_green_onion=Wild Green Onion

# Kilima & Bahari Region
text.mountain_morel=Mountain Morel
text.sundrop_lily=Sundrop Lily
text.wild_garlic=Wild Garlic

# Bahari Region
text.briar_daisy=Briar Daisy
text.brightshroom=Brightshroom
text.coral=Coral
text.dari_cloves=Dari Cloves
text.dragons_beard_peat=Dragon's Beard Peat
text.heartdrop_lily=Heartdrop Lily
text.heat_root=Heat Root
text.shell=Shell
text.sweet_leaf=Sweet Leaf
text.oyster=Oyster

# Elderwood Region
text.batterfly_beans=Batterfly Beans
text.elder_clam_mushroom=Elder Clam Mushroom
text.elderflower=Elderflower
text.elderwood_lotus=Elderwood Lotus
text.elderwood_orchid=Elderwood Orchid
text.floatfish_mushroom=Floatfish Mushroom
text.flowtato=Flowtato
text.honey=Honey
text.infected_essence=Infected Essence
text.kopaa_nut=Kopaa Nut
text.piksii_berries=Piksii Berries
text.staircase_mushroom=Staircase Mushroom
)";

    // 07 — Ores
    static const char* EN_07_ORES = R"(
## Ores - from ESP_OreSettings.h
header.ores=Ores
button.clay=Clay
button.stone=Stone
button.whitestone=Whitestone
button.copper=Copper
button.iron=Iron
button.silver=Silver
button.gold=Gold
button.palium=Palium
button.platinum=Platinum
text.small=Sm
text.medium=Med
text.large=Lg
)";

    // 08 — Trees
    static const char* EN_08_TREES = R"(
## Trees - from ESP_TreeSettings.h
header.trees=Trees
button.bush=Bush
button.sapwood=Sapwood
button.heartwood=Heartwood
button.flow=Flow
button.ancient=Ancient
button.infected_trees=Infected
text.sapling=Sap
text.flow_infused=Flow-Infused
)";

    // 09 — Player & Entities
    static const char* EN_09_PLAYER_ENTITIES = R"(
## Player & Entities - from ESP_SingleSettings.h
header.player_entities=Player & Entities
button.toggle_all_misc=Toggle All
text.players=Players
text.npcs=NPCs
text.fish=Fish
text.fish_pools=Fish Pools
text.loot=Loot
text.quests=Quests
text.rummage_piles=Rummage Piles
text.treasure=Treasure
text.stables=Stables
text.timed_drops=Timed Drops
text.books_lost_relics=Books & Lost Relics
text.unpurchased_furniture=Unpurchased Furniture
text.others=Others
)";

    // 10 — Aim Assistants
    static const char* EN_10_AIM = R"(
# Aim Assistants Tab - from Aimbots_FunSettings.h
header.inteliaim_settings=InteliAim Settings
checkbox.enable_inteliaim=Enable InteliAim
tooltip.enable_inteliaim=Enable the FOV targeting system. Teleport to actors, enable aimbots, and more.
slider.inteliaim_radius=InteliAim Radius
tooltip.inteliaim_radius=Make your targeting area bigger or smaller. Set this before Hiding Circle.
checkbox.hide_circle=Hide Circle
tooltip.hide_circle=Use the InteliTarget system without displaying the InteliAim Circle.
slider.circle_transparency=Circle Transparency
tooltip.circle_transparency=Adjust the transparency of the InteliAim Circle.
checkbox.show_crosshair=Show Crosshair
tooltip.show_crosshair=Display a small purple crosshair in the middle of your screen. Nicely paired with Hide Circle.

header.intelitarget_settings=InteliTarget Settings
checkbox.enable_aimbot=Enable Classic Aimbot
tooltip.enable_aimbot=Classic aimbot that smoothly aims at targets when key is held.
text.aimkey=Aim Key: %s
button.set_aimkey=Set Aim Key
text.press_key_cancel=Press any key to set, or ESC to cancel
tooltip.aimkey=Set the key to hold for aimbot activation
checkbox.enable_silent_aimbot=Enable Silent Aimbot
tooltip.enable_silent_aimbot=Teleport Bug Bombs & Arrows To Your Target.
checkbox.enable_teleporting_to_target=Enable Teleporting To Target
tooltip.enable_teleporting_to_target=Teleport directly to your targeted entity.
checkbox.avoid_teleporting_to_players=Avoid Teleporting To Players
tooltip.avoid_teleporting_to_players=Don't teleport to targeted players.
checkbox.avoid_teleporting_when_players_near=Avoid Teleporting To Target When Players Are Near
tooltip.avoid_teleporting_when_players_near=Don't teleport if a player is detected near your destination.
slider.avoidance_radius=Avoidance Radius
tooltip.avoidance_radius=The distance to avoid players when teleporting to a target.
text.enable_inteliaim_notice=[ ENABLE INTELIAIM TO VIEW INTELITARGET OPTIONS ]
)";

    // 11 — Movement & TPs
    static const char* EN_11_MOVEMENT = R"(
# Movements & TPs Tab - from Movement_TeleportSettings.h
header.movement_settings=Movement Settings
checkbox.enable_noclip=Enable Noclip
tooltip.enable_noclip=Allows you to fly and phase through anything.
checkbox.enable_spinbot=Enable Spinbot
tooltip.enable_spinbot=Spin your player in a circle quickly, funny looking!
slider.spinbot_speed=Spinbot Speed
tooltip.spinbot_speed=Change the speed of your spinbot.
text.movement_mode=Movement Mode
text.walking=Walking
text.flying=Flying
text.fly_no_collision=Fly No Collision
button.set_movement=Set
text.global_game_speed=Global Game Speed
text.walk_speed=Walk Speed
text.sprint_speed=Sprint Speed
text.climbing_speed=Climbing Speed
text.gliding_speed=Gliding Speed
text.gliding_fall_speed=Gliding Fall Speed
text.jump_velocity=Jump Velocity
text.max_jumps=Max Jumps
text.step_height=Step Height

header.locations_coordinates=Locations & Coordinates
text.teleport_list=Teleport List
text.double_click_teleport=Double-click a location listing to teleport
text.map=Map
text.current_coords=Current Coords
button.get_current_coordinates=Get Current Coordinates
button.teleport_to_coordinates=Teleport To Coordinates
text.travel_list=Travel List
text.double_click_travel=Double-click a location listing to travel
)";

    // 12 — Skills & Tools: Axe/Pickaxe
    static const char* EN_12_SKILLS_AXE_PICK = R"(
# Skills & Tools Tab - from Skills_ToolsSettings.h and sub-modules
header.axe_pickaxe_settings=Axe & Pickaxe Settings
checkbox.auto_swing_tool=Auto Swing Tool
tooltip.auto_swing_tool=Automatically chop or mine resources around you as you play.
checkbox.auto_equip_tool=Auto Equip Tool
tooltip.auto_equip_tool=Automatically equips your Axe/Pickaxe when in range of resources.
checkbox.require_esp_toggles_swing=Require ESP Toggles (Swing)
tooltip.require_esp_toggles_swing=Swing only at ESP enabled resources.
checkbox.avoid_swinging_low_durability=Avoid Swinging On Low Durability
tooltip.avoid_swinging_low_durability=Avoid swinging tools with low durability.
checkbox.avoid_chopping_grove=Avoid Chopping Grove
tooltip.avoid_chopping_grove=Avoid chopping flow trees near other flow trees.
checkbox.avoid_swinging_near_players=Avoid Swinging Near Players
tooltip.avoid_swinging_near_players=Avoid swinging tools near other players.
checkbox.avoid_swinging_housing_plots=Avoid Swinging On Housing Plots
tooltip.avoid_swinging_housing_plots=Avoid swinging tools on housing plots.
)";

    // 13 — Skills & Tools: Bug Settings
    static const char* EN_13_SKILLS_BUGS = R"(
header.bug_settings=Bug Settings
checkbox.auto_catch_bugs=Auto Catch Bugs
tooltip.auto_catch_bugs=Automatically catch bugs within set distance of your player while you have a bug belt active
checkbox.auto_equip_smoke_bombs=Auto Equip Smoke Bombs
tooltip.auto_equip_smoke_bombs=Automatically equips your Smoke Bombs when in range of bugs.
checkbox.require_esp_toggles_catch=Require ESP Toggles (Catch)
tooltip.require_esp_toggles_catch=Catch only ESP enabled bugs.
checkbox.avoid_catching_low_durability=Avoid Catching On Low Durability
tooltip.avoid_catching_low_durability=Avoid catching bugs with low durability.
text.catch_distance=Catch Distance
tooltip.catch_distance=Change the distance of your auto catching detection range
checkbox.avoid_catching_near_players=Avoid Catching Near Players
tooltip.avoid_catching_near_players=Avoid catching bugs near other players.
text.catching_speed=Catching Speed
text.speed_fast=Fast
text.speed_medium=Medium
text.speed_slow=Slow
text.speed_custom=Custom
text.custom_speed=Custom Speed
)";

    // 14 — Skills & Tools: Animal/Balloon
    static const char* EN_14_SKILLS_ANIMAL_BALLOON = R"(
header.animal_balloon_settings=Animal / Balloon Settings
checkbox.auto_hunt=Auto Hunt
tooltip.auto_hunt=Automatically hunt animals or balloons within set distance of your player while you have a bow active
checkbox.auto_equip_bow=Auto Equip Bow
tooltip.auto_equip_bow=Automatically equips your Bow when in range of animals.
checkbox.require_esp_toggles_hunt=Require ESP Toggles (Hunt)
tooltip.require_esp_toggles_hunt=Hunt only ESP enabled animals/balloons.
checkbox.avoid_hunting_low_durability=Avoid Hunting On Low Durability
tooltip.avoid_hunting_low_durability=Avoid hunting animals/balloons with low durability.
text.hunt_distance=Hunt Distance
tooltip.hunt_distance=Change the distance of your auto hunting detection range
checkbox.avoid_hunting_near_players=Avoid Hunting Near Players
tooltip.avoid_hunting_near_players=Avoid hunting animals/balloons near other players.
text.hunting_speed=Hunting Speed
)";

    // 15 — Skills & Tools: Other
    static const char* EN_15_SKILLS_OTHER = R"(
header.other_settings=Other Settings
checkbox.auto_gather_nearby_loot=Auto Gather Nearby Loot
tooltip.auto_gather_nearby_loot=Automatically gather forageables (within range) when you play.
checkbox.skip_cooking_minigames=Skip Cooking Minigames
tooltip.skip_cooking_minigames=Skips the cooking minigame process completely.
checkbox.auto_refill_focus=Auto Refill Focus
tooltip.auto_refill_focus=Consumes the highest focus food in inventory without going over max focus.
text.when_below=When Below
tooltip.when_below=The percentage of focus at which auto focus will trigger.
)";

    // 16 — Skills & Tools: Fishing
    static const char* EN_16_SKILLS_FISHING = R"(
header.fishing_settings=Fishing Settings
checkbox.no_rod_durability_loss=No Rod Durability Loss
tooltip.no_rod_durability_loss=Never break your fishing rod.
checkbox.enable_multiplayer_help=Enable Multiplayer Help
tooltip.enable_multiplayer_help=Force fishing with other players for extra quest completion.
checkbox.always_perfect_catch=Always Perfect Catch
tooltip.always_perfect_catch=Fishing will always result in a perfect catch.
checkbox.instant_catch=Instant Catch
tooltip.instant_catch=Catch fish as soon as your bobber hits the water.
checkbox.auto_fast_fishing=Auto Fast Fishing
tooltip.auto_fast_fishing=Fish extremely fast. Pairs nicely with other fishing features.
checkbox.require_holding_left_click=Require Holding Left-Click To Auto Fish
tooltip.require_holding_left_click=Require holding the left mouse button to toggle the fast fishing.
checkbox.force_fishing_pool=Force Fishing Pool
tooltip.force_fishing_pool=Force all catches to result from the selected pool.
text.equip_fishing_rod_notice=[ EQUIP FISHING ROD TO VIEW FAST FISHING OPTIONS ]
)";

    // 17 — Skills & Tools: Gardening
    static const char* EN_17_SKILLS_GARDENING = R"(
header.gardening_settings=Gardening Settings
checkbox.auto_till=Auto Till
tooltip.auto_till=With your hoe equipped, till any soil that needs it.
checkbox.auto_weed=Auto Weed
tooltip.auto_weed=Clear any weeds from your garden.
checkbox.auto_harvest=Auto Harvest
tooltip.auto_harvest=Harvest any plants ready to be picked.
checkbox.auto_replant=Auto Replant
tooltip.auto_replant=Using seeds from your inventory, replant the previous plant on that plot.
checkbox.auto_fertilize=Auto Fertilize
tooltip.auto_fertilize=Adds one fertilizer to any unfertilized plot. Takes the first found fertilizer in your inventory.
text.max_quantity=Max Quantity
tooltip.max_quantity=Max amount of fertilizer to apply to one plot
)";

    // 18 — Stores & Inventory: Inventory Actions
    static const char* EN_18_STORE_INVENTORY_ACTIONS = R"(
# Stores & Inventory Tab - from Selling_PlayerSettings.h and Store_AutoSellSettings.h
header.inventory_actions=Inventory Actions
text.inventory_slot_selector=Inventory Slot Selector
button.all=All
text.amount=Amount
text.backpack=Backpack
text.ammo_pouch=Ammo Pouch
button.sell=Sell
button.discard=Discard
button.storage=Storage
button.duplicate=Duplicate
)";

    // 19 — Stores & Inventory: Auto Sell
    static const char* EN_19_STORE_AUTOSELL = R"(
header.auto_sell=Auto Sell
text.auto_sell_type=Type
text.auto_sell_common=Common
text.auto_sell_uncommon=Uncommon
text.auto_sell_rare=Rare
text.auto_sell_epic=Epic
text.auto_sell_sq=SQ
checkbox.bugs_auto_sell=Bugs
tooltip.bugs_auto_sell=Automatically sell bugs from your inventory.
checkbox.fish_auto_sell=Fish
tooltip.fish_auto_sell=Automatically sell fish from your inventory.
checkbox.forageables_auto_sell=Forageables
tooltip.forageables_auto_sell=Automatically sell forageables from your inventory.
checkbox.hunting_auto_sell=Hunting
tooltip.hunting_auto_sell=Automatically sell hunting loot from your inventory.
text.tree_fiber=Fiber
text.tree_sapwood=Sapwood
text.tree_heartwood=Heartwood
text.tree_flow=Flow
text.tree_ancient=Ancient
checkbox.trees_auto_sell=Trees
tooltip.trees_auto_sell=Automatically sell logs from your inventory.
checkbox.flowers_auto_sell=Flowers
tooltip.flowers_auto_sell=Automatically sell flowers from your inventory.
checkbox.junk_auto_sell=Junk
tooltip.junk_auto_sell=Automatically sell junk fished up.
)";

    // 20 — Stores & Inventory: Stores (remote)
    static const char* EN_20_STORE_REMOTE = R"(
header.stores=Stores
checkbox.item_buy_multiplier=Item Buy Multiplier
tooltip.item_buy_multiplier=Enables ability to change how many items you purchase each time.
checkbox.enable_ctrl_click_buy=Enable CTRL-Click to Buy Modded
tooltip.enable_ctrl_click_buy=Enables ability to require holding CTRL key to buy modded stack amount.
text.amount_to_multiply=Amount to Multiply
tooltip.amount_to_multiply=Buy amount multiplier
text.open_remote_stores=Open Remote Stores
button.open_guild_store=Open Guild Store
button.open_building_store=Open Building Store
text.stores_night_notice=Some stores are only available at night.
text.stores_hours_notice=Opening during off hours will show no inventory, or the inventory of a previously opened store.
text.couldnt_retrieve_stores=Couldn't retrieve stores.
)";

    // 21 — Stores & Inventory: Player features / Auto Open / Auto Storage
    static const char* EN_21_STORE_MISC = R"(
header.player_features=Player Features
button.open_player_storage=Open Player Storage

header.auto_open=Auto Open
checkbox.waterlogged_chests=Waterlogged Chests
tooltip.waterlogged_chests=Automatically opens any Waterlogged Chests fished up.
checkbox.unopened_oysters=Unopened Oysters
tooltip.unopened_oysters=Automatically opens any Unopened Oysters foraged.
checkbox.elder_clam_mushrooms=Elder Clam Mushrooms
tooltip.elder_clam_mushrooms=Automatically opens any Elder Clam Mushrooms foraged.

header.auto_storage=Auto Storage
checkbox.furniture_auto_storage=Furniture
tooltip.furniture_auto_storage=Automatically sends Decor items to Storage.
)";

    // 22 — Mods & Settings: Character
    static const char* EN_22_MODS_CHARACTER = R"(
# Mods & Settings Tab - from Mods_SettingsGlobal.h
header.character_settings=Character Settings
checkbox.anti_afk=Anti AFK
tooltip.anti_afk=Stop inactivity disconnects and play forever.
checkbox.unlimited_wardrobe_respecs=Unlimited Wardrobe Respecs
tooltip.unlimited_wardrobe_respecs=Allows yous to change genders/appereances without the cooldown.
checkbox.further_interaction_distance=Further Interaction Distance
tooltip.further_interaction_distance=Interact with things from further distances.
text.interaction_distance=Interaction Distance
tooltip.interaction_distance=Adjust the maximum distance for interactions. Range: 1.0 to 99999.0
checkbox.teleport_to_waypoints=Teleport To Waypoints
tooltip.teleport_to_waypoints=Automatically teleports you at your waypoints locations.
checkbox.easy_quest_mode=Easy Quest Mode
tooltip.easy_quest_mode=Experimental - May skip some questing requirements.
)";

    // 23 — Mods & Settings: UI
    static const char* EN_23_MODS_UI = R"(
header.ui_settings=UI Settings
checkbox.show_watermark=Show Watermark
tooltip.show_watermark=Toggle display of the custom watermark on the screen.
text.select_theme=Select Theme
button.edit_custom_theme=Edit Custom Theme
tooltip.edit_custom_theme_disabled=Select 'Custom Theme' to begin editing.
popup.custom_theme_editor=Custom Theme Editor
text.widgets=Widgets
button.save=Save
button.close_without_saving=Close Without Saving
button.undo=Undo
text.undo_changes=Undo Changes.
)";

    // 24 — Fun Settings
    static const char* EN_24_FUN = R"(
header.fun_settings=Fun Settings
checkbox.advanced_placement=Advanced Placement
tooltip.advanced_placement=Allow for placement of housing items anywhere.
text.caps_lock_rotation=Caps Lock Rotation
tooltip.caps_lock_rotation=While caps lock is on, rotate by this amount instead.
checkbox.temporarily_unlock_outfits=Temporarily Unlock Outfits
tooltip.temporarily_unlock_outfits=Temporarily unlocks premium outfits.
text.outfits_notice=To finish enabling outfits & collections, you need to open the Premium Store and let it load.
checkbox.temporarily_unlock_decor_tints=Temporarily Unlock All Decor Tints
tooltip.temporarily_unlock_decor_tints=Temporarily unlocks extra tints in the Modification Bench
checkbox.temporarily_unlock_landscapes=Temporarily Unlock Landscapes
tooltip.temporarily_unlock_landscapes=Allows you to activate any landscape for previewing.
checkbox.show_villager_weekly_gifts=Show All Villager Weekly Gifts
tooltip.show_villager_weekly_gifts=Show all the gifts Villagers want this week without learning about them.
checkbox.unrepair_tool_for_gold=Unrepair Tool For Gold
tooltip.unrepair_tool_for_gold=Unrepair your tool of choice for max gold in return.
text.max_unrepair_amount=Max Unrepair Amount
checkbox.fulfill_infinite_player_requests=Fulfill Infinite Player Requests
tooltip.fulfill_infinite_player_requests=Fulfill as many requests as you want. May require multiple tries.
checkbox.black_market_prize_wheel=Black Market Prize Wheel
tooltip.black_market_prize_wheel=Choose which positions on the wheel to accept.
checkbox.use_locked_storage=Use Locked Storage
tooltip.use_locked_storage=Use locked storage instead of general storage.
text.prize_wheel_positions=Prize Wheel Positions
text.prize_wheel_red_fireworks=0| Red    - Fireworks
text.prize_wheel_purple_decor=1| Purple - Decor
text.prize_wheel_blue_ingredients=2| Blue   - Ingredients
text.prize_wheel_green_gold=3| Green  - Gold
text.prize_wheel_red_fireworks2=4| Red    - Fireworks
text.prize_wheel_brown_coins=5| Brown  - Lucky Coins
text.prize_wheel_blue_ingredients2=6| Blue   - Ingredients
text.prize_wheel_green_gold2=7| Green  - Gold
text.prize_wheel_yellow_plushie=8| Yellow - Plushie
)";

// 25 — Language selector & feedback
static const char* EN_25_KEYS_LANG = R"(
# Language Selection
combo.language=Language
tooltip.language=Select your preferred language
note.translation_feedback=Found a translation error? Let us know in Discord!
)";

// 26 — Hotkey Names
static const char* EN_26_HOTKEY_NAMES = R"(
# Hotkey Names
key.no_key_set=No key set
key.left_mouse=Left Mouse Button
key.right_mouse=Right Mouse Button
key.middle_mouse=Middle Mouse Button
key.side_mouse_1=Side Mouse Button 1
key.side_mouse_2=Side Mouse Button 2
key.unknown_key=Unknown Key
)";

// 27 — Function Keys
static const char* EN_27_FUNCTION_KEYS = R"(
# Function Keys
key.f1=F1
key.f2=F2
key.f3=F3
key.f4=F4
key.f5=F5
key.f6=F6
key.f7=F7
key.f8=F8
key.f9=F9
key.f10=F10
key.f11=F11
key.f12=F12
)";

// 28 — Special / Navigation Keys
static const char* EN_28_SPECIAL_KEYS = R"(
# Special Keys
key.caps_lock=Caps Lock
key.scroll_lock=Scroll Lock
key.num_lock=Num Lock
key.tab=Tab
key.space=Space
key.enter=Enter
key.escape=Escape
key.backspace=Backspace
key.insert=Insert
key.delete=Delete
key.home=Home
key.end=End
key.page_up=Page Up
key.page_down=Page Down
)";

// 29 — Arrows & Modifiers
static const char* EN_29_ARROWS_MODS = R"(
# Arrow Keys
key.up_arrow=Up Arrow
key.down_arrow=Down Arrow
key.left_arrow=Left Arrow
key.right_arrow=Right Arrow

# Modifier Keys
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Left Shift
key.right_shift=Right Shift
key.left_ctrl=Left Ctrl
key.right_ctrl=Right Ctrl
key.left_alt=Left Alt
key.right_alt=Right Alt
)";

// 30 — Numpad Keys
static const char* EN_30_NUMPAD = R"(
# Numpad Keys
key.numpad_0=Numpad 0
key.numpad_1=Numpad 1
key.numpad_2=Numpad 2
key.numpad_3=Numpad 3
key.numpad_4=Numpad 4
key.numpad_5=Numpad 5
key.numpad_6=Numpad 6
key.numpad_7=Numpad 7
key.numpad_8=Numpad 8
key.numpad_9=Numpad 9
key.numpad_multiply=Numpad *
key.numpad_add=Numpad +
key.numpad_subtract=Numpad -
key.numpad_decimal=Numpad .
key.numpad_divide=Numpad /
key.numpad_enter=Numpad Enter
)";

// 31 — Common UI & Notifications
static const char* EN_31_COMMON_UI_AND_NOTIFS = R"(
# Common UI Elements
text.show=Show
text.color=Color
text.normal=Normal
text.star=Star
text.infected=Infected
text.name=Name
text.type=Type
button.reset=R
text.waiting_game_load=Waiting for the game to load...
text.waiting_in_game=Waiting for in-game...
text.waiting_character_init=Waiting for character initialization...

# Notifications
notification.first_use=Thank you for using our Palia Tool. To get started, open the menu with the 'INSERT' key.
)";

    // -----------------------------
    // Final concatenated content
    // -----------------------------
    static const char* ENGLISH_CONTENT = []() {
        static std::string combined =
            std::string(EN_01_MAIN_AND_VISUALS)
            + std::string(EN_02_ANIMALS)
            + std::string(EN_03_BUGS_META)
            + std::string(EN_04_BUGS_LIST)
            + std::string(EN_05_FORAGE_META)
            + std::string(EN_06_FORAGE_LIST)
            + std::string(EN_07_ORES)
            + std::string(EN_08_TREES)
            + std::string(EN_09_PLAYER_ENTITIES)
            + std::string(EN_10_AIM)
            + std::string(EN_11_MOVEMENT)
            + std::string(EN_12_SKILLS_AXE_PICK)
            + std::string(EN_13_SKILLS_BUGS)
            + std::string(EN_14_SKILLS_ANIMAL_BALLOON)
            + std::string(EN_15_SKILLS_OTHER)
            + std::string(EN_16_SKILLS_FISHING)
            + std::string(EN_17_SKILLS_GARDENING)
            + std::string(EN_18_STORE_INVENTORY_ACTIONS)
            + std::string(EN_19_STORE_AUTOSELL)
            + std::string(EN_20_STORE_REMOTE)
            + std::string(EN_21_STORE_MISC)
            + std::string(EN_22_MODS_CHARACTER)
            + std::string(EN_23_MODS_UI)
            + std::string(EN_24_FUN)
            + std::string(EN_25_KEYS_LANG)
            + std::string(EN_26_HOTKEY_NAMES)
            + std::string(EN_27_FUNCTION_KEYS)
            + std::string(EN_28_SPECIAL_KEYS)
            + std::string(EN_29_ARROWS_MODS)
            + std::string(EN_30_NUMPAD)
            + std::string(EN_31_COMMON_UI_AND_NOTIFS);
        return combined.c_str();
    }();
}
