#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "overworld_anim_manager.h"
#include "sys_task_manager.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    int unk_10;
    int unk_14;
    SlotMachineReelType unk_18;
    SlotMachineWinType unk_1C;
    SlotMachineContext *unk_20;
    SysTask *unk_24;
    OverworldAnimManager *unk_28;
    OverworldAnimManager *unk_2C;
    OverworldAnimManager *unk_30;
    OverworldAnimManager *unk_34;
    OverworldAnimManager *unk_38;
    OverworldAnimManager *unk_3C;
    OverworldAnimManager *unk_40;
    OverworldAnimManager *unk_44;
} SlotMachineReelAnimTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H
