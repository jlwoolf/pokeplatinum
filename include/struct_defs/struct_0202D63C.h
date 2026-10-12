#ifndef POKEPLATINUM_STRUCT_0202D63C_H
#define POKEPLATINUM_STRUCT_0202D63C_H

#include "constants/string.h"

#include "frontier_facilities/frontier_opponents.h"

typedef struct WifiTrainerRecord {
    FrontierPokemon mons[3];
    u16 trainerName[TRAINER_NAME_LEN + 1];
    u8 version; // version?
    u8 language; // language?
    u8 country; // country?
    u8 region; // region?
    u32 trainerInfoId; // trainerInfoId?
    u16 no1Sentence[4]; // no1Sentence?
    union {
        struct {
            u8 isAnonymous : 1;
            u8 anonymousNameIdx : 1;
            u8 : 6;
        };
        u8 rawFlags;
    };
    u8 trainerType;
    u16 introMsg[4];
    u16 winMsg[4];
    u16 loseMsg[4];
    u16 ratingScore; // ratingScore?
} WifiTrainerRecord;

#endif // POKEPLATINUM_STRUCT_0202D63C_H
