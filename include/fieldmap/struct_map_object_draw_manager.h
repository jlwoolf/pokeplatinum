#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H

#include "struct_decls/map_object_manager.h"

#include "fieldmap/resource_heap.h"
#include "fieldmap/struct_map_object_draw_task_manager.h"

#include "billboard.h"
#include "resource_collection.h"

typedef struct MapObjectDrawManager_t {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20[8];
    int unk_40[8];
    int unk_60[32];
    BillboardList *unk_E0;
    BillboardResources *unk_E4;
    ResourceCollection *unk_E8;
    ResourceCollection *unk_EC;
    TextureResourceManager *unk_F0;
    BillboardResourceEntry *unk_F4;
    ResourceHeap *unk_F8;
    ResourceHeap *unk_FC;
    MapObjectDrawTaskManager *unk_100;
    const MapObjectManager *unk_104;
} MapObjectDrawManager;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H
