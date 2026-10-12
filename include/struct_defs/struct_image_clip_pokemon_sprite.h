#ifndef POKEPLATINUM_STRUCT_IMAGE_CLIP_POKEMON_SPRITE_H
#define POKEPLATINUM_STRUCT_IMAGE_CLIP_POKEMON_SPRITE_H

#include "image_clip_app/struct_image_clip_app_022596B0.h"

#include "pokemon.h"
#include "pokemon_sprite.h"
#include "touch_screen.h"

typedef struct {
    PokemonSprite *sprite;
    TouchScreenHitTable hitTable;
    ImageClipPixelBounds pixelBounds;
    Pokemon *pokemon;
} ImageClipPokemonSprite;

#endif // POKEPLATINUM_STRUCT_IMAGE_CLIP_POKEMON_SPRITE_H
