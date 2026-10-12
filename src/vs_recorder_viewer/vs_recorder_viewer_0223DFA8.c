#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_vs_recorder_state.h"

#include "global_terminal/global_terminal_0222AE60.h"
#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"
#include "global_terminal/struct_global_terminal_0222BED8_sub1.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233F74.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02249380.h"

#include "bg_window.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "network_icon.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "battle_recording.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"
#include "vs_recorder.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    Window unk_14[8];
    Window unk_94[8];
    VsRecorderViewerTextSprite unk_114[4];
    GlobalTerminalRecordAlt *unk_184;
    TouchScreenActions *unk_188[3];
    VsRecorderViewerProfilePanel unk_194;
    VsRecorderViewerSummaryPanel unk_220;
    GlobalTerminalRecordAlt unk_2DC;
    int unk_1FB0;
    int unk_1FB4;
    int unk_1FB8;
    int unk_1FBC;
    BOOL unk_1FC0;
    VsRecorderViewerRankingMessageBox unk_1FC4;
    VsRecorderViewerListEntry *unk_1FD8;
    VsRecorderViewerListConfig unk_1FDC;
    VsRecorderViewerRankingIconGrid unk_2008;
} VsRecorderViewerRankingContext;

static const VsRecorderViewerListConfig sVsRecorderViewerRankingWindowConfig = {
    NULL,
    0x6,
    0x3,
    0x2,
    0x8,
    0xA,
    0xF,
    0x80,
    0x2,
    0x5,
    NULL
};

static const TouchScreenRect sVsRecorderViewerRankingMainButtonRects[] = {
    { 0x10, 0x30, 0x40, 0xC8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x80, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 }
};

static const TouchScreenRect sVsRecorderViewerRankingProfileButtonRects[] = {
    { 0x19, 0x39, 0x32, 0xD2 },
    { 0x3D, 0x5D, 0x32, 0xD2 },
    { 0x61, 0x81, 0x32, 0xD2 },
    { 0x85, 0xA5, 0x32, 0xD2 }
};

static const TouchScreenRect sVsRecorderViewerRankingSummaryButtonRects[] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 }
};

static const TouchScreenRect sVsRecorderViewerRankingBackButtonRects[] = {
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerRankingIconButtonRects[] = {
    { 0x20, 0x60, 0x50, 0xB0 }
};

static void VsRecorderViewerRanking_LayoutIconGrid(VsRecorderState *param0);
static void VsRecorderViewerRanking_CreateBottomPromptSprites(VsRecorderState *param0);
static void VsRecorderViewerRanking_DrawMessageText(VsRecorderState *param0, int param1, int param2);
static BOOL VsRecorderViewerRanking_State_TransferSelectedRecord(VsRecorderState *param0);
static void VsRecorderViewerRanking_FreeSummaryAndProfile(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_UpdateSummaryList(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitOwnRecord(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_UploadSummary(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitProfileRecord(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_UpdateProfileList(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitGlobalRecord(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_ShowRecordPanel(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitPlayerSelect(VsRecorderState *param0);
static void VsRecorderViewerRanking_DrawProfileName(VsRecorderViewerTextSprite *param0, VsRecorderState *param1, int param2);
static void VsRecorderViewerRanking_CreateProfileLabels(VsRecorderState *param0);
static void VsRecorderViewerRanking_FreeProfileLabels(VsRecorderState *param0);
static void VsRecorderViewerRanking_FreeBottomPromptSprites(VsRecorderState *param0);
static void VsRecorderViewerRanking_SetBottomPromptLayout(VsRecorderState *param0, int param1);
static void VsRecorderViewerRanking_RemoveHeaderWindows(VsRecorderState *param0);
static void VsRecorderViewerRanking_RemoveMessageWindows(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_Init(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitScreen(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_TransferRecord(VsRecorderState *param0);
static void VsRecorderViewerRanking_CreateHeaderWindows(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitRankingView(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_UpdateRankingView(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_ExitRankingView(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_InitTouchHandlers(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_UpdateMainMenu(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_ToggleRecordPanel(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_ExitAndRequestPlayback(VsRecorderState *param0);
static BOOL VsRecorderViewerRanking_State_ReenterRanking(VsRecorderState *param0);
static void VsRecorderViewerRanking_DrawMessageWithPlayerName(VsRecorderState *param0, int param1, BOOL param2);
static BOOL VsRecorderViewerRanking_State_ViewSelectedRecord(VsRecorderState *param0);
static void VsRecorderViewerRanking_RemoveMessageWindow(VsRecorderState *param0);
static void VsRecorderViewerRanking_SetMessageWindowText(VsRecorderState *param0, int param1);
static void VsRecorderViewerRanking_CreateMessageWindow(VsRecorderState *param0);
static void VsRecorderViewerRanking_CreateStatWindows(VsRecorderState *param0);
static void VsRecorderViewerRanking_RemoveStatWindows(VsRecorderState *param0);
static void VsRecorderViewerRanking_HandleMainButtonTouch(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRanking_HandleProfileTouch(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRanking_HandleSummaryListTouch(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRanking_LoadProfileAndSummary(VsRecorderState *param0);
static void VsRecorderViewerRanking_BuildRankingIconGrid(VsRecorderState *param0);
static void VsRecorderViewerRanking_SetIconGridVisible(VsRecorderState *param0, BOOL param1);
static void VsRecorderViewerRanking_FreeIconGridSprites(VsRecorderState *param0);
static void VsRecorderViewerRanking_ScrollIconGrid(VsRecorderState *param0);
static void VsRecorderViewerRanking_FreeBottomPromptSpritesAndCleanup(VsRecorderState *param0);

static void VsRecorderViewerRanking_LayoutIconGrid(VsRecorderState *param0)
{
    const s16 v0[][2] = {
        { 13 * 8, 9 * 8 },
        { 16 * 8, 9 * 8 },
        { 19 * 8, 9 * 8 },
        { 22 * 8, 9 * 8 },
        { 25 * 8, 9 * 8 },
        { 28 * 8, 9 * 8 },
        { 13 * 8, 12 * 8 },
        { 16 * 8, 12 * 8 },
        { 19 * 8, 12 * 8 },
        { 22 * 8, 12 * 8 },
        { 25 * 8, 12 * 8 },
        { 28 * 8, 12 * 8 },
        { 13 * 8, 15 * 8 },
        { 16 * 8, 15 * 8 },
        { 19 * 8, 15 * 8 },
        { 22 * 8, 15 * 8 },
        { 25 * 8, 15 * 8 },
        { 28 * 8, 15 * 8 },
        { 13 * 8, 18 * 8 },
        { 16 * 8, 18 * 8 },
        { 19 * 8, 18 * 8 },
        { 22 * 8, 18 * 8 },
        { 25 * 8, 18 * 8 },
        { 28 * 8, 18 * 8 },
        { 13 * 8, 21 * 8 },
        { 16 * 8, 21 * 8 },
        { 19 * 8, 21 * 8 },
        { 22 * 8, 21 * 8 },
        { 25 * 8, 21 * 8 },
        { 28 * 8, 21 * 8 },
    };
    int v1, v2;
    VsRecorderViewerRankingContext *v3 = param0->viewerData;

    for (v1 = 0; v1 < 5; v1++) {
        for (v2 = 0; v2 < 6; v2++) {
            if (v3->unk_2008.cells[v1][v2].sprite) {
                ManagedSprite_SetPositionXY(v3->unk_2008.cells[v1][v2].sprite, v0[(v1 * 6) + v2][0], v0[(v1 * 6) + v2][1]);
            }
        }
    }
}

static void VsRecorderViewerRanking_CreateBottomPromptSprites(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    VsRecorderViewerMenu_LoadSpriteResourceSetA(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_114[0].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);
    v0->unk_114[1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_114[0], &param0->menuContext, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_114[1], &param0->menuContext, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 94);

    ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
    ManagedSprite_SetAnim(v0->unk_114[1].sprite, 3);
    ManagedSprite_SetPositionXY(v0->unk_114[0].sprite, 32, 232);
    ManagedSprite_SetPositionXY(v0->unk_114[1].sprite, 128, 232);
    FontOAM_SetXY(v0->unk_114[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_114[1].fontOAM, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_114[0].fontOAM, 1);
    FontOAM_SetDrawFlag(v0->unk_114[1].fontOAM, 1);

    VsRecorderViewerRanking_SetBottomPromptLayout(param0, 0);
}

static void VsRecorderViewerRanking_DrawMessageText(VsRecorderState *param0, int param1, int param2)
{
    String *v0;
    Window *v1 = &param0->window;
    VsRecorderViewerRankingContext *v2 = param0->viewerData;

    if (param1 == 100) {
        StringTemplate *v3;
        String *v4;
        String *v5;
        PlayerProfile *v6 = v2->unk_194.profile;

        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v4 = PlayerProfile_GetName(v6, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v4);
        v5 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);
        StringTemplate_SetString(v3, 0, v4, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v5);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    } else if (param1 == 102) {
        StringTemplate *v7;
        String *v8;
        String *v9;
        PlayerProfile *v10 = param0->profiles[param2];

        v7 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v8 = PlayerProfile_GetName(v10, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v8);
        v9 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);

        StringTemplate_SetString(v7, 0, v8, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v7, v0, v9);
        String_Free(v8);
        String_Free(v9);
        StringTemplate_Free(v7);
    } else {
        v0 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);
    }

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static BOOL VsRecorderViewerRanking_State_TransferSelectedRecord(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->subState) {
    case 0:
        Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
        Bg_ClearTilemap(param0->menuContext.bgConfig, 6);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);
        } else {
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 0);
        }

        param0->subState++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->subState++;
        }
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 2:
        VsRecorderViewerList_OpenMainMessage(param0, 117);
        VsRecorderViewerList_SetupRing(param0, param0->ring, 128, 96);
        VsRecorderRing_SetVisible(param0->ring, 1);
        VsRecorderRing_SetOrbitRadii(param0->ring, 24, 24);
        v0->unk_1FC0 = 0;
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->subState++;
        break;
    case 3:
        if (GlobalTerminalTransfer_UploadId(VsRecorderViewerTransfer_GetTransfer(param0), param0->recordStore.records[param0->menuContext.listWindow.scrollState.selection]->data.recordingID) == 1) {
            param0->subState++;
        }
        break;
    case 4:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 8, v1->index, v1->category);
            param0->subState++;
            v0->unk_1FC0 = 0;
        } else {
            Sound_StopEffect(1381, 0);
            param0->subState = 0xFF;
            v0->unk_1FC0 = 1;
            param0->recordFlagPtr = &param0->recordStore.recordFlags[param0->menuContext.listWindow.scrollState.selection];
            v0->unk_184 = param0->recordStore.record;
            MI_CpuCopy8(v0->unk_184, &param0->recordStore.recordCopy, sizeof(GlobalTerminalRecordAlt));
        }

        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetOrbitRadii(param0->ring, 0, 0);
        break;
    default:
        if (v0->unk_1FC0) {
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            VsRecorderViewerMain_SetState(param0, v0->unk_1FBC);
            VsRecorderViewerList_SetHasPendingRecording(param0, 1);
        } else {
            VsRecorderViewerMain_SetState(param0, 20);
        }
        break;
    }

    return 0;
}

static void VsRecorderViewerRanking_FreeSummaryAndProfile(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    BattleRecording_FreeSummary(v0->unk_220.summary);
    PlayerProfile_Free(v0->unk_194.profile);
}

static BOOL VsRecorderViewerRanking_State_UpdateSummaryList(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    TouchScreenActions_HandleAction(v0->unk_188[2]);
    return 0;
}

static BOOL VsRecorderViewerRanking_State_InitOwnRecord(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            VsRecorderViewerRanking_RemoveStatWindows(param0);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 7);
            param0->subState++;
        }
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerRanking_DrawMessageText(param0, 100, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 12);
        break;
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_UploadSummary(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    VsRecorderViewerTransferStatus *v1;

    switch (param0->subState) {
    case 0:
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
            VsRecorderViewerRanking_DrawMessageText(param0, 278, 0);
            VsRecorderViewerList_ResetRecordState(param0);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 2:;
        if (VsRecorderViewerList_CheckRecordData(param0, v0->unk_1FB0, param0->recordStore.recordFlags[param0->menuContext.listWindow.scrollState.selection])) {
            param0->subState++;
        }
        break;
    case 3:
        VsRecorderViewerList_SetupRing(param0, param0->ring, 128, 96);
        VsRecorderRing_SetVisible(param0->ring, 1);
        VsRecorderRing_SetOrbitRadii(param0->ring, 24, 24);
        param0->subState++;
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        break;
    case 4:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        VsRecorderViewerRanking_DrawMessageText(param0, 280, 0);

        {
            u64 v2 = BattleRecording_GetSummaryValue(BattleRecording_GetSummary(), 4, 0);

            if (GlobalTerminalTransfer_UploadId2(VsRecorderViewerTransfer_GetTransfer(param0), v2) == 1) {
                param0->subState++;
            }
        }
        break;
    case 5:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);

            param0->subState++;
        } else {
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->subState++;
        }
        VsRecorderViewerRanking_DrawMessageText(param0, 281, 0);
        break;
    case 6:
        if (!TouchScreen_Tapped()) {
            break;
        }

        VsRecorderViewerList_RemoveMessageWindow(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRanking_FreeProfileLabels(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetOrbitRadii(param0->ring, 0, 0);
        VsRecorderViewerList_FreeBattleRecordings(param0);
        VsRecorderViewerList_LoadBattleRecordings(param0);
        VsRecorderViewerList_ResetWindow(&param0->menuContext.listWindow);
        param0->subState++;
        break;
    case 7:
        TouchScreenActions_Free(v0->unk_188[0]);
        TouchScreenActions_Free(v0->unk_188[1]);
        TouchScreenActions_Free(v0->unk_188[2]);
        VsRecorderViewerRanking_FreeSummaryAndProfile(param0);
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        NetworkIcon_CreateOnSubScreen(1, HEAP_ID_102);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->subState++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->menuContext.themeColor);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->animState);
            VsRecorderViewerMain_SetState(param0, 5);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 3);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 7);
            Heap_Free(v0);

            if (BattleRecording_Exists() == 1) {
                BattleRecording_Free();
            }
        } else {
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->menuContext.themeColor);
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_InitProfileRecord(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 84, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            VsRecorderViewerRanking_DrawMessageText(param0, 102, v0->unk_1FB0);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerRanking_CreateStatWindows(param0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 15);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_ShowRecordPanel(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
        Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 2:
        if (param0->selectedDataIndex == 210) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 94);
            ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_114[1].sprite, 3);
        }

        VsRecorderViewerRanking_RemoveMessageWindow(param0);
        VsRecorderViewerRanking_CreateMessageWindow(param0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_220, param0);
            VsRecorderViewerList_InitSummary(&v0->unk_220, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_220), 3);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_194, param0);
            VsRecorderViewerList_InitProfile(&v0->unk_194, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 80, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 6, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        param0->subState++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            if (v0->unk_10 == 0) {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default: {
        int v1;

        for (v1 = 0; v1 < param0->recordStore.recordCount; v1++) {
            param0->recordStore.records[v1] = &param0->recordStore.recordCopies[v1];
        }
    }
        VsRecorderViewerMain_SetState(param0, 7);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_UpdateProfileList(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    TouchScreenActions_HandleAction(v0->unk_188[1]);
    return 0;
}

static BOOL VsRecorderViewerRanking_State_InitGlobalRecord(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
        Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerRanking_FreeProfileLabels(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 2:
        VsRecorderViewerRanking_CreateBottomPromptSprites(param0);

        if (param0->selectedDataIndex == 210) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 94);
            ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_114[1].sprite, 3);
        }

        VsRecorderViewerRanking_CreateMessageWindow(param0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_InitSummary(&v0->unk_220, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);

            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_220), 3);
        } else {
            VsRecorderViewerList_InitProfile(&v0->unk_194, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 80, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->menuContext.narc, 6, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        param0->subState++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            if (v0->unk_10 == 0) {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default: {
        int v1;

        for (v1 = 0; v1 < param0->recordStore.recordCount; v1++) {
            param0->recordStore.records[v1] = &param0->recordStore.recordCopies[v1];
        }
    }
        VsRecorderViewerMain_SetState(param0, 7);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_InitPlayerSelect(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        TouchScreenActions_Free(v0->unk_188[0]);
        TouchScreenActions_Free(v0->unk_188[1]);
        TouchScreenActions_Free(v0->unk_188[2]);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        VsRecorderViewerRanking_FreeSummaryAndProfile(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_220, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_194, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerRanking_RemoveMessageWindow(param0);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 111);
            ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_114[1].sprite, 1);
            VsRecorderViewerRanking_SetBottomPromptLayout(param0, 1);
            param0->subState++;
        }
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

BOOL (*const sVsRecorderViewerRankingStateTable[])(VsRecorderState *) = {
    VsRecorderViewerRanking_State_Init,
    VsRecorderViewerRanking_State_InitScreen,
    VsRecorderViewerRanking_State_TransferRecord,
    VsRecorderViewerRanking_State_InitRankingView,
    VsRecorderViewerRanking_State_UpdateRankingView,
    VsRecorderViewerRanking_State_ExitRankingView,
    VsRecorderViewerRanking_State_InitTouchHandlers,
    VsRecorderViewerRanking_State_UpdateMainMenu,
    VsRecorderViewerRanking_State_ToggleRecordPanel,
    VsRecorderViewerRanking_State_ExitAndRequestPlayback,
    VsRecorderViewerRanking_State_InitPlayerSelect,
    VsRecorderViewerRanking_State_ViewSelectedRecord,
    VsRecorderViewerRanking_State_UpdateProfileList,
    VsRecorderViewerRanking_State_InitGlobalRecord,
    VsRecorderViewerRanking_State_InitProfileRecord,
    VsRecorderViewerRanking_State_UpdateSummaryList,
    VsRecorderViewerRanking_State_InitOwnRecord,
    VsRecorderViewerRanking_State_UploadSummary,
    VsRecorderViewerRanking_State_TransferSelectedRecord,
    VsRecorderViewerRanking_State_ReenterRanking,
    VsRecorderViewerRanking_State_ShowRecordPanel,
};

static void VsRecorderViewerRanking_DrawProfileName(VsRecorderViewerTextSprite *param0, VsRecorderState *param1, int param2)
{
    String *v0;
    MessageLoader *v1;
    Window v2;
    StringTemplate *v3;
    String *v4;
    String *v5;

    v1 = param1->menuContext.messageLoader;

    if (param1->profiles[param2] == NULL) {
        v0 = MessageLoader_GetNewString(v1, 8);
    } else {
        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v4 = MessageLoader_GetNewString(param1->menuContext.messageLoader, 7);
        v5 = PlayerProfile_GetName(param1->profiles[param2], HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param1, v5);
        v0 = String_Init(255, HEAP_ID_102);

        StringTemplate_SetString(v3, 0, v5, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v4);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    }

    Window_Init(&v2);
    Window_AddToTopLeftCorner(param1->menuContext.bgConfig, &v2, 20, 2, 0, 0);
    Text_AddPrinterWithParamsAndColor(&v2, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(14, 13, 0), NULL);
    FontOAMWindow_UploadToVRAM(param0->fontOAM, param0->fontOAMWindow, &v2, HEAP_ID_102);
    String_Free(v0);
    Window_Remove(&v2);
}

static void VsRecorderViewerRanking_CreateProfileLabels(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    int v1;
    int v2[] = {
        8,
        8,
        8,
        3,
    };
    int v3[] = { 0, 0, 0, 1 };

    VsRecorderViewerMenu_LoadSpriteResourceSetB(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    for (v1 = 0; v1 < 4; v1++) {
        v0->unk_114[v1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);
        VsRecorderViewerMenu_InitLabelOAM(&v0->unk_114[v1], &param0->menuContext, NNS_G2D_VRAM_TYPE_2DSUB);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[v1], &param0->menuContext, v2[v1]);

        if (v1 != 3) {
            VsRecorderViewerRanking_DrawProfileName(&v0->unk_114[v1], param0, v1 + 1);
        }

        ManagedSprite_SetPositionXY(v0->unk_114[v1].sprite, 42 + 8, (25 + (36 * (v1)) + (16 * (5 - 4))) + 64);
        ManagedSprite_SetAnim(v0->unk_114[v1].sprite, v3[v1]);
        FontOAM_SetXY(v0->unk_114[v1].fontOAM, 36, -8);
        FontOAM_SetDrawFlag(v0->unk_114[v1].fontOAM, 1);
    }
}

static void VsRecorderViewerRanking_FreeProfileLabels(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    int v1;

    for (v1 = 0; v1 < 4; v1++) {
        VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_114[v1]);
        Sprite_DeleteAndFreeResources(v0->unk_114[v1].sprite);
    }

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerRanking_FreeBottomPromptSprites(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_114[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_114[1]);
    Sprite_DeleteAndFreeResources(v0->unk_114[0].sprite);
    Sprite_DeleteAndFreeResources(v0->unk_114[1].sprite);
    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerRanking_SetBottomPromptLayout(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_114[1].sprite, 1);
        FontOAM_SetDrawFlag(v0->unk_114[1].fontOAM, 1);
        ManagedSprite_SetPositionXY(v0->unk_114[0].sprite, 32, 232);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_114[1].sprite, 0);
        FontOAM_SetDrawFlag(v0->unk_114[1].fontOAM, 0);
        ManagedSprite_SetPositionXY(v0->unk_114[0].sprite, 80, 232);
    }

    FontOAM_SetXY(v0->unk_114[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_114[1].fontOAM, 36, -8);
}

static void VsRecorderViewerRanking_RemoveHeaderWindows(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerRankingContext *v1 = param0->viewerData;

    for (v0 = 0; v0 < v1->unk_1FB8; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_14[v0]);
        Window_Remove(&v1->unk_14[v0]);
    }

    v1->unk_1FB8 = 0;
}

static void VsRecorderViewerRanking_RemoveMessageWindows(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerRankingContext *v1 = param0->viewerData;

    for (v0 = 0; v0 < v1->unk_1FB4; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_94[v0]);
        Window_Remove(&v1->unk_94[v0]);
    }

    v1->unk_1FB4 = 0;
}

static BOOL VsRecorderViewerRanking_State_Init(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerRankingContext));

    memset(v0, 0, sizeof(VsRecorderViewerRankingContext));

    param0->viewerData = v0;

    if (param0->selectedDataIndex == 300) {
        v0->unk_0C = 0;
    } else if (param0->selectedDataIndex == 301) {
        v0->unk_0C = 1;
    } else if (param0->selectedDataIndex == 200) {
        v0->unk_0C = 2;
    }

    Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
    Bg_ClearTilemap(param0->menuContext.bgConfig, 3);
    Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
    Bg_ClearTilemap(param0->menuContext.bgConfig, 7);
    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerRanking_State_InitScreen(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 1:
        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);
        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 0);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderRing_SetVisible(param0->ring, 0);
        param0->subState++;
        break;
    case 2:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_HideAndFreeMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRanking_CreateBottomPromptSprites(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->subState++;
        break;
    default:
        if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
            VsRecorderViewerMain_SetState(param0, 19);
        } else {
            VsRecorderViewerMain_SetState(param0, 2);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_TransferRecord(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_SetupRing(param0, param0->ring, 128, 96);
        VsRecorderRing_SetVisible(param0->ring, 1);
        VsRecorderRing_SetOrbitRadii(param0->ring, 24, 24);

        if ((param0->selectedDataIndex == 300) || (param0->selectedDataIndex == 301)) {
            VsRecorderViewerList_OpenMainMessage(param0, 279);
        } else {
            VsRecorderViewerList_OpenMainMessage(param0, 292);
        }

        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->subState++;
        break;
    case 1:
        if (param0->selectedDataIndex == 300) {
            v0->unk_0C = 0;
            if (GlobalTerminalTransfer_UploadRecordAlt(VsRecorderViewerTransfer_GetTransfer(param0)) == 1) {
                param0->subState++;
            }
        } else if (param0->selectedDataIndex == 301) {
            v0->unk_0C = 1;
            if (GlobalTerminalTransfer_UploadRecordAlt2(VsRecorderViewerTransfer_GetTransfer(param0)) == 1) {
                param0->subState++;
            }
        } else if (param0->selectedDataIndex == 200) {
            v0->unk_0C = 2;
            if (VsRecorder_CheckFirstArrivalBattlePark(param0) == 1) {
                if (GlobalTerminalTransfer_UploadEmptyRecord(VsRecorderViewerTransfer_GetTransfer(param0)) == 1) {
                    param0->subState++;
                }
            } else {
                if (GlobalTerminalTransfer_UploadRecordDefault(VsRecorderViewerTransfer_GetTransfer(param0)) == 1) {
                    param0->subState++;
                }
            }
        } else {
            GF_ASSERT(FALSE);
        }

        break;
    case 2:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 7, v1->index, v1->category);
            param0->subState++;
        } else {
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);

            if (param0->recordStore.recordCount == 0) {
                VsRecorderViewerList_OpenMessage(param0, 5, 0, 0);

                if (v0->unk_0C == 2) {
                    param0->menuContext.subContext.messageIndex = 118;
                } else {
                    param0->menuContext.subContext.messageIndex = 300;
                }

                VsRecorderRing_SetVisible(param0->ring, 0);
                param0->subState++;
            } else {
                param0->subState = 0xFF;
            }
        }

        break;
    case 3:
        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetOrbitRadii(param0->ring, 0, 0);
        param0->subState++;
        break;
    case 4:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 5:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRanking_FreeBottomPromptSprites(param0);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        NetworkIcon_CreateOnSubScreen(1, HEAP_ID_102);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->subState++;
        break;
    case 6:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->menuContext.themeColor);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->animState);
            VsRecorderViewerMain_SetState(param0, 5);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 2);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 6);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 3);
            Bg_ClearTilemap(param0->menuContext.bgConfig, 7);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->menuContext.themeColor);
            PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        }

        break;
    default:
        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetOrbitRadii(param0->ring, 0, 0);
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static void VsRecorderViewerRanking_CreateHeaderWindows(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    int v1 = 0;
    int v2 = 32;
    String *v3;
    Window *v4;
    int v5[] = { 97, 98, 123 };

    v4 = &v0->unk_14[0];

    Window_Init(v4);
    Window_Add(param0->menuContext.bgConfig, v4, 2, 3, 3, 20, 4, 14, v2);
    Window_FillTilemap(v4, 0x0);

    v3 = MessageLoader_GetNewString(param0->menuContext.messageLoader, v5[v0->unk_0C]);

    Text_AddPrinterWithParamsAndColor(v4, FONT_SYSTEM, v3, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v4);
    String_Free(v3);

    v2 = 256;
    v4 = &v0->unk_94[0];

    Window_Init(v4);
    Window_Add(param0->menuContext.bgConfig, v4, 6, 11, 6, 10, 4, 14, v2);
    Window_FillTilemap(v4, 0x0);

    v3 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 95);

    {
        u32 v6 = (80 - Font_CalcMaxLineWidth(FONT_SYSTEM, v3, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(v4, FONT_SYSTEM, v3, v6, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(v4);
    String_Free(v3);

    v0->unk_1FB4 = 1;
    v0->unk_1FB8 = 1;
}

static BOOL VsRecorderViewerRanking_State_InitRankingView(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        if (BattleRecording_Exists()) {
            BattleRecording_Free();
        }

        v0->unk_1FDC = sVsRecorderViewerRankingWindowConfig;
        v0->unk_1FDC.entries = NULL;
        v0->unk_1FDC.entryCount = param0->recordStore.recordCount;

        VsRecorderViewerList_LoadIconResources(param0);

        v0->unk_2008.narc = VsRecorderViewerList_OpenIconNarc(102);
        v0->unk_2008.spriteIndex = 500;

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_LoadBgTilemap(param0, 4, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 7, 7);

        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);

        VsRecorderViewerRanking_SetBottomPromptLayout(param0, 1);
        VsRecorderViewerRanking_CreateHeaderWindows(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitScrollBar(&param0->menuContext.scrollBar, param0);
        VsRecorderViewerList_InitRecordWindow(&param0->menuContext.listWindow, param0, NULL, &v0->unk_1FDC);

        param0->menuContext.listWindow.twoColumn = 1;

        VsRecorderViewerList_UpdateScrollBarVisibility(&param0->menuContext.scrollBar, &param0->menuContext.listWindow);
        VsRecorderViewerList_LoadArrowSprites(&param0->menuContext.listWindow, param0, 1);
        VsRecorderViewerList_SetArrowSpritesPosition(&param0->menuContext.listWindow, 64, 184);
        VsRecorderViewerList_UpdateSpeciesWindow(&param0->menuContext.listWindow, param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRanking_BuildRankingIconGrid(param0);
        VsRecorderViewerRanking_SetIconGridVisible(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            VsRecorderViewerRanking_SetIconGridVisible(param0, 1);
            VsRecorderViewerList_SetupRing(param0, param0->ring, 16, 76 + (param0->menuContext.listWindow.scrollState.scroll * 24));
            VsRecorderRing_SetVisible(param0->ring, 1);
            VsRecorderRing_SetOrbitRadii(param0->ring, 12, 12);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 4);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_UpdateRankingView(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_HandleScrollBarInput(&param0->menuContext.scrollBar);
        VsRecorderViewerList_MoveSelection(&param0->menuContext.listWindow, param0->menuContext.scrollBar.direction);
        VsRecorderViewerList_UpdateSpeciesWindow(&param0->menuContext.listWindow, param0);
        VsRecorderRing_TrySetTargetPosition(param0->ring, 16, 76 + (param0->menuContext.listWindow.scrollState.scroll * 24));
        VsRecorderViewerRanking_ScrollIconGrid(param0);

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRankingIconButtonRects[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            if (param0->recordStore.records[param0->menuContext.listWindow.scrollState.selection] != NULL) {
                v0->unk_1FBC = 6;
                v0->unk_10 = 0;
                param0->subState++;
            }
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRankingBackButtonRects[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            v0->unk_1FBC = 5;
            param0->subState++;
        }

        break;
    case 1:
        VsRecorderViewerList_FreeScrollBar(&param0->menuContext.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->menuContext.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->menuContext.listWindow, param0);
        VsRecorderViewerList_CloseIconNarc(v0->unk_2008.narc);
        VsRecorderViewerRanking_FreeIconGridSprites(param0);
        VsRecorderViewerList_FreeIconResources(param0);
        VsRecorderViewerRanking_RemoveHeaderWindows(param0);
        VsRecorderViewerRanking_RemoveMessageWindows(param0);

        VsRecorderRing_SetVisible(param0->ring, 0);
        VsRecorderRing_SetOrbitRadii(param0->ring, 0, 0);

        if (v0->unk_1FBC == 5) {
            VsRecorderViewerList_ResetScrollBar(&param0->menuContext.scrollBar);
            VsRecorderViewerList_ResetWindow(&param0->menuContext.listWindow);
            v0->unk_2008.lastScroll = 0;
        }

        param0->subState++;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerRanking_SetBottomPromptLayout(param0, 0);

            if (v0->unk_1FBC == 6) {
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 94);
                ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
                ManagedSprite_SetAnim(v0->unk_114[1].sprite, 3);
            }

            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, v0->unk_1FBC);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_ExitRankingView(VsRecorderState *a0)
{
    VsRecorderState *r5 = a0;
    VsRecorderViewerRankingContext *r4 = r5->viewerData;
    switch (r5->subState) {
    case 0:
        VsRecorderViewerRanking_RemoveHeaderWindows(r5);
        VsRecorderViewerRanking_RemoveMessageWindows(r5);
        VsRecorderViewerList_CloseMainMessage(r5);
        r5->subState++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&r4->unk_08, 1);
        if (VsRecorderViewerMenu_StepBlendAlpha(&r4->unk_00, &r4->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(r5, 1);
            VsRecorderViewerRanking_FreeBottomPromptSprites(r5);
            VsRecorderViewerList_SetDrawSuspended(r5, 0);
            r5->subState++;
        }
        PaletteData_BlendMulti(r5->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r4->unk_08, r5->menuContext.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_ResetFadeValue(&r4->unk_08);
        VsRecorderViewerMenu_InitMenu(r5);
        NetworkIcon_CreateOnSubScreen(1, 0x66);
        VsRecorderViewerList_StartNetworkTask(r5, 1);
        r5->subState++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(r5) == 0) {
            break;
        }
        if (VsRecorderViewerMenu_StepFadeValue(&r4->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(r5);
            VsRecorderViewerMenu_ResetFadeValue(&r4->unk_08);
            PaletteData_BlendMulti(r5->menuContext.palette, PLTTBUF_MAIN_OBJ, 0xc, 0x10, r5->menuContext.themeColor);
            VsRecorderViewerMain_AdvanceState(r5, 1, 1, r5->animState);
            VsRecorderViewerMain_SetState(r5, 5);
            Bg_ClearTilemap(r5->menuContext.bgConfig, 2);
            Bg_ClearTilemap(r5->menuContext.bgConfig, 6);
            Bg_ClearTilemap(r5->menuContext.bgConfig, 3);
            Bg_ClearTilemap(r5->menuContext.bgConfig, 7);
            Heap_Free(r4);
        } else {
            PaletteData_BlendMulti(r5->menuContext.palette, PLTTBUF_SUB_BG, 2, r4->unk_08, r5->menuContext.themeColor);
            PaletteData_BlendMulti(r5->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r4->unk_08, r5->menuContext.themeColor);
        }
        break;
    }
    return FALSE;
}

static BOOL VsRecorderViewerRanking_State_InitTouchHandlers(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerRanking_LoadProfileAndSummary(param0);
        v0->unk_188[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingMainButtonRects, NELEMS(sVsRecorderViewerRankingMainButtonRects), VsRecorderViewerRanking_HandleMainButtonTouch, param0, HEAP_ID_102);
        v0->unk_188[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingProfileButtonRects, NELEMS(sVsRecorderViewerRankingProfileButtonRects), VsRecorderViewerRanking_HandleProfileTouch, param0, HEAP_ID_102);
        v0->unk_188[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingSummaryButtonRects, NELEMS(sVsRecorderViewerRankingSummaryButtonRects), VsRecorderViewerRanking_HandleSummaryListTouch, param0, HEAP_ID_102);
        param0->subState++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_220, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_220), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 1);
            VsRecorderViewerRanking_CreateMessageWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 7);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_UpdateMainMenu(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    TouchScreenActions_HandleAction(v0->unk_188[0]);
    return 0;
}

static BOOL VsRecorderViewerRanking_State_ToggleRecordPanel(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_220, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_194, param0);
        }
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->subState++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 1)) {
            param0->subState++;
        }

        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_InitProfile(&v0->unk_194, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, 80, 3);
        } else {
            VsRecorderViewerList_InitSummary(&v0->unk_220, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_220), 3);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->subState++;
        break;
    case 3:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            if (v0->unk_10 == 0) {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_194, 1);
            } else {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        break;
    default:
        v0->unk_10 ^= 1;
        VsRecorderViewerRanking_SetMessageWindowText(param0, 121 + v0->unk_10);
        VsRecorderViewerMain_SetState(param0, 7);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_ExitAndRequestPlayback(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_102);
        param0->subState++;
        break;
    case 1:
        if (IsScreenFadeDone() == TRUE) {
            param0->subState++;
        }

        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_10 == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_220, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_194, param0);
        }

        TouchScreenActions_Free(v0->unk_188[0]);
        TouchScreenActions_Free(v0->unk_188[1]);
        TouchScreenActions_Free(v0->unk_188[2]);

        VsRecorderViewerRanking_FreeSummaryAndProfile(param0);
        VsRecorderViewerRanking_RemoveMessageWindow(param0);
        VsRecorderViewerRanking_FreeBottomPromptSpritesAndCleanup(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenuWithExtraEntry(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerMain_SetPendingSelection(param0, *(param0->animState));

        VsRecorder_SetPlaybackRequest(param0->playbackRequest, 1, 0);

        param0->subState++;
        break;
    default:
        Heap_Free(v0);
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRanking_State_ReenterRanking(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    switch (param0->subState) {
    case 0:
        VsRecorderViewerList_SetBgPriorities();
        VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
        {
            int v1;

            for (v1 = 0; v1 < param0->recordStore.recordCount; v1++) {
                param0->recordStore.records[v1] = &param0->recordStore.recordCopies[v1];
            }
        }

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->menuContext.narc, 62, param0->menuContext.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);

        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[0], &param0->menuContext, 3);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_114[1], &param0->menuContext, 94);

        ManagedSprite_SetAnim(v0->unk_114[0].sprite, 0);
        ManagedSprite_SetAnim(v0->unk_114[1].sprite, 3);

        v0->unk_2008.spriteIndex = 500;
        v0->unk_2008.lastScroll = param0->menuContext.listWindow.scroll;
        param0->subState++;
        break;
    case 1:
        VsRecorderViewerRanking_LoadProfileAndSummary(param0);
        v0->unk_188[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingMainButtonRects, NELEMS(sVsRecorderViewerRankingMainButtonRects), VsRecorderViewerRanking_HandleMainButtonTouch, param0, HEAP_ID_102);
        v0->unk_188[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingProfileButtonRects, NELEMS(sVsRecorderViewerRankingProfileButtonRects), VsRecorderViewerRanking_HandleProfileTouch, param0, HEAP_ID_102);
        v0->unk_188[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingSummaryButtonRects, NELEMS(sVsRecorderViewerRankingSummaryButtonRects), VsRecorderViewerRanking_HandleSummaryListTouch, param0, HEAP_ID_102);
        param0->subState++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_220, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_220), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->subState++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_220, 1);
            VsRecorderViewerRanking_CreateMessageWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->subState++;
        }

        PaletteData_BlendMulti(param0->menuContext.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->menuContext.themeColor);
        break;
    case 4:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_102);
        param0->subState++;
        break;
    case 5:
        if (IsScreenFadeDone() == TRUE) {
            param0->subState++;
        }

        break;
    default:
        param0->menu.mainEntryCount += 1;
        VsRecorderViewerMain_ResetSelection(param0);
        VsRecorderViewerMain_SetState(param0, 7);
        break;
    }

    return 0;
}

static void VsRecorderViewerRanking_DrawMessageWithPlayerName(VsRecorderState *param0, int param1, BOOL param2)
{
    String *v0;
    Window *v1 = &param0->window;
    VsRecorderViewerRankingContext *v2 = param0->viewerData;

    VsRecorderViewerMenu_LoadBgPanel(param0, 2, param2);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    Window_Init(v1);
    Window_Add(param0->menuContext.bgConfig, v1, 2, 1, 19, 30, 4, 14, 300);

    if (param1 == 100) {
        StringTemplate *v3;
        String *v4;
        String *v5;
        PlayerProfile *v6 = v2->unk_194.profile;

        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v4 = PlayerProfile_GetName(v6, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v4);
        v5 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);
        StringTemplate_SetString(v3, 0, v4, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v5);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    } else {
        v0 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);
    }

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static BOOL VsRecorderViewerRanking_State_ViewSelectedRecord(VsRecorderState *a0)
{
    VsRecorderState *r4 = a0;
    VsRecorderViewerRankingContext *r5 = r4->viewerData;
    if (VsRecorderViewerList_HasRecordingValue(r4, BattleRecording_GetSummaryValue(BattleRecording_GetSummary(), 4, 0))) {
        switch (r4->subState) {
        case 0:
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            if (r5->unk_10 == 0) {
                VsRecorderViewerList_FreeSummary(&r5->unk_220, r4);
            } else {
                VsRecorderViewerList_FreeProfile(&r5->unk_194, r4);
            }
            VsRecorderViewerRanking_RemoveMessageWindow(r4);
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            VsRecorderViewerRanking_FreeBottomPromptSpritesAndCleanup(r4);
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            GXLayers_EngineAToggleLayers(4, 0);
            GXLayers_EngineBToggleLayers(4, 0);
            r4->subState++;
            break;
        case 1:
            VsRecorderViewerMenu_StepFadeValue(&r5->unk_08, 1);
            if (VsRecorderViewerMenu_StepBlendAlpha(&r5->unk_00, &r5->unk_04, 1, 0)) {
                VsRecorderViewerList_SetDrawSuspended(r4, 1);
                VsRecorderViewerRanking_CreateProfileLabels(r4);
                VsRecorderViewerList_SetDrawSuspended(r4, 0);
                Bg_ClearTilemap(r4->menuContext.bgConfig, 3);
                Bg_ClearTilemap(r4->menuContext.bgConfig, 7);
                r4->subState++;
            }
            PaletteData_BlendMulti(r4->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r5->unk_08, r4->menuContext.themeColor);
            break;
        case 2:
            VsRecorderViewerList_OpenMainMessage(r4, 0x115);
            r4->subState++;
            break;
        case 3:
            if (!TouchScreen_Tapped()) {
                break;
            }
            VsRecorderViewerList_CloseMainMessage(r4);
            Bg_ClearTilemap(r4->menuContext.bgConfig, 2);
            Bg_ClearTilemap(r4->menuContext.bgConfig, 6);
            GXLayers_EngineBToggleLayers(4, 0);
            GXLayers_EngineAToggleLayers(4, 0);
            r4->subState++;
            break;
        case 4:
            VsRecorderViewerMenu_StepFadeValue(&r5->unk_08, 1);
            if (VsRecorderViewerMenu_StepBlendAlpha(&r5->unk_00, &r5->unk_04, 1, 0)) {
                VsRecorderViewerList_SetDrawSuspended(r4, 1);
                VsRecorderViewerRanking_FreeProfileLabels(r4);
                VsRecorderViewerList_SetDrawSuspended(r4, 0);
                r4->subState++;
            }
            PaletteData_BlendMulti(r4->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r5->unk_08, r4->menuContext.themeColor);
            break;
        case 5:
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            VsRecorderViewerRanking_CreateBottomPromptSprites(r4);
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            if (r4->selectedDataIndex == 0xd2) {
                VsRecorderViewerMenu_SetLabelOAMText(&r5->unk_114[0], &r4->menuContext, 3);
                VsRecorderViewerMenu_SetLabelOAMText(&r5->unk_114[1], &r4->menuContext, 0x5e);
                ManagedSprite_SetAnim(r5->unk_114[0].sprite, 0);
                ManagedSprite_SetAnim(r5->unk_114[1].sprite, 3);
            }
            VsRecorderViewerRanking_CreateMessageWindow(r4);
            Graphics_LoadTilesToBgLayerFromOpenNARC(r4->menuContext.narc, 0x3e, r4->menuContext.bgConfig, 3, 0, 0, 0, 0x66);
            Graphics_LoadTilesToBgLayerFromOpenNARC(r4->menuContext.narc, 0x3e, r4->menuContext.bgConfig, 7, 0, 0, 0, 0x66);
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            if (r5->unk_10 == 0) {
                VsRecorderViewerList_InitSummary(&r5->unk_220, r4);
                VsRecorderViewerList_SetSummarySpritesVisible(&r5->unk_220, 0);
                VsRecorderViewerList_LoadBgTilemap(r4, VsRecorderViewerList_GetSummaryResultMessageID(&r5->unk_220), 3);
            } else {
                VsRecorderViewerList_InitProfile(&r5->unk_194, r4);
                VsRecorderViewerList_SetProfileSpritesVisible(&r5->unk_194, 0);
                Graphics_LoadTilemapToBgLayerFromOpenNARC(r4->menuContext.narc, 0x50, r4->menuContext.bgConfig, 3, 0, 0, 0, 0x66);
            }
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(r4->menuContext.narc, 6, r4->menuContext.bgConfig, 7, 0, 0, 0, 0x66);
            r4->subState++;
            break;
        case 6:
            VsRecorderViewerMenu_StepFadeValue(&r5->unk_08, 0);
            if (VsRecorderViewerMenu_StepBlendAlpha(&r5->unk_00, &r5->unk_04, 0, 0)) {
                if (r5->unk_10 == 0) {
                    VsRecorderViewerList_SetSummarySpritesVisible(&r5->unk_220, 1);
                } else {
                    VsRecorderViewerList_SetProfileSpritesVisible(&r5->unk_194, 1);
                }
                GXLayers_EngineBToggleLayers(4, 1);
                GXLayers_EngineAToggleLayers(4, 1);
                r4->subState++;
            }
            PaletteData_BlendMulti(r4->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r5->unk_08, r4->menuContext.themeColor);
            break;
        default:
            for (int i = 0; i < r4->recordStore.recordCount; i++) {
                r4->recordStore.records[i] = &r4->recordStore.recordCopies[i];
            }
            VsRecorderViewerMain_SetState(r4, 7);
            break;
        }
    } else {
        switch (r4->subState) {
        case 0:
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            if (r5->unk_10 == 0) {
                VsRecorderViewerList_FreeSummary(&r5->unk_220, r4);
            } else {
                VsRecorderViewerList_FreeProfile(&r5->unk_194, r4);
            }
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            VsRecorderViewerList_SetDrawSuspended(r4, 1);
            VsRecorderViewerRanking_FreeBottomPromptSpritesAndCleanup(r4);
            VsRecorderViewerList_SetDrawSuspended(r4, 0);
            VsRecorderViewerRanking_RemoveMessageWindow(r4);
            GXLayers_EngineAToggleLayers(4, 0);
            GXLayers_EngineBToggleLayers(4, 0);
            r4->subState++;
            break;
        case 1:
            VsRecorderViewerMenu_StepFadeValue(&r5->unk_08, 1);
            if (VsRecorderViewerMenu_StepBlendAlpha(&r5->unk_00, &r5->unk_04, 1, 0)) {
                VsRecorderViewerList_SetDrawSuspended(r4, 1);
                VsRecorderViewerRanking_CreateProfileLabels(r4);
                VsRecorderViewerList_SetDrawSuspended(r4, 0);
                Bg_ClearTilemap(r4->menuContext.bgConfig, 3);
                Bg_ClearTilemap(r4->menuContext.bgConfig, 7);
                r4->subState++;
            }
            PaletteData_BlendMulti(r4->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r5->unk_08, r4->menuContext.themeColor);
            break;
        case 2:
            VsRecorderViewerMenu_StepFadeValue(&r5->unk_08, 0);
            if (VsRecorderViewerMenu_StepBlendAlpha(&r5->unk_00, &r5->unk_04, 0, 1)) {
                VsRecorderViewerRanking_DrawMessageWithPlayerName(r4, 0x64, 0);
                r4->subState++;
            }
            PaletteData_BlendMulti(r4->menuContext.palette, PLTTBUF_SUB_OBJ, 0xc, r5->unk_08, r4->menuContext.themeColor);
            break;
        default:
            VsRecorderViewerMain_SetState(r4, 0xc);
            break;
        }
    }
    return FALSE;
}

static void VsRecorderViewerRanking_RemoveMessageWindow(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    Window_ClearAndCopyToVRAM(&v0->unk_94[0]);
    Window_Remove(&v0->unk_94[0]);
}

static void VsRecorderViewerRanking_SetMessageWindowText(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_94[0];
    Window_FillTilemap(v1, 0x0);
    v2 = MessageLoader_GetNewString(param0->menuContext.messageLoader, param1);
    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerRanking_CreateMessageWindow(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    Window *v1;
    int v2 = 1;

    v1 = &v0->unk_94[0];

    Window_Init(v1);
    Window_Add(param0->menuContext.bgConfig, v1, 6, 8, 3, 16, 2, 14, v2);
    VsRecorderViewerRanking_SetMessageWindowText(param0, 121 + v0->unk_10);
}

static void VsRecorderViewerRanking_CreateStatWindows(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;
    Window *v1;
    String *v2;
    int v3 = 1;
    int v4;

    v1 = &v0->unk_94[0];

    Window_Init(v1);
    Window_Add(param0->menuContext.bgConfig, v1, 6, 4, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 130);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);

    v3 += (10 * 2);
    v1 = &v0->unk_94[1];

    Window_Init(v1);
    Window_Add(param0->menuContext.bgConfig, v1, 6, 18, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->menuContext.messageLoader, 131);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerRanking_RemoveStatWindows(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    Window_ClearAndCopyToVRAM(&v0->unk_94[0]);
    Window_Remove(&v0->unk_94[0]);
    Window_ClearAndCopyToVRAM(&v0->unk_94[1]);
    Window_Remove(&v0->unk_94[1]);
}

static void VsRecorderViewerRanking_HandleMainButtonTouch(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRankingContext *v1 = v0->viewerData;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 8);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);

        if (BattleRecording_Exists()) {
            VsRecorderViewerMain_SetState(v0, 9);
        } else {
            v1->unk_1FBC = 9;
            VsRecorderViewerMain_SetState(v0, 18);
        }
        break;
    case 2:
        VsRecorderViewerList_PlayRingAnim(v0);

        if (BattleRecording_Exists()) {
            VsRecorderViewerMain_SetState(v0, 11);
        } else {
            v1->unk_1FBC = 11;
            VsRecorderViewerMain_SetState(v0, 18);
        }
        break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 10);
        break;
    }
}

static void VsRecorderViewerRanking_HandleProfileTouch(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRankingContext *v1 = v0->viewerData;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
    case 1:
    case 2:
        v1->unk_1FB0 = param0 + 1;

        if (v0->profiles[v1->unk_1FB0] != NULL) {
            VsRecorderViewerMain_SetState(v0, 14);
        } else {
            VsRecorderViewerMain_SetState(v0, 17);
        }

        VsRecorderViewerList_PlayRingAnim(v0);
        break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerList_RemoveMessageWindow(v0);
        VsRecorderViewerMain_SetState(v0, 13);
        break;
    }
}

static void VsRecorderViewerRanking_HandleSummaryListTouch(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRankingContext *v1 = v0->viewerData;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerRanking_RemoveStatWindows(v0);
        VsRecorderViewerMain_SetState(v0, 17);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 16);
        break;
    }
}

static void VsRecorderViewerRanking_LoadProfileAndSummary(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    v0->unk_194.profile = PlayerProfile_New(HEAP_ID_102);
    GlobalTerminal_DeserializePlayerProfile(&param0->recordStore.records[param0->menuContext.listWindow.scrollState.selection]->profile, v0->unk_194.profile);
    v0->unk_220.profile = v0->unk_194.profile;
    v0->unk_220.summary = BattleRecording_NewSummary(HEAP_ID_102);
    MI_CpuCopy8(&param0->recordStore.records[param0->menuContext.listWindow.scrollState.selection]->data, v0->unk_220.summary, sizeof(GlobalTerminalRecordAltData));
}

static void VsRecorderViewerRanking_BuildRankingIconGrid(VsRecorderState *param0)
{
    int v0, v1;
    int v2 = 0;
    VsRecorderViewerRankingContext *v3 = param0->viewerData;
    int v4;
    int v5;
    int v6;
    int v7 = param0->menuContext.listWindow.scroll;
    int v8[][6] = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
    };
    int v9[6] = { 0, 0, 0, 0, 0, 0 };
    int v10[6] = { 0, 0, 0, 0, 0, 0 };
    int v11 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->recordStore.records[v7 + v0] == NULL) {
            continue;
        }

        if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->recordStore.records[v7 + v0]->data)) {
            v11 = 1;
        } else {
            v11 = 0;
        }

        {
            int v12, v13;
            int v14 = 0;

            for (v12 = 0; v12 < 6; v12++) {
                v9[v12] = 0;
                v10[v12] = 0;
            }

            for (v12 = 0; v12 < 3; v12++) {
                v4 = param0->recordStore.records[v7 + v0]->data.species[v8[v11][v12]];

                if (v4 == 0) {
                    continue;
                }

                v9[v14] = v4;
                v10[v14] = param0->recordStore.records[v7 + v0]->data.forms[v8[v11][v12]];
                v14++;
            }

            if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->recordStore.records[v7 + v0]->data)) {
                v14 = 3;
            }

            for (v12 = 3; v12 < 6; v12++) {
                v4 = param0->recordStore.records[v7 + v0]->data.species[v8[v11][v12]];

                if (v4 == 0) {
                    continue;
                }

                v9[v14] = v4;
                v10[v14] = param0->recordStore.records[v7 + v0]->data.forms[v8[v11][v12]];
                v14++;
            }
        }

        for (v1 = 0; v1 < 6; v1++) {
            v4 = v9[v1];
            v5 = v10[v1];
            v6 = 0;

            v3->unk_2008.cells[v0][v1].index = v3->unk_2008.spriteIndex;
            v3->unk_2008.cells[v0][v1].sprite = VsRecorderViewerList_NewPokemonIconSprite(param0, v3->unk_2008.narc, v3->unk_2008.cells[v0][v1].index, v4, v5, v6);

            if (v3->unk_2008.cells[v0][v1].sprite) {
                ManagedSprite_SetPriority(v3->unk_2008.cells[v0][v1].sprite, 6 - v1);
            }

            v3->unk_2008.spriteIndex++;
        }
    }

    VsRecorderViewerRanking_LayoutIconGrid(param0);
}

static void VsRecorderViewerRanking_SetIconGridVisible(VsRecorderState *param0, BOOL param1)
{
    int v0, v1;
    VsRecorderViewerRankingContext *v2 = param0->viewerData;

    for (v0 = 0; v0 < 5; v0++) {
        for (v1 = 0; v1 < 6; v1++) {
            if (v2->unk_2008.cells[v0][v1].sprite) {
                ManagedSprite_SetDrawFlag(v2->unk_2008.cells[v0][v1].sprite, param1);
            }
        }
    }
}

static void VsRecorderViewerRanking_FreeIconGridSprites(VsRecorderState *param0)
{
    int v0, v1;
    VsRecorderViewerRankingContext *v2 = param0->viewerData;

    for (v0 = 0; v0 < 5; v0++) {
        for (v1 = 0; v1 < 6; v1++) {
            if (v2->unk_2008.cells[v0][v1].sprite) {
                VsRecorderViewerList_FreePokemonIconSprite(param0, v2->unk_2008.cells[v0][v1].index, v2->unk_2008.cells[v0][v1].sprite);
                v2->unk_2008.cells[v0][v1].sprite = NULL;
            }
        }
    }
}

static void VsRecorderViewerRanking_ScrollIconGrid(VsRecorderState *param0)
{
    int v0, v1;
    int v2 = 0;
    int v3;
    int v4[6] = { 0, 0, 0, 0, 0, 0 };
    VsRecorderViewerRankingContext *v5 = param0->viewerData;

    if (v5->unk_2008.lastScroll == param0->menuContext.listWindow.scroll) {
        return;
    }

    VsRecorderViewerList_SetDrawSuspended(param0, 1);

    if (v5->unk_2008.lastScroll > param0->menuContext.listWindow.scroll) {
        v2 = 4;
    }

    for (v0 = 0; v0 < 6; v0++) {
        if (v5->unk_2008.cells[v2][v0].sprite) {
            VsRecorderViewerList_DeletePokemonIconSprite(param0, v5->unk_2008.cells[v2][v0].index, v5->unk_2008.cells[v2][v0].sprite);
            v4[v0] = v5->unk_2008.cells[v2][v0].index;
            v5->unk_2008.cells[v2][v0].sprite = NULL;
        }
    }

    if (v2) {
        for (v0 = 4; v0 >= 1; v0--) {
            for (v1 = 0; v1 < 6; v1++) {
                v5->unk_2008.cells[v0][v1].sprite = v5->unk_2008.cells[v0 - 1][v1].sprite;
                v5->unk_2008.cells[v0][v1].index = v5->unk_2008.cells[v0 - 1][v1].index;
            }
        }

        v2 = 0;
    } else {
        for (v0 = 1; v0 < 5; v0++) {
            for (v1 = 0; v1 < 6; v1++) {
                v5->unk_2008.cells[v0 - 1][v1].sprite = v5->unk_2008.cells[v0][v1].sprite;
                v5->unk_2008.cells[v0 - 1][v1].index = v5->unk_2008.cells[v0][v1].index;
            }
        }

        v2 = 4;
    }

    {
        int v6;
        int v7;
        int v8;
        int v9 = param0->menuContext.listWindow.scroll + v2;
        int v10[][6] = {
            { 0, 1, 2, 3, 4, 5 },
            { 0, 1, 2, 3, 4, 5 },
        };
        int v11[6] = { 0, 0, 0, 0, 0, 0 };
        int v12[6] = { 0, 0, 0, 0, 0, 0 };
        int v13 = 0;

        if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->recordStore.records[v9]->data)) {
            v13 = 1;
        }

        {
            int v14, v15;
            int v16 = 0;

            for (v14 = 0; v14 < 6; v14++) {
                v11[v14] = 0;
                v12[v14] = 0;
            }

            for (v14 = 0; v14 < 3; v14++) {
                v6 = param0->recordStore.records[v9]->data.species[v10[v13][v14]];

                if (v6 == 0) {
                    continue;
                }

                v11[v16] = v6;
                v12[v16] = param0->recordStore.records[v9]->data.forms[v10[v13][v14]];
                v16++;
            }

            if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->recordStore.records[v9]->data)) {
                v16 = 3;
            }

            for (v14 = 3; v14 < 6; v14++) {
                v6 = param0->recordStore.records[v9]->data.species[v10[v13][v14]];

                if (v6 == 0) {
                    continue;
                }

                v11[v16] = v6;
                v12[v16] = param0->recordStore.records[v9]->data.forms[v10[v13][v14]];
                v16++;
            }
        }

        for (v1 = 0; v1 < 6; v1++) {
            v6 = v11[v1];
            v7 = v12[v1];
            v8 = 0;
            v5->unk_2008.cells[v2][v1].index = v5->unk_2008.spriteIndex;
            v5->unk_2008.cells[v2][v1].sprite = VsRecorderViewerList_NewPokemonIconSprite(param0, v5->unk_2008.narc, v5->unk_2008.cells[v2][v1].index, v6, v7, v8);

            if (v5->unk_2008.cells[v2][v1].sprite) {
                ManagedSprite_SetPriority(v5->unk_2008.cells[v2][v1].sprite, 6 - v1);
            }

            v5->unk_2008.spriteIndex++;
        }
    }

    VsRecorderViewerRanking_LayoutIconGrid(param0);
    v5->unk_2008.lastScroll = param0->menuContext.listWindow.scroll;

    for (v0 = 0; v0 < 6; v0++) {
        if (v4[v0] == 0) {
            continue;
        }

        SpriteManager_UnloadCharObjById(param0->menuContext.spriteManager, 100000 + v4[v0]);
    }

    VsRecorderViewerList_SetDrawSuspended(param0, 0);
}

static void VsRecorderViewerRanking_FreeBottomPromptSpritesAndCleanup(VsRecorderState *param0)
{
    VsRecorderViewerRankingContext *v0 = param0->viewerData;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_114[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_114[1]);
    Sprite_DeleteAndFreeResources(v0->unk_114[0].sprite);
    Sprite_DeleteAndFreeResources(v0->unk_114[1].sprite);
    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}
