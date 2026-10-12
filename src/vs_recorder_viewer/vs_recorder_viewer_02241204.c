#include "vs_recorder_viewer/vs_recorder_viewer_02241204.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_vs_recorder_state.h"

#include "global_terminal/global_terminal_0222AE60.h"
#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"
#include "global_terminal/struct_global_terminal_0222BED8_sub1.h"
#include "vs_recorder_viewer/const_vs_recorder_viewer_022491F0.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233F74.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02249380.h"

#include "bg_window.h"
#include "enums.h"
#include "font.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "network_icon.h"
#include "palette.h"
#include "pokedex.h"
#include "save_player.h"
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
    VsRecorderViewerTextSprite unk_10[4];
    VsRecorderViewerProfilePanel unk_80;
    VsRecorderViewerSummaryPanel unk_10C;
    int unk_1C8;
    int unk_1CC;
    PlayerProfile *unk_1D0;
    VsRecorderViewerIdEntryState unk_1D4;
    VsRecorderViewerIdEntryConfig *unk_4AC;
    u64 unk_4B0;
    BOOL unk_4B8;
    GlobalTerminalRecordAlt *unk_4BC;
    u16 unk_4C0;
    u8 unk_4C2;
    u8 unk_4C3;
    u8 unk_4C4;
    u8 unk_4C5;
    u8 unk_4C6[2];
    VsRecorderViewerRankingMessageBox unk_4C8;
    VsRecorderViewerListEntry *unk_4DC;
    VsRecorderViewerListConfig unk_4E0;
    VsRecorderViewerRankingIconGrid unk_50C;
    TouchScreenActions *unk_608[3];
    Window unk_614[12];
    Window unk_6D4[12];
    int unk_794;
    int unk_798;
    u8 unk_79C;
} VsRecorderViewerRecordContext;

static void VsRecorderViewerRecord_LayoutBoxSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_CreateBoxSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_SetBoxSpritesVisible(VsRecorderState *param0, BOOL param1);
static void VsRecorderViewerRecord_FreeBoxSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_ScrollBoxList(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_HasAnySelection(VsRecorderState *param0);
static void VsRecorderViewerRecord_CreateMenuWindows(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_DrawRankLabel(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_DrawSpeciesName(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_DrawLocationName(VsRecorderState *param0, int param1, int param2);
static void VsRecorderViewerRecord_CreateCategoryWindows(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_RemoveMenuWindows(VsRecorderState *param0);
static void VsRecorderViewerRecord_RemoveCategoryWindows(VsRecorderState *param0);
static void VsRecorderViewerRecord_CreateHeaderWindows(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BoxViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BoxViewHandleTouch(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BoxViewExit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BoxViewOptions(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankMenu(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SpeciesMenu(VsRecorderState *param0);
static void VsRecorderViewerRecord_CreatePokedexLetterWindows(VsRecorderState *param0);
static void VsRecorderViewerRecord_RemovePokedexLetterWindows(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_PokedexGridMenu(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SpeciesSelect(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_IsPokedexSectionSeen(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_BuildPokedexSection(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_FreePokedexSection(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_LocationSelect(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SpeciesMenuOpen(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadRecord(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadRecordExit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_PlaybackInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_PlaybackInput(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BoxView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankListInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankListHandleTouch(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankListToggleView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankListExit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RankListCleanup(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingHandleTouch1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingToggle1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingToggle2(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingHandleTouch2(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingToggle3(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_BattleRecordingPlayback(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadId(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_PlaybackViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_Init(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_Setup(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ConfigInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ConfigUpdate(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ConfigExit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ConfigExitCleanup(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadId2(VsRecorderState *param0);
static void VsRecorderViewerRecord_LoadRecordProfile(VsRecorderState *param0);
static void VsRecorderViewerRecord_LoadBoxRecordProfile(VsRecorderState *param0);
static void VsRecorderViewerRecord_FreeRecordProfile(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ProfileViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ProfileViewHandleTouch(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ProfileViewToggle(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ProfileViewExit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ProfileViewCleanup(VsRecorderState *param0);
static void VsRecorderViewerRecord_DrawPlayerName(VsRecorderViewerTextSprite *param0, VsRecorderState *param1, int param2);
static void VsRecorderViewerRecord_DrawHeaderText(VsRecorderState *param0, int param1, BOOL param2);
static void VsRecorderViewerRecord_DrawHeaderTextForProfile(VsRecorderState *param0, int param1, int param2);
static void VsRecorderViewerRecord_CreateSummarySprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_FreeSummarySprites(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryHandleTouch1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryToggle1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryHandleTouch2(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryToggle3(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryPlayback(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RingViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadBattleRecording(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadBattleRecordingExit(VsRecorderState *param0);
static void VsRecorderViewerRecord_RemoveInfoWindow(VsRecorderState *param0);
static void VsRecorderViewerRecord_DrawInfoMessage(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_CreateInfoWindow(VsRecorderState *param0);
static void VsRecorderViewerRecord_CreateDetailWindows(VsRecorderState *param0);
static void VsRecorderViewerRecord_RemoveDetailWindows(VsRecorderState *param0);
static void VsRecorderViewerRecord_TouchHandlerRecordActions(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerProfileSelect(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerBack(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerBoxMenu(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerPokedexGrid(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerRankActions(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerRankProfileSelect(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_TouchHandlerRankBack(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void VsRecorderViewerRecord_SetMenuSpriteVisibility(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_CreateMainScreenSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_FreeMainScreenSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_SetViewToggleSprite(VsRecorderState *param0, int param1);
static void VsRecorderViewerRecord_CreateSubScreenSprites(VsRecorderState *param0);
static void VsRecorderViewerRecord_FreeSubScreenSprites(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ToggleViewState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_CloseView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SpeciesDetailState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_CloseSpeciesDetailState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_PlaybackUploadState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_ReopenBoxViewState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RestoreBoxViewState(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_Exit(VsRecorderState *param0);
void VsRecorderViewerRecord_SetBattleRecordingId(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerRecord_LoadRecordAlt(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerRecord_Noop(void *param0, const VsRecorderViewerTransferStatus *param1);
static BOOL VsRecorderViewerRecord_SummaryView(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryHandleTouch1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryToggle1(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryToggle2(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryDetail(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryHandleTouch2(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryToggle3(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryPlayback(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_SummaryViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_RingViewInit(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadBattleRecording(VsRecorderState *param0);
static BOOL VsRecorderViewerRecord_UploadBattleRecordingExit(VsRecorderState *param0);
static void VsRecorderViewerRecord_DrawRecordId(VsRecorderViewerRecordContext *param0, VsRecorderState *param1);

static u16 sVsRecorderViewerRecord_PokedexSectionOffsets[] = {
    0x0,
    0x57,
    0x88,
    0xBF,
    0xEB,
    0x12F,
    0x168,
    0x1C9,
    0x1E7,
    0x1ED
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsRecordMenu[] = {
    { 0x10, 0x30, 0x40, 0xC8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x80, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsProfileSelect[] = {
    { 0x19, 0x39, 0x32, 0xD2 },
    { 0x3D, 0x5D, 0x32, 0xD2 },
    { 0x61, 0x81, 0x32, 0xD2 },
    { 0x85, 0xA5, 0x32, 0xD2 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsBackButton[] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectBack[] = {
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectPlayback[] = {
    { 0x20, 0x60, 0x50, 0xB0 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsBoxMenu[] = {
    { 0x10, 0x30, 0x28, 0xD8 },
    { 0x38, 0x58, 0x28, 0xD8 },
    { 0x60, 0x80, 0x28, 0xD8 },
    { 0x98, 0xB8, 0x20, 0x80 },
    { 0x98, 0xB8, 0x80, 0xE0 }
};

const TouchScreenRect sVsRecorderViewerRecord_TouchRectsPokedexGrid[9] = {
    { 0x18, 0x30, 0x28, 0x48 },
    { 0x18, 0x30, 0x70, 0x90 },
    { 0x18, 0x30, 0xB8, 0xD8 },
    { 0x38, 0x50, 0x28, 0x48 },
    { 0x38, 0x50, 0x70, 0x90 },
    { 0x38, 0x50, 0xB8, 0xD8 },
    { 0x58, 0x70, 0x28, 0x48 },
    { 0x58, 0x70, 0x70, 0x90 },
    { 0x58, 0x70, 0xB8, 0xD8 }
};

static void VsRecorderViewerRecord_LayoutBoxSprites(VsRecorderState *param0)
{
    const s16 v0[][2] = {
        { 0x68, 0x48 },
        { 0x80, 0x48 },
        { 0x98, 0x48 },
        { 0xB0, 0x48 },
        { 0xC8, 0x48 },
        { 0xE0, 0x48 },
        { 0x68, 0x60 },
        { 0x80, 0x60 },
        { 0x98, 0x60 },
        { 0xB0, 0x60 },
        { 0xC8, 0x60 },
        { 0xE0, 0x60 },
        { 0x68, 0x78 },
        { 0x80, 0x78 },
        { 0x98, 0x78 },
        { 0xB0, 0x78 },
        { 0xC8, 0x78 },
        { 0xE0, 0x78 },
        { 0x68, 0x90 },
        { 0x80, 0x90 },
        { 0x98, 0x90 },
        { 0xB0, 0x90 },
        { 0xC8, 0x90 },
        { 0xE0, 0x90 },
        { 0x68, 0xA8 },
        { 0x80, 0xA8 },
        { 0x98, 0xA8 },
        { 0xB0, 0xA8 },
        { 0xC8, 0xA8 },
        { 0xE0, 0xA8 },
    };
    int v1, v2;
    VsRecorderViewerRecordContext *v3 = param0->unk_860;

    for (v1 = 0; v1 < 5; v1++) {
        for (v2 = 0; v2 < 6; v2++) {
            if (v3->unk_50C.cells[v1][v2].sprite) {
                ManagedSprite_SetPositionXY(v3->unk_50C.cells[v1][v2].sprite, v0[(v1 * 6) + v2][0], v0[(v1 * 6) + v2][1]);
            }
        }
    }
}

static void VsRecorderViewerRecord_CreateBoxSprites(VsRecorderState *param0)
{
    int v0, v1;
    int v2 = 0;
    VsRecorderViewerRecordContext *v3 = param0->unk_860;
    int v4[][6] = {
        { 0, 1, 2, 3, 4, 5 },
        { 0, 1, 2, 3, 4, 5 },
    };
    int v5[6] = { 0, 0, 0, 0, 0, 0 };
    int v6[6] = { 0, 0, 0, 0, 0, 0 };
    int v7 = 0;
    int v8;
    int v9;
    int v10;
    int v11 = param0->unk_14.listWindow.scroll;

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->unk_8B4.records[v11 + v0] == NULL) {
            continue;
        }

        if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->unk_8B4.records[v11 + v0]->data)) {
            v7 = 1;
        } else {
            v7 = 0;
        }

        {
            int v12, v13;
            int v14 = 0;

            for (v12 = 0; v12 < 6; v12++) {
                v5[v12] = 0;
                v6[v12] = 0;
            }

            for (v12 = 0; v12 < 3; v12++) {
                v8 = param0->unk_8B4.records[v11 + v0]->data.species[v4[v7][v12]];
                if (v8 == 0) {
                    continue;
                }

                v5[v14] = v8;
                v6[v14] = param0->unk_8B4.records[v11 + v0]->data.forms[v4[v7][v12]];
                v14++;
            }

            if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->unk_8B4.records[v11 + v0]->data)) {
                v14 = 3;
            }

            for (v12 = 3; v12 < 6; v12++) {
                v8 = param0->unk_8B4.records[v11 + v0]->data.species[v4[v7][v12]];

                if (v8 == 0) {
                    continue;
                }

                v5[v14] = v8;
                v6[v14] = param0->unk_8B4.records[v11 + v0]->data.forms[v4[v7][v12]];
                v14++;
            }
        }

        for (v1 = 0; v1 < 6; v1++) {
            v8 = v5[v1];
            v9 = v6[v1];
            v10 = 0;
            v3->unk_50C.cells[v0][v1].index = v3->unk_50C.spriteIndex;
            v3->unk_50C.cells[v0][v1].sprite = VsRecorderViewerList_NewPokemonIconSprite(param0, v3->unk_50C.narc, v3->unk_50C.cells[v0][v1].index, v8, v9, v10);

            if (v3->unk_50C.cells[v0][v1].sprite) {
                ManagedSprite_SetPriority(v3->unk_50C.cells[v0][v1].sprite, 6 - v1);
            }

            v3->unk_50C.spriteIndex++;
        }
    }

    VsRecorderViewerRecord_LayoutBoxSprites(param0);
}

static void VsRecorderViewerRecord_SetBoxSpritesVisible(VsRecorderState *param0, BOOL param1)
{
    int v0, v1;
    VsRecorderViewerRecordContext *v2 = param0->unk_860;

    for (v0 = 0; v0 < 5; v0++) {
        for (v1 = 0; v1 < 6; v1++) {
            if (v2->unk_50C.cells[v0][v1].sprite) {
                ManagedSprite_SetDrawFlag(v2->unk_50C.cells[v0][v1].sprite, param1);
            }
        }
    }
}

static void VsRecorderViewerRecord_FreeBoxSprites(VsRecorderState *param0)
{
    int v0, v1;
    VsRecorderViewerRecordContext *v2 = param0->unk_860;

    VsRecorderViewerList_SetDrawSuspended(param0, 1);

    for (v0 = 0; v0 < 5; v0++) {
        for (v1 = 0; v1 < 6; v1++) {
            if (v2->unk_50C.cells[v0][v1].sprite) {
                VsRecorderViewerList_FreePokemonIconSprite(param0, v2->unk_50C.cells[v0][v1].index, v2->unk_50C.cells[v0][v1].sprite);
                v2->unk_50C.cells[v0][v1].sprite = NULL;
            }
        }
    }

    VsRecorderViewerList_SetDrawSuspended(param0, 0);
}

static void VsRecorderViewerRecord_ScrollBoxList(VsRecorderState *param0)
{
    int v0, v1;
    int v2 = 0;
    int v3;
    int v4[6] = { 0, 0, 0, 0, 0, 0 };
    VsRecorderViewerRecordContext *v5 = param0->unk_860;

    if (v5->unk_50C.lastScroll == param0->unk_14.listWindow.scroll) {
        return;
    }

    VsRecorderViewerList_SetDrawSuspended(param0, 1);

    if (v5->unk_50C.lastScroll > param0->unk_14.listWindow.scroll) {
        v2 = 4;
    }

    for (v0 = 0; v0 < 6; v0++) {
        if (v5->unk_50C.cells[v2][v0].sprite) {
            VsRecorderViewerList_DeletePokemonIconSprite(param0, v5->unk_50C.cells[v2][v0].index, v5->unk_50C.cells[v2][v0].sprite);
            v4[v0] = v5->unk_50C.cells[v2][v0].index;
            v5->unk_50C.cells[v2][v0].sprite = NULL;
        }
    }

    if (v2) {
        for (v0 = 4; v0 >= 1; v0--) {
            for (v1 = 0; v1 < 6; v1++) {
                v5->unk_50C.cells[v0][v1].sprite = v5->unk_50C.cells[v0 - 1][v1].sprite;
                v5->unk_50C.cells[v0][v1].index = v5->unk_50C.cells[v0 - 1][v1].index;
            }
        }

        v2 = 0;
    } else {
        for (v0 = 1; v0 < 5; v0++) {
            for (v1 = 0; v1 < 6; v1++) {
                v5->unk_50C.cells[v0 - 1][v1].sprite = v5->unk_50C.cells[v0][v1].sprite;
                v5->unk_50C.cells[v0 - 1][v1].index = v5->unk_50C.cells[v0][v1].index;
            }
        }

        v2 = 4;
    }

    {
        int v6;
        int v7;
        int v8;
        int v9 = param0->unk_14.listWindow.scroll + v2;
        int v10[][6] = {
            { 0, 1, 2, 3, 4, 5 },
            { 0, 1, 2, 3, 4, 5 },
        };
        int v11[6] = { 0, 0, 0, 0, 0, 0 };
        int v12[6] = { 0, 0, 0, 0, 0, 0 };
        int v13 = 0;

        if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->unk_8B4.records[v9]->data)) {
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
                v6 = param0->unk_8B4.records[v9]->data.species[v10[v13][v14]];

                if (v6 == 0) {
                    continue;
                }

                v11[v16] = v6;
                v12[v16] = param0->unk_8B4.records[v9]->data.forms[v10[v13][v14]];
                v16++;
            }

            if (VsRecorderViewerList_IsSummaryResultSpecial((BattleRecordingSummary *)&param0->unk_8B4.records[v9]->data)) {
                v16 = 3;
            }

            for (v14 = 3; v14 < 6; v14++) {
                v6 = param0->unk_8B4.records[v9]->data.species[v10[v13][v14]];

                if (v6 == 0) {
                    continue;
                }

                v11[v16] = v6;
                v12[v16] = param0->unk_8B4.records[v9]->data.forms[v10[v13][v14]];
                v16++;
            }
        }

        for (v1 = 0; v1 < 6; v1++) {
            v6 = v11[v1];
            v7 = v12[v1];
            v8 = 0;
            v5->unk_50C.cells[v2][v1].index = v5->unk_50C.spriteIndex;
            v5->unk_50C.cells[v2][v1].sprite = VsRecorderViewerList_NewPokemonIconSprite(param0, v5->unk_50C.narc, v5->unk_50C.cells[v2][v1].index, v6, v7, v8);

            if (v5->unk_50C.cells[v2][v1].sprite) {
                ManagedSprite_SetPriority(v5->unk_50C.cells[v2][v1].sprite, 6 - v1);
            }

            v5->unk_50C.spriteIndex++;
        }
    }

    VsRecorderViewerRecord_LayoutBoxSprites(param0);
    v5->unk_50C.lastScroll = param0->unk_14.listWindow.scroll;

    for (v0 = 0; v0 < 6; v0++) {
        if (v4[v0] == 0) {
            continue;
        }

        SpriteManager_UnloadCharObjById(param0->unk_14.spriteManager, 100000 + v4[v0]);
    }

    VsRecorderViewerList_SetDrawSuspended(param0, 0);
}

static BOOL VsRecorderViewerRecord_HasAnySelection(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (v0->unk_4C0 != 0xffff) {
        return 1;
    }

    if (v0->unk_4C2 != 0xff) {
        return 1;
    }

    if ((v0->unk_4C3 != 0xff) || (v0->unk_4C4 != 0xff)) {
        return 1;
    }

    return 0;
}

static void VsRecorderViewerRecord_CreateMenuWindows(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    int v1;
    int v2;
    const int(*v3)[4];
    const int *v4;
    const int v5[][4] = {
        { 4, 3, 15, 2 },
        { 4, 9, 15, 2 },
        { 4, 13, 15, 2 },
        { 5, 5, 20, 4 },
        { 5, 11, 20, 2 },
        { 5, 15, 20, 2 },
    };
    const int v6[] = { 48, 49, 50, 125, 125, 125 };

    switch (param1) {
    case 0:
        v0->unk_794 = 6;
        v2 = 0;
        v3 = v5;
        v4 = v6;
        break;
    case 1:
        break;
    default:
        break;
    }

    {
        int v7;
        int v8 = 0;
        int v9 = 256;
        String *v10;
        Window *v11;

        for (v7 = 0; v7 < v0->unk_794; v7++) {
            v11 = &v0->unk_614[v7];

            Window_Init(v11);
            Window_Add(param0->unk_14.bgConfig, v11, 2, v3[v7][0], v3[v7][1], v3[v7][2], v3[v7][3], 14, v9);
            Window_FillTilemap(v11, 0x0);

            v10 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v4[v7]);
            v9 += v3[v7][2] * v3[v7][3];

            if (v2) {
                v8 = VsRecorderViewerList_CalcCenteredTextX(v11, v10);
            }

            Text_AddPrinterWithParamsAndColor(v11, FONT_SYSTEM, v10, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v11);
            String_Free(v10);
        }
    }
}

static void VsRecorderViewerRecord_DrawRankLabel(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_614[3];
    Window_FillTilemap(v1, 0x0);

    if (param1 == 0xff) {
        v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 125);
    } else {
        if ((param1 == UnkEnum_0202F510_33) || (param1 == UnkEnum_0202F510_34) || (param1 == UnkEnum_0202F510_35) || (param1 == UnkEnum_0202F510_36)) {
            v3 = 165 + (param1 - UnkEnum_0202F510_33);
            v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v3);
        } else {
            v3 = 132 + param1;
            v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v3);
        }
    }

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerRecord_DrawSpeciesName(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    u16 v3[255];

    v1 = &v0->unk_614[4];
    Window_FillTilemap(v1, 0x0);

    if (param1 == 0xffff) {
        v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 125);
    } else {
        v2 = String_Init(255, HEAP_ID_102);
        MessageLoader_GetSpeciesName(param1, 102, v3);
        String_CopyChars(v2, v3);
    }

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerRecord_DrawLocationName(VsRecorderState *param0, int param1, int param2)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    String *v3;
    StringTemplate *v4;

    v1 = &v0->unk_614[5];
    Window_FillTilemap(v1, 0x0);

    if ((param1 == 0xff) && (param2 == 0xff)) {
        v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 125);
    } else {
        v4 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

        if (param2 != 0) {
            v2 = String_Init(255, HEAP_ID_102);
            v3 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 23);
            StringTemplate_SetCityName(v4, 0, param1, param2);
            StringTemplate_Format(v4, v2, v3);
        } else {
            v2 = String_Init(255, HEAP_ID_102);
            v3 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 22);
            StringTemplate_SetCountryName(v4, 0, param1);
            StringTemplate_Format(v4, v2, v3);
        }

        String_Free(v3);
        StringTemplate_Free(v4);
    }

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v2);
}

static void VsRecorderViewerRecord_CreateCategoryWindows(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    int v1;
    int v2;
    const int(*v3)[4];
    const int *v4;
    const int v5[][4] = {
        { 7, 3, 20, 2 },
        { 7, 8, 20, 2 },
        { 7, 13, 20, 2 },
    };
    const int v6[] = { 48, 49, 50 };

    switch (param1) {
    case 0:
        v0->unk_798 = 3;
        v2 = 0;
        v3 = v5;
        v4 = v6;
        break;
    case 1:
        break;
    default:
        break;
    }

    {
        int v7;
        int v8 = 0;
        int v9 = 256;
        String *v10;
        Window *v11;

        for (v7 = 0; v7 < v0->unk_798; v7++) {
            v11 = &v0->unk_6D4[v7];

            Window_Init(v11);
            Window_Add(param0->unk_14.bgConfig, v11, 6, v3[v7][0], v3[v7][1], v3[v7][2], v3[v7][3], 14, v9);
            Window_FillTilemap(v11, 0x0);

            v10 = MessageLoader_GetNewString(param0->unk_14.messageLoader, v4[v7]);
            v9 += v3[v7][2] * v3[v7][3];

            if (v2) {
                v8 = VsRecorderViewerList_CalcCenteredTextX(v11, v10);
            }

            Text_AddPrinterWithParamsAndColor(v11, FONT_SYSTEM, v10, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v11);
            String_Free(v10);
        }
    }
}

static void VsRecorderViewerRecord_RemoveMenuWindows(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerRecordContext *v1 = param0->unk_860;

    for (v0 = 0; v0 < v1->unk_794; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_614[v0]);
        Window_Remove(&v1->unk_614[v0]);
    }

    v1->unk_794 = 0;
}

static void VsRecorderViewerRecord_RemoveCategoryWindows(VsRecorderState *param0)
{
    int v0;
    VsRecorderViewerRecordContext *v1 = param0->unk_860;

    for (v0 = 0; v0 < v1->unk_798; v0++) {
        Window_ClearAndCopyToVRAM(&v1->unk_6D4[v0]);
        Window_Remove(&v1->unk_6D4[v0]);
    }

    v1->unk_798 = 0;
}

static void VsRecorderViewerRecord_CreateHeaderWindows(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    int v1 = 0;
    int v2 = 32;
    String *v3;
    Window *v4;

    v4 = &v0->unk_614[0];
    Window_Init(v4);
    Window_Add(param0->unk_14.bgConfig, v4, 2, 3, 3, 20, 4, 14, v2);
    Window_FillTilemap(v4, 0x0);

    v3 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 126);
    Text_AddPrinterWithParamsAndColor(v4, FONT_SYSTEM, v3, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v4);
    String_Free(v3);

    v2 = 256;
    v4 = &v0->unk_6D4[0];
    Window_Init(v4);
    Window_Add(param0->unk_14.bgConfig, v4, 6, 11, 6, 10, 4, 14, v2);
    Window_FillTilemap(v4, 0x0);
    v3 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 95);

    {
        u32 v5 = (80 - Font_CalcMaxLineWidth(FONT_SYSTEM, v3, 0)) / 2;
        Text_AddPrinterWithParamsAndColor(v4, FONT_SYSTEM, v3, v5, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(v4);
    String_Free(v3);

    v0->unk_798 = 1;
    v0->unk_794 = 1;
}

static BOOL VsRecorderViewerRecord_BoxViewInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetBgPriorities();
        VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_LoadBgTilemap(param0, 56, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 59, 7);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);

        VsRecorderViewerRecord_CreateSubScreenSprites(param0);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);

        v0->unk_50C.spriteIndex = 500;
        v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBoxMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsBoxMenu), VsRecorderViewerRecord_TouchHandlerBoxMenu, param0, HEAP_ID_102);
        v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsPokedexGrid, NELEMS(sVsRecorderViewerRecord_TouchRectsPokedexGrid), VsRecorderViewerRecord_TouchHandlerPokedexGrid, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_OpenMainMessage(param0, 124);
            VsRecorderViewerRecord_CreateMenuWindows(param0, 0);
            VsRecorderViewerRecord_CreateCategoryWindows(param0, 0);

            v0->unk_4C0 = 0xffff;
            v0->unk_4C2 = 0xff;
            v0->unk_4C3 = 0xff;
            v0->unk_4C4 = 0xff;

            VsRecorderViewerRecord_DrawSpeciesName(param0, v0->unk_4C0);
            VsRecorderViewerRecord_DrawRankLabel(param0, v0->unk_4C2);
            VsRecorderViewerRecord_DrawLocationName(param0, v0->unk_4C3, v0->unk_4C4);

            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BoxViewHandleTouch(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[0]);
    return 0;
}

static BOOL VsRecorderViewerRecord_BoxViewExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerRecord_RemoveMenuWindows(param0);
        VsRecorderViewerRecord_RemoveCategoryWindows(param0);
        VsRecorderViewerList_CloseMainMessage(param0);

        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRecord_FreeSubScreenSprites(param0);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BoxViewOptions(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerRecord_RemoveCategoryWindows(param0);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:;
        switch (v0->unk_4C5) {
        case 0:
            VsRecorderViewerMain_SetState(param0, 6);
            break;
        case 1:
            VsRecorderViewerMain_SetState(param0, 7);
            break;
        case 2:
            VsRecorderViewerMain_SetState(param0, 10);
            break;
        }

        break;
    }

    return 0;
}

static const VsRecorderViewerListEntry sVsRecorderViewerRecord_RankEntriesShort[] = {
    { 0xA9, UnkEnum_0202F510_33, 0x0 },
    { 0xAA, UnkEnum_0202F510_34, 0x0 },
    { 0xAB, UnkEnum_0202F510_35, 0x0 },
    { 0xAC, UnkEnum_0202F510_36, 0x0 },
    { 0xAD, UnkEnum_0202F510_14, 0x0 }
};

static const VsRecorderViewerListEntry sVsRecorderViewerRecord_RankEntriesFull[] = {
    { 0xA9, UnkEnum_0202F510_33, 0x0 },
    { 0xAA, UnkEnum_0202F510_34, 0x0 },
    { 0xAB, UnkEnum_0202F510_35, 0x0 },
    { 0xAC, UnkEnum_0202F510_36, 0x0 },
    { 0xAD, UnkEnum_0202F510_14, 0x0 },
    { 0xAE, UnkEnum_0202F510_15, 0x0 },
    { 0xAF, UnkEnum_0202F510_16, 0x0 },
    { 0xB0, UnkEnum_0202F510_17, 0x0 },
    { 0xB1, UnkEnum_0202F510_18, 0x0 },
    { 0xB2, UnkEnum_0202F510_19, 0x0 },
    { 0xB3, UnkEnum_0202F510_20, 0x0 },
    { 0xB4, UnkEnum_0202F510_21, 0x0 },
    { 0xB5, UnkEnum_0202F510_22, 0x0 },
    { 0xB6, UnkEnum_0202F510_23, 0x0 },
    { 0xB7, UnkEnum_0202F510_24, 0x0 },
    { 0xB8, UnkEnum_0202F510_25, 0x0 },
    { 0xB9, UnkEnum_0202F510_26, 0x0 },
    { 0xBA, UnkEnum_0202F510_27, 0x0 },
    { 0xBB, UnkEnum_0202F510_28, 0x0 },
    { 0xBC, UnkEnum_0202F510_29, 0x0 },
    { 0xBD, UnkEnum_0202F510_30, 0x0 },
    { 0xBE, UnkEnum_0202F510_31, 0x0 },
    { 0xBF, UnkEnum_0202F510_32, 0x0 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsRank[] = {
    { 0x18, 0x38, 0x30, 0xD0 },
    { 0x38, 0x58, 0x30, 0xD0 },
    { 0x58, 0x78, 0x30, 0xD0 }
};

static const VsRecorderViewerListConfig sVsRecorderViewerRecord_RankMenuConfigShort = {
    sVsRecorderViewerRecord_RankEntriesShort,
    NELEMS(sVsRecorderViewerRecord_RankEntriesShort),
    0x2,
    0x7,
    0x3,
    0x12,
    0xC,
    0x20,
    0x6,
    0x3,
    sVsRecorderViewerRecord_TouchRectsRank
};

static const VsRecorderViewerListConfig sVsRecorderViewerRecord_RankMenuConfigFull = {
    sVsRecorderViewerRecord_RankEntriesFull,
    NELEMS(sVsRecorderViewerRecord_RankEntriesFull),
    0x2,
    0x7,
    0x3,
    0x12,
    0xC,
    0x20,
    0x6,
    0x3,
    sVsRecorderViewerRecord_TouchRectsRank
};

static BOOL VsRecorderViewerRecord_RankMenu(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_UpdateMessageText(param0, 113);
        v0->unk_4C2 = 0xff;
        VsRecorderViewerRecord_DrawRankLabel(param0, v0->unk_4C2);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
        VsRecorderViewerList_LoadBgTilemap(param0, 61, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_InitScrollBar(&param0->unk_14.scrollBar, param0);
            VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);

            if (VsRecorder_CheckFirstArrivalBattlePark(param0) == 1) {
                VsRecorderViewerList_InitWindow(&param0->unk_14.listWindow, param0, &sVsRecorderViewerRecord_RankMenuConfigFull);
            } else {
                VsRecorderViewerList_InitWindow(&param0->unk_14.listWindow, param0, &sVsRecorderViewerRecord_RankMenuConfigShort);
            }

            VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
            VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 2);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ScrollList(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);

        {
            int v1 = VsRecorderViewerList_UpdateRecordWindow(&param0->unk_14.listWindow, param0);

            if (v1) {
                v0->unk_4C2 = v1;
                VsRecorderViewerRecord_DrawRankLabel(param0, v1);
                param0->unk_08++;
            }
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectBack[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        VsRecorderViewerList_ResetScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
        param0->unk_08++;
    case 4:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 11);
        break;
    }

    return 0;
}

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsPokedexLetters[] = {
    { 0x18, 0x28, 0x38, 0xC0 },
    { 0x28, 0x38, 0x38, 0xC0 },
    { 0x38, 0x48, 0x38, 0xC0 },
    { 0x48, 0x58, 0x38, 0xC0 },
    { 0x58, 0x68, 0x38, 0xC0 },
    { 0x68, 0x78, 0x38, 0xC0 }
};

static const VsRecorderViewerListConfig sVsRecorderViewerRecord_PokedexGridConfig = {
    NULL,
    0x0,
    0x1,
    0x9,
    0x3,
    0xE,
    0xC,
    0x20,
    0x6,
    0x6,
    sVsRecorderViewerRecord_TouchRectsPokedexLetters
};

static BOOL VsRecorderViewerRecord_SpeciesMenu(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_UpdateMessageText(param0, 114);
        v0->unk_4C0 = 0xffff;
        VsRecorderViewerRecord_DrawSpeciesName(param0, v0->unk_4C0);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
        param0->unk_08++;
    default:
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static void VsRecorderViewerRecord_CreatePokedexLetterWindows(VsRecorderState *a0)
{
    String *sp2c;
    VsRecorderState *sp14 = a0;
    int sp28 = 1;
    VsRecorderViewerRecordContext *r1 = sp14->unk_860;

    for (u32 r7 = 0; r7 < 9; r7++) {
        Window *r4 = &r1->unk_6D4[r7];
        u8 sp24 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[r7].rect.left / 8;
        u8 sp20 = sVsRecorderViewerRecord_TouchRectsPokedexGrid[r7].rect.top / 8;
        u8 sp1c = (sVsRecorderViewerRecord_TouchRectsPokedexGrid[r7].rect.right / 8) - sp24;
        u8 r6 = (sVsRecorderViewerRecord_TouchRectsPokedexGrid[r7].rect.bottom / 8) - sp20;
        Window_Init(r4);
        Window_Add(sp14->unk_14.bgConfig, r4, 6, sp24, sp20, sp1c, r6, 0xe, sp28);
        Window_FillTilemap(r4, 0);
        sp2c = MessageLoader_GetNewString(sp14->unk_14.messageLoader, r7 + 0x44);
        int sp30 = VsRecorderViewerList_CalcCenteredTextX(r4, sp2c);
        int sp18 = ((r6 * 8) - 0x10) / 2;
        if (VsRecorderViewerRecord_IsPokedexSectionSeen(sp14, r7) == 1) {
            Text_AddPrinterWithParamsAndColor(r4, 0, sp2c, sp30, sp18, 0xff, 0x000f0d00, 0);
        } else {
            Text_AddPrinterWithParamsAndColor(r4, 0, sp2c, sp30, sp18, 0xff, 0x000c0b00, 0);
        }
        Window_ScheduleCopyToVRAM(r4);
        String_Free(sp2c);
        sp28 += sp1c * r6;
    }
}

static void VsRecorderViewerRecord_RemovePokedexLetterWindows(VsRecorderState *param0)
{
    u32 v0;
    Window *v1;
    VsRecorderViewerRecordContext *v2 = param0->unk_860;

    for (v0 = 0; v0 < 9; v0++) {
        v1 = &v2->unk_6D4[v0];
        Window_ClearAndCopyToVRAM(v1);
        Window_Remove(v1);
    }
}

static BOOL VsRecorderViewerRecord_PokedexGridMenu(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 60, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerRecord_CreatePokedexLetterWindows(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        TouchScreenActions_HandleAction(v0->unk_608[1]);

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectBack[0])
            || (v0->unk_4C8.active == 1)) {
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerRecord_RemovePokedexLetterWindows(param0);
        param0->unk_08++;
    case 4:
        if (v0->unk_4C8.active == 1) {
            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                param0->unk_08++;
            }
        } else {
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;

    default:
        if (v0->unk_4C8.active == 1) {
            VsRecorderViewerMain_SetState(param0, 9);
        } else {
            VsRecorderViewerMain_SetState(param0, 11);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SpeciesSelect(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_UpdateMessageText(param0, 114);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
        VsRecorderViewerList_LoadBgTilemap(param0, 58, 7);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_InitScrollBar(&param0->unk_14.scrollBar, param0);

            v0->unk_4E0 = sVsRecorderViewerRecord_PokedexGridConfig;
            v0->unk_4E0.entries = v0->unk_4DC;
            v0->unk_4E0.entryCount = v0->unk_4C8.entryCount;

            VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
            VsRecorderViewerList_InitRecordWindow(&param0->unk_14.listWindow, param0, v0->unk_4C8.messageLoader, &v0->unk_4E0);

            param0->unk_14.listWindow.twoColumn = 0;

            VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
            VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 2);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);

            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ScrollList(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);

        {
            int v1 = VsRecorderViewerList_UpdateRecordWindow(&param0->unk_14.listWindow, param0);

            if (v1) {
                v0->unk_4C0 = v1;
                VsRecorderViewerRecord_DrawSpeciesName(param0, v1);
                param0->unk_08++;
            }
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectBack[0])) {
            v0->unk_4C0 = 0xffff;
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }

        break;

    case 3:
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        VsRecorderViewerList_ResetScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
        param0->unk_08++;
    case 4:
        if (v0->unk_4C0 != 0xffff) {
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        } else {
            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
                param0->unk_08++;
            }
        }
        break;
    default:
        VsRecorderViewerRecord_FreePokedexSection(param0);

        if (v0->unk_4C0 != 0xffff) {
            VsRecorderViewerMain_SetState(param0, 11);
        } else {
            VsRecorderViewerMain_SetState(param0, 8);
        }
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_IsPokedexSectionSeen(VsRecorderState *param0, int param1)
{
    BOOL v0 = 0;
    u16 *v1;
    int v2;
    int v3;
    int v4;
    int pokedexLength;
    VsRecorderViewerRecordContext *v6 = param0->unk_860;

    v4 = sVsRecorderViewerRecord_PokedexSectionOffsets[param1 + 1];
    v3 = sVsRecorderViewerRecord_PokedexSectionOffsets[param1];
    v2 = v4 - v3;
    v1 = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &pokedexLength);

    {
        int v7;
        int v8 = 0;
        BOOL v9;
        Pokedex *v10 = SaveData_GetPokedex(param0->saveData);

        for (v7 = v3; v7 < v4; v7++) {
            v9 = Pokedex_HasSeenSpecies(v10, v1[v7]);

            if (v9 == 0) {
                v1[v7] = 0xFFFF;
            }
        }

        v8 = 0;

        for (v7 = v3; v7 < v4; v7++) {
            if (v1[v7] != 0xFFFF) {
                v0 = 1;
                break;
            }
        }

        Heap_Free(v1);
    }

    return v0;
}

static void VsRecorderViewerRecord_BuildPokedexSection(VsRecorderState *param0, int param1)
{
    u16 *v0;
    int v1;
    int v2;
    int v3;
    VsRecorderViewerRecordContext *v4 = param0->unk_860;

    v3 = sVsRecorderViewerRecord_PokedexSectionOffsets[param1 + 1];
    v2 = sVsRecorderViewerRecord_PokedexSectionOffsets[param1];
    v1 = v3 - v2;

    v4->unk_4C8.pokedex = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &v4->unk_4C8.pokedexCount);
    v0 = VsRecorderViewerList_LoadPokedexAlphabetical(102, 0, &v4->unk_4C8.pokedexCount);

    {
        int v5;
        int v6 = 0;
        BOOL v7;
        Pokedex *v8 = SaveData_GetPokedex(param0->saveData);

        v4->unk_4C8.entryCount = 0;

        for (v5 = v2; v5 < v3; v5++) {
            v7 = Pokedex_HasSeenSpecies(v8, v0[v5]);

            if (v7 == 0) {
                v0[v5] = 0xFFFF;
            } else {
                v4->unk_4C8.entryCount++;
            }
        }

        v6 = 0;

        for (v5 = v2; v5 < v3; v5++) {
            if (v0[v5] == 0xFFFF) {
                continue;
            }

            v4->unk_4C8.pokedex[v6] = v0[v5];
            v6++;
        }

        for (v5 = v6; v5 < v4->unk_4C8.pokedexCount; v5++) {
            v4->unk_4C8.pokedex[v5] = v0[v5];
        }

        Heap_Free(v0);

        v4->unk_4DC = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerListEntry) * v4->unk_4C8.entryCount);
        MI_CpuFill8(v4->unk_4DC, 0, sizeof(VsRecorderViewerListEntry) * v4->unk_4C8.entryCount);

        for (v5 = 0; v5 < v4->unk_4C8.entryCount; v5++) {
            v4->unk_4DC[v5].messageID = v4->unk_4C8.pokedex[v5];
            v4->unk_4DC[v5].value = v4->unk_4C8.pokedex[v5];
        }
    }

    v4->unk_4C8.messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_SPECIES_NAME, HEAP_ID_102);
    v4->unk_4C8.active = 1;
}

static void VsRecorderViewerRecord_FreePokedexSection(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    MessageLoader_Free(v0->unk_4C8.messageLoader);
    Heap_Free(v0->unk_4DC);
    Heap_Free(v0->unk_4C8.pokedex);

    v0->unk_4C8.active = 0;
}

static const VsRecorderViewerListEntry sVsRecorderViewerRecord_CountryEntries[] = {
    { 0x10, 0xD, 0x0 }
};

static const TouchScreenRect sVsRecorderViewerRecord_TouchRectsCountry[] = {
    { 0x18, 0x38, 0x38, 0xC8 }
};

static const VsRecorderViewerListConfig sVsRecorderViewerRecord_CountryMenuConfig = {
    sVsRecorderViewerRecord_CountryEntries,
    NELEMS(sVsRecorderViewerRecord_CountryEntries),
    0x2,
    0x8,
    0x2,
    0x10,
    0xC,
    0x20,
    0x6,
    0x1,
    sVsRecorderViewerRecord_TouchRectsCountry
};

static BOOL VsRecorderViewerRecord_LocationSelect(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_UpdateMessageText(param0, 115);
        v0->unk_4C3 = 0xff;
        v0->unk_4C4 = 0xff;
        VsRecorderViewerRecord_DrawLocationName(param0, v0->unk_4C3, v0->unk_4C4);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
        VsRecorderViewerList_LoadBgTilemap(param0, 57, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerList_InitScrollBar(&param0->unk_14.scrollBar, param0);
            VsRecorderViewerList_InitWindow(&param0->unk_14.listWindow, param0, &sVsRecorderViewerRecord_CountryMenuConfig);
            VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
            VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 2);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_ScrollList(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);

        {
            int v1 = VsRecorderViewerList_UpdateRecordWindow(&param0->unk_14.listWindow, param0);

            if (v1) {
                v0->unk_4C3 = PlayerProfile_GetCountry(param0->unk_88C[0]);
                v0->unk_4C4 = PlayerProfile_GetRegion(param0->unk_88C[0]);
                VsRecorderViewerRecord_DrawLocationName(param0, v0->unk_4C3, v0->unk_4C4);
                param0->unk_08++;
            }
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectBack[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        param0->unk_08++;
    case 4:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 11);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SpeciesMenuOpen(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 56, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 59, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerList_UpdateMessageText(param0, 124);
            VsRecorderViewerRecord_CreateCategoryWindows(param0, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_UploadRecord(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_UpdateMessageText(param0, 117);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 1: {
        int v2 = v0->unk_4C2;

        if (v2 == 0xff) {
            if (VsRecorder_CheckFirstArrivalBattlePark(param0) == 1) {
                v2 = 0xff;
            } else {
                v2 = UnkEnum_0202F510_37;
            }
        }

        if (GlobalTerminalTransfer_UploadRecord(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_4C0, v2, v0->unk_4C3, v0->unk_4C4) == 1) {
            param0->unk_08++;
        }
    } break;
    case 2:
        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_GetMessageIndex(param0, 7, v1->index, v1->category);
            param0->unk_8B4.recordCount = 0;
            param0->unk_08++;
        } else {
            Sound_StopEffect(1381, 0);
            param0->unk_14.subContext.messageIndex = 118;
            param0->unk_08++;
        }
        break;
    case 3:
        if (param0->unk_8B4.recordCount == 0) {
            VsRecorderViewerList_UpdateMessageText(param0, param0->unk_14.subContext.messageIndex);
            Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
        } else {
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
        }

        param0->unk_08++;
        break;
    default:
        VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);

        if (param0->unk_8B4.recordCount == 0) {
            VsRecorderViewerMain_SetState(param0, 3);
        } else {
            VsRecorderViewerMain_SetState(param0, 13);
        }

        break;
    }

    return 0;
}

static const VsRecorderViewerListConfig sVsRecorderViewerRecord_PlaybackConfig = {
    sVsRecorderViewerRecord_RankEntriesFull,
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

static BOOL VsRecorderViewerRecord_UploadRecordExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerRecord_RemoveMenuWindows(param0);
        VsRecorderViewerRecord_RemoveCategoryWindows(param0);
        VsRecorderViewerList_CloseMainMessage(param0);
        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 14);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_PlaybackInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (BattleRecording_Exists()) {
            BattleRecording_Free();
        }

        v0->unk_4E0 = sVsRecorderViewerRecord_PlaybackConfig;
        v0->unk_4E0.entries = NULL;
        v0->unk_4E0.entryCount = param0->unk_8B4.recordCount;

        VsRecorderViewerList_LoadIconResources(param0);
        v0->unk_50C.narc = VsRecorderViewerList_OpenIconNarc(102);

        VsRecorderViewerList_LoadBgTilemap(param0, 4, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 7, 7);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);

        VsRecorderViewerRecord_CreateHeaderWindows(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitScrollBar(&param0->unk_14.scrollBar, param0);
        VsRecorderViewerList_InitRecordWindow(&param0->unk_14.listWindow, param0, NULL, &v0->unk_4E0);

        param0->unk_14.listWindow.twoColumn = 1;

        VsRecorderViewerList_UpdateScrollBarVisibility(&param0->unk_14.scrollBar, &param0->unk_14.listWindow);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_LoadArrowSprites(&param0->unk_14.listWindow, param0, 1);
        VsRecorderViewerList_SetArrowSpritesPosition(&param0->unk_14.listWindow, 64, 184);
        VsRecorderViewerList_UpdateSpeciesWindow(&param0->unk_14.listWindow, param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRecord_CreateBoxSprites(param0);
        VsRecorderViewerRecord_SetBoxSpritesVisible(param0, 0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);

            VsRecorderViewerRecord_SetBoxSpritesVisible(param0, 1);
            VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 16, 76 + (param0->unk_14.listWindow.scrollState.scroll * 24));

            VsRecorderRing_SetVisible(param0->unk_6F0, 1);
            VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 12, 12);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 15);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_PlaybackInput(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.scrollBar);
        VsRecorderViewerList_MoveSelection(&param0->unk_14.listWindow, param0->unk_14.scrollBar.direction);
        VsRecorderViewerList_UpdateSpeciesWindow(&param0->unk_14.listWindow, param0);
        VsRecorderRing_TrySetTargetPosition(param0->unk_6F0, 16, 76 + (param0->unk_14.listWindow.scrollState.scroll * 24));
        VsRecorderViewerRecord_ScrollBoxList(param0);

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectPlayback[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            v0->unk_0C = 17;
            param0->unk_08++;
        }

        if (TouchScreen_LocationPressed(&sVsRecorderViewerRecord_TouchRectBack[0])) {
            VsRecorderViewerList_PlayRingAnim(param0);
            v0->unk_0C = 16;
            param0->unk_08++;
        }
        break;
    case 1:
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.scrollBar);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.listWindow);
        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.listWindow, param0);
        VsRecorderViewerList_CloseIconNarc(v0->unk_50C.narc);
        VsRecorderViewerRecord_FreeBoxSprites(param0);
        VsRecorderViewerList_FreeIconResources(param0);
        VsRecorderViewerRecord_RemoveMenuWindows(param0);
        VsRecorderViewerRecord_RemoveCategoryWindows(param0);

        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);

        if (v0->unk_0C == 16) {
            VsRecorderViewerList_ResetScrollBar(&param0->unk_14.scrollBar);
            VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
            v0->unk_50C.lastScroll = 0;
        }

        param0->unk_08++;

    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);

            if (v0->unk_0C == 17) {
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);
                ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
                ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);
            }

            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, v0->unk_0C);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BoxView(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 56, 3);
        VsRecorderViewerList_LoadBgTilemap(param0, 59, 7);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);

        v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBoxMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsBoxMenu), VsRecorderViewerRecord_TouchHandlerBoxMenu, param0, HEAP_ID_102);
        v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsPokedexGrid, NELEMS(sVsRecorderViewerRecord_TouchRectsPokedexGrid), VsRecorderViewerRecord_TouchHandlerPokedexGrid, param0, HEAP_ID_102);

        VsRecorderViewerRecord_CreateCategoryWindows(param0, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_OpenMainMessage(param0, 124);
            VsRecorderViewerRecord_CreateMenuWindows(param0, 0);
            VsRecorderViewerRecord_DrawSpeciesName(param0, v0->unk_4C0);
            VsRecorderViewerRecord_DrawRankLabel(param0, v0->unk_4C2);
            VsRecorderViewerRecord_DrawLocationName(param0, v0->unk_4C3, v0->unk_4C4);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RankListInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerRecord_LoadBoxRecordProfile(param0);
        v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsRecordMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsRecordMenu), VsRecorderViewerRecord_TouchHandlerRankActions, param0, HEAP_ID_102);
        v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsProfileSelect, NELEMS(sVsRecorderViewerRecord_TouchRectsProfileSelect), VsRecorderViewerRecord_TouchHandlerRankProfileSelect, param0, HEAP_ID_102);
        v0->unk_608[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBackButton, NELEMS(sVsRecorderViewerRecord_TouchRectsBackButton), VsRecorderViewerRecord_TouchHandlerRankBack, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 2:
        v0->unk_1CC = 0;
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
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
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            VsRecorderViewerRecord_CreateInfoWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 18);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RankListHandleTouch(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[0]);
    return 0;
}

static BOOL VsRecorderViewerRecord_RankListToggleView(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_ToggleViewState(param0)) {
        VsRecorderViewerMain_SetState(param0, 18);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RankListExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_Exit(param0)) {
        Heap_Free(v0);
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RankListCleanup(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        TouchScreenActions_Free(v0->unk_608[2]);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);

        VsRecorderViewerRecord_FreeRecordProfile(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerRecord_RemoveInfoWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 111);
            ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_10[1].sprite, 1);
            VsRecorderViewerRecord_SetViewToggleSprite(param0, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 14);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingView(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerList_HasRecordingValue(param0, BattleRecording_GetSummaryValue(BattleRecording_GetSummary(), 4, 0))) {
        switch (param0->unk_08) {
        case 0:
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
            } else {
                VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
            }

            VsRecorderViewerRecord_RemoveInfoWindow(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            param0->unk_08++;
            break;
        case 1:
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
                VsRecorderViewerList_SetDrawSuspended(param0, 1);
                VsRecorderViewerRecord_FreeSubScreenSprites(param0);
                VsRecorderViewerRecord_CreateSummarySprites(param0);
                VsRecorderViewerList_SetDrawSuspended(param0, 0);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            break;
        case 2:
            VsRecorderViewerList_OpenMainMessage(param0, 277);
            param0->unk_08++;
            break;
        case 3:
            if (!TouchScreen_Tapped()) {
                break;
            }

            VsRecorderViewerRecord_FreeSummarySprites(param0);
            VsRecorderViewerList_CloseMainMessage(param0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            param0->unk_08++;
            break;
        case 4:
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerRecord_CreateSubScreenSprites(param0);

            if (param0->unk_86C == 210) {
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
                VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);
                ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
                ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerRecord_CreateInfoWindow(param0);
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);

                VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
            } else {
                VsRecorderViewerList_InitProfile(&v0->unk_80, param0);
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
                Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 80, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 6, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            param0->unk_08++;
            break;
        case 5:
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
                if (v0->unk_1CC == 0) {
                    VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
                } else {
                    VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 1);
                }

                GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
                GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            break;
        default: {
            int v1;

            for (v1 = 0; v1 < param0->unk_8B4.recordCount; v1++) {
                param0->unk_8B4.records[v1] = &param0->unk_8B4.recordCopies[v1];
            }
        }
            VsRecorderViewerMain_SetState(param0, 18);
            break;
        }
    } else {
        if (VsRecorderViewerRecord_CloseView(param0)) {
            VsRecorderViewerMain_SetState(param0, 23);
        }
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingHandleTouch1(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[1]);
    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingToggle1(VsRecorderState *param0)
{
    if (VsRecorderViewerRecord_ReopenBoxViewState(param0)) {
        {
            int v0;

            for (v0 = 0; v0 < param0->unk_8B4.recordCount; v0++) {
                param0->unk_8B4.records[v0] = &param0->unk_8B4.recordCopies[v0];
            }
        }
        VsRecorderViewerMain_SetState(param0, 18);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingToggle2(VsRecorderState *param0)
{
    if (VsRecorderViewerRecord_RestoreBoxViewState(param0)) {
        {
            int v0;

            for (v0 = 0; v0 < param0->unk_8B4.recordCount; v0++) {
                param0->unk_8B4.records[v0] = &param0->unk_8B4.recordCopies[v0];
            }
        }
        VsRecorderViewerMain_SetState(param0, 18);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingDetail(VsRecorderState *param0)
{
    if (VsRecorderViewerRecord_SpeciesDetailState(param0)) {
        VsRecorderViewerMain_SetState(param0, 26);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingHandleTouch2(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[2]);
    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingToggle3(VsRecorderState *param0)
{
    if (VsRecorderViewerRecord_CloseSpeciesDetailState(param0)) {
        VsRecorderViewerMain_SetState(param0, 23);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_BattleRecordingPlayback(VsRecorderState *param0)
{
    VsRecorderViewerRecord_PlaybackUploadState(param0);
    return 0;
}

static BOOL VsRecorderViewerRecord_UploadId(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
        } else {
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
        }

        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerList_OpenMainMessage(param0, 117);
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);

        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);

        v0->unk_4B8 = 0;
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 3:
        if (GlobalTerminalTransfer_UploadId(VsRecorderViewerTransfer_GetTransfer(param0), param0->unk_8B4.records[param0->unk_14.listWindow.scrollState.selection]->data.recordingID) == 1) {
            param0->unk_08++;
        }
        break;
    case 4:
        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_CloseMainMessage(param0);
            VsRecorderViewerList_OpenMessage(param0, 8, v1->index, v1->category);
            param0->unk_08++;
            v0->unk_4B8 = 0;
        } else {
            Sound_StopEffect(1381, 0);
            param0->unk_08 = 0xFF;
            v0->unk_4B8 = 1;
            param0->unk_878 = &param0->unk_8B4.recordFlags[param0->unk_14.listWindow.scrollState.selection];
            v0->unk_4BC = param0->unk_8B4.record;
            MI_CpuCopy8(v0->unk_4BC, &param0->unk_8B4.recordCopy, sizeof(GlobalTerminalRecordAlt));
        }

        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        break;
    default:
        if (v0->unk_4B8) {
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            VsRecorderViewerList_CloseMainMessage(param0);
            VsRecorderViewerMain_SetState(param0, v0->unk_0C);
            VsRecorderViewerList_SetHasPendingRecording(param0, 1);
        } else {
            VsRecorderViewerList_CloseMainMessage(param0);
            VsRecorderViewerMain_SetState(param0, 31);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_PlaybackViewInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetBgPriorities();
        VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
        {
            int v1;

            for (v1 = 0; v1 < param0->unk_8B4.recordCount; v1++) {
                param0->unk_8B4.records[v1] = &param0->unk_8B4.recordCopies[v1];
            }
        }

        v0->unk_79C = param0->unk_8B4.recordFlags[param0->unk_14.listWindow.scrollState.selection];

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);

        VsRecorderViewerRecord_CreateSubScreenSprites(param0);
        VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);

        ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
        ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);

        v0->unk_4C0 = 0xffff;
        v0->unk_4C2 = 0xff;
        v0->unk_4C3 = 0xff;
        v0->unk_4C4 = 0xff;
        v0->unk_50C.spriteIndex = 500;
        v0->unk_50C.lastScroll = param0->unk_14.listWindow.scroll;
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerRecord_LoadBoxRecordProfile(param0);
        v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsRecordMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsRecordMenu), VsRecorderViewerRecord_TouchHandlerRankActions, param0, HEAP_ID_102);
        v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsProfileSelect, NELEMS(sVsRecorderViewerRecord_TouchRectsProfileSelect), VsRecorderViewerRecord_TouchHandlerRankProfileSelect, param0, HEAP_ID_102);
        v0->unk_608[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBackButton, NELEMS(sVsRecorderViewerRecord_TouchRectsBackButton), VsRecorderViewerRecord_TouchHandlerRankBack, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
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
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            VsRecorderViewerRecord_CreateInfoWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
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
        param0->unk_534.mainEntryCount += 1;
        VsRecorderViewerMain_ResetSelection(param0);
        VsRecorderViewerMain_SetState(param0, 18);
        break;
    }

    return 0;
}

BOOL (*const sVsRecorderViewerRecord_MainStateTable[])(VsRecorderState *) = {
    VsRecorderViewerRecord_Init,
    VsRecorderViewerRecord_Setup,
    VsRecorderViewerRecord_BoxViewInit,
    VsRecorderViewerRecord_BoxViewHandleTouch,
    VsRecorderViewerRecord_BoxViewExit,
    VsRecorderViewerRecord_BoxViewOptions,
    VsRecorderViewerRecord_RankMenu,
    VsRecorderViewerRecord_SpeciesMenu,
    VsRecorderViewerRecord_PokedexGridMenu,
    VsRecorderViewerRecord_SpeciesSelect,
    VsRecorderViewerRecord_LocationSelect,
    VsRecorderViewerRecord_SpeciesMenuOpen,
    VsRecorderViewerRecord_UploadRecord,
    VsRecorderViewerRecord_UploadRecordExit,
    VsRecorderViewerRecord_PlaybackInit,
    VsRecorderViewerRecord_PlaybackInput,
    VsRecorderViewerRecord_BoxView,
    VsRecorderViewerRecord_RankListInit,
    VsRecorderViewerRecord_RankListHandleTouch,
    VsRecorderViewerRecord_RankListToggleView,
    VsRecorderViewerRecord_RankListExit,
    VsRecorderViewerRecord_RankListCleanup,
    VsRecorderViewerRecord_BattleRecordingView,
    VsRecorderViewerRecord_BattleRecordingHandleTouch1,
    VsRecorderViewerRecord_BattleRecordingToggle1,
    VsRecorderViewerRecord_BattleRecordingDetail,
    VsRecorderViewerRecord_BattleRecordingHandleTouch2,
    VsRecorderViewerRecord_BattleRecordingToggle3,
    VsRecorderViewerRecord_BattleRecordingPlayback,
    VsRecorderViewerRecord_UploadId,
    VsRecorderViewerRecord_PlaybackViewInit,
    VsRecorderViewerRecord_BattleRecordingToggle2,
};

BOOL (*const sVsRecorderViewerRecord_ProfileStateTable[])(VsRecorderState *) = {
    VsRecorderViewerRecord_Init,
    VsRecorderViewerRecord_Setup,
    VsRecorderViewerRecord_ConfigInit,
    VsRecorderViewerRecord_ConfigUpdate,
    VsRecorderViewerRecord_ConfigExit,
    VsRecorderViewerRecord_ConfigExitCleanup,
    VsRecorderViewerRecord_UploadId2,
    VsRecorderViewerRecord_ProfileViewInit,
    VsRecorderViewerRecord_ProfileViewHandleTouch,
    VsRecorderViewerRecord_ProfileViewToggle,
    VsRecorderViewerRecord_ProfileViewExit,
    VsRecorderViewerRecord_ProfileViewCleanup,
    VsRecorderViewerRecord_SummaryView,
    VsRecorderViewerRecord_SummaryHandleTouch1,
    VsRecorderViewerRecord_SummaryToggle1,
    VsRecorderViewerRecord_SummaryDetail,
    VsRecorderViewerRecord_SummaryHandleTouch2,
    VsRecorderViewerRecord_SummaryToggle3,
    VsRecorderViewerRecord_SummaryPlayback,
    VsRecorderViewerRecord_SummaryViewInit,
    VsRecorderViewerRecord_SummaryToggle2,
};

BOOL (*const sVsRecorderViewerRecord_RingStateTable[])(VsRecorderState *) = {
    VsRecorderViewerRecord_Init,
    VsRecorderViewerRecord_Setup,
    VsRecorderViewerRecord_RingViewInit,
    VsRecorderViewerRecord_UploadBattleRecording,
    VsRecorderViewerRecord_UploadBattleRecordingExit,
};

static BOOL VsRecorderViewerRecord_Init(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerRecordContext));

    memset(v0, 0, sizeof(VsRecorderViewerRecordContext));
    param0->unk_860 = v0;

    Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
    Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerRecord_Setup(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
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
        param0->unk_08++;
        break;
    default:
        switch (param0->unk_86C) {
        case 200:
            VsRecorderViewerList_StartNetworkTask(param0, 0);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);

            if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
                VsRecorderViewerMain_SetState(param0, 6);
            } else {
                VsRecorderViewerMain_SetState(param0, 2);
            }

            break;

        case 210:
            VsRecorderViewerList_StartNetworkTask(param0, 0);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);

            if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
                VsRecorderViewerMain_SetState(param0, 30);
            } else {
                VsRecorderViewerMain_SetState(param0, 2);
            }
            break;

        case 220:
            if (VsRecorderViewerMain_HasPendingSelection(param0) == 1) {
                VsRecorderViewerMain_SetState(param0, 19);
            } else {
                VsRecorderViewerMain_SetState(param0, 2);
            }

            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            break;
        default:
            VsRecorderViewerList_StartNetworkTask(param0, 0);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            VsRecorderViewerMain_SetState(param0, 2);
            break;
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ConfigInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerIdEntryState *v1 = &v0->unk_1D4;

    switch (param0->unk_08) {
    case 0: {
        int v2[3];

        v2[0] = 2;
        v2[1] = 5;
        v2[2] = 5;
        v0->unk_4AC = VsRecorderViewerIdEntry_NewConfig(HEAP_ID_102, 12, v2, SaveData_GetOptions(param0->saveData));
        v1->graphics.narc = param0->unk_14.narc;
        v1->graphics.spriteSystem = param0->unk_14.spriteSystem;
        v1->graphics.spriteManager = param0->unk_14.spriteManager;
        v1->graphics.bgConfig = param0->unk_14.bgConfig;
        v1->graphics.palette = param0->unk_14.palette;
        v1->config = *(v0->unk_4AC);
        v1->state = param0;
        VsRecorderViewerRecord_CreateMainScreenSprites(param0);
    }
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_SetBlendAlpha(&v0->unk_00, &v0->unk_04, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            VsRecorderViewerList_OpenSubMessage(param0, 112);
            param0->unk_08++;
        }
        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 3);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ConfigUpdate(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerIdEntryState *v1 = &v0->unk_1D4;
    BOOL v2 = VsRecorderViewerIdEntry_Run(v1);

    if (v2 == 1) {
        VsRecorderViewerMain_SetState(param0, 4);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ConfigExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerIdEntryState *v1 = &v0->unk_1D4;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_CloseSubMessage(param0);
        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_00, &v0->unk_04, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 0);
        VsRecorderViewerIdEntry_FreeConfig(v0->unk_4AC);
        param0->unk_08++;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
            VsRecorderViewerRecord_FreeMainScreenSprites(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        if (v1->confirmed) {
            VsRecorderViewerMain_SetState(param0, 6);
        } else {
            VsRecorderViewerMain_SetState(param0, 5);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ConfigExitCleanup(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_UploadId2(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerIdEntryState *v1 = &v0->unk_1D4;
    VsRecorderViewerTransferStatus *v2;

    switch (param0->unk_08) {
    case 0:

        VsRecorderViewerList_OpenSubMessage(param0, 117);
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F4, 128, 96);

        VsRecorderRing_SetVisible(param0->unk_6F4, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F4, 24, 24);

        v0->unk_4B8 = 0;
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        if (GlobalTerminalTransfer_UploadId(VsRecorderViewerTransfer_GetTransfer(param0), v1->idValue) == 1) {
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        VsRecorderViewerList_CloseSubMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v2) == 1) {
            Sound_StopEffect(1381, 0);
            G2_BlendNone();
            VsRecorderViewerList_OpenMessage(param0, 8, v2->index, v2->category);
            VsRecorderViewerList_StartNetworkTask(param0, 0);
            param0->unk_08++;
            v0->unk_4B8 = 0;
        } else {
            Sound_StopEffect(1381, 0);
            param0->unk_08 = 0xFF;
            v0->unk_4B8 = 1;
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_878 = &param0->unk_8B4.recordFlag;
            v0->unk_4BC = param0->unk_8B4.record;
            MI_CpuCopy8(v0->unk_4BC, &param0->unk_8B4.recordCopy, sizeof(GlobalTerminalRecordAlt));
        }

        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F4, 0, 0);
        break;
    case 3:
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    case 4:
        param0->unk_08++;
        break;
    default:
        if (v0->unk_4B8) {
            VsRecorderViewerMain_SetState(param0, 7);
        } else {
            VsRecorderViewerMain_SetState(param0, 5);
        }

        break;
    }

    return 0;
}

static void VsRecorderViewerRecord_LoadRecordProfile(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    v0->unk_80.profile = PlayerProfile_New(HEAP_ID_102);
    GlobalTerminal_DeserializePlayerProfile(&v0->unk_4BC->profile, v0->unk_80.profile);
    v0->unk_10C.profile = v0->unk_80.profile;
    v0->unk_10C.summary = BattleRecording_NewSummary(HEAP_ID_102);
    MI_CpuCopy8(&v0->unk_4BC->data, v0->unk_10C.summary, sizeof(GlobalTerminalRecordAltData));
}

static void VsRecorderViewerRecord_LoadBoxRecordProfile(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    v0->unk_80.profile = PlayerProfile_New(HEAP_ID_102);
    GlobalTerminal_DeserializePlayerProfile(&param0->unk_8B4.records[param0->unk_14.listWindow.scrollState.selection]->profile, v0->unk_80.profile);
    v0->unk_10C.profile = v0->unk_80.profile;
    v0->unk_10C.summary = BattleRecording_NewSummary(HEAP_ID_102);
    MI_CpuCopy8(&param0->unk_8B4.records[param0->unk_14.listWindow.scrollState.selection]->data, v0->unk_10C.summary, sizeof(GlobalTerminalRecordAltData));
}

static void VsRecorderViewerRecord_FreeRecordProfile(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    BattleRecording_FreeSummary(v0->unk_10C.summary);
    PlayerProfile_Free(v0->unk_80.profile);
}

static BOOL VsRecorderViewerRecord_ProfileViewInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerMenu_UpdateBlendAlpha(&v0->unk_00, &v0->unk_04, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_LoadBgTilemap(param0, 6, 7);

        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);
        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 0);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);

        VsRecorderViewerRecord_LoadRecordProfile(param0);
        VsRecorderViewerRecord_CreateSubScreenSprites(param0);

        v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsRecordMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsRecordMenu), VsRecorderViewerRecord_TouchHandlerRecordActions, param0, HEAP_ID_102);
        v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsProfileSelect, NELEMS(sVsRecorderViewerRecord_TouchRectsProfileSelect), VsRecorderViewerRecord_TouchHandlerProfileSelect, param0, HEAP_ID_102);
        v0->unk_608[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBackButton, NELEMS(sVsRecorderViewerRecord_TouchRectsBackButton), VsRecorderViewerRecord_TouchHandlerBack, param0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 2:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        v0->unk_1CC = 0;

        VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
        VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
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
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            VsRecorderViewerRecord_CreateInfoWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ProfileViewHandleTouch(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[0]);
    return 0;
}

static BOOL VsRecorderViewerRecord_ProfileViewToggle(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_ToggleViewState(param0)) {
        VsRecorderViewerMain_SetState(param0, 8);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ProfileViewExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_Exit(param0)) {
        Heap_Free(v0);
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ProfileViewCleanup(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        TouchScreenActions_Free(v0->unk_608[2]);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);

        VsRecorderViewerRecord_FreeRecordProfile(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerRecord_RemoveInfoWindow(param0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerRecord_FreeSubScreenSprites(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    case 3:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

            if (BattleRecording_Exists() == 1) {
                BattleRecording_Free();
            }
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }
        break;
    default:
        break;
    }

    return 0;
}

static void VsRecorderViewerRecord_DrawPlayerName(VsRecorderViewerTextSprite *param0, VsRecorderState *param1, int param2)
{
    String *v0;
    MessageLoader *v1;
    Window v2;
    StringTemplate *v3;
    String *v4;
    String *v5;

    v1 = param1->unk_14.messageLoader;

    if (param1->unk_88C[param2] == NULL) {
        v0 = MessageLoader_GetNewString(v1, 8);
    } else {
        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v4 = MessageLoader_GetNewString(param1->unk_14.messageLoader, 7);
        v5 = PlayerProfile_GetName(param1->unk_88C[param2], HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param1, v5);
        v0 = String_Init(255, HEAP_ID_102);
        StringTemplate_SetString(v3, 0, v5, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v4);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    }

    Window_Init(&v2);
    Window_AddToTopLeftCorner(param1->unk_14.bgConfig, &v2, 20, 2, 0, 0);
    Text_AddPrinterWithParamsAndColor(&v2, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(14, 13, 0), NULL);
    FontOAMWindow_UploadToVRAM(param0->fontOAM, param0->fontOAMWindow, &v2, HEAP_ID_102);
    String_Free(v0);
    Window_Remove(&v2);
}

static void VsRecorderViewerRecord_DrawHeaderText(VsRecorderState *param0, int param1, BOOL param2)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;
    VsRecorderViewerRecordContext *v2 = param0->unk_860;

    VsRecorderViewerMenu_LoadBgPanel(param0, 2, param2);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    Window_Init(v1);
    Window_Add(param0->unk_14.bgConfig, v1, 2, 1, 19, 30, 4, 14, 300);

    if (param1 == 100) {
        StringTemplate *v3;
        String *v4;
        String *v5;
        PlayerProfile *v6 = v2->unk_80.profile;

        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v4 = PlayerProfile_GetName(v6, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v4);
        v5 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
        StringTemplate_SetString(v3, 0, v4, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v5);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    } else {
        v0 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
    }

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static void VsRecorderViewerRecord_DrawHeaderTextForProfile(VsRecorderState *param0, int param1, int param2)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;
    VsRecorderViewerRecordContext *v2 = param0->unk_860;

    if (param1 == 100) {
        StringTemplate *v3;
        String *v4;
        String *v5;
        PlayerProfile *v6 = v2->unk_80.profile;

        v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v4 = PlayerProfile_GetName(v6, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v4);
        v5 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
        StringTemplate_SetString(v3, 0, v4, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v0, v5);
        String_Free(v4);
        String_Free(v5);
        StringTemplate_Free(v3);
    } else if (param1 == 102) {
        StringTemplate *v7;
        String *v8;
        String *v9;
        PlayerProfile *v10 = param0->unk_88C[param2];

        v7 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
        v0 = String_Init(255, HEAP_ID_102);
        v8 = PlayerProfile_GetName(v10, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param0, v8);
        v9 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
        StringTemplate_SetString(v7, 0, v8, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v7, v0, v9);
        String_Free(v8);
        String_Free(v9);
        StringTemplate_Free(v7);
    } else {
        v0 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
    }

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static void VsRecorderViewerRecord_CreateSummarySprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
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
        v0->unk_10[v1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

        VsRecorderViewerMenu_InitLabelOAM(&v0->unk_10[v1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[v1], &param0->unk_14, v2[v1]);

        if (v1 != 3) {
            VsRecorderViewerRecord_DrawPlayerName(&v0->unk_10[v1], param0, v1 + 1);
        }

        ManagedSprite_SetPositionXY(v0->unk_10[v1].sprite, 42 + 8, (25 + (36 * (v1)) + (16 * (5 - 4))) + 64);
        ManagedSprite_SetAnim(v0->unk_10[v1].sprite, v3[v1]);
        FontOAM_SetXY(v0->unk_10[v1].fontOAM, 36, -8);
        FontOAM_SetDrawFlag(v0->unk_10[v1].fontOAM, 1);
    }
}

static void VsRecorderViewerRecord_FreeSummarySprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    int v1;

    for (v1 = 0; v1 < 4; v1++) {
        VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_10[v1]);
        Sprite_DeleteAndFreeResources(v0->unk_10[v1].sprite);
    }

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static BOOL VsRecorderViewerRecord_SummaryView(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerList_HasRecordingValue(param0, BattleRecording_GetSummaryValue(BattleRecording_GetSummary(), 4, 0))) {
        switch (param0->unk_08) {
        case 0:
            VsRecorderViewerList_SetDrawSuspended(param0, 1);

            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
            } else {
                VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
            }

            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerRecord_RemoveInfoWindow(param0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            param0->unk_08++;
            break;
        case 1:
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);
            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
                VsRecorderViewerList_SetDrawSuspended(param0, 1);
                VsRecorderViewerRecord_FreeSubScreenSprites(param0);
                VsRecorderViewerRecord_CreateSummarySprites(param0);
                VsRecorderViewerList_SetDrawSuspended(param0, 0);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
                param0->unk_08++;
            }

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            break;
        case 2:
            VsRecorderViewerList_OpenMainMessage(param0, 277);
            param0->unk_08++;
            break;
        case 3:
            if (!TouchScreen_Tapped()) {
                break;
            }

            VsRecorderViewerList_CloseMainMessage(param0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            param0->unk_08++;
            break;
        case 4:
            VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

            if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
                VsRecorderViewerRecord_FreeSummarySprites(param0);
                param0->unk_08++;
            }
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            break;
        case 5:
            TouchScreenActions_Free(v0->unk_608[0]);
            TouchScreenActions_Free(v0->unk_608[1]);
            TouchScreenActions_Free(v0->unk_608[2]);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerRecord_FreeRecordProfile(param0);
            VsRecorderViewerMenu_InitMenu(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            VsRecorderViewerList_StartNetworkTask(param0, 1);
            param0->unk_08++;
            break;
        default:
            if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
                break;
            }

            if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
                VsRecorderViewerList_BlendPalettes(param0);
                VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

                PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

                VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
                VsRecorderViewerMain_SetState(param0, 5);

                Heap_Free(v0);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
                Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

                if (BattleRecording_Exists() == 1) {
                    BattleRecording_Free();
                }
            } else {
                PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
                PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
            }

            break;
        }
    } else {
        if (VsRecorderViewerRecord_CloseView(param0)) {
            VsRecorderViewerMain_SetState(param0, 13);
        }
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryHandleTouch1(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[1]);
    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryToggle1(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_ReopenBoxViewState(param0)) {
        VsRecorderViewerMain_SetState(param0, 8);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryToggle2(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_RestoreBoxViewState(param0)) {
        VsRecorderViewerMain_SetState(param0, 8);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryDetail(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_SpeciesDetailState(param0)) {
        VsRecorderViewerMain_SetState(param0, 16);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryHandleTouch2(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    TouchScreenActions_HandleAction(v0->unk_608[2]);
    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryToggle3(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (VsRecorderViewerRecord_CloseSpeciesDetailState(param0)) {
        VsRecorderViewerMain_SetState(param0, 13);
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryPlayback(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    VsRecorderViewerRecord_PlaybackUploadState(param0);

    return 0;
}

static BOOL VsRecorderViewerRecord_SummaryViewInit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);

        v0->unk_79C = param0->unk_8B4.recordFlag;
        v0->unk_4BC = &param0->unk_8B4.recordCopy;
        param0->unk_8B4.record = v0->unk_4BC;

        VsRecorderViewerList_StoreBattleRecording(param0);
        VsRecorderViewerRecord_LoadRecordProfile(param0);

        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_StartNetworkTask(param0, 0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            Bg_SetPriority(BG_LAYER_MAIN_0, 1);
            Bg_SetPriority(BG_LAYER_MAIN_1, 3);
            Bg_SetPriority(BG_LAYER_MAIN_2, 0);
            Bg_SetPriority(BG_LAYER_MAIN_3, 1);
            Bg_SetPriority(BG_LAYER_SUB_0, 1);
            Bg_SetPriority(BG_LAYER_SUB_1, 3);
            Bg_SetPriority(BG_LAYER_SUB_2, 0);
            Bg_SetPriority(BG_LAYER_SUB_3, 2);

            v0->unk_608[0] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsRecordMenu, NELEMS(sVsRecorderViewerRecord_TouchRectsRecordMenu), VsRecorderViewerRecord_TouchHandlerRecordActions, param0, HEAP_ID_102);
            v0->unk_608[1] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsProfileSelect, NELEMS(sVsRecorderViewerRecord_TouchRectsProfileSelect), VsRecorderViewerRecord_TouchHandlerProfileSelect, param0, HEAP_ID_102);
            v0->unk_608[2] = TouchScreenActions_RegisterHandler(sVsRecorderViewerRecord_TouchRectsBackButton, NELEMS(sVsRecorderViewerRecord_TouchRectsBackButton), VsRecorderViewerRecord_TouchHandlerBack, param0, HEAP_ID_102);
            param0->unk_08++;
        }
        break;

    case 2:
        VsRecorderViewerRecord_CreateSubScreenSprites(param0);
        VsRecorderViewerRecord_CreateInfoWindow(param0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);

            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        } else {
            VsRecorderViewerList_InitProfile(&v0->unk_80, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 80, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 6, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 3:
        v0->unk_08 = 0;

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
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
        param0->unk_534.mainEntryCount += 1;
        VsRecorderViewerMain_ResetSelection(param0);
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RingViewInit(VsRecorderState *param0)
{
    VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
    VsRecorderRing_SetVisible(param0->unk_6F0, 1);
    VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
    VsRecorderViewerMain_SetState(param0, 3);

    return 0;
}

static BOOL VsRecorderViewerRecord_UploadBattleRecording(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_OpenMainMessage(param0, 119);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        {
            int v2;

            BattleRecording_Load(param0->saveData, 102, &v2, NULL, 0);
            v0->unk_1D0 = PlayerProfile_New(HEAP_ID_102);
            PlayerProfile_Init(v0->unk_1D0, param0->saveData);

            if (GlobalTerminalTransfer_UploadBattleRecording(VsRecorderViewerTransfer_GetTransfer(param0), v0->unk_1D0) == 1) {
                PlayerProfile_Free(v0->unk_1D0);
                param0->unk_08++;
            }
        }
        break;

    case 2:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        BattleRecording_Free();
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 6, v1->index, v1->category);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);

            param0->unk_08 = 0xFF;
        } else {
            VsRecorderViewerList_OpenMainMessage(param0, 119);
            VsRecorderViewerRecord_DrawRecordId(v0, param0);
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_08++;
        }
        break;
    case 3:
        if (!TouchScreen_Tapped()) {
            break;
        }

        VsRecorderViewerList_CloseMainMessage(param0);
        param0->unk_08++;
        break;
    default:
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        VsRecorderViewerList_IncrementTrainerScore(param0, 46);
        VsRecorderViewerMain_SetState(param0, 4);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_UploadBattleRecordingExit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerMain_ReturnToParentMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static void VsRecorderViewerRecord_RemoveInfoWindow(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_6D4[0]);
    Window_Remove(&v0->unk_6D4[0]);
}

static void VsRecorderViewerRecord_DrawInfoMessage(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3;

    v1 = &v0->unk_6D4[0];
    Window_FillTilemap(v1, 0x0);
    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, param1);
    v3 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v3, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerRecord_CreateInfoWindow(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;

    v1 = &v0->unk_6D4[0];

    Window_Init(v1);
    Window_Add(param0->unk_14.bgConfig, v1, 6, 8, 3, 16, 2, 14, v2);
    VsRecorderViewerRecord_DrawInfoMessage(param0, 121 + v0->unk_1CC);
}

static void VsRecorderViewerRecord_CreateDetailWindows(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    Window *v1;
    String *v2;
    int v3 = 1;
    int v4;

    v1 = &v0->unk_6D4[0];

    Window_Init(v1);
    Window_Add(param0->unk_14.bgConfig, v1, 6, 4, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 130);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);

    v3 += (10 * 2);

    v1 = &v0->unk_6D4[1];

    Window_Init(v1);
    Window_Add(param0->unk_14.bgConfig, v1, 6, 18, 6, 10, 2, 14, v3);
    Window_FillTilemap(v1, 0x0);

    v2 = MessageLoader_GetNewString(param0->unk_14.messageLoader, 131);
    v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v2);

    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    String_Free(v2);
    Window_ScheduleCopyToVRAM(v1);
}

static void VsRecorderViewerRecord_RemoveDetailWindows(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    Window_ClearAndCopyToVRAM(&v0->unk_6D4[0]);
    Window_Remove(&v0->unk_6D4[0]);
    Window_ClearAndCopyToVRAM(&v0->unk_6D4[1]);
    Window_Remove(&v0->unk_6D4[1]);
}

static void VsRecorderViewerRecord_TouchHandlerRecordActions(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 9);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 10);
        break;
    case 2:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 12);
        break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 11);
        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerProfileSelect(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
    case 1:
    case 2:
        v1->unk_1C8 = param0 + 1;

        if (v0->unk_88C[v1->unk_1C8] != NULL) {
            VsRecorderViewerMain_SetState(v0, 15);
        } else {
            VsRecorderViewerMain_SetState(v0, 18);
        }

        VsRecorderViewerList_PlayRingAnim(v0);
        break;

    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 14);
        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerBack(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerRecord_RemoveDetailWindows(v0);
        VsRecorderViewerMain_SetState(v0, 18);
        break;

    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 17);
        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerBoxMenu(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_4C5 = param0;
        VsRecorderViewerMain_SetState(v0, 5);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_4C5 = param0;
        VsRecorderViewerMain_SetState(v0, 5);
        break;
    case 2: {
        int v2 = PlayerProfile_GetCountry(v0->unk_88C[0]);

        VsRecorderViewerList_PlayRingAnim(v0);

        if (v2 == 0) {
            Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
            VsRecorderViewerList_UpdateMessageText(v0, 128);
        } else {
            v1->unk_4C5 = param0;
            VsRecorderViewerMain_SetState(v0, 5);
        }
    } break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 4:
        VsRecorderViewerList_PlayRingAnim(v0);

        if (VsRecorderViewerRecord_HasAnySelection(v0) == 0) {
            Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
            VsRecorderViewerList_UpdateMessageText(v0, 116);
        } else {
            VsRecorderViewerMain_SetState(v0, 12);
        }

        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerPokedexGrid(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    if (VsRecorderViewerRecord_IsPokedexSectionSeen(v0, param0) == 0) {
        Sound_PlayEffect(SEQ_SE_PL_BREC58_sseq);
        return;
    }

    VsRecorderViewerRecord_BuildPokedexSection(v0, param0);
}

static void VsRecorderViewerRecord_TouchHandlerRankActions(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 19);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);

        if (BattleRecording_Exists()) {
            VsRecorderViewerMain_SetState(v0, 20);
        } else {
            v1->unk_0C = 20;
            VsRecorderViewerMain_SetState(v0, 29);
        }
        break;
    case 2:
        VsRecorderViewerList_PlayRingAnim(v0);

        if (BattleRecording_Exists()) {
            VsRecorderViewerMain_SetState(v0, 22);
        } else {
            v1->unk_0C = 22;
            VsRecorderViewerMain_SetState(v0, 29);
        }
        break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 21);
        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerRankProfileSelect(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
    case 1:
    case 2:
        v1->unk_1C8 = param0 + 1;

        if (v0->unk_88C[v1->unk_1C8] != NULL) {
            VsRecorderViewerMain_SetState(v0, 25);
        } else {
            VsRecorderViewerMain_SetState(v0, 28);
        }

        VsRecorderViewerList_PlayRingAnim(v0);
        break;
    case 3:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 24);
        break;
    }
}

static void VsRecorderViewerRecord_TouchHandlerRankBack(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderState *v0 = param2;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerRecord_RemoveDetailWindows(v0);
        VsRecorderViewerMain_SetState(v0, 28);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 27);
        break;
    }
}

static void VsRecorderViewerRecord_SetMenuSpriteVisibility(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_10[0].sprite, 1);
        FontOAM_SetDrawFlag(v0->unk_10[0].fontOAM, 1);
        ManagedSprite_SetPositionXY(v0->unk_10[1].sprite, 128, 232 - 64);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_10[0].sprite, 0);
        FontOAM_SetDrawFlag(v0->unk_10[0].fontOAM, 0);
        ManagedSprite_SetPositionXY(v0->unk_10[1].sprite, 80, 232 - 64);
    }

    FontOAM_SetXY(v0->unk_10[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_10[1].fontOAM, 36, -8);
}

static void VsRecorderViewerRecord_CreateMainScreenSprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadSpriteResourceSetA(param0, NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->unk_10[0].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DMAIN);
    v0->unk_10[1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DMAIN);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_10[0], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DMAIN);
    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_10[1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DMAIN);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 111);

    ManagedSprite_SetPositionXY(v0->unk_10[0].sprite, 32, 232 - 64);
    ManagedSprite_SetPositionXY(v0->unk_10[1].sprite, 128, 232 - 64);
    FontOAM_SetXY(v0->unk_10[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_10[1].fontOAM, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_10[0].fontOAM, 1);
    FontOAM_SetDrawFlag(v0->unk_10[1].fontOAM, 1);
    ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
    ManagedSprite_SetAnim(v0->unk_10[1].sprite, 1);

    VsRecorderViewerRecord_SetMenuSpriteVisibility(param0, 0);
}

static void VsRecorderViewerRecord_FreeMainScreenSprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_10[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_10[1]);

    Sprite_DeleteAndFreeResources(v0->unk_10[0].sprite);
    Sprite_DeleteAndFreeResources(v0->unk_10[1].sprite);

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerRecord_SetViewToggleSprite(VsRecorderState *param0, int param1)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_10[1].sprite, 1);
        FontOAM_SetDrawFlag(v0->unk_10[1].fontOAM, 1);
        ManagedSprite_SetPositionXY(v0->unk_10[0].sprite, 32, 232);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_10[1].sprite, 0);
        FontOAM_SetDrawFlag(v0->unk_10[1].fontOAM, 0);
        ManagedSprite_SetPositionXY(v0->unk_10[0].sprite, 80, 232);
    }

    FontOAM_SetXY(v0->unk_10[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_10[1].fontOAM, 36, -8);
}

static void VsRecorderViewerRecord_CreateSubScreenSprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadSpriteResourceSetA(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_10[0].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);
    v0->unk_10[1].sprite = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_10[0], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_10[1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);

    if (param0->unk_86C == 210) {
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 111);
        ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
        ManagedSprite_SetAnim(v0->unk_10[1].sprite, 1);
    } else {
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
        VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);
        ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
        ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);
    }

    ManagedSprite_SetPositionXY(v0->unk_10[0].sprite, 32, 232);
    ManagedSprite_SetPositionXY(v0->unk_10[1].sprite, 128, 232);
    FontOAM_SetXY(v0->unk_10[0].fontOAM, 36, -8);
    FontOAM_SetXY(v0->unk_10[1].fontOAM, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_10[0].fontOAM, 1);
    FontOAM_SetDrawFlag(v0->unk_10[1].fontOAM, 1);

    VsRecorderViewerRecord_SetViewToggleSprite(param0, 0);
}

static void VsRecorderViewerRecord_FreeSubScreenSprites(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_10[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_10[1]);

    Sprite_DeleteAndFreeResources(v0->unk_10[0].sprite);
    Sprite_DeleteAndFreeResources(v0->unk_10[1].sprite);

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static BOOL VsRecorderViewerRecord_ToggleViewState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
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

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_InitProfile(&v0->unk_80, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, 80, 3);
        } else {
            VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        param0->unk_08++;
        break;
    case 3:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 1);
            } else {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }
        break;
    default:
        v0->unk_1CC ^= 1;
        VsRecorderViewerRecord_DrawInfoMessage(param0, 121 + v0->unk_1CC);
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_CloseView(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerRecord_RemoveInfoWindow(param0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerList_SetDrawSuspended(param0, 1);
            VsRecorderViewerRecord_FreeSubScreenSprites(param0);
            VsRecorderViewerRecord_CreateSummarySprites(param0);
            VsRecorderViewerList_SetDrawSuspended(param0, 0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            VsRecorderViewerRecord_DrawHeaderText(param0, 100, 0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        return 1;
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_SpeciesDetailState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 84, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
            VsRecorderViewerRecord_DrawHeaderTextForProfile(param0, 102, v0->unk_1C8);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerRecord_CreateDetailWindows(param0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_CloseSpeciesDetailState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            VsRecorderViewerRecord_RemoveDetailWindows(param0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);
            param0->unk_08++;
        }
        break;
    case 2:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 2)) {
            VsRecorderViewerRecord_DrawHeaderTextForProfile(param0, 100, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_PlaybackUploadState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    switch (param0->unk_08) {
    case 0:
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 2)) {
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            VsRecorderViewerRecord_DrawHeaderTextForProfile(param0, 278, 0);
            VsRecorderViewerList_ResetRecordState(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:;
        if (VsRecorderViewerList_CheckRecordData(param0, v0->unk_1C8, v0->unk_79C)) {
            v0->unk_79C = 0;
            param0->unk_08++;
        }
        break;
    case 3:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 4:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        VsRecorderViewerRecord_DrawHeaderTextForProfile(param0, 280, 0);

        {
            u64 v2 = BattleRecording_GetSummaryValue(BattleRecording_GetSummary(), 4, 0);

            if (GlobalTerminalTransfer_UploadId2(VsRecorderViewerTransfer_GetTransfer(param0), v2) == 1) {
                param0->unk_08++;
            }
        }
        break;
    case 5:
        if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
            return 0;
        }

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            param0->unk_08++;
        } else {
            Sound_StopEffect(1381, 0);
            Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
            param0->unk_08++;
        }

        VsRecorderViewerRecord_DrawHeaderTextForProfile(param0, 281, 0);
        break;
    case 6:
        if (!TouchScreen_Tapped()) {
            break;
        }

        VsRecorderViewerList_RemoveMessageWindow(param0);
        VsRecorderViewerRecord_FreeSummarySprites(param0);

        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);

        VsRecorderViewerList_FreeBattleRecordings(param0);
        VsRecorderViewerList_LoadBattleRecordings(param0);
        VsRecorderViewerList_ResetWindow(&param0->unk_14.listWindow);
        param0->unk_08++;
        break;
    case 7:
        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        TouchScreenActions_Free(v0->unk_608[2]);

        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRecord_FreeRecordProfile(param0);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        NetworkIcon_CreateOnSubScreen(1, HEAP_ID_102);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }
        if (VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0)) {
            VsRecorderViewerList_BlendPalettes(param0);
            VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);

            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.themeColor);

            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);

            Heap_Free(v0);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 3);
            Bg_ClearTilemap(param0->unk_14.bgConfig, 7);

            if (BattleRecording_Exists() == 1) {
                BattleRecording_Free();
            }
        } else {
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.themeColor);
            PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_RestoreBoxViewState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        if (param0->unk_86C == 210) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);
            ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);
        }

        VsRecorderViewerRecord_RemoveInfoWindow(param0);
        VsRecorderViewerRecord_CreateInfoWindow(param0);

        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
            VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
            VsRecorderViewerList_InitProfile(&v0->unk_80, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 80, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 6, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_ReopenBoxViewState(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_RemoveMessageWindow(param0);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 2);
        Bg_ClearTilemap(param0->unk_14.bgConfig, 6);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            VsRecorderViewerRecord_FreeSummarySprites(param0);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    case 2:
        VsRecorderViewerRecord_CreateSubScreenSprites(param0);

        if (param0->unk_86C == 210) {
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[0], &param0->unk_14, 3);
            VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_10[1], &param0->unk_14, 94);
            ManagedSprite_SetAnim(v0->unk_10[0].sprite, 0);
            ManagedSprite_SetAnim(v0->unk_10[1].sprite, 3);
        }

        VsRecorderViewerRecord_CreateInfoWindow(param0);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.narc, 62, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_InitSummary(&v0->unk_10C, param0);
            VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 0);
            VsRecorderViewerList_LoadBgTilemap(param0, VsRecorderViewerList_GetSummaryResultMessageID(&v0->unk_10C), 3);
        } else {
            VsRecorderViewerList_InitProfile(&v0->unk_80, param0);
            VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 0);
            Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 80, param0->unk_14.bgConfig, 3, 0, 0, 0, HEAP_ID_102);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.narc, 6, param0->unk_14.bgConfig, 7, 0, 0, 0, HEAP_ID_102);
        param0->unk_08++;
        break;
    case 3:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            if (v0->unk_1CC == 0) {
                VsRecorderViewerList_SetSummarySpritesVisible(&v0->unk_10C, 1);
            } else {
                VsRecorderViewerList_SetProfileSpritesVisible(&v0->unk_80, 1);
            }

            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.palette, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.themeColor);
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL VsRecorderViewerRecord_Exit(VsRecorderState *param0)
{
    VsRecorderViewerRecordContext *v0 = param0->unk_860;

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
        VsRecorderViewerList_SetDrawSuspended(param0, 1);

        if (v0->unk_1CC == 0) {
            VsRecorderViewerList_FreeSummary(&v0->unk_10C, param0);
        } else {
            VsRecorderViewerList_FreeProfile(&v0->unk_80, param0);
        }

        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        TouchScreenActions_Free(v0->unk_608[0]);
        TouchScreenActions_Free(v0->unk_608[1]);
        TouchScreenActions_Free(v0->unk_608[2]);

        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRecord_FreeRecordProfile(param0);
        VsRecorderViewerRecord_RemoveInfoWindow(param0);
        VsRecorderViewerRecord_FreeSubScreenSprites(param0);
        VsRecorderViewerMenu_InitMenuWithExtraEntry(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerMain_SetPendingSelection(param0, *(param0->unk_10));
        VsRecorder_SetPlaybackRequest(param0->unk_868, 1, 0);
        param0->unk_08++;
        break;
    default:
        return 1;
    }

    return 0;
}

void VsRecorderViewerRecord_SetBattleRecordingId(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;
    VsRecorderViewerRecordContext *v1 = v0->unk_860;

    if (param1->done == 1) {
        (void)0;
    } else {
        u64 v2;

        v2 = GlobalTerminalGds_GetBattleRecording(VsRecorderViewerTransfer_GetTransfer(v0));
        v1->unk_4B0 = v2;
    }
}

void VsRecorderViewerRecord_LoadRecordAlt(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;

    if (param1->done == 1) {
        (void)0;
    } else {
        GlobalTerminalGds_GetRecordAlt(VsRecorderViewerTransfer_GetTransfer(v0), &v0->unk_8B4.record);
        VsRecorderViewerList_StoreBattleRecording(v0);
        v0->unk_8B4.recordFlag = v0->unk_8B4.record->data.isSaved;
    }
}

void VsRecorderViewerRecord_Noop(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderState *v0 = param0;

    if (param1->done == 1) {
        (void)0;
    } else {
        (void)0;
    }
}

static void VsRecorderViewerRecord_DrawRecordId(VsRecorderViewerRecordContext *param0, VsRecorderState *param1)
{
    String *v0;
    String *v1;
    String *v2;
    StringTemplate *v3;
    Window *v4;

    v3 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

    {
        u64 v5 = param0->unk_4B0;
        u64 v6 = v5;
        u32 v7[3];
        String *v8 = String_Init(255, HEAP_ID_102);
        String *v9 = String_Init(255, HEAP_ID_102);
        String *v10 = String_Init(255, HEAP_ID_102);

        v4 = &param1->unk_8A4;
        v7[0] = v6 % 100000;
        v6 /= 100000;
        v7[1] = v6 % 100000;
        v6 /= 100000;
        v7[2] = v6;
        v1 = MessageLoader_GetNewString(param1->unk_14.messageLoader, 295);
        v2 = String_Init(255, HEAP_ID_102);

        String_FormatInt(v8, v7[0], 5, 2, 1);
        String_FormatInt(v9, v7[1], 5, 2, 1);
        String_FormatInt(v10, v7[2], 2, 2, 1);
        StringTemplate_SetString(v3, 2, v8, 0, 1, GAME_LANGUAGE);
        StringTemplate_SetString(v3, 1, v9, 0, 1, GAME_LANGUAGE);
        StringTemplate_SetString(v3, 0, v10, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v3, v2, v1);
        Window_FillTilemap(v4, 0xCC);
        Text_AddPrinterWithParamsAndColor(v4, FONT_SYSTEM, v2, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v4);
        String_Free(v8);
        String_Free(v9);
        String_Free(v10);
        String_Free(v1);
        String_Free(v2);
        StringTemplate_ClearArgs(v3);
    }

    StringTemplate_Free(v3);
}
