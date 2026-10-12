#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AE9C_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AE9C_H

#include <nitro/fx/fx.h>

#include "image_clip_app/struct_image_clip_app_0225AD68.h"

#include "sprite.h"

typedef struct {
    BOOL active;
    Sprite *sprites[2];
    VecFx32 positions[2];
    ContestScoreDisplayTween scaleTween;
    ContestScoreDisplayTween xTween;
    ContestScoreDisplayTween yTween;
} ContestScoreDisplayScoreAnimation;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225AE9C_H
