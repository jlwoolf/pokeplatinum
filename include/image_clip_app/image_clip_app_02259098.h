#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02259098_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02259098_H

#include <nnsys.h>

#include "struct_defs/struct_020298D8.h"

#include "image_clip_app/struct_image_clip_app_022596B0.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"

#include "pokemon.h"

void ImageClipPokemonSprite_LoadDecryptedSprite(ImageClipGraphics *param0, PokemonSpriteTemplate *param1);
void ImageClipPokemonSprite_Init(UnkStruct_020298D8 *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4);
void ImageClipPokemonSprite_InitEx(UnkStruct_020298D8 *param0, PokemonSpriteManager *param1, Pokemon *param2, PokemonSpriteTemplate *param3, int param4, BOOL param5);
void ImageClipPokemonSprite_Free(UnkStruct_020298D8 *param0);
void ImageClipPokemonSprite_SetZ(UnkStruct_020298D8 *param0, int param1);
int ImageClipPokemonSprite_GetZ(UnkStruct_020298D8 *param0);
void ImageClipPokemonSprite_SetPosition(UnkStruct_020298D8 *param0, int param1, int param2);
BOOL ImageClipPokemonSprite_IsScreenTouched(UnkStruct_020298D8 *param0);
BOOL ImageClipPokemonSprite_IsTouchInHitTable(UnkStruct_020298D8 *param0, int param1, int param2);
void ImageClipPokemonSprite_GetCenter(UnkStruct_020298D8 *param0, int *xCenter, int *yCenter);
void ImageClipPokemonSprite_GetSize(UnkStruct_020298D8 *param0, int *param1, int *param2);
BOOL ImageClipPokemonSprite_IsTouchedByTouch(UnkStruct_020298D8 *param0, int *param1, int *param2, NNSG2dCharacterData *param3);
BOOL ImageClipPokemonSprite_IsPixelHit(UnkStruct_020298D8 *param0, int param1, int param2, NNSG2dCharacterData *param3);
void ImageClipPokemonSprite_GetPixelBounds(UnkStruct_020298D8 *param0, ImageClipPixelBounds *param1);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02259098_H
