#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H

#include "struct_defs/struct_image_clip_pokemon_sprite.h"

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_022597BC.h"

#include "bg_window.h"
#include "software_sprite.h"

typedef struct {
    SoftwareSpriteManager *unk_00;
    SoftwareSpriteChars **unk_04;
    SoftwareSpritePalette **unk_08;
    u8 *unk_0C;
    PokemonSpriteManager *unk_10;
    BgConfig *unk_14;
    ImageClipSpriteManager *unk_18;
    ImageClipBg unk_1C;
    int unk_48;
    ImageClipPokemonSprite unk_4C;
} PhotoRendererContext;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_APP_02257964_SUB2_H
