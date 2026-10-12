#include "fieldmap/fieldmap_021D1A94.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/struct_field_effect_system_decl.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/struct_field_effect.h"

#include "field_system.h"
#include "heap.h"
#include "sys_task.h"
#include "sys_task_manager.h"

struct FieldEffectSystem_t {
    FieldSystem *fieldSystem;
    enum HeapID heapID;
    int unk_08;
    FieldEffect *unk_0C;
    SysTaskManager *sysTaskManager;
};

struct FieldEffect_t {
    FieldEffectSystem *unk_00;
    SysTask *sysTask1;
    SysTask *sysTask2;
    const FieldEffectTemplate *unk_0C;
    void *unk_10;
};

FieldEffectSystem *FieldMap_021D1A94(FieldSystem *fieldSystem, enum HeapID heapID, int param2)
{
    FieldEffectSystem *v0;
    u32 v1;

    v0 = Heap_Alloc(heapID, sizeof(FieldEffectSystem));

    v0->fieldSystem = fieldSystem;
    v0->heapID = heapID;
    v0->unk_08 = param2;
    v0->unk_0C = Heap_Alloc(heapID, sizeof(FieldEffect) * param2);

    MI_CpuClear32(v0->unk_0C, sizeof(FieldEffect) * param2);

    v1 = SysTaskManager_GetRequiredSize(param2);

    v0->sysTaskManager = Heap_Alloc(heapID, v1);
    v0->sysTaskManager = SysTaskManager_Init(param2, v0->sysTaskManager);

    return v0;
}

void FieldMap_021D1AE4(FieldEffectSystem *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_08; v0++) {
        FieldMap_021D1BEC(&param0->unk_0C[v0]);
    }

    Heap_Free(param0->unk_0C);
    Heap_Free(param0->sysTaskManager);
    Heap_Free(param0);
}

void FieldMap_021D1B18(FieldEffectSystem *param0)
{
    SysTaskManager_ExecuteTasks(param0->sysTaskManager);
}

static void FieldMap_021D1B24(SysTask *param0, void *param1)
{
    FieldEffect *v0 = param1;

    if (FieldSystem_IsRunningFieldMapInner(v0->unk_00->fieldSystem)) {
        if (v0->unk_0C->unk_10) {
            v0->unk_0C->unk_10(v0, v0->unk_00->fieldSystem, v0->unk_10);
        }
    }
}

static void FieldMap_021D1B48(SysTask *param0, void *param1)
{
    FieldEffect *v0 = param1;

    if (FieldSystem_IsRunningFieldMapInner(v0->unk_00->fieldSystem)) {
        if (v0->unk_0C->unk_14) {
            v0->unk_0C->unk_14(v0, v0->unk_00->fieldSystem, v0->unk_10);
        }
    }
}

FieldEffect *FieldMap_021D1B6C(FieldEffectSystem *param0, const FieldEffectTemplate *param1)
{
    int v0;
    FieldEffect *v1;

    for (v1 = param0->unk_0C, v0 = 0; v0 < param0->unk_08; v1++, v0++) {
        if (v1->sysTask1 == NULL) {
            v1->sysTask1 = SysTask_Start(FieldMap_021D1B24, v1, param1->unk_00);
            v1->sysTask2 = SysTaskManager_AddTask(param0->sysTaskManager, FieldMap_021D1B48, v1, param1->unk_00);
            v1->unk_00 = param0;
            v1->unk_0C = param1;

            GF_ASSERT(v1->sysTask1 != NULL);
            GF_ASSERT(v1->sysTask2 != NULL);

            if (param1->unk_04 != 0) {
                v1->unk_10 = Heap_Alloc(param0->heapID, param1->unk_04);
            }

            if (param1->unk_08) {
                param1->unk_08(v1, param0->fieldSystem, v1->unk_10);
            }

            return v1;
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

void FieldMap_021D1BEC(FieldEffect *param0)
{
    if (param0->sysTask1 == NULL) {
        return;
    }

    if (param0->unk_0C->unk_0C) {
        param0->unk_0C->unk_0C(param0, param0->unk_00->fieldSystem, param0->unk_10);
    }

    if (param0->unk_0C->unk_04 != 0) {
        Heap_Free(param0->unk_10);
    }

    SysTask_Done(param0->sysTask1);
    SysTask_Done(param0->sysTask2);

    MI_CpuClear32(param0, sizeof(FieldEffect));
}

void *FieldMap_021D1C2C(FieldEffect *param0)
{
    return param0->unk_10;
}
