#include "image_clip_app/image_clip_app_02257F50.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/image_clip_app.h"
#include "image_clip_app/image_clip_app_0225894C.h"
#include "image_clip_app/image_clip_app_02259484.h"
#include "image_clip_app/image_clip_app_02259560.h"
#include "image_clip_app/image_clip_app_022597BC.h"
#include "image_clip_app/struct_image_clip_app_0225500C.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"
#include "image_clip_app/struct_image_clip_app_02257F50.h"
#include "image_clip_app/struct_image_clip_app_02257F50_sub1_sub1.h"
#include "image_clip_app/struct_image_clip_app_02258470.h"
#include "image_clip_app/struct_image_clip_app_0225899C.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_022599A0.h"

#include "heap.h"
#include "math_util.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "touch_screen.h"

typedef struct {
    ImageClipSpriteResource *unk_00;
    int unk_04;
    int unk_08;
} PhotoAccessoryRendererTransition;

typedef struct {
    PhotoAccessoryRenderer *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    BOOL unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    PhotoAccessoryRendererTransition *unk_28;
    int unk_2C;
} PhotoAccessoryRendererScrollTask;

static void PhotoAccessoryRenderer_InitGroups(PhotoAccessoryRenderer *param0, PhotoAccessoryRendererResources *param1);
static void PhotoAccessoryRenderer_SetListEnabled(ImageClipSpriteResource *param0, int param1);
static void PhotoAccessoryRenderer_AllocGroup(PhotoAccessoryRendererGroup *param0, int param1);
static void PhotoAccessoryRenderer_FreeGroup(PhotoAccessoryRendererGroup *param0);
static ImageClipSpriteResource *PhotoAccessoryRenderer_GetCurrentIcon(PhotoAccessoryRenderer *param0);
static ImageClipSpriteResource *PhotoAccessoryRenderer_GetIcon(PhotoAccessoryRenderer *param0, int param1, int param2);
static int PhotoAccessoryRenderer_CountGroupIcons(PhotoAccessoryRenderer *param0, int param1, int param2);
static ImageClipSpriteResource *PhotoAccessoryRenderer_GetNthIcon(PhotoAccessoryRenderer *param0, int param1, int param2, int param3);
static void PhotoAccessoryRenderer_SetCurrentGroupEnabled(PhotoAccessoryRenderer *param0, int param1);
static void PhotoAccessoryRenderer_UpdateItemEnabled(PhotoAccessoryRenderer *param0, ImageClipSprite *param1, int param2, int param3);
static void PhotoAccessoryRenderer_GetGridPosition(int param0, int *param1, int *param2);
static void PhotoAccessoryRenderer_StartScrollTask(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, int param4);
static void PhotoAccessoryRenderer_ScrollTask(SysTask *param0, void *param1);
static void PhotoAccessoryRenderer_AddTransition(ImageClipSpriteResource *param0, PhotoAccessoryRendererTransition *param1, int param2);
static PhotoAccessoryRendererTransition *PhotoAccessoryRenderer_FindTransitionSlot(PhotoAccessoryRendererTransition *param0, int param1);
static void PhotoAccessoryRenderer_UpdateTransitions(PhotoAccessoryRendererTransition *param0, int param1);
static void PhotoAccessoryRenderer_UpdateTransition(PhotoAccessoryRendererTransition *param0);
static int PhotoAccessoryRenderer_DivideRoundUp(int param0, int param1);

void PhotoAccessoryRenderer_Init(PhotoAccessoryRenderer *param0, PhotoAccessoryRendererResources *param1)
{
    param0->unk_44.unk_00 = param1->unk_00;
    param0->unk_44.unk_04 = param1->unk_04;
    param0->unk_44.unk_08 = param1->unk_08;
    param0->unk_44.unk_0C = param1->unk_0C;
    param0->unk_44.unk_10 = param1->unk_10;
    param0->unk_44.unk_14 = param1->unk_14;
    param0->unk_00.unk_08 = param1->unk_18;
    param0->unk_00.unk_04 = param1->unk_28;

    PhotoAccessoryRenderer_LoadBackground(param0, 0);
    PhotoAccessoryRenderer_InitGroups(param0, param1);
}

void PhotoAccessoryRenderer_Free(PhotoAccessoryRenderer *param0)
{
    int v0;

    PhotoAccessoryRenderer_ClearItems(param0);

    for (v0 = 0; v0 < (3 + 1); v0++) {
        PhotoAccessoryRenderer_FreeGroup(&param0->unk_00.unk_0C[v0]);
    }

    memset(param0, 0, sizeof(PhotoAccessoryRenderer));
}

int PhotoAccessoryRenderer_GetGroupIndex(int param0, int param1, FashionCaseCounts *param2)
{
    int v0;

    switch (param0) {
    case 0:
        if (param1 <= 5) {
            v0 = 0;
        } else if (param1 <= 11) {
            v0 = 1;
        } else if (param1 <= 17) {
            v0 = 2;
        } else if (param1 <= 21) {
            v0 = 3;
        } else if (param1 <= 28) {
            v0 = 4;
        } else if (param1 <= 33) {
            v0 = 5;
        } else if (param1 <= 38) {
            v0 = 6;
        } else if (param1 <= 42) {
            v0 = 7;
        } else if (param1 <= 49) {
            v0 = 8;
        } else if (param1 <= 55) {
            v0 = 9;
        } else if (param1 <= 60) {
            v0 = 10;
        } else if (param1 <= 71) {
            v0 = 11;
        } else if (param1 <= 91) {
            v0 = 12;
        } else if (param1 <= 99) {
            v0 = 13;
        }
        break;
    case 1:
        param1 = FashionCaseCounts_FindBackdropIndex(param2, param1);
        v0 = param1 / 9;
        break;
    case 2:
        param1 = FashionCaseCounts_FindBackdropIndex(param2, param1);
        v0 = param1 / 9;
        break;
    }

    return v0;
}

void PhotoAccessoryRenderer_GetItemPosition(int param0, int param1, int *param2, int *param3, int param4, int param5, FashionCaseCounts *param6)
{
    switch (param0) {
    case 0:
        *param2 = (8 + 2);
        *param3 = (16 + 2);
        *param2 += (MTRNG_Next() % ((112 - (2 * 2)) - param4));
        *param3 += (MTRNG_Next() % ((129 - (2 * 2)) - param5));
        break;
    case 1:
    case 2:
        param1 = FashionCaseCounts_FindBackdropIndex(param6, param1);
        PhotoAccessoryRenderer_GetGridPosition(param1, param2, param3);
        break;
    }
}

void PhotoAccessoryRenderer_AddItem(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    ImageClipSpriteConfig v0;
    ImageClipSprite *v1;
    ImageClipSpriteResource *v2;
    int v3;
    int v4, v5;
    int v6, v7;
    int v8, v9;

    v0.unk_00 = param0->unk_44.unk_14;
    v0.unk_18 = param2;
    v0.unk_04 = param0->unk_44.unk_00;
    v0.unk_10 = 0;
    v0.unk_14 = 0;

    switch (param1) {
    case 0:
        v4 = param2;
        v5 = 0;
        v0.unk_1C = param0->unk_44.unk_0C[param2];
        break;
    case 1:
        v4 = param2 + 100;
        v5 = param2 + 1;
        v0.unk_1C = 0;
        break;
    case 2:
        v4 = param2 + 100;
        v5 = param2 + 1;
        v0.unk_1C = 0;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    v0.unk_08 = param0->unk_44.unk_04[v4];
    v0.unk_0C = param0->unk_44.unk_08[v5];

    GF_ASSERT(v0.unk_08);
    GF_ASSERT(v0.unk_0C);

    v3 = PhotoAccessoryRenderer_GetGroupIndex(param1, param2, param0->unk_00.unk_04);
    v1 = ImageClipSprite_Add(&v0);
    v2 = ImageClipResourceList_Alloc(param0->unk_00.unk_08, v1, param1);

    ImageClipResourceList_InsertAfter(v2, param0->unk_00.unk_0C[param1].unk_00[v3].unk_0C);
    ImageClipSpriteResource_GetSize(v2, &v8, &v9);
    PhotoAccessoryRenderer_GetItemPosition(param1, param2, &v6, &v7, v8, v9, param0->unk_00.unk_04);
    ImageClipSpriteResource_SetPosition(v2, v6, v7);
    PhotoAccessoryRenderer_UpdateItemEnabled(param0, v1, param1, v3);
}

void PhotoAccessoryRenderer_InsertItem(PhotoAccessoryRenderer *param0, int param1, int param2, ImageClipSpriteResource *param3)
{
    ImageClipResourceList_InsertAfter(param3, param0->unk_00.unk_0C[param1].unk_00 + param2);
    PhotoAccessoryRenderer_UpdateItemEnabled(param0, param3->unk_00, param1, param2);
}

void PhotoAccessoryRenderer_RemoveItem(ImageClipSpriteResource *param0)
{
    ImageClipResourceList_RemoveNode(param0);
}

void PhotoAccessoryRenderer_ClearItems(PhotoAccessoryRenderer *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 3; v0++) {
        for (v1 = 0; v1 < param0->unk_00.unk_0C[v0].unk_04; v1++) {
            ImageClipResourceList_RemoveAll(param0->unk_00.unk_0C[v0].unk_00 + v1);
        }
    }
}

void PhotoAccessoryRenderer_UpdateZOrder(PhotoAccessoryRenderer *param0)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    BOOL v2;
    int v3 = -1;

    v1 = PhotoAccessoryRenderer_GetCurrentIcon(param0);
    v0 = v1->unk_08;

    while (v0 != v1) {
        if ((v0->unk_04 == 0) || (v0->unk_04 == 1) || (v0->unk_04 == 2)) {
            ImageClipSprite_SetPriority(v0->unk_00, v3);
        }

        v3--;

        v0 = v0->unk_08;
    }
}

BOOL PhotoAccessoryRenderer_SetSelection(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    if (param0->unk_00.unk_3C == 0) {
        PhotoAccessoryRenderer_StartScrollTask(param0, param0->unk_00.unk_00, param0->unk_00.unk_0C[param0->unk_00.unk_00].unk_08, param1, param2);

        param0->unk_00.unk_00 = param1;
        param0->unk_00.unk_0C[param1].unk_08 = param2;

        PhotoAccessoryRenderer_UpdateZOrder(param0);

        return 1;
    }

    return 0;
}

BOOL PhotoAccessoryRenderer_ScrollSelection(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    ImageClipSpriteResource *v0;
    int v1;
    int v2;
    int v3;
    int v4;
    BOOL v5;

    v1 = PhotoAccessoryRenderer_GetIndex(param0, param1);

    for (v3 = 1; v3 < param0->unk_00.unk_0C[param1].unk_04; v3++) {
        if (param2 == 0) {
            v4 = (v3 + v1) % param0->unk_00.unk_0C[param1].unk_04;
        } else {
            v4 = v1 - v3;

            if (v4 < 0) {
                v4 += param0->unk_00.unk_0C[param1].unk_04;
            }
        }

        v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, v4);

        if (v0->unk_08 != v0) {
            v5 = PhotoAccessoryRenderer_SetSelection(param0, param1, v4);
            return v5;
        }
    }

    return 0;
}

void PhotoAccessoryRenderer_SetSelectionImmediate(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    PhotoAccessoryRenderer_SetCurrentGroupEnabled(param0, 0);

    param0->unk_00.unk_00 = param1;
    param0->unk_00.unk_0C[param1].unk_08 = param2;

    PhotoAccessoryRenderer_SetCurrentGroupEnabled(param0, 1);
    PhotoAccessoryRenderer_UpdateZOrder(param0);
}

BOOL PhotoAccessoryRenderer_IsScreenTouched(PhotoAccessoryRenderer *param0)
{
    TouchScreenHitTable v0;

    v0.rect.top = (16 + 2);
    v0.rect.bottom = (16 + 2) + (129 - (2 * 2));
    v0.rect.left = (8 + 2);
    v0.rect.right = (8 + 2) + (112 - (2 * 2));

    return TouchScreen_LocationHeld(&v0);
}

BOOL PhotoAccessoryRenderer_IsTouchInScreen(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    TouchScreenHitTable v0;

    v0.rect.top = (16 + 2);
    v0.rect.bottom = (16 + 2) + (129 - (2 * 2));
    v0.rect.left = (8 + 2);
    v0.rect.right = (8 + 2) + (112 - (2 * 2));

    return TouchScreen_IsTouchInHitTable(&v0, param1, param2);
}

ImageClipSpriteResource *PhotoAccessoryRenderer_GetTouchedItem(PhotoAccessoryRenderer *param0, int *param1, int *param2, NNSG2dCharacterData **param3)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    BOOL v2;

    v1 = PhotoAccessoryRenderer_GetCurrentIcon(param0);
    v0 = v1->unk_08;

    while (v0 != v1) {
        v2 = 0;

        v2 = ImageClipSpriteResource_IsPixelHit(v0, param1, param2, param3);

        if (v2 == 1) {
            return v0;
        }

        v0 = v0->unk_08;
    }

    return NULL;
}

void PhotoAccessoryRenderer_LoadBackground(PhotoAccessoryRenderer *param0, int param1)
{
    ImageClipBgTemplate v0;

    v0.unk_00 = param0->unk_44.unk_10;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.unk_08 = (param1) * 2 + 129;
    v0.unk_0C = 133;
    v0.unk_10 = (param1) * 2 + 129 + 1;
    v0.unk_14 = 8;
    v0.unk_18 = 129;
    v0.unk_1C = 3;
    v0.unk_20 = 1;
    v0.unk_24 = 2;
    v0.unk_28 = 0;
    v0.heapID = HEAP_ID_14;

    ImageClipBg_Init(&param0->unk_44.unk_18, &v0);

    param0->unk_00.unk_40 = param1;
}

void PhotoAccessoryRenderer_ScrollBackground(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, BOOL *param4)
{
    ImageClipBgTemplate v0;
    int v1, v2;

    v0.unk_00 = param0->unk_44.unk_10;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.unk_08 = (param1) * 2 + 129;
    v0.unk_0C = 133;
    v0.unk_10 = (param1) * 2 + 129 + 1;
    v0.unk_14 = 8;
    v0.unk_18 = 129;
    v0.unk_1C = 3;
    v0.unk_20 = 1;
    v0.unk_24 = 2;
    v0.unk_28 = 0;
    v0.heapID = HEAP_ID_14;

    if (param2 & 1) {
        v1 = 112;
    } else {
        v1 = 0;
    }

    if (param2 & 2) {
        v2 = 129;
    } else {
        v2 = 0;
    }

    ImageClipBg_StartScroll(&param0->unk_44.unk_18, &v0, v1, v2, param3, param4);

    param0->unk_00.unk_40 = param1;
}

void PhotoAccessoryRenderer_FreeBackground(PhotoAccessoryRenderer *param0)
{
    ImageClipBg_Free(&param0->unk_44.unk_18);
}

int PhotoAccessoryRenderer_GetGroup(PhotoAccessoryRenderer *param0)
{
    GF_ASSERT(param0);
    return param0->unk_00.unk_00;
}

int PhotoAccessoryRenderer_GetIndex(PhotoAccessoryRenderer *param0, int param1)
{
    PhotoAccessoryRendererGroup v0;

    GF_ASSERT(param0);

    v0 = param0->unk_00.unk_0C[param1];
    return v0.unk_08;
}

void PhotoAccessoryRenderer_MoveItem(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, int param4)
{
    ImageClipSpriteResource *v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    ImageClipSpriteResource_Move(v0, param3, param4);
}

BOOL PhotoAccessoryRenderer_IsIdle(PhotoAccessoryRenderer *param0)
{
    if (param0->unk_00.unk_3C == 0) {
        return 1;
    }

    return 0;
}

static void PhotoAccessoryRenderer_InitGroups(PhotoAccessoryRenderer *param0, PhotoAccessoryRendererResources *param1)
{
    PhotoAccessoryRenderer_AllocGroup(&param0->unk_00.unk_0C[0], param1->unk_1C);

    param0->unk_00.unk_00 = 0;

    PhotoAccessoryRenderer_SetListEnabled(param0->unk_00.unk_0C[0].unk_00, 1);
    PhotoAccessoryRenderer_AllocGroup(&param0->unk_00.unk_0C[1], param1->unk_20);
    PhotoAccessoryRenderer_AllocGroup(&param0->unk_00.unk_0C[2], param1->unk_24);
    PhotoAccessoryRenderer_AllocGroup(&param0->unk_00.unk_0C[3], 1);
}

static void PhotoAccessoryRenderer_SetListEnabled(ImageClipSpriteResource *param0, int param1)
{
    ImageClipSpriteResource *v0 = param0->unk_08;

    while (v0 != (param0)) {
        if ((v0->unk_04 == 0) || (v0->unk_04 == 1) || (v0->unk_04 == 2)) {
            ImageClipSprite_SetVisible(v0->unk_00, param1);
        }

        v0 = v0->unk_08;
    }
}

static void PhotoAccessoryRenderer_SetItemEnabledAt(PhotoAccessoryRenderer *param0, int param1, int param2, int param3)
{
    ImageClipSpriteResource *v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    PhotoAccessoryRenderer_SetListEnabled(v0, param3);
}

static void PhotoAccessoryRenderer_SetCurrentGroupEnabled(PhotoAccessoryRenderer *param0, int param1)
{
    ImageClipSpriteResource *v0 = PhotoAccessoryRenderer_GetCurrentIcon(param0);
    PhotoAccessoryRenderer_SetListEnabled(v0, param1);
}

static void PhotoAccessoryRenderer_AllocGroup(PhotoAccessoryRendererGroup *param0, int param1)
{
    int v0;

    param0->unk_00 = Heap_Alloc(HEAP_ID_14, sizeof(ImageClipSpriteResource) * param1);
    param0->unk_04 = param1;
    param0->unk_08 = 0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        param0->unk_00[v0].unk_08 = param0->unk_00 + v0;
        param0->unk_00[v0].unk_0C = param0->unk_00 + v0;

        PhotoAccessoryRenderer_SetListEnabled(param0->unk_00 + v0, 0);
    }
}

static void PhotoAccessoryRenderer_FreeGroup(PhotoAccessoryRendererGroup *param0)
{
    Heap_Free(param0->unk_00);
    param0->unk_00 = NULL;
    memset(param0, 0, sizeof(PhotoAccessoryRendererGroup));
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetCurrentIcon(PhotoAccessoryRenderer *param0)
{
    PhotoAccessoryRendererGroup v0;

    v0 = param0->unk_00.unk_0C[param0->unk_00.unk_00];
    return &v0.unk_00[v0.unk_08];
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetIcon(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    PhotoAccessoryRendererGroup v0;

    v0 = param0->unk_00.unk_0C[param1];
    return &v0.unk_00[param2];
}

static int PhotoAccessoryRenderer_CountGroupIcons(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    int v2 = 0;

    v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    v1 = v0->unk_08;

    while (v1 != v0) {
        v2++;
        v1 = v1->unk_08;
    }

    return v2;
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetNthIcon(PhotoAccessoryRenderer *param0, int param1, int param2, int param3)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    int v2 = 0;

    v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    v1 = v0->unk_08;

    while (v1 != v0) {
        if (v2 == param3) {
            return v1;
        }

        v2++;
        v1 = v1->unk_08;
    }

    return NULL;
}

static void PhotoAccessoryRenderer_UpdateItemEnabled(PhotoAccessoryRenderer *param0, ImageClipSprite *param1, int param2, int param3)
{
    if ((param0->unk_00.unk_00 != param2) || (param0->unk_00.unk_0C[param2].unk_08 != param3)) {
        ImageClipSprite_SetVisible(param1, 0);
    } else {
        ImageClipSprite_SetVisible(param1, 1);
    }
}

static void PhotoAccessoryRenderer_GetGridPosition(int param0, int *param1, int *param2)
{
    int v0;
    int v1;

    param0 %= 9;

    v0 = param0 / 3;
    v1 = param0 % 3;

    *param2 = 8 * (v0 + 1);
    *param2 += 32 * v0;
    *param2 += 16;
    *param1 = 8 * (v1 + 1);
    *param1 += 24 * v1;
    *param1 += 8;
}

static void PhotoAccessoryRenderer_StartScrollTask(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, int param4)
{
    SysTask *v0 = SysTask_StartAndAllocateParam(PhotoAccessoryRenderer_ScrollTask, sizeof(PhotoAccessoryRendererScrollTask), 0, 13);
    PhotoAccessoryRendererScrollTask *v1 = SysTask_GetParam(v0);

    v1->unk_00 = param0;
    v1->unk_04 = param1;
    v1->unk_08 = param2;
    v1->unk_0C = param3;
    v1->unk_10 = param4;
    v1->unk_1C = 0;
    v1->unk_20 = PhotoAccessoryRenderer_CountGroupIcons(param0, param1, param2);
    v1->unk_24 = PhotoAccessoryRenderer_CountGroupIcons(param0, param3, param4);
    v1->unk_2C = v1->unk_20 + v1->unk_24;
    v1->unk_28 = Heap_Alloc(HEAP_ID_13, sizeof(PhotoAccessoryRendererTransition) * v1->unk_2C);

    GF_ASSERT(v1->unk_28);

    memset(v1->unk_28, 0, sizeof(PhotoAccessoryRendererTransition) * v1->unk_2C);
    param0->unk_00.unk_3C = 1;
}

static void PhotoAccessoryRenderer_ScrollTask(SysTask *param0, void *param1)
{
    PhotoAccessoryRendererScrollTask *v0 = param1;
    int v1;
    int v2;

    switch (v0->unk_1C) {
    case 0:
        PhotoAccessoryRenderer_MoveItem(v0->unk_00, v0->unk_0C, v0->unk_10, 0, -132);
        PhotoAccessoryRenderer_SetItemEnabledAt(v0->unk_00, v0->unk_0C, v0->unk_10, 1);

        v0->unk_14 = 0;
        v2 = (v0->unk_00->unk_00.unk_40 + 1) % 2;
        PhotoAccessoryRenderer_ScrollBackground(v0->unk_00, v2, 2, 5, &v0->unk_14);

        v0->unk_18 = PhotoAccessoryRenderer_DivideRoundUp(v0->unk_20, 1);
        v0->unk_1C++;
        break;
    case 1:
        for (v1 = 0; v1 < v0->unk_18; v1++) {
            if ((v0->unk_20 - 1) >= 0) {
                ImageClipSpriteResource *v3;

                v0->unk_20--;
                v3 = PhotoAccessoryRenderer_GetNthIcon(v0->unk_00, v0->unk_04, v0->unk_08, v0->unk_20);
                PhotoAccessoryRenderer_AddTransition(v3, v0->unk_28, v0->unk_2C);
            }
        }

        if (v0->unk_20 == 0) {
            v0->unk_18 = PhotoAccessoryRenderer_DivideRoundUp(v0->unk_24, 2);
            v0->unk_1C++;
        }
        break;
    case 2:
        for (v1 = 0; v1 < v0->unk_18; v1++) {
            if ((v0->unk_24 - 1) >= 0) {
                ImageClipSpriteResource *v4;

                v0->unk_24--;
                v4 = PhotoAccessoryRenderer_GetNthIcon(v0->unk_00, v0->unk_0C, v0->unk_10, v0->unk_24);

                PhotoAccessoryRenderer_AddTransition(v4, v0->unk_28, v0->unk_2C);
            }
        }

        if (v0->unk_24 == 0) {
            v0->unk_1C++;
            v0->unk_18 = 0;
        }
        break;
    case 3:
        v0->unk_18++;

        if (v0->unk_18 > 3) {
            if (v0->unk_14) {
                v0->unk_1C++;
            }
        }
        break;
    case 4:
        PhotoAccessoryRenderer_SetItemEnabledAt(v0->unk_00, v0->unk_04, v0->unk_08, 0);
        PhotoAccessoryRenderer_MoveItem(v0->unk_00, v0->unk_04, v0->unk_08, 0, -132);

        v0->unk_00->unk_00.unk_3C = 0;

        Heap_Free(v0->unk_28);
        SysTask_FinishAndFreeParam(param0);

        return;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    PhotoAccessoryRenderer_UpdateTransitions(v0->unk_28, v0->unk_2C);
}

static void PhotoAccessoryRenderer_AddTransition(ImageClipSpriteResource *param0, PhotoAccessoryRendererTransition *param1, int param2)
{
    PhotoAccessoryRendererTransition *v0 = PhotoAccessoryRenderer_FindTransitionSlot(param1, param2);

    v0->unk_00 = param0;
    v0->unk_04 = 3;
    v0->unk_08 = (132 / 3);
}

static PhotoAccessoryRendererTransition *PhotoAccessoryRenderer_FindTransitionSlot(PhotoAccessoryRendererTransition *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param1; v0++) {
        if (param0[v0].unk_00 == NULL) {
            return param0 + v0;
        }
    }

    return NULL;
}

static void PhotoAccessoryRenderer_UpdateTransitions(PhotoAccessoryRendererTransition *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param1; v0++) {
        if (param0[v0].unk_00) {
            PhotoAccessoryRenderer_UpdateTransition(param0 + v0);
        }
    }
}

static void PhotoAccessoryRenderer_UpdateTransition(PhotoAccessoryRendererTransition *param0)
{
    int v0, v1;

    ImageClipSpriteResource_GetPosition(param0->unk_00, &v0, &v1);
    v1 += param0->unk_08;
    ImageClipSpriteResource_SetPosition(param0->unk_00, v0, v1);

    param0->unk_04--;

    if (param0->unk_04 <= 0) {
        memset(param0, 0, sizeof(PhotoAccessoryRendererTransition));
    }
}

static int PhotoAccessoryRenderer_DivideRoundUp(int param0, int param1)
{
    param0 += param1 - (param0 % param1);
    return param0 / param1;
}
