#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *sprite;
    ManagedSprite *targetSprite;
    int index;
    int state;
    s16 unk_10;
    s16 unk_12;
    s16 yPos;
    s16 unk_16;
    s16 unk_18;
    int orbitAngle;
    int wobbleAngle;
    int jitterRange;
    int params[4];
    int unk_38;
    BOOL followTarget;
    SysTask *task;
} SpearPillarSprite;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_SPRITE_H
