#ifndef POKEPLATINUM_IMAGE_CLIP_APP_0225AF8C_H
#define POKEPLATINUM_IMAGE_CLIP_APP_0225AF8C_H

#include <nitro/gx.h>

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02029C88.h"

#include "image_clip_app/struct_image_clip_app_0225AF8C.h"
#include "image_clip_app/struct_image_clip_app_0225B1BC_decl.h"

PhotoSprite *PhotoSprite_CreateForDressUp(const PhotoSpriteConfig *param0, const DressUpPhoto *photo);
PhotoSprite *PhotoSprite_CreateForContest(const PhotoSpriteConfig *param0, const ContestPhoto *param1);
PhotoSprite *PhotoSprite_CreateForContestNoBackdrop(const PhotoSpriteConfig *param0, const ContestPhoto *param1);
void PhotoSprite_Update(PhotoSprite *param0);
void PhotoSprite_Free(PhotoSprite *param0);
void PhotoSprite_UpdateGraphics(PhotoSprite *param0);
void PhotoSprite_SetTransformEnabled(PhotoSprite *param0, BOOL param1);
void PhotoSprite_SetVisible(PhotoSprite *param0, BOOL param1);
void PhotoSprite_SetPosition(PhotoSprite *param0, int param1, int param2);
void PhotoSprite_SetOffset(PhotoSprite *param0, int param1, int param2);
void PhotoSprite_SetRotation(PhotoSprite *param0, u16 param1);
void PhotoSprite_SetScale(PhotoSprite *param0, fx32 param1, fx32 param2, fx32 param3);
void PhotoSprite_MoveTo(PhotoSprite *param0, int param1, int param2);
void PhotoSprite_MoveToWithOffset(PhotoSprite *param0, int param1, int param2, int param3);
void PhotoSprite_SetTint(PhotoSprite *param0, GXRgb param1);
void PhotoSprite_AdjustPriority(PhotoSprite *param0, int param1);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_0225AF8C_H
