#include "fieldmap/encounter_effect.h"

#include "nitro/fx/fx.h"
#include <nitro.h>
#include <string.h>

#include "constants/battle.h"
#include "constants/graphics.h"
#include "constants/heap.h"

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/encounter_effect.h"
#include "fieldmap/encounter_effect_core.h"
#include "fieldmap/fieldmap.h"
#include "fieldmap/hblank_system.h"
#include "fieldmap/linear_interpolation_task_fx32.h"
#include "fieldmap/linear_interpolation_task_s32.h"
#include "fieldmap/quadratic_interpolation_task_fx32.h"
#include "fieldmap/struct_brightness_fade_task.h"
#include "fieldmap/struct_encounter_sprite_renderer.h"
#include "fieldmap/struct_encounter_sprite_resources.h"

#include "bg_window.h"
#include "camera.h"
#include "enc_effects.h"
#include "field_battle_data_transfer.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "party_helpers.h"

enum ScreenFlashState {
    SCREENFLASH_STATE_INIT_OTHER_SCREEN_FADE = 0,
    SCREENFLASH_STATE_TARGET_INIT_SCREEN_FADE,
    SCREENFLASH_STATE_WAIT_FOR_TARGET_SCREEN_FADE,
    SCREENFLASH_STATE_RESET_TARGET_SCREEN_FADE,
    SCREENFLASH_STATE_WAIT_FOR_TARGET_SCREEN_FADE_RESET,
    SCREENFLASH_STATE_FINISH,
};

enum ScreenSliceEffectState {
    SCREENSLICE_STATE_INTERPOLATE = 0,
    SCREENSLICE_STATE_FINISH,
};

enum ScreenSplitEffectState {
    SCREENSPLIT_STATE_INTERPOLATE = 0,
    SCREENSPLIT_STATE_FINISH,
};

typedef struct ScreenFlash {
    enum ScreenFlashState state;
    u32 numFlashes;
    int flashCounter;
    enum Screen screen;
    u32 screenFlashColor;
    u32 otherScreenFlashColor;
    BrightnessFadeTask screenFadeTask;
    BrightnessFadeTask otherScreenFadeTask;
    BOOL *done;
} ScreenFlash;

typedef struct CutInEffect {
    u16 state;
    u8 ready;
    u8 finishRequested;
    FieldSystem *fieldSystem;
    ParticleSystem *particleSystem;
    void *particleBuffer;
    u32 texAllocOffset;
    u32 palAllocOffset;
} CutInEffect;

static void FieldMap_021DE89C(Window *param0, s32 param1, s32 param2, s32 param3, s32 param4, u8 param5);
static void FieldMap_021DEB04(Window *param0, u16 param1, u16 param2, u8 param3);
static void BrightnessFadeTask_SetBrightness(SysTask *task, void *param);
static void EncounterEffect_FlashTask(SysTask *task, void *param);
static void ScreenSliceEffect_CreateTasks(SysTask *param0, void *param1);
static void ScreenSliceSystem_VBlankCallback(SysTask *param0, void *param1);
static void ScreenSliceEffect_HBlankCallback(HBlankTask *param0, void *param1);
static void ScreenSliceEffect_Finish(ScreenSliceEffect *param0);
static void ScreenSplitEffect_SetupTasks(SysTask *param0, void *param1);
static void ScreenSplitEffect_VBlankCallback(SysTask *param0, void *param1);
static void ScreenSplitEffect_HBlankCallback(HBlankTask *param0, void *param1);
static void ScreenSplitEffect_Finish(ScreenSplitEffect *param0);
static void FieldMap_021DEDE8(SysTask *param0, void *param1);
static void FieldMap_021DEE24(SysTask *param0, void *param1);
static void FieldMap_021DEE50(HBlankTask *param0, void *param1);
static void FieldMap_021DEE84(EncounterScreenWave *param0);
static void FieldMap_021DE67C(Sprite *param0, void *param1, u32 param2);
static void FieldMap_021DF258(SysTask *param0, void *param1);
static void FieldMap_021DF28C(SysTask *param0, void *param1);
static void FieldMap_021DF30C(FieldSystem *fieldSystem);
static void FieldMap_021DF3D4(FieldSystem *fieldSystem);
static u32 FieldMap_021DF3E8(u32 param0, BOOL param1);
static u32 FieldMap_021DF414(u32 param0, BOOL param1);
static void EncounterEffect_UnusedTask(SysTask *dummy1, void *dummy2);
void EncounterEffect_Unused(void);

// "LowerLevel" means the level of the encountered Pokemon is lower
// than the player's first Pokemon, and vice versa
static const SysTaskFunc sEncounterEffectTaskFuncs[] = {
    EncounterEffect_Grass_LowerLevel,
    EncounterEffect_Grass_HigherLevel,
    EncounterEffect_Water_LowerLevel,
    EncounterEffect_Water_HigherLevel,
    EncounterEffect_Cave_LowerLevel,
    EncounterEffect_Cave_HigherLevel,

    EncounterEffect_Trainer_Grass_LowerLevel,
    EncounterEffect_Trainer_Grass_HigherLevel,
    EncounterEffect_Trainer_Water_LowerLevel,
    EncounterEffect_Trainer_Water_HigherLevel,
    EncounterEffect_Trainer_Cave_LowerLevel,
    EncounterEffect_Trainer_Cave_HigherLevel,

    EncounterEffect_LeaderRoark,
    EncounterEffect_LeaderGardenia,
    EncounterEffect_LeaderWake,
    EncounterEffect_LeaderMaylene,
    EncounterEffect_LeaderFantina,
    EncounterEffect_LeaderCandice,
    EncounterEffect_LeaderByron,
    EncounterEffect_LeaderVolkner,

    EncounterEffect_EliteFourAaron,
    EncounterEffect_EliteFourBertha,
    EncounterEffect_EliteFourFlint,
    EncounterEffect_EliteFourLucian,
    EncounterEffect_ChampionCynthia,

    EncounterEffect_Mythical,
    EncounterEffect_Legendary,

    EncounterEffect_GalacticGrunt,
    EncounterEffect_GalacticBoss,

    EncounterEffect_Frontier,
    EncounterEffect_Double
};

static const u8 Unk_FieldMap_021F9988[8] = {
    0x0,
    0x2,
    0x5,
    0x7,
    0x1,
    0x6,
    0x3,
    0x4
};

static const u16 Unk_FieldMap_021F9A2C[8][2] = {
    { 0x0, 0x17 },
    { 0x2D, 0x16 },
    { 0x2D, 0x44 },
    { 0x5A, 0x43 },
    { 0x5B, 0x71 },
    { 0x87, 0x70 },
    { 0x87, 0x9E },
    { 0xB4, 0x9D }
};

static CutInEffect *Unk_FieldMap_02202120 = NULL;

void EncounterEffect_Start(enum EncEffectCutIn effect, FieldSystem *fieldSystem, BOOL *done)
{
    SysTask *effectTask = SysTask_StartAndAllocateParam(sEncounterEffectTaskFuncs[effect], sizeof(EncounterEffect), 5, HEAP_ID_FIELD1);
    EncounterEffect *encEffect = SysTask_GetParam(effectTask);
    encEffect->fieldSystem = fieldSystem;
    encEffect->done = done;
    encEffect->narc = NARC_ctor(NARC_INDEX_GRAPHIC__FIELD_ENCOUNTEFFECT, HEAP_ID_FIELD1);

    if (encEffect->done != NULL) {
        *(encEffect->done) = FALSE;
    }

    encEffect->hBlankFlag = FALSE;
}

void EncounterEffect_Finish(EncounterEffect *encEffect, SysTask *effectTask)
{
    NARC_dtor(encEffect->narc);
    Heap_FreeExplicit(HEAP_ID_FIELD1, encEffect->param);
    SysTask_FinishAndFreeParam(effectTask);
}

void EncounterEffect_Flash(enum Screen screen, u32 screenFlashColor, u32 otherScreenFlashColor, BOOL *done, u32 numFlashes)
{
    ScreenFlash *screenFlash = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ScreenFlash));
    memset(screenFlash, 0, sizeof(ScreenFlash));
    SysTask_Start(EncounterEffect_FlashTask, screenFlash, 5);

    screenFlash->done = done;

    if (screenFlash->done != NULL) {
        *(screenFlash->done) = FALSE;
    }

    screenFlash->screen = screen;
    screenFlash->screenFlashColor = screenFlashColor;
    screenFlash->otherScreenFlashColor = otherScreenFlashColor;
    screenFlash->numFlashes = numFlashes;
}

static void EncounterEffect_FlashTask(SysTask *task, void *param)
{
    ScreenFlash *screenFlash = param;

    switch (screenFlash->state) {
    case SCREENFLASH_STATE_INIT_OTHER_SCREEN_FADE:
        if (screenFlash->screen == SCREEN_TOP) {
            BrightnessFadeTask_Init(&screenFlash->otherScreenFadeTask, 0, screenFlash->otherScreenFlashColor, 2, 8);
        } else {
            if (screenFlash->screen == SCREEN_BOTTOM) {
                BrightnessFadeTask_Init(&screenFlash->otherScreenFadeTask, 0, screenFlash->otherScreenFlashColor, 1, 8);
            }
        }

        screenFlash->state++;
        break;
    case SCREENFLASH_STATE_TARGET_INIT_SCREEN_FADE:
        BrightnessFadeTask_Init(&screenFlash->screenFadeTask, 0, screenFlash->screenFlashColor, screenFlash->screen, 3);
        screenFlash->state++;
        break;
    case SCREENFLASH_STATE_WAIT_FOR_TARGET_SCREEN_FADE:
        if (BrightnessFadeTask_Update(&screenFlash->screenFadeTask)) {
            screenFlash->state++;
        }
        break;
    case SCREENFLASH_STATE_RESET_TARGET_SCREEN_FADE:
        BrightnessFadeTask_Init(&screenFlash->screenFadeTask, screenFlash->screenFlashColor, 0, screenFlash->screen, 3);
        screenFlash->state++;
        break;
    case SCREENFLASH_STATE_WAIT_FOR_TARGET_SCREEN_FADE_RESET:
        if (BrightnessFadeTask_Update(&screenFlash->screenFadeTask)) {
            screenFlash->flashCounter++;

            if (screenFlash->flashCounter == screenFlash->numFlashes) {
                screenFlash->state = SCREENFLASH_STATE_FINISH;
            } else {
                screenFlash->state = SCREENFLASH_STATE_TARGET_INIT_SCREEN_FADE;
            }
        }
        break;
    case SCREENFLASH_STATE_FINISH:
        screenFlash->state = SCREENFLASH_STATE_INIT_OTHER_SCREEN_FADE;
        screenFlash->flashCounter = 0;

        if (screenFlash->done != NULL) {
            *(screenFlash->done) = TRUE;
        }

        SysTask_Done(task);
        Heap_Free(screenFlash);

        return;
    }

    BrightnessFadeTask_Update(&screenFlash->otherScreenFadeTask);
}

BOOL EncounterEffect_GetHBlankFlag(EncounterEffect *encEffect)
{
    return encEffect->hBlankFlag;
}

void LinearInterpolationTaskS32_Init(LinearInterpolationTaskS32 *task, int start, int end, int numSteps)
{
    task->currentValue = start;
    task->startValue = start;
    task->delta = end - start;
    task->numSteps = numSteps;
    task->currentStep = 0;
}

BOOL LinearInterpolationTaskS32_Update(LinearInterpolationTaskS32 *task)
{
    int interpolated = (task->delta * task->currentStep) / task->numSteps;

    task->currentValue = interpolated + task->startValue;

    if (task->currentStep + 1 <= task->numSteps) {
        task->currentStep++;
        return FALSE;
    }

    task->currentStep = task->numSteps;
    return TRUE;
}

void LinearInterpolationTaskFX32_Init(LinearInterpolationTaskFX32 *task, fx32 startValue, fx32 endValue, int numSteps)
{
    task->currentValue = startValue;
    task->startValue = startValue;
    task->delta = endValue - startValue;
    task->numSteps = numSteps;
    task->currentStep = 0;
}

BOOL LinearInterpolationTaskFX32_Update(LinearInterpolationTaskFX32 *task)
{
    fx32 interpolated = FX_Mul(task->delta, task->currentStep << FX32_SHIFT);
    interpolated = FX_Div(interpolated, task->numSteps << FX32_SHIFT);

    task->currentValue = interpolated + task->startValue;

    if (task->currentStep + 1 <= task->numSteps) {
        task->currentStep++;
        return FALSE;
    }

    task->currentStep = task->numSteps;
    return TRUE;
}

void QuadraticInterpolationTaskFX32_Init(QuadraticInterpolationTaskFX32 *task, fx32 startValue, fx32 endValue, fx32 initialRate, int numSteps)
{
    fx32 distance = endValue - startValue;
    fx32 tSquared = (numSteps * numSteps) << FX32_SHIFT;
    fx32 v0t = FX_Mul(initialRate, numSteps * FX32_ONE);
    v0t = distance - v0t;
    v0t = FX_Mul(v0t, 2 * FX32_ONE);
    fx32 quadraticCoeff = FX_Div(v0t, tSquared);

    task->currentValue = startValue;
    task->startValue = startValue;
    task->initialRate = initialRate;
    task->quadraticCoeff = quadraticCoeff;
    task->currentStep = 0;
    task->numSteps = numSteps;
}

BOOL QuadraticInterpolationTaskFX32_Update(QuadraticInterpolationTaskFX32 *task)
{
    // Quadratic interpolation
    // delta = linearTerm + ((quadraticCoeff * (currentStep^2)) / 2
    // f(t) = f(0) + v0t + (1/2)at^2
    fx32 linearTerm = FX_Mul(task->initialRate, task->currentStep << FX32_SHIFT);
    fx32 stepSquared = (task->currentStep * task->currentStep) << FX32_SHIFT;
    fx32 quadraticTerm = FX_Mul(task->quadraticCoeff, stepSquared);
    quadraticTerm = FX_Div(quadraticTerm, 2 * FX32_ONE);
    fx32 delta = linearTerm + quadraticTerm;

    task->currentValue = task->startValue + delta;

    if (task->currentStep + 1 <= task->numSteps) {
        task->currentStep++;
        return FALSE;
    }

    task->currentStep = task->numSteps;
    return TRUE;
}

void BrightnessFadeTask_ApplyBrightnessToScreen(enum Screen screen, int brightness)
{
    screen == SCREEN_TOP
        ? GX_SetMasterBrightness(brightness)
        : GXS_SetMasterBrightness(brightness);
}

void BrightnessFadeTask_Init(BrightnessFadeTask *task, s32 startValue, s32 endValue, s32 screen, s32 sync)
{
    task->screen = screen;
    LinearInterpolationTaskS32_Init(&task->interpolationTask, startValue, endValue, sync);
}

BOOL BrightnessFadeTask_Update(BrightnessFadeTask *task)
{
    BOOL finished = LinearInterpolationTaskS32_Update(&task->interpolationTask);
    SysTask_ExecuteAfterVBlank(BrightnessFadeTask_SetBrightness, task, 10);

    return finished;
}

static void BrightnessFadeTask_SetBrightness(SysTask *task, void *param)
{
    BrightnessFadeTask *brightnessTask = param;

    BrightnessFadeTask_ApplyBrightnessToScreen(brightnessTask->screen, brightnessTask->interpolationTask.currentValue);
    SysTask_Done(task);
}

ScreenSliceEffect *ScreenSliceEffect_New(void)
{
    ScreenSliceEffect *efx = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ScreenSliceEffect));
    memset(efx, 0, sizeof(ScreenSliceEffect));

    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_NONE, FALSE);

    return efx;
}

void ScreenSliceEffect_Delete(ScreenSliceEffect *efx)
{
    if (efx->hBlankTask != NULL) {
        ScreenSliceEffect_Finish(efx);
    }

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    Heap_Free(efx);
}

void EncounterEffect_ScreenSlice(EncounterEffect *encEffect, ScreenSliceEffect *screenSliceEfx, u8 pixelsPerSlice, u32 numSteps, fx32 startX, fx32 endX, fx32 initialSpeed)
{
    GF_ASSERT(screenSliceEfx->hBlankTask == NULL);

    encEffect->hBlankFlag = FALSE;
    screenSliceEfx->hBlankSystem = encEffect->fieldSystem->unk_04->hBlankSystem;
    screenSliceEfx->pixelsPerSlice = pixelsPerSlice;
    screenSliceEfx->state = SCREENSLICE_STATE_INTERPOLATE;
    screenSliceEfx->done = &encEffect->hBlankFlag;

    QuadraticInterpolationTaskFX32_Init(&screenSliceEfx->interpolationTask, startX, endX, initialSpeed, numSteps);

    if (startX >= 0) {
        G2_SetWnd0Position(0, 0, 255 - startX, 192);
        G2_SetWnd1Position(0, 0, 1 + startX, 192);
    } else {
        G2_SetWnd0Position(0, 0, 255 + startX, 192);
        G2_SetWnd1Position(0, 0, 1 - startX, 192);
    }

    SysTask_ExecuteAfterVBlank(ScreenSliceEffect_CreateTasks, screenSliceEfx, 1024);
}

static void ScreenSliceEffect_CreateTasks(SysTask *task, void *param)
{
    ScreenSliceEffect *screenSliceEfx = param;

    screenSliceEfx->vBlankTask = SysTask_ExecuteAfterVBlank(ScreenSliceSystem_VBlankCallback, screenSliceEfx, 1024);
    screenSliceEfx->hBlankTask = HBlankSystem_StartTask(screenSliceEfx->hBlankSystem, ScreenSliceEffect_HBlankCallback, screenSliceEfx);

    SysTask_Done(task);
}

void ScreenSliceEffect_Modify(EncounterEffect *encEffect, ScreenSliceEffect *screenSliceEfx, u8 pixelsPerSlice, u32 numSteps, fx32 startX, fx32 endX, fx32 initialSpeed)
{
    GF_ASSERT(EncounterEffect_GetHBlankFlag(encEffect) == FALSE);

    screenSliceEfx->pixelsPerSlice = pixelsPerSlice;
    screenSliceEfx->state = SCREENSLICE_STATE_INTERPOLATE;

    QuadraticInterpolationTaskFX32_Init(&screenSliceEfx->interpolationTask, startX, endX, initialSpeed, numSteps);
}

static void ScreenSliceSystem_VBlankCallback(SysTask *task, void *param)
{
    ScreenSliceEffect *screenSliceEfx = param;

    switch (screenSliceEfx->state) {
    case SCREENSLICE_STATE_INTERPOLATE:
        if (QuadraticInterpolationTaskFX32_Update(&screenSliceEfx->interpolationTask)) {
            screenSliceEfx->state++;
        }

        s32 currentX = screenSliceEfx->interpolationTask.currentValue >> FX32_SHIFT;

        if (currentX >= 0) {
            G2_SetWnd0Position(0, 0, 255 - currentX, 192);
            G2_SetWnd1Position(0, 0, 1 + currentX, 192);
        } else {
            G2_SetWnd0Position(0, 0, 255 + currentX, 192);
            G2_SetWnd1Position(0, 0, 1 - currentX, 192);
        }
        break;
    case SCREENSLICE_STATE_FINISH:
        ScreenSliceEffect_Finish(param);
        break;
    }
}

static void ScreenSliceEffect_Finish(ScreenSliceEffect *screenSliceEfx)
{
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
    G2_SetWnd0Position(0, 0, 0, 0);
    GX_SetVisibleWnd(GX_WNDMASK_W0);

    *(screenSliceEfx->done) = TRUE;

    HBlankTask_Delete(screenSliceEfx->hBlankTask);
    screenSliceEfx->hBlankTask = NULL;
    SysTask_Done(screenSliceEfx->vBlankTask);
    screenSliceEfx->vBlankTask = NULL;
}

static void ScreenSliceEffect_HBlankCallback(HBlankTask *task, void *param)
{
    ScreenSliceEffect *screenSliceEfx = param;
    int vCount;
    int currentX;

    vCount = GX_GetVCount();

    if (((vCount / screenSliceEfx->pixelsPerSlice) % 2) == 0) {
        currentX = screenSliceEfx->interpolationTask.currentValue >> FX32_SHIFT;
    } else {
        currentX = -screenSliceEfx->interpolationTask.currentValue >> FX32_SHIFT;
    }

    G2_SetBG0Offset(currentX, 0);
    G2_SetBG1Offset(currentX, 0);
    G2_SetBG2Offset(currentX, 0);
    G2_SetBG3Offset(currentX, 0);

    if (currentX >= 0) {
        GX_SetVisibleWnd(GX_WNDMASK_W0);
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
    } else {
        GX_SetVisibleWnd(GX_WNDMASK_W1);
        G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    }
}

ScreenSplitEffect *ScreenSplitEffect_New(void)
{
    ScreenSplitEffect *screenSplitEfx = Heap_Alloc(HEAP_ID_FIELD1, sizeof(ScreenSplitEffect));
    memset(screenSplitEfx, 0, sizeof(ScreenSplitEffect));

    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);

    return screenSplitEfx;
}

void ScreenSplitEffect_Delete(ScreenSplitEffect *screenSplitEfx)
{
    if (screenSplitEfx->hBlankTask != NULL) {
        ScreenSplitEffect_Finish(screenSplitEfx);
    }

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    Heap_Free(screenSplitEfx);
}

void EncounterEffect_ScreenSplit(EncounterEffect *encEffect, ScreenSplitEffect *screenSplitEfx, u32 numSteps, fx32 initialSpeedX, fx32 initialSpeedY)
{
    GF_ASSERT(screenSplitEfx->hBlankTask == NULL);

    encEffect->hBlankFlag = FALSE;
    screenSplitEfx->hBlankSystem = encEffect->fieldSystem->unk_04->hBlankSystem;
    screenSplitEfx->splitHeight = 96;
    screenSplitEfx->state = SCREENSPLIT_STATE_INTERPOLATE;
    screenSplitEfx->done = &encEffect->hBlankFlag;

    QuadraticInterpolationTaskFX32_Init(&screenSplitEfx->xInterpolationTask, 0, 255 * FX32_ONE, initialSpeedX, numSteps);
    QuadraticInterpolationTaskFX32_Init(&screenSplitEfx->yInterpolationTask, 0, 96 * FX32_ONE, initialSpeedY, numSteps);

    G2_SetWnd0Position(0, 0, 255, 192);
    G2_SetWnd1Position(0, 0, 255, 192);

    SysTask_ExecuteAfterVBlank(ScreenSplitEffect_SetupTasks, screenSplitEfx, 1024);
}

static void ScreenSplitEffect_SetupTasks(SysTask *task, void *param)
{
    ScreenSplitEffect *screenSplitEfx = param;

    screenSplitEfx->vBlankTask = SysTask_ExecuteAfterVBlank(ScreenSplitEffect_VBlankCallback, screenSplitEfx, 1024);
    screenSplitEfx->hBlankTask = HBlankSystem_StartTask(screenSplitEfx->hBlankSystem, ScreenSplitEffect_HBlankCallback, screenSplitEfx);

    SysTask_Done(task);
}

static void ScreenSplitEffect_VBlankCallback(SysTask *task, void *param)
{
    ScreenSplitEffect *screenSplitEfx = param;

    switch (screenSplitEfx->state) {
    case SCREENSPLIT_STATE_INTERPOLATE:
        QuadraticInterpolationTaskFX32_Update(&screenSplitEfx->yInterpolationTask);

        if (QuadraticInterpolationTaskFX32_Update(&screenSplitEfx->xInterpolationTask)) {
            screenSplitEfx->state++;
        }

        s32 currentX = screenSplitEfx->xInterpolationTask.currentValue >> FX32_SHIFT;
        s32 currentY = screenSplitEfx->yInterpolationTask.currentValue >> FX32_SHIFT;
        G2_SetWnd0Position(0, 0, 255 - currentX, 96 - currentY);
        G2_SetWnd1Position(currentX, 96 + currentY, 255, 192);
        break;
    case SCREENSPLIT_STATE_FINISH:
        ScreenSplitEffect_Finish(param);
        break;
    }
}

static void ScreenSplitEffect_HBlankCallback(HBlankTask *task, void *param)
{
    ScreenSplitEffect *screenSplitEfx = param;
    int vCount;
    int v2;
    int v3;

    vCount = GX_GetVCount();

    if (vCount <= screenSplitEfx->splitHeight) {
        GX_SetVisibleWnd(GX_WNDMASK_W0);
    } else {
        GX_SetVisibleWnd(GX_WNDMASK_W1);
    }
}

static void ScreenSplitEffect_Finish(ScreenSplitEffect *screenSplitEfx)
{
    G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
    G2_SetWnd0Position(0, 0, 0, 0);
    GX_SetVisibleWnd(GX_WNDMASK_W0);

    *(screenSplitEfx->done) = TRUE;

    HBlankTask_Delete(screenSplitEfx->hBlankTask);
    screenSplitEfx->hBlankTask = NULL;
    SysTask_Done(screenSplitEfx->vBlankTask);
    screenSplitEfx->vBlankTask = NULL;
}

void EncounterEffect_Unused(void)
{
    SysTaskFunc dummy = EncounterEffect_UnusedTask;
}

static void EncounterEffect_UnusedTask(SysTask *dummy1, void *dummy2)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_1,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x04000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_256,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 0,
            .areaOver = 1,
            .mosaic = FALSE,
        };
    }
}

void FieldMap_021DE3D0(NARC *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, BgConfig *param6, u32 param7)
{
    void *v0;
    NNSG2dScreenData *v1;

    Graphics_LoadPaletteFromOpenNARC(param0, param3, 0, param4 * 32, param5 * 32, HEAP_ID_FIELD1);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param0, param2, param6, param7, 0, 0, 0, HEAP_ID_FIELD1);

    v0 = Graphics_GetScrnDataFromOpenNARC(param0, param1, 0, &v1, HEAP_ID_FIELD1);

    Bg_LoadToTilemapRect(param6, param7, v1->rawData, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8);
    Bg_ChangeTilemapRectPalette(param6, param7, 0, 0, v1->screenWidth / 8, v1->screenHeight / 8, param4);
    Heap_Free(v0);
    Bg_ScheduleTilemapTransfer(param6, param7);
}

void EncounterEffect_InitSpriteCollection(EncounterSpriteRenderer *param0, int param1, int param2)
{
    int v0;

    param0->spriteList = SpriteList_InitRendering(param1, &param0->renderer, HEAP_ID_FIELD1);

    for (v0 = 0; v0 < 4; v0++) {
        param0->spriteResourceCollections[v0] = SpriteResourceCollection_New(param2, v0, HEAP_ID_FIELD1);
    }
}

void FieldMap_021DE4AC(EncounterSpriteRenderer *param0)
{
    int v0;

    SpriteList_Delete(param0->spriteList);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->spriteResourceCollections[v0]);
    }
}

void FieldMap_021DE4CC(NARC *param0, EncounterSpriteRenderer *param1, EncounterSpriteResources *param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8)
{
    param2->resources[0] = SpriteResourceCollection_AddTilesFromEx(param1->spriteResourceCollections[0], param0, param5, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, 4, HEAP_ID_SAVE);
    param2->resources[1] = SpriteResourceCollection_AddPaletteFrom(param1->spriteResourceCollections[1], param0, param3, 0, param8, NNS_G2D_VRAM_TYPE_2DMAIN, param4, HEAP_ID_FIELD1);
    param2->resources[2] = SpriteResourceCollection_AddFrom(param1->spriteResourceCollections[2], param0, param6, 0, param8, 2, HEAP_ID_FIELD1);
    param2->resources[3] = SpriteResourceCollection_AddFrom(param1->spriteResourceCollections[3], param0, param7, 0, param8, 3, HEAP_ID_FIELD1);

    SpriteTransfer_RequestCharAtEnd(param2->resources[0]);
    SpriteResource_ReleaseData(param2->resources[0]);
    SpriteTransfer_RequestPlttFreeSpace(param2->resources[1]);
    SpriteResourcesHeader_Init(&param2->header, param8, param8, param8, param8, 0xffffffff, 0xffffffff, 0, 0, param1->spriteResourceCollections[0], param1->spriteResourceCollections[1], param1->spriteResourceCollections[2], param1->spriteResourceCollections[3], NULL, NULL);
}

void FieldMap_021DE5A4(EncounterSpriteRenderer *param0, EncounterSpriteResources *param1)
{
    int v0;

    SpriteTransfer_ResetCharTransfer(param1->resources[0]);
    SpriteTransfer_ResetPlttTransfer(param1->resources[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param0->spriteResourceCollections[v0], param1->resources[v0]);
    }
}

void EncounterEffect_BlendTrainerSpritePltt(Sprite *mugshotSprite, enum HeapID heapID, enum TrainerClass trainerClass, u8 fraction, u16 target)
{
    TrainerClassGraphicIndex classIndex;
    NNSG2dPaletteData *paletteData;
    void *nclrBuffer;
    u16 *objPltt;

    SpriteSystem_SetTrainerClassGraphicsIndex(trainerClass, FACE_FRONT, &classIndex);
    objPltt = Heap_Alloc(heapID, PALETTE_SIZE_BYTES);
    nclrBuffer = Graphics_GetPlttData(classIndex.narcID, classIndex.palette, &paletteData, heapID);
    BlendPalette(paletteData->pRawData, objPltt, SLOTS_PER_PALETTE, fraction, target);

    FieldMap_021DE67C(mugshotSprite, objPltt, PALETTE_SIZE_BYTES);

    Heap_Free(objPltt);
    Heap_Free(nclrBuffer);
}

Sprite *FieldMap_021DE62C(EncounterSpriteRenderer *param0, EncounterSpriteResources *param1, fx32 param2, fx32 param3, fx32 param4, int param5)
{
    SpriteListTemplate v0;
    Sprite *v1;

    v0.list = param0->spriteList;
    v0.resourceData = &param1->header;
    v0.position.x = param2;
    v0.position.y = param3;
    v0.position.z = param4;
    v0.priority = param5;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.heapID = HEAP_ID_FIELD1;

    v1 = SpriteList_Add(&v0);
    GF_ASSERT(v1);
    return v1;
}

VecFx32 VecFx32_FromXYZ(fx32 x, fx32 y, fx32 z)
{
    return (VecFx32) { x, y, z };
}

static void FieldMap_021DE67C(Sprite *param0, void *param1, u32 param2)
{
    NNSG2dImagePaletteProxy *v0 = Sprite_GetPaletteProxy(param0);

    DC_FlushRange(param1, param2);
    GX_LoadOBJPltt(param1, NNS_G2dGetImagePaletteLocation(v0, NNS_G2D_VRAM_TYPE_2DMAIN), param2);
}

EncounterTextFade *FieldMap_021DE6A4(u32 heapID)
{
    EncounterTextFade *v0 = Heap_Alloc(heapID, sizeof(EncounterTextFade));
    memset(v0, 0, sizeof(EncounterTextFade));

    return v0;
}

void FieldMap_021DE6BC(EncounterTextFade *param0)
{
    Heap_Free(param0);
}

void FieldMap_021DE6C4(EncounterTextFade *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9)
{
    GF_ASSERT(param0->active == 0);

    LinearInterpolationTaskS32_Init(&param0->xInterpolationTask, param1, param2, param5);
    LinearInterpolationTaskS32_Init(&param0->yInterpolationTask, param3, param4, param5);

    param0->window = param6;
    param0->width = param7;
    param0->height = param8;
    param0->color = param9;
    param0->active = 1;
}

BOOL FieldMap_021DE71C(EncounterTextFade *param0)
{
    BOOL v0;
    s16 v1, v2, v3, v4;

    if (param0->active == 0) {
        return 1;
    }

    v0 = LinearInterpolationTaskS32_Update(&param0->xInterpolationTask);
    LinearInterpolationTaskS32_Update(&param0->yInterpolationTask);

    v3 = param0->xInterpolationTask.currentValue - (param0->width / 2);
    v1 = param0->yInterpolationTask.currentValue - (param0->height / 2);
    v4 = v3 + param0->width;
    v2 = v1 + param0->height;

    FieldMap_021DE89C(param0->window, v1, v2, v3, v4, param0->color);

    return v0;
}

static EncounterTextChar *FieldMap_021DE784(u32 heapID)
{
    EncounterTextChar *v0 = Heap_Alloc(heapID, sizeof(EncounterTextChar));

    memset(v0, 0, sizeof(EncounterTextChar));
    return v0;
}

void FieldMap_021DE79C(EncounterTextChar *param0)
{
    Heap_Free(param0);
}

void FieldMap_021DE7A4(EncounterTextChar *param0, int param1, int param2, int param3, int param4, int param5, Window *param6, u32 param7, u32 param8, u8 param9)
{
    GF_ASSERT(param0->active == 0);

    LinearInterpolationTaskS32_Init(&param0->xInterpolationTask, param1, param2, param5);
    LinearInterpolationTaskS32_Init(&param0->yInterpolationTask, param3, param4, param5);

    param0->window = param6;
    param0->width = param7;
    param0->height = param8;
    param0->color = param9;
    param0->active = 1;
}

BOOL FieldMap_021DE7FC(EncounterTextChar *param0)
{
    BOOL v0;
    s16 v1, v2, v3, v4;

    if (param0->active == 0) {
        return 1;
    }

    v3 = param0->xInterpolationTask.currentValue - (param0->width / 2);
    v1 = param0->yInterpolationTask.currentValue - (param0->height / 2);
    v4 = v3 + param0->width;
    v2 = v1 + param0->height;

    FieldMap_021DE89C(param0->window, v1, v2, v3, v4, 0);
    v0 = LinearInterpolationTaskS32_Update(&param0->xInterpolationTask);
    LinearInterpolationTaskS32_Update(&param0->yInterpolationTask);

    v3 = param0->xInterpolationTask.currentValue - (param0->width / 2);
    v1 = param0->yInterpolationTask.currentValue - (param0->height / 2);
    v4 = v3 + param0->width;
    v2 = v1 + param0->height;

    FieldMap_021DE89C(param0->window, v1, v2, v3, v4, param0->color);

    return v0;
}

static void FieldMap_021DE89C(Window *param0, s32 param1, s32 param2, s32 param3, s32 param4, u8 param5)
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

EncounterTextScroll *FieldMap_021DE8F8(u32 heapID)
{
    EncounterTextScroll *v0;
    int v1;

    v0 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(EncounterTextScroll));
    memset(v0, 0, sizeof(EncounterTextScroll));

    for (v1 = 0; v1 < 48; v1++) {
        v0->chars[v1] = FieldMap_021DE784(heapID);
    }

    return v0;
}

void FieldMap_021DE928(EncounterTextScroll *param0)
{
    int v0;

    for (v0 = 0; v0 < 48; v0++) {
        FieldMap_021DE79C(param0->chars[v0]);
    }

    Heap_Free(param0);
}

void FieldMap_021DE948(EncounterTextScroll *param0, u8 param1, u8 param2, Window *param3, u8 param4)
{
    param0->window = param3;
    param0->color = param4;
    param0->interpolationSteps = param1;
    param0->spawnDelay = param2;
    param0->charIndex = 0;
    param0->finishedCharCount = 0;
    param0->spawnTimer = 0;
    param0->active = 1;
}

BOOL FieldMap_021DE988(EncounterTextScroll *param0)
{
    int v0, v1, v2;
    int v3;
    BOOL v4;

    if (param0->active == 0) {
        return 1;
    }

    if (param0->charIndex < 48) {
        param0->spawnTimer--;

        if (param0->spawnTimer <= 0) {
            param0->spawnTimer = param0->spawnDelay;

            v0 = Unk_FieldMap_021F9988[param0->charIndex % 8];
            v0 = (32 / 2) + (v0 * 32);
            v1 = -16 - ((param0->charIndex / 8) * 32);
            v2 = (192 + -16) - ((param0->charIndex / 8) * 32);

            FieldMap_021DE7A4(param0->chars[param0->charIndex], v0, v0, v1, v2, param0->interpolationSteps, param0->window, 32, 32, param0->color);
            param0->charIndex++;
        }
    }

    for (v3 = param0->finishedCharCount; v3 < param0->charIndex; v3++) {
        v4 = FieldMap_021DE7FC(param0->chars[v3]);

        if (v4 == 1) {
            param0->finishedCharCount++;
        }
    }

    if ((param0->finishedCharCount >= 48) && (v4 == 1)) {
        param0->active = 0;
        return 1;
    }

    return 0;
}

EncounterTextLine *FieldMap_021DEA80(u32 heapID)
{
    EncounterTextLine *v0 = Heap_Alloc(heapID, sizeof(EncounterTextLine));
    memset(v0, 0, sizeof(EncounterTextLine));
    return v0;
}

void FieldMap_021DEA98(EncounterTextLine *param0)
{
    Heap_Free(param0);
}

void FieldMap_021DEAA0(EncounterTextLine *param0, u8 param1, u16 param2, u16 param3, Window *param4, u8 param5)
{
    param0->window = param4;
    param0->color = param5;
    param0->active = 1;

    LinearInterpolationTaskS32_Init(&param0->interpolationTask, param2, param3, param1);
}

BOOL FieldMap_021DEAC8(EncounterTextLine *param0)
{
    BOOL v0;
    u16 v1;

    if (param0->active == 0) {
        return 1;
    }

    v1 = param0->interpolationTask.currentValue;
    v0 = LinearInterpolationTaskS32_Update(&param0->interpolationTask);

    FieldMap_021DEB04(param0->window, v1, param0->interpolationTask.currentValue, param0->color);

    if (v0 == 1) {
        param0->active = 0;
        return 1;
    }

    return 0;
}

static inline fx32 inline_FieldMap_021DEB04(u16 param0)
{
    return FX_Div(FX_SinIdx(param0), FX_CosIdx(param0));
}

static void FieldMap_021DEB04(Window *param0, u16 param1, u16 param2, u8 param3)
{
    int v0, v1, v2;
    int v3, v4;
    int v5;
    int v6;
    fx32 v7, v8;

    v7 = inline_FieldMap_021DEB04(param2);
    v8 = inline_FieldMap_021DEB04(param1);

    for (v5 = 0; v5 < 96; v5++) {
        v6 = 95 - v5;
        v0 = FX_Mul(v7, v6 * FX32_ONE) >> FX32_SHIFT;
        v1 = FX_Mul(v8, v6 * FX32_ONE) >> FX32_SHIFT;
        v3 = 128 + v0;
        v4 = 128 + v1;
        v0 = 128 - v0;
        v1 = 128 - v1;

        if (v1 > v0) {
            v2 = v1;
            v1 = v0;
            v0 = v2;
        }

        if (v4 > v3) {
            v2 = v4;
            v4 = v3;
            v3 = v2;
        }

        FieldMap_021DE89C(param0, v5, v5 + 1, v1, v0 + 1, param3);
        FieldMap_021DE89C(param0, 191 - v5, 192 - v5, v4, v3 + 1, param3);
    }
}

EncounterTextLines *FieldMap_021DEBEC(u32 heapID)
{
    EncounterTextLines *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(EncounterTextLines));
    memset(v0, 0, sizeof(EncounterTextLines));

    for (v1 = 0; v1 < 8; v1++) {
        v0->lines[v1] = FieldMap_021DEA80(heapID);
    }

    return v0;
}

void FieldMap_021DEC18(EncounterTextLines *param0)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        FieldMap_021DEA98(param0->lines[v0]);
    }

    Heap_Free(param0);
}

void FieldMap_021DEC38(EncounterTextLines *param0, u8 param1, Window *param2, u8 param3)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        FieldMap_021DEAA0(param0->lines[v0], param1, (Unk_FieldMap_021F9A2C[v0][0] * 0xffff) / 360, (Unk_FieldMap_021F9A2C[v0][1] * 0xffff) / 360, param2, param3);
    }

    param0->active = 1;
    FieldMap_021DE89C(param2, 93, 99, 0, 256, param3);
}

BOOL FieldMap_021DECB8(EncounterTextLines *param0)
{
    int v0;
    BOOL v1;

    if (param0->active == 0) {
        return 1;
    }

    for (v0 = 0; v0 < 8; v0++) {
        v1 = FieldMap_021DEAC8(param0->lines[v0]);
    }

    if (v1 == 1) {
        param0->active = 0;
        return 1;
    }

    return 0;
}

EncounterScreenWave *FieldMap_021DECEC(void)
{
    EncounterScreenWave *v0 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(EncounterScreenWave));
    memset(v0, 0, sizeof(EncounterScreenWave));

    return v0;
}

void FieldMap_021DED04(EncounterScreenWave *param0)
{
    if (param0->vBlankTask != NULL) {
        FieldMap_021DEE84(param0);
    }

    Heap_Free(param0);
}

void FieldMap_021DED20(EncounterEffect *param0, EncounterScreenWave *param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6)
{
    int v0;
    int v1;
    int v2;

    GF_ASSERT(param1->vBlankTask == NULL);

    param0->hBlankFlag = 0;
    param1->hBlankSystem = param0->fieldSystem->unk_04->hBlankSystem;
    param1->state = 0;
    param1->done = &param0->hBlankFlag;

    LinearInterpolationTaskS32_Init(&param1->interpolationTask, 255, 0, param2);

    for (v0 = 0; v0 < 192; v0++) {
        v1 = v0 % param3;
        v2 = v1 * param4;
        v2 = v2 / param3;

        if (((v0 / param3) % 2) == 0) {
            param1->vOffsets[v0] = v2;
        } else {
            param1->vOffsets[v0] = param4 - v2;
        }
    }

    G2_SetWnd0InsidePlane(param5, 1);
    G2_SetWndOutsidePlane(param6, 0);
    G2_SetWnd0Position(0, 0, 0, 192);
    GX_SetVisibleWnd(GX_WNDMASK_W0);

    SysTask_ExecuteAfterVBlank(FieldMap_021DEDE8, param1, 1024);
}

static void FieldMap_021DEDE8(SysTask *param0, void *param1)
{
    EncounterScreenWave *v0 = param1;

    v0->hBlankTask = HBlankSystem_StartTask(v0->hBlankSystem, FieldMap_021DEE50, v0);
    v0->vBlankTask = SysTask_ExecuteAfterVBlank(FieldMap_021DEE24, v0, 1024);

    SysTask_Done(param0);
}

static void FieldMap_021DEE24(SysTask *param0, void *param1)
{
    EncounterScreenWave *v0 = param1;
    BOOL v1;

    switch (v0->state) {
    case 0:
        v1 = LinearInterpolationTaskS32_Update(&v0->interpolationTask);

        if (v1 == 1) {
            v0->state++;
        }
        break;
    case 1:
        FieldMap_021DEE84(v0);
        break;
    }
}

static void FieldMap_021DEE50(HBlankTask *param0, void *param1)
{
    EncounterScreenWave *v0 = param1;
    int v1;
    int v2 = GX_GetVCount();

    if (v2 < 192) {
        v1 = -v0->vOffsets[v2] + v0->interpolationTask.currentValue;

        if (v1 < 0) {
            v1 = 0;
        }

        G2_SetWnd0Position(v1, 0, 255, 192);
    }
}

static void FieldMap_021DEE84(EncounterScreenWave *param0)
{
    GX_SetVisibleWnd(GX_WNDMASK_NONE);

    *(param0->done) = 1;
    HBlankTask_Delete(param0->hBlankTask);
    param0->hBlankTask = NULL;
    SysTask_Done(param0->vBlankTask);
    param0->vBlankTask = NULL;
}

u32 CutInEffects_ForBattle(const FieldBattleDTO *param0)
{
    int v0;
    int v1;
    int v2;
    Pokemon *v3;
    Pokemon *v4;
    int v5, v6;

    if (param0->battleType & BATTLE_TYPE_TRAINER) {
        v2 = 1;
        // Implicitly, this must be a wild battle
    } else if ((param0->battleType & BATTLE_TYPE_SPECIAL_WILD)
        || (param0->battleType == BATTLE_TYPE_SINGLES)) {
        v2 = 0;
    } else {
        GF_ASSERT(FALSE);
        v2 = 0;
    }

    v3 = Party_FindFirstEligibleBattler(param0->parties[0]);
    v4 = Party_FindFirstEligibleBattler(param0->parties[1]);
    v5 = Pokemon_GetValue(v3, MON_DATA_LEVEL, NULL);
    v6 = Pokemon_GetValue(v4, MON_DATA_LEVEL, NULL);
    v0 = v6 - v5;

    switch (param0->terrain) {
    case TERRAIN_PLAIN:
    case TERRAIN_SAND:
    case TERRAIN_GRASS:
    case TERRAIN_PUDDLE:
    case TERRAIN_MOUNTAIN:
    case TERRAIN_SNOW:
    case TERRAIN_ICE:
    case TERRAIN_BUILDING:
    case TERRAIN_GREAT_MARSH:
    case TERRAIN_BRIDGE:
    case TERRAIN_MAX:
        v1 = 0 * 2;
        break;
    case TERRAIN_WATER:
        v1 = 1 * 2;
        break;
    case TERRAIN_CAVE:
        v1 = 2 * 2;
        break;
    }

    if (v0 > 0) {
        v1++;
    }

    return (v2 * 6) + v1;
}

static void FieldMap_021DEF74(SysTask *param0, void *param1)
{
    int *v0 = param1;

    GX_SetMasterBrightness(*v0);
    SysTask_Done(param0);
}

void FieldMap_021DEF8C(int *param0)
{
    SysTask_ExecuteAfterVBlank(FieldMap_021DEF74, param0, 1024);
}

void FieldMap_021DEFA0(FieldSystem *fieldSystem)
{
    GF_ASSERT(Unk_FieldMap_02202120 == NULL);

    Unk_FieldMap_02202120 = Heap_Alloc(HEAP_ID_FIELD1, sizeof(CutInEffect));
    memset(Unk_FieldMap_02202120, 0, sizeof(CutInEffect));

    Unk_FieldMap_02202120->state = 0;
    Unk_FieldMap_02202120->ready = 0;
    Unk_FieldMap_02202120->fieldSystem = fieldSystem;

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);

    GX_ResetBankForBG();
    MI_CpuClearFast((void *)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE);
    GX_SetCapture(GX_CAPTURE_SIZE_256x192, GX_CAPTURE_MODE_AB, GX_CAPTURE_SRCA_2D3D, GX_CAPTURE_SRCB_VRAM_0x00000, GX_CAPTURE_DEST_VRAM_C_0x00000, 4, 12);

    SysTask_ExecuteAfterVBlank(FieldMap_021DF258, Unk_FieldMap_02202120, 1024);
    SysTask_Start(FieldMap_021DF28C, Unk_FieldMap_02202120, 1024);
}

void FieldMap_021DF038(void)
{
    GF_ASSERT(Unk_FieldMap_02202120);
    Unk_FieldMap_02202120->finishRequested = 1;
}

BOOL FieldMap_021DF054(void)
{
    GF_ASSERT(Unk_FieldMap_02202120);
    return Unk_FieldMap_02202120->ready;
}

void FieldMap_021DF070(void)
{
    if (Unk_FieldMap_02202120 == NULL) {
        return;
    }

    ParticleSystem_DrawAll();
}

void FieldMap_021DF084(void)
{
    GF_ASSERT(Unk_FieldMap_02202120);

    ParticleSystem_FreeAll();

    FieldMap_021DF3D4(Unk_FieldMap_02202120->fieldSystem);
    FieldMap_021D16F4(Unk_FieldMap_02202120->fieldSystem, 1);
    FieldMap_021D1718(Unk_FieldMap_02202120->fieldSystem, 1);

    Heap_Free(Unk_FieldMap_02202120);
    Unk_FieldMap_02202120 = NULL;
}

void FieldMap_021DF0CC(NARC *param0, u32 param1)
{
    void *v0;
    Camera *v1;

    GF_ASSERT(Unk_FieldMap_02202120);
    GF_ASSERT(Unk_FieldMap_02202120->particleSystem == NULL);

    Unk_FieldMap_02202120->particleBuffer = Heap_Alloc(HEAP_ID_FIELD1, 0x4800);
    Unk_FieldMap_02202120->particleSystem = ParticleSystem_New(FieldMap_021DF3E8, FieldMap_021DF414, Unk_FieldMap_02202120->particleBuffer, 0x4800, 1, HEAP_ID_FIELD1);
    GF_ASSERT(Unk_FieldMap_02202120->particleSystem);

    ParticleSystem_SetCameraProjection(Unk_FieldMap_02202120->particleSystem, 1);

    v1 = ParticleSystem_GetCamera(Unk_FieldMap_02202120->particleSystem);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, v1);

    v0 = LoadMemberFromOpenNARC(param0, param1, 0, HEAP_ID_FIELD1, 0);
    ParticleSystem_SetResource(Unk_FieldMap_02202120->particleSystem, v0, 0 | 0, 0);
}

void FieldMap_021DF17C(u32 param0)
{
    int v0;
    VecFx32 v1 = { 0, 0, 0 };

    GF_ASSERT(Unk_FieldMap_02202120);
    GF_ASSERT(Unk_FieldMap_02202120->particleSystem);

    for (v0 = 0; v0 < param0; v0++) {
        ParticleSystem_CreateEmitter(Unk_FieldMap_02202120->particleSystem, v0, &v1);
    }
}

BOOL FieldMap_021DF1CC(void)
{
    GF_ASSERT(Unk_FieldMap_02202120);

    if (Unk_FieldMap_02202120->particleSystem == NULL) {
        return 1;
    }

    ParticleSystem_UpdateAll();

    if (ParticleSystem_GetActiveEmitterCount(Unk_FieldMap_02202120->particleSystem) == 0) {
        return 1;
    }

    return 0;
}

BOOL FieldMap_021DF208(void)
{
    if (ParticleSystem_GetActiveEmitterCount(Unk_FieldMap_02202120->particleSystem) == 0) {
        return 1;
    }

    return 0;
}

void FieldMap_021DF224(void)
{
    GF_ASSERT(Unk_FieldMap_02202120);

    ParticleSystem_Free(Unk_FieldMap_02202120->particleSystem);
    Heap_Free(Unk_FieldMap_02202120->particleBuffer);

    Unk_FieldMap_02202120->particleSystem = NULL;
    Unk_FieldMap_02202120->particleBuffer = NULL;
}

static void FieldMap_021DF258(SysTask *param0, void *param1)
{
    CutInEffect *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->state++;
        break;
    case 1:
        if (v0->finishRequested == 1) {
            FieldMap_021DF30C(v0->fieldSystem);
            SysTask_Done(param0);
            v0->state++;
        }
        break;
    }
}

static void FieldMap_021DF28C(SysTask *param0, void *param1)
{
    CutInEffect *v0 = param1;

    switch (v0->state) {
    case 2:

        ParticleSystem_ZeroAll();

        {
            VecFx32 v1 = { 0 };
            VecFx32 v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
            MtxFx33 v3;

            MTX_Identity33(&v3);

            NNS_G3dGlbSetBaseTrans(&v1);
            NNS_G3dGlbSetBaseScale(&v2);
            NNS_G3dGlbSetBaseRot(&v3);
        }

        FieldMap_021D16F4(v0->fieldSystem, 0);
        FieldMap_021D1718(v0->fieldSystem, 0);

        Bg_SetPriority(BG_LAYER_MAIN_0, 0);

        v0->ready = 1;
        SysTask_Done(param0);
        break;
    default:
        break;
    }
}

static void FieldMap_021DF30C(FieldSystem *fieldSystem)
{
    {
        GXBanks v0 = {
            GX_VRAM_BG_256_BC,
            GX_VRAM_BGEXTPLTT_NONE,
            GX_VRAM_SUB_BG_32_H,
            GX_VRAM_SUB_BGEXTPLTT_NONE,
            GX_VRAM_OBJ_16_F,
            GX_VRAM_OBJEXTPLTT_NONE,
            GX_VRAM_SUB_OBJ_16_I,
            GX_VRAM_SUB_OBJEXTPLTT_NONE,
            GX_VRAM_TEX_0_A,
            GX_VRAM_TEXPLTT_0123_E
        };

        GXLayers_SetBanks(&v0);
    }

    GXLayers_EngineAToggleLayers(
        GX_PLANEMASK_BG0, 0);

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_3,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v1);
    }

    {
        FieldMap_021D143C(fieldSystem->bgConfig);

        {
            G2_SetBG3ControlDCBmp(GX_BG_SCRSIZE_DCBMP_256x256, GX_BG_AREAOVER_XLU, GX_BG_BMPSCRBASE_0x20000);

            Bg_SetPriority(BG_LAYER_MAIN_3, 3);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);

            {
                MtxFx22 v2;

                MTX_Identity22(&v2);
                G2_SetBG3Affine(&v2, 0, 0, 0, 0);
            }
        }

        {
            BgTemplate v3 = {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0xe800,
                .charBase = GX_BG_CHARBASE_0x00000,
                .bgExtPltt = GX_BG_EXTPLTT_23,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            };

            Bg_InitFromTemplate(fieldSystem->bgConfig, BG_LAYER_MAIN_2, &v3, 0);
            Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_FIELD1);
            Bg_ClearTilemap(fieldSystem->bgConfig, BG_LAYER_MAIN_2);
        }
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void FieldMap_021DF3D4(FieldSystem *fieldSystem)
{
    Bg_FreeTilemapBuffer(fieldSystem->bgConfig, BG_LAYER_MAIN_2);
    FieldMap_021D1434(fieldSystem->bgConfig);
}

static u32 FieldMap_021DF3E8(u32 param0, BOOL param1)
{
    u32 v0;

    GF_ASSERT(Unk_FieldMap_02202120);
    GF_ASSERT(param1 == 0);

    v0 = Unk_FieldMap_02202120->texAllocOffset;
    Unk_FieldMap_02202120->texAllocOffset += param0;

    return v0;
}

static u32 FieldMap_021DF414(u32 param0, BOOL param1)
{
    u32 v0;

    GF_ASSERT(Unk_FieldMap_02202120);
    GF_ASSERT(param1 == 0);

    v0 = Unk_FieldMap_02202120->palAllocOffset;
    Unk_FieldMap_02202120->palAllocOffset += param0;

    return v0;
}
