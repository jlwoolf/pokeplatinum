#include "image_clip_app/image_clip_app.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/struct_image_clip_app_02254DE0.h"
#include "image_clip_app/struct_image_clip_app_0225500C.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"

#include "heap.h"
#include "software_sprite.h"
#include "system.h"
#include "touch_screen.h"

static ImageClipSprite *ImageClipSprite_FindFreeSlot(ImageClipSpriteManager *param0);
static SoftwareSprite *ImageClipSprite_LoadSoftwareSprite(ImageClipSpriteConfig *param0);
static void ImageClipSprite_BuildHitTable(ImageClipSprite *param0, TouchScreenHitTable *hitTable);

ImageClipSpriteManager *ImageClipSprite_New(int param0, enum HeapID heapID)
{
    ImageClipSpriteManager *v0 = Heap_Alloc(heapID, sizeof(ImageClipSpriteManager));
    v0->sprites = Heap_Alloc(heapID, sizeof(ImageClipSprite) * param0);
    memset(v0->sprites, 0, sizeof(ImageClipSprite) * param0);
    v0->count = param0;

    return v0;
}

void ImageClipSprite_Free(ImageClipSpriteManager *param0)
{
    Heap_Free(param0->sprites);
    Heap_Free(param0);
    param0 = NULL;
}

ImageClipSprite *ImageClipSprite_Add(ImageClipSpriteConfig *param0)
{
    ImageClipSprite *v0 = ImageClipSprite_FindFreeSlot(param0->spriteManager);
    GF_ASSERT(v0);

    v0->resourceIndex = param0->resourceIndex;
    v0->softSprite = ImageClipSprite_LoadSoftwareSprite(param0);

    return v0;
}

BOOL ImageClipSprite_IsTouched(ImageClipSprite *param0)
{
    TouchScreenHitTable v0;

    ImageClipSprite_BuildHitTable(param0, &v0);
    return TouchScreen_LocationHeld(&v0);
}

BOOL ImageClipSprite_HitTest(ImageClipSprite *param0, int *param1, int *param2, NNSG2dCharacterData *param3)
{
    BOOL v0;
    int v1, v2;
    int v3, v4;

    v0 = ImageClipSprite_IsTouched(param0);

    if (v0 == 0) {
        return 0;
    }

    ImageClipSprite_GetPosition(param0, &v1, &v2);

    *param1 = gSystem.touchX - v1;
    *param2 = gSystem.touchY - v2;

    for (v3 = (*param2 - 4); v3 < (*param2 + 4); v3++) {
        if (v3 >= 0) {
            for (v4 = (*param1 - 4); v4 < (*param1 + 4); v4++) {
                if (v4 >= 0) {
                    v0 = ImageClipGraphics_TestPixel(param3, v4, v3, 0);

                    if (v0 == 0) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

BOOL ImageClipSprite_ContainsTouch(ImageClipSprite *param0, int param1, int param2)
{
    TouchScreenHitTable v0;

    ImageClipSprite_BuildHitTable(param0, &v0);
    return TouchScreen_IsTouchInHitTable(&v0, param1, param2);
}

void ImageClipSprite_SetPosition(ImageClipSprite *param0, s16 param1, s16 param2)
{
    SoftwareSprite_SetPosition(param0->softSprite, param1, param2);
}

void ImageClipSprite_GetPosition(ImageClipSprite *param0, int *param1, int *param2)
{
    NNSG2dSVec2 v0;

    v0 = SoftwareSprite_GetPosition(param0->softSprite);
    *param1 = v0.x;
    *param2 = v0.y;
}

void ImageClipSprite_GetDimensions(ImageClipSprite *param0, int *param1, int *param2)
{
    NNSG2dSVec2 v0;

    v0 = SoftwareSprite_GetDimensions(param0->softSprite);
    *param1 = v0.x;
    *param2 = v0.y;
}

void ImageClipSprite_SetVisible(ImageClipSprite *param0, BOOL param1)
{
    SoftwareSprite_SetVisible(param0->softSprite, param1);
}

void ImageClipSprite_SetPriority(ImageClipSprite *param0, int param1)
{
    SoftwareSprite_SetPriority(param0->softSprite, param1);
}

int ImageClipSprite_GetPriority(ImageClipSprite *param0)
{
    return SoftwareSprite_GetPriority(param0->softSprite);
}

void ImageClipSprite_GetDimensionOffset(ImageClipSprite *param0, int *param1, int *param2)
{
    int v0, v1;

    ImageClipSprite_GetDimensions(param0, &v0, &v1);

    switch (v0) {
    case 16:
        *param1 = 0;
        break;
    case 32:
        *param1 = 10;
        break;
    case 64:
        *param1 = 20;
        break;
    }

    switch (v1) {
    case 16:
        *param2 = 0;
        break;
    case 32:
        *param2 = 10;
        break;
    case 64:
        *param2 = 20;
        break;
    }
}

static ImageClipSprite *ImageClipSprite_FindFreeSlot(ImageClipSpriteManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->count; v0++) {
        if (param0->sprites[v0].softSprite == NULL) {
            return param0->sprites + v0;
        }
    }

    return NULL;
}

static SoftwareSprite *ImageClipSprite_LoadSoftwareSprite(ImageClipSpriteConfig *param0)
{
    SoftwareSpriteTemplate v0;

    v0.softSpriteMan = param0->softSpriteManager;
    v0.chars = param0->chars;
    v0.palette = param0->palette;
    v0.xPos = param0->xPos;
    v0.yPos = param0->yPos;
    v0.rotation = 0;
    v0.alpha = 31;
    v0.priority = 0;
    v0.paletteSlot = param0->paletteSlot;

    return SoftwareSprite_Load(&v0);
}

static void ImageClipSprite_BuildHitTable(ImageClipSprite *param0, TouchScreenHitTable *hitTable)
{
    NNSG2dSVec2 v0 = SoftwareSprite_GetPosition(param0->softSprite);
    NNSG2dSVec2 v1 = SoftwareSprite_GetDimensions(param0->softSprite);

    hitTable->rect.top = v0.y;
    hitTable->rect.bottom = v0.y + v1.y;
    hitTable->rect.left = v0.x;
    hitTable->rect.right = v0.x + v1.x;
}
