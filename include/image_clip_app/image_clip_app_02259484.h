#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02259484_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02259484_H

#include "constants/heap.h"

#include "image_clip_app/struct_image_clip_app_02259484.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"

void ImageClipResourceList_Init(ImageClipResourceList *param0, int param1, enum HeapID heapID);
void ImageClipResourceList_Free(ImageClipResourceList *param0);
ImageClipSpriteResource *ImageClipResourceList_Alloc(ImageClipResourceList *param0, void *param1, int param2);
void ImageClipResourceList_ResetNode(ImageClipSpriteResource *param0);
void ImageClipResourceList_InsertAfter(ImageClipSpriteResource *param0, ImageClipSpriteResource *param1);
void ImageClipResourceList_RemoveNode(ImageClipSpriteResource *param0);
void ImageClipResourceList_RemoveAll(ImageClipSpriteResource *param0);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02259484_H
