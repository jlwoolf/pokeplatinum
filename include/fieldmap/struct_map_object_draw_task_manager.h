#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H

#include "fieldmap/struct_map_object_draw_manager.h"
#include "fieldmap/struct_map_object_texture_load_task.h"
#include "fieldmap/struct_map_object_texture_manager.h"
#include "fieldmap/struct_map_object_billboard_list.h"

#include "sys_task_manager.h"

typedef struct {
    s16 count;
    s16 maxTexturesPerFrame;
    vs16 loadedTextureCount;
    vu16 locked;
    MapObjectBillboardList *billboardLists;
    MapObjectTextureLoadTask *textureLoadTasks;
    MapObjectTextureManager *textureManagers;
    struct MapObjectDrawManager_t *drawManager;
    SysTask *textureLoadTask;
    SysTask *billboardProcessTask;
    SysTask *vBlankUploadTask;
    SysTask *afterVBlankTask;
} MapObjectDrawTaskManager;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H
