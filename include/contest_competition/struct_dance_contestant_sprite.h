#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "pokemon_sprite.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    struct DanceCompetition_t *competition;
    SysTask *task;
    PokemonSprite *sprite;
    DancePhotoSprite *photoSprite;
    s32 moveOffsetX;
    s32 rotation;
    u8 unused_18;
    u8 param;
    u8 contestantID;
    u8 unused_1B;
    u8 unused_1C;
    u32 prevRotation;
    u8 flag0 : 1;
    u8 flag1 : 1;
    u8 flag2 : 1;
    u8 flag3 : 1;
    u8 flag4 : 1;
    u8 flag5 : 1;
    u8 flag6 : 1;
    u8 : 1;
} DanceContestantSprite;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H
