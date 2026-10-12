#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H

#include "enums.h"
#include "sys_task_manager.h"

typedef struct {
    u32 state;
    int done;
    SlotMachineBgmMode currentMode;
    SlotMachineBgmMode requestedMode;
    SysTask *task;
} SlotMachineBgmState;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H
