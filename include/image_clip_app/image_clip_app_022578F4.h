#ifndef POKEPLATINUM_IMAGE_CLIP_APP_022578F4_H
#define POKEPLATINUM_IMAGE_CLIP_APP_022578F4_H

#include <nitro/gx.h>
#include <nnsys.h>

#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_0225B388.h"

#include "pokemon.h"

void PhotoRenderer_Init(PhotoRenderer *param0, PhotoRendererTemplate *param1);
void PhotoRenderer_Free(PhotoRenderer *param0);
void PhotoRenderer_SetupPokemonSprite(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3, int param4, int param5, int param6);
void PhotoRenderer_CreatePokemonSprite(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3);
void PhotoRenderer_CreatePokemonSpriteExact(PhotoRenderer *param0, Pokemon *param1, PokemonSpriteTemplate *param2, int param3);
void PhotoRenderer_AppendSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1);
void PhotoRenderer_RemoveSprite(ImageClipSpriteResource *param0);
void PhotoRenderer_DeletePokemonSprite(PhotoRenderer *param0);
BOOL PhotoRenderer_CreateAccessorySprite(PhotoRenderer *param0, int param1, int param2, int param3, int param4);
BOOL PhotoRenderer_AddSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1, NNSG2dCharacterData **param2);
void PhotoRenderer_PopSprite(PhotoRenderer *param0, ImageClipSpriteResource *param1);
void PhotoRenderer_ClearSprites(PhotoRenderer *param0);
void PhotoRenderer_MoveSprites(PhotoRenderer *param0, int param1, int param2);
void PhotoRenderer_MoveVisibleSprites(PhotoRenderer *param0, int param1, int param2);
void PhotoRenderer_PanSprites(PhotoRenderer *param0, int param1, int param2, int param3, int param4);
void PhotoRenderer_AssignZOrder(PhotoRenderer *param0);
void PhotoRenderer_AssignZOrderFrom(PhotoRenderer *param0, int param1);
void PhotoRenderer_OffsetZ(PhotoRenderer *param0, int param1);
BOOL PhotoRenderer_IsScreenTouched(PhotoRenderer *param0);
BOOL PhotoRenderer_IsTouchInScreen(PhotoRenderer *param0, int param1, int param2);
ImageClipSpriteResource *PhotoRenderer_GetTouchedSprite(PhotoRenderer *param0, int *param1, int *param2, NNSG2dCharacterData **param3);
void PhotoRenderer_LoadBackground(PhotoRenderer *param0, int param1, enum HeapID heapID);
void PhotoRenderer_FreeBackground(PhotoRenderer *param0);
void PhotoRenderer_GetPokemonSpriteCenter(PhotoRenderer *param0, int *param1, int *param2);
int PhotoRenderer_GetSpriteCount(PhotoRenderer *param0);
void PhotoRenderer_GetMaxOutOfBounds(PhotoRenderer *param0, int *param1, int *param2);
void PhotoRenderer_SetSpriteDiffuse(PhotoRenderer *param0, GXRgb param1);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_022578F4_H
