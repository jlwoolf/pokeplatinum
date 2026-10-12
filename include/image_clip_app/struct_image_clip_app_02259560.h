#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259560_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259560_H

#include "image_clip_app/struct_image_clip_app_02259560.h"

typedef struct ImageClipSpriteResource {
    void *data;
    int category;
    struct ImageClipSpriteResource *next;
    struct ImageClipSpriteResource *prev;
} ImageClipSpriteResource;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259560_H
