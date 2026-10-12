#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "pokemon_sprite.h"
#include "sys_task_manager.h"

struct DanceCompetition_t;

typedef struct {
    struct DanceCompetition_t *unk_00;
    SysTask *unk_04;
    PokemonSprite *unk_08;
    DancePhotoSprite *unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
    u8 unk_1B;
    u8 unk_1C;
    u32 unk_20;
    u8 unk_24_0 : 1;
    u8 unk_24_1 : 1;
    u8 unk_24_2 : 1;
    u8 unk_24_3 : 1;
    u8 unk_24_4 : 1;
    u8 unk_24_5 : 1;
    u8 unk_24_6 : 1;
    u8 : 1;
} DanceContestantSprite;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_SPRITE_H
