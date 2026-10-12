#include "vs_recorder_viewer/vs_recorder_viewer_02246B00.h"

#include <nitro.h>
#include <string.h>

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub1.h"

#include "bg_window.h"
#include "game_options.h"
#include "graphics.h"
#include "heap.h"
#include "inlines.h"
#include "narc.h"
#include "palette.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "touch_screen_actions.h"

static inline void VsRecorderViewerIdEntry_SetItemTouchRect(VsRecorderViewerIdEntryState *param0, int param1, s16 param2, s16 param3);

VsRecorderViewerIdEntryConfig *VsRecorderViewerIdEntry_NewConfig(enum HeapID heapID, int param1, int param2[], Options *options)
{
    int v0;
    VsRecorderViewerIdEntryConfig *v1 = NULL;

    v1 = Heap_Alloc(heapID, sizeof(VsRecorderViewerIdEntryConfig));
    MI_CpuFill8(v1, 0, sizeof(VsRecorderViewerIdEntryConfig));
    v1->digitCount = param1;
    v1->idString = String_Init(param1 + 1, heapID);
    v1->options = options;

    for (v0 = 0; v0 < 3; v0++) {
        v1->categoryCounts[v0] = param2[v0];
    }

    v1->categoryCounts[v0] = param2[v0 - 1];

    return v1;
}

void VsRecorderViewerIdEntry_FreeConfig(VsRecorderViewerIdEntryConfig *param0)
{
    GF_ASSERT(param0->idString != NULL);
    GF_ASSERT(param0 != NULL);

    String_Free(param0->idString);
    Heap_Free(param0);
}

void VsRecorderViewerIdEntry_SetCategory(VsRecorderViewerIdEntryState *param0, int param1)
{
    int v0;

    param0->prevCategory = param0->category;
    param0->category = param1;
    param0->firstItemIndex = 0;
    param0->lastItemIndex = 0;
    param0->prevFirstItemIndex = 0;
    param0->prevLastItemIndex = 0;

    if (param0->category != 0) {
        param0->firstItemIndex = param0->categoryRanges[param0->category - 1][0];
        param0->lastItemIndex = param0->categoryRanges[param0->category - 1][1];
    }

    if (param0->prevCategory != 0) {
        param0->prevFirstItemIndex = param0->categoryRanges[param0->prevCategory - 1][0];
        param0->prevLastItemIndex = param0->categoryRanges[param0->prevCategory - 1][1];
    }
}

void VsRecorderViewerIdEntry_InitLayout(VsRecorderViewerIdEntryState *param0)
{
    int v0;

    param0->graphics.cursorHidden = 1;

    {
        param0->categoryRanges[0][0] = 0;
        param0->categoryRanges[0][1] = param0->config.categoryCounts[0];
        param0->categoryRanges[1][0] = param0->config.categoryCounts[0];
        param0->categoryRanges[1][1] = param0->config.categoryCounts[0] + param0->config.categoryCounts[1];
        param0->categoryRanges[2][0] = param0->config.categoryCounts[0] + param0->config.categoryCounts[1];
        param0->categoryRanges[2][1] = param0->config.categoryCounts[0] + param0->config.categoryCounts[1] + param0->config.categoryCounts[2];
    }

    VsRecorderViewerIdEntry_SetCategory(param0, 1);

    for (v0 = 0; v0 < 3; v0++) {
        param0->itemCount += param0->config.categoryCounts[v0];
    }

    {
        int v1 = 0;
        const v2[][3] = {
            { 56, 20, 8 },
            { 56, 12, 0 },
        };

        if (param0->config.categoryCounts[0] != 4) {
            v1 = 1;
        }

        for (v0 = 0; v0 < 3; v0++) {
            param0->categoryXPositions[v0] = v2[v1][v0];
        }

        param0->categoryXPositions[v0] = v2[v1][v0 - 1];
    }

    {
        int v3 = 0;

        for (v0 = 0; v0 < 3 - 1; v0++) {
            v3 += param0->config.categoryCounts[v0];
            param0->separatorButtons[v0].value = v3 - 1;
        }
    }

    {
        int v4;
        int v5 = 0;

        v0 = 0;

        do {
            for (v4 = 0; v4 < param0->config.categoryCounts[v5]; v4++) {
                param0->itemButtons[v0].category = v5 + 1;
                v0++;
            }

            v5++;
        } while (v0 < param0->itemCount);
    }
}

void VsRecorderViewerIdEntry_SetStep(VsRecorderViewerIdEntryState *param0, int param1)
{
    param0->step = param1;
    param0->unused_1F8 = 0;
    param0->animState = 0;
    param0->animTimer = 0;
}

BOOL VsRecorderViewerIdEntry_Init(VsRecorderViewerIdEntryState *param0)
{
    VsRecorderViewerIdEntry_InitLayout(param0);
    VsRecorderViewerIdEntry_InitTouchInput(param0);
    VsRecorderViewerIdEntry_LoadGraphics(param0);
    VsRecorderViewerIdEntry_UpdateItemSelection(param0);
    VsRecorderViewerIdEntry_CreateItemSprites(param0);
    VsRecorderViewerIdEntry_LayoutItems(param0, 0);
    VsRecorderViewerIdEntry_CreateCursorSprites(param0);
    VsRecorderViewerIdEntry_UpdateTouchRects(param0);
    VsRecorderViewerIdEntry_SetStep(param0, 1);

    return 0;
}

BOOL VsRecorderViewerIdEntry_Exit(VsRecorderViewerIdEntryState *param0)
{
    TouchScreenActions_Free(param0->graphics.touchScreenActions);
    VsRecorderViewerIdEntry_FreeGraphics(param0);

    return 1;
}

BOOL VsRecorderViewerIdEntry_UpdateInput(VsRecorderViewerIdEntryState *param0)
{
    switch (param0->animState) {
    case 0:
        param0->animState++;
        break;
    default:
        VsRecorderViewerIdEntry_ProcessSelection(param0);
        TouchScreenActions_HandleAction(param0->graphics.touchScreenActions);
        break;
    }

    return 0;
}

BOOL VsRecorderViewerIdEntry_UpdateAnimation(VsRecorderViewerIdEntryState *param0)
{
    int v0;
    static f32 v1[] = {
        0.5f, 0.2f, 0.5f, 1.0f, 1.2f, 1.0f, 1.0f
    };
    static f32 v2[] = {
        0.8f, 0.6f, 0.4f, 0.2f, 0.8f, 1.0f, 1.0f
    };

    switch (param0->animState) {
    case 0:
        VsRecorderViewerIdEntry_SetCursorVisible(param0, 0, 0);
        {
            for (v0 = 0; v0 < param0->itemCount; v0++) {
                if (param0->itemButtons[v0].rect.timer == 0) {
                    continue;
                }

                ManagedSprite_OffsetPositionXY(param0->itemButtons[v0].sprite, param0->itemButtons[v0].rect.offsetX, param0->itemButtons[v0].rect.offsetY);
                param0->itemButtons[v0].rect.timer--;

                if ((v0 >= param0->firstItemIndex) && (v0 < param0->lastItemIndex)) {
                    ManagedSprite_SetAffineScale(param0->itemButtons[v0].sprite, v1[param0->itemButtons[v0].rect.scaleIndex], v1[param0->itemButtons[v0].rect.scaleIndex]);
                    param0->itemButtons[v0].rect.scaleIndex++;
                    ManagedSprite_SetAffineOverwriteMode(param0->itemButtons[v0].sprite, AFFINE_OVERWRITE_MODE_DOUBLE);
                }

                if ((v0 >= param0->prevFirstItemIndex) && (v0 < param0->prevLastItemIndex)) {
                    ManagedSprite_SetAffineScale(param0->itemButtons[v0].sprite, v2[param0->itemButtons[v0].rect.scaleIndex], v2[param0->itemButtons[v0].rect.scaleIndex]);
                    param0->itemButtons[v0].rect.scaleIndex++;
                    ManagedSprite_SetAffineOverwriteMode(param0->itemButtons[v0].sprite, AFFINE_OVERWRITE_MODE_DOUBLE);
                }
            }

            for (v0 = 0; v0 < 3 - 1; v0++) {
                if (param0->separatorButtons[v0].rect.timer == 0) {
                    continue;
                }

                ManagedSprite_OffsetPositionXY(param0->separatorButtons[v0].sprite, param0->separatorButtons[v0].rect.offsetX, param0->separatorButtons[v0].rect.offsetY);
                param0->separatorButtons[v0].rect.timer--;
            }

            if (param0->itemButtons[0].rect.timer == 0) {
                for (v0 = param0->firstItemIndex; v0 < param0->lastItemIndex; v0++) {
                    ManagedSprite_SetAnim(param0->itemButtons[v0].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v0].value, param0->itemButtons[v0].selected));
                    ManagedSprite_TickFrame(param0->itemButtons[v0].sprite);
                }

                for (v0 = param0->prevFirstItemIndex; v0 < param0->prevLastItemIndex; v0++) {
                    ManagedSprite_SetAnim(param0->itemButtons[v0].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v0].value, param0->itemButtons[v0].selected));
                    ManagedSprite_TickFrame(param0->itemButtons[v0].sprite);
                }
                param0->animState++;
            }
            param0->animTimer++;
        }
        break;
    case 1:
        for (v0 = param0->firstItemIndex; v0 < param0->lastItemIndex; v0++) {
            if (param0->itemButtons[v0].rect.scaleIndex == 6) {
                ManagedSprite_SetAffineOverwriteMode(param0->itemButtons[v0].sprite, AFFINE_OVERWRITE_MODE_NORMAL);
                continue;
            }

            ManagedSprite_SetAffineScale(param0->itemButtons[v0].sprite, v1[param0->itemButtons[v0].rect.scaleIndex], v1[param0->itemButtons[v0].rect.scaleIndex]);
            param0->itemButtons[v0].rect.scaleIndex++;
        }

        for (v0 = param0->prevFirstItemIndex; v0 < param0->prevLastItemIndex; v0++) {
            if (param0->itemButtons[v0].rect.scaleIndex == 6) {
                ManagedSprite_SetAffineOverwriteMode(param0->itemButtons[v0].sprite, AFFINE_OVERWRITE_MODE_NORMAL);
                continue;
            }

            ManagedSprite_SetAffineScale(param0->itemButtons[v0].sprite, v2[param0->itemButtons[v0].rect.scaleIndex], v2[param0->itemButtons[v0].rect.scaleIndex]);
            param0->itemButtons[v0].rect.scaleIndex++;
        }

        param0->animTimer++;

        if (param0->animTimer == 6) {
            param0->animState++;
        }
        break;
    default:
        VsRecorderViewerIdEntry_UpdateTouchRects(param0);

        if (param0->selection.forward == 0) {
            VsRecorderViewerIdEntry_SetSelectorPosition(param0, VsRecorderViewerIdEntry_GetFirstItemIndexInCategory(param0, param0->selection.value));
        } else {
            VsRecorderViewerIdEntry_SetSelectorPosition(param0, VsRecorderViewerIdEntry_GetLastItemIndexInCategory(param0, param0->selection.value));
        }

        if (param0->category != 0) {
            VsRecorderViewerIdEntry_SetCursorVisible(param0, 0, 1);
        }

        VsRecorderViewerIdEntry_ClearSelection(param0);
        VsRecorderViewerIdEntry_SetStep(param0, 1);
        break;
    }

    return 0;
}

static BOOL (*const sVsRecorderViewerIdEntryStepTable[])(VsRecorderViewerIdEntryState *wk) = {
    VsRecorderViewerIdEntry_Init,
    VsRecorderViewerIdEntry_UpdateInput,
    VsRecorderViewerIdEntry_UpdateAnimation,
    VsRecorderViewerIdEntry_Exit,
};

BOOL VsRecorderViewerIdEntry_Run(VsRecorderViewerIdEntryState *param0)
{
    BOOL v0 = sVsRecorderViewerIdEntryStepTable[param0->step](param0);

    if (v0 == 0) {
        VsRecorderViewerIdEntry_UpdateCursors(param0);
    }

    return v0;
}

void VsRecorderViewerIdEntry_ConfirmId(VsRecorderViewerIdEntryState *param0)
{
    int v0;
    u32 v1 = 0;
    String *v2 = String_Init(100, HEAP_ID_102);

    param0->confirmed = 1;
    param0->idValue = 0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if (param0->itemButtons[v0].value == 0) {
            param0->itemButtons[v0].value = 1;
            ManagedSprite_SetAnim(param0->itemButtons[v0].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v0].value, param0->itemButtons[v0].selected));
        }

        v1 = param0->itemButtons[v0].value - 1;

        if (v0 != 0) {
            param0->idValue *= 10;
        }

        param0->idValue += v1;

        String_FormatInt(v2, v1, 1, 1, 1);
        String_Concat(param0->config.idString, v2);
    }

    String_Free(v2);
    VsRecorderViewerIdEntry_SetStep(param0, 3);
}

void VsRecorderViewerIdEntry_Backspace(VsRecorderViewerIdEntryState *param0)
{
    int v0;
    int v1;
    int v2;

    if (param0->category == 0) {
        v0 = param0->cursorButtons[0].value = param0->itemCount - 1;
        v2 = param0->itemButtons[v0].category;
        param0->selection.action = 1;
        param0->selection.value = v2;
        param0->selection.forward = 1;
        return;
    }

    v0 = param0->cursorButtons[0].value;
    param0->itemButtons[v0].value = 0;

    ManagedSprite_SetAnim(param0->itemButtons[v0].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v0].value, param0->itemButtons[v0].selected));

    v1 = param0->itemButtons[v0].category;

    if (v0 > 0) {
        v0--;
        ManagedSprite_SetAnim(param0->itemButtons[v0].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v0].value, param0->itemButtons[v0].selected));
        v2 = param0->itemButtons[v0].category;

        if (v1 != v2) {
            param0->selection.action = 1;
            param0->selection.value = v2;
            param0->selection.forward = 1;
        } else {
            param0->selection.action = 2;
            param0->selection.value = v0;
        }
    } else {
        param0->confirmed = 0;
        VsRecorderViewerIdEntry_SetStep(param0, 3);
    }
}

void VsRecorderViewerIdEntry_InitTouchInput(VsRecorderViewerIdEntryState *param0)
{
    int v0;

    for (v0 = 0; v0 < 11 + 1; v0++) {
        param0->itemButtons[v0].touchRect = &param0->graphics.touchRects[v0];
    }

    {
        const s16 v1[][4] = {
            { 32, 80, 20, 20 },
            { 80, 80, 20, 20 },
            { 128, 80, 20, 20 },
            { 176, 80, 20, 20 },
            { 224, 80, 20, 20 },
            { 32, 128, 20, 20 },
            { 80, 128, 20, 20 },
            { 128, 128, 20, 20 },
            { 176, 128, 20, 20 },
            { 224, 128, 20, 20 },
            { 64 + 12, 176, 60, 12 },
            { 192, 176, 60, 12 },
        };

        for (; v0 < 24; v0++) {
            param0->graphics.touchRects[v0].rect.top = v1[v0 - 12][1] - v1[v0 - 12][3];
            param0->graphics.touchRects[v0].rect.left = v1[v0 - 12][0] - v1[v0 - 12][2];
            param0->graphics.touchRects[v0].rect.bottom = v1[v0 - 12][1] + v1[v0 - 12][3];
            param0->graphics.touchRects[v0].rect.right = v1[v0 - 12][0] + v1[v0 - 12][2];
        }

        param0->graphics.touchRects[22].rect.top = 152;
        param0->graphics.touchRects[22].rect.left = 32;
        param0->graphics.touchRects[22].rect.bottom = 152 + 32;
        param0->graphics.touchRects[22].rect.right = 128;
        param0->graphics.touchRects[23].rect.top = 152;
        param0->graphics.touchRects[23].rect.left = 128;
        param0->graphics.touchRects[23].rect.bottom = 152 + 32;
        param0->graphics.touchRects[23].rect.right = 224;
    }

    param0->graphics.touchScreenActions = TouchScreenActions_RegisterHandler(param0->graphics.touchRects, 24, VsRecorderViewerIdEntry_TouchCallback, param0, HEAP_ID_102);
}

void VsRecorderViewerIdEntry_TouchCallback(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderViewerIdEntryState *v0 = param2;

    if (v0->step != 1) {
        return;
    }

    if (v0->graphics.cursorHidden != 1) {
        v0->graphics.cursorHidden = 1;
    }

    if (param1 == TOUCH_BUTTON_PRESSED) {
        if ((param0 >= 0) && (param0 <= 11)) {
            if (v0->itemButtons[param0].selected == 1) {
                v0->selection.action = 2;
                v0->selection.value = param0;
            } else {
                v0->selection.action = 1;
                v0->selection.value = v0->itemButtons[param0].category;
            }

            Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
        } else {
            if (param0 == 22) {
                v0->cursorButtons[1].rect.offsetX = 0;
                v0->cursorButtons[1].rect.offsetY = 2;
            } else if (param0 == 23) {
                v0->cursorButtons[1].rect.offsetX = 3;
                v0->cursorButtons[1].rect.offsetY = 2;
            } else {
                v0->cursorButtons[1].rect.offsetX = (param0 - 12) % 5;
                v0->cursorButtons[1].rect.offsetY = (param0 - 12) / 5;
            }

            if ((param0 >= 12) && (param0 <= 21)) {
                int v1;
                int v2;
                int v3;

                if (v0->category == 0) {
                    return;
                }

                Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);

                v1 = v0->cursorButtons[0].value;
                v0->itemButtons[v1].value = param0 - 12 + 1;

                ManagedSprite_SetAnim(v0->itemButtons[v1].sprite, VsRecorderViewerIdEntry_GetAnimForValue(v0->itemButtons[v1].value, v0->itemButtons[v1].selected));
                VsRecorderViewerIdEntry_SetCursorVisible(v0, 1, 1);
                VsRecorderViewerIdEntry_SetTouchCursorPosition(v0, param0 - 12);
                VsRecorderViewerIdEntry_SetCursorVisible(v0, 1, 0);
                VsRecorderViewerIdEntry_SetCursorVisible(v0, 2, 1);
                VsRecorderViewerIdEntry_SetCursorPositionForItem(v0, param0 - 12, 2);
                ManagedSprite_SetAnim(v0->cursorButtons[2].sprite, 3);

                v2 = v0->itemButtons[v1].category;
                v1++;

                if (v1 == v0->itemCount) {
                    v0->selection.action = 1;
                    v0->selection.value = 0;
                    v0->selection.forward = 0;
                } else {
                    v3 = v0->itemButtons[v1].category;

                    if (v2 != v3) {
                        v0->selection.action = 1;
                        v0->selection.value = v3;
                        v0->selection.forward = 0;
                    } else {
                        v0->selection.action = 2;
                        v0->selection.value = v1;
                    }
                }
            } else {
                if (param0 == 22) {
                    Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
                    VsRecorderViewerIdEntry_Backspace(v0);
                } else {
                    Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
                    VsRecorderViewerIdEntry_ConfirmId(v0);
                }
            }
        }
    }
}

void VsRecorderViewerIdEntry_ProcessSelection(VsRecorderViewerIdEntryState *param0)
{
    switch (param0->selection.action) {
    case 0:
        break;
    case 1:
        VsRecorderViewerIdEntry_SetCategory(param0, param0->selection.value);
        VsRecorderViewerIdEntry_UpdateItemSelection(param0);
        VsRecorderViewerIdEntry_LayoutItems(param0, 1);
        VsRecorderViewerIdEntry_SetStep(param0, 2);
        param0->selection.action = 255;
        break;
    case 2:
        VsRecorderViewerIdEntry_SetSelectorPosition(param0, param0->selection.value);
        VsRecorderViewerIdEntry_ClearSelection(param0);
        break;
    case 255:
        break;
    }
}

void VsRecorderViewerIdEntry_ClearSelection(VsRecorderViewerIdEntryState *param0)
{
    param0->selection.action = 0;
    param0->selection.value = 0;
    param0->selection.forward = 0;
}

int VsRecorderViewerIdEntry_GetFirstItemIndexInCategory(VsRecorderViewerIdEntryState *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if (param0->itemButtons[v0].category == param1) {
            return v0;
        }
    }

    return 0;
}

int VsRecorderViewerIdEntry_GetLastItemIndexInCategory(VsRecorderViewerIdEntryState *param0, int param1)
{
    int v0;
    int v1 = 0;
    int v2 = 0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if (param0->itemButtons[v0].category == param1) {
            v2 = 1;
        } else {
            if (v2 == 1) {
                return v0 - 1;
            }
        }
    }

    return param0->itemCount - 1;
}

void VsRecorderViewerIdEntry_LoadGraphics(VsRecorderViewerIdEntryState *param0)
{
    NARC *v0;
    BgConfig *v1;
    SpriteSystem *v2 = param0->graphics.spriteSystem;
    SpriteManager *v3 = param0->graphics.spriteManager;
    PaletteData *v4 = param0->graphics.palette;
    v1 = param0->graphics.bgConfig;
    v0 = param0->graphics.narc;

    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 54, param0->graphics.bgConfig, BG_LAYER_MAIN_3, 0, 0, FALSE, HEAP_ID_102);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 43, v1, BG_LAYER_MAIN_3, 0, 0, FALSE, HEAP_ID_102);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_MAIN_OBJ, v2, v3, v0, 44, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 1000);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 40, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 1000);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 41, FALSE, 1000);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 42, FALSE, 1000);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v4, PLTTBUF_MAIN_OBJ, v2, v3, v0, 88, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 1001);
    SpriteSystem_LoadCharResObjFromOpenNarc(v2, v3, v0, 87, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 1001);
    SpriteSystem_LoadCellResObjFromOpenNarc(v2, v3, v0, 85, FALSE, 1001);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v2, v3, v0, 86, FALSE, 1001);
}

void VsRecorderViewerIdEntry_FreeGraphics(VsRecorderViewerIdEntryState *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        Sprite_DeleteAndFreeResources(param0->itemButtons[v0].sprite);
    }

    for (v0 = 0; v0 < 2; v0++) {
        Sprite_DeleteAndFreeResources(param0->separatorButtons[v0].sprite);
    }

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_DeleteAndFreeResources(param0->cursorButtons[v0].sprite);
    }

    SpriteManager_UnloadCharObjById(param0->graphics.spriteManager, 1000);
    SpriteManager_UnloadPlttObjById(param0->graphics.spriteManager, 1000);
    SpriteManager_UnloadCellObjById(param0->graphics.spriteManager, 1000);
    SpriteManager_UnloadAnimObjById(param0->graphics.spriteManager, 1000);
    SpriteManager_UnloadCharObjById(param0->graphics.spriteManager, 1001);
    SpriteManager_UnloadPlttObjById(param0->graphics.spriteManager, 1001);
    SpriteManager_UnloadCellObjById(param0->graphics.spriteManager, 1001);
    SpriteManager_UnloadAnimObjById(param0->graphics.spriteManager, 1001);
}

void VsRecorderViewerIdEntry_CreateItemSprites(VsRecorderViewerIdEntryState *param0)
{
    int v0;
    int v1 = 0;
    int v2 = 0;
    SpriteTemplate v3;
    SpriteSystem *v4 = param0->graphics.spriteSystem;
    SpriteManager *v5 = param0->graphics.spriteManager;
    PaletteData *v6 = param0->graphics.palette;

    v3.x = 0;
    v3.y = 0;
    v3.z = 0;
    v3.animIdx = 0;
    v3.priority = 10;
    v3.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v3.bgPriority = 0;
    v3.vramTransfer = FALSE;
    v3.plttIdx = 0;
    v3.resources[0] = 1000;
    v3.resources[1] = 1000;
    v3.resources[2] = 1000;
    v3.resources[3] = 1000;
    v3.resources[4] = SPRITE_RESOURCE_NONE;
    v3.resources[5] = SPRITE_RESOURCE_NONE;

    for (v0 = 0; v0 < param0->itemCount + 3 - 1; v0++) {
        if (v0 == (param0->separatorButtons[v2].value + v2 + 1)) {
            param0->separatorButtons[v2].sprite = SpriteSystem_NewSprite(v4, v5, &v3);
            ManagedSprite_SetPositionXY(param0->separatorButtons[v2].sprite, 72 + (v0 * 8) + 4, 24);
            ManagedSprite_SetAnim(param0->separatorButtons[v2].sprite, 22);
            ManagedSprite_TickFrame(param0->separatorButtons[v2].sprite);
            v2++;
        } else {
            param0->itemButtons[v1].sprite = SpriteSystem_NewSprite(v4, v5, &v3);
            ManagedSprite_SetPositionXY(param0->itemButtons[v1].sprite, 72 + (v0 * 8) + 4, 24);
            ManagedSprite_SetAnim(param0->itemButtons[v1].sprite, VsRecorderViewerIdEntry_GetAnimForValue(param0->itemButtons[v1].value, param0->itemButtons[v1].selected));
            ManagedSprite_SetAffineOverwriteMode(param0->itemButtons[v1].sprite, AFFINE_OVERWRITE_MODE_NONE);
            ManagedSprite_TickFrame(param0->itemButtons[v1].sprite);
            v1++;
        }
    }
}

void VsRecorderViewerIdEntry_CreateCursorSprites(VsRecorderViewerIdEntryState *param0)
{
    SpriteTemplate v0;
    SpriteSystem *v1 = param0->graphics.spriteSystem;
    SpriteManager *v2 = param0->graphics.spriteManager;
    PaletteData *v3 = param0->graphics.palette;

    v0.x = 0;
    v0.y = 0;
    v0.z = 0;
    v0.animIdx = 0;
    v0.priority = 0;
    v0.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v0.bgPriority = 0;
    v0.vramTransfer = FALSE;
    v0.plttIdx = 0;
    v0.resources[0] = 1001;
    v0.resources[1] = 1001;
    v0.resources[2] = 1001;
    v0.resources[3] = 1001;
    v0.resources[4] = SPRITE_RESOURCE_NONE;
    v0.resources[5] = SPRITE_RESOURCE_NONE;

    param0->cursorButtons[0].sprite = SpriteSystem_NewSprite(v1, v2, &v0);
    param0->cursorButtons[1].sprite = SpriteSystem_NewSprite(v1, v2, &v0);
    param0->cursorButtons[2].sprite = SpriteSystem_NewSprite(v1, v2, &v0);

    VsRecorderViewerIdEntry_SetSelectorPosition(param0, 0);
    ManagedSprite_SetAnim(param0->cursorButtons[0].sprite, 0);
    ManagedSprite_TickFrame(param0->cursorButtons[0].sprite);

    param0->cursorButtons[1].rect.offsetX = 0;
    param0->cursorButtons[1].rect.offsetY = 0;
    param0->cursorButtons[1].value = 1;

    VsRecorderViewerIdEntry_SetTouchCursorPosition(param0, 0);
    ManagedSprite_SetAnim(param0->cursorButtons[1].sprite, param0->cursorButtons[1].value);
    ManagedSprite_TickFrame(param0->cursorButtons[1].sprite);
    ManagedSprite_SetExplicitOamMode(param0->cursorButtons[1].sprite, GX_OAM_MODE_XLU);

    param0->cursorButtons[2].rect.offsetX = 0;
    param0->cursorButtons[2].rect.offsetY = 0;
    param0->cursorButtons[2].value = 1;

    VsRecorderViewerIdEntry_SetTouchCursorPosition(param0, 0);
    ManagedSprite_SetAnim(param0->cursorButtons[2].sprite, param0->cursorButtons[2].value);
    ManagedSprite_TickFrame(param0->cursorButtons[2].sprite);
    ManagedSprite_SetExplicitOamMode(param0->cursorButtons[2].sprite, GX_OAM_MODE_XLU);
    VsRecorderViewerIdEntry_SetCursorVisible(param0, 1, 0);
    VsRecorderViewerIdEntry_SetCursorVisible(param0, 2, 0);
}

void VsRecorderViewerIdEntry_SetCursorVisible(VsRecorderViewerIdEntryState *param0, int param1, BOOL param2)
{
    if (param2 == 1) {
        ManagedSprite_SetDrawFlag(param0->cursorButtons[param1].sprite, 1);
    } else {
        ManagedSprite_SetDrawFlag(param0->cursorButtons[param1].sprite, 0);
    }
}

void VsRecorderViewerIdEntry_SetSelectorPosition(VsRecorderViewerIdEntryState *param0, int param1)
{
    s16 v0, v1;
    ManagedSprite *v2 = param0->itemButtons[param1].sprite;
    param0->cursorButtons[0].value = param1;

    ManagedSprite_GetPositionXY(v2, &v0, &v1);
    ManagedSprite_SetPositionXY(param0->cursorButtons[0].sprite, v0, v1 + 16);
}

void VsRecorderViewerIdEntry_SetTouchCursorPosition(VsRecorderViewerIdEntryState *param0, int param1)
{
    s16 v0 = (param0->graphics.touchRects[param1 + 12].rect.left + param0->graphics.touchRects[param1 + 12].rect.right) / 2;
    s16 v1 = (param0->graphics.touchRects[param1 + 12].rect.top + param0->graphics.touchRects[param1 + 12].rect.bottom) / 2;

    ManagedSprite_SetPositionXY(param0->cursorButtons[1].sprite, v0 - 0, v1 - 8);
}

void VsRecorderViewerIdEntry_SetCursorPositionForItem(VsRecorderViewerIdEntryState *param0, int param1, int param2)
{
    s16 v0 = (param0->graphics.touchRects[param1 + 12].rect.left + param0->graphics.touchRects[param1 + 12].rect.right) / 2;
    s16 v1 = (param0->graphics.touchRects[param1 + 12].rect.top + param0->graphics.touchRects[param1 + 12].rect.bottom) / 2;

    ManagedSprite_SetPositionXY(param0->cursorButtons[param2].sprite, v0 - 0, v1 - 8);
}

void VsRecorderViewerIdEntry_UpdateCursors(VsRecorderViewerIdEntryState *param0)
{
    ManagedSprite_TickFrame(param0->cursorButtons[0].sprite);
    ManagedSprite_TickFrame(param0->cursorButtons[1].sprite);
    ManagedSprite_TickFrame(param0->cursorButtons[2].sprite);

    {
        int v0 = 2;
        int v1;
        BOOL v2;

        for (v0 = 1; v0 < 3; v0++) {
            v1 = ManagedSprite_GetActiveAnim(param0->cursorButtons[v0].sprite);

            if (v1 == 3) {
                v2 = ManagedSprite_IsAnimated(param0->cursorButtons[v0].sprite);

                if (v2 == 0) {
                    ManagedSprite_SetAnim(param0->cursorButtons[v0].sprite, param0->cursorButtons[v0].value);

                    if (param0->graphics.cursorHidden == 1) {
                        VsRecorderViewerIdEntry_SetCursorVisible(param0, 1, 0);
                    } else {
                        VsRecorderViewerIdEntry_SetCursorVisible(param0, 1, 1);
                    }

                    VsRecorderViewerIdEntry_SetCursorVisible(param0, 2, 0);
                }
            } else {
                if (v1 != param0->cursorButtons[v0].value) {
                    ManagedSprite_SetAnim(param0->cursorButtons[v0].sprite, param0->cursorButtons[v0].value);
                }

                {
                    v1 = ManagedSprite_GetActiveAnim(param0->cursorButtons[2].sprite);

                    if (v1 != 3) {
                        if (param0->graphics.cursorHidden == 1) {
                            VsRecorderViewerIdEntry_SetCursorVisible(param0, 1, 0);
                        } else {
                            VsRecorderViewerIdEntry_SetCursorVisible(param0, 1, 1);
                        }
                    }
                }
            }
        }
    }
}

int VsRecorderViewerIdEntry_GetAnimForValue(int param0, BOOL param1)
{
    int v0 = 0;

    if (param1 == 0) {
        v0 = 11;
    }

    v0 += param0;
    return v0;
}

void VsRecorderViewerIdEntry_UpdateItemSelection(VsRecorderViewerIdEntryState *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if ((v0 >= param0->firstItemIndex) && (v0 < param0->lastItemIndex)) {
            param0->itemButtons[v0].selected = 1;
        } else {
            param0->itemButtons[v0].selected = 0;
        }
    }
}

void VsRecorderViewerIdEntry_LayoutItems(VsRecorderViewerIdEntryState *param0, int param1)
{
    int v0;
    int v1;
    s16 v2;
    s16 v3, v4;

    v2 = param0->categoryXPositions[param0->category];
    v1 = 0;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if ((v0 >= param0->firstItemIndex) && (v0 < param0->lastItemIndex)) {
            if (v0 == param0->firstItemIndex) {
                v2 += ((32 + 8) / 2);
            } else {
                v2 += 32;
            }
        } else {
            if (v0 == 0) {
                v2 += ((32 + 8) / 2);
            } else {
                v2 += 8;
            }
        }

        ManagedSprite_GetPositionXY(param0->itemButtons[v0].sprite, &v3, &v4);

        if (param1 == 0) {
            ManagedSprite_SetPositionXY(param0->itemButtons[v0].sprite, v2, v4);
        } else {
            param0->itemButtons[v0].rect.offsetX = (v2 - v3) / 2;
            param0->itemButtons[v0].rect.offsetY = 0;
            param0->itemButtons[v0].rect.timer = 2;
            param0->itemButtons[v0].rect.scaleIndex = 0;
        }

        if ((v0 == param0->separatorButtons[v1].value) && (v1 != 3 - 1)) {
            ManagedSprite_GetPositionXY(param0->separatorButtons[v1].sprite, &v3, &v4);

            if (param0->firstItemIndex == param0->lastItemIndex) {
                v2 += 8;
            } else {
                if ((v0 > param0->firstItemIndex) && (v0 < param0->lastItemIndex)) {
                    v2 += ((32 + 8) / 2);
                } else {
                    v2 += 8;
                }
            }

            if (param1 == 0) {
                ManagedSprite_SetPositionXY(param0->separatorButtons[v1].sprite, v2, v4);
            } else {
                param0->separatorButtons[v1].rect.offsetX = (v2 - v3) / 2;
                param0->separatorButtons[v1].rect.offsetY = 0;
                param0->separatorButtons[v1].rect.timer = 2;
            }

            v1++;
        }
    }
}

static inline void VsRecorderViewerIdEntry_SetItemTouchRect(VsRecorderViewerIdEntryState *param0, int param1, s16 param2, s16 param3)
{
    s16 v0, v1;
    VsRecorderViewerIdEntryButton *v2 = &param0->itemButtons[param1];

    ManagedSprite_GetPositionXY(v2->sprite, &v0, &v1);

    v2->touchRect->rect.top = v1 - param3;
    v2->touchRect->rect.left = v0 - param2;
    v2->touchRect->rect.bottom = v1 + param3;
    v2->touchRect->rect.right = v0 + param2;

    if (param1 == 0) {
        v2->touchRect->rect.left -= 4;
    }
}

void VsRecorderViewerIdEntry_UpdateTouchRects(VsRecorderViewerIdEntryState *param0)
{
    int v0;
    s16 v1;
    s16 v2;

    for (v0 = 0; v0 < param0->itemCount; v0++) {
        if ((v0 >= param0->firstItemIndex) && (v0 < param0->lastItemIndex)) {
            v1 = 32 / 2;
            v2 = 32 / 2;
        } else {
            v1 = 8 / 2;
            v2 = 8;
        }

        VsRecorderViewerIdEntry_SetItemTouchRect(param0, v0, v1, v2);
    }
}
