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
    param0->unk_00 = param1;
    param0->unk_04 = param2;

    if (param3 == 0) {
        param0->unk_0C = Bg_GetXOffset(param1, param2);
        param0->unk_08 = 0;
    } else {
        param0->unk_0C = Bg_GetYOffset(param1, param2);
        param0->unk_08 = 3;
    }

    param0->unk_10 = (param0->unk_0C + param4) & 0x1ff;
    param0->unk_0C *= FX32_ONE;
    param0->unk_14 = (param4 * FX32_ONE) / param5;
    param0->unk_18 = param5;
    param0->unk_1A = 0;
}

BOOL EasyChatScrollAnimation_Update(EasyChatScrollAnimation *param0)
{
    switch (param0->unk_1A) {
    case 0:
        param0->unk_1C = EasyChatWordListScreen_StartVBlankTask(EasyChatScrollAnimation_Task, param0, 0);
        param0->unk_1A++;
        break;
    case 1:
        if (param0->unk_18 == 0) {
            SysTask_Done(param0->unk_1C);
            param0->unk_1A++;
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

    if (v0->unk_18) {
        v0->unk_0C += v0->unk_14;
        Bg_SetOffset(v0->unk_00, v0->unk_04, v0->unk_08, (v0->unk_0C >> FX32_SHIFT));
        v0->unk_18--;
    } else {
        Bg_SetOffset(v0->unk_00, v0->unk_04, v0->unk_08, v0->unk_10);
    }
}

void EasyChatBlendAnimation_Start(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4, int param5)
{
    param0->unk_00 = param1;
    param0->unk_04 = param2;
    param0->unk_14 = param5;
    param0->unk_08 = param3;
    param0->unk_10 = (fx32)(param4 - param3) / param5;
    param0->unk_0C = param4;
    param0->unk_18 = 0;
    param0->unk_1C = EasyChatWordListScreen_StartVBlankTask(EasyChatBlendAnimation_Task, param0, 0);
}

BOOL EasyChatBlendAnimation_Update(EasyChatBlendAnimation *param0)
{
    switch (param0->unk_18) {
    case 0:
        if (param0->unk_14 == 0) {
            SysTask_Done(param0->unk_1C);
            param0->unk_18++;
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

    if (v0->unk_14) {
        v0->unk_08 += v0->unk_10;
        v1 = v0->unk_08 >> 3;
        v0->unk_14--;
    } else {
        v1 = v0->unk_0C >> 3;
    }

    if (v1 > 16) {
        v1 = 16;
    }

    v2 = 16 - v1;

    G2_SetBlendAlpha(v0->unk_00, v0->unk_04, v1, v2);
}

void EasyChatBlendAnimation_StartBrightness(EasyChatBlendAnimation *param0, int param1, int param2, int param3, int param4)
{
    G2_SetBlendBrightness(param1, param2);

    param0->unk_00 = param1;
    param0->unk_14 = param4;
    param0->unk_08 = param2 * FX32_ONE;
    param0->unk_0C = param3 * FX32_ONE;
    param0->unk_10 = (fx32)(param0->unk_0C - param0->unk_08) / param4;
    param0->unk_18 = 0;
    param0->unk_1C = EasyChatWordListScreen_StartVBlankTask(EasyChatBlendAnimation_BrightnessTask, param0, 0);
}

BOOL EasyChatBlendAnimation_UpdateBrightness(EasyChatBlendAnimation *param0)
{
    switch (param0->unk_18) {
    case 0:
        if (param0->unk_14 == 0) {
            SysTask_Done(param0->unk_1C);
            param0->unk_18++;
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

    if (v0->unk_14) {
        v0->unk_08 += v0->unk_10;
        v1 = v0->unk_08 >> FX32_SHIFT;
        v0->unk_14--;
    } else {
        v1 = v0->unk_0C >> FX32_SHIFT;
    }

    G2_SetBlendBrightness(v0->unk_00, v1);
}
