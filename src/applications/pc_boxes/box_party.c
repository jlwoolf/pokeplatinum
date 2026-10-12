#include "applications/pc_boxes/box_party.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_view.h"
#include "applications/pc_boxes/box_mon_sprite_manager.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_party.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "party.h"
#include "pokemon.h"
#include "sprite.h"
#include "sys_task.h"
#include "sys_task_manager.h"

static const struct {
    u16 x;
    u16 y;
} sBoxPartyMonPositions[] = {
    { 144, 28 },
    { 192, 36 },
    { 144, 68 },
    { 192, 76 },
    { 144, 108 },
    { 192, 116 },
};

static void BoxParty_HideTask(SysTask *param0, void *param1);
static void BoxParty_ShowTask(SysTask *param0, void *param1);
static void BoxParty_ShiftMonsTask(SysTask *param0, void *param1);
static void BoxParty_MoveTask(SysTask *param0, void *param1);
static void BoxParty_DrawWindow(BoxParty *param0, u32 param1);
static void BoxParty_InitMonPath(BoxParty *param0, VecFx32 *param1);
static void BoxParty_ShiftMonY(BoxParty *param0, fx32 param1);
static void BoxParty_CreateMonSprites(BoxParty *param0, BOOL param1);
static void BoxParty_DeleteMonSprites(BoxParty *param0);

BOOL BoxParty_Load(BoxParty *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, NARC *param5)
{
    param0->boxGraphics = param1;
    param0->boxApp = param2;
    param0->spriteList = param4;
    param0->bgConfig = param3;
    param0->monSpriteManager = BoxGraphics_GetBoxMonSpriteManager(param1);
    param0->boxView = BoxGraphics_GetBoxView(param1);

    if (BoxApp_GetBoxMode(param2) != PC_MODE_COMPARE) {
        param0->tileOffset = 14;
        param0->xOffset = 0;
    } else {
        param0->tileOffset = 9;
        param0->xOffset = (9 - 14) * 8;
    }

    param0->windowOffset = 0;
    param0->taskActive = 0;

    BoxMonSprite_InitSlots(param0->monSpriteManager, param0->monSprites, 6);

    param0->monPath = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(VecFx32) * 6 * 8);
    param0->screenDataFile = Graphics_GetScrnDataFromOpenNARC(param5, 6, 1, &(param0->screenData), HEAP_ID_BOX_GRAPHICS);

    if ((param0->screenDataFile == NULL) || (param0->monPath == NULL)) {
        return 0;
    }

    BoxParty_InitMonPath(param0, param0->monPath);

    return 1;
}

void BoxParty_Free(BoxParty *param0)
{
    if (param0->screenDataFile) {
        Heap_Free(param0->screenDataFile);
    }

    if (param0->monPath != NULL) {
        Heap_Free(param0->monPath);
    }

    BoxParty_DeleteMonSprites(param0);
}

void BoxParty_Show(BoxParty *param0)
{
    param0->windowOffset = 0;
    BoxParty_DrawWindow(param0, param0->windowOffset);
    BoxParty_CreateMonSprites(param0, 1);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, 2);
}

void BoxParty_Hide(BoxParty *param0)
{
    BoxParty_CreateMonSprites(param0, 0);

    param0->windowOffset = 26;
    param0->taskActive = (BoxGraphics_StartVBlankTask(BoxParty_HideTask, param0, 0) != NULL);
}

BOOL BoxParty_IsHideDone(BoxParty *param0)
{
    return param0->taskActive == 0;
}

static void BoxParty_HideTask(SysTask *param0, void *param1)
{
    BoxParty *v0 = (BoxParty *)param1;
    fx32 v1;

    if (v0->windowOffset > 2) {
        v1 = -((2 * 8) << FX32_SHIFT);
        v0->windowOffset -= 2;
    } else {
        v1 = -((v0->windowOffset * 8) << FX32_SHIFT);
        v0->windowOffset = 0;
    }

    BoxParty_DrawWindow(v0, v0->windowOffset);
    Bg_CopyTilemapBufferToVRAM(v0->bgConfig, 2);
    BoxParty_ShiftMonY(v0, v1);

    if (v0->windowOffset == 0) {
        v0->taskActive = 0;
        SysTask_Done(param0);
    }
}

void BoxParty_StartHide(BoxParty *param0)
{
    param0->taskActive = (BoxGraphics_StartVBlankTask(BoxParty_ShowTask, param0, 0) != NULL);
}

BOOL BoxParty_IsShowDone(BoxParty *param0)
{
    if (param0->taskActive == 0) {
        BoxParty_DeleteMonSprites(param0);
        return 1;
    }

    return 0;
}

static void BoxParty_ShowTask(SysTask *param0, void *param1)
{
    BoxParty *v0 = (BoxParty *)param1;
    fx32 v1;

    if (v0->windowOffset < (26 - 2)) {
        v1 = ((2 * 8) << FX32_SHIFT);
        v0->windowOffset += 2;
    } else {
        v1 = ((26 - v0->windowOffset) * 8) << FX32_SHIFT;
        v0->windowOffset = 26;
    }

    if (v0->windowOffset > 2) {
        u32 v2, v3;

        v3 = (u32)((v1) >> FX32_SHIFT) / 8;
        v2 = v0->windowOffset - 2 - v3;

        Bg_FillTilemapRect(v0->bgConfig, 2, 0x0, v0->tileOffset, v2, 15, v3, 17);
    }

    BoxParty_DrawWindow(v0, v0->windowOffset);
    Bg_CopyTilemapBufferToVRAM(v0->bgConfig, 2);
    BoxParty_ShiftMonY(v0, v1);

    if (v0->windowOffset == 26) {
        v0->taskActive = 0;
        SysTask_Done(param0);
    }
}

void BoxParty_ShiftMonsDown(BoxParty *param0)
{
    int partyCount = Party_GetCurrentCount(param0->boxApp->party);

    if (param0->monIndex < partyCount) {
        int v2 = partyCount - param0->monIndex;

        for (int v1 = param0->monIndex; v1 < MAX_PARTY_SIZE - 1; v1++) {
            BoxMonSprite_CopySlot(&(param0->monSprites[v1 + 1]), &(param0->monSprites[v1]), 1);
            BoxMonSprite_InitSlots(param0->monSpriteManager, &(param0->monSprites[v1 + 1]), 1);

            if (param0->monSprites[v1].sprite != NULL) {
                BoxMonSprite_LoadIcon(param0->monSpriteManager, &(param0->monSprites[v1]), 1048 + 32 * v1);
            }
        }

        param0->shiftMonCount = v2;
        param0->pathStep = 0;
        param0->taskActive = (BoxGraphics_StartVBlankTask(BoxParty_ShiftMonsTask, param0, 0) != NULL);
    } else {
        param0->taskActive = 0;
    }
}

static void BoxParty_ShiftMonsTask(SysTask *param0, void *param1)
{
    BoxParty *v0;
    VecFx32 *v1;
    int v2, v3, v4;

    v0 = (BoxParty *)param1;
    v2 = v0->monIndex;
    v4 = v0->shiftMonCount;
    v1 = ((VecFx32 *)(v0->monPath)) + ((v2 * 8) + v0->pathStep);

    for (v3 = 0; v3 < v4; v3++) {
        if (v0->monSprites[v2].sprite != NULL) {
            Sprite_SetPosition(v0->monSprites[v2].sprite, v1);
        }

        v2++;
        v1 += 8;
    }

    if (++(v0->pathStep) >= 8) {
        v0->taskActive = 0;
        SysTask_Done(param0);
    }
}

BOOL BoxParty_IsShiftDone(BoxParty *param0)
{
    return param0->taskActive == 0;
}

void BoxParty_MoveCursorToLastMon(BoxParty *param0)
{
    u32 v0 = Party_GetCurrentCount(param0->boxApp->party) - 1;

    if (param0->monIndex > v0) {
        VecFx32 v1;

        v1 = *Sprite_GetPosition(param0->monSprites[v0].sprite);
        param0->pathStepX = (((sBoxPartyMonPositions[v0].x + param0->xOffset) << FX32_SHIFT) - v1.x) / 8;
        param0->pathStepY = ((sBoxPartyMonPositions[v0].y << FX32_SHIFT) - v1.y) / 8;
        param0->pathStep = 0;
        param0->monIndex = v0;
        param0->taskActive = (BoxGraphics_StartVBlankTask(BoxParty_MoveTask, param0, 0) != NULL);
    } else {
        param0->taskActive = 0;
    }
}

BOOL BoxParty_IsMoveDone(BoxParty *param0)
{
    return param0->taskActive == 0;
}

static void BoxParty_MoveTask(SysTask *param0, void *param1)
{
    BoxParty *v0;
    VecFx32 v1;
    BOOL v2;

    v0 = (BoxParty *)param1;
    v1 = *Sprite_GetPosition(v0->monSprites[v0->monIndex].sprite);

    if (++(v0->pathStep) >= 8) {
        v1.x = (sBoxPartyMonPositions[v0->monIndex].x + v0->xOffset) << FX32_SHIFT;
        v1.y = sBoxPartyMonPositions[v0->monIndex].y << FX32_SHIFT;
        v2 = 1;
    } else {
        v1.x += v0->pathStepX;
        v1.y += v0->pathStepY;
        v2 = 0;
    }

    Sprite_SetPosition(v0->monSprites[v0->monIndex].sprite, &v1);

    if (v2) {
        v0->taskActive = 0;
        SysTask_Done(param0);
    }
}

void BoxParty_ReloadMons(BoxParty *param0)
{
    u32 v0;

    if (param0->boxApp->selectedBoxID == BoxApp_GetCurrentBox(param0->boxApp)) {
        BoxView_DrawAllBoxMons(param0->boxView);
    }

    v0 = BoxApp_GetCursorPartyPosition(param0->boxApp);
    BoxMonSprite_DeleteSlots(param0->monSpriteManager, &param0->monSprites[v0], 1);
    param0->monIndex = v0;
}

void BoxParty_StartReleaseAnimation(BoxParty *param0, u32 param1)
{
    param0->state = 0;
    param0->monIndex = param1;
    BoxMonSprite_SetAnim(param0->monSpriteManager, &(param0->monSprites[param1]), 1);
}

BOOL BoxParty_UpdateReleaseAnimation(BoxParty *param0)
{
    BoxMonSprite *v0 = &(param0->monSprites[param0->monIndex]);

    switch (param0->state) {
    case 0:
        if (BoxMonSprite_IsAnimDone(param0->monSpriteManager, v0)) {
            const BoxApplicationManager *v1 = BoxGraphics_GetAppManager(param0->boxGraphics);

            if (BoxAppMan_HasCheckedCanReleaseMon(v1)) {
                if (BoxAppMan_CanReleaseMon(v1)) {
                    BoxMonSprite_DeleteSlots(param0->monSpriteManager, v0, 1);
                    return 1;
                } else {
                    BoxMonSprite_SetAnim(param0->monSpriteManager, v0, 2);
                    param0->state++;
                }
            }
        }
        break;
    case 1:
        if (BoxMonSprite_IsAnimDone(param0->monSpriteManager, v0)) {
            return 1;
        }
        break;
    }

    return 0;
}

void BoxParty_ApplyTransparency(BoxParty *param0)
{
    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_PARTY) {
        u32 v0;
        int v1;

        v0 = BoxApp_GetMonSpriteTransparencyMask(param0->boxApp);

        for (v1 = 0; v1 < 6; v1++) {
            if (param0->monSprites[v1].sprite != NULL) {
                BoxMonSprite_UpdateTransparency(param0->monSpriteManager, &(param0->monSprites[v1]), v0);
            }
        }
    }
}

void BoxParty_UpdateMonItem(BoxParty *param0, u32 param1, u32 param2)
{
    if (param0->monSprites[param1].sprite != NULL) {
        BoxMonSprite_SetHeldItem(param0->monSpriteManager, &param0->monSprites[param1], param2);
        BoxMonSprite_UpdateTransparency(param0->monSpriteManager, &param0->monSprites[param1], BoxApp_GetMonSpriteTransparencyMask(param0->boxApp));
        BoxMonSprite_UpdateFormIcon(param0->monSpriteManager, &param0->monSprites[param1], 0);
    }
}

void BoxParty_UpdateMonMarkings(BoxParty *param0)
{
    u32 v0 = BoxApp_GetCursorPartyPosition(param0->boxApp);
    u32 v1 = BoxApp_GetPreviewedMonMarkings(param0->boxApp);

    if (param0->monSprites[v0].sprite != NULL) {
        BoxMonSprite_SetMarkings(param0->monSpriteManager, &(param0->monSprites[v0]), v1);
    }
}

void BoxParty_PlaceMonSprite(BoxParty *param0, u32 param1, u32 param2, BoxMonSprite *param3)
{
    BoxMonSprite_CopySlot(&param0->monSprites[param1], param3, 1);
    BoxMonSprite_LoadIcon(param0->monSpriteManager, param3, param2);
    BoxMonSprite_InitSlots(param0->monSpriteManager, &param0->monSprites[param1], 1);

    param0->monIndex = param1;
}

void BoxParty_AddMonSprite(BoxParty *param0, u32 param1, const BoxMonSprite *param2)
{
    u32 v0;
    u32 v1;
    BoxMonSprite *v2;

    v0 = Party_GetCurrentCount(param0->boxApp->party) - 1;
    v1 = 1048 + 32 * v0;
    v2 = &param0->monSprites[v0];

    BoxMonSprite_CopySlot(param2, v2, 1);
    BoxMonSprite_LoadIcon(param0->monSpriteManager, v2, v1);
    Sprite_SetExplicitPriority(v2->sprite, 1);
    BoxGraphics_SetSpritePriority(v2->sprite, 4 + v0);

    param0->monIndex = param1;
}

void BoxParty_SetMonSprite(BoxParty *param0, u32 param1, const BoxMonSprite *param2)
{
    u32 v0;
    u32 v1;
    BoxMonSprite *v2;

    v0 = param1;
    v1 = 1048 + 32 * v0;
    v2 = &param0->monSprites[v0];

    BoxMonSprite_CopySlot(param2, v2, 1);
    BoxMonSprite_LoadIcon(param0->monSpriteManager, v2, v1);
    Sprite_SetExplicitPriority(v2->sprite, 1);
    BoxGraphics_SetSpritePriority(v2->sprite, 4 + v0);

    param0->monIndex = param1;
}

BoxMonSprite *BoxParty_GetMonSprite(BoxParty *param0, u32 param1)
{
    GF_ASSERT(param1 < 6);
    return &param0->monSprites[param1];
}

void BoxParty_GetMonPosition(BoxParty *param0, u32 param1, s32 *param2, s32 *param3)
{
    if (param1 == 6) {
        *param2 = 192 + param0->xOffset;
        *param3 = 184;
    } else {
        *param2 = sBoxPartyMonPositions[param1].x + param0->xOffset;
        *param3 = sBoxPartyMonPositions[param1].y;
    }
}

static void BoxParty_DrawWindow(BoxParty *param0, u32 param1)
{
    u32 v0, v1, v2;

    if (param1 <= 2) {
        v0 = ((2 - param1) * 15) * 2;
        v1 = 24;
        v2 = 0;
    } else {
        if (param1 >= 26) {
            return;
        }

        v0 = 0;
        v1 = 26 - param1;
        v2 = 24 - v1;
    }

    Bg_LoadToTilemapRect(param0->bgConfig, 2, ((u8 *)param0->screenData->rawData) + v0, param0->tileOffset, v2, 15, v1);
}

static void BoxParty_InitMonPath(BoxParty *param0, VecFx32 *param1)
{
    fx32 v0, v1;
    u32 v2, v3, v4;

    v4 = 0;

    for (v2 = 0; v2 < (6 - 1); v2++) {
        v0 = ((sBoxPartyMonPositions[v2].x - sBoxPartyMonPositions[v2 + 1].x) * FX32_ONE) / 8;
        v1 = ((sBoxPartyMonPositions[v2].y - sBoxPartyMonPositions[v2 + 1].y) * FX32_ONE) / 8;

        for (v3 = 0; v3 < (8 - 1); v3++) {
            param1[v3].x = ((sBoxPartyMonPositions[v2 + 1].x + param0->xOffset) * FX32_ONE) + (v0 * (v3 + 1));
            param1[v3].y = (sBoxPartyMonPositions[v2 + 1].y * FX32_ONE) + (v1 * (v3 + 1));
            param1[v3].z = 0;
        }

        param1[v3].x = ((sBoxPartyMonPositions[v2].x + param0->xOffset) * FX32_ONE);
        param1[v3].y = (sBoxPartyMonPositions[v2].y * FX32_ONE);
        param1[v3].z = 0;
        param1 += 8;
    }
}

static void BoxParty_ShiftMonY(BoxParty *param0, fx32 param1)
{
    VecFx32 v0;
    int v1;

    for (v1 = 0; v1 < 6; v1++) {
        if (param0->monSprites[v1].sprite != NULL) {
            v0 = *Sprite_GetPosition(param0->monSprites[v1].sprite);
            v0.y += param1;
            Sprite_SetPosition(param0->monSprites[v1].sprite, &v0);

            if (param1 < 0) {
                if (v0.y < 851968) {
                    Sprite_SetDrawFlag(param0->monSprites[v1].sprite, TRUE);
                }
            } else {
                if (v0.y >= 851968) {
                    Sprite_SetDrawFlag(param0->monSprites[v1].sprite, FALSE);
                }
            }
        } else {
            break;
        }
    }
}

static void BoxParty_CreateMonSprites(BoxParty *param0, BOOL param1)
{
    Pokemon *v0;
    int v1, v2, v3;

    v3 = (param1) ? 0 : 208;
    v2 = Party_GetCurrentCount(param0->boxApp->party);

    for (v1 = 0; v1 < v2; v1++) {
        v0 = Party_GetPokemonBySlotIndex(param0->boxApp->party, v1);
        BoxMonSprite_CreateFromBoxMon(param0->monSpriteManager, (BoxPokemon *)v0, sBoxPartyMonPositions[v1].x + param0->xOffset, sBoxPartyMonPositions[v1].y + v3, 1, 4 + v1, 1048 + 32 * v1, &param0->monSprites[v1]);
        Sprite_SetDrawFlag(param0->monSprites[v1].sprite, param1);
    }
}

static void BoxParty_DeleteMonSprites(BoxParty *param0)
{
    int v0, v1;

    v1 = Party_GetCurrentCount(param0->boxApp->party);

    for (v0 = 0; v0 < v1; v0++) {
        if (param0->monSprites[v0].sprite) {
            BoxMonSprite_DeleteSlots(param0->monSpriteManager, &(param0->monSprites[v0]), 1);
        }
    }
}
