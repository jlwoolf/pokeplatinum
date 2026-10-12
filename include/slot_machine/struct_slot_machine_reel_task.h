#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "sys_task_manager.h"

typedef struct {
    u32 state;
    int done;
    fx32 bounceSpeed;
    int bounceCount;
    SlotMachineReelIndex reelIndex;
    int targetPosition;
    int spinOffset;
    SysTask *task;
    SlotMachineContext *context;
} SlotMachineReelTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H
