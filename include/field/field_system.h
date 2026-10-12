#ifndef POKEPLATINUM_FIELD_SYSTEM_STRUCT_H
#define POKEPLATINUM_FIELD_SYSTEM_STRUCT_H

#include "struct_decls/map_object_manager.h"
#include "struct_decls/struct_0205B43C_decl.h"
#include "struct_decls/struct_0205C22C_decl.h"
#include "struct_defs/battle_tower.h"
#include "struct_defs/map_load_mode.h"

#include "applications/trade_room/defs.h"
#include "field/field_system_sub2_decl.h"
#include "fieldmap/area_data.h"
#include "fieldmap/area_light.h"
#include "fieldmap/dynamic_terrain_height.h"
#include "fieldmap/field_effect_manager.h"
#include "fieldmap/fog_manager.h"
#include "fieldmap/land_data_manager_decl.h"
#include "fieldmap/map_prop.h"
#include "fieldmap/map_prop_animation.h"
#include "fieldmap/model_attributes.h"
#include "fieldmap/fieldmap_021EAFA4.h"
#include "fieldmap/signpost.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0_sub1.h"
#include "underground/struct_underground_top_screen_context_decl.h"
#include "union_room_chat/union_room_chat_decl.h"

#include "bag.h"
#include "battle_regulation.h"
#include "bg_window.h"
#include "camera.h"
#include "field_task.h"
#include "journal.h"
#include "location.h"
#include "map_header_data.h"
#include "map_matrix.h"
#include "overlay_manager.h"
#include "player_avatar.h"
#include "pokedex_memory.h"
#include "pokeradar.h"
#include "savedata.h"
#include "terrain_attributes.h"
#include "terrain_collision_manager.h"

#define NUM_HONEY_TREES 21

typedef struct HoneyTreeShake {
    u8 shakeValue;
    BOOL isShaking;
} HoneyTreeShake;

typedef struct HoneyTreeShakeList {
    HoneyTreeShake trees[NUM_HONEY_TREES];
    int unused[NUM_HONEY_TREES];
} HoneyTreeShakeList;

typedef struct FieldWildBattleMetadata {
    u16 encounterAttempts;
    u16 wildMonDefeated;
} FieldWildBattleMetadata;

typedef struct FieldProcessManager {
    ApplicationManager *parent;
    ApplicationManager *child;
    BOOL pause;
    BOOL kill;
} FieldProcessManager;

#define MAP_OBJECT_PRELOAD_SENTINEL 0xFFFF
#define MAX_MAP_OBJECTS_TO_PRELOAD  24

typedef struct MapObjectsToPreload {
    u16 count;
    int ids[MAX_MAP_OBJECTS_TO_PRELOAD];
} MapObjectsToPreload;

typedef struct FieldSystem_t {
    FieldProcessManager *processManager;
    FieldSystem_sub2 *unk_04;
    BgConfig *bgConfig;
    SaveData *saveData;
    FieldTask *task;
    MapHeaderData *mapHeaderData;
    int bottomScreen;
    Location *location;
    int unk_20;
    Camera *camera;
    LandDataManager *landDataMan;
    MapMatrix *mapMatrix;
    AreaDataManager *areaDataManager;
    MapObjectsToPreload *mapObjectsToPreload;
    MapObjectManager *mapObjMan;
    PlayerAvatar *playerAvatar;
    FieldEffectManager *fieldEffMan;
    ModelAttributes *areaModelAttrs;
    FogManager *fogMan;
    AreaLightManager *areaLightMan;
    MapPropAnimationManager *mapPropAnimMan;
    MapPropOneShotAnimationManager *mapPropOneShotAnimMan;
    TerrainAttributes *terrainAttributes;
    const TerrainCollisionManager *terrainCollisionMan;
    BOOL skipMapAttributes;
    Signpost *signpost;
    BOOL runningFieldMap;
    UndergroundTopScreenContext *ugTopScreenCtx;
    int mapLoadType;
    const MapLoadMode *mapLoadMode;
    FieldWildBattleMetadata wildBattleMetadata;
    UnionRoom *unk_7C;
    UnionRoomTrainers *unk_80;
    UnionRoomChat *unk_84;
    TradeRoom *tradeRoom;
    UnkStruct_fieldmap_021EB0E0 *unk_8C;
    int menuCursorPos;
    RadarChain *chain;
    BagCursor *bagCursor;
    JournalEntry *journalEntry;
    DynamicTerrainHeightManager *dynamicTerrainHeightMan;
    MapPropManager *mapPropManager;
    HoneyTreeShakeList *unk_A8;
    BattleTower *battleTower;
    const BattleRegulation *battleRegulation;
    PokedexMemory *pokedexMemory;
    BOOL temporaryMapChange;
    u8 *battleSubscreenCursorOn;
    u32 unk_C0;
    WiFiPlazaLobbyCooldownTimestamp unk_C4;
} FieldSystem;

#endif // POKEPLATINUM_FIELD_SYSTEM_H
