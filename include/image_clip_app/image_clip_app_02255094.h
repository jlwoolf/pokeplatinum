#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02255094_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02255094_H

#include <nitro/fx/fx.h>
#include <nnsys.h>

#include "image_clip_app/struct_image_clip_app_02255CB8.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"

#include "bg_window.h"
#include "narc.h"
#include "software_sprite.h"
#include "sprite.h"

void ImageClipGraphics_Init(void);
void ImageClipGraphics_Free(void);
void ImageClipGraphics_InitManager(ImageClipGraphics *param0);
void ImageClipGraphics_FreeManager(ImageClipGraphics *param0);
void ImageClipGraphics_Render(ImageClipGraphics *param0);
void ImageClipGraphics_LoadTemplates(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1);
void ImageClipGraphics_FreeAllSprites(ImageClipGraphics *param0);
Sprite *ImageClipGraphics_AddSprite(ImageClipGraphics *param0, int param1, int param2, int param3, int param4, int param5);
void ImageClipGraphics_LoadTiles(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4, int param5);
void ImageClipGraphics_LoadPalette(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4, int param5, int param6);
void ImageClipGraphics_LoadCell(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4);
void ImageClipGraphics_LoadAnim(ImageClipGraphics *param0, NARC *param1, int param2, BOOL param3, int param4);
void ImageClipGraphics_RemoveTiles(ImageClipGraphics *param0, int param1);
void ImageClipGraphics_RemovePalette(ImageClipGraphics *param0, int param1);
void ImageClipGraphics_RemoveCell(ImageClipGraphics *param0, int param1);
void ImageClipGraphics_RemoveAnim(ImageClipGraphics *param0, int param1);
void ImageClipGraphics_LoadImageResources(ImageClipGraphics *param0, ImageClipGraphicsTemplates *param1);
void ImageClipGraphics_FreeResourceTemplates(ImageClipGraphicsTemplates *param0);
NNSG2dCharacterData *ImageClipGraphics_AddCharacterData(ImageClipGraphics *param0, void *param1, int param2);
void ImageClipGraphics_DisableWindow(void);
void ImageClipGraphics_EnableWindow(void);
void ImageClipGraphics_Update(ImageClipGraphics *param0);
void ImageClipGraphics_InitResourceTemplates(ImageClipGraphicsTemplates *param0, enum HeapID heapID);
int ImageClipGraphics_TestPixel(NNSG2dCharacterData *param0, int param1, int param2, int param3);
void ImageClipGraphics_InitSpriteManager(ImageClipGraphics *param0, const SoftwareSpriteManagerTemplate *param1, enum HeapID heapID);
void ImageClipGraphics_InitBackground(ImageClipGraphics *param0, BgConfig *param1, int param2);
void ImageClipGraphics_FreeSprites(ImageClipGraphics *param0);
void ImageClipGraphics_FreeBackground(ImageClipGraphics *param0);
void ImageClipGraphics_UpdatePokemonSprites(ImageClipGraphics *param0);
void ImageClipGraphics_DrawTransformed(ImageClipGraphics *param0, int param1, int param2, u16 param3, const VecFx32 *param4);
void ImageClipGraphics_InitNarc(ImageClipGraphics *param0, int param1);
void ImageClipGraphics_FreeNarc(ImageClipGraphics *param0);
void ImageClipGraphics_Flush(ImageClipGraphics *param0);
void ImageClipGraphics_UpdateSprites(ImageClipGraphics *param0);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02255094_H
