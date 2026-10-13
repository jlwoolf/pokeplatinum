#include "frontier_facilities/frontier_facilities_0223E894.h"

#include <nitro.h>
#include <string.h>

#include "frontier_facilities/struct_frontier_facilities_0223E9EC.h"
#include "frontier_facilities/struct_frontier_facilities_0223EA38.h"
#include "frontier_facilities/struct_frontier_facilities_0223F094.h"
#include "frontier_facilities/struct_frontier_facilities_0223F1B4.h"

#include "bg_window.h"
#include "buffer_manager.h"
#include "heap.h"
#include "screen_scroll_manager.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    int state;
    u32 repeatCount;
    int repeatIndex;
    int screen;
    u32 flashBrightness;
    u32 baseBrightness;
    FrontierFacilitiesAnimation flashAnimation;
    FrontierFacilitiesAnimation baseAnimation;
    BOOL *doneFlag;
} FrontierFacilitiesScreenFlash;

typedef struct FrontierFacilitiesWipeRect_t {
    FrontierFacilitiesLinearAnimation xAnimation;
    FrontierFacilitiesLinearAnimation yAnimation;
    Window *window;
    u8 width;
    u8 height;
    u8 active;
    u8 color;
} FrontierFacilitiesWipeRect;

typedef struct FrontierFacilitiesWipeManager_t {
    Window *window;
    FrontierFacilitiesWipeRect *rects[96];
    u8 rectCount;
    u8 waveIndex;
    u8 row;
    u8 direction;
    u8 completedCount;
    u8 rectSteps;
    u8 stepDelay;
    s8 delayCounter;
    u8 rectColor;
    u8 active;
    u8 unk_18E[1];
} FrontierFacilitiesWipeManager;

typedef void (*FrontierFacilitiesCallback)(void *);

typedef struct {
    SysTask *onVBlankTask;
    SysTask *afterVBlankTask;
    BOOL enabled;
    BOOL afterVBlankPending;
    FrontierFacilitiesCallback afterVBlankCallback;
    FrontierFacilitiesCallback onVBlankCallback;
    void *data;
} FrontierFacilitiesVBlankCallbacks;

typedef struct FrontierFacilitiesAffineBuffer_t {
    FrontierFacilitiesVBlankCallbacks vBlankCallbacks;
    BufferManager *bufferManager;
    FrontierFacilitiesAffineEntry bufferA[192];
    FrontierFacilitiesAffineEntry bufferB[192];
    u32 destAddress;
} FrontierFacilitiesAffineBuffer;

static void FrontierFacilities_ApplyBrightnessFade(SysTask *param0, void *param1);
static void FrontierFacilities_UpdateScreenFlash(SysTask *param0, void *param1);
static void FrontierFacilities_FillWindowRect(Window *param0, s32 param1, s32 param2, s32 param3, s32 param4, u8 param5);
static SysTask *FrontierFacilities_CreateScreenScrollTask(FrontierFacilitiesScreenScroll *param0);
static void FrontierFacilities_UpdateScreenScroll(SysTask *param0, void *param1);

void FrontierFacilities_StartScreenFlash(int param0, u32 param1, u32 param2, BOOL *param3, u32 param4)
{
    SysTask *v0;
    FrontierFacilitiesScreenFlash *v1 = Heap_Alloc(HEAP_ID_FIELD2, sizeof(FrontierFacilitiesScreenFlash));
    memset(v1, 0, sizeof(FrontierFacilitiesScreenFlash));

    SysTask_Start(FrontierFacilities_UpdateScreenFlash, v1, 5);

    v1->doneFlag = param3;

    if (v1->doneFlag != NULL) {
        *(v1->doneFlag) = 0;
    }

    v1->screen = param0;
    v1->flashBrightness = param1;
    v1->baseBrightness = param2;
    v1->repeatCount = param4;
}

static void FrontierFacilities_UpdateScreenFlash(SysTask *param0, void *param1)
{
    FrontierFacilitiesScreenFlash *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->screen == 1) {
            FrontierFacilities_StartBrightnessFade(&v0->baseAnimation, 0, v0->baseBrightness, 2, 8);
        } else {
            if (v0->screen == 2) {
                FrontierFacilities_StartBrightnessFade(&v0->baseAnimation, 0, v0->baseBrightness, 1, 8);
            }
        }

        v0->state++;
        break;
    case 1:
        FrontierFacilities_StartBrightnessFade(&v0->flashAnimation, 0, v0->flashBrightness, v0->screen, 3);
        v0->state++;
        break;
    case 2:
        if (FrontierFacilities_UpdateBrightnessFade(&v0->flashAnimation)) {
            v0->state++;
        }
        break;
    case 3:
        FrontierFacilities_StartBrightnessFade(&v0->flashAnimation, v0->flashBrightness, 0, v0->screen, 3);
        v0->state++;
        break;
    case 4:
        if (FrontierFacilities_UpdateBrightnessFade(&v0->flashAnimation)) {
            v0->repeatIndex++;

            if (v0->repeatIndex == v0->repeatCount) {
                v0->state = 5;
            } else {
                v0->state = 1;
            }
        }
        break;
    case 5:
        v0->state = 0;
        v0->repeatIndex = 0;

        if (v0->doneFlag != NULL) {
            *(v0->doneFlag) = 1;
        }

        SysTask_Done(param0);
        Heap_Free(v0);

        return;
    }

    FrontierFacilities_UpdateBrightnessFade(&v0->baseAnimation);
}

void FrontierFacilities_SetMasterBrightness(int param0, int param1)
{
    if (param0 == 1) {
        GX_SetMasterBrightness(param1);
    } else {
        GXS_SetMasterBrightness(param1);
    }
}

void FrontierFacilities_StartBrightnessFade(FrontierFacilitiesAnimation *param0, int param1, int param2, int param3, int param4)
{
    param0->screen = param3;
    FrontierFacilities_InitAnimation(&param0->animation, param1, param2, param4);
}

BOOL FrontierFacilities_UpdateBrightnessFade(FrontierFacilitiesAnimation *param0)
{
    BOOL v0 = FrontierFacilities_StepAnimation(&param0->animation);
    SysTask_ExecuteAfterVBlank(FrontierFacilities_ApplyBrightnessFade, param0, 10);

    return v0;
}

static void FrontierFacilities_ApplyBrightnessFade(SysTask *param0, void *param1)
{
    FrontierFacilitiesAnimation *v0 = param1;

    FrontierFacilities_SetMasterBrightness(v0->screen, v0->animation.current);
    SysTask_Done(param0);
}

void FrontierFacilities_InitAnimation(FrontierFacilitiesLinearAnimation *param0, int param1, int param2, int param3)
{
    param0->current = param1;
    param0->start = param1;
    param0->range = param2 - param1;
    param0->stepCount = param3;
    param0->elapsedSteps = 0;
}

BOOL FrontierFacilities_StepAnimation(FrontierFacilitiesLinearAnimation *param0)
{
    int v0 = param0->range * param0->elapsedSteps;
    v0 = v0 / param0->stepCount;

    param0->current = v0 + param0->start;

    if ((param0->elapsedSteps + 1) <= param0->stepCount) {
        param0->elapsedSteps++;
        return 0;
    }

    param0->elapsedSteps = param0->stepCount;
    return 1;
}

FrontierFacilitiesWipeRect *FrontierFacilities_NewWipeRect(enum HeapID heapID)
{
    FrontierFacilitiesWipeRect *v0 = Heap_Alloc(heapID, sizeof(FrontierFacilitiesWipeRect));
    memset(v0, 0, sizeof(FrontierFacilitiesWipeRect));

    return v0;
}

void FrontierFacilities_FreeWipeRect(FrontierFacilitiesWipeRect *param0)
{
    Heap_Free(param0);
}

void FrontierFacilities_StartWipeRect(FrontierFacilitiesWipeRect *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9)
{
    GF_ASSERT(param0->active == 0);

    FrontierFacilities_InitAnimation(&param0->xAnimation, param1, param2, param5);
    FrontierFacilities_InitAnimation(&param0->yAnimation, param3, param4, param5);

    param0->window = param6;
    param0->width = param7;
    param0->height = param8;
    param0->color = param9;
    param0->active = 1;
}

BOOL FrontierFacilities_UpdateWipeRect(FrontierFacilitiesWipeRect *param0)
{
    BOOL v0;
    s16 v1, v2, v3, v4;

    if (param0->active == 0) {
        return 1;
    }

    v3 = param0->xAnimation.current - (param0->width / 2);
    v1 = param0->yAnimation.current - (param0->height / 2);
    v4 = v3 + param0->width;
    v2 = v1 + param0->height;

    v0 = FrontierFacilities_StepAnimation(&param0->xAnimation);
    FrontierFacilities_StepAnimation(&param0->yAnimation);

    v3 = param0->xAnimation.current - (param0->width / 2);
    v1 = param0->yAnimation.current - (param0->height / 2);
    v4 = v3 + param0->width;
    v2 = v1 + param0->height;

    FrontierFacilities_FillWindowRect(param0->window, v1, v2, v3, v4, param0->color);

    return v0;
}

static void FrontierFacilities_FillWindowRect(Window *param0, s32 param1, s32 param2, s32 param3, s32 param4, u8 param5)
{
    if ((param4 <= 0) || (param2 <= 0)) {
        return;
    }

    if ((param3 == param4) || (param1 == param2)) {
        return;
    }

    if (param3 < 0) {
        param3 = 0;
    }

    if (param4 > 256) {
        param4 = 256;
    }

    if (param1 < 0) {
        param1 = 0;
    }

    if (param2 > 256) {
        param2 = 256;
    }

    Window_FillRectWithColor(param0, param5, param3, param1, param4 - param3, param2 - param1);
}

FrontierFacilitiesWipeManager *FrontierFacilities_NewWipeManager(enum HeapID heapID)
{
    FrontierFacilitiesWipeManager *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(FrontierFacilitiesWipeManager));
    memset(v0, 0, sizeof(FrontierFacilitiesWipeManager));

    for (v1 = 0; v1 < ((256 / 16) * (192 / 32)); v1++) {
        v0->rects[v1] = FrontierFacilities_NewWipeRect(heapID);
    }

    return v0;
}

void FrontierFacilities_FreeWipeManager(FrontierFacilitiesWipeManager *param0)
{
    int v0;

    for (v0 = 0; v0 < ((256 / 16) * (192 / 32)); v0++) {
        FrontierFacilities_FreeWipeRect(param0->rects[v0]);
    }

    Heap_Free(param0);
}

void FrontierFacilities_StartWipe(FrontierFacilitiesWipeManager *param0, u8 param1, u8 param2, Window *param3, u8 param4)
{
    param0->window = param3;
    param0->rectColor = param4;
    param0->rectSteps = param1;
    param0->stepDelay = param2;
    param0->rectCount = 0;
    param0->waveIndex = 0;
    param0->row = 0;
    param0->direction = 0;
    param0->completedCount = 0;
    param0->delayCounter = 0;
    param0->active = 1;
}

static const u8 sHorizontalWipeOrder[][(256 / 16)] = {
    { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7 },
    { 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0 }
};

BOOL FrontierFacilities_UpdateHorizontalWipe(FrontierFacilitiesWipeManager *param0)
{
    int v0, v1, v2, v3;
    int v4;
    BOOL v5;

    if (param0->active == 0) {
        return 1;
    }

    if (param0->rectCount < ((256 / 16) * (192 / 32))) {
        param0->delayCounter--;

        if (param0->delayCounter <= 0) {
            param0->delayCounter = param0->stepDelay;

            v0 = 32 * (sHorizontalWipeOrder[param0->direction][param0->waveIndex] * 1);
            v1 = v0 + 32;
            v2 = param0->row;
            v3 = (16 / 2) + (v2 * 16);

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount], v0, v1, v3, v3, param0->rectSteps, param0->window, 32, 16, param0->rectColor);

            v0 = 32 * (sHorizontalWipeOrder[param0->direction ^ 1][param0->waveIndex] * 1);
            v1 = v0 + 32;
            v2 = ((192 / 16) / 2) - param0->row - 1;
            v3 = (16 / 2) + (v2 * 16);

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 1], v0, v1, v3, v3, param0->rectSteps, param0->window, 32, 16, param0->rectColor);

            v0 = 32 * (sHorizontalWipeOrder[param0->direction][param0->waveIndex] * 1);
            v1 = v0 + 32;
            v2 = ((192 / 16) / 2) + param0->row;
            v3 = (16 / 2) + (v2 * 16);

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 2], v0, v1, v3, v3, param0->rectSteps, param0->window, 32, 16, param0->rectColor);

            v0 = 32 * (sHorizontalWipeOrder[param0->direction ^ 1][param0->waveIndex] * 1);
            v1 = v0 + 32;
            v2 = (192 / 16) - param0->row - 1;
            v3 = (16 / 2) + (v2 * 16);

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 3], v0, v1, v3, v3, param0->rectSteps, param0->window, 32, 16, param0->rectColor);

            param0->rectCount += 4;
            param0->waveIndex++;

            if ((param0->waveIndex % (256 / 32)) == 0) {
                param0->direction ^= 1;
                param0->row++;
                param0->waveIndex = 0;
            }
        }
    }

    for (v4 = param0->completedCount; v4 < param0->rectCount; v4++) {
        v5 = FrontierFacilities_UpdateWipeRect(param0->rects[v4]);

        if (v5 == 1) {
            param0->completedCount++;
        }
    }

    if ((param0->completedCount >= ((256 / 16) * (192 / 32))) && (v5 == 1)) {
        param0->active = 0;
        return 1;
    }

    return 0;
}

static const u8 sVerticalWipeOrder[][(192 / 32)] = {
    { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5 },
    { 0x5, 0x4, 0x3, 0x2, 0x1, 0x0 }
};

BOOL FrontierFacilities_UpdateVerticalWipe(FrontierFacilitiesWipeManager *param0)
{
    int v0, v1, v2;
    int v3;
    BOOL v4;

    if (param0->active == 0) {
        return 1;
    }

    if (param0->rectCount < ((256 / 16) * (192 / 32))) {
        param0->delayCounter--;

        if (param0->delayCounter <= 0) {
            param0->delayCounter = param0->stepDelay;

            v0 = param0->waveIndex;
            v0 = (16 / 2) + (v0 * 16);
            v1 = 32 * (sVerticalWipeOrder[param0->direction][param0->row] * 1);
            v2 = v1 + 32;

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount], v0, v0, v1, v2, param0->rectSteps, param0->window, 16, 32, param0->rectColor);

            v0 = ((256 / 16) / 2) - param0->waveIndex - 1;
            v0 = (16 / 2) + (v0 * 16);
            v1 = 32 * (sVerticalWipeOrder[param0->direction ^ 1][param0->row] * 1);
            v2 = v1 + 32;

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 1], v0, v0, v1, v2, param0->rectSteps, param0->window, 16, 32, param0->rectColor);

            v0 = ((256 / 16) / 2) + param0->waveIndex;
            v0 = (16 / 2) + (v0 * 16);
            v1 = 32 * (sVerticalWipeOrder[param0->direction][param0->row] * 1);
            v2 = v1 + 32;

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 2], v0, v0, v1, v2, param0->rectSteps, param0->window, 16, 32, param0->rectColor);

            v0 = (256 / 16) - param0->waveIndex - 1;
            v0 = (16 / 2) + (v0 * 16);
            v1 = 32 * (sVerticalWipeOrder[param0->direction ^ 1][param0->row] * 1);
            v2 = v1 + 32;

            FrontierFacilities_StartWipeRect(param0->rects[param0->rectCount + 3], v0, v0, v1, v2, param0->rectSteps, param0->window, 16, 32, param0->rectColor);

            param0->rectCount += 4;
            param0->row++;

            if ((param0->row % (192 / 32)) == 0) {
                param0->direction ^= 1;
                param0->waveIndex++;
                param0->row = 0;
            }
        }
    }

    for (v3 = param0->completedCount; v3 < param0->rectCount; v3++) {
        v4 = FrontierFacilities_UpdateWipeRect(param0->rects[v3]);

        if (v4 == 1) {
            param0->completedCount++;
        }
    }

    if ((param0->completedCount >= ((256 / 16) * (192 / 32))) && (v4 == 1)) {
        param0->active = 0;
        return 1;
    }

    return 0;
}

static SysTask *FrontierFacilities_CreateScreenScrollTask(FrontierFacilitiesScreenScroll *param0)
{
    return SysTask_ExecuteOnVBlank(FrontierFacilities_UpdateScreenScroll, param0, 1024);
}

static void FrontierFacilities_UpdateScreenScroll(SysTask *param0, void *param1)
{
    FrontierFacilitiesScreenScroll *v0 = param1;

    if (v0->vBlankCounter >= 2) {
        ScreenScrollManager_SwapBuffers(v0->screenScrollMgr);
        v0->vBlankCounter = 0;
    }

    ScreenScrollManager_RestartDMA(v0->screenScrollMgr);
    v0->vBlankCounter++;
}

void FrontierFacilities_InitScreenScroll(FrontierFacilitiesScreenScroll *param0, enum HeapID heapID)
{
    param0->screenScrollMgr = ScreenScrollManager_New(heapID);
    param0->vBlankCounter = 0;
    param0->task = FrontierFacilities_CreateScreenScrollTask(param0);
}

void FrontierFacilities_BeginScreenScroll(FrontierFacilitiesScreenScroll *param0, u8 param1, u8 param2, u16 param3, fx32 param4, s16 param5, u32 param6, u32 param7, u32 param8)
{
    ScreenScrollManager_ScrollX(param0->screenScrollMgr, param1, param2, param3, param4, param5, param6, param7, param8);
}

static void FrontierFacilities_AfterVBlankCallback(SysTask *param0, void *param1)
{
    FrontierFacilitiesVBlankCallbacks *v0 = param1;

    if (v0->enabled) {
        v0->afterVBlankPending = 1;

        v0->afterVBlankCallback(v0->data);
    } else {
        BufferManager_StopDMA();
    }
}

static void FrontierFacilities_OnVBlankCallback(SysTask *param0, void *param1)
{
    FrontierFacilitiesVBlankCallbacks *v0 = param1;

    if (v0->enabled && v0->afterVBlankPending) {
        v0->onVBlankCallback(v0->data);

        v0->afterVBlankPending = 0;
    }
}

static void FrontierFacilities_InitVBlankCallbacks(FrontierFacilitiesVBlankCallbacks *param0, void *param1, FrontierFacilitiesCallback param2, FrontierFacilitiesCallback param3)
{
    GF_ASSERT(param0);

    param0->enabled = 1;
    param0->afterVBlankPending = 0;
    param0->data = param1;
    param0->afterVBlankCallback = param2;
    param0->onVBlankCallback = param3;
    param0->afterVBlankTask = SysTask_ExecuteAfterVBlank(FrontierFacilities_AfterVBlankCallback, param0, 0);
    param0->onVBlankTask = SysTask_ExecuteOnVBlank(FrontierFacilities_OnVBlankCallback, param0, 0);
}

static void FrontierFacilities_FreeVBlankCallbacks(FrontierFacilitiesVBlankCallbacks *param0)
{
    GF_ASSERT(param0);

    if (param0->afterVBlankTask != NULL) {
        SysTask_Done(param0->afterVBlankTask);
    }

    if (param0->onVBlankTask != NULL) {
        SysTask_Done(param0->onVBlankTask);
    }

    BufferManager_StopDMA();
}

static void FrontierFacilities_TransferAffineData(FrontierFacilitiesAffineBuffer *param0)
{
    const void *v0 = BufferManager_GetReadBuffer(param0->bufferManager);

    BufferManager_StopDMA();
    BufferManager_StartDMA(v0, (void *)param0->destAddress, (sizeof(FrontierFacilitiesAffineEntry)), 1);
}

static void FrontierFacilities_SwapAffineBuffers(void *param0)
{
    FrontierFacilitiesAffineBuffer *v0 = param0;

    BufferManager_SwapBuffers(v0->bufferManager);
    FrontierFacilities_TransferAffineData(v0);
}

static void FrontierFacilities_TransferAffineDataCallback(void *param0)
{
    FrontierFacilitiesAffineBuffer *v0 = param0;
    FrontierFacilities_TransferAffineData(v0);
}

FrontierFacilitiesAffineBuffer *FrontierFacilities_NewAffineBuffer(u32 param0, FrontierFacilitiesAffineEntry *param1, enum HeapID heapID)
{
    FrontierFacilitiesAffineBuffer *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(FrontierFacilitiesAffineBuffer));
    memset(v0, 0, sizeof(FrontierFacilitiesAffineBuffer));

    GF_ASSERT(v0);
    v0->bufferManager = BufferManager_New(heapID, v0->bufferA, v0->bufferB);

    GF_ASSERT(v0->bufferManager);
    v0->destAddress = param0;

    for (v1 = 0; v1 < 192; v1++) {
        v0->bufferA[v1] = *param1;
        v0->bufferB[v1] = *param1;
    }

    FrontierFacilities_InitVBlankCallbacks(&v0->vBlankCallbacks, v0, FrontierFacilities_SwapAffineBuffers, FrontierFacilities_TransferAffineDataCallback);
    return v0;
}

void FrontierFacilities_FreeAffineBuffer(FrontierFacilitiesAffineBuffer *param0)
{
    GF_ASSERT(param0);

    FrontierFacilities_FreeVBlankCallbacks(&param0->vBlankCallbacks);

    if (param0->bufferManager != NULL) {
        BufferManager_Delete(param0->bufferManager);
    }

    Heap_Free(param0);
}

void *FrontierFacilities_GetAffineWriteBuffer(const FrontierFacilitiesAffineBuffer *param0)
{
    GF_ASSERT(param0);

    return BufferManager_GetWriteBuffer(param0->bufferManager);
}
