#include "field_events/destroy_obstacle.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/hidden_effect.h"

#include "heap.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    FieldEffect *effect;
    u16 *finishedFlag;
    u32 state;
    u32 variant;
} DestroyObstacleTask;

typedef FieldEffect *(*DestroyObstacle_NewFunc)(FieldSystem *);
typedef void (*DestroyObstacle_FreeFunc)(FieldEffect *);
typedef BOOL (*DestroyObstacle_FinishedFunc)(FieldEffect *);

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

    switch (v0->state) {
    case 0:
        if (sDestroyObstacleFinishedFuncs[v0->variant](v0->effect) == 1) {
            v0->state++;
        }
        break;
    case 1:
        sDestroyObstacleFreeFuncs[v0->variant](v0->effect);
        *v0->finishedFlag = 1;
        Heap_Free(v0);
        SysTask_Done(param0);
        break;
    }
}

void DestroyObstacle_Start(FieldSystem *fieldSystem, u16 *param1, u32 param2, enum HeapID heapID)
{
    DestroyObstacleTask *v0 = Heap_Alloc(heapID, sizeof(DestroyObstacleTask));

    memset(v0, 0, sizeof(DestroyObstacleTask));

    v0->effect = sDestroyObstacleNewFuncs[param2](fieldSystem);
    v0->finishedFlag = param1;
    v0->variant = param2;

    *param1 = 0;
    SysTask_Start(DestroyObstacle_Task, v0, 0);
}
