#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"
#include "constants/narc.h"
#include "constants/string.h"

#include "struct_decls/struct_0202F298_decl.h"
#include "struct_decls/struct_0202F41C_decl.h"
#include "struct_defs/struct_02030A80.h"
#include "struct_defs/struct_0208B878.h"
#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BE20.h"
#include "vs_recorder_viewer/vs_recorder_viewer.h"
#include "vs_recorder_viewer/vs_recorder_viewer_022300D8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02248408.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022323B8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233310.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223359C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233750.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233828.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233F74.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"

#include "bg_window.h"
#include "easy_chat_sentence.h"
#include "enums.h"
#include "font.h"
#include "game_records.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "palette.h"
#include "pokemon_icon.h"
#include "pokemon_sprite.h"
#include "savedata_misc.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_screen.h"
#include "font_oam.h"
#include "battle_recording.h"
#include "player_profile.h"
#include "vs_recorder_ring.h"

static void VsRecorderViewerList_ReplaceInvalidName(String *param0, enum HeapID heapID);

StringTemplate *VsRecorderViewerList_NewStringTemplate(enum HeapID heapID)
{
    return StringTemplate_New(4, 64, heapID);
}

int VsRecorderViewerList_GetThemeColorA(VsRecorderViewerState *param0)
{
    u32 v0[] = {
        0x73fa,
        0x771f,
        0x6f7b,
        0x6fff,
        0x4ebf,
        0x575e,
        0x5b9f,
    };

    return v0[param0->unk_14.unk_48];
}

int VsRecorderViewerList_GetThemeColorB(VsRecorderViewerState *param0)
{
    u32 v0[] = {
        0x1642,
        0x357f,
        0x3def,
        0x31f,
        0xbc,
        0x131,
        0x23f,
    };

    if (param0->unk_00 != 0) {
        return 0x7e05;
    }

    return v0[param0->unk_14.unk_48];
}

int VsRecorderViewerList_GetThemeGraphicsFileIndex(VsRecorderViewerState *param0, int param1)
{
    int v0[] = {
        102,
        103,
        104,
        105,
        106,
        129,
        134,
    };
    int v1[] = {
        107,
        108,
        109,
        110,
        111,
        130,
        135,
    };
    int v2[] = {
        117,
        118,
        119,
        120,
        121,
        132,
        137,
    };
    int v3[] = {
        112,
        113,
        114,
        115,
        116,
        131,
        136,
    };
    int v4 = param0->unk_14.unk_48;

    switch (param1) {
    case 0:
        return v0[v4];
    case 1:
        return v1[v4];
    case 2:
        return v2[v4];
    case 3:
        return v3[v4];
    }

    GF_ASSERT(FALSE);

    return v0[0];
}

void VsRecorderViewerList_LoadThemeGraphics(VsRecorderViewerState *param0, int param1)
{
    PaletteData *v0 = param0->unk_14.unk_14;
    SpriteSystem *v1 = param0->unk_14.unk_04;
    SpriteManager *v2 = param0->unk_14.unk_08;
    NARC *v3 = param0->unk_14.unk_00;

    PaletteData_LoadBufferFromFileStart(v0, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 3), HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
    PaletteData_LoadBufferFromFileStart(v0, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 3), HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * (8 + 1), PLTT_DEST(0));
    PaletteData_LoadBufferFromFileStart(v0, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 0), HEAP_ID_102, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    PaletteData_LoadBufferFromFileStart(v0, NARC_INDEX_RESOURCE__ENG__BATT_REC__BATT_REC_GRA, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 0), HEAP_ID_102, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    VsRecorderRing_LoadColorPalette(param0->unk_6F0, param0->unk_14.unk_48);
    VsRecorderRing_LoadColorPalette(param0->unk_6F0, param0->unk_14.unk_48);
    SpriteManager_UnloadPlttObjById(v2, 9999);
    SpriteManager_UnloadPlttObjById(v2, 10000);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v0, 2, v1, v2, v3, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 2), 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 9999);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(v0, 3, v1, v2, v3, VsRecorderViewerList_GetThemeGraphicsFileIndex(param0, 2), 0, 3, NNS_G2D_VRAM_TYPE_2DSUB, 10000);
}

void VsRecorderViewerList_BlendPalettes(VsRecorderViewerState *param0)
{
    PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_OBJ, 0xFFFF, 0, param0->unk_14.unk_44);
    PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_MAIN_BG, 0xFFFF, 0, param0->unk_14.unk_44);
    PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_OBJ, 0xFFFF, 0, param0->unk_14.unk_44);
    PaletteData_BlendMulti(param0->unk_14.unk_14, PLTTBUF_SUB_BG, 0xFFFF, 0, param0->unk_14.unk_44);
}

u16 *VsRecorderViewerList_LoadPokedexAlphabetical(enum HeapID heapID, int unused, int *pokedexLength)
{
    u32 pokedexSize;
    u16 *pokedexAlphabetical = LoadMemberFromNARC_OutFileSize(NARC_INDEX_APPLICATION__ZUKANLIST__ZKN_DATA__ZUKAN_DATA, 13, 0, heapID, 0, &pokedexSize);
    *pokedexLength = pokedexSize / sizeof(u16);

    return pokedexAlphabetical;
}

void VsRecorderViewerList_SetRecordTransferDone(VsRecorderViewerState *param0, BOOL param1)
{
    param0->unk_870 = param1;
}

BOOL VsRecorderViewerList_IsRecordTransferDone(VsRecorderViewerState *param0)
{
    return param0->unk_870;
}

void VsRecorderViewerList_OpenSubMessage(VsRecorderViewerState *param0, int param1)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;

    if (param0->unk_8A0 == 1) {
        return;
    }

    param0->unk_8A0 = 1;

    VsRecorderViewerMenu_LoadBgPanel(param0, 6, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    G2S_BlendNone();
    Bg_SetPriority(BG_LAYER_SUB_2, 0);
    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 1, 19, 30, 4, 14, 32);

    v0 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

void VsRecorderViewerList_CloseSubMessage(VsRecorderViewerState *param0)
{
    if (param0->unk_8A0 == 0) {
        return;
    }

    param0->unk_8A0 = 0;

    Window_ClearAndCopyToVRAM(&param0->unk_8A4);
    Window_Remove(&param0->unk_8A4);
    Bg_ClearTilemap(param0->unk_14.unk_10, 6);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    Bg_SetPriority(BG_LAYER_SUB_2, 2);

    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ, 7, 8);
}

void VsRecorderViewerList_RemoveMessageWindow(VsRecorderViewerState *param0)
{
    Window_ClearAndCopyToVRAM(&param0->unk_8A4);
    Window_Remove(&param0->unk_8A4);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

void VsRecorderViewerList_OpenMainMessage(VsRecorderViewerState *param0, int param1)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;

    if (param0->unk_8A0 == 1) {
        return;
    }

    param0->unk_8A0 = 1;

    VsRecorderViewerMenu_LoadBgPanel(param0, 2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 2, 1, 19, 30, 4, 14, 32);

    v0 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

void VsRecorderViewerList_UpdateMessageText(VsRecorderViewerState *param0, int param1)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;

    if (param0->unk_8A0 == 0) {
        return;
    }

    v0 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

void VsRecorderViewerList_CloseMainMessage(VsRecorderViewerState *param0)
{
    if (param0->unk_8A0 == 0) {
        return;
    }

    param0->unk_8A0 = 0;

    Window_ClearAndCopyToVRAM(&param0->unk_8A4);
    Window_Remove(&param0->unk_8A4);
    Bg_ClearTilemap(param0->unk_14.unk_10, 2);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
}

void VsRecorderViewerList_OpenSubMessageWithBlend(VsRecorderViewerState *param0, int param1)
{
    String *v0;
    Window *v1 = &param0->unk_8A4;

    if (param0->unk_8A0 == 1) {
        return;
    }

    if (param0->unk_89C == 1) {
        return;
    }

    param0->unk_8A0 = 1;
    param0->unk_89C = 1;

    G2S_BlendNone();

    Bg_SetPriority(BG_LAYER_SUB_2, 0);
    VsRecorderViewerMenu_LoadBgPanel(param0, 6, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    Window_Init(v1);
    Window_Add(param0->unk_14.unk_10, v1, 6, 1, 19, 30, 4, 14, 32);

    v0 = MessageLoader_GetNewString(param0->unk_14.unk_34, param1);

    Window_FillTilemap(v1, 0xCC);
    Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 12), NULL);
    Window_ScheduleCopyToVRAM(v1);
    String_Free(v0);
}

static void VsRecorderViewerList_InitProfileWindows(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
static void VsRecorderViewerList_FreeProfileWindows(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
static void VsRecorderViewerList_SetPokemonSpriteVisible(VsRecorderViewerProfilePanel *param0, int param1);
static void VsRecorderViewerList_FreePokemonSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
static void VsRecorderViewerList_LoadPokemonSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
static void VsRecorderViewerList_SetTrainerSpriteVisible(VsRecorderViewerProfilePanel *param0, int param1);
static void VsRecorderViewerList_FreeTrainerSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);
static void VsRecorderViewerList_LoadTrainerSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1);

static void VsRecorderViewerList_InitProfileWindows(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1;
    Window *v2;
    String *v3;

    {
        const s16 sVsRecorderViewerListProfileWindowRects[][4] = {
            { 0x4, 0x4, 0x18, 0x2 },
            { 0xF, 0x8, 0x5, 0x2 },
            { 0x10, 0x8, 0xD, 0x2 },
            { 0x4, 0xB, 0xB, 0x2 },
            { 0x4, 0xD, 0x18, 0x2 },
            { 0x4, 0xF, 0x18, 0x2 },
            { 0x4, 0x11, 0xB, 0x2 },
            { 0x4, 0x13, 0x18, 0x4 },
            { 0xFF, 0x0, 0x0, 0x0 },
            { 0x4, 0x15, 0x18, 0x2 }
        };

        const int sVsRecorderViewerListProfileMsgIDs[] = {
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14,
            0x14
        };

        v1 = 1;

        for (v0 = 0; v0 < 8; v0++) {
            v2 = &param0->unk_0C[v0];
            v3 = MessageLoader_GetNewString(param1->unk_14.unk_34, sVsRecorderViewerListProfileMsgIDs[v0]);
            Window_Init(v2);
            Window_Add(param1->unk_14.unk_10, v2, 2, sVsRecorderViewerListProfileWindowRects[v0][0], sVsRecorderViewerListProfileWindowRects[v0][1], sVsRecorderViewerListProfileWindowRects[v0][2], sVsRecorderViewerListProfileWindowRects[v0][3], 14, v1);
            Window_FillTilemap(v2, 0x00);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v3, VsRecorderViewerList_CalcCenteredTextX(v2, v3), 0, (0xff), ((u32)(((15 & (0xff)) << 16) | ((13 & (0xff)) << 8) | ((0 & (0xff)) << 0))), NULL);
            Window_ScheduleCopyToVRAM(v2);
            v1 += (sVsRecorderViewerListProfileWindowRects[v0][2] * sVsRecorderViewerListProfileWindowRects[v0][3]);
            String_Free(v3);
        }
    }

    {
        String *v6;
        String *v7;
        String *v8;
        StringTemplate *v9;
        Window *v10;
        PlayerProfile *v11;

        v11 = param0->unk_00;
        v9 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

        v10 = &param0->unk_0C[0];
        v6 = PlayerProfile_GetName(v11, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param1, v6);
        v7 = MessageLoader_GetNewString(param1->unk_14.unk_34, 13);
        v8 = String_Init(255, HEAP_ID_102);

        StringTemplate_SetString(v9, 0, v6, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v9, v8, v7);

        Window_FillTilemap(v10, 0x00);
        Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v10);

        String_Free(v6);
        String_Free(v7);
        String_Free(v8);
        StringTemplate_ClearArgs(v9);

        {
            int v12 = PlayerProfile_GetBirthdayMonth(v11);

            v10 = &param0->unk_0C[2];
            v6 = MessageLoader_GetNewString(param1->unk_14.unk_34, 15);
            v7 = PlayerProfile_GetName(v11, HEAP_ID_102);
            VsRecorderViewerList_CheckNameChars(param1, v7);
            v8 = String_Init(255, HEAP_ID_102);

            StringTemplate_SetMonthName(v9, 0, v12);
            StringTemplate_Format(v9, v8, v6);

            Window_FillTilemap(v10, 0x00);
            Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v10);

            String_Free(v6);
            String_Free(v7);
            String_Free(v8);
            StringTemplate_ClearArgs(v9);
        }

        {
            v10 = &param0->unk_0C[3];
            v8 = MessageLoader_GetNewString(param1->unk_14.unk_34, 16);
            Window_FillTilemap(v10, 0x00);
            Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v10);
            String_Free(v8);

            {
                int v13 = PlayerProfile_GetCountry(v11);
                int v14 = PlayerProfile_GetRegion(v11);

                v10 = &param0->unk_0C[4];
                Window_FillTilemap(v10, 0x00);
                if (v13 == 0) {
                    v8 = MessageLoader_GetNewString(param1->unk_14.unk_34, 21);

                    Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
                    Window_ScheduleCopyToVRAM(v10);
                    String_Free(v8);
                } else {
                    v8 = String_Init(255, HEAP_ID_102);
                    v6 = MessageLoader_GetNewString(param1->unk_14.unk_34, 22);
                    StringTemplate_SetCountryName(v9, 0, v13);
                    StringTemplate_Format(v9, v8, v6);

                    Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
                    Window_ScheduleCopyToVRAM(v10);
                    String_Free(v8);
                    String_Free(v6);
                    if (v14 != 0) {
                        v10 = &param0->unk_0C[5];
                        Window_FillTilemap(v10, 0x00);
                        v8 = String_Init(255, HEAP_ID_102);
                        v6 = MessageLoader_GetNewString(param1->unk_14.unk_34, 23);
                        StringTemplate_SetCityName(v9, 0, v13, v14);
                        StringTemplate_Format(v9, v8, v6);

                        Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, 4, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
                        Window_ScheduleCopyToVRAM(v10);
                        String_Free(v8);
                        String_Free(v6);
                    }
                }

                StringTemplate_ClearArgs(v9);
            }
        }

        {
            v10 = &param0->unk_0C[6];
            v8 = MessageLoader_GetNewString(param1->unk_14.unk_34, 17);
            Window_FillTilemap(v10, 0x00);
            Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v10);
            String_Free(v8);

            {
                EasyChatSentence v15;

                v10 = &param0->unk_0C[7];

                v8 = PlayerProfile_GetIntroMessage(v11, &v15, HEAP_ID_102);
                if (v8 == NULL) {
                    v8 = EasyChatSentence_ToString(&v15, HEAP_ID_102);
                }

                Window_FillTilemap(v10, 0x00);
                Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
                Window_ScheduleCopyToVRAM(v10);

                String_Free(v8);
            }
        }

        StringTemplate_Free(v9);
    }
}

static void VsRecorderViewerList_FreeProfileWindows(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    int v0;

    for (v0 = 0; v0 < 8; v0++) {
        Window_ClearAndCopyToVRAM(&param0->unk_0C[v0]);
        Window_Remove(&param0->unk_0C[v0]);
    }
}

static void VsRecorderViewerList_SetPokemonSpriteVisible(VsRecorderViewerProfilePanel *param0, int param1)
{
    if (param0->unk_04) {
        ManagedSprite_SetDrawFlag(param0->unk_04, param1);
    }
}

static void VsRecorderViewerList_FreePokemonSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    SpriteManager_UnloadCharObjById(param1->unk_14.unk_08, 100000);
    SpriteManager_UnloadPlttObjById(param1->unk_14.unk_08, 100000);
    SpriteManager_UnloadCellObjById(param1->unk_14.unk_08, 100000);
    SpriteManager_UnloadAnimObjById(param1->unk_14.unk_08, 100000);

    if (param0->unk_04) {
        Sprite_DeleteAndFreeResources(param0->unk_04);
        param0->unk_04 = NULL;
    }
}

static void VsRecorderViewerList_LoadPokemonSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1;
    int v2;
    int v3;
    u8 v4;
    SpriteSystem *v5;
    SpriteManager *v6;
    PaletteData *v7;
    SpriteTemplate v8;

    v5 = param1->unk_14.unk_04;
    v6 = param1->unk_14.unk_08;
    v7 = param1->unk_14.unk_14;

    v4 = SpriteSystem_LoadPaletteBuffer(v7, PLTTBUF_MAIN_OBJ, v5, v6, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, PokeIconPalettesFileIndex(), FALSE, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 100000);

    {
        int v9 = PokeIcon64KCellsFileIndex();
        SpriteSystem_LoadCellResObj(v5, v6, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, v9, FALSE, 100000);
    }

    {
        int v10 = PokeIcon64KAnimationFileIndex();
        SpriteSystem_LoadAnimResObj(v5, v6, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, v10, FALSE, 100000);
    }

    {
        int v11;

        v1 = PlayerProfile_GetSpecies(param0->unk_00);
        v3 = PlayerProfile_GetForm(param0->unk_00);
        v0 = PlayerProfile_GetIsEgg(param0->unk_00);

        if (v1 == 0) {
            return;
        }

        v11 = PokeIconSpriteIndex(v1, v0, v3);

        SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v5, v6, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, v11, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 100000);

        v8.x = 72 + 4;
        v8.y = 64 - 4;
        v8.z = 0;
        v8.animIdx = 0;
        v8.priority = 0;
        v8.plttIdx = 0;
        v8.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v8.bgPriority = 0;
        v8.vramTransfer = FALSE;
        v8.resources[0] = 100000;
        v8.resources[1] = 100000;
        v8.resources[2] = 100000;
        v8.resources[3] = 100000;
        v8.resources[4] = SPRITE_RESOURCE_NONE;
        v8.resources[5] = SPRITE_RESOURCE_NONE;

        param0->unk_04 = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v8);
        v2 = PokeIconPaletteIndex(v1, v3, v0);

        ManagedSprite_SetExplicitPaletteOffset(param0->unk_04, v4 + v2);
        ManagedSprite_SetAnim(param0->unk_04, 1);
    }
}

static void VsRecorderViewerList_SetTrainerSpriteVisible(VsRecorderViewerProfilePanel *param0, int param1)
{
    ManagedSprite_SetDrawFlag(param0->unk_08, param1);
}

static void VsRecorderViewerList_FreeTrainerSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    SpriteManager_UnloadCharObjById(param1->unk_14.unk_08, 165535);
    SpriteManager_UnloadPlttObjById(param1->unk_14.unk_08, 165535);
    SpriteManager_UnloadCellObjById(param1->unk_14.unk_08, 165535);
    SpriteManager_UnloadAnimObjById(param1->unk_14.unk_08, 165535);
    Sprite_DeleteAndFreeResources(param0->unk_08);
}

static const int sVsRecorderViewerListAppearanceFileIndices[16][4] = {
    { 0x3, 0x3C, 0x11, 0x12 },
    { 0x5, 0x6, 0x13, 0x14 },
    { 0xB, 0x18, 0x15, 0x16 },
    { 0x1F, 0x39, 0x17, 0x18 },
    { 0x32, 0x30, 0x19, 0x1A },
    { 0x33, 0xE, 0x1B, 0x1C },
    { 0x3E, 0x20, 0x1D, 0x1E },
    { 0x46, 0x31, 0x1F, 0x20 },
    { 0x6, 0x3, 0x21, 0x22 },
    { 0x7, 0xA, 0x23, 0x24 },
    { 0xD, 0x24, 0x25, 0x26 },
    { 0xE, 0x19, 0x27, 0x28 },
    { 0x23, 0x55, 0x29, 0x2A },
    { 0x25, 0x23, 0x2B, 0x2C },
    { 0x2A, 0x12, 0x2D, 0x2E },
    { 0x3F, 0x21, 0x2F, 0x30 }
};

int VsRecorderViewerList_GetAppearanceFileIndex(int param0, int param1)
{
    int v0 = param0;

    if ((param0 > 16) || (param0 < 0)) {
        GF_ASSERT(FALSE);
        v0 = 0;
    }

    if (param1 == 4) {
        return 316 + v0;
    }

    if (param1 >= 5) {
        return 0;
    }

    return sVsRecorderViewerListAppearanceFileIndices[v0][param1];
}

static void VsRecorderViewerList_LoadTrainerSprite(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    int v0;
    SpriteSystem *v1;
    SpriteManager *v2;
    PaletteData *v3;
    SpriteTemplate v4;
    int v5 = 13;
    int v6 = 14;
    int v7 = 9;
    int v8 = 10;

    v0 = PlayerProfile_GetGender(param0->unk_00);
    v1 = param1->unk_14.unk_04;
    v2 = param1->unk_14.unk_08;
    v3 = param1->unk_14.unk_14;

    if (param1->unk_86C == 0) {
        if (v0 == 1) {
            v5 = 15;
            v6 = 16;
        }
    } else {
        int v9 = PlayerProfile_GetAppearance(param0->unk_00);

        if (v9 >= 16) {
            v9 = 0;
        }

        v5 = VsRecorderViewerList_GetAppearanceFileIndex(v9, 2);
        v6 = VsRecorderViewerList_GetAppearanceFileIndex(v9, 3);
    }

    SpriteSystem_LoadPaletteBuffer(v3, PLTTBUF_MAIN_OBJ, v1, v2, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v5, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 165535);
    SpriteSystem_LoadCellResObj(v1, v2, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v7, FALSE, 165535);
    SpriteSystem_LoadAnimResObj(v1, v2, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v8, FALSE, 165535);
    SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v1, v2, NARC_INDEX_GRAPHIC__WIFI2DCHAR, v6, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 165535);

    v4.x = 40;
    v4.y = 56 + 4;
    v4.z = 0;
    v4.animIdx = 0;
    v4.priority = 0;
    v4.plttIdx = 0;
    v4.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v4.bgPriority = 0;
    v4.vramTransfer = FALSE;
    v4.resources[0] = 165535;
    v4.resources[1] = 165535;
    v4.resources[2] = 165535;
    v4.resources[3] = 165535;
    v4.resources[4] = SPRITE_RESOURCE_NONE;
    v4.resources[5] = SPRITE_RESOURCE_NONE;

    param0->unk_08 = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v4);
    ManagedSprite_SetAnim(param0->unk_08, 1);
    ManagedSprite_TickFrame(param0->unk_08);
}

void VsRecorderViewerList_InitProfile(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    VsRecorderViewerList_InitProfileWindows(param0, param1);
    VsRecorderViewerList_LoadTrainerSprite(param0, param1);
    VsRecorderViewerList_LoadPokemonSprite(param0, param1);
}

void VsRecorderViewerList_FreeProfile(VsRecorderViewerProfilePanel *param0, VsRecorderViewerState *param1)
{
    VsRecorderViewerList_FreeProfileWindows(param0, param1);
    VsRecorderViewerList_SetProfileSpritesVisible(param0, 0);
    VsRecorderViewerList_FreeTrainerSprite(param0, param1);
    VsRecorderViewerList_FreePokemonSprite(param0, param1);
}

void VsRecorderViewerList_SetProfileSpritesVisible(VsRecorderViewerProfilePanel *param0, int param1)
{
    VsRecorderViewerList_SetPokemonSpriteVisible(param0, param1);
    VsRecorderViewerList_SetTrainerSpriteVisible(param0, param1);
}

static void VsRecorderViewerList_DrawLocationString(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1)
{
    String *v0;
    String *v1;
    StringTemplate *v2;
    Window *v3;
    int v4 = PlayerProfile_GetCountry(param1->unk_88C[0]);
    int v5 = PlayerProfile_GetRegion(param1->unk_88C[0]);

    v3 = &param0->unk_18;

    if ((v4 == 0) && (v5 == 0)) {
        v0 = MessageLoader_GetNewString(param1->unk_14.unk_34, 125);
    } else {
        v2 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

        if (v5 != 0) {
            v0 = String_Init(255, HEAP_ID_102);
            v1 = MessageLoader_GetNewString(param1->unk_14.unk_34, 23);
            StringTemplate_SetCityName(v2, 0, v4, v5);
            StringTemplate_Format(v2, v0, v1);
        } else {
            v0 = String_Init(255, HEAP_ID_102);
            v1 = MessageLoader_GetNewString(param1->unk_14.unk_34, 22);
            StringTemplate_SetCountryName(v2, 0, v4);
            StringTemplate_Format(v2, v0, v1);
        }

        String_Free(v1);
        StringTemplate_Free(v2);
    }

    Text_AddPrinterWithParamsAndColor(v3, FONT_SYSTEM, v0, 0, 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    Window_ScheduleCopyToVRAM(v3);
    String_Free(v0);
}

void VsRecorderViewerList_InitWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, const VsRecorderViewerListConfig *param2)
{
    int v0;
    Window *v1;
    String *v2;

    v1 = &param0->unk_18;

    param0->unk_04 = param2->unk_04;
    param0->unk_00 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = param2->unk_24;
    param0->unk_28 = param2;
    param0->unk_34 = param1->unk_14.unk_34;
    param0->unk_14 = (param0->unk_04 / param0->unk_10) + 1;

    if (param0->unk_04 < param0->unk_10) {
        param0->unk_10 = param0->unk_04;
        param0->unk_38.unk_08 = param0->unk_10 - 1;
        param0->unk_38.unk_0C = param0->unk_10 - 1;
    }

    Window_Init(v1);
    Window_Add(param1->unk_14.unk_10, v1, param2->unk_20, param2->unk_0C, param2->unk_10, param2->unk_14, param2->unk_18, 14, param2->unk_1C);
    Window_FillTilemap(v1, 0x0);

    for (v0 = 0; v0 < param0->unk_10; v0++) {
        v2 = MessageLoader_GetNewString(param0->unk_34, param2->unk_00[v0].unk_00);

        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, (param2->unk_08 * 16) * v0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        String_Free(v2);

        if (param2->unk_00[v0].unk_00 == 16) {
            VsRecorderViewerList_DrawLocationString(param0, param1);
        }
    }

    Window_ScheduleCopyToVRAM(v1);
}

void VsRecorderViewerList_InitRecordWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3)
{
    int v0;
    Window *v1;
    String *v2;

    v1 = &param0->unk_18;

    param0->unk_04 = param3->unk_04;
    param0->unk_00 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = param3->unk_24;
    param0->unk_28 = param3;

    if (param2) {
        param0->unk_34 = param2;
    } else {
        param0->unk_34 = param1->unk_14.unk_34;
    }

    param0->unk_14 = (param0->unk_04 / param0->unk_10) + 1;
    param0->unk_38.unk_08 = param0->unk_10 / 2;
    param0->unk_38.unk_0C = param0->unk_10 / 2;

    if (param0->unk_04 < param0->unk_10) {
        param0->unk_10 = param0->unk_04;
        param0->unk_38.unk_08 = param0->unk_10 - 1;
        param0->unk_38.unk_0C = param0->unk_10 - 1;
    }

    Window_Init(v1);
    Window_Add(param1->unk_14.unk_10, v1, param3->unk_20, param3->unk_0C, param3->unk_10, param3->unk_14, param3->unk_18, 14, param3->unk_1C);
    Window_FillTilemap(v1, 0x0);

    if (param3->unk_00) {
        for (v0 = 0; v0 < param0->unk_10; v0++) {
            v2 = MessageLoader_GetNewString(param0->unk_34, param3->unk_00[v0].unk_00);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v2, 0, (param3->unk_08 * 16) * v0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            String_Free(v2);
        }
    } else {
        int v3;
        String *v4;
        String *v5;
        String *v6;
        int v7;

        for (v0 = 0; v0 < param0->unk_10; v0++) {
            v4 = String_Init(255, HEAP_ID_102);
            v5 = String_Init(255, HEAP_ID_102);
            v6 = MessageLoader_GetNewString(param1->unk_14.unk_34, 99);

            String_FormatInt(v5, (v0 + 1), 2, 1, 1);
            String_CopyChars(v4, param1->unk_8B4.unk_1D58[v0]->unk_00.unk_00);
            VsRecorderViewerList_CheckNameChars(param1, v4);

            v7 = Font_CalcStringWidth(FONT_SYSTEM, v5, 0);

            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v5, 16 - v7, 4 + (v0 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v6, 16, 4 + (v0 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v4, 22, 4 + (v0 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            String_Free(v4);
            String_Free(v5);
            String_Free(v6);
        }
    }

    Window_ScheduleCopyToVRAM(v1);
}

void VsRecorderViewerList_InitRankingWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, MessageLoader *param2, const VsRecorderViewerListConfig *param3, int param4, int param5, String *param6)
{
    int v0;
    Window *v1;
    String *v2;
    String *v3;
    String *v4;
    String *v5;
    String *v6;
    StringTemplate *v7;
    int v8 = 0;
    u64 v9 = 0;
    int v10[30] = { 0 };
    String *v11;

    v1 = &param0->unk_18;

    param0->unk_04 = param3->unk_04;
    param0->unk_00 = 0;

    param0->unk_0C = 0;
    param0->unk_10 = param3->unk_24;
    param0->unk_28 = param3;
    if (param2) {
        param0->unk_34 = param2;
    } else {
        param0->unk_34 = param1->unk_14.unk_34;
    }

    param0->unk_14 = (param0->unk_04 / param0->unk_10) + 1;
    if (param0->unk_04 < param0->unk_10) {
        param0->unk_10 = param0->unk_04;
        param0->unk_38.unk_08 = param0->unk_10 - 1;
        param0->unk_38.unk_0C = param0->unk_10 - 1;
    }

    param0->unk_38.unk_08 = param0->unk_10 / 2;
    param0->unk_38.unk_0C = param0->unk_10 / 2;

    Window_Init(v1);
    Window_Add(param1->unk_14.unk_10, v1, param3->unk_20, param3->unk_0C, param3->unk_10, param3->unk_14, param3->unk_18, 14, param3->unk_1C);
    Window_FillTilemap(v1, 0x00);

    v7 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

    u64 v12 = param0->unk_28->unk_00[0].unk_08;
    int v13[] = { 16, 12, 20 };

    v9 = v12;
    v10[0] = v8;

    for (v0 = 1; v0 < v13[param5]; v0++) {
        u64 v14 = param0->unk_28->unk_00[v0].unk_08;

        if (v14 == v9) {
            v10[v0] = v8;
        } else {
            v9 = v14;
            v10[v0] = v0;
            v8 = v0;
        }
    }

    for (v0 = 0; v0 < param0->unk_10; v0++) {
        v3 = MessageLoader_GetNewString(param1->unk_14.unk_34, 88 + param5);

        v4 = String_Init(255, HEAP_ID_102);
        v6 = String_Init(255, HEAP_ID_102);
        v11 = String_Init(255, HEAP_ID_102);

        switch (param5) {
        case 0:
            int v15 = param0->unk_28->unk_00[v0].unk_04;
            v5 = MessageLoader_GetNewString(param0->unk_34, v15);
            StringTemplate_SetString(v7, 1, v5, 0, 1, GAME_LANGUAGE);
            break;
        case 1:
            int v16 = param0->unk_28->unk_00[v0].unk_04;
            v5 = String_Init(255, HEAP_ID_102);
            StringTemplate_SetMonthName(v7, 1, v16);
            break;
        case 2:
            u16 v17[255];
            int v18 = param0->unk_28->unk_00[v0].unk_04;
            v5 = String_Init(255, HEAP_ID_102);
            MessageLoader_GetSpeciesName(v18, 102, v17);
            String_CopyChars(v5, v17);
            StringTemplate_SetString(v7, 1, v5, 0, 1, GAME_LANGUAGE);
            break;
        }

        u64 v19 = param0->unk_28->unk_00[v0].unk_08;

        String_FormatU64(v11, v19, VsRecorderViewerList_CountDigits(v19), 0, 1);

        String_FormatInt(v4, v10[v0] + 1, 2, 1, 1);
        StringTemplate_SetString(v7, 0, v4, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v7, v6, v3);

        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v6, 0, v0 * (16 * param0->unk_28->unk_08), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        if (param0->unk_28->unk_08 == 2) {
            if (param6) {
                StringTemplate_SetString(v7, 2, v11, 0, 1, GAME_LANGUAGE);
                StringTemplate_Format(v7, v6, param6);
                Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, v6, 16, (v0 * (16 * param0->unk_28->unk_08)) + 16, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            }
        }

        String_Free(v3);
        String_Free(v4);
        String_Free(v5);
        String_Free(v6);

        String_Free(v11);

        StringTemplate_ClearArgs(v7);
    }

    Window_ScheduleCopyToVRAM(v1);
    StringTemplate_Free(v7);
}

void VsRecorderViewerList_InitTwoColumnWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, const VsRecorderViewerListConfig *param2, String *param3[20][2])
{
    int v0;
    Window *v1 = &param0->unk_18;

    param0->unk_04 = param2->unk_04;
    param0->unk_00 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = param2->unk_24;
    param0->unk_28 = param2;
    param0->unk_34 = param1->unk_14.unk_34;
    param0->unk_14 = (param0->unk_04 / param0->unk_10) + 1;
    param0->unk_38.unk_08 = param0->unk_10 / 2;
    param0->unk_38.unk_0C = param0->unk_10 / 2;

    if (param0->unk_04 < param0->unk_10) {
        param0->unk_10 = param0->unk_04;
        param0->unk_38.unk_08 = param0->unk_10 - 1;
        param0->unk_38.unk_0C = param0->unk_10 - 1;
    }

    param0->unk_48 = 1;

    Window_Init(v1);
    Window_Add(param1->unk_14.unk_10, v1, param2->unk_20, param2->unk_0C, param2->unk_10, param2->unk_14, param2->unk_18, 14, param2->unk_1C);
    Window_FillTilemap(v1, 0x0);

    for (v0 = 0; v0 < param0->unk_10; v0++) {
        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param3[v0][0], 0, ((param2->unk_08 * 8) * v0) + 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Text_AddPrinterWithParamsAndColor(v1, FONT_SYSTEM, param3[v0][1], 136, ((param2->unk_08 * 8) * v0) + 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(v1);
}

int VsRecorderViewerList_UpdateTwoColumnWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, String *param2[20][2])
{
    int v0;
    int v1 = 0;
    Window *v2;

    if (param0->unk_38.unk_00 == param0->unk_0C) {
        return v1;
    }
    if (param0->unk_10 == param0->unk_04) {
        return v1;
    }

    v2 = &param0->unk_18;

    Window_FillTilemap(v2, 0x0);
    {
        int v3;
        int v4 = 0;
        int v5;

        if (param0->unk_38.unk_04 >= param0->unk_38.unk_08) {
            v4 = param0->unk_38.unk_00 - param0->unk_38.unk_08;
            if (param0->unk_38.unk_00 >= (param0->unk_04 - (param0->unk_38.unk_08 + 1))) {
                v4 = param0->unk_04 - param0->unk_10;
            }
        }

        for (v3 = 0; v3 < param0->unk_10; v3++) {
            if (param2[v4 + v3][0] == NULL) {
                continue;
            }

            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, param2[v4 + v3][0], 0, ((param0->unk_28->unk_08 * 8) * v3) + 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, param2[v4 + v3][1], 136, ((param0->unk_28->unk_08 * 8) * v3) + 4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        }
    }
    Window_CopyToVRAM(v2);

    param0->unk_0C = param0->unk_38.unk_00;

    return v1;
}

int VsRecorderViewerList_UpdateRankingWindow(VsRecorderViewerListWindow *a0, VsRecorderViewerState *a1, int a2, int a3, String *a4)
{
    int i;
    Window *sp58;
    String *sp54;
    String *sp50;
    String *sp4c;
    String *r7;
    String *sp48;

    if (a0->unk_08 == a0->unk_0C) {
        return 0;
    }
    if (a0->unk_10 == a0->unk_04) {
        return 0;
    }

    sp58 = &a0->unk_18;
    StringTemplate *r5 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);
    Window_FillTilemap(sp58, 0);
    int sp44 = 0;
    int sp40 = 0;
    u64 sp3c;
    int sp18 = a0->unk_08;
    int sp34 = sp18 + a0->unk_10;
    int sp26c[30] = { 0 };

    if (sp34 >= a0->unk_04) {
        sp34 = a0->unk_04;
        sp18 = a0->unk_04 - a0->unk_10;
    }

    u64 sp38 = a0->unk_28->unk_00[0].unk_08;
    int sp60[] = { 0x10, 0xc, 0x14 };
    sp3c = sp38;
    sp26c[0] = 0;

    for (i = 1; i < sp60[a3]; i++) {
        u64 r7 = a0->unk_28->unk_00[i].unk_08;
        if (r7 == sp3c) {
            sp26c[i] = sp40;
        } else {
            sp3c = r7;
            sp26c[i] = i;
            sp40 = i;
        }
    }

    for (i = sp18; i < sp34; i++) {
        sp54 = MessageLoader_GetNewString(a1->unk_14.unk_34, 88 + a3);
        sp50 = String_Init(255, HEAP_ID_102);
        r7 = String_Init(255, HEAP_ID_102);
        sp48 = String_Init(255, HEAP_ID_102);
        switch (a3) {
        case 0:
            int r1 = a0->unk_28->unk_00[i].unk_04;
            sp4c = MessageLoader_GetNewString(a0->unk_34, r1);
            StringTemplate_SetString(r5, 1, sp4c, 0, 1, GAME_LANGUAGE);
            break;
        case 1:
            int sp30 = a0->unk_28->unk_00[i].unk_04;
            sp4c = String_Init(255, HEAP_ID_102);
            StringTemplate_SetMonthName(r5, 1, sp30);
            break;
        case 2:
            charcode_t sp6c[255];
            int sp2c = a0->unk_28->unk_00[i].unk_04;
            sp4c = String_Init(255, HEAP_ID_102);
            MessageLoader_GetSpeciesName(sp2c, HEAP_ID_102, sp6c);
            String_CopyChars(sp4c, sp6c);
            StringTemplate_SetString(r5, 1, sp4c, 0, 1, GAME_LANGUAGE);
            break;
        }
        u64 sp24 = a0->unk_28->unk_00[i].unk_08;
        String_FormatU64(sp48, sp24, VsRecorderViewerList_CountDigits(sp24), PADDING_MODE_NONE, 1);
        String_FormatInt(sp50, sp26c[i] + 1, 2, PADDING_MODE_SPACES, 1);
        StringTemplate_SetString(r5, 0, sp50, 0, TRUE, GAME_LANGUAGE);
        StringTemplate_Format(r5, r7, sp54);
        int yOffset = 16 * a0->unk_28->unk_08 * sp44;
        Text_AddPrinterWithParamsAndColor(sp58, FONT_SYSTEM, r7, 0, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        if (a0->unk_28->unk_08 == 2 && a4) {
            StringTemplate_SetString(r5, 2, sp48, 0, 1, GAME_LANGUAGE);
            StringTemplate_Format(r5, r7, a4);
            yOffset = (16 * a0->unk_28->unk_08 * sp44) + 16;
            Text_AddPrinterWithParamsAndColor(sp58, FONT_SYSTEM, r7, 0x10, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        }
        sp44++;
        String_Free(sp54);
        String_Free(sp50);
        String_Free(sp4c);
        String_Free(r7);
        String_Free(sp48);
        StringTemplate_ClearArgs(r5);
    }

    Window_ScheduleCopyToVRAM(sp58);
    StringTemplate_Free(r5);
    a0->unk_0C = a0->unk_08;
    return 0;
}

int VsRecorderViewerList_UpdateRecordWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1 = 0;
    Window *v2;
    String *v3;

    if (param0->unk_28->unk_28 != NULL) {
        for (v0 = 0; v0 < param0->unk_10; v0++) {
            if (TouchScreen_LocationPressed(&param0->unk_28->unk_28[v0])) {
                VsRecorderViewerList_PlayRingAnim(param1);
                v1 = param0->unk_28->unk_00[param0->unk_08 + v0].unk_04;
            }
        }
    }

    if (param0->unk_08 == param0->unk_0C) {
        return v1;
    }

    if (param0->unk_10 == param0->unk_04) {
        return v1;
    }

    v2 = &param0->unk_18;

    Window_FillTilemap(v2, 0x0);

    {
        int v4 = 0;
        int v5 = param0->unk_08;
        int v6 = v5 + param0->unk_10;

        if (v6 >= param0->unk_04) {
            v5 = param0->unk_04 - param0->unk_10;
            v6 = param0->unk_04;
        }

        for (v0 = v5; v0 < v6; v0++) {
            v3 = MessageLoader_GetNewString(param0->unk_34, param0->unk_28->unk_00[v0].unk_00);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v3, 0, (param0->unk_28->unk_08 * 16) * v4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            String_Free(v3);
            v4++;
        }
    }

    Window_CopyToVRAM(v2);
    param0->unk_0C = param0->unk_08;

    return v1;
}

int VsRecorderViewerList_UpdateSpeciesWindow(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1 = 0;
    Window *v2;
    String *v3;

    if (param0->unk_38.unk_00 == param0->unk_0C) {
        return v1;
    }

    if (param0->unk_10 == param0->unk_04) {
        return v1;
    }

    v2 = &param0->unk_18;
    Window_FillTilemap(v2, 0x0);

    {
        int v4;
        int v5 = 0;
        int v6;
        String *v7;
        String *v8;
        String *v9;
        int v10;
        int v11;

        if (param0->unk_38.unk_04 >= param0->unk_38.unk_08) {
            v5 = param0->unk_38.unk_00 - param0->unk_38.unk_08;

            if (param0->unk_38.unk_00 >= (param0->unk_04 - (param0->unk_38.unk_08 + 1))) {
                v5 = param0->unk_04 - param0->unk_10;
            }
        }

        for (v4 = 0; v4 < param0->unk_10; v4++) {
            v7 = String_Init(255, HEAP_ID_102);
            v8 = String_Init(255, HEAP_ID_102);
            v9 = MessageLoader_GetNewString(param1->unk_14.unk_34, 99);

            String_FormatInt(v8, (v5 + v4 + 1), 2, 1, 1);
            String_CopyChars(v7, param1->unk_8B4.unk_1D58[v5 + v4]->unk_00.unk_00);
            VsRecorderViewerList_CheckNameChars(param1, v7);

            v10 = Font_CalcStringWidth(FONT_SYSTEM, v8, 0);

            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v8, 16 - v10, 4 + (v4 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v9, 16, 4 + (v4 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v7, 22, 4 + (v4 * 24), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            String_Free(v7);
            String_Free(v8);
            String_Free(v9);
        }
    }

    Window_CopyToVRAM(v2);
    param0->unk_0C = param0->unk_38.unk_00;

    return v1;
}

void VsRecorderViewerList_MoveSelection(VsRecorderViewerListWindow *param0, s16 param1)
{
    s16 v0 = 0;
    int v1 = 0xFF;

    if (param1 < 0) {
        if (param0->unk_38.unk_00 > 0) {
            param0->unk_38.unk_00--;
            v1 = 0;
            Sound_PlayEffect(SEQ_SE_PL_BUTTON_sseq);
        }
    } else if (param1 > 0) {
        if (param0->unk_38.unk_00 < param0->unk_04 - 1) {
            param0->unk_38.unk_00++;
            v1 = 1;
            Sound_PlayEffect(SEQ_SE_PL_BUTTON_sseq);
        }
    }

    switch (v1) {
    case 0:
        if (param0->unk_38.unk_00 < param0->unk_38.unk_0C) {
            v0 = param0->unk_38.unk_00;
        } else if (param0->unk_38.unk_00 >= (param0->unk_04 - param0->unk_38.unk_0C)) {
            v0 = param0->unk_38.unk_0C + 1;

            if (param0->unk_38.unk_00 >= (param0->unk_04 - param0->unk_38.unk_0C)) {
                v0 += (param0->unk_38.unk_00 - (param0->unk_04 - param0->unk_38.unk_0C));
            }
        } else {
            v0 = param0->unk_38.unk_0C;

            if (param0->unk_38.unk_00 <= param0->unk_38.unk_0C) {
                v0 += (param0->unk_38.unk_00 - param0->unk_38.unk_0C);
            }
        }
        break;
    case 1:
        if (param0->unk_38.unk_00 <= param0->unk_38.unk_08) {
            v0 = param0->unk_38.unk_00;
        } else {
            v0 = param0->unk_38.unk_08;
            if (param0->unk_38.unk_00 >= (param0->unk_04 - param0->unk_38.unk_08)) {
                v0 += (param0->unk_38.unk_00 - (param0->unk_04 - param0->unk_38.unk_08 - 1));
            }
        }
        break;
    }

    if (v0 < 0) {
        GF_ASSERT(FALSE);
    }

    if (v1 != 0xFF) {
        param0->unk_38.unk_04 = v0;
    }

    {
        s16 v2 = 0;

        if (param0->unk_38.unk_04 >= param0->unk_38.unk_08) {
            v2 = param0->unk_38.unk_00 - param0->unk_38.unk_08;

            if (param0->unk_38.unk_00 >= (param0->unk_04 - (param0->unk_38.unk_08 + 1))) {
                v2 = param0->unk_04 - param0->unk_10;
            }
        }

        param0->unk_08 = v2;
        VsRecorderViewerList_UpdateArrowSpritesForScroll(param0);
    }
}

void VsRecorderViewerList_ScrollList(VsRecorderViewerListWindow *param0, s16 param1)
{
    s16 v0 = param0->unk_08;

    param0->unk_08 += param1;

    if (param0->unk_08 < 0) {
        param0->unk_08 = 0;
    }

    if (param0->unk_10 == param0->unk_04) {
        param0->unk_08 = 0;
    }

    if (param0->unk_08 + param0->unk_10 > param0->unk_04) {
        param0->unk_08 = param0->unk_04 - param0->unk_10;
    }

    if (v0 != param0->unk_08) {
        Sound_PlayEffect(SEQ_SE_PL_BUTTON_sseq);
    }

    VsRecorderViewerList_UpdateArrowSprites(param0);
}

void VsRecorderViewerList_FreeWindow(VsRecorderViewerListWindow *param0)
{
    Window_ClearAndCopyToVRAM(&param0->unk_18);
    Window_Remove(&param0->unk_18);
}

void VsRecorderViewerList_ResetWindow(VsRecorderViewerListWindow *param0)
{
    memset(param0, 0, sizeof(VsRecorderViewerListWindow));
}

void VsRecorderViewerList_LoadArrowSprites(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1, int param2)
{
    ManagedSprite *v0;
    SpriteTemplate v1;
    NARC *v2 = param1->unk_14.unk_00;
    BgConfig *v3 = param1->unk_14.unk_10;
    SpriteSystem *v4 = param1->unk_14.unk_04;
    SpriteManager *v5 = param1->unk_14.unk_08;
    PaletteData *v6 = param1->unk_14.unk_14;

    SpriteSystem_LoadCharResObjFromOpenNarc(v4, v5, v2, 127, FALSE, param2, 200000);
    SpriteSystem_LoadCellResObjFromOpenNarc(v4, v5, v2, 126, FALSE, 200000);
    SpriteSystem_LoadAnimResObjFromOpenNarc(v4, v5, v2, 125, FALSE, 200000);

    v1.x = 128;
    v1.y = 96;
    v1.z = 0;
    v1.animIdx = 0;
    v1.priority = 1;
    v1.plttIdx = 0;
    v1.vramType = param2;
    v1.bgPriority = 1;
    v1.vramTransfer = FALSE;
    v1.resources[4] = SPRITE_RESOURCE_NONE;
    v1.resources[5] = SPRITE_RESOURCE_NONE;
    v1.resources[0] = 200000;
    v1.resources[2] = 200000;
    v1.resources[3] = 200000;

    if (param2 == NNS_G2D_VRAM_TYPE_2DMAIN) {
        v1.resources[1] = 9999;
    } else {
        v1.resources[1] = 10000;
    }

    param0->unk_2C[0] = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v1);
    param0->unk_2C[1] = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v1);

    ManagedSprite_SetExplicitPalette(param0->unk_2C[0], 2);
    ManagedSprite_SetExplicitPalette(param0->unk_2C[1], 2);
    ManagedSprite_SetAnim(param0->unk_2C[0], 0);
    ManagedSprite_SetAnim(param0->unk_2C[1], 0);
    ManagedSprite_TickFrame(param0->unk_2C[0]);
    ManagedSprite_TickFrame(param0->unk_2C[1]);
    ManagedSprite_SetFlipMode(param0->unk_2C[1], 2);

    if (param2 == 1) {
        ManagedSprite_SetPositionXY(param0->unk_2C[0], 256 / 2, 24);
        ManagedSprite_SetPositionXY(param0->unk_2C[1], 256 / 2, 120);
    } else {
        ManagedSprite_SetPositionXY(param0->unk_2C[0], 256 / 2, 24 + 64);
        ManagedSprite_SetPositionXY(param0->unk_2C[1], 256 / 2, 120 + 64);
    }

    VsRecorderViewerList_UpdateArrowSprites(param0);
}

void VsRecorderViewerList_SetArrowSpritesPosition(VsRecorderViewerListWindow *param0, s16 param1, s16 param2)
{
    ManagedSprite_SetPositionXY(param0->unk_2C[0], 256 / 2, param1);
    ManagedSprite_SetPositionXY(param0->unk_2C[1], 256 / 2, param2);
}

void VsRecorderViewerList_UpdateArrowSprites(VsRecorderViewerListWindow *param0)
{
    ManagedSprite_SetDrawFlag(param0->unk_2C[0], 1);
    ManagedSprite_SetDrawFlag(param0->unk_2C[1], 1);

    if (param0->unk_08 == 0) {
        ManagedSprite_SetDrawFlag(param0->unk_2C[0], 0);
    }

    if (param0->unk_08 + param0->unk_10 >= param0->unk_04) {
        ManagedSprite_SetDrawFlag(param0->unk_2C[1], 0);
    }

    ManagedSprite_TickTwoFrames(param0->unk_2C[0]);
    ManagedSprite_TickTwoFrames(param0->unk_2C[1]);
}

void VsRecorderViewerList_UpdateArrowSpritesForScroll(VsRecorderViewerListWindow *param0)
{
    ManagedSprite_SetDrawFlag(param0->unk_2C[0], 1);
    ManagedSprite_SetDrawFlag(param0->unk_2C[1], 1);

    if (param0->unk_08 == 0) {
        ManagedSprite_SetDrawFlag(param0->unk_2C[0], 0);
    }

    if (param0->unk_08 + param0->unk_10 >= param0->unk_04) {
        ManagedSprite_SetDrawFlag(param0->unk_2C[1], 0);
    }

    if (param0->unk_10 >= param0->unk_04) {
        ManagedSprite_SetDrawFlag(param0->unk_2C[0], 0);
        ManagedSprite_SetDrawFlag(param0->unk_2C[1], 0);
    }

    ManagedSprite_TickTwoFrames(param0->unk_2C[0]);
    ManagedSprite_TickTwoFrames(param0->unk_2C[1]);
}

void VsRecorderViewerList_FreeArrowSprites(VsRecorderViewerListWindow *param0, VsRecorderViewerState *param1)
{
    SpriteManager_UnloadCharObjById(param1->unk_14.unk_08, 200000);
    SpriteManager_UnloadCellObjById(param1->unk_14.unk_08, 200000);
    SpriteManager_UnloadAnimObjById(param1->unk_14.unk_08, 200000);
    Sprite_DeleteAndFreeResources(param0->unk_2C[0]);
    Sprite_DeleteAndFreeResources(param0->unk_2C[1]);
}

static ManagedSprite *VsRecorderViewerList_NewScrollIndicatorSprite(VsRecorderViewerListScrollBar *param0, VsRecorderViewerState *param1, int param2, int param3)
{
    ManagedSprite *v0;
    SpriteTemplate v1;

    v1.x = 128;
    v1.y = 96;
    v1.z = 0;
    v1.animIdx = 0;
    v1.priority = 1;
    v1.plttIdx = 0;
    v1.vramType = param2;
    v1.bgPriority = 1;
    v1.vramTransfer = FALSE;
    v1.resources[4] = SPRITE_RESOURCE_NONE;
    v1.resources[5] = SPRITE_RESOURCE_NONE;
    v1.resources[0] = 11924;
    v1.resources[2] = 11924;
    v1.resources[3] = 11924;

    if (param2 == NNS_G2D_VRAM_TYPE_2DMAIN) {
        v1.resources[1] = 9999;
    } else {
        v1.resources[1] = 10000;
    }

    v0 = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v1);
    ManagedSprite_SetExplicitPalette(v0, 2);
    ManagedSprite_SetAnim(v0, param3);
    ManagedSprite_TickFrame(v0);

    return v0;
}

static void VsRecorderViewerList_FreeScrollIndicatorSprites(VsRecorderViewerListScrollBar *param0)
{
    Sprite_DeleteAndFreeResources(param0->unk_18[0]);
    Sprite_DeleteAndFreeResources(param0->unk_18[1]);
}

void VsRecorderViewerList_InitScrollBar(VsRecorderViewerListScrollBar *param0, VsRecorderViewerState *param1)
{
    VsRecorderViewerList_InitScrollBarWithAnim(param0, param1, 5);
}

void VsRecorderViewerList_InitScrollBarWithAnim(VsRecorderViewerListScrollBar *param0, VsRecorderViewerState *param1, int param2)
{
    param0->unk_18[0] = VsRecorderViewerList_NewScrollIndicatorSprite(param0, param1, 2, param2);
    param0->unk_18[1] = VsRecorderViewerList_NewScrollIndicatorSprite(param0, param1, 2, param2);

    ManagedSprite_SetPositionXY(param0->unk_18[0], 0 + 24, 72 + 64);
    ManagedSprite_SetPositionXY(param0->unk_18[1], 256 - 24, 72 + 64);
}

void VsRecorderViewerList_ResetScrollBar(VsRecorderViewerListScrollBar *param0)
{
    memset(param0, 0, sizeof(VsRecorderViewerListScrollBar));
}

void VsRecorderViewerList_FreeScrollBar(VsRecorderViewerListScrollBar *param0)
{
    VsRecorderViewerList_FreeScrollIndicatorSprites(param0);
}

void VsRecorderViewerList_UpdateScrollDirection(VsRecorderViewerListScrollBar *param0, u32 param1)
{
    s32 v0 = param1 - param0->unk_0C;

    if ((v0 * v0) >= (16 * 16)) {
        if (v0 < 0) {
            param0->unk_10 = -1;
        } else {
            param0->unk_10 = +1;
        }
        param0->unk_0C = param1;
    } else {
        param0->unk_10 = 0;
    }
}

static const TouchScreenHitTable sVsRecorderViewerListScrollHitTables[] = {
    { 0x8, 0x80, 0x8, 0x20 },
    { 0x8, 0x80, 0xE0, 0xF8 }
};

void VsRecorderViewerList_UpdateScrollBarVisibility(VsRecorderViewerListScrollBar *param0, VsRecorderViewerListWindow *param1)
{
    if (param1->unk_48) {
        if (param1->unk_04 < 2) {
            param0->unk_14 = 0;
        } else {
            param0->unk_14 = 1;
        }
    } else {
        if (param1->unk_10 >= param1->unk_04) {
            param0->unk_14 = 0;
        } else {
            param0->unk_14 = 1;
        }
    }
}

void VsRecorderViewerList_HandleScrollBarInput(VsRecorderViewerListScrollBar *param0)
{
    u32 v0, v1;
    s16 v2;
    BOOL v3;
    BOOL v4 = 0;

    v3 = TouchScreen_GetHoldState(&v0, &v1);

    if (param0->unk_14) {
        ManagedSprite_TickTwoFrames(param0->unk_18[0]);
        ManagedSprite_TickTwoFrames(param0->unk_18[1]);
    }

    if ((param0->unk_04 == 0) && (v3 == 0)) {
        param0->unk_04 = 0;
        param0->unk_00 = 0;
        param0->unk_08 = 0;
        param0->unk_0C = 0;
        param0->unk_10 = 0;
        return;
    }

    if (TouchScreen_LocationHeld(&sVsRecorderViewerListScrollHitTables[0])
        || TouchScreen_LocationHeld(&sVsRecorderViewerListScrollHitTables[1])) {
        v4 = 1;
    }

    if (v4) {
        if (!param0->unk_04) {
            param0->unk_04 = 1;
            param0->unk_08 = v0;
            param0->unk_0C = v1;
            param0->unk_00 = 2;
        } else {
            param0->unk_00--;
            VsRecorderViewerList_UpdateScrollDirection(param0, v1);
        }
    } else {
        if (param0->unk_04) {
            param0->unk_04 = 0;
            param0->unk_00 = 0;
            param0->unk_08 = 0;
            param0->unk_0C = 0;
        }
    }
}

void VsRecorderViewerList_IncrementTrainerScore(VsRecorderViewerState *param0, u32 param1)
{
    GameRecords *v0 = SaveData_GetGameRecords(param0->saveData);
    GameRecords_IncrementTrainerScore(v0, param1);
}

void VsRecorderViewerList_StoreBattleRecording(VsRecorderViewerState *param0)
{
    int v0;

    BattleRecording_New(param0->saveData, HEAP_ID_119, &v0);

    {
        PlayerProfile *v1 = (PlayerProfile *)(&param0->unk_8B4.unk_00->unk_00);
        BattleRecordingSummary *v2 = (BattleRecordingSummary *)(&param0->unk_8B4.unk_00->unk_80);
        BattleRecordingData *v3 = (BattleRecordingData *)(&param0->unk_8B4.unk_00->unk_E4);
        BattleRecording_Store(v1, v2, v3, NULL, param0->saveData);
    }
}

static void VsRecorderViewerList_Task_UpdateNetwork(SysTask *param0, void *param1)
{
    VsRecorderViewerListNetworkTask *v0 = param1;

    VsRecorderViewerMain_SetWhichScreenIs3D(v0->unk_00);
    NetworkIcon_Update();
    v0->unk_04 = 1;
    SysTask_Done(param0);
}

void VsRecorderViewerList_StartNetworkTask(VsRecorderViewerState *param0, int param1)
{
    param0->unk_52C.unk_00 = param1;
    param0->unk_52C.unk_04 = 0;

    SysTask_ExecuteOnVBlank(VsRecorderViewerList_Task_UpdateNetwork, &param0->unk_52C, 4);
}

BOOL VsRecorderViewerList_IsNetworkTaskDone(VsRecorderViewerState *param0)
{
    return param0->unk_52C.unk_04;
}

static void VsRecorderViewerList_Task_DrawSprites(SysTask *param0, void *param1)
{
    VsRecorderViewerState *v0 = param1;

    if (v0->unk_14.unk_08 == NULL) {
        return;
    }

    if (VsRecorderViewerList_IsDrawSuspended(v0) == 1) {
        return;
    }

    if (v0->unk_14.unk_510 == 1) {
        return;
    }

    v0->unk_14.unk_510 = 1;

    PokemonSpriteManager_UpdateCharAndPltt(v0->unk_14.unk_50);
    SpriteSystem_DrawSprites(v0->unk_14.unk_08);
    SpriteSystem_TransferOam();

    v0->unk_14.unk_510 = 0;
}

void VsRecorderViewerList_StartDrawTask(VsRecorderViewerState *param0)
{
    param0->unk_41E8 = SysTask_ExecuteOnVBlank(VsRecorderViewerList_Task_DrawSprites, param0, 5);
}

BOOL VsRecorderViewerList_CheckRecordData(VsRecorderViewerState *param0, int param1, u8 param2)
{
    int v0 = VsRecorderViewerRecording_SaveStep(param0->saveData, param1, param2, &param0->unk_834, &param0->unk_836);

    if ((v0 == 0) || (v0 == 1)) {
        return 0;
    }

    return 1;
}

void VsRecorderViewerList_SetHasPendingRecording(VsRecorderViewerState *param0, BOOL param1)
{
    param0->unk_874 = param1;
}

void VsRecorderViewerList_LoadRecordList(void *param0, const VsRecorderViewerTransferStatus *param1)
{
    VsRecorderViewerState *v0 = param0;
    VsRecorderViewerListRecordStore *v1 = &v0->unk_8B4;

    if (param1->unk_00 == 1) {
        (void)0;
    } else {
        v1->unk_3900 = GlobalTerminalGds_GetRecordList(VsRecorderViewerTransfer_GetTransfer(v0), v1->unk_1D58, 30);

        {
            int v2;

            for (v2 = 0; v2 < v1->unk_3900; v2++) {
                GF_ASSERT(v0->unk_8B4.unk_1D58[v2] != NULL);
                MI_CpuCopy8(v0->unk_8B4.unk_1D58[v2], &v0->unk_8B4.unk_1DD0[v2], sizeof(GlobalTerminalRecord));
                v0->unk_8B4.unk_3904[v2] = v0->unk_8B4.unk_1D58[v2]->unk_80.unk_27;
            }
        }
    }
}

void VsRecorderViewerList_LoadBattleRecordings(VsRecorderViewerState *param0)
{
    int v0;
    int v1;

    for (v0 = 0; v0 < 4; v0++) {
        BattleRecording_Load(param0->saveData, 102, &v1, NULL, v0);

        switch (v1) {
        case 0:
            param0->unk_87C[v0] = NULL;
            param0->unk_88C[v0] = NULL;

            if (v0 == 0) {
                param0->unk_88C[v0] = PlayerProfile_New(HEAP_ID_102);
                PlayerProfile_Init(param0->unk_88C[v0], param0->saveData);
            }
            break;
        case 2:
            param0->unk_87C[v0] = NULL;
            param0->unk_88C[v0] = NULL;

            if (v0 == 0) {
                param0->unk_88C[v0] = PlayerProfile_New(HEAP_ID_102);
                PlayerProfile_Init(param0->unk_88C[v0], param0->saveData);
            }
            break;
        case 3:
            param0->unk_87C[v0] = NULL;
            param0->unk_88C[v0] = NULL;

            if (v0 == 0) {
                param0->unk_88C[v0] = PlayerProfile_New(HEAP_ID_102);
                PlayerProfile_Init(param0->unk_88C[v0], param0->saveData);
            }
            break;
        case 1:
            param0->unk_87C[v0] = BattleRecording_CloneSummary(HEAP_ID_102);

            if (v0 == 0) {
                param0->unk_88C[v0] = PlayerProfile_New(HEAP_ID_102);
                PlayerProfile_Init(param0->unk_88C[v0], param0->saveData);
            } else {
                param0->unk_88C[v0] = BattleRecording_CloneHeader(HEAP_ID_102);
            }
            break;
        }
        if (BattleRecording_Exists() == 1) {
            BattleRecording_Free();
        }
    }
}

void VsRecorderViewerList_FreeBattleRecordings(VsRecorderViewerState *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_87C[v0] != NULL) {
            Heap_Free(param0->unk_87C[v0]);
            param0->unk_87C[v0] = NULL;
        }

        if (param0->unk_88C[v0] != NULL) {
            Heap_Free(param0->unk_88C[v0]);
            param0->unk_88C[v0] = NULL;
        }
    }
}

void VsRecorderViewerList_LoadIconResources(VsRecorderViewerState *param0)
{
    SpriteSystem *v0 = param0->unk_14.unk_04;
    SpriteManager *v1 = param0->unk_14.unk_08;
    PaletteData *v2 = param0->unk_14.unk_14;

    SpriteSystem_LoadPaletteBuffer(v2, 2, v0, v1, 19, PokeIconPalettesFileIndex(), 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 100000);
    SpriteSystem_LoadCellResObj(v0, v1, 19, PokeIcon64KCellsFileIndex(), 0, 100000);
    SpriteSystem_LoadAnimResObj(v0, v1, 19, PokeIcon64KAnimationFileIndex(), 0, 100000);
}

void VsRecorderViewerList_FreeIconResources(VsRecorderViewerState *param0)
{
    SpriteManager_UnloadPlttObjById(param0->unk_14.unk_08, 100000);
    SpriteManager_UnloadCellObjById(param0->unk_14.unk_08, 100000);
    SpriteManager_UnloadAnimObjById(param0->unk_14.unk_08, 100000);
}

NARC *VsRecorderViewerList_OpenIconNarc(int param0)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, HEAP_ID_102);
    return v0;
}

void VsRecorderViewerList_CloseIconNarc(NARC *param0)
{
    NARC_dtor(param0);
}

ManagedSprite *VsRecorderViewerList_NewPokemonIconSprite(VsRecorderViewerState *param0, NARC *param1, int param2, int param3, int param4, int param5)
{
    ManagedSprite *v0;
    SpriteSystem *v1;
    SpriteManager *v2;
    PaletteData *v3;
    SpriteTemplate v4;
    int v5;

    v1 = param0->unk_14.unk_04;
    v2 = param0->unk_14.unk_08;
    v3 = param0->unk_14.unk_14;

    if (param3 == 0) {
        return NULL;
    }

    SpriteSystem_LoadCharResObjFromOpenNarcWithHardwareMappingType(v1, v2, param1, PokeIconSpriteIndex(param3, param5, param4), FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 100000 + param2);

    v4.x = 0;
    v4.y = -48;
    v4.z = 0;
    v4.animIdx = 0;
    v4.priority = 0;
    v4.plttIdx = 0;
    v4.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v4.bgPriority = 0;
    v4.vramTransfer = FALSE;
    v4.resources[0] = 100000 + param2;
    v4.resources[1] = 100000;
    v4.resources[2] = 100000;
    v4.resources[3] = 100000;
    v4.resources[4] = SPRITE_RESOURCE_NONE;
    v4.resources[5] = SPRITE_RESOURCE_NONE;

    v0 = SpriteSystem_NewSprite(v1, v2, &v4);
    v5 = PokeIconPaletteIndex(param3, param4, param5);

    ManagedSprite_SetExplicitPaletteOffset(v0, 4 + v5);
    ManagedSprite_SetAnim(v0, 1);
    ManagedSprite_TickFrame(v0);

    return v0;
}

void VsRecorderViewerList_FreePokemonIconSprite(VsRecorderViewerState *param0, int param1, ManagedSprite *param2)
{
    int v0;

    if (param2 == NULL) {
        return;
    }

    SpriteManager_UnloadCharObjById(param0->unk_14.unk_08, 100000 + param1);
    Sprite_DeleteAndFreeResources(param2);
}

void VsRecorderViewerList_DeletePokemonIconSprite(VsRecorderViewerState *param0, int param1, ManagedSprite *param2)
{
    int v0;

    if (param2 == NULL) {
        return;
    }

    Sprite_DeleteAndFreeResources(param2);
}

static void VsRecorderViewerList_InitSummaryWindows(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1;
    Window *v2;
    String *v3;

    {
        s16 v4[][4] = {
            { 0x4, 0x4, 0x18, 0x2 },
            { 0x4, 0x6, 0x18, 0x4 },
            { 0x4, 0xB, 0x5, 0x2 },
            { 0x4, 0xD, 0x5, 0x2 },
            { 0x4, 0x15, 0x18, 0x2 }
        };

        int v5[] = {
            0x14, 0x14, 0x14, 0xA, 0x14, 0x14
        };

        v1 = 1;

        for (v0 = 0; v0 < 5; v0++) {
            if (v4[v0][0] == 0xFF) {
                break;
            }

            v2 = &param0->unk_3C[v0];
            v3 = MessageLoader_GetNewString(param1->unk_14.unk_34, v5[v0]);

            Window_Init(v2);
            Window_Add(param1->unk_14.unk_10, v2, 2, v4[v0][0], v4[v0][1], v4[v0][2], v4[v0][3], 14, v1);
            Window_FillTilemap(v2, 0x0);
            Text_AddPrinterWithParamsAndColor(v2, FONT_SYSTEM, v3, VsRecorderViewerList_CalcCenteredTextX(v2, v3), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v2);

            v1 += (v4[v0][2] * v4[v0][3]);

            String_Free(v3);
        }
    }

    {
        String *v6;
        String *v7;
        String *v8;
        StringTemplate *v9;
        Window *v10;
        PlayerProfile *v11;

        v11 = param0->unk_00;
        v9 = VsRecorderViewerList_NewStringTemplate(HEAP_ID_102);

        v10 = &param0->unk_3C[0];
        v6 = PlayerProfile_GetName(v11, HEAP_ID_102);
        VsRecorderViewerList_CheckNameChars(param1, v6);
        v7 = MessageLoader_GetNewString(param1->unk_14.unk_34, 7);
        v8 = String_Init(255, HEAP_ID_102);

        StringTemplate_SetString(v9, 0, v6, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v9, v8, v7);
        Window_FillTilemap(v10, 0x0);
        Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
        Window_ScheduleCopyToVRAM(v10);
        String_Free(v6);
        String_Free(v7);
        String_Free(v8);
        StringTemplate_ClearArgs(v9);

        {
            int v12 = BattleRecording_GetSummaryValue(param0->unk_04, 3, 0);

            v10 = &param0->unk_3C[1];
            v8 = MessageLoader_GetNewString(param1->unk_14.unk_34, 132 + v12);

            Window_FillTilemap(v10, 0x0);
            Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v10);
            String_Free(v8);
            StringTemplate_ClearArgs(v9);
        }

        {
            int v13 = BattleRecording_GetSummaryValue(param0->unk_04, 2, 0);

            if (v13 != 0) {
                v10 = &param0->unk_3C[2];
                v6 = String_Init(255, HEAP_ID_102);
                v7 = MessageLoader_GetNewString(param1->unk_14.unk_34, 9);
                v8 = String_Init(255, HEAP_ID_102);

                String_FormatInt(v6, v13, 4, 0, 1);
                StringTemplate_SetString(v9, 0, v6, 0, 1, GAME_LANGUAGE);
                StringTemplate_Format(v9, v8, v7);
                Window_FillTilemap(v10, 0x0);
                Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
                Window_ScheduleCopyToVRAM(v10);
                String_Free(v6);
                String_Free(v7);
                String_Free(v8);
                StringTemplate_ClearArgs(v9);
            } else {
                v10 = &param0->unk_3C[3];
                Window_FillTilemap(v10, 0x0);
                Window_ScheduleCopyToVRAM(v10);
            }
        }

        {
            u64 v14 = BattleRecording_GetSummaryValue(param0->unk_04, 4, 0);
            u64 v15 = v14;
            u32 v16[3];
            String *v17 = String_Init(255, HEAP_ID_102);
            String *v18 = String_Init(255, HEAP_ID_102);
            String *v19 = String_Init(255, HEAP_ID_102);

            v10 = &param0->unk_3C[4];
            v16[0] = v15 % 100000;
            v15 /= 100000;
            v16[1] = v15 % 100000;
            v15 /= 100000;
            v16[2] = v15;

            {
                int v20 = (v16[2] / 10) % 10;

                if ((v20 == 0) && (v14 != 0)) {
                    v7 = MessageLoader_GetNewString(param1->unk_14.unk_34, 12);
                } else {
                    v7 = MessageLoader_GetNewString(param1->unk_14.unk_34, 11);
                }
            }

            v8 = String_Init(255, HEAP_ID_102);

            String_FormatInt(v17, v16[0], 5, 2, 1);
            String_FormatInt(v18, v16[1], 5, 2, 1);
            String_FormatInt(v19, v16[2], 2, 2, 1);
            StringTemplate_SetString(v9, 2, v17, 0, 1, GAME_LANGUAGE);
            StringTemplate_SetString(v9, 1, v18, 0, 1, GAME_LANGUAGE);
            StringTemplate_SetString(v9, 0, v19, 0, 1, GAME_LANGUAGE);
            StringTemplate_Format(v9, v8, v7);
            Window_FillTilemap(v10, 0x0);
            Text_AddPrinterWithParamsAndColor(v10, FONT_SYSTEM, v8, VsRecorderViewerList_CalcCenteredTextX(v10, v8), 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 13, 0), NULL);
            Window_ScheduleCopyToVRAM(v10);
            String_Free(v17);
            String_Free(v18);
            String_Free(v19);
            String_Free(v7);
            String_Free(v8);
            StringTemplate_ClearArgs(v9);
        }

        StringTemplate_Free(v9);
    }
}

static void VsRecorderViewerList_FreeSummaryWindows(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        Window_ClearAndCopyToVRAM(&param0->unk_3C[v0]);
        Window_Remove(&param0->unk_3C[v0]);
    }
}

BOOL VsRecorderViewerList_IsSummaryResultSpecial(BattleRecordingSummary *param0)
{
    int v0;
    BOOL v1 = 0;

    v0 = BattleRecording_GetSummaryValue(param0, 3, 0);

    switch (v0) {
    case UnkEnum_0202F510_17:
    case UnkEnum_0202F510_20:
    case UnkEnum_0202F510_23:
    case UnkEnum_0202F510_26:
    case UnkEnum_0202F510_29:
    case UnkEnum_0202F510_32:
    case UnkEnum_0202F510_14:
        v1 = 1;
        break;
    default:
        v1 = 0;
        break;
    }

    return v1;
}

static BOOL VsRecorderViewerList_IsSummarySpecial(VsRecorderViewerSummaryPanel *param0)
{
    return VsRecorderViewerList_IsSummaryResultSpecial(param0->unk_04);
}

int VsRecorderViewerList_GetSummaryResultMessageID(VsRecorderViewerSummaryPanel *param0)
{
    if (VsRecorderViewerList_IsSummarySpecial(param0) == 1) {
        return 81;
    }

    return 82;
}

static void VsRecorderViewerList_LoadSummarySprites(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1)
{
    int v0;
    int v1;
    int v2;
    int v3 = 0;
    SpriteTemplate v4;
    int v5;
    int v6;
    int v7[12];
    int v8[12];
    int v9;
    SpriteSystem *v10;
    SpriteManager *v11;
    PaletteData *v12;
    s16 v13[][12][2] = {
        {
            { 11 * 8, 13 * 8 },
            { 14 * 8, 13 * 8 },
            { 17 * 8, 13 * 8 },
            { 20 * 8, 13 * 8 },
            { 23 * 8, 13 * 8 },
            { 26 * 8, 13 * 8 },
            { 3 * 8, 19 * 8 },
            { 6 * 8, 19 * 8 },
            { 9 * 8, 19 * 8 },
            { 12 * 8, 19 * 8 },
            { 15 * 8, 19 * 8 },
            { 18 * 8, 19 * 8 },
        },
        {
            { 3 * 8, 17 * 8 },
            { 6 * 8, 17 * 8 },
            { 9 * 8, 17 * 8 },
            { 5 * 8, 20 * 8 },
            { 8 * 8, 20 * 8 },
            { 11 * 8, 20 * 8 },
            { 18 * 8, 17 * 8 },
            { 21 * 8, 17 * 8 },
            { 24 * 8, 17 * 8 },
            { 20 * 8, 20 * 8 },
            { 23 * 8, 20 * 8 },
            { 26 * 8, 20 * 8 },
        },
    };

    v10 = param1->unk_14.unk_04;
    v11 = param1->unk_14.unk_08;
    v12 = param1->unk_14.unk_14;

    SpriteSystem_LoadPaletteBuffer(v12, 2, v10, v11, 19, PokeIconPalettesFileIndex(), 0, 3, NNS_G2D_VRAM_TYPE_2DMAIN, 100000);

    {
        int v14 = PokeIcon64KCellsFileIndex();
        SpriteSystem_LoadCellResObj(v10, v11, 19, v14, 0, 100000);
    }

    {
        int v15 = PokeIcon64KAnimationFileIndex();
        SpriteSystem_LoadAnimResObj(v10, v11, 19, v15, 0, 100000);
    }

    {
        int v16 = 0;
        int v17 = 0;
        int v18 = 0;
        int v19 = 6;
        int v20 = 0;
        int v21 = v19;

        v9 = 0;

        if (VsRecorderViewerList_IsSummarySpecial(param0) == 1) {
            v19 = 3;
            v21 = 3;
            v9 = 1;
        }

        do {
            for (v0 = v20; v0 < v21; v0++) {
                v7[v16] = 0xFF;
                v17 = BattleRecording_GetSummaryValue(param0->unk_04, 0, v0);
                v18 = BattleRecording_GetSummaryValue(param0->unk_04, 1, v0);

                if (v17 == 0) {
                    continue;
                }

                v7[v16] = v17;
                v8[v16] = v18;

                v16++;
            }

            for (v0 = v16; v0 < v21; v0++) {
                v7[v16] = 0;
                v8[v16] = 0;
                v16++;
            }

            v20 += v19;
            v21 += v19;
        } while (v21 <= 12);
    }

    for (v0 = 0; v0 < 12; v0++) {
        param0->unk_0C[v0] = NULL;
        v1 = v7[v0];

        if (v1 == 0) {
            continue;
        }

        v2 = v8[v0];
        v6 = PokeIconSpriteIndex(v1, 0, v2);

        SpriteSystem_LoadCharResObjAtEndWithHardwareMappingType(v10, v11, NARC_INDEX_POKETOOL__ICONGRA__PL_POKE_ICON, v6, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 100000 + v3);

        v4.x = v13[v9][v0][0] + 12 - 4;
        v4.y = v13[v9][v0][1] - 12;
        v4.z = 0;
        v4.animIdx = 0;
        v4.priority = 0;
        v4.plttIdx = 0;
        v4.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v4.bgPriority = 0;
        v4.vramTransfer = FALSE;
        v4.resources[0] = 100000 + v3;
        v4.resources[1] = 100000;
        v4.resources[2] = 100000;
        v4.resources[3] = 100000;
        v4.resources[4] = SPRITE_RESOURCE_NONE;
        v4.resources[5] = SPRITE_RESOURCE_NONE;

        param0->unk_0C[v3] = SpriteSystem_NewSprite(param1->unk_14.unk_04, param1->unk_14.unk_08, &v4);

        v5 = PokeIconPaletteIndex(v1, v2, 0);
        ManagedSprite_SetExplicitPaletteOffset(param0->unk_0C[v3], 4 + v5);
        ManagedSprite_SetAnim(param0->unk_0C[v3], 1);
        ManagedSprite_TickFrame(param0->unk_0C[v3]);
        ManagedSprite_SetPriority(param0->unk_0C[v3], 12 - v0);
        v3++;
    }
}

void VsRecorderViewerList_InitSummary(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1)
{
    VsRecorderViewerList_InitSummaryWindows(param0, param1);
    VsRecorderViewerList_LoadSummarySprites(param0, param1);
}

void VsRecorderViewerList_FreeSummary(VsRecorderViewerSummaryPanel *param0, VsRecorderViewerState *param1)
{
    int v0;

    SpriteManager_UnloadPlttObjById(param1->unk_14.unk_08, 100000);
    SpriteManager_UnloadCellObjById(param1->unk_14.unk_08, 100000);
    SpriteManager_UnloadAnimObjById(param1->unk_14.unk_08, 100000);

    for (v0 = 0; v0 < 12; v0++) {
        if (param0->unk_0C[v0]) {
            SpriteManager_UnloadCharObjById(param1->unk_14.unk_08, 100000 + v0);
            Sprite_DeleteAndFreeResources(param0->unk_0C[v0]);
            param0->unk_0C[v0] = NULL;
        }
    }

    VsRecorderViewerList_FreeSummaryWindows(param0, param1);
}

void VsRecorderViewerList_SetSummarySpritesVisible(VsRecorderViewerSummaryPanel *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 12; v0++) {
        if (param0->unk_0C[v0]) {
            ManagedSprite_SetDrawFlag(param0->unk_0C[v0], param1);
        }
    }
}

int VsRecorderViewerList_CalcCenteredTextX(Window *param0, String *param1)
{
    int v0 = Font_CalcStringWidth(FONT_SYSTEM, param1, 0);
    int v1 = (Window_GetWidth(param0) * 8 - v0) / 2;

    return v1;
}

void VsRecorderViewerList_ResetRecordState(VsRecorderViewerState *param0)
{
    param0->unk_834 = 0;
    param0->unk_836 = 0;
}

BOOL VsRecorderViewerList_ClearExtraSaveKey(VsRecorderViewerState *param0)
{
    MiscSaveBlock *v0 = SaveData_MiscSaveBlock(param0->saveData);
    u32 v1, v2;
    u8 v3;

    MiscSaveBlock_ExtraSaveKey(v0, 2 + param0->unk_86C, &v1, &v2, &v3);
    MiscSaveBlock_SetExtraSaveKey(v0, 2 + param0->unk_86C, 0xffffffff, 0xffffffff, v3);

    return 1;
}

void VsRecorderViewerList_SetBgPriorities(void)
{
    Bg_SetPriority(BG_LAYER_MAIN_0, 1);
    Bg_SetPriority(BG_LAYER_MAIN_1, 3);
    Bg_SetPriority(BG_LAYER_MAIN_2, 0);
    Bg_SetPriority(BG_LAYER_MAIN_3, 1);
    Bg_SetPriority(BG_LAYER_SUB_0, 1);
    Bg_SetPriority(BG_LAYER_SUB_1, 3);
    Bg_SetPriority(BG_LAYER_SUB_2, 0);
    Bg_SetPriority(BG_LAYER_SUB_3, 1);
}

void VsRecorderViewerList_SetupRing(VsRecorderViewerState *param0, VsRecorderRing *param1, s16 param2, s16 param3)
{
    if (param0->unk_14.unk_30 == 0) {
        VsRecorderRing_SetVisible(param1, 1);
    }

    VsRecorderRing_SetActive(param1, 1);

    {
        VsRecorderRing_SetPosition(param1, param2, param3);
        VsRecorderRing_SetTargetPosition(param1, param2, param3);
    }
}

int VsRecorderViewerList_CountDigits(u64 param0)
{
    int v0 = 1;
    u64 v1 = param0;

    while (v1 > 1) {
        v1 /= 10;
        v0++;
    }

    return v0;
}

void VsRecorderViewerList_LoadBgTilemap(VsRecorderViewerState *param0, int param1, int param2)
{
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param0->unk_14.unk_00, param1, param0->unk_14.unk_10, param2, 0, 0, 0, HEAP_ID_102);
}

static void VsRecorderViewerList_Task_ShrinkRing(SysTask *param0, void *param1)
{
    VsRecorderViewerState *v0 = param1;
    s16 v1;

    if ((++v0->unk_41D8.unk_04) >= 7) {
        SysTask_Done(param0);
        v0->unk_41D8.unk_04 = 0;
        v0->unk_41D8.unk_00 = 0;
        VsRecorderRing_StopAnim(v0->unk_41D8.unk_08);
        VsRecorderRing_SetOrbitRadii(v0->unk_41D8.unk_08, 0, 0);
        VsRecorderRing_SetActive(v0->unk_41D8.unk_08, 0);
        VsRecorderRing_SetVisible(v0->unk_41D8.unk_08, 0);
        return;
    }

    v1 = (6 + (v0->unk_41D8.unk_04 * 2));
    VsRecorderRing_SetOrbitRadii(v0->unk_41D8.unk_08, v1, v1);
}

static void VsRecorderViewerList_StartRingAnim(VsRecorderViewerState *param0)
{
    u32 v0, v1;
    s16 v2 = 0;

    if (param0->unk_41D8.unk_00 == 1) {
        if (param0->unk_41D8.unk_0C) {
            SysTask_Done(param0->unk_41D8.unk_0C);
        }

        param0->unk_41D8.unk_0C = NULL;
    }

    if (gSystem.whichScreenIs3D == DS_SCREEN_MAIN) {
        param0->unk_41D8.unk_08 = param0->unk_6F4;
    } else {
        param0->unk_41D8.unk_08 = param0->unk_6F0;
    }

    param0->unk_41D8.unk_00 = 1;
    param0->unk_41D8.unk_04 = 0;

    TouchScreen_GetTapState(&v0, &v1);
    VsRecorderRing_StartAnim(param0->unk_41D8.unk_08);
    VsRecorderRing_SetActive(param0->unk_41D8.unk_08, 1);
    VsRecorderRing_SetVisible(param0->unk_41D8.unk_08, 1);
    VsRecorderRing_SetTargetPosition(param0->unk_41D8.unk_08, v0, v1 + v2);
    VsRecorderRing_SetPosition(param0->unk_41D8.unk_08, v0, v1 + v2);

    param0->unk_41D8.unk_0C = SysTask_Start(VsRecorderViewerList_Task_ShrinkRing, param0, 4096);

    if (param0->unk_41D8.unk_0C != NULL) {
        VsRecorderViewerList_Task_ShrinkRing(param0->unk_41D8.unk_0C, param0);
    } else {
        param0->unk_41D8.unk_00 = 0;
        VsRecorderRing_SetVisible(param0->unk_41D8.unk_08, 0);
        GF_ASSERT(FALSE);
    }
}

void VsRecorderViewerList_PlayRingAnim(VsRecorderViewerState *param0)
{
    VsRecorderViewerList_StartRingAnim(param0);
    Sound_PlayEffect(SEQ_SE_PL_BREC57_sseq);
}

BOOL VsRecorderViewerList_IsDrawSuspended(VsRecorderViewerState *param0)
{
    return param0->unk_14.unk_514;
}

void VsRecorderViewerList_SetDrawSuspended(VsRecorderViewerState *param0, BOOL param1)
{
    param0->unk_14.unk_514 = param1;
}

void VsRecorderViewerList_InitSpriteWithFont(VsRecorderViewerState *param0, VsRecorderViewerTextSprite *param1, int param2, int param3, s16 param4, s16 param5, s16 param6, s16 param7, int param8, BOOL param9)
{
    param1->unk_08 = VsRecorderViewerMenu_CreateCursorSprite(param0, param2);

    VsRecorderViewerMenu_InitLabelOAM(param1, &param0->unk_14, param2);
    VsRecorderViewerMenu_SetLabelOAMText(param1, &param0->unk_14, param3);
    ManagedSprite_SetPositionXY(param1->unk_08, param4, param5);
    FontOAM_SetXY(param1->unk_0C, param6, param7);
    FontOAM_SetDrawFlag(param1->unk_0C, param9);
    ManagedSprite_SetAnim(param1->unk_08, param8);
}

void VsRecorderViewerList_FreeSpriteWithFont(VsRecorderViewerTextSprite *param0)
{
    VsRecorderViewerMenu_FreeLabelOAM(param0);
    Sprite_DeleteAndFreeResources(param0->unk_08);
}

int VsRecorderViewerList_GetMessageIndex(VsRecorderViewerState *param0, int param1, int param2, int param3)
{
    param0->unk_14.unk_4F0.unk_00 = param0->unk_04;
    param0->unk_14.unk_4F0.unk_04 = param0->unk_08;
    param0->unk_14.unk_4F0.unk_08 = *param0->unk_10;
    param0->unk_14.unk_4F0.unk_18 = 1;

    {
        int v0 = 194;

        switch (param3) {
        case 0:
            switch (param2) {
            case 0:
                v0 = 244;
                break;
            case 1:
                v0 = 245;
                break;
            case 2:
                v0 = 246;
                break;
            case 3:
                v0 = 247;
                break;
            case 4:
                v0 = 248;
                break;
            case 5:
                v0 = 249;
                break;
            case 6:
                v0 = 250;
                break;
            case 7:
                v0 = 251;
                break;
            case 8:
                v0 = 252;
                break;
            case 9:
                v0 = 253;
                break;
            case 10:
                v0 = 254;
                break;
            case 11:
                v0 = 255;
                break;
            case 12:
                v0 = 256;
                break;
            case 13:
                v0 = 257;
                break;
            case 14:
                v0 = 258;
                break;
            default:
                GF_ASSERT(FALSE);
                break;
            }
            break;
        case 1:
            switch (param2) {
            case 0:
                v0 = 259;
                break;
            case 1:
                v0 = 260;
                break;
            case 2:
                v0 = 261;
                break;
            case 3:
                v0 = 262;
                break;
            case 4:
                v0 = 263;
                break;
            case 5:
                v0 = 264;
                break;
            case 6:
                v0 = 265;
                break;
            case 7:
                v0 = 266;
                break;
            case 8:
                v0 = 267;
                break;
            case 9:
                v0 = 268;
                break;
            default:
                GF_ASSERT(FALSE);
                break;
            }
            break;
        case 2: {
            switch (param1) {
            case 0:
                switch (param2) {
                case 0:
                    v0 = 194;
                    break;
                case 1:
                    v0 = 195;
                    break;
                case 2:
                    v0 = 196;
                    break;
                case 3:
                    v0 = 197;
                    break;
                case 4:
                    v0 = 198;
                    break;
                case 5:
                    v0 = 199;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 1:
                switch (param2) {
                case 0:
                    v0 = 200;
                    break;
                case 1:
                    v0 = 201;
                    break;
                case 2:
                    v0 = 202;
                    break;
                case 3:
                    v0 = 203;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 2:
                switch (param2) {
                case 0:
                    v0 = 204;
                    break;
                case 1:
                    v0 = 205;
                    break;
                case 2:
                    v0 = 206;
                    break;
                case 3:
                    v0 = 207;
                    break;
                case 4:
                    v0 = 208;
                    break;
                case 5:
                    v0 = 209;
                    break;
                case 6:
                    v0 = 210;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 3:
                switch (param2) {
                case 0:
                    v0 = 211;
                    break;
                case 1:
                    v0 = 212;
                    break;
                case 2:
                    v0 = 213;
                    break;
                case 3:
                    v0 = 214;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 4:
                switch (param2) {
                case 0:
                    v0 = 215;
                    break;
                case 1:
                    v0 = 216;
                    break;
                case 2:
                    v0 = 217;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 5:
                switch (param2) {
                case 0:
                    v0 = 218;
                    break;
                case 1:
                    v0 = 219;
                    break;
                case 2:
                    v0 = 220;
                    break;
                case 3:
                    v0 = 221;
                    break;
                case 4:
                    v0 = 222;
                    break;
                case 5:
                    v0 = 223;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 6:
                switch (param2) {
                case 0:
                    v0 = 224;
                    break;
                case 1:
                    v0 = 225;
                    break;
                case 2:
                    v0 = 226;
                    break;
                case 3:
                    v0 = 227;
                    break;
                case 4:
                    v0 = 228;
                    break;
                case 5:
                    v0 = 229;
                    break;
                case 6:
                    v0 = 230;
                    break;
                case 7:
                    v0 = 231;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 7:
                switch (param2) {
                case 0:
                    v0 = 232;
                    break;
                case 1:
                    v0 = 233;
                    break;
                case 2:
                    v0 = 234;
                    break;
                case 3:
                    v0 = 235;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            case 8:
                switch (param2) {
                case 0:
                    v0 = 236;
                    break;
                case 1:
                    v0 = 237;
                    break;
                case 2:
                    v0 = 238;
                    break;
                case 3:
                    v0 = 239;
                    break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
                break;
            default:
                GF_ASSERT(FALSE);
                break;
            }
        } break;
        }

        param0->unk_14.unk_4F0.unk_0C = v0;
    }

    return param0->unk_14.unk_4F0.unk_0C;
}

void VsRecorderViewerList_OpenMessage(VsRecorderViewerState *param0, int param1, int param2, int param3)
{
    param0->unk_14.unk_4F0.unk_00 = param0->unk_04;
    param0->unk_14.unk_4F0.unk_04 = param0->unk_08;
    param0->unk_14.unk_4F0.unk_08 = *param0->unk_10;
    param0->unk_14.unk_4F0.unk_10 = 0;
    param0->unk_14.unk_4F0.unk_14 = 0;
    param0->unk_14.unk_4F0.unk_0C = VsRecorderViewerList_GetMessageIndex(param0, param1, param2, param3);
    param0->unk_14.unk_4F0.unk_18 = 1;
    *param0->unk_10 = 18;
}

void VsRecorderViewerList_UpdateMessage(VsRecorderViewerState *param0)
{
    switch (param0->unk_14.unk_4F0.unk_10) {
    case 0:
        if (param0->unk_14.unk_4F0.unk_14 < 8) {
            param0->unk_14.unk_4F0.unk_14++;
        } else {
            VsRecorderViewerList_OpenMainMessage(param0, param0->unk_14.unk_4F0.unk_0C);
            param0->unk_14.unk_4F0.unk_10++;
        }

        break;
    case 1:
        if (TouchScreen_Tapped()) {
            VsRecorderViewerList_CloseMainMessage(param0);
            param0->unk_14.unk_4F0.unk_10++;
        }

        break;
    default:
        if (param0->unk_14.unk_4F0.unk_14 > 0) {
            param0->unk_14.unk_4F0.unk_14--;
        } else {
            *param0->unk_10 = param0->unk_14.unk_4F0.unk_08;
        }

        break;
    }
}

BOOL VsRecorderViewerList_HasRecordingValue(VsRecorderViewerState *param0, u64 param1)
{
    u64 v0;
    int v1;

    for (v1 = 1; v1 < 4; v1++) {
        if (param0->unk_87C[v1] == NULL) {
            continue;
        }

        v0 = BattleRecording_GetSummaryValue(param0->unk_87C[v1], 4, 0);

        if (v0 == param1) {
            return 1;
        }
    }

    return 0;
}

void VsRecorderViewerList_CheckNameChars(VsRecorderViewerState *param0, String *param1)
{
    VsRecorderViewerTransferContext *v0 = VsRecorderViewerTransfer_GetTransfer(param0);
    String *v1;
    int v2 = 64;

    v1 = String_Init(v2, v0->heapID);

    if (Font_AreAllCharsValid(FONT_SYSTEM, param1, v1) == 0) {
        VsRecorderViewerList_ReplaceInvalidName(param1, v0->heapID);
    }

    String_Free(v1);
}

static void VsRecorderViewerList_ReplaceInvalidName(String *param0, enum HeapID heapID)
{
    MessageLoader *v0;

    String_Clear(param0);
    v0 = MessageLoader_Init(MSG_LOADER_LOAD_ON_DEMAND, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0010, heapID);

    MessageLoader_GetString(v0, 332, param0);
    MessageLoader_Free(v0);
}
