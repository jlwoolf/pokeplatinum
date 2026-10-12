
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"

#include <nitro.h>
#include <string.h>

#include "constants/graphics.h"

#include "nintendo_wfc/main.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_balloon.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_graphics.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_comm_cmd.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_comm_cmd_handlers.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_3d_object.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_model.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_sequence_state.h"

#include "bg_window.h"
#include "camera.h"
#include "comm_manager.h"
#include "communication_system.h"
#include "easy3d_object.h"
#include "enums.h"
#include "font.h"
#include "g3d_pipeline.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "palette.h"
#include "particle_system.h"
#include "render_text.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "text.h"
#include "touch_pad.h"
#include "trainer_info.h"
#include "font_oam.h"
#include "g3_buffer.h"
#include "comm_tool.h"
#include "vram_transfer.h"

static void WiFiLobbyMinigameBalloon_VBlankCallback(void *param0);
static G3DPipelineBuffers *WiFiLobbyMinigameBalloon_InitPipeline(enum HeapID heapID);
static void WiFiLobbyMinigameBalloon_Setup3D(void);
static void WiFiLobbyMinigameBalloon_FreePipeline(G3DPipelineBuffers *param0);
static void WiFiLobbyMinigameBalloon_DrawTask(SysTask *param0, void *param1);
static void WiFiLobbyMinigameBalloon_InitGraphics(BgConfig *param0);
static void WiFiLobbyMinigameBalloon_InitWindows(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_InitParticles(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_FreeParticles(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_LoadMainGraphics(WiFiLobbyMinigameBalloonGame *param0, NARC *param1);
static void WiFiLobbyMinigameBalloon_FreeMainGraphics(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_LoadSubGraphics(WiFiLobbyMinigameBalloonGame *param0, NARC *param1);
static void WiFiLobbyMinigameBalloon_FreeSubGraphics(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_LoadMainBg(WiFiLobbyMinigameBalloonGame *param0, NARC *param1);
static void WiFiLobbyMinigameBalloon_Noop1(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_LoadSubBg(WiFiLobbyMinigameBalloonGame *param0, NARC *param1);
static void WiFiLobbyMinigameBalloon_Noop2(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_Load3DModels(WiFiLobbyMinigameBalloonGame *param0, NARC *param1);
static void WiFiLobbyMinigameBalloon_Free3DModels(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_InitCameras(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_FreeCameras(WiFiLobbyMinigameBalloonGame *param0);
BOOL WiFiLobbyMinigameBalloon_IsLocalPlayer(WiFiLobbyMinigameBalloonGame *param0);
void WiFiLobbyMinigameBalloon_QueueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1, const WiFiLobbyMinigameBalloonPacket *param2);
WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1);
static BOOL WiFiLobbyMinigameBalloon_HandleImmediatePacket(WiFiLobbyMinigameBalloonGame *param0, int param1, const WiFiLobbyMinigameBalloonPacket *param2);
void WiFiLobbyMinigameBalloon_QueueSendPacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static BOOL WiFiLobbyMinigameBalloon_HandleImmediateSendPacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueSendPacket(WiFiLobbyMinigameBalloonGame *param0);
static int WiFiLobbyMinigameBalloon_SendQueuedPacket(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_ProcessReceivedPackets(WiFiLobbyMinigameBalloonGame *param0);
int WiFiLobbyMinigameBalloon_GetBalloonLevel(WiFiLobbyMinigameBalloonGame *param0);
int WiFiLobbyMinigameBalloon_FindWinner(WiFiLobbyMinigameBalloonGame *param0);
static BOOL WiFiLobbyMinigameBalloon_UpdateSync(WiFiLobbyMinigameBalloonGame *param0);
static int WiFiLobbyMinigameBalloon_CheckSync(WiFiLobbyMinigameBalloonGame *param0, int param1);
static int WiFiLobbyMinigameBalloon_IntroSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1);
static int WiFiLobbyMinigameBalloon_GameSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1);
static int WiFiLobbyMinigameBalloon_ResultsSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1);
static BOOL WiFiLobbyMinigameBalloon_UpdateSequence(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_DrawScoreWindow(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_ClearScoreWindow(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_DrawPlayerNames(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_ClearPlayerNameWindows(WiFiLobbyMinigameBalloonGame *param0, int param1);
BOOL WiFiLobbyMinigameBalloon_SpawnBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1);
void WiFiLobbyMinigameBalloon_RemoveBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2);
void WiFiLobbyMinigameBalloon_UpdateBalloonPops(WiFiLobbyMinigameBalloonGame *param0);
void WiFiLobbyMinigameBalloon_DrawBalloonPops(WiFiLobbyMinigameBalloonGame *param0);
static void WiFiLobbyMinigameBalloon_NoopCamera(Camera *camera);
static u32 WiFiLobbyMinigameBalloon_AllocTextureVram(u32 param0, BOOL param1);
static u32 WiFiLobbyMinigameBalloon_AllocPaletteVram(u32 param0, BOOL param1);

static const CameraAngle sCameraAngle = {
    0x0,
    0x0,
    0x0
};

static int (*const sSequenceTable[])(WiFiLobbyMinigameBalloonGame *, WiFiLobbyMinigameBalloonSequenceState *) = {
    WiFiLobbyMinigameBalloon_IntroSequence,
    WiFiLobbyMinigameBalloon_GameSequence,
    WiFiLobbyMinigameBalloon_ResultsSequence,
};

__attribute__((aligned(4))) static const u8 sPlayerSlotOrder[][4] = {
    { 0x0 },
    { 0x0 },
    { 0x0, 0x1 },
    { 0x0, 0x2, 0x1 },
    { 0x0, 0x3, 0x1, 0x2 }
};

__attribute__((aligned(4))) static const u8 sPlayerNameWindowIndex[][4] = {
    { 0x0 },
    { 0x0 },
    { 0x0, 0x1 },
    { 0x0, 0x3, 0x2 },
    { 0x0, 0x3, 0x1, 0x2 }
};

static const RenderOamTemplate sRenderOamTemplate = {
    0x0,
    0x80,
    0x0,
    0x20,
    0x0,
    0x80,
    0x0,
    0x20
};

static const CharTransferTemplateWithModes sCharTransferTemplate = {
    0x60,
    0x10000,
    0x4000,
    GX_OBJVRAMMODE_CHAR_1D_128K,
    GX_OBJVRAMMODE_CHAR_1D_32K
};

static const SpriteResourceCapacities sSpriteResourceCapacities = {
    0x60,
    0x20,
    0x40,
    0x40,
    0x2,
    0x2
};

static const struct {
    u32 baseModel;
    u32 popModel0;
    u32 popModel1;
    u32 popModel2;
    u32 popModel3;
} sPlayerModelFiles[] = {
    { 0x20, 0x27, 0x28, 0x29, 0x2A },
    { 0x21, 0x2F, 0x30, 0x31, 0x32 },
    { 0x22, 0x33, 0x34, 0x35, 0x36 },
    { 0x1F, 0x2B, 0x2C, 0x2D, 0x2E }
};

int WiFiLobbyMinigameBalloon_AppInit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonGame *v0;

    SetVBlankCallback(NULL, NULL);
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);
    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_ALL, 16, 16);
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG3, GX_BLEND_BGALL | GX_BLEND_PLANEMASK_OBJ, 13, 3);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameBalloonGame), HEAP_ID_110);
    MI_CpuClear8(v0, sizeof(WiFiLobbyMinigameBalloonGame));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_110, 32);

    v0->pipeline = WiFiLobbyMinigameBalloon_InitPipeline(HEAP_ID_110);
    v0->context = ApplicationManager_Args(appMan);
    WiFiLobbyMinigameBalloon_InitCommCmd(v0);
    v0->paletteData = PaletteData_New(HEAP_ID_110);

    PaletteData_SetAutoTransparent(v0->paletteData, TRUE);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_110);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 16, HEAP_ID_110);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_MAIN_OBJ, PALETTE_SIZE_BYTES * 14, HEAP_ID_110);
    PaletteData_AllocBuffer(v0->paletteData, PLTTBUF_SUB_OBJ, PALETTE_SIZE_BYTES * 16, HEAP_ID_110);

    v0->bgConfig = BgConfig_New(HEAP_ID_110);

    VramTransfer_New(64, HEAP_ID_110);
    SetAutorepeat(4, 8);
    WiFiLobbyMinigameBalloon_InitGraphics(v0->bgConfig);
    EnableTouchPad();
    InitializeTouchPad(4);
    WiFiLobbyMinigameBalloon_InitCameras(v0);

    v0->spriteSystem = SpriteSystem_Alloc(HEAP_ID_110);

    SpriteSystem_Init(v0->spriteSystem, &sRenderOamTemplate, &sCharTransferTemplate, 16 + 16);
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_64K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    v0->spriteManager = SpriteManager_New(v0->spriteSystem);

    SpriteSystem_InitSprites(v0->spriteSystem, v0->spriteManager, 96 + 128);
    SpriteSystem_InitManagerWithCapacities(v0->spriteSystem, v0->spriteManager, &sSpriteResourceCapacities);
    SetSubScreenViewRect(SpriteSystem_GetRenderer(v0->spriteSystem), 0, (192 + 160) << FX32_SHIFT);
    WiFiLobbyMinigameBalloon_InitParticles(v0);

    v0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0009, HEAP_ID_110);
    v0->stringTemplate = StringTemplate_Default(HEAP_ID_110);
    v0->scratchString = String_Init(2 * 160, HEAP_ID_110);
    v0->fontOAMManager = FontOAMManager_New(2 * 6 + 6 + 1, HEAP_ID_110);

    WiFiLobbyMinigameBalloon_InitPlayerBalloons(v0, &v0->playerBalloons);

    {
        NARC *v1;
        v1 = NARC_ctor(NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, HEAP_ID_110);

        WiFiLobbyMinigameBalloon_LoadMainBg(v0, v1);
        WiFiLobbyMinigameBalloon_LoadSubBg(v0, v1);
        WiFiLobbyMinigameBalloon_InitWindows(v0);
        WiFiLobbyMinigameBalloon_LoadMainGraphics(v0, v1);
        WiFiLobbyMinigameBalloon_LoadSubGraphics(v0, v1);
        WiFiLobbyMinigameBalloon_Load3DModels(v0, v1);
        NARC_dtor(v1);
    }

    PaletteData_LoadBufferFromFileStart(v0->paletteData, NARC_INDEX_GRAPHIC__PL_FONT, 6, HEAP_ID_110, PLTTBUF_MAIN_BG, PALETTE_SIZE_BYTES, PLTT_DEST(14));
    PaletteData_LoadBufferFromFileStart(v0->paletteData, NARC_INDEX_GRAPHIC__PL_FONT, 6, HEAP_ID_110, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES, PLTT_DEST(5));
    WiFiLobbyMinigameBalloon_DrawPlayerNames(v0);
    WiFiLobbyMinigameBalloon_ClearPlayerNameWindows(v0, 0);
    WiFiLobbyMinigameBalloon_DrawScoreWindow(v0);
    NetworkIcon_Init();

    v0->balloon = WiFiLobbyMinigameBalloonBalloon_New(v0);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_27, FADE_TYPE_UNK_27, COLOR_BLACK, 6, 1, HEAP_ID_110);
    v0->drawTask = SysTask_Start(WiFiLobbyMinigameBalloon_DrawTask, v0, 60000);

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;

    GXLayers_SwapDisplay();
    GXLayers_TurnBothDispOn();
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);

    {
        RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_ENABLED);
        RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
        RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    }

    v0->introAnimation = WiFiLobbyMinigame_CreateIntroAnimation(SpriteManager_GetSpriteList(v0->spriteManager), HEAP_ID_110);

    int v2 = WiFiLobbyMinigame_GetIntroAnimationPaletteOffset(v0->introAnimation);
    PaletteData_LoadBufferFromHardware(v0->paletteData, PLTTBUF_MAIN_OBJ, PLTT_DEST(v2), 3 * PALETTE_SIZE_BYTES);

    SetVBlankCallback(WiFiLobbyMinigameBalloon_VBlankCallback, v0);

    if (v0->context->voiceChatEnabled) {
        NintendoWFC_StartVoiceChat(HEAP_ID_110);
    }

    return 1;
}

int WiFiLobbyMinigameBalloon_AppMain(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonGame *v0 = ApplicationManager_Data(appMan);
    int v1;

    if (v0->context->disconnected == 1) {
        switch (v0->context->disconnectState) {
        case 0:
            if (IsScreenFadeDone() == TRUE) {
                FinishScreenFade();
            }

            SetColorBrightness(COLOR_BLACK);
            GX_SetVisibleWnd(GX_WNDMASK_NONE);
            v0->context->disconnectState++;
            break;

        default:
        case 1:
            if (WiFiLobbyMinigame_HandleDisconnect(&v0->context->playerContext) == 1) {
                return 1;
            }
            break;
        }

        return 0;
    }

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone() == TRUE) {
            (*param1)++;
        }
        break;
    case 1:
        CommTiming_StartSync(211);
        (*param1)++;
        break;
    case 2:
        if (CommTiming_IsSyncState(211) == 1) {
            (*param1)++;
        }
        break;
    case 3:
        if (WiFiLobbyMinigameBalloon_SendScore(v0) == 1) {
            (*param1)++;
        }
        break;
    case 4:
        if (v0->scorePacketsReceived >= v0->context->playerCount) {
            WiFiLobbyMinigameBalloon_FindWinner(v0);
            (*param1)++;
        }
        break;
    case 5:
        if (v0->readyReceived == 1) {
            WiFiLobbyMinigameBalloon_CreateScoreDigits(v0);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_26, FADE_TYPE_UNK_26, COLOR_BLACK, 6, 1, HEAP_ID_110);
            (*param1)++;
        }

        WiFiLobbyMinigameBalloon_UpdateSequence(v0);

        switch (v0->phase) {
        case 1:
            GX_SetVisibleWnd(GX_WNDMASK_W1);
            G2_SetWnd1Position(4, 192 - 32 + 8, 8 * 9 + 4, 192 - 8);
            G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_OBJ, 0);
            G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, 1);
            WiFiLobbyMinigameBalloon_FreeScoreDigits(v0);
            v0->phase = 2;
        case 2:
            if (WiFiLobbyMinigameBalloon_UpdateIntroBanner(v0, &v0->introBanner) == 1) {
                v0->introBanner.finished = 1;
                v0->phase = 0;
            }
            break;
        case 3:
            WiFiLobbyMinigame_StartIntroAnimationRoll(v0->introAnimation);
            v0->phase = 4;
            break;
        case 4:
            if (WiFiLobbyMinigame_IntroAnimationIsDone(v0->introAnimation) == 1) {
                v0->gameStarted = 1;
                v0->playerBalloons.idle = 0;
                v0->phase = 5;
                WiFiLobbyMinigameBalloon_ClearScoreWindow(v0);
                WiFiLobbyMinigameBalloon_ClearPlayerNameWindows(v0, 1);
            }
            break;
        case 6:
            WiFiLobbyMinigame_StartIntroAnimationPop(v0->introAnimation);
            v0->phase = 7;
            break;
        case 7:
            if (WiFiLobbyMinigame_IntroAnimationIsDone(v0->introAnimation) == 1) {
                v0->phase = 8;
            }
            break;
        }

        WiFiLobbyMinigameBalloon_UpdateSync(v0);
        WiFiLobbyMinigameBalloon_ProcessReceivedPackets(v0);

        if (v0->gameEnded == 1) {
            break;
        }

        if (WiFiLobbyMinigameBalloon_SendQueuedPacket(v0) == 1) {
            v0->sendCooldown = 13;
        }

        if (v0->gameTimer == (3 * 30)) {
            (void)0;
        }

        if ((v0->gameStarted == 1) && (v0->gameTimer <= (43 * 30 + 12))) {
            v0->gameTimer++;
        }
        break;
    case 6:
        if (IsScreenFadeDone() == TRUE) {
            return 1;
        }
        break;
    }

    WiFiLobbyMinigameBalloon_NoopCamera(v0->camera1);
    v0->frameCounter++;

    return 0;
}

int WiFiLobbyMinigameBalloon_AppExit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonGame *v0 = ApplicationManager_Data(appMan);
    int v1;

    v0->context->ranking.unk_14 = v0->popCount;

    WiFiLobbyMinigame_FreeIntroAnimation(v0->introAnimation);
    WiFiLobbyMinigameBalloon_FreePopEffects(v0);
    WiFiLobbyMinigameBalloon_FreeConfetti(v0);

    SetVBlankCallback(NULL, NULL);

    WiFiLobbyMinigameBalloon_FreeParticles(v0);
    WiFiLobbyMinigameBalloon_FreeMainGraphics(v0);
    WiFiLobbyMinigameBalloon_FreeSubGraphics(v0);
    WiFiLobbyMinigameBalloon_Noop1(v0);
    WiFiLobbyMinigameBalloon_Noop2(v0);
    WiFiLobbyMinigameBalloon_Free3DModels(v0);
    WiFiLobbyMinigameBalloonBalloon_Free(v0, v0->balloon);

    for (v1 = 0; v1 < 5; v1++) {
        Window_Remove(&v0->windows[v1]);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(v0->bgConfig, BG_LAYER_SUB_3);
    FontOAMManager_Free(v0->fontOAMManager);
    SpriteSystem_FreeResourcesAndManager(v0->spriteSystem, v0->spriteManager);
    SpriteSystem_Free(v0->spriteSystem);
    VramTransfer_Free();
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_MAIN_BG);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_SUB_BG);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_MAIN_OBJ);
    PaletteData_FreeBuffer(v0->paletteData, PLTTBUF_SUB_OBJ);
    PaletteData_Free(v0->paletteData);
    String_Free(v0->scratchString);
    StringTemplate_Free(v0->stringTemplate);
    MessageLoader_Free(v0->messageLoader);
    Heap_Free(v0->bgConfig);
    WiFiLobbyMinigameBalloon_FreeCameras(v0);
    SysTask_Done(v0->drawTask);

    GX_SetVisibleWnd(GX_WNDMASK_NONE);
    GXS_SetVisibleWnd(GX_WNDMASK_NONE);

    WiFiLobbyMinigameBalloon_FreePipeline(v0->pipeline);
    DisableTouchPad();
    ApplicationManager_FreeData(appMan);
    RenderControlFlags_SetCanABSpeedUpPrint(FALSE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);
    RenderControlFlags_SetSpeedUpOnTouch(FALSE);
    NetworkIcon_Destroy();

    return 1;
}

static void WiFiLobbyMinigameBalloon_VBlankCallback(void *param0)
{
    WiFiLobbyMinigameBalloonGame *v0 = param0;

    WiFiLobbyMinigameBalloonBalloon_CommitPalette(v0, v0->balloon);

    VramTransfer_Process();
    SpriteSystem_TransferOam();
    PaletteData_CommitFadedBuffers(v0->paletteData);

    if (v0->scoreGauge.showRequest == 1) {
        Bg_ToggleLayer(BG_LAYER_SUB_3, 1);
        v0->scoreGauge.showRequest = 0;
    } else if (v0->scoreGauge.hideRequest == 1) {
        Bg_ToggleLayer(BG_LAYER_SUB_3, 0);
        v0->scoreGauge.hideRequest = 0;
    }

    Bg_RunScheduledUpdates(v0->bgConfig);
    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static G3DPipelineBuffers *WiFiLobbyMinigameBalloon_InitPipeline(enum HeapID heapID)
{
    return G3DPipeline_Init(heapID, TEXTURE_VRAM_SIZE_128K, PALETTE_VRAM_SIZE_32K, WiFiLobbyMinigameBalloon_Setup3D);
}

static void WiFiLobbyMinigameBalloon_Setup3D(void)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);

    G2_SetBG0Priority(1);
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(1);
    G3X_AlphaTest(0, 0);
    G3X_AlphaBlend(1);
    G3X_EdgeMarking(0);
    G3X_SetFog(0, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0);
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 63, 0);
    G3_ViewPort(0, 0, 255, 191);
}

static void WiFiLobbyMinigameBalloon_FreePipeline(G3DPipelineBuffers *param0)
{
    G3DPipelineBuffers_Free(param0);
}

static void WiFiLobbyMinigameBalloon_InitCameras(WiFiLobbyMinigameBalloonGame *param0)
{
    VecFx32 v0 = { 0, 0x1881e, 0 };
    VecFx32 v1 = { 0, 0x1881e, (FX32_ONE * 5) };

    param0->camera1 = Camera_Alloc(HEAP_ID_110);

    Camera_InitWithTarget(&v0, 0x7b << FX32_SHIFT, &sCameraAngle, (22 * 0xffff) / 360, 1, 0, param0->camera1);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, param0->camera1);
    Camera_SetAsActive(param0->camera1);

    param0->camera2 = Camera_Alloc(HEAP_ID_110);

    Camera_InitWithTarget(&v0, 80 << FX32_SHIFT, &sCameraAngle, (22 * 0xffff) / 360, 1, 0, param0->camera2);
    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, param0->camera2);
}

static void WiFiLobbyMinigameBalloon_FreeCameras(WiFiLobbyMinigameBalloonGame *param0)
{
    Camera_Delete(param0->camera1);
    Camera_Delete(param0->camera2);
}

static void WiFiLobbyMinigameBalloon_DrawTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameBalloonGame *v0 = param1;
    VecFx32 v1, v2;
    MtxFx33 v3;

    v1.x = FX32_ONE;
    v1.y = FX32_ONE;
    v1.z = FX32_ONE;

    v2.x = 0;
    v2.y = 0;
    v2.z = 0;

    MTX_Identity33(&v3);

    WiFiLobbyMinigameBalloon_UpdateScoreDisplay(v0, &v0->scoreDisplay);
    WiFiLobbyMinigameBalloon_UpdatePlayerBalloons(v0, &v0->playerBalloons);
    WiFiLobbyMinigameBalloon_UpdateOpponentBalloons(v0, &v0->opponentBalloons);
    WiFiLobbyMinigameBalloon_UpdatePopEffects(v0);
    WiFiLobbyMinigameBalloon_DrawScoreGauge(v0, v0->bgConfig, &v0->scoreGauge);
    WiFiLobbyMinigameBalloon_UpdateConfetti(v0);
    WiFiLobbyMinigameBalloon_UpdateBalloonPops(v0);
    WiFiLobbyMinigameBalloon_UpdateRankIcons(v0);

    {
        G3_ResetG3X();
        Camera_SetAsActive(v0->camera1);
        Camera_ComputeProjectionMatrix(1, v0->camera1);
        Camera_ComputeViewMatrix();

        NNS_G3dGlbLightVector(0, 0, -FX32_ONE, 0);
        NNS_G3dGlbLightColor(0, GX_RGB(28, 28, 28));
        NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
        NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(31, 31, 31), GX_RGB(31, 31, 31), 0);
        NNS_G3dGlbSetBaseTrans(&v2);
        NNS_G3dGlbSetBaseRot(&v3);
        NNS_G3dGlbSetBaseScale(&v1);
        NNS_G3dGlbFlush();

        WiFiLobbyMinigameBalloonBalloon_Update(v0, v0->balloon);
        NNS_G3dGePushMtx();

        {
            Easy3DObject_Draw(&v0->balloon3DObject.object);
            Easy3DObject_Draw(&v0->playerModel.object);
            WiFiLobbyMinigameBalloon_DrawBalloonPops(v0);
        }

        NNS_G3dGePopMtx(1);
    }

    {
        int v4;

        G3_ResetG3X();
        v4 = ParticleSystem_DrawAll();

        if (v4 > 0) {
            G3_ResetG3X();
        }

        ParticleSystem_UpdateAll();
    }

    SpriteSystem_DrawSprites(v0->spriteManager);
    SpriteSystem_UpdateTransfer();
    G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
    CommManager_Dummy_02038A1C(110, v0->bgConfig);
}

static void WiFiLobbyMinigameBalloon_InitGraphics(BgConfig *param0)
{
    GXLayers_DisableEngineALayers();

    {
        GXBanks v0 = {
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

        GXLayers_SetBanks(&v0);

        MI_CpuClear32((void *)HW_BG_VRAM, HW_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
        MI_CpuClear32((void *)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
        MI_CpuClear32((void *)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    }

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_1,
            GX_BG0_AS_3D,
        };

        SetAllGraphicsModes(&v1);
    }

    {
        BgTemplate v2[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x04000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x2000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x512,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x1000,
                .charBase = GX_BG_CHARBASE_0x0c000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_512x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x3000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 2,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2[0], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_1, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v2[1], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_2, 3, 0);
        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v2[2], 0);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 0, 0);
        Bg_SetOffset(param0, BG_LAYER_MAIN_3, 3, 0);

        G2_SetBG0Priority(2);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    }

    {
        int v3;
        static const BgTemplate v4[] = {
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x0000,
                .charBase = GX_BG_CHARBASE_0x08000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 1,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x800,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x2000,
                .charBase = GX_BG_CHARBASE_0x10000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x1000,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_16,
                .screenBase = GX_BG_SCRBASE_0x4000,
                .charBase = GX_BG_CHARBASE_0x14000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 3,
                .areaOver = 0,
                .mosaic = FALSE,
            },
            {
                .x = 0,
                .y = 0,
                .bufferSize = 0x400,
                .baseTile = 0,
                .screenSize = BG_SCREEN_SIZE_256x256,
                .colorMode = GX_BG_COLORMODE_256,
                .screenBase = GX_BG_SCRBASE_0x6000,
                .charBase = GX_BG_CHARBASE_0x18000,
                .bgExtPltt = GX_BG_EXTPLTT_01,
                .priority = 0,
                .areaOver = 0,
                .mosaic = FALSE,
            },
        };

        for (v3 = 0; v3 < NELEMS(v4); v3++) {
            if (v3 < 3) {
                Bg_InitFromTemplate(param0, BG_LAYER_SUB_0 + v3, &v4[v3], 0);
            } else {
                Bg_InitFromTemplate(param0, BG_LAYER_SUB_0 + v3, &v4[v3], 1);
            }

            Bg_ClearTilesRange(4 + v3, 0x20, 0, HEAP_ID_110);
            Bg_ClearTilemap(param0, BG_LAYER_SUB_0 + v3);
            Bg_SetOffset(param0, BG_LAYER_SUB_0 + v3, 0, 0);
            Bg_SetOffset(param0, BG_LAYER_SUB_0 + v3, 3, 0);
        }

        Bg_ToggleLayer(BG_LAYER_SUB_3, 0);
    }
}

static void WiFiLobbyMinigameBalloon_InitWindows(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;

    Window_Add(param0->bgConfig, &param0->windows[0], 1, 11, 0x13, 20, 4, 0xe, (0x8000 - 0x2000) / 32);
    Window_Add(param0->bgConfig, &param0->windows[1], 4, 0x12, 1, 10, 2, 5, ((0x8000 - 0x2000) / 32) + (10 * 2));
    Window_Add(param0->bgConfig, &param0->windows[2], 4, 0x15, 0xe, 10, 2, 5, (((0x8000 - 0x2000) / 32) + (10 * 2)) + (10 * 2));
    Window_Add(param0->bgConfig, &param0->windows[3], 4, 1, 14, 10, 2, 5, ((((0x8000 - 0x2000) / 32) + (10 * 2)) + (10 * 2)) + (10 * 2));
    Window_FillTilemap(&param0->windows[1], 0xf);
    Window_FillTilemap(&param0->windows[2], 0xf);
    Window_FillTilemap(&param0->windows[3], 0xf);
    Window_Add(param0->bgConfig, &param0->windows[4], 4, 2, 0x13, 0x1c, 4, 5, ((((((0x8000 - 0x2000) / 32) + (10 * 2)) + (10 * 2)) + (10 * 2)) + (10 * 2)) + 9);
    Window_FillTilemap(&param0->windows[4], 0xf);
}

static void WiFiLobbyMinigameBalloon_DrawScoreWindow(WiFiLobbyMinigameBalloonGame *param0)
{
    String *v0;

    Window_DrawStandardFrame(&param0->windows[4], 1, (((((0x8000 - 0x2000) / 32) + (10 * 2)) + (10 * 2)) + (10 * 2)) + (10 * 2), 6);

    v0 = MessageLoader_GetNewString(param0->messageLoader, 3);
    Text_AddPrinterWithParamsAndColor(&param0->windows[4], FONT_SYSTEM, v0, 0, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 2, 15), NULL);
    String_Free(v0);

    Window_ScheduleCopyToVRAM(&param0->windows[4]);
}

static void WiFiLobbyMinigameBalloon_ClearScoreWindow(WiFiLobbyMinigameBalloonGame *param0)
{
    Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 2 - 1, 0x13 - 1, 0x1c + 2, 4 + 2, 17);
    Bg_ScheduleTilemapTransfer(param0->bgConfig, 4);
}

static void WiFiLobbyMinigameBalloon_DrawPlayerNames(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0, v1;
    TrainerInfo *v2;
    String *v3;
    int v4;
    TextColor v5;
    int v6, v7;

    v4 = CommSys_CurNetId();

    for (v0 = 0; v0 < param0->context->playerCount; v0++) {
        if (v4 != param0->context->netIds[v0]) {
            v2 = WiFiLobbyMinigame_GetTrainerInfo(&param0->context->playerContext, param0->context->netIds[v0]);
            v3 = TrainerInfo_NameNewString(v2, HEAP_ID_110);
            v1 = WiFiLobbyMinigameBalloon_GetPlayerSlot(param0, param0->context->netIds[v0]);

            if (WiFiLobbyMinigame_IsPlayerReady(&param0->context->playerContext, param0->context->netIds[v0]) == 1) {
                v5 = TEXT_COLOR(7, 8, 15);
            } else {
                v5 = TEXT_COLOR(1, 2, 15);
            }

            v6 = Font_CalcStringWidth(FONT_SYSTEM, v3, 0);
            v7 = 8 * 10 / 2 - v6 / 2;

            if (v6 & 1) {
                v7--;
            }

            Text_AddPrinterWithParamsAndColor(&param0->windows[sPlayerNameWindowIndex[param0->context->playerCount][v1]], FONT_SYSTEM, v3, v7, 0, TEXT_SPEED_INSTANT, v5, NULL);
            Heap_Free(v3);
        }
    }
}

static void WiFiLobbyMinigameBalloon_ClearPlayerNameWindows(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    if (param1 == 1) {
        Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0, 13, 12, 4, 17);
        Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0x11, 0, 12, 4, 17);
        Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0x14, 13, 12, 4, 17);
    } else {
        switch (param0->context->playerCount) {
        case 2:
            Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0, 13, 12, 4, 17);
            Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0x14, 13, 12, 4, 17);
            break;
        case 3:
            Bg_FillTilemapRect(param0->bgConfig, 4, 1023, 0x11, 0, 12, 4, 17);
            break;
        }
    }

    Bg_ScheduleTilemapTransfer(param0->bgConfig, 4);
}

static void WiFiLobbyMinigameBalloon_InitParticles(WiFiLobbyMinigameBalloonGame *param0)
{
    void *v0;
    Camera *camera;
    void *v2;

    ParticleSystem_ZeroAll();

    v0 = Heap_Alloc(HEAP_ID_110, 0x4800);
    param0->particleSystem = ParticleSystem_New(WiFiLobbyMinigameBalloon_AllocTextureVram, WiFiLobbyMinigameBalloon_AllocPaletteVram, v0, 0x4800, 1, HEAP_ID_110);
    camera = ParticleSystem_GetCamera(param0->particleSystem);

    Camera_SetClipping(FX32_ONE, FX32_ONE * 900, camera);
    v2 = ParticleSystem_LoadResourceFromNARC(NARC_INDEX_PARTICLEDATA__PL_ETC__PL_ETC_PARTICLE, 0, HEAP_ID_110);
    ParticleSystem_SetResource(param0->particleSystem, v2, (1 << 1) | (1 << 3), 1);
}

static void WiFiLobbyMinigameBalloon_FreeParticles(WiFiLobbyMinigameBalloonGame *param0)
{
    void *v0 = ParticleSystem_GetHeapStart(param0->particleSystem);

    ParticleSystem_Free(param0->particleSystem);
    Heap_Free(v0);
}

void WiFiLobbyMinigameBalloon_CreateParticleEmitter(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    switch (param1) {
    case 0:
        ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 0, NULL, param0);
        break;
    case 1:
        ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 1, NULL, param0);
        break;
    case 2:
        ParticleSystem_CreateEmitterWithCallback(param0->particleSystem, 2, NULL, param0);
        break;
    default:
        GF_ASSERT(FALSE);
        return;
    }
}

static u32 WiFiLobbyMinigameBalloon_AllocTextureVram(u32 param0, BOOL param1)
{
    NNSGfdTexKey v0;

    v0 = NNS_GfdAllocTexVram(param0, param1, 0);
    GF_ASSERT(v0 != NNS_GFD_ALLOC_ERROR_TEXKEY);
    ParticleSystem_RegisterTextureKey(v0);

    return NNS_GfdGetTexKeyAddr(v0);
}

static u32 WiFiLobbyMinigameBalloon_AllocPaletteVram(u32 param0, BOOL param1)
{
    NNSGfdPlttKey v0;

    v0 = NNS_GfdAllocPlttVram(param0, param1, NNS_GFD_ALLOC_FROM_LOW);
    GF_ASSERT(v0 != NNS_GFD_ALLOC_ERROR_PLTTKEY);

    ParticleSystem_RegisterPaletteKey(v0);

    return NNS_GfdGetPlttKeyAddr(v0);
}

static void WiFiLobbyMinigameBalloon_LoadMainGraphics(WiFiLobbyMinigameBalloonGame *param0, NARC *param1)
{
    int v0;
    String *v1, *v2;
    int v3;

    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, 2, param0->spriteSystem, param0->spriteManager, param1, 27, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10003);

    v1 = MessageLoader_GetNewString(param0->messageLoader, 2);
    v0 = 6 + ((30 - Font_CalcStringWidth(0, v1, 0)) / 2);
    WiFiLobbyMinigameBalloon_CreateTextOAM(param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->scoreDisplay.labelText, v1, FONT_SYSTEM, TEXT_COLOR(14, 15, 0), 0, 10003, v0 + 6 * 6, 168, 0, 1, 12, 2);
    String_Free(v1);

    v1 = MessageLoader_GetNewString(param0->messageLoader, 0);
    v2 = MessageLoader_GetNewString(param0->messageLoader, 1);
    for (v3 = 0; v3 < 6; v3++) {
        WiFiLobbyMinigameBalloon_CreateTextOAM(param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->scoreDisplay.digitReel[v3][0], v1, FONT_SYSTEM, TEXT_COLOR(14, 15, 0), 0, 10003, v0 + 6 * v3, 168, 0, 3, 12, 2 * 5);
        WiFiLobbyMinigameBalloon_CreateTextOAM(param0->bgConfig, param0->spriteManager, param0->fontOAMManager, &param0->scoreDisplay.digitReel[v3][1], v2, FONT_SYSTEM, TEXT_COLOR(14, 15, 0), 0, 10003, v0 + 6 * v3, 168, 0, 3, 12, 2 * 5);
    }
    String_Free(v1);
    String_Free(v2);

    WiFiLobbyMinigameBalloon_LayoutScoreDigits(&param0->scoreDisplay);

    WiFiLobbyMinigameBalloon_CreateScoreDigits(param0);

    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_MAIN_OBJ, param0->spriteSystem, param0->spriteManager, param1, 27, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10004);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 24, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10002);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 26, FALSE, 10002);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 25, FALSE, 10002);
    param0->scoreDisplay.sprite = WiFiLobbyMinigameBalloon_CreateScoreSprite(param0);

    SpriteSystem_LoadPaletteBuffer(param0->paletteData, PLTTBUF_MAIN_OBJ, param0->spriteSystem, param0->spriteManager, NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, 20, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 10002);
    SpriteSystem_LoadCharResObj(param0->spriteSystem, param0->spriteManager, NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, 21, FALSE, NNS_G2D_VRAM_TYPE_2DMAIN, 10001);
    SpriteSystem_LoadCellResObj(param0->spriteSystem, param0->spriteManager, NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, 22, FALSE, 10001);
    SpriteSystem_LoadAnimResObj(param0->spriteSystem, param0->spriteManager, NARC_INDEX_RESOURCE__ENG__WIFI_LOBBY_MINIGAME__WLMNGM_TOOL, 23, FALSE, 10001);
    param0->introBanner.sprite = WiFiLobbyMinigameBalloon_CreateIntroBannerSprite(param0);
}

static void WiFiLobbyMinigameBalloon_FreeMainGraphics(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        WiFiLobbyMinigameBalloon_FreeTextOAM(&param0->scoreDisplay.digitReel[v0][0]);
        WiFiLobbyMinigameBalloon_FreeTextOAM(&param0->scoreDisplay.digitReel[v0][1]);
    }

    WiFiLobbyMinigameBalloon_FreeTextOAM(&param0->scoreDisplay.labelText);
    WiFiLobbyMinigameBalloon_FreeScoreDigits(param0);
    WiFiLobbyMinigameBalloon_FreeScoreSprite(param0, param0->scoreDisplay.sprite);
    WiFiLobbyMinigameBalloon_FreeIntroBannerSprite(param0, param0->introBanner.sprite);
}

static void WiFiLobbyMinigameBalloon_LoadSubGraphics(WiFiLobbyMinigameBalloonGame *param0, NARC *param1)
{
    SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->paletteData, PLTTBUF_SUB_OBJ, param0->spriteSystem, param0->spriteManager, param1, 23, FALSE, 9, NNS_G2D_VRAM_TYPE_2DSUB, 10006);
    SpriteSystem_LoadCharResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 20, FALSE, NNS_G2D_VRAM_TYPE_2DSUB, 10004);
    SpriteSystem_LoadCellResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 22, FALSE, 10004);
    SpriteSystem_LoadAnimResObjFromOpenNarc(param0->spriteSystem, param0->spriteManager, param1, 21, FALSE, 10004);

    WiFiLobbyMinigameBalloon_CreateRankIcons(param0);
    WiFiLobbyMinigameBalloon_CreatePlayerBalloonSprites(param0, &param0->playerBalloonSprites);
    WiFiLobbyMinigameBalloon_CreatePlayerBalloons(param0, &param0->playerBalloons);
    WiFiLobbyMinigameBalloon_CreateOpponentBalloons(param0, &param0->opponentBalloons);
    WiFiLobbyMinigameBalloon_ApplySubPlayerPalettes(param0);
    WiFiLobbyMinigameBalloon_ApplySubPlayerPalettes2(param0);
}

static void WiFiLobbyMinigameBalloon_FreeSubGraphics(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloon_FreeRankIcons(param0);
    WiFiLobbyMinigameBalloon_FreePlayerBalloonSprites(param0, &param0->playerBalloonSprites);
    WiFiLobbyMinigameBalloon_FreePlayerBalloons(param0, &param0->playerBalloons);
    WiFiLobbyMinigameBalloon_FreeOpponentBalloons(param0, &param0->opponentBalloons);
}

static void WiFiLobbyMinigameBalloon_LoadMainBg(WiFiLobbyMinigameBalloonGame *param0, NARC *param1)
{
    PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, 4, HEAP_ID_110, PLTTBUF_MAIN_BG, 0, 0);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 2, param0->bgConfig, 3, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 3, param0->bgConfig, 3, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 0, param0->bgConfig, 2, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 1, param0->bgConfig, 2, 0, 0, 0, HEAP_ID_110);
    PaletteData_FillBufferRange(param0->paletteData, PLTTBUF_MAIN_BG, PLTTSEL_BOTH, 0x0, 0, 1);
}

static void WiFiLobbyMinigameBalloon_Noop1(WiFiLobbyMinigameBalloonGame *param0)
{
    return;
}

static void WiFiLobbyMinigameBalloon_LoadSubBg(WiFiLobbyMinigameBalloonGame *param0, NARC *param1)
{
    PaletteData_LoadBufferFromFileStart(param0->paletteData, NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, 5, HEAP_ID_110, PLTTBUF_SUB_BG, 5 * PALETTE_SIZE_BYTES, 0);
    PaletteData_LoadBufferFromFile(param0->paletteData, NARC_INDEX_APPLICATION__BALLOON__GRAPHIC__BALLOON_GRA, 6, HEAP_ID_110, PLTTBUF_SUB_BG, PALETTE_SIZE_BYTES * 10, PLTT_DEST(6), PLTT_DEST(6));
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 13, param0->bgConfig, 6, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 14, param0->bgConfig, 6, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 18, param0->bgConfig, 5, 0, 0, 0, HEAP_ID_110);

    switch (param0->context->playerCount) {
    case 2:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 15, param0->bgConfig, 5, 0, 0, 0, HEAP_ID_110);
        break;
    case 3:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 16, param0->bgConfig, 5, 0, 0, 0, HEAP_ID_110);
        break;
    default:
        Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 17, param0->bgConfig, 5, 0, 0, 0, HEAP_ID_110);
        break;
    }

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 18, param0->bgConfig, 4, 0, 0, 0, HEAP_ID_110);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 19, param0->bgConfig, 4, 0, 0, 0, HEAP_ID_110);

    WiFiLobbyMinigameBalloon_ApplyMainPlayerPalettes(param0);
    WiFiLobbyMinigameBalloon_ApplyPlayerPalettes(param0);

    LoadStandardWindowGraphics(param0->bgConfig, BG_LAYER_SUB_0, (((((0x8000 - 0x2000) / 32) + (10 * 2)) + (10 * 2)) + (10 * 2)) + (10 * 2), 6, 0, HEAP_ID_110);
    PaletteData_LoadBufferFromHardware(param0->paletteData, PLTTBUF_SUB_BG, PLTT_DEST(6), PALETTE_SIZE_BYTES);
    PaletteData_FillBufferRange(param0->paletteData, PLTTBUF_SUB_BG, PLTTSEL_BOTH, 0x0, 0, 1);
}

static void WiFiLobbyMinigameBalloon_Noop2(WiFiLobbyMinigameBalloonGame *param0)
{
    return;
}

static void WiFiLobbyMinigameBalloon_Load3DModels(WiFiLobbyMinigameBalloonGame *param0, NARC *param1)
{
    int v0, v1;
    WiFiLobbyMinigameBalloonPlayerModel *v2 = &param0->playerModel;
    WiFiLobbyMinigameBalloon3DObject *v3 = &param0->balloon3DObject;
    int v4;
    void *v5 = NULL;

    v4 = WiFiLobbyMinigameBalloon_GetPlayerIndex(param0, CommSys_CurNetId());

    Easy3DModel_LoadFrom(&v2->model, param1, sPlayerModelFiles[v4].baseModel, HEAP_ID_110);
    Easy3DObject_Init(&v2->object, &v2->model);
    Easy3DObject_SetPosition(&v2->object, FX32_CONST(0), FX32_CONST(-25), FX32_CONST(0));
    Easy3DObject_SetScale(&v2->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&v2->object, 1);
    Easy3DModel_LoadFrom(&v2->popModels[0], param1, sPlayerModelFiles[v4].popModel0, HEAP_ID_110);
    Easy3DModel_LoadFrom(&v2->popModels[1], param1, sPlayerModelFiles[v4].popModel1, HEAP_ID_110);
    Easy3DModel_LoadFrom(&v2->popModels[2], param1, sPlayerModelFiles[v4].popModel2, HEAP_ID_110);
    Easy3DModel_LoadFrom(&v2->popModels[3], param1, sPlayerModelFiles[v4].popModel3, HEAP_ID_110);

    for (v0 = 0; v0 < 8; v0++) {
        for (v1 = 0; v1 < 4; v1++) {
            if (v5 == NULL) {
                Easy3DAnim_LoadFrom(&v2->popAnims[v0][v1].anim, &v2->popModels[v1], param1, 35 + v1, 110, &param0->allocator);
                v5 = v2->popAnims[v0][v1].anim.data;
            } else {
                Easy3DAnim_LoadFromData(&v2->popAnims[v0][v1].anim, &v2->popModels[v1], v5, &param0->allocator);
            }

            Easy3DAnim_SetFrame(&v2->popAnims[v0][v1].anim, 0);
        }
    }

    Easy3DModel_LoadFrom(&v3->model, param1, 30, HEAP_ID_110);
    Easy3DObject_Init(&v3->object, &v3->model);
    Easy3DObject_SetPosition(&v3->object, FX32_CONST(0), FX32_CONST(-25), FX32_CONST(0));
    Easy3DObject_SetScale(&v3->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&v3->object, 1);
}

static void WiFiLobbyMinigameBalloon_Free3DModels(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0, v1;
    WiFiLobbyMinigameBalloonPlayerModel *v2 = &param0->playerModel;

    Easy3DModel_Release(&v2->model);

    for (v0 = 0; v0 < 4; v0++) {
        Easy3DModel_Release(&v2->popModels[v0]);
    }

    for (v0 = 0; v0 < 8; v0++) {
        for (v1 = 0; v1 < 4; v1++) {
            Easy3DAnim_Release(&v2->popAnims[v0][v1].anim, &param0->allocator);
        }
    }

    Easy3DModel_Release(&param0->balloon3DObject.model);
}

BOOL WiFiLobbyMinigameBalloon_SpawnBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    WiFiLobbyMinigameBalloonPlayerModel *v0 = &param0->playerModel;
    Easy3DModel *v1;
    int v2, v3;

    if (param1 > 1200) {
        v3 = 3;
    } else if (param1 > 3 / 3 * 2) {
        v3 = 2;
    } else if (param1 > 3 / 3 * 1) {
        v3 = 1;
    } else {
        v3 = 0;
    }

    v1 = &v0->popModels[v3];

    for (v2 = 0; v2 < 8; v2++) {
        if (v0->popAnims[v2][v3].active == 0) {
            Easy3DObject_Init(&v0->popAnims[v2][v3].object, v1);
            Easy3DObject_SetPosition(&v0->popAnims[v2][v3].object, FX32_CONST(0), FX32_CONST(-25), FX32_CONST(0));
            Easy3DObject_SetScale(&v0->popAnims[v2][v3].object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
            Easy3DObject_SetVisible(&v0->popAnims[v2][v3].object, 1);
            Easy3DAnim_SetFrame(&v0->popAnims[v2][v3].anim, 0);
            Easy3DObject_AddAnim(&v0->popAnims[v2][v3].object, &v0->popAnims[v2][v3].anim);

            v0->popAnims[v2][v3].active = 1;

            Sound_PlayEffect(SEQ_SE_PL_BALLOON03_2_sseq);
            return 1;
        }
    }

    return 0;
}

void WiFiLobbyMinigameBalloon_RemoveBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2)
{
    WiFiLobbyMinigameBalloonPlayerModel *v0 = &param0->playerModel;

    Easy3DObject_RemoveAnim(&v0->popAnims[param1][param2].object, &v0->popAnims[param1][param2].anim);
    v0->popAnims[param1][param2].active = 0;
}

void WiFiLobbyMinigameBalloon_UpdateBalloonPops(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonPlayerModel *v0 = &param0->playerModel;
    int v1, v2;

    for (v1 = 0; v1 < 8; v1++) {
        for (v2 = 0; v2 < 4; v2++) {
            if (v0->popAnims[v1][v2].active == 1) {
                if (Easy3DAnim_Update(&v0->popAnims[v1][v2].anim, FX32_ONE) == 1) {
                    WiFiLobbyMinigameBalloon_RemoveBalloonPop(param0, v1, v2);
                }
            }
        }
    }
}

void WiFiLobbyMinigameBalloon_DrawBalloonPops(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonPlayerModel *v0 = &param0->playerModel;
    int v1, v2;

    for (v1 = 0; v1 < 8; v1++) {
        for (v2 = 0; v2 < 4; v2++) {
            if (v0->popAnims[v1][v2].active == 1) {
                Easy3DObject_Draw(&v0->popAnims[v1][v2].object);
            }
        }
    }
}

BOOL WiFiLobbyMinigameBalloon_IsLocalPlayer(WiFiLobbyMinigameBalloonGame *param0)
{
    if (param0->winnerNetId == CommSys_CurNetId()) {
        return 1;
    }

    return 0;
}

int WiFiLobbyMinigameBalloon_FindWinner(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0, v1;
    u32 v2;

    v0 = param0->context->netIds[0];
    v2 = param0->scores[0];

    for (v1 = 1; v1 < param0->context->playerCount; v1++) {
        if (v2 < param0->scores[v1]) {
            v2 = param0->scores[v1];
            v0 = param0->context->netIds[v1];
        }
    }

    param0->winnerNetId = v0;
    return param0->winnerNetId;
}

void WiFiLobbyMinigameBalloon_QueueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1, const WiFiLobbyMinigameBalloonPacket *param2)
{
    WiFiLobbyMinigameBalloonPacket *v0;
    int v1;

    if (WiFiLobbyMinigameBalloon_HandleImmediatePacket(param0, param1, param2) == 1) {
        return;
    }

    v1 = param0->receiveQueueWriteIndex[param1] % 60;
    v0 = &param0->receiveQueues[param1].packets[v1];

    param0->receiveQueueWriteIndex[param1]++;

    GF_ASSERT(v0->type == 0);

    *v0 = *param2;
}

WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    WiFiLobbyMinigameBalloonPacket *v0;
    int v1 = param0->receiveQueueReadIndex[param1] % 60;
    v0 = &param0->receiveQueues[param1].packets[v1];

    if (v0->type != 0) {
        param0->receiveQueueReadIndex[param1]++;
        return v0;
    }

    return NULL;
}

static BOOL WiFiLobbyMinigameBalloon_HandleImmediatePacket(WiFiLobbyMinigameBalloonGame *param0, int param1, const WiFiLobbyMinigameBalloonPacket *param2)
{
    switch (param2->type) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        GF_ASSERT(param0->pendingReceivePacket.type == 0);
        param0->pendingReceivePacket = *param2;
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameBalloon_QueueSendPacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    WiFiLobbyMinigameBalloonPacket *v0;
    int v1;

    if (WiFiLobbyMinigameBalloon_HandleImmediateSendPacket(param0, param1) == 1) {
        return;
    }

    v1 = param0->sendQueueWriteIndex % 60;
    v0 = &param0->sendQueue.packets[v1];

    param0->sendQueueWriteIndex++;

    GF_ASSERT(v0->type == 0);

    *v0 = *param1;
}

static BOOL WiFiLobbyMinigameBalloon_HandleImmediateSendPacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    switch (param1->type) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (param0->pendingSendPacket.type == 0) {
            param0->pendingSendPacket = *param1;
            return 1;
        } else if (param1->type == param0->pendingSendPacket.type) {
            return 1;
        } else {
            GF_ASSERT(FALSE);
            return 0;
        }
        break;
    }

    return 0;
}

WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueSendPacket(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonPacket *v0;
    int v1 = param0->sendQueueReadIndex % 60;
    v0 = &param0->sendQueue.packets[v1];
    if (v0->type != 0) {
        return v0;
    }

    return NULL;
}

static int WiFiLobbyMinigameBalloon_SendQueuedPacket(WiFiLobbyMinigameBalloonGame *param0)
{
    WiFiLobbyMinigameBalloonPacket *v0;

    if (param0->sendCooldown > 0) {
        param0->sendCooldown--;
        return 0;
    }

    if (param0->pendingSendPacket.type != 0) {
        if (WiFiLobbyMinigameBalloon_SendPacket(param0, &param0->pendingSendPacket) == 1) {
            param0->pendingSendPacket.type = 0;
            return 1;
        } else {
            return 0;
        }
    }

    v0 = WiFiLobbyMinigameBalloon_DequeueSendPacket(param0);

    if (v0 == NULL) {
        return 0;
    }

    if (WiFiLobbyMinigameBalloon_SendPacket(param0, v0) == 1) {
        v0->type = 0;
        param0->sendQueueReadIndex++;
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_ProcessReceivedPackets(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0, v1;
    WiFiLobbyMinigameBalloonPacket *v2;
    int v3, v4;

    v4 = param0->pendingReceivePacket.type;

    if (WiFiLobbyMinigameBalloon_HandlePacket(param0, &param0->pendingReceivePacket) == 1) {
        return;
    }

    v2 = &param0->pendingReceivePacket;

    for (v1 = 0; v1 < param0->context->playerCount; v1++) {
        while (TRUE) {
            v2 = WiFiLobbyMinigameBalloon_DequeueReceivedPacket(param0, param0->context->netIds[v1]);

            if (v2 == NULL) {
                break;
            }

            v4 = v2->type;
            v3 = WiFiLobbyMinigameBalloon_HandlePacket(param0, v2);

            if (v3 == 1) {
                (void)0;
            }
        }
    }
}

int WiFiLobbyMinigameBalloon_GetBalloonLevel(WiFiLobbyMinigameBalloonGame *param0)
{
    return param0->balloonLevel;
}

int WiFiLobbyMinigameBalloon_GetPlayerSlot(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    int v0, v1, v2;
    int v3, v4;
    int v5, v6;
    int v7;
    const u8 *v8;

    v6 = CommSys_CurNetId();
    v3 = 0xff;
    v4 = 0xff;

    for (v5 = 0; v5 < param0->context->playerCount; v5++) {
        if (param0->context->netIds[v5] == v6) {
            v4 = v5;
        }

        if (param0->context->netIds[v5] == param1) {
            v3 = v5;
        }
    }

    GF_ASSERT(v3 != 0xff && v4 != 0xff);

    for (v5 = 0; v5 < param0->context->playerCount; v5++) {
        if (sPlayerSlotOrder[param0->context->playerCount][v5] == v4) {
            v1 = v5;
        }

        if (sPlayerSlotOrder[param0->context->playerCount][v5] == v3) {
            v0 = v5;
        }
    }

    v2 = v0 - v1;

    if (v2 < 0) {
        v2 += param0->context->playerCount;
    }

    return v2;
}

int WiFiLobbyMinigameBalloon_GetPlayerIndex(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < param0->context->playerCount; v0++) {
        if (param0->context->netIds[v0] == param1) {
            return v0;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

void WiFiLobbyMinigameBalloon_StartSync(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2)
{
    GF_ASSERT(param0->syncState == 0);

    param0->syncState = param1;
    param0->syncId = param2;
}

static BOOL WiFiLobbyMinigameBalloon_UpdateSync(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0 = 0;

    switch (param0->syncState) {
    case 1:
        v0 = 1;
        break;
    case 2:
        v0 = 1;
        break;
    case 3:
        v0 = 1;
        break;
    case 4:
        if (param0->gaugeActive == 1) {
            v0 = 1;
        }
        break;
    case 5:
        if (param0->confetti.active == 0) {
            v0 = 1;
        }
        break;
    case 6:
        if (param0->introBanner.finished == 1) {
            v0 = 1;
        }
        break;
    default:
        return 0;
    }

    if (v0 == 1) {
        CommTiming_StartSync(param0->syncId);

        if (WiFiLobbyMinigameBalloon_IsLocalPlayer(param0) == 1) {
            param0->syncState = 7;
        } else {
            param0->syncState = 0;
        }

        return 1;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloon_CheckSync(WiFiLobbyMinigameBalloonGame *param0, int param1)
{
    if (param0->syncState != 7) {
        return 0;
    }

    if (param0->syncId != param1) {
        return 0;
    }

    if (CommTiming_IsSyncState(param0->syncId) == 1) {
        param0->syncState = 0;
        return 1;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloon_IntroSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1)
{
    switch (param1->step) {
    case 0:
        WiFiLobbyMinigameBalloon_SendSync(param0, 1, param1->syncId);
        param1->step++;
        break;
    case 1:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            param1->step++;
        }
        break;
    case 2:
        WiFiLobbyMinigameBalloon_SendSync2(param0, param1->syncId);
        param1->step++;
        break;
    case 3:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            param1->step++;
        }
        break;
    case 4:
        WiFiLobbyMinigameBalloon_SendPlayerState(param0, param1->syncId);
        param1->step++;
        break;
    case 5:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            return 1;
        }
        break;
    }
    return 0;
}

static int WiFiLobbyMinigameBalloon_GameSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1)
{
    if (param0->gameTimer > (43 * 30 + 12)) {
        if ((param0->syncState == 0) && (param0->pendingSendPacket.type == 0) && (param0->pendingReceivePacket.type == 0)) {
            return 1;
        } else {
            (void)0;
        }
    }

    switch (param1->step) {
    case 0:
        WiFiLobbyMinigameBalloon_SendBalloonPop(param0, param0->balloonLevel, WiFiLobbyMinigameBalloon_GetGaugeLevel(param0->balloonLevel), param1->syncId);
        param1->step++;
        break;
    case 1:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            param1->step++;
        }
        break;
    case 2:
        if ((param0->scoreGauge.targetScore != 0) && (param0->scoreGauge.currentScore >= param0->scoreGauge.targetScore)) {
            param0->balloonLevel++;
            WiFiLobbyMinigameBalloon_SendBalloonLevel(param0, WiFiLobbyMinigameBalloon_GetBalloonLevel(param0), param1->syncId);
            param1->step++;
        }
        break;
    case 3:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            param1->step = 0;
        }
        break;
    }

    return 0;
}

static int WiFiLobbyMinigameBalloon_ResultsSequence(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonSequenceState *param1)
{
    switch (param1->step) {
    case 0:
        WiFiLobbyMinigameBalloon_SendGameState(param0, param1->syncId);
        param1->step++;
        break;
    case 1:
        if (WiFiLobbyMinigameBalloon_CheckSync(param0, param1->syncId) == 1) {
            param1->syncId++;
            param1->step++;
        }
        break;
    case 2:
        if (param0->phase == 8) {
            param1->step++;
        }
        break;
    case 3:
        param1->delay++;

        if (param1->delay < 90) {
            break;
        }

        if (WiFiLobbyMinigameBalloon_SendReady(param0) == 1) {
            return 1;
        }
        break;
    }

    return 0;
}

static BOOL WiFiLobbyMinigameBalloon_UpdateSequence(WiFiLobbyMinigameBalloonGame *param0)
{
    int v0;
    WiFiLobbyMinigameBalloonSequenceState *v1;

    if (WiFiLobbyMinigameBalloon_IsLocalPlayer(param0) == 0) {
        return 0;
    }

    v1 = &param0->sequenceState;

    if (v1->sequenceIndex >= NELEMS(sSequenceTable)) {
        return 1;
    }

    v0 = sSequenceTable[v1->sequenceIndex](param0, v1);

    if (v0 == 1) {
        v1->sequenceIndex++;
        v1->step = 0;
        v1->delay = 0;
        v1->unk_10 = 0;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_NoopCamera(Camera *camera)
{
    return;
}
