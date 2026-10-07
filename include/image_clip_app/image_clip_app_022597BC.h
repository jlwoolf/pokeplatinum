#ifndef POKEPLATINUM_IMAGE_CLIP_APP_022597BC_H
#define POKEPLATINUM_IMAGE_CLIP_APP_022597BC_H

#include "image_clip_app/struct_image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_02259820.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"
#include "image_clip_app/struct_image_clip_app_0225AF44.h"

void ImageClipBg_Init(ImageClipBg *param0, ImageClipBgTemplate *param1);
void ImageClipBg_Free(ImageClipBg *param0);
void ImageClipBg_InitBackgroundAnimation(ImageClipBgAnimation *param0, PhotoRendererBgTemplate *param1);
void ImageClipBg_UpdateBackgroundAnimation(ImageClipBgAnimation *param0, int param1);
void ImageClipBg_StopBackgroundAnimation(ImageClipBgAnimation *param0);
void ImageClipBg_StartScroll(ImageClipBg *param0, ImageClipBgTemplate *param1, int param2, int param3, int param4, BOOL *param5);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_022597BC_H
