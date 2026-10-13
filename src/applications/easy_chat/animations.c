#include "applications/easy_chat/animations.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/word_list_screen.h"
#include "applications/easy_chat/struct_easy_chat_scroll_animation.h"
#include "applications/easy_chat/struct_easy_chat_blend_animation.h"

#include "bg_window.h"
#include "sys_task.h"
#include "sys_task_manager.h"

static void EasyChatScrollAnimation_Task(SysTask *param0, void *param1);
static void EasyChatBlendAnimation_Task(SysTask *param0, void *param1);
static void EasyChatBlendAnimation_BrightnessTask(SysTask *param0, void *param1);

void EasyChatScrollAnimation_Start(EasyChatScrollAnimation *param0, BgConfig *param1, u32 param2, int param3, int param4, int param5)
{
    param0->bgConfig = param1;
    param0->bgLayer = param2;

    if (param3 == 0) {
        param0->currentOffset = Bg_GetXOffset(param1, param2);
        param0->direction = 0;
    } else {
        param0->currentOffset = Bg_GetYOffset(param1, param2);
        param0->direction = 3;
    }

    param0->targetOffset = (param0->currentOffset + param4) & 0x1ff;
    param0->currentOffset *= FX32_ONE;
    param0->offsetStep = (param4 * FX32_ONE) / param5;
    param0->remainingFrames = param5;
    param0->state = 0;
}

BOOL EasyChatScrollAnimation_Update(EasyChatScrollAnimation *param0)
{
    switch (param0->state) {
    case 0:
        param0->sysTask = EasyChatWordListScreen_StartVBlankTask(EasyChatScrollAnimation_Task, param0, 0);
        param0->state++;
        break;
    case 1:
        if (param0->remainingFrames == 0) {
            SysTask_Done(param0->sysTask);
            param0->state++;
            return 1;
        }
        break;
    case 2:
        return 1;
    }

    return 0;
}

static void EasyChatScrollAnimation_Task(SysTask *param0, void *param1)
{
    EasyChatScrollAnimation *v0 = param1;

    if (v0->remainingFrames) {
        v0->currentOffset += v0->offsetStep;
        Bg_SetOffset(v0->bgConfig, v0->bgLayer, v0->direction, (v0->currentOffset >> FX32_SHIFT));
        v0->remainingFrames--;
    } else {
        Bg_SetOffset(v0->bgConfig, v0->bgLayer, v0->direction, v0->targetOffset);
    }
}

void EasyChatBlendAnimation_Start(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4, int param5)
{
    param0->plane1 = param1;
    param0->plane2 = param2;
    param0->remainingFrames = param5;
    param0->currentValue = param3;
    param0->step = (fx32)(param4 - param3) / param5;
    param0->targetValue = param4;
    param0->state = 0;
    param0->sysTask = EasyChatWordListScreen_StartVBlankTask(EasyChatBlendAnimation_Task, param0, 0);
}

BOOL EasyChatBlendAnimation_Update(EasyChatBlendAnimation *param0)
{
    switch (param0->state) {
    case 0:
        if (param0->remainingFrames == 0) {
            SysTask_Done(param0->sysTask);
            param0->state++;
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static void EasyChatBlendAnimation_Task(SysTask *param0, void *param1)
{
    EasyChatBlendAnimation *v0 = param1;
    int v1, v2;

    if (v0->remainingFrames) {
        v0->currentValue += v0->step;
        v1 = v0->currentValue >> 3;
        v0->remainingFrames--;
    } else {
        v1 = v0->targetValue >> 3;
    }

    if (v1 > 16) {
        v1 = 16;
    }

    v2 = 16 - v1;

    G2_SetBlendAlpha(v0->plane1, v0->plane2, v1, v2);
}

void EasyChatBlendAnimation_StartBrightness(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4)
{
    G2_SetBlendBrightness(param1, param2);

    param0->plane1 = param1;
    param0->remainingFrames = param4;
    param0->currentValue = param2 * FX32_ONE;
    param0->targetValue = param3 * FX32_ONE;
    param0->step = (fx32)(param0->targetValue - param0->currentValue) / param4;
    param0->state = 0;
    param0->sysTask = EasyChatWordListScreen_StartVBlankTask(EasyChatBlendAnimation_BrightnessTask, param0, 0);
}

BOOL EasyChatBlendAnimation_UpdateBrightness(EasyChatBlendAnimation *param0)
{
    switch (param0->state) {
    case 0:
        if (param0->remainingFrames == 0) {
            SysTask_Done(param0->sysTask);
            param0->state++;
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static void EasyChatBlendAnimation_BrightnessTask(SysTask *param0, void *param1)
{
    EasyChatBlendAnimation *v0 = param1;
    int v1;

    if (v0->remainingFrames) {
        v0->currentValue += v0->step;
        v1 = v0->currentValue >> FX32_SHIFT;
        v0->remainingFrames--;
    } else {
        v1 = v0->targetValue >> FX32_SHIFT;
    }

    G2_SetBlendBrightness(v0->plane1, v1);
}
