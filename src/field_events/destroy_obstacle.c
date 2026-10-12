#include "field_events/destroy_obstacle.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/struct_fieldmap_021D1BEC_decl.h"
#include "field_events/hidden_effect.h"

#include "heap.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    UnkStruct_fieldmap_021D1BEC *unk_00;
    u16 *unk_04;
    u32 unk_08;
    u32 unk_0C;
} DestroyObstacleTask;

typedef UnkStruct_fieldmap_021D1BEC *(*DestroyObstacle_NewFunc)(FieldSystem *);
typedef void (*DestroyObstacle_FreeFunc)(UnkStruct_fieldmap_021D1BEC *);
typedef BOOL (*DestroyObstacle_FinishedFunc)(UnkStruct_fieldmap_021D1BEC *);

static const DestroyObstacle_NewFunc sDestroyObstacleNewFuncs[3] = {
    HiddenEffectSingle_New,
    HiddenEffectDouble_New,
    HiddenEffectDoubleAtMapObject_New
};

static const DestroyObstacle_FreeFunc sDestroyObstacleFreeFuncs[3] = {
    HiddenEffectSingle_Delete,
    HiddenEffectDouble_Delete,
    HiddenEffectDouble_Delete
};

static const DestroyObstacle_FinishedFunc sDestroyObstacleFinishedFuncs[3] = {
    HiddenEffectSingle_IsFinished,
    HiddenEffectDouble_IsFinished,
    HiddenEffectDouble_IsFinished
};

static void DestroyObstacle_Task(SysTask *param0, void *param1)
{
    DestroyObstacleTask *v0 = param1;

    switch (v0->unk_08) {
    case 0:
        if (sDestroyObstacleFinishedFuncs[v0->unk_0C](v0->unk_00) == 1) {
            v0->unk_08++;
        }
        break;
    case 1:
        sDestroyObstacleFreeFuncs[v0->unk_0C](v0->unk_00);
        *v0->unk_04 = 1;
        Heap_Free(v0);
        SysTask_Done(param0);
        break;
    }
}

void DestroyObstacle_Start(FieldSystem *fieldSystem, u16 *param1, u32 param2, enum HeapID heapID)
{
    DestroyObstacleTask *v0 = Heap_Alloc(heapID, sizeof(DestroyObstacleTask));

    memset(v0, 0, sizeof(DestroyObstacleTask));

    v0->unk_00 = sDestroyObstacleNewFuncs[param2](fieldSystem);
    v0->unk_04 = param1;
    v0->unk_0C = param2;

    *param1 = 0;
    SysTask_Start(DestroyObstacle_Task, v0, 0);
}
