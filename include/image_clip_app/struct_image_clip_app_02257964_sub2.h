#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H

#include "struct_defs/struct_image_clip_pokemon_sprite.h"

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"

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
    ImageClipBg bg;
    int backdropIndex;
    ImageClipPokemonSprite pokemonSprite;
} PhotoRendererContext;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H
