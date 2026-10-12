#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_H

#include "sprite.h"

typedef struct ImageClipUi {
    Sprite *sprite;
    int buttonId;
    void *callbackParam;
    void (*callback)(struct ImageClipUi *param0, void *param1);
} ImageClipUi;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02259C58_H
