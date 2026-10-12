#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "overworld_anim_manager.h"
#include "sys_task_manager.h"

typedef struct {
    u32 state;
    u32 done;
    int timer;
    SlotMachineContext *context;
    SysTask *task;
    OverworldAnimManager *animManager;
    OverworldAnimManager *animManager2;
} SlotMachinePayoutTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_PAYOUT_TASK_H
