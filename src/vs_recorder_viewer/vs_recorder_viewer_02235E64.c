#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_0208C06C.h"

#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02248408.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233F74.h"

#include "bg_window.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "battle_recording.h"
#include "vs_recorder.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    VsRecorderViewerProfilePanel unk_10;
    VsRecorderViewerSummaryPanel unk_9C;
    VsRecorderViewerTextSprite unk_158[1];
    TouchScreenActions *unk_174[1];
    Window unk_178[2];
    int unk_198;
} VsRecorderViewerBattleVideo;

static BOOL VsRecorderViewerBattleVideo_State_Init(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_FadeIn(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_SetupViewer(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_HandleTouch(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_SwitchView(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_SavePrompt(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_LoadRecordings(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_StartPlayback(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_Exit(UnkStruct_0208C06C *param0);
static BOOL VsRecorderViewerBattleVideo_State_OpenViewer(UnkStruct_0208C06C *param0);
static void VsRecorderViewerBattleVideo_TouchCallback(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerBattleVideo_LoadSelectedRecord(UnkStruct_0208C06C *param0);
static void VsRecorderViewerBattleVideo_CreateMessageWindow(UnkStruct_0208C06C *param0);
static void VsRecorderViewerBattleVideo_RemoveMessageWindow(UnkStruct_0208C06C *param0);
static void VsRecorderViewerBattleVideo_SetMessageWindowText(UnkStruct_0208C06C *param0, int param1);
static void VsRecorderViewerBattleVideo_CreateStatusSprite(UnkStruct_0208C06C *param0);
static void VsRecorderViewerBattleVideo_FreeStatusSprite(UnkStruct_0208C06C *param0);

// clang-format off
BOOL(*const sVsRecorderViewerBattleVideoStateTable[])(UnkStruct_0208C06C *) = {
    VsRecorderViewerBattleVideo_State_Init,
    VsRecorderViewerBattleVideo_State_FadeIn,
    VsRecorderViewerBattleVideo_State_SetupViewer,
    VsRecorderViewerBattleVideo_State_HandleTouch,
    VsRecorderViewerBattleVideo_State_SwitchView,
    VsRecorderViewerBattleVideo_State_SavePrompt,
    VsRecorderViewerBattleVideo_State_LoadRecordings,
    VsRecorderViewerBattleVideo_State_StartPlayback,
    VsRecorderViewerBattleVideo_State_Exit,
    VsRecorderViewerBattleVideo_State_OpenViewer,
};
// clang-format on

static const TouchScreenRect sVsRecorderViewerBattleVideoTouchRects[] = {
    { 0x10, 0x30, 0x40, 0xC8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static BOOL VsRecorderViewerBattleVideo_State_Init(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerBattleVideo));

    memset(v0, 0, sizeof(VsRecorderViewerBattleVideo));
    param0->unk_860 = v0;

    Bg_ClearTilemap(param0->unk_14.unk_10, 2);
    Bg_ClearTilemap(param0->unk_14.unk_10, 3);
    Bg_ClearTilemap(param0->unk_14.unk_10, 6);
    Bg_ClearTilemap(param0->unk_14.unk_10, 7);

    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_FadeIn(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 1:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_SetPriority(BG_LAYER_MAIN_0, 0);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_3, 2);
        Bg_SetPriority(BG_LAYER_SUB_0, 0);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 1);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);
        param0->unk_08++;
        break;
    default:
        VsRecorderViewerList_StartNetworkTask(param0, 0);

        if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
            BOOL v1 = 0;

            if (param0->unk_86C == 0) {
                v1 = 1;
            } else if (BattleRecording_GetSummaryValue(param0->unk_87C[param0->unk_86C], 5, 0) == 1) {
                v1 = 1;
            } else if (param0->unk_874 == 1) {
                v1 = 1;
            }

            if (v1) {
                VsRecorderViewerBattleVideo_CreateStatusSprite(param0);
                v0->unk_198 = 0;
                VsRecorderViewerMain_SetState(param0, 9);
            } else {
                v0->unk_198 = 1;
                VsRecorderViewerMain_SetState(param0, 6);
            }
        } else {
            VsRecorderViewerMain_SetState(param0, 2);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_SetupViewer(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerBattleVideo_CreateStatusSprite(param0);
        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerBattleVideo_LoadSelectedRecord(param0);
        v0->unk_174[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerBattleVideoTouchRects, NELEMS(sVsRecorderViewerBattleVideoTouchRects), VsRecorderViewerBattleVideo_TouchCallback, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_9C, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_9C), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 1);
            VsRecorderViewerBattleVideo_CreateMessageWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_HandleTouch(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_174[0]);
    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_SwitchView(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (v0->unk_0C == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_9C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_10, param0);
        }

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 1)) {
            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_0C == 0) {
            VsRecorderViewerList_InitProfile(&v0->unk_10, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_10, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, 80, 3);
        } else {
            VsRecorderViewerList_InitSummary(&v0->unk_9C, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_9C), 3);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    case 3:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            if (v0->unk_0C == 0) {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_10, 1);
            } else {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }
        break;
    default:
        v0->unk_0C ^= 1;
        VsRecorderViewerBattleVideo_SetMessageWindowText(param0, 121 + v0->unk_0C);
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static const TouchScreenRect sVsRecorderViewerBattleVideoSavePromptTouchRects[] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 }
};

static void VsRecorderViewerBattleVideo_CreateSavePromptWindows(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3 = 1;
    int v4;

    v1 = &v0->unk_178[0];
    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 4, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.unk_34, 130);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);

    v3 += (10 * 2);
    v1 = &v0->unk_178[1];

    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 18, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.unk_34, 131);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerBattleVideo_RemoveSavePromptWindows(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_178[0]);
    Window_Remove(&v0->unk_178[0]);
    Window_ClearAndCopyToVRAM(&v0->unk_178[1]);
    Window_Remove(&v0->unk_178[1]);
}

static BOOL VsRecorderViewerBattleVideo_State_SavePrompt(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        TouchScreenActions_Free(v0->unk_174[0]);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_0C == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_9C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_10, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerBattleVideo_RemoveMessageWindow(param0);
        v0->unk_198 = 0;
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerBattleVideo_FreeStatusSprite(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 2:
        VsRecorderViewerBattleVideo_CreateSavePromptWindows(param0);
        VsRecorderViewerList_OpenMainMessage(param0, 296);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.unk_00, 84, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 4:
        if (TouchScreen_LocationPressed(&sVsRecorderViewerBattleVideoSavePromptTouchRects[0])) {
            v0->unk_198 = 1;
            VsRecorderViewerList_PlayRingAnim(param0);

            if (SaveData_FullSaveRequired(param0->saveData)) {
                VsRecorderViewerList_UpdateMessageText(param0, 298);
            } else {
                VsRecorderViewerList_UpdateMessageText(param0, 299);
            }

            param0->unk_08++;
        } else if (TouchScreen_LocationPressed(&sVsRecorderViewerBattleVideoSavePromptTouchRects[1])) {
            v0->unk_198 = 2;
            VsRecorderViewerList_PlayRingAnim(param0);

            param0->unk_08 = 6;
        }

        break;
    case 5:
        SaveData_Save(param0->saveData);
        param0->unk_08++;
        break;
    case 6:
        VsRecorderViewerList_CloseMainMessage(param0);
        VsRecorderViewerBattleVideo_RemoveSavePromptWindows(param0);
        param0->unk_08++;
        break;
    case 7:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    default:
        if (v0->unk_198 == 1) {
            VsRecorderViewerMain_SetState(param0, 7);
        } else {
            v0->unk_198 = 0;
            v0->unk_0C = 0;
            VsRecorderViewerMain_SetState(param0, 2);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_LoadRecordings(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_OpenMainMessage(param0, 299);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 1:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_08++;
        }
        break;
    case 2:
        if (param0->unk_874 == 0) {
            {
                int v1;
                int v2;

                BattleRecording_Load(param0->saveData, 102, &v1, NULL, param0->unk_86C);
                v2 = VsRecorderViewerRecording_FinalizeAndSave(param0->saveData, param0->unk_86C);
                BattleRecording_Free();

                VsRecorderViewerList_FreeBattleRecordings(param0);
                VsRecorderViewerList_LoadBattleRecordings(param0);
            }
        }

        param0->unk_08++;
        break;
    default:
        VsRecorderViewerList_CloseMainMessage(param0);
        VsRecorderViewerBattleVideo_CreateStatusSprite(param0);
        VsRecorderViewerMain_SetState(param0, 9);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_StartPlayback(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 1:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_08++;
        }
        break;
    case 2:
        if (v0->unk_198 == 0) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_0C == 0) {
                VsRecorderViewerList_FreeSummary(&v0->unk_9C, param0);
            } else {
                VsRecorderViewerList_FreeProfile(&v0->unk_10, param0);
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            TouchScreenActions_Free(v0->unk_174[0]);
            VsRecorderViewerBattleVideo_RemoveMessageWindow(param0);
            VsRecorderViewerBattleVideo_FreeStatusSprite(param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenuWithExtraEntry(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerMain_SetPendingSelection(param0, *(param0->unk_10));
        VsRecorder_SetPlaybackRequest(param0->unk_868, 1, 0);
        param0->unk_08++;
        break;
    default:
        Heap_Free(v0);
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_Exit(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        TouchScreenActions_Free(v0->unk_174[0]);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);

        if (v0->unk_0C == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_9C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_10, param0);
        }

        VsRecorderViewerBattleVideo_RemoveMessageWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerBattleVideo_FreeStatusSprite(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 2:
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.unk_44);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerBattleVideo_State_OpenViewer(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerBattleVideo_LoadSelectedRecord(param0);
        v0->unk_174[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerBattleVideoTouchRects, NELEMS(sVsRecorderViewerBattleVideoTouchRects), VsRecorderViewerBattleVideo_TouchCallback, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_9C, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_9C), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_9C, 1);
            VsRecorderViewerBattleVideo_CreateMessageWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);

            if (v0->unk_198 == 1) {
                param0->unk_08 = 0xFF;
            } else {
                param0->unk_08++;
            }

            v0->unk_198 = 0;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    case 4:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 5:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_08++;
        }

        break;
    default:
        param0->unk_534.unk_1A4 += 1;
        VsRecorderViewerMain_ResetSelection(param0);
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static void VsRecorderViewerBattleVideo_TouchCallback(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    UnkStruct_0208C06C *v0 = param2;
    VsRecorderViewerBattleVideo *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);

        if ((v0->unk_86C == 0) || (BattleRecording_GetSummaryValue(v1->unk_9C.unk_04, 5, 0) == 1)) {
            VsRecorderViewerMain_SetState(v0, 7);
        } else {
            VsRecorderViewerMain_SetState(v0, 5);
        }
        break;
    case 2:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 8);
        break;
    }
}

static void VsRecorderViewerBattleVideo_LoadSelectedRecord(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    v0->unk_10.unk_00 = param0->unk_88C[param0->unk_86C];
    v0->unk_9C.unk_00 = v0->unk_10.unk_00;
    v0->unk_9C.unk_04 = param0->unk_87C[param0->unk_86C];
}

static void VsRecorderViewerBattleVideo_CreateMessageWindow(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;

    v1 = &v0->unk_178[0];
    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 8, 3, 16, 2, 14, v2);
    VsRecorderViewerBattleVideo_SetMessageWindowText(param0, 121);
}

static void VsRecorderViewerBattleVideo_RemoveMessageWindow(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_178[0]);
    Window_Remove(&v0->unk_178[0]);
}

static void VsRecorderViewerBattleVideo_SetMessageWindowText(UnkStruct_0208C06C *param0, int param1)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_178[0];

    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);
    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerBattleVideo_CreateStatusSprite(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadSpriteResourceSetA(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_158[0].unk_08 = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_158[0], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_158[0], &param0->unk_14, 3);

    ManagedSprite_SetAnim(v0->unk_158[0].unk_08, 0);
    ManagedSprite_SetPositionXY(v0->unk_158[0].unk_08, 80, 232);
    FontOAM_SetXY(v0->unk_158[0].unk_0C, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_158[0].unk_0C, 1);
}

static void VsRecorderViewerBattleVideo_FreeStatusSprite(UnkStruct_0208C06C *param0)
{
    VsRecorderViewerBattleVideo *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_158[0]);
    Sprite_DeleteAndFreeResources(v0->unk_158[0].unk_08);
    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}
