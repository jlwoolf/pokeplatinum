#ifndef POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H
#define POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H

#include "fieldmap/struct_map_object_draw_manager.h"
#include "fieldmap/struct_map_object_texture_load_task.h"
#include "fieldmap/struct_map_object_texture_manager.h"
#include "fieldmap/struct_map_object_billboard_list.h"

#include "sys_task_manager.h"

typedef struct {
    s16 unk_00;
    s16 unk_02;
    vs16 unk_04;
    vu16 unk_06;
    MapObjectBillboardList *unk_08;
    MapObjectTextureLoadTask *unk_0C;
    MapObjectTextureManager *unk_10;
    struct MapObjectDrawManager_t *unk_14;
    SysTask *unk_18;
    SysTask *unk_1C;
    SysTask *unk_20;
    SysTask *unk_24;
} MapObjectDrawTaskManager;

#endif // POKEPLATINUM_STRUCT_MAP_OBJECT_DRAW_TASK_MANAGER_H
