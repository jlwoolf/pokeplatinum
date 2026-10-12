#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "pokemon.h"
#include "pokemon_sprite.h"

typedef struct {
    Pokemon *mon;
    PokemonSprite *unk_04;
    DancePhotoSprite *unk_08;
    u8 contestantID;
    u8 unk_0D;
    u16 unk_0E;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u16 unk_28;
    u8 unk_2A;
    u8 unk_2B;
} DanceContestantInfo;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H
