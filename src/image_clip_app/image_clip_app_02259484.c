#include "image_clip_app/image_clip_app_02259484.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/struct_image_clip_app_02259484.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"

#include "heap.h"

void ImageClipResourceList_Init(ImageClipResourceList *param0, int param1, enum HeapID heapID)
{
    param0->nodes = Heap_Alloc(heapID, sizeof(ImageClipSpriteResource) * param1);
    GF_ASSERT(param0->nodes);
    memset(param0->nodes, 0, sizeof(ImageClipSpriteResource) * param1);
    param0->capacity = param1;
}

void ImageClipResourceList_Free(ImageClipResourceList *param0)
{
    Heap_Free(param0->nodes);
    param0->nodes = NULL;
    param0->capacity = 0;
}

ImageClipSpriteResource *ImageClipResourceList_Alloc(ImageClipResourceList *param0, void *param1, int param2)
{
    int v0;

    GF_ASSERT(param0->nodes);
    GF_ASSERT(param0->capacity);

    for (v0 = 0; v0 < param0->capacity; v0++) {
        if (param0->nodes[v0].data == NULL) {
            break;
        }
    }

    GF_ASSERT(param0->capacity > v0);

    param0->nodes[v0].data = param1;
    param0->nodes[v0].category = param2;

    return param0->nodes + v0;
}

void ImageClipResourceList_ResetNode(ImageClipSpriteResource *param0)
{
    memset(param0, 0, sizeof(ImageClipSpriteResource));
}

void ImageClipResourceList_InsertAfter(ImageClipSpriteResource *param0, ImageClipSpriteResource *param1)
{
    param0->next = param1->next;
    param1->next->prev = param0;
    param0->prev = param1;
    param1->next = param0;
}

void ImageClipResourceList_RemoveNode(ImageClipSpriteResource *param0)
{
    param0->prev->next = param0->next;
    param0->next->prev = param0->prev;
}

void ImageClipResourceList_RemoveAll(ImageClipSpriteResource *param0)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;

    v0 = param0->next;

    while (v0 != param0) {
        v1 = v0->next;

        ImageClipResourceList_RemoveNode(v0);
        ImageClipResourceList_ResetNode(v0);

        v0 = v1;
    }
}
