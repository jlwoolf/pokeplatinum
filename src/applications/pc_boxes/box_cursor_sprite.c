#include "applications/pc_boxes/box_cursor_sprite.h"

#include <nitro.h>
#include <string.h>

#include "constants/items.h"

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_view.h"
#include "applications/pc_boxes/box_mon_sprite_manager.h"
#include "applications/pc_boxes/box_party.h"
#include "applications/pc_boxes/box_held_item_icons.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_cursor_sprite.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "sprite.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    Sprite *sprite;
    u16 stepCount;
    u16 priorityChangeStep;
    u32 priority;
    fx32 y;
    fx32 targetY;
    fx32 x;
    fx32 angle;
    fx32 yStep;
    fx32 angleStep;
    fx32 amplitude;
    BoxCursorSprite *cursorSprite;
} BoxCursorSpriteAnimation;

static void BoxCursorSprite_CreateHeldMonSprite(BoxCursorSprite *param0);
static void BoxCursorSprite_GetWrapFlags(const BoxCursorSprite *param0, BOOL *param1, BOOL *param2);
static void BoxCursorSprite_MoveTask(SysTask *param0, void *param1);
static void BoxCursorSprite_PickUpTask(SysTask *param0, void *param1);
static void BoxCursorSprite_PlaceTask(SysTask *param0, void *param1);
static void BoxCursorSprite_StartSlideAnimation(BoxCursorSprite *param0, Sprite *param1, fx32 param2, s32 param3, u32 param4);
static BOOL BoxCursorSprite_IsSlideDone(BoxCursorSprite *param0);
static void BoxCursorSprite_SlideDone(void *param0);
static void BoxCursorSprite_SlideTask(SysTask *param0, void *param1);
static void BoxCursorSprite_PressTask(SysTask *param0, void *param1);
static void BoxCursorSprite_ReleasePressTask(SysTask *param0, void *param1);
static void BoxCursorSprite_PickUpItemTask(SysTask *param0, void *param1);
static void BoxCursorSprite_PlaceItemTask(SysTask *param0, void *param1);
static void BoxCursorSprite_SwapItemTask(SysTask *param0, void *param1);
static void BoxCursorSprite_GetCursorScreenPos(s32 *param0, s32 *param1, u8 *param2, BoxCursorSprite *param3);
static void BoxCursorSprite_SetPosition(BoxCursorSprite *param0, VecFx32 *param1);
static void BoxCursorSprite_LoadHeldMons(BoxCursorSprite *param0);
static void BoxCursorSprite_SetHeldMonsPriority(BoxCursorSprite *param0);
static void BoxCursorSprite_ReturnHeldMons(BoxCursorSprite *param0);
static void BoxCursorSprite_SwapHeldMon(BoxCursorSprite *param0);
static void BoxCursorSprite_ClearHeldMonFlag(BoxCursorSprite *param0);
static void BoxCursorSprite_DeleteHeldMons(BoxCursorSprite *param0);
static Sprite *BoxCursorSprite_GetHeldMonSprite(BoxCursorSprite *param0);

BOOL BoxCursorSprite_Load(BoxCursorSprite *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4)
{
    param0->boxGraphics = param1;
    param0->boxApp = param2;
    param0->spriteList = param3;
    param0->boxView = BoxGraphics_GetBoxView(param1);
    param0->boxParty = BoxGraphics_GetBoxParty(param1);
    param0->monSpriteManager = BoxGraphics_GetBoxMonSpriteManager(param1);
    param0->cursorLocation = BoxApp_GetCursorLocation(param2);
    param0->boxCol = BoxApp_GetCursorBoxCol(param2);
    param0->boxRow = BoxApp_GetCursorBoxRow(param2);
    param0->partyPos = BoxApp_GetCursorPartyPosition(param2);
    param0->monSprite = NULL;
    param0->shadowSprite = NULL;
    param0->leftArrowSprite = NULL;
    param0->rightArrowSprite = NULL;
    param0->heldMonCount = 0;
    param0->shadowEnabled = 1;
    param0->cellBank = Graphics_GetCellBankFromOpenNARC(param4, 13, 1, &(param0->cellBankData), HEAP_ID_BOX_GRAPHICS);
    param0->animBank = Graphics_GetAnimBankFromOpenNARC(param4, 14, 1, &(param0->animBankData), HEAP_ID_BOX_GRAPHICS);

    if ((param0->cellBank == NULL) || (param0->animBank == NULL)) {
        return 0;
    }

    return 1;
}

void BoxCursorSprite_Init(BoxCursorSprite *param0, NARC *param1)
{
    SpriteResourcesHeader v0;
    u32 cursorLocation, pcMode;

    NNS_G2dInitImageProxy(&(param0->imageProxy));

    Graphics_LoadImageMappingFromOpenNARC(param1, 12, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0 * 0x20, 10, &(param0->imageProxy));
    BoxGraphics_InitSpriteResources(&v0, &(param0->imageProxy), BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->cellBankData, param0->animBankData, ((param0->cursorLocation == 1) ? 1 : 2));
    BoxCursorSprite_GetCursorScreenPos(&param0->x, &param0->y, &param0->cursorLocation, param0);

    param0->monSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, param0->x, param0->y, 1, NNS_G2D_VRAM_TYPE_2DMAIN);
    param0->shadowSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, param0->x, param0->y + 24, 42, NNS_G2D_VRAM_TYPE_2DMAIN);

    cursorLocation = BoxApp_GetCursorLocation(param0->boxApp);
    pcMode = BoxApp_GetBoxMode(param0->boxApp);

    {
        int v3, v4;

        if (pcMode != PC_MODE_COMPARE) {
            v3 = 108;
            v4 = 236;
        } else {
            v3 = 108 + -44;
            v4 = 236 + -44;
        }

        v0.priority = 2;
        param0->leftArrowSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, v3, 20, 43, NNS_G2D_VRAM_TYPE_2DMAIN);
        param0->rightArrowSprite = BoxGraphics_CreateSprite(param0->spriteList, &v0, v4, 20, 43, NNS_G2D_VRAM_TYPE_2DMAIN);
    }

    Sprite_SetAnim(param0->shadowSprite, 5);
    Sprite_SetExplicitPriority(param0->shadowSprite, 2);

    cursorLocation = BoxApp_GetCursorLocation(param0->boxApp);

    if (cursorLocation != CURSOR_ON_BOX_HEADER) {
        Sprite_SetAnim(param0->leftArrowSprite, 6);
        Sprite_SetAnim(param0->rightArrowSprite, 7);
    } else {
        Sprite_SetAnim(param0->leftArrowSprite, 8);
        Sprite_SetAnim(param0->rightArrowSprite, 9);
    }

    if (cursorLocation != CURSOR_IN_BOX) {
        Sprite_SetDrawFlag(param0->shadowSprite, FALSE);
    }

    if (pcMode != PC_MODE_MOVE_ITEMS) {
        if (BoxApp_GetPreviewMonSource(param0->boxApp) == PREVIEW_MON_UNDER_CURSOR) {
            Sprite_SetAnim(param0->monSprite, 0);
            BoxMonSprite_InitSlots(param0->monSpriteManager, param0->heldMons, (5 * 6));
            param0->isHoldingMon = 0;
        } else {
            Sprite_SetAnim(param0->monSprite, 2);
            BoxCursorSprite_CreateHeldMonSprite(param0);
            param0->isHoldingMon = 1;
        }

        param0->isHoldingItem = 0;
    } else {
        if (BoxApp_GetCursorItem(param0->boxApp) == ITEM_NONE) {
            Sprite_SetAnim(param0->monSprite, 0);
            param0->isHoldingItem = 0;
        } else {
            Sprite_SetAnim(param0->monSprite, 2);
            param0->isHoldingItem = 1;
        }

        BoxMonSprite_InitSlots(param0->monSpriteManager, param0->heldMons, (5 * 6));
        param0->isHoldingMon = 0;
    }

    param0->heldItemIcons = BoxGraphics_GetHeldItemIcons(param0->boxGraphics);

    BoxCursorSprite_UpdateFastMode(param0);
}

static void BoxCursorSprite_CreateHeldMonSprite(BoxCursorSprite *param0)
{
    VecFx32 v0;
    s32 v1, v2;

    v0 = *Sprite_GetPosition(param0->monSprite);
    v1 = (v0.x >> FX32_SHIFT) - 0;
    v2 = (v0.y >> FX32_SHIFT) - -4;

    BoxMonSprite_InitSlots(param0->monSpriteManager, param0->heldMons, 1);
    BoxMonSprite_CreateFromBoxMon(param0->monSpriteManager, BoxApp_GetPreviewedBoxMon(param0->boxApp), v1, v2, Sprite_GetExplicitPriority(param0->monSprite), 2, 1240, param0->heldMons);

    param0->heldMonOffsets[0].x = (0 * FX32_ONE);
    param0->heldMonOffsets[0].y = (-4 * FX32_ONE);
    param0->heldMonCount = 1;
    param0->isHoldingMon = 1;
}

void BoxCursorSprite_Free(BoxCursorSprite *param0)
{
    if (param0->cellBank) {
        Heap_Free(param0->cellBank);
        param0->cellBank = NULL;
    }

    if (param0->animBank) {
        Heap_Free(param0->animBank);
        param0->animBank = NULL;
    }

    if (param0->monSprite != NULL) {
        Sprite_Delete(param0->monSprite);
        param0->monSprite = NULL;
    }

    if (param0->shadowSprite != NULL) {
        Sprite_Delete(param0->shadowSprite);
        param0->shadowSprite = NULL;
    }

    if (param0->leftArrowSprite != NULL) {
        Sprite_Delete(param0->leftArrowSprite);
        param0->leftArrowSprite = NULL;
    }

    if (param0->rightArrowSprite != NULL) {
        Sprite_Delete(param0->rightArrowSprite);
        param0->rightArrowSprite = NULL;
    }
}

static void BoxCursorSprite_GetWrapFlags(const BoxCursorSprite *param0, BOOL *param1, BOOL *param2)
{
    *param1 = *param2 = 0;

    switch (param0->cursorLocation) {
    case 0:
        if (param0->destCursorLocation == 0) {
            u32 col = BoxApp_GetCursorBoxCol(param0->boxApp);

            if ((param0->boxCol == 0) && (col == 5) || (param0->boxCol == 5) && (col == 0)) {
                *param1 = 1;
            }
        }
        break;
    case 2:
        if ((param0->destCursorLocation == 4) || (param0->destCursorLocation == 3)) {
            *param2 = 1;
        }
        break;
    case 4:
    case 3:
        if (param0->destCursorLocation == 2) {
            *param2 = 1;
        }
        break;
    }
}

void BoxCursorSprite_MoveToPosition(BoxCursorSprite *param0)
{
    BOOL v0, v1;
    s32 v2, v3;
    s32 v4, v5;
    s32 v6;

    BoxCursorSprite_GetCursorScreenPos(&(param0->targetX), &(param0->targetY), &(param0->destCursorLocation), param0);
    BoxCursorSprite_GetWrapFlags(param0, &v0, &v1);

    if (param0->destCursorLocation != 0) {
        Sprite_SetDrawFlag(param0->shadowSprite, FALSE);
    }

    param0->fxX = param0->x << FX32_SHIFT;
    param0->fxY = param0->y << FX32_SHIFT;

    v2 = param0->targetX << FX32_SHIFT;
    v3 = param0->targetY << FX32_SHIFT;

    if (v0 == 0) {
        v4 = v2 - param0->fxX;
    } else {
        if (v2 > param0->fxX) {
            v4 = -((272 - param0->targetX) + (param0->x - 70));
        } else {
            v4 = (272 - param0->x) + (param0->targetX - 70);
        }

        v4 <<= FX32_SHIFT;
    }

    if (v1 == 0) {
        v5 = v3 - param0->fxY;
    } else {
        if (v3 > param0->fxY) {
            v5 = -((208 - param0->targetY) + (param0->y - -24));
        } else {
            v5 = (208 - param0->y) + (param0->targetY - -24);
        }

        v5 <<= FX32_SHIFT;
    }

    if (v0 || v1) {
        v6 = 12;
    } else {
        v6 = 6;
    }

    param0->velocityX = v4 / v6;
    param0->velocityY = v5 / v6;
    param0->moveSteps = v6;

    BoxGraphics_StartVBlankTask(BoxCursorSprite_MoveTask, param0, 0);
}

BOOL BoxCursorSprite_IsMoveDone(BoxCursorSprite *param0)
{
    return param0->moveSteps == 0;
}

static void BoxCursorSprite_MoveTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = (BoxCursorSprite *)param1;
    VecFx32 v1;

    v1.z = 0;

    if (v0->moveSteps) {
        v0->fxX += v0->velocityX;

        if ((v0->velocityX > 0) && (v0->fxX > 1114112)) {
            v0->fxX = 286720 + (1114112 - v0->fxX);
        }

        if ((v0->velocityX < 0) && (v0->fxX < 286720)) {
            v0->fxX = 1114112 - (286720 - v0->fxX);
        }

        v0->fxY += v0->velocityY;

        if ((v0->velocityY > 0) && (v0->fxY > 851968)) {
            v0->fxY = -98304 + (851968 - v0->fxY);
        }

        if ((v0->velocityY < 0) && (v0->fxY < -98304)) {
            v0->fxY = 851968 - (-98304 - v0->fxY);
        }

        v1.x = v0->fxX;
        v1.y = v0->fxY;
        v1.z = 0;

        BoxCursorSprite_SetPosition(v0, &v1);

        v0->moveSteps--;
        return;
    }

    v1.x = v0->targetX << FX32_SHIFT;
    v1.y = v0->targetY << FX32_SHIFT;
    v1.z = 0;

    BoxCursorSprite_SetPosition(v0, &v1);

    v0->x = v0->targetX;
    v0->y = v0->targetY;
    v0->cursorLocation = v0->destCursorLocation;
    v0->boxCol = BoxApp_GetCursorBoxCol(v0->boxApp);
    v0->boxRow = BoxApp_GetCursorBoxRow(v0->boxApp);
    v0->partyPos = BoxApp_GetCursorPartyPosition(v0->boxApp);

    if (v0->destCursorLocation == 0) {
        Sprite_SetDrawFlag(v0->shadowSprite, TRUE);
    }

    if (v0->destCursorLocation != 2) {
        Sprite_SetAnim(v0->leftArrowSprite, 6);
        Sprite_SetAnim(v0->rightArrowSprite, 7);
    } else {
        Sprite_SetAnim(v0->leftArrowSprite, 8);
        Sprite_SetAnim(v0->rightArrowSprite, 9);
    }

    SysTask_Done(param0);
}

void BoxCursorSprite_StartPickUpAnimation(BoxCursorSprite *param0)
{
    Sprite_SetAnim(param0->monSprite, 1);

    param0->velocityY = (12 << FX32_SHIFT) / 6;
    param0->targetY = (param0->y + 12);
    param0->moveSteps = 6;
    param0->state = 0;

    BoxCursorSprite_LoadHeldMons(param0);
    BoxGraphics_StartVBlankTask(BoxCursorSprite_PickUpTask, param0, 0);
}

BOOL BoxCursorSprite_IsPickUpDone(BoxCursorSprite *param0)
{
    return param0->state == 255;
}

static void BoxCursorSprite_PickUpTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = (BoxCursorSprite *)param1;
    VecFx32 v1 = *(Sprite_GetPosition(v0->monSprite));

    switch (v0->state) {
    case 0:
        v0->shadowEnabled = 0;

        if (v0->moveSteps) {
            v1.y += v0->velocityY;
            BoxCursorSprite_SetPosition(v0, &v1);
            v0->moveSteps--;
            break;
        }

        v1.y = v0->targetY << FX32_SHIFT;

        BoxCursorSprite_SetPosition(v0, &v1);
        Sprite_SetAnim(v0->monSprite, 2);
        BoxCursorSprite_SetHeldMonsPriority(v0);

        v0->moveSteps = 6;
        v0->state++;
    case 1:
        if (v0->moveSteps) {
            v1.y -= v0->velocityY;
            BoxCursorSprite_SetPosition(v0, &v1);
            v0->moveSteps--;
            break;
        }

        v1.y = v0->y << FX32_SHIFT;
        BoxCursorSprite_SetPosition(v0, &v1);
        v0->state = 255;
        v0->shadowEnabled = 1;
        SysTask_Done(param0);
    }
}

void BoxCursorSprite_StartPlaceAnimation(BoxCursorSprite *param0)
{
    param0->velocityY = (12 << FX32_SHIFT) / 6;
    param0->targetY = (param0->y + 12);
    param0->moveSteps = 6;
    param0->state = 0;

    BoxGraphics_StartVBlankTask(BoxCursorSprite_PlaceTask, param0, 0);
}

BOOL BoxCursorSprite_IsPlaceDone(BoxCursorSprite *param0)
{
    if (param0->state == 255) {
        BoxCursorSprite_ReturnHeldMons(param0);
        BoxMonSprite_InitSlots(param0->monSpriteManager, param0->heldMons, param0->heldMonCount);
        param0->heldMonCount = 0;
        return 1;
    }

    return 0;
}

static void BoxCursorSprite_PlaceTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = (BoxCursorSprite *)param1;
    VecFx32 v1 = *(Sprite_GetPosition(v0->monSprite));

    switch (v0->state) {
    case 0:
        v0->shadowEnabled = 0;

        if (v0->moveSteps) {
            v1.y += v0->velocityY;
            BoxCursorSprite_SetPosition(v0, &v1);
            v0->moveSteps--;
            break;
        }

        v1.y = v0->targetY << FX32_SHIFT;

        BoxCursorSprite_SetPosition(v0, &v1);
        Sprite_SetAnim(v0->monSprite, 1);
        BoxCursorSprite_ClearHeldMonFlag(v0);

        v0->moveSteps = 6;
        v0->state++;
    case 1:
        if (v0->moveSteps) {
            v1.y -= v0->velocityY;
            BoxCursorSprite_SetPosition(v0, &v1);
            v0->moveSteps--;
            break;
        }

        v1.y = v0->y << FX32_SHIFT;

        BoxCursorSprite_SetPosition(v0, &v1);
        Sprite_SetAnim(v0->monSprite, 0);

        v0->state = 255;
        v0->shadowEnabled = 1;

        SysTask_Done(param0);
    }
}

void BoxCursorSprite_StartSwapAnimation(BoxCursorSprite *param0)
{
    VecFx32 v0;
    Sprite *v1;

    Sprite_SetAnim(param0->monSprite, 1);

    param0->animFinished = 0;

    v1 = BoxCursorSprite_GetHeldMonSprite(param0);
    v0 = *(Sprite_GetPosition(v1));
    BoxCursorSprite_StartSlideAnimation(param0, param0->heldMons->sprite, v0.y, 1, Sprite_GetPriority(v1));

    v0 = *(Sprite_GetPosition(param0->heldMons->sprite));
    BoxCursorSprite_StartSlideAnimation(param0, v1, v0.y, -1, Sprite_GetPriority(param0->heldMons->sprite));

    param0->state = 0;
}

BOOL BoxCursorSprite_IsSwapDone(BoxCursorSprite *param0)
{
    if (BoxCursorSprite_IsSlideDone(param0)) {
        Sprite_SetAnim(param0->monSprite, 2);
        BoxCursorSprite_SwapHeldMon(param0);
        return 1;
    }

    return 0;
}

static void BoxCursorSprite_StartSlideAnimation(BoxCursorSprite *param0, Sprite *param1, fx32 param2, s32 param3, u32 param4)
{
    BoxCursorSpriteAnimation *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxCursorSpriteAnimation));

    if (v0) {
        VecFx32 v1;

        v1 = *Sprite_GetPosition(param1);

        v0->sprite = param1;
        v0->stepCount = 12;
        v0->priorityChangeStep = 12 / 2;
        v0->priority = param4;
        v0->y = v1.y;
        v0->x = v1.x;
        v0->targetY = param2;
        v0->angle = 0;
        v0->amplitude = param3 * 12;
        v0->yStep = (v0->targetY - v0->y) / 12;
        v0->angleStep = (180 << FX32_SHIFT) / 12;
        v0->cursorSprite = param0;

        if (BoxGraphics_StartVBlankTask(BoxCursorSprite_SlideTask, v0, 0)) {
            param0->animFinished = 1;
            return;
        } else {
            Heap_Free(v0);
        }
    }
}

static BOOL BoxCursorSprite_IsSlideDone(BoxCursorSprite *param0)
{
    return param0->animFinished == 0;
}

static void BoxCursorSprite_SlideDone(void *param0)
{
    BoxCursorSprite *v0 = param0;
    v0->animFinished = 0;
}

static void BoxCursorSprite_SlideTask(SysTask *param0, void *param1)
{
    BoxCursorSpriteAnimation *v0 = (BoxCursorSpriteAnimation *)param1;
    VecFx32 v1;

    v1 = *Sprite_GetPosition(v0->sprite);

    if (v0->stepCount) {
        fx32 v2;

        v0->stepCount--;

        if (v0->stepCount == v0->priorityChangeStep) {
            BoxGraphics_SetSpritePriority(v0->sprite, v0->priority);
        }

        v0->y += v0->yStep;
        v1.y = v0->y;
        v0->angle += v0->angleStep;
        v2 = v0->amplitude * CalcSineDegrees(v0->angle >> FX32_SHIFT);
        v1.x = v0->x + v2;

        Sprite_SetPosition(v0->sprite, &v1);
    } else {
        v1.x = v0->x;
        v1.y = v0->targetY;

        Sprite_SetPosition(v0->sprite, &v1);
        BoxGraphics_DeferFree(param1, BoxCursorSprite_SlideDone, v0->cursorSprite);
        SysTask_Done(param0);
    }
}

void BoxCursorSprite_StartPressAnimation(BoxCursorSprite *param0)
{
    VecFx32 v0;

    if ((param0->isHoldingMon == 0) && (param0->isHoldingItem == 0)) {
        Sprite_SetAnim(param0->monSprite, 3);
    }

    v0 = *Sprite_GetPosition(param0->monSprite);
    v0.y += (-2 * FX32_ONE);

    BoxCursorSprite_SetPosition(param0, &v0);

    param0->state = 0;
    param0->moveSteps = 0;

    if (BoxGraphics_StartVBlankTask(BoxCursorSprite_PressTask, param0, 0)) {
        param0->animFinished = 1;
    }
}

BOOL BoxCursorSprite_IsPressDone(BoxCursorSprite *param0)
{
    return param0->animFinished == 0;
}

static void BoxCursorSprite_PressTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = (BoxCursorSprite *)param1;

    switch (v0->state) {
    case 0:
        if (++(v0->moveSteps) >= 4) {
            VecFx32 v1 = *Sprite_GetPosition(v0->monSprite);

            v0->targetY = (v1.y >> FX32_SHIFT) + 6;
            v0->velocityY = (6 * FX32_ONE) / 2;
            v0->moveSteps = 2;

            if ((v0->isHoldingMon == 0) && (v0->isHoldingItem == 0)) {
                Sprite_SetAnim(v0->monSprite, 4);
            }

            v0->state++;
        }
        break;
    case 1: {
        VecFx32 v2 = *Sprite_GetPosition(v0->monSprite);

        if (v0->moveSteps) {
            v2.y += v0->velocityY;
            BoxCursorSprite_SetPosition(v0, &v2);
            v0->moveSteps--;
        } else {
            v2.y = v0->targetY << FX32_SHIFT;
            BoxCursorSprite_SetPosition(v0, &v2);
            v0->animFinished = 0;
            SysTask_Done(param0);
        }
    } break;
    }
}

void BoxCursorSprite_StartReleasePressAnimation(BoxCursorSprite *param0)
{
    VecFx32 v0 = *Sprite_GetPosition(param0->monSprite);

    param0->targetY = (v0.y >> FX32_SHIFT) + -4;
    param0->velocityY = (-4 * FX32_ONE) / 4;
    param0->moveSteps = 4;
    param0->state = 0;

    if (BoxGraphics_StartVBlankTask(BoxCursorSprite_ReleasePressTask, param0, 0)) {
        param0->animFinished = 1;
    }
}

BOOL BoxCursorSprite_IsReleasePressDone(BoxCursorSprite *param0)
{
    if (param0->animFinished == 0) {
        if ((param0->isHoldingMon == 0) && (param0->isHoldingItem == 0)) {
            if (Sprite_GetActiveAnim(param0->monSprite) != 0) {
                Sprite_SetAnim(param0->monSprite, 0);
            }
        }

        return 1;
    }

    return 0;
}

static void BoxCursorSprite_ReleasePressTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0;
    VecFx32 v1;

    v0 = (BoxCursorSprite *)param1;
    v1 = *Sprite_GetPosition(v0->monSprite);

    if (v0->moveSteps) {
        v1.y += v0->velocityY;
        BoxCursorSprite_SetPosition(v0, &v1);
        v0->moveSteps--;
    } else {
        v1.y = v0->targetY << FX32_SHIFT;
        BoxCursorSprite_SetPosition(v0, &v1);
        v0->animFinished = 0;
        SysTask_Done(param0);
    }
}

void BoxCursorSprite_ResetPosition(BoxCursorSprite *param0)
{
    if (param0->boxApp->selectedBoxID == BoxApp_GetCurrentBox(param0->boxApp)) {
        BoxView_DrawAllBoxMons(param0->boxView);
    }

    BoxCursorSprite_DeleteHeldMons(param0);
    Sprite_SetAnim(param0->monSprite, 0);
}

void BoxCursorSprite_StartReleaseAnimation(BoxCursorSprite *param0)
{
    Sprite_SetAnim(param0->monSprite, 1);
    BoxMonSprite_SetAnim(param0->monSpriteManager, param0->heldMons, 1);

    param0->state = 0;
}

BOOL BoxCursorSprite_UpdateReleaseAnimation(BoxCursorSprite *param0)
{
    const BoxApplicationManager *v0 = BoxGraphics_GetAppManager(param0->boxGraphics);

    switch (param0->state) {
    case 0:
        if (BoxMonSprite_IsAnimDone(param0->monSpriteManager, param0->heldMons)) {
            param0->state++;
        }
        break;
    case 1:
        if (BoxAppMan_HasCheckedCanReleaseMon(v0)) {
            if (BoxAppMan_CanReleaseMon(v0)) {
                Sprite_SetAnim(param0->monSprite, 0);
                BoxCursorSprite_DeleteHeldMons(param0);
                return 1;
            } else {
                BoxMonSprite_SetAnim(param0->monSpriteManager, param0->heldMons, 2);
                param0->state++;
            }
        }
        break;
    case 2:
        if (BoxMonSprite_IsAnimDone(param0->monSpriteManager, param0->heldMons)) {
            Sprite_SetAnim(param0->monSprite, 2);
            return 1;
        }

        break;
    }

    return 0;
}

void BoxCursorSprite_SetPriorityHigh(BoxCursorSprite *param0)
{
    Sprite_SetExplicitPriority(param0->monSprite, 1);

    if (param0->isHoldingMon) {
        Sprite_SetExplicitPriority(param0->heldMons->sprite, 1);
    }

    if (param0->isHoldingItem) {
        BoxHeldItem_SetPriority(param0->heldItemIcons, 1);
    }
}

void BoxCursorSprite_SetPriorityNormal(BoxCursorSprite *param0)
{
    Sprite_SetExplicitPriority(param0->monSprite, 2);

    if (param0->isHoldingMon) {
        Sprite_SetExplicitPriority(param0->heldMons->sprite, 2);
    }

    if (param0->isHoldingItem) {
        BoxHeldItem_SetPriority(param0->heldItemIcons, 2);
    }
}

void BoxCursorSprite_UpdateHeldMonMarkings(BoxCursorSprite *param0)
{
    if (param0->isHoldingMon) {
        u32 v0 = BoxApp_GetPreviewedMonMarkings(param0->boxApp);
        BoxMonSprite_SetMarkings(param0->monSpriteManager, param0->heldMons, v0);
    }
}

void BoxCursorSprite_ApplyHeldMonTransparency(BoxCursorSprite *param0)
{
    u32 v0 = BoxApp_GetMonSpriteTransparencyMask(param0->boxApp);

    if (param0->heldMons->sprite != NULL) {
        BoxMonSprite_UpdateTransparency(param0->monSpriteManager, param0->heldMons, v0);
    }
}

void BoxCursorSprite_UpdateHeldMonItem(BoxCursorSprite *param0, u32 param1)
{
    if (param0->heldMons->sprite != NULL) {
        BoxMonSprite_SetHeldItem(param0->monSpriteManager, param0->heldMons, param1);
        BoxMonSprite_UpdateTransparency(param0->monSpriteManager, param0->heldMons, BoxApp_GetMonSpriteTransparencyMask(param0->boxApp));
        BoxMonSprite_UpdateFormIcon(param0->monSpriteManager, param0->heldMons, 0);
    }
}

void BoxCursorSprite_UpdateFastMode(BoxCursorSprite *param0)
{
    if (BoxApp_IsCursorFastMode(param0->boxApp)) {
        Sprite_SetExplicitPalette(param0->monSprite, 1);
    } else {
        Sprite_SetExplicitPalette(param0->monSprite, 0);
    }
}

void BoxGraphics_OpenMultiSelectCursor(BoxCursorSprite *param0)
{
    Sprite_SetAnim(param0->monSprite, 1);
}

void BoxCursorSprite_GetPosition(BoxCursorSprite *param0, VecFx32 *param1)
{
    *param1 = *(Sprite_GetPosition(param0->monSprite));
}

void BoxCursorSprite_StartPickUpItemAnimation(BoxCursorSprite *param0)
{
    param0->state = 0;

    if (SysTask_Start(BoxCursorSprite_PickUpItemTask, param0, 0)) {
        param0->isHoldingItem = 1;
        param0->animFinished = 1;
    }
}

BOOL BoxCursorSprite_IsPickUpItemDone(BoxCursorSprite *param0)
{
    return param0->animFinished == 0;
}

static void BoxCursorSprite_PickUpItemTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = param1;

    switch (v0->state) {
    case 0:
        Sprite_SetAnim(v0->monSprite, 1);
        BoxHeldItem_StartReturnToPreview(v0->heldItemIcons);
        v0->state++;
        break;
    case 1:
        if (BoxHeldItem_IsReturnToPreviewDone(v0->heldItemIcons)) {
            Sprite_SetAnim(v0->monSprite, 2);
            v0->animFinished = 0;
            SysTask_Done(param0);
        }
    }
}

void BoxCursorSprite_StartPlaceItemAnimation(BoxCursorSprite *param0)
{
    param0->state = 0;

    if (SysTask_Start(BoxCursorSprite_PlaceItemTask, param0, 0)) {
        param0->isHoldingItem = 0;
        param0->animFinished = 1;
    }
}

BOOL BoxCursorSprite_IsPlaceItemDone(BoxCursorSprite *param0)
{
    return param0->animFinished == 0;
}

static void BoxCursorSprite_PlaceItemTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = param1;

    switch (v0->state) {
    case 0:
        Sprite_SetAnim(v0->monSprite, 1);
        BoxHeldItem_StartReturnToCursor(v0->heldItemIcons);
        v0->state++;
        break;
    case 1:
        if (BoxHeldItem_IsReturnToCursorDone(v0->heldItemIcons)) {
            Sprite_SetAnim(v0->monSprite, 0);
            v0->animFinished = 0;
            SysTask_Done(param0);
        }
    }
}

void BoxCursorSprite_StartSwapItemAnimation(BoxCursorSprite *param0)
{
    param0->state = 0;

    if (SysTask_Start(BoxCursorSprite_SwapItemTask, param0, 0)) {
        param0->animFinished = 1;
    }
}

BOOL BoxCursorSprite_IsSwapItemDone(BoxCursorSprite *param0)
{
    return param0->animFinished == 0;
}

static void BoxCursorSprite_SwapItemTask(SysTask *param0, void *param1)
{
    BoxCursorSprite *v0 = param1;

    switch (v0->state) {
    case 0:
        Sprite_SetAnim(v0->monSprite, 1);
        BoxHeldItem_StartSwap(v0->heldItemIcons);
        v0->state++;
        break;
    case 1:
        if (BoxHeldItem_IsSwapDone(v0->heldItemIcons)) {
            Sprite_SetAnim(v0->monSprite, 2);
            v0->animFinished = 0;
            SysTask_Done(param0);
        }
    }
}

void BoxCursorSprite_HideHeldItem(BoxCursorSprite *param0)
{
    if (param0->isHoldingItem) {
        Sprite_SetAnim(param0->monSprite, 1);
    }
}

void BoxCursorSprite_ShowHeldItem(BoxCursorSprite *param0)
{
    if (param0->isHoldingItem) {
        Sprite_SetAnim(param0->monSprite, 0);
        param0->isHoldingItem = 0;
    }
}

static void BoxCursorSprite_GetCursorScreenPos(s32 *param0, s32 *param1, u8 *cursorLocation, BoxCursorSprite *param3)
{
    const BoxApplication *v0 = param3->boxApp;

    *cursorLocation = BoxApp_GetCursorLocation(v0);

    switch (*cursorLocation) {
    case CURSOR_IN_BOX:
        *param0 = 112 + BoxGraphics_GetCompareXOffset(param3->boxGraphics) + BoxApp_GetCursorBoxCol(v0) * 24 + 0;
        *param1 = 40 + BoxApp_GetCursorBoxRow(v0) * 24 + -16;
        break;
    case CURSOR_IN_PARTY: {
        u32 partyIndex = BoxApp_GetCursorPartyPosition(v0);

        BoxParty_GetMonPosition(BoxGraphics_GetBoxParty(param3->boxGraphics), partyIndex, param0, param1);
        (*param0) += 0;
        (*param1) += -16;
    } break;
    case CURSOR_ON_BOX_HEADER:
        *param0 = 168 + BoxGraphics_GetCompareXOffset(param3->boxGraphics);
        *param1 = 8;
        break;
    case CURSOR_ON_PARTY_BUTTON:
        *param0 = 159 + BoxGraphics_GetCompareXOffset(param3->boxGraphics);
        *param1 = 160;
        break;
    case CURSOR_ON_CLOSE_BUTTON:
        *param0 = 235 + BoxGraphics_GetCompareXOffset(param3->boxGraphics);
        *param1 = 160;
        break;
    }
}

static void BoxCursorSprite_SetPosition(BoxCursorSprite *param0, VecFx32 *param1)
{
    Sprite_SetPosition(param0->monSprite, param1);

    if (param0->isHoldingMon) {
        VecFx32 v0;
        int v1;

        v0.z = 0;

        for (v1 = 0; v1 < param0->heldMonCount; v1++) {
            v0.x = param1->x + param0->heldMonOffsets[v1].x;
            v0.y = param1->y - param0->heldMonOffsets[v1].y;
            Sprite_SetPosition(param0->heldMons[v1].sprite, &v0);
        }
    }

    if (param0->isHoldingItem) {
        BoxHeldItem_SetPosition(param0->heldItemIcons, param1);
    }

    if (param0->shadowEnabled) {
        VecFx32 v2 = *param1;

        v2.y += (24 << FX32_SHIFT);
        Sprite_SetPosition(param0->shadowSprite, &v2);
    }
}

static void BoxCursorSprite_LoadHeldMons(BoxCursorSprite *param0)
{
    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_BOX) {
        if (BoxApp_IsMultiSelectSingleSelect(param0->boxApp)) {
            u32 posInBox = BoxApp_GetCursorBoxPosition(param0->boxApp);
            BoxView_PlaceMonSprite(param0->boxView, posInBox, 1240, param0->heldMons);
            param0->heldMonCount = 1;
            param0->heldMonOffsets[0].x = (0 * FX32_ONE);
            param0->heldMonOffsets[0].y = (-4 * FX32_ONE);
        } else {
            u32 v1, v2, v3, v4, v5, v6, v7, col, row;

            BoxApp_GetMultiSelectBoundingBox(param0->boxApp, &v4, &v5, &v6, &v7);

            col = BoxApp_GetCursorBoxCol(param0->boxApp);
            row = BoxApp_GetCursorBoxRow(param0->boxApp);
            v1 = 0;

            for (v3 = v6; v3 <= v7; v3++) {
                for (v2 = v4; v2 <= v5; v2++) {
                    BoxView_PlaceMonSprite(param0->boxView, v3 * 6 + v2, 1520 + v1 * 16, &param0->heldMons[v1]);

                    if (param0->heldMons[v1].sprite != NULL) {
                        param0->heldMonOffsets[v1].x = (0 + (v2 - col) * 24) * FX32_ONE;
                        param0->heldMonOffsets[v1].y = (-4 - (v3 - row) * 24) * FX32_ONE;
                        v1++;
                    }
                }
            }

            param0->heldMonCount = v1;
        }
    } else {
        u32 partyIndex = BoxApp_GetCursorPartyPosition(param0->boxApp);

        BoxParty_PlaceMonSprite(param0->boxParty, partyIndex, 1240, param0->heldMons);

        param0->heldMonCount = 1;
        param0->heldMonOffsets[0].x = (0 * FX32_ONE);
        param0->heldMonOffsets[0].y = (-4 * FX32_ONE);
    }
}

static void BoxCursorSprite_SetHeldMonsPriority(BoxCursorSprite *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->heldMonCount; v0++) {
        BoxGraphics_SetSpritePriority(param0->heldMons[v0].sprite, 2);
    }

    param0->isHoldingMon = 1;
}

static void BoxCursorSprite_ReturnHeldMons(BoxCursorSprite *param0)
{
    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_BOX) {
        if (BoxApp_IsMultiSelectSingleSelect(param0->boxApp)) {
            u32 posInBox = BoxApp_GetCursorBoxPosition(param0->boxApp);
            BoxView_ReturnMonSprite(param0->boxView, posInBox, param0->heldMons);
        } else {
            int v1, v2, v3;

            v2 = BoxApp_GetMultiSelectTopLeftPos(param0->boxApp);

            for (v1 = 0; v1 < param0->heldMonCount; v1++) {
                v3 = v2 + BoxApp_GetRelativeMonPosInMultiSelection(param0->boxApp, v1);
                BoxView_ReturnMonSprite(param0->boxView, v3, &param0->heldMons[v1]);
            }
        }
    } else {
        u32 partyIndex = BoxApp_GetCursorPartyPosition(param0->boxApp);
        BoxParty_AddMonSprite(param0->boxParty, partyIndex, param0->heldMons);
    }
}

static void BoxCursorSprite_SwapHeldMon(BoxCursorSprite *param0)
{
    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_BOX) {
        u32 posInBox = BoxApp_GetCursorBoxPosition(param0->boxApp);

        {
            BoxMonSprite *v1 = BoxView_GetMonSprite(param0->boxView, posInBox);

            BoxMonSprite_LoadIcon(param0->monSpriteManager, param0->heldMons, 1520);
            BoxMonSprite_LoadIcon(param0->monSpriteManager, v1, 1520 + 16);

            OS_WaitVBlankIntr();
        }

        BoxView_PlaceMonSprite(param0->boxView, posInBox, 1240, &param0->heldMons[1]);
        BoxView_ReturnMonSprite(param0->boxView, posInBox, param0->heldMons);
        BoxMonSprite_CopySlot(&(param0->heldMons[1]), &(param0->heldMons[0]), 1);
    } else {
        u32 v2 = BoxApp_GetCursorPartyPosition(param0->boxApp);

        {
            BoxMonSprite *v3 = BoxParty_GetMonSprite(param0->boxParty, v2);

            BoxMonSprite_LoadIcon(param0->monSpriteManager, param0->heldMons, 1520);
            BoxMonSprite_LoadIcon(param0->monSpriteManager, v3, 1520 + 16);

            OS_WaitVBlankIntr();
        }

        BoxParty_PlaceMonSprite(param0->boxParty, v2, 1240, &param0->heldMons[1]);
        BoxParty_SetMonSprite(param0->boxParty, v2, param0->heldMons);
        BoxMonSprite_CopySlot(&(param0->heldMons[1]), &(param0->heldMons[0]), 1);
    }
}

static void BoxCursorSprite_ClearHeldMonFlag(BoxCursorSprite *param0)
{
    param0->isHoldingMon = 0;
}

static void BoxCursorSprite_DeleteHeldMons(BoxCursorSprite *param0)
{
    BoxMonSprite_DeleteSlots(param0->monSpriteManager, param0->heldMons, 1);
    param0->isHoldingMon = 0;
    param0->heldMonCount = 0;
}

static Sprite *BoxCursorSprite_GetHeldMonSprite(BoxCursorSprite *param0)
{
    BoxMonSprite *v0;
    u32 cursorPosition;

    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_BOX) {
        cursorPosition = BoxApp_GetCursorBoxPosition(param0->boxApp);
        v0 = BoxView_GetMonSprite(param0->boxView, cursorPosition);
        return v0->sprite;
    } else {
        cursorPosition = BoxApp_GetCursorPartyPosition(param0->boxApp);
        v0 = BoxParty_GetMonSprite(param0->boxParty, cursorPosition);
        return v0->sprite;
    }
}
