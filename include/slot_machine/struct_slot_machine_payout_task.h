#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "overworld_anim_manager.h"
#include "sys_task_manager.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    int unk_08;
    SlotMachineContext *unk_0C;
    SysTask *unk_10;
    OverworldAnimManager *unk_14;
    OverworldAnimManager *unk_18;
} SlotMachinePayoutTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H
