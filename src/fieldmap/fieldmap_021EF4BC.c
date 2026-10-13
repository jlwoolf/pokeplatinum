#include "fieldmap/fieldmap_021EF4BC.h"

#include <nitro.h>
#include <string.h>

#include "fieldmap/hblank_system.h"

#include "buffer_manager.h"
#include "heap.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct PoisonEffect_t {
    u32 active;
    int counter;
    int state;
    u16 bufferA[192];
    u16 bufferB[192];
    BufferManager *bufferManager;
    HBlankSystem *hBlankSystem;
    HBlankTask *hBlankTask;
    BOOL swapReady;
    SysTask *mainTask;
    SysTask *vBlankTask;
    SysTask *vBlankSwapTask;
} PoisonEffect;

static void FieldMap_021EF5A8(SysTask *param0, void *param1);
static void FieldMap_021EF6B0(SysTask *param0, void *param1);
static void FieldMap_021EF6E4(SysTask *param0, void *param1);
static void FieldMap_021EF634(PoisonEffect *param0);
static void FieldMap_021EF66C(u16 *param0, int param1, int param2);
static void FieldMap_021EF6C0(HBlankTask *param0, void *param1);
static void FieldMap_021EF6CC(PoisonEffect *param0);
static void FieldMap_021EF6F0(PoisonEffect *param0);
static void FieldMap_021EF710(PoisonEffect *param0);

PoisonEffect *FieldMap_021EF4BC(enum HeapID heapID, HBlankSystem *param1)
{
    PoisonEffect *v0 = Heap_Alloc(heapID, sizeof(PoisonEffect));
    memset(v0, 0, sizeof(PoisonEffect));

    v0->active = 0;
    v0->bufferManager = BufferManager_New(heapID, v0->bufferA, v0->bufferB);
    v0->hBlankSystem = param1;

    return v0;
}

void FieldMap_021EF4F8(PoisonEffect *param0)
{
    if (param0->active == 1) {
        FieldMap_021EF710(param0);
    }

    BufferManager_Delete(param0->bufferManager);
    Heap_Free(param0);
}

void Field_DoPoisonEffect(PoisonEffect *param0)
{
    GF_ASSERT(param0->active == 0);

    param0->hBlankTask = HBlankSystem_StartTask(param0->hBlankSystem, FieldMap_021EF6C0, param0);
    param0->mainTask = SysTask_Start(FieldMap_021EF5A8, param0, 1024);
    param0->vBlankTask = SysTask_ExecuteOnVBlank(FieldMap_021EF6B0, param0, 1024);
    param0->vBlankSwapTask = SysTask_ExecuteOnVBlank(FieldMap_021EF6E4, param0, 1024);

    memset(param0->bufferA, 0, sizeof(u16) * 192);
    memset(param0->bufferB, 0, sizeof(u16) * 192);

    param0->active = 1;
    param0->state = 0;

    Sound_PlayEffect(SEQ_SE_DP_DOKU2_sseq);
}

static void FieldMap_021EF5A8(SysTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;
    u16 *v1;

    switch (v0->state) {
    case 0:
        v0->counter = 3;
        v0->state++;
        break;
    case 1:
        v0->counter--;
        v1 = BufferManager_GetWriteBuffer(v0->bufferManager);

        FieldMap_021EF66C(v1, 3 - v0->counter, 3);

        if (v0->counter <= 0) {
            v0->counter = 3;
            v0->state++;
        }
        break;
    case 2:
        v0->counter--;
        v1 = BufferManager_GetWriteBuffer(v0->bufferManager);

        FieldMap_021EF66C(v1, v0->counter, 3);

        if (v0->counter <= 0) {
            v0->state++;
        }
        break;
    case 3:
        FieldMap_021EF710(v0);
        G3X_SetHOffset(0);
        break;
    }
}

static void FieldMap_021EF634(PoisonEffect *param0)
{
    const u16 *v0;
    int v1 = GX_GetVCount();
    v0 = BufferManager_GetReadBuffer(param0->bufferManager);

    if (v1 < 192) {
        v1++;

        if (v1 >= 192) {
            v1 -= 192;
        }

        if (GX_IsHBlank()) {
            G3X_SetHOffset(v0[v1]);
        }
    }
}

static void FieldMap_021EF66C(u16 *param0, int param1, int param2)
{
    int v0;
    int v1;
    BOOL v2 = 1;

    v1 = 3 * param1;
    v1 = v1 / param2;

    for (v0 = 0; v0 < 192; v0++) {
        if ((v0 % 10) == 0) {
            v2 ^= 1;
        }

        if (v2) {
            param0[v0] = v1;
        } else {
            param0[v0] = -v1;
        }
    }
}

static void FieldMap_021EF6B0(SysTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;

    v0->swapReady = 0;
    G3X_SetHOffset(0);
}

static void FieldMap_021EF6C0(HBlankTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;
    FieldMap_021EF6CC(v0);
}

static void FieldMap_021EF6CC(PoisonEffect *param0)
{
    if (param0->active == 1) {
        if (param0->swapReady == 1) {
            FieldMap_021EF634(param0);
        }
    }
}

static void FieldMap_021EF6E4(SysTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;
    FieldMap_021EF6F0(v0);
}

static void FieldMap_021EF6F0(PoisonEffect *param0)
{
    if (param0->active == 1) {
        BufferManager_SwapBuffers(param0->bufferManager);
        param0->swapReady = 1;
    }
}

static void FieldMap_021EF710(PoisonEffect *param0)
{
    HBlankTask_Delete(param0->hBlankTask);
    param0->hBlankTask = NULL;

    SysTask_Done(param0->mainTask);
    param0->mainTask = NULL;

    SysTask_Done(param0->vBlankTask);
    param0->vBlankTask = NULL;

    SysTask_Done(param0->vBlankSwapTask);
    param0->vBlankSwapTask = NULL;
    param0->active = 0;
}
