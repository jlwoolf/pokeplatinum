#ifndef POKEPLATINUM_IMAGE_CLIP_APP_0225894C_H
#define POKEPLATINUM_IMAGE_CLIP_APP_0225894C_H

#include "struct_defs/fashion_case.h"

#include "image_clip_app/struct_image_clip_app_0225899C.h"

void FashionCaseCounts_Init(const FashionCase *fashionCase, FashionCaseCounts *param1);
u32 FashionCaseCounts_GetAccessoryCount(const FashionCaseCounts *param0, u32 param1);
u32 FashionCaseCounts_GetBackdropCount(const FashionCaseCounts *param0, u32 param1);
u32 FashionCaseCounts_FindBackdropIndex(const FashionCaseCounts *param0, u32 param1);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_0225894C_H
