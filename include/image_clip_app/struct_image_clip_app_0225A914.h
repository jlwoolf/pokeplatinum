#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A914_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A914_H

#include "sprite.h"
#include "sprite_resource.h"

typedef struct {
    SpriteResource *resources[4];
    Sprite *sprites[20];
    int visibleCount;
    int unused_64;
} ContestScoreDisplayIconRow;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225A914_H
