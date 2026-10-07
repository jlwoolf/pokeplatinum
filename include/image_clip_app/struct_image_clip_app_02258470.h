#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_0225899C.h"
#include "image_clip_app/struct_image_clip_app_02259484.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *unk_00;
    SoftwareSpriteChars **unk_04;
    SoftwareSpritePalette **unk_08;
    u8 *unk_0C;
    BgConfig *unk_10;
    ImageClipSpriteManager *unk_14;
    ImageClipResourceList *unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    FashionCaseCounts *unk_28;
} PhotoAccessoryRendererResources;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H
