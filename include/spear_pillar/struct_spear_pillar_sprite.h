#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *unk_00;
    ManagedSprite *unk_04;
    int unk_08;
    int unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28[4];
    int unk_38;
    BOOL unk_3C;
    SysTask *unk_40;
} SpearPillarSprite;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H
