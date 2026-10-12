#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H

#include "struct_defs/struct_02095C60.h"

#include "image_clip_app/struct_image_clip_app_0225AE9C.h"

#include "bg_window.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sys_task_manager.h"

typedef struct {
    SpriteResource *resources[4];
    Sprite *sprites[2];
    Window *window;
    int score;
    int scoreTimer;
    SysTask *scoreTask;
    SysTask *animationTask;
    ContestScoringCommState *commState;
    ContestScoreDisplayScoreAnimation animation;
    BOOL paletteChanged;
} ContestScoreDisplayScore;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AB54_H
