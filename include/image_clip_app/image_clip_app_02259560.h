#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02259560_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02259560_H

#include <nnsys.h>

#include "image_clip_app/struct_image_clip_app_02259560.h"

void ImageClipSpriteResource_SetZ(ImageClipSpriteResource *param0, int param1);
BOOL ImageClipSpriteResource_IsHit(ImageClipSpriteResource *param0, int param1, int param2);
BOOL ImageClipSpriteResource_IsPixelHit(ImageClipSpriteResource *param0, int *param1, int *param2, NNSG2dCharacterData **param3);
void ImageClipSpriteResource_SetPosition(ImageClipSpriteResource *param0, int param1, int param2);
void ImageClipSpriteResource_GetPosition(ImageClipSpriteResource *param0, int *param1, int *param2);
void ImageClipSpriteResource_GetSize(ImageClipSpriteResource *param0, int *param1, int *param2);
void ImageClipSpriteResource_GetBounds(ImageClipSpriteResource *param0, int *param1, int *param2, int *param3, int *param4);
void ImageClipSpriteResource_Move(ImageClipSpriteResource *param0, int param1, int param2);
void ImageClipSpriteResource_GetBoundingBox(ImageClipSpriteResource *param0, int *param1, int *param2, int *param3, int *param4);
void ImageClipSpriteResource_GetCenter(ImageClipSpriteResource *param0, int *param1, int *param2);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02259560_H
