#include "image_clip_app/image_clip_app_02259484.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/struct_image_clip_app_02259484.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"

#include "heap.h"

void ImageClipResourceList_Init(ImageClipResourceList *param0, int param1, enum HeapID heapID)
{
    param0->unk_00 = Heap_Alloc(heapID, sizeof(ImageClipSpriteResource) * param1);
    GF_ASSERT(param0->unk_00);
    memset(param0->unk_00, 0, sizeof(ImageClipSpriteResource) * param1);
    param0->unk_04 = param1;
}

void ImageClipResourceList_Free(ImageClipResourceList *param0)
{
    Heap_Free(param0->unk_00);
    param0->unk_00 = NULL;
    param0->unk_04 = 0;
}

ImageClipSpriteResource *ImageClipResourceList_Alloc(ImageClipResourceList *param0, void *param1, int param2)
{
    int v0;

    GF_ASSERT(param0->unk_00);
    GF_ASSERT(param0->unk_04);

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_00[v0].unk_00 == NULL) {
            break;
        }
    }

    GF_ASSERT(param0->unk_04 > v0);

    param0->unk_00[v0].unk_00 = param1;
    param0->unk_00[v0].unk_04 = param2;

    return param0->unk_00 + v0;
}

void ImageClipResourceList_ResetNode(ImageClipSpriteResource *param0)
{
    memset(param0, 0, sizeof(ImageClipSpriteResource));
}

void ImageClipResourceList_InsertAfter(ImageClipSpriteResource *param0, ImageClipSpriteResource *param1)
{
    param0->unk_08 = param1->unk_08;
    param1->unk_08->unk_0C = param0;
    param0->unk_0C = param1;
    param1->unk_08 = param0;
}

void ImageClipResourceList_RemoveNode(ImageClipSpriteResource *param0)
{
    param0->unk_0C->unk_08 = param0->unk_08;
    param0->unk_08->unk_0C = param0->unk_0C;
}

void ImageClipResourceList_RemoveAll(ImageClipSpriteResource *param0)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;

    v0 = param0->unk_08;

    while (v0 != param0) {
        v1 = v0->unk_08;

        ImageClipResourceList_RemoveNode(v0);
        ImageClipResourceList_ResetNode(v0);

        v0 = v1;
    }
}
