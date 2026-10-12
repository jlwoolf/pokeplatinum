#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_0225899C.h"
#include "image_clip_app/struct_image_clip_app_02259484.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *softSpriteManager;
    SoftwareSpriteChars **chars;
    SoftwareSpritePalette **palettes;
    u8 *extraResource;
    BgConfig *bgConfig;
    ImageClipSpriteManager *spriteManager;
    ImageClipResourceList *resourceList;
    int groupCapacity0;
    int groupCapacity1;
    int groupCapacity2;
    FashionCaseCounts *fashionCase;
} PhotoAccessoryRendererResources;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02258470_H
