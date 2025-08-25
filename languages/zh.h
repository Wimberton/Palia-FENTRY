#pragma once
#include <string>
#include <cstring>

//
// Palia Overlay Tool 的中文内置翻译
// 编辑此文件以更新中文翻译，然后重新编译 DLL
//

namespace EmbeddedTranslations {

    // -----------------------------
    // 分段内容（安全大小）
    // -----------------------------

    // 01 — 主界面 / 选项卡 / 视觉设置
    static const char* ZH_01_MAIN_AND_VISUALS = R"(# Palia Overlay Tool 中文语言文件
# 格式：键=值

# 主程序
window.main_title=Palia 叠加工具

# 选项卡名称 - 来自 PaliaOverlay.cpp (BeginTabItem)
tab.esp_visuals=ESP 与视觉
tab.aim_assistants=瞄准助手
tab.movements_tps=移动与传送
tab.skills_tools=技能与工具
tab.stores_inventory=商店与库存
tab.mods_settings=模组与设置

# ESP 与视觉 选项卡
## 视觉设置 - 来自 ESP_VisualSettings.h
header.visual_settings=视觉设置
checkbox.enable_esp=启用 ESP
tooltip.enable_esp=启用或禁用所有 ESP 功能
slider.esp_distance=ESP 距离
tooltip.esp_distance=更改 ESP 的最大渲染距离
slider.esp_text_scale=ESP 文本缩放
tooltip.esp_text_scale=调整 ESP 文本尺寸的缩放比例
checkbox.show_entity_distance=显示实体距离
tooltip.show_entity_distance=显示到你已启用 ESP 的实体的距离
checkbox.show_entity_despawn_timers=显示消失计时
tooltip.show_entity_despawn_timers=显示资源在消失前剩余的秒数
checkbox.show_esps_on_world_map=在世界地图上显示 ESP
tooltip.show_esps_on_world_map=在世界地图上显示 ESP 元素
checkbox.use_native_esp_icons=使用原生 ESP 图标
tooltip.use_native_esp_icons=在屏幕上显示游戏内图标，而非 Font Awesome 图标与文字
checkbox.show_active_mods=显示已激活模组
tooltip.show_active_mods=显示当前已激活模组的叠加窗口
)";

    // 02 — 动物
    static const char* ZH_02_ANIMALS = R"(
## 动物 - 来自 ESP_AnimalSettings.h
header.animals=动物
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

    // 03 — 昆虫（分组/区域）
    static const char* ZH_03_BUGS_META = R"(
## 昆虫 - 来自 ESP_BugSettings.h
header.bugs=昆虫
button.common_bugs=常见
button.uncommon_bugs=较少见
button.rare_bugs=稀有
button.epic_bugs=史诗
button.star_bugs=星级
button.infected_bugs=感染
text.kilima_bugs=Kilima
text.kilima_bahari_bugs=Kilima 与 Bahari
text.bahari_bugs=Bahari Bay
text.elderwood_bugs=Elderwood
)";

    // 04 — 单个昆虫名称
    static const char* ZH_04_BUGS_LIST = R"(
# 单个昆虫名称
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

    // 05 — 采集物（元信息）
    static const char* ZH_05_FORAGE_META = R"(
## 采集物 - 来自 ESP_ForageableSettings.h
header.forageables=可采集物
button.common_forage=常见
button.uncommon_forage=较少见
button.rare_forage=稀有
button.epic_forage=史诗
button.star_forage=星级
button.infected_forage=感染
text.kilima_forageables=Kilima
text.kilima_bahari_forageables=Kilima 与 Bahari
text.bahari_forageables=Bahari Bay
text.elderwood_forageables=Elderwood
)";

    // 06 — 采集物（名称）
    static const char* ZH_06_FORAGE_LIST = R"(
# 单个采集物名称
# Kilima 区域
text.crystal_lake_lotus=Crystal Lake Lotus
text.emerald_carpet_moss=Emerald Carpet Moss
text.spice_sprouts=Spice Sprouts
text.wild_ginger=Wild Ginger
text.wild_green_onion=Wild Green Onion

# Kilima 与 Bahari 区域
text.mountain_morel=Mountain Morel
text.sundrop_lily=Sundrop Lily
text.wild_garlic=Wild Garlic

# Bahari 区域
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

# Elderwood 区域
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

    // 07 — 矿石
    static const char* ZH_07_ORES = R"(
## 矿石 - 来自 ESP_OreSettings.h
header.ores=矿石
button.clay=黏土
button.stone=石头
button.whitestone=白石
button.copper=铜
button.iron=铁
button.silver=银
button.gold=金
button.palium=Palium
button.platinum=铂金
text.small=小
text.medium=中
text.large=大
)";

    // 08 — 树木
    static const char* ZH_08_TREES = R"(
## 树木 - 来自 ESP_TreeSettings.h
header.trees=树木
button.bush=灌木
button.sapwood=Sapwood
button.heartwood=Heartwood
button.flow=Flow
button.ancient=Ancient
button.infected_trees=感染
text.sapling=幼树
text.flow_infused=注入Flow
)";

    // 09 — 玩家与实体
    static const char* ZH_09_PLAYER_ENTITIES = R"(
## 玩家与实体 - 来自 ESP_SingleSettings.h
header.player_entities=玩家与实体
button.toggle_all_misc=全部切换
text.players=玩家
text.npcs=NPC
text.fish=鱼类
text.fish_pools=鱼池
text.loot=战利品
text.quests=任务
text.rummage_piles=翻找堆
text.treasure=宝藏
text.stables=马厩
text.timed_drops=限时掉落
text.books_lost_relics=书籍与失落的遗物
text.unpurchased_furniture=未购买的家具
text.others=其他
)";

    // 10 — 瞄准助手
    static const char* ZH_10_AIM = R"(
# “瞄准助手”选项卡 - 来自 Aimbots_FunSettings.h
header.inteliaim_settings=InteliAim 设置
checkbox.enable_inteliaim=启用 InteliAim
tooltip.enable_inteliaim=启用基于视野（FOV）的锁定系统。可传送到角色、启用自瞄等。
slider.inteliaim_radius=InteliAim 半径
tooltip.inteliaim_radius=放大或缩小你的瞄准区域。请先设置此项再选择“隐藏圆圈”。
checkbox.hide_circle=隐藏圆圈
tooltip.hide_circle=不显示 InteliAim 圆圈而使用 InteliTarget 系统。
slider.circle_transparency=圆圈透明度
tooltip.circle_transparency=调整 InteliAim 圆圈的透明度。
checkbox.show_crosshair=显示准星
tooltip.show_crosshair=在屏幕中央显示一个小型紫色准星。与“隐藏圆圈”搭配良好。

header.intelitarget_settings=InteliTarget 设置
checkbox.enable_aimbot=启用经典自瞄
tooltip.enable_aimbot=按住按键时平滑瞄准目标的经典自瞄。
text.aimkey=瞄准按键: %s
button.set_aimkey=设置瞄准按键
text.press_key_cancel=按任意键设置，或按 ESC 取消
tooltip.aimkey=设置按住激活自瞄的按键
checkbox.enable_silent_aimbot=启用静默自瞄
tooltip.enable_silent_aimbot=将烟雾弹与箭矢传送至你的目标。
checkbox.enable_teleporting_to_target=启用传送至目标
tooltip.enable_teleporting_to_target=直接传送到目标实体。
checkbox.avoid_teleporting_to_players=避免传送到玩家
tooltip.avoid_teleporting_to_players=不要传送到被选中的玩家。
checkbox.avoid_teleporting_when_players_near=附近有玩家时避免传送
tooltip.avoid_teleporting_when_players_near=若在目的地附近检测到玩家则不传送。
slider.avoidance_radius=避让半径
tooltip.avoidance_radius=传送到目标时与玩家保持的避让距离。
text.enable_inteliaim_notice=[ 启用 INTELIAIM 以查看 INTELITARGET 选项 ]
)";

    // 11 — 移动与传送
    static const char* ZH_11_MOVEMENT = R"(
# “移动与传送”选项卡 - 来自 Movement_TeleportSettings.h
header.movement_settings=移动设置
checkbox.enable_noclip=启用 Noclip
tooltip.enable_noclip=允许你飞行并穿过任何物体。
checkbox.enable_spinbot=启用 Spinbot
tooltip.enable_spinbot=让你的角色快速原地旋转，效果有趣！
slider.spinbot_speed=Spinbot 速度
tooltip.spinbot_speed=更改 Spinbot 的旋转速度。
text.movement_mode=移动模式
text.walking=步行
text.flying=飞行
text.fly_no_collision=无碰撞飞行
button.set_movement=设置
text.global_game_speed=全局游戏速度
text.walk_speed=步行速度
text.sprint_speed=奔跑速度
text.climbing_speed=攀爬速度
text.gliding_speed=滑翔速度
text.gliding_fall_speed=滑翔下落速度
text.jump_velocity=跳跃速度
text.max_jumps=最大跳跃次数
text.step_height=跨步高度

header.locations_coordinates=位置与坐标
text.teleport_list=传送列表
text.double_click_teleport=双击某个位置以传送
text.map=地图
text.current_coords=当前坐标
button.get_current_coordinates=获取当前坐标
button.teleport_to_coordinates=传送到坐标
text.travel_list=旅行列表
text.double_click_travel=双击某个位置以旅行
)";

    // 12 — 技能与工具：斧/镐
    static const char* ZH_12_SKILLS_AXE_PICK = R"(
# “技能与工具”选项卡 - 来自 Skills_ToolsSettings.h 及其子模块
header.axe_pickaxe_settings=斧与镐 设置
checkbox.auto_swing_tool=自动挥击工具
tooltip.auto_swing_tool=在你游玩时，自动砍伐或开采周围的资源。
checkbox.auto_equip_tool=自动装备工具
tooltip.auto_equip_tool=在靠近资源时自动装备你的斧/镐。
checkbox.require_esp_toggles_swing=需要 ESP 开关 (Swing)
tooltip.require_esp_toggles_swing=仅对已启用 ESP 的资源挥击。
checkbox.avoid_swinging_low_durability=低耐久时避免挥击
tooltip.avoid_swinging_low_durability=避免使用耐久度较低的工具。
checkbox.avoid_chopping_grove=避免在树林中砍伐
tooltip.avoid_chopping_grove=避免在其他 Flow 树附近砍伐 Flow 树。
checkbox.avoid_swinging_near_players=避免在玩家附近挥击
tooltip.avoid_swinging_near_players=避免在其他玩家附近使用工具。
checkbox.avoid_swinging_housing_plots=避免在宅基地挥击
tooltip.avoid_swinging_housing_plots=避免在宅基地上使用工具。
)";

    // 13 — 技能与工具：昆虫
    static const char* ZH_13_SKILLS_BUGS = R"(
header.bug_settings=捕虫设置
checkbox.auto_catch_bugs=自动捕虫
tooltip.auto_catch_bugs=当你佩戴虫腰带时，自动捕捉在设定距离内的昆虫
checkbox.auto_equip_smoke_bombs=自动装备烟雾弹
tooltip.auto_equip_smoke_bombs=在靠近昆虫时自动装备烟雾弹。
checkbox.require_esp_toggles_catch=需要 ESP 开关 (Catch)
tooltip.require_esp_toggles_catch=仅捕捉已启用 ESP 的昆虫。
checkbox.avoid_catching_low_durability=低耐久时避免捕捉
tooltip.avoid_catching_low_durability=避免使用低耐久工具捕虫。
text.catch_distance=捕捉距离
tooltip.catch_distance=更改自动捕捉的检测范围
checkbox.avoid_catching_near_players=避免在玩家附近捕捉
tooltip.avoid_catching_near_players=避免在其他玩家附近捕虫。
text.catching_speed=捕捉速度
text.speed_fast=快速
text.speed_medium=中等
text.speed_slow=慢速
text.speed_custom=自定义
text.custom_speed=自定义速度
)";

    // 14 — 技能与工具：动物/气球
    static const char* ZH_14_SKILLS_ANIMAL_BALLOON = R"(
header.animal_balloon_settings=动物 / 气球 设置
checkbox.auto_hunt=自动狩猎
tooltip.auto_hunt=当你持弓时，自动狩猎在设定距离内的动物或气球
checkbox.auto_equip_bow=自动装备弓
tooltip.auto_equip_bow=在靠近动物时自动装备你的弓。
checkbox.require_esp_toggles_hunt=需要 ESP 开关 (Hunt)
tooltip.require_esp_toggles_hunt=仅狩猎已启用 ESP 的动物/气球。
checkbox.avoid_hunting_low_durability=低耐久时避免狩猎
tooltip.avoid_hunting_low_durability=避免用低耐久进行狩猎。
text.hunt_distance=狩猎距离
tooltip.hunt_distance=更改自动狩猎的检测范围
checkbox.avoid_hunting_near_players=避免在玩家附近狩猎
tooltip.avoid_hunting_near_players=避免在其他玩家附近狩猎动物/气球。
text.hunting_speed=狩猎速度
)";

    // 15 — 技能与工具：其他
    static const char* ZH_15_SKILLS_OTHER = R"(
header.other_settings=其他设置
checkbox.auto_gather_nearby_loot=自动拾取附近战利品
tooltip.auto_gather_nearby_loot=在游玩时自动拾取（范围内的）可采集物。
checkbox.skip_cooking_minigames=跳过烹饪小游戏
tooltip.skip_cooking_minigames=完全跳过烹饪小游戏流程。
checkbox.auto_refill_focus=自动补充专注
tooltip.auto_refill_focus=消耗背包中最高专注值食物，且不超过最大专注。
text.when_below=当低于
tooltip.when_below=触发自动补充的专注百分比。
)";

    // 16 — 技能与工具：钓鱼
    static const char* ZH_16_SKILLS_FISHING = R"(
header.fishing_settings=钓鱼设置
checkbox.no_rod_durability_loss=鱼竿无耐久损耗
tooltip.no_rod_durability_loss=你的鱼竿永不损坏。
checkbox.enable_multiplayer_help=启用多人协助
tooltip.enable_multiplayer_help=强制与其他玩家一同钓鱼以获得额外任务进度。
checkbox.always_perfect_catch=始终完美上钩
tooltip.always_perfect_catch=钓鱼将总是获得完美上钩。
checkbox.instant_catch=瞬间上钩
tooltip.instant_catch=浮标入水瞬间即可钓起鱼类。
checkbox.auto_fast_fishing=自动极速钓鱼
tooltip.auto_fast_fishing=极快的钓鱼速度。与其他钓鱼功能搭配良好。
checkbox.require_holding_left_click=需要按住左键以自动钓鱼
tooltip.require_holding_left_click=需要按住鼠标左键以切换极速钓鱼。
checkbox.force_fishing_pool=强制鱼池
tooltip.force_fishing_pool=强制所有渔获来自所选鱼池。
text.equip_fishing_rod_notice=[ 装备鱼竿以查看极速钓鱼选项 ]
)";

    // 17 — 技能与工具：园艺
    static const char* ZH_17_SKILLS_GARDENING = R"(
header.gardening_settings=园艺设置
checkbox.auto_till=自动耕地
tooltip.auto_till=装备锄头后，耕作任何需要耕作的土壤。
checkbox.auto_weed=自动除草
tooltip.auto_weed=清理花园中的杂草。
checkbox.auto_harvest=自动收获
tooltip.auto_harvest=收获任何已成熟的作物。
checkbox.auto_replant=自动重新种植
tooltip.auto_replant=使用背包中的种子，在该地块重新种植之前的作物。
checkbox.auto_fertilize=自动施肥
tooltip.auto_fertilize=为任何未施肥的地块添加一份肥料。使用背包中找到的第一个肥料。
text.max_quantity=最大数量
tooltip.max_quantity=对单个地块可施加的肥料最大数量
)";

    // 18 — 商店与库存：库存操作
    static const char* ZH_18_STORE_INVENTORY_ACTIONS = R"(
# “商店与库存”选项卡 - 来自 Selling_PlayerSettings.h 与 Store_AutoSellSettings.h
header.inventory_actions=库存操作
text.inventory_slot_selector=物品栏槽位选择器
button.all=全部
text.amount=数量
text.backpack=背包
text.ammo_pouch=弹药袋
button.sell=出售
button.discard=丢弃
button.storage=存入仓库
button.duplicate=复制
)";

    // 19 — 商店与库存：自动出售
    static const char* ZH_19_STORE_AUTOSELL = R"(
header.auto_sell=自动出售
text.auto_sell_type=类型
text.auto_sell_common=普通
text.auto_sell_uncommon=较少见
text.auto_sell_rare=稀有
text.auto_sell_epic=史诗
text.auto_sell_sq=SQ
checkbox.bugs_auto_sell=昆虫
tooltip.bugs_auto_sell=自动出售背包中的昆虫。
checkbox.fish_auto_sell=鱼类
tooltip.fish_auto_sell=自动出售背包中的鱼类。
checkbox.forageables_auto_sell=可采集物
tooltip.forageables_auto_sell=自动出售背包中的可采集物。
checkbox.hunting_auto_sell=狩猎
tooltip.hunting_auto_sell=自动出售背包中的狩猎战利品。
text.tree_fiber=纤维
text.tree_sapwood=Sapwood
text.tree_heartwood=Heartwood
text.tree_flow=Flow
text.tree_ancient=Ancient
checkbox.trees_auto_sell=木材
tooltip.trees_auto_sell=自动出售背包中的原木。
checkbox.flowers_auto_sell=花朵
tooltip.flowers_auto_sell=自动出售背包中的花朵。
checkbox.junk_auto_sell=垃圾
tooltip.junk_auto_sell=自动出售钓起的垃圾。
)";

    // 20 — 商店与库存：远程商店
    static const char* ZH_20_STORE_REMOTE = R"(
header.stores=商店
checkbox.item_buy_multiplier=物品购买倍数
tooltip.item_buy_multiplier=允许更改每次购买的数量。
checkbox.enable_ctrl_click_buy=启用按住 CTRL 修改购买数量
tooltip.enable_ctrl_click_buy=需要按住 CTRL 键以购买修改后的堆叠数量。
text.amount_to_multiply=倍数
tooltip.amount_to_multiply=购买数量倍数
text.open_remote_stores=打开远程商店
button.open_guild_store=打开公会商店
button.open_building_store=打开建造商店
text.stores_night_notice=部分商店仅在夜间开放。
text.stores_hours_notice=在非营业时间打开将显示无库存，或显示先前打开的商店库存。
text.couldnt_retrieve_stores=无法获取商店。
)";

    // 21 — 商店与库存：玩家功能 / 自动开启 / 自动存储
    static const char* ZH_21_STORE_MISC = R"(
header.player_features=玩家功能
button.open_player_storage=打开玩家仓库

header.auto_open=自动开启
checkbox.waterlogged_chests=浸水宝箱
tooltip.waterlogged_chests=自动开启任何钓起的浸水宝箱。
checkbox.unopened_oysters=未开启的牡蛎
tooltip.unopened_oysters=自动开启任何采集到的未开启牡蛎。
checkbox.elder_clam_mushrooms=Elder Clam Mushrooms
tooltip.elder_clam_mushrooms=自动开启任何采集到的 Elder Clam Mushroom。

header.auto_storage=自动存储
checkbox.furniture_auto_storage=家具
tooltip.furniture_auto_storage=自动将装饰类物品发送到仓库。
)";

    // 22 — 模组与设置：角色
    static const char* ZH_22_MODS_CHARACTER = R"(
# “模组与设置”选项卡 - 来自 Mods_SettingsGlobal.h
header.character_settings=角色设置
checkbox.anti_afk=防挂机
tooltip.anti_afk=防止因不活动而断线，持续游戏。
checkbox.unlimited_wardrobe_respecs=无限衣柜重置
tooltip.unlimited_wardrobe_respecs=允许你在无冷却的情况下更改性别/外观。
checkbox.further_interaction_distance=更远的交互距离
tooltip.further_interaction_distance=可在更远距离与物体交互。
text.interaction_distance=交互距离
tooltip.interaction_distance=调整交互的最大距离。范围：1.0 到 99999.0
checkbox.teleport_to_waypoints=传送到航点
tooltip.teleport_to_waypoints=自动传送到你的航点位置。
checkbox.easy_quest_mode=简易任务模式
tooltip.easy_quest_mode=实验性——可能跳过部分任务要求。
)";

    // 23 — 模组与设置：界面
    static const char* ZH_23_MODS_UI = R"(
header.ui_settings=界面设置
checkbox.show_watermark=显示水印
tooltip.show_watermark=切换屏幕上自定义水印的显示。
text.select_theme=选择主题
button.edit_custom_theme=编辑自定义主题
tooltip.edit_custom_theme_disabled=请选择“自定义主题”以开始编辑。
popup.custom_theme_editor=自定义主题编辑器
text.widgets=组件
button.save=保存
button.close_without_saving=不保存并关闭
button.undo=撤销
text.undo_changes=撤销更改。
)";

    // 24 — 趣味设置
    static const char* ZH_24_FUN = R"(
header.fun_settings=趣味设置
checkbox.advanced_placement=高级摆放
tooltip.advanced_placement=允许在任意位置摆放住宅物品。
text.caps_lock_rotation=Caps Lock 旋转
tooltip.caps_lock_rotation=启用 Caps Lock 时，按此数值进行旋转。
checkbox.temporarily_unlock_outfits=临时解锁服装
tooltip.temporarily_unlock_outfits=临时解锁高级服装。
text.outfits_notice=要完成启用服装与收藏，请打开高级商店并等待其加载。
checkbox.temporarily_unlock_decor_tints=临时解锁所有装饰色调
tooltip.temporarily_unlock_decor_tints=在改造工作台临时解锁更多色调
checkbox.temporarily_unlock_landscapes=临时解锁景观
tooltip.temporarily_unlock_landscapes=允许你启用任意景观以进行预览。
checkbox.show_villager_weekly_gifts=显示所有村民每周礼物
tooltip.show_villager_weekly_gifts=无需自行探索，即可查看本周所有村民想要的礼物。
checkbox.unrepair_tool_for_gold=取消修理换取金币
tooltip.unrepair_tool_for_gold=取消修理所选工具，以换取最大数量金币。
text.max_unrepair_amount=最大取消修理数量
checkbox.fulfill_infinite_player_requests=无限完成玩家请求
tooltip.fulfill_infinite_player_requests=可完成任意数量的请求。可能需要多次尝试。
checkbox.black_market_prize_wheel=黑市奖品转盘
tooltip.black_market_prize_wheel=选择要接受的转盘位置。
checkbox.use_locked_storage=使用锁定仓库
tooltip.use_locked_storage=使用锁定仓库而非通用仓库。
text.prize_wheel_positions=转盘位置
text.prize_wheel_red_fireworks=0| 红色  - 烟花
text.prize_wheel_purple_decor=1| 紫色  - 装饰
text.prize_wheel_blue_ingredients=2| 蓝色  - 材料
text.prize_wheel_green_gold=3| 绿色  - 金币
text.prize_wheel_red_fireworks2=4| 红色  - 烟花
text.prize_wheel_brown_coins=5| 棕色  - 幸运币
text.prize_wheel_blue_ingredients2=6| 蓝色  - 材料
text.prize_wheel_green_gold2=7| 绿色  - 金币
text.prize_wheel_yellow_plushie=8| 黄色  - 毛绒玩具
)";

    // 25 — 语言选择与反馈
    static const char* ZH_25_KEYS_LANG = R"(
# 语言选择
combo.language=语言
tooltip.language=选择你的首选语言
note.translation_feedback=发现翻译错误？请在 Discord 告诉我们！
)";

    // 26 — 热键名称
    static const char* ZH_26_HOTKEY_NAMES = R"(
# 热键名称
key.no_key_set=未设置按键
key.left_mouse=鼠标左键
key.right_mouse=鼠标右键
key.middle_mouse=鼠标中键
key.side_mouse_1=鼠标侧键 1
key.side_mouse_2=鼠标侧键 2
key.unknown_key=未知按键
)";

    // 27 — 功能键
    static const char* ZH_27_FUNCTION_KEYS = R"(
# 功能键
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

    // 28 — 特殊 / 导航键
    static const char* ZH_28_SPECIAL_KEYS = R"(
# 特殊按键
key.caps_lock=大写锁定
key.scroll_lock=滚动锁定
key.num_lock=数字锁定
key.tab=Tab
key.space=空格
key.enter=回车
key.escape=Esc
key.backspace=退格
key.insert=Insert
key.delete=删除
key.home=Home
key.end=End
key.page_up=Page Up
key.page_down=Page Down
)";

    // 29 — 方向键与修饰键
    static const char* ZH_29_ARROWS_MODS = R"(
# 方向键
key.up_arrow=上箭头
key.down_arrow=下箭头
key.left_arrow=左箭头
key.right_arrow=右箭头

# 修饰键
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=左 Shift
key.right_shift=右 Shift
key.left_ctrl=左 Ctrl
key.right_ctrl=右 Ctrl
key.left_alt=左 Alt
key.right_alt=右 Alt
)";

    // 30 — 小键盘
    static const char* ZH_30_NUMPAD = R"(
# 小键盘
key.numpad_0=小键盘 0
key.numpad_1=小键盘 1
key.numpad_2=小键盘 2
key.numpad_3=小键盘 3
key.numpad_4=小键盘 4
key.numpad_5=小键盘 5
key.numpad_6=小键盘 6
key.numpad_7=小键盘 7
key.numpad_8=小键盘 8
key.numpad_9=小键盘 9
key.numpad_multiply=小键盘 *
key.numpad_add=小键盘 +
key.numpad_subtract=小键盘 -
key.numpad_decimal=小键盘 .
key.numpad_divide=小键盘 /
key.numpad_enter=小键盘回车
)";

    // 31 — 常用 UI 与通知
    static const char* ZH_31_COMMON_UI_AND_NOTIFS = R"(
# 常用 UI 元素
text.show=显示
text.color=颜色
text.normal=普通
text.star=星级
text.infected=感染
text.name=名称
text.type=类型
button.reset=R
text.waiting_game_load=等待游戏加载中……
text.waiting_in_game=等待进入游戏中……
text.waiting_character_init=等待角色初始化……

# 通知
notification.first_use=感谢使用我们的 Palia 工具。开始使用，请按下“INSERT”键打开菜单。
)";

    // -----------------------------
    // 最终拼接内容
    // -----------------------------
    static const char* CHINESE_CONTENT = []() {
        static std::string combined =
              std::string(ZH_01_MAIN_AND_VISUALS)
            + std::string(ZH_02_ANIMALS)
            + std::string(ZH_03_BUGS_META)
            + std::string(ZH_04_BUGS_LIST)
            + std::string(ZH_05_FORAGE_META)
            + std::string(ZH_06_FORAGE_LIST)
            + std::string(ZH_07_ORES)
            + std::string(ZH_08_TREES)
            + std::string(ZH_09_PLAYER_ENTITIES)
            + std::string(ZH_10_AIM)
            + std::string(ZH_11_MOVEMENT)
            + std::string(ZH_12_SKILLS_AXE_PICK)
            + std::string(ZH_13_SKILLS_BUGS)
            + std::string(ZH_14_SKILLS_ANIMAL_BALLOON)
            + std::string(ZH_15_SKILLS_OTHER)
            + std::string(ZH_16_SKILLS_FISHING)
            + std::string(ZH_17_SKILLS_GARDENING)
            + std::string(ZH_18_STORE_INVENTORY_ACTIONS)
            + std::string(ZH_19_STORE_AUTOSELL)
            + std::string(ZH_20_STORE_REMOTE)
            + std::string(ZH_21_STORE_MISC)
            + std::string(ZH_22_MODS_CHARACTER)
            + std::string(ZH_23_MODS_UI)
            + std::string(ZH_24_FUN)
            + std::string(ZH_25_KEYS_LANG)
            + std::string(ZH_26_HOTKEY_NAMES)
            + std::string(ZH_27_FUNCTION_KEYS)
            + std::string(ZH_28_SPECIAL_KEYS)
            + std::string(ZH_29_ARROWS_MODS)
            + std::string(ZH_30_NUMPAD)
            + std::string(ZH_31_COMMON_UI_AND_NOTIFS);
        return combined.c_str();
    }();
}
