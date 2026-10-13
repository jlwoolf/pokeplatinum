#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H

#include "struct_decls/map_object_manager.h"

#include "fieldmap/resource_heap.h"
#include "fieldmap/struct_map_object_draw_task_manager.h"

#include "billboard.h"
#include "resource_collection.h"

typedef struct MapObjectDrawManager_t {
    int unk_00;
    int maxBillboards;
    int preloadedModelCount;
    int dynamicModelCount;
    int preloadedFrameSeqCount;
    int dynamicFrameSeqCount;
    int preloadedTextureCount;
    int dynamicTextureCount;
    int modelIDs[8];
    int frameSeqIDs[8];
    int textureIDs[32];
    BillboardList *billboardList;
    BillboardResources *billboardResources;
    ResourceCollection *modelResourceCollection;
    ResourceCollection *frameSeqResourceCollection;
    TextureResourceManager *textureResourceManager;
    BillboardResourceEntry *billboardResourceEntries;
    ResourceHeap *modelResourceHeap;
    ResourceHeap *frameSeqResourceHeap;
    MapObjectDrawTaskManager *drawTaskManager;
    const MapObjectManager *mapObjectManager;
} MapObjectDrawManager;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_MANAGER_H
