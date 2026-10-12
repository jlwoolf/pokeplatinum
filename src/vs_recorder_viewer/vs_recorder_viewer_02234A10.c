#include "vs_recorder_viewer/vs_recorder_viewer_02234A10.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_vs_recorder_state.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02235008.h"

#include "bg_window.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "math_util.h"
#include "message.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "text.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "vs_recorder_ring.h"

static void VsRecorderViewerEntry_CreateMessageWindow(VsRecorderState *param0);
static void VsRecorderViewerEntry_DestroyMessageWindow(VsRecorderState *param0);
static BOOL VsRecorderViewerEntry_RevealRing(VsRecorderState *param0);
static BOOL VsRecorderViewerEntry_EnterMenu(VsRecorderState *param0);
static BOOL VsRecorderViewerEntry_ShowRingAtCenter(VsRecorderState *param0);
static BOOL VsRecorderViewerEntry_FanOutEntries(VsRecorderState *param0);
BOOL VsRecorderViewerEntry_AnimateEntries(VsRecorderState *param0);

static void VsRecorderViewerEntry_CreateMessageWindow(VsRecorderState *param0)
{
    String *v0;
    int v1;
    Window *v2 = &param0->window;

    Window_Init(v2);
    Window_Add(param0->menuContext.bgConfig, v2, 2, 8, 16, 16, 2, 14, 300);
    Window_FillTilemap(v2, 0x0);

    v0 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 192);
    v1 = VsRecorderViewerList_CalcCenteredTextX(v2, v0);

    Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v0, v1, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 14, 0), NULL);
    String_Free(v0);
    Window_ScheduleCopyToVRAM(v2);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
}

static void VsRecorderViewerEntry_DestroyMessageWindow(VsRecorderState *param0)
{
    Window_ClearAndCopyToVRAM(&param0->window);
    Window_Remove(&param0->window);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

static BOOL VsRecorderViewerEntry_RevealRing(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
            VsRecorderViewerMain_SetState(param0, 1);
            break;
        }

        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_102);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFE, 16, VsRecorderViewerList_GetThemeColorB(param0));
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xBFFF, 16, VsRecorderViewerList_GetThemeColorB(param0));
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0x3FFE, 16, VsRecorderViewerList_GetThemeColorB(param0));
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, 16, VsRecorderViewerList_GetThemeColorB(param0));
        VsRecorderRing_StartAnim(param0->backgroundRing);
        VsRecorderRing_StartAnim(param0->ring);
        param0->subState++;
        break;
    case 1:
        if (IsScreenFadeDone() == FALSE) {
            break;
        }

        VsRecorderRing_SetPosition(param0->backgroundRing, 256 / 2, 16);
        VsRecorderRing_SetTargetPosition(param0->backgroundRing, 256 / 2, 192 + 24);
        VsRecorderRing_SetVisible(param0->backgroundRing, 1);
        VsRecorderRing_SetActive(param0->backgroundRing, 1);
        Sound_PlayEffect(SEQ_SE_PL_BREC11_2_sseq);
        param0->subState++;
        break;
    case 2:
        if ((++param0->timer) < 25) {
            break;
        }

        param0->timer = 0;
        VsRecorderRing_SetPosition(param0->ring, 256 / 2, -16);
        VsRecorderRing_SetTargetPosition(param0->ring, 256 / 2, 192 / 2);
        VsRecorderRing_SetVisible(param0->ring, 1);
        VsRecorderRing_SetActive(param0->ring, 1);
        param0->subState++;
        break;
    case 3:
        if ((++param0->timer) < 18) {
            break;
        }

        VsRecorderViewerEntry_CreateMessageWindow(param0);
        VsRecorderRing_SetVisible(param0->backgroundRing, 0);

        param0->timer = 0;
        param0->subState++;
        break;
    case 4:
        if (param0->timer < 16) {
            param0->timer += 4;
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xF000, param0->timer, 0xFFFF);
        } else {
            param0->subState++;
        }
        break;
    case 5:
        if (param0->timer > 0) {
            param0->timer -= 4;
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xF000, param0->timer, 0xFFFF);
        } else {
            param0->subState++;
        }
        break;
    case 6:
        if (TouchScreen_Touched() == 1) {
            VsRecorderViewerEntry_DestroyMessageWindow(param0);
            VsRecorderRing_SetVisible(param0->ring, 0);
            VsRecorderRing_StopAnim(param0->backgroundRing);
            VsRecorderRing_StopAnim(param0->ring);
            param0->subState++;
        }
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 1);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerEntry_EnterMenu(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_LoadEntrySpriteResources(param0);
        VsRecorderViewerMenu_CreateDecorativeSprites(param0);
        VsRecorderViewerMenu_LoadEntryIconResources(param0);
        VsRecorderViewerMenu_CreateMenuEntries(param0);
        VsRecorderViewerMenu_CreateEntryLabels(param0);
        VsRecorderViewerMenu_UpdateSubEntryLabels(param0);
        VsRecorderViewerMenu_UpdateMainEntryLabels(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
            if (param0->mode == 0) {
                Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 69, param0->menuContext.bgConfig, 5, 0, 0, 0, HEAP_ID_102);
            } else {
                Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 55, param0->menuContext.bgConfig, 5, 0, 0, 0, HEAP_ID_102);
            }

            VsRecorderRing_SetPosition(param0->ring, 256 / 2, 192 + 32);
            VsRecorderRing_SetTargetPosition(param0->ring, 256 / 2, 192 + 32);
            VsRecorderRing_SetVisible(param0->ring, 0);
            VsRecorderRing_SetActive(param0->ring, 1);
            VsRecorderViewerMain_AdvanceState(param0, param0->pendingSelection.selection, 1, param0->animState);
            break;
        }

        Sound_PlayEffect(SEQ_SE_PL_BREC03_sseq);

        param0->timer = 16;
        param0->subState++;
        break;
    case 1:
        if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
            if (IsScreenFadeDone() == TRUE) {
                param0->subState++;
            }
        } else {
            if (param0->timer != 0) {
                param0->timer -= 2;
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xFFFE, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_BG, 0xFFFF, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0x3FFE, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0xFFFF, param0->timer, VsRecorderViewerList_GetThemeColorB(param0));
            } else {
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, 16, param0->menuContext.themeColor);
                PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->menuContext.themeColor);
                param0->subState++;
            }
        }
        break;
    case 2:
        if (param0->mode == 0) {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 69, param0->menuContext.bgConfig, 5, 0, 0, 0, HEAP_ID_102);
        } else {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 55, param0->menuContext.bgConfig, 5, 0, 0, 0, HEAP_ID_102);
        }

        param0->subState++;
        break;
    default:
        if (param0->menuSprites[0].state < 3) {
            break;
        }

        VsRecorderViewerMain_SetState(param0, 2);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerEntry_ShowRingAtCenter(VsRecorderState *param0)
{
    switch (param0->subState) {
    case 0:
        VsRecorderRing_SetPosition(param0->ring, 256 / 2, 192 / 2);
        VsRecorderRing_SetTargetPosition(param0->ring, 256 / 2, 192 / 2);
        VsRecorderRing_SetVisible(param0->ring, 1);
        VsRecorderRing_SetActive(param0->ring, 1);
        param0->timer++;
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, 16 - param0->timer, param0->menuContext.themeColor);

        if (param0->timer == 2) {
            param0->timer = 15;
            param0->subState++;
        }
        break;
    case 1:
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, param0->timer, param0->menuContext.themeColor);
        param0->subState++;
        break;
    case 2:
        param0->timer--;
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, param0->timer, param0->menuContext.themeColor);

        if (param0->timer == 0) {
            param0->subState++;
        }
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerEntry_FanOutEntries(VsRecorderState *param0)
{
    BOOL v0 = VsRecorderViewerEntry_AnimateEntries(param0);

    {
        s16 v1, v2;

        VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.subEntries[0].sprite, &v1, &v2);
        VsRecorderRing_SetTargetPosition(param0->ring, v1 + (15 + 1), v2);
    }

    return v0;
}

BOOL VsRecorderViewerEntry_AnimateEntries(VsRecorderState *param0)
{
    VsRecorderViewerEntryAnim *v0;

    switch (param0->subState) {
    case 0:

        v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerEntryAnim));
        MI_CpuFill8(v0, 0, sizeof(VsRecorderViewerEntryAnim));
        param0->viewerData = v0;
        v0->fadeValue = 16;

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->fadeValue, param0->menuContext.themeColor);

        {
            int v1;
            fx32 v2;

            for (v1 = 0; v1 < param0->menu.subEntryCount; v1++) {
                v0->entries[v1].delay = (4 / 1) * v1;
                v0->entries[v1].angle = 90;
                v0->entries[v1].targetY = (25 + (36 * (v1)) + (16 * (5 - (param0->menu.subEntryCount))));

                VsRecorderViewerMenu_SetSpritePositionWithOffset(param0->menu.subEntries[v1].sprite, 42, (25 + (36 * (5 - 1)) + (16 * (5 - (param0->menu.subEntryCount)))));
                ManagedSprite_GetPositionFxXY(param0->menu.subEntries[v1].sprite, &v0->entries[v1].baseX, &v2);
                ManagedSprite_SetPositionFxXY(param0->menu.subEntries[v1].sprite, v0->entries[v1].baseX, (25 + (36 * (5 - 1)) + (16 * (5 - (param0->menu.subEntryCount)))) * FX32_ONE);
                FontOAM_SetXY(param0->menu.subEntries[v1].fontOAM, 36, -8);
                FontOAM_SetDrawFlag(param0->menu.subEntries[v1].fontOAM, 1);
            }

            param0->subState++;
        }
        break;
    case 1:
        v0 = param0->viewerData;

        if (v0->fadeValue != 0) {
            v0->fadeValue -= (1 * 1);
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->fadeValue, param0->menuContext.themeColor);
        }

        {
            int v3;
            int v4 = 0;
            s16 v5, v6;
            fx32 v7, v8;

            for (v3 = 0; v3 < param0->menu.subEntryCount; v3++) {
                if (v0->entries[v3].delay != 0) {
                    v0->entries[v3].delay--;
                    continue;
                }

                VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.subEntries[v3].sprite, &v5, &v6);

                if (v6 == v0->entries[v3].targetY) {
                    v4++;
                    continue;
                } else if (v6 - (8 * 1) > v0->entries[v3].targetY) {
                    v6 -= (8 * 1);
                } else {
                    v6 = v0->entries[v3].targetY;
                }

                v8 = v6 * FX32_ONE;
                v7 = v0->entries[v3].baseX + (CalcSineDegrees_Wraparound((v0->entries[v3].angle * 0xffff) / 360) * 16);
                v0->entries[v3].angle += (-4 * 1);

                ManagedSprite_SetPositionFxXY(param0->menu.subEntries[v3].sprite, v7, v8);
                FontOAM_SetXY(param0->menu.subEntries[v3].fontOAM, 36, -8);
            }
            if (v4 == param0->menu.subEntryCount) {
                param0->subState++;
            }
        }
        break;
    default:
        v0 = param0->viewerData;
        {
            s16 v9, v10;

            VsRecorderViewerMenu_GetSpritePositionWithOffset(param0->menu.subEntries[param0->menu.selectedIndex].sprite, &v9, &v10);
            VsRecorderRing_SetPosition(param0->ring, v9 + (15 + 1), v10);
            VsRecorderRing_SetTargetPosition(param0->ring, v9 + (15 + 1), v10);
            VsRecorderRing_SetVisible(param0->ring, 0);
            VsRecorderViewerMain_UpdateTouchRects(param0);
            Heap_Free(v0);
        }
        return 1;
    }

    return 0;
}

// clang-format off
BOOL(*const sVsRecorderViewerEntryHandlers[])(VsRecorderState *) = {
    VsRecorderViewerEntry_RevealRing,
    VsRecorderViewerEntry_EnterMenu,
    VsRecorderViewerEntry_ShowRingAtCenter,
    VsRecorderViewerEntry_FanOutEntries,
};
// clang-format on
