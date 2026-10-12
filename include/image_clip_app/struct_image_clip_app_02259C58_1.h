#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_1_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_1_H

#include "image_clip_app/funcptr_image_clip_app_02259D78.h"

#include "sprite.h"

typedef struct {
    AffineSpriteListTemplate *spriteTemplate;
    ImageClipUiCallback callback;
    void *callbackParam;
    int buttonId;
} ImageClipUiTemplate;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_1_H
