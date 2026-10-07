#include "spear_pillar/spear_pillar_screen.h"

#include <nitro.h>
#include <string.h>

#include "overlay005/struct_ov5_021DDF24_sub1.h"
#include "spear_pillar/struct_spear_pillar_screen_scroll.h"
#include "spear_pillar/struct_spear_pillar_capture_config.h"
#include "overlay104/ov104_0223E894.h"

#include "bg_window.h"
#include "buffer_manager.h"
#include "heap.h"
#include "inlines.h"
#include "screen_scroll_manager.h"
#include "sys_task.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"

typedef void (*SpearPillarCaptureCallback)(void *);

typedef struct {
    SysTask *unk_00;
    SysTask *unk_04;
    BOOL unk_08;
    BOOL unk_0C;
    SpearPillarCaptureCallback unk_10;
    SpearPillarCaptureCallback unk_14;
    void *unk_18;
} SpearPillarCaptureBufferSub1;

typedef struct SpearPillarCaptureBuffer_t {
    SpearPillarCaptureBufferSub1 unk_00;
    BufferManager *bufferManager;
    u32 unk_20[192];
    u32 unk_320[192];
    u32 unk_620;
} SpearPillarCaptureBuffer;

typedef struct SpearPillarCapture_t {
    GXVRamLCDC unk_00;
    SpearPillarCaptureConfig unk_04;
    BOOL unk_30;
    SysTask *unk_34;
} SpearPillarCapture;

static SysTask *SpearPillarScreen_StartScrollTask(SpearPillarScreenScroll *param0);
static void SpearPillarScreen_ScrollTask(SysTask *param0, void *param1);
static void SpearPillarScreen_SetupCaptureTask(SysTask *param0, void *param1);
static void SpearPillarScreen_CaptureTask(SysTask *param0, void *param1);
static void SpearPillarScreen_InitCapture(SpearPillarCaptureConfig *param0);

static const u8 sSpearPillarCaptureOrder[][6] = {
    { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5 },
    { 0x5, 0x4, 0x3, 0x2, 0x1, 0x0 }
};

static SysTask *SpearPillarScreen_StartScrollTask(SpearPillarScreenScroll *param0)
{
    return SysTask_ExecuteOnVBlank(SpearPillarScreen_ScrollTask, param0, 1024);
}

static void SpearPillarScreen_ScrollTask(SysTask *param0, void *param1)
{
    SpearPillarScreenScroll *v0 = param1;

    if (v0->frameCounter >= 2) {
        ScreenScrollManager_SwapBuffers(v0->screenScrollMgr);
        v0->frameCounter = 0;
    }

    ScreenScrollManager_RestartDMA(v0->screenScrollMgr);
    v0->frameCounter++;
}

void SpearPillarScreen_InitScroll(SpearPillarScreenScroll *param0, u32 heapID)
{
    param0->screenScrollMgr = ScreenScrollManager_New(heapID);
    param0->frameCounter = 0;
    param0->task = SpearPillarScreen_StartScrollTask(param0);
}

void SpearPillarScreen_FreeScroll(SpearPillarScreenScroll *param0)
{
    SysTask_Done(param0->task);
    ScreenScrollManager_Stop(param0->screenScrollMgr);
    ScreenScrollManager_Delete(param0->screenScrollMgr);
}

void SpearPillarScreen_Scroll(SpearPillarScreenScroll *param0, u8 param1, u8 param2, u16 param3, fx32 param4, s16 param5, u32 param6, u32 param7, u32 param8, int param9)
{
    if (param9 == 0) {
        ScreenScrollManager_ScrollX(param0->screenScrollMgr, param1, param2, param3, param4, param5, param6, param7, param8);
    } else {
        ScreenScrollManager_ScrollY(param0->screenScrollMgr, param1, param2, param3, param4, param5, param6, param7, param8);
    }
}

SpearPillarCapture *SpearPillarScreen_StartCapture(SpearPillarCaptureConfig *param0)
{
    SysTask *v0 = SysTask_StartAndAllocateParam(SpearPillarScreen_CaptureTask, sizeof(SpearPillarCapture), 5, param0->unk_28);
    SpearPillarCapture *v1 = SysTask_GetParam(v0);

    v1->unk_04 = *param0;
    v1->unk_34 = v0;
    v1->unk_30 = 0;
    v1->unk_00 = GX_GetBankForLCDC();

    SpearPillarScreen_InitCapture(&v1->unk_04);
    SysTask_ExecuteAfterVBlank(SpearPillarScreen_SetupCaptureTask, v1, 0);

    return v1;
}

void SpearPillarScreen_StopCapture(SpearPillarCapture **param0, GXDispMode param1, GXBGMode param2, GXBG0As param3)
{
    GX_SetGraphicsMode(param1, param2, param3);
    GX_SetBankForLCDC((*param0)->unk_00);

    switch ((*param0)->unk_04.dispMode) {
    case GX_DISPMODE_VRAM_A:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_A, HW_VRAM_A_SIZE);
        break;
    case GX_DISPMODE_VRAM_B:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_B, HW_VRAM_B_SIZE);
        break;
    case GX_DISPMODE_VRAM_C:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE);
        break;
    case GX_DISPMODE_VRAM_D:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_D, HW_VRAM_D_SIZE);
        break;
    default:
        GX_SetBankForLCDC(GX_VRAM_LCDC_NONE);
        break;
    }

    SysTask_FinishAndFreeParam((*param0)->unk_34);
    *param0 = NULL;
}

static void SpearPillarScreen_CaptureTask(SysTask *param0, void *param1)
{
    SpearPillarCapture *v0 = param1;

    if (v0->unk_30) {
        GX_SetCapture(v0->unk_04.captureSize, v0->unk_04.captureMode, v0->unk_04.captureSrcA, v0->unk_04.captureSrcB, v0->unk_04.captureDest, v0->unk_04.unk_20, v0->unk_04.unk_24);
    }
}

static void SpearPillarScreen_SetupCaptureTask(SysTask *param0, void *param1)
{
    SpearPillarCapture *v0 = (SpearPillarCapture *)param1;

    switch (v0->unk_04.dispMode) {
    case GX_DISPMODE_VRAM_A:
        GX_SetBankForLCDC(GX_VRAM_LCDC_A);
        break;
    case GX_DISPMODE_VRAM_B:
        GX_SetBankForLCDC(GX_VRAM_LCDC_B);
        break;
    case GX_DISPMODE_VRAM_C:
        GX_SetBankForLCDC(GX_VRAM_LCDC_C);
        break;
    case GX_DISPMODE_VRAM_D:
        GX_SetBankForLCDC(GX_VRAM_LCDC_D);
        break;
    default:
        GX_SetBankForLCDC(GX_VRAM_LCDC_NONE);
        break;
    }

    GX_SetGraphicsMode(v0->unk_04.dispMode, v0->unk_04.bgMode, v0->unk_04.bg0As);

    v0->unk_30 = 1;
    SysTask_Done(param0);
}

static void SpearPillarScreen_InitCapture(SpearPillarCaptureConfig *param0)
{
    switch (param0->dispMode) {
    case GX_DISPMODE_VRAM_A:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_A, HW_VRAM_A_SIZE);
        break;
    case GX_DISPMODE_VRAM_B:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_B, HW_VRAM_B_SIZE);
        break;
    case GX_DISPMODE_VRAM_C:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE);
        break;
    case GX_DISPMODE_VRAM_D:
        MI_CpuClearFast((void *)HW_LCDC_VRAM_D, HW_VRAM_D_SIZE);
        break;
    default:
        break;
    }

    GX_SetCapture(param0->captureSize, param0->captureMode, param0->captureSrcA, param0->captureSrcB, param0->captureDest, 16, 0);
}
