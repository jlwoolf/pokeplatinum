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
    u16 unk_00_0 : 5;
    u16 unk_00_5 : 5;
    u16 unk_00_10 : 5;
    u16 unk_00_15 : 1;
} SlotMachineColor555;

typedef struct {
    u32 unk_00[3];
    SlotMachineWinSymbolState unk_0C[3];
} SlotMachineButtonOrder;

typedef struct {
    SlotMachinePaletteIndex unk_00;
    u32 unk_04;
    SlotMachineContext *unk_08;
} SlotMachinePaletteAnimArgs;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    SlotMachinePaletteIndex unk_10;
    u32 unk_14;
    fx32 unk_18;
    SlotMachineContext *unk_1C;
    SlotMachinePalette *unk_20;
} SlotMachinePaletteAnim;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    fx32 unk_0C;
    SlotMachinePaletteIndex unk_10;
    fx32 unk_14[5];
    SlotMachineContext *unk_28;
    SlotMachinePalette *unk_2C;
} SlotMachinePayoutAnim;

typedef struct {
    u32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
} SlotMachinePayoutAnimStep;

typedef struct {
    int unk_00;
    fx32 unk_04;
    int unk_08;
    SlotMachineContext *unk_0C;
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
        param0->unk_A8[v0] = v1;
        param0->unk_90[v0] = (FX32_ONE * (21 * 32)) - (FX32_ONE * ((v1) * 32));
        param0->unk_90[v0] %= (FX32_ONE * (21 * 32));
    }
}

int SlotMachine_Update(SlotMachineContext *param0)
{
    int v0;

    do {
        v0 = sSlotMachineStateFuncs[param0->unk_00](param0);
    } while (v0 == 1);

    if (v0 == 2) {
        return 1;
    }

    return 0;
}

static int SlotMachine_State_Init(SlotMachineContext *param0)
{
    param0->unk_64 = 0;
    param0->unk_68 = 0;
    param0->unk_8C = (FX32_ONE * 16);
    param0->unk_74 = 0;
    param0->unk_08 = 0;
    param0->unk_00 = 1;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);

    if (param0->unk_60 == 0) {
        param0->unk_00 = 60;
        param0->unk_04 = 63;
    } else if (param0->unk_60 < 3) {
        param0->unk_00 = 59;
        param0->unk_04 = 63;
    } else if (param0->unk_60 >= 50000) {
        param0->unk_00 = 61;
        param0->unk_04 = 1;
    }

    return 1;
}

static int SlotMachine_State_InsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        SlotMachine_FinishPayoutAnim(param0);
        param0->unk_00 = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->unk_60 -= 3;
        param0->unk_45C += 3;
        param0->unk_00 = 2;

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
        param0->unk_60 += 3;
        param0->unk_00 = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->unk_00 = 3;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartSpin(SlotMachineContext *param0)
{
    SlotMachine_GenerateSymbols(param0);

    param0->unk_460++;
    param0->unk_464++;
    param0->unk_70 = 0;

    if (param0->unk_74 & ((1 << 0) | (1 << 1) | (1 << 4) | (1 << 5))) {
        param0->unk_70 = 1;
    }

    param0->unk_30 = 0;

    if (param0->unk_74 != 0) {
        if (SlotMachine_RollBonus(param0) == 0) {
            param0->unk_13C.unk_18 = SlotMachineReelType_04;
        } else {
            param0->unk_13C.unk_18 = SlotMachine_GetWinType(param0->unk_74);
            param0->unk_490++;
        }

        param0->unk_30 = 1;
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

    param0->unk_7C[0] = 1;
    param0->unk_7C[1] = 1;
    param0->unk_7C[2] = 1;
    param0->unk_6C = 0;
    param0->unk_00 = 4;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    return 1;
}

static int SlotMachine_State_SpinDelay(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        param0->unk_6C = 0;
        param0->unk_00 = 5;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->unk_7C[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->unk_7C[0] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->unk_7C[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->unk_7C[1] = 2;

        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->unk_7C[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->unk_7C[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    }

    if ((param0->unk_7C[0] == 2) && (param0->unk_7C[1] == 2) && (param0->unk_7C[2] == 2)) {
        param0->unk_00 = 6;
    }

    return 0;
}

static int SlotMachine_State_WaitReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->unk_00 = 7;
    return 1;
}

static int SlotMachine_State_Evaluate(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLines(param0, param0->unk_74, &param0->unk_48);

    param0->unk_44 = v0;

    if (v0 == 6) {
        if (param0->unk_74 & ((1 << 1) | (1 << 3) | (1 << 5) | (1 << 7))) {
            param0->unk_00 = 16;
            return 1;
        }

        if (param0->unk_74 != 0) {
            param0->unk_00 = 10;
            return 1;
        }

        param0->unk_00 = 8;
        return 1;
    }

    if (param0->unk_74 & ((1 << 1) | (1 << 3) | (1 << 5) | (1 << 7))) {
        if (param0->unk_74 & (1 << 1)) {
            param0->unk_00 = 21;
        } else {
            param0->unk_00 = 19;
        }

        return 1;
    }

    if (v0 == 2) {
        param0->unk_00 = 14;
        return 1;
    }

    param0->unk_00 = 12;
    return 1;
}

static int SlotMachine_State_NoWin(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);

    param0->unk_6C = 0;
    param0->unk_00 = 9;

    return 1;
}

static int SlotMachine_State_NoWinWait(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        param0->unk_6C = 0;
        param0->unk_00 = 0;
    }

    return 0;
}

static int SlotMachine_State_Payout(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 2);
    param0->unk_00 = 11;

    return 0;
}

static int SlotMachine_State_WaitPayout(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 1) {
        SlotMachine_SetReelAnim(param0, 0);
        param0->unk_00 = 0;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_Win(SlotMachineContext *param0)
{
    param0->unk_64 = SlotMachine_GetPayoutAmount(param0);
    param0->unk_458 += param0->unk_64;
    param0->unk_6C = 0;
    param0->unk_00 = 13;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitWin(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C == (FX32_ONE * 30)) {
        SlotMachine_SetReelAnim(param0, 2);
    } else if (param0->unk_6C > (FX32_ONE * 30)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            SlotMachine_SetReelAnim(param0, 0);
            param0->unk_6C = 0;
            param0->unk_00 = 0;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_BigWin(SlotMachineContext *param0)
{
    param0->unk_64 = 0;
    param0->unk_6C = 0;
    param0->unk_00 = 15;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitBigWin(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C == (FX32_ONE * 15)) {
        SlotMachine_SetReelAnim(param0, 2);
    } else if (param0->unk_6C > (FX32_ONE * 15)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            SlotMachine_SetReelAnim(param0, 0);
            param0->unk_6C = 0;
            param0->unk_00 = 3;
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

    param0->unk_6C = 0;
    param0->unk_00 = 17;

    return 0;
}

static int SlotMachine_State_BonusWait(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        SlotMachine_SetReelAnim(param0, 3);
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
        param0->unk_00 = 18;
    }

    return 0;
}

static int SlotMachine_State_WaitBonus(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 1) {
        param0->unk_00 = 23;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_BonusPayout(SlotMachineContext *param0)
{
    param0->unk_64 = SlotMachine_GetPayoutAmount(param0);
    param0->unk_6C = 0;
    param0->unk_00 = 20;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_ChooseBonus(param0);
    SlotMachine_ChooseBonusMultiplier(param0);
    SlotMachine_SetReelAnim(param0, 11);

    return 0;
}

static int SlotMachine_State_WaitBonusPayout(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C == (FX32_ONE * 30)) {
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
        SlotMachine_SetReelAnim(param0, 3);
    } else if (param0->unk_6C >= (FX32_ONE * 30)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            param0->unk_6C = 0;
            param0->unk_00 = 23;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_BonusEnd(SlotMachineContext *param0)
{
    param0->unk_6C = 0;
    param0->unk_00 = 22;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 11);
    SlotMachine_ChooseBonus(param0);
    SlotMachine_ChooseBonusMultiplier(param0);

    return 0;
}

static int SlotMachine_State_WaitBonusEnd(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C == (FX32_ONE * 8)) {
        SlotMachine_SetReelAnim(param0, 3);
        SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_01);
    } else if (param0->unk_6C >= (FX32_ONE * 8)) {
        if ((SlotMachine_IsPayoutAnimDone(param0) == 1) && (SlotMachine_IsReelAnimDone(param0) == 1)) {
            param0->unk_6C = 0;
            param0->unk_00 = 24;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_CheckBonus(SlotMachineContext *param0)
{
    GF_ASSERT(param0->unk_50 < SlotMachineBonusType_06);
    param0->unk_00 = 25;
    return 1;
}

static int SlotMachine_State_CheckBonus2(SlotMachineContext *param0)
{
    GF_ASSERT(param0->unk_50 < SlotMachineBonusType_06);
    param0->unk_00 = 28;

    return 1;
}

static int SlotMachine_State_InitDoubleUp(SlotMachineContext *param0)
{
    param0->unk_64 = 0;
    param0->unk_68 = 0;
    param0->unk_00 = 26;
    param0->unk_74 = 0;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 7);

    if (param0->unk_60 == 0) {
        param0->unk_00 = 60;
        param0->unk_04 = 63;
    } else if (param0->unk_60 < 3) {
        param0->unk_00 = 59;
        param0->unk_04 = 63;
    } else if (param0->unk_60 >= 50000) {
        param0->unk_00 = 61;
        param0->unk_04 = 26;
    }

    return 1;
}

static int SlotMachine_State_DoubleUpInsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->unk_00 = 63;
        SlotMachine_FinishPayoutAnim(param0);
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->unk_60 -= 3;
        param0->unk_45C += 3;
        param0->unk_00 = 27;

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
        param0->unk_60 += 3;
        param0->unk_00 = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->unk_00 = 28;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartDoubleUp(SlotMachineContext *param0)
{
    SlotMachine_GenerateDoubleUpSymbols(param0);

    param0->unk_460++;
    param0->unk_468++;
    param0->unk_70 = 0;

    if (param0->unk_74 & ((1 << 0) | (1 << 1) | (1 << 4) | (1 << 5))) {
        param0->unk_70 = 1;
    }

    param0->unk_30 = 0;

    if (param0->unk_74 != 0) {
        param0->unk_30 = 1;
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

    param0->unk_7C[0] = 1;
    param0->unk_7C[1] = 1;
    param0->unk_7C[2] = 1;
    param0->unk_6C = 0;
    param0->unk_00 = 29;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    return 1;
}

static int SlotMachine_State_DoubleUpSpinDelay(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        param0->unk_6C = 0;
        param0->unk_00 = 30;

        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpStopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->unk_7C[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->unk_7C[0] = 2;

        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->unk_7C[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->unk_7C[1] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    } else if ((param0->unk_7C[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->unk_7C[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder(param0) == 0) {
            param0->unk_70 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SEQ_SE_DP_UG_022_sseq);
    }

    if ((param0->unk_7C[0] == 2) && (param0->unk_7C[1] == 2) && (param0->unk_7C[2] == 2)) {
        param0->unk_00 = 31;
    }

    return 0;
}

static int SlotMachine_State_WaitDoubleUpReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->unk_00 = 32;
    return 1;
}

static int SlotMachine_State_EvaluateDoubleUp(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLines(param0, param0->unk_74, &param0->unk_48);

    param0->unk_44 = v0;

    if (v0 == 6) {
        param0->unk_00 = 33;
        return 1;
    }

    if (param0->unk_74 & ((1 << 8) | (1 << 9))) {
        param0->unk_00 = 39;
        return 1;
    }

    if (v0 == 2) {
        param0->unk_00 = 37;
        return 1;
    }

    param0->unk_00 = 35;
    return 1;
}

static int SlotMachine_State_DoubleUpWin(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 7);

    param0->unk_6C = 0;
    param0->unk_00 = 34;

    return 1;
}

static int SlotMachine_State_WaitDoubleUpWin(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        param0->unk_6C = 0;
        param0->unk_00 = 25;

        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpLose(SlotMachineContext *param0)
{
    param0->unk_64 = SlotMachine_GetPayoutAmount(param0);
    param0->unk_458 += param0->unk_64;
    param0->unk_6C = 0;
    param0->unk_00 = 36;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    return 0;
}

static int SlotMachine_State_WaitDoubleUpLose(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
        SlotMachine_SetReelAnim(param0, 7);
        param0->unk_00 = 25;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_DoubleUpRetry(SlotMachineContext *param0)
{
    param0->unk_64 = 0;
    param0->unk_6C = 0;
    param0->unk_00 = 38;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    return 0;
}

static int SlotMachine_State_WaitDoubleUpRetry(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C > (FX32_ONE * 15)) {
        if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
            SlotMachine_SetReelAnim(param0, 7);
            SlotMachine_ResetReelPalettes(param0);

            param0->unk_6C = 0;
            param0->unk_00 = 28;

            return 1;
        }
    }

    return 0;
}

static int SlotMachine_State_Jackpot(SlotMachineContext *param0)
{
    param0->unk_64 = SlotMachine_GetPayoutAmount(param0);
    param0->unk_458 += param0->unk_64;
    param0->unk_6C = 0;
    param0->unk_00 = 40;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);
    SlotMachine_StartFadeInTask(param0);
    SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_02);

    param0->unk_454 = SlotMachine_CreateJackpot(param0);

    return 0;
}

static int SlotMachine_State_WaitJackpot(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 1) {
        OverworldAnimManager_Finish(param0->unk_454);
        SlotMachine_SetReelAnim(param0, 7);
        param0->unk_00 = 41;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_InitPayout(SlotMachineContext *param0)
{
    SlotMachine_CreateReelSprites(param0);

    param0->unk_1C = 0;
    param0->unk_14 = 0;
    param0->unk_08 = 1;
    param0->unk_00 = 42;

    return 1;
}

static int SlotMachine_State_CountPayout(SlotMachineContext *param0)
{
    param0->unk_0C++;
    param0->unk_1C++;

    if (param0->unk_1C > 999) {
        param0->unk_1C = 999;
    }

    SlotMachine_CreateNumber2(param0, param0->unk_1C);

    param0->unk_10 = 15 + 1;
    param0->unk_08 = 1;
    param0->unk_24 = 0;
    param0->unk_28 = 0;
    param0->unk_2C = 0;

    if (SlotMachine_RollPayout(param0) == 0) {
        param0->unk_2C = 1;
    }

    param0->unk_00 = 43;
    return 1;
}

static int SlotMachine_State_NextPayout(SlotMachineContext *param0)
{
    param0->unk_10--;
    GF_ASSERT((int)param0->unk_10 >= 1);

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_CreatePayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 7);

    param0->unk_00 = 44;

    if (param0->unk_60 == 0) {
        param0->unk_00 = 60;
        param0->unk_04 = 63;
    } else if (param0->unk_60 < 1) {
        param0->unk_00 = 60;
        param0->unk_04 = 63;
    } else if (param0->unk_60 >= 50000) {
        param0->unk_00 = 61;
        param0->unk_04 = 44;
    }

    return 1;
}

static int SlotMachine_State_PayoutInsertCoin(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_START) != 0) {
        param0->unk_00 = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_BUTTON_X) != 0) {
        param0->unk_60 -= 1;
        param0->unk_14 -= 1;
        param0->unk_45C += 1;

        if ((int)param0->unk_14 < 0) {
            param0->unk_14 = 0;
        }

        param0->unk_00 = 45;

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
        param0->unk_60 += 1;
        param0->unk_00 = 63;
        return 0;
    }

    if (SlotMachine_GetPressedKey(PAD_KEY_DOWN | PAD_BUTTON_X) != 0) {
        param0->unk_00 = 46;
        return 1;
    }

    return 0;
}

static int SlotMachine_State_StartPayout(SlotMachineContext *param0)
{
    param0->unk_460++;
    param0->unk_46C++;
    param0->unk_74 = (1 << 0);
    param0->unk_30 = 1;
    param0->unk_70 = 1;

    SlotMachine_ClearReelHighlight(param0, 0);
    SlotMachine_ClearReelHighlight(param0, 1);
    SlotMachine_ClearReelHighlight(param0, 2);
    SlotMachine_SetReelPaletteBlend2(param0, SlotMachinePaletteIndex_00);

    SlotMachine_ReelTask_Start(param0, 0);
    SlotMachine_ReelTask_Start(param0, 1);
    SlotMachine_ReelTask_Start(param0, 2);
    SlotMachine_ClearButtonInputs(param0);
    SlotMachine_RandomButtonOrder(param0);

    param0->unk_7C[0] = 1;
    param0->unk_7C[1] = 1;
    param0->unk_7C[2] = 1;
    param0->unk_6C = 0;
    param0->unk_00 = 47;

    Sound_PlayEffect(SEQ_SE_DP_OPEN2_sseq);

    if ((param0->unk_24 == 0) && (param0->unk_28 == 0)) {
        if (SlotMachine_RollDoubleUpLose(param0) == 1) {
            param0->unk_28 = 1;
            param0->unk_4C0++;
        }

        if (param0->unk_28 == 1) {
            SlotMachine_StartFlashTask(param0, 1);
        }
    }

    if ((param0->unk_24 == 0) && (param0->unk_28 == 0)) {
        if (SlotMachine_RollDoubleUpWin(param0) == 1) {
            param0->unk_24 = 1;
            param0->unk_4BC++;
        }

        if (param0->unk_24 == 1) {
            SlotMachine_StartFlashTask(param0, 0);
        }
    }

    return 1;
}

static int SlotMachine_State_PayoutSpinDelay(SlotMachineContext *param0)
{
    param0->unk_6C += FX32_ONE;

    if (param0->unk_6C >= (FX32_ONE * 8)) {
        param0->unk_6C = 0;
        param0->unk_00 = 48;
        SlotMachine_SetReelAnim(param0, 6);
        return 1;
    }

    return 0;
}

static int SlotMachine_State_PayoutStopReels(SlotMachineContext *param0)
{
    u32 v0 = gSystem.pressedKeys;

    if ((param0->unk_7C[0] == 1) && (v0 & PAD_BUTTON_Y)) {
        param0->unk_7C[0] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_Y);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->unk_70 = 0;
            param0->unk_30 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 0);
        SlotMachine_ReelTask_Stop(param0, 0);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    } else if ((param0->unk_7C[1] == 1) && (v0 & PAD_BUTTON_B)) {
        param0->unk_7C[1] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_B);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->unk_70 = 0;
            param0->unk_30 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 1);
        SlotMachine_ReelTask_Stop(param0, 1);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    } else if ((param0->unk_7C[2] == 1) && (v0 & PAD_BUTTON_A)) {
        param0->unk_7C[2] = 2;
        SlotMachine_RecordButtonInput(param0, PAD_BUTTON_A);

        if (SlotMachine_CheckButtonOrder2(param0) == 0) {
            param0->unk_70 = 0;
            param0->unk_30 = 0;
        }

        SlotMachine_SetReelHighlight(param0, 2);
        SlotMachine_ReelTask_Stop(param0, 2);
        Sound_PlayEffect(SE_CONFIRM_sseq_6);
    }

    if ((param0->unk_7C[0] == 2) && (param0->unk_7C[1] == 2) && (param0->unk_7C[2] == 2)) {
        param0->unk_00 = 49;
    }

    return 0;
}

static int SlotMachine_State_WaitPayoutReelsStop(SlotMachineContext *param0)
{
    if ((SlotMachine_ReelTask_IsDone(param0, 0) == 1) || (SlotMachine_ReelTask_IsDone(param0, 1) == 1) || (SlotMachine_ReelTask_IsDone(param0, 2) == 1)) {
        return 0;
    }

    SlotMachine_ResetReelPalettes(param0);
    param0->unk_00 = 50;
    return 1;
}

static int SlotMachine_State_EvaluatePayout(SlotMachineContext *param0)
{
    SlotMachineSymbol v0 = SlotMachine_EvaluateLine2(param0, param0->unk_74, &param0->unk_48);

    param0->unk_44 = v0;

    if (v0 == 6) {
        if (param0->unk_28 == 1) {
            param0->unk_28 = 3;
        }

        param0->unk_00 = 51;
        return 1;
    }

    if (param0->unk_28 == 1) {
        param0->unk_28 = 2;
    }

    param0->unk_00 = 52;

    return 1;
}

static int SlotMachine_State_PayoutResult(SlotMachineContext *param0)
{
    SlotMachine_ResetReelPalettes(param0);
    SlotMachine_SetReelAnim(param0, 7);

    if ((int)param0->unk_10 <= 1) {
        param0->unk_00 = 54;
    } else {
        param0->unk_00 = 43;
    }

    return 0;
}

static int SlotMachine_State_PayoutWin(SlotMachineContext *param0)
{
    param0->unk_64 = sSlotMachinePayoutPerLine2[param0->unk_44];
    param0->unk_458 += param0->unk_64;

    SlotMachine_StartPayoutAnim(param0);
    SlotMachine_SetReelAnim(param0, 10);

    param0->unk_6C = 0;
    param0->unk_00 = 53;

    return 0;
}

static int SlotMachine_State_WaitPayoutWin(SlotMachineContext *param0)
{
    if (SlotMachine_IsPayoutAnimDone(param0) == 0) {
        return 0;
    }

    SlotMachine_SetReelAnim(param0, 7);

    if ((int)param0->unk_10 <= 1) {
        param0->unk_00 = 54;
    } else {
        param0->unk_00 = 43;
    }

    return 1;
}

static int SlotMachine_State_EndPayout(SlotMachineContext *param0)
{
    param0->unk_10--;
    GF_ASSERT(param0->unk_10 == 0);

    if ((param0->unk_2C == 1) && (param0->unk_24 == 0)) {
        SlotMachine_SetReelAnim(param0, 8);
        param0->unk_00 = 58;
        return 0;
    }

    param0->unk_00 = 55;
    return 1;
}

static int SlotMachine_State_CheckPayout(SlotMachineContext *param0)
{
    SlotMachinePayoutResultEnum v0;

    SlotMachine_AdjustPayout(param0);
    v0 = SlotMachine_GetPayoutResult(param0);

    if (param0->unk_24 == 1) {
        v0 = SlotMachinePayoutResultEnum_02;
    }

    if (v0 == SlotMachinePayoutResultEnum_02) {
        SlotMachine_SetReelAnim(param0, 5);
        param0->unk_00 = 56;
        return 0;
    }

    if (v0 == SlotMachinePayoutResultEnum_01) {
        SlotMachine_SetReelAnim(param0, 12);
        param0->unk_00 = 57;
        return 0;
    }

    Sound_PlayPokemonCry(SPECIES_CLEFAIRY, 0);
    param0->unk_00 = 42;
    return 0;
}

static int SlotMachine_State_WaitPayoutAnim(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    param0->unk_00 = 42;
    return 1;
}

static int SlotMachine_State_WaitPayoutAnim2(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    param0->unk_00 = 42;
    return 1;
}

static int SlotMachine_State_Finish(SlotMachineContext *param0)
{
    if (SlotMachine_IsReelAnimDone(param0) == 0) {
        return 0;
    }

    if (param0->unk_1C > param0->unk_20) {
        param0->unk_20 = param0->unk_1C;
    }

    SlotMachine_SetBgmMode(param0, SlotMachineBgmMode_00);
    SlotMachine_StartFadeOutTask(param0);
    param0->unk_00 = 0;

    return 1;
}

static int SlotMachine_State_ShowMessage0(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 0);
    param0->unk_00 = 62;
    return 0;
}

static int SlotMachine_State_ShowMessage2(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 2);
    param0->unk_00 = 62;
    return 0;
}

static int SlotMachine_State_ShowMessage1(SlotMachineContext *param0)
{
    SlotMachine_ShowMessage(param0, 1);
    param0->unk_00 = 62;
    return 0;
}

static int SlotMachine_State_WaitMessage(SlotMachineContext *param0)
{
    if (SlotMachine_GetPressedKey(PAD_BUTTON_A | PAD_BUTTON_B)) {
        SlotMachine_HideMessage(param0);
        param0->unk_00 = param0->unk_04;
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
    SlotMachineReelTask *v1 = param0->unk_B4;

    do {
        v1->unk_00 = 0;
        v1->unk_10 = v0;
        v1->unk_20 = param0;
        v1->unk_1C = SysTask_Start(SlotMachine_ReelTask, &param0->unk_B4[v0], 129 + v0);
        v1++;
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_StopReelTasks(SlotMachineContext *param0)
{
    u32 v0 = 0;

    do {
        SysTask_Done(param0->unk_B4[v0].unk_1C);
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_ReelTask_Start(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    param0->unk_B4[param1].unk_00 = 1;
    param0->unk_B4[param1].unk_04 = 1;
}

static void SlotMachine_ReelTask_Stop(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    param0->unk_B4[param1].unk_00 = 2;
}

static int SlotMachine_ReelTask_IsDone(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    return param0->unk_B4[param1].unk_04;
}

static void SlotMachine_ReelTask(SysTask *param0, void *param1)
{
    SlotMachineReelTask *v0 = param1;
    SlotMachineContext *v1 = v0->unk_20;

    while (sSlotMachineReelTaskFuncs[v0->unk_00](v0, v1) == 1) {
        (void)0;
    }
}

static int SlotMachine_ReelTask_Noop(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    return 0;
}

static int SlotMachine_ReelTask_Update(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachine_AdvanceReel(param1, param0->unk_10, param1->unk_8C);
    return 0;
}

static int SlotMachine_ReelTask_Advance(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    param0->unk_00++;
    param0->unk_14 = 0;
    param0->unk_18 = 0;

    if (param1->unk_30 == 1) {
        if (param1->unk_08 == 0) {
            if (SlotMachine_ReelTask_Spin(param0, param1) == 0) {
                SlotMachine_ChooseStopPositionA(param0, param1);
                param1->unk_30 = 0;
            }
        } else {
            if (SlotMachine_ReelTask_Spin2(param0, param1) == 0) {
                SlotMachine_ChooseStopPositionB(param0, param1);
                param1->unk_30 = 0;
            }
        }
    } else {
        if (param1->unk_08 == 0) {
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
    int v2 = param0->unk_10;
    int v3 = 0;

    v0 = param1->unk_90[v2] % (FX32_ONE * 32);

    if (v0) {
        v3 = 1;
        v1 = param1->unk_8C;

        if (v0 < v1) {
            v1 = v0;
        }

        v0 = SlotMachine_AdvanceReelToStop(param1, v2, v1);
    } else if (param0->unk_18) {
        v3 = 1;
        param0->unk_18--;
        SlotMachine_AdvanceReel(param1, v2, param1->unk_8C);
        v0 = param1->unk_90[v2] % (FX32_ONE * 32);
    }

    if ((v0 == 0) && (param0->unk_18 == 0)) {
        fx32 v4[5] = { (FX32_ONE * 4), (FX32_ONE * 8), (FX32_ONE * 8), (FX32_ONE * 8), (FX32_ONE * 16) };
        s32 v5 = param0->unk_18;

        if (v5 > 4) {
            v5 = 4;
        }

        param0->unk_08 = v4[v5];
        param0->unk_0C = 0;
        param0->unk_00++;

        if (v3 == 0) {
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_ReelTask_Bounce(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    int v0 = param0->unk_10;

    param1->unk_9C[v0] = param0->unk_08;
    param0->unk_08 = -param0->unk_08;
    param0->unk_0C++;

    if ((param0->unk_0C & 0x1) == 0) {
        param0->unk_08 >>= 2;
    }

    if (param0->unk_08 == 0) {
        param0->unk_00 = 0;
        param0->unk_04 = 0;
        param1->unk_9C[v0] = 0;
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
    if (param1->unk_74 == 0) {
        return 0;
    }

    switch (param0->unk_10) {
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
    if (param1->unk_74 == 0) {
        return 0;
    }

    {
        SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->unk_74);
        return SlotMachine_FindStopPositionE(param0, param1, v0);
    }
}

static int SlotMachine_ReelTask_Stop0(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->unk_74);

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
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->unk_74);

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
    SlotMachineSymbol v0 = SlotMachine_GetSymbolFromMask(param1->unk_74);

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
    int v5 = param0->unk_10;

    for (v0 = 1; v0 <= 3; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v5, v0) == param2) {
            for (v1 = 0; (v0 + v1) <= 3; v1++) {
                if (SlotMachine_IsSymbolMatch(param1, v1, param2) == 1) {
                    param0->unk_14 = v0 + v1;
                    param0->unk_18 = v1;
                    return 1;
                }
            }
        }
    }

    v2 = 4;

    if (param1->unk_70 == 1) {
        v2 = 21;
    }

    v4 = (int)param1->unk_A8[0];

    for (v0 = 1; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v5, 1 - v0) == param2) {
            for (v1 = 0; v1 < 3; v1++) {
                if (SlotMachine_IsSymbolMatch(param1, v0 + v1, param2) == 1) {
                    if (v1 == 0) {
                        v3 = v4 % 4;

                        if ((v3 == 0) && (SlotMachine_IsSymbolMatch(param1, v0 + 2, param2) == 1)) {
                            param0->unk_14 = 3;
                            param0->unk_18 = v0 + 2;
                            return 1;
                        }
                    } else if (v1 == 1) {
                        v3 = v4 % 6;

                        if ((v3 < 2) && (SlotMachine_IsSymbolMatch(param1, v0 + 2, param2) == 1)) {
                            param0->unk_14 = 3;
                            param0->unk_18 = v0 + 2;
                            return 1;
                        }
                    }

                    param0->unk_14 = 1 + v1;
                    param0->unk_18 = v0 + v1;
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
    int v6 = param0->unk_10;

    if (SlotMachine_GetStopCandidates(param0, param1, &v2, &v3, &v4) == 0) {
        return 0;
    }

    if (SlotMachine_IsSymbolMatch(param1, 0, param2) == 1) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2) == param2) {
            param0->unk_14 = v2;
            param0->unk_18 = 0;
            return 1;
        }

        if ((v3 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v6, v3) == param2)) {
            param0->unk_14 = v3;
            param0->unk_18 = 0;
            return 1;
        }

        if ((v4 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v6, v4) == param2)) {
            param0->unk_14 = v4;
            param0->unk_18 = 0;
            return 1;
        }
    }

    v5 = 4;

    if (param1->unk_70 == 1) {
        v5 = 21;
    }

    if (v3 == 0) {
        for (v0 = 1; v0 <= v5; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v2;
                    param0->unk_18 = v0;
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
                        param0->unk_14 = v2;
                        param0->unk_18 = v0;
                        return 1;
                    }
                }

                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->unk_14 = v3;
                        param0->unk_18 = v0;
                        return 1;
                    }
                }
            } else {
                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->unk_14 = v3;
                        param0->unk_18 = v0;
                        return 1;
                    }
                }

                if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                    if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                        param0->unk_14 = v2;
                        param0->unk_18 = v0;
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
                    param0->unk_14 = v2;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v3;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v4 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v4;
                    param0->unk_18 = v0;
                    return 1;
                }
            }
        } else if (v7 == 1) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v3;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v2;
                    param0->unk_18 = v0;
                    return 1;
                }
            }
        } else {
            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v4 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v4;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v2 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v2;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            if (SlotMachine_GetVisibleReelSymbol(param1, v6, v3 - v0) == param2) {
                if (SlotMachine_IsSymbolMatch(param1, v0, param2) == 1) {
                    param0->unk_14 = v3;
                    param0->unk_18 = v0;
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
    int v3 = param0->unk_10;

    for (v0 = 1; v0 <= 3; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, v0) == param2) {
            param0->unk_14 = v0;
            param0->unk_18 = 0;
            return 1;
        }
    }

    v2 = 4;

    if (param1->unk_70 == 1) {
        v2 = 21;
    }

    for (v0 = 1; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, 1 - v0) == param2) {
            v1 = v0 % 4;

            if (v1 == 1) {
                param0->unk_14 = 3;
                param0->unk_18 = v0 + 2;
                return 1;
            }

            if ((v1 == 2) || (v1 == 3)) {
                param0->unk_14 = 2;
                param0->unk_18 = v0 + 1;
                return 1;
            }

            param0->unk_14 = 1;
            param0->unk_18 = v0;
            return 1;
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionD(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2, v3, v4, v5, v6 = 4, v7 = param0->unk_10;

    if (SlotMachine_GetStopCandidates(param0, param1, &v3, &v4, &v5) == 0) {
        return 0;
    }

    if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3) == param2) {
        param0->unk_14 = v3;
        param0->unk_18 = 0;
        return 1;
    }

    if ((v4 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v7, v4) == param2)) {
        param0->unk_14 = v4;
        param0->unk_18 = 0;
        return 1;
    }

    if ((v5 != 0) && (SlotMachine_GetVisibleReelSymbol(param1, v7, v5) == param2)) {
        param0->unk_14 = v5;
        param0->unk_18 = 0;
        return 1;
    }

    v6 = 4;

    if (param1->unk_70 == 1) {
        v6 = 21;
    }

    if (v4 == 0) {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->unk_14 = v3;
                param0->unk_18 = v0;
                return 1;
            }
        }

        return 0;
    }

    v2 = (int)param1->unk_A8[v7];

    if (v5 == 0) {
        if (v2 & 0x1) {
            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                    param0->unk_14 = v3;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                    param0->unk_14 = v4;
                    param0->unk_18 = v0;
                    return 1;
                }
            }
        } else {
            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                    param0->unk_14 = v4;
                    param0->unk_18 = v0;
                    return 1;
                }
            }

            for (v0 = 1; v0 <= v6; v0++) {
                if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                    param0->unk_14 = v3;
                    param0->unk_18 = v0;
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
                param0->unk_14 = v3;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->unk_14 = v4;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->unk_14 = v5;
                param0->unk_18 = v0;
                return 1;
            }
        }
    } else if (v2 == 1) {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->unk_14 = v4;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->unk_14 = v5;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->unk_14 = v3;
                param0->unk_18 = v0;
                return 1;
            }
        }
    } else {
        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v5 - v0) == param2) {
                param0->unk_14 = v5;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v3 - v0) == param2) {
                param0->unk_14 = v3;
                param0->unk_18 = v0;
                return 1;
            }
        }

        for (v0 = 1; v0 <= v6; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, v7, v4 - v0) == param2) {
                param0->unk_14 = v4;
                param0->unk_18 = v0;
                return 1;
            }
        }
    }

    return 0;
}

static int SlotMachine_FindStopPositionE(SlotMachineReelTask *param0, SlotMachineContext *param1, SlotMachineSymbol param2)
{
    int v0, v1, v2;
    int v3 = param0->unk_10;

    v2 = 4;

    if (param1->unk_70 == 1) {
        v2 = 21;
    }

    for (v0 = 0; v0 <= v2; v0++) {
        if (SlotMachine_GetVisibleReelSymbol(param1, v3, 2 - v0) == param2) {
            param0->unk_14 = 2;
            param0->unk_18 = v0;
            return 1;
        }
    }

    return 0;
}

static void SlotMachine_ChooseStopPositionA(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    int v0, v1;

    v1 = SlotMachine_CountStoppedReels(param1);

    if ((param0->unk_10 != 0) && (v1 < 2)) {
        return;
    }

    if ((param0->unk_10 == 0) && (v1 < 2)) {
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_IsSymbolOnLine(param1, v0) == 0) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    }

    switch (param0->unk_10) {
    case 0:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine0(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 1:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine1(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);

        break;
    case 2:
        for (v0 = 1; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine2(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
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

    if ((param0->unk_10 != 0) && (v1 < 2)) {
        return;
    }

    if ((param0->unk_10 == 0) && (v1 < 2)) {
        for (v0 = 0; v0 < 21; v0++) {
            if (SlotMachine_GetVisibleReelSymbol(param1, 0, 2 - v0) != 3) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
    }

    switch (param0->unk_10) {
    case 0:
        for (v0 = 0; v0 < 21; v0++) {
            if (SlotMachine_CheckLine3(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 1:
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine4(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
                return;
            }
        }

        GF_ASSERT(FALSE);
        return;
    case 2:
        for (v0 = 0; v0 <= 21; v0++) {
            if (SlotMachine_CheckLine5(param0, param1, v0) == 0) {
                param0->unk_18 = v0;
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
        if (param0->unk_7C[v0] != 1) {
            v1++;
        }

        v0++;
    } while (v0 < 3);

    return v1;
}

static int SlotMachine_CanStopReel(SlotMachineReelTask *param0, SlotMachineContext *param1)
{
    switch (param0->unk_10) {
    case 0:
        if ((param1->unk_7C[1] != 1) || (param1->unk_7C[2] != 1)) {
            return 0;
        }

        break;
    case 1:
        if ((param1->unk_7C[0] != 1) || (param1->unk_7C[2] != 1)) {
            return 0;
        }

        break;
    case 2:
        if ((param1->unk_7C[0] != 1) || (param1->unk_7C[1] != 1)) {
            return 0;
        }

        break;
    }

    return 1;
}

static int SlotMachine_GetStopCandidates(SlotMachineReelTask *param0, SlotMachineContext *param1, int *param2, int *param3, int *param4)
{
    SlotMachineReelButtonState v0 = param1->unk_7C[0];
    SlotMachineReelButtonState v1 = param1->unk_7C[1];
    SlotMachineReelButtonState v2 = param1->unk_7C[2];
    SlotMachineReelTask *v3 = &param1->unk_B4[0];
    SlotMachineReelTask *v4 = &param1->unk_B4[1];
    SlotMachineReelTask *v5 = &param1->unk_B4[2];
    int v6 = v3->unk_14;
    int v7 = v4->unk_14;
    int v8 = v5->unk_14;

    *param2 = 0;
    *param3 = 0;
    *param4 = 0;

    switch (param0->unk_10) {
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
    int v3 = param1->unk_B4[1].unk_18;
    int v4 = param1->unk_B4[2].unk_18;

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
    int v3 = param1->unk_B4[0].unk_18;
    int v4 = param1->unk_B4[2].unk_18;

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
    int v3 = param1->unk_B4[0].unk_18;
    int v4 = param1->unk_B4[1].unk_18;

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
    int v3 = param1->unk_B4[1].unk_18;
    int v4 = param1->unk_B4[2].unk_18;

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
    int v3 = param1->unk_B4[0].unk_18;
    int v4 = param1->unk_B4[2].unk_18;

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
    int v3 = param1->unk_B4[0].unk_18;
    int v4 = param1->unk_B4[1].unk_18;

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
    param0->unk_90[param1] += param2;
    param0->unk_90[param1] %= (FX32_ONE * (21 * 32));
    param0->unk_A8[param1] = 21 - (((param0->unk_90[param1]) / FX32_ONE) / 32);
}

static fx32 SlotMachine_AdvanceReelToStop(SlotMachineContext *param0, SlotMachineReelIndex param1, fx32 param2)
{
    fx32 v0;

    v0 = param0->unk_90[param1] % (FX32_ONE * 32);

    if (v0) {
        if (v0 < param2) {
            param2 = v0;
        }

        SlotMachine_AdvanceReel(param0, param1, param2);
        v0 = param0->unk_90[param1] % (FX32_ONE * 32);
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
    u32 v1 = sSlotMachineSymbolChance[param0->unk_88];

    if (v1 > v0) {
        return 1;
    }

    return 0;
}

static int SlotMachine_GenerateSymbols(SlotMachineContext *param0)
{
    param0->unk_74 = 0;

    if (SlotMachine_RollSymbol(param0) == 1) {
        u32 v0 = SlotMachine_Random100(param0);
        const SlotMachineSymbolWeights *v1 = &sSlotMachineSymbolWeights[param0->unk_88];

        param0->unk_470++;

        if (SlotMachine_ConsumeRandom(v1->unk_00.unk_00, &v0)) {
            param0->unk_74 |= (1 << 3);
            param0->unk_4A0++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_00.unk_02, &v0)) {
            param0->unk_74 |= (1 << 2);
            param0->unk_49C++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_04.unk_00, &v0)) {
            param0->unk_74 |= (1 << 7);
            param0->unk_4B0++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_04.unk_02, &v0)) {
            param0->unk_74 |= (1 << 6);
            param0->unk_4AC++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_08.unk_00, &v0)) {
            param0->unk_74 |= (1 << 5);
            param0->unk_4A8++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_08.unk_02, &v0)) {
            param0->unk_74 |= (1 << 4);
            param0->unk_4A4++;
            return 1;
        }

        if (SlotMachine_ConsumeRandom(v1->unk_0C.unk_00, &v0)) {
            param0->unk_74 |= (1 << 1);
            param0->unk_498++;
            return 1;
        }

        param0->unk_74 |= (1 << 0);
        param0->unk_494++;

        return 1;
    }

    return 0;
}

static int SlotMachine_RollBonus(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineBonusChance[param0->unk_88];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static void SlotMachine_ChooseBonus(SlotMachineContext *param0)
{
    int v0;
    u32 v1 = SlotMachine_Random100(param0);
    const SlotMachineBonusEntry *v2 = sSlotMachineBonusTable[param0->unk_88];

    for (v0 = 0; v0 < SlotMachineBonusType_06; v0++) {
        if (SlotMachine_ConsumeRandom(v2[v0].unk_00, &v1) == 1) {
            param0->unk_50 = v2[v0].unk_04;
            param0->unk_4C = v2[v0].unk_08;
            param0->unk_18 = sSlotMachineBonusDuration[param0->unk_50];

            switch (param0->unk_4C) {
            case SlotMachineBonusKind_00:
                param0->unk_478++;
                break;
            case SlotMachineBonusKind_01:
                param0->unk_47C++;
                break;
            case SlotMachineBonusKind_02:
                param0->unk_480++;
                break;
            }

            return;
        }
    }

    v0--;

    param0->unk_50 = v2[v0].unk_04;
    param0->unk_4C = v2[v0].unk_08;
    param0->unk_18 = sSlotMachineBonusDuration[param0->unk_50];

    GF_ASSERT(FALSE);
}

static void SlotMachine_ChooseBonusMultiplier(SlotMachineContext *param0)
{
    u32 v0 = 0, v1 = SlotMachine_Random100(param0);
    const SlotMachineBonusMultiplier *v2 = sSlotMachineBonusMultiplierTable[param0->unk_88][param0->unk_4C];

    do {
        if (SlotMachine_ConsumeRandom(v2[v0].unk_00, &v1) == 1) {
            param0->unk_13C.unk_1C = v2[v0].unk_04;

            switch (param0->unk_13C.unk_1C) {
            case SlotMachineWinType_00:
                param0->unk_488++;
                break;
            case SlotMachineWinType_01:
                param0->unk_484++;
                break;
            case SlotMachineWinType_02:
                param0->unk_48C++;
                break;
            }

            return;
        }

        v0++;
    } while (v0 < SlotMachineWinType_03);

    param0->unk_13C.unk_1C = SlotMachineWinType_01;
    GF_ASSERT(FALSE);
}

static int SlotMachine_RollDoubleUp(SlotMachineContext *param0)
{
    u32 v0 = sSlotMachineDoubleUpChance[param0->unk_88];
    u32 v1 = SlotMachine_Random100(param0);

    if (v1 < v0) {
        return 1;
    }

    return 0;
}

static void SlotMachine_GenerateDoubleUpSymbols(SlotMachineContext *param0)
{
    u32 v0;
    const u32 *v1 = sSlotMachineDoubleUpWeights[param0->unk_88];
    u32 v2 = SlotMachine_Random100(param0);

    param0->unk_74 = 0;

    if (SlotMachine_RollDoubleUp(param0) == 0) {
        param0->unk_474++;

        switch (param0->unk_50) {
        case SlotMachineBonusType_00:
        case SlotMachineBonusType_01:
        case SlotMachineBonusType_02:
            param0->unk_74 |= (1 << 9);
            param0->unk_4B8++;
            return;
        case SlotMachineBonusType_03:
        case SlotMachineBonusType_04:
        case SlotMachineBonusType_05:
            param0->unk_74 |= (1 << 8);
            param0->unk_4B4++;
            return;
        }

        GF_ASSERT(FALSE);
        param0->unk_74 |= (1 << 9);
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[0], &v2) == 1) {
        param0->unk_74 |= (1 << 2);
        param0->unk_49C++;
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[1], &v2) == 1) {
        param0->unk_74 |= (1 << 6);
        param0->unk_4AC++;
        return;
    }

    if (SlotMachine_ConsumeRandom(v1[1], &v2) == 1) {
        param0->unk_74 |= (1 << 4);
        param0->unk_4A4++;
        return;
    }

    param0->unk_74 = (1 << 0);
    param0->unk_494++;
}

static int SlotMachine_RollDoubleUpWin(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineDoubleUpWinChance[param0->unk_88];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static int SlotMachine_RollDoubleUpLose(SlotMachineContext *param0)
{
    u32 v0 = SlotMachine_Random100(param0);
    u32 v1 = sSlotMachineDoubleUpLoseChance[param0->unk_88];

    if (v0 < v1) {
        return 1;
    }

    return 0;
}

static int SlotMachine_RollPayout(SlotMachineContext *param0)
{
    u32 v0 = param0->unk_18;
    u32 v1 = SlotMachine_Random100(param0);

    if (v1 < v0) {
        return 1;
    }

    return 0;
}

static void SlotMachine_AdjustPayout(SlotMachineContext *param0)
{
    u32 v0 = param0->unk_18;
    u32 v1 = SlotMachine_Random100(param0);
    const u32 *v2 = sSlotMachinePayoutAdjust[param0->unk_88];

    if (param0->unk_28 == 2) {
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

    param0->unk_18 = v0;
}

static SlotMachinePayoutResultEnum SlotMachine_GetPayoutResult(SlotMachineContext *param0)
{
    int v0;
    u32 v1 = param0->unk_18;
    u32 v2 = SlotMachine_Random100(param0);
    const SlotMachinePayoutResult *v3 = sSlotMachinePayoutResultTable[param0->unk_88];

    for (v0 = 0; v0 < SlotMachinePayoutThreshold_09; v0++) {
        if (v1 >= v3[v0].unk_00) {
            if (SlotMachine_ConsumeRandom(v3[v0].unk_04, &v2) == 1) {
                return SlotMachinePayoutResultEnum_01;
            }

            if (SlotMachine_ConsumeRandom(v3[v0].unk_08, &v2) == 1) {
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
    param0->unk_34 = LCRNG_Next() % 6;
}

static void SlotMachine_StartPayoutTask(SlotMachineContext *param0)
{
    SlotMachinePayoutTask *v0 = &param0->unk_120;

    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_0C = param0;
    v0->unk_10 = SysTask_Start(SlotMachine_PayoutTask, v0, 138);
}

static void SlotMachine_StopPayoutTask(SlotMachineContext *param0)
{
    SysTask_Done(param0->unk_120.unk_10);
}

static void SlotMachine_StartPayoutAnim(SlotMachineContext *param0)
{
    param0->unk_120.unk_04 = 0;
    param0->unk_120.unk_08 = 0;
    param0->unk_120.unk_00 = 1;
}

static int SlotMachine_IsPayoutAnimDone(SlotMachineContext *param0)
{
    return param0->unk_120.unk_04;
}

static void SlotMachine_PayoutTask(SysTask *param0, void *param1)
{
    int v0;
    SlotMachinePayoutTask *v1 = param1;
    SlotMachineContext *v2 = v1->unk_0C;

    switch (v1->unk_00) {
    case 0:
        break;
    case 1:
        SlotMachine_CreatePayoutSprites(v1);
        v1->unk_00++;
        break;
    case 2:
        if (((v1->unk_14 != NULL) && (SlotMachine_IsPaletteAnimDone(v1->unk_14) != 1)) || ((v1->unk_18 != NULL) && (SlotMachine_IsPaletteAnimDone(v1->unk_18) != 1))) {
            break;
        }

        v1->unk_00++;
    case 3:
        if (SlotMachine_GetPressedKey(PAD_BUTTON_X) || (v2->unk_64 == 0)) {
            Sound_PlayEffect(SEQ_SE_DP_DENSI16_sseq);
            v2->unk_60 += v2->unk_64;

            if (v2->unk_60 >= 50000) {
                v2->unk_60 = 50000;
            }

            if (v2->unk_08 == 1) {
                v2->unk_14 += v2->unk_64;
            }

            v2->unk_64 = 0;

            if (v1->unk_14 != NULL) {
                OverworldAnimManager_Finish(v1->unk_14);
                v1->unk_14 = NULL;
            }

            if (v1->unk_18 != NULL) {
                OverworldAnimManager_Finish(v1->unk_18);
                v1->unk_18 = NULL;
            }

            v1->unk_04 = 1;
            v1->unk_00 = 0;

            return;
        }

        v0 = 0x3;

        if (gSystem.heldKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y)) {
            v0 = 0x1;
        }

        v1->unk_08++;

        if ((v1->unk_08 & v0) == 0) {
            v2->unk_64--;
            v2->unk_60++;

            if (v2->unk_60 >= 50000) {
                v2->unk_60 = 50000;
            }

            Sound_PlayEffect(SEQ_SE_DP_DENSI16_sseq);

            if (v2->unk_08 == 1) {
                v2->unk_14++;
            }
        }
    }
}

static void SlotMachine_CreatePayoutSprites(SlotMachinePayoutTask *param0)
{
    int v0;
    SlotMachineContext *v1 = param0->unk_0C;
    u32 v2 = v1->unk_48;

    GF_ASSERT(v2 != 0);

    for (v0 = 0; v0 < SlotMachinePaletteIndex_05; v0++, v2 >>= 1) {
        if (v2 & 0x1) {
            if (param0->unk_14 == NULL) {
                param0->unk_14 = SlotMachine_CreatePaletteAnim(v1, v0, v1->unk_64);
            } else if (param0->unk_18 == NULL) {
                param0->unk_18 = SlotMachine_CreatePaletteAnim(v1, v0, v1->unk_64);
            } else {
                GF_ASSERT(FALSE);
            }
        }
    }
}

static void SlotMachine_StartReelAnimTask(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->unk_13C;

    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_20 = param0;
    v0->unk_24 = SysTask_Start(SlotMachine_ReelAnimTask, v0, 132);
}

static void SlotMachine_StopReelAnimTask(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->unk_13C;
    SysTask_Done(v0->unk_24);
}

static void SlotMachine_SetReelAnim(SlotMachineContext *param0, u32 param1)
{
    SlotMachineReelAnimTask *v0 = &param0->unk_13C;

    v0->unk_00 = param1;
    v0->unk_04 = 0;
    v0->unk_08 = 0;
    v0->unk_10 = 0;
}

static int SlotMachine_IsReelAnimDone(SlotMachineContext *param0)
{
    SlotMachineReelAnimTask *v0 = &param0->unk_13C;
    return v0->unk_08;
}

static void SlotMachine_CreateReelSprites(SlotMachineContext *param0)
{
    param0->unk_13C.unk_0C = 0;
    param0->unk_13C.unk_38 = SlotMachine_CreateButton(param0);
    param0->unk_13C.unk_3C = SlotMachine_CreateButton3(param0);
    param0->unk_13C.unk_40 = SlotMachine_CreateCreditDigit(param0);
    param0->unk_13C.unk_44 = SlotMachine_CreatePayoutDigit(param0);
}

static void SlotMachine_FinishReelSprites(SlotMachineContext *param0)
{
    param0->unk_13C.unk_0C = 1;

    OverworldAnimManager_Finish(param0->unk_13C.unk_38);
    OverworldAnimManager_Finish(param0->unk_13C.unk_3C);
    OverworldAnimManager_Finish(param0->unk_13C.unk_40);
    OverworldAnimManager_Finish(param0->unk_13C.unk_44);
}

static void SlotMachine_ReelAnimTask(SysTask *param0, void *param1)
{
    int v0;
    SlotMachineReelAnimTask *v1 = param1;

    int (*const *v2)(SlotMachineReelAnimTask *);

    do {
        v2 = sSlotMachineReelAnimFuncs[v1->unk_00];
        v0 = v2[v1->unk_04](v1);
    } while (v0 == 1);
}

static int SlotMachine_ReelAnim_Create(SlotMachineReelAnimTask *param0)
{
    param0->unk_28 = SlotMachine_CreateReel(param0->unk_20, param0->unk_18);
    param0->unk_04++;

    return 0;
}

static int SlotMachine_ReelAnim_WaitCreate(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 0) {
        return 0;
    }

    SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_01);
    param0->unk_04++;

    return 0;
}

static int SlotMachine_ReelAnim_Finish(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 0) {
        return 0;
    }

    SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_05);
    param0->unk_08 = 1;
    param0->unk_04++;

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
    SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_04);
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitStop(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        OverworldAnimManager_Finish(param0->unk_28);
        param0->unk_08 = 1;
        param0->unk_04++;
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
    SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_02);
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitStart(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        param0->unk_2C = SlotMachine_CreateSymbol(param0->unk_20);
        param0->unk_30 = SlotMachine_CreateWinSymbol(param0->unk_20, param0->unk_1C);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_ShowResult(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_01);
        SlotMachine_SetReelVisible(param0->unk_28, 1);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitResult(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        OverworldAnimManager_Finish(param0->unk_2C);
        param0->unk_08 = 1;
        param0->unk_04++;
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
    param0->unk_2C = SlotMachine_CreateSymbol(param0->unk_20);
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_02);
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitHide(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        OverworldAnimManager_Finish(param0->unk_30);
        OverworldAnimManager_Finish(param0->unk_2C);
        SlotMachine_SetReelVisible(param0->unk_28, 0);
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_03);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Stop2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_04);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitStop2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        OverworldAnimManager_Finish(param0->unk_28);
        param0->unk_08 = 1;
        param0->unk_04++;
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
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_03);
    param0->unk_34 = SlotMachine_CreateBonus(param0->unk_20);
    param0->unk_10 = 0;
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitBonus(SlotMachineReelAnimTask *param0)
{
    param0->unk_10++;

    if (param0->unk_10 >= 48) {
        param0->unk_10 = 0;
        param0->unk_04++;
        Sound_PlayPokemonCry(SPECIES_CLEFAIRY, 0);
        SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_04);
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishBonus(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsBonusDone(param0->unk_34) == 1) {
        SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_03);
        OverworldAnimManager_Finish(param0->unk_34);
        param0->unk_04++;
        param0->unk_10 = 0;
        param0->unk_08 = 1;
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
    const SlotMachineButtonOrder *v0 = &sSlotMachineButtonOrder[param0->unk_20->unk_34];

    param0->unk_04++;
    param0->unk_14 = 0;

    SlotMachine_SetWinSymbolState(param0->unk_30, v0->unk_0C[param0->unk_14]);

    return 0;
}

static int SlotMachine_ReelAnim_UpdateButton(SlotMachineReelAnimTask *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->unk_20->unk_7C[v0] != 1) {
            v1++;
        }
    }

    if ((param0->unk_14 < 2) && (param0->unk_14 != v1)) {
        const SlotMachineButtonOrder *v2 = &sSlotMachineButtonOrder[param0->unk_20->unk_34];

        param0->unk_14 = v1;
        SlotMachine_SetWinSymbolState(param0->unk_30, v2->unk_0C[param0->unk_14]);
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
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_03);
    param0->unk_04++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Win[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Button2,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Jackpot(SlotMachineReelAnimTask *param0)
{
    SlotMachine_FinishReelSprites(param0->unk_20);
    param0->unk_2C = SlotMachine_CreateSymbol(param0->unk_20);
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_02);
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitJackpot(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        OverworldAnimManager_Finish(param0->unk_30);
        OverworldAnimManager_Finish(param0->unk_2C);
        SlotMachine_SetReelVisible(param0->unk_28, 0);
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_03);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Jackpot2(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        SlotMachine_CreateButton2(param0->unk_20);
        SlotMachine_CreateButton4(param0->unk_20);
        SlotMachine_CreateNumber(param0->unk_20, SlotMachineNumberType_00);
        SlotMachine_CreateNumber(param0->unk_20, SlotMachineNumberType_01);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_WaitJackpot2(SlotMachineReelAnimTask *param0)
{
    param0->unk_10++;

    if (param0->unk_10 >= 45) {
        param0->unk_10 = 0;
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_04);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishJackpot(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        OverworldAnimManager_Finish(param0->unk_28);
        param0->unk_08 = 1;
        param0->unk_04++;
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
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_04);
    param0->unk_08 = 1;
    param0->unk_04++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Win2[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Win,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Lose(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_08);
    param0->unk_08 = 1;
    param0->unk_04++;
    return 0;
}

static int (*const sSlotMachineReelAnim_Lose[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Lose,
    SlotMachine_ReelAnim_Noop,
};

static int SlotMachine_ReelAnim_Stop3(SlotMachineReelAnimTask *param0)
{
    SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_06);
    param0->unk_04++;
    param0->unk_08 = 1;
    return 0;
}

static int (*const sSlotMachineReelAnim_Stop3[])(SlotMachineReelAnimTask *) = {
    SlotMachine_ReelAnim_Stop3,
    SlotMachine_ReelAnim_Noop
};

static int SlotMachine_ReelAnim_Payout(SlotMachineReelAnimTask *param0)
{
    param0->unk_2C = SlotMachine_CreateSymbol(param0->unk_20);
    SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_02);
    param0->unk_0C = 1;
    param0->unk_04++;
    return 0;
}

static int SlotMachine_ReelAnim_WaitPayout(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        OverworldAnimManager_Finish(param0->unk_2C);
        OverworldAnimManager_Finish(param0->unk_30);
        SlotMachine_SetReelVisible(param0->unk_28, 0);
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_03);
        param0->unk_10 = 0;
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout2(SlotMachineReelAnimTask *param0)
{
    param0->unk_10++;

    if (param0->unk_10 >= 30) {
        param0->unk_10 = 0;
        param0->unk_04++;
        SlotMachine_SetReelState(param0->unk_28, SlotMachineReelStateEnum_02);
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout3(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsReelDone(param0->unk_28) == 1) {
        param0->unk_2C = SlotMachine_CreateSymbol(param0->unk_20);
        param0->unk_30 = SlotMachine_CreateWinSymbol(param0->unk_20, param0->unk_1C);
        param0->unk_0C = 0;
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_Payout4(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        SlotMachine_SetWinSymbolState(param0->unk_30, SlotMachineWinSymbolState_01);
        SlotMachine_SetReelVisible(param0->unk_28, 1);
        param0->unk_04++;
    }

    return 0;
}

static int SlotMachine_ReelAnim_FinishPayout(SlotMachineReelAnimTask *param0)
{
    if (SlotMachine_IsWinSymbolDone(param0->unk_30) == 1) {
        OverworldAnimManager_Finish(param0->unk_2C);
        param0->unk_08 = 1;
        param0->unk_04++;
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
    SlotMachinePalette *v2 = &param0->unk_184;

    v2->unk_00 = param0;
    v0 = SlotMachine_ReadNarcMember(param0, 3, 0);

    NNS_G2dGetUnpackedPaletteData(v0, &v1);

    SlotMachine_CopyPalette(v1, 0x1, v2->unk_04);
    SlotMachine_CopyPalette(v1, 0x2, v2->unk_A4[SlotMachinePaletteIndex_00]);
    SlotMachine_CopyPalette(v1, 0x3, v2->unk_A4[SlotMachinePaletteIndex_01]);
    SlotMachine_CopyPalette(v1, 0x3, v2->unk_A4[SlotMachinePaletteIndex_02]);
    SlotMachine_CopyPalette(v1, 0x4, v2->unk_A4[SlotMachinePaletteIndex_03]);
    SlotMachine_CopyPalette(v1, 0x4, v2->unk_A4[SlotMachinePaletteIndex_04]);

    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 5, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_24);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 6, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_44);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 7, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_64);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 74, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_144[SlotMachinePaletteIndex_00]);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 75, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_144[SlotMachinePaletteIndex_01]);
    SlotMachine_CopyPalette(v1, 0, v2->unk_144[SlotMachinePaletteIndex_02]);
    Heap_Free(v0);

    v0 = SlotMachine_ReadNarcMember(param0, 76, 0);
    NNS_G2dGetUnpackedPaletteData(v0, &v1);
    SlotMachine_CopyPalette(v1, 0, v2->unk_144[SlotMachinePaletteIndex_03]);
    SlotMachine_CopyPalette(v1, 0, v2->unk_144[SlotMachinePaletteIndex_04]);
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

    (*param3) = (v0->unk_00_0 + ((v1->unk_00_0 - v0->unk_00_0) * param2 >> 4)) | ((v0->unk_00_5 + ((v1->unk_00_5 - v0->unk_00_5) * param2 >> 4)) << 5) | ((v0->unk_00_10 + ((v1->unk_00_10 - v0->unk_00_10) * param2 >> 4)) << 10);
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
    SlotMachinePalette *v0 = &param0->unk_184;
    int v1 = sSlotMachinePaletteSlot[param1];

    SlotMachine_LoadPalette(param0, 1, v1, v0->unk_A4[param1]);
}

static void SlotMachine_SetReelPaletteBlend(SlotMachineContext *param0, SlotMachinePaletteIndex param1)
{
    SlotMachinePalette *v0 = &param0->unk_184;
    int v1 = sSlotMachinePaletteSlot[param1];
    const u16 *v2 = v0->unk_A4[param1];
    const u16 *v3 = v0->unk_144[param1];
    u16 *v4 = v0->unk_1E4[param1];

    SlotMachine_BlendPalette(v2, v3, 10, v4);
    SlotMachine_LoadPalette(param0, 1, v1, v4);
}

static void SlotMachine_SetReelPaletteBlend2(SlotMachineContext *param0, SlotMachinePaletteIndex param1)
{
    SlotMachinePalette *v0 = &param0->unk_184;
    int v1 = sSlotMachinePaletteSlot[param1];
    const u16 *v2 = v0->unk_A4[param1];
    const u16 *v3 = v0->unk_144[param1];
    u16 *v4 = v0->unk_1E4[param1];

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

    v2.unk_00 = param1;
    v2.unk_04 = param2;
    v2.unk_08 = param0;

    v0 = OverworldAnimManagerList_InitManager(param0->unk_44C, &sSlotMachinePaletteAnimFuncs, &v1, 0, &v2, 143);

    return v0;
}

static int SlotMachine_IsPaletteAnimDone(OverworldAnimManager *param0)
{
    SlotMachinePaletteAnim *v0 = OverworldAnimManager_GetFuncsContext(param0);
    return v0->unk_0C;
}

static int SlotMachine_PaletteAnim_Init(OverworldAnimManager *param0, void *param1)
{
    const SlotMachinePaletteAnimArgs *v0;
    SlotMachinePaletteAnim *v1 = param1;

    v0 = (const SlotMachinePaletteAnimArgs *)OverworldAnimManager_GetUserData(param0);
    v1->unk_1C = v0->unk_08;
    v1->unk_10 = v0->unk_00;
    v1->unk_14 = v0->unk_04;
    v1->unk_20 = &v1->unk_1C->unk_184;

    return 1;
}

static void SlotMachine_PaletteAnim_Exit(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePaletteAnim *v0 = param1;
    SlotMachine_SetReelPalette(v0->unk_1C, v0->unk_10);
}

static void SlotMachine_PaletteAnim_Update(OverworldAnimManager *param0, void *param1)
{
    int v0;
    SlotMachinePaletteAnim *v1 = param1;
    int v2 = sSlotMachinePaletteSlot[v1->unk_10];
    u16 *v3 = v1->unk_20->unk_1E4[v1->unk_10];
    const u16 *v4 = v1->unk_20->unk_A4[v1->unk_10];
    const u16 *v5 = v1->unk_20->unk_144[v1->unk_10];

    switch (v1->unk_00) {
    case 0:
        v1->unk_18 += 0x4000;

        if (v1->unk_18 > (FX32_ONE * 16)) {
            v1->unk_18 = (FX32_ONE * 16);
        }

        v0 = ((v1->unk_18) / FX32_ONE);

        if (v0 == 16) {
            v1->unk_00++;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->unk_1C, 1, v2, v3);
        break;
    case 1:
        v1->unk_18 -= 0x4000;

        if (v1->unk_18 < (FX32_ONE * 0)) {
            v1->unk_18 = (FX32_ONE * 0);
        }

        v0 = ((v1->unk_18) / FX32_ONE);

        if (v0 == 0) {
            v1->unk_04++;

            if (v1->unk_04 >= 4) {
                if (v1->unk_14) {
                    v1->unk_00++;
                    v1->unk_0C = 1;
                } else {
                    v1->unk_00 = 4;
                    v1->unk_0C = 1;
                }
            } else {
                v1->unk_00--;
            }
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->unk_1C, 1, v2, v3);
        break;
    case 2:
        v1->unk_18 += 0x8000;

        if (v1->unk_18 > (FX32_ONE * 16)) {
            v1->unk_18 = (FX32_ONE * 16);
        }

        v0 = ((v1->unk_18) / FX32_ONE);

        if (v0 == 16) {
            v1->unk_00++;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->unk_1C, 1, v2, v3);
        break;
    case 3:
        v1->unk_18 -= 0x8000;

        if (v1->unk_18 < (FX32_ONE * 0)) {
            v1->unk_18 = (FX32_ONE * 0);
        }

        v0 = ((v1->unk_18) / FX32_ONE);

        if (v0 == 0) {
            v1->unk_00--;
        }

        SlotMachine_BlendPalette(v4, v5, v0, v3);
        SlotMachine_LoadPalette(v1->unk_1C, 1, v2, v3);
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

    GF_ASSERT(param0->unk_120.unk_14 == NULL);
    param0->unk_120.unk_14 = OverworldAnimManagerList_InitManager(param0->unk_44C, &sSlotMachinePayoutAnimFuncs, &v0, 0, param0, 143);
}

static void SlotMachine_FinishPayoutAnim(SlotMachineContext *param0)
{
    if (param0->unk_120.unk_14 != NULL) {
        OverworldAnimManager_Finish(param0->unk_120.unk_14);
        param0->unk_120.unk_14 = NULL;
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
    const SlotMachinePayoutAnimStep *v7 = &sSlotMachinePayoutAnimSteps[param0->unk_04];

    for (v1 = 0, v2 = 1, v0 = (1 << 0); v0 <= (1 << 4); v1++, v0 <<= 1) {
        if (v7->unk_00 & v0) {
            if (param0->unk_08 == 0) {
                param0->unk_14[v1] = v7->unk_04;
                v2 = 0;
            } else {
                if (v7->unk_04 < v7->unk_08) {
                    param0->unk_14[v1] += v7->unk_0C;

                    if (param0->unk_14[v1] >= v7->unk_08) {
                        param0->unk_14[v1] = v7->unk_08;
                    } else {
                        v2 = 0;
                    }
                } else {
                    param0->unk_14[v1] -= v7->unk_0C;

                    if (param0->unk_14[v1] <= v7->unk_08) {
                        param0->unk_14[v1] = v7->unk_08;
                    } else {
                        v2 = 0;
                    }
                }
            }

            v3 = sSlotMachinePaletteSlot[v1];
            v5 = param0->unk_2C->unk_A4[v1];
            v6 = param0->unk_2C->unk_144[v1];
            v4 = param0->unk_2C->unk_1E4[v1];

            SlotMachine_BlendPalette(v5, v6, ((param0->unk_14[v1]) / FX32_ONE), v4);
            SlotMachine_LoadPalette(param0->unk_28, 1, v3, v4);
        }
    }

    for (; v0 <= (1 << 5); v0 <<= 1) {
        if (v7->unk_00 & (1 << 5)) {
            param0->unk_0C += FX32_ONE;

            if (param0->unk_0C >= v7->unk_04) {
                param0->unk_0C = 0;
            } else {
                v2 = 0;
            }
        }
    }

    param0->unk_08 = 1;

    if (v2 == 1) {
        param0->unk_08 = 0;
        param0->unk_04++;
        v7 = &sSlotMachinePayoutAnimSteps[param0->unk_04];

        if (v7->unk_00 == (1 << 6)) {
            param0->unk_04 = (int)v7->unk_04;
            param0->unk_04 = 0;
        }
    }
}

static int SlotMachine_PayoutAnim_Init(OverworldAnimManager *param0, void *param1)
{
    SlotMachinePayoutAnim *v0 = param1;

    v0->unk_28 = (SlotMachineContext *)OverworldAnimManager_GetUserData(param0);
    v0->unk_2C = &v0->unk_28->unk_184;

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

    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_0C = param0;

    SysTask_Start(SlotMachine_FadeInTask, v0, 143);
}

static void SlotMachine_StartFadeOutTask(SlotMachineContext *param0)
{
    SlotMachineFadeTask *v0 = Heap_AllocAtEnd(HEAP_ID_79, sizeof(SlotMachineFadeTask));

    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_0C = param0;

    SysTask_Start(SlotMachine_FadeOutTask, v0, 143);
}

static void SlotMachine_StartFlashTask(SlotMachineContext *param0, int param1)
{
    SlotMachineFadeTask *v0 = Heap_AllocAtEnd(HEAP_ID_79, sizeof(SlotMachineFadeTask));

    v0->unk_00 = 0;
    v0->unk_08 = param1;
    v0->unk_04 = (FX32_ONE * 8);
    v0->unk_0C = param0;

    SysTask_Start(SlotMachine_FlashTask, v0, 143);
    Sound_PlayEffect(SEQ_SE_DP_025_sseq);
}

static void SlotMachine_FadeInTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->unk_0C->unk_184;
    const u16 *v2 = v1->unk_04;
    const u16 *v3 = v1->unk_24;
    u16 *v4 = v1->unk_84;
    u16 v5;

    v0->unk_04 += 0x800;
    v5 = ((v0->unk_04) / FX32_ONE);

    if (v5 > 16) {
        v5 = 16;
    }

    SlotMachine_BlendPalette(v2, v3, v5, v4);
    SlotMachine_LoadPalette(v0->unk_0C, 7, 0x1, v4);

    if ((v5 == 16) || (v0->unk_0C->unk_00 == 63)) {
        Heap_Free(v0);
        SysTask_Done(param0);
    }
}

static void SlotMachine_FadeOutTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->unk_0C->unk_184;
    const u16 *v2 = v1->unk_24;
    const u16 *v3 = v1->unk_04;
    u16 *v4 = v1->unk_84;
    u16 v5;

    v0->unk_04 += 0x800;
    v5 = ((v0->unk_04) / FX32_ONE);

    if (v5 > 16) {
        v5 = 16;
    }

    SlotMachine_BlendPalette(v2, v3, v5, v4);
    SlotMachine_LoadPalette(v0->unk_0C, 7, 0x1, v4);

    if ((v5 == 16) || (v0->unk_0C->unk_00 == 63)) {
        Heap_Free(v0);
        SysTask_Done(param0);
    }
}

static void SlotMachine_FlashTask(SysTask *param0, void *param1)
{
    SlotMachineFadeTask *v0 = param1;
    SlotMachinePalette *v1 = &v0->unk_0C->unk_184;
    const u16 *v2, *v3 = v1->unk_24;
    u16 *v4 = v1->unk_84;
    int v5;

    if (v0->unk_0C->unk_00 == 63) {
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }

    if (v0->unk_08 == 0) {
        v2 = v1->unk_44;
    } else {
        v2 = v1->unk_64;
    }

    switch (v0->unk_00) {
    case 0:
        v0->unk_04 += 0x1000;
        v5 = ((v0->unk_04) / FX32_ONE);

        if (v5 > 16) {
            v5 = 16;
            v0->unk_00++;
        }

        SlotMachine_BlendPalette(v3, v2, v5, v4);
        SlotMachine_LoadPalette(v0->unk_0C, 7, 0x1, v4);
        break;
    case 1:
        v0->unk_04 -= 0x400;
        v5 = ((v0->unk_04) / FX32_ONE);

        if (v5 < 0) {
            v5 = 0;
        }

        SlotMachine_BlendPalette(v3, v2, v5, v4);
        SlotMachine_LoadPalette(v0->unk_0C, 7, 0x1, v4);

        if (v5 == 0) {
            Heap_Free(v0);
            SysTask_Done(param0);
        }
    }
}

SlotMachineSymbol SlotMachine_GetReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2)
{
    int v0 = (param0->unk_A8[param1] + param2) % 21;

    if (v0 < 0) {
        v0 = 21 + v0;
    }

    return sSlotMachineReelStrips[param1][v0];
}

SlotMachineSymbol SlotMachine_GetVisibleReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2)
{
    int v0 = 0;

    if (param0->unk_90[param1] % (FX32_ONE * 32)) {
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
        param0->unk_54[v0] = 0;
        v0++;
    } while (v0 < 3);
}

static void SlotMachine_RecordButtonInput(SlotMachineContext *param0, u32 param1)
{
    int v0 = 0;

    do {
        if (param0->unk_54[v0] == 0) {
            break;
        }

        v0++;
    } while (v0 < 3);

    GF_ASSERT(v0 < 3);
    param0->unk_54[v0] = param1;
}

static int SlotMachine_CheckButtonOrder(SlotMachineContext *param0)
{
    int v0 = 0;
    u32 v1[3] = { PAD_BUTTON_Y, PAD_BUTTON_B, PAD_BUTTON_A };

    do {
        if ((param0->unk_54[v0] != 0) && (param0->unk_54[v0] != v1[v0])) {
            return 0;
        }

        v0++;
    } while (v0 < 3);

    return 1;
}

static int SlotMachine_CheckButtonOrder2(SlotMachineContext *param0)
{
    int v0 = 0;
    const SlotMachineButtonOrder *v1 = &sSlotMachineButtonOrder[param0->unk_34];

    do {
        if ((param0->unk_54[v0] != 0) && (param0->unk_54[v0] != v1->unk_00[v0])) {
            return 0;
        }

        v0++;
    } while (v0 < 3);

    return 1;
}

static void SlotMachine_SetReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    const int *v0 = sSlotMachineReelHighlightPos[param1];

    Bg_ChangeTilemapRectPalette(param0->unk_43C, 1, v0[0], v0[1], 3, 2, 6);
    Bg_ScheduleTilemapTransfer(param0->unk_43C, 1);
}

static void SlotMachine_ClearReelHighlight(SlotMachineContext *param0, SlotMachineReelIndex param1)
{
    const int *v0 = sSlotMachineReelHighlightPos[param1];

    Bg_ChangeTilemapRectPalette(param0->unk_43C, 1, v0[0], v0[1], 3, 2, 5);
    Bg_ScheduleTilemapTransfer(param0->unk_43C, 1);
}

static u32 SlotMachine_GetPayoutAmount(SlotMachineContext *param0)
{
    int v0, v1;
    SlotMachineSymbol v2 = param0->unk_44;
    u32 v3 = param0->unk_48;

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
