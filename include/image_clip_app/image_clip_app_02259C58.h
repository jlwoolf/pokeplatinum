#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02259C58_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02259C58_H

#include "image_clip_app/funcptr_image_clip_app_02259D78.h"
#include "image_clip_app/struct_image_clip_app_02259C58.h"
#include "image_clip_app/struct_image_clip_app_02259C58_1.h"
#include "image_clip_app/struct_image_clip_app_02259C9C.h"
#include "image_clip_app/struct_image_clip_app_02259D2C.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"
#include "image_clip_app/struct_image_clip_app_0225A154.h"

void ImageClipUi_Init(ImageClipUi *param0, ImageClipUiTemplate *param1);
void ImageClipUi_InitTextButton(ImageClipUiTextButton *param0, ImageClipUiTextButtonTemplate *param1);
void ImageClipUi_Free(ImageClipUi *param0);
void ImageClipUi_FreeTextButton(ImageClipUiTextButton *param0);
void ImageClipUi_InvokeCallback(ImageClipUi *param0, int param1);
void ImageClipUi_UpdateSelection(ImageClipUiMenu *param0, int param1, int param2);
void ImageClipUi_SetCallback(ImageClipUi *param0, ImageClipUiCallback param1, void *param2, int param3);
void ImageClipUi_SetButtonHeld(ImageClipUi *param0);
void ImageClipUi_SetButtonIdle(ImageClipUi *param0);
void ImageClipUi_SetButtonPressed(ImageClipUi *param0);
void ImageClipUi_InitMenu(ImageClipUiMenu *param0, ImageClipGraphics *param1);
void ImageClipUi_FreeMenu(ImageClipUiMenu *param0, ImageClipGraphics *param1);
void ImageClipUi_HandleTouch(ImageClipUiMenu *param0);
void ImageClipUi_ResetSelection(ImageClipUiMenu *param0);
void ImageClipUi_MoveMenu(ImageClipUiMenu *param0, int param1, int param2);
void ImageClipUi_SetElementCallback(ImageClipUiMenu *param0, int param1, ImageClipUiCallback param2, void *param3, int param4);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02259C58_H
