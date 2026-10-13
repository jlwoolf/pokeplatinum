#ifndef POKEPLATINUM_STRUCT_CONTEST_OPPONENT_DATA_H
#define POKEPLATINUM_STRUCT_CONTEST_OPPONENT_DATA_H

#include "constants/moves.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u16 contestantObjEventGFX;
    u16 trainerSpriteID;
    u16 moves[LEARNED_MOVES_MAX];
    u16 species;
    u16 monNicknameID;
    u16 monOTNameID;
    u8 cool;
    u8 beauty;
    u8 cute;
    u8 smart;
    u8 tough;
    u8 sheen;
    u16 contestRank : 3;
    u16 isCool : 1;
    u16 isBeauty : 1;
    u16 isCute : 1;
    u16 isSmart : 1;
    u16 isTough : 1;
    u16 isRealCompetition : 1;
    u16 isPracticeCompetition : 1;
    u16 storyProgress : 2;
    u16 gender : 2;
    u16 cameraFlashVariant : 2;
    u8 npcPhotoPreset0;
    u8 npcPhotoPreset1;
    u8 npcPhotoPreset2;
    u8 npcPhotoPreset3;
    u8 npcPhotoPreset4;
    u8 npcPhotoPreset5;
    u8 npcPhotoPreset6;
    u8 npcPhotoPreset7;
    u8 npcPhotoPreset8;
    u8 npcPhotoPreset9;
    u8 npcPhotoPreset10;
    u8 npcPhotoPreset11;
    u8 monContestFame;
    u8 padding_2F;
} ContestOpponentData;

#endif // POKEPLATINUM_STRUCT_CONTEST_OPPONENT_DATA_H
