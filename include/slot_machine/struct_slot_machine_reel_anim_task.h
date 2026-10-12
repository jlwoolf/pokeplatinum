#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "overworld_anim_manager.h"
#include "sys_task_manager.h"

typedef struct {
    u32 state;
    u32 step;
    u32 done;
    u32 spritesFinished;
    int timer;
    int orderIndex;
    SlotMachineReelType reelType;
    SlotMachineWinType winType;
    SlotMachineContext *context;
    SysTask *task;
    OverworldAnimManager *reelAnim;
    OverworldAnimManager *symbolAnim;
    OverworldAnimManager *winSymbolAnim;
    OverworldAnimManager *bonusAnim;
    OverworldAnimManager *buttonAnim;
    OverworldAnimManager *button3Anim;
    OverworldAnimManager *creditDigitAnim;
    OverworldAnimManager *payoutDigitAnim;
} SlotMachineReelAnimTask;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_REEL_ANIM_TASK_H
