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
    ImageClipGraphics *unk_00;
    PhotoRenderer *unk_04;
    PhotoAccessoryRenderer *unk_08;
    ContestScoreDisplay *unk_0C;
    ImageClipSpriteResource *unk_10;
    int unk_14;
    int unk_18;
    s16 unk_1C;
    s16 unk_1E;
    u8 unk_20;
    u8 unk_21;
    int unk_24;
    int unk_28;
    BOOL unk_2C;
    u32 unk_30;
} PhotoRendererControllerState;

typedef struct {
    PhotoAccessoryRenderer *unk_00;
    ImageClipSpriteResource *unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int *unk_24;
    u32 *unk_28;
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

    param0->unk_00 = Heap_Alloc(HEAP_ID_13, sizeof(PhotoRendererControllerState));
    memset(param0->unk_00, 0, sizeof(PhotoRendererControllerState));
    v0 = param0->unk_00;

    v0->unk_04 = param1;
    v0->unk_08 = param2;
    v0->unk_00 = param3;
    v0->unk_0C = param4;
    v0->unk_2C = param5;

    param0->unk_04 = PhotoRendererController_HandleTouchDown;
    param0->unk_08 = PhotoRendererController_HandleTouchUp;
    param0->unk_0C = PhotoRendererController_HandleTouchDrag;
    param0->unk_10 = PhotoRendererController_Free;
}

void PhotoRendererController_Free(PhotoRendererController *param0)
{
    Heap_Free(param0->unk_00);
    PhotoRendererController_InitInput(param0);
}

static void PhotoRendererController_HandleTouchDown(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    ImageClipSpriteResource *v1;
    BOOL v2;
    int v3, v4;
    int v5;
    int v6;

    v2 = PhotoRenderer_IsScreenTouched(v0->unk_04);

    if (v2) {
        v1 = PhotoRenderer_GetTouchedSprite(v0->unk_04, &v3, &v4, v0->unk_00->unk_38);

        if (v1) {
            if (v1->unk_04 == 3) {
                if (v0->unk_2C == 0) {
                    v1 = NULL;
                }
            }
        }

        if (v1 != NULL) {
            if (v1->unk_04 == 0) {
                PhotoRenderer_PopSprite(v0->unk_04, v1);
                v6 = 0;
            } else {
                PhotoRenderer_RemoveSprite(v1);
                v6 = ImageClipPokemonSprite_GetZ(v1->unk_00);
                ImageClipSpriteResource_GetPosition(v1, &v0->unk_24, &v0->unk_28);
            }

            PhotoRenderer_AssignZOrder(v0->unk_04);
            PhotoRendererController_SetActivePhoto(v0, v1, 1, v3, v4, v6);
            ImageClipGraphics_EnableWindow();
        }
    } else {
        v2 = PhotoAccessoryRenderer_IsScreenTouched(v0->unk_08);

        if (v2) {
            v1 = PhotoAccessoryRenderer_GetTouchedItem(v0->unk_08, &v3, &v4, v0->unk_00->unk_38);

            if (v1 != NULL) {
                PhotoAccessoryRenderer_RemoveItem(v1);
                PhotoAccessoryRenderer_UpdateZOrder(v0->unk_08);
                PhotoRendererController_SetActivePhoto(v0, v1, 0, v3, v4, 0);
                ImageClipGraphics_EnableWindow();
            }
        }
    }

    if (v0->unk_10) {
        int v7 = 1515;

        switch (v0->unk_10->unk_04) {
        case 0:
            param0->unk_08 = PhotoRendererController_HandleTouchUp;
            param0->unk_0C = PhotoRendererController_HandleTouchDrag;
            break;
        case 1:
            param0->unk_08 = PhotoRendererController_HandleAnimatedRelease;
            param0->unk_0C = PhotoRendererController_HandleNoOp;
            PhotoRendererController_BeginDrag(param0);
            v7 = 1662;
            break;
        case 3:
            param0->unk_08 = PhotoRendererController_HandleRotateRelease;
            param0->unk_0C = PhotoRendererController_HandleRotateDrag;
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
    PhotoRendererControllerState *v0 = param0->unk_00;

    if (v0->unk_10) {
        GF_ASSERT(v0->unk_10->unk_04 == 1);

        PhotoRendererController_StartMoveAnimation(v0, 4, v0->unk_1C, v0->unk_1E, v0->unk_10->unk_04, v0->unk_21);
        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleTouchUp(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    int v1;
    int v2;
    int v3, v4, v5, v6;
    int v7, v8;
    int v9, v10;
    BOOL v11;

    if (v0->unk_10) {
        PhotoRendererController_GetActivePhotoBounds(param0, &v3, &v4, &v5, &v6);

        v2 = PhotoRenderer_IsTouchInScreen(v0->unk_04, v5, v3);
        v2 += PhotoRenderer_IsTouchInScreen(v0->unk_04, v6, v3);
        v2 += PhotoRenderer_IsTouchInScreen(v0->unk_04, v5, v4);
        v2 += PhotoRenderer_IsTouchInScreen(v0->unk_04, v6, v4);

        if (v2 >= 4) {
            v11 = PhotoRenderer_AddSprite(v0->unk_04, v0->unk_10, v0->unk_00->unk_38);

            if (v11 == 0) {
                v9 = v0->unk_1C;
                v10 = v0->unk_1E;

                Sound_PlayEffect(SEQ_SE_DP_HYUN2_sseq);
                ContestScoreDisplay_DrawMessage(v0->unk_0C, 26, 385, 3);
                PhotoRendererController_StartMoveAnimation(v0, 4, v9, v10, v0->unk_10->unk_04, v0->unk_21);
            } else {
                PhotoRenderer_AssignZOrder(v0->unk_04);
                ImageClipGraphics_DisableWindow();
                v0->unk_30 = 0;
                Sound_PlayEffect(SEQ_SE_DP_BOX01_sseq);
            }
        } else {
            ImageClipSprite *v12 = v0->unk_10->unk_00;

            PhotoRendererController_GetPhotoBounds(param0, &v3, &v4, &v5, &v6);

            v2 = PhotoAccessoryRenderer_IsTouchInScreen(v0->unk_08, v5, v3);
            v2 += PhotoAccessoryRenderer_IsTouchInScreen(v0->unk_08, v6, v4);

            if (v2 < 2) {
                if (v0->unk_20 == 1) {
                    ImageClipSpriteResource_GetSize(v0->unk_10, &v7, &v8);

                    v9 = (8 + 2) + (MTRNG_Next() % ((112 - (2 * 2)) - v7));
                    v10 = (16 + 2) + (MTRNG_Next() % ((129 - (2 * 2)) - v8));
                } else {
                    v9 = v0->unk_1C;
                    v10 = v0->unk_1E;
                }

                Sound_PlayEffect(SEQ_SE_DP_HYUN2_sseq);
            } else {
                ImageClipSpriteResource_GetPosition(v0->unk_10, &v9, &v10);
                Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
            }

            if (v0->unk_20 == 1) {
                v0->unk_21 = PhotoAccessoryRenderer_GetGroupIndex(v0->unk_10->unk_04, v12->unk_00, v0->unk_08->unk_00.unk_04);
            }

            PhotoRendererController_StartMoveAnimation(v0, 4, v9, v10, v0->unk_10->unk_04, v0->unk_21);
        }

        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleTouchDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    int v1, v2;

    if (v0->unk_10 != NULL) {
        if ((gSystem.touchX != 0xffff) && (gSystem.touchX != 0xffff)) {
            v1 = gSystem.touchX - v0->unk_14;
            v2 = gSystem.touchY - v0->unk_18;

            ImageClipSpriteResource_SetPosition(v0->unk_10, v1, v2);
        }
    }
}

static void PhotoRendererController_HandleRotateRelease(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    BOOL v1, v2;
    int v3, v4;

    if (v0->unk_10) {
        PhotoRenderer_AppendSprite(v0->unk_04, v0->unk_10);
        PhotoRenderer_AssignZOrder(v0->unk_04);
        ImageClipGraphics_DisableWindow();

        v0->unk_30 = 0;

        Sound_PlayEffect(SEQ_SE_DP_BOX02_sseq);
        PhotoRendererController_ClearActivePhoto(v0);
    }
}

static void PhotoRendererController_HandleRotateDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    int v1, v2;
    int v3, v4;
    int v5, v6;
    int v7, v8;
    int v9, v10;

    if (v0->unk_10 != NULL) {
        if ((gSystem.touchX != 0xffff) && (gSystem.touchX != 0xffff)) {
            ImageClipSpriteResource_GetBounds(v0->unk_10, &v7, &v9, &v8, &v10);
            ImageClipSpriteResource_GetSize(v0->unk_10, &v1, &v2);

            v3 = gSystem.touchX - v0->unk_14;
            v4 = gSystem.touchY - v0->unk_18;

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
            PhotoRenderer_GetMaxOutOfBounds(v0->unk_04, &v7, &v8);

            v3 += v7;
            v4 += v8;

            PhotoRendererController_SetPhotoPosition(param0, v3, v4);
        }
    }
}

static void PhotoRendererController_BeginDrag(PhotoRendererController *param0)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    ImageClipSprite *v1;
    int v2;

    if (v0->unk_10) {
        GF_ASSERT(v0->unk_10->unk_04 == 1);

        v1 = v0->unk_10->unk_00;

        PhotoRenderer_FreeBackground(v0->unk_04);
        PhotoRenderer_LoadBackground(v0->unk_04, v1->unk_00, HEAP_ID_14);
    }
}

static void PhotoRendererController_SetActivePhoto(PhotoRendererControllerState *param0, ImageClipSpriteResource *param1, int param2, int param3, int param4, int param5)
{
    int v0, v1;

    ImageClipSpriteResource_GetPosition(param1, &v0, &v1);

    param0->unk_10 = param1;
    param0->unk_1C = v0;
    param0->unk_1E = v1;
    param0->unk_20 = param2;
    param0->unk_14 = param3;
    param0->unk_18 = param4;

    if (param2 == 0) {
        param0->unk_21 = PhotoAccessoryRenderer_GetIndex(param0->unk_08, param0->unk_10->unk_04);
    } else {
        param0->unk_21 = 0;
    }

    param0->unk_30 = 1;

    ImageClipSpriteResource_SetZ(param1, param5);
}

static void PhotoRendererController_ClearActivePhoto(PhotoRendererControllerState *param0)
{
    param0->unk_10 = NULL;
    param0->unk_1C = 0;
    param0->unk_1E = 0;
    param0->unk_20 = 0;
    param0->unk_21 = 0;
}

static void PhotoRendererController_GetPhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4)
{
    PhotoRendererControllerState *v0 = param0->unk_00;
    int v1, v2;
    int v3, v4;

    ImageClipSpriteResource_GetSize(v0->unk_10, &v1, &v2);
    ImageClipSpriteResource_GetPosition(v0->unk_10, &v3, &v4);

    *param1 = v4;
    *param2 = v4 + v2;
    *param3 = v3;
    *param4 = v3 + v1;
}

static void PhotoRendererController_GetActivePhotoBounds(PhotoRendererController *param0, int *param1, int *param2, int *param3, int *param4)
{
    PhotoRendererControllerState *v0 = param0->unk_00;

    ImageClipSpriteResource_GetBoundingBox(v0->unk_10, param1, param2, param3, param4);
}

static void PhotoRendererController_StartMoveAnimation(PhotoRendererControllerState *param0, int param1, int param2, int param3, int param4, int param5)
{
    SysTask *v0;
    PhotoRendererControllerMoveAnimation *v1;
    int v2, v3;

    v0 = SysTask_StartAndAllocateParam(PhotoRendererController_MoveAnimationTask, sizeof(PhotoRendererControllerMoveAnimation), 0, 13);
    v1 = SysTask_GetParam(v0);

    v1->unk_00 = param0->unk_08;
    v1->unk_04 = param0->unk_10;
    v1->unk_20 = param1;
    v1->unk_10 = param2;
    v1->unk_14 = param3;
    v1->unk_18 = param4;
    v1->unk_1C = param5;
    v1->unk_24 = &param0->unk_08->unk_00.unk_3C;
    v1->unk_28 = &param0->unk_30;

    ImageClipSpriteResource_GetPosition(param0->unk_10, &v2, &v3);

    v1->unk_08 = (v1->unk_10 - v2) / param1;
    v1->unk_0C = (v1->unk_14 - v3) / param1;

    param0->unk_30 = 0;
}

static void PhotoRendererController_MoveAnimationTask(SysTask *param0, void *param1)
{
    PhotoRendererControllerMoveAnimation *v0 = param1;
    int v1, v2;

    if (*v0->unk_24 == 1) {
        return;
    }

    ImageClipSpriteResource_GetPosition(v0->unk_04, &v1, &v2);

    v1 += v0->unk_08;
    v2 += v0->unk_0C;

    v0->unk_20--;

    if ((v0->unk_20 < 0) || ((v0->unk_08 == 0) && (v0->unk_0C == 0))) {
        ImageClipSpriteResource_SetPosition(v0->unk_04, v0->unk_10, v0->unk_14);
        PhotoAccessoryRenderer_InsertItem(v0->unk_00, v0->unk_18, v0->unk_1C, v0->unk_04);
        PhotoAccessoryRenderer_UpdateZOrder(v0->unk_00);

        if (*(v0->unk_28) == 0) {
            ImageClipGraphics_DisableWindow();
        }

        SysTask_FinishAndFreeParam(param0);
    } else {
        ImageClipSpriteResource_SetPosition(v0->unk_04, v1, v2);
    }
}

static void PhotoRendererController_PlayPickupSound(PhotoRendererControllerState *param0)
{
    if (param0->unk_10->unk_04 == 0) {
        ImageClipSprite *v0 = param0->unk_10->unk_00;
        ContestScoreDisplay_DrawMessage(param0->unk_0C, 26, 386, v0->unk_00);
    } else if (param0->unk_10->unk_04 == 1) {
        ImageClipSprite *v0 = param0->unk_10->unk_00;
        ContestScoreDisplay_DrawMessage(param0->unk_0C, 26, 388, v0->unk_00);
    }
}

static void PhotoRendererController_SetPhotoPosition(PhotoRendererController *param0, int param1, int param2)
{
    PhotoRendererControllerState *v0 = param0->unk_00;

    ImageClipSpriteResource_SetPosition(v0->unk_10, param1, param2);
    PhotoRenderer_MoveVisibleSprites(v0->unk_04, param1 - v0->unk_24, param2 - v0->unk_28);

    v0->unk_24 = param1;
    v0->unk_28 = param2;
}
