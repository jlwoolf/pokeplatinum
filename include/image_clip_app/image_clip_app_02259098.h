#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02259098_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02259098_H

#include <nnsys.h>

#include "struct_defs/struct_image_clip_pokemon_sprite.h"

#include "image_clip_app/struct_image_clip_app_022596B0.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"

#include "pokemon.h"

void ImageClipPokemonSprite_LoadDecryptedSprite(ImageClipGraphics *param0, PokemonSpriteTemplate *param1);
void ImageClipPokemonSprite_Init(ImageClipPokemonSprite *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4);
void ImageClipPokemonSprite_InitEx(ImageClipPokemonSprite *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4, BOOL param5);
void ImageClipPokemonSprite_Free(ImageClipPokemonSprite *param0);
void ImageClipPokemonSprite_SetZ(ImageClipPokemonSprite *param0, int param1);
int ImageClipPokemonSprite_GetZ(ImageClipPokemonSprite *param0);
void ImageClipPokemonSprite_SetPosition(ImageClipPokemonSprite *param0, int param1, int param2);
BOOL ImageClipPokemonSprite_IsScreenTouched(ImageClipPokemonSprite *param0);
BOOL ImageClipPokemonSprite_IsTouchInHitTable(ImageClipPokemonSprite *param0, int param1, int param2);
void ImageClipPokemonSprite_GetCenter(ImageClipPokemonSprite *param0, int *xCenter, int *yCenter);
void ImageClipPokemonSprite_GetSize(ImageClipPokemonSprite *param0, int *param1, int *param2);
BOOL ImageClipPokemonSprite_IsTouchedByTouch(ImageClipPokemonSprite *param0, int *param1, int *param2, NNSG2dCharacterData *param3);
BOOL ImageClipPokemonSprite_IsPixelHit(ImageClipPokemonSprite *param0, int param1, int param2, NNSG2dCharacterData *param3);
void ImageClipPokemonSprite_GetPixelBounds(ImageClipPokemonSprite *param0, ImageClipPixelBounds *param1);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02259098_H
