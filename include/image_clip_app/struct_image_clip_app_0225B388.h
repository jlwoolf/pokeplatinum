#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225B388_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225B388_H

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_02259484.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *softSpriteManager;
    SoftwareSpriteChars **chars;
    SoftwareSpritePalette **palettes;
    u8 *extraResource;
    PokemonSpriteManager *pokemonSpriteManager;
    BgConfig *bgConfig;
    ImageClipSpriteManager *spriteManager;
    ImageClipResourceList *resourceList;
    int maxSpriteCount;
} PhotoRendererTemplate;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_0225B388_H
