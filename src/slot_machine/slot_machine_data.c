#include <nitro.h>
#include <string.h>

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
#include "slot_machine/struct_slot_machine_symbol_weights.h"
#include "slot_machine/struct_slot_machine_bonus_multiplier.h"
#include "slot_machine/struct_slot_machine_bonus_entry.h"
#include "slot_machine/struct_slot_machine_payout_result.h"

#include "enums.h"

const SlotMachineSymbol sSlotMachineReelStrips[3][21] = {
    {
        0x5,
        0x3,
        0x1,
        0x0,
        0x2,
        0x4,
        0x5,
        0x3,
        0x1,
        0x2,
        0x4,
        0x5,
        0x3,
        0x1,
        0x2,
        0x4,
        0x5,
        0x2,
        0x0,
        0x2,
        0x4,
    },
    {
        0x3,
        0x0,
        0x1,
        0x5,
        0x4,
        0x2,
        0x3,
        0x0,
        0x5,
        0x4,
        0x2,
        0x3,
        0x0,
        0x5,
        0x4,
        0x2,
        0x3,
        0x1,
        0x5,
        0x4,
        0x2,
    },
    {
        0x4,
        0x2,
        0x1,
        0x0,
        0x2,
        0x5,
        0x4,
        0x2,
        0x1,
        0x3,
        0x5,
        0x4,
        0x2,
        0x1,
        0x3,
        0x5,
        0x4,
        0x2,
        0x0,
        0x3,
        0x5,
    },
};

const int sSlotMachinePayoutPerLine[6] = {
    0x64,
    0x64,
    0x0,
    0x2,
    0xA,
    0xF
};

const int sSlotMachinePayoutPerLine2[6] = {
    0x64,
    0x64,
    0xF,
    0x2,
    0xA,
    0xF
};

const u32 sSlotMachineSymbolChance[6] = {
    0x19,
    0x19,
    0x1E,
    0x1E,
    0x23,
    0x23
};

const SlotMachineSymbolWeights sSlotMachineSymbolWeights[6] = {
    {
        { 0x1, 0x4 },
        { 0x2, 0xD },
        { 0x1, 0x27 },
        { 0x1, 0x27 },
    },
    {
        { 0x1, 0x4 },
        { 0x2, 0xD },
        { 0x1, 0x27 },
        { 0x1, 0x27 },
    },
    {
        { 0x2, 0x3 },
        { 0x4, 0xB },
        { 0x2, 0x26 },
        { 0x2, 0x26 },
    },
    {
        { 0x3, 0x2 },
        { 0x4, 0xB },
        { 0x2, 0x26 },
        { 0x2, 0x26 },
    },
    {
        { 0x4, 0x1 },
        { 0x6, 0x9 },
        { 0x3, 0x25 },
        { 0x3, 0x25 },
    },
    {
        { 0x4, 0x1 },
        { 0x6, 0x9 },
        { 0x3, 0x25 },
        { 0x3, 0x25 },
    },
};

const u32 sSlotMachineBonusChance[6] = {
    0x50,
    0x50,
    0x50,
    0x50,
    0x50,
    0x46
};

const SlotMachineBonusEntry sSlotMachineBonusTable[6][SlotMachineBonusType_06] = {
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0xA, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xA, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0xA, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xF, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x32, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0xA, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xA, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0xA, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xF, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x32, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0xF, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xA, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0xF, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xF, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x28, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0xF, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xF, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0xF, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xA, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x28, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0x14, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xF, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0x14, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xA, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x1E, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
    {
        { 0x5, SlotMachineBonusType_03, SlotMachineBonusKind_00 },
        { 0x14, SlotMachineBonusType_01, SlotMachineBonusKind_01 },
        { 0xF, SlotMachineBonusType_05, SlotMachineBonusKind_02 },
        { 0x14, SlotMachineBonusType_02, SlotMachineBonusKind_02 },
        { 0xA, SlotMachineBonusType_04, SlotMachineBonusKind_01 },
        { 0x1E, SlotMachineBonusType_00, SlotMachineBonusKind_00 },
    },
};

const u32 sSlotMachineBonusDuration[SlotMachineBonusType_06] = {
    0x32,
    0x46,
    0x5A,
    0x32,
    0x46,
    0x5A
};

const SlotMachineBonusMultiplier sSlotMachineBonusMultiplierTable[6][SlotMachineBonusKind_03][SlotMachineWinType_03] = {
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
    {
        {
            { 0x5, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x4B, SlotMachineWinType_01 },
        },
        {
            { 0x14, SlotMachineWinType_02 },
            { 0x3C, SlotMachineWinType_00 },
            { 0x14, SlotMachineWinType_01 },
        },
        {
            { 0x4B, SlotMachineWinType_02 },
            { 0x14, SlotMachineWinType_00 },
            { 0x5, SlotMachineWinType_01 },
        },
    },
};

const u32 sSlotMachineDoubleUpChance[6] = {
    0x19,
    0x19,
    0x1E,
    0x1E,
    0x23,
    0x23
};

const u32 sSlotMachineDoubleUpWeights[6][4] = {
    { 0x5, 0xF, 0x1E, 0x32 },
    { 0x5, 0xF, 0x1E, 0x32 },
    { 0x5, 0xF, 0x1E, 0x32 },
    { 0x5, 0xF, 0x1E, 0x32 },
    { 0x5, 0xF, 0x1E, 0x32 },
    { 0x5, 0xF, 0x1E, 0x32 }
};

const u32 sSlotMachineDoubleUpWinChance[6] = {
    0x1,
    0x1,
    0x3,
    0x3,
    0x5,
    0x5
};

const u32 sSlotMachineDoubleUpLoseChance[6] = {
    0x3,
    0x3,
    0x5,
    0x5,
    0x7,
    0x7
};

const u32 sSlotMachinePayoutAdjust[6][2] = {
    { 0x19, 0x14 },
    { 0x14, 0xF },
    { 0xF, 0xF },
    { 0xF, 0xF },
    { 0xA, 0xF },
    { 0x5, 0xA }
};

const SlotMachinePayoutResult sSlotMachinePayoutResultTable[6][SlotMachinePayoutThreshold_09] = {
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
    {
        { SlotMachinePayoutThreshold_08, 0xA, 0xA, 0x50 },
        { SlotMachinePayoutThreshold_07, 0xA, 0x1E, 0x3C },
        { SlotMachinePayoutThreshold_06, 0xA, 0x28, 0x32 },
        { SlotMachinePayoutThreshold_05, 0x14, 0x32, 0x1E },
        { SlotMachinePayoutThreshold_04, 0x1E, 0x32, 0x14 },
        { SlotMachinePayoutThreshold_03, 0x32, 0x28, 0xA },
        { SlotMachinePayoutThreshold_02, 0x3C, 0x1E, 0xA },
        { SlotMachinePayoutThreshold_01, 0x50, 0xA, 0xA },
        { SlotMachinePayoutThreshold_00, 0x5A, 0x5, 0x5 },
    },
};
