#include "wifi_menu_app/wifi_menu_app_0223648C.h"

#include <nitro.h>
#include <string.h>

#include "generated/journal_online_events.h"

#include "struct_defs/struct_0207DE04.h"
#include "struct_defs/struct_0207DFAC.h"
#include "struct_defs/struct_0207E060.h"

#include "nintendo_wfc/main.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/wifi_2d_char_0222CCE4.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CD2C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_menu_app/struct_wifi_menu_app_022366E4.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236744_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236760.h"
#include "wifi_menu_app/struct_wifi_menu_app_022376D0.h"

#include "bg_window.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "enums.h"
#include "font.h"
#include "game_options.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "journal.h"
#include "menu.h"
#include "message.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "pltt_transfer.h"
#include "render_oam.h"
#include "render_window.h"
#include "save_player.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"
#include "comm_tool.h"
#include "wifi_comm.h"
#include "vram_transfer.h"

FS_EXTERN_OVERLAY(wifi_2d_char);

typedef struct {
    WFCStatusBuffer *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s32 unk_08;
    s32 unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14[4];
    u8 unk_18[4];
    u8 unk_1C[4];
    u8 unk_20[4];
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    u8 unk_28[4];
    u8 unk_2C;
    u8 unk_2D;
} WiFiCommAppState;

typedef struct {
    WiFi2DCharObject *unk_00;
    WiFi2DCharRenderObject *unk_04;
    u16 unk_08;
    s16 unk_0A;
} WiFiCommActorRender;

typedef struct {
    BgConfig *unk_00;
    StringTemplate *unk_04;
    MessageLoader *unk_08;
    String *unk_0C;
    String *unk_10;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
    SpriteList *unk_18;
    G2dRenderer unk_1C;
    SpriteResourceCollection *unk_1A8[4];
    WiFi2DCharObjectManager *unk_1B8;
    WiFi2DCharRenderer *unk_1BC;
    WiFiCommActorRender unk_1C0[4];
    Window unk_1F0;
    Window unk_200;
    Window unk_210;
    Window unk_220;
    Window unk_230;
    Menu *unk_240;
    void *unk_244;
    NNSG2dScreenData *unk_248;
    void *unk_24C;
    void *unk_250;
    NNSG2dPaletteData *unk_254;
    s16 unk_258;
    s16 unk_25A;
} WiFiCommAppGraphics;

typedef struct WiFiCommApp_t {
    WiFiCommAppState unk_00;
    WiFiCommAppGraphics unk_30;
} WiFiCommApp;

static void WiFiCommApp_VBlankCallback(void *param0);
static BOOL WiFiCommApp_IsHost(const WiFiCommAppState *param0);
static void WiFiCommApp_InitAllGraphics(WiFiCommApp *param0, const WiFiCommAppArgs *param1, u32 heapID);
static void WiFiCommApp_FreeAllGraphics(WiFiCommApp *param0, u32 heapID);
static void WiFiCommApp_SetGxBanks(void);
static void WiFiCommApp_InitBackgrounds(WiFiCommAppGraphics *param0, u32 heapID);
static void WiFiCommApp_FreeBackgrounds(WiFiCommAppGraphics *param0);
static void WiFiCommApp_InitWindows(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID);
static void WiFiCommApp_FreeWindows(WiFiCommAppGraphics *param0, u32 heapID);
static void WiFiCommApp_InitText(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID);
static void WiFiCommApp_FreeText(WiFiCommAppGraphics *param0);
static void WiFiCommApp_DrawActivityHeader(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID);
static void WiFiCommApp_InitSprites(WiFiCommAppGraphics *param0, u32 heapID);
static void WiFiCommApp_FreeSprites(WiFiCommAppGraphics *param0);
static void WiFiCommApp_ShowMessageWithDelay(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 param2, u8 param3, u32 heapID);
static BOOL WiFiCommApp_IsMessageDone(WiFiCommAppGraphics *param0);
static void WiFiCommApp_ClearMessage(WiFiCommAppGraphics *param0);
static void WiFiCommApp_ShowPlayerJoinPrompt(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, u32 heapID);
static void WiFiCommApp_ClearPlayerJoinPrompt(WiFiCommAppGraphics *param0);
static void WiFiCommApp_DrawAllPlayerRows(WiFiCommApp *param0, const WiFiCommAppArgs *param1, u32 heapID);
static void WiFiCommApp_DrawPlayerRow(WiFiCommApp *param0, WiFiCommAppGraphics *param1, const WiFiCommAppArgs *param2, int param3, u32 heapID);
static void WiFiCommApp_ClearPlayerRow(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, u32 heapID);
static void WiFiCommApp_SetTemplatePlayerName(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, int param3, u32 heapID);
static void WiFiCommApp_SetTemplatePlayerId(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, int param3, u32 heapID);
static void WiFiCommApp_AnimateSelectionPalette(WiFiCommAppGraphics *param0);
static void WiFiCommApp_ApplySelectionPalette(WiFiCommAppGraphics *param0, u32 param1);
static void WiFiCommApp_CheckForDisconnect(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 param2);
static void WiFiCommApp_CheckClientDisconnect(WiFiCommApp *param0);
static BOOL WiFiCommApp_HasConnectedPlayers(const WiFiCommApp *param0);
static BOOL WiFiCommApp_StartWifiActivity(u32 param0, u32 param1);
static void WiFiCommApp_SetCommStateForActivity(WiFiCommApp *param0, const WiFiCommAppArgs *param1);
static BOOL WiFiCommApp_StartVoiceChat(WiFiCommApp *param0);
static BOOL WiFiCommApp_StopVoiceChat(WiFiCommApp *param0);
static void WiFiCommApp_EnableVoiceChat(WiFiCommApp *param0);
static void WiFiCommApp_DisableVoiceChat(WiFiCommApp *param0);
static int WiFiCommApp_GetConnectedPlayerCount(WiFiCommApp *param0);
static void WiFiCommApp_ClearNewPlayers(WiFiCommApp *param0);
static void WiFiCommApp_ClearKnownPlayers(WiFiCommApp *param0);
static void WiFiCommApp_InstallConnectionCallback(WiFiCommApp *param0);
static void WiFiCommApp_RemoveConnectionCallback(WiFiCommApp *param0);
static BOOL WiFiCommApp_ProcessDisconnects(WiFiCommApp *param0);
static void WiFiCommApp_OnConnectionClosed(u16 param0, void *param1);
static BOOL WiFiCommApp_HasVoiceChatChanged(WiFiCommApp *param0);
static void WiFiCommApp_RequestPlayerRedraw(WiFiCommApp *param0);
static void WiFiCommApp_AddPlayerActor(WiFiCommApp *param0, u32 param1, u32 heapID);
static void WiFiCommApp_CreatePlayerActor(WiFiCommApp *param0, u32 param1, u32 heapID);
static void WiFiCommApp_UpdateActors(WiFiCommApp *param0);
static void WiFiCommApp_FreePlayerActors(WiFiCommApp *param0);
static void WiFiCommApp_SendPlayerResetStatus(WiFiCommApp *param0, u32 param1);
static void WiFiCommApp_ResetStalePlayers(WiFiCommApp *param0);
static void WiFiCommApp_ProcessJoinedPlayers(WiFiCommApp *param0, u32 heapID);
static void WiFiCommApp_ShowWaitDial(WiFiCommApp *param0);
static void WiFiCommApp_ActorRenderStep0(WiFiCommApp *param0, WiFiCommActorRender *param1);
static void WiFiCommApp_ActorRenderStep1(WiFiCommApp *param0, WiFiCommActorRender *param1);
static void WiFiCommApp_ActorRenderStep2(WiFiCommApp *param0, WiFiCommActorRender *param1);
static void WiFiCommApp_ActorRenderStep3(WiFiCommApp *param0, WiFiCommActorRender *param1);
static void WiFiCommApp_BroadcastVoiceChatFlags(WiFiCommApp *param0);
static BOOL WiFiCommApp_IsTimingSync13Complete(WiFiCommApp *param0);
static void WiFiCommApp_RecordJournalWifiClub(WiFiCommAppArgs *param0, u32 heapID);
static void WiFiCommApp_StartMatchmakingTimer(WiFiCommApp *param0);
static BOOL WiFiCommApp_IsMatchmakingTimerExpired(WiFiCommApp *param0);
static BOOL WiFiCommApp_HostState0(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState1(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState2(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState3(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState4(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState5(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState6(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState7(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState8(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState9(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState10(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState11(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState12(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState13(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState14(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState15(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState16(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState17(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState18(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState19(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState20(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState21(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState22(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState23(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState24(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState25(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState26(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState27(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState28(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState29(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState30(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState31(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_HostState32(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState0(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState1(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState2(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState3(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState4(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState5(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState6(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState7(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState8(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState9(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState10(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState11(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState12(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState13(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState14(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState15(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState16(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState17(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState18(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState19(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState20(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState21(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState22(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState23(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState24(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState25(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState26(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState27(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState28(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);
static BOOL WiFiCommApp_ClientState29(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID);

static const u8 sWiFiCommAppActorSpawnOffsets[4] = {
    0x8,
    0x0,
    0x4,
    0xC
};

static const u8 sWiFiCommAppPaletteAnimFrames[18] = {
    0x5,
    0x4,
    0x3,
    0x2,
    0x1,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x1,
    0x2,
    0x3,
    0x4,
    0x5,
    0x5,
    0x5,
    0x5
};

static const WindowTemplate sWiFiCommAppYesNoWindowTemplate = {
    0x2,
    0x19,
    0xD,
    0x5,
    0x4,
    0x1,
    0x39
};

static u8 sWiFiCommAppActivityMessageIds[4] = {
    0x7E,
    0x7F,
    0x7F,
    0x7F
};

static const WiFiMenuAppRect sWiFiCommAppActorSpawnRects[4] = {
    { 0xD0, 0x30, 0x0, 0x0, 0x1, 0x0 },
    { 0xE8, 0x48, 0x1, 0x0, 0x2, 0x0 },
    { 0xD0, 0x60, 0x2, 0x0, 0x0, 0x0 },
    { 0xB8, 0x48, 0x3, 0x0, 0x3, 0x0 }
};

static BOOL (*const sWiFiCommAppHostStateHandlers[33])(WiFiCommApp *, WiFiCommAppArgs *, u32) = {
    WiFiCommApp_HostState0,
    WiFiCommApp_HostState1,
    WiFiCommApp_HostState2,
    WiFiCommApp_HostState3,
    WiFiCommApp_HostState4,
    WiFiCommApp_HostState5,
    WiFiCommApp_HostState6,
    WiFiCommApp_HostState7,
    WiFiCommApp_HostState8,
    WiFiCommApp_HostState9,
    WiFiCommApp_HostState10,
    WiFiCommApp_HostState11,
    WiFiCommApp_HostState12,
    WiFiCommApp_HostState13,
    WiFiCommApp_HostState14,
    WiFiCommApp_HostState15,
    WiFiCommApp_HostState16,
    WiFiCommApp_HostState17,
    WiFiCommApp_HostState18,
    WiFiCommApp_HostState19,
    WiFiCommApp_HostState20,
    WiFiCommApp_HostState21,
    WiFiCommApp_HostState22,
    WiFiCommApp_HostState23,
    WiFiCommApp_HostState24,
    WiFiCommApp_HostState25,
    WiFiCommApp_HostState26,
    WiFiCommApp_HostState27,
    WiFiCommApp_HostState28,
    WiFiCommApp_HostState29,
    WiFiCommApp_HostState30,
    WiFiCommApp_HostState31,
    WiFiCommApp_HostState32
};

static BOOL (*const sWiFiCommAppClientStateHandlers[30])(WiFiCommApp *, WiFiCommAppArgs *, u32) = {
    WiFiCommApp_ClientState0,
    WiFiCommApp_ClientState1,
    WiFiCommApp_ClientState2,
    WiFiCommApp_ClientState3,
    WiFiCommApp_ClientState4,
    WiFiCommApp_ClientState5,
    WiFiCommApp_ClientState6,
    WiFiCommApp_ClientState7,
    WiFiCommApp_ClientState8,
    WiFiCommApp_ClientState9,
    WiFiCommApp_ClientState10,
    WiFiCommApp_ClientState11,
    WiFiCommApp_ClientState12,
    WiFiCommApp_ClientState13,
    WiFiCommApp_ClientState14,
    WiFiCommApp_ClientState15,
    WiFiCommApp_ClientState16,
    WiFiCommApp_ClientState17,
    WiFiCommApp_ClientState18,
    WiFiCommApp_ClientState19,
    WiFiCommApp_ClientState20,
    WiFiCommApp_ClientState21,
    WiFiCommApp_ClientState22,
    WiFiCommApp_ClientState23,
    WiFiCommApp_ClientState24,
    WiFiCommApp_ClientState25,
    WiFiCommApp_ClientState26,
    WiFiCommApp_ClientState27,
    WiFiCommApp_ClientState28,
    WiFiCommApp_ClientState29
};

static void (*const sWiFiCommAppActorRenderFuncs[4])(WiFiCommApp *, WiFiCommActorRender *) = {
    WiFiCommApp_ActorRenderStep0,
    WiFiCommApp_ActorRenderStep1,
    WiFiCommApp_ActorRenderStep2,
    WiFiCommApp_ActorRenderStep3,
};

int WiFiCommApp_Init(ApplicationManager *appMan, int *param1)
{
    WiFiCommApp *v0;
    WiFiCommAppArgs *v1 = ApplicationManager_Args(appMan);
    BOOL v2;

    Overlay_LoadByID(FS_OVERLAY_ID(wifi_2d_char), 2);

    v2 = CommManager_IsConnectedToWifi();
    GF_ASSERT(v2 == 1);

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_96, 0x18000);
    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_97, 0xa000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiCommApp), HEAP_ID_96);

    MI_CpuFill8(v0, 0, sizeof(WiFiCommApp));
    MI_CpuFill8(v0->unk_00.unk_1C, 1, sizeof(u8) * 4);
    MI_CpuFill8(v0->unk_00.unk_20, 1, sizeof(u8) * 4);

    VramTransfer_New(16, HEAP_ID_96);

    v0->unk_00.unk_00 = CommManager_GetUnk00();
    v0->unk_00.unk_00->ownStatus.voiceChatEnabled = v0->unk_00.unk_00->ownStatus.voiceChatEnabledBackup;
    v0->unk_00.unk_04 = WiFiCommApp_IsHost(&v0->unk_00);
    v0->unk_00.unk_06 = 0xff;

    WiFiComm_Init(v0);

    WiFiCommApp_InstallConnectionCallback(v0);
    WiFiCommApp_InitAllGraphics(v0, v1, HEAP_ID_96);

    SetVBlankCallback(WiFiCommApp_VBlankCallback, v0);
    NetworkIcon_Init();

    v0->unk_00.unk_27 = 1;

    return 1;
}

int WiFiCommApp_Main(ApplicationManager *appMan, int *param1)
{
    WiFiCommApp *v0 = ApplicationManager_Data(appMan);
    WiFiCommAppArgs *v1 = ApplicationManager_Args(appMan);
    BOOL v2;

    switch (*param1) {
    case 0:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_96);
        (*param1)++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            (*param1)++;
        }
        break;
    case 2:
        if (v0->unk_00.unk_27) {
            WiFiCommApp_CheckForDisconnect(v0, v1, 96);
        }

        if (v0->unk_00.unk_04) {
            if (CommInfo_IsInitialized() == 1) {
                WiFiCommApp_BroadcastVoiceChatFlags(v0);
                CommInfo_ServerSendArray();
                WiFiCommApp_ResetStalePlayers(v0);
            }

            v2 = sWiFiCommAppHostStateHandlers[v0->unk_00.unk_05](v0, v1, HEAP_ID_96);
        } else {
            v2 = sWiFiCommAppClientStateHandlers[v0->unk_00.unk_05](v0, v1, HEAP_ID_96);

            if (CommInfo_IsInitialized() == 1) {
                WiFiCommApp_ProcessJoinedPlayers(v0, HEAP_ID_96);
            }
        }

        if (WiFiCommApp_HasVoiceChatChanged(v0)) {
            WiFiCommApp_DrawAllPlayerRows(v0, v1, HEAP_ID_96);
        }

        WiFiCommApp_UpdateActors(v0);

        if (v2 == 1) {
            v1->success = v0->unk_00.unk_07;
            v1->result = v0->unk_00.unk_11;
            (*param1)++;
        }
        break;
    case 3:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_96);
        (*param1)++;
        break;
    case 4:
        if (IsScreenFadeDone()) {
            return 1;
        }

        break;
    }

    WiFiCommApp_AnimateSelectionPalette(&v0->unk_30);
    SpriteList_Update(v0->unk_30.unk_18);

    return 0;
}

int WiFiCommApp_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiCommApp *v0 = ApplicationManager_Data(appMan);
    WiFiCommAppArgs *v1 = ApplicationManager_Args(appMan);

    SetVBlankCallback(NULL, NULL);

    WiFiCommApp_RemoveConnectionCallback(v0);
    WiFiCommApp_FreePlayerActors(v0);
    WiFiCommApp_StopVoiceChat(v0);
    WiFiCommApp_FreeAllGraphics(v0, HEAP_ID_96);

    VramTransfer_Free();
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_97);
    Heap_Destroy(HEAP_ID_96);
    Overlay_UnloadByID(FS_OVERLAY_ID(wifi_2d_char));

    return 1;
}

void WiFiCommApp_HandlePlayerStatus(WiFiCommApp *param0, const WiFiCommPlayerStatus *param1)
{
    if (param0->unk_00.unk_04 == 0) {
        if (param1->unk_00 == CommSys_CurNetId()) {
            switch (param1->unk_04) {
            case 1:
                param0->unk_00.unk_13 = 1;
                break;
            case 0:
                param0->unk_00.unk_13 = 2;
                break;
            case 2:
                param0->unk_00.unk_13 = 3;
                break;
            }
        } else {
            switch (param1->unk_04) {
            case 1:
                param0->unk_00.unk_28[param1->unk_00] = 1;
                break;

            case 0:
            case 2:
                if (CommInfo_IsInitialized() == 1) {
                    CommInfo_InitPlayer(param1->unk_00);
                }
                break;
            }
        }
    }
}

void WiFiCommApp_RequestSync(WiFiCommApp *param0)
{
    if (param0->unk_00.unk_2C == 0) {
        param0->unk_00.unk_2C = 1;

        CommTiming_StartSync(13);
    }
}

void WiFiCommApp_HandleVoiceChatFlags(WiFiCommApp *param0, const WiFiCommVoiceChatFlags *param1)
{
    if (param0->unk_00.unk_04 != 1) {
        memcpy(param0->unk_00.unk_20, param1->unk_00, sizeof(u8) * 4);
    }
}

static void WiFiCommApp_VBlankCallback(void *param0)
{
    WiFiCommApp *v0 = param0;

    Bg_RunScheduledUpdates(v0->unk_30.unk_00);
    VramTransfer_Process();
    RenderOam_Transfer();
}

static BOOL WiFiCommApp_IsHost(const WiFiCommAppState *param0)
{
    if (CommSys_CurNetId() == 0) {
        return 1;
    }

    return 0;
}

static void WiFiCommApp_InitAllGraphics(WiFiCommApp *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_SetGxBanks();
    WiFiCommApp_InitBackgrounds(&param0->unk_30, heapID);
    WiFiCommApp_InitWindows(&param0->unk_30, param1, heapID);
    WiFiCommApp_InitText(&param0->unk_30, param1, heapID);
    WiFiCommApp_DrawActivityHeader(&param0->unk_30, param1, heapID);
    WiFiCommApp_DrawAllPlayerRows(param0, param1, heapID);
    WiFiCommApp_InitSprites(&param0->unk_30, heapID);
}

static void WiFiCommApp_FreeAllGraphics(WiFiCommApp *param0, u32 heapID)
{
    WiFiCommApp_FreeSprites(&param0->unk_30);
    WiFiCommApp_FreeText(&param0->unk_30);
    WiFiCommApp_FreeWindows(&param0->unk_30, heapID);
    WiFiCommApp_FreeBackgrounds(&param0->unk_30);
}

static void WiFiCommApp_SetGxBanks(void)
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

static void WiFiCommApp_InitBackgrounds(WiFiCommAppGraphics *param0, u32 heapID)
{
    NARC *v0;

    param0->unk_00 = BgConfig_New(heapID);

    {
        GraphicsModes v1 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D,
        };

        SetAllGraphicsModes(&v1);
    }

    {
        BgTemplate v2 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_MAIN_0, &v2, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate v3 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 1,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_MAIN_1, &v3, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_MAIN_1);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xd800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0->unk_00, BG_LAYER_MAIN_2, &v4, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, heapID);
        Bg_ClearTilemap(param0->unk_00, BG_LAYER_MAIN_2);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);

    v0 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, heapID);

    Graphics_LoadPaletteFromOpenNARC(v0, 13, 0, 5 * 32, 1 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 12, param0->unk_00, 2, 0 * 32, (24 * 2) * 32, 0, heapID);

    param0->unk_244 = Graphics_GetScrnDataFromOpenNARC(v0, 14, 0, &param0->unk_248, heapID);

    {
        param0->unk_250 = Graphics_GetPlttDataFromOpenNARC(v0, 44, &param0->unk_254, heapID);

        Graphics_LoadTilesToBgLayerFromOpenNARC(v0, 45, param0->unk_00, 0, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayerFromOpenNARC(v0, 46, param0->unk_00, 0, 0, 0, 0, heapID);
        WiFiCommApp_ApplySelectionPalette(param0, 0);

        param0->unk_258 = 3;
        param0->unk_25A = 1;
    }

    NARC_dtor(v0);
}

static void WiFiCommApp_FreeBackgrounds(WiFiCommAppGraphics *param0)
{
    Heap_Free(param0->unk_244);
    Heap_Free(param0->unk_250);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->unk_00, BG_LAYER_MAIN_0);
    Heap_Free(param0->unk_00);
}

static void WiFiCommApp_InitWindows(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(1), heapID);

    v0 = Options_Frame(SaveData_GetOptions(param1->saveData));

    LoadMessageBoxGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1, 2, v0, heapID);
    LoadStandardWindowGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1 + (18 + 12), 3, 0, heapID);
    LoadStandardWindowGraphics(param0->unk_00, BG_LAYER_MAIN_2, 0 + (24 * 2), 4, 0, heapID);
    Window_Add(param0->unk_00, &param0->unk_1F0, 1, 2, 19, 27, 4, 1, (1 + (18 + 12)) + 9);
    Window_FillTilemap(&param0->unk_1F0, 15);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_1F0, 1, 1, 2);
    Window_Add(param0->unk_00, &param0->unk_200, 1, 1, 1, 27, 2, 1, ((1 + (18 + 12)) + 9) + (27 * 4));
    Window_FillTilemap(&param0->unk_200, 15);
    Window_DrawStandardFrame(&param0->unk_200, 1, 1 + (18 + 12), 3);
    Window_Add(param0->unk_00, &param0->unk_210, 1, 2, 16, 28, 2, 1, (((1 + (18 + 12)) + 9) + (27 * 4)) + (27 * 2));
    Window_FillTilemap(&param0->unk_210, 0);
    Window_Add(param0->unk_00, &param0->unk_220, 1, 1, 5, 20, 8, 1, ((((1 + (18 + 12)) + 9) + (27 * 4)) + (27 * 2)) + (28 * 2));
    Window_FillTilemap(&param0->unk_220, 15);
    Window_DrawStandardFrame(&param0->unk_220, 1, 1 + (18 + 12), 3);
    Window_Add(param0->unk_00, &param0->unk_230, 1, 23, 5, 7, 5, 1, (((((1 + (18 + 12)) + 9) + (27 * 4)) + (27 * 2)) + (28 * 2)) + (20 * 8));
    Window_FillTilemap(&param0->unk_230, 15);
}

static void WiFiCommApp_FreeWindows(WiFiCommAppGraphics *param0, u32 heapID)
{
    WiFiCommApp_ClearMessage(param0);

    Window_EraseMessageBox(&param0->unk_1F0, 0);
    Window_Remove(&param0->unk_1F0);
    Window_EraseStandardFrame(&param0->unk_200, 0);
    Window_Remove(&param0->unk_200);
    Window_Remove(&param0->unk_210);
    Window_EraseStandardFrame(&param0->unk_220, 0);
    Window_Remove(&param0->unk_220);
    Window_EraseStandardFrame(&param0->unk_230, 0);
    Window_Remove(&param0->unk_230);

    if (param0->unk_240 != NULL) {
        Menu_DestroyForExit(param0->unk_240, heapID);
    }
}

static void WiFiCommApp_InitText(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    param0->unk_04 = StringTemplate_Default(heapID);
    param0->unk_08 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0674, heapID);
    param0->unk_0C = String_Init(256, heapID);
    param0->unk_10 = String_Init(256, heapID);
    param0->unk_14 = 0xff;
    param0->unk_16 = Options_TextFrameDelay(SaveData_GetOptions(param1->saveData));
}

static void WiFiCommApp_FreeText(WiFiCommAppGraphics *param0)
{
    String_Free(param0->unk_10);
    String_Free(param0->unk_0C);
    MessageLoader_Free(param0->unk_08);
    StringTemplate_Free(param0->unk_04);
}

static void WiFiCommApp_DrawActivityHeader(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    switch (param1->appType) {
    case 0:
        break;
    case 1:
        StringTemplate_SetPlazaMinigameName(param0->unk_04, 0, WiFiPlazaLobbyActivity_00);
        break;
    case 2:
        StringTemplate_SetPlazaMinigameName(param0->unk_04, 0, WiFiPlazaLobbyActivity_01);
        break;
    case 3:
        StringTemplate_SetPlazaMinigameName(param0->unk_04, 0, WiFiPlazaLobbyActivity_02);
        break;
    }

    MessageLoader_GetString(param0->unk_08, sWiFiCommAppActivityMessageIds[param1->appType], param0->unk_10);
    StringTemplate_Format(param0->unk_04, param0->unk_0C, param0->unk_10);
    Text_AddPrinterWithParamsAndColor(&param0->unk_200, FONT_SYSTEM, param0->unk_0C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(&param0->unk_200);
    Window_ScheduleCopyToVRAM(&param0->unk_220);
    MessageLoader_GetString(param0->unk_08, 128, param0->unk_0C);
    Text_AddPrinterWithParamsAndColor(&param0->unk_210, FONT_SYSTEM, param0->unk_0C, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    Window_ScheduleCopyToVRAM(&param0->unk_210);
    Window_ScheduleCopyToVRAM(&param0->unk_1F0);
}

static void WiFiCommApp_InitSprites(WiFiCommAppGraphics *param0, u32 heapID)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 31, 0, 126, 0, 31, heapID);

    {
        CharTransferTemplate v1 = {
            4, 128 * 1024, 16 * 1024, 0
        };

        v1.heapID = heapID;
        CharTransfer_InitWithVramModes(&v1, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K);
    }

    PlttTransfer_Init(4, heapID);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);

    param0->unk_18 = SpriteList_InitRendering(4, &param0->unk_1C, heapID);

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_1A8[v0] = SpriteResourceCollection_New(4, v0, heapID);
    }

    param0->unk_1B8 = WiFi2DCharObjectManager_New(4, heapID);
    param0->unk_1BC = WiFi2DCharRenderer_New(param0->unk_18, NULL, 4, NNS_G2D_VRAM_TYPE_2DMAIN, heapID);
}

static void WiFiCommApp_FreeSprites(WiFiCommAppGraphics *param0)
{
    int v0;

    WiFi2DCharRenderer_Free(param0->unk_1BC);
    WiFi2DCharObjectManager_Free(param0->unk_1B8);

    SpriteList_Delete(param0->unk_18);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_1A8[v0]);
    }

    CharTransfer_Free();
    PlttTransfer_Free();
    RenderOam_Free();
}

static void WiFiCommApp_ShowMessage(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 param2, u32 heapID)
{
    WiFiCommApp_ShowMessageWithDelay(param0, param1, param2, 0, heapID);
}

static void WiFiCommApp_ShowMessageWithDelay(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, u32 param2, u8 param3, u32 heapID)
{
    String *v0;
    int v1;

    if (param0->unk_14 != 0xff) {
        if (Text_IsPrinterActive(param0->unk_14) != 0) {
            Text_RemovePrinter(param0->unk_14);
            param0->unk_14 = 0xff;
        }
    }

    Window_FillTilemap(&param0->unk_1F0, 15);
    v0 = String_Init(256, heapID);

    MessageLoader_GetString(param0->unk_08, param2, v0);
    StringTemplate_Format(param0->unk_04, param0->unk_0C, v0);

    param0->unk_14 = Text_AddPrinterWithParamsAndColor(&param0->unk_1F0, FONT_MESSAGE, param0->unk_0C, 0, 0, param0->unk_16, TEXT_COLOR(1, 2, 15), NULL);

    Window_ScheduleCopyToVRAM(&param0->unk_1F0);
    String_Free(v0);

    v1 = Options_Frame(SaveData_GetOptions(param1->saveData));

    LoadMessageBoxGraphics(param0->unk_00, BG_LAYER_MAIN_1, 1, 2, v1, heapID);

    param0->unk_15 = param3;
}

static BOOL WiFiCommApp_IsMessageDone(WiFiCommAppGraphics *param0)
{
    if (param0->unk_14 == 0xff) {
        if (param0->unk_15 > 0) {
            param0->unk_15--;
            return 0;
        }
    } else {
        if (Text_IsPrinterActive(param0->unk_14) == 0) {
            if (param0->unk_14 != 0xff) {
                param0->unk_14 = 0xff;
            }
        }
    }

    if ((param0->unk_14 == 0xff) && (param0->unk_15 == 0)) {
        return 1;
    }

    return 0;
}

static void WiFiCommApp_ClearMessage(WiFiCommAppGraphics *param0)
{
    if (param0->unk_14 != 0xff) {
        if (Text_IsPrinterActive(param0->unk_14) != 0) {
            Text_RemovePrinter(param0->unk_14);
        }

        param0->unk_14 = 0xff;
    }

    Window_FillTilemap(&param0->unk_1F0, 15);
    Window_ScheduleCopyToVRAM(&param0->unk_1F0);

    param0->unk_15 = 0;
}

static void WiFiCommApp_ShowPlayerJoinPrompt(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, u32 heapID)
{
    String *v0 = String_Init(256, heapID);
    String *v1 = String_Init(256, heapID);

    WiFiCommApp_SetTemplatePlayerName(param0, param1, param2, 0, heapID);
    WiFiCommApp_SetTemplatePlayerId(param0, param1, param2, 1, heapID);

    MessageLoader_GetString(param0->unk_08, 131, v0);
    StringTemplate_Format(param0->unk_04, v1, v0);

    Window_FillTilemap(&param0->unk_230, 15);
    Text_AddPrinterWithParamsAndColor(&param0->unk_230, FONT_SYSTEM, v1, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_DrawStandardFrame(&param0->unk_230, 1, 1 + (18 + 12), 3);
    Window_ScheduleCopyToVRAM(&param0->unk_230);

    String_Free(v0);
    String_Free(v1);
}

static void WiFiCommApp_ClearPlayerJoinPrompt(WiFiCommAppGraphics *param0)
{
    Window_EraseStandardFrame(&param0->unk_230, 1);
    Window_ClearAndScheduleCopyToVRAM(&param0->unk_230);
}

static void WiFiCommApp_DrawAllPlayerRows(WiFiCommApp *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;
    int v1 = 4;

    if (CommInfo_IsInitialized() == 0) {
        return;
    }

    for (v0 = 0; v0 < v1; v0++) {
        if ((v0 == 0) && (CommInfo_HasPlayerData(v0) == 1)) {
            WiFiCommApp_DrawPlayerRow(param0, &param0->unk_30, param1, v0, heapID);
        } else {
            if (CommInfo_IsDataRead(v0) == 1) {
                WiFiCommApp_DrawPlayerRow(param0, &param0->unk_30, param1, v0, heapID);
            } else {
                WiFiCommApp_ClearPlayerRow(&param0->unk_30, param1, v0, heapID);
            }
        }
    }
}

static void WiFiCommApp_DrawPlayerRow(WiFiCommApp *param0, WiFiCommAppGraphics *param1, const WiFiCommAppArgs *param2, int param3, u32 heapID)
{
    String *v0;
    String *v1;
    u8 v2;
    u8 v3;

    v0 = String_Init(256, heapID);
    v1 = String_Init(256, heapID);

    WiFiCommApp_SetTemplatePlayerName(param1, param2, param3, 0, heapID);

    MessageLoader_GetString(param1->unk_08, 129, v0);
    StringTemplate_Format(param1->unk_04, v1, v0);
    Window_FillRectWithColor(&param1->unk_220, 15, 0, param3 * (2 * 8), 20 * 8, 2 * 8);
    Text_AddPrinterWithParamsAndColor(&param1->unk_220, FONT_SYSTEM, v1, 0, param3 * (2 * 8), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);

    WiFiCommApp_SetTemplatePlayerId(param1, param2, param3, 0, heapID);

    MessageLoader_GetString(param1->unk_08, 130, v0);
    StringTemplate_Format(param1->unk_04, v1, v0);
    Text_AddPrinterWithParamsAndColor(&param1->unk_220, FONT_SYSTEM, v1, 72, param3 * (2 * 8), TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 15), NULL);
    Window_ScheduleCopyToVRAM(&param1->unk_220);

    if (param3 == CommSys_CurNetId()) {
        if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled) {
            v2 = 2;
        } else {
            v2 = 1;
        }

        v3 = 0;
    } else {
        if (param0->unk_00.unk_20[param3]) {
            v2 = 2;
        } else {
            v2 = 1;
        }
    }

    Bg_CopyToTilemapRect(param1->unk_00, 2, 18, 5 + (param3 * 2), 2, 2, param1->unk_248->rawData, v2 * 2, 0, param1->unk_248->screenWidth / 8, param1->unk_248->screenHeight / 8);
    Bg_ChangeTilemapRectPalette(param1->unk_00, 2, 18, 5 + (param3 * 2), 2, 2, 5);
    Bg_ScheduleTilemapTransfer(param1->unk_00, 2);
    String_Free(v0);
    String_Free(v1);
}

static void WiFiCommApp_ClearPlayerRow(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, u32 heapID)
{
    Window_FillRectWithColor(&param0->unk_220, 15, 0, param2 * (2 * 8), 20 * 8, 2 * 8);
    Bg_CopyToTilemapRect(param0->unk_00, 2, 18, 5 + param2 * 2, 2, 2, param0->unk_248->rawData, 0 * 2, 0, param0->unk_248->screenWidth / 8, param0->unk_248->screenHeight / 8);
    Bg_ScheduleTilemapTransfer(param0->unk_00, 2);
    Window_ScheduleCopyToVRAM(&param0->unk_220);
}

static void WiFiCommApp_SetTemplatePlayerName(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, int param3, u32 heapID)
{
    TrainerInfo *v0 = CommInfo_TrainerInfo(param2);
    StringTemplate_SetPlayerName(param0->unk_04, param3, v0);
}

static void WiFiCommApp_SetTemplatePlayerId(WiFiCommAppGraphics *param0, const WiFiCommAppArgs *param1, int param2, int param3, u32 heapID)
{
    TrainerInfo *v0;
    u16 v1;

    v0 = CommInfo_TrainerInfo(param2);
    v1 = TrainerInfo_ID_LowHalf(v0);

    StringTemplate_SetNumber(param0->unk_04, param3, v1, 5, 2, 1);
}

static void WiFiCommApp_AnimateSelectionPalette(WiFiCommAppGraphics *param0)
{
    if (param0->unk_258 <= 0) {
        WiFiCommApp_ApplySelectionPalette(param0, param0->unk_25A);
        param0->unk_258 = 3;
        param0->unk_25A = (param0->unk_25A + 1) % 18;
    } else {
        param0->unk_258--;
    }
}

static void WiFiCommApp_ApplySelectionPalette(WiFiCommAppGraphics *param0, u32 param1)
{
    BOOL v0;
    u16 *v1;
    u32 v2 = sWiFiCommAppPaletteAnimFrames[param1];
    v1 = param0->unk_254->pRawData;
    v0 = VramTransfer_Request(NNS_GFD_DST_2D_BG_PLTT_MAIN, 0 * 32, &v1[v2 * 16], 32);

    GF_ASSERT(v0);
}

static BOOL WiFiCommApp_ToggleVoiceChat(WiFiCommApp *param0, u32 heapID)
{
    param0->unk_00.unk_00->ownStatus.voiceChatEnabledBackup = 1 - param0->unk_00.unk_00->ownStatus.voiceChatEnabledBackup;
    param0->unk_00.unk_00->ownStatus.voiceChatEnabled = param0->unk_00.unk_00->ownStatus.voiceChatEnabledBackup;

    NintendoWFC_SetVoiceChatEnabled(param0->unk_00.unk_00->ownStatus.voiceChatEnabled);
    NintendoWFC_SetStatusData(&(param0->unk_00.unk_00->ownStatus), sizeof(WFCTrainerInfo));

    if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
        WiFiCommApp_EnableVoiceChat(param0);
    } else {
        WiFiCommApp_DisableVoiceChat(param0);
    }

    return param0->unk_00.unk_00->ownStatus.voiceChatEnabledBackup;
}

static void WiFiCommApp_CheckForDisconnect(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 param2)
{
    BOOL v0;
    BOOL v1;
    BOOL v2;

    if (param0->unk_00.unk_04) {
        if ((param0->unk_00.unk_05 == 27) || (param0->unk_00.unk_05 == 28) || (param0->unk_00.unk_05 == 29)) {
            return;
        }

        if (CommManager_GetMatchmakingState() <= 2) {
            if ((WiFiCommApp_GetConnectedPlayerCount(param0) <= 1) && (WiFiCommApp_HasConnectedPlayers(param0) == 0)) {
                return;
            }
        }
    } else {
        if ((param0->unk_00.unk_05 == 15) || (param0->unk_00.unk_05 == 16) || (param0->unk_00.unk_05 == 17) || (param0->unk_00.unk_05 == 7) || (param0->unk_00.unk_05 == 6)) {
            return;
        }
    }

    v2 = WiFiCommApp_IsMatchmakingTimerExpired(param0);
    v0 = WiFiCommApp_ProcessDisconnects(param0);

    if (WiFiCommApp_GetConnectedPlayerCount(param0) > CommSys_ConnectedCount()) {
        v1 = 1;
    } else {
        v1 = 0;
    }

    if ((CommManager_GetMatchmakingState() >= 3) || (CommManager_CheckWifiError()) || CommManager_GetDisconnectedWifi() || (CommSys_IsPlayerConnected(0) == 0) || (WiFiCommApp_HasConnectedPlayers(param0) == 0) || (v1 == 1) || (v2 == 1) || (v0 == 1)) {
        if (param0->unk_00.unk_04) {
            param0->unk_00.unk_05 = 27;
        } else {
            param0->unk_00.unk_05 = 15;
        }
    }
}

static void WiFiCommApp_CheckClientDisconnect(WiFiCommApp *param0)
{
    if ((CommManager_GetMatchmakingState() > 3) || CommManager_GetDisconnectedWifi() || (CommManager_CheckWifiError())) {
        param0->unk_00.unk_05 = 15;
    }
}

static BOOL WiFiCommApp_HasConnectedPlayers(const WiFiCommApp *param0)
{
    if (CommSys_ConnectedCount() > 0) {
        return 1;
    }

    return 0;
}

static BOOL WiFiCommApp_StartWifiActivity(u32 param0, u32 param1)
{
    BOOL v0 = CommManager_StartWifiBattle(param0);

    if (v0 == 1) {
        switch (param1) {
        case 0:
            CommManager_SetState_WifiPoffin();
            break;
        case 1:
        case 2:
        case 3:
            CommManager_SetState_WifiClub();
            break;
        }
    }

    return v0;
}

static void WiFiCommApp_SetCommStateForActivity(WiFiCommApp *param0, const WiFiCommAppArgs *param1)
{
    switch (param1->appType) {
    case 0:
        param0->unk_00.unk_00->ownStatus.commState = 18;
        break;
    case 1:
        param0->unk_00.unk_00->ownStatus.commState = 22;
        break;
    case 2:
        param0->unk_00.unk_00->ownStatus.commState = 24;
        break;
    case 3:
        param0->unk_00.unk_00->ownStatus.commState = 26;
        break;
    }

    NintendoWFC_SetStatusData(&(param0->unk_00.unk_00->ownStatus), sizeof(WFCTrainerInfo));
}

static BOOL WiFiCommApp_StartVoiceChat(WiFiCommApp *param0)
{
    if (param0->unk_00.unk_11 == 1) {
        return 0;
    }

    if (WiFiCommApp_HasConnectedPlayers(param0) == 1) {
        NintendoWFC_StartVoiceChat(HEAP_ID_97);
        param0->unk_00.unk_11 = 1;
        return 1;
    }

    return 0;
}

static BOOL WiFiCommApp_StopVoiceChat(WiFiCommApp *param0)
{
    if (param0->unk_00.unk_11 == 0) {
        return 0;
    }

    NintendoWFC_TerminateVoiceChat();
    param0->unk_00.unk_11 = 0;

    return 1;
}

static void WiFiCommApp_EnableVoiceChat(WiFiCommApp *param0)
{
    if (WiFiCommApp_StartVoiceChat(param0)) {
        Sound_AdjustVolumeForVoiceChat(Sound_GetCurrentBGM());
    }
}

static void WiFiCommApp_DisableVoiceChat(WiFiCommApp *param0)
{
    if (WiFiCommApp_StopVoiceChat(param0)) {
        Sound_SetInitialVolumeForHandle(SOUND_HANDLE_TYPE_FIELD_BGM, 120);
    }
}

static int WiFiCommApp_GetConnectedPlayerCount(WiFiCommApp *param0)
{
    if (param0->unk_00.unk_04) {
        return CommInfo_CountReceived();
    } else {
        return CommInfo_CountReceived();
    }
}

static BOOL WiFiCommApp_ProcessReceivedPlayerData(WiFiCommApp *param0, u32 heapID)
{
    int v0;
    int v1;
    BOOL v2 = 1;

    v1 = CommSys_CurNetId();
    v1--;

    for (v0 = v1; v0 >= 0; v0--) {
        if (CommInfo_HasNewData(v0) == 1) {
            WiFiCommApp_AddPlayerActor(param0, v0, heapID);
        } else if (CommInfo_IsDataRead(v0) == 0) {
            v2 = 0;
        }
    }

    return v2;
}

static void WiFiCommApp_ClearNewPlayers(WiFiCommApp *param0)
{
    int v0;
    WiFiCommPlayerStatus v1;
    BOOL v2;

    v1.unk_04 = 0;

    for (v0 = 1; v0 < 4; v0++) {
        if (CommInfo_HasNewData(v0) == 1) {
            v1.unk_00 = v0;
            v2 = CommSys_SendData(22, &v1, sizeof(WiFiCommPlayerStatus));
            GF_ASSERT(v2 == 1);
            CommInfo_InitPlayer(v0);
        }
    }
}

static void WiFiCommApp_ClearKnownPlayers(WiFiCommApp *param0)
{
    int v0;
    WiFiCommPlayerStatus v1;
    BOOL v2;

    v1.unk_04 = 0;

    for (v0 = 1; v0 < 4; v0++) {
        if (CommInfo_HasPlayerData(v0) == 1) {
            v1.unk_00 = v0;
            v2 = CommSys_SendData(22, &v1, sizeof(WiFiCommPlayerStatus));
            GF_ASSERT(v2 == 1);
            CommInfo_InitPlayer(v0);
        }
    }
}

static void WiFiCommApp_InstallConnectionCallback(WiFiCommApp *param0)
{
    NintendoWFC_SetConnectionClosedCB(WiFiCommApp_OnConnectionClosed, param0);
}

static void WiFiCommApp_RemoveConnectionCallback(WiFiCommApp *param0)
{
    NintendoWFC_SetConnectionClosedCB(NULL, NULL);
}

static BOOL WiFiCommApp_ProcessDisconnects(WiFiCommApp *param0)
{
    int v0;
    BOOL v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_00.unk_14[v0] == 1) {
            if (CommInfo_IsDataRead(param0->unk_00.unk_18[v0]) == 1) {
                v1 = 1;
            }

            param0->unk_00.unk_14[v0] = 0;
            param0->unk_00.unk_18[v0] = 0;
        }
    }

    return v1;
}

static void WiFiCommApp_OnConnectionClosed(u16 param0, void *param1)
{
    WiFiCommApp *v0 = param1;

    v0->unk_00.unk_14[param0] = 1;
    v0->unk_00.unk_18[param0] = param0;
}

static BOOL WiFiCommApp_HasVoiceChatChanged(WiFiCommApp *param0)
{
    int v0;
    BOOL v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_00.unk_1C[v0] != param0->unk_00.unk_20[v0]) {
            v1 = 1;
        }

        param0->unk_00.unk_1C[v0] = param0->unk_00.unk_20[v0];
    }

    if (param0->unk_00.unk_24) {
        param0->unk_00.unk_24 = 0;
        v1 = 1;
    }

    return v1;
}

static void WiFiCommApp_RequestPlayerRedraw(WiFiCommApp *param0)
{
    param0->unk_00.unk_24 = 1;
}

static void WiFiCommApp_AddPlayerActor(WiFiCommApp *param0, u32 param1, u32 heapID)
{
    if (CommInfo_IsDataRead(param1) == 0) {
        CommInfo_MarkDataRead(param1);

        param0->unk_00.unk_25 = param1;

        WiFiCommApp_CreatePlayerActor(param0, param1, heapID);
        WiFiCommApp_RequestPlayerRedraw(param0);
    }
}

static void WiFiCommApp_CreatePlayerActor(WiFiCommApp *param0, u32 param1, u32 heapID)
{
    WiFiMenuAppRect v0;
    TrainerInfo *v1;

    if (param0->unk_30.unk_1C0[param1].unk_00 != NULL) {
        return;
    }

    v0 = sWiFiCommAppActorSpawnRects[param1];

    if (param1 != CommSys_CurNetId()) {
        v1 = CommInfo_TrainerInfo(param1);
        GF_ASSERT(v1 != NULL);
        v0.unk_0A = TrainerInfo_Appearance(v1);
    } else {
        if (param0->unk_00.unk_00->ownStatus.gender == 0) {
            v0.unk_0A = 0x0;
        } else {
            v0.unk_0A = 0x61;
        }
    }

    param0->unk_30.unk_1C0[param1].unk_00 = WiFi2DCharObjectManager_AddObject(param0->unk_30.unk_1B8, &v0);

    if (WiFi2DCharRenderer_IsSpeciesLoaded(param0->unk_30.unk_1BC, v0.unk_0A) == 0) {
        WiFi2DCharRenderer_LoadSpecies(param0->unk_30.unk_1BC, v0.unk_0A, 2, heapID);
    }

    param0->unk_30.unk_1C0[param1].unk_04 = WiFi2DCharRenderer_AddObject(param0->unk_30.unk_1BC, param0->unk_30.unk_1C0[param1].unk_00, 0, heapID);
    WiFi2DCharRenderer_SetObjectVisible(param0->unk_30.unk_1C0[param1].unk_04, 0);
    param0->unk_30.unk_1C0[param1].unk_08++;
}

static void WiFiCommApp_UpdateActors(WiFiCommApp *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        sWiFiCommAppActorRenderFuncs[param0->unk_30.unk_1C0[v0].unk_08](param0, &param0->unk_30.unk_1C0[v0]);
    }

    WiFi2DCharObjectManager_Update(param0->unk_30.unk_1B8);
    WiFi2DCharRenderer_UpdateAll(param0->unk_30.unk_1BC);
}

static void WiFiCommApp_FreePlayerActors(WiFiCommApp *param0)
{
    WiFi2DCharRenderer_UnloadAllSpecies(param0->unk_30.unk_1BC);
    memset(param0->unk_30.unk_1C0, 0, sizeof(WiFiCommActorRender) * 4);
}

static void WiFiCommApp_SendPlayerResetStatus(WiFiCommApp *param0, u32 param1)
{
    WiFiCommPlayerStatus v0;
    BOOL v1;

    v0.unk_00 = param1;
    v0.unk_04 = 2;
    v1 = CommSys_SendData(22, &v0, sizeof(WiFiCommPlayerStatus));

    GF_ASSERT(v1 == 1);
}

static void WiFiCommApp_ResetStalePlayers(WiFiCommApp *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_00.unk_25 + 1 < v0) {
            if (CommInfo_HasNewData(v0) == 1) {
                WiFiCommApp_SendPlayerResetStatus(param0, v0);
                CommInfo_InitPlayer(v0);
            }
        }
    }
}

static void WiFiCommApp_ProcessJoinedPlayers(WiFiCommApp *param0, u32 heapID)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_00.unk_28[v0] == 1) {
            if (CommInfo_HasPlayerData(v0) == 1) {
                WiFiCommApp_AddPlayerActor(param0, v0, heapID);
                param0->unk_00.unk_28[v0] = 0;
                param0->unk_00.unk_12 = 1;
            }
        }
    }
}

static void WiFiCommApp_ShowWaitDial(WiFiCommApp *param0)
{
    GF_ASSERT(param0->unk_30.unk_24C == NULL);
    param0->unk_30.unk_24C = Window_AddWaitDial(&param0->unk_30.unk_1F0, 1);
}

static void WiFiCommApp_HideWaitDial(WiFiCommApp *param0, const WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;

    if (param0->unk_30.unk_24C == NULL) {
        return;
    }

    DestroyWaitDial(param0->unk_30.unk_24C);

    param0->unk_30.unk_24C = NULL;
    v0 = Options_Frame(SaveData_GetOptions(param1->saveData));

    LoadMessageBoxGraphics(param0->unk_30.unk_00, 1, 1, 2, v0, heapID);
}

static void WiFiCommApp_ActorRenderStep0(WiFiCommApp *param0, WiFiCommActorRender *param1)
{
    return;
}

static void WiFiCommApp_ActorRenderStep1(WiFiCommApp *param0, WiFiCommActorRender *param1)
{
    u32 v0;

    WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 0);
    WiFi2DCharRenderer_ResetObjectAnim(param1->unk_04);
    WiFi2DCharRenderer_SetObjectVisible(param1->unk_04, 1);

    param1->unk_08 = 2;
    v0 = WiFi2DCharObject_GetField(param1->unk_00, 6);
    param1->unk_0A = 16 + sWiFiCommAppActorSpawnOffsets[v0];
}

static void WiFiCommApp_ActorRenderStep2(WiFiCommApp *param0, WiFiCommActorRender *param1)
{
    WiFi2DCharRenderer_UpdateObjectAnim(param1->unk_04);

    param1->unk_0A--;

    if (param1->unk_0A <= 0) {
        WiFi2DCharRenderer_RefreshObject(param1->unk_04);
        WiFi2DCharRenderer_SetObjectEnabled(param1->unk_04, 1);
        param1->unk_08 = 3;
    }
}

static void WiFiCommApp_ActorRenderStep3(WiFiCommApp *param0, WiFiCommActorRender *param1)
{
    return;
}

static void WiFiCommApp_BroadcastVoiceChatFlags(WiFiCommApp *param0)
{
    int v0;
    int v1;
    BOOL v2 = 0;
    int v3;
    int v4;
    WiFiCommVoiceChatFlags v5;

    if (CommInfo_IsInitialized() == 0) {
        return;
    }

    v1 = CommInfo_CountReceived();

    if (CommInfo_IsReceivingData()) {
        if (!CommSys_IsCmdQueuedServer(5)) {
            v2 = 1;
        }
    }

    for (v0 = 0; v0 < v1; v0++) {
        if (v0 == 0) {
            v4 = param0->unk_00.unk_00->ownStatus.voiceChatEnabled;
        } else {
            v3 = CommInfo_FindFriendSlotForNetId(v0);
            GF_ASSERT(v3 != 32);
            v4 = param0->unk_00.unk_00->friendStatuses[v3].voiceChatEnabled;
        }

        if (param0->unk_00.unk_20[v0] != v4) {
            v2 = 1;
        }

        param0->unk_00.unk_20[v0] = v4;
    }

    if (v2 == 1) {
        BOOL v6;

        memcpy(v5.unk_00, param0->unk_00.unk_20, sizeof(u8) * 4);
        CommSys_SendData(24, &v5, sizeof(WiFiCommVoiceChatFlags));
    }
}

static BOOL WiFiCommApp_IsTimingSync13Complete(WiFiCommApp *param0)
{
    if (CommTiming_IsSyncState(13)) {
        return 1;
    }

    return 0;
}

static void WiFiCommApp_RecordJournalWifiClub(WiFiCommAppArgs *param0, u32 heapID)
{
    void *journalEntryOnlineEvent;
    JournalEntry *journalEntry;
    WFCTrainerInfo *v2;

    journalEntry = SaveData_GetJournal(param0->saveData);
    journalEntryOnlineEvent = JournalEntry_CreateEventMisc(heapID, ONLINE_EVENT_WIFI_CLUB);

    JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
}

static void WiFiCommApp_StartMatchmakingTimer(WiFiCommApp *param0)
{
    param0->unk_00.unk_10 = 1;
    param0->unk_00.unk_0C = (60 * 30);
}

static BOOL WiFiCommApp_IsMatchmakingTimerExpired(WiFiCommApp *param0)
{
    if (param0->unk_00.unk_10 == 0) {
        return 0;
    }

    if (param0->unk_00.unk_0C > 0) {
        param0->unk_00.unk_0C--;
        return 0;
    }

    return 1;
}

static BOOL WiFiCommApp_HostState0(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
        WiFiCommApp_EnableVoiceChat(param0);
    }

    NintendoWFC_SetDisconnectIfAlone(0);
    CommManager_SetErrorHandling(0, 1);
    WiFiCommApp_CreatePlayerActor(param0, CommSys_CurNetId(), heapID);

    param0->unk_00.unk_05 = 1;

    return 0;
}

static BOOL WiFiCommApp_HostState1(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 107, heapID);

    param0->unk_00.unk_05 = 2;
    return 0;
}

static BOOL WiFiCommApp_HostState2(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    if (WiFiCommApp_HasConnectedPlayers(param0) == 1) {
        int v1;
        WiFiCommPlayerStatus v2;
        BOOL v3;

        v1 = CommInfo_NewNetworkId();

        if (v1 != 0xff) {
            if (param0->unk_00.unk_06 != 0) {
                if (CommInfo_FindFriendSlotForNetId(v1) == 32) {
                    v2.unk_00 = v1;
                    v2.unk_04 = 0;

                    CommInfo_InitPlayer(v1);

                    v3 = CommSys_SendData(22, &v2, sizeof(WiFiCommPlayerStatus));
                    GF_ASSERT(v3 == 1);
                } else {
                    param0->unk_00.unk_06 = v1;
                }
            }
        }
    }

    do {
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

            if (WiFiCommApp_HasConnectedPlayers(param0) == 0) {
                param0->unk_00.unk_05 = 6;
                break;
            } else {
                if (param1->minPlayers <= WiFiCommApp_GetConnectedPlayerCount(param0)) {
                    param0->unk_00.unk_05 = 8;
                    break;
                } else {
                    param0->unk_00.unk_05 = 6;
                    break;
                }
            }
        }

        if (gSystem.pressedKeys & PAD_BUTTON_B) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            param0->unk_00.unk_05 = 22;
            break;
        }

        if (param0->unk_00.unk_06 != 0xff) {
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            param0->unk_00.unk_05 = 3;
            break;
        }

        if (gSystem.pressedKeys & PAD_BUTTON_X) {
            param0->unk_00.unk_05 = 30;
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            break;
        }
    } while (0);

    return 0;
}

static BOOL WiFiCommApp_HostState3(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowPlayerJoinPrompt(&param0->unk_30, param1, param0->unk_00.unk_06, heapID);
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 108, heapID);

    param0->unk_00.unk_05 = 4;

    return 0;
}

static BOOL WiFiCommApp_HostState4(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoice(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, heapID);
    param0->unk_00.unk_05 = 5;

    return 0;
}

static BOOL WiFiCommApp_HostState5(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;
    WiFiCommPlayerStatus v1;
    BOOL v2;

    v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        v1.unk_00 = param0->unk_00.unk_06;

        if (v0 == 0) {
            v1.unk_04 = 1;

            WiFiCommApp_AddPlayerActor(param0, param0->unk_00.unk_06, heapID);

            if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
                WiFiCommApp_StopVoiceChat(param0);
                WiFiCommApp_EnableVoiceChat(param0);
            }

            if (param1->requiredPlayers <= WiFiCommApp_GetConnectedPlayerCount(param0)) {
                param0->unk_00.unk_05 = 8;
            } else {
                param0->unk_00.unk_05 = 1;
            }
        } else {
            v1.unk_04 = 0;

            CommInfo_InitPlayer(param0->unk_00.unk_06);

            param0->unk_00.unk_05 = 1;
        }

        v2 = CommSys_SendData(22, &v1, sizeof(WiFiCommPlayerStatus));
        GF_ASSERT(v2 == 1);

        param0->unk_00.unk_06 = 0xff;
        WiFiCommApp_ClearPlayerJoinPrompt(&param0->unk_30);
        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState6(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 119, heapID);

    param0->unk_00.unk_05 = 7;
    return 0;
}

static BOOL WiFiCommApp_HostState7(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_00.unk_05 = 19;
    return 0;
}

static BOOL WiFiCommApp_HostState8(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 111, heapID);

    param0->unk_00.unk_05 = 9;
    return 0;
}

static BOOL WiFiCommApp_HostState9(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoice(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, heapID);
    param0->unk_00.unk_05 = 10;

    return 0;
}

static BOOL WiFiCommApp_HostState10(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            param0->unk_00.unk_05 = 11;
        } else {
            if (param1->requiredPlayers <= WiFiCommApp_GetConnectedPlayerCount(param0)) {
                param0->unk_00.unk_05 = 19;
            } else {
                param0->unk_00.unk_05 = 1;
            }
        }

        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState11(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    param0->unk_00.unk_08 = 30;

    WiFiCommApp_ClearNewPlayers(param0);
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 102, heapID);
    WiFiCommApp_ShowWaitDial(param0);
    WiFiCommApp_StartMatchmakingTimer(param0);

    param0->unk_00.unk_05 = 12;
    NintendoWFC_ResetMatchmakingCancelState();

    return 0;
}

static BOOL WiFiCommApp_HostState12(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;

    if (CommSys_ConnectedCount() != CommInfo_CountReceived()) {
        WiFiCommApp_ClearNewPlayers(param0);
        return 0;
    }

    v0 = NintendoWFC_CancelMatchmaking();

    if (v0 == 0) {
        return 0;
    }

    NintendoWFC_SetDisconnectIfAlone(1);
    param0->unk_00.unk_05 = 13;

    return 0;
}

static BOOL WiFiCommApp_HostState13(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    if (param0->unk_00.unk_08 == 0) {
        v0 = CommSys_SendData(23, NULL, 0);

        if (v0) {
            param0->unk_00.unk_05 = 14;
        }
    } else {
        param0->unk_00.unk_08--;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState14(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (CommTiming_IsSyncState(13)) {
        WiFiCommApp_SetCommStateForActivity(param0, param1);
        CommTool_ClearReceivedTempDataAllPlayers();
        CommTiming_StartSync(14);

        param0->unk_00.unk_05 = 15;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState15(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (CommTiming_IsSyncState(14)) {
        u16 v0 = param0->unk_00.unk_00->ownStatus.commState;
        BOOL v1;

        v1 = CommTool_SendTempData(CommSys_CurNetId(), &v0);

        if (v1 == 1) {
            param0->unk_00.unk_05 = 16;
        }
    }

    return 0;
}

static BOOL WiFiCommApp_HostState16(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;
    int v1;
    int v2;
    const u16 *v3;
    int v4;

    v1 = WiFiCommApp_GetConnectedPlayerCount(param0);
    v2 = CommSys_CurNetId();
    v4 = 0;

    for (v0 = 0; v0 < v1; v0++) {
        if (v2 != v0) {
            v3 = CommTool_GetReceivedTempData(v0);

            if (v3 != NULL) {
                if (v3[0] == param0->unk_00.unk_00->ownStatus.commState) {
                    v4++;
                } else {
                    param0->unk_00.unk_05 = 27;
                }
            }
        } else {
            v4++;
        }
    }

    if (v4 == v1) {
        param0->unk_00.unk_05 = 17;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState17(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    CommManager_SetErrorHandling(1, 1);
    CommTiming_StartSync(18);

    param0->unk_00.unk_05 = 18;

    return 0;
}

static BOOL WiFiCommApp_HostState18(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (CommTiming_IsSyncState(18)) {
        param0->unk_00.unk_07 = 1;

        WiFiCommApp_RecordJournalWifiClub(param1, heapID);
        WiFiCommApp_HideWaitDial(param0, param1, heapID);

        return 1;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState19(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 120, heapID);
    param0->unk_00.unk_05 = 20;

    return 0;
}

static BOOL WiFiCommApp_HostState20(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoiceWithCursorAt(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, 1, heapID);
    param0->unk_00.unk_05 = 21;

    return 0;
}

static BOOL WiFiCommApp_HostState21(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            param0->unk_00.unk_05 = 22;
        } else {
            if (WiFiCommApp_HasConnectedPlayers(param0)) {
                if (param1->requiredPlayers <= WiFiCommApp_GetConnectedPlayerCount(param0)) {
                    param0->unk_00.unk_05 = 8;
                } else {
                    param0->unk_00.unk_05 = 1;
                }
            } else {
                param0->unk_00.unk_05 = 1;
            }
        }

        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState22(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 121, heapID);

    param0->unk_00.unk_05 = 23;
    return 0;
}

static BOOL WiFiCommApp_HostState23(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoiceWithCursorAt(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, 1, heapID);
    param0->unk_00.unk_05 = 24;

    return 0;
}

static BOOL WiFiCommApp_HostState24(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            param0->unk_00.unk_05 = 25;
        } else {
            if (WiFiCommApp_HasConnectedPlayers(param0)) {
                if (param1->requiredPlayers <= WiFiCommApp_GetConnectedPlayerCount(param0)) {
                    param0->unk_00.unk_05 = 8;
                } else {
                    param0->unk_00.unk_05 = 1;
                }
            } else {
                param0->unk_00.unk_05 = 1;
            }
        }

        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_HostState25(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 122, heapID);

    param0->unk_00.unk_08 = 30;
    param0->unk_00.unk_05 = 26;

    return 0;
}

static BOOL WiFiCommApp_HostState26(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_00.unk_08--;

    if (param0->unk_00.unk_08 > 0) {
        return 0;
    }

    param0->unk_00.unk_07 = 0;

    CommManager_EndWifiMatch();
    WiFiCommApp_ClearKnownPlayers(param0);
    CommManager_SetState_LoginWifi();
    CommManager_SetErrorHandling(0, 1);

    return 1;
}

static BOOL WiFiCommApp_HostState27(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (param0->unk_30.unk_240 != NULL) {
        Menu_DestroyForExit(param0->unk_30.unk_240, heapID);
        param0->unk_30.unk_240 = NULL;
    }

    WiFiCommApp_ClearPlayerJoinPrompt(&param0->unk_30);
    WiFiCommApp_HideWaitDial(param0, param1, heapID);

    param0->unk_00.unk_05 = 28;
    return 0;
}

static BOOL WiFiCommApp_HostState28(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 118, heapID);
    param0->unk_00.unk_05 = 29;
    WiFiCommApp_ClearKnownPlayers(param0);

    return 0;
}

static BOOL WiFiCommApp_HostState29(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    CommManager_EndWifiMatch();
    CommManager_SetState_LoginWifi();
    WiFiCommApp_ClearKnownPlayers(param0);
    param0->unk_00.unk_07 = 0;
    CommManager_SetErrorHandling(0, 1);

    return 1;
}

static BOOL WiFiCommApp_HostState30(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    u32 v0;

    if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
        v0 = 125;
    } else {
        v0 = 124;
    }

    WiFiCommApp_ShowMessage(&param0->unk_30, param1, v0, heapID);

    param0->unk_00.unk_05 = 31;
    return 0;
}

static BOOL WiFiCommApp_HostState31(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoice(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, heapID);
    param0->unk_00.unk_05 = 32;

    return 0;
}

static BOOL WiFiCommApp_HostState32(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            WiFiCommApp_ToggleVoiceChat(param0, heapID);

            WiFiCommApp_RequestPlayerRedraw(param0);
        }

        param0->unk_00.unk_05 = 1;
        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState0(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    CommInfo_SendPlayerInfo();
    CommManager_SetErrorHandling(0, 1);
    param0->unk_00.unk_05 = 1;
    return 0;
}

static BOOL WiFiCommApp_ClientState1(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    if (CommSys_IsPlayerConnected(0) == 0) {
        param0->unk_00.unk_05 = 15;
    } else {
        if (CommInfo_IsDataRead(0)) {
            param0->unk_00.unk_05 = 2;
        }
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState2(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);
    WiFiCommApp_SetTemplatePlayerName(&param0->unk_30, param1, 0, 0, heapID);
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 114, heapID);
    WiFiCommApp_ShowWaitDial(param0);

    param0->unk_00.unk_05 = 3;

    return 0;
}

static BOOL WiFiCommApp_ClientState3(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    if (param0->unk_00.unk_13 != 0) {
        WiFiCommApp_HideWaitDial(param0, param1, heapID);

        switch (param0->unk_00.unk_13) {
        case 1:
            param0->unk_00.unk_05 = 4;
            break;
        case 2:
            param0->unk_00.unk_05 = 6;
            param0->unk_00.unk_2D = 116;
            break;
        case 3:
            param0->unk_00.unk_05 = 6;
            param0->unk_00.unk_2D = 132;

            break;
        }
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState4(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_SetTemplatePlayerName(&param0->unk_30, param1, 0, 0, heapID);
    WiFiCommApp_ShowMessageWithDelay(&param0->unk_30, param1, 115, 30, heapID);
    param0->unk_00.unk_05 = 5;
    WiFiCommApp_AddPlayerActor(param0, CommSys_CurNetId(), HEAP_ID_96);

    return 0;
}

static BOOL WiFiCommApp_ClientState5(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_00.unk_05 = 8;

    return 0;
}

static BOOL WiFiCommApp_ClientState6(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_SetTemplatePlayerName(&param0->unk_30, param1, 0, 0, heapID);
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, param0->unk_00.unk_2D, heapID);

    param0->unk_00.unk_05 = 7;

    CommManager_EndWifiMatch();
    CommManager_SetState_LoginWifi();

    return 0;
}

static BOOL WiFiCommApp_ClientState7(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_00.unk_07 = 0;
    CommManager_SetErrorHandling(0, 1);

    return 1;
}

static BOOL WiFiCommApp_ClientState8(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 123, heapID);
    WiFiCommApp_ShowWaitDial(param0);

    param0->unk_00.unk_05 = 9;

    if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
        WiFiCommApp_EnableVoiceChat(param0);
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState9(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);
    v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_00.unk_05 = 10;

    return 0;
}

static BOOL WiFiCommApp_ClientState10(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    if (param0->unk_00.unk_12) {
        param0->unk_00.unk_12 = 0;

        if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
            WiFiCommApp_StopVoiceChat(param0);
            WiFiCommApp_EnableVoiceChat(param0);
        }

        WiFiCommApp_RequestPlayerRedraw(param0);
    }

    if (WiFiCommApp_IsTimingSync13Complete(param0) == 1) {
        CommTool_ClearReceivedTempDataAllPlayers();
        CommTiming_StartSync(14);

        WiFiCommApp_HideWaitDial(param0, param1, heapID);
        WiFiCommApp_ShowMessage(&param0->unk_30, param1, 102, heapID);
        WiFiCommApp_StartMatchmakingTimer(param0);

        param0->unk_00.unk_08 = (10 * 30);
        WiFiCommApp_ShowWaitDial(param0);
        param0->unk_00.unk_05 = 11;
    } else {
        if (gSystem.pressedKeys & PAD_BUTTON_X) {
            WiFiCommApp_HideWaitDial(param0, param1, heapID);
            param0->unk_00.unk_05 = 18;
        }
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState11(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;

    if (CommTiming_IsSyncState(14)) {
        u16 v1 = param0->unk_00.unk_00->ownStatus.commState;
        BOOL v2;

        v0 = WiFiCommApp_GetConnectedPlayerCount(param0);

        if (CommSys_ConnectedCount() != v0) {
            param0->unk_00.unk_08--;

            if (param0->unk_00.unk_08 <= 0) {
                param0->unk_00.unk_05 = 15;
            }

            return 0;
        }

        v2 = CommTool_SendTempData(CommSys_CurNetId(), &v1);

        if (v2 == 1) {
            param0->unk_00.unk_05 = 12;
        }
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState12(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;
    int v1;
    int v2;
    const u16 *v3;
    int v4;

    v1 = WiFiCommApp_GetConnectedPlayerCount(param0);
    v2 = CommSys_CurNetId();
    v4 = 0;

    for (v0 = 0; v0 < v1; v0++) {
        if (v2 != v0) {
            v3 = CommTool_GetReceivedTempData(v0);

            if (v3 != NULL) {
                if (v3[0] == param0->unk_00.unk_00->ownStatus.commState) {
                    v4++;
                } else {
                    param0->unk_00.unk_05 = 15;
                }
            }
        } else {
            v4++;
        }
    }

    if (v4 == v1) {
        param0->unk_00.unk_05 = 13;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState13(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    CommManager_SetErrorHandling(1, 1);
    CommTiming_StartSync(18);

    param0->unk_00.unk_05 = 14;

    return 0;
}

static BOOL WiFiCommApp_ClientState14(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (CommTiming_IsSyncState(18)) {
        WiFiCommApp_HideWaitDial(param0, param1, heapID);
        param0->unk_00.unk_07 = 1;
        WiFiCommApp_RecordJournalWifiClub(param1, heapID);

        return 1;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState15(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (param0->unk_30.unk_240 != NULL) {
        Menu_DestroyForExit(param0->unk_30.unk_240, heapID);
        param0->unk_30.unk_240 = NULL;
    }

    WiFiCommApp_ClearPlayerJoinPrompt(&param0->unk_30);
    WiFiCommApp_HideWaitDial(param0, param1, heapID);

    param0->unk_00.unk_05 = 16;

    return 0;
}

static BOOL WiFiCommApp_ClientState16(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 118, heapID);

    param0->unk_00.unk_05 = 17;

    return 0;
}

static BOOL WiFiCommApp_ClientState17(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    CommManager_EndWifiMatch();
    CommManager_SetState_LoginWifi();

    param0->unk_00.unk_07 = 0;

    CommManager_SetErrorHandling(0, 1);

    return 1;
}

static BOOL WiFiCommApp_ClientState18(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    u32 v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    if (param0->unk_00.unk_00->ownStatus.voiceChatEnabled == 1) {
        v0 = 125;
    } else {
        v0 = 124;
    }

    WiFiCommApp_ShowMessage(&param0->unk_30, param1, v0, heapID);

    param0->unk_00.unk_05 = 19;
    return 0;
}

static BOOL WiFiCommApp_ClientState19(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    if (WiFiCommApp_IsTimingSync13Complete(param0) == 1) {
        param0->unk_00.unk_05 = 10;
        WiFiCommApp_ClearMessage(&param0->unk_30);
        return 0;
    }

    v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoice(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, heapID);
    param0->unk_00.unk_05 = 20;

    return 0;
}

static BOOL WiFiCommApp_ClientState20(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0;

    WiFiCommApp_ProcessReceivedPlayerData(param0, heapID);

    if (WiFiCommApp_IsTimingSync13Complete(param0) == 1) {
        param0->unk_00.unk_05 = 10;
        WiFiCommApp_ClearMessage(&param0->unk_30);
        Menu_DestroyForExit(param0->unk_30.unk_240, heapID);
        param0->unk_30.unk_240 = NULL;
        return 0;
    }

    v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            WiFiCommApp_ToggleVoiceChat(param0, heapID);

            WiFiCommApp_RequestPlayerRedraw(param0);
        }

        param0->unk_00.unk_05 = 8;
        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState21(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    param0->unk_00.unk_26 = CommInfo_FindFriendSlotForNetId(0);

    GF_ASSERT(param0->unk_00.unk_26 != 32);
    WiFiCommApp_SetTemplatePlayerName(&param0->unk_30, param1, 0, 0, heapID);

    CommManager_EndWifiMatch();
    param0->unk_00.unk_27 = 0;

    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 132, heapID);
    param0->unk_00.unk_05 = 22;

    return 0;
}

static BOOL WiFiCommApp_ClientState22(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    param0->unk_30.unk_240 = Menu_MakeYesNoChoice(param0->unk_30.unk_00, &sWiFiCommAppYesNoWindowTemplate, 0 + (24 * 2), 4, heapID);
    param0->unk_00.unk_05 = 23;

    return 0;
}

static BOOL WiFiCommApp_ClientState23(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    int v0 = Menu_ProcessInputAndHandleExit(param0->unk_30.unk_240, heapID);

    if (v0 != 0xffffffff) {
        if (v0 == 0) {
            param0->unk_00.unk_05 = 24;
        } else {
            param0->unk_00.unk_05 = 29;
        }

        param0->unk_30.unk_240 = NULL;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState24(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_ShowMessage(&param0->unk_30, param1, 17, heapID);
    WiFiCommApp_ShowWaitDial(param0);

    param0->unk_00.unk_08 = 90;
    param0->unk_00.unk_05 = 25;

    return 0;
}

static BOOL WiFiCommApp_ClientState25(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    BOOL v0;

    if (param0->unk_00.unk_08 > 0) {
        param0->unk_00.unk_08--;
        return 0;
    }

    v0 = WiFiCommApp_IsMessageDone(&param0->unk_30);

    if (v0 == 0) {
        return 0;
    }

    if (WiFiCommApp_StartWifiActivity(param0->unk_00.unk_26, param1->appType)) {
        param0->unk_00.unk_05 = 26;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState26(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    WiFiCommApp_CheckClientDisconnect(param0);

    if ((CommManager_GetMatchmakingState() == 1) && (CommSys_IsPlayerConnected(0) == 1)) {
        CommSys_SetRecvLimitEnabled(0);
        WiFiCommApp_HideWaitDial(param0, param1, heapID);
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, heapID);
        param0->unk_00.unk_05 = 27;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState27(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (IsScreenFadeDone()) {
        CommInfo_Init(param1->saveData, NULL);

        param0->unk_00.unk_27 = 1;

        {
            WiFiCommApp_FreePlayerActors(param0);
            WiFiCommApp_FreeAllGraphics(param0, heapID);

            memset(&param0->unk_30, 0, sizeof(WiFiCommAppGraphics));

            WiFiCommApp_InstallConnectionCallback(param0);
            WiFiCommApp_InitAllGraphics(param0, param1, heapID);
            NetworkIcon_Init();
        }

        {
            param0->unk_00.unk_12 = 0;
            param0->unk_00.unk_13 = 0;

            memset(param0->unk_00.unk_14, 0, sizeof(u8) * 4);
            memset(param0->unk_00.unk_18, 0, sizeof(u8) * 4);

            MI_CpuFill8(param0->unk_00.unk_1C, 1, sizeof(u8) * 4);
            MI_CpuFill8(param0->unk_00.unk_20, 1, sizeof(u8) * 4);

            param0->unk_00.unk_24 = 0;
            param0->unk_00.unk_26 = 0;

            memset(param0->unk_00.unk_28, 0, sizeof(u8) * 4);
        }

        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, heapID);

        param0->unk_00.unk_05 = 28;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState28(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    if (IsScreenFadeDone()) {
        param0->unk_00.unk_05 = 0;
    }

    return 0;
}

static BOOL WiFiCommApp_ClientState29(WiFiCommApp *param0, WiFiCommAppArgs *param1, u32 heapID)
{
    CommManager_EndWifiMatch();
    CommManager_SetState_LoginWifi();

    param0->unk_00.unk_07 = 0;
    CommManager_SetErrorHandling(0, 1);

    return 1;
}
