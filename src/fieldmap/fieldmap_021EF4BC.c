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
    u32 unk_00;
    int unk_04;
    int unk_08;
    u16 unk_0C[192];
    u16 unk_18C[192];
    BufferManager *bufferManager;
    HBlankSystem *unk_310;
    HBlankTask *unk_314;
    BOOL unk_318;
    SysTask *unk_31C;
    SysTask *unk_320;
    SysTask *unk_324;
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

    v0->unk_00 = 0;
    v0->bufferManager = BufferManager_New(heapID, v0->unk_0C, v0->unk_18C);
    v0->unk_310 = param1;

    return v0;
}

void FieldMap_021EF4F8(PoisonEffect *param0)
{
    if (param0->unk_00 == 1) {
        FieldMap_021EF710(param0);
    }

    BufferManager_Delete(param0->bufferManager);
    Heap_Free(param0);
}

void Field_DoPoisonEffect(PoisonEffect *param0)
{
    GF_ASSERT(param0->unk_00 == 0);

    param0->unk_314 = HBlankSystem_StartTask(param0->unk_310, FieldMap_021EF6C0, param0);
    param0->unk_31C = SysTask_Start(FieldMap_021EF5A8, param0, 1024);
    param0->unk_320 = SysTask_ExecuteOnVBlank(FieldMap_021EF6B0, param0, 1024);
    param0->unk_324 = SysTask_ExecuteOnVBlank(FieldMap_021EF6E4, param0, 1024);

    memset(param0->unk_0C, 0, sizeof(u16) * 192);
    memset(param0->unk_18C, 0, sizeof(u16) * 192);

    param0->unk_00 = 1;
    param0->unk_08 = 0;

    Sound_PlayEffect(SEQ_SE_DP_DOKU2_sseq);
}

static void FieldMap_021EF5A8(SysTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;
    u16 *v1;

    switch (v0->unk_08) {
    case 0:
        v0->unk_04 = 3;
        v0->unk_08++;
        break;
    case 1:
        v0->unk_04--;
        v1 = BufferManager_GetWriteBuffer(v0->bufferManager);

        FieldMap_021EF66C(v1, 3 - v0->unk_04, 3);

        if (v0->unk_04 <= 0) {
            v0->unk_04 = 3;
            v0->unk_08++;
        }
        break;
    case 2:
        v0->unk_04--;
        v1 = BufferManager_GetWriteBuffer(v0->bufferManager);

        FieldMap_021EF66C(v1, v0->unk_04, 3);

        if (v0->unk_04 <= 0) {
            v0->unk_08++;
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

    v0->unk_318 = 0;
    G3X_SetHOffset(0);
}

static void FieldMap_021EF6C0(HBlankTask *param0, void *param1)
{
    PoisonEffect *v0 = param1;
    FieldMap_021EF6CC(v0);
}

static void FieldMap_021EF6CC(PoisonEffect *param0)
{
    if (param0->unk_00 == 1) {
        if (param0->unk_318 == 1) {
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
    if (param0->unk_00 == 1) {
        BufferManager_SwapBuffers(param0->bufferManager);
        param0->unk_318 = 1;
    }
}

static void FieldMap_021EF710(PoisonEffect *param0)
{
    HBlankTask_Delete(param0->unk_314);
    param0->unk_314 = NULL;

    SysTask_Done(param0->unk_31C);
    param0->unk_31C = NULL;

    SysTask_Done(param0->unk_320);
    param0->unk_320 = NULL;

    SysTask_Done(param0->unk_324);
    param0->unk_324 = NULL;
    param0->unk_00 = 0;
}
