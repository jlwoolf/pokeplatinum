#include "slot_machine/slot_machine_game.h"

#include <nitro.h>
#include <string.h>

#include "constants/species.h"

#include "slot_machine/const_slot_machine_bonus_chance.h"
#include "slot_machine/const_slot_machine_payout_per_line2.h"
#include "slot_machine/const_slot_machine_double_up_lose_chance.h"
#include "slot_machine/const_slot_machine_symbol_chance.h"
#include "slot_machine/const_slot_machine_double_up_chance.h"
#include "slot_machine/const_slot_machine_payout_per_line.h"
#include "slot_machine/const_slot_machine_bonus_duration.h"
#include "slot_machine/const_slot_machine_double_up_win_chance.h"
#include "slot_machine/const_slot_machine_payout_adjust.h"
#include "slot_machine/const_slot_machine_symbol_weights.h"
#include "slot_machine/const_slot_machine_double_up_weights.h"
#include "slot_machine/const_slot_machine_reel_strips.h"
#include "slot_machine/const_slot_machine_bonus_multiplier_table.h"
#include "slot_machine/const_slot_machine_bonus_table.h"
#include "slot_machine/const_slot_machine_payout_result_table.h"
#include "slot_machine/slot_machine.h"
#include "slot_machine/slot_machine_anim.h"
#include "slot_machine/struct_slot_machine_context.h"
#include "slot_machine/struct_slot_machine_reel_task.h"
#include "slot_machine/struct_slot_machine_payout_task.h"
#include "slot_machine/struct_slot_machine_reel_anim_task.h"
#include "slot_machine/struct_slot_machine_palette.h"
#include "slot_machine/struct_slot_machine_symbol_weights.h"
#include "slot_machine/struct_slot_machine_bonus_multiplier.h"
#include "slot_machine/struct_slot_machine_bonus_entry.h"
#include "slot_machine/struct_slot_machine_payout_result.h"

#include "bg_window.h"
#include "enums.h"
#include "heap.h"
#include "math_util.h"
#include "overworld_anim_manager.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"

typedef struct {
    u16 red : 5;
    u16 green : 5;
    u16 blue : 5;
    u16 unk_00_15 : 1;
} SlotMachineColor555;

typedef struct {
    u32 buttons[3];
    SlotMachineWinSymbolState winSymbolStates[3];
} SlotMachineButtonOrder;

typedef struct {
    SlotMachinePaletteIndex paletteIndex;
    u32 delay;
    SlotMachineContext *context;
} SlotMachinePaletteAnimArgs;

typedef struct {
    int state;
    int repeatCount;
    int unk_08;
    int done;
    SlotMachinePaletteIndex paletteIndex;
    u32 delay;
    fx32 blendAmount;
    SlotMachineContext *context;
    SlotMachinePalette *palette;
} SlotMachinePaletteAnim;

typedef struct {
    int unk_00;
    int stepIndex;
    int direction;
    fx32 timer;
    SlotMachinePaletteIndex unk_10;
    fx32 blendValues[5];
    SlotMachineContext *context;
    SlotMachinePalette *palette;
} SlotMachinePayoutAnim;

typedef struct {
    u32 mask;
    fx32 start;
    fx32 end;
    fx32 speed;
} SlotMachinePayoutAnimStep;

typedef struct {
    int state;
    fx32 progress;
    int flashType;
    SlotMachineContext *context;
} SlotMachineFadeTask;

static void SlotMachine_InitReels(SlotMachineContext *param0);
static void SlotMachine_StartReelTasks(SlotMachineContext *param0);
static void SlotMachine_StopReelTasks(SlotMachineContext *param0);
static void SlotMachine_ReelTask_Start(SlotMachineContext *param0, SlotMachineReelIndex param1);
static void SlotMachine_ReelTask_Stop(SlotMachineContext *param0, SlotMachineReelIndex param1);
static int SlotMachine_ReelTask_IsDone(SlotMachineContext *param0, SlotMachineReelIndex param1);
static void SlotMachine_ReelTask(SysTask *param0, void *param1);
static int SlotMachine_ReelTask_Spin(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_ReelTask_Spin2(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_ReelTask_Stop0(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_ReelTask_Stop1(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_ReelTask_Stop2(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_FindStopPositionA(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2);
static int SlotMachine_FindStopPositionB(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2);
static int SlotMachine_FindStopPositionC(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2);
static int SlotMachine_FindStopPositionD(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2);
static int SlotMachine_FindStopPositionE(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2);
static void SlotMachine_ChooseStopPositionA(SlotMachineReelTask *param0, SlotMachineContext *param1);
static void SlotMachine_ChooseStopPositionB(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_IsSymbolOnLine(SlotMachineContext *param0, int param1);
static int SlotMachine_IsSymbolMatch(SlotMachineContext *param0, int param1, SlotMachineSymbol param2);
static int SlotMachine_CheckLine0(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CheckLine1(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CheckLine2(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CheckLine3(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CheckLine4(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CheckLine5(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2);
static int SlotMachine_CountStoppedReels(SlotMachineContext *param0);
static int SlotMachine_CanStopReel(SlotMachineReelTask *param0, SlotMachineContext *param1);
static int SlotMachine_GetStopCandidates(SlotMachineReelTask *param0, SlotMachineContext *param1, int *param2, int *param3, int *param4);
static void SlotMachine_AdvanceReel(SlotMachineContext *param0, SlotMachineReelIndex param1, fx32 param2);
static fx32 SlotMachine_AdvanceReelToStop(SlotMachineContext *param0, SlotMachineReelIndex param1, fx32 param2);
static u32 SlotMachine_Random100(SlotMachineContext *param0);
static int SlotMachine_ConsumeRandom(u32 param0, u32 *param1);
static int SlotMachine_RollSymbol(SlotMachineContext *param0);
static int SlotMachine_GenerateSymbols(SlotMachineContext *param0);
static int SlotMachine_RollBonus(SlotMachineContext *param0);
static void SlotMachine_ChooseBonus(SlotMachineContext *param0);
static void SlotMachine_ChooseBonusMultiplier(SlotMachineContext *param0);
static int SlotMachine_RollDoubleUp(SlotMachineContext *param0);
static void SlotMachine_GenerateDoubleUpSymbols(SlotMachineContext *param0);
static int SlotMachine_RollDoubleUpLose(SlotMachineContext *param0);
static int SlotMachine_RollDoubleUpWin(SlotMachineContext *param0);
static int SlotMachine_RollPayout(SlotMachineContext *param0);
static void SlotMachine_AdjustPayout(SlotMachineContext *param0);
static SlotMachinePayoutResultEnum SlotMachine_GetPayoutResult(SlotMachineContext *param0);
static void SlotMachine_RandomButtonOrder(SlotMachineContext *param0);
static void SlotMachine_StartPayoutTask(SlotMachineContext *param0);
static void SlotMachine_StopPayoutTask(SlotMachineContext *param0);
static void SlotMachine_StartPayoutAnim(SlotMachineContext *param0);
static int SlotMachine_IsPayoutAnimDone(SlotMachineContext *param0);
static void SlotMachine_PayoutTask(SysTask *param0, void *param1);
static void SlotMachine_CreatePayoutSprites(SlotMachinePayoutTask *param0);
static void SlotMachine_StartReelAnimTask(SlotMachineContext *param0);
static void SlotMachine_StopReelAnimTask(SlotMachineContext *param0);
static void SlotMachine_SetReelAnim(SlotMachineContext *param0, u32 param1);
static int SlotMachine_IsReelAnimDone(SlotMachineContext *param0);
static void SlotMachine_CreateReelSprites(SlotMachineContext *param0);
static void SlotMachine_FinishReelSprites(SlotMachineContext *param0);
static void SlotMachine_LoadPalettes(SlotMachineContext *param0);
static void SlotMachine_Noop2(SlotMachineContext *param0);
static void SlotMachine_CopyPalette(NNSG2dPaletteData *param0, int param1, u16 *param2);
static void SlotMachine_BlendColor(u16 param0, u16 param1, u16 param2, u16 *param3);
static void SlotMachine_BlendPalette(const u16 *param0, const u16 *param1, u16 param2, u16 *param3);
static void SlotMachine_LoadPalette(SlotMachineContext *param0, u32 param1, int param2, u16 *param3);
static void SlotMachine_SetReelPalette(SlotMachineContext *param0, SlotMachinePaletteIndex param1);
static void SlotMachine_SetReelPaletteBlend(SlotMachineContext *param0, SlotMachinePaletteIndex param1);
static void SlotMachine_SetReelPaletteBlend2(SlotMachineContext *param0, SlotMachinePaletteIndex param1);
static void SlotMachine_ResetReelPalettes(SlotMachineContext *param0);
static void SlotMachine_BlendReelPalettes(SlotMachineContext *param0);
static OverworldAnimManager *SlotMachine_CreatePaletteAnim(SlotMachineContext *param0, SlotMachinePaletteIndex param1, u32 param2);
static int SlotMachine_IsPaletteAnimDone(OverworldAnimManager *param0);
static void SlotMachine_CreatePayoutAnim(SlotMachineContext *param0);
static void SlotMachine_FinishPayoutAnim(SlotMachineContext *param0);
static void SlotMachine_StartFadeInTask(SlotMachineContext *param0);
static void SlotMachine_StartFadeOutTask(SlotMachineContext *param0);
static void SlotMachine_StartFlashTask(SlotMachineContext *param0, int param1);
static int SlotMachine_GetPressedKey(u32 param0);
static SlotMachineSymbol SlotMachine_GetSymbolFromMask(u32 param0);
static SlotMachineSymbol SlotMachine_CheckLine1Symbol(SlotMachineContext *param0);
static SlotMachineSymbol SlotMachine_CheckLine2Symbol(SlotMachineContext *param0);
static SlotMachineSymbol SlotMachine_CheckLine3Symbol(SlotMachineContext *param0);
static SlotMachineSymbol SlotMachine_CheckDiagonal1Symbol(SlotMachineContext *param0);
static SlotMachineSymbol SlotMachine_CheckDiagonal2Symbol(SlotMachineContext *param0);
static SlotMachineSymbol SlotMachine_EvaluateLines(SlotMachineContext *param0, u32 param1, u32 *param2);
static SlotMachineSymbol SlotMachine_EvaluateLine2(SlotMachineContext *param0, u32 param1, u32 *param2);
static SlotMachineReelType SlotMachine_GetWinType(u32 param0);
static void SlotMachine_ClearButtonInputs(SlotMachineContext *param0);
static void SlotMachine_RecordButtonInput(SlotMachineContext *param0, u32 param1);
static int SlotMachine_CheckButtonOrder(SlotMachineContext *param0);
static int SlotMachine_CheckButtonOrder2(SlotMachineContext *param0);
static void SlotMachine_SetReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1);
static void SlotMachine_ClearReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1);
static u32 SlotMachine_GetPayoutAmount(SlotMachineContext *param0);
static void SlotMachine_ReelAnimTask(SysTask *param0, void *param1);
static void SlotMachine_FadeInTask(SysTask *param0, void *param1);
static void SlotMachine_FadeOutTask(SysTask *param0, void *param1);
static void SlotMachine_FlashTask(SysTask *param0, void *param1);

static const SlotMachineButtonOrder sSlotMachineButtonOrder[6];
static const int sSlotMachineReelHighlightPos[3][2];
static int (*const sSlotMachineStateFuncs[64])(SlotMachineContext *);
static int (*const sSlotMachineReelTaskFuncs[5])(SlotMachineReelTask *, SlotMachineContext *);
static int (*const *const sSlotMachineReelAnimFuncs[13])(SlotMachineReelAnimTask *);

void SlotMachine_InitGame(SlotMachineContext *param0)
{
    SlotMachine_InitReels(param0);
    SlotMachine_StartReelTasks(param0);
    SlotMachine_StartPayoutTask(param0);
    SlotMachine_StartReelAnimTask(param0);
    SlotMachine_LoadPalettes(param0);
}

void SlotMachine_FreeGame(SlotMachineContext *param0)
{
    SlotMachine_StopReelTasks(param0);
    SlotMachine_StopPayoutTask(param0);
    SlotMachine_StopReelAnimTask(param0);
    SlotMachine_Noop2(param0);
}

static void SlotMachine_InitReels(SlotMachineContext *param0)
{
    int v0, v1;
    fx32 v2;

    for (v0 = 0; v0 < 3; v0++) {
        v1 = (int)LCRNG_Next() % 21;
        param0->reelPosition[v0] = v1;
        param0->reelPositions[v0] = (FX32_ONE * (21 * 32)) - (FX32_ONE * ((v1) * 32));
        param0->reelPositions[v0] %= (FX32_ONE * (21 * 32));
    }
}

int SlotMachine_Update(SlotMachineContext *param0)
{
    int v0;

    do {
        v0 = sSlotMachineStateFuncs[param0->state](param0);
    } while (v0 == 1);

    if (v0 == 2) {
        return 1;
    }

    return 0;
}

static int SlotMachine_State_Init(SlotMachineContext *param0)
{
    param0->winAmount = 0;
    param0->unk_68 = 0;
    param0->reelSpeed = (FX32_ONE * 16);
    param0->symbolMask = 0;
    param0->payoutMode = 0;
    param0->state = 1;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);

    if (param0->coins == 0) {
        param0->state = 60;
        param0->returnState = 63;
    } else if (param0->coins < 3) {
        param0->state = 59;
        param0->returnState = 63;
    } else if (param0->coins >= 50000) {
        param0->state = 61;
        param0->returnState = 1;
    }

    return 1;
}

static int SlotMachine_State_InsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        SlotMachine_FinishPayoutAnim(param0);
        param0->state = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->coins -= 3;
        param0->coinsInserted += 3;
        param0->state = 2;

        Sound_PlayEffect(SEQ_SE_DP_ZUKAN02_sseq);
        SlotMachine_FinishPayoutAnim(param0);
        SlotMachine_BlendReelPalettes(param0);

        return 0;
    }

    return 0;
}

static int SlotMachine_State_InsertCoinWait(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->coins += 3;
        param0->state = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->state = 3;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartSpin(SlotMachineContext *param0)
{
    SlotMachine_GenerateSymbols(param0);

    param0->totalSpins++;
    param0->normalSpins++;
    param0->extendedSearch = 0;

    if (param0->symbolMask & ((1 << 0) | (1 << 1) | (1 << 4) | (1 << 5))) {
        param0->extendedSearch = 1;
    }

    param0->isWin = 0;

    if (param0->symbolMask != 0) {
        if (SlotMachine_RollBonus(param0) == 0) {
            param0->reelAnimTask.reelType = SlotMachineReelType_04;
        } else {
            param0->reelAnimTask.reelType = SlotMachine_GetWinType(param0->symbolMask);
            param0->bonusCount++;
        }

        param0->isWin = 1;
        SlotMachine_SetReelAnim(param0, 1);
    }

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_BlendReelPalettes(param0);

    SlotMachine_ReelTask_Start(param0, 0);
    SlotMachine_ReelTask_Start(param0, 1);
    SlotMachine_ReelTask_Start(param0, 2);
    SlotMachine_ClearButtonInputs(param0);

    param0->reelButtons[0] = 1;
    param0->reelButtons[1] = 1;
    param0->reelButtons[2] = 1;
    param0->timer = 0;
    param0->state = 4;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    return 1;
}

static int SlotMachine_State_SpinDelay(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        param0->timer = 0;
        param0->state = 5;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->reelButtons[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->reelButtons[0] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->reelButtons[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->reelButtons[1] = 2;

        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->reelButtons[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->reelButtons[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    }

    if ((param0->reelButtons[0] == 2) && (param0->reelButtons[1] == 2) && (param0->reelButtons[2] == 2)) {
        param0->state = 6;
    }

    return 0;
}

static int SlotMachine_State_WaitReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->state = 7;
    return 1;
}

static int SlotMachine_State_Evaluate(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLines(param0, param0->symbolMask, &param0->winLineMask);

    param0->winSymbol = v0;

    if (v0 == 6) {
        if (param0->symbolMask & ((1 << 1) | (1 << 3) | (1 << 5) | (1 << 7))) {
            param0->state = 16;
            return 1;
        }

        if (param0->symbolMask != 0) {
            param0->state = 10;
            return 1;
        }

        param0->state = 8;
        return 1;
    }

    if (param0->symbolMask & ((1 << 1) | (1 << 3) | (1 << 5) | (1 << 7))) {
        if (param0->symbolMask & (1 << 1)) {
            param0->state = 21;
        } else {
            param0->state = 19;
        }

        return 1;
    }

    if (v0 == 2) {
        param0->state = 14;
        return 1;
    }

    param0->state = 12;
    return 1;
}

static int SlotMachine_State_NoWin(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);

    param0->timer = 0;
    param0->state = 9;

    return 1;
}

static int SlotMachine_State_NoWinWait(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        param0->timer = 0;
        param0->state = 0;
    }

    return 0;
}

static int SlotMachine_State_Payout(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 2);
    param0->state = 11;

    return 0;
}

static int SlotMachine_State_WaitPayout(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 1) {
        SlotMachine_SetReelAnim(param0, 0);
        param0->state = 0;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_Win(SlotMachineContext *param0)
{
    param0->winAmount = SlotMachine_GetPayoutAmount(param0);
    param0->totalPayout += param0->winAmount;
    param0->timer = 0;
    param0->state = 13;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitWin(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer == (FX32_ONE * 30)) {
        SlotMachine_SetReelAnim(param0, 2);
    } else if (param0->timer > (FX32_ONE * 30)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            SlotMachine_SetReelAnim(param0, 0);
            param0->timer = 0;
            param0->state = 0;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_BigWin(SlotMachineContext *param0)
{
    param0->winAmount = 0;
    param0->timer = 0;
    param0->state = 15;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitBigWin(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer == (FX32_ONE * 15)) {
        SlotMachine_SetReelAnim(param0, 2);
    } else if (param0->timer > (FX32_ONE * 15)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            SlotMachine_SetReelAnim(param0, 0);
            param0->timer = 0;
            param0->state = 3;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_Bonus(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_ChooseBonus(param0);
    SlotMachine_ChooseBonusMultiplier(param0);
    SlotMachine_SetReelAnim(param0, 11);

    param0->timer = 0;
    param0->state = 17;

    return 0;
}

static int SlotMachine_State_BonusWait(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        SlotMachine_SetReelAnim(param0, 3);
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
        param0->state = 18;
    }

    return 0;
}

static int SlotMachine_State_WaitBonus(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 1) {
        param0->state = 23;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_BonusPayout(SlotMachineContext *param0)
{
    param0->winAmount = SlotMachine_GetPayoutAmount(param0);
    param0->timer = 0;
    param0->state = 20;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_ChooseBonus(param0);
    SlotMachine_ChooseBonusMultiplier(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitBonusPayout(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer == (FX32_ONE * 30)) {
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
        SlotMachine_SetReelAnim(param0, 3);
    } else if (param0->timer >= (FX32_ONE * 30)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            param0->timer = 0;
            param0->state = 23;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_BonusEnd(SlotMachineContext *param0)
{
    param0->timer = 0;
    param0->state = 22;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);
    SlotMachine_ChooseBonus(param0);
    SlotMachine_ChooseBonusMultiplier(param0);

    return 0;
}

static int SlotMachine_State_WaitBonusEnd(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer == (FX32_ONE * 8)) {
        SlotMachine_SetReelAnim(param0, 3);
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
    } else if (param0->timer >= (FX32_ONE * 8)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            param0->timer = 0;
            param0->state = 24;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_CheckBonus(SlotMachineContext *param0)
{
    GF_ASSERT(param0->bonusType < SlotMachineBonusType_06);
    param0->state = 25;
    return 1;
}

static int SlotMachine_State_CheckBonus2(SlotMachineContext *param0)
{
    GF_ASSERT(param0->bonusType < SlotMachineBonusType_06);
    param0->state = 28;

    return 1;
}

static int SlotMachine_State_InitDoubleUp(SlotMachineContext *param0)
{
    param0->winAmount = 0;
    param0->unk_68 = 0;
    param0->state = 26;
    param0->symbolMask = 0;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 7);

    if (param0->coins == 0) {
        param0->state = 60;
        param0->returnState = 63;
    } else if (param0->coins < 3) {
        param0->state = 59;
        param0->returnState = 63;
    } else if (param0->coins >= 50000) {
        param0->state = 61;
        param0->returnState = 26;
    }

    return 1;
}

static int SlotMachine_State_DoubleUpInsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->state = 63;
        SlotMachine_FinishPayoutAnim(param0);
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->coins -= 3;
        param0->coinsInserted += 3;
        param0->state = 27;

        Sound_PlayEffect(SEQ_SE_DP_ZUKAN02_sseq);
        SlotMachine_FinishPayoutAnim(param0);
        SlotMachine_BlendReelPalettes(param0);

        return 0;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpInsertCoinWait(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->coins += 3;
        param0->state = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->state = 28;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartDoubleUp(SlotMachineContext *param0)
{
    SlotMachine_GenerateDoubleUpSymbols(param0);

    param0->totalSpins++;
    param0->doubleUpSpins++;
    param0->extendedSearch = 0;

    if (param0->symbolMask & ((1 << 0) | (1 << 1) | (1 << 4) | (1 << 5))) {
        param0->extendedSearch = 1;
    }

    param0->isWin = 0;

    if (param0->symbolMask != 0) {
        param0->isWin = 1;
    }

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_BlendReelPalettes(param0);

    SlotMachine_ReelTask_Start(param0, 0);
    SlotMachine_ReelTask_Start(param0, 1);
    SlotMachine_ReelTask_Start(param0, 2);
    SlotMachine_ClearButtonInputs(param0);

    SlotMachine_SetReelAnim(param0, 9);

    param0->reelButtons[0] = 1;
    param0->reelButtons[1] = 1;
    param0->reelButtons[2] = 1;
    param0->timer = 0;
    param0->state = 29;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    return 1;
}

static int SlotMachine_State_DoubleUpSpinDelay(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        param0->timer = 0;
        param0->state = 30;

        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpStopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->reelButtons[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->reelButtons[0] = 2;

        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->reelButtons[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->reelButtons[1] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->reelButtons[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->reelButtons[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->extendedSearch = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    }

    if ((param0->reelButtons[0] == 2) && (param0->reelButtons[1] == 2) && (param0->reelButtons[2] == 2)) {
        param0->state = 31;
    }

    return 0;
}

static int SlotMachine_State_WaitDoubleUpReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->state = 32;
    return 1;
}

static int SlotMachine_State_EvaluateDoubleUp(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLines(param0, param0->symbolMask, &param0->winLineMask);

    param0->winSymbol = v0;

    if (v0 == 6) {
        param0->state = 33;
        return 1;
    }

    if (param0->symbolMask & ((1 << 8) | (1 << 9))) {
        param0->state = 39;
        return 1;
    }

    if (v0 == 2) {
        param0->state = 37;
        return 1;
    }

    param0->state = 35;
    return 1;
}

static int SlotMachine_State_DoubleUpWin(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 7);

    param0->timer = 0;
    param0->state = 34;

    return 1;
}

static int SlotMachine_State_WaitDoubleUpWin(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        param0->timer = 0;
        param0->state = 25;

        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpLose(SlotMachineContext *param0)
{
    param0->winAmount = SlotMachine_GetPayoutAmount(param0);
    param0->totalPayout += param0->winAmount;
    param0->timer = 0;
    param0->state = 36;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    return 0;
}

static int SlotMachine_State_WaitDoubleUpLose(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
        SlotMachine_SetReelAnim(param0, 7);
        param0->state = 25;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpRetry(SlotMachineContext *param0)
{
    param0->winAmount = 0;
    param0->timer = 0;
    param0->state = 38;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    return 0;
}

static int SlotMachine_State_WaitDoubleUpRetry(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer > (FX32_ONE * 15)) {
        if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
            SlotMachine_SetReelAnim(param0, 7);
            SlotMachine_ResetReelPalettes(param0);

            param0->timer = 0;
            param0->state = 28;

            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_Jackpot(SlotMachineContext *param0)
{
    param0->winAmount = SlotMachine_GetPayoutAmount(param0);
    param0->totalPayout += param0->winAmount;
    param0->timer = 0;
    param0->state = 40;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);
    SlotMachine_StartFadeInTask(param0);
    SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_02);

    param0->jackpotAnim = SlotMachine_CreateJackpot(param0);

    return 0;
}

static int SlotMachine_State_WaitJackpot(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
        OverworldAnimManager_Finish(param0->jackpotAnim);
        SlotMachine_SetReelAnim(param0, 7);
        param0->state = 41;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_InitPayout(SlotMachineContext *param0)
{
    SlotMachine_CreateReelSprites(param0);

    param0->bonusRoundStreak = 0;
    param0->payoutCoins = 0;
    param0->payoutMode = 1;
    param0->state = 42;

    return 1;
}

static int SlotMachine_State_CountPayout(SlotMachineContext *param0)
{
    param0->bonusRounds++;
    param0->bonusRoundStreak++;

    if (param0->bonusRoundStreak > 999) {
        param0->bonusRoundStreak = 999;
    }

    SlotMachine_CreateNumber2(param0, param0->bonusRoundStreak);

    param0->payoutLines = 15 + 1;
    param0->payoutMode = 1;
    param0->doubleUpWin = 0;
    param0->doubleUpLose = 0;
    param0->payoutFailed = 0;

    if (SlotMachine_RollPayout(param0) == 0) {
        param0->payoutFailed = 1;
    }

    param0->state = 43;
    return 1;
}

static int SlotMachine_State_NextPayout(SlotMachineContext *param0)
{
    param0->payoutLines--;
    GF_ASSERT((int)param0->payoutLines >= 1);

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 7);

    param0->state = 44;

    if (param0->coins == 0) {
        param0->state = 60;
        param0->returnState = 63;
    } else if (param0->coins < 1) {
        param0->state = 60;
        param0->returnState = 63;
    } else if (param0->coins >= 50000) {
        param0->state = 61;
        param0->returnState = 44;
    }

    return 1;
}

static int SlotMachine_State_PayoutInsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->state = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->coins -= 1;
        param0->payoutCoins -= 1;
        param0->coinsInserted += 1;

        if ((int)param0->payoutCoins < 0) {
            param0->payoutCoins = 0;
        }

        param0->state = 45;

        Sound_PlayEffect(SEQ_SE_DP_ZUKAN02_sseq);
        SlotMachine_FinishPayoutAnim(param0);
        SlotMachine_SetReelPaletteBlend2(param0, SlotMachinePaletteIndex_00);

        return 0;
    }

    return 0;
}

static int SlotMachine_State_PayoutInsertCoinWait(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->coins += 1;
        param0->state = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->state = 46;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartPayout(SlotMachineContext *param0)
{
    param0->totalSpins++;
    param0->payoutSpins++;
    param0->symbolMask = (1 << 0);
    param0->isWin = 1;
    param0->extendedSearch = 1;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_SetReelPaletteBlend2(param0, SlotMachinePaletteIndex_00);

    SlotMachine_ReelTask_Start(param0, 0);
    SlotMachine_ReelTask_Start(param0, 1);
    SlotMachine_ReelTask_Start(param0, 2);
    SlotMachine_ClearButtonInputs(param0);
    SlotMachine_RandomButtonOrder(param0);

    param0->reelButtons[0] = 1;
    param0->reelButtons[1] = 1;
    param0->reelButtons[2] = 1;
    param0->timer = 0;
    param0->state = 47;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    if ((param0->doubleUpWin == 0) && (param0->doubleUpLose == 0)) {
        if (SlotMachine_RollDoubleUpLose(param0) == 1) {
            param0->doubleUpLose = 1;
            param0->doubleUpLoseRolls++;
        }

        if (param0->doubleUpLose == 1) {
            SlotMachine_StartFlashTask(param0, 1);
        }
    }

    if ((param0->doubleUpWin == 0) && (param0->doubleUpLose == 0)) {
        if (SlotMachine_RollDoubleUpWin(param0) == 1) {
            param0->doubleUpWin = 1;
            param0->doubleUpWinRolls++;
        }

        if (param0->doubleUpWin == 1) {
            SlotMachine_StartFlashTask(param0, 0);
        }
    }

    return 1;
}

static int SlotMachine_State_PayoutSpinDelay(SlotMachineContext *param0)
{
    param0->timer += FX32_ONE;

    if (param0->timer >= (FX32_ONE * 8)) {
        param0->timer = 0;
        param0->state = 48;
        SlotMachine_SetReelAnim(param0, 6);
        return 1;
    }

    return 0;
}

static int SlotMachine_State_PayoutStopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->reelButtons[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->reelButtons[0] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->extendedSearch = 0;
            param0->isWin = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    } else if ((param0->reelButtons[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->reelButtons[1] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->extendedSearch = 0;
            param0->isWin = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    } else if ((param0->reelButtons[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->reelButtons[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->extendedSearch = 0;
            param0->isWin = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    }

    if ((param0->reelButtons[0] == 2) && (param0->reelButtons[1] == 2) && (param0->reelButtons[2] == 2)) {
        param0->state = 49;
    }

    return 0;
}

static int SlotMachine_State_WaitPayoutReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->state = 50;
    return 1;
}

static int SlotMachine_State_EvaluatePayout(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLine2(param0, param0->symbolMask, &param0->winLineMask);

    param0->winSymbol = v0;

    if (v0 == 6) {
        if (param0->doubleUpLose == 1) {
            param0->doubleUpLose = 3;
        }

        param0->state = 51;
        return 1;
    }

    if (param0->doubleUpLose == 1) {
        param0->doubleUpLose = 2;
    }

    param0->state = 52;

    return 1;
}

static int SlotMachine_State_PayoutResult(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 7);

    if ((int)param0->payoutLines <= 1) {
        param0->state = 54;
    } else {
        param0->state = 43;
    }

    return 0;
}

static int SlotMachine_State_PayoutWin(SlotMachineContext *param0)
{
    param0->winAmount = sSlotMachinePayoutPerLine2[param0->winSymbol];
    param0->totalPayout += param0->winAmount;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    param0->timer = 0;
    param0->state = 53;

    return 0;
}

static int SlotMachine_State_WaitPayoutWin(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 0) {
        return 0;
    }

    SlotMachine_SetReelAnim(param0, 7);

    if ((int)param0->payoutLines <= 1) {
        param0->state = 54;
    } else {
        param0->state = 43;
    }

    return 1;
}

static int SlotMachine_State_EndPayout(SlotMachineContext *param0)
{
    param0->payoutLines--;
    GF_ASSERT(param0->payoutLines == 0);

    if ((param0->payoutFailed == 1) && (param0->doubleUpWin == 0)) {
        SlotMachine_SetReelAnim(param0, 8);
        param0->state = 58;
        return 0;
    }

    param0->state = 55;
    return 1;
}

static int SlotMachine_State_CheckPayout(SlotMachineContext *param0)
{
    SlotMachinePayoutResultEnum v0;

    SlotMachine_AdjustPayout(param0);
    v0 = SlotMachine_GetPayoutResult(param0);

    if (param0->doubleUpWin == 1) {
        v0 = SlotMachinePayoutResultEnum_02;
    }

    if (v0 == SlotMachinePayoutResultEnum_02) {
        SlotMachine_SetReelAnim(param0, 5);
        param0->state = 56;
        return 0;
    }

    if (v0 == SlotMachinePayoutResultEnum_01) {
        SlotMachine_SetReelAnim(param0, 12);
        param0->state = 57;
        return 0;
    }

    Sound_PlayPokemonCry(SPECIES_CLEFAIRY, 0);
    param0->state = 42;
    return 0;
}

static int SlotMachine_State_WaitPayoutAnim(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    param0->state = 42;
    return 1;
}

static int SlotMachine_State_WaitPayoutAnim2(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    param0->state = 42;
    return 1;
}

static int SlotMachine_State_Finish(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    if (param0->bonusRoundStreak > param0->consecutiveBonusRoundWins) {
        param0->consecutiveBonusRoundWins = param0->bonusRoundStreak;
    }

    SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_00);
    SlotMachine_StartFadeOutTask(param0);
    param0->state = 0;

    return 1;
}

static int SlotMachine_State_ShowMessage0(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 0);
    param0->state = 62;
    return 0;
}

static int SlotMachine_State_ShowMessage2(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 2);
    param0->state = 62;
    return 0;
}

static int SlotMachine_State_ShowMessage1(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 1);
    param0->state = 62;
    return 0;
}

static int SlotMachine_State_WaitMessage(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_A | PAD_BUTTON_B)) {
        SlotMachine_HideMessage(param0);
        param0->state = param0->returnState;
    }

    return 0;
}

static int SlotMachine_State_Exit(SlotMachineContext *param0)
{
    SlotMachine_FinishPayoutAnim(param0);
    return 2;
}

static int (*const sSlotMachineStateFuncs[64])(SlotMachineContext *) = {
    SlotMachine_State_Init,
    SlotMachine_State_InsertCoin,
    SlotMachine_State_InsertCoinWait,
    SlotMachine_State_StartSpin,
    SlotMachine_State_SpinDelay,
    SlotMachine_State_StopReels,
    SlotMachine_State_WaitReelsStop,
    SlotMachine_State_Evaluate,
    SlotMachine_State_NoWin,
    SlotMachine_State_NoWinWait,
    SlotMachine_State_Payout,
    SlotMachine_State_WaitPayout,
    SlotMachine_State_Win,
    SlotMachine_State_WaitWin,
    SlotMachine_State_BigWin,
    SlotMachine_State_WaitBigWin,
    SlotMachine_State_Bonus,
    SlotMachine_State_BonusWait,
    SlotMachine_State_WaitBonus,
    SlotMachine_State_BonusPayout,
    SlotMachine_State_WaitBonusPayout,
    SlotMachine_State_BonusEnd,
    SlotMachine_State_WaitBonusEnd,
    SlotMachine_State_CheckBonus,
    SlotMachine_State_CheckBonus2,
    SlotMachine_State_InitDoubleUp,
    SlotMachine_State_DoubleUpInsertCoin,
    SlotMachine_State_DoubleUpInsertCoinWait,
    SlotMachine_State_StartDoubleUp,
    SlotMachine_State_DoubleUpSpinDelay,
    SlotMachine_State_DoubleUpStopReels,
    SlotMachine_State_WaitDoubleUpReelsStop,
    SlotMachine_State_EvaluateDoubleUp,
    SlotMachine_State_DoubleUpWin,
    SlotMachine_State_WaitDoubleUpWin,
    SlotMachine_State_DoubleUpLose,
    SlotMachine_State_WaitDoubleUpLose,
    SlotMachine_State_DoubleUpRetry,
    SlotMachine_State_WaitDoubleUpRetry,
    SlotMachine_State_Jackpot,
    SlotMachine_State_WaitJackpot,
    SlotMachine_State_InitPayout,
    SlotMachine_State_CountPayout,
    SlotMachine_State_NextPayout,
    SlotMachine_State_PayoutInsertCoin,
    SlotMachine_State_PayoutInsertCoinWait,
    SlotMachine_State_StartPayout,
    SlotMachine_State_PayoutSpinDelay,
    SlotMachine_State_PayoutStopReels,
    SlotMachine_State_WaitPayoutReelsStop,
    SlotMachine_State_EvaluatePayout,
    SlotMachine_State_PayoutResult,
    SlotMachine_State_PayoutWin,
    SlotMachine_State_WaitPayoutWin,
    SlotMachine_State_EndPayout,
    SlotMachine_State_CheckPayout,
    SlotMachine_State_WaitPayoutAnim,
    SlotMachine_State_WaitPayoutAnim2,
    SlotMachine_State_Finish,
    SlotMachine_State_ShowMessage0,
    SlotMachine_State_ShowMessage2,
    SlotMachine_State_ShowMessage1,
    SlotMachine_State_WaitMessage,
    SlotMachine_State_Exit
};

static void SlotMachine_StartReelTasks(SlotMachineContext *param0)
{
    u32 v0 = 0;
    SlotMachineReelTask *v1 = param0->reelTasks;

    do {
        v1->state = 0;
        v1->reelIndex = v0;
        v1->context = param0;
        v1->task = SysTask_Start(SlotMachine_ReelTask, &param0->reelTasks[v0], 129 + v0);
        v1++;
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_StopReelTasks(SlotMachineContext *param0)
{
    u32 v0 = 0;

    do {
        SysTask_Done(param0->reelTasks[v0].task);
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_ReelTask_Start(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    param0->reelTasks[param1].state = 1;
    param0->reelTasks[param1].done = 1;
}

static void SlotMachine_ReelTask_Stop(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    param0->reelTasks[param1].state = 2;
}

static int SlotMachine_ReelTask_IsDone(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    return param0->reelTasks[param1].done;
}

static void SlotMachine_ReelTask(SysTask *param0, void *param1)
{
    SlotMachineReelTask *v0 = param1;
    SlotMachineContext *v1 = v0->context;

    while (sSlotMachineReelTaskFuncs[v0->state](v0, v1) == 1) {
        (void)0;
    }
}

static int SlotMachine_ReelTask_Noop(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    return 0;
}

static int SlotMachine_ReelTask_Update(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachine_AdvanceReel(param1, param0->reelIndex, param1->reelSpeed);
    return 0;
}

static int SlotMachine_ReelTask_Advance(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    param0->state++;
    param0->targetPosition = 0;
    param0->spinOffset = 0;

    if (param1->isWin == 1) {
        if (param1->payoutMode == 0) {
            if (SlotMachine_ReelTask_Spin(param0, param1) == 0) {
                SlotMachine_ChooseStopPositionA(param0, param1);
                param1->isWin = 0;
            }
        } else {
            if (SlotMachine_ReelTask_Spin2(param0, param1) == 0) {
                SlotMachine_ChooseStopPositionB(param0, param1);
                param1->isWin = 0;
            }
        }
    } else {
        if (param1->payoutMode == 0) {
            SlotMachine_ChooseStopPositionA(param0, param1);
        } else {
            SlotMachine_ChooseStopPositionB(param0, param1);
        }
    }

    return 1;
}

static int SlotMachine_ReelTask_Decelerate(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    fx32 v0, v1;
    int v2 = param0->reelIndex;
    int v3 = 0;

    v0 = param1->reelPositions[v2] % (FX32_ONE * 32);

    if (v0) {
        v3 = 1;
        v1 = param1->reelSpeed;

        if (v0 < v1) {
            v1 = v0;
        }

        v0 = SlotMachine_AdvanceReelToStop(param1, v2, v1);
    } else if (param0->spinOffset) {
        v3 = 1;
        param0->spinOffset--;
        SlotMachine_AdvanceReel(param1, v2, param1->reelSpeed);
        v0 = param1->reelPositions[v2] % (FX32_ONE * 32);
    }

    if ((v0 == 0) && (param0->spinOffset == 0)) {
        fx32 v4[5] = { (FX32_ONE * 4), (FX32_ONE * 8), (FX32_ONE * 8), (FX32_ONE * 8), (FX32_ONE * 16) };
        s32 v5 = param0->spinOffset;

        if (v5 > 4) {
            v5 = 4;
        }

        param0->bounceSpeed = v4[v5];
        param0->bounceCount = 0;
        param0->state++;

        if (v3 == 0) {
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_ReelTask_Bounce(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    int v0 = param0->reelIndex;

    param1->reelBounce[v0] = param0->bounceSpeed;
    param0->bounceSpeed = -param0->bounceSpeed;
    param0->bounceCount++;

    if ((param0->bounceCount & 0x1) == 0) {
        param0->bounceSpeed >>= 2;
    }

    if (param0->bounceSpeed == 0) {
        param0->state = 0;
        param0->done = 0;
        param1->reelBounce[v0] = 0;
    }

    return 0;
}

static int (*const sSlotMachineReelTaskFuncs[5])(SlotMachineReelTask *, SlotMachineContext *) = {
    SlotMachine_ReelTask_Noop,
    SlotMachine_ReelTask_Update,
    SlotMachine_ReelTask_Advance,
    SlotMachine_ReelTask_Decelerate,
    SlotMachine_ReelTask_Bounce,
};

static int SlotMachine_ReelTask_Spin(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    if (param1->symbolMask == 0) {
        return 0;
    }

    switch (param0->reelIndex) {
    case 0:
        return SlotMachine_ReelTask_Stop0(param0, param1);
    case 1:
        return SlotMachine_ReelTask_Stop1(param0, param1);
    case 2:
        return SlotMachine_ReelTask_Stop2(param0, param1);
    }

    GF_ASSERT(FALSE);
    return 0;
}

static int SlotMachine_ReelTask_Spin2(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    if (param1->symbolMask == 0) {
        return 0;
    }

    {
        SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->symbolMask);
        return SlotMachine_FindStopPositionE(param0, param1, v0);
    }
}

static int SlotMachine_ReelTask_Stop0(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->symbolMask);

    if (v0 == 6) {
        return 0;
    }

    if (SlotMachine_CanStopReel(param0, param1) == 1) {
        return SlotMachine_FindStopPositionA(param0, param1, v0);
    }

    return SlotMachine_FindStopPositionB(param0, param1, v0);
}

static int SlotMachine_ReelTask_Stop1(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->symbolMask);

    if (v0 == 6) {
        return 0;
    }

    if (SlotMachine_CanStopReel(param0, param1) == 1) {
        return SlotMachine_FindStopPositionC(param0, param1, v0);
    }

    return SlotMachine_FindStopPositionD(param0, param1, v0);
}

static int SlotMachine_ReelTask_Stop2(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->symbolMask);

    if (v0 == 6) {
        return 0;
    }

    if (SlotMachine_CanStopReel(param0, param1) == 1) {
        return SlotMachine_FindStopPositionC(param0, param1, v0);
    }

    return SlotMachine_FindStopPositionD(param0, param1, v0);
}

static int SlotMachine_FindStopPositionA(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2, v3, v4;
    int v5 = param0->reelIndex;

    for (v0 = 1; v0 <= 3; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v5, v0) == param2) {
            for (v1 = 0; (v0 + v1) <= 3; v1++) {
                if (SlotMachine_IsSymbolMatch(param1, v1, param2) == 1) {
                    param0->targetPosition = v0 + v1;
                    param0->spinOffset = v1;
                    return 1;
                }
            }
        }
    }

    v2 = 4;

    if (param1->extendedSearch == 1) {
        v2 = 21;
    }

    v4 = (int)param1->reelPosition[0];

    for (v0 = 1; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v5, 1 - v0) == param2) {
            for (v1 = 0; v1 < 3; v1++) {
                if (SlotMachine_IsSymbolMatch(param1, v0 + v1, param2) == 1) {
                    if (v1 == 0) {
                        v3 = v4 % 4;

                        if ((v3 == 0) && (SlotMachine_IsSymbolMatch(param1, v0 + 2, param2) == 1)) {
                            param0->targetPosition = 3;
                            param0->spinOffset = v0 + 2;
                            return 1;
                        }
                    } else if (v1 == 1) {
                        v3 = v4 % 6;

                        if ((v3 < 2) && (SlotMachine_IsSymbolMatch(param1, v0 + 2, param2) == 1)) {
                            param0->targetPosition = 3;
                            param0->spinOffset = v0 + 2;
                            return 1;
                        }
                    }

                    param0->targetPosition = 1 + v1;
                    param0->spinOffset = v0 + v1;
                    return 1;
                }
            }
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionB(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2, v3, v4, v5;
    int v6 = param0->reelIndex;

    if (SlotMachine_GetStopCandidates(param0, param1, &v2, &v3, &v4) == 0) {
        return 0;
    }

    if (SlotMachine_IsSymbolMatch(param1, 0, param2) == 1) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2) == param2) {
            param0->targetPosition = v2;
            param0->spinOffset = 0;
            return 1;
        }

        if ((v3 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v6, v3) == param2)) {
            param0->targetPosition = v3;
            param0->spinOffset = 0;
            return 1;
        }

        if ((v4 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v6, v4) == param2)) {
            param0->targetPosition = v4;
            param0->spinOffset = 0;
            return 1;
        }
    }

    v5 = 4;

    if (param1->extendedSearch == 1) {
        v5 = 21;
    }

    if (v3 == 0) {
        for (v0 = 1; v0 <= v5; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v2;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        }

        return 0;
    }

    if (v4 == 0) {
        for (v0 = 1; v0 <= v5; v0++) {
            if (v0 & 0x1) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->targetPosition = v2;
                        param0->spinOffset = v0;
                        return 1;
                    }
                }

                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->targetPosition = v3;
                        param0->spinOffset = v0;
                        return 1;
                    }
                }
            } else {
                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->targetPosition = v3;
                        param0->spinOffset = v0;
                        return 1;
                    }
                }

                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->targetPosition = v2;
                        param0->spinOffset = v0;
                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    for (v0 = 1; v0 <= v5; v0++) {
        int v7 = v0 & 0x3;

        if (v7 == 0) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v2;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v3;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v4 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v4;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        } else if (v7 == 1) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v3;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v2;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        } else {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v4 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v4;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v2;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->targetPosition = v3;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionC(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2;
    int v3 = param0->reelIndex;

    for (v0 = 1; v0 <= 3; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, v0) == param2) {
            param0->targetPosition = v0;
            param0->spinOffset = 0;
            return 1;
        }
    }

    v2 = 4;

    if (param1->extendedSearch == 1) {
        v2 = 21;
    }

    for (v0 = 1; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, 1 - v0) == param2) {
            v1 = v0 % 4;

            if (v1 == 1) {
                param0->targetPosition = 3;
                param0->spinOffset = v0 + 2;
                return 1;
            }

            if ((v1 == 2) || (v1 == 3)) {
                param0->targetPosition = 2;
                param0->spinOffset = v0 + 1;
                return 1;
            }

            param0->targetPosition = 1;
            param0->spinOffset = v0;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionD(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2, v3, v4, v5, v6 = 4, v7 = param0->reelIndex;

    if (SlotMachine_GetStopCandidates(param0, param1, &v3, &v4, &v5) == 0) {
        return 0;
    }

    if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3) == param2) {
        param0->targetPosition = v3;
        param0->spinOffset = 0;
        return 1;
    }

    if ((v4 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v7, v4) == param2)) {
        param0->targetPosition = v4;
        param0->spinOffset = 0;
        return 1;
    }

    if ((v5 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v7, v5) == param2)) {
        param0->targetPosition = v5;
        param0->spinOffset = 0;
        return 1;
    }

    v6 = 4;

    if (param1->extendedSearch == 1) {
        v6 = 21;
    }

    if (v4 == 0) {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->targetPosition = v3;
                param0->spinOffset = v0;
                return 1;
            }
        }

        return 0;
    }

    v2 = (int)param1->reelPosition[v7];

    if (v5 == 0) {
        if (v2 & 0x1) {
            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                    param0->targetPosition = v3;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                    param0->targetPosition = v4;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        } else {
            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                    param0->targetPosition = v4;
                    param0->spinOffset = v0;
                    return 1;
                }
            }

            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                    param0->targetPosition = v3;
                    param0->spinOffset = v0;
                    return 1;
                }
            }
        }

        return 0;
    }

    v2 %= 3;

    if (v2 == 0) {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->targetPosition = v3;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->targetPosition = v4;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->targetPosition = v5;
                param0->spinOffset = v0;
                return 1;
            }
        }
    } else if (v2 == 1) {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->targetPosition = v4;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->targetPosition = v5;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->targetPosition = v3;
                param0->spinOffset = v0;
                return 1;
            }
        }
    } else {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->targetPosition = v5;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->targetPosition = v3;
                param0->spinOffset = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->targetPosition = v4;
                param0->spinOffset = v0;
                return 1;
            }
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionE(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2;
    int v3 = param0->reelIndex;

    v2 = 4;

    if (param1->extendedSearch == 1) {
        v2 = 21;
    }

    for (v0 = 0; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, 2 - v0) == param2) {
            param0->targetPosition = 2;
            param0->spinOffset = v0;
            return 1;
        }
    }

    return 0;
}

static void SlotMachine_ChooseStopPositionA(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    int v0, v1;

    v1 = SlotMachine_CountStoppedReels(param1);

    if ((param0->reelIndex != 0) && (v1 < 2)) {
        return;
    }

    if ((param0->reelIndex == 0) && (v1 < 2)) {
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_IsSymbolOnLine(param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    }

    switch (param0->reelIndex) {
    case 0:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine0(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 1:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine1(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);

        break;
    case 2:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine2(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        break;
    }

    GF_ASSERT(FALSE);
}

static void SlotMachine_ChooseStopPositionB(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    int v0, v1;

    v1 = SlotMachine_CountStoppedReels(param1);

    if ((param0->reelIndex != 0) && (v1 < 2)) {
        return;
    }

    if ((param0->reelIndex == 0) && (v1 < 2)) {
        for (v0 = 0; v0 < 21; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v0) != 3) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
    }

    switch (param0->reelIndex) {
    case 0:
        for (v0 = 0; v0 < 21; v0++) {
            if (SlotMachine_CheckLine3(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 1:
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine4(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 2:
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine5(param0, param1, v0) == 0) {
                param0->spinOffset = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
    }

    GF_ASSERT(FALSE);
}

static int SlotMachine_CountStoppedReels(SlotMachineContext *param0)
{
    int v0 = 0, v1 = 0;

    do {
        if (param0->reelButtons[v0] != 1) {
            v1++;
        }

        v0++;
    } while (v0 < 3);

    return v1;
}

static int SlotMachine_CanStopReel(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    switch (param0->reelIndex) {
    case 0:
        if ((param1->reelButtons[1] != 1) || (param1->reelButtons[2] != 1)) {
            return 0;
        }

        break;
    case 1:
        if ((param1->reelButtons[0] != 1) || (param1->reelButtons[2] != 1)) {
            return 0;
        }

        break;
    case 2:
        if ((param1->reelButtons[0] != 1) || (param1->reelButtons[1] != 1)) {
            return 0;
        }

        break;
    }

    return 1;
}

static int SlotMachine_GetStopCandidates(SlotMachineReelTask *param0, SlotMachineContext *param1, int *param2, int *param3, int *param4)
{
    SlotMachineReelButtonState v0 = param1->reelButtons[0];
    SlotMachineReelButtonState v1 = param1->reelButtons[1];
    SlotMachineReelButtonState v2 = param1->reelButtons[2];
    SlotMachineReelTask *v3 = &param1->reelTasks[0];
    SlotMachineReelTask *v4 = &param1->reelTasks[1];
    SlotMachineReelTask *v5 = &param1->reelTasks[2];
    int v6 = v3->targetPosition;
    int v7 = v4->targetPosition;
    int v8 = v5->targetPosition;

    *param2 = 0;
    *param3 = 0;
    *param4 = 0;

    switch (param0->reelIndex) {
    case 0:
        if ((v1 != 1) && (v2 != 1)) {
            if (v7 == v8) {
                *param2 = v7;
                return 1;
            }

            if (v8 == 1) {
                *param2 = 3;
                return 1;
            }

            *param2 = 1;
            return 1;
        }

        if (v1 != 1) {
            if (v7 == 2) {
                *param2 = 1;
                *param3 = 2;
                *param4 = 3;
                return 1;
            }

            *param2 = v7;
            return 1;
        }

        if (v8 == 2) {
            *param2 = v8;
            return 1;
        }

        *param2 = 1;
        *param3 = 3;
        return 1;
    case 1:
        if ((v0 != 1) && (v2 != 1)) {
            if (v6 == v8) {
                *param2 = v6;
                return 1;
            }

            *param2 = 2;
            return 1;
        }

        if (v0 != 1) {
            if (v6 == 2) {
                *param2 = 2;
                return 1;
            }

            if (v6 == 1) {
                *param2 = 1;
                *param3 = 2;
                return 1;
            }

            *param2 = 2;
            *param3 = 3;
            return 1;
        }

        if (v8 == 2) {
            *param2 = 2;
            return 1;
        }

        if (v8 == 1) {
            *param2 = 1;
            *param3 = 2;
            return 1;
        }

        *param2 = 2;
        *param3 = 3;
        return 1;
    case 2:
        if ((v0 != 1) && (v1 != 1)) {
            if (v6 == v7) {
                *param2 = v6;
                return 1;
            }

            if (v6 == 1) {
                *param2 = 3;
            } else {
                *param2 = 1;
            }

            return 1;
        }

        if (v0 != 1) {
            if (v6 == 2) {
                *param2 = 2;
                return 1;
            }

            *param2 = 1;
            *param3 = 3;
            return 1;
        }

        if (v7 == 2) {
            *param2 = 1;
            *param3 = 2;
            *param4 = 3;
            return 1;
        }

        *param2 = v7;
        return 1;
    }

    GF_ASSERT(FALSE);
    return 0;
}

static int SlotMachine_IsSymbolOnLine(SlotMachineContext *param0, int param1)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 1 - param1);

    if (v0 == 3) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 2 - param1);

    if (v0 == 3) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 3 - param1);

    if (v0 == 3) {
        return 1;
    }

    return 0;
}

static int SlotMachine_IsSymbolMatch(SlotMachineContext *param0, int param1, SlotMachineSymbol param2)
{
    if (param2 == 3) {
        return 1;
    }

    if (SlotMachine_IsSymbolOnLine(param0, param1) == 0) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine0(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[1].spinOffset;
    int v4 = param1->reelTasks[2].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 1 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - v4);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - v4);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 3 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - v4);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - v4);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - v4);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine1(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[0].spinOffset;
    int v4 = param1->reelTasks[2].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 1 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 3 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine2(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[0].spinOffset;
    int v4 = param1->reelTasks[1].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 1 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 3 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 1 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 3 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 3 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 1 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine3(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[1].spinOffset;
    int v4 = param1->reelTasks[2].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - param2);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v3);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - v4);

    if ((v0 == 3) || (v0 == v1) && (v0 == v2)) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine4(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[0].spinOffset;
    int v4 = param1->reelTasks[2].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - param2);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - v4);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    return 0;
}

static int SlotMachine_CheckLine5(SlotMachineReelTask *param0, SlotMachineContext *param1, int param2)
{
    u32 v0, v1, v2;
    int v3 = param1->reelTasks[0].spinOffset;
    int v4 = param1->reelTasks[1].spinOffset;

    v0 = SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v3);
    v1 = SlotMachine_GetVisibleReelSymbol(param1, 1, 2 - v4);
    v2 = SlotMachine_GetVisibleReelSymbol(param1, 2, 2 - param2);

    if ((v0 == v1) && (v0 == v2)) {
        return 1;
    }

    return 0;
}

static void SlotMachine_AdvanceReel(SlotMachineContext *param0, SlotMachineReelIndex param1, fx32 param2)
{
    param0->reelPositions[param1] += param2;
    param0->reelPositions[param1] %= (FX32_ONE * (21 * 32));
    param0->reelPosition[param1] = 21 - (((param0->reelPositions[param1]) / FX32_ONE) / 32);
}

static fx32 SlotMachine_AdvanceReelToStop(SlotMachineContext *param0, SlotMachineReelIndex param1, fx32 param2)
{
    fx32 v0;

    v0 = param0->reelPositions[param1] % (FX32_ONE * 32);

    if (v0) {
        if (v0 < param2) {
            param2 = v0;
        }

        SlotMachine_AdvanceReel(param0, param1, param2);
        v0 = param0->reelPositions[param1] % (FX32_ONE * 32);
    }

    return v0;
}

static u32 SlotMachine_Random100(SlotMachineContext *param0)
{
    u32 v0 = ((u32)LCRNG_Next()) % 100;
    return v0;
}

static int SlotMachine_ConsumeRandom(u32 param0, u32 *param1)
{
    u32 v0 = *param1;

    (*param1) -= param0;

    if ((int)(*param1) < 0) {
        (*param1) = 0;
    }

    if (v0 < param0) {
        return 1;
    }

    return 0;
}

static int SlotMachine_RollSymbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineSymbolChance[param0->machineMode];

    if (v1 > v0) {
        return 1;
    }

    return 0;
}

static int SlotMachine_GenerateSymbols(SlotMachineContext *param0)
{
    param0->symbolMask = 0;

    if (SlotMachine_RollSymbol(param0) == 1) {
        u32 v0 = SlotMachine_Random100(param0);
        const SlotMachineSymbolWeights *v1 = &sSlotMachineSymbolWeights[param0->machineMode];

        param0->symbolRollCount++;

        if (SlotMachine_ConsumeRandom(v1->symbol3Weights.weight, &v0)) {
            param0->symbolMask |= (1 << 3);
            param0->symbolBit3Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol3Weights.weight2, &v0)) {
            param0->symbolMask |= (1 << 2);
            param0->symbolBit2Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol5Weights.weight, &v0)) {
            param0->symbolMask |= (1 << 7);
            param0->symbolBit7Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol5Weights.weight2, &v0)) {
            param0->symbolMask |= (1 << 6);
            param0->symbolBit6Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol4Weights.weight, &v0)) {
            param0->symbolMask |= (1 << 5);
            param0->symbolBit5Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol4Weights.weight2, &v0)) {
            param0->symbolMask |= (1 << 4);
            param0->symbolBit4Count++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->symbol2Weights.weight, &v0)) {
            param0->symbolMask |= (1 << 1);
            param0->symbolBit1Count++;
            return 1;
        }

        param0->symbolMask |= (1 << 0);
        param0->symbolBit0Count++;

        return 1;
    }

    return 0;
}

static int SlotMachine_RollBonus(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineBonusChance[param0->machineMode];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static void SlotMachine_ChooseBonus(SlotMachineContext *param0)
{
    int v0;
    u32 v1 = SlotMachine_Random100(param0);
    const SlotMachineBonusEntry *v2 = sSlotMachineBonusTable[param0->machineMode];

    for (v0 = 0; v0 < SlotMachineBonusType_06; v0++) {
        if (SlotMachine_ConsumeRandom(v2[v0].weight, &v1) == 1) {
            param0->bonusType = v2[v0].bonusType;
            param0->bonusKind = v2[v0].bonusKind;
            param0->payoutChance = sSlotMachineBonusDuration[param0->bonusType];

            switch (param0->bonusKind) {
            case SlotMachineBonusKind_00:
                param0->bonusKind00Count++;
                break;
            case SlotMachineBonusKind_01:
                param0->bonusKind01Count++;
                break;
            case SlotMachineBonusKind_02:
                param0->bonusKind02Count++;
                break;
            }

            return;
        }
    }

    v0--;

    param0->bonusType = v2[v0].bonusType;
    param0->bonusKind = v2[v0].bonusKind;
    param0->payoutChance = sSlotMachineBonusDuration[param0->bonusType];

    GF_ASSERT(FALSE);
}

static void SlotMachine_ChooseBonusMultiplier(SlotMachineContext *param0)
{
    u32 v0 = 0, v1 = SlotMachine_Random100(param0);
    const SlotMachineBonusMultiplier *v2 = sSlotMachineBonusMultiplierTable[param0->machineMode][param0->bonusKind];

    do {
        if (SlotMachine_ConsumeRandom(v2[v0].weight, &v1) == 1) {
            param0->reelAnimTask.winType = v2[v0].winType;

            switch (param0->reelAnimTask.winType) {
            case SlotMachineWinType_00:
                param0->winType00Count++;
                break;
            case SlotMachineWinType_01:
                param0->winType01Count++;
                break;
            case SlotMachineWinType_02:
                param0->winType02Count++;
                break;
            }

            return;
        }

        v0++;
    } while (v0 < SlotMachineWinType_03);

    param0->reelAnimTask.winType = SlotMachineWinType_01;
    GF_ASSERT(FALSE);
}

static int SlotMachine_RollDoubleUp(SlotMachineContext *param0)
{
    u32 v0 = sSlotMachineDoubleUpChance[param0->machineMode];
    u32 v1 = SlotMachine_Random100(param0);

    if (v1 < v0) {
        return 1;
    }

    return 0;
}

static void SlotMachine_GenerateDoubleUpSymbols(SlotMachineContext *param0)
{
    u32 v0;
    const u32 *v1 = sSlotMachineDoubleUpWeights[param0->machineMode];
    u32 v2 = SlotMachine_Random100(param0);

    param0->symbolMask = 0;

    if (SlotMachine_RollDoubleUp(param0) == 0) {
        param0->doubleUpRollCount++;

        switch (param0->bonusType) {
        case SlotMachineBonusType_00:
        case SlotMachineBonusType_01:
        case SlotMachineBonusType_02:
            param0->symbolMask |= (1 << 9);
            param0->doubleUpWinCount++;
            return;
        case SlotMachineBonusType_03:
        case SlotMachineBonusType_04:
        case SlotMachineBonusType_05:
            param0->symbolMask |= (1 << 8);
            param0->doubleUpLoseCount++;
            return;
        }

        GF_ASSERT(FALSE);
        param0->symbolMask |= (1 << 9);
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[0], &v2) == 1) {
        param0->symbolMask |= (1 << 2);
        param0->symbolBit2Count++;
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[1], &v2) == 1) {
        param0->symbolMask |= (1 << 6);
        param0->symbolBit6Count++;
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[1], &v2) == 1) {
        param0->symbolMask |= (1 << 4);
        param0->symbolBit4Count++;
        return;
    }

    param0->symbolMask = (1 << 0);
    param0->symbolBit0Count++;
}

static int SlotMachine_RollDoubleUpWin(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineDoubleUpWinChance[param0->machineMode];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static int SlotMachine_RollDoubleUpLose(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineDoubleUpLoseChance[param0->machineMode];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static int SlotMachine_RollPayout(SlotMachineContext *param0)
{
    u32 v0 = param0->payoutChance;
    u32 v1 = SlotMachine_Random100(param0);

    if (v1 < v0) {
        return 1;
    }

    return 0;
}

static void SlotMachine_AdjustPayout(SlotMachineContext *param0)
{
    u32 v0 = param0->payoutChance;
    u32 v1 = SlotMachine_Random100(param0);
    const u32 *v2 = sSlotMachinePayoutAdjust[param0->machineMode];

    if (param0->doubleUpLose == 2) {
        v0 -= 10;
    } else {
        if (SlotMachine_ConsumeRandom(v2[0], &v1) == 1) {
            v0 -= 10;
        } else if (SlotMachine_ConsumeRandom(v2[1], &v1) == 1) {
            v0 -= 5;
        }
    }

    if ((int)v0 < 0) {
        v0 = 0;
    }

    param0->payoutChance = v0;
}

static SlotMachinePayoutResultEnum SlotMachine_GetPayoutResult(SlotMachineContext *param0)
{
    int v0;
    u32 v1 = param0->payoutChance;
    u32 v2 = SlotMachine_Random100(param0);
    const SlotMachinePayoutResult *v3 = sSlotMachinePayoutResultTable[param0->machineMode];

    for (v0 = 0; v0 < SlotMachinePayoutThreshold_09; v0++) {
        if (v1 >= v3[v0].threshold) {
            if (SlotMachine_ConsumeRandom(v3[v0].chanceA, &v2) == 1) {
                return SlotMachinePayoutResultEnum_01;
            }

            if (SlotMachine_ConsumeRandom(v3[v0].chanceB, &v2) == 1) {
                return SlotMachinePayoutResultEnum_00;
            }

            return SlotMachinePayoutResultEnum_02;
        }
    }

    GF_ASSERT(FALSE);
    return SlotMachinePayoutResultEnum_00;
}

static void SlotMachine_RandomButtonOrder(SlotMachineContext *param0)
{
    param0->buttonOrder = LCRNG_Next() % 6;
}

static void SlotMachine_StartPayoutTask(SlotMachineContext *param0)
{
    SlotMachinePayoutTask *v0 = &param0->payoutTask;

    v0->state = 0;
    v0->done = 0;
    v0->context = param0;
    v0->task = SysTask_Start(SlotMachine_PayoutTask, v0, 138);
}

static void SlotMachine_StopPayoutTask(SlotMachineContext *param0)
{
    SysTask_Done(param0->payoutTask.task);
}

static void SlotMachine_StartPayoutAnim(SlotMachineContext *param0)
{
    param0->payoutTask.done = 0;
    param0->payoutTask.timer = 0;
    param0->payoutTask.state = 1;
}

static int SlotMachine_IsPayoutAnimDone(SlotMachineContext *param0)
{
    return param0->payoutTask.done;
}

static void SlotMachine_PayoutTask(SysTask *param0, void *param1)
{
    int v0;
    SlotMachinePayoutTask *v1 = param1;
    SlotMachineContext *v2 = v1->context;

    switch (v1->state) {
    case 0:
        break;
    case 1:
        SlotMachine_CreatePayoutSprites(v1);
        v1->state++;
        break;
    case 2:
        if (((v1->animManager != NULL) && (SlotMachine_IsPaletteAnimDone(v1->animManager) != 1)) || ((v1->animManager2 != NULL) && (SlotMachine_IsPaletteAnimDone(v1->animManager2) != 1))) {
            break;
        }

        v1->state++;
    case 3:
        if (SlotMachine_GetPressedKey(PAD_BUTTON_X) || (v2->winAmount == 0)) {
            Sound_PlayEffect(SEQ_SE_DP_DENSI16_sseq);
            v2->coins += v2->winAmount;

            if (v2->coins >= 50000) {
                v2->coins = 50000;
            }

            if (v2->payoutMode == 1) {
                v2->payoutCoins += v2->winAmount;
            }

            v2->winAmount = 0;

            if (v1->animManager != NULL) {
                OverworldAnimManager_Finish(v1->animManager);
                v1->animManager = NULL;
            }

            if (v1->animManager2 != NULL) {
                OverworldAnimManager_Finish(v1->animManager2);
                v1->animManager2 = NULL;
            }

            v1->done = 1;
            v1->state = 0;

            return;
        }

        v0 = 0x3;

        if (gSystem.heldKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y)) {
            v0 = 0x1;
        }

        v1->timer++;

        if ((v1->timer & v0) == 0) {
            v2->winAmount--;
            v2->coins++;

            if (v2->coins >= 50000) {
                v2->coins = 50000;
            }

            Sound_PlayEffect(SEQ_SE_DP_DENSI16_sseq);

            if (v2->payoutMode == 1) {
                v2->payoutCoins++;
            }
        }
    }
}

static void SlotMachine_CreatePayoutSprites(SlotMachinePayoutTask *param0)
{
    int v0;
    SlotMachineContext *v1 = param0->context;
    u32 v2 = v1->winLineMask;

    GF_ASSERT(v2 != 0);

    for (v0 = 0; v0 < SlotMachinePaletteIndex_05; v0++, v2 >>= 1) {
        if (v2 & 0x1) {
            if (param0->animManager == NULL) {
                param0->animManager = SlotMachine_CreatePaletteAnim(v1, v0, v1->winAmount);
            } else if (param0->animManager2 == NULL) {
                param0->animManager2 = SlotMachine_CreatePaletteAnim(v1, v0, v1->winAmount);
            } else {
                GF_ASSERT(FALSE);
            }
        }
    }
}

static void SlotMachine_StartReelAnimTask(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->reelAnimTask;

    v0->state = 0;
    v0->step = 0;
    v0->context = param0;
    v0->task = SysTask_Start(SlotMachine_ReelAnimTask, v0, 132);
}

static void SlotMachine_StopReelAnimTask(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->reelAnimTask;
    SysTask_Done(v0->task);
}

static void SlotMachine_SetReelAnim(SlotMachineContext *param0, u32 param1)
{
    SlotMachineReelAnimTask *v0 = &param0->reelAnimTask;

    v0->state = param1;
    v0->step = 0;
    v0->done = 0;
    v0->timer = 0;
}

static int SlotMachine_IsReelAnimDone(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->reelAnimTask;
    return v0->done;
}

static void SlotMachine_CreateReelSprites(SlotMachineContext *param0)
{
    param0->reelAnimTask.spritesFinished = 0;
    param0->reelAnimTask.buttonAnim = SlotMachine_CreateButton(param0);
    param0->reelAnimTask.button3Anim = SlotMachine_CreateButton3(param0);
    param0->reelAnimTask.creditDigitAnim = SlotMachine_CreateCreditDigit(param0);
    param0->reelAnimTask.payoutDigitAnim = SlotMachine_CreatePayoutDigit(param0);
}

static void SlotMachine_FinishReelSprites(SlotMachineContext *param0)
{
    param0->reelAnimTask.spritesFinished = 1;

    OverworldAnimManager_Finish(param0->reelAnimTask.buttonAnim);
    OverworldAnimManager_Finish(param0->reelAnimTask.button3Anim);
    OverworldAnimManager_Finish(param0->reelAnimTask.creditDigitAnim);
    OverworldAnimManager_Finish(param0->reelAnimTask.payoutDigitAnim);
}

static void SlotMachine_ReelAnimTask(SysTask *param0, void *param1)
{
    int v0;
    SlotMachineReelAnimTask *v1 = param1;

    int (*const *v2)(SlotMachineReelAnimTask *);

    do {
        v2 = sSlotMachineReelAnimFuncs[v1->state];
        v0 = v2[v1->step](v1);
    } while (v0 == 1);
}

static int SlotMachine_ReelAnim_Create(SlotMachineReelAnimTask *param0)
{
    param0->reelAnim = SlotMachine_CreateReel(param0->context, param0->reelType);
    param0->step++;

    return 0;
}

static int SlotMachine_ReelAnim_WaitCreate(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 0) {
        return 0;
    }

    SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_01);
    param0->step++;

    return 0;
}

static int SlotMachine_ReelAnim_Finish(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 0) {
        return 0;
    }

    SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_05);
    param0->done = 1;
    param0->step++;

    return 0;
}

static int SlotMachine_ReelAnim_Noop(SlotMachineReelAnimTask *param0)
{
    return 0;
}

static int (*const sSlotMachineReelAnim_Noop[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Noop,
};

static int (*const sSlotMachineReelAnim_Finish[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Create,
    SlotMachine_ReelAnim_WaitCreate,
    SlotMachine_ReelAnim_Finish,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Stop(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_04);
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitStop(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        OverworldAnimManager_Finish(param0->reelAnim);
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Stop2[])(SlotMachineReelAnimTask *work) = {
    SlotMachine_ReelAnim_Stop,
    SlotMachine_ReelAnim_WaitStop,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Start(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_02);
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitStart(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        param0->symbolAnim = SlotMachine_CreateSymbol(param0->context);
        param0->winSymbolAnim = SlotMachine_CreateWinSymbol(param0->context, param0->winType);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_ShowResult(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_01);
        SlotMachine_SetReelVisible(param0->reelAnim, 1);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitResult(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        OverworldAnimManager_Finish(param0->symbolAnim);
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Start[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Start,
    SlotMachine_ReelAnim_WaitStart,
    SlotMachine_ReelAnim_ShowResult,
    SlotMachine_ReelAnim_WaitResult,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Hide(SlotMachineReelAnimTask *param0)
{
    param0->symbolAnim = SlotMachine_CreateSymbol(param0->context);
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_02);
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitHide(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        OverworldAnimManager_Finish(param0->winSymbolAnim);
        OverworldAnimManager_Finish(param0->symbolAnim);
        SlotMachine_SetReelVisible(param0->reelAnim, 0);
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_03);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Stop2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_04);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitStop2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        OverworldAnimManager_Finish(param0->reelAnim);
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Hide[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Hide,
    SlotMachine_ReelAnim_WaitHide,
    SlotMachine_ReelAnim_Stop2,
    SlotMachine_ReelAnim_WaitStop2,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Bonus(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_03);
    param0->bonusAnim = SlotMachine_CreateBonus(param0->context);
    param0->timer = 0;
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitBonus(SlotMachineReelAnimTask *param0)
{
    param0->timer++;

    if (param0->timer >= 48) {
        param0->timer = 0;
        param0->step++;
        Sound_PlayPokemonCry(SPECIES_CLEFAIRY, 0);
        SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_04);
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishBonus(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsBonusDone(param0->bonusAnim) == 1) {
        SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_03);
        OverworldAnimManager_Finish(param0->bonusAnim);
        param0->step++;
        param0->timer = 0;
        param0->done = 1;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Bonus[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Bonus,
    SlotMachine_ReelAnim_WaitBonus,
    SlotMachine_ReelAnim_FinishBonus,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Button(SlotMachineReelAnimTask *param0)
{
    const SlotMachineButtonOrder *v0 = &sSlotMachineButtonOrder[param0->context->buttonOrder];

    param0->step++;
    param0->orderIndex = 0;

    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, v0->winSymbolStates[param0->orderIndex]);

    return 0;
}

static int SlotMachine_ReelAnim_UpdateButton(SlotMachineReelAnimTask *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->context->reelButtons[v0] != 1) {
            v1++;
        }
    }

    if ((param0->orderIndex < 2) && (param0->orderIndex != v1)) {
        const SlotMachineButtonOrder *v2 = &sSlotMachineButtonOrder[param0->context->buttonOrder];

        param0->orderIndex = v1;
        SlotMachine_SetWinSymbolState(param0->winSymbolAnim, v2->winSymbolStates[param0->orderIndex]);
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Button[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Button,
    SlotMachine_ReelAnim_UpdateButton,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Button2(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_03);
    param0->step++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Win[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Button2,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Jackpot(SlotMachineReelAnimTask *param0)
{
    SlotMachine_FinishReelSprites(param0->context);
    param0->symbolAnim = SlotMachine_CreateSymbol(param0->context);
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_02);
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitJackpot(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        OverworldAnimManager_Finish(param0->winSymbolAnim);
        OverworldAnimManager_Finish(param0->symbolAnim);
        SlotMachine_SetReelVisible(param0->reelAnim, 0);
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_03);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Jackpot2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        SlotMachine_CreateButton2(param0->context);
        SlotMachine_CreateButton4(param0->context);
        SlotMachine_CreateNumber(param0->context, SlotMachineNumberType_00);
        SlotMachine_CreateNumber(param0->context, SlotMachineNumberType_01);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitJackpot2(SlotMachineReelAnimTask *param0)
{
    param0->timer++;

    if (param0->timer >= 45) {
        param0->timer = 0;
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_04);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishJackpot(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        OverworldAnimManager_Finish(param0->reelAnim);
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Jackpot[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Jackpot,
    SlotMachine_ReelAnim_WaitJackpot,
    SlotMachine_ReelAnim_Jackpot2,
    SlotMachine_ReelAnim_WaitJackpot2,
    SlotMachine_ReelAnim_FinishJackpot,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Win(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_04);
    param0->done = 1;
    param0->step++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Win2[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Win,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Lose(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_08);
    param0->done = 1;
    param0->step++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Lose[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Lose,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Stop3(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_06);
    param0->step++;
    param0->done = 1;
    return 0;
}

static int (*const sSlotMachineReelAnim_Stop3[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Stop3,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Payout(SlotMachineReelAnimTask *param0)
{
    param0->symbolAnim = SlotMachine_CreateSymbol(param0->context);
    SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_02);
    param0->spritesFinished = 1;
    param0->step++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitPayout(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        OverworldAnimManager_Finish(param0->symbolAnim);
        OverworldAnimManager_Finish(param0->winSymbolAnim);
        SlotMachine_SetReelVisible(param0->reelAnim, 0);
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_03);
        param0->timer = 0;
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout2(SlotMachineReelAnimTask *param0)
{
    param0->timer++;

    if (param0->timer >= 30) {
        param0->timer = 0;
        param0->step++;
        SlotMachine_SetReelState(param0->reelAnim, SlotMachineReelStateEnum_02);
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout3(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->reelAnim) == 1) {
        param0->symbolAnim = SlotMachine_CreateSymbol(param0->context);
        param0->winSymbolAnim = SlotMachine_CreateWinSymbol(param0->context, param0->winType);
        param0->spritesFinished = 0;
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout4(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        SlotMachine_SetWinSymbolState(param0->winSymbolAnim, SlotMachineWinSymbolState_01);
        SlotMachine_SetReelVisible(param0->reelAnim, 1);
        param0->step++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishPayout(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->winSymbolAnim) == 1) {
        OverworldAnimManager_Finish(param0->symbolAnim);
        param0->done = 1;
        param0->step++;
    }

    return 0;
}

static int (*const sSlotMachineReelAnim_Payout[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Payout,
    SlotMachine_ReelAnim_WaitPayout,
    SlotMachine_ReelAnim_Payout2,
    SlotMachine_ReelAnim_Payout3,
    SlotMachine_ReelAnim_Payout4,
    SlotMachine_ReelAnim_FinishPayout,
    SlotMachine_ReelAnim_Noop
};

static int (*const *const sSlotMachineReelAnimFuncs[13])(SlotMachineReelAnimTask *) = {
    sSlotMachineReelAnim_Noop,
    sSlotMachineReelAnim_Finish,
    sSlotMachineReelAnim_Stop2,
    sSlotMachineReelAnim_Start,
    sSlotMachineReelAnim_Hide,
    sSlotMachineReelAnim_Bonus,
    sSlotMachineReelAnim_Button,
    sSlotMachineReelAnim_Win,
    sSlotMachineReelAnim_Jackpot,
    sSlotMachineReelAnim_Win2,
    sSlotMachineReelAnim_Lose,
    sSlotMachineReelAnim_Stop3,
    sSlotMachineReelAnim_Payout,
};

static void SlotMachine_LoadPalettes(SlotMachineContext *param0)
{
    void *v0;
    NNSG2dPaletteData *v1;
    SlotMachinePalette *v2 = &param0->palette;

    v2->context = param0;
    v0 = SlotMachine_ReadNarcMember(param0, 3, 0);

    NNS_G2dGetUnpackedPaletteData(v0, &v1);

    SlotMachine_CopyPalette(v1, 0x1, v2->paletteA);
    SlotMachine_CopyPalette(v1, 0x2, v2->baseReelPalettes[SlotMachinePaletteIndex_00]);
    SlotMachine_CopyPalette(v1, 0x3, v2->baseReelPalettes[SlotMachinePaletteIndex_01]);
    SlotMachine_CopyPalette(v1, 0x3, v2->baseReelPalettes[SlotMachinePaletteIndex_02]);
    SlotMachine_CopyPalette(v1, 0x4, v2->baseReelPalettes[SlotMachinePaletteIndex_03]);
    SlotMachine_CopyPalette(v1, 0x4, v2->baseReelPalettes[SlotMachinePaletteIndex_04]);

    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 5, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->paletteB);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 6, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->flashPaletteA);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 7, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->flashPaletteB);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 74, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->litReelPalettes[SlotMachinePaletteIndex_00]);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 75, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->litReelPalettes[SlotMachinePaletteIndex_01]);
    SlotMachine_CopyPalette(v1, 0, v2->litReelPalettes[SlotMachinePaletteIndex_02]);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 76, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->litReelPalettes[SlotMachinePaletteIndex_03]);
    SlotMachine_CopyPalette(v1, 0, v2->litReelPalettes[SlotMachinePaletteIndex_04]);
    Heap_Free(v0);
}

static void SlotMachine_Noop2(SlotMachineContext *param0)
{
    return;
}

static void SlotMachine_CopyPalette(NNSG2dPaletteData *param0, int param1, u16 *param2)
{
    int v0;
    u16 *v1 = param0->pRawData;

    v1 = &v1[param1 * 16];

    for (v0 = 0; v0 < 16; v0++) {
        param2[v0] = v1[v0];
    }
}

static void SlotMachine_BlendColor(u16 param0, u16 param1, u16 param2, u16 *param3)
{
    const SlotMachineColor555 *v0 = (SlotMachineColor555 *)&param0;
    const SlotMachineColor555 *v1 = (SlotMachineColor555 *)&param1;

    if (param2 > 16) {
        param2 = 16;
    }

    (*param3) = (v0->red + ((v1->red - v0->red) * param2 >> 4)) | ((v0->green + ((v1->green - v0->green) * param2 >> 4)) << 5) | ((v0->blue + ((v1->blue - v0->blue) * param2 >> 4)) << 10);
}

static void SlotMachine_BlendPalette(const u16 *param0, const u16 *param1, u16 param2, u16 *param3)
{
    int v0 = 0;

    do {
        SlotMachine_BlendColor(param0[v0], param1[v0], param2, &param3[v0]);
        v0++;
    } while (v0 < 16);
}

static void SlotMachine_LoadPalette(SlotMachineContext *param0, u32 param1, int param2, u16 *param3)
{
    Bg_LoadPalette(param1, param3, PALETTE_SIZE_BYTES, PLTT_OFFSET(param2));
}

static int sSlotMachinePaletteSlot[SlotMachinePaletteIndex_05] = {
    0x2,
    0x3,
    0xc,
    0x4,
    0xb,
};

static void SlotMachine_SetReelPalette(SlotMachineContext *param0, SlotMachinePaletteIndex param1)
{
    SlotMachinePalette *v0 = &param0->palette;
    int v1 = sSlotMachinePaletteSlot[param1];

    SlotMachine_LoadPalette(param0, 1, v1, v0->baseReelPalettes[param1]);
}

static void SlotMachine_SetReelPaletteBlend(SlotMachineContext *param0, SlotMachinePaletteIndex param1)
{
    SlotMachinePalette *v0 = &param0->palette;
    int v1 = sSlotMachinePaletteSlot[param1];
    const u16 *v2 = v0->baseReelPalettes[param1];
    const u16 *v3 = v0->litReelPalettes[param1];
    u16 *v4 = v0->blendedReelPalettes[param1];

    SlotMachine_BlendPalette(v2, v3, 10, v4);
    SlotMachine_LoadPalette(param0, 1, v1, v4);
}

static void SlotMachine_SetReelPaletteBlend2(SlotMachineContext *param0, SlotMachinePaletteIndex param1)
{
    SlotMachinePalette *v0 = &param0->palette;
    int v1 = sSlotMachinePaletteSlot[param1];
    const u16 *v2 = v0->baseReelPalettes[param1];
    const u16 *v3 = v0->litReelPalettes[param1];
    u16 *v4 = v0->blendedReelPalettes[param1];

    SlotMachine_BlendPalette(v2, v3, 12, v4);
    SlotMachine_LoadPalette(param0, 1, v1, v4);
}

static void SlotMachine_ResetReelPalettes(SlotMachineContext *param0)
{
    int v0 = SlotMachinePaletteIndex_00;

    do {
        SlotMachine_SetReelPalette(param0, v0);
        v0++;
    } while (v0 < SlotMachinePaletteIndex_05);
}

static void SlotMachine_BlendReelPalettes(SlotMachineContext *param0)
{
    int v0 = SlotMachinePaletteIndex_00;

    do {
        SlotMachine_SetReelPaletteBlend(param0, v0);
        v0++;
    } while (v0 < SlotMachinePaletteIndex_05);
}

static const OverworldAnimManagerFuncs sSlotMachinePaletteAnimFuncs;

static OverworldAnimManager *SlotMachine_CreatePaletteAnim(SlotMachineContext *param0, SlotMachinePaletteIndex param1, u32 param2)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { 0, 0, 0 };
    SlotMachinePaletteAnimArgs v2;

    v2.paletteIndex = param1;
    v2.delay = param2;
    v2.context = param0;

    v0 = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachinePaletteAnimFuncs, &v1, 0, &v2, 143);

    return v0;
}

static int SlotMachine_IsPaletteAnimDone(OverworldAnimManager *param0)
{
    SlotMachinePaletteAnim *v0 = OverworldAnimManager_GetFuncsContext(param0);
    return v0->done;
}

static int SlotMachine_PaletteAnim_Init(OverworldAnimManager *param0, void *param1)
{
    const SlotMachinePaletteAnimArgs *v0;
    SlotMachinePaletteAnim *v1 = param1;

    v0 = (const SlotMachinePaletteAnimArgs *)OverworldAnimManager_GetUserData(param0);
    v1->context = v0->context;
    v1->paletteIndex = v0->paletteIndex;
    v1->delay = v0->delay;
    v1->palette = &v1->context->palette;

    return 1;
}

static void SlotMachine_PaletteAnim_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePaletteAnim *v0 = param1;
    SlotMachine_SetReelPalette(v0->context, v0->paletteIndex);
}

static void SlotMachine_PaletteAnim_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachinePaletteAnim *v1 = param1;
    int v2 = sSlotMachinePaletteSlot[v1->paletteIndex];
    u16 *v3 = v1->palette->blendedReelPalettes[v1->paletteIndex];
    const u16 *v4 = v1->palette->baseReelPalettes[v1->paletteIndex];
    const u16 *v5 = v1->palette->litReelPalettes[v1->paletteIndex];

    switch (v1->state) {
    case 0:
        v1->blendAmount += 0x4000;

        if (v1->blendAmount > (FX32_ONE * 16)) {
            v1->blendAmount = (FX32_ONE * 16);
        }

        v0 = ((v1->blendAmount) / FX32_ONE);

        if (v0 == 16) {
            v1->state++;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->context, 1, v2, v3);
        break;
    case 1:
        v1->blendAmount -= 0x4000;

        if (v1->blendAmount < (FX32_ONE * 0)) {
            v1->blendAmount = (FX32_ONE * 0);
        }

        v0 = ((v1->blendAmount) / FX32_ONE);

        if (v0 == 0) {
            v1->repeatCount++;

            if (v1->repeatCount >= 4) {
                if (v1->delay) {
                    v1->state++;
                    v1->done = 1;
                } else {
                    v1->state = 4;
                    v1->done = 1;
                }
            } else {
                v1->state--;
            }
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->context, 1, v2, v3);
        break;
    case 2:
        v1->blendAmount += 0x8000;

        if (v1->blendAmount > (FX32_ONE * 16)) {
            v1->blendAmount = (FX32_ONE * 16);
        }

        v0 = ((v1->blendAmount) / FX32_ONE);

        if (v0 == 16) {
            v1->state++;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->context, 1, v2, v3);
        break;
    case 3:
        v1->blendAmount -= 0x8000;

        if (v1->blendAmount < (FX32_ONE * 0)) {
            v1->blendAmount = (FX32_ONE * 0);
        }

        v0 = ((v1->blendAmount) / FX32_ONE);

        if (v0 == 0) {
            v1->state--;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->context, 1, v2, v3);
        break;
    case 4:
        break;
    }
}

static const OverworldAnimManagerFuncs sSlotMachinePaletteAnimFuncs = {
    sizeof(SlotMachinePaletteAnim),
    SlotMachine_PaletteAnim_Init,
    SlotMachine_PaletteAnim_Exit,
    SlotMachine_PaletteAnim_Update,
    OverworldAnimManager_DummyRenderFunc
};

static const OverworldAnimManagerFuncs sSlotMachinePayoutAnimFuncs;

static void SlotMachine_CreatePayoutAnim(SlotMachineContext *param0)
{
    VecFx32 v0 = { 0, 0, 0 };

    GF_ASSERT(param0->payoutTask.animManager == NULL);
    param0->payoutTask.animManager = OverworldAnimManagerList_InitManager(param0->animManagerList, &sSlotMachinePayoutAnimFuncs, &v0, 0, param0, 143);
}

static void SlotMachine_FinishPayoutAnim(SlotMachineContext *param0)
{
    if (param0->payoutTask.animManager != NULL) {
        OverworldAnimManager_Finish(param0->payoutTask.animManager);
        param0->payoutTask.animManager = NULL;
    }

    SlotMachine_ResetReelPalettes(param0);
}

#define LB_WAIT_DATA(wait) (1 << 5), (FX32_ONE * (wait)), 0, 0

static const SlotMachinePayoutAnimStep sSlotMachinePayoutAnimSteps[] = {
    { LB_WAIT_DATA(30) },
    { (1 << 0), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 0), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 1) | (1 << 2), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 1) | (1 << 2), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 3) | (1 << 4), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 3) | (1 << 4), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(16) },
    { (1 << 3) | (1 << 4), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 3) | (1 << 4), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 1) | (1 << 2), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 1) | (1 << 2), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 0), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 0), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(16) },
    { (1 << 1), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 1), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 4), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 4), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 2), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 2), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 3), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 3), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 0), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 0), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(16) },
    { (1 << 3), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 3), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 1), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 1), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 0), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 0), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 2), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 2), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 4), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 4), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(8) },
    { (1 << 2), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 2), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 0), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 0), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 1), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 1), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(2) },
    { (1 << 3), (FX32_ONE * 0), (FX32_ONE * 14), 0x4000 },
    { LB_WAIT_DATA(1) },
    { (1 << 3), (FX32_ONE * 14), (FX32_ONE * 0), 0x4000 },
    { LB_WAIT_DATA(16) },
    { (1 << 6), 1, 0, 0 },
};

static void SlotMachine_UpdatePayoutAnim(SlotMachinePayoutAnim *param0)
{
    u32 v0;
    int v1, v2, v3;
    u16 *v4;
    const u16 *v5, *v6;
    const SlotMachinePayoutAnimStep *v7 = &sSlotMachinePayoutAnimSteps[param0->stepIndex];

    for (v1 = 0, v2 = 1, v0 = (1 << 0); v0 <= (1 << 4); v1++, v0 <<= 1) {
        if (v7->mask & v0) {
            if (param0->direction == 0) {
                param0->blendValues[v1] = v7->start;
                v2 = 0;
            } else {
                if (v7->start < v7->end) {
                    param0->blendValues[v1] += v7->speed;

                    if (param0->blendValues[v1] >= v7->end) {
                        param0->blendValues[v1] = v7->end;
                    } else {
                        v2 = 0;
                    }
                } else {
                    param0->blendValues[v1] -= v7->speed;

                    if (param0->blendValues[v1] <= v7->end) {
                        param0->blendValues[v1] = v7->end;
                    } else {
                        v2 = 0;
                    }
                }
            }

            v3 = sSlotMachinePaletteSlot[v1];
            v5 = param0->palette->baseReelPalettes[v1];
            v6 = param0->palette->litReelPalettes[v1];
            v4 = param0->palette->blendedReelPalettes[v1];

            SlotMachine_BlendPalette(v5, v6, ((param0->blendValues[v1]) / FX32_ONE), v4);
            SlotMachine_LoadPalette(param0->context, 1, v3, v4);
        }
    }

    for (; v0 <= (1 << 5); v0 <<= 1) {
        if (v7->mask & (1 << 5)) {
            param0->timer += FX32_ONE;

            if (param0->timer >= v7->start) {
                param0->timer = 0;
            } else {
                v2 = 0;
            }
        }
    }

    param0->direction = 1;

    if (v2 == 1) {
        param0->direction = 0;
        param0->stepIndex++;
        v7 = &sSlotMachinePayoutAnimSteps[param0->stepIndex];

        if (v7->mask == (1 << 6)) {
            param0->stepIndex = (int)v7->start;
            param0->stepIndex = 0;
        }
    }
}

static int SlotMachine_PayoutAnim_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePayoutAnim *v0 = param1;

    v0->context = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v0->palette = &v0->context->palette;

    return 1;
}

static void SlotMachine_PayoutAnim_Exit(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void SlotMachine_PayoutAnim_Update(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePayoutAnim *v0 = param1;
    SlotMachine_UpdatePayoutAnim(v0);
}

static const OverworldAnimManagerFuncs sSlotMachinePayoutAnimFuncs = {
    sizeof(SlotMachinePayoutAnim),
    SlotMachine_PayoutAnim_Init,
    SlotMachine_PayoutAnim_Exit,
    SlotMachine_PayoutAnim_Update,
    OverworldAnimManager_DummyRenderFunc
};

static void SlotMachine_StartFadeInTask(SlotMachineContext *param0)
{
    SlotMachineFadeTask *v0 = Heap_AllocAtEnd(HEAP_ID_79, sizeof(SlotMachineFadeTask));

    v0->state = 0;
    v0->progress = 0;
    v0->context = param0;

    SysTask_Start(SlotMachine_FadeInTask, v0, 143);
}

static void SlotMachine_StartFadeOutTask(SlotMachineContext *param0)
{
    SlotMachineFadeTask *v0 = Heap_AllocAtEnd(HEAP_ID_79, sizeof(SlotMachineFadeTask));

    v0->state = 0;
    v0->progress = 0;
    v0->context = param0;

    SysTask_Start(SlotMachine_FadeOutTask, v0, 143);
}

static void SlotMachine_StartFlashTask(SlotMachineContext *param0, int param1)
{
    SlotMachineFadeTask *v0 = Heap_AllocAtEnd(HEAP_ID_79, sizeof(SlotMachineFadeTask));

    v0->state = 0;
    v0->flashType = param1;
    v0->progress = (FX32_ONE * 8);
    v0->context = param0;

    SysTask_Start(SlotMachine_FlashTask, v0, 143);
    Sound_PlayEffect(SEQ_SE_DP_025_sseq);
}

static void SlotMachine_FadeInTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->context->palette;
    const u16 *v2 = v1->paletteA;
    const u16 *v3 = v1->paletteB;
    u16 *v4 = v1->blendTarget;
    u16 v5;

    v0->progress += 0x800;
    v5 = ((v0->progress) / FX32_ONE);

    if (v5 > 16) {
        v5 = 16;
    }

    SlotMachine_BlendPalette(v2, v3, v5, v4);
    SlotMachine_LoadPalette(v0->context, 7, 0x1, v4);

    if ((v5 == 16) || (v0->context->state == 63)) {
        Heap_Free(v0);
        SysTask_Done(param0);
    }
}

static void SlotMachine_FadeOutTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->context->palette;
    const u16 *v2 = v1->paletteB;
    const u16 *v3 = v1->paletteA;
    u16 *v4 = v1->blendTarget;
    u16 v5;

    v0->progress += 0x800;
    v5 = ((v0->progress) / FX32_ONE);

    if (v5 > 16) {
        v5 = 16;
    }

    SlotMachine_BlendPalette(v2, v3, v5, v4);
    SlotMachine_LoadPalette(v0->context, 7, 0x1, v4);

    if ((v5 == 16) || (v0->context->state == 63)) {
        Heap_Free(v0);
        SysTask_Done(param0);
    }
}

static void SlotMachine_FlashTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->context->palette;
    const u16 *v2, *v3 = v1->paletteB;
    u16 *v4 = v1->blendTarget;
    int v5;

    if (v0->context->state == 63) {
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }

    if (v0->flashType == 0) {
        v2 = v1->flashPaletteA;
    } else {
        v2 = v1->flashPaletteB;
    }

    switch (v0->state) {
    case 0:
        v0->progress += 0x1000;
        v5 = ((v0->progress) / FX32_ONE);

        if (v5 > 16) {
            v5 = 16;
            v0->state++;
        }

        SlotMachine_BlendPalette(v3, v2, v5, v4);
        SlotMachine_LoadPalette(v0->context, 7, 0x1, v4);
        break;
    case 1:
        v0->progress -= 0x400;
        v5 = ((v0->progress) / FX32_ONE);

        if (v5 < 0) {
            v5 = 0;
        }

        SlotMachine_BlendPalette(v3, v2, v5, v4);
        SlotMachine_LoadPalette(v0->context, 7, 0x1, v4);

        if (v5 == 0) {
            Heap_Free(v0);
            SysTask_Done(param0);
        }
    }
}

SlotMachineSymbol SlotMachine_GetReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2)
{
    int v0 = (param0->reelPosition[param1] + param2) % 21;

    if (v0 < 0) {
        v0 = 21 + v0;
    }

    return sSlotMachineReelStrips[param1][v0];
}

SlotMachineSymbol SlotMachine_GetVisibleReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2)
{
    int v0 = 0;

    if (param0->reelPositions[param1] % (FX32_ONE * 32)) {
        v0--;
    }

    return SlotMachine_GetReelSymbol(param0, param1, param2 + v0);
}

static int SlotMachine_GetPressedKey(u32 param0)
{
    u32 v0 = gSystem.pressedKeys & param0;

    if (v0 == param0) {
        return 2;
    }

    if (v0 & param0) {
        return 1;
    }

    return 0;
}

static SlotMachineSymbol SlotMachine_GetSymbolFromMask(u32 param0)
{
    if (param0 & ((1 << 0) | (1 << 1))) {
        return 2;
    }

    if (param0 & ((1 << 2) | (1 << 3))) {
        return 3;
    }

    if (param0 & ((1 << 4) | (1 << 5))) {
        return 4;
    }

    if (param0 & ((1 << 6) | (1 << 7))) {
        return 5;
    }

    if (param0 & (1 << 8)) {
        return 1;
    }

    if (param0 & (1 << 9)) {
        return 0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_CheckLine1Symbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 1);
    u32 v1 = SlotMachine_GetVisibleReelSymbol(param0, 1, 1);
    u32 v2 = SlotMachine_GetVisibleReelSymbol(param0, 2, 1);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return v0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_CheckLine2Symbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 2);
    u32 v1 = SlotMachine_GetVisibleReelSymbol(param0, 1, 2);
    u32 v2 = SlotMachine_GetVisibleReelSymbol(param0, 2, 2);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return v0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_CheckLine3Symbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 3);
    u32 v1 = SlotMachine_GetVisibleReelSymbol(param0, 1, 3);
    u32 v2 = SlotMachine_GetVisibleReelSymbol(param0, 2, 3);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return v0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_CheckDiagonal1Symbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 1);
    u32 v1 = SlotMachine_GetVisibleReelSymbol(param0, 1, 2);
    u32 v2 = SlotMachine_GetVisibleReelSymbol(param0, 2, 3);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return v0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_CheckDiagonal2Symbol(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_GetVisibleReelSymbol(param0, 0, 3);
    u32 v1 = SlotMachine_GetVisibleReelSymbol(param0, 1, 2);
    u32 v2 = SlotMachine_GetVisibleReelSymbol(param0, 2, 1);

    if ((v0 == 3) || ((v0 == v1) && (v0 == v2))) {
        return v0;
    }

    return 6;
}

static SlotMachineSymbol SlotMachine_EvaluateLines(SlotMachineContext *param0, u32 param1, u32 *param2)
{
    u32 v0, v1;

    *param2 = 0;

    v1 = 6;
    v0 = SlotMachine_CheckLine1Symbol(param0);

    if (v0 != 6) {
        v1 = v0;
        *param2 |= (1 << 1);
    }

    v0 = SlotMachine_CheckLine2Symbol(param0);

    if (v0 != 6) {
        v1 = v0;
        *param2 |= (1 << 0);
    }

    v0 = SlotMachine_CheckLine3Symbol(param0);

    if (v0 != 6) {
        v1 = v0;
        *param2 |= (1 << 2);
    }

    v0 = SlotMachine_CheckDiagonal1Symbol(param0);

    if (v0 != 6) {
        v1 = v0;
        *param2 |= (1 << 3);
    }

    v0 = SlotMachine_CheckDiagonal2Symbol(param0);

    if (v0 != 6) {
        v1 = v0;
        *param2 |= (1 << 4);
    }

    return v1;
}

static SlotMachineSymbol SlotMachine_EvaluateLine2(SlotMachineContext *param0, u32 param1, u32 *param2)
{
    u32 v0;

    *param2 = 0;
    v0 = SlotMachine_CheckLine2Symbol(param0);

    if (v0 != 6) {
        GF_ASSERT(v0 == 2);
        *param2 |= (1 << 0);
    }

    return v0;
}

static SlotMachineReelType SlotMachine_GetWinType(u32 param0)
{
    if (param0 & ((1 << 0) | (1 << 1))) {
        return SlotMachineReelType_01;
    }

    if (param0 & ((1 << 2) | (1 << 3))) {
        return SlotMachineReelType_00;
    }

    if (param0 & ((1 << 4) | (1 << 5))) {
        return SlotMachineReelType_02;
    }

    if (param0 & ((1 << 6) | (1 << 7))) {
        return SlotMachineReelType_03;
    }

    GF_ASSERT(FALSE);
    return SlotMachineReelType_04;
}

static void SlotMachine_ClearButtonInputs(SlotMachineContext *param0)
{
    int v0 = 0;

    do {
        param0->buttonInputs[v0] = 0;
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_RecordButtonInput(SlotMachineContext *param0, u32 param1)
{
    int v0 = 0;

    do {
        if (param0->buttonInputs[v0] == 0) {
            break;
        }

        v0++;
    } while (v0 < 3);

    GF_ASSERT(v0 < 3);
    param0->buttonInputs[v0] = param1;
}

static int SlotMachine_CheckButtonOrder(SlotMachineContext *param0)
{
    int v0 = 0;
    u32 v1[3] = { PAD_BUTTON_Y, PAD_BUTTON_B, PAD_BUTTON_A };

    do {
        if ((param0->buttonInputs[v0] != 0) && (param0->buttonInputs[v0] != v1[v0])) {
            return 0;
        }

        v0++;
    } while (v0 < 3);

    return 1;
}

static int SlotMachine_CheckButtonOrder2(SlotMachineContext *param0)
{
    int v0 = 0;
    const SlotMachineButtonOrder *v1 = &sSlotMachineButtonOrder[param0->buttonOrder];

    do {
        if ((param0->buttonInputs[v0] != 0) && (param0->buttonInputs[v0] != v1->buttons[v0])) {
            return 0;
        }

        v0++;
    } while (v0 < 3);

    return 1;
}

static void SlotMachine_SetReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    const int *v0 = sSlotMachineReelHighlightPos[param1];

    Bg_ChangeTilemapRectPalette(param0->bgConfig, 1, v0[0], v0[1], 3, 2, 6);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 1);
}

static void SlotMachine_ClearReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    const int *v0 = sSlotMachineReelHighlightPos[param1];

    Bg_ChangeTilemapRectPalette(param0->bgConfig, 1, v0[0], v0[1], 3, 2, 5);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 1);
}

static u32 SlotMachine_GetPayoutAmount(SlotMachineContext *param0)
{
    int v0, v1;
    SlotMachineSymbol v2 = param0->winSymbol;
    u32 v3 = param0->winLineMask;

    GF_ASSERT(v2 != 6);

    for (v0 = 0, v1 = 0; v0 < SlotMachinePaletteIndex_05; v0++, v3 >>= 1) {
        if (v3 & 0x1) {
            v1 += sSlotMachinePayoutPerLine[v2];
        }
    }

    return v1;
}

static const SlotMachineButtonOrder sSlotMachineButtonOrder[6] = {
    {
        { PAD_BUTTON_Y, PAD_BUTTON_B, PAD_BUTTON_A },
        { SlotMachineWinSymbolState_06, SlotMachineWinSymbolState_05, SlotMachineWinSymbolState_07 },
    },
    {
        { PAD_BUTTON_Y, PAD_BUTTON_A, PAD_BUTTON_B },
        { SlotMachineWinSymbolState_06, SlotMachineWinSymbolState_07, SlotMachineWinSymbolState_05 },
    },
    {
        { PAD_BUTTON_B, PAD_BUTTON_Y, PAD_BUTTON_A },
        { SlotMachineWinSymbolState_05, SlotMachineWinSymbolState_06, SlotMachineWinSymbolState_07 },
    },
    {
        { PAD_BUTTON_B, PAD_BUTTON_A, PAD_BUTTON_Y },
        { SlotMachineWinSymbolState_05, SlotMachineWinSymbolState_07, SlotMachineWinSymbolState_06 },
    },
    {
        { PAD_BUTTON_A, PAD_BUTTON_Y, PAD_BUTTON_B },
        { SlotMachineWinSymbolState_07, SlotMachineWinSymbolState_06, SlotMachineWinSymbolState_05 },
    },
    {
        { PAD_BUTTON_A, PAD_BUTTON_B, PAD_BUTTON_Y },
        { SlotMachineWinSymbolState_07, SlotMachineWinSymbolState_05, SlotMachineWinSymbolState_06 },
    },
};

static const int sSlotMachineReelHighlightPos[3][2] = {
    { 0x7, 0x11 },
    { 0xf, 0x11 },
    { 0x16, 0x11 },
};
