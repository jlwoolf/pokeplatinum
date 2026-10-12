#include "image_clip_app/image_clip_app_022589E0.h"

#include <nitro.h>
#include <string.h>

#include "image_clip_app/image_clip_app_02255094.h"
#include "image_clip_app/image_clip_app_022578F4.h"
#include "image_clip_app/image_clip_app_02257F50.h"
#include "image_clip_app/image_clip_app_022588F0.h"
#include "image_clip_app/image_clip_app_02259098.h"
#include "image_clip_app/image_clip_app_02259560.h"
#include "image_clip_app/image_clip_app_0225A428.h"
#include "image_clip_app/struct_image_clip_app_02255040.h"
#include "image_clip_app/struct_image_clip_app_02257964.h"
#include "image_clip_app/struct_image_clip_app_02257F50.h"
#include "image_clip_app/struct_image_clip_app_02258A48.h"
#include "image_clip_app/struct_image_clip_app_02259560.h"
#include "image_clip_app/struct_image_clip_app_0225A0E4.h"
#include "image_clip_app/struct_image_clip_app_0225A428.h"

#include "heap.h"
#include "math_util.h"
#include "sound_playback.h"
#include "sys_task_extensions.h"
#include "sys_task_manager.h"
#include "system.h"

typedef struct {
    ImageClipGraphics *graphics;
    PhotoRenderer *photoRenderer;
    PhotoAccessoryRenderer *accessoryRenderer;
    ContestScoreDisplay *scoreDisplay;
    ImageClipSpriteResource *activeSprite;
    int touchX;
    int touchY;
    s16 spriteX;
    s16 spriteY;
    u8 isAccessory;
    u8 accessoryIndex;
    int lastX;
    int lastY;
    BOOL allowPokemon;
    u32 dragActive;
} PhotoRendererControllerState;

typedef struct {
    PhotoAccessoryRenderer *accessoryRenderer;
    ImageClipSpriteResource *sprite;
    int stepX;
    int stepY;
    int targetX;
    int targetY;
    int targetGroup;
    int targetIndex;
    int remainingFrames;
    int *scrollFlag;
    u32 *dragFlag;
} PhotoRendererControllerMoveAnimation;

static void PhotoRendererController_HandleTouchDown(PhotoRendererController *param0);
static void PhotoRendererController_HandleTouchUp(PhotoRendererController *param0);
static void PhotoRendererController_HandleTouchDrag(PhotoRendererController *param0);
static void PhotoRendererController_SetActivePhoto(PhotoRendererControllerState *param0, ImageClipSpriteResource *param1, int param2, int param3, int param4, int param5);
static void PhotoRendererController_ClearActivePhoto(PhotoRendererControllerState *param0);
static void PhotoRendererController_PlayPickupSound(PhotoRendererControllerState *param0);
static void PhotoRendererController_HandleRotateRelease(PhotoRendererController *param0);
static void PhotoRendererController_HandleRotateDrag(PhotoRendererController *param0);
static void PhotoRendererController_GetPhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4);
static void PhotoRendererController_GetActivePhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4);
static void PhotoRendererController_SetPhotoPosition(PhotoRendererController *param0, int param1, int param2);
static void PhotoRendererController_HandleAnimatedRelease(PhotoRendererController *param0);
static void PhotoRendererController_HandleNoOp(PhotoRendererController *param0);
static void PhotoRendererController_BeginDrag(PhotoRendererController *param0);
static void PhotoRendererController_StartMoveAnimation(PhotoRendererControllerState *param0, int param1, int param2, int param3, int param4, int param5);
static void PhotoRendererController_MoveAnimationTask(SysTask *param0, void *param1);

void PhotoRendererController_New(PhotoRendererController *param0, PhotoRenderer *param1, PhotoAccessoryRenderer *param2, ImageClipGraphics *param3, ContestScoreDisplay *param4, BOOL param5)
{
    PhotoRendererControllerState *v0;

    PhotoRendererController_InitInput(param0);

    param0->data = Heap_Alloc(HEAP_ID_13, sizeof(PhotoRendererControllerState));
    memset(param0->data, 0, sizeof(PhotoRendererControllerState));
    v0 = param0->data;

    v0->photoRenderer = param1;
    v0->accessoryRenderer = param2;
    v0->graphics = param3;
    v0->scoreDisplay = param4;
    v0->allowPokemon = param5;

    param0->onTouchDown = PhotoRendererController_HandleTouchDown;
    param0->onTouchUp = PhotoRendererController_HandleTouchUp;
    param0->onTouchDrag = PhotoRendererController_HandleTouchDrag;
    param0->onFree = PhotoRendererController_Free;
}

void PhotoRendererController_Free(PhotoRendererController *param0)
{
    Heap_Free(param0->data);
    PhotoRendererController_InitInput(param0);
}

static void PhotoRendererController_HandleTouchDown(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    ImageClipSpriteResource *v1;
    BOOL v2;
    int v3, v4;
    int v5;
    int v6;

    v2 = PhotoRenderer_IsScreenTouched(v0->photoRenderer);

    if (v2) {
        v1 = PhotoRenderer_GetTouchedSprite(v0->photoRenderer, &v3, &v4, v0->graphics->characterData);

        if (v1) {
            if (v1->category == 3) {
                if (v0->allowPokemon == 0) {
                    v1 = NULL;
                }
            }
        }

        if (v1 != NULL) {
            if (v1->category == 0) {
                PhotoRenderer_PopSprite(v0->photoRenderer, v1);
                v6 = 0;
            } else {
                PhotoRenderer_RemoveSprite(v1);
                v6 = ImageClipPokemonSprite_GetZ(v1->data);
                ImageClipSpriteResource_GetPosition(v1, &v0->lastX, &v0->lastY);
            }

            PhotoRenderer_AssignZOrder(v0->photoRenderer);
            PhotoRendererController_SetActivePhoto(v0, v1, 1, v3, v4, v6);
            ImageClipGraphics_EnableWindow();
        }
    } else {
        v2 = PhotoAccessoryRenderer_IsScreenTouched(v0->accessoryRenderer);

        if (v2) {
            v1 = PhotoAccessoryRenderer_GetTouchedItem(v0->accessoryRenderer, &v3, &v4, v0->graphics->characterData);

            if (v1 != NULL) {
                PhotoAccessoryRenderer_RemoveItem(v1);
                PhotoAccessoryRenderer_UpdateZOrder(v0->accessoryRenderer);
                PhotoRendererController_SetActivePhoto(v0, v1, 0, v3, v4, 0);
                ImageClipGraphics_EnableWindow();
            }
        }
    }

    if (v0->activeSprite) {
        int v7 = 1515;

        switch (v0->activeSprite->category) {
        case 0:
            param0->onTouchUp = PhotoRendererController_HandleTouchUp;
            param0->onTouchDrag = PhotoRendererController_HandleTouchDrag;
            break;
        case 1:
            param0->onTouchUp = PhotoRendererController_HandleAnimatedRelease;
            param0->onTouchDrag = PhotoRendererController_HandleNoOp;
            PhotoRendererController_BeginDrag(param0);
            v7 = 1662;
            break;
        case 3:
            param0->onTouchUp = PhotoRendererController_HandleRotateRelease;
            param0->onTouchDrag = PhotoRendererController_HandleRotateDrag;
            break;
        default:
            break;
        }

        Sound_PlayEffect(v7);
        PhotoRendererController_PlayPickupSound(v0);
    }
}

static void PhotoRendererController_HandleNoOp(PhotoRendererController *param0)
{
    return;
}

static void PhotoRendererController_HandleAnimatedRelease(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;

    if (v0->activeSprite) {
        GF_ASSERT(v0->activeSprite->category == 1);

        PhotoRendererController_StartMoveAnimation(v0, 4, v0->spriteX, v0->spriteY, v0->activeSprite->category, v0->accessoryIndex);
        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleTouchUp(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    int v1;
    int v2;
    int v3, v4, v5, v6;
    int v7, v8;
    int v9, v10;
    BOOL v11;

    if (v0->activeSprite) {
        PhotoRendererController_GetActivePhotoBounds(param0, &v3, &v4, &v5, &v6);

        v2 = PhotoRenderer_IsTouchInScreen(v0->photoRenderer, v5, v3);
        v2 += PhotoRenderer_IsTouchInScreen(v0->photoRenderer, v6, v3);
        v2 += PhotoRenderer_IsTouchInScreen(v0->photoRenderer, v5, v4);
        v2 += PhotoRenderer_IsTouchInScreen(v0->photoRenderer, v6, v4);

        if (v2 >= 4) {
            v11 = PhotoRenderer_AddSprite(v0->photoRenderer, v0->activeSprite, v0->graphics->characterData);

            if (v11 == 0) {
                v9 = v0->spriteX;
                v10 = v0->spriteY;

                Sound_PlayEffect(SEQ_SE_DP_HYUN2_sseq);
                ContestScoreDisplay_DrawMessage(v0->scoreDisplay, 26, 385, 3);
                PhotoRendererController_StartMoveAnimation(v0, 4, v9, v10, v0->activeSprite->category, v0->accessoryIndex);
            } else {
                PhotoRenderer_AssignZOrder(v0->photoRenderer);
                ImageClipGraphics_DisableWindow();
                v0->dragActive = 0;
                Sound_PlayEffect(SEQ_SE_DP_BOX01_sseq);
            }
        } else {
            ImageClipSprite *v12 = v0->activeSprite->data;

            PhotoRendererController_GetPhotoBounds(param0, &v3, &v4, &v5, &v6);

            v2 = PhotoAccessoryRenderer_IsTouchInScreen(v0->accessoryRenderer, v5, v3);
            v2 += PhotoAccessoryRenderer_IsTouchInScreen(v0->accessoryRenderer, v6, v4);

            if (v2 < 2) {
                if (v0->isAccessory == 1) {
                    ImageClipSpriteResource_GetSize(v0->activeSprite, &v7, &v8);

                    v9 = (8 + 2) + (MTRNG_Next() % ((112 - (2 * 2)) - v7));
                    v10 = (16 + 2) + (MTRNG_Next() % ((129 - (2 * 2)) - v8));
                } else {
                    v9 = v0->spriteX;
                    v10 = v0->spriteY;
                }

                Sound_PlayEffect(SEQ_SE_DP_HYUN2_sseq);
            } else {
                ImageClipSpriteResource_GetPosition(v0->activeSprite, &v9, &v10);
                Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
            }

            if (v0->isAccessory == 1) {
                v0->accessoryIndex = PhotoAccessoryRenderer_GetGroupIndex(v0->activeSprite->category, v12->resourceIndex, v0->accessoryRenderer->groups.fashionCase);
            }

            PhotoRendererController_StartMoveAnimation(v0, 4, v9, v10, v0->activeSprite->category, v0->accessoryIndex);
        }

        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleTouchDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    int v1, v2;

    if (v0->activeSprite != NULL) {
        if ((gSystem.touchX != 0xffff) && (gSystem.touchX != 0xffff)) {
            v1 = gSystem.touchX - v0->touchX;
            v2 = gSystem.touchY - v0->touchY;

            ImageClipSpriteResource_SetPosition(v0->activeSprite, v1, v2);
        }
    }
}

static void PhotoRendererController_HandleRotateRelease(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    BOOL v1, v2;
    int v3, v4;

    if (v0->activeSprite) {
        PhotoRenderer_AppendSprite(v0->photoRenderer, v0->activeSprite);
        PhotoRenderer_AssignZOrder(v0->photoRenderer);
        ImageClipGraphics_DisableWindow();

        v0->dragActive = 0;

        Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleRotateDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    int v1, v2;
    int v3, v4;
    int v5, v6;
    int v7, v8;
    int v9, v10;

    if (v0->activeSprite != NULL) {
        if ((gSystem.touchX != 0xffff) && (gSystem.touchX != 0xffff)) {
            ImageClipSpriteResource_GetBounds(v0->activeSprite, &v7, &v9, &v8, &v10);
            ImageClipSpriteResource_GetSize(v0->activeSprite, &v1, &v2);

            v3 = gSystem.touchX - v0->touchX;
            v4 = gSystem.touchY - v0->touchY;

            v5 = v3 + v7;
            v6 = v4 + v8;
            v1 -= v9;
            v2 -= v10;

            if (v5 <= (136 + 2)) {
                v3 = (136 + 2) - v7;
            } else {
                if (v3 + v1 >= ((136 + 2) + (112 - (2 * 2)))) {
                    v3 = ((136 + 2) + (112 - (2 * 2))) - v1;
                }
            }

            if (v6 <= (16 + 2)) {
                v4 = (16 + 2) - v8;
            } else {
                if (v4 + v2 >= ((16 + 2) + (129 - (2 * 2)))) {
                    v4 = ((16 + 2) + (129 - (2 * 2))) - v2;
                }
            }

            PhotoRendererController_SetPhotoPosition(param0, v3, v4);
            PhotoRenderer_GetMaxOutOfBounds(v0->photoRenderer, &v7, &v8);

            v3 += v7;
            v4 += v8;

            PhotoRendererController_SetPhotoPosition(param0, v3, v4);
        }
    }
}

static void PhotoRendererController_BeginDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->data;
    ImageClipSprite *v1;
    int v2;

    if (v0->activeSprite) {
        GF_ASSERT(v0->activeSprite->category == 1);

        v1 = v0->activeSprite->data;

        PhotoRenderer_FreeBackground(v0->photoRenderer);
        PhotoRenderer_LoadBackground(v0->photoRenderer, v1->resourceIndex, HEAP_ID_14);
    }
}

static void PhotoRendererController_SetActivePhoto(PhotoRendererControllerState *param0, ImageClipSpriteResource *param1, int param2, int param3, int param4, int param5)
{
    int v0, v1;

    ImageClipSpriteResource_GetPosition(param1, &v0, &v1);

    param0->activeSprite = param1;
    param0->spriteX = v0;
    param0->spriteY = v1;
    param0->isAccessory = param2;
    param0->touchX = param3;
    param0->touchY = param4;

    if (param2 == 0) {
        param0->accessoryIndex = PhotoAccessoryRenderer_GetIndex(param0->accessoryRenderer, param0->activeSprite->category);
    } else {
        param0->accessoryIndex = 0;
    }

    param0->dragActive = 1;

    ImageClipSpriteResource_SetZ(param1, param5);
}

static void PhotoRendererController_ClearActivePhoto(PhotoRendererControllerState *param0)
{
    param0->activeSprite = NULL;
    param0->spriteX = 0;
    param0->spriteY = 0;
    param0->isAccessory = 0;
    param0->accessoryIndex = 0;
}

static void PhotoRendererController_GetPhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4)
{
    PhotoRendererControllerState *v0 = param0->data;
    int v1, v2;
    int v3, v4;

    ImageClipSpriteResource_GetSize(v0->activeSprite, &v1, &v2);
    ImageClipSpriteResource_GetPosition(v0->activeSprite, &v3, &v4);

    *param1 = v4;
    *param2 = v4 + v2;
    *param3 = v3;
    *param4 = v3 + v1;
}

static void PhotoRendererController_GetActivePhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4)
{
    PhotoRendererControllerState *v0 = param0->data;

    ImageClipSpriteResource_GetBoundingBox(v0->activeSprite, param1, param2, param3, param4);
}

static void PhotoRendererController_StartMoveAnimation(PhotoRendererControllerState *param0, int param1, int param2, int param3, int param4, int param5)
{
    SysTask *v0;
    PhotoRendererControllerMoveAnimation *v1;
    int v2, v3;

    v0 = SysTask_StartAndAllocateParam(PhotoRendererController_MoveAnimationTask, sizeof(PhotoRendererControllerMoveAnimation), 0, 13);
    v1 = SysTask_GetParam(v0);

    v1->accessoryRenderer = param0->accessoryRenderer;
    v1->sprite = param0->activeSprite;
    v1->remainingFrames = param1;
    v1->targetX = param2;
    v1->targetY = param3;
    v1->targetGroup = param4;
    v1->targetIndex = param5;
    v1->scrollFlag = &param0->accessoryRenderer->groups.scrolling;
    v1->dragFlag = &param0->dragActive;

    ImageClipSpriteResource_GetPosition(param0->activeSprite, &v2, &v3);

    v1->stepX = (v1->targetX - v2) / param1;
    v1->stepY = (v1->targetY - v3) / param1;

    param0->dragActive = 0;
}

static void PhotoRendererController_MoveAnimationTask(SysTask *param0, void *param1)
{
    PhotoRendererControllerMoveAnimation *v0 = param1;
    int v1, v2;

    if (*v0->scrollFlag == 1) {
        return;
    }

    ImageClipSpriteResource_GetPosition(v0->sprite, &v1, &v2);

    v1 += v0->stepX;
    v2 += v0->stepY;

    v0->remainingFrames--;

    if ((v0->remainingFrames < 0) || ((v0->stepX == 0) && (v0->stepY == 0))) {
        ImageClipSpriteResource_SetPosition(v0->sprite, v0->targetX, v0->targetY);
        PhotoAccessoryRenderer_InsertItem(v0->accessoryRenderer, v0->targetGroup, v0->targetIndex, v0->sprite);
        PhotoAccessoryRenderer_UpdateZOrder(v0->accessoryRenderer);

        if (*(v0->dragFlag) == 0) {
            ImageClipGraphics_DisableWindow();
        }

        SysTask_FinishAndFreeParam(param0);
    } else {
        ImageClipSpriteResource_SetPosition(v0->sprite, v1, v2);
    }
}

static void PhotoRendererController_PlayPickupSound(PhotoRendererControllerState *param0)
{
    if (param0->activeSprite->category == 0) {
        ImageClipSprite *v0 = param0->activeSprite->data;
        ContestScoreDisplay_DrawMessage(param0->scoreDisplay, 26, 386, v0->resourceIndex);
    } else if (param0->activeSprite->category == 1) {
        ImageClipSprite *v0 = param0->activeSprite->data;
        ContestScoreDisplay_DrawMessage(param0->scoreDisplay, 26, 388, v0->resourceIndex);
    }
}

static void PhotoRendererController_SetPhotoPosition(PhotoRendererController *param0, int param1, int param2)
{
    PhotoRendererControllerState *v0 = param0->data;

    ImageClipSpriteResource_SetPosition(v0->activeSprite, param1, param2);
    PhotoRenderer_MoveVisibleSprites(v0->photoRenderer, param1 - v0->lastX, param2 - v0->lastY);

    v0->lastX = param1;
    v0->lastY = param2;
}
