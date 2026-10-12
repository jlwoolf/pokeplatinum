#include "applications/pc_boxes/box_graphics.h"

#include <nitro.h>
#include <string.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_callback.h"
#include "applications/pc_boxes/box_view.h"
#include "applications/pc_boxes/box_cursor_sprite.h"
#include "applications/pc_boxes/box_mon_sprite_manager.h"
#include "applications/pc_boxes/box_button_sprite.h"
#include "applications/pc_boxes/pc_mon_preview_panel.h"
#include "applications/pc_boxes/box_menu_graphics.h"
#include "applications/pc_boxes/box_selection_popup.h"
#include "applications/pc_boxes/box_party.h"
#include "applications/pc_boxes/box_touch_dial_graphics.h"
#include "applications/pc_boxes/box_held_item_icons.h"
#include "applications/pc_boxes/pc_compare_screen.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_view.h"
#include "applications/pc_boxes/struct_box_cursor_sprite.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_button_sprite.h"
#include "applications/pc_boxes/struct_pc_mon_preview_panel.h"
#include "applications/pc_boxes/struct_box_menu_graphics.h"
#include "applications/pc_boxes/struct_box_selection_popup.h"
#include "applications/pc_boxes/struct_box_party.h"
#include "applications/pc_boxes/struct_box_touch_dial_graphics_decl.h"
#include "applications/pc_boxes/struct_box_held_item_icons_decl.h"
#include "applications/pc_boxes/struct_pc_compare_screen_decl.h"

#include "bg_window.h"
#include "enums.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "pokemon_sprite.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"

struct BoxGraphics_t {
    SysTask *unk_00;
    SysTask *unk_04;
    SysTask *unk_08[4];
    SpriteList *unk_18;
    G2dRenderer unk_1C;
    NNSG2dImagePaletteProxy unk_1A8;
    PokemonSpriteManager *unk_1BC;
    BgConfig *unk_1C0;
    const BoxApplication *unk_1C4;
    BoxMonSpriteManager unk_1C8;
    BoxView unk_494;
    BoxCursorSprite unk_5E24;
    BoxButtonSprite unk_65BC;
    PCMonPreviewPanel unk_6604;
    BoxMenuGraphics unk_6658;
    BoxSelectionPopup unk_6690;
    BoxParty unk_B290;
    BoxTouchDialGraphics *unk_B408;
    BoxHeldItemIcons *unk_B40C;
    PCCompareScreen *unk_B410;
    const BoxApplicationManager *unk_B414;
};

typedef struct BoxTaskParams {
    enum BoxGraphicsFunctions function;
    u16 unk_04;
    u16 state;
    u16 unk_08;
    u16 unk_0A;
    BoxGraphics *unk_0C;
    void *unk_10;
} BoxTaskParams;

static void BoxGraphics_RenderTask(SysTask *param0, void *param1);
static void BoxTaskParams_Free(BoxTaskParams *params);
static void BoxGraphics_VBlankTask(SysTask *param0, void *param1);
static void BoxGraphics_SetupScene(SysTask *param0, void *param1);
static void BoxGraphics_ScreenFadeBothToBlackLogIn(SysTask *task, void *param1);
static void BoxGraphics_ScreenFadeBothToBlack1(SysTask *task, void *param1);
static void BoxGraphics_ScreenFadeBothToBlack2(SysTask *task, void *param1);
static void BoxGraphics_ChangeToNewBox(SysTask *param0, void *param1);
static void BoxGraphics_MoveCursor(SysTask *param0, void *param1);
static void BoxGraphics_PreviewMon(SysTask *param0, void *param1);
static void BoxGraphics_UpdatePreviewedMonMarkings(SysTask *param0, void *param1);
static void BoxGraphics_ClearMonPreview(SysTask *param0, void *param1);
static void BoxGraphics_PickUpMonIntoCursor(SysTask *param0, void *param1);
static void BoxGraphics_PlaceMonDownFromCursor(SysTask *param0, void *param1);
static void BoxGraphics_SwapMonsInBox(SysTask *param0, void *param1);
static void BoxGraphics_ReloadBoxMons(SysTask *param0, void *param1);
static void BoxGraphics_ReloadPartyMons(SysTask *param0, void *param1);
static void BoxGraphics_PlayReleaseCursorMonAnimation(SysTask *task, void *param1);
static void BoxGraphics_PlayReleaseBoxMonAnimation(SysTask *task, void *param1);
static void BoxGraphics_PlayReleasePartyMonAnimation(SysTask *task, void *param1);
static void BoxGraphics_DisplayItemInfo(SysTask *param0, void *param1);
static void BoxGraphics_CloseItemInfo(SysTask *param0, void *param1);
static void BoxGraphics_PickUpItemIntoCursor(SysTask *param0, void *param1);
static void BoxGraphics_PlaceItemDownFromCursor(SysTask *param0, void *param1);
static void BoxGraphics_SwapItems(SysTask *param0, void *param1);
static void BoxGraphics_UpdateHeldItemDisplay(SysTask *param0, void *param1);
static void BoxGraphics_ItemShrinkToNothing(SysTask *param0, void *param1);
static void BoxGraphics_DisplayBoxMessage(SysTask *task, void *param1);
static void BoxGraphics_ShowMenu(SysTask *param0, void *param1);
static void BoxGraphics_CloseMessageBox(SysTask *task, void *param1);
static void BoxGraphics_HideMenu(SysTask *param0, void *param1);
static void BoxGraphics_UpdateMenuCursor(SysTask *param0, void *param1);
static void BoxGraphics_UpdateMarkings(SysTask *param0, void *param1);
static void BoxGraphics_ShowBoxSelectionPopup(SysTask *param0, void *param1);
static void BoxGraphics_ScrollBoxSelectionPopup(SysTask *param0, void *param1);
static void BoxGraphics_HideBoxSelectionPopup(SysTask *param0, void *param1);
static void BoxGraphics_TransitionWallpaper(SysTask *param0, void *param1);
static void BoxGraphics_PressBoxButton(SysTask *param0, void *param1);
static void BoxGraphics_OpenPartyPopup(SysTask *param0, void *param1);
static void BoxGraphics_ClosePartyPopup(SysTask *param0, void *param1);
static void BoxGraphics_PlayAdjustPartyAnimation(SysTask *task, void *param1);
static void BoxGraphics_MovePartyCursor(SysTask *param0, void *param1);
static void BoxGraphics_SetMonMarkingsTransparency(SysTask *param0, void *param1);
static void BoxGraphics_OpenOrCloseSelectedTouchDial(SysTask *param0, void *param1);
static void BoxGraphics_ScrollTouchDial(SysTask *param0, void *param1);
static void BoxGraphics_UpdateMarkingsTouchButton(SysTask *param0, void *param1);
static void BoxGraphics_UpdateCursorFastMode(SysTask *param0, void *param1);
static void BoxGraphics_StartDrawMultiSelect(SysTask *param0, void *param1);
static void BoxGraphics_ClearMultiSelectShading(SysTask *param0, void *param1);
static void BoxGraphics_ApplyMultiSelectMonShadingTask(SysTask *param0, void *param1);
static void BoxGraphics_BounceCursor(SysTask *param0, void *param1);
static void BoxGraphics_SetCompareButtonUnpressed(SysTask *param0, void *param1);
static void BoxGraphics_SetCompareButtonPressed(SysTask *param0, void *param1);
static void BoxGraphics_SwitchCompareMode(SysTask *param0, void *param1);
static void BoxGraphics_ScreenFadeBothToBlackLogOff(SysTask *task, void *param1);
static void BoxGraphics_InitBgLayers(BoxGraphics *param0, const BoxApplication *param1);
static void BoxGraphics_LoadBgTiles(BoxGraphics *param0, const BoxApplication *param1, NARC *param2);
static void BoxGraphics_Init3D(void);
static void BoxGraphics_LoadSprites(BoxGraphics *param0, const BoxApplication *param1, NARC *param2);
static int BoxGraphics_GetBoxMoveDirection(u32 param0, u32 param1);
static void BoxGraphics_ResetDeferredFrees(void);
static void BoxGraphics_ProcessDeferredFrees(void);

static const struct {
    SysTaskFunc sysTaskFunc;
    u32 unk_04;
} sBoxGraphicsTaskHandlers[] = {
    [FUNC_BoxGraphics_SetupScene] = { BoxGraphics_SetupScene, 0 },
    [FUNC_BoxGraphics_ScreenFadeBothToBlack0] = { BoxGraphics_ScreenFadeBothToBlackLogIn, 0 },
    [FUNC_BoxGraphics_ScreenFadeBothToBlack1] = { BoxGraphics_ScreenFadeBothToBlack1, 0 },
    [FUNC_BoxGraphics_ScreenFadeBothToBlack2] = { BoxGraphics_ScreenFadeBothToBlack2, 0 },
    [FUNC_BoxGraphics_ChangeToNewBox] = { BoxGraphics_ChangeToNewBox, 0 },
    [FUNC_BoxGraphics_MoveCursor] = { BoxGraphics_MoveCursor, 0 },
    [FUNC_BoxGraphics_PreviewMon] = { BoxGraphics_PreviewMon, 0 },
    [FUNC_BoxGraphics_UpdatePreviewedMonMarkings] = { BoxGraphics_UpdatePreviewedMonMarkings, 0 },
    [FUNC_BoxGraphics_ClearMonPreview] = { BoxGraphics_ClearMonPreview, 0 },
    [FUNC_BoxGraphics_PickUpMonIntoCursor] = { BoxGraphics_PickUpMonIntoCursor, 0 },
    [FUNC_BoxGraphics_PlaceMonDownFromCursor] = { BoxGraphics_PlaceMonDownFromCursor, 0 },
    [FUNC_BoxGraphics_SwapMonsInBox] = { BoxGraphics_SwapMonsInBox, 0 },
    [FUNC_BoxGraphics_ReloadBoxMons] = { BoxGraphics_ReloadBoxMons, 0 },
    [FUNC_BoxGraphics_ReloadPartyMons] = { BoxGraphics_ReloadPartyMons, 0 },
    [FUNC_BoxGraphics_PlayReleaseCursorMonAnimation] = { BoxGraphics_PlayReleaseCursorMonAnimation, 0 },
    [FUNC_BoxGraphics_PlayReleaseBoxMonAnimation] = { BoxGraphics_PlayReleaseBoxMonAnimation, 0 },
    [FUNC_BoxGraphics_PlayReleasePartyMonAnimation] = { BoxGraphics_PlayReleasePartyMonAnimation, 0 },
    [FUNC_BoxGraphics_DisplayItemInfo] = { BoxGraphics_DisplayItemInfo, 0 },
    [FUNC_BoxGraphics_CloseItemInfo] = { BoxGraphics_CloseItemInfo, 0 },
    [FUNC_BoxGraphics_PickUpItemIntoCursor] = { BoxGraphics_PickUpItemIntoCursor, 0 },
    [FUNC_BoxGraphics_PlaceItemDownFromCursor] = { BoxGraphics_PlaceItemDownFromCursor, 0 },
    [FUNC_BoxGraphics_SwapItems] = { BoxGraphics_SwapItems, 0 },
    [FUNC_BoxGraphics_UpdateHeldItemDisplay] = { BoxGraphics_UpdateHeldItemDisplay, 0 },
    [FUNC_BoxGraphics_ItemShrinkToNothing] = { BoxGraphics_ItemShrinkToNothing, 0 },
    [FUNC_BoxGraphics_DisplayBoxMessage] = { BoxGraphics_DisplayBoxMessage, 0 },
    [FUNC_BoxGraphics_ShowMenu] = { BoxGraphics_ShowMenu, 0 },
    [FUNC_BoxGraphics_CloseMessageBox] = { BoxGraphics_CloseMessageBox, 0 },
    [FUNC_BoxGraphics_HideMenu] = { BoxGraphics_HideMenu, 0 },
    [FUNC_BoxGraphics_UpdateMenuCursor] = { BoxGraphics_UpdateMenuCursor, 0 },
    [FUNC_BoxGraphics_UpdateMarkings] = { BoxGraphics_UpdateMarkings, 0 },
    [FUNC_BoxGraphics_ShowBoxSelectionPopup] = { BoxGraphics_ShowBoxSelectionPopup, 0 },
    [FUNC_BoxGraphics_ScrollBoxSelectionPopup] = { BoxGraphics_ScrollBoxSelectionPopup, 0 },
    [FUNC_BoxGraphics_HideBoxSelectionPopup] = { BoxGraphics_HideBoxSelectionPopup, 0 },
    [FUNC_BoxGraphics_TransitionWallpaper] = { BoxGraphics_TransitionWallpaper, 0 },
    [FUNC_BoxGraphics_PressBoxButton] = { BoxGraphics_PressBoxButton, 0 },
    [FUNC_BoxGraphics_OpenPartyPopup] = { BoxGraphics_OpenPartyPopup, 0 },
    [FUNC_BoxGraphics_ClosePartyPopup] = { BoxGraphics_ClosePartyPopup, 0 },
    [FUNC_BoxGraphics_PlayAdjustPartyAnimation] = { BoxGraphics_PlayAdjustPartyAnimation, 0 },
    [FUNC_BoxGraphics_MovePartyCursor] = { BoxGraphics_MovePartyCursor, 0 },
    [FUNC_BoxGraphics_SetMonMarkingsTransparency] = { BoxGraphics_SetMonMarkingsTransparency, 0 },
    [FUNC_BoxGraphics_OpenOrCloseSelectedTouchDial] = { BoxGraphics_OpenOrCloseSelectedTouchDial, 0 },
    [FUNC_BoxGraphics_ScrollTouchDial] = { BoxGraphics_ScrollTouchDial, 0 },
    [FUNC_BoxGraphics_UpdateMarkingsTouchButton] = { BoxGraphics_UpdateMarkingsTouchButton, 0 },
    [FUNC_BoxGraphics_UpdateCursorFastMode] = { BoxGraphics_UpdateCursorFastMode, 0 },
    [FUNC_BoxGraphics_StartDrawMultiSelect] = { BoxGraphics_StartDrawMultiSelect, 0 },
    [FUNC_BoxGraphics_ClearMultiSelectShading] = { BoxGraphics_ClearMultiSelectShading, 0 },
    [FUNC_BoxGraphics_ApplyMultiSelectMonShadingTask] = { BoxGraphics_ApplyMultiSelectMonShadingTask, 0 },
    [FUNC_BoxGraphics_BounceCursor] = { BoxGraphics_BounceCursor, 0 },
    [FUNC_BoxGraphics_SetCompareButtonUnpressed] = { BoxGraphics_SetCompareButtonUnpressed, 0 },
    [FUNC_BoxGraphics_SetCompareButtonPressed] = { BoxGraphics_SetCompareButtonPressed, 0 },
    [FUNC_BoxGraphics_SwitchCompareMode] = { BoxGraphics_SwitchCompareMode, 0 },
    [FUNC_BoxGraphics_ScreenFadeBothToBlackLogOff] = { BoxGraphics_ScreenFadeBothToBlackLogOff, 0 },
};

BOOL BoxGraphics_Load(BoxGraphics **param0, const BoxApplication *param1, const BoxApplicationManager *param2)
{
    BoxGraphics *v0 = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxGraphics));

    if (v0 != NULL) {
        v0->unk_1C4 = param1;
        v0->unk_1C0 = BgConfig_New(HEAP_ID_BOX_GRAPHICS);

        if (v0->unk_1C0 != NULL) {
            u32 v1;
            BOOL v2 = TRUE;
            NARC *boxGraphicsNarc;

            boxGraphicsNarc = NARC_ctor(NARC_INDEX_GRAPHIC__BOX, HEAP_ID_BOX_GRAPHICS);

            SetVBlankCallback(NULL, NULL);
            DisableHBlank();
            GXLayers_DisableEngineALayers();
            GXLayers_DisableEngineBLayers();

            GX_SetVisiblePlane(0);
            GXS_SetVisiblePlane(0);
            GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_64K);
            GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
            NNS_G2dInitOamManagerModule();

            RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, 10);
            v0->unk_18 = SpriteList_InitRendering(128, &v0->unk_1C, HEAP_ID_BOX_GRAPHICS);
            SetSubScreenViewRect(&(v0->unk_1C), 0, 384 << FX32_SHIFT);

            NNS_G2dInitImagePaletteProxy(&(v0->unk_1A8));

            Graphics_LoadPartialPaletteFromOpenNARC(boxGraphicsNarc, 26, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 10, &(v0->unk_1A8));
            Font_UseImmediateGlyphAccess(FONT_SYSTEM, 10);

            v0->unk_1BC = PokemonSpriteManager_New(HEAP_ID_BOX_GRAPHICS);

            for (v1 = 0; v1 < 4; v1++) {
                v0->unk_08[v1] = NULL;
            }

            BoxGraphics_ResetDeferredFrees();
            *param0 = v0;

            v2 &= BoxMonSprite_LoadManager(&(v0->unk_1C8), v0, v0->unk_1C4, v0->unk_18, boxGraphicsNarc);
            v2 &= BoxView_Load(&(v0->unk_494), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18);
            v2 &= BoxCursorSprite_Load(&(v0->unk_5E24), v0, v0->unk_1C4, v0->unk_18, boxGraphicsNarc);
            v2 &= BoxButtonSprite_Load(&(v0->unk_65BC), v0, v0->unk_1C4, v0->unk_18, boxGraphicsNarc);
            v2 &= PCMonPreviewPanel_Load(&(v0->unk_6604), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18, BoxAppMan_GetBoxMessagesLoader(param2), boxGraphicsNarc);
            v2 &= BoxMenuGraphics_Load(&(v0->unk_6658), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18, BoxAppMan_GetBoxMessagesLoader(param2), BoxAppMan_GetMessageVariableBuffer(param2), BoxAppMan_GetOptionsFrame(param2), boxGraphicsNarc);
            v2 &= BoxSelectionPopup_Load(&(v0->unk_6690), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18, boxGraphicsNarc);
            v2 &= BoxParty_Load(&(v0->unk_B290), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18, boxGraphicsNarc);
            v2 &= BoxTouchDial_Load(&(v0->unk_B408), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18);
            v2 &= BoxHeldItem_Load(&(v0->unk_B40C), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18);
            v2 &= PCCompare_Load(&(v0->unk_B410), v0, v0->unk_1C4, v0->unk_1C0, v0->unk_18, BoxAppMan_GetBoxMessagesLoader(param2), boxGraphicsNarc);

            v0->unk_B414 = param2;
            v0->unk_00 = SysTask_Start(BoxGraphics_RenderTask, v0, 2);
            v0->unk_04 = BoxGraphics_StartVBlankTask(BoxGraphics_VBlankTask, v0, 1);

            NARC_dtor(boxGraphicsNarc);

            return v2;
        }
    }

    return FALSE;
}

static void BoxGraphics_RenderTask(SysTask *param0, void *param1)
{
    BoxGraphics *v0 = (BoxGraphics *)param1;

    BoxGraphics_ProcessDeferredFrees();

    G3X_Reset();
    G3X_ResetMtxStack();
    NNS_G2dSetupSoftwareSpriteCamera();

    PokemonSpriteManager_DrawSprites(v0->unk_1BC);

    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}

void BoxGraphics_Free(BoxGraphics *param0)
{
    SetVBlankCallback(NULL, NULL);
    SysTask_Done(param0->unk_00);
    SysTask_Done(param0->unk_04);

    PCCompare_Free(param0->unk_B410);
    BoxHeldItem_Free(param0->unk_B40C);
    BoxTouchDial_Free(param0->unk_B408);
    BoxParty_Free(&(param0->unk_B290));
    BoxSelectionPopup_Free(&(param0->unk_6690));
    BoxMenuGraphics_Free(&(param0->unk_6658));
    PCMonPreviewPanel_Free(&(param0->unk_6604));
    BoxButtonSprite_Free(&(param0->unk_65BC));
    BoxCursorSprite_Free(&(param0->unk_5E24));
    BoxView_Free(&(param0->unk_494));
    BoxMonSprite_FreeManager(&(param0->unk_1C8));

    SpriteList_Delete(param0->unk_18);
    Bg_FreeTilemapBuffer(param0->unk_1C0, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->unk_1C0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->unk_1C0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->unk_1C0, BG_LAYER_SUB_0);
    PokemonSpriteManager_Free(param0->unk_1BC);
    Font_UseLazyGlyphAccess(FONT_SYSTEM);
    Heap_Free(param0->unk_1C0);
    Heap_Free(param0);
    RenderOam_Free();
}

void BoxGraphics_TaskHandler(BoxGraphics *param0, enum BoxGraphicsFunctions function)
{
    if (function < NELEMS(sBoxGraphicsTaskHandlers)) {
        BoxTaskParams *taskParams;

        for (u32 i = 0; i < 4; i++) {
            if (param0->unk_08[i] == NULL) {
                taskParams = Heap_Alloc(HEAP_ID_BOX_GRAPHICS, sizeof(BoxTaskParams) + sBoxGraphicsTaskHandlers[function].unk_04);

                if (taskParams != NULL) {
                    taskParams->function = function;
                    taskParams->unk_04 = i;
                    taskParams->state = 0;
                    taskParams->unk_0C = param0;
                    taskParams->unk_10 = ((u8 *)(taskParams) + sBoxGraphicsTaskHandlers[function].unk_04);

                    param0->unk_08[i] = SysTask_Start(sBoxGraphicsTaskHandlers[function].sysTaskFunc, taskParams, 1);
                } else {
                    GF_ASSERT(FALSE);
                }

                break;
            }
        }
    } else {
        GF_ASSERT(FALSE);
    }
}

BOOL BoxGraphics_IsSysTaskDone(BoxGraphics *param0, enum BoxGraphicsFunctions function)
{
    BoxTaskParams *params;

    for (int i = 0; i < 4; i++) {
        if (param0->unk_08[i] != NULL) {
            params = SysTask_GetParam(param0->unk_08[i]);

            if (params->function == function) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL BoxGraphics_CheckAllTasksDone(BoxGraphics *param0)
{
    for (int i = 0; i < 4; i++) {
        if (param0->unk_08[i] != NULL) {
            return FALSE;
        }
    }

    return TRUE;
}

static void BoxTaskParams_Free(BoxTaskParams *params)
{
    BoxGraphics *v0 = params->unk_0C;

    SysTask_Done(v0->unk_08[params->unk_04]);
    v0->unk_08[params->unk_04] = NULL;
    Heap_Free(params);
}

static void BoxGraphics_VBlankTask(SysTask *param0, void *param1)
{
    BoxGraphics *v0 = (BoxGraphics *)param1;

    PCMonPreviewPanel_UpdateSprites(&v0->unk_6604);

    SpriteList_Update(v0->unk_18);
    RenderOam_Transfer();

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void BoxGraphics_SetupScene(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v1 = v0->unk_1C4;

    switch (params->state) {
    case 0: {
        NARC *boxGraphicsNarc = NARC_ctor(NARC_INDEX_GRAPHIC__BOX, HEAP_ID_BOX_GRAPHICS);

        BoxGraphics_InitBgLayers(v0, v1);
        BoxGraphics_LoadBgTiles(v0, v1, boxGraphicsNarc);
        BoxGraphics_LoadSprites(v0, v1, boxGraphicsNarc);
        NARC_dtor(boxGraphicsNarc);
    }

        if (BoxApp_GetBoxMode(v1) != PC_MODE_COMPARE) {
            PCMonPreviewPanel_CreateSprite(&v0->unk_6604);
            params->state++;
        } else {
            BoxTaskParams_Free(params);
        }
        break;
    case 1:
        if (PCMonPreviewPanel_DeleteSprite(&v0->unk_6604)) {
            PCMonPreviewPanel_Draw(&(v0->unk_6604));
            BoxTaskParams_Free(params);
        }
        break;
    }
}

static void BoxGraphics_ScreenFadeBothToBlackLogIn(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_PC_LOGIN_sseq);
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, GX_BLEND_ALL, 0x6, 0xa);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 8, 1, HEAP_ID_BOX_GRAPHICS);
        v2->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_ScreenFadeBothToBlack1(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, GX_BLEND_ALL, 0x6, 0xa);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_BOX_GRAPHICS);
        v2->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_ScreenFadeBothToBlack2(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_BOX_GRAPHICS);
        v2->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_ChangeToNewBox(SysTask *param0, void *taskParams)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *params = (BoxTaskParams *)taskParams;
    v0 = params->unk_0C;
    v1 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        BoxHeldItem_StartReturnToMon(v0->unk_B40C);
        params->state++;
    case 1:
        if (BoxHeldItem_IsReturnToMonDone(v0->unk_B40C) == FALSE) {
            break;
        }

        params->state++;
    case 2: {
        int boxChangeDirection = BoxGraphics_GetBoxMoveDirection(v0->unk_494.boxID, v1->customization.boxID);

        BoxView_LoadWallpaper(&v0->unk_494, &v1->customization, boxChangeDirection, TRUE);
        BoxView_StartBoxChange(&v0->unk_494, &v1->customization, boxChangeDirection);
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        params->state++;
    }
    case 3:
        if (BoxView_IsBoxChangeDone(&v0->unk_494) == 0) {
            break;
        }

        BoxHeldItem_Refresh(v0->unk_B40C);
        params->state++;
    case 4:
        if (BoxHeldItem_IsAnimDone(v0->unk_B40C) == 0) {
            break;
        }

        BoxTaskParams_Free(params);
        break;
    }
}

static void BoxGraphics_MoveCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        BoxCursorSprite_MoveToPosition(&(v0->unk_5E24));
        BoxHeldItem_Refresh(v0->unk_B40C);
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsMoveDone(&(v0->unk_5E24))
            && BoxHeldItem_IsAnimDone(v0->unk_B40C)) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PreviewMon(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    if (BoxApp_GetBoxMode(v1) != PC_MODE_COMPARE) {
        switch (v2->state) {
        case 0:
            PCMonPreviewPanel_DrawWithSprite(&(v0->unk_6604));
            v2->state++;
            break;
        case 1:
            if (PCMonPreviewPanel_IsDrawDone(&(v0->unk_6604))) {
                BoxTaskParams_Free(v2);
            }
            break;
        }
    } else {
        switch (v2->state) {
        case 0:
            PCCompare_DrawMonInfo(v0->unk_B410);
            v2->state++;
            break;
        case 1:
            if (PCCompare_IsDrawDone(v0->unk_B410)) {
                BoxTaskParams_Free(v2);
            }
            break;
        }
    }
}

static void BoxGraphics_UpdatePreviewedMonMarkings(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    if (BoxApp_GetPreviewMonSource(v1) == PREVIEW_MON_IN_CURSOR) {
        BoxCursorSprite_UpdateHeldMonMarkings(&v0->unk_5E24);
    } else {
        switch (BoxApp_GetCursorLocation(v1)) {
        case CURSOR_IN_BOX:
            BoxView_UpdateMonMarkings(&v0->unk_494);
            break;
        case CURSOR_IN_PARTY:
            BoxParty_UpdateMonMarkings(&v0->unk_B290);
            break;
        }
    }

    PCMonPreviewPanel_UpdateMarkings(&v0->unk_6604);
    BoxTaskParams_Free(v2);
}

static void BoxGraphics_ClearMonPreview(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    PCMonPreviewPanel_Hide(&(v0->unk_6604));
    BoxTaskParams_Free(v2);
}

static void BoxGraphics_PickUpMonIntoCursor(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v1 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        BoxCursorSprite_StartPickUpAnimation(&(v0->unk_5E24));
        params->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPickUpDone(&(v0->unk_5E24))) {
            BoxTaskParams_Free(params);
        }
        break;
    }
}

static void BoxGraphics_PlaceMonDownFromCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartPlaceAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPlaceDone(&(v0->unk_5E24))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_SwapMonsInBox(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartSwapAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsSwapDone(&(v0->unk_5E24))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_ReloadBoxMons(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_ResetPosition(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        BoxTaskParams_Free(v2);
        break;
    }
}

static void BoxGraphics_ReloadPartyMons(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxParty_ReloadMons(&(v0->unk_B290));
        v2->state++;
        break;
    case 1:
        BoxParty_ShiftMonsDown(&(v0->unk_B290));
        v2->state++;
        break;
    case 2:
        if (BoxParty_IsShiftDone(&(v0->unk_B290))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PlayReleaseCursorMonAnimation(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartReleaseAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_UpdateReleaseAnimation(&(v0->unk_5E24))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PlayReleaseBoxMonAnimation(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxView_StartReleaseMonAnimation(&(v0->unk_494), BoxApp_GetCursorBoxPosition(v1));
        v2->state++;
        break;
    case 1:
        if (BoxView_UpdateReleaseMonAnimation(&(v0->unk_494))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PlayReleasePartyMonAnimation(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxParty_StartReleaseAnimation(&(v0->unk_B290), BoxApp_GetCursorPartyPosition(v1));
        v2->state++;
        break;
    case 1:
        if (BoxParty_UpdateReleaseAnimation(&(v0->unk_B290))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_DisplayItemInfo(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxSelectionPopup_ShowItemInfo(&(v0->unk_6690));
        v2->state++;
        break;
    case 1:
        if (BoxSelectionPopup_IsItemInfoDone(&(v0->unk_6690))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_CloseItemInfo(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxSelectionPopup_HideItemInfo(&(v0->unk_6690));
        v2->state++;
        break;
    case 1:
        if (BoxSelectionPopup_IsHideItemInfoDone(&(v0->unk_6690))) {
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PickUpItemIntoCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartPickUpItemAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPickUpItemDone(&(v0->unk_5E24))) {
            PCMonPreviewPanel_DrawHeldItem(&(v0->unk_6604));
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_PlaceItemDownFromCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartPlaceItemAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPlaceItemDone(&(v0->unk_5E24))) {
            PCMonPreviewPanel_DrawHeldItem(&(v0->unk_6604));
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_SwapItems(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_StartSwapItemAnimation(&(v0->unk_5E24));
        v2->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsSwapItemDone(&(v0->unk_5E24))) {
            PCMonPreviewPanel_DrawHeldItem(&(v0->unk_6604));
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_UpdateHeldItemDisplay(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2;
    u32 item;

    v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;
    item = BoxApp_GetPreviewedMonHeldItem(v1);

    if (BoxApp_GetPreviewMonSource(v1) == PREVIEW_MON_IN_CURSOR) {
        BoxCursorSprite_UpdateHeldMonItem(&v0->unk_5E24, item);
    } else {
        switch (BoxApp_GetCursorLocation(v1)) {
        case CURSOR_IN_PARTY:
            BoxParty_UpdateMonItem(&v0->unk_B290, BoxApp_GetCursorPartyPosition(v1), item);
            break;
        case CURSOR_IN_BOX:
            BoxView_UpdateMonItem(&v0->unk_494, BoxApp_GetCursorBoxPosition(v1), item);
            break;
        }
    }

    BoxTaskParams_Free(v2);
}

static void BoxGraphics_ItemShrinkToNothing(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *v2;
    u32 v3;

    v2 = (BoxTaskParams *)param1;
    v0 = v2->unk_0C;
    v1 = v0->unk_1C4;

    switch (v2->state) {
    case 0:
        BoxCursorSprite_HideHeldItem(&v0->unk_5E24);
        BoxHeldItem_StartShrink(v0->unk_B40C);
        v2->state++;
        break;
    case 1:
        if (BoxHeldItem_IsShrinkDone(v0->unk_B40C)) {
            BoxCursorSprite_ShowHeldItem(&v0->unk_5E24);
            BoxTaskParams_Free(v2);
        }
        break;
    }
}

static void BoxGraphics_DisplayBoxMessage(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *params;
    const BoxApplication *v2;

    params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v2 = v0->unk_1C4;

    BoxMenuGraphics_DrawMessage(&(v0->unk_6658), BoxApp_GetBoxMessageID(v2));
    BoxTaskParams_Free(params);
}

static void BoxGraphics_ShowMenu(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxMenuGraphics_DrawMessage(&(v0->unk_6658), BoxApp_GetBoxMessageID(v2));
    BoxMenuGraphics_DrawMenu(&(v0->unk_6658), &(v2->boxMenu));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_CloseMessageBox(SysTask *param0, void *param1)
{
    BoxTaskParams *v1 = (BoxTaskParams *)param1;
    BoxGraphics *v0 = v1->unk_0C;

    BoxMenuGraphics_Hide(&(v0->unk_6658));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_HideMenu(SysTask *param0, void *param1)
{
    BoxTaskParams *v1 = (BoxTaskParams *)param1;
    BoxGraphics *v0 = v1->unk_0C;

    BoxMenuGraphics_HideMenu(&(v0->unk_6658));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_UpdateMenuCursor(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    Sound_PlayEffect(SE_CONFIRM_sseq_3);
    BoxGraphics_DrawMenuCursorBox(&(v0->unk_6658), &(v2->boxMenu));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_UpdateMarkings(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
    BoxMenuGraphics_UpdateMarkings(&(v0->unk_6658), &(v2->boxMenu));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_ShowBoxSelectionPopup(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *params;
    const BoxApplication *v2;

    params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v2 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        BoxSelectionPopup_Show(&(v0->unk_6690));
        params->state++;
        break;
    case 1:
        if (BoxSelectionPopup_IsShowDone(&(v0->unk_6690))) {
            BoxTaskParams_Free(params);
        }
    }
}

static void BoxGraphics_ScrollBoxSelectionPopup(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        BoxSelectionPopup_Update(&(v0->unk_6690));
        v1->state++;
        break;
    case 1:
        BoxTaskParams_Free(v1);
    }
}

static void BoxGraphics_HideBoxSelectionPopup(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        BoxSelectionPopup_Hide(&(v0->unk_6690));
        v1->state++;
        break;
    case 1:
        if (BoxSelectionPopup_IsHideDone(&(v0->unk_6690))) {
            BoxTaskParams_Free(v1);
        }
    }
}

static void BoxGraphics_TransitionWallpaper(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *params;
    const BoxApplication *v2;

    params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v2 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        BoxView_StartWallpaperTransition(&(v0->unk_494));
        params->state++;
        break;
    case 1:
        if (BoxView_UpdateWallpaperTransition(&(v0->unk_494))) {
            BoxTaskParams_Free(params);
        }
        break;
    }
}

static void BoxGraphics_PressBoxButton(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        BoxCursorSprite_StartPressAnimation(&(v0->unk_5E24));
        v1->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPressDone(&(v0->unk_5E24))) {
            switch (BoxApp_GetCursorLocation(v2)) {
            case CURSOR_ON_PARTY_BUTTON:
                BoxButtonSprite_SetState(&(v0->unk_65BC), 1);
                break;
            case CURSOR_ON_CLOSE_BUTTON:
                BoxButtonSprite_SetState(&(v0->unk_65BC), 2);
                break;
            }

            v1->unk_08 = 0;
            v1->state++;
        }
        break;
    case 2:
        if (++(v1->unk_08) >= 6) {
            BoxCursorSprite_StartReleasePressAnimation(&(v0->unk_5E24));
            BoxButtonSprite_SetState(&(v0->unk_65BC), 0);
            v1->state++;
        }
        break;
    case 3:
        if (BoxCursorSprite_IsReleasePressDone(&(v0->unk_5E24))) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_OpenPartyPopup(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_OPEN7_sseq);
        BoxCursorSprite_SetPriorityHigh(&(v0->unk_5E24));
        BoxParty_Hide(&(v0->unk_B290));
        v1->state++;
        break;
    case 1:
        if (BoxParty_IsHideDone(&(v0->unk_B290))) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_ClosePartyPopup(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        BoxHeldItem_StartReturnToMon(v0->unk_B40C);
        v1->state++;
    case 1:
        if (BoxHeldItem_IsReturnToMonDone(v0->unk_B40C) == 0) {
            break;
        }

        v1->state++;
    case 2:
        Sound_PlayEffect(SEQ_SE_DP_CLOSE7_sseq);
        BoxParty_StartHide(&(v0->unk_B290));
        v1->state++;
        break;
    case 3:
        if (BoxParty_IsShowDone(&(v0->unk_B290))) {
            BoxCursorSprite_SetPriorityNormal(&(v0->unk_5E24));
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_PlayAdjustPartyAnimation(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *params;
    const BoxApplication *v2;

    params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v2 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        BoxParty_ShiftMonsDown(&(v0->unk_B290));
        params->state++;
        break;
    case 1:
        if (BoxParty_IsShiftDone(&(v0->unk_B290))) {
            BoxTaskParams_Free(params);
        }
        break;
    }
}

static void BoxGraphics_MovePartyCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        if (BoxApp_GetCursorLocation(v2) == CURSOR_IN_PARTY) {
            BoxParty_MoveCursorToLastMon(&v0->unk_B290);
            v1->state++;
            break;
        }

        BoxTaskParams_Free(v1);
        break;
    case 1:
        if (BoxParty_IsMoveDone(&v0->unk_B290)) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_SetMonMarkingsTransparency(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxView_ApplyTransparencyToMons(&v0->unk_494);
    BoxParty_ApplyTransparency(&v0->unk_B290);
    BoxCursorSprite_ApplyHeldMonTransparency(&v0->unk_5E24);
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_OpenOrCloseSelectedTouchDial(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        BoxTouchDial_ChangeSelected(v0->unk_B408);
        v1->state++;
        break;
    case 1:
        if (BoxTouchDial_IsChangeDone(v0->unk_B408)) {
            if (v2->touchDialHelper.selectedTouchDial == TOUCH_DIALS_NONE) {
                BoxTaskParams_Free(v1);
            } else {
                BoxTouchDial_Update(v0->unk_B408);
                v1->state++;
            }
        }
        break;
    case 2:
        if (BoxTouchDial_IsUpdateDone(v0->unk_B408)) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_ScrollTouchDial(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        BoxTouchDial_Scroll(v0->unk_B408);
        v1->state++;
        break;
    case 1:
        if (BoxTouchDial_IsScrollDone(v0->unk_B408)) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_UpdateMarkingsTouchButton(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxTouchDial_UpdateMarkingIcons(v0->unk_B408);
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_UpdateCursorFastMode(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxCursorSprite_UpdateFastMode(&(v0->unk_5E24));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_StartDrawMultiSelect(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxGraphics_OpenMultiSelectCursor(&(v0->unk_5E24));
    BoxGraphics_ApplyMultiSelectMonShading(&(v0->unk_494));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_ClearMultiSelectShading(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxView_ClearMultiSelectShading(&(v0->unk_494));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_ApplyMultiSelectMonShadingTask(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    BoxGraphics_ApplyMultiSelectMonShading(&(v0->unk_494));
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_BounceCursor(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        BoxCursorSprite_StartPickUpAnimation(&(v0->unk_5E24));
        v1->state++;
        break;
    case 1:
        if (BoxCursorSprite_IsPickUpDone(&(v0->unk_5E24))) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_SetCompareButtonUnpressed(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    PCCompare_SetButtonState(v0->unk_B410, 0);
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_SetCompareButtonPressed(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    PCCompare_SetButtonState(v0->unk_B410, 1);
    BoxTaskParams_Free(v1);
}

static void BoxGraphics_SwitchCompareMode(SysTask *param0, void *param1)
{
    BoxGraphics *v0;
    BoxTaskParams *v1;
    const BoxApplication *v2;

    v1 = (BoxTaskParams *)param1;
    v0 = v1->unk_0C;
    v2 = v0->unk_1C4;

    switch (v1->state) {
    case 0:
        PCCompare_StartModeSwitch(v0->unk_B410);
        v1->state++;
        break;
    case 1:
        if (PCCompare_UpdateModeSwitch(v0->unk_B410)) {
            BoxTaskParams_Free(v1);
        }
        break;
    }
}

static void BoxGraphics_ScreenFadeBothToBlackLogOff(SysTask *task, void *param1)
{
    BoxGraphics *v0;
    const BoxApplication *v1;
    BoxTaskParams *params = (BoxTaskParams *)param1;
    v0 = params->unk_0C;
    v1 = v0->unk_1C4;

    switch (params->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_PC_LOGOFF_sseq);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_BOX_GRAPHICS);
        params->state++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            BoxTaskParams_Free(params);
        }
        break;
    }
}

static void BoxGraphics_InitBgLayers(BoxGraphics *param0, const BoxApplication *param1)
{
    static const GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_01_FG
    };

    static const GraphicsModes v1 = {
        GX_DISPMODE_GRAPHICS,
        GX_BGMODE_0,
        GX_BGMODE_0,
        GX_BG0_AS_3D,
    };

    static const BgTemplate v2 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = 0,
        .charBase = 0,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v3 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xe000),
        .charBase = (GX_BG_CHARBASE_0x18000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v4 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xe800),
        .charBase = (GX_BG_CHARBASE_0x00000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v5 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x1000,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xf000),
        .charBase = (GX_BG_CHARBASE_0x10000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 3,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v6 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xf000),
        .charBase = (GX_BG_CHARBASE_0x10000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v7 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x0,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xd000),
        .charBase = (GX_BG_CHARBASE_0x00000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v8 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x0,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xe000),
        .charBase = (GX_BG_CHARBASE_0x00000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 2,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v9 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x0,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = (GX_BG_SCRBASE_0xf800),
        .charBase = (GX_BG_CHARBASE_0x00000),
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 3,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v10 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x0,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    static const BgTemplate v11 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x0,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 2,
        .areaOver = 0,
        .mosaic = FALSE,
    };

    GXLayers_SetBanks(&v0);

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

    SetAllGraphicsModes(&v1);
    Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_MAIN_1, &v3, 0);
    Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_MAIN_2, &v4, 0);
    Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_MAIN_3, &v5, 0);

    if (BoxApp_GetBoxMode(param1) != PC_MODE_COMPARE) {
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_0, &v6, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_1, &v7, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_2, &v8, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_3, &v9, 0);
    } else {
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_0, &v6, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_1, &v10, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_2, &v11, 0);
        Bg_InitFromTemplate(param0->unk_1C0, BG_LAYER_SUB_3, &v9, 0);
    }

    BoxGraphics_Init3D();
}

static void BoxGraphics_LoadBgTiles(BoxGraphics *param0, const BoxApplication *param1, NARC *param2)
{
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 4, param0->unk_1C0, 1, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
    Bg_FillTilemapRect(param0->unk_1C0, 1, 0x0, 0, 0, 32, 32, 17);
    Bg_CopyTilemapBufferToVRAM(param0->unk_1C0, 1);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 1, param0->unk_1C0, 2, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
    Graphics_LoadPaletteFromOpenNARC(param2, 5, 0, 0, 0x20 * 7, HEAP_ID_BOX_GRAPHICS);

    if (BoxApp_GetBoxMode(param1) != PC_MODE_COMPARE) {
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param2, 0, param0->unk_1C0, 2, 0, 0, 1, HEAP_ID_BOX_GRAPHICS);
    }

    BoxView_DrawBackground(&param0->unk_494);
    BoxView_LoadWallpaper(&param0->unk_494, &param1->customization, 0, TRUE);
    PCMonPreviewPanel_InitWindows(&(param0->unk_6604));
    BoxMenuGraphics_InitWindows(&(param0->unk_6658));
    BoxSelectionPopup_InitWindows(&(param0->unk_6690));
    BoxTouchDial_Init(param0->unk_B408, param2);
    PCCompare_Init(param0->unk_B410, param2);

    if (BoxApp_GetCursorLocation(param1) == CURSOR_IN_PARTY) {
        BoxParty_Show(&(param0->unk_B290));
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    GX_DispOn();
}

static void BoxGraphics_Init3D(void)
{
    NNS_G3dInit();
    G3X_InitMtxStack();

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);
    G3_ViewPort(0, 0, 255, 191);
}

static void BoxGraphics_LoadSprites(BoxGraphics *param0, const BoxApplication *param1, NARC *param2)
{
    BoxCursorSprite_Init(&param0->unk_5E24, param2);
    BoxButtonSprite_Init(&param0->unk_65BC, param2);
    BoxHeldItem_Show(param0->unk_B40C);
}

static int BoxGraphics_GetBoxMoveDirection(u32 sourceBoxID, u32 destBoxID)
{
    int distanceRight, distanceLeft;

    if (destBoxID > sourceBoxID) {
        distanceRight = destBoxID - sourceBoxID;
        distanceLeft = sourceBoxID + (MAX_PC_BOXES - destBoxID);
    } else {
        distanceRight = destBoxID + (MAX_PC_BOXES - sourceBoxID);
        distanceLeft = sourceBoxID - destBoxID;
    }

    return (distanceRight >= distanceLeft) ? -1 : 1;
}

SysTask *BoxGraphics_StartVBlankTask(SysTaskFunc param0, void *param1, u32 param2)
{
    return SysTask_ExecuteOnVBlank(param0, param1, param2);
}

NNSG2dImagePaletteProxy *BoxGraphics_GetPaletteProxy(BoxGraphics *param0)
{
    return &(param0->unk_1A8);
}

BoxMonSpriteManager *BoxGraphics_GetBoxMonSpriteManager(BoxGraphics *param0)
{
    return &(param0->unk_1C8);
}

BoxView *BoxGraphics_GetBoxView(BoxGraphics *param0)
{
    return &(param0->unk_494);
}

BoxParty *BoxGraphics_GetBoxParty(BoxGraphics *param0)
{
    return &(param0->unk_B290);
}

BoxCursorSprite *BoxGraphics_GetCursorSprite(BoxGraphics *param0)
{
    return &(param0->unk_5E24);
}

BoxHeldItemIcons *BoxGraphics_GetHeldItemIcons(BoxGraphics *param0)
{
    return param0->unk_B40C;
}

BoxSelectionPopup *BoxGraphics_GetBoxSelectionPopup(BoxGraphics *param0)
{
    return &(param0->unk_6690);
}

PokemonSpriteManager *BoxGraphics_GetPokemonSpriteManager(BoxGraphics *param0)
{
    return param0->unk_1BC;
}

int BoxGraphics_GetCompareXOffset(BoxGraphics *param0)
{
    if (BoxApp_GetBoxMode(param0->unk_1C4) != PC_MODE_COMPARE) {
        return 0;
    } else {
        return -44;
    }
}

void BoxGraphics_InitSpriteResources(SpriteResourcesHeader *param0, NNSG2dImageProxy *param1, NNSG2dImagePaletteProxy *param2, NNSG2dCellDataBank *param3, NNSG2dCellAnimBankData *param4, u32 param5)
{
    param0->imageProxy = param1;
    param0->paletteProxy = param2;
    param0->cellBank = param3;
    param0->cellAnimBank = param4;
    param0->priority = param5;
    param0->charData = NULL;
    param0->multiCellBank = NULL;
    param0->multiCellAnimBank = NULL;
    param0->isVRamTransfer = 0;
}

Sprite *BoxGraphics_CreateSprite(SpriteList *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3, u32 param4, int param5)
{
    SpriteListTemplate v0;
    Sprite *v1;

    v0.list = param0;
    v0.resourceData = param1;
    v0.position.x = param2 * FX32_ONE;
    v0.position.y = param3 * FX32_ONE;
    v0.position.z = 0;
    v0.priority = param4;
    v0.vramType = param5;
    v0.heapID = HEAP_ID_BOX_GRAPHICS;

    {
        OSIntrMode v2 = OS_DisableInterrupts();

        v1 = SpriteList_Add(&v0);
        OS_RestoreInterrupts(v2);
    }

    if (v1) {
        Sprite_SetAnimateFlag(v1, 1);
        Sprite_SetAnimSpeed(v1, FX32_ONE * (2 / 2));
    }

    return v1;
}

void BoxGraphics_SetSpritePriority(Sprite *sprite, u32 priority)
{
    OSIntrMode mode = OS_DisableInterrupts();

    Sprite_SetPriority(sprite, priority);
    OS_RestoreInterrupts(mode);
}

void BoxGraphics_BlendPalette(const u16 *param0, u16 *param1, u32 param2, u16 param3, u32 param4)
{
    int v0, v1, v2;
    int v3, v4, v5;
    int v6;

    v3 = (param3 & 0x1f) << 8;
    v4 = ((param3 >> 5) & 0x1f) << 8;
    v5 = ((param3 >> 10) & 0x1f) << 8;

    while (param2--) {
        v0 = ((*param0) & 0x1f) << 8;
        v1 = (((*param0) >> 5) & 0x1f) << 8;
        v2 = (((*param0) >> 10) & 0x1f) << 8;

        v0 += (((v3 - v0) / 16) * param4);
        v1 += (((v4 - v1) / 16) * param4);
        v2 += (((v5 - v2) / 16) * param4);

        v0 = (v0 >> 8) & 0x1f;
        v1 = (v1 >> 8) & 0x1f;
        v2 = (v2 >> 8) & 0x1f;

        *param1 = ((v2 << 10) | (v1 << 5) | v0);

        param0++;
        param1++;
    }
}

const BoxApplicationManager *BoxGraphics_GetAppManager(BoxGraphics *param0)
{
    return param0->unk_B414;
}

static u32 sBoxGraphicsDeferredFreeCount = 0;

static struct {
    BoxGraphicsDeferredFreeCallback unk_00;
    void *unk_04;
    void *unk_08;
} sBoxGraphicsDeferredFrees[32];

static void BoxGraphics_ResetDeferredFrees(void)
{
    sBoxGraphicsDeferredFreeCount = 0;
}

static void BoxGraphics_ProcessDeferredFrees(void)
{
    if (sBoxGraphicsDeferredFreeCount) {
        u32 i;

        for (i = 0; i < sBoxGraphicsDeferredFreeCount; i++) {
            Heap_Free(sBoxGraphicsDeferredFrees[i].unk_08);

            if (sBoxGraphicsDeferredFrees[i].unk_00) {
                sBoxGraphicsDeferredFrees[i].unk_00(sBoxGraphicsDeferredFrees[i].unk_04);
            }
        }

        sBoxGraphicsDeferredFreeCount = 0;
    }
}

void BoxGraphics_DeferFree(void *param0, BoxGraphicsDeferredFreeCallback param1, void *param2)
{
    GF_ASSERT(sBoxGraphicsDeferredFreeCount < 32);

    sBoxGraphicsDeferredFrees[sBoxGraphicsDeferredFreeCount].unk_08 = param0;
    sBoxGraphicsDeferredFrees[sBoxGraphicsDeferredFreeCount].unk_00 = param1;
    sBoxGraphicsDeferredFrees[sBoxGraphicsDeferredFreeCount].unk_04 = param2;
    sBoxGraphicsDeferredFreeCount++;
}
