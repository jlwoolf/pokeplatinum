#include "spin_trade/group_confirmation.h"

#include <nitro.h>
#include <string.h>

#include "generated/journal_online_events.h"
#include "generated/trainer_score_events.h"

#include "struct_defs/struct_0209BF64.h"
#include "struct_defs/struct_0209C194.h"

#include "spin_trade/struct_spin_trade_group.h"
#include "spin_trade/struct_spin_trade_group_palette_anim.h"
#include "spin_trade/struct_spin_trade_group_save_buffer.h"

#include "appearance.h"
#include "bg_window.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "font.h"
#include "game_options.h"
#include "game_records.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "journal.h"
#include "math_util.h"
#include "menu.h"
#include "message.h"
#include "message_util.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"
#include "comm_tool.h"
#include "comm_sync_save.h"
#include "union_room.h"
#include "union_room_comm.h"
#include "vram_transfer.h"
#include "wireless_manager.h"

static void SpinTradeGroup_VBlankCallback(void *param0);
static void SpinTradeGroup_SetGXBanks(void);
static void SpinTradeGroup_InitBg(BgConfig *param0);
static void SpinTradeGroup_InitState(SpinTradeGroup *param0, NARC *param1);
static void SpinTradeGroup_FreeState(SpinTradeGroup *param0);
static void SpinTradeGroup_FreeBg(BgConfig *param0);
static void SpinTradeGroup_LoadGraphics(SpinTradeGroup *param0, NARC *param1);
static void SpinTradeGroup_InitTransfers(void);
static void SpinTradeGroup_InitSprites(SpinTradeGroup *param0, NARC *param1);
static void SpinTradeGroup_CreateSprites(SpinTradeGroup *param0);
static void SpinTradeGroup_CreateWindows(SpinTradeGroup *param0);
static void SpinTradeGroup_RemoveWindows(SpinTradeGroup *param0);
static void SpinTradeGroup_NoOp(SpinTradeGroup *param0);
static void SpinTradeGroup_AnimateIconColor(u16 *param0);
static BOOL SpinTradeGroup_DrawPlayerList(Window *param0, int param1, TextColor param2, SpinTradeGroup *param3);
static BOOL SpinTradeGroup_UpdateTrainerList(SpinTradeGroup *param0);
static void SpinTradeGroup_ShowMessage(SpinTradeGroup *param0, int param1, int param2);
static int SpinTradeGroup_IsMessageDone(int param0);
static void SpinTradeGroup_EraseMessage(SpinTradeGroup *param0);
static int SpinTradeGroup_CountTrainers(void);
static int SpinTradeGroup_CountConnected(void);
static u32 SpinTradeGroup_GetConnectedBitmap(void);
static void SpinTradeGroup_NoOp2(SpinTradeGroup *param0);
static void SpinTradeGroup_DrawCenteredText(Window *param0, String *param1, int param2);
static void SpinTradeGroup_SetState(SpinTradeGroup *param0, int param1);
static void SpinTradeGroup_UpdatePlayerSprites(SpinTradeGroup *param0);
static void SpinTradeGroup_LoadAppearanceGraphics(SpinTradeGroup *param0, NARC *param1);
static void SpinTradeGroup_FreeAppearanceGraphics(SpinTradeGroup *param0);
static void SpinTradeGroup_LoadAppearance(NNSG2dCharacterData *param0[2], NNSG2dPaletteData *param1[2], int param2, int param3, int param4);
static void SpinTradeGroup_PaletteAnimTask(SysTask *param0, void *param1);
static int SpinTradeGroup_GetTextSpeed(SpinTradeGroup *param0);
static void SpinTradeGroup_SetMaxConnections(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_UpdateConnectionState(SpinTradeGroup *param0, int param1);
static void SpinTradeGroup_HandleInput(SpinTradeGroup *param0);
static int SpinTradeGroup_State0(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State1(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State24(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State25(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State26(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State23(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State22(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State4(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State5(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State6(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State7(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State8(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State9(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State10(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State11(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State12(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State13(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State15(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State16(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State17(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State18(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State30(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State19(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State21(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State20(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State2(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State3(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State27(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State28(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State29(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State14(SpinTradeGroup *param0, int param1);
static int SpinTradeGroup_State31(SpinTradeGroup *param0, int param1);
static void SpinTradeGroup_SaveRecords(SaveData *saveData, const SpinTradeGroupSaveBuffer *param1);

static int (*const sStateHandlers[])(SpinTradeGroup *, int) = {
    SpinTradeGroup_State0,
    SpinTradeGroup_State2,
    SpinTradeGroup_State3,
    SpinTradeGroup_State1,
    SpinTradeGroup_State4,
    SpinTradeGroup_State5,
    SpinTradeGroup_State6,
    SpinTradeGroup_State7,
    SpinTradeGroup_State8,
    SpinTradeGroup_State9,
    SpinTradeGroup_State10,
    SpinTradeGroup_State11,
    SpinTradeGroup_State12,
    SpinTradeGroup_State13,
    SpinTradeGroup_State14,
    SpinTradeGroup_State15,
    SpinTradeGroup_State16,
    SpinTradeGroup_State17,
    SpinTradeGroup_State18,
    SpinTradeGroup_State19,
    SpinTradeGroup_State20,
    SpinTradeGroup_State21,
    SpinTradeGroup_State22,
    SpinTradeGroup_State23,
    SpinTradeGroup_State24,
    SpinTradeGroup_State25,
    SpinTradeGroup_State26,
    SpinTradeGroup_State27,
    SpinTradeGroup_State28,
    SpinTradeGroup_State29,
    SpinTradeGroup_State30,
    SpinTradeGroup_State31,
};

int SpinTradeGroup_Init(ApplicationManager *appMan, int *param1)
{
    SpinTradeGroup *v0;
    NARC *v1;
    UnionRoomSpinTradeSession *v2 = ApplicationManager_Args(appMan);

    switch (*param1) {
    case 0:
        SetVBlankCallback(NULL, NULL);
        DisableHBlank();
        GXLayers_DisableEngineALayers();
        GXLayers_DisableEngineBLayers();

        GX_SetVisiblePlane(0);
        GXS_SetVisiblePlane(0);

        Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_95, 0x80000);

        v1 = NARC_ctor(NARC_INDEX_GRAPHIC__RECORD, HEAP_ID_95);
        GF_ASSERT(v1);

        v0 = ApplicationManager_NewData(appMan, sizeof(SpinTradeGroup), HEAP_ID_95);
        memset(v0, 0, sizeof(SpinTradeGroup));

        v2->groupAppData = v0;
        v0->unk_0C = v2;
        v0->unk_10 = v2->comm;
        v0->unk_14 = BgConfig_New(HEAP_ID_95);
        v0->unk_34 = StringTemplate_Default(HEAP_ID_95);
        v0->unk_38 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0377, HEAP_ID_95);

        SetAutorepeat(4, 8);
        SpinTradeGroup_SetGXBanks();
        SpinTradeGroup_InitBg(v0->unk_14);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 16, 1, HEAP_ID_95);
        SpinTradeGroup_LoadGraphics(v0, v1);
        SetVBlankCallback(SpinTradeGroup_VBlankCallback, v0);
        SpinTradeGroup_InitState(v0, v1);
        SpinTradeGroup_InitTransfers();
        SpinTradeGroup_InitSprites(v0, v1);
        SpinTradeGroup_CreateSprites(v0);
        SpinTradeGroup_CreateWindows(v0);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_52, SEQ_NONE, 0);
        UnionRoomComm_Init(v2->comm);
        CommManager_SetState_SpinTrade();
        CommManager_SetMaxNumConnections(3);

        if (CommSys_CurNetId() == 0) {
            UnionRoom_BroadcastActivity(13);
        }

        NetworkIcon_Init();
        v0->unk_30 = SysTask_ExecuteOnVBlank(SpinTradeGroup_PaletteAnimTask, v0, 5);
        NARC_dtor(v1);
        (*param1)++;
        break;
    case 1:
        (*param1) = 0;
        return 1;
    }

    return 0;
}

int SpinTradeGroup_Main(ApplicationManager *appMan, int *param1)
{
    SpinTradeGroup *v0 = ApplicationManager_Data(appMan);

    if ((CommSys_CurNetId() == 0) && (v0->unk_10->confirmedBitmap != 0)) {
        v0->unk_10->confirmedBitmap &= WirelessManager_GetConnectedBitmap();
    }

    switch (v0->unk_00) {
    case 0:
        if (IsScreenFadeDone()) {
            v0->unk_00 = 1;

            if (CommSys_CurNetId() != 0) {
                if (SpinTradeGroup_CountConnected() > 2) {
                    UnionRoomComm_Send(v0->unk_10, 4, NULL, 0);
                }
            }
        }

        break;
    case 1:

        if (sStateHandlers[v0->unk_3B8] != NULL) {
            v0->unk_00 = (*sStateHandlers[v0->unk_3B8])(v0, v0->unk_00);
        }

        if (v0->unk_10->disconnected == 0) {
            SpinTradeGroup_DrawPlayerList(
                v0->unk_30C, 0, TEXT_COLOR(1, 3, 0), v0);
        }

        SpinTradeGroup_UpdatePlayerSprites(v0);

        if (CommSys_CurNetId() == 0) {
            int v1 = SpinTradeGroup_UpdateConnectionState(v0, 1);

            if (v0->unk_00 == 1) {
                v0->unk_00 = v1;
            }
        }

        break;
    case 2:
        if (sStateHandlers[v0->unk_3B8] != NULL) {
            v0->unk_00 = (*sStateHandlers[v0->unk_3B8])(v0, v0->unk_00);
        }

        break;
    case 3:
        if (IsScreenFadeDone()) {
            return 1;
        }

        break;
    }

    SpriteList_Update(v0->unk_60);
    return 0;
}

int SpinTradeGroup_Exit(ApplicationManager *appMan, int *param1)
{
    int v0;
    SpinTradeGroup *v1 = ApplicationManager_Data(appMan);

    SysTask_Done(v1->unk_30);
    SpriteTransfer_ResetCharTransfer(v1->unk_200[2][0]);
    SpriteTransfer_ResetPlttTransfer(v1->unk_200[2][1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(v1->unk_1F0[v0]);
    }

    SpriteList_Delete(v1->unk_60);
    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();

    SpinTradeGroup_RemoveWindows(v1);
    SpinTradeGroup_FreeBg(v1->unk_14);

    MessageLoader_Free(v1->unk_38);
    StringTemplate_Free(v1->unk_34);

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

    SetVBlankCallback(NULL, NULL);

    v1->unk_0C->groupConfirmed = v1->unk_08;
    v1->unk_0C->connectedCount = SpinTradeGroup_CountConnected();
    v1->unk_0C->connectedBitmap = SpinTradeGroup_GetConnectedBitmap();

    SpinTradeGroup_FreeState(v1);
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_95);

    return 1;
}

static const u8 sPaletteAnimFrames[][2] = {
    { 0x8, 0x2 },
    { 0x8, 0x3 },
    { 0x8, 0x4 },
    { 0x18, 0x0 },
    { 0x0, 0xFF }
};

static void SpinTradeGroup_PaletteAnimTask(SysTask *param0, void *param1)
{
    SpinTradeGroup *v0 = (SpinTradeGroup *)param1;
    SpinTradeGroupPaletteAnim *v1 = &v0->unk_1C;

    if (v1->active) {
        if (v1->timer > sPaletteAnimFrames[v1->frameIndex][0]) {
            u16 *v2;

            v1->timer = 0;
            v1->frameIndex++;

            if (sPaletteAnimFrames[v1->frameIndex][1] == 0xff) {
                v1->frameIndex = 0;
            }

            v2 = (u16 *)v1->paletteData->pRawData;
            GX_LoadOBJPltt(&v2[16 * sPaletteAnimFrames[v1->frameIndex][1]], 0, 32);
        } else {
            v0->unk_1C.timer++;
        }

        SpinTradeGroup_AnimateIconColor(&v0->unk_418);
    }
}

static void SpinTradeGroup_VBlankCallback(void *param0)
{
    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates((BgConfig *)param0);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void SpinTradeGroup_SetGXBanks(void)
{
    GXBanks v0 = {
        GX_VRAM_BG_128_A,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_128_B,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_NONE,
        GX_VRAM_TEXPLTT_NONE
    };

    GXLayers_SetBanks(&v0);
}

static void SpinTradeGroup_InitBg(BgConfig *param0)
{
    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v1, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v2, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &v3, 0);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v4, 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate v5 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v5, 0);
    }

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_95);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_95);
}

static void SpinTradeGroup_InitState(SpinTradeGroup *param0, NARC *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->unk_3C[v0] = String_Init(7 + 1, HEAP_ID_95);
        param0->unk_3D8[v0][0] = NULL;
        param0->unk_3D8[v0][1] = NULL;
        param0->unk_400[v0] = 0;
    }

    param0->unk_54 = String_Init(90 * 2, HEAP_ID_95);
    param0->unk_58 = String_Init(20 * 2, HEAP_ID_95);
    param0->unk_3B8 = 0;

    MessageLoader_GetString(param0->unk_38, 17, param0->unk_58);
    SpinTradeGroup_LoadAppearanceGraphics(param0, param1);

    param0->unk_41C = Appearance_LoadTrainerPalette(HEAP_ID_95);
    param0->unk_1C.active = 0;
    param0->unk_1C.timer = 0;
    param0->unk_1C.frameIndex = 0;
    param0->unk_1C.unk_0C = Graphics_GetPlttDataFromOpenNARC(param1, 1, &param0->unk_1C.paletteData, HEAP_ID_95);
    param0->unk_4AA8 = 0;
    param0->unk_394 = NULL;
    param0->unk_10->playerCount = 2;
}

static void SpinTradeGroup_FreeState(SpinTradeGroup *param0)
{
    int v0;

    SpinTradeGroup_FreeAppearanceGraphics(param0);
    Heap_Free(param0->unk_1C.unk_0C);
    Heap_Free(param0->unk_41C);

    for (v0 = 0; v0 < 5; v0++) {
        String_Free(param0->unk_3C[v0]);
    }

    String_Free(param0->unk_58);
    String_Free(param0->unk_54);
}

static void SpinTradeGroup_FreeBg(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
    Heap_Free(param0);
}

static void SpinTradeGroup_LoadGraphics(SpinTradeGroup *param0, NARC *param1)
{
    BgConfig *v0 = param0->unk_14;

    Graphics_LoadPaletteFromOpenNARC(param1, 0, 0, 0, 16 * 16 * 2, HEAP_ID_95);
    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__POKETCH, 12, 4, 0, 16 * 2, HEAP_ID_95);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_95);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(13), HEAP_ID_95);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 10, v0, 6, 0, 0, 1, HEAP_ID_95);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 11, v0, 6, 0, 0, 1, HEAP_ID_95);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 2, v0, 1, 0, 32 * 8 * 0x20, 1, HEAP_ID_95);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 3, v0, 1, 0, 32 * 24 * 2, 1, HEAP_ID_95);
    LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_0, 1, 10, Options_Frame(param0->unk_0C->context.options), HEAP_ID_95);
    LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_0, 1 + (18 + 12), 11, 0, HEAP_ID_95);
}

static void SpinTradeGroup_InitTransfers(void)
{
    {
        CharTransferTemplate v0 = {
            20, 2048, 2048, HEAP_ID_95
        };

        CharTransfer_Init(&v0);
    }

    PlttTransfer_Init(20, HEAP_ID_95);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void SpinTradeGroup_InitSprites(SpinTradeGroup *param0, NARC *param1)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 32, 0, 126, 0, 32, 95);

    param0->unk_60 = SpriteList_InitRendering(30, &param0->unk_64, HEAP_ID_95);
    GF_ASSERT(param0->unk_60);

    SetSubScreenViewRect(&param0->unk_64, 0, 256 * FX32_ONE);

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_1F0[v0] = SpriteResourceCollection_New(3, v0, HEAP_ID_95);
    }

    param0->unk_200[2][0] = SpriteResourceCollection_AddTilesFrom(param0->unk_1F0[0], param1, 12, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_95);
    param0->unk_200[2][1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_1F0[1], param1, 1, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 15, HEAP_ID_95);
    param0->unk_200[2][2] = SpriteResourceCollection_AddFrom(param0->unk_1F0[2], param1, 13, 1, 2, 2, HEAP_ID_95);
    param0->unk_200[2][3] = SpriteResourceCollection_AddFrom(param0->unk_1F0[3], param1, 14, 1, 2, 3, HEAP_ID_95);

    SpriteTransfer_RequestChar(param0->unk_200[2][0]);
    SpriteTransfer_RequestPlttWholeRange(param0->unk_200[2][1]);
}

static const u16 sPlayerSpritePositions[][2] = {
    { 0xCC, 0x54 },
    { 0xCC, 0x35 },
    { 0xE9, 0x48 },
    { 0xDF, 0x67 },
    { 0xB8, 0x67 },
    { 0xAE, 0x48 }
};

static void SpinTradeGroup_CreateSprites(SpinTradeGroup *param0)
{
    int v0;

    SpriteResourcesHeader_Init(&param0->unk_278, 2, 2, 2, 2, 0xffffffff, 0xffffffff, 0, 1, param0->unk_1F0[0], param0->unk_1F0[1], param0->unk_1F0[2], param0->unk_1F0[3], NULL, NULL);

    {
        AffineSpriteListTemplate v1;

        v1.list = param0->unk_60;
        v1.resourceData = &param0->unk_278;
        v1.position.z = 0;
        v1.affineScale.x = FX32_ONE;
        v1.affineScale.y = FX32_ONE;
        v1.affineScale.z = FX32_ONE;
        v1.affineZRotation = 0;
        v1.priority = 1;
        v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v1.heapID = HEAP_ID_95;

        for (v0 = 0; v0 < 5; v0++) {
            v1.position.x = FX32_ONE * sPlayerSpritePositions[v0 + 1][0];
            v1.position.y = FX32_ONE * sPlayerSpritePositions[v0 + 1][1];

            param0->unk_29C[v0 + 1] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->unk_29C[v0 + 1], 1);
            Sprite_SetAnim(param0->unk_29C[v0 + 1], 27 + (v0 - 1) * 2);
            Sprite_SetDrawFlag(param0->unk_29C[v0 + 1], FALSE);
        }

        for (v0 = 0; v0 < 5; v0++) {
            v1.position.x = FX32_ONE * 24;
            v1.position.y = FX32_ONE * (32 + 32 * v0) + (256 * FX32_ONE);
        }
    }
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void SpinTradeGroup_CreateWindows(SpinTradeGroup *param0)
{
    Window_Add(param0->unk_14, &param0->unk_36C, 5, 26, 20, 6, 2, 13, 1 + 30 * 15);
    Window_FillTilemap(&param0->unk_36C, 0x0);
    Window_Add(param0->unk_14, &param0->unk_35C, 0, 2, 19, 27, 4, 13, 1 + (18 + 12) + 9);
    Window_FillTilemap(&param0->unk_35C, 0xf0f);
    Window_Add(param0->unk_14, &param0->unk_37C, 0, 3, 1, 26, 2, 15, (1 + (18 + 12) + 9) + 27 * 4);
    SpinTradeGroup_DrawCenteredText(&param0->unk_37C, param0->unk_58, TEXT_SPEED_INSTANT);

    {
        int v0;

        Window_Add(param0->unk_14, &param0->unk_30C[0], 0, 2, 6, 16, 11, 15, ((1 + (18 + 12) + 9) + 27 * 4) + 26 * 2);
        Window_FillTilemap(&param0->unk_30C[0], 0);
        SpinTradeGroup_DrawPlayerList(param0->unk_30C, 0, TEXT_COLOR(1, 3, 0), param0);
    }
}

static void SpinTradeGroup_DrawCenteredText(Window *param0, String *param1, int param2)
{
    int v0 = Font_CalcStringWidth(FONT_MESSAGE, param1, 0);
    int v1 = (26 * 8 - v0) / 2;

    Window_FillTilemap(param0, 0x0);
    Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, param1, v1, 1, param2, TEXT_COLOR(1, 4, 0), NULL);
}

static void SpinTradeGroup_RemoveWindows(SpinTradeGroup *param0)
{
    int v0;

    Window_Remove(&param0->unk_30C[0]);
    Window_Remove(&param0->unk_37C);
    Window_Remove(&param0->unk_36C);
    Window_Remove(&param0->unk_35C);
}

static int SpinTradeGroup_State0(SpinTradeGroup *param0, int param1)
{
    CommManager_SetErrorHandling(0, 1);

    if (CommSys_CurNetId() == 0) {
        if (CommSys_ConnectedCount() >= 2) {
            SpinTradeGroup_ShowMessage(param0, 2, 0);
        }
    } else {
        SpinTradeGroup_ShowMessage(param0, 8, 0);
    }

    SpinTradeGroup_SetState(param0, 3);

    return param1;
}

static int SpinTradeGroup_State1(SpinTradeGroup *param0, int param1)
{
    SpinTradeGroup_HandleInput(param0);

    if (CommSys_CurNetId() == 0) {
        if (SpinTradeGroup_CountTrainers() != 1) {
            SpinTradeGroup_NoOp2(param0);
        }
    } else {
        SpinTradeGroup_NoOp2(param0);
    }

    return param1;
}

static void SpinTradeGroup_HandleInput(SpinTradeGroup *param0)
{
    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        if (CommSys_CurNetId() == 0) {
            if ((SpinTradeGroup_CountConnected() == param0->unk_10->playerCount) && (param0->unk_10->confirmedBitmap == 0)) {
                u8 v0 = 1;

                SpinTradeGroup_ShowMessage(param0, 3, 0);
                SpinTradeGroup_SetState(param0, 22);
                UnionRoomComm_Send(param0->unk_10, 7, &v0, 1);
                SpinTradeGroup_SetMaxConnections(param0, 0);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        }
    } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
        if (CommSys_CurNetId()) {
            if (param0->unk_10->confirmed == 0) {
                SpinTradeGroup_ShowMessage(param0, 4, 0);
                SpinTradeGroup_SetState(param0, 4);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        } else {
            if ((CommSys_ConnectedCount() == param0->unk_10->playerCount) && (param0->unk_10->confirmedBitmap == 0)) {
                u8 v1 = 1;

                SpinTradeGroup_ShowMessage(param0, 4, 0);
                SpinTradeGroup_SetState(param0, 4);
                UnionRoomComm_Send(param0->unk_10, 7, &v1, 1);
                SpinTradeGroup_SetMaxConnections(param0, 0);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        }
    } else {
        if (param0->unk_4AAC == 0) {
            if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() == param0->unk_10->playerCount)) {
                u8 v2 = 0;

                UnionRoomComm_Send(param0->unk_10, 7, &v2, 1);
            }
        }
    }
}

static void SpinTradeGroup_NoOp(SpinTradeGroup *param0)
{
    return;
}

static int SpinTradeGroup_State2(SpinTradeGroup *param0, int param1)
{
    SpinTradeGroup_SetState(param0, 2);
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static void SpinTradeGroup_SetState(SpinTradeGroup *param0, int param1)
{
    param0->unk_3B8 = 30;
    param0->unk_3BC = param1;
}

static int SpinTradeGroup_State30(SpinTradeGroup *param0, int param1)
{
    if (SpinTradeGroup_IsMessageDone(param0->unk_5C)) {
        param0->unk_3B8 = param0->unk_3BC;
    }

    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State3(SpinTradeGroup *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        int v0 = 0;

        UnionRoomComm_Send(param0->unk_10, 7, &v0, 1);
    }

    param0->unk_3B8 = 3;
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static const WindowTemplate sYesNoWindowTemplate = {
    0x0,
    0x17,
    0xD,
    0x7,
    0x4,
    0xD,
    0x178
};

static int SpinTradeGroup_State4(SpinTradeGroup *param0, int param1)
{
    param0->unk_394 = Menu_MakeYesNoChoice(param0->unk_14, &sYesNoWindowTemplate, 1 + (18 + 12), 11, 95);
    param0->unk_3B8 = 5;

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State5(SpinTradeGroup *param0, int param1)
{
    int v0;
    u32 v1;

    if (CommSys_CurNetId()) {
        if (param0->unk_10->confirmed) {
            if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }

            SpinTradeGroup_NoOp(param0);
            return param1;
        }
    } else {
        if (param0->unk_10->confirmedBitmap != 0) {
            if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }

            SpinTradeGroup_NoOp(param0);
            return param1;
        }
    }

    if (SpinTradeGroup_CountConnected() != CommSys_ConnectedCount()) {
        SpinTradeGroup_NoOp(param0);
        return param1;
    }

    v1 = Menu_ProcessInputAndHandleExit(param0->unk_394, 95);

    if (v1 != 0xffffffff) {
        if (v1 == 0xfffffffe) {
            if (CommSys_CurNetId() == 0) {
                int v2 = 0;

                UnionRoomComm_Send(param0->unk_10, 7, &v2, 1);
                SpinTradeGroup_SetMaxConnections(param0, 1);
            }

            SpinTradeGroup_SetState(param0, 0);
        } else {
            if (CommSys_CurNetId() == 0) {
                SpinTradeGroup_SetState(param0, 11);
                SpinTradeGroup_ShowMessage(param0, 14, 0);
            } else {
                UnionRoomCommConfirm v3;

                MI_CpuClear8(&v3, sizeof(UnionRoomCommConfirm));
                v3.type = 0;
                v3.netId = CommSys_CurNetId();

                param0->unk_4AB4 = 1;
                param0->unk_4AC0 = 0;
                param0->unk_3B8 = 6;

                UnionRoomComm_Send(param0->unk_10, 2, &v3, sizeof(UnionRoomCommConfirm));
            }
        }

        param0->unk_394 = NULL;
    }

    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State6(SpinTradeGroup *param0, int param1)
{
    param0->unk_4AC0 = 0;
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State7(SpinTradeGroup *param0, int param1)
{
    if ((param0->unk_10->serverPlayerCount != CommSys_ConnectedCount()) || (param0->unk_10->serverPlayerCount != SpinTradeGroup_CountConnected())) {
        param0->unk_4AC0 = 0;
        param0->unk_3B8 = 8;
        SpinTradeGroup_NoOp(param0);
        return param1;
    }

    param0->unk_4AC0++;

    if (param0->unk_4AC0 > 30) {
        UnionRoomCommConfirm v0;

        MI_CpuClear8(&v0, sizeof(UnionRoomCommConfirm));
        v0.type = 1;
        v0.netId = CommSys_CurNetId();

        UnionRoomComm_Send(param0->unk_10, 2, &v0, sizeof(UnionRoomCommConfirm));

        param0->unk_4AC0 = 0;
        param0->unk_3B8 = 9;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State8(SpinTradeGroup *param0, int param1)
{
    param0->unk_4AB4 = 0;

    SpinTradeGroup_SetState(param0, 0);
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State22(SpinTradeGroup *param0, int param1)
{
    param0->unk_394 = Menu_MakeYesNoChoice(param0->unk_14, &sYesNoWindowTemplate, 1 + (18 + 12), 11, 95);
    param0->unk_3B8 = 23;

    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State23(SpinTradeGroup *param0, int param1)
{
    int v0;
    u32 v1;

    if ((SpinTradeGroup_CountConnected() != param0->unk_10->playerCount) || (param0->unk_10->confirmedBitmap != 0)) {
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
            Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
        }

        SpinTradeGroup_NoOp(param0);
        return param1;
    }

    v1 = Menu_ProcessInputAndHandleExit(param0->unk_394, 95);

    if (v1 != 0xffffffff) {
        if (v1 == 0xfffffffe) {
            int v2 = 0;

            UnionRoomComm_Send(param0->unk_10, 7, &v2, 1);
            SpinTradeGroup_SetMaxConnections(param0, 1);
            SpinTradeGroup_SetState(param0, 0);
        } else {
            if (CommSys_CurNetId() == 0) {
                param0->unk_3B8 = 24;
                param0->unk_4AB6 = SpinTradeGroup_CountConnected();
                UnionRoom_BroadcastActivity(12);
            } else {
                GF_ASSERT(FALSE);
            }
        }

        param0->unk_394 = NULL;
    }

    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State24(SpinTradeGroup *param0, int param1)
{
    if (param0->unk_4AB7 == 0) {
        if (UnionRoomComm_Send(param0->unk_10, 5, NULL, 0) == 1) {
            param0->unk_3B8 = 31;
        }
    }

    return param1;
}

static int SpinTradeGroup_State25(SpinTradeGroup *param0, int param1)
{
    int v0, v1 = 0;

    if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() != param0->unk_4AB6)) {
        (void)0;
    }

    if (CommSys_ConnectedCount() == param0->unk_10->receivedCount) {
        param0->unk_3B8 = 31;
    }

    return param1;
}

static int SpinTradeGroup_State26(SpinTradeGroup *param0, int param1)
{
    SpinTradeGroup_SaveRecords(param0->unk_0C->context.saveData, param0->unk_FE4);

    param0->unk_3B8 = 27;

    return param1;
}

static int SpinTradeGroup_State27(SpinTradeGroup *param0, int param1)
{
    gSystem.inhibitReset = 1;

    void *journalEntryOnlineEvent = JournalEntry_CreateEventMixedRecords(95);
    JournalEntry_SaveData(param0->unk_0C->context.journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);

    journalEntryOnlineEvent = JournalEntry_CreateEventMisc(95, ONLINE_EVENT_SPIN_TRADE);
    JournalEntry_SaveData(param0->unk_0C->context.journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
    GameRecords_IncrementTrainerScore(param0->unk_0C->context.records, TRAINER_SCORE_EVENT_UNK_20);
    CommSyncSave_Reset(&param0->unk_414);
    param0->unk_3B8 = 28;

    return param1;
}

static int SpinTradeGroup_State28(SpinTradeGroup *param0, int param1)
{
    if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() != param0->unk_4AB6)) {
        (void)0;
    }

    if (CommSyncSave_Update(param0->unk_0C->context.saveData, 2, &param0->unk_414)) {
        Sound_StopEffect(1624, 8);
        SpinTradeGroup_ShowMessage(param0, 13, 0);
        SpinTradeGroup_SetState(param0, 29);

        param0->unk_1C.active = 0;
        param0->unk_3C4 = 0;
        gSystem.inhibitReset = 0;
        param0->unk_10->disconnected = 0;
    }

    return param1;
}

static int SpinTradeGroup_State29(SpinTradeGroup *param0, int param1)
{
    if (param0->unk_3C4++ > 60) {
        param0->unk_3B8 = 15;
    }

    return param1;
}

static int SpinTradeGroup_State9(SpinTradeGroup *param0, int param1)
{
    u8 v0;

    SpinTradeGroup_ShowMessage(param0, 5, 0);

    v0 = 0;

    SpinTradeGroup_SetState(param0, 10);
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State10(SpinTradeGroup *param0, int param1)
{
    if (++param0->unk_3C4 > 60) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_95);
        param1 = 3;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State11(SpinTradeGroup *param0, int param1)
{
    param0->unk_394 = Menu_MakeYesNoChoice(param0->unk_14, &sYesNoWindowTemplate, 1 + (18 + 12), 11, 95);
    param0->unk_3B8 = 12;

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State12(SpinTradeGroup *param0, int param1)
{
    int v0;

    if ((param0->unk_10->playerCount != SpinTradeGroup_CountConnected()) || (param0->unk_10->confirmedBitmap != 0)) {
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
            Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
        }

        SpinTradeGroup_NoOp(param0);
        return param1;
    }

    v0 = Menu_ProcessInputAndHandleExit(param0->unk_394, 95);

    if (v0 != 0xffffffff) {
        if (v0 == 0xfffffffe) {
            int v1 = 0;

            param0->unk_3B8 = 0;

            UnionRoomComm_Send(param0->unk_10, 7, &v1, 1);
            SpinTradeGroup_SetMaxConnections(param0, 1);
        } else {
            param0->unk_3B8 = 13;
            UnionRoomComm_Send(param0->unk_10, 3, NULL, 0);
            StringTemplate_SetPlayerName(param0->unk_34, 0, CommInfo_TrainerInfo(0));
        }

        param0->unk_394 = NULL;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State13(SpinTradeGroup *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        SpinTradeGroup_ShowMessage(param0, 5, 0);
    } else {
        StringTemplate_SetPlayerName(param0->unk_34, 0, CommInfo_TrainerInfo(0));
        SpinTradeGroup_ShowMessage(param0, 16, 0);
    }

    SpinTradeGroup_SetState(param0, 14);
    param0->unk_3C4 = 0;
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State14(SpinTradeGroup *param0, int param1)
{
    param0->unk_3C4++;

    if (param0->unk_3C4 > 45) {
        param0->unk_3B8 = 15;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State15(SpinTradeGroup *param0, int param1)
{
    CommTiming_StartSync(202);
    param0->unk_3B8 = 16;

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State16(SpinTradeGroup *param0, int param1)
{
    if (CommTiming_IsSyncState(202)) {
        CommManager_SetErrorHandling(0, 0);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_95);
        param1 = 3;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State17(SpinTradeGroup *param0, int param1)
{
    if (SpinTradeGroup_IsMessageDone(param0->unk_5C)) {
        SpinTradeGroup_ShowMessage(param0, 9, 0);
    }

    param0->unk_3B8 = 18;
    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State18(SpinTradeGroup *param0, int param1)
{
    if (SpinTradeGroup_IsMessageDone(param0->unk_5C)) {
        param0->unk_3B8 = 10;
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State19(SpinTradeGroup *param0, int param1)
{
    if ((param0->unk_5C != 0xff) && (SpinTradeGroup_IsMessageDone(param0->unk_5C) == 0)) {
        Text_RemovePrinter(param0->unk_5C);
    }

    SpinTradeGroup_ShowMessage(param0, 15, 1);
    param0->unk_3B8 = 20;

    if (CommSys_CurNetId() == 0) {
        SpinTradeGroup_SetMaxConnections(param0, 0);
    }

    param0->unk_4ABC = CommSys_ConnectedCount();
    param0->unk_4AB8 = (10 * 30);

    SpinTradeGroup_NoOp(param0);

    return param1;
}

static int SpinTradeGroup_State20(SpinTradeGroup *param0, int param1)
{
    if ((param0->unk_4ABC != 0) && (CommSys_ConnectedCount() != param0->unk_4ABC)) {
        param0->unk_4ABC = 0;
    }

    param0->unk_3B8 = 21;
    param0->unk_3C4 = 0;

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State21(SpinTradeGroup *param0, int param1)
{
    if ((param0->unk_4ABC != 0) && (CommSys_ConnectedCount() != param0->unk_4ABC)) {
        param0->unk_4ABC = 0;
    }

    param0->unk_4AB8--;

    if (param0->unk_4AB8 < 0) {
        param0->unk_4ABC = 0;
    }

    if ((++param0->unk_3C4 > 60) && (param0->unk_4ABC == 0)) {
        param0->unk_3B8 = 0;

        if (CommSys_CurNetId() == 0) {
            SpinTradeGroup_SetMaxConnections(param0, 1);
        }
    }

    SpinTradeGroup_NoOp(param0);
    return param1;
}

static int SpinTradeGroup_State31(SpinTradeGroup *param0, int param1)
{
    UnionRoom_BroadcastActivity(12);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_95);

    param0->unk_08 = 1;
    param1 = 3;

    SpinTradeGroup_NoOp(param0);
    return param1;
}

void SpinTradeGroup_HandleCommState(SpinTradeGroup *param0, int param1, u8 param2)
{
    switch (param1) {
    case 2:
        SpinTradeGroup_EraseMessage(param0);
        break;
    case 13:
        if (param0->unk_394 != NULL) {
            Menu_DestroyForExit(param0->unk_394, 95);
            param0->unk_394 = NULL;
        }

        break;
    case 25:
        if (SpinTradeGroup_IsMessageDone(param0->unk_5C) == 0) {
            Text_RemovePrinter(param0->unk_5C);
        }

        SpinTradeGroup_ShowMessage(param0, 12, 0);

        if (param0->unk_394 != NULL) {
            Menu_DestroyForExit(param0->unk_394, 95);
            param0->unk_394 = NULL;
        }

        break;
    case 19:
        if (param0->unk_4AB4 == 1) {
            return;
        }

        StringTemplate_SetPlayerName(param0->unk_34, 0, CommInfo_TrainerInfo(param2));

        if (param2 == CommSys_CurNetId()) {
            return;
        }

        if (param0->unk_394 != NULL) {
            Menu_DestroyForExit(param0->unk_394, 95);
            param0->unk_394 = NULL;
        }

        if (CommSys_CurNetId() == 0) {
            param0->unk_10->confirmedBitmap &= 0xffff ^ param2;
        }
        break;
    case 7:
        break;
    case 8:
        break;
    case 31:
        if (SpinTradeGroup_IsMessageDone(param0->unk_5C) == 0) {
            Text_RemovePrinter(param0->unk_5C);
        }

        if (param0->unk_394 != NULL) {
            Menu_DestroyForExit(param0->unk_394, 95);
            param0->unk_394 = NULL;
        }

        break;
    default:
        GF_ASSERT("FALSE");
        return;
    }

    param0->unk_3B8 = param1;
}

void SpinTradeGroup_HandleConfirm(SpinTradeGroup *param0, int param1, u8 param2)
{
    if (param0->unk_3B8 == 3) {
        switch (param1) {
        case 1:
            StringTemplate_SetPlayerName(param0->unk_34, 0, CommInfo_TrainerInfo(param2));
            SpinTradeGroup_SetMaxConnections(param0, 1);

            param0->unk_3B8 = param1;
            param0->unk_10->playerCount = CommSys_ConnectedCount();
            param0->unk_10->confirmedBitmap = 0;

            if (CommSys_CurNetId() == 0) {
                int v0 = 1;
                UnionRoomComm_Send(param0->unk_10, 7, &v0, 1);
            }
            break;
        case 19:
            StringTemplate_SetPlayerName(param0->unk_34, 0, CommInfo_TrainerInfo(param2));

            if (param2 == CommSys_CurNetId()) {
                return;
            }

            if (CommSys_CurNetId() == 0) {
                param0->unk_10->confirmedBitmap &= 0xffff ^ param2;
            }

            param0->unk_3B8 = param1;
            break;
        default:
            GF_ASSERT(FALSE);
            return;
        }
    } else if (param1 == 1) {
        param0->unk_10->confirmedBitmap = 0;
        param0->unk_10->playerCount = CommSys_ConnectedCount();
    }
}

static void SpinTradeGroup_AnimateIconColor(u16 *param0)
{
    fx32 v0;
    GXRgb v1;
    int v2, v3, v4;

    *param0 += 10;

    if (*param0 > 360) {
        *param0 = 0;
    }

    v0 = CalcSineDegrees_Wraparound(*param0);
    v3 = 15 + (v0 * 10) / FX32_ONE;
    v1 = GX_RGB(29, v3, 0);

    GX_LoadOBJPltt((u16 *)&v1, 5 * 2, 2);
    GX_LoadOBJPltt((u16 *)&v1, (5 + 16) * 2, 2);
}

static int SpinTradeGroup_CountTrainers(void)
{
    int v0, v1;
    TrainerInfo *v2;

    v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        v2 = CommInfo_TrainerInfo(v0);

        if (v2 != NULL) {
            v1++;
        }
    }

    return v1;
}

static BOOL SpinTradeGroup_DrawPlayerList(Window *param0, int param1, TextColor param2, SpinTradeGroup *param3)
{
    int v0, v1 = CommSys_CurNetId();
    String *v2 = NULL;

    if (!SpinTradeGroup_UpdateTrainerList(param3)) {
        return 0;
    }

    Window_FillTilemap(&param0[0], 0x0);

    for (v0 = 0; v0 < 5; v0++) {
        if (param3->unk_3D8[v0][0] != NULL) {
            u16 v3 = TrainerInfo_ID_LowHalf(param3->unk_3D8[v0][0]);

            TrainerInfo_NameString(param3->unk_3D8[v0][0], param3->unk_3C[v0]);
            StringTemplate_SetNumber(param3->unk_34, 0, v3, 5, 2, 1);
            v2 = MessageUtil_ExpandedString(param3->unk_34, param3->unk_38, 1, HEAP_ID_95);

            if (v1 == v0) {
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, param3->unk_3C[v0], 5, 1 + v0 * 18, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 3, 0), NULL);
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, v2, 5 + 13 * 5, 1 + v0 * 18, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 3, 0), NULL);
            } else {
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, param3->unk_3C[v0], 5, 1 + v0 * 18, TEXT_SPEED_NO_TRANSFER, param2, NULL);
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, v2, 5 + 13 * 5, 1 + v0 * 18, TEXT_SPEED_NO_TRANSFER, param2, NULL);
            }

            String_Free(v2);
        }
    }

    Window_CopyToVRAM(&param0[0]);

    return 1;
}

static void SpinTradeGroup_NoOp2(SpinTradeGroup *param0)
{
    return;
}

static int SpinTradeGroup_CountConnected(void)
{
    int v0, v1;

    for (v1 = 0, v0 = 0; v0 < 5; v0++) {
        if (CommInfo_TrainerInfo(v0) != NULL) {
            v1++;
        }
    }

    return v1;
}

static u32 SpinTradeGroup_GetConnectedBitmap(void)
{
    int v0;
    u32 v1;

    for (v1 = 0, v0 = 0; v0 < 5; v0++) {
        if (CommInfo_TrainerInfo(v0) != NULL) {
            v1 |= 1 << v0;
        }
    }

    return v1;
}

static BOOL SpinTradeGroup_UpdateTrainerList(SpinTradeGroup *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->unk_3D8[v0][1] = param0->unk_3D8[v0][0];
        param0->unk_3D8[v0][0] = CommInfo_TrainerInfo(v0);
        param0->unk_4AC4[v0][1] = param0->unk_4AC4[v0][0];

        if (param0->unk_3D8[v0][0] != NULL) {
            param0->unk_4AC4[v0][0].val2.unk_00 = TrainerInfo_ID(param0->unk_3D8[v0][0]);
            param0->unk_4AC4[v0][0].val2.unk_04 = 1;
        } else {
            param0->unk_4AC4[v0][0].val1 = 0;
        }
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->unk_3D8[v0][1] != param0->unk_3D8[v0][0]) {
            v1 = 1;

            if (param0->unk_3D8[v0][0] == NULL) {
                param0->unk_400[v0] = 3;
            } else {
                param0->unk_400[v0] = 1;
            }
        } else {
            if (param0->unk_4AC4[v0][0].val1 != param0->unk_4AC4[v0][1].val1) {
                v1 = 1;

                if (param0->unk_4AC4[v0][0].val2.unk_04 == 0) {
                    param0->unk_400[v0] = 3;
                } else {
                    param0->unk_400[v0] = 1;
                }
            }
        }
    }

    return v1;
}

static void SpinTradeGroup_ShowMessage(SpinTradeGroup *param0, int param1, int param2)
{
    String *v0 = String_Init(90 * 2, HEAP_ID_95);

    MessageLoader_GetString(param0->unk_38, param1, v0);
    StringTemplate_Format(param0->unk_34, param0->unk_54, v0);
    String_Free(v0);
    Window_FillTilemap(&param0->unk_35C, 0xf0f);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_35C, 0, 1, 10);

    if (param2 == 0) {
        param0->unk_5C = Text_AddPrinterWithParams(&param0->unk_35C, FONT_MESSAGE, param0->unk_54, 0, 0, SpinTradeGroup_GetTextSpeed(param0), NULL);
    } else {
        Text_AddPrinterWithParams(&param0->unk_35C, FONT_MESSAGE, param0->unk_54, 0, 0, TEXT_SPEED_INSTANT, NULL);
        param0->unk_5C = 0xff;
    }
}

static int SpinTradeGroup_IsMessageDone(int param0)
{
    if (param0 == 0xff) {
        return 1;
    }

    if (Text_IsPrinterActive(param0) == 0) {
        return 1;
    }

    return 0;
}

static void SpinTradeGroup_EraseMessage(SpinTradeGroup *param0)
{
    Window_EraseMessageBox(&param0->unk_35C, 0);
}

static void SpinTradeGroup_UpdatePlayerSprites(SpinTradeGroup *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        switch (param0->unk_400[v0]) {
        case 0:
            break;
        case 1: {
            int v2, v3;

            GF_ASSERT(param0->unk_3D8[v0][0] != NULL);

            v3 = TrainerInfo_Gender(param0->unk_3D8[v0][0]);
            v2 = TrainerInfo_Appearance(param0->unk_3D8[v0][0]);

            if (CommSys_CurNetId() == v0) {
                Sprite_SetAnim(param0->unk_29C[v0 + 1], 38 + v3 * 2);
            } else {
                SpinTradeGroup_LoadAppearance(param0->unk_3A0, param0->unk_3B0, v0, v2, v3);
                Sprite_SetAnim(param0->unk_29C[v0 + 1], 27 + v0 * 2);
            }
        }
            Sprite_SetDrawFlag(param0->unk_29C[v0 + 1], TRUE);
            param0->unk_400[v0] = 2;
            v1 = 1;
            break;
        case 2:
            break;
        case 3:
            if (CommSys_CurNetId() == v0) {
                int v4 = TrainerInfo_Gender(param0->unk_3D8[v0][0]);

                Sprite_SetAnim(param0->unk_29C[v0 + 1], 38 + v4 * 2 + 1);
            } else {
                Sprite_SetAnim(param0->unk_29C[v0 + 1], 27 + v0 * 2 + 1);
            }

            param0->unk_400[v0] = 0;
            break;
        }
    }

    if (v1) {
        Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
    }
}

static void SpinTradeGroup_LoadAppearanceGraphics(SpinTradeGroup *param0, NARC *param1)
{
    param0->unk_3A8[0] = Graphics_GetPlttData(NARC_INDEX_GRAPHIC__WORLDTRADE, 8, &(param0->unk_3B0[0]), HEAP_ID_95);
    param0->unk_3A8[1] = Graphics_GetPlttDataFromOpenNARC(param1, 7, &(param0->unk_3B0[1]), HEAP_ID_95);
    param0->unk_398[0] = Graphics_GetCharData(NARC_INDEX_GRAPHIC__WORLDTRADE, 32, 1, &(param0->unk_3A0[0]), HEAP_ID_95);
    param0->unk_398[1] = Graphics_GetCharDataFromOpenNARC(param1, 9, 1, &(param0->unk_3A0[1]), HEAP_ID_95);
}

static const u16 sAppearanceObjOffsets[] = {
    0x1A0,
    0x7A0,
    0xDA0,
    0x13A0,
    0x19A0
};

static void SpinTradeGroup_LoadAppearance(NNSG2dCharacterData *param0[2], NNSG2dPaletteData *param1[2], int param2, int param3, int param4)
{
    int v0;
    u8 *v1, *v2;

    v0 = Appearance_GetIndex(param4, param3);
    v1 = (u8 *)param0[1]->pRawData;
    v2 = (u8 *)param1[1]->pRawData;

    GX_LoadOBJ(&v1[(3 * 4 * 4) * v0 * 0x20], sAppearanceObjOffsets[param2], (3 * 4 * 4) * 0x20);
    GX_LoadOBJPltt(&v2[v0 * 32], (param2 + 7) * 32, 32);
}

static void SpinTradeGroup_FreeAppearanceGraphics(SpinTradeGroup *param0)
{
    Heap_Free(param0->unk_3A8[0]);
    Heap_Free(param0->unk_3A8[1]);
    Heap_Free(param0->unk_398[0]);
    Heap_Free(param0->unk_398[1]);
}

static int SpinTradeGroup_GetTextSpeed(SpinTradeGroup *param0)
{
    return TEXT_SPEED_FAST;
}

static void SpinTradeGroup_SetMaxConnections(SpinTradeGroup *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        if (param1 == -1) {
            CommManager_SetMaxNumConnections(1);
        } else {
            int v0 = CommSys_ConnectedCount() + param1;

            if (v0 > 5) {
                v0 = 5;
            }

            CommManager_SetMaxNumConnections(v0);
        }

        if (param1 == -1) {
            param0->unk_4AB5 = 2;
        } else if (param1 == 0) {
            param0->unk_4AB5 = 1;
        } else {
            param0->unk_4AB5 = 0;
        }
    }
}

static int SpinTradeGroup_UpdateConnectionState(SpinTradeGroup *param0, int param1)
{
    int v0 = SpinTradeGroup_CountConnected();

    if (v0 > param0->unk_10->playerCount) {
        u8 v1 = 1;

        UnionRoomComm_Send(param0->unk_10, 7, &v1, 1);
        param0->unk_4AAC = 1;
    } else {
        param0->unk_4AAC = 0;
    }

    if (v0 == param0->unk_4AA8) {
        return 1;
    }

    switch (v0) {
    case 1:
        if ((CommSys_ConnectedCount() > 1) || (WirelessManager_GetConnectedBitmap() > 1)) {
            return 1;
        }

        param0->unk_3B8 = 17;
        SpinTradeGroup_SetMaxConnections(param0, -1);

        if (param0->unk_394 != NULL) {
            Menu_DestroyForExit(param0->unk_394, 95);
            param0->unk_394 = NULL;
        }
        return 2;
        break;
    case 2:
    case 3:
    case 4:
        UnionRoom_BroadcastActivity(13);

        if (v0 < param0->unk_4AA8) {
            switch (param0->unk_4AB5) {
            case 0:
                SpinTradeGroup_SetMaxConnections(param0, param1);
                break;
            case 1:
                SpinTradeGroup_SetMaxConnections(param0, 0);
                break;
            }

            param0->unk_10->playerCount = CommSys_ConnectedCount();
        }
        break;
    case 5:
        UnionRoom_BroadcastActivity(12);
        SpinTradeGroup_SetMaxConnections(param0, param1);
        break;
    }

    param0->unk_4AA8 = SpinTradeGroup_CountConnected();

    return 1;
}

void SpinTradeGroup_SaveRecords(SaveData *saveData, const SpinTradeGroupSaveBuffer *param1)
{
    return;
}
