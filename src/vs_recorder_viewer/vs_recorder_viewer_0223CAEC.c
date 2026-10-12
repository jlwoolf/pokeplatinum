#include "vs_recorder_viewer/vs_recorder_viewer_0223CAEC.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BDAC.h"
#include "global_terminal/struct_global_terminal_0222BDAC_1.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_const_funcptr_tables.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223D518_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223DF10.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02249380.h"

#include "bg_window.h"
#include "game_records.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "palette.h"
#include "play_time.h"
#include "save_player.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "font_oam.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"
#include "vs_recorder.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    Window unk_24[6];
    Window unk_84[2];
    VsRecorderViewerTextSprite unk_A4[2];
    TouchScreenActions *unk_DC;
    GlobalTerminalPlayTimeData unk_E0;
    GlobalTerminalPlayTimeDataAlt unk_638;
    VsRecorderViewerRankingsPlayTime unk_710;
    GlobalTerminalPlayTimeData *unk_714;
    GlobalTerminalPlayTimeDataAlt *unk_718;
    VsRecorderViewerRankingsPlayTime *unk_71C;
    VsRecorderViewerRankingsUploadProfile unk_720;
    MessageLoader *unk_744;
    String *unk_748;
    VsRecorderViewerListEntry unk_74C[3][20];
    VsRecorderViewerListConfig unk_B0C;
} VsRecorderViewerRankingsScreen;

static void VsRecorderViewerRankings_InitRankingList(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_PopulateEntries(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_CreateHeaderWindows(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_RemoveHeaderWindows(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_CreateMessageWindows(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_RemoveMessageWindows(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_DrawPlayerProfileHeader(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_LayoutArrowSprites(VsRecorderViewerState *param0, int param1);
static void VsRecorderViewerRankings_CreateArrowSprites(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_FreeArrowSprites(VsRecorderViewerState *param0);
static void VsRecorderViewerRankings_SetEntryCount(VsRecorderViewerRankingsScreen *param0);
static void VsRecorderViewerRankings_HandleTouchInput(u32 param0, enum TouchScreenButtonState param1, void *param2);
int VsRecorderViewerList_CountDigits(u64 param0);
void VsRecorderViewerRankings_LoadPlayTime(void *param0, const VsRecorderViewerTransferStatus *param1);
void VsRecorderViewerRankings_LoadPlayTimeProfile(void *param0, const VsRecorderViewerTransferStatus *param1);
static BOOL VsRecorderViewerRankings_Init(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_FadeIn(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_UploadPlayTime(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_Unused(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_RefreshEntries(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_LoadGraphics(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_HandleInput(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_Exit(VsRecorderViewerState *param0);
static BOOL VsRecorderViewerRankings_Free(VsRecorderViewerState *param0);

BOOL (*const sVsRecorderViewerRankingsStateTable[])(VsRecorderViewerState *) = {
    VsRecorderViewerRankings_Init,
    VsRecorderViewerRankings_FadeIn,
    VsRecorderViewerRankings_UploadPlayTime,
    VsRecorderViewerRankings_Unused,
    VsRecorderViewerRankings_RefreshEntries,
    VsRecorderViewerRankings_LoadGraphics,
    VsRecorderViewerRankings_HandleInput,
    VsRecorderViewerRankings_Exit,
    VsRecorderViewerRankings_Free,
};

static const int sVsRecorderViewerRankingsMessageWindowLayout[][4] = {
    { 0x4, 0x3, 0x18, 0x4 },
    { 0x4, 0x9, 0x18, 0x4 }
};

static const int sVsRecorderViewerRankingsMessageWindowLayoutAlt[][4] = {
    { 0x4, 0x3, 0x18, 0x4 },
    { 0x4, 0x9, 0x18, 0x4 }
};

static const int sVsRecorderViewerRankingsHeaderWindowLayout[][4] = {
    { 0x7, 0x4, 0x12, 0x2 },
    { 0x7, 0xB, 0x12, 0x2 }
};

static const VsRecorderViewerListConfig sVsRecorderViewerRankingsListConfig = {
    NULL,
    0xC,
    0x1,
    0x4,
    0xF,
    0x18,
    0x8,
    0x100,
    0x2,
    0x4,
    NULL
};

static const VsRecorderViewerListConfig sVsRecorderViewerRankingsListConfigAlt = {
    NULL,
    0xC,
    0x2,
    0x4,
    0xF,
    0x18,
    0x8,
    0x100,
    0x2,
    0x2,
    NULL
};

static void VsRecorderViewerRankings_InitRankingList(VsRecorderViewerState *a0)
{
    VsRecorderViewerRankingsScreen *r4 = a0->unk_860;
    if (r4->unk_1C == 0) {
        r4->unk_B0C = sVsRecorderViewerRankingsListConfig;
        r4->unk_748 = NULL;
    } else {
        r4->unk_B0C = sVsRecorderViewerRankingsListConfigAlt;
        r4->unk_748 = MessageLoader_GetNewString(a0->unk_14.unk_38, r4->unk_714->unk_00[r4->unk_0C].unk_00 + 0x5e);
    }
    r4->unk_B0C.unk_04 = r4->unk_20;
    r4->unk_B0C.unk_00 = r4->unk_74C[r4->unk_0C];
    VsRecorderViewerList_SetDrawSuspended(a0, 1);
    VsRecorderViewerList_ResetWindow(&a0->unk_14.unk_48C);
    VsRecorderViewerList_InitRankingWindow(&a0->unk_14.unk_48C, a0, r4->unk_744, &r4->unk_B0C, r4->unk_0C, r4->unk_14, r4->unk_748);
    VsRecorderViewerList_UpdateScrollBarVisibility(&a0->unk_14.unk_46C, &a0->unk_14.unk_48C);
    VsRecorderViewerList_LoadArrowSprites(&a0->unk_14.unk_48C, a0, 1);
    VsRecorderViewerList_SetArrowSpritesPosition(&a0->unk_14.unk_48C, 0x70, 0xb8);
    VsRecorderViewerList_SetDrawSuspended(a0, 0);
}

static void VsRecorderViewerRankings_PopulateEntries(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    int v1;
    u64 v2;

    v0->unk_714 = &v0->unk_E0;
    v0->unk_718 = &v0->unk_638;

    switch (v0->unk_14) {
    case 0: {
        for (v1 = 0; v1 < 16; v1++) {
            if (v0->unk_1C == 0) {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 10000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = VsRecorderViewerList_GetAppearanceFileIndex(v0->unk_718->unk_00[v0->unk_0C].unk_04[v1], 4);
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v1;
            } else {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 20000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = VsRecorderViewerList_GetAppearanceFileIndex(v0->unk_714->unk_00[v0->unk_0C].unk_04[v1], 4);
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v0->unk_714->unk_00[v0->unk_0C].unk_14[v1];

                if (v0->unk_74C[v0->unk_0C][v1].unk_08 >= 9999999999999999999) {
                    v0->unk_74C[v0->unk_0C][v1].unk_08 = 9999999999999999999;
                }
            }
        }
    } break;
    case 1: {
        for (v1 = 0; v1 < 12; v1++) {
            if (v0->unk_1C == 0) {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 30000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = v0->unk_718->unk_00[v0->unk_0C].unk_14[v1];
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v1;
            } else {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 40000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = v0->unk_714->unk_00[v0->unk_0C].unk_94[v1];
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v0->unk_714->unk_00[v0->unk_0C].unk_A0[v1];

                if (v0->unk_74C[v0->unk_0C][v1].unk_08 >= 9999999999999999999) {
                    v0->unk_74C[v0->unk_0C][v1].unk_08 = 9999999999999999999;
                }
            }
        }
    } break;
    case 2: {
        for (v1 = 0; v1 < 20; v1++) {
            if (v0->unk_1C == 0) {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 50000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = v0->unk_718->unk_00[v0->unk_0C].unk_20[v1];
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v1;
            } else {
                v0->unk_74C[v0->unk_0C][v1].unk_00 = 60000;
                v0->unk_74C[v0->unk_0C][v1].unk_04 = v0->unk_714->unk_00[v0->unk_0C].unk_100[v1];
                v0->unk_74C[v0->unk_0C][v1].unk_08 = v0->unk_714->unk_00[v0->unk_0C].unk_128[v1];

                if (v0->unk_74C[v0->unk_0C][v1].unk_08 >= 9999999999999999999) {
                    v0->unk_74C[v0->unk_0C][v1].unk_08 = 9999999999999999999;
                }
            }
        }
    } break;
    }
}

static void VsRecorderViewerRankings_CreateHeaderWindows(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    String *v5;

    for (v3 = 0; v3 < 2; v3++) {
        v1 = &v0->unk_84[v3];
        Window_Add(param0->unk_14.unk_10, v1, 6, sVsRecorderViewerRankingsHeaderWindowLayout[v3][0], sVsRecorderViewerRankingsHeaderWindowLayout[v3][1], sVsRecorderViewerRankingsHeaderWindowLayout[v3][2], sVsRecorderViewerRankingsHeaderWindowLayout[v3][3], 14, v2);
        v2 += (sVsRecorderViewerRankingsHeaderWindowLayout[v3][2] * sVsRecorderViewerRankingsHeaderWindowLayout[v3][3]);
        Window_FillTilemap(v1, 0x0);

        v5 = MessageLoader_GetNewString(param0->unk_14.unk_34, 80 + v3);
        v4 = VsRecorderViewerList_CalcCenteredTextX(v1, v5);

        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v5, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v1);
        String_Free(v5);
    }
}

static void VsRecorderViewerRankings_RemoveHeaderWindows(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    Window *v1;
    int v2;

    for (v2 = 0; v2 < 2; v2++) {
        Window_ClearAndCopyToVRAM(&v0->unk_84[v2]);
        Window_Remove(&v0->unk_84[v2]);
    }
}

static void VsRecorderViewerRankings_CreateMessageWindows(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    String *v5;
    int v6;

    if (v0->unk_1C == 0) {
        v6 = NELEMS(sVsRecorderViewerRankingsMessageWindowLayout);
    } else {
        v6 = NELEMS(sVsRecorderViewerRankingsMessageWindowLayoutAlt);
    }

    for (v3 = 0; v3 < v6; v3++) {
        v1 = &v0->unk_24[v3];

        Window_Init(v1);

        if (v0->unk_1C == 0) {
            Window_Add(param0->unk_14.unk_10, v1, 2, sVsRecorderViewerRankingsMessageWindowLayout[v3][0], sVsRecorderViewerRankingsMessageWindowLayout[v3][1], sVsRecorderViewerRankingsMessageWindowLayout[v3][2], sVsRecorderViewerRankingsMessageWindowLayout[v3][3], 14, v2);
            v2 += (sVsRecorderViewerRankingsMessageWindowLayout[v3][2] * sVsRecorderViewerRankingsMessageWindowLayout[v3][3]);
        } else {
            Window_Add(param0->unk_14.unk_10, v1, 2, sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][0], sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][1], sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][2], sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][3], 14, v2);
            v2 += (sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][2] * sVsRecorderViewerRankingsMessageWindowLayoutAlt[v3][3]);
        }

        Window_FillTilemap(v1, 0x0);

        v5 = MessageLoader_GetNewString(param0->unk_14.unk_34, 67);
        v4 = 0;

        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v5, v4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v1);
        String_Free(v5);
    }
}

static void VsRecorderViewerRankings_RemoveMessageWindows(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    Window *v1;
    int v2 = 1;
    int v3;
    int v4;
    String *v5;
    int v6;

    if (v0->unk_1C == 0) {
        v6 = NELEMS(sVsRecorderViewerRankingsMessageWindowLayout);
    } else {
        v6 = NELEMS(sVsRecorderViewerRankingsMessageWindowLayoutAlt);
    }

    for (v3 = 0; v3 < v6; v3++) {
        Window_ClearAndCopyToVRAM(&v0->unk_24[v3]);
        Window_Remove(&v0->unk_24[v3]);
    }
}

static u32 sVsRecorderViewerRankingsGameRecordIDs[87] = {
    0x49,
    0x4C,
    0x4E,
    0x4F,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0x5A,
    0x5B,
    0x5C,
    0x5D,
    0x5E,
    0x5F,
    0x60,
    0x61,
    0x62,
    0x63,
    0x64,
    0x4,
    0x0,
    0x7,
    0x8,
    0x9,
    0xA,
    0xB,
    0xC,
    0xE,
    0xF,
    0x13,
    0x15,
    0x16,
    0x17,
    0x18,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x23,
    0x28,
    0x29,
    0x2C,
    0x71,
    0x72,
    0x73,
    0x74,
    0x2D,
    0x75,
    0x2E,
    0x2F,
    0x30,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x3A,
    0x3B,
    0x3C,
    0x3D,
    0x3E,
    0x3F,
    0x40,
    0x41,
    0x42,
    0x43,
    0x44,
    0x45,
    0x76,
    0x77,
    0x46,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF
};

static u32 VsRecorderViewerRankings_GetGameRecordValue(VsRecorderViewerState *param0, int param1)
{
    u32 v0;
    int v1 = param1;

    if (v1 >= 87) {
        v1 = 0;
        GF_ASSERT(FALSE);
    }

    GF_ASSERT(sVsRecorderViewerRankingsGameRecordIDs[v1] != 0xFFFF);

    v0 = GameRecords_GetRecordValue(SaveData_GetGameRecords(param0->saveData), sVsRecorderViewerRankingsGameRecordIDs[v1]);

    return v0;
}

static void VsRecorderViewerRankings_DrawPlayerProfileHeader(VsRecorderViewerState *a0)
{
    VsRecorderViewerState *r5 = a0;
    VsRecorderViewerRankingsScreen *r4 = r5->unk_860;
    String *r7;
    String *sp1c;
    String *sp18;
    String *sp14 = String_Init(0xff, 0x66);
    StringTemplate *r6 = VsRecorderViewerList_NewStringTemplate(0x66);
    Window_FillTilemap(&r4->unk_24[0], 0);
    r7 = (r4->unk_1C == 0)
        ? MessageLoader_GetNewString(r5->unk_14.unk_38, r4->unk_718->unk_00[r4->unk_0C].unk_00 - 1)
        : MessageLoader_GetNewString(r5->unk_14.unk_38, r4->unk_714->unk_00[r4->unk_0C].unk_00 - 1);
    Text_AddPrinterWithParamsAndColor(&r4->unk_24[0], 0, r7, 0, 0, 0xff, 0x000f0d00, 0);
    Window_ScheduleCopyToVRAM(&r4->unk_24[0]);
    String_Free(r7);
    Window_FillTilemap(&r4->unk_24[1], 0);
    r7 = (r4->unk_1C == 0)
        ? MessageLoader_GetNewString(r5->unk_14.unk_34, r4->unk_14 + 0x52)
        : MessageLoader_GetNewString(r5->unk_14.unk_34, 0x5b);
    Text_AddPrinterWithParamsAndColor(&r4->unk_24[1], 0, r7, 0, 0, 0xff, 0x000f0d00, 0);
    Window_ScheduleCopyToVRAM(&r4->unk_24[1]);
    String_Free(r7);
    sp18 = PlayerProfile_GetName(r5->unk_88C[0], 0x66);
    VsRecorderViewerList_CheckNameChars(r5, sp18);
    switch (r4->unk_14) {
    case 0:
        int sp20 = PlayerProfile_GetAppearance(r5->unk_88C[0]);
        r7 = MessageLoader_GetNewString(r5->unk_14.unk_34, 0x55);
        sp1c = MessageLoader_GetNewString(r4->unk_744, VsRecorderViewerList_GetAppearanceFileIndex(sp20, 4));
        StringTemplate_SetString(r6, 0, sp1c, 0, 1, GAME_LANGUAGE);
        break;
    case 1:
        int sp24 = PlayerProfile_GetBirthdayMonth(r5->unk_88C[0]);
        r7 = MessageLoader_GetNewString(r5->unk_14.unk_34, 0x56);
        sp1c = String_Init(0xff, 0x66);
        StringTemplate_SetMonthName(r6, 0, sp24);
        break;
    case 2:
        int sp10 = PlayerProfile_GetSpecies(r5->unk_88C[0]);
        int sp28 = PlayerProfile_GetIsEgg(r5->unk_88C[0]);
        r7 = MessageLoader_GetNewString(r5->unk_14.unk_34, 0x57);
        if (sp28) {
            sp10 = 0x1ee;
        }
        if (sp10) {
            sp1c = String_Init(0xff, 0x66);
            charcode_t sp2c[0xff];
            MessageLoader_GetSpeciesName(sp10, 0x66, sp2c);
            String_CopyChars(sp1c, sp2c);
        } else {
            sp1c = MessageLoader_GetNewString(r5->unk_14.unk_34, 0x15);
        }
        StringTemplate_SetString(r6, 0, sp1c, 0, 1, GAME_LANGUAGE);
        break;
    }
    StringTemplate_SetString(r6, 1, sp18, 0, 1, GAME_LANGUAGE);
    StringTemplate_Format(r6, sp14, r7);
    Text_AddPrinterWithParamsAndColor(&r4->unk_24[1], 0, sp14, 0, 0x10, 0xff, 0x000f0d00, 0);
    Window_ScheduleCopyToVRAM(&r4->unk_24[1]);
    String_Free(r7);
    String_Free(sp1c);
    String_Free(sp14);
    String_Free(sp18);
    StringTemplate_ClearArgs(r6);
    StringTemplate_Free(r6);
}

static void VsRecorderViewerRankings_LayoutArrowSprites(VsRecorderViewerState *param0, int param1)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    if (param1 == 0) {
        ManagedSprite_SetDrawFlag(v0->unk_A4[0].unk_08, 1);
        FontOAM_SetDrawFlag(v0->unk_A4[0].unk_0C, 1);
        ManagedSprite_SetPositionXY(v0->unk_A4[1].unk_08, 128, 232);
    } else {
        ManagedSprite_SetDrawFlag(v0->unk_A4[0].unk_08, 0);
        FontOAM_SetDrawFlag(v0->unk_A4[0].unk_0C, 0);
        ManagedSprite_SetPositionXY(v0->unk_A4[1].unk_08, 80, 232);
    }

    FontOAM_SetXY(v0->unk_A4[0].unk_0C, 36, -8);
    FontOAM_SetXY(v0->unk_A4[1].unk_0C, 36, -8);
}

static void VsRecorderViewerRankings_CreateArrowSprites(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    VsRecorderViewerMenu_LoadCursorSpriteResources(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    v0->unk_A4[0].unk_08 = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);
    v0->unk_A4[1].unk_08 = VsRecorderViewerMenu_CreateCursorSprite(param0, NNS_G2D_VRAM_TYPE_2DSUB);

    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_A4[0], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_InitLabelOAM(&v0->unk_A4[1], &param0->unk_14, NNS_G2D_VRAM_TYPE_2DSUB);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_A4[0], &param0->unk_14, 53);
    VsRecorderViewerMenu_SetLabelOAMText(&v0->unk_A4[1], &param0->unk_14, 3);

    ManagedSprite_SetPositionXY(v0->unk_A4[0].unk_08, 32, 232);
    ManagedSprite_SetPositionXY(v0->unk_A4[1].unk_08, 128, 232);
    FontOAM_SetXY(v0->unk_A4[0].unk_0C, 36, -8);
    FontOAM_SetXY(v0->unk_A4[1].unk_0C, 36, -8);
    FontOAM_SetDrawFlag(v0->unk_A4[0].unk_0C, 0);
    FontOAM_SetDrawFlag(v0->unk_A4[1].unk_0C, 1);

    VsRecorderViewerRankings_LayoutArrowSprites(param0, 1);
}

static void VsRecorderViewerRankings_FreeArrowSprites(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_A4[0]);
    VsRecorderViewerMenu_FreeLabelOAM(&v0->unk_A4[1]);

    Sprite_DeleteAndFreeResources(v0->unk_A4[0].unk_08);
    Sprite_DeleteAndFreeResources(v0->unk_A4[1].unk_08);

    VsRecorderViewerMenu_FreeCursorSpriteResources(param0);
}

static void VsRecorderViewerRankings_SetEntryCount(VsRecorderViewerRankingsScreen *param0)
{
    int v0[] = { 16, 12, 20 };

    param0->unk_20 = v0[param0->unk_14];
}

static const TouchScreenRect sVsRecorderViewerRankingsTouchRects[] = {
    { 0x18, 0x38, 0x30, 0xD0 },
    { 0x50, 0x70, 0x30, 0xD0 },
    { 0x98, 0xB8, 0x50, 0xB0 }
};

static void VsRecorderViewerRankings_HandleTouchInput(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    VsRecorderViewerState *v0 = param2;
    VsRecorderViewerRankingsScreen *v1 = v0->unk_860;

    if (param1 != TOUCH_BUTTON_PRESSED) {
        return;
    }

    switch (param0) {
    case 0:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_0C++;
        v1->unk_0C %= v1->unk_10;
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    case 1:
        VsRecorderViewerList_PlayRingAnim(v0);
        v1->unk_14++;
        v1->unk_14 %= v1->unk_18;
        VsRecorderViewerMain_SetState(v0, 4);
        break;
    default:
        VsRecorderViewerList_PlayRingAnim(v0);
        VsRecorderViewerMain_SetState(v0, 7);
        break;
    }
}

static BOOL VsRecorderViewerRankings_Init(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = Heap_Alloc(HEAP_ID_102, sizeof(VsRecorderViewerRankingsScreen));

    memset(v0, 0, sizeof(VsRecorderViewerRankingsScreen));

    param0->unk_860 = v0;
    v0->unk_1C = param0->unk_86C;
    v0->unk_10 = 3;

    if (VsRecorder_CheckFirstArrivalBattlePark(param0) == 0) {
        v0->unk_10--;
    }

    v0->unk_18 = 3;
    VsRecorderViewerRankings_SetEntryCount(v0);
    v0->unk_744 = param0->unk_14.unk_34;

    Bg_ClearTilemap(param0->unk_14.unk_10, 2);
    Bg_ClearTilemap(param0->unk_14.unk_10, 3);
    Bg_ClearTilemap(param0->unk_14.unk_10, 6);
    Bg_ClearTilemap(param0->unk_14.unk_10, 7);

    VsRecorderViewerMenu_SetDefaultBlendAlpha(&v0->unk_00, &v0->unk_04, 0);
    v0->unk_DC = TouchScreenActions_RegisterHandler(sVsRecorderViewerRankingsTouchRects, NELEMS(sVsRecorderViewerRankingsTouchRects), VsRecorderViewerRankings_HandleTouchInput, param0, HEAP_ID_102);
    VsRecorderViewerMain_SetState(param0, 1);

    return 0;
}

static BOOL VsRecorderViewerRankings_FadeIn(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

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
        VsRecorderViewerRankings_CreateArrowSprites(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        Bg_SetPriority(BG_LAYER_MAIN_0, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 3);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_3, 1);

        Bg_SetPriority(BG_LAYER_SUB_0, 1);
        Bg_SetPriority(BG_LAYER_SUB_1, 3);
        Bg_SetPriority(BG_LAYER_SUB_2, 0);
        Bg_SetPriority(BG_LAYER_SUB_3, 2);

        VsRecorderViewerList_StartNetworkTask(param0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        param0->unk_08++;
        break;
    default:
        if (VsRecorderViewerList_IsNetworkTaskDone(param0) == 0) {
            break;
        }

        VsRecorderViewerMain_SetState(param0, 2);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRankings_UploadPlayTime(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;
    VsRecorderViewerTransferStatus *v1;

    if (VsRecorderViewerTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetupRing(param0, param0->unk_6F0, 128, 96);
        VsRecorderRing_SetVisible(param0->unk_6F0, 1);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 24, 24);
        VsRecorderViewerList_OpenMainMessage(param0, 279);
        Sound_PlayEffect(SEQ_SE_PL_BREC80_sseq);
        param0->unk_08++;
        break;
    case 1:
        if (GlobalTerminalTransfer_UploadPlayTime(VsRecorderViewerTransfer_GetTransfer(param0)) == 1) {
            param0->unk_08++;
        }
        break;
    case 2:
        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_CloseMainMessage(param0);
            VsRecorderViewerList_OpenMessage(param0, 4, v1->unk_0C, v1->unk_04);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            param0->unk_08 = 5;
        } else {
            {
                v0->unk_71C = &v0->unk_710;
                v0->unk_720.unk_08.unk_00 = PlayTime_GetHours(SaveData_GetPlayTime(param0->saveData));
                v0->unk_720.unk_08.unk_02 = PlayTime_GetMinutes(SaveData_GetPlayTime(param0->saveData));
                v0->unk_720.unk_08.unk_03 = PlayTime_GetSeconds(SaveData_GetPlayTime(param0->saveData));
                v0->unk_720.unk_0C[0].unk_00 = v0->unk_71C->unk_00[0];
                v0->unk_720.unk_0C[1].unk_00 = v0->unk_71C->unk_00[1];
                v0->unk_720.unk_0C[2].unk_00 = v0->unk_71C->unk_00[2];
                v0->unk_720.unk_0C[0].unk_04 = VsRecorderViewerRankings_GetGameRecordValue(param0, v0->unk_720.unk_0C[0].unk_00 - 1);
                v0->unk_720.unk_0C[1].unk_04 = VsRecorderViewerRankings_GetGameRecordValue(param0, v0->unk_720.unk_0C[1].unk_00 - 1);
                v0->unk_720.unk_0C[2].unk_04 = VsRecorderViewerRankings_GetGameRecordValue(param0, v0->unk_720.unk_0C[2].unk_00 - 1);
            }
            Sound_StopEffect(1381, 0);
            param0->unk_08++;
        }
        break;
    case 3:
        if (GlobalTerminalTransfer_UploadPlayTimeProfile(VsRecorderViewerTransfer_GetTransfer(param0), param0->unk_88C[0], &v0->unk_720.unk_0C[0]) == 1) {
            param0->unk_08++;
        }
        break;
    case 4:
        VsRecorderViewerList_CloseMainMessage(param0);

        if (GlobalTerminalTransfer_GetState(VsRecorderViewerTransfer_GetTransfer(param0), &v1) == 1) {
            Sound_StopEffect(1381, 0);
            VsRecorderViewerList_OpenMessage(param0, 5, v1->unk_0C, v1->unk_04);
            VsRecorderRing_SetVisible(param0->unk_6F0, 0);
            param0->unk_08 = 5;
        } else {
            BOOL v2 = 0;

            if (v0->unk_1C == 0) {
                if ((v0->unk_718->unk_00[0].unk_00 == 0) || (v0->unk_718->unk_00[1].unk_00 == 0) || (v0->unk_718->unk_00[2].unk_00 == 0)) {
                    v2 = 1;
                }
            } else {
                if ((v0->unk_714->unk_00[0].unk_00 == 0) || (v0->unk_714->unk_00[1].unk_00 == 0) || (v0->unk_714->unk_00[2].unk_00 == 0)) {
                    v2 = 1;
                }
            }

            if (v2) {
                VsRecorderViewerList_OpenMessage(param0, 5, 0, 0);
                param0->unk_14.unk_4F0.unk_0C = 300;
                VsRecorderRing_SetVisible(param0->unk_6F0, 0);
                param0->unk_08 = 5;
            } else {
                Sound_StopEffect(1381, 0);
                Sound_PlayEffect(SEQ_SE_PL_BREC12_sseq);
                param0->unk_08 = 0xFF;
            }
        }
        break;
    case 5:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRankings_FreeArrowSprites(param0);

        TouchScreenActions_Free(v0->unk_DC);

        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);

        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
        VsRecorderViewerList_StartNetworkTask(param0, 1);
        param0->unk_08++;
        break;
    case 6:
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
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        }
        break;
    default:
        VsRecorderViewerRankings_PopulateEntries(param0);
        VsRecorderRing_SetVisible(param0->unk_6F0, 0);
        VsRecorderRing_SetOrbitRadii(param0->unk_6F0, 0, 0);
        VsRecorderViewerMain_SetState(param0, 5);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRankings_LoadGraphics(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilesToBgLayerFromOpenNARC(param0->unk_14.unk_00, 62, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.unk_00, 33, param0->unk_14.unk_10, 3, 0, 0, 0, HEAP_ID_102);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.unk_00, 34, param0->unk_14.unk_10, 7, 0, 0, 0, HEAP_ID_102);

        VsRecorderViewerRankings_CreateMessageWindows(param0);
        VsRecorderViewerRankings_DrawPlayerProfileHeader(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_InitScrollBarWithAnim(&param0->unk_14.unk_46C, param0, 2);
        VsRecorderViewerRankings_InitRankingList(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderViewerRankings_CreateHeaderWindows(param0);

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_08++;
        break;

    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 0);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 0)) {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 6);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRankings_HandleInput(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    VsRecorderViewerList_HandleScrollBarInput(&param0->unk_14.unk_46C);
    VsRecorderViewerList_ScrollList(&param0->unk_14.unk_48C, param0->unk_14.unk_46C.unk_10);
    VsRecorderViewerList_UpdateRankingWindow(&param0->unk_14.unk_48C, param0, v0->unk_0C, v0->unk_14, v0->unk_748);

    TouchScreenActions_HandleAction(v0->unk_DC);

    return 0;
}

static BOOL VsRecorderViewerRankings_Exit(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerList_FreeScrollBar(&param0->unk_14.unk_46C);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.unk_48C);

        if (v0->unk_748) {
            String_Free(v0->unk_748);
        }

        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.unk_48C, param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        VsRecorderRing_SetVisible(param0->unk_6F4, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerMenu_StepFadeValue(&v0->unk_08, 1);

        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 0)) {
            param0->unk_08++;
        }

        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 8);
        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRankings_Free(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerRankings_RemoveHeaderWindows(param0);
        VsRecorderViewerRankings_RemoveMessageWindows(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerRankings_FreeArrowSprites(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        TouchScreenActions_Free(v0->unk_DC);
        param0->unk_08++;
        break;
    case 1:
        VsRecorderViewerList_SetDrawSuspended(param0, 1);
        VsRecorderViewerMenu_ResetFadeValue(&v0->unk_08);
        VsRecorderViewerMenu_InitMenu(param0);
        VsRecorderViewerList_SetDrawSuspended(param0, 0);
        Bg_ClearTilemap(param0->unk_14.unk_10, 2);
        Bg_ClearTilemap(param0->unk_14.unk_10, 6);
        Bg_ClearTilemap(param0->unk_14.unk_10, 3);
        Bg_ClearTilemap(param0->unk_14.unk_10, 7);
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
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xC, 16, param0->unk_14.unk_44);
            VsRecorderViewerMain_AdvanceState(param0, 1, 1, param0->unk_10);
            VsRecorderViewerMain_SetState(param0, 5);
            Heap_Free(v0);
        } else {
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0x2, v0->unk_08, param0->unk_14.unk_44);
            PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xC, v0->unk_08, param0->unk_14.unk_44);
        }

        break;
    }

    return 0;
}

static BOOL VsRecorderViewerRankings_Unused(VsRecorderViewerState *param0)
{
    GF_ASSERT(FALSE);
    return 0;
}

static BOOL VsRecorderViewerRankings_RefreshEntries(VsRecorderViewerState *param0)
{
    VsRecorderViewerRankingsScreen *v0 = param0->unk_860;

    switch (param0->unk_08) {
    case 0:
        VsRecorderViewerRankings_PopulateEntries(param0);
        VsRecorderViewerRankings_SetEntryCount(v0);
        VsRecorderViewerRankings_RemoveMessageWindows(param0);
        VsRecorderViewerList_FreeWindow(&param0->unk_14.unk_48C);

        if (v0->unk_748) {
            String_Free(v0->unk_748);
        }

        VsRecorderViewerList_FreeArrowSprites(&param0->unk_14.unk_48C, param0);
        param0->unk_08++;
        break;
    case 1:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 1, 1)) {
            param0->unk_08++;
        }
        break;
    case 2:
        if (VsRecorderViewerMenu_StepBlendAlpha(&v0->unk_00, &v0->unk_04, 0, 1)) {
            VsRecorderViewerRankings_CreateMessageWindows(param0);
            VsRecorderViewerRankings_DrawPlayerProfileHeader(param0);
            VsRecorderViewerRankings_InitRankingList(param0);
            param0->unk_08++;
        }
        break;
    default:
        VsRecorderViewerMain_SetState(param0, 6);
        break;
    }

    return 0;
}

void VsRecorderViewerRankings_LoadPlayTime(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderViewerState *v0 = param0;
    VsRecorderViewerRankingsScreen *v1 = v0->unk_860;

    if (param1->unk_00 == 1) {
        v1->unk_71C = &v1->unk_710;
    } else {
        VsRecorderViewerRankingsPlayTime *v2;
        int v3;

        GlobalTerminalGds_GetPlayTime(VsRecorderViewerTransfer_GetTransfer(v0), &v1->unk_71C);
        MI_CpuCopy8(v1->unk_71C, &v1->unk_710, sizeof(VsRecorderViewerRankingsPlayTime));
    }
}

void VsRecorderViewerRankings_LoadPlayTimeProfile(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderViewerState *v0 = param0;
    VsRecorderViewerRankingsScreen *v1 = v0->unk_860;

    if (param1->unk_00 == 1) {
        v1->unk_714 = &v1->unk_E0;
        v1->unk_718 = &v1->unk_638;
    } else {
        GlobalTerminalGds_GetPlayTimeProfile(VsRecorderViewerTransfer_GetTransfer(v0), &v1->unk_714, &v1->unk_718);
        MI_CpuCopy8(v1->unk_714, &v1->unk_E0, sizeof(GlobalTerminalPlayTimeData));
        MI_CpuCopy8(v1->unk_718, &v1->unk_638, sizeof(GlobalTerminalPlayTimeDataAlt));

        {
            int v2;

            for (v2 = 0; v2 < 3; v2++) {
                (void)0;
            }
        }
    }
}
