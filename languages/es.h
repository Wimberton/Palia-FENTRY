#pragma once
#include <string>
#include <cstring>

//
// Traducciones incrustadas al Español para Palia Overlay Tool
// Edita este archivo para actualizar las traducciones al español, luego recompila el DLL
//

namespace EmbeddedTranslations {

    // -----------------------------
    // Contenido fragmentado (tamaños seguros)
    // -----------------------------

    // 01 — Principal / Pestañas / Ajustes visuales
    static const char* ES_01_MAIN_AND_VISUALS = R"(# Archivo de Idioma Español para Palia Overlay Tool
# Formato: clave=valor

# Aplicación Principal
window.main_title=Herramienta de Superposición de Palia

# Nombres de Pestañas - de PaliaOverlay.cpp (BeginTabItem)
tab.esp_visuals=ESP y Visuales
tab.aim_assistants=Asistentes de Puntería
tab.movements_tps=Movimientos y TPs
tab.skills_tools=Habilidades y Herramientas
tab.stores_inventory=Tiendas e Inventario
tab.mods_settings=Mods y Configuración

# Pestaña ESP y Visuales
## Ajustes visuales - de ESP_VisualSettings.h
header.visual_settings=Configuración visual
checkbox.enable_esp=Habilitar ESP
tooltip.enable_esp=Habilita o deshabilita todas las funciones de ESP
slider.esp_distance=Distancia del ESP
tooltip.esp_distance=Cambia la distancia máxima de renderizado de tu ESP
slider.esp_text_scale=Escala del texto del ESP
tooltip.esp_text_scale=Ajusta la escala del tamaño del texto del ESP
checkbox.show_entity_distance=Mostrar distancia de entidades
tooltip.show_entity_distance=Muestra las distancias a tus entidades de ESP activadas
checkbox.show_entity_despawn_timers=Mostrar temporizadores de desaparición
tooltip.show_entity_despawn_timers=Muestra el tiempo restante en segundos antes de que un recurso desaparezca
checkbox.show_esps_on_world_map=Mostrar ESP en el mapa mundial
tooltip.show_esps_on_world_map=Muestra elementos de ESP en el mapa del mundo
checkbox.use_native_esp_icons=Usar iconos nativos de ESP
tooltip.use_native_esp_icons=Muestra iconos del juego en lugar de iconos de Font Awesome y texto en pantalla
checkbox.show_active_mods=Mostrar mods activos
tooltip.show_active_mods=Muestra una ventana superpuesta con tus mods actualmente activados
)";

    // 02 — Animales
    static const char* ES_02_ANIMALS = R"(
## Animales - de ESP_AnimalSettings.h
header.animals=Animales
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

    // 03 — Insectos (grupos/regiones)
    static const char* ES_03_BUGS_META = R"(
## Insectos - de ESP_BugSettings.h
header.bugs=Insectos
button.common_bugs=Comunes
button.uncommon_bugs=Poco comunes
button.rare_bugs=Raros
button.epic_bugs=Épicos
button.star_bugs=Con estrella
button.infected_bugs=Infectados
text.kilima_bugs=Kilima
text.kilima_bahari_bugs=Kilima y Bahari
text.bahari_bugs=Bahari Bay
text.elderwood_bugs=Elderwood
)";

    // 04 — Nombres individuales de insectos
    static const char* ES_04_BUGS_LIST = R"(
# Nombres individuales de insectos
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

    // 05 — Recolectables (meta)
    static const char* ES_05_FORAGE_META = R"(
## Recolectables - de ESP_ForageableSettings.h
header.forageables=Recolectables
button.common_forage=Comunes
button.uncommon_forage=Poco comunes
button.rare_forage=Raros
button.epic_forage=Épicos
button.star_forage=Con estrella
button.infected_forage=Infectados
text.kilima_forageables=Kilima
text.kilima_bahari_forageables=Kilima y Bahari
text.bahari_forageables=Bahari Bay
text.elderwood_forageables=Elderwood
)";

    // 06 — Recolectables (nombres)
    static const char* ES_06_FORAGE_LIST = R"(
# Nombres individuales de recolectables
# Región Kilima
text.crystal_lake_lotus=Crystal Lake Lotus
text.emerald_carpet_moss=Emerald Carpet Moss
text.spice_sprouts=Spice Sprouts
text.wild_ginger=Wild Ginger
text.wild_green_onion=Wild Green Onion

# Regiones Kilima y Bahari
text.mountain_morel=Mountain Morel
text.sundrop_lily=Sundrop Lily
text.wild_garlic=Wild Garlic

# Región Bahari
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

# Región Elderwood
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

    // 07 — Minerales
    static const char* ES_07_ORES = R"(
## Minerales - de ESP_OreSettings.h
header.ores=Minerales
button.clay=Arcilla
button.stone=Piedra
button.whitestone=Piedra blanca
button.copper=Cobre
button.iron=Hierro
button.silver=Plata
button.gold=Oro
button.palium=Palium
button.platinum=Platino
text.small=Peq
text.medium=Med
text.large=Gra
)";

    // 08 — Árboles
    static const char* ES_08_TREES = R"(
## Árboles - de ESP_TreeSettings.h
header.trees=Árboles
button.bush=Arbusto
button.sapwood=Sapwood
button.heartwood=Heartwood
button.flow=Flow
button.ancient=Ancient
button.infected_trees=Infectados
text.sapling=Sap
text.flow_infused=Infundido con Flow
)";

    // 09 — Jugador y Entidades
    static const char* ES_09_PLAYER_ENTITIES = R"(
## Jugador y Entidades - de ESP_SingleSettings.h
header.player_entities=Jugador y Entidades
button.toggle_all_misc=Alternar todo
text.players=Jugadores
text.npcs=NPCs
text.fish=Peces
text.fish_pools=Pozas de pesca
text.loot=Botín
text.quests=Misiones
text.rummage_piles=Montones de rebusca
text.treasure=Tesoro
text.stables=Establos
text.timed_drops=Botines temporizados
text.books_lost_relics=Libros y reliquias perdidas
text.unpurchased_furniture=Mobiliario no comprado
text.others=Otros
)";

    // 10 — Asistentes de Puntería
    static const char* ES_10_AIM = R"(
# Pestaña Asistentes de Puntería - de Aimbots_FunSettings.h
header.inteliaim_settings=Ajustes de InteliAim
checkbox.enable_inteliaim=Habilitar InteliAim
tooltip.enable_inteliaim=Habilita el sistema de puntería por FOV. Teletranspórtate a actores, habilita aimbots y más.
slider.inteliaim_radius=Radio de InteliAim
tooltip.inteliaim_radius=Haz más grande o más pequeña tu zona de puntería. Ajusta esto antes de Ocultar círculo.
checkbox.hide_circle=Ocultar círculo
tooltip.hide_circle=Usa el sistema InteliTarget sin mostrar el círculo de InteliAim.
slider.circle_transparency=Transparencia del círculo
tooltip.circle_transparency=Ajusta la transparencia del círculo de InteliAim.
checkbox.show_crosshair=Mostrar mira
tooltip.show_crosshair=Muestra una pequeña mira morada en el centro de la pantalla. Combina bien con Ocultar círculo.

header.intelitarget_settings=Ajustes de InteliTarget
checkbox.enable_aimbot=Habilitar Aimbot clásico
tooltip.enable_aimbot=Aimbot clásico que apunta suavemente a objetivos cuando se mantiene la tecla presionada.
text.aimkey=Tecla de Apuntado: %s
button.set_aimkey=Establecer Tecla de Apuntado
text.press_key_cancel=Presiona cualquier tecla para establecer, o ESC para cancelar
tooltip.aimkey=Establece la tecla a mantener presionada para activar el aimbot
checkbox.enable_silent_aimbot=Habilitar Aimbot silencioso
tooltip.enable_silent_aimbot=Teletransporta Bombas de Humo y Flechas a tu objetivo.
checkbox.enable_teleporting_to_target=Habilitar teletransporte al objetivo
tooltip.enable_teleporting_to_target=Teletranspórtate directamente a la entidad objetivo.
checkbox.avoid_teleporting_to_players=Evitar teletransportarse a jugadores
tooltip.avoid_teleporting_to_players=No te teletransportes a jugadores objetivo.
checkbox.avoid_teleporting_when_players_near=Evitar teletransportarse si hay jugadores cerca
tooltip.avoid_teleporting_when_players_near=No te teletransportes si se detecta un jugador cerca del destino.
slider.avoidance_radius=Radio de evitación
tooltip.avoidance_radius=La distancia para evitar jugadores al teletransportarte a un objetivo.
text.enable_inteliaim_notice=[ HABILITA INTELIAIM PARA VER LAS OPCIONES DE INTELITARGET ]
)";

    // 11 — Movimiento y TPs
    static const char* ES_11_MOVEMENT = R"(
# Pestaña Movimientos y TPs - de Movement_TeleportSettings.h
header.movement_settings=Ajustes de movimiento
checkbox.enable_noclip=Habilitar Noclip
tooltip.enable_noclip=Te permite volar y atravesar cualquier cosa.
checkbox.enable_spinbot=Habilitar Spinbot
tooltip.enable_spinbot=Hace girar tu personaje rápidamente en círculo; ¡se ve gracioso!
slider.spinbot_speed=Velocidad del Spinbot
tooltip.spinbot_speed=Cambia la velocidad de tu Spinbot.
text.movement_mode=Modo de movimiento
text.walking=Caminando
text.flying=Volando
text.fly_no_collision=Volar sin colisión
button.set_movement=Establecer
text.global_game_speed=Velocidad global del juego
text.walk_speed=Velocidad al caminar
text.sprint_speed=Velocidad al correr
text.climbing_speed=Velocidad de escalada
text.gliding_speed=Velocidad de planeo
text.gliding_fall_speed=Velocidad de caída en planeo
text.jump_velocity=Velocidad de salto
text.max_jumps=Saltos máximos
text.step_height=Altura del paso

header.locations_coordinates=Ubicaciones y coordenadas
text.teleport_list=Lista de teletransporte
text.double_click_teleport=Haz doble clic en una ubicación para teletransportarte
text.map=Mapa
text.current_coords=Coordenadas actuales
button.get_current_coordinates=Obtener coordenadas actuales
button.teleport_to_coordinates=Teletransportar a coordenadas
text.travel_list=Lista de viaje
text.double_click_travel=Haz doble clic en una ubicación para viajar
)";

    // 12 — Habilidades y Herramientas: Hacha/Pico
    static const char* ES_12_SKILLS_AXE_PICK = R"(
# Pestaña Habilidades y Herramientas - de Skills_ToolsSettings.h y submódulos
header.axe_pickaxe_settings=Ajustes de Hacha y Pico
checkbox.auto_swing_tool=Golpe automático con herramienta
tooltip.auto_swing_tool=Corta o mina recursos automáticamente a tu alrededor mientras juegas.
checkbox.auto_equip_tool=Equipar herramienta automáticamente
tooltip.auto_equip_tool=Equipa automáticamente tu Hacha/Pico al estar en rango de recursos.
checkbox.require_esp_toggles_swing=Requerir conmutadores del ESP (Swing)
tooltip.require_esp_toggles_swing=Golpea solo recursos con ESP habilitado.
checkbox.avoid_swinging_low_durability=Evitar golpear con baja durabilidad
tooltip.avoid_swinging_low_durability=Evita usar herramientas con baja durabilidad.
checkbox.avoid_chopping_grove=Evitar talar en arboleda
tooltip.avoid_chopping_grove=Evita talar árboles de Flow cerca de otros árboles de Flow.
checkbox.avoid_swinging_near_players=Evitar golpear cerca de jugadores
tooltip.avoid_swinging_near_players=Evita golpear herramientas cerca de otros jugadores.
checkbox.avoid_swinging_housing_plots=Evitar golpear en parcelas de vivienda
tooltip.avoid_swinging_housing_plots=Evita usar herramientas en parcelas de vivienda.
)";

    // 13 — Habilidades y Herramientas: Insectos
    static const char* ES_13_SKILLS_BUGS = R"(
header.bug_settings=Ajustes de caza de insectos
checkbox.auto_catch_bugs=Captura automática de insectos
tooltip.auto_catch_bugs=Captura automáticamente insectos dentro de la distancia configurada mientras llevas un cinturón de insectos activo
checkbox.auto_equip_smoke_bombs=Equipar Bombas de Humo automáticamente
tooltip.auto_equip_smoke_bombs=Equipa automáticamente tus Bombas de Humo al estar en rango de insectos.
checkbox.require_esp_toggles_catch=Requerir conmutadores del ESP (Catch)
tooltip.require_esp_toggles_catch=Captura solo insectos con ESP habilitado.
checkbox.avoid_catching_low_durability=Evitar capturar con baja durabilidad
tooltip.avoid_catching_low_durability=Evita capturar insectos con herramientas de baja durabilidad.
text.catch_distance=Distancia de captura
tooltip.catch_distance=Cambia la distancia del rango de detección de captura automática
checkbox.avoid_catching_near_players=Evitar capturar cerca de jugadores
tooltip.avoid_catching_near_players=Evita capturar insectos cerca de otros jugadores.
text.catching_speed=Velocidad de captura
text.speed_fast=Rápida
text.speed_medium=Media
text.speed_slow=Lenta
text.speed_custom=Personalizada
text.custom_speed=Velocidad personalizada
)";

    // 14 — Habilidades y Herramientas: Animales/Globos
    static const char* ES_14_SKILLS_ANIMAL_BALLOON = R"(
header.animal_balloon_settings=Ajustes de Animales / Globos
checkbox.auto_hunt=Caza automática
tooltip.auto_hunt=Caza automáticamente animales o globos dentro de la distancia configurada mientras llevas un arco activo
checkbox.auto_equip_bow=Equipar arco automáticamente
tooltip.auto_equip_bow=Equipa automáticamente tu Arco al estar en rango de animales.
checkbox.require_esp_toggles_hunt=Requerir conmutadores del ESP (Hunt)
tooltip.require_esp_toggles_hunt=Caza solo animales/globos con ESP habilitado.
checkbox.avoid_hunting_low_durability=Evitar cazar con baja durabilidad
tooltip.avoid_hunting_low_durability=Evita cazar animales/globos con baja durabilidad.
text.hunt_distance=Distancia de caza
tooltip.hunt_distance=Cambia la distancia del rango de detección de caza automática
checkbox.avoid_hunting_near_players=Evitar cazar cerca de jugadores
tooltip.avoid_hunting_near_players=Evita cazar animales/globos cerca de otros jugadores.
text.hunting_speed=Velocidad de caza
)";

    // 15 — Habilidades y Herramientas: Otros
    static const char* ES_15_SKILLS_OTHER = R"(
header.other_settings=Otros ajustes
checkbox.auto_gather_nearby_loot=Recoger botín cercano automáticamente
tooltip.auto_gather_nearby_loot=Recoge automáticamente recolectables (dentro del rango) mientras juegas.
checkbox.skip_cooking_minigames=Omitir minijuegos de cocina
tooltip.skip_cooking_minigames=Omite completamente el proceso del minijuego de cocina.
checkbox.auto_refill_focus=Rellenado automático de foco
tooltip.auto_refill_focus=Consume el alimento de foco de mayor valor en el inventario sin sobrepasar el foco máximo.
text.when_below=Cuando esté por debajo
tooltip.when_below=El porcentaje de foco al que se activará el rellenado automático.
)";

    // 16 — Habilidades y Herramientas: Pesca
    static const char* ES_16_SKILLS_FISHING = R"(
header.fishing_settings=Ajustes de pesca
checkbox.no_rod_durability_loss=Sin pérdida de durabilidad de la caña
tooltip.no_rod_durability_loss=Tu caña de pescar nunca se romperá.
checkbox.enable_multiplayer_help=Habilitar ayuda multijugador
tooltip.enable_multiplayer_help=Fuerza la pesca con otros jugadores para completar misiones extra.
checkbox.always_perfect_catch=Captura perfecta siempre
tooltip.always_perfect_catch=La pesca siempre resultará en una captura perfecta.
checkbox.instant_catch=Captura instantánea
tooltip.instant_catch=Captura peces en cuanto el flotador toca el agua.
checkbox.auto_fast_fishing=Pesca rápida automática
tooltip.auto_fast_fishing=Pescas extremadamente rápido. Combina bien con otras funciones de pesca.
checkbox.require_holding_left_click=Requerir mantener clic izquierdo para pesca automática
tooltip.require_holding_left_click=Requiere mantener presionado el botón izquierdo del ratón para activar la pesca rápida.
checkbox.force_fishing_pool=Forzar poza de pesca
tooltip.force_fishing_pool=Fuerza a que todas las capturas provengan de la poza seleccionada.
text.equip_fishing_rod_notice=[ EQUIPA LA CAÑA DE PESCAR PARA VER LAS OPCIONES DE PESCA RÁPIDA ]
)";

    // 17 — Habilidades y Herramientas: Jardinería
    static const char* ES_17_SKILLS_GARDENING = R"(
header.gardening_settings=Ajustes de jardinería
checkbox.auto_till=Labranza automática
tooltip.auto_till=Con la azada equipada, labra cualquier suelo que lo necesite.
checkbox.auto_weed=Desmalezado automático
tooltip.auto_weed=Limpia cualquier maleza de tu jardín.
checkbox.auto_harvest=Cosecha automática
tooltip.auto_harvest=Cosecha cualquier planta lista para recoger.
checkbox.auto_replant=Replantar automáticamente
tooltip.auto_replant=Usando semillas de tu inventario, replanta la planta anterior en esa parcela.
checkbox.auto_fertilize=Fertilizar automáticamente
tooltip.auto_fertilize=Añade un fertilizante a cualquier parcela sin fertilizar. Usa el primer fertilizante encontrado en tu inventario.
text.max_quantity=Cantidad máxima
tooltip.max_quantity=Cantidad máxima de fertilizante a aplicar en una parcela
)";

    // 18 — Tiendas e Inventario: Acciones de inventario
    static const char* ES_18_STORE_INVENTORY_ACTIONS = R"(
# Pestaña Tiendas e Inventario - de Selling_PlayerSettings.h y Store_AutoSellSettings.h
header.inventory_actions=Acciones de inventario
text.inventory_slot_selector=Selector de casilla de inventario
button.all=Todo
text.amount=Cantidad
text.backpack=Mochila
text.ammo_pouch=Cartuchera
button.sell=Vender
button.discard=Descartar
button.storage=Almacenar
button.duplicate=Duplicar
)";

    // 19 — Tiendas e Inventario: Venta automática
    static const char* ES_19_STORE_AUTOSELL = R"(
header.auto_sell=Venta automática
text.auto_sell_type=Tipo
text.auto_sell_common=Común
text.auto_sell_uncommon=Poco común
text.auto_sell_rare=Raro
text.auto_sell_epic=Épico
text.auto_sell_sq=SQ
checkbox.bugs_auto_sell=Insectos
tooltip.bugs_auto_sell=Vende automáticamente insectos de tu inventario.
checkbox.fish_auto_sell=Peces
tooltip.fish_auto_sell=Vende automáticamente peces de tu inventario.
checkbox.forageables_auto_sell=Recolectables
tooltip.forageables_auto_sell=Vende automáticamente recolectables de tu inventario.
checkbox.hunting_auto_sell=Caza
tooltip.hunting_auto_sell=Vende automáticamente botín de caza de tu inventario.
text.tree_fiber=Fibra
text.tree_sapwood=Sapwood
text.tree_heartwood=Heartwood
text.tree_flow=Flow
text.tree_ancient=Ancient
checkbox.trees_auto_sell=Troncos
tooltip.trees_auto_sell=Vende automáticamente troncos de tu inventario.
checkbox.flowers_auto_sell=Flores
tooltip.flowers_auto_sell=Vende automáticamente flores de tu inventario.
checkbox.junk_auto_sell=Chatarra
tooltip.junk_auto_sell=Vende automáticamente la chatarra pescada.
)";

    // 20 — Tiendas e Inventario: Tiendas (remotas)
    static const char* ES_20_STORE_REMOTE = R"(
header.stores=Tiendas
checkbox.item_buy_multiplier=Multiplicador de compra
tooltip.item_buy_multiplier=Permite cambiar cuántos artículos compras cada vez.
checkbox.enable_ctrl_click_buy=Habilitar CTRL-clic para comprar modificado
tooltip.enable_ctrl_click_buy=Requiere mantener CTRL para comprar la cantidad modificada.
text.amount_to_multiply=Cantidad a multiplicar
tooltip.amount_to_multiply=Multiplicador de compra
text.open_remote_stores=Abrir tiendas remotas
button.open_guild_store=Abrir Tienda del Gremio
button.open_building_store=Abrir Tienda de Construcción
text.stores_night_notice=Algunas tiendas solo están disponibles por la noche.
text.stores_hours_notice=Abrir fuera de horario mostrará sin inventario, o el inventario de una tienda abierta previamente.
text.couldnt_retrieve_stores=No se pudieron obtener las tiendas.
)";

    // 21 — Tiendas e Inventario: Funciones del jugador / Auto abrir / Auto almacenar
    static const char* ES_21_STORE_MISC = R"(
header.player_features=Funciones del jugador
button.open_player_storage=Abrir Almacén del Jugador

header.auto_open=Apertura automática
checkbox.waterlogged_chests=Cofres anegados
tooltip.waterlogged_chests=Abre automáticamente cualquier Cofre anegado pescado.
checkbox.unopened_oysters=Ostras sin abrir
tooltip.unopened_oysters=Abre automáticamente cualquier Ostra sin abrir recolectada.
checkbox.elder_clam_mushrooms=Elder Clam Mushrooms
tooltip.elder_clam_mushrooms=Abre automáticamente cualquier Elder Clam Mushroom recolectado.

header.auto_storage=Almacenamiento automático
checkbox.furniture_auto_storage=Mobiliario
tooltip.furniture_auto_storage=Envía automáticamente los artículos de Decoración al Almacén.
)";

    // 22 — Mods y Configuración: Personaje
    static const char* ES_22_MODS_CHARACTER = R"(
# Pestaña Mods y Configuración - de Mods_SettingsGlobal.h
header.character_settings=Ajustes de personaje
checkbox.anti_afk=Anti AFK
tooltip.anti_afk=Evita desconexiones por inactividad y juega sin parar.
checkbox.unlimited_wardrobe_respecs=Reasignaciones de vestuario ilimitadas
tooltip.unlimited_wardrobe_respecs=Te permite cambiar de género/apariencia sin tiempo de reutilización.
checkbox.further_interaction_distance=Mayor distancia de interacción
tooltip.further_interaction_distance=Interactúa con objetos desde mayores distancias.
text.interaction_distance=Distancia de interacción
tooltip.interaction_distance=Ajusta la distancia máxima para interacciones. Rango: 1.0 a 99999.0
checkbox.teleport_to_waypoints=Teletransportarse a puntos de ruta
tooltip.teleport_to_waypoints=Te teletransporta automáticamente a las ubicaciones de tus puntos de ruta.
checkbox.easy_quest_mode=Modo de misiones fácil
tooltip.easy_quest_mode=Experimental: puede omitir algunos requisitos de misiones.
)";

    // 23 — Mods y Configuración: Interfaz
    static const char* ES_23_MODS_UI = R"(
header.ui_settings=Ajustes de interfaz
checkbox.show_watermark=Mostrar marca de agua
tooltip.show_watermark=Activa o desactiva la marca de agua personalizada en pantalla.
text.select_theme=Seleccionar tema
button.edit_custom_theme=Editar tema personalizado
tooltip.edit_custom_theme_disabled=Selecciona 'Tema personalizado' para comenzar a editar.
popup.custom_theme_editor=Editor de tema personalizado
text.widgets=Widgets
button.save=Guardar
button.close_without_saving=Cerrar sin guardar
button.undo=Deshacer
text.undo_changes=Deshacer cambios.
)";

    // 24 — Ajustes divertidos
    static const char* ES_24_FUN = R"(
header.fun_settings=Ajustes divertidos
checkbox.advanced_placement=Colocación avanzada
tooltip.advanced_placement=Permite colocar objetos de vivienda en cualquier lugar.
text.caps_lock_rotation=Rotación con Bloq Mayús
tooltip.caps_lock_rotation=Con Bloq Mayús activado, rota por esta cantidad en su lugar.
checkbox.temporarily_unlock_outfits=Desbloquear temporalmente los atuendos
tooltip.temporarily_unlock_outfits=Desbloquea temporalmente los atuendos premium.
text.outfits_notice=Para terminar de habilitar atuendos y colecciones, debes abrir la Tienda Premium y dejar que cargue.
checkbox.temporarily_unlock_decor_tints=Desbloquear temporalmente todos los tintes de decoración
tooltip.temporarily_unlock_decor_tints=Desbloquea temporalmente tintes extra en el Banco de Modificación
checkbox.temporarily_unlock_landscapes=Desbloquear temporalmente paisajes
tooltip.temporarily_unlock_landscapes=Te permite activar cualquier paisaje para previsualizar.
checkbox.show_villager_weekly_gifts=Mostrar todos los regalos semanales de aldeanos
tooltip.show_villager_weekly_gifts=Muestra todos los regalos que quieren los aldeanos esta semana sin tener que descubrirlos.
checkbox.unrepair_tool_for_gold=Deshacer reparación de herramienta por oro
tooltip.unrepair_tool_for_gold=Deshace la reparación de la herramienta elegida para obtener el máximo oro a cambio.
text.max_unrepair_amount=Cantidad máxima de desreparación
checkbox.fulfill_infinite_player_requests=Completar solicitudes infinitas de jugadores
tooltip.fulfill_infinite_player_requests=Completa tantas solicitudes como quieras. Puede requerir varios intentos.
checkbox.black_market_prize_wheel=Ruleta de premios del mercado negro
tooltip.black_market_prize_wheel=Elige qué posiciones de la ruleta aceptar.
checkbox.use_locked_storage=Usar almacén bloqueado
tooltip.use_locked_storage=Usa el almacén bloqueado en lugar del almacén general.
text.prize_wheel_positions=Posiciones de la ruleta
text.prize_wheel_red_fireworks=0| Rojo   - Fuegos artificiales
text.prize_wheel_purple_decor=1| Morado - Decoración
text.prize_wheel_blue_ingredients=2| Azul   - Ingredientes
text.prize_wheel_green_gold=3| Verde  - Oro
text.prize_wheel_red_fireworks2=4| Rojo   - Fuegos artificiales
text.prize_wheel_brown_coins=5| Marrón - Monedas de la suerte
text.prize_wheel_blue_ingredients2=6| Azul   - Ingredientes
text.prize_wheel_green_gold2=7| Verde  - Oro
text.prize_wheel_yellow_plushie=8| Amarillo - Peluche
)";

    // 25 — Selector de idioma y feedback
    static const char* ES_25_KEYS_LANG = R"(
# Selección de idioma
combo.language=Idioma
tooltip.language=Selecciona tu idioma preferido
note.translation_feedback=¿Encontraste un error de traducción? ¡Avísanos en Discord!
)";

    // 26 — Nombres de teclas rápidas
    static const char* ES_26_HOTKEY_NAMES = R"(
# Nombres de teclas rápidas
key.no_key_set=Sin tecla asignada
key.left_mouse=Botón izquierdo del ratón
key.right_mouse=Botón derecho del ratón
key.middle_mouse=Botón central del ratón
key.side_mouse_1=Botón lateral del ratón 1
key.side_mouse_2=Botón lateral del ratón 2
key.unknown_key=Tecla desconocida
)";

    // 27 — Teclas de función
    static const char* ES_27_FUNCTION_KEYS = R"(
# Teclas de función
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

    // 28 — Teclas especiales / navegación
    static const char* ES_28_SPECIAL_KEYS = R"(
# Teclas especiales
key.caps_lock=Bloq Mayús
key.scroll_lock=Bloq Despl
key.num_lock=Bloq Num
key.tab=Tabulador
key.space=Espacio
key.enter=Enter
key.escape=Escape
key.backspace=Retroceso
key.insert=Insert
key.delete=Suprimir
key.home=Inicio
key.end=Fin
key.page_up=Re Pág
key.page_down=Av Pág
)";

    // 29 — Flechas y modificadores
    static const char* ES_29_ARROWS_MODS = R"(
# Teclas de flecha
key.up_arrow=Flecha arriba
key.down_arrow=Flecha abajo
key.left_arrow=Flecha izquierda
key.right_arrow=Flecha derecha

# Teclas modificadoras
key.shift=Mayús
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Mayús izquierda
key.right_shift=Mayús derecha
key.left_ctrl=Ctrl izquierda
key.right_ctrl=Ctrl derecha
key.left_alt=Alt izquierda
key.right_alt=Alt derecha
)";

    // 30 — Teclado numérico
    static const char* ES_30_NUMPAD = R"(
# Teclado numérico
key.numpad_0=Teclado numérico 0
key.numpad_1=Teclado numérico 1
key.numpad_2=Teclado numérico 2
key.numpad_3=Teclado numérico 3
key.numpad_4=Teclado numérico 4
key.numpad_5=Teclado numérico 5
key.numpad_6=Teclado numérico 6
key.numpad_7=Teclado numérico 7
key.numpad_8=Teclado numérico 8
key.numpad_9=Teclado numérico 9
key.numpad_multiply=Teclado numérico *
key.numpad_add=Teclado numérico +
key.numpad_subtract=Teclado numérico -
key.numpad_decimal=Teclado numérico .
key.numpad_divide=Teclado numérico /
key.numpad_enter=Enter del teclado numérico
)";

    // 31 — UI común y notificaciones
    static const char* ES_31_COMMON_UI_AND_NOTIFS = R"(
# Elementos comunes de UI
text.show=Mostrar
text.color=Color
text.normal=Normal
text.star=Estrella
text.infected=Infectado
text.name=Nombre
text.type=Tipo
button.reset=R
text.waiting_game_load=Esperando a que el juego cargue...
text.waiting_in_game=Esperando en el juego...
text.waiting_character_init=Esperando la inicialización del personaje...

# Notificaciones
notification.first_use=Gracias por usar nuestra herramienta de Palia. Para comenzar, abre el menú con la tecla 'INSERT'.
)";

    // -----------------------------
    // Contenido concatenado final
    // -----------------------------
    static const char* SPANISH_CONTENT = []() {
        static std::string combined =
              std::string(ES_01_MAIN_AND_VISUALS)
            + std::string(ES_02_ANIMALS)
            + std::string(ES_03_BUGS_META)
            + std::string(ES_04_BUGS_LIST)
            + std::string(ES_05_FORAGE_META)
            + std::string(ES_06_FORAGE_LIST)
            + std::string(ES_07_ORES)
            + std::string(ES_08_TREES)
            + std::string(ES_09_PLAYER_ENTITIES)
            + std::string(ES_10_AIM)
            + std::string(ES_11_MOVEMENT)
            + std::string(ES_12_SKILLS_AXE_PICK)
            + std::string(ES_13_SKILLS_BUGS)
            + std::string(ES_14_SKILLS_ANIMAL_BALLOON)
            + std::string(ES_15_SKILLS_OTHER)
            + std::string(ES_16_SKILLS_FISHING)
            + std::string(ES_17_SKILLS_GARDENING)
            + std::string(ES_18_STORE_INVENTORY_ACTIONS)
            + std::string(ES_19_STORE_AUTOSELL)
            + std::string(ES_20_STORE_REMOTE)
            + std::string(ES_21_STORE_MISC)
            + std::string(ES_22_MODS_CHARACTER)
            + std::string(ES_23_MODS_UI)
            + std::string(ES_24_FUN)
            + std::string(ES_25_KEYS_LANG)
            + std::string(ES_26_HOTKEY_NAMES)
            + std::string(ES_27_FUNCTION_KEYS)
            + std::string(ES_28_SPECIAL_KEYS)
            + std::string(ES_29_ARROWS_MODS)
            + std::string(ES_30_NUMPAD)
            + std::string(ES_31_COMMON_UI_AND_NOTIFS);
        return combined.c_str();
    }();
}
