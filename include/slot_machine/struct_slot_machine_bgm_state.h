#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H

#include "enums.h"
#include "sys_task_manager.h"

typedef struct {
    u32 unk_00;
    int unk_04;
    SlotMachineBgmMode unk_08;
    SlotMachineBgmMode unk_0C;
    SysTask *unk_10;
} SlotMachineBgmState;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_BGM_STATE_H
