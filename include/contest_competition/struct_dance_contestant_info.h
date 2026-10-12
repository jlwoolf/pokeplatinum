#ifndef POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H
#define POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H

#include "contest_competition/struct_dance_photo_sprite.h"

#include "pokemon.h"
#include "pokemon_sprite.h"

typedef struct {
    Pokemon *mon;
    PokemonSprite *sprite;
    DancePhotoSprite *photoSprite;
    u8 contestantID;
    u8 slot;
    u16 duration;
    s32 currentX;
    s32 currentY;
    s32 currentZ;
    s32 velocityX;
    s32 velocityY;
    s32 velocityZ;
    u16 frame;
    u8 state;
    u8 finished;
} DanceContestantInfo;

#endif // POKEPLATINUM_STRUCT_DANCE_CONTESTANT_INFO_H
