#ifndef POKEPLATINUM_IMAGE_CLIP_APP_H
#define POKEPLATINUM_IMAGE_CLIP_APP_H

#include <nnsys.h>

#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_0225500C.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"

ImageClipSpriteManager *ImageClipSprite_New(int param0, enum HeapID heapID);
void ImageClipSprite_Free(ImageClipSpriteManager *param0);
ImageClipSprite *ImageClipSprite_Add(ImageClipSpriteConfig *param0);
BOOL ImageClipSprite_IsTouched(ImageClipSprite *param0);
BOOL ImageClipSprite_HitTest(ImageClipSprite *param0, int *param1, int *param2, NNSG2dCharacterData *param3);
BOOL ImageClipSprite_ContainsTouch(ImageClipSprite *param0, int param1, int param2);
void ImageClipSprite_SetPosition(ImageClipSprite *param0, s16 param1, s16 param2);
void ImageClipSprite_GetPosition(ImageClipSprite *param0, int *param1, int *param2);
void ImageClipSprite_GetDimensions(ImageClipSprite *param0, int *param1, int *param2);
void ImageClipSprite_SetVisible(ImageClipSprite *param0, BOOL param1);
void ImageClipSprite_SetPriority(ImageClipSprite *param0, int param1);
int ImageClipSprite_GetPriority(ImageClipSprite *param0);
void ImageClipSprite_GetDimensionOffset(ImageClipSprite *param0, int *param1, int *param2);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_H
