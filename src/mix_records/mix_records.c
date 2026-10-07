#include "mix_records/mix_records.h"

#include <nitro.h>
#include <string.h>

#include "generated/trainer_score_events.h"

#include "struct_decls/struct_020961E8_decl.h"
#include "struct_defs/struct_0203DE34.h"
#include "struct_defs/struct_020961E8_t.h"
#include "struct_defs/struct_02096274.h"

#include "mix_records/mix_records_exchange.h"
#include "mix_records/struct_mix_records_animation.h"

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
#include "union_room_trainers.h"
#include "mix_records_comm.h"
#include "vram_transfer.h"
#include "wireless_manager.h"

static void MixRecords_VBlankCallback(void *param0);
static void MixRecords_SetGXBanks(void);
static void MixRecords_InitBgLayers(BgConfig *param0);
static void MixRecords_InitState(MixRecordsComm *param0, NARC *param1);
static void MixRecords_FreeState(MixRecordsComm *param0);
static void MixRecords_FreeBgLayers(BgConfig *param0);
static void MixRecords_LoadGraphics(MixRecordsComm *param0, NARC *param1);
static void MixRecords_InitTransfers(void);
static void MixRecords_InitSprites(MixRecordsComm *param0, NARC *param1);
static void MixRecords_CreateSprites(MixRecordsComm *param0);
static void MixRecords_CreateWindows(MixRecordsComm *param0, ApplicationManager *appMan);
static void MixRecords_RemoveWindows(MixRecordsComm *param0);
static void MixRecords_NoOp(MixRecordsComm *unused);
static void MixRecords_AnimatePaletteCycle(u16 *param0);
static BOOL MixRecords_DrawPlayerList(Window *param0, int unused, u32 param2, MixRecordsComm *param3);
static BOOL MixRecords_UpdateTrainerInfo(MixRecordsComm *param0);
static void MixRecords_ShowMessage(MixRecordsComm *param0, int param1, int param2);
static int MixRecords_IsMessageDone(int param0);
static void MixRecords_EraseMessageBox(MixRecordsComm *param0);
static int MixRecords_CountConnectedTrainers(void);
static int MixRecords_CountConnectedPlayers(void);
static void MixRecords_NoOpUnused(MixRecordsComm *unused);
static void MixRecords_DrawHeader(Window *param0, String *param1, int param2);
static void MixRecords_SetNextState(MixRecordsComm *param0, int param1);
static void MixRecords_UpdateSprites(MixRecordsComm *param0);
static void MixRecords_LoadTrainerGraphics(MixRecordsComm *param0, NARC *param1);
static void MixRecords_FreeTrainerGraphics(MixRecordsComm *param0);
static void MixRecords_LoadTrainerSprite(NNSG2dCharacterData *param0[2], NNSG2dPaletteData *param1[2], int param2, int param3, int param4);
static void MixRecords_VBlankTask(SysTask *sysTask, void *param1);
static int MixRecords_GetMessageTextSpeed(MixRecordsComm *param0);
static void MixRecords_SetMaxConnections(MixRecordsComm *param0, int param1);
static int MixRecords_UpdateConnectionState(MixRecordsComm *param0, int param1);
static void MixRecords_HandleInput(MixRecordsComm *param0);
static int MixRecords_StateWaitForPlayers(MixRecordsComm *param0, int param1);
static int MixRecords_StateHandleInput(MixRecordsComm *param0, int param1);
static int MixRecords_StateSendDisconnect(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitReceivedRecords(MixRecordsComm *param0, int param1);
static int MixRecords_StateApplyRecords(MixRecordsComm *param0, int param1);
static int MixRecords_StateProcessRecordMenu(MixRecordsComm *param0, int param1);
static int MixRecords_StateCreateRecordMenu(MixRecordsComm *param0, int param1);
static int MixRecords_StateCreateYesNoMenu(MixRecordsComm *param0, int param1);
static int MixRecords_StateProcessYesNo(MixRecordsComm *param0, int param1);
static int MixRecords_StateResetRetryTimer(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitConnectionConfirm(MixRecordsComm *param0, int param1);
static int MixRecords_StateConfirmRejected(MixRecordsComm *param0, int param1);
static int MixRecords_StateShowCancelled(MixRecordsComm *param0, int param1);
static int MixRecords_StateFadeOut(MixRecordsComm *param0, int param1);
static int MixRecords_StateCreateCancelMenu(MixRecordsComm *param0, int param1);
static int MixRecords_StateProcessCancelMenu(MixRecordsComm *param0, int param1);
static int MixRecords_StateShowMixing(MixRecordsComm *param0, int param1);
static int MixRecords_StateStartSync(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitSync(MixRecordsComm *param0, int param1);
static int MixRecords_StateShowPlayerLeft(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitPlayerLeft(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitMessage(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitRecords(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitRecordsDone(MixRecordsComm *param0, int param1);
static int MixRecords_StateCheckConnection(MixRecordsComm *param0, int param1);
static int MixRecords_StateStart(MixRecordsComm *param0, int param1);
static int MixRecords_StateResetConfirm(MixRecordsComm *param0, int param1);
static int MixRecords_StateSaveRecords(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitSaveSync(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitAfterSave(MixRecordsComm *param0, int param1);
static int MixRecords_StateWaitMixing(MixRecordsComm *param0, int param1);

static int (*sStateHandlers[])(MixRecordsComm *, int) = {
    MixRecords_StateWaitForPlayers,
    MixRecords_StateStart,
    MixRecords_StateResetConfirm,
    MixRecords_StateHandleInput,
    MixRecords_StateCreateYesNoMenu,
    MixRecords_StateProcessYesNo,
    MixRecords_StateResetRetryTimer,
    MixRecords_StateWaitConnectionConfirm,
    MixRecords_StateConfirmRejected,
    MixRecords_StateShowCancelled,
    MixRecords_StateFadeOut,
    MixRecords_StateCreateCancelMenu,
    MixRecords_StateProcessCancelMenu,
    MixRecords_StateShowMixing,
    MixRecords_StateWaitMixing,
    MixRecords_StateStartSync,
    MixRecords_StateWaitSync,
    MixRecords_StateShowPlayerLeft,
    MixRecords_StateWaitPlayerLeft,
    MixRecords_StateWaitRecords,
    MixRecords_StateCheckConnection,
    MixRecords_StateWaitRecordsDone,
    MixRecords_StateCreateRecordMenu,
    MixRecords_StateProcessRecordMenu,
    MixRecords_StateSendDisconnect,
    MixRecords_StateWaitReceivedRecords,
    MixRecords_StateApplyRecords,
    MixRecords_StateSaveRecords,
    MixRecords_StateWaitSaveSync,
    MixRecords_StateWaitAfterSave,
    MixRecords_StateWaitMessage,
};

int MixRecords_Init(ApplicationManager *appMan, int *param1)
{
    MixRecordsComm *v0;
    NARC *v1;

    switch (*param1) {
    case 0:
        SetVBlankCallback(NULL, NULL);
        DisableHBlank();
        GXLayers_DisableEngineALayers();
        GXLayers_DisableEngineBLayers();

        GX_SetVisiblePlane(0);
        GXS_SetVisiblePlane(0);

        Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_51, 0x41000);

        v1 = NARC_ctor(NARC_INDEX_GRAPHIC__RECORD, HEAP_ID_51);
        v0 = ApplicationManager_NewData(appMan, sizeof(MixRecordsComm), HEAP_ID_51);

        memset(v0, 0, sizeof(MixRecordsComm));

        v0->bgConfig = BgConfig_New(HEAP_ID_51);
        v0->appArgs = (UnkStruct_0203DE34 *)ApplicationManager_Args(appMan);
        v0->saveData = v0->appArgs->saveData;
        v0->strTemplate = StringTemplate_Default(HEAP_ID_51);
        v0->msgLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0533, HEAP_ID_51);

        SetAutorepeat(4, 8);

        MixRecords_SetGXBanks();
        MixRecords_InitBgLayers(v0->bgConfig);

        ResetScreenMasterBrightness(DS_SCREEN_MAIN);
        ResetScreenMasterBrightness(DS_SCREEN_SUB);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_IN, FADE_TYPE_CIRCLE_IN, COLOR_BLACK, 16, 1, HEAP_ID_51);

        MixRecords_LoadGraphics(v0, v1);
        SetVBlankCallback(MixRecords_VBlankCallback, v0);

        MixRecords_InitState(v0, v1);
        MixRecords_InitTransfers();
        MixRecords_InitSprites(v0, v1);
        MixRecords_CreateSprites(v0);
        MixRecords_CreateWindows(v0, appMan);

        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_52, SEQ_NONE, 0);
        MixRecordsComm_Init(v0);
        CommManager_SetState_MixRecords();
        CommManager_SetMaxNumConnections(3);

        if (CommSys_CurNetId() == 0) {
            UnionRoom_BroadcastActivity(2);
        }

        NetworkIcon_Init();
        MixRecords_SerializeLocalRecord(v0->saveData, &v0->localRecord);

        v0->vBlankTask = SysTask_ExecuteOnVBlank(MixRecords_VBlankTask, v0, 5);

        NARC_dtor(v1);
        (*param1)++;
        break;
    case 1:
        v0 = ApplicationManager_Data(appMan);
        (*param1) = 0;
        return 1;
        break;
    }

    return 0;
}

int MixRecords_Main(ApplicationManager *appMan, int *param1)
{
    MixRecordsComm *v0 = ApplicationManager_Data(appMan);

    if ((CommSys_CurNetId() == 0) && (v0->confirmedBitmap != 0)) {
        v0->confirmedBitmap &= WirelessManager_GetConnectedBitmap();
    }

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone()) {
            *param1 = 1;

            if (CommSys_CurNetId() != 0) {
                if (MixRecords_CountConnectedPlayers() > 2) {
                    CommSys_SendData(114, NULL, 0);
                }
            }
        }
        break;
    case 1:
        if (sStateHandlers[v0->state] != NULL) {
            *param1 = (*sStateHandlers[v0->state])(v0, *param1);
        }

        if (v0->disconnected == 0) {
            MixRecords_DrawPlayerList(v0->playerWindows, 0, TEXT_COLOR(1, 3, 0), v0);
        }

        MixRecords_UpdateSprites(v0);

        if (CommSys_CurNetId() == 0) {
            int v1 = MixRecords_UpdateConnectionState(v0, 1);

            if (*param1 == 1) {
                *param1 = v1;
            }
        }
        break;
    case 2:
        if (sStateHandlers[v0->state] != NULL) {
            *param1 = (*sStateHandlers[v0->state])(v0, *param1);
        }
        break;
    case 3:
        if (IsScreenFadeDone()) {
            return 1;
        }
        break;
    }

    SpriteList_Update(v0->spriteList);

    return 0;
}

int MixRecords_Exit(ApplicationManager *appMan, int *unused)
{
    MixRecordsComm *v0 = ApplicationManager_Data(appMan);

    SysTask_Done(v0->vBlankTask);
    SpriteTransfer_ResetCharTransfer(v0->spriteResources[2][0]);
    SpriteTransfer_ResetPlttTransfer(v0->spriteResources[2][1]);

    for (int i = 0; i < 4; i++) {
        SpriteResourceCollection_Delete(v0->spriteResourceCollections[i]);
    }

    SpriteList_Delete(v0->spriteList);
    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();

    MixRecords_RemoveWindows(v0);
    MixRecords_FreeBgLayers(v0->bgConfig);

    CommManager_SetMaxNumConnections(2);
    CommManager_UnionRestartSearch();
    UnionRoomTrainers_Reset(v0->appArgs->unk_04);
    MessageLoader_Free(v0->msgLoader);
    StringTemplate_Free(v0->strTemplate);

    MixRecords_FreeState(v0);
    ApplicationManager_FreeData(appMan);

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

    UnionRoom_BroadcastActivity(0);
    SetVBlankCallback(NULL, NULL);
    Heap_Destroy(HEAP_ID_51);

    return 1;
}

static const u8 sRecordIconAnimFrames[][2] = {
    { 0x8, 0x2 },
    { 0x8, 0x3 },
    { 0x8, 0x4 },
    { 0x18, 0x0 },
    { 0x0, 0xFF }
};

static void MixRecords_VBlankTask(SysTask *sysTask, void *param1)
{
    MixRecordsComm *v0 = (MixRecordsComm *)param1;
    MixRecordsAnimation *v1 = &v0->animation;

    if (v1->active) {
        if (v1->frameTimer > sRecordIconAnimFrames[v1->frameIndex][0]) {
            u16 *v2;

            v1->frameTimer = 0;
            v1->frameIndex++;

            if (sRecordIconAnimFrames[v1->frameIndex][1] == 0xff) {
                v1->frameIndex = 0;
            }

            v2 = (u16 *)v1->paletteData->pRawData;
            GX_LoadOBJPltt(&v2[16 * sRecordIconAnimFrames[v1->frameIndex][1]], 0, 32);
        } else {
            v0->animation.frameTimer++;
        }

        MixRecords_AnimatePaletteCycle(&v0->paletteCycleAngle);
    }
}

static void MixRecords_VBlankCallback(void *param0)
{
    VramTransfer_Process();
    RenderOam_Transfer();
    Bg_RunScheduledUpdates((BgConfig *)param0);

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void MixRecords_SetGXBanks(void)
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

static void MixRecords_InitBgLayers(BgConfig *param0)
{
    GraphicsModes v0 = {
        GX_DISPMODE_GRAPHICS,
        GX_BGMODE_0,
        GX_BGMODE_0,
        GX_BG0_AS_2D,
    };

    SetAllGraphicsModes(&v0);

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

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_51);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_51);
}

static void MixRecords_InitState(MixRecordsComm *param0, NARC *param1)
{
    for (int i = 0; i < 5; i++) {
        param0->trainerNameStrings[i] = String_Init(7 + 1, HEAP_ID_51);
        param0->trainerInfo[i][0] = NULL;
        param0->trainerInfo[i][1] = NULL;
        param0->trainerIds[i][0].raw = 0;
        param0->trainerIds[i][1].raw = 0;
        param0->spriteStates[i] = 0;
    }

    param0->formattedMessage = String_Init(90 * 2, HEAP_ID_51);
    param0->headerString = String_Init(20 * 2, HEAP_ID_51);
    param0->state = 0;

    MessageLoader_GetString(param0->msgLoader, 17, param0->headerString);
    MixRecords_LoadTrainerGraphics(param0, param1);

    param0->paletteBuffer = Appearance_LoadTrainerPalette(HEAP_ID_51);
    param0->animation.active = 0;
    param0->animation.frameTimer = 0;
    param0->animation.frameIndex = 0;
    param0->animation.paletteBuffer = Graphics_GetPlttDataFromOpenNARC(param1, 1, &param0->animation.paletteData, HEAP_ID_51);
    param0->prevConnectedCount = 0;
    param0->yesNoMenu = NULL;
    param0->expectedPlayerCount = 2;
}

static void MixRecords_FreeState(MixRecordsComm *param0)
{
    MixRecords_FreeTrainerGraphics(param0);

    Heap_Free(param0->animation.paletteBuffer);
    Heap_Free(param0->paletteBuffer);

    for (int i = 0; i < 5; i++) {
        String_Free(param0->trainerNameStrings[i]);
    }

    String_Free(param0->headerString);
    String_Free(param0->formattedMessage);
}

static void MixRecords_FreeBgLayers(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
    Heap_Free(param0);
}

static void MixRecords_LoadGraphics(MixRecordsComm *param0, NARC *param1)
{
    BgConfig *bgConfig = param0->bgConfig;

    Graphics_LoadPaletteFromOpenNARC(param1, 0, 0, 0, 16 * 16 * 2, HEAP_ID_51);
    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__POKETCH, 12, 4, 0, 16 * 2, HEAP_ID_51);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_51);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(13), HEAP_ID_51);
    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 10, bgConfig, 6, 0, 0, 1, HEAP_ID_51);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_GRAPHIC__POKETCH, 11, bgConfig, 6, 0, 0, 1, HEAP_ID_51);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 2, bgConfig, 1, 0, 32 * 8 * 0x20, 1, HEAP_ID_51);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 3, bgConfig, 1, 0, 32 * 24 * 2, 1, HEAP_ID_51);
    LoadMessageBoxGraphics(bgConfig, BG_LAYER_MAIN_0, 1, 10, Options_Frame(param0->appArgs->options), HEAP_ID_51);
    LoadStandardWindowGraphics(bgConfig, BG_LAYER_MAIN_0, 1 + (18 + 12), 11, 0, HEAP_ID_51);
}

static void MixRecords_InitTransfers(void)
{
    CharTransferTemplate v0 = {
        20, 2048, 2048, HEAP_ID_51
    };

    CharTransfer_Init(&v0);

    PlttTransfer_Init(20, HEAP_ID_51);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
}

static void MixRecords_InitSprites(MixRecordsComm *param0, NARC *param1)
{
    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 32, 0, 126, 0, 32, 51);

    param0->spriteList = SpriteList_InitRendering(30, &param0->g2dRenderer, HEAP_ID_51);

    SetSubScreenViewRect(&param0->g2dRenderer, 0, 256 * FX32_ONE);

    for (int i = 0; i < 4; i++) {
        param0->spriteResourceCollections[i] = SpriteResourceCollection_New(3, i, HEAP_ID_51);
    }

    param0->spriteResources[2][0] = SpriteResourceCollection_AddTilesFrom(param0->spriteResourceCollections[0], param1, 12, 1, 2, NNS_G2D_VRAM_TYPE_2DMAIN, HEAP_ID_51);
    param0->spriteResources[2][1] = SpriteResourceCollection_AddPaletteFrom(param0->spriteResourceCollections[1], param1, 1, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, 15, HEAP_ID_51);
    param0->spriteResources[2][2] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[2], param1, 13, 1, 2, 2, HEAP_ID_51);
    param0->spriteResources[2][3] = SpriteResourceCollection_AddFrom(param0->spriteResourceCollections[3], param1, 14, 1, 2, 3, HEAP_ID_51);

    SpriteTransfer_RequestChar(param0->spriteResources[2][0]);
    SpriteTransfer_RequestPlttWholeRange(param0->spriteResources[2][1]);
}

static const u16 sSpritePositions[][2] = {
    { 0xCC, 0x54 },
    { 0xCC, 0x35 },
    { 0xE9, 0x48 },
    { 0xDF, 0x67 },
    { 0xB8, 0x67 },
    { 0xAE, 0x48 }
};

static void MixRecords_CreateSprites(MixRecordsComm *param0)
{

    SpriteResourcesHeader_Init(&param0->spriteHeader, 2, 2, 2, 2, 0xffffffff, 0xffffffff, 0, 1, param0->spriteResourceCollections[0], param0->spriteResourceCollections[1], param0->spriteResourceCollections[2], param0->spriteResourceCollections[3], NULL, NULL);

    {
        AffineSpriteListTemplate v1;

        v1.list = param0->spriteList;
        v1.resourceData = &param0->spriteHeader;
        v1.position.z = 0;
        v1.affineScale.x = FX32_ONE;
        v1.affineScale.y = FX32_ONE;
        v1.affineScale.z = FX32_ONE;
        v1.affineZRotation = 0;
        v1.priority = 1;
        v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
        v1.heapID = HEAP_ID_51;
        v1.position.x = FX32_ONE * sSpritePositions[0][0];
        v1.position.y = FX32_ONE * sSpritePositions[0][1];

        param0->sprites[0] = SpriteList_AddAffine(&v1);

        Sprite_SetAnimateFlag(param0->sprites[0], 1);
        Sprite_SetDrawFlag(param0->sprites[0], TRUE);

        for (int i = 0; i < 5; i++) {
            v1.position.x = FX32_ONE * sSpritePositions[i + 1][0];
            v1.position.y = FX32_ONE * sSpritePositions[i + 1][1];

            param0->sprites[i + 1] = SpriteList_AddAffine(&v1);

            Sprite_SetAnimateFlag(param0->sprites[i + 1], 1);
            Sprite_SetAnim(param0->sprites[i + 1], 27 + (i - 1) * 2);
            Sprite_SetDrawFlag(param0->sprites[i + 1], FALSE);
        }

        for (int i = 0; i < 5; i++) {
            v1.position.x = FX32_ONE * 24;
            v1.position.y = FX32_ONE * (32 + 32 * i) + (256 * FX32_ONE);
        }
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void MixRecords_CreateWindows(MixRecordsComm *param0, ApplicationManager *appMan)
{
    Window_Add(param0->bgConfig, &param0->unk_35C, 5, 26, 20, 6, 2, 13, 1 + 30 * 15);
    Window_FillTilemap(&param0->unk_35C, 0x0);
    Window_Add(param0->bgConfig, &param0->messageWindow, 0, 2, 19, 27, 4, 13, 1 + (18 + 12) + 9);
    Window_FillTilemap(&param0->messageWindow, 0xf0f);
    Window_Add(param0->bgConfig, &param0->headerWindow, 0, 3, 1, 26, 2, 15, (1 + (18 + 12) + 9) + 27 * 4);

    MixRecords_DrawHeader(&param0->headerWindow, param0->headerString, TEXT_SPEED_INSTANT);

    {
        Window_Add(param0->bgConfig, &param0->playerWindows[0], 0, 2, 6, 16, 11, 15, ((1 + (18 + 12) + 9) + 27 * 4) + 26 * 2);
        Window_FillTilemap(&param0->playerWindows[0], 0);

        MixRecords_DrawPlayerList(param0->playerWindows, 0, TEXT_COLOR(1, 3, 0), param0);
    }
}

static void MixRecords_DrawHeader(Window *param0, String *param1, int param2)
{
    int v0 = Font_CalcStringWidth(FONT_MESSAGE, param1, 0);
    int v1 = (26 * 8 - v0) / 2;

    Window_FillTilemap(param0, 0x0);
    Text_AddPrinterWithParamsAndColor(param0, FONT_MESSAGE, param1, v1, 1, param2, TEXT_COLOR(1, 4, 0), NULL);
}

static void MixRecords_RemoveWindows(MixRecordsComm *param0)
{
    Window_Remove(&param0->playerWindows[0]);
    Window_Remove(&param0->headerWindow);
    Window_Remove(&param0->unk_35C);
    Window_Remove(&param0->messageWindow);
}

static int MixRecords_StateWaitForPlayers(MixRecordsComm *param0, int param1)
{
    CommManager_SetErrorHandling(0, 1);

    if (CommSys_CurNetId() == 0) {
        if (CommSys_ConnectedCount() >= 2) {
            MixRecords_ShowMessage(param0, 2, 0);
        }
    } else {
        MixRecords_ShowMessage(param0, 8, 0);
    }

    MixRecords_SetNextState(param0, 3);

    return param1;
}

static int MixRecords_StateHandleInput(MixRecordsComm *param0, int param1)
{
    MixRecords_HandleInput(param0);

    if (CommSys_CurNetId() == 0) {
        if (MixRecords_CountConnectedTrainers() != 1) {
            MixRecords_NoOpUnused(param0);
        }
    } else {
        MixRecords_NoOpUnused(param0);
    }

    return param1;
}

static void MixRecords_HandleInput(MixRecordsComm *param0)
{
    if (gSystem.pressedKeys & PAD_BUTTON_A) {
        if (CommSys_CurNetId() == 0) {
            if ((MixRecords_CountConnectedPlayers() == param0->expectedPlayerCount) && (param0->confirmedBitmap == 0)) {
                u8 v0 = 1;

                MixRecords_ShowMessage(param0, 3, 0);
                MixRecords_SetNextState(param0, 22);

                CommSys_SendData(117, &v0, 1);

                MixRecords_SetMaxConnections(param0, 0);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        }
    } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
        if (CommSys_CurNetId()) {
            if (param0->confirmFlag == 0) {
                MixRecords_ShowMessage(param0, 4, 0);
                MixRecords_SetNextState(param0, 4);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        } else {
            if ((CommSys_ConnectedCount() == param0->expectedPlayerCount) && (param0->confirmedBitmap == 0)) {
                u8 v1 = 1;

                MixRecords_ShowMessage(param0, 4, 0);
                MixRecords_SetNextState(param0, 4);
                CommSys_SendData(117, &v1, 1);
                MixRecords_SetMaxConnections(param0, 0);
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }
        }
    } else {
        if (param0->playerCountExceeded == 0) {
            if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() == param0->expectedPlayerCount)) {
                u8 v2 = 0;

                CommSys_SendData(117, &v2, 1);
            }
        }
    }
}

static void MixRecords_NoOp(MixRecordsComm *unused)
{
}

static int MixRecords_StateStart(MixRecordsComm *param0, int param1)
{
    MixRecords_SetNextState(param0, 2);
    MixRecords_NoOp(param0);

    return param1;
}

static void MixRecords_SetNextState(MixRecordsComm *param0, int param1)
{
    param0->state = 30;
    param0->nextState = param1;
}

static int MixRecords_StateWaitMessage(MixRecordsComm *param0, int param1)
{
    if (MixRecords_IsMessageDone(param0->textPrinterID)) {
        param0->state = param0->nextState;
    }

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateResetConfirm(MixRecordsComm *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        int v0 = 0;

        CommSys_SendData(117, &v0, 1);
    }

    param0->state = 3;
    MixRecords_NoOp(param0);

    return param1;
}

static const WindowTemplate sYesNoMenuTemplate = {
    0x0,
    0x17,
    0xD,
    0x7,
    0x4,
    0xD,
    0x178
};

static int MixRecords_StateCreateYesNoMenu(MixRecordsComm *param0, int param1)
{
    param0->yesNoMenu = Menu_MakeYesNoChoice(param0->bgConfig, &sYesNoMenuTemplate, 1 + (18 + 12), 11, 51);
    param0->state = 5;

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateProcessYesNo(MixRecordsComm *param0, int param1)
{
    if (CommSys_CurNetId()) {
        if (param0->confirmFlag) {
            if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }

            MixRecords_NoOp(param0);
            return param1;
        }
    } else {
        if (param0->confirmedBitmap != 0) {
            if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
            }

            MixRecords_NoOp(param0);
            return param1;
        }
    }

    if (MixRecords_CountConnectedPlayers() != CommSys_ConnectedCount()) {
        MixRecords_NoOp(param0);
        return param1;
    }

    u32 v1 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, 51);

    if (v1 != 0xffffffff) {
        if (v1 == 0xfffffffe) {
            if (CommSys_CurNetId() == 0) {
                int v2 = 0;

                CommSys_SendData(117, &v2, 1);
                MixRecords_SetMaxConnections(param0, 1);
            }

            MixRecords_SetNextState(param0, 0);
        } else {
            if (CommSys_CurNetId() == 0) {
                MixRecords_SetNextState(param0, 11);
                MixRecords_ShowMessage(param0, 14, 0);
            } else {
                MixRecordsConnectionConfirm v3;

                MI_CpuClear8(&v3, sizeof(MixRecordsConnectionConfirm));

                v3.type = 0;
                v3.netId = CommSys_CurNetId();

                param0->confirmPending = 1;
                param0->retryTimer = 0;
                param0->state = 6;

                CommSys_SendData(112, &v3, sizeof(MixRecordsConnectionConfirm));
            }
        }

        param0->yesNoMenu = NULL;
    }

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateResetRetryTimer(MixRecordsComm *param0, int param1)
{
    param0->retryTimer = 0;
    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateWaitConnectionConfirm(MixRecordsComm *param0, int param1)
{
    if ((param0->serverPlayerCount != CommSys_ConnectedCount()) || (param0->serverPlayerCount != MixRecords_CountConnectedPlayers())) {
        param0->retryTimer = 0;
        param0->state = 8;
        MixRecords_NoOp(param0);
        return param1;
    }

    param0->retryTimer++;

    if (param0->retryTimer > 30) {
        MixRecordsConnectionConfirm v0;

        MI_CpuClear8(&v0, sizeof(MixRecordsConnectionConfirm));

        v0.type = 1;
        v0.netId = CommSys_CurNetId();

        CommSys_SendData(112, &v0, sizeof(MixRecordsConnectionConfirm));

        param0->retryTimer = 0;
        param0->state = 9;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateConfirmRejected(MixRecordsComm *param0, int param1)
{
    param0->confirmPending = 0;

    MixRecords_SetNextState(param0, 0);
    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateCreateRecordMenu(MixRecordsComm *param0, int param1)
{
    param0->yesNoMenu = Menu_MakeYesNoChoice(param0->bgConfig, &sYesNoMenuTemplate, 1 + (18 + 12), 11, 51);
    param0->state = 23;

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateProcessRecordMenu(MixRecordsComm *param0, int param1)
{
    if ((MixRecords_CountConnectedPlayers() != param0->expectedPlayerCount) || (param0->confirmedBitmap != 0)) {
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
            Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
        }

        MixRecords_NoOp(param0);
        return param1;
    }

    u32 v1 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, 51);

    if (v1 != 0xffffffff) {
        if (v1 == 0xfffffffe) {
            int v2 = 0;

            CommSys_SendData(117, &v2, 1);
            MixRecords_SetMaxConnections(param0, 1);
            MixRecords_SetNextState(param0, 0);
        } else {
            if (CommSys_CurNetId() == 0) {
                param0->state = 24;
                param0->recordPlayerCount = MixRecords_CountConnectedPlayers();
            } else {
                GF_ASSERT(FALSE);
            }
        }

        param0->yesNoMenu = NULL;
    }

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateSendDisconnect(MixRecordsComm *param0, int param1)
{
    if (param0->disconnectSent == 0) {
        if (CommSys_SendData(115, NULL, 0) == 1) {
            param0->disconnectSent = 1;
        }
    }

    return param1;
}

void MixRecords_ShowDisconnectMessage(MixRecordsComm *param0)
{
    MessageLoader_GetString(param0->msgLoader, 18, param0->headerString);
    MixRecords_DrawHeader(&param0->headerWindow, param0->headerString, TEXT_SPEED_INSTANT);
    Sprite_SetAnim(param0->sprites[0], 37);

    param0->animation.active = 1;
}

static int MixRecords_StateWaitReceivedRecords(MixRecordsComm *param0, int param1)
{
    if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() != param0->recordPlayerCount)) {
        (void)0;
    }

    if (CommSys_ConnectedCount() == param0->receivedRecordCount) {
        param0->state = 26;

        for (int i = 0; i < 5; i++) {
            (void)0;
        }
    }

    return param1;
}

static int MixRecords_StateApplyRecords(MixRecordsComm *param0, int param1)
{
    MixRecords_ApplyReceivedRecords(param0->saveData, param0->receivedRecords);

    param0->state = 27;

    return param1;
}

static int MixRecords_StateSaveRecords(MixRecordsComm *param0, int param1)
{
    gSystem.inhibitReset = 1;

    void *journalEntryOnlineEvent = JournalEntry_CreateEventMixedRecords(51);

    JournalEntry_SaveData(param0->appArgs->journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
    GameRecords_IncrementTrainerScore(param0->appArgs->records, TRAINER_SCORE_EVENT_UNK_20);
    CommSyncSave_Reset(&param0->syncSaveState);

    param0->state = 28;
    return param1;
}

static int MixRecords_StateWaitSaveSync(MixRecordsComm *param0, int param1)
{
    if ((CommSys_CurNetId() == 0) && (CommSys_ConnectedCount() != param0->recordPlayerCount)) {
        (void)0;
    }

    if (CommSyncSave_Update(param0->appArgs->saveData, 2, &param0->syncSaveState)) {
        Sound_StopEffect(1624, 8);
        MixRecords_ShowMessage(param0, 13, 0);
        MixRecords_SetNextState(param0, 29);
        Sprite_SetAnim(param0->sprites[0], 0);

        param0->animation.active = 0;
        param0->timer = 0;
        gSystem.inhibitReset = 0;
        param0->disconnected = 0;
    }

    return param1;
}

static int MixRecords_StateWaitAfterSave(MixRecordsComm *param0, const int param1)
{
    if (param0->timer++ > 60) {
        param0->state = 15;
    }

    return param1;
}

static int MixRecords_StateShowCancelled(MixRecordsComm *param0, const int param1)
{
    MixRecords_ShowMessage(param0, 5, 0);
    MixRecords_SetNextState(param0, 10);
    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateFadeOut(MixRecordsComm *param0, int param1)
{
    if (++param0->timer > 60) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_51);
        param1 = 3;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateCreateCancelMenu(MixRecordsComm *param0, int param1)
{
    param0->yesNoMenu = Menu_MakeYesNoChoice(param0->bgConfig, &sYesNoMenuTemplate, 1 + (18 + 12), 11, 51);
    param0->state = 12;

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateProcessCancelMenu(MixRecordsComm *param0, int param1)
{
    if ((param0->expectedPlayerCount != MixRecords_CountConnectedPlayers()) || (param0->confirmedBitmap != 0)) {
        if (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_KEY_UP | PAD_KEY_DOWN)) {
            Sound_PlayEffect(SEQ_SE_DP_CUSTOM06_sseq);
        }

        MixRecords_NoOp(param0);
        return param1;
    }

    int v0 = Menu_ProcessInputAndHandleExit(param0->yesNoMenu, 51);

    if (v0 != 0xffffffff) {
        if (v0 == 0xfffffffe) {
            int v1 = 0;

            param0->state = 0;

            CommSys_SendData(117, &v1, 1);
            MixRecords_SetMaxConnections(param0, 1);
        } else {
            param0->state = 13;
            CommSys_SendData(113, NULL, 0);
            StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(0));
        }

        param0->yesNoMenu = NULL;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateShowMixing(MixRecordsComm *param0, int param1)
{
    if (CommSys_CurNetId() == 0) {
        MixRecords_ShowMessage(param0, 5, 0);
    } else {
        StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(0));
        MixRecords_ShowMessage(param0, 16, 0);
    }

    MixRecords_SetNextState(param0, 14);
    param0->timer = 0;

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateWaitMixing(MixRecordsComm *param0, int param1)
{
    param0->timer++;

    if (param0->timer > 45) {
        param0->state = 15;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateStartSync(MixRecordsComm *param0, int param1)
{
    CommTiming_StartSync(201);
    param0->state = 16;
    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateWaitSync(MixRecordsComm *param0, int param1)
{
    if (CommTiming_IsSyncState(201)) {
        CommManager_SetErrorHandling(0, 0);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_CIRCLE_OUT, FADE_TYPE_CIRCLE_OUT, COLOR_BLACK, 16, 1, HEAP_ID_51);

        param1 = 3;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateShowPlayerLeft(MixRecordsComm *param0, int param1)
{
    if (MixRecords_IsMessageDone(param0->textPrinterID)) {
        MixRecords_ShowMessage(param0, 9, 0);
    }

    param0->state = 18;
    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateWaitPlayerLeft(MixRecordsComm *param0, int param1)
{
    if (MixRecords_IsMessageDone(param0->textPrinterID)) {
        param0->state = 10;
    }

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateWaitRecords(MixRecordsComm *param0, int param1)
{
    if ((param0->textPrinterID != 0xff) && (MixRecords_IsMessageDone(param0->textPrinterID) == 0)) {
        Text_RemovePrinter(param0->textPrinterID);
    }

    MixRecords_ShowMessage(param0, 15, 1);
    param0->state = 20;

    if (CommSys_CurNetId() == 0) {
        MixRecords_SetMaxConnections(param0, 0);
    }

    param0->connectedCountSnapshot = CommSys_ConnectedCount();
    param0->timeoutTimer = (10 * 30);

    MixRecords_NoOp(param0);

    return param1;
}

static int MixRecords_StateCheckConnection(MixRecordsComm *param0, int param1)
{
    if ((param0->connectedCountSnapshot != 0) && (CommSys_ConnectedCount() != param0->connectedCountSnapshot)) {
        param0->connectedCountSnapshot = 0;
    }

    param0->state = 21;
    param0->timer = 0;

    MixRecords_NoOp(param0);
    return param1;
}

static int MixRecords_StateWaitRecordsDone(MixRecordsComm *param0, int param1)
{
    if ((param0->connectedCountSnapshot != 0) && (CommSys_ConnectedCount() != param0->connectedCountSnapshot)) {
        param0->connectedCountSnapshot = 0;
    }

    param0->timeoutTimer--;

    if (param0->timeoutTimer < 0) {
        param0->connectedCountSnapshot = 0;
    }

    if ((++param0->timer > 60) && (param0->connectedCountSnapshot == 0)) {
        param0->state = 0;

        if (CommSys_CurNetId() == 0) {
            MixRecords_SetMaxConnections(param0, 1);
        }
    }

    MixRecords_NoOp(param0);
    return param1;
}

void MixRecords_HandleCommState(MixRecordsComm *param0, int param1, u8 param2)
{
    switch (param1) {
    case 2:
        MixRecords_EraseMessageBox(param0);
        break;
    case 13:
        if (param0->yesNoMenu != NULL) {
            Menu_DestroyForExit(param0->yesNoMenu, 51);
            param0->yesNoMenu = NULL;
        }
        break;
    case 25:
        if (MixRecords_IsMessageDone(param0->textPrinterID) == 0) {
            Text_RemovePrinter(param0->textPrinterID);
        }

        MixRecords_ShowMessage(param0, 12, 0);

        if (param0->yesNoMenu != NULL) {
            Menu_DestroyForExit(param0->yesNoMenu, 51);
            param0->yesNoMenu = NULL;
        }
        break;
    case 19:
        if (param0->confirmPending == 1) {
            return;
        }

        StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(param2));

        if (param2 == CommSys_CurNetId()) {
            return;
        }

        if (param0->yesNoMenu != NULL) {
            Menu_DestroyForExit(param0->yesNoMenu, 51);
            param0->yesNoMenu = NULL;
        }

        if (CommSys_CurNetId() == 0) {
            param0->confirmedBitmap &= 0xffff ^ param2;
        }

        break;
    case 7:
        break;
    case 8:
        break;
    default:
        GF_ASSERT("FALSE");
        return;
    }

    param0->state = param1;
}

void MixRecords_HandlePlayerReady(MixRecordsComm *param0, int param1, u8 param2)
{
    if (param0->state == 3) {
        switch (param1) {
        case 1:
            StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(param2));
            MixRecords_SetMaxConnections(param0, 1);

            param0->state = param1;
            param0->expectedPlayerCount = CommSys_ConnectedCount();
            param0->confirmedBitmap = 0;

            if (CommSys_CurNetId() == 0) {
                int v0 = 1;
                CommSys_SendData(117, &v0, 1);
            }
            break;
        case 19:
            StringTemplate_SetPlayerName(param0->strTemplate, 0, CommInfo_TrainerInfo(param2));

            if (param2 == CommSys_CurNetId()) {
                return;
            }

            if (CommSys_CurNetId() == 0) {
                param0->confirmedBitmap &= 0xffff ^ param2;
            }

            param0->state = param1;
            break;
        default:
            GF_ASSERT(FALSE);
        }
    } else if (param1 == 1) {
        param0->confirmedBitmap = 0;
        param0->expectedPlayerCount = CommSys_ConnectedCount();
    }
}

static void MixRecords_AnimatePaletteCycle(u16 *param0)
{
    *param0 += 10;

    if (*param0 > 360) {
        *param0 = 0;
    }

    fx32 v0 = CalcSineDegrees_Wraparound(*param0);
    int v3 = 15 + (v0 * 10) / FX32_ONE;
    GXRgb v1 = GX_RGB(29, v3, 0);

    GX_LoadOBJPltt((u16 *)&v1, 5 * 2, 2);
    GX_LoadOBJPltt((u16 *)&v1, (5 + 16) * 2, 2);
}

static int MixRecords_CountConnectedTrainers(void)
{
    int i, v1 = 0;

    for (i = 0; i < 5; i++) {
        TrainerInfo *trainerInfo = CommInfo_TrainerInfo(i);

        if (trainerInfo != NULL) {
            v1++;
        }
    }

    return v1;
}

static BOOL MixRecords_DrawPlayerList(Window *param0, int unused, u32 param2, MixRecordsComm *param3)
{
    int i;
    const int v1 = CommSys_CurNetId();
    String *v2 = NULL;

    if (!MixRecords_UpdateTrainerInfo(param3)) {
        return 0;
    }

    Window_FillTilemap(&param0[0], 0x0);

    for (i = 0; i < 5; i++) {
        if (param3->trainerInfo[i][0] != NULL) {
            u16 v3 = TrainerInfo_ID_LowHalf(param3->trainerInfo[i][0]);

            TrainerInfo_NameString(param3->trainerInfo[i][0], param3->trainerNameStrings[i]);
            StringTemplate_SetNumber(param3->strTemplate, 0, v3, 5, 2, 1);

            v2 = MessageUtil_ExpandedString(param3->strTemplate, param3->msgLoader, 1, HEAP_ID_51);

            if (v1 == i) {
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, param3->trainerNameStrings[i], 5, 1 + i * 18, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 3, 0), NULL);
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, v2, 5 + 13 * 5, 1 + i * 18, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(2, 3, 0), NULL);
            } else {
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, param3->trainerNameStrings[i], 5, 1 + i * 18, TEXT_SPEED_NO_TRANSFER, param2, NULL);
                Text_AddPrinterWithParamsAndColor(&param0[0], FONT_SYSTEM, v2, 5 + 13 * 5, 1 + i * 18, TEXT_SPEED_NO_TRANSFER, param2, NULL);
            }

            String_Free(v2);
        }
    }

    Window_CopyToVRAM(&param0[0]);

    return 1;
}

static void MixRecords_NoOpUnused(MixRecordsComm *unused)
{
}

static int MixRecords_CountConnectedPlayers(void)
{
    int v0, v1;

    for (v1 = 0, v0 = 0; v0 < 5; v0++) {
        if (CommInfo_TrainerInfo(v0) != NULL) {
            v1++;
        }
    }

    return v1;
}

int MixRecords_GetConnectedPlayerCount(void)
{
    return MixRecords_CountConnectedPlayers();
}

static BOOL MixRecords_UpdateTrainerInfo(MixRecordsComm *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        param0->trainerInfo[v0][1] = param0->trainerInfo[v0][0];
        param0->trainerInfo[v0][0] = CommInfo_TrainerInfo(v0);
        param0->trainerIds[v0][1] = param0->trainerIds[v0][0];

        if (param0->trainerInfo[v0][0] != NULL) {
            param0->trainerIds[v0][0].parts.trainerId = TrainerInfo_ID(param0->trainerInfo[v0][0]);
            param0->trainerIds[v0][0].parts.valid = 1;
        } else {
            param0->trainerIds[v0][0].raw = 0;
        }
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->trainerInfo[v0][1] != param0->trainerInfo[v0][0]) {
            v1 = 1;

            if (param0->trainerInfo[v0][0] == NULL) {
                param0->spriteStates[v0] = 3;
            } else {
                param0->spriteStates[v0] = 1;
            }
        } else {
            if (param0->trainerIds[v0][0].raw != param0->trainerIds[v0][1].raw) {
                v1 = 1;

                if (param0->trainerIds[v0][0].parts.valid == 0) {
                    param0->spriteStates[v0] = 3;
                } else {
                    param0->spriteStates[v0] = 1;
                }
            }
        }
    }

    return v1;
}

static void MixRecords_ShowMessage(MixRecordsComm *param0, int param1, int param2)
{
    String *v0 = String_Init(90 * 2, HEAP_ID_51);

    MessageLoader_GetString(param0->msgLoader, param1, v0);
    StringTemplate_Format(param0->strTemplate, param0->formattedMessage, v0);
    String_Free(v0);
    Window_FillTilemap(&param0->messageWindow, 0xf0f);
    Window_DrawMessageBoxWithScrollCursor(&param0->messageWindow, 0, 1, 10);

    if (param2 == 0) {
        param0->textPrinterID = Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->formattedMessage, 0, 0, MixRecords_GetMessageTextSpeed(param0), NULL);
    } else {
        Text_AddPrinterWithParams(&param0->messageWindow, FONT_MESSAGE, param0->formattedMessage, 0, 0, TEXT_SPEED_INSTANT, NULL);
        param0->textPrinterID = 0xff;
    }
}

static int MixRecords_IsMessageDone(int param0)
{
    if (param0 == 0xff) {
        return 1;
    }

    if (Text_IsPrinterActive(param0) == 0) {
        return 1;
    }

    return 0;
}

static void MixRecords_EraseMessageBox(MixRecordsComm *param0)
{
    Window_EraseMessageBox(&param0->messageWindow, 0);
}

static void MixRecords_UpdateSprites(MixRecordsComm *param0)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 5; v0++) {
        switch (param0->spriteStates[v0]) {
        case 0:
            break;
        case 1: {
            int v2, v3;

            GF_ASSERT(param0->trainerInfo[v0][0] != NULL);

            v3 = TrainerInfo_Gender(param0->trainerInfo[v0][0]);
            v2 = TrainerInfo_Appearance(param0->trainerInfo[v0][0]);

            if (CommSys_CurNetId() == v0) {
                Sprite_SetAnim(param0->sprites[v0 + 1], 38 + v3 * 2);
            } else {
                MixRecords_LoadTrainerSprite(param0->charData, param0->plttData, v0, v2, v3);
                Sprite_SetAnim(param0->sprites[v0 + 1], 27 + v0 * 2);
            }
        }
            Sprite_SetDrawFlag(param0->sprites[v0 + 1], TRUE);
            param0->spriteStates[v0] = 2;
            v1 = 1;
            break;
        case 2:
            break;
        case 3:
            if (CommSys_CurNetId() == v0) {
                int v4 = TrainerInfo_Gender(param0->trainerInfo[v0][0]);
                Sprite_SetAnim(param0->sprites[v0 + 1], 38 + v4 * 2 + 1);
            } else {
                Sprite_SetAnim(param0->sprites[v0 + 1], 27 + v0 * 2 + 1);
            }

            param0->spriteStates[v0] = 0;
            break;
        }
    }

    if (v1) {
        Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
    }
}

static void MixRecords_LoadTrainerGraphics(MixRecordsComm *param0, NARC *param1)
{
    param0->plttDataBuffers[0] = Graphics_GetPlttData(NARC_INDEX_GRAPHIC__WORLDTRADE, 8, &(param0->plttData[0]), HEAP_ID_51);
    param0->plttDataBuffers[1] = Graphics_GetPlttDataFromOpenNARC(param1, 7, &(param0->plttData[1]), HEAP_ID_51);
    param0->charDataBuffers[0] = Graphics_GetCharData(NARC_INDEX_GRAPHIC__WORLDTRADE, 32, 1, &(param0->charData[0]), HEAP_ID_51);
    param0->charDataBuffers[1] = Graphics_GetCharDataFromOpenNARC(param1, 9, 1, &(param0->charData[1]), HEAP_ID_51);
}

static const u16 sTrainerSpriteObjOffsets[] = {
    0x1A0,
    0x7A0,
    0xDA0,
    0x13A0,
    0x19A0
};

static void MixRecords_LoadTrainerSprite(NNSG2dCharacterData *param0[2], NNSG2dPaletteData *param1[2], int param2, int param3, int param4)
{
    int v0;
    u8 *v1, *v2;

    v0 = Appearance_GetIndex(param4, param3);

    v1 = (u8 *)param0[1]->pRawData;
    v2 = (u8 *)param1[1]->pRawData;

    GX_LoadOBJ(&v1[(3 * 4 * 4) * v0 * 0x20], sTrainerSpriteObjOffsets[param2], (3 * 4 * 4) * 0x20);
    GX_LoadOBJPltt(&v2[v0 * 32], (param2 + 7) * 32, 32);
}

static void MixRecords_FreeTrainerGraphics(MixRecordsComm *param0)
{
    Heap_Free(param0->plttDataBuffers[0]);
    Heap_Free(param0->plttDataBuffers[1]);

    Heap_Free(param0->charDataBuffers[0]);
    Heap_Free(param0->charDataBuffers[1]);
}

static int MixRecords_GetMessageTextSpeed(MixRecordsComm *param0)
{
    return 1;
}

static void MixRecords_SetMaxConnections(MixRecordsComm *param0, int param1)
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
            param0->maxConnectionsMode = 2;
        } else if (param1 == 0) {
            param0->maxConnectionsMode = 1;
        } else {
            param0->maxConnectionsMode = 0;
        }
    }
}

static int MixRecords_UpdateConnectionState(MixRecordsComm *param0, int param1)
{
    int v0 = MixRecords_CountConnectedPlayers();

    if (v0 > param0->expectedPlayerCount) {
        u8 v1 = 1;

        CommSys_SendData(117, &v1, 1);
        param0->playerCountExceeded = 1;
    } else {
        param0->playerCountExceeded = 0;
    }

    if (v0 == param0->prevConnectedCount) {
        return 1;
    }

    switch (v0) {
    case 1:
        if ((CommSys_ConnectedCount() > 1) || (WirelessManager_GetConnectedBitmap() > 1)) {
            return 1;
        }

        param0->state = 17;
        MixRecords_SetMaxConnections(param0, -1);

        if (param0->yesNoMenu != NULL) {
            Menu_DestroyForExit(param0->yesNoMenu, 51);
            param0->yesNoMenu = NULL;
        }

        return 2;
        break;
    case 2:
    case 3:
    case 4:
        UnionRoom_BroadcastActivity(2);

        if (v0 < param0->prevConnectedCount) {
            switch (param0->maxConnectionsMode) {
            case 0:
                MixRecords_SetMaxConnections(param0, param1);
                break;
            case 1:
                MixRecords_SetMaxConnections(param0, 0);
                break;
            }

            param0->expectedPlayerCount = CommSys_ConnectedCount();
        }
        break;
    case 5:
        UnionRoom_BroadcastActivity(9);
        MixRecords_SetMaxConnections(param0, param1);
        break;
    }

    param0->prevConnectedCount = MixRecords_CountConnectedPlayers();

    return 1;
}
