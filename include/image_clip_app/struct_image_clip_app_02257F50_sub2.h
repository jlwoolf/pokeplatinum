#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *softSpriteManager;
    SoftwareSpriteChars **chars;
    SoftwareSpritePalette **palettes;
    u8 *extraResource;
    BgConfig *bgConfig;
    ImageClipSpriteManager *spriteManager;
    ImageClipBg bg;
    ImageClipSpriteManager *unused_44;
} PhotoAccessoryRendererContext;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H
