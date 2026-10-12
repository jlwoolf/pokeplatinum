#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02256BAC_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02256BAC_H

#include "struct_defs/struct_02095C60.h"

#include "bg_window.h"
#include "game_options.h"
#include "narc.h"
#include "sprite.h"
#include "sprite_resource.h"

typedef struct {
    BgConfig *bgConfig;
    SpriteList *spriteList;
    SpriteResourceCollection **spriteResources;
    const Options *options;
    int iconCount;
    int textBankID;
    int messageNumber;
    int initialScore;
    ContestScoringCommState *commState;
    NARC *narc;
} ContestScoreDisplayTemplate;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02256BAC_H
