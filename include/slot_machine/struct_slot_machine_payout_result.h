#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_RESULT_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_RESULT_H

#include "enums.h"

typedef struct {
    SlotMachinePayoutThreshold threshold;
    u32 chanceA;
    u32 chanceB;
    u32 unk_0C;
} SlotMachinePayoutResult;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_RESULT_H
