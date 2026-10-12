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
    ImageClipSpriteResource *item;
    int remainingFrames;
    int speed;
} PhotoAccessoryRendererTransition;

typedef struct {
    PhotoAccessoryRenderer *renderer;
    int fromGroup;
    int fromIndex;
    int toGroup;
    int toIndex;
    BOOL doneFlag;
    int stepTimer;
    int state;
    int fromRemaining;
    int toRemaining;
    PhotoAccessoryRendererTransition *transitions;
    int transitionCount;
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
    param0->context.softSpriteManager = param1->softSpriteManager;
    param0->context.chars = param1->chars;
    param0->context.palettes = param1->palettes;
    param0->context.extraResource = param1->extraResource;
    param0->context.bgConfig = param1->bgConfig;
    param0->context.spriteManager = param1->spriteManager;
    param0->groups.resourceList = param1->resourceList;
    param0->groups.fashionCase = param1->fashionCase;

    PhotoAccessoryRenderer_LoadBackground(param0, 0);
    PhotoAccessoryRenderer_InitGroups(param0, param1);
}

void PhotoAccessoryRenderer_Free(PhotoAccessoryRenderer *param0)
{
    int v0;

    PhotoAccessoryRenderer_ClearItems(param0);

    for (v0 = 0; v0 < (3 + 1); v0++) {
        PhotoAccessoryRenderer_FreeGroup(&param0->groups.groups[v0]);
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

    v0.spriteManager = param0->context.spriteManager;
    v0.resourceIndex = param2;
    v0.softSpriteManager = param0->context.softSpriteManager;
    v0.xPos = 0;
    v0.yPos = 0;

    switch (param1) {
    case 0:
        v4 = param2;
        v5 = 0;
        v0.paletteSlot = param0->context.extraResource[param2];
        break;
    case 1:
        v4 = param2 + 100;
        v5 = param2 + 1;
        v0.paletteSlot = 0;
        break;
    case 2:
        v4 = param2 + 100;
        v5 = param2 + 1;
        v0.paletteSlot = 0;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    v0.chars = param0->context.chars[v4];
    v0.palette = param0->context.palettes[v5];

    GF_ASSERT(v0.chars);
    GF_ASSERT(v0.palette);

    v3 = PhotoAccessoryRenderer_GetGroupIndex(param1, param2, param0->groups.fashionCase);
    v1 = ImageClipSprite_Add(&v0);
    v2 = ImageClipResourceList_Alloc(param0->groups.resourceList, v1, param1);

    ImageClipResourceList_InsertAfter(v2, param0->groups.groups[param1].items[v3].prev);
    ImageClipSpriteResource_GetSize(v2, &v8, &v9);
    PhotoAccessoryRenderer_GetItemPosition(param1, param2, &v6, &v7, v8, v9, param0->groups.fashionCase);
    ImageClipSpriteResource_SetPosition(v2, v6, v7);
    PhotoAccessoryRenderer_UpdateItemEnabled(param0, v1, param1, v3);
}

void PhotoAccessoryRenderer_InsertItem(PhotoAccessoryRenderer *param0, int param1, int param2, ImageClipSpriteResource *param3)
{
    ImageClipResourceList_InsertAfter(param3, param0->groups.groups[param1].items + param2);
    PhotoAccessoryRenderer_UpdateItemEnabled(param0, param3->data, param1, param2);
}

void PhotoAccessoryRenderer_RemoveItem(ImageClipSpriteResource *param0)
{
    ImageClipResourceList_RemoveNode(param0);
}

void PhotoAccessoryRenderer_ClearItems(PhotoAccessoryRenderer *param0)
{
    int v0, v1;

    for (v0 = 0; v0 < 3; v0++) {
        for (v1 = 0; v1 < param0->groups.groups[v0].capacity; v1++) {
            ImageClipResourceList_RemoveAll(param0->groups.groups[v0].items + v1);
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
    v0 = v1->next;

    while (v0 != v1) {
        if ((v0->category == 0) || (v0->category == 1) || (v0->category == 2)) {
            ImageClipSprite_SetPriority(v0->data, v3);
        }

        v3--;

        v0 = v0->next;
    }
}

BOOL PhotoAccessoryRenderer_SetSelection(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    if (param0->groups.scrolling == 0) {
        PhotoAccessoryRenderer_StartScrollTask(param0, param0->groups.currentGroup, param0->groups.groups[param0->groups.currentGroup].currentIndex, param1, param2);

        param0->groups.currentGroup = param1;
        param0->groups.groups[param1].currentIndex = param2;

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

    for (v3 = 1; v3 < param0->groups.groups[param1].capacity; v3++) {
        if (param2 == 0) {
            v4 = (v3 + v1) % param0->groups.groups[param1].capacity;
        } else {
            v4 = v1 - v3;

            if (v4 < 0) {
                v4 += param0->groups.groups[param1].capacity;
            }
        }

        v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, v4);

        if (v0->next != v0) {
            v5 = PhotoAccessoryRenderer_SetSelection(param0, param1, v4);
            return v5;
        }
    }

    return 0;
}

void PhotoAccessoryRenderer_SetSelectionImmediate(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    PhotoAccessoryRenderer_SetCurrentGroupEnabled(param0, 0);

    param0->groups.currentGroup = param1;
    param0->groups.groups[param1].currentIndex = param2;

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
    v0 = v1->next;

    while (v0 != v1) {
        v2 = 0;

        v2 = ImageClipSpriteResource_IsPixelHit(v0, param1, param2, param3);

        if (v2 == 1) {
            return v0;
        }

        v0 = v0->next;
    }

    return NULL;
}

void PhotoAccessoryRenderer_LoadBackground(PhotoAccessoryRenderer *param0, int param1)
{
    ImageClipBgTemplate v0;

    v0.bgConfig = param0->context.bgConfig;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.charMember = (param1) * 2 + 129;
    v0.paletteMember = 133;
    v0.tilemapMember = (param1) * 2 + 129 + 1;
    v0.destTilemapX = 8;
    v0.destTilemapY = 129;
    v0.bgLayer = 3;
    v0.paletteSize = 1;
    v0.paletteOffset = 2;
    v0.charOffset = 0;
    v0.heapID = HEAP_ID_14;

    ImageClipBg_Init(&param0->context.bg, &v0);

    param0->groups.backdropIndex = param1;
}

void PhotoAccessoryRenderer_ScrollBackground(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, BOOL *param4)
{
    ImageClipBgTemplate v0;
    int v1, v2;

    v0.bgConfig = param0->context.bgConfig;
    v0.narcID = NARC_INDEX_GRAPHIC__IMAGECLIP;
    v0.charMember = (param1) * 2 + 129;
    v0.paletteMember = 133;
    v0.tilemapMember = (param1) * 2 + 129 + 1;
    v0.destTilemapX = 8;
    v0.destTilemapY = 129;
    v0.bgLayer = 3;
    v0.paletteSize = 1;
    v0.paletteOffset = 2;
    v0.charOffset = 0;
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

    ImageClipBg_StartScroll(&param0->context.bg, &v0, v1, v2, param3, param4);

    param0->groups.backdropIndex = param1;
}

void PhotoAccessoryRenderer_FreeBackground(PhotoAccessoryRenderer *param0)
{
    ImageClipBg_Free(&param0->context.bg);
}

int PhotoAccessoryRenderer_GetGroup(PhotoAccessoryRenderer *param0)
{
    GF_ASSERT(param0);
    return param0->groups.currentGroup;
}

int PhotoAccessoryRenderer_GetIndex(PhotoAccessoryRenderer *param0, int param1)
{
    PhotoAccessoryRendererGroup v0;

    GF_ASSERT(param0);

    v0 = param0->groups.groups[param1];
    return v0.currentIndex;
}

void PhotoAccessoryRenderer_MoveItem(PhotoAccessoryRenderer *param0, int param1, int param2, int param3, int param4)
{
    ImageClipSpriteResource *v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    ImageClipSpriteResource_Move(v0, param3, param4);
}

BOOL PhotoAccessoryRenderer_IsIdle(PhotoAccessoryRenderer *param0)
{
    if (param0->groups.scrolling == 0) {
        return 1;
    }

    return 0;
}

static void PhotoAccessoryRenderer_InitGroups(PhotoAccessoryRenderer *param0, PhotoAccessoryRendererResources *param1)
{
    PhotoAccessoryRenderer_AllocGroup(&param0->groups.groups[0], param1->groupCapacity0);

    param0->groups.currentGroup = 0;

    PhotoAccessoryRenderer_SetListEnabled(param0->groups.groups[0].items, 1);
    PhotoAccessoryRenderer_AllocGroup(&param0->groups.groups[1], param1->groupCapacity1);
    PhotoAccessoryRenderer_AllocGroup(&param0->groups.groups[2], param1->groupCapacity2);
    PhotoAccessoryRenderer_AllocGroup(&param0->groups.groups[3], 1);
}

static void PhotoAccessoryRenderer_SetListEnabled(ImageClipSpriteResource *param0, int param1)
{
    ImageClipSpriteResource *v0 = param0->next;

    while (v0 != (param0)) {
        if ((v0->category == 0) || (v0->category == 1) || (v0->category == 2)) {
            ImageClipSprite_SetVisible(v0->data, param1);
        }

        v0 = v0->next;
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

    param0->items = Heap_Alloc(HEAP_ID_14, sizeof(ImageClipSpriteResource) * param1);
    param0->capacity = param1;
    param0->currentIndex = 0;

    for (v0 = 0; v0 < param0->capacity; v0++) {
        param0->items[v0].next = param0->items + v0;
        param0->items[v0].prev = param0->items + v0;

        PhotoAccessoryRenderer_SetListEnabled(param0->items + v0, 0);
    }
}

static void PhotoAccessoryRenderer_FreeGroup(PhotoAccessoryRendererGroup *param0)
{
    Heap_Free(param0->items);
    param0->items = NULL;
    memset(param0, 0, sizeof(PhotoAccessoryRendererGroup));
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetCurrentIcon(PhotoAccessoryRenderer *param0)
{
    PhotoAccessoryRendererGroup v0;

    v0 = param0->groups.groups[param0->groups.currentGroup];
    return &v0.items[v0.currentIndex];
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetIcon(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    PhotoAccessoryRendererGroup v0;

    v0 = param0->groups.groups[param1];
    return &v0.items[param2];
}

static int PhotoAccessoryRenderer_CountGroupIcons(PhotoAccessoryRenderer *param0, int param1, int param2)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    int v2 = 0;

    v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    v1 = v0->next;

    while (v1 != v0) {
        v2++;
        v1 = v1->next;
    }

    return v2;
}

static ImageClipSpriteResource *PhotoAccessoryRenderer_GetNthIcon(PhotoAccessoryRenderer *param0, int param1, int param2, int param3)
{
    ImageClipSpriteResource *v0;
    ImageClipSpriteResource *v1;
    int v2 = 0;

    v0 = PhotoAccessoryRenderer_GetIcon(param0, param1, param2);
    v1 = v0->next;

    while (v1 != v0) {
        if (v2 == param3) {
            return v1;
        }

        v2++;
        v1 = v1->next;
    }

    return NULL;
}

static void PhotoAccessoryRenderer_UpdateItemEnabled(PhotoAccessoryRenderer *param0, ImageClipSprite *param1, int param2, int param3)
{
    if ((param0->groups.currentGroup != param2) || (param0->groups.groups[param2].currentIndex != param3)) {
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

    v1->renderer = param0;
    v1->fromGroup = param1;
    v1->fromIndex = param2;
    v1->toGroup = param3;
    v1->toIndex = param4;
    v1->state = 0;
    v1->fromRemaining = PhotoAccessoryRenderer_CountGroupIcons(param0, param1, param2);
    v1->toRemaining = PhotoAccessoryRenderer_CountGroupIcons(param0, param3, param4);
    v1->transitionCount = v1->fromRemaining + v1->toRemaining;
    v1->transitions = Heap_Alloc(HEAP_ID_13, sizeof(PhotoAccessoryRendererTransition) * v1->transitionCount);

    GF_ASSERT(v1->transitions);

    memset(v1->transitions, 0, sizeof(PhotoAccessoryRendererTransition) * v1->transitionCount);
    param0->groups.scrolling = 1;
}

static void PhotoAccessoryRenderer_ScrollTask(SysTask *param0, void *param1)
{
    PhotoAccessoryRendererScrollTask *v0 = param1;
    int v1;
    int v2;

    switch (v0->state) {
    case 0:
        PhotoAccessoryRenderer_MoveItem(v0->renderer, v0->toGroup, v0->toIndex, 0, -132);
        PhotoAccessoryRenderer_SetItemEnabledAt(v0->renderer, v0->toGroup, v0->toIndex, 1);

        v0->doneFlag = 0;
        v2 = (v0->renderer->groups.backdropIndex + 1) % 2;
        PhotoAccessoryRenderer_ScrollBackground(v0->renderer, v2, 2, 5, &v0->doneFlag);

        v0->stepTimer = PhotoAccessoryRenderer_DivideRoundUp(v0->fromRemaining, 1);
        v0->state++;
        break;
    case 1:
        for (v1 = 0; v1 < v0->stepTimer; v1++) {
            if ((v0->fromRemaining - 1) >= 0) {
                ImageClipSpriteResource *v3;

                v0->fromRemaining--;
                v3 = PhotoAccessoryRenderer_GetNthIcon(v0->renderer, v0->fromGroup, v0->fromIndex, v0->fromRemaining);
                PhotoAccessoryRenderer_AddTransition(v3, v0->transitions, v0->transitionCount);
            }
        }

        if (v0->fromRemaining == 0) {
            v0->stepTimer = PhotoAccessoryRenderer_DivideRoundUp(v0->toRemaining, 2);
            v0->state++;
        }
        break;
    case 2:
        for (v1 = 0; v1 < v0->stepTimer; v1++) {
            if ((v0->toRemaining - 1) >= 0) {
                ImageClipSpriteResource *v4;

                v0->toRemaining--;
                v4 = PhotoAccessoryRenderer_GetNthIcon(v0->renderer, v0->toGroup, v0->toIndex, v0->toRemaining);

                PhotoAccessoryRenderer_AddTransition(v4, v0->transitions, v0->transitionCount);
            }
        }

        if (v0->toRemaining == 0) {
            v0->state++;
            v0->stepTimer = 0;
        }
        break;
    case 3:
        v0->stepTimer++;

        if (v0->stepTimer > 3) {
            if (v0->doneFlag) {
                v0->state++;
            }
        }
        break;
    case 4:
        PhotoAccessoryRenderer_SetItemEnabledAt(v0->renderer, v0->fromGroup, v0->fromIndex, 0);
        PhotoAccessoryRenderer_MoveItem(v0->renderer, v0->fromGroup, v0->fromIndex, 0, -132);

        v0->renderer->groups.scrolling = 0;

        Heap_Free(v0->transitions);
        SysTask_FinishAndFreeParam(param0);

        return;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    PhotoAccessoryRenderer_UpdateTransitions(v0->transitions, v0->transitionCount);
}

static void PhotoAccessoryRenderer_AddTransition(ImageClipSpriteResource *param0, PhotoAccessoryRendererTransition *param1, int param2)
{
    PhotoAccessoryRendererTransition *v0 = PhotoAccessoryRenderer_FindTransitionSlot(param1, param2);

    v0->item = param0;
    v0->remainingFrames = 3;
    v0->speed = (132 / 3);
}

static PhotoAccessoryRendererTransition *PhotoAccessoryRenderer_FindTransitionSlot(PhotoAccessoryRendererTransition *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param1; v0++) {
        if (param0[v0].item == NULL) {
            return param0 + v0;
        }
    }

    return NULL;
}

static void PhotoAccessoryRenderer_UpdateTransitions(PhotoAccessoryRendererTransition *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param1; v0++) {
        if (param0[v0].item) {
            PhotoAccessoryRenderer_UpdateTransition(param0 + v0);
        }
    }
}

static void PhotoAccessoryRenderer_UpdateTransition(PhotoAccessoryRendererTransition *param0)
{
    int v0, v1;

    ImageClipSpriteResource_GetPosition(param0->item, &v0, &v1);
    v1 += param0->speed;
    ImageClipSpriteResource_SetPosition(param0->item, v0, v1);

    param0->remainingFrames--;

    if (param0->remainingFrames <= 0) {
        memset(param0, 0, sizeof(PhotoAccessoryRendererTransition));
    }
}

static int PhotoAccessoryRenderer_DivideRoundUp(int param0, int param1)
{
    param0 += param1 - (param0 % param1);
    return param0 / param1;
}
