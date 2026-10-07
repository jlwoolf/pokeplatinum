#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H

#include "struct_defs/struct_02095C60.h"

#include "image_clip_app/struct_image_clip_app_0225AE9C.h"

#include "bg_window.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sys_task_manager.h"

typedef struct {
    SpriteResource *unk_00[4];
    Sprite *unk_10[2];
    Window *unk_18;
    int unk_1C;
    int unk_20;
    SysTask *unk_24;
    SysTask *unk_28;
    ContestScoringCommState *unk_2C;
    ContestScoreDisplayScoreAnimation unk_30;
    BOOL unk_90;
} ContestScoreDisplayScore;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H
