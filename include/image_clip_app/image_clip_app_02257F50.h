#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02257F50_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02257F50_H

#include <nnsys.h>

#include "image_clip_app/struct_image_clip_app_02257F50.h"
#include "image_clip_app/struct_image_clip_app_02258470.h"
#include "image_clip_app/struct_image_clip_app_0225899C.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"

void PhotoAccessoryRenderer_Init(PhotoAccessoryRenderer *param0, PhotoAccessoryRendererResources *param1);
void PhotoAccessoryRenderer_Free(PhotoAccessoryRenderer *param0);
int PhotoAccessoryRenderer_GetGroupIndex(int param0, int param1, FashionCaseCounts *param2);
void PhotoAccessoryRenderer_GetItemPosition(int param0, int param1, int *param2, int *param3, int param4, int param5, FashionCaseCounts *param6);
void PhotoAccessoryRenderer_AddItem(PhotoAccessoryRenderer *param0, int param1, int param2);
void PhotoAccessoryRenderer_InsertItem(PhotoAccessoryRenderer *param0, int param1, int param2, ImageClipSpriteResource *param3);
void PhotoAccessoryRenderer_RemoveItem(ImageClipSpriteResource *param0);
void PhotoAccessoryRenderer_ClearItems(PhotoAccessoryRenderer *param0);
void PhotoAccessoryRenderer_UpdateZOrder(PhotoAccessoryRenderer *param0);
BOOL PhotoAccessoryRenderer_SetSelection(PhotoAccessoryRenderer *param0, int param1, int param2);
BOOL PhotoAccessoryRenderer_ScrollSelection(PhotoAccessoryRenderer *param0, int param1, int param2);
void PhotoAccessoryRenderer_SetSelectionImmediate(PhotoAccessoryRenderer *param0, int param1, int param2);
BOOL PhotoAccessoryRenderer_IsScreenTouched(PhotoAccessoryRenderer *param0);
BOOL PhotoAccessoryRenderer_IsTouchInScreen(PhotoAccessoryRenderer *param0, int param1, int param2);
ImageClipSpriteResource *PhotoAccessoryRenderer_GetTouchedItem(PhotoAccessoryRenderer *param0, int *param1, int *param2, NNSG2dCharacterData **param3);
void PhotoAccessoryRenderer_LoadBackground(PhotoAccessoryRenderer *param0, int param1);
void PhotoAccessoryRenderer_ScrollBackground(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, BOOL *param4);
void PhotoAccessoryRenderer_FreeBackground(PhotoAccessoryRenderer *param0);
int PhotoAccessoryRenderer_GetGroup(PhotoAccessoryRenderer *param0);
int PhotoAccessoryRenderer_GetIndex(PhotoAccessoryRenderer *param0, int param1);
void PhotoAccessoryRenderer_MoveItem(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, int param4);
BOOL PhotoAccessoryRenderer_IsIdle(PhotoAccessoryRenderer *param0);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02257F50_H
