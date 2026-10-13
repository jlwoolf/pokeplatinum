#include "fieldmap/fieldmap_021F0EB0.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"

#include "camera.h"
#include "heap.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    enum HeapID heapID;
    int state;
    int finished;
    int mode;
    fx32 targetDistance;
    fx32 delta;
    fx32 endDistance;
    u32 numSteps;
    fx32 currentDistance;
    u32 currentStep;
    fx32 stepIncrement;
    FieldSystem *fieldSystem;
    Camera *camera;
} CameraDistanceTask;

static void FieldMap_021F0F2C(SysTask *param0, void *param1);
static void FieldMap_021F0FB8(CameraDistanceTask *param0);
static void FieldMap_021F0FC8(CameraDistanceTask *param0);
static void FieldMap_021F0FE0(CameraDistanceTask *param0);
static int FieldMap_021F0FF8(CameraDistanceTask *param0);

static void (*const Unk_FieldMap_0220020C[4])(CameraDistanceTask *);

SysTask *FieldMap_021F0EB0(FieldSystem *fieldSystem, enum HeapID heapID)
{
    SysTask *task;
    CameraDistanceTask *v1 = Heap_AllocAtEnd(heapID, (sizeof(CameraDistanceTask)));

    memset(v1, 0, (sizeof(CameraDistanceTask)));

    v1->heapID = heapID;
    v1->mode = 0;
    v1->fieldSystem = fieldSystem;
    v1->camera = fieldSystem->camera;
    v1->targetDistance = Camera_GetDistance(v1->camera);
    v1->currentDistance = v1->targetDistance;

    task = SysTask_Start(FieldMap_021F0F2C, v1, 0xffff);
    return task;
}

BOOL FieldMap_021F0EF0(SysTask *param0)
{
    CameraDistanceTask *v0 = SysTask_GetParam(param0);
    return v0->finished;
}

void FieldMap_021F0EFC(SysTask *param0)
{
    CameraDistanceTask *v0 = SysTask_GetParam(param0);

    Heap_Free(v0);
    SysTask_Done(param0);
}

void FieldMap_021F0F10(SysTask *param0, int param1, fx32 param2, u32 param3)
{
    CameraDistanceTask *v0 = SysTask_GetParam(param0);

    v0->state = 0;
    v0->finished = 0;
    v0->mode = param1;
    v0->delta = param2;
    v0->numSteps = param3;
    v0->currentStep = 0;
}

static void FieldMap_021F0F2C(SysTask *param0, void *param1)
{
    CameraDistanceTask *v0 = param1;
    Unk_FieldMap_0220020C[v0->mode](v0);
}

static void FieldMap_021F0F40(CameraDistanceTask *param0)
{
    param0->finished = 1;
}

static void FieldMap_021F0F48(CameraDistanceTask *param0)
{
    switch (param0->state) {
    case 0:
        FieldMap_021F0FC8(param0);
        param0->state++;
    case 1:
        if (FieldMap_021F0FF8(param0) == 1) {
            param0->state++;
            param0->finished = 1;
        }

        FieldMap_021F0FB8(param0);
    }
}

static void FieldMap_021F0F80(CameraDistanceTask *param0)
{
    switch (param0->state) {
    case 0:
        FieldMap_021F0FE0(param0);
        param0->state++;
    case 1:
        if (FieldMap_021F0FF8(param0) == 1) {
            param0->state++;
            param0->finished = 1;
        }

        FieldMap_021F0FB8(param0);
    }
}

static void FieldMap_021F0FB8(CameraDistanceTask *param0)
{
    Camera_SetDistance(param0->currentDistance, param0->camera);
}

static void FieldMap_021F0FC8(CameraDistanceTask *param0)
{
    fx32 v0 = param0->numSteps;

    param0->stepIncrement = param0->delta / v0;
    param0->endDistance = param0->currentDistance + param0->delta;
}

static void FieldMap_021F0FE0(CameraDistanceTask *param0)
{
    fx32 v0 = param0->numSteps;
    fx32 v1 = param0->targetDistance - param0->currentDistance;

    param0->stepIncrement = v1 / v0;
    param0->endDistance = param0->targetDistance;
}

static int FieldMap_021F0FF8(CameraDistanceTask *param0)
{
    param0->currentDistance += param0->stepIncrement;
    param0->currentStep++;

    if (param0->currentStep >= param0->numSteps) {
        param0->currentStep = param0->numSteps;
        param0->currentDistance = param0->endDistance;
        return 1;
    }

    return 0;
}

static void (*const Unk_FieldMap_0220020C[4])(CameraDistanceTask *) = {
    FieldMap_021F0F40,
    FieldMap_021F0F48,
    FieldMap_021F0F80,
};
