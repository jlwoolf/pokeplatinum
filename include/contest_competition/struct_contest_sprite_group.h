#ifndef POKEPLATINUM_STRUCT_CONTEST_SPRITE_GROUP_H
#define POKEPLATINUM_STRUCT_CONTEST_SPRITE_GROUP_H

#include "sprite_system.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *sprites[6];
    SysTask *task;
} ContestSpriteGroup;

#endif // POKEPLATINUM_STRUCT_CONTEST_SPRITE_GROUP_H
