#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "sys_task_manager.h"

typedef struct {
    u32 unk_00;
    int unk_04;
    fx32 unk_08;
    int unk_0C;
    SlotMachineReelIndex unk_10;
    int unk_14;
    int unk_18;
    SysTask *unk_1C;
    SlotMachineContext *unk_20;
} SlotMachineReelTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_TASK_H
