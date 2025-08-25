#pragma once
#include <string>
#include <cstring>

//
// Traduções incorporadas em Português para Palia Overlay Tool
// Edite este arquivo para atualizar as traduções para português, depois recompile o DLL
//

namespace EmbeddedTranslations {

    // -----------------------------
    // Conteúdo segmentado (tamanhos seguros)
    // -----------------------------

    // 01 — Principal / Abas / Configurações visuais
    static const char* PT_01_MAIN_AND_VISUALS = R"(# Arquivo de Idioma Português para Palia Overlay Tool
# Formato: chave=valor

# Aplicativo Principal
window.main_title=Ferramenta de Sobreposição do Palia

# Nomes das Abas - de PaliaOverlay.cpp (BeginTabItem)
tab.esp_visuals=ESP e Visuais
tab.aim_assistants=Assistentes de Mira
tab.movements_tps=Movimentos e TPs
tab.skills_tools=Habilidades e Ferramentas
tab.stores_inventory=Lojas e Inventário
tab.mods_settings=Mods e Configurações

# Aba ESP e Visuais
## Configurações visuais - de ESP_VisualSettings.h
header.visual_settings=Configurações visuais
checkbox.enable_esp=Habilitar ESP
tooltip.enable_esp=Habilita ou desabilita todas as funcionalidades de ESP
slider.esp_distance=Distância do ESP
tooltip.esp_distance=Altera a distância máxima de renderização do seu ESP
slider.esp_text_scale=Escala do texto do ESP
tooltip.esp_text_scale=Ajusta a escala do tamanho do texto do ESP
checkbox.show_entity_distance=Mostrar distância das entidades
tooltip.show_entity_distance=Exibe as distâncias para as entidades ativadas do seu ESP
checkbox.show_entity_despawn_timers=Mostrar temporizadores de desaparecimento
tooltip.show_entity_despawn_timers=Mostra o tempo restante em segundos antes de um recurso desaparecer
checkbox.show_esps_on_world_map=Mostrar ESP no mapa mundial
tooltip.show_esps_on_world_map=Exibe elementos de ESP no mapa do mundo
checkbox.use_native_esp_icons=Usar ícones nativos do ESP
tooltip.use_native_esp_icons=Mostra ícones do jogo em vez de ícones do Font Awesome e texto na tela
checkbox.show_active_mods=Mostrar mods ativos
tooltip.show_active_mods=Exibe uma janela sobreposta com seus mods atualmente ativados
)";

    // 02 — Animais
    static const char* PT_02_ANIMALS = R"(
## Animais - de ESP_AnimalSettings.h
header.animals=Animais
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

    // 03 — Insetos (grupos/regiões)
    static const char* PT_03_BUGS_META = R"(
## Insetos - de ESP_BugSettings.h
header.bugs=Insetos
button.common_bugs=Comuns
button.uncommon_bugs=Pouco comuns
button.rare_bugs=Raros
button.epic_bugs=Épicos
button.star_bugs=Com estrela
button.infected_bugs=Infectados
text.kilima_bugs=Kilima
text.kilima_bahari_bugs=Kilima e Bahari
text.bahari_bugs=Bahari Bay
text.elderwood_bugs=Elderwood
)";

    // 04 — Nomes individuais de insetos
    static const char* PT_04_BUGS_LIST = R"(
# Nomes individuais de insetos
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

    // 05 — Coletáveis (meta)
    static const char* PT_05_FORAGE_META = R"(
## Coletáveis - de ESP_ForageableSettings.h
header.forageables=Coletáveis
button.common_forage=Comuns
button.uncommon_forage=Pouco comuns
button.rare_forage=Raros
button.epic_forage=Épicos
button.star_forage=Com estrela
button.infected_forage=Infectados
text.kilima_forageables=Kilima
text.kilima_bahari_forageables=Kilima e Bahari
text.bahari_forageables=Bahari Bay
text.elderwood_forageables=Elderwood
)";

    // 06 — Coletáveis (nomes)
    static const char* PT_06_FORAGE_LIST = R"(
# Nomes individuais de coletáveis
# Região Kilima
text.crystal_lake_lotus=Crystal Lake Lotus
text.emerald_carpet_moss=Emerald Carpet Moss
text.spice_sprouts=Spice Sprouts
text.wild_ginger=Wild Ginger
text.wild_green_onion=Wild Green Onion

# Regiões Kilima e Bahari
text.mountain_morel=Mountain Morel
text.sundrop_lily=Sundrop Lily
text.wild_garlic=Wild Garlic

# Região Bahari
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

# Região Elderwood
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

    // 07 — Minérios
    static const char* PT_07_ORES = R"(
## Minérios - de ESP_OreSettings.h
header.ores=Minérios
button.clay=Argila
button.stone=Pedra
button.whitestone=Pedra branca
button.copper=Cobre
button.iron=Ferro
button.silver=Prata
button.gold=Ouro
button.palium=Palium
button.platinum=Platina
text.small=Peq
text.medium=Med
text.large=Gra
)";

    // 08 — Árvores
    static const char* PT_08_TREES = R"(
## Árvores - de ESP_TreeSettings.h
header.trees=Árvores
button.bush=Arbusto
button.sapwood=Sapwood
button.heartwood=Heartwood
button.flow=Flow
button.ancient=Ancient
button.infected_trees=Infectadas
text.sapling=Sap
text.flow_infused=Infundido com Flow
)";

    // 09 — Jogador e Entidades
    static const char* PT_09_PLAYER_ENTITIES = R"(
## Jogador e Entidades - de ESP_SingleSettings.h
header.player_entities=Jogador e Entidades
button.toggle_all_misc=Alternar tudo
text.players=Jogadores
text.npcs=NPCs
text.fish=Peixes
text.fish_pools=Poços de pesca
text.loot=Saque
text.quests=Missões
text.rummage_piles=Montes para vasculhar
text.treasure=Tesouro
text.stables=Estábulos
text.timed_drops=Drops temporizados
text.books_lost_relics=Livros e relíquias perdidas
text.unpurchased_furniture=Móveis não comprados
text.others=Outros
)";

    // 10 — Assistentes de Mira
    static const char* PT_10_AIM = R"(
# Aba Assistentes de Mira - de Aimbots_FunSettings.h
header.inteliaim_settings=Configurações do InteliAim
checkbox.enable_inteliaim=Habilitar InteliAim
tooltip.enable_inteliaim=Habilita o sistema de mira por FOV. Teleporte-se para atores, habilite aimbots e mais.
slider.inteliaim_radius=Raio do InteliAim
tooltip.inteliaim_radius=Aumente ou reduza sua área de mira. Ajuste isto antes de Ocultar círculo.
checkbox.hide_circle=Ocultar círculo
tooltip.hide_circle=Use o sistema InteliTarget sem exibir o círculo do InteliAim.
slider.circle_transparency=Transparência do círculo
tooltip.circle_transparency=Ajusta a transparência do círculo do InteliAim.
checkbox.show_crosshair=Mostrar mira
tooltip.show_crosshair=Exibe uma pequena mira roxa no centro da tela. Combina bem com Ocultar círculo.

header.intelitarget_settings=Configurações do InteliTarget
checkbox.enable_aimbot=Habilitar Aimbot clássico
tooltip.enable_aimbot=Aimbot clássico que mira suavemente nos alvos quando a tecla é mantida pressionada.
text.aimkey=Tecla de Mira: %s
button.set_aimkey=Definir Tecla de Mira
text.press_key_cancel=Pressione qualquer tecla para definir, ou ESC para cancelar
tooltip.aimkey=Define a tecla a ser mantida pressionada para ativação do aimbot
checkbox.enable_silent_aimbot=Habilitar Aimbot silencioso
tooltip.enable_silent_aimbot=Teletransporta Bombas de fumaça e Flechas para o seu alvo.
checkbox.enable_teleporting_to_target=Habilitar teletransporte para o alvo
tooltip.enable_teleporting_to_target=Teleporte-se diretamente para a entidade alvo.
checkbox.avoid_teleporting_to_players=Evitar teletransportar para jogadores
tooltip.avoid_teleporting_to_players=Não teletransportar para jogadores alvo.
checkbox.avoid_teleporting_when_players_near=Evitar teletransportar se houver jogadores por perto
tooltip.avoid_teleporting_when_players_near=Não teletransportar se um jogador for detectado perto do destino.
slider.avoidance_radius=Raio de evitação
tooltip.avoidance_radius=A distância para evitar jogadores ao teletransportar para um alvo.
text.enable_inteliaim_notice=[ HABILITE O INTELIAIM PARA VER AS OPÇÕES DO INTELITARGET ]
)";

    // 11 — Movimento e TPs
    static const char* PT_11_MOVEMENT = R"(
# Aba Movimentos e TPs - de Movement_TeleportSettings.h
header.movement_settings=Configurações de movimento
checkbox.enable_noclip=Habilitar Noclip
tooltip.enable_noclip=Permite voar e atravessar qualquer coisa.
checkbox.enable_spinbot=Habilitar Spinbot
tooltip.enable_spinbot=Faz seu personagem girar rapidamente em círculo; fica engraçado!
slider.spinbot_speed=Velocidade do Spinbot
tooltip.spinbot_speed=Altera a velocidade do seu Spinbot.
text.movement_mode=Modo de movimento
text.walking=Andando
text.flying=Voando
text.fly_no_collision=Voar sem colisão
button.set_movement=Definir
text.global_game_speed=Velocidade global do jogo
text.walk_speed=Velocidade ao caminhar
text.sprint_speed=Velocidade ao correr
text.climbing_speed=Velocidade de escalada
text.gliding_speed=Velocidade de planagem
text.gliding_fall_speed=Velocidade de queda em planagem
text.jump_velocity=Velocidade do salto
text.max_jumps=Saltos máximos
text.step_height=Altura do degrau

header.locations_coordinates=Localizações e coordenadas
text.teleport_list=Lista de teletransporte
text.double_click_teleport=Clique duas vezes em uma localização para teletransportar
text.map=Mapa
text.current_coords=Coordenadas atuais
button.get_current_coordinates=Obter coordenadas atuais
button.teleport_to_coordinates=Teletransportar para coordenadas
text.travel_list=Lista de viagem
text.double_click_travel=Clique duas vezes em uma localização para viajar
)";

    // 12 — Habilidades e Ferramentas: Machado/Picareta
    static const char* PT_12_SKILLS_AXE_PICK = R"(
# Aba Habilidades e Ferramentas - de Skills_ToolsSettings.h e submódulos
header.axe_pickaxe_settings=Configurações de Machado e Picareta
checkbox.auto_swing_tool=Golpear automaticamente com ferramenta
tooltip.auto_swing_tool=Corta ou minera recursos automaticamente ao seu redor enquanto joga.
checkbox.auto_equip_tool=Equipar ferramenta automaticamente
tooltip.auto_equip_tool=Equipa automaticamente seu Machado/Picareta ao estar no alcance de recursos.
checkbox.require_esp_toggles_swing=Exigir alternâncias do ESP (Swing)
tooltip.require_esp_toggles_swing=Golpear apenas recursos com ESP habilitado.
checkbox.avoid_swinging_low_durability=Evitar golpear com baixa durabilidade
tooltip.avoid_swinging_low_durability=Evita usar ferramentas com baixa durabilidade.
checkbox.avoid_chopping_grove=Evitar cortar no bosque
tooltip.avoid_chopping_grove=Evita cortar árvores de Flow perto de outras árvores de Flow.
checkbox.avoid_swinging_near_players=Evitar golpear perto de jogadores
tooltip.avoid_swinging_near_players=Evita usar ferramentas perto de outros jogadores.
checkbox.avoid_swinging_housing_plots=Evitar golpear em lotes residenciais
tooltip.avoid_swinging_housing_plots=Evita usar ferramentas em lotes residenciais.
)";

    // 13 — Habilidades e Ferramentas: Insetos
    static const char* PT_13_SKILLS_BUGS = R"(
header.bug_settings=Configurações de caça a insetos
checkbox.auto_catch_bugs=Captura automática de insetos
tooltip.auto_catch_bugs=Captura automaticamente insetos dentro da distância definida enquanto você usa um cinto de insetos ativo
checkbox.auto_equip_smoke_bombs=Equipar Bombas de fumaça automaticamente
tooltip.auto_equip_smoke_bombs=Equipa automaticamente suas Bombas de fumaça ao estar no alcance de insetos.
checkbox.require_esp_toggles_catch=Exigir alternâncias do ESP (Catch)
tooltip.require_esp_toggles_catch=Captura apenas insetos com ESP habilitado.
checkbox.avoid_catching_low_durability=Evitar capturar com baixa durabilidade
tooltip.avoid_catching_low_durability=Evita capturar insetos com ferramentas de baixa durabilidade.
text.catch_distance=Distância de captura
tooltip.catch_distance=Altera a distância do alcance de detecção da captura automática
checkbox.avoid_catching_near_players=Evitar capturar perto de jogadores
tooltip.avoid_catching_near_players=Evita capturar insetos perto de outros jogadores.
text.catching_speed=Velocidade de captura
text.speed_fast=Rápida
text.speed_medium=Média
text.speed_slow=Lenta
text.speed_custom=Personalizada
text.custom_speed=Velocidade personalizada
)";

    // 14 — Habilidades e Ferramentas: Animais/Balões
    static const char* PT_14_SKILLS_ANIMAL_BALLOON = R"(
header.animal_balloon_settings=Configurações de Animais / Balões
checkbox.auto_hunt=Caça automática
tooltip.auto_hunt=Caça automaticamente animais ou balões dentro da distância definida enquanto você usa um arco ativo
checkbox.auto_equip_bow=Equipar arco automaticamente
tooltip.auto_equip_bow=Equipa automaticamente seu Arco ao estar no alcance de animais.
checkbox.require_esp_toggles_hunt=Exigir alternâncias do ESP (Hunt)
tooltip.require_esp_toggles_hunt=Caça apenas animais/balões com ESP habilitado.
checkbox.avoid_hunting_low_durability=Evitar caçar com baixa durabilidade
tooltip.avoid_hunting_low_durability=Evita caçar animais/balões com baixa durabilidade.
text.hunt_distance=Distância de caça
tooltip.hunt_distance=Altera a distância do alcance de detecção da caça automática
checkbox.avoid_hunting_near_players=Evitar caçar perto de jogadores
tooltip.avoid_hunting_near_players=Evita caçar animais/balões perto de outros jogadores.
text.hunting_speed=Velocidade de caça
)";

    // 15 — Habilidades e Ferramentas: Outros
    static const char* PT_15_SKILLS_OTHER = R"(
header.other_settings=Outras configurações
checkbox.auto_gather_nearby_loot=Coletar saque próximo automaticamente
tooltip.auto_gather_nearby_loot=Coleta automaticamente coletáveis (dentro do alcance) enquanto você joga.
checkbox.skip_cooking_minigames=Pular minijogos de cozinha
tooltip.skip_cooking_minigames=Ignora completamente o processo do minijogo de cozinha.
checkbox.auto_refill_focus=Reabastecer Foco automaticamente
tooltip.auto_refill_focus=Consome o alimento de foco de maior valor no inventário sem ultrapassar o foco máximo.
text.when_below=Quando abaixo
tooltip.when_below=A porcentagem de foco na qual o reabastecimento automático será acionado.
)";

    // 16 — Habilidades e Ferramentas: Pesca
    static const char* PT_16_SKILLS_FISHING = R"(
header.fishing_settings=Configurações de pesca
checkbox.no_rod_durability_loss=Sem perda de durabilidade da vara
tooltip.no_rod_durability_loss=Sua vara de pescar nunca quebrará.
checkbox.enable_multiplayer_help=Ativar ajuda multijogador
tooltip.enable_multiplayer_help=Força a pescaria com outros jogadores para completar missões extras.
checkbox.always_perfect_catch=Captura perfeita sempre
tooltip.always_perfect_catch=A pescaria sempre resultará em uma captura perfeita.
checkbox.instant_catch=Captura instantânea
tooltip.instant_catch=Captura peixes assim que o flutuador tocar a água.
checkbox.auto_fast_fishing=Pesca rápida automática
tooltip.auto_fast_fishing=Pescaria extremamente rápida. Combina bem com outras funcionalidades de pesca.
checkbox.require_holding_left_click=Exigir manter clique esquerdo para pesca automática
tooltip.require_holding_left_click=Exige manter o botão esquerdo do mouse pressionado para alternar a pesca rápida.
checkbox.force_fishing_pool=Forçar poça de pesca
tooltip.force_fishing_pool=Força que todas as capturas sejam da poça selecionada.
text.equip_fishing_rod_notice=[ EQUIPE A VARA DE PESCA PARA VER AS OPÇÕES DE PESCA RÁPIDA ]
)";

    // 17 — Habilidades e Ferramentas: Jardinagem
    static const char* PT_17_SKILLS_GARDENING = R"(
header.gardening_settings=Configurações de jardinagem
checkbox.auto_till=Arar automaticamente
tooltip.auto_till=Com a enxada equipada, ara qualquer solo que precise.
checkbox.auto_weed=Capinar automaticamente
tooltip.auto_weed=Remove quaisquer ervas daninhas do seu jardim.
checkbox.auto_harvest=Colheita automática
tooltip.auto_harvest=Colhe qualquer planta pronta para ser recolhida.
checkbox.auto_replant=Replantar automaticamente
tooltip.auto_replant=Usando sementes do seu inventário, replanta a planta anterior naquele lote.
checkbox.auto_fertilize=Fertilizar automaticamente
tooltip.auto_fertilize=Adiciona um fertilizante a qualquer lote não fertilizado. Usa o primeiro fertilizante encontrado no seu inventário.
text.max_quantity=Quantidade máxima
tooltip.max_quantity=Quantidade máxima de fertilizante a aplicar em um lote
)";

    // 18 — Lojas e Inventário: Ações de inventário
    static const char* PT_18_STORE_INVENTORY_ACTIONS = R"(
# Aba Lojas e Inventário - de Selling_PlayerSettings.h e Store_AutoSellSettings.h
header.inventory_actions=Ações de inventário
text.inventory_slot_selector=Seletor de espaço do inventário
button.all=Todos
text.amount=Quantidade
text.backpack=Mochila
text.ammo_pouch=Bolsa de munição
button.sell=Vender
button.discard=Descartar
button.storage=Armazenar
button.duplicate=Duplicar
)";

    // 19 — Lojas e Inventário: Venda automática
    static const char* PT_19_STORE_AUTOSELL = R"(
header.auto_sell=Venda automática
text.auto_sell_type=Tipo
text.auto_sell_common=Comum
text.auto_sell_uncommon=Pouco comum
text.auto_sell_rare=Raro
text.auto_sell_epic=Épico
text.auto_sell_sq=SQ
checkbox.bugs_auto_sell=Insetos
tooltip.bugs_auto_sell=Vende automaticamente insetos do seu inventário.
checkbox.fish_auto_sell=Peixes
tooltip.fish_auto_sell=Vende automaticamente peixes do seu inventário.
checkbox.forageables_auto_sell=Coletáveis
tooltip.forageables_auto_sell=Vende automaticamente coletáveis do seu inventário.
checkbox.hunting_auto_sell=Caça
tooltip.hunting_auto_sell=Vende automaticamente o saque de caça do seu inventário.
text.tree_fiber=Fibra
text.tree_sapwood=Sapwood
text.tree_heartwood=Heartwood
text.tree_flow=Flow
text.tree_ancient=Ancient
checkbox.trees_auto_sell=Troncos
tooltip.trees_auto_sell=Vende automaticamente troncos do seu inventário.
checkbox.flowers_auto_sell=Flores
tooltip.flowers_auto_sell=Vende automaticamente flores do seu inventário.
checkbox.junk_auto_sell=Sucata
tooltip.junk_auto_sell=Vende automaticamente a sucata pescada.
)";

    // 20 — Lojas e Inventário: Lojas (remotas)
    static const char* PT_20_STORE_REMOTE = R"(
header.stores=Lojas
checkbox.item_buy_multiplier=Multiplicador de compra
tooltip.item_buy_multiplier=Permite alterar quantos itens você compra cada vez.
checkbox.enable_ctrl_click_buy=Habilitar CTRL-Clique para compra modificada
tooltip.enable_ctrl_click_buy=Exige manter CTRL pressionado para comprar a quantidade modificada.
text.amount_to_multiply=Quantidade a multiplicar
tooltip.amount_to_multiply=Multiplicador de compra
text.open_remote_stores=Abrir lojas remotas
button.open_guild_store=Abrir Loja da Guilda
button.open_building_store=Abrir Loja de Construção
text.stores_night_notice=Algumas lojas estão disponíveis somente à noite.
text.stores_hours_notice=Abrir fora do horário exibirá nenhum inventário, ou o inventário da última loja aberta.
text.couldnt_retrieve_stores=Não foi possível obter as lojas.
)";

    // 21 — Lojas e Inventário: Recursos do jogador / Abertura automática / Armazenamento automático
    static const char* PT_21_STORE_MISC = R"(
header.player_features=Recursos do jogador
button.open_player_storage=Abrir Armazenamento do Jogador

header.auto_open=Abertura automática
checkbox.waterlogged_chests=Baús encharcados
tooltip.waterlogged_chests=Abre automaticamente qualquer Baú encharcado pescado.
checkbox.unopened_oysters=Ostras não abertas
tooltip.unopened_oysters=Abre automaticamente qualquer Ostra não aberta coletada.
checkbox.elder_clam_mushrooms=Elder Clam Mushrooms
tooltip.elder_clam_mushrooms=Abre automaticamente qualquer Elder Clam Mushroom coletado.

header.auto_storage=Armazenamento automático
checkbox.furniture_auto_storage=Mobília
tooltip.furniture_auto_storage=Envia automaticamente itens de Decoração para o Armazenamento.
)";

    // 22 — Mods e Configurações: Personagem
    static const char* PT_22_MODS_CHARACTER = R"(
# Aba Mods e Configurações - de Mods_SettingsGlobal.h
header.character_settings=Configurações do personagem
checkbox.anti_afk=Anti AFK
tooltip.anti_afk=Evita desconexões por inatividade e permite jogar indefinidamente.
checkbox.unlimited_wardrobe_respecs=Reatribuições de guarda-roupa ilimitadas
tooltip.unlimited_wardrobe_respecs=Permite alterar gênero/aparência sem tempo de recarga.
checkbox.further_interaction_distance=Maior distância de interação
tooltip.further_interaction_distance=Interaja com coisas a distâncias maiores.
text.interaction_distance=Distância de interação
tooltip.interaction_distance=Ajusta a distância máxima para interações. Faixa: 1.0 a 99999.0
checkbox.teleport_to_waypoints=Teletransportar para pontos de rota
tooltip.teleport_to_waypoints=Teletransporta você automaticamente para as localizações dos seus pontos de rota.
checkbox.easy_quest_mode=Modo de missões fácil
tooltip.easy_quest_mode=Experimental — pode pular alguns requisitos de missões.
)";

    // 23 — Mods e Configurações: Interface
    static const char* PT_23_MODS_UI = R"(
header.ui_settings=Configurações da interface
checkbox.show_watermark=Mostrar marca d'água
tooltip.show_watermark=Alterna a exibição da marca d'água personalizada na tela.
text.select_theme=Selecionar tema
button.edit_custom_theme=Editar tema personalizado
tooltip.edit_custom_theme_disabled=Selecione 'Tema personalizado' para começar a editar.
popup.custom_theme_editor=Editor de tema personalizado
text.widgets=Widgets
button.save=Salvar
button.close_without_saving=Fechar sem salvar
button.undo=Desfazer
text.undo_changes=Desfazer alterações.
)";

    // 24 — Configurações divertidas
    static const char* PT_24_FUN = R"(
header.fun_settings=Configurações divertidas
checkbox.advanced_placement=Colocação avançada
tooltip.advanced_placement=Permite posicionar itens de moradia em qualquer lugar.
text.caps_lock_rotation=Rotação com Caps Lock
tooltip.caps_lock_rotation=Com Caps Lock ativo, rotaciona por esta quantidade em vez disso.
checkbox.temporarily_unlock_outfits=Desbloquear temporariamente trajes
tooltip.temporarily_unlock_outfits=Desbloqueia temporariamente trajes premium.
text.outfits_notice=Para concluir a habilitação de trajes e coleções, abra a Loja Premium e aguarde o carregamento.
checkbox.temporarily_unlock_decor_tints=Desbloquear temporariamente todos os tons de decoração
tooltip.temporarily_unlock_decor_tints=Desbloqueia temporariamente tons extras na Bancada de Modificação
checkbox.temporarily_unlock_landscapes=Desbloquear temporariamente paisagens
tooltip.temporarily_unlock_landscapes=Permite ativar qualquer paisagem para pré-visualização.
checkbox.show_villager_weekly_gifts=Mostrar todos os presentes semanais dos aldeões
tooltip.show_villager_weekly_gifts=Mostra todos os presentes que os aldeões querem nesta semana sem precisar descobri-los.
checkbox.unrepair_tool_for_gold=Desfazer reparo da ferramenta por ouro
tooltip.unrepair_tool_for_gold=Desfaz o reparo da ferramenta escolhida para obter o máximo de ouro em troca.
text.max_unrepair_amount=Quantidade máxima de desreparo
checkbox.fulfill_infinite_player_requests=Atender infinitos pedidos de jogadores
tooltip.fulfill_infinite_player_requests=Atende quantos pedidos você quiser. Pode exigir várias tentativas.
checkbox.black_market_prize_wheel=Roleta de prêmios do mercado negro
tooltip.black_market_prize_wheel=Escolha quais posições da roleta aceitar.
checkbox.use_locked_storage=Usar armazenamento bloqueado
tooltip.use_locked_storage=Usa o armazenamento bloqueado em vez do armazenamento geral.
text.prize_wheel_positions=Posições da roleta
text.prize_wheel_red_fireworks=0| Vermelho - Fogos de artifício
text.prize_wheel_purple_decor=1| Roxo    - Decoração
text.prize_wheel_blue_ingredients=2| Azul     - Ingredientes
text.prize_wheel_green_gold=3| Verde   - Ouro
text.prize_wheel_red_fireworks2=4| Vermelho - Fogos de artifício
text.prize_wheel_brown_coins=5| Marrom  - Moedas da sorte
text.prize_wheel_blue_ingredients2=6| Azul     - Ingredientes
text.prize_wheel_green_gold2=7| Verde   - Ouro
text.prize_wheel_yellow_plushie=8| Amarelo - Bichinho de pelúcia
)";

    // 25 — Seletor de idioma e feedback
    static const char* PT_25_KEYS_LANG = R"(
# Seleção de idioma
combo.language=Idioma
tooltip.language=Selecione seu idioma preferido
note.translation_feedback=Encontrou um erro de tradução? Avise-nos no Discord!
)";

    // 26 — Nomes de teclas de atalho
    static const char* PT_26_HOTKEY_NAMES = R"(
# Nomes de teclas de atalho
key.no_key_set=Sem tecla definida
key.left_mouse=Botão esquerdo do mouse
key.right_mouse=Botão direito do mouse
key.middle_mouse=Botão do meio do mouse
key.side_mouse_1=Botão lateral do mouse 1
key.side_mouse_2=Botão lateral do mouse 2
key.unknown_key=Tecla desconhecida
)";

    // 27 — Teclas de função
    static const char* PT_27_FUNCTION_KEYS = R"(
# Teclas de função
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

    // 28 — Teclas especiais / navegação
    static const char* PT_28_SPECIAL_KEYS = R"(
# Teclas especiais
key.caps_lock=Caps Lock
key.scroll_lock=Scroll Lock
key.num_lock=Num Lock
key.tab=Tab
key.space=Espaço
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

    // 29 — Setas e modificadoras
    static const char* PT_29_ARROWS_MODS = R"(
# Teclas de seta
key.up_arrow=Seta para cima
key.down_arrow=Seta para baixo
key.left_arrow=Seta para a esquerda
key.right_arrow=Seta para a direita

# Teclas modificadoras
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Shift esquerdo
key.right_shift=Shift direito
key.left_ctrl=Ctrl esquerdo
key.right_ctrl=Ctrl direito
key.left_alt=Alt esquerdo
key.right_alt=Alt direito
)";

    // 30 — Teclado numérico
    static const char* PT_30_NUMPAD = R"(
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
key.numpad_enter=Enter do teclado numérico
)";

    // 31 — UI comum e notificações
    static const char* PT_31_COMMON_UI_AND_NOTIFS = R"(
# Elementos comuns de UI
text.show=Mostrar
text.color=Cor
text.normal=Normal
text.star=Estrela
text.infected=Infectado
text.name=Nome
text.type=Tipo
button.reset=R
text.waiting_game_load=Aguardando o carregamento do jogo...
text.waiting_in_game=Aguardando dentro do jogo...
text.waiting_character_init=Aguardando a inicialização do personagem...

# Notificações
notification.first_use=Obrigado por usar nossa Ferramenta do Palia. Para começar, abra o menu com a tecla 'INSERT'.
)";

    // -----------------------------
    // Conteúdo concatenado final
    // -----------------------------
    static const char* PORTUGUESE_CONTENT = []() {
        static std::string combined =
              std::string(PT_01_MAIN_AND_VISUALS)
            + std::string(PT_02_ANIMALS)
            + std::string(PT_03_BUGS_META)
            + std::string(PT_04_BUGS_LIST)
            + std::string(PT_05_FORAGE_META)
            + std::string(PT_06_FORAGE_LIST)
            + std::string(PT_07_ORES)
            + std::string(PT_08_TREES)
            + std::string(PT_09_PLAYER_ENTITIES)
            + std::string(PT_10_AIM)
            + std::string(PT_11_MOVEMENT)
            + std::string(PT_12_SKILLS_AXE_PICK)
            + std::string(PT_13_SKILLS_BUGS)
            + std::string(PT_14_SKILLS_ANIMAL_BALLOON)
            + std::string(PT_15_SKILLS_OTHER)
            + std::string(PT_16_SKILLS_FISHING)
            + std::string(PT_17_SKILLS_GARDENING)
            + std::string(PT_18_STORE_INVENTORY_ACTIONS)
            + std::string(PT_19_STORE_AUTOSELL)
            + std::string(PT_20_STORE_REMOTE)
            + std::string(PT_21_STORE_MISC)
            + std::string(PT_22_MODS_CHARACTER)
            + std::string(PT_23_MODS_UI)
            + std::string(PT_24_FUN)
            + std::string(PT_25_KEYS_LANG)
            + std::string(PT_26_HOTKEY_NAMES)
            + std::string(PT_27_FUNCTION_KEYS)
            + std::string(PT_28_SPECIAL_KEYS)
            + std::string(PT_29_ARROWS_MODS)
            + std::string(PT_30_NUMPAD)
            + std::string(PT_31_COMMON_UI_AND_NOTIFS);
        return combined.c_str();
    }();
}
