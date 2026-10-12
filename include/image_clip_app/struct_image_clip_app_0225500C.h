#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225500C_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225500C_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"

#include "software_sprite.h"

typedef struct {
    ImageClipSpriteManager *spriteManager;
    SoftwareSpriteManager *softSpriteManager;
    SoftwareSpriteChars *chars;
    SoftwareSpritePalette *palette;
    int xPos;
    int yPos;
    u32 resourceIndex;
    u32 paletteSlot;
} ImageClipSpriteConfig;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225500C_H
