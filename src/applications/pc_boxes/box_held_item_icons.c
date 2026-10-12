#include "applications/pc_boxes/box_held_item_icons.h"

#include <nitro.h>
#include <string.h>

#include "constants/items.h"

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics.h"
#include "applications/pc_boxes/box_cursor_sprite.h"
#include "applications/pc_boxes/box_party.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_cursor_sprite.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_held_item_icons_decl.h"

#include "bg_window.h"
#include "graphics.h"
#include "heap.h"
#include "item.h"
#include "sprite.h"
#include "sys_task.h"
#include "sys_task_manager.h"

static const struct {
    u32 tileOffset;
    u32 paletteIndex;
} sBoxHeldItemIconSlots[] = {
    { 1536 * 0x20, 7 },
    { 1552 * 0x20, 8 },
    { 1568 * 0x20, 9 },
};

struct BoxHeldItemIcons_t {
    BOOL isLoaded;
    BoxGraphics *boxGraphics;
    const BoxApplication *boxApp;
    BgConfig *bgConfig;
    SpriteList *spriteList;
    BoxMonSpriteManager *monSpriteManager;
    BoxCursorSprite *cursorSprite;
    Sprite *sprites[3];
    int slotStates[3];
    int activeAnimCount;
    int activeSlot;
};

typedef struct {
    BoxHeldItemIcons *heldItemIcons;
    Sprite *sprite;
    VecFx32 currentPos;
    VecFx32 targetPos;
    fx32 stepX;
    fx32 stepY;
    int priority;
    int stepCount;
    int state;
} BoxHeldItemAnim;

static void BoxHeldItem_InitSprites(BoxHeldItemIcons *param0);
static void BoxHeldItem_DeleteSprites(BoxHeldItemIcons *param0);
static int BoxHeldItem_AllocSlot(BoxHeldItemIcons *param0, int param1);
static int BoxHeldItem_FindSlot(BoxHeldItemIcons *param0, int param1);
static void BoxHeldItem_SetSlotState(BoxHeldItemIcons *param0, int param1, int param2);
static void BoxHeldItem_ShowPreviewedItem(BoxHeldItemIcons *param0);
static void BoxHeldItem_ShowCursorItem(BoxHeldItemIcons *param0);
static void BoxHeldItem_GetCursorPosition(BoxHeldItemIcons *param0, VecFx32 *param1, u32 *param2);
static void BoxHeldItem_LoadItemIcon(BoxHeldItemIcons *param0, int param1, int param2);
static void BoxHeldItem_StartAnim(BoxHeldItemIcons *param0, int param1, const VecFx32 *param2, int param3, int param4);
static void BoxHeldItem_AnimTask(SysTask *param0, void *param1);

BOOL BoxHeldItem_Load(BoxHeldItemIcons **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4)
{
    BoxHeldItemIcons *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxHeldItemIcons));

    if (v0) {
        v0->boxGraphics = param1;
        v0->boxApp = param2;
        v0->bgConfig = param3;
        v0->spriteList = param4;
        v0->monSpriteManager = BoxGraphics_GetBoxMonSpriteManager(param1);
        v0->cursorSprite = BoxGraphics_GetCursorSprite(param1);
        v0->activeAnimCount = 0;
        v0->isLoaded = (BoxApp_GetBoxMode(param2) == PC_MODE_MOVE_ITEMS);

        BoxHeldItem_InitSprites(v0);
        *param0 = v0;

        return 1;
    }

    return 0;
}

void BoxHeldItem_Free(BoxHeldItemIcons *param0)
{
    BoxHeldItem_DeleteSprites(param0);
    Heap_Free(param0);
}

static void BoxHeldItem_InitSprites(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        SpriteResourcesHeader v0;
        NNSG2dImageProxy v1;
        NNSG2dCharacterData *v2;
        void *v3;
        int v4;

        BoxGraphics_InitSpriteResources(&v0, &v1, BoxGraphics_GetPaletteProxy(param0->boxGraphics), param0->monSpriteManager->formCellBankData, param0->monSpriteManager->formAnimBankData, 0);
        v3 = Graphics_GetCharData(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(1, 1), 0, &v2, HEAP_ID_BOX_GRAPHICS);

        if (v3) {
            int v5;

            v2->mappingType = GX_GetOBJVRamModeChar();

            for (v5 = 0; v5 < 3; v5++) {
                NNS_G2dInitImageProxy(&v1);
                NNS_G2dLoadImage1DMapping(v2, sBoxHeldItemIconSlots[v5].tileOffset, NNS_G2D_VRAM_TYPE_2DMAIN, &v1);

                param0->sprites[v5] = BoxGraphics_CreateSprite(param0->spriteList, &v0, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN);

                Sprite_SetExplicitPalette(param0->sprites[v5], sBoxHeldItemIconSlots[v5].paletteIndex);
                Sprite_SetDrawFlag(param0->sprites[v5], FALSE);
                Sprite_SetAffineOverwriteMode(param0->sprites[v5], 1);

                param0->slotStates[v5] = 0;
            }

            Heap_Free(v3);
        }
    } else {
        int v6;

        for (v6 = 0; v6 < 3; v6++) {
            param0->sprites[v6] = NULL;
            param0->slotStates[v6] = 0;
        }
    }
}

static void BoxHeldItem_DeleteSprites(BoxHeldItemIcons *param0)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->sprites[v0]) {
            Sprite_Delete(param0->sprites[v0]);
        }
    }
}

static int BoxHeldItem_AllocSlot(BoxHeldItemIcons *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->slotStates[v0] == 0) {
            param0->slotStates[v0] = param1;
            return v0;
        }
    }

    return -1;
}

static int BoxHeldItem_FindSlot(BoxHeldItemIcons *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->slotStates[v0] == param1) {
            return v0;
        }
    }

    return -1;
}

static void BoxHeldItem_SetSlotState(BoxHeldItemIcons *param0, int param1, int param2)
{
    param0->slotStates[param1] = param2;
}

void BoxHeldItem_Show(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    BoxHeldItem_ShowPreviewedItem(param0);
    BoxHeldItem_ShowCursorItem(param0);
}

static void BoxHeldItem_ShowPreviewedItem(BoxHeldItemIcons *param0)
{
    u32 v0 = BoxApp_GetPreviewedMonHeldItem(param0->boxApp);

    if (v0 != 0) {
        int v1 = BoxHeldItem_AllocSlot(param0, 1);

        BoxHeldItem_LoadItemIcon(param0, v1, v0);
        Sprite_SetAnim(param0->sprites[v1], 6);
        Sprite_SetDrawFlag(param0->sprites[v1], TRUE);
    }
}

static void BoxHeldItem_ShowCursorItem(BoxHeldItemIcons *param0)
{
    u32 item = BoxApp_GetCursorItem(param0->boxApp);

    if (item != ITEM_NONE) {
        VecFx32 v1;
        u32 v2;
        int v3 = BoxHeldItem_AllocSlot(param0, 3);

        BoxCursorSprite_GetPosition(param0->cursorSprite, &v1);

        v1.x += (0 << FX32_SHIFT);
        v1.y += (8 << FX32_SHIFT);

        if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_PARTY) {
            v2 = 1;
        } else {
            v2 = 2;
        }

        Graphics_LoadObjectTiles(16, Item_FileID(item, 1), 0, sBoxHeldItemIconSlots[v3].tileOffset, 0, 0, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadPalette(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(item, 2), 1, sBoxHeldItemIconSlots[v3].paletteIndex * 0x20, 0x20, HEAP_ID_BOX_GRAPHICS);
        Sprite_SetExplicitPriority(param0->sprites[v3], v2);

        BoxGraphics_SetSpritePriority(param0->sprites[v3], 2);

        Sprite_SetPosition(param0->sprites[v3], &v1);
        Sprite_SetAnim(param0->sprites[v3], 0);
        Sprite_SetDrawFlag(param0->sprites[v3], TRUE);
    }
}

static void BoxHeldItem_GetCursorPosition(BoxHeldItemIcons *param0, VecFx32 *param1, u32 *param2)
{
    param1->z = 0;

    if (BoxApp_GetCursorLocation(param0->boxApp) == CURSOR_IN_PARTY) {
        s32 v0, v1;

        BoxParty_GetMonPosition(BoxGraphics_GetBoxParty(param0->boxGraphics), BoxApp_GetCursorPartyPosition(param0->boxApp), &v0, &v1);

        param1->x = (v0 + 10) << FX32_SHIFT;
        param1->y = (v1 + 8) << FX32_SHIFT;
        *param2 = 1;
    } else {
        param1->x = 112 + BoxGraphics_GetCompareXOffset(param0->boxGraphics) + BoxApp_GetCursorBoxCol(param0->boxApp) * 24 + 10;
        param1->y = 40 + BoxApp_GetCursorBoxRow(param0->boxApp) * 24 + 8;
        param1->x <<= FX32_SHIFT;
        param1->y <<= FX32_SHIFT;
        *param2 = 2;
    }
}

static void BoxHeldItem_LoadItemIcon(BoxHeldItemIcons *param0, int param1, int param2)
{
    if (param1 >= 0) {
        VecFx32 v0;
        u32 v1;

        BoxHeldItem_GetCursorPosition(param0, &v0, &v1);

        Graphics_LoadObjectTiles(16, Item_FileID(param2, 1), 0, sBoxHeldItemIconSlots[param1].tileOffset, 0, 0, HEAP_ID_BOX_GRAPHICS);
        Graphics_LoadPalette(NARC_INDEX_ITEMTOOL__ITEMDATA__ITEM_ICON, Item_FileID(param2, 2), 1, sBoxHeldItemIconSlots[param1].paletteIndex * 0x20, 0x20, HEAP_ID_BOX_GRAPHICS);
        Sprite_SetExplicitPriority(param0->sprites[param1], v1);

        BoxGraphics_SetSpritePriority(param0->sprites[param1], 3);
        Sprite_SetPosition(param0->sprites[param1], &v0);
    }
}

void BoxHeldItem_Refresh(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0, v1;

        v0 = BoxHeldItem_FindSlot(param0, 1);

        if (v0 >= 0) {
            BoxHeldItem_SetSlotState(param0, v0, 2);
            Sprite_SetAnim(param0->sprites[v0], 2);
        }

        v1 = BoxApp_GetPreviewedMonHeldItem(param0->boxApp);

        if (v1 != 0) {
            v0 = BoxHeldItem_AllocSlot(param0, 1);

            if (v0 >= 0) {
                BoxHeldItem_LoadItemIcon(param0, v0, v1);
                Sprite_SetAnim(param0->sprites[v0], 1);
                Sprite_SetDrawFlag(param0->sprites[v0], TRUE);
            }
        }
    }
}

BOOL BoxHeldItem_IsAnimDone(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded == 0) {
        return 1;
    } else {
        int v0 = BoxHeldItem_FindSlot(param0, 1);

        if (v0 >= 0) {
            if (Sprite_IsAnimated(param0->sprites[v0])) {
                return 0;
            }
        }

        v0 = BoxHeldItem_FindSlot(param0, 2);

        if (v0 >= 0) {
            if (Sprite_IsAnimated(param0->sprites[v0])) {
                return 0;
            }

            BoxHeldItem_SetSlotState(param0, v0, 0);
        }

        return 1;
    }
}

static void BoxHeldItem_StartAnim(BoxHeldItemIcons *param0, int param1, const VecFx32 *param2, int param3, int param4)
{
    BoxHeldItemAnim *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxHeldItemAnim));

    if (v0) {
        v0->heldItemIcons = param0;
        v0->sprite = param0->sprites[param1];
        v0->currentPos = *(Sprite_GetPosition(v0->sprite));
        v0->targetPos = *param2;
        v0->stepX = (v0->targetPos.x - v0->currentPos.x) / param4;
        v0->stepY = (v0->targetPos.y - v0->currentPos.y) / param4;
        v0->stepCount = param4;
        v0->priority = param3;
        v0->state = 0;

        if (BoxGraphics_StartVBlankTask(BoxHeldItem_AnimTask, v0, 0)) {
            param0->activeAnimCount++;
        } else {
            Heap_Free(v0);
        }
    }
}

static void BoxHeldItem_AnimTask(SysTask *param0, void *param1)
{
    BoxHeldItemAnim *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->stepCount) {
            v0->currentPos.x += v0->stepX;
            v0->currentPos.y += v0->stepY;
            Sprite_SetPosition(v0->sprite, &v0->currentPos);
            v0->stepCount--;
        } else {
            Sprite_SetPosition(v0->sprite, &v0->targetPos);
            v0->state++;
        }
        break;
    case 1:
        if (Sprite_IsAnimated(v0->sprite) == 0) {
            BoxGraphics_SetSpritePriority(v0->sprite, v0->priority);
            v0->heldItemIcons->activeAnimCount--;
            SysTask_Done(param0);
            BoxGraphics_DeferFree(v0, NULL, NULL);
        }
        break;
    }
}

void BoxHeldItem_StartReturnToPreview(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 1);

        if (v0 >= 0) {
            VecFx32 v1;

            BoxCursorSprite_GetPosition(param0->cursorSprite, &v1);

            v1.x += (0 << FX32_SHIFT);
            v1.y += (8 << FX32_SHIFT);

            BoxHeldItem_SetSlotState(param0, v0, 3);
            Sprite_SetAnim(param0->sprites[v0], 3);
            BoxHeldItem_StartAnim(param0, v0, &v1, 2, 12);
        }
    }
}

BOOL BoxHeldItem_IsReturnToPreviewDone(BoxHeldItemIcons *param0)
{
    return param0->activeAnimCount == 0;
}

void BoxHeldItem_StartReturnToMon(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 1);

        if (v0 >= 0) {
            BoxHeldItem_SetSlotState(param0, v0, 2);
            Sprite_SetAnim(param0->sprites[v0], 2);
        }
    }
}

BOOL BoxHeldItem_IsReturnToMonDone(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 2);

        if (v0 >= 0) {
            if (Sprite_IsAnimated(param0->sprites[v0])) {
                return 0;
            }

            BoxHeldItem_SetSlotState(param0, v0, 0);
        }
    }

    return 1;
}

void BoxHeldItem_StartReturnToCursor(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 3);

        if (v0 >= 0) {
            VecFx32 v1;
            u32 v2;

            BoxHeldItem_GetCursorPosition(param0, &v1, &v2);
            BoxHeldItem_SetSlotState(param0, v0, 1);
            Sprite_SetAnim(param0->sprites[v0], 4);
            BoxHeldItem_StartAnim(param0, v0, &v1, 3, 12);
        }
    }
}

BOOL BoxHeldItem_IsReturnToCursorDone(BoxHeldItemIcons *param0)
{
    return param0->activeAnimCount == 0;
}

void BoxHeldItem_StartSwap(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 3);
        int v1 = BoxHeldItem_FindSlot(param0, 1);

        if ((v0 >= 0) && (v1 >= 0)) {
            VecFx32 v2;
            u32 v3;

            BoxHeldItem_GetCursorPosition(param0, &v2, &v3);
            BoxHeldItem_SetSlotState(param0, v0, 1);
            Sprite_SetAnim(param0->sprites[v0], 4);

            BoxHeldItem_StartAnim(param0, v0, &v2, 3, 12);
            BoxCursorSprite_GetPosition(param0->cursorSprite, &v2);

            v2.x += (0 << FX32_SHIFT);
            v2.y += (8 << FX32_SHIFT);

            BoxHeldItem_SetSlotState(param0, v1, 3);
            Sprite_SetAnim(param0->sprites[v1], 3);
            BoxHeldItem_StartAnim(param0, v1, &v2, 2, 12);
        }
    }
}

BOOL BoxHeldItem_IsSwapDone(BoxHeldItemIcons *param0)
{
    return param0->activeAnimCount == 0;
}

void BoxHeldItem_StartShrink(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 3);

        if (v0 >= 0) {
            Sprite_SetAnim(param0->sprites[v0], 5);
            param0->activeSlot = v0;
            return;
        }

        v0 = BoxHeldItem_FindSlot(param0, 1);

        if (v0 >= 0) {
            Sprite_SetAnim(param0->sprites[v0], 2);
            param0->activeSlot = v0;
            return;
        }

        param0->activeSlot = -1;
    }
}

BOOL BoxHeldItem_IsShrinkDone(BoxHeldItemIcons *param0)
{
    if (param0->isLoaded) {
        if (param0->activeSlot != -1) {
            if (Sprite_IsAnimated(param0->sprites[param0->activeSlot])) {
                return 0;
            }

            BoxHeldItem_SetSlotState(param0, param0->activeSlot, 0);
            param0->activeSlot = -1;
        }
    }

    return 1;
}

void BoxHeldItem_SetPosition(BoxHeldItemIcons *param0, const VecFx32 *param1)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 3);

        if (v0 >= 0) {
            VecFx32 v1 = *param1;

            v1.x += (0 << FX32_SHIFT);
            v1.y += (8 << FX32_SHIFT);

            Sprite_SetPosition(param0->sprites[v0], &v1);
        }
    }
}

void BoxHeldItem_SetPriority(BoxHeldItemIcons *param0, u32 param1)
{
    if (param0->isLoaded) {
        int v0 = BoxHeldItem_FindSlot(param0, 3);

        if (v0 >= 0) {
            Sprite_SetExplicitPriority(param0->sprites[v0], param1);
        }
    }
}
