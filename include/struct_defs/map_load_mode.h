#ifndef POKEPLATINUM_STRUCT_MAP_LOAD_MODE_H
#define POKEPLATINUM_STRUCT_MAP_LOAD_MODE_H

typedef struct MapLoadMode {
    u32 fieldBottomScreen : 4;
    u32 skipMapAttributes : 4;
    u32 useSimpleTerrainCollisions : 4;
    u32 whichScreenIs3D : 4;
    u32 useSeparateTerrainAttributes : 4;
    u32 loadExtOverlay : 4;
    u32 separateTerrainAttributesBlockCount : 8;
    u32 flags;
} MapLoadMode;

#endif // POKEPLATINUM_STRUCT_MAP_LOAD_MODE_H
