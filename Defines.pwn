
// � 3096 �// LD_SPAC:tvcorn  // Dialog_TD
#define STREAMER_USE_DYNAMIC_TEXT3D_TAG

// DEFINES //
#define MAX_OBJETOS_BASES 200 // Maximum objects allowed per base
#define TIPO_OBJETO 0 // Object type: Generic object
#define TIPO_RECICLADORA 1 // Object type: Recycler
#define TIPO_MESA 2 // Object type: Craft table
#define TIPO_CADEIRA 3 // Object type: Chair
#define TIPO_ABAJU 4 // Object type: Lamp/Abajur
#define TIPO_JBL 5 // Object type: Speaker/JBL
#define TIPO_CAMA 6 // Object type: Bed
#define TIPO_BAU 7 // Object type: Chest/Loot box
#define TIPO_PORTAO 8 // Object type: Gate/Door
#define TIPO_CAIXA 9 // Object type: Box/Crate

#define MASCULINO 134 // Gender: Male skin ID
#define FEMININO 192 // Gender: Female skin ID
#define UPAR_BASE 2500 // Base level up cost in materials
#define DESCER_SALA 35.0 // Room descent/lower distance
#define MOVER_SALA 125.0 // Room movement distance
#define TIPO_COMIDA 55555 // Item type: Food
#define TIPO_BEBIDA 66666 // Item type: Beverage/Drink
#define TIPO_SUCATA 77777 // Item type: Scrap/Junk material
#define TIPO_SKIN 999 // Item type: Skin/Character model
#define TIPO_TINTA 123123 // Item type: Paint/Dye

#define UPAR_LEVEL 150 // Points needed to level up
#define AGUA_Z -0.000030 // Water surface Z-coordinate
#define PONTOS_RANK 250 // Points awarded per rank achievement

//  LIMITES DO SERVIDOR  //
#define MAX_VEICULOS 10000 // Maximum vehicles on server
#define MAX_PORTA_MALAS 36 // Maximum trunk slots per vehicle
#define MAX_BAUS 3000 // Maximum loot chests/boxes
#define MAX_EXPLOSIVOS 300 // Maximum explosives on server
#define MAX_JBL 1500 // Maximum speakers/sound systems
#define MAX_DROPS 70 // Maximum item drops on ground
#define MAX_CONTATOS 30 // Maximum contacts per player
#define MAX_LOBBY 50 // Maximum players in lobby
#define MAX_MESAS 3000 // Maximum craft tables
#define MAX_RECICLADORAS 3000 // Maximum recyclers on server
#define SLOTS_RECICLADORA 10 // Inventory slots per recycler
#define MAX_LOOT 3000 // Maximum loot containers
#define MAX_SLOT_LOOT 5 // Item slots per loot container
#define MAX_CARROS 300 // Maximum personal vehicles per player
#define MAX_OFICINAS    30 // Maximum garages/workshops
#define MAX_TUNINGS 15 // Maximum vehicle tuning options
#define MAX_MERCADO_NEGRO 50 // Maximum black markets on server
#define MAX_BOOTS 1000 // Maximum actors/NPCs on server
#define MAX_FOGUEIRAS 1000 // Maximum campfires
#define MAX_OBJETOS 25000 // Maximum objects on server
#define MAX_PORTOES 2500 // Maximum gates/doors on server
#define MAX_PORTOES_PLAYER 3 // Maximum gates per player
#define MAX_CAIXAS 2500 // Maximum boxes/crates
#define MAX_SLOTS 50 // Maximum inventory slots
#define MAX_MEMBROS 20 // Maximum members per faction/group
#define MAX_BASES 1000 // Maximum bases on server
#define MAX_ADMINS 50 // Maximum administrators
#define MAX_ROUNDS 9 // Maximum rounds in event/game
#define MAX_TEMPO_SALA 3*60 // Maximum room time in seconds
#define MAX_SALAS MAX_PLAYERS // Maximum rooms (matches player slots)
#define MAX_POSTOS 25 // Maximum gas stations
#define MAX_CAMERAS 1000 // Maximum security cameras
#define MAX_PEDRAS 2000 // Maximum rocks/stones
#define MAX_ARVORES 2000 // Maximum trees
#define MAX_SKINS 312 // Maximum available character skins
#define MAX_DIALOG_TEXTDRAW 250 // Maximum dialog text displays
#define MAX_ITENS 15000 // Maximum items on server
#define MAX_ZOMBIES 300 // Maximum zombies/NPCs

// anti bot
#define MAX_BOT_CONNECTIONS 6 // Maximum bot connections to prevent spam

// cadastros //
#define MAX_CADASTROS 3000 // Maximum account registrations


#define MAX_DANOS 500 // Maximum damage records



// Minas Terrestres //
#define MINA 19602 // Mine/landmine object model ID
#define MAX_MINAS 1000 // Maximum landmines on server



#define MAX_PASSE 10 // Maximum passes/tickets
#define UNI (512.0 - 408.0)/180 // Unit conversion factor


// SISTEMA DE ATENDIMENTO //
#define MAX_ATENDIMENTOS 50 // Maximum concurrent help/support sessions


// sistema menu //
#define MAX_MENU 1000 // Maximum menu options


// algumas definicoes //
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0))) // Macro to detect key press
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0))) // Macro to detect key release

#define barra_inteira (188.300018-116.499771) // Full progress bar width
#define barra_unidade barra_inteira/100 // Unit width for progress bar (1%)
