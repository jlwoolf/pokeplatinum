#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *unk_00;
    SoftwareSpriteChars **unk_04;
    SoftwareSpritePalette **unk_08;
    u8 *unk_0C;
    BgConfig *unk_10;
    ImageClipSpriteManager *unk_14;
    ImageClipBg unk_18;
    ImageClipSpriteManager *unk_44;
} PhotoAccessoryRendererContext;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257F50_SUB2_H
