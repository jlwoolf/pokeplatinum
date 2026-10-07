#include "wifi_menu_app/wifi_menu_app.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "generated/journal_online_events.h"

#include "struct_decls/struct_02012B20_decl.h"
#include "struct_decls/wi_fi_list.h"
#include "struct_defs/battle_frontier.h"
#include "struct_defs/struct_020127E8.h"
#include "struct_defs/struct_0207DFAC.h"
#include "struct_defs/struct_0207E060.h"
#include "struct_defs/wi_fi_history.h"

#include "nintendo_wfc/main.h"
#include "wifi_menu_app/wifi_menu_app_02235060.h"
#include "wifi_menu_app/struct_wifi_menu_app_0222E99C.h"
#include "wifi_menu_app/struct_wifi_menu_app_0222EBE0_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_0222EBE0_t.h"
#include "wifi_menu_app/struct_wifi_menu_app_0222F6EC.h"
#include "wifi_menu_app/struct_wifi_menu_app_02234E50.h"
#include "wifi_menu_app/struct_wifi_menu_app_022354D8.h"
#include "gts/struct_gts_menu_args.h"

#include "assert.h"
#include "bag.h"
#include "battle_frontier_save.h"
#include "bg_window.h"
#include "char_transfer.h"
#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "enums.h"
#include "error_handling.h"
#include "font.h"
#include "game_options.h"
#include "game_overlay.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "inlines.h"
#include "journal.h"
#include "list_menu.h"
#include "menu.h"
#include "message.h"
#include "message_util.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "party.h"
#include "pltt_transfer.h"
#include "poffin.h"
#include "pokedex.h"
#include "pokemon.h"
#include "render_oam.h"
#include "render_text.h"
#include "render_window.h"
#include "rtc.h"
#include "save_player.h"
#include "savedata.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_transfer.h"
#include "sprite_util.h"
#include "string_gf.h"
#include "string_list.h"
#include "string_template.h"
#include "system.h"
#include "system_flags.h"
#include "text.h"
#include "touch_pad.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"
#include "trainer_info.h"
#include "font_oam.h"
#include "email.h"
#include "comm_server_client.h"
#include "comm_tool.h"
#include "wifi_friend_registration.h"
#include "wfc_host_match.h"
#include "wifi_comm.h"
#include "vars_flags.h"
#include "vram_transfer.h"
#include "wifi_history_save_data.h"
#include "wifi_list.h"
#include "wifi_overlays.h"

FS_EXTERN_OVERLAY(wifi_2d_char);

typedef struct {
    u32 unk_00;
    u32 unk_04;
} WiFiMenuAppActivityMenuEntry;

static WFCTrainerInfo *WiFiMenuApp_GetFriendStatus(WiFiMenuApp *param0, u32 param1);
static u8 WiFiMenuApp_GetFriendOnlineStatus(int param0);
static BOOL WiFiMenuApp_StartWifiBattle(WiFiMenuApp *param0, int param1, int param2);
static void WiFiMenuApp_VBlankCallback(void *param0);
static void WiFiMenuApp_SetGXBanks(void);
static void WiFiMenuApp_InitBgLayers(BgConfig *param0);
static void WiFiMenuApp_InitStrings(WiFiMenuApp *param0);
static void WiFiMenuApp_FreeStrings(WiFiMenuApp *param0);
static void WiFiMenuApp_FreeBgLayers(BgConfig *param0);
static void WiFiMenuApp_LoadMainBgGraphics(WiFiMenuApp *param0, NARC *param1);
static void WiFiMenuApp_InitTransfers(void);
static void WiFiMenuApp_InitSpriteManager(WiFiMenuApp *param0, NARC *param1);
static void WiFiMenuApp_EnableObjLayer(WiFiMenuApp *param0);
static void WiFiMenuApp_CreateHeaderWindow(WiFiMenuApp *param0);
static void WiFiMenuApp_AddActor(WiFiMenuApp *param0, WiFiMenuAppActor *param1);
static void WiFiMenuApp_RemoveActor(WiFiMenuApp *param0, WiFiMenuAppActor *param1);
static int WiFiMenuApp_UpdateBoardActors(WiFiMenuApp *param0);
static WiFiMenuAppActor *WiFiMenuApp_GetActorByIndex(WiFiMenuApp *param0, u32 param1);
static void WiFiMenuApp_LoadScreenData(BgConfig *param0, WiFiMenuAppScreenData *param1, NARC *param2, u32 param3);
static void WiFiMenuApp_FreeScreenData(WiFiMenuAppScreenData *param0);
static void WiFiMenuApp_DrawScreenDataTilemap(BgConfig *param0, WiFiMenuAppScreenData *param1, u32 param2, u8 param3, u8 param4, u32 param5, u32 param6);
static void WiFiMenuApp_DrawStateIconToBg(BgConfig *param0, WiFiMenuAppScreenData *param1, u32 param2, u8 param3, u8 param4, u32 param5);
static void WiFiMenuApp_DrawStateIconToWindow(Window *param0, WiFiMenuAppScreenData *param1, u16 param2, u16 param3, u32 param4, u32 param5);
static void WiFiMenuApp_DrawActorStateIcon(Window *param0, WiFiMenuAppScreenData *param1, u16 param2, u16 param3, u32 param4);
static int WiFiMenuApp_GetBgPaletteOffset(u32 param0);
static int WiFiMenuApp_StartFadeOutAndPlayBgm(void);
static void WiFiMenuApp_ResetBoardAndRedraw(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_ResetIfCurrentActor(WiFiMenuApp *param0, u32 param1, enum HeapID heapID);
static BOOL WiFiMenuApp_IsTouchScreenActive(const WiFiMenuApp *param0);
static void WiFiMenuApp_InitTouchScreen(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID);
static void WiFiMenuApp_FreeTouchScreen(WiFiMenuApp *param0);
static u32 WiFiMenuApp_UpdateTouchScreen(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_UpdateTouchScreenCursor(WiFiMenuApp *param0);
static BOOL WiFiMenuApp_IsTouchSelectionInput(WiFiMenuApp *param0, u32 param1);
static u32 WiFiMenuApp_GetTouchScreenSelection(const WiFiMenuApp *param0);
static void WiFiMenuApp_ResetTouchScreenSelection(WiFiMenuApp *param0);
static void WiFiMenuApp_ChangeTouchScreenPage(WiFiMenuApp *param0, u32 param1);
static void WiFiMenuApp_SetFriendListState(WiFiMenuApp *param0, u32 param1, u32 param2);
static void WiFiMenuApp_ClearFriendListState(WiFiMenuApp *param0, u32 param1);
static u32 WiFiMenuApp_GetFriendListState(const WiFiMenuApp *param0, u32 param1);
static void WiFiMenuApp_RedrawTouchScreen(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_MarkTouchScreenDirty(WiFiMenuApp *param0);
static void WiFiMenuApp_TouchButtonCallback(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void WiFiMenuApp_UpdateTouchScreenAnim(WiFiMenuApp *param0);
static void WiFiMenuApp_LoadTouchScreenGraphics(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID);
static void WiFiMenuApp_FreeTouchScreenGraphics(WiFiMenuApp *param0);
static void WiFiMenuApp_OffsetScreenData(NNSG2dScreenData *param0, u8 param1);
static void WiFiMenuApp_UpdateTouchScreenPalette(WiFiMenuApp *param0);
static void WiFiMenuApp_DrawFriendList(WiFiMenuApp *param0);
static void WiFiMenuApp_DrawFriendDetail(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage0(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage1(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage2(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage3(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage4(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage5(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendDetailPage6(WiFiMenuApp *param0, enum HeapID heapID);
static void WiFiMenuApp_DrawFriendListHeader(WiFiMenuApp *param0);
static void WiFiMenuApp_DrawFrontierStat(WiFiMenuApp *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
static void WiFiMenuApp_SetFrontierRecordMessage(WiFiMenuApp *param0, String *param1, u32 param2, u32 param3);
static void WiFiMenuApp_DrawCenteredNumber(WiFiMenuApp *param0, u32 param1, u32 param2, u32 param3, u32 param4);
static void WiFiMenuApp_DrawFriendRow(WiFiMenuApp *param0, u8 param1, u8 param2, u8 param3, u8 param4);
static u32 WiFiMenuApp_GetCommStateMessage(u32 param0, TextColor *param1);
static void WiFiMenuApp_DrawFriendName(WiFiMenuApp *param0, Window *param1, u32 param2, u32 param3, u32 param4);
static void WiFiMenuApp_DrawFriendStatus(WiFiMenuApp *param0, Window *param1, u32 param2, u32 param3, u32 param4);
static void WiFiMenuApp_InitTouchScreenSprites(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID);
static void WiFiMenuApp_FreeTouchScreenSprites(WiFiMenuApp *param0);
static void WiFiMenuApp_ShowTouchButtons(WiFiMenuApp *param0);
static void WiFiMenuApp_HideTouchButtons(WiFiMenuApp *param0);
static u32 WiFiMenuApp_UpdateTouchButtons(WiFiMenuApp *param0);
static void WiFiMenuApp_TouchButtonActionCallback(u32 param0, enum TouchScreenButtonState param1, void *param2);
static void WiFiMenuApp_SetTouchButtonAnim(WiFiMenuAppTouchScreen *param0, u32 param1);
static BOOL WiFiMenuApp_UpdateTouchButtonAnim(WiFiMenuAppTouchScreen *param0, u32 param1, u32 param2, u32 param3);
static void WiFiMenuApp_SetTouchScreenFriendName(WiFiMenuApp *param0, int param1);
static void WiFiMenuApp_FreeWindows(WiFiMenuApp *param0);
static void WiFiMenuApp_ShowMessageBox(WiFiMenuApp *param0, int param1);
static void WiFiMenuApp_ShowMessage(WiFiMenuApp *param0, int param1, BOOL param2);
static void WiFiMenuApp_ClearMessage(WiFiMenuApp *param0);
static void WiFiMenuApp_SetCommState(WiFiMenuApp *param0, int param1);
static void WiFiMenuApp_UpdateCommState(WiFiMenuApp *param0, int param1);
static void WiFiMenuApp_DestroyWaitDial(WiFiMenuApp *param0);
static void WiFiMenuApp_SetFriendNameTemplate(WiFiMenuApp *param0, int param1);
static u32 WiFiMenuApp_GetPoffinAvailability(WiFiMenuApp *param0);
static void WiFiMenuApp_PlayLobbyBgm(void);
static BOOL WiFiMenuApp_IsLobbyBgmPlaying(void);
static void WiFiMenuApp_SaveWifiClubJournalEvent(WiFiMenuApp *param0, u32 unused);
static void WiFiMenuApp_HandleWifiError(WiFiMenuApp *param0);
static void WiFiMenuApp_SetBoardBusyFlag(WiFiMenuApp *param0, BOOL param1);
static void WiFiMenuApp_ClearBoardBusyFlag(WiFiMenuApp *param0);
static int WiFiMenuApp_StateConnectWifi(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmLogin(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessLogin(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmWfcNotice(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessWfcNotice(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateResetWifiData(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateLoginAfterReset(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateDismissError(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateTo9(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateTo11(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitErrorAck(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmDisconnect(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessDisconnect(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateHandleDisconnect(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitMatchEnd(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitWfcSetup(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitBattleWifiLogin(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSaveStateInit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateShowConnecting(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateHandleBack(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateInitBoard(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateBoardInput(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitForMatch(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSelectFriend(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmFriend(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateFriendAction(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmLeave(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessLeave(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitBattleStart(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateCancelMatch(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitThenLogin(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop1(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop2(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop3(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateReturnFromMatch(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_CreateActivityListMenu(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessActivityList(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateStartBattleMatch(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessActivitySubMenu(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateOpenActivityMenu(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmExitActivity(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessExitActivity(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StatePrepareFriendAction(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateCreateFriendActionMenu(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessFriendAction(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitMatchSynchronize(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop4(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop5(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop6(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateNoop7(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateEvaluateMatchState(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSyncWifiReady(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSendTempData(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateReceiveTempData(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSendPlayerInfo(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateFinishSync(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWait55(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitBeforeExit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateReturnToBoard(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmQuit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessQuit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateLogoutAndCompact(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitExit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmSyncExit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessSyncExit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateConfirmFriendAction(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateProcessFriendActionConfirm(WiFiMenuApp *param0, int param1);
static BOOL WiFiMenuApp_ToggleVoiceChat(WiFiMenuApp *param0);
static BOOL WiFiMenuApp_ToggleVoiceChatBackup(WiFiMenuApp *param0);
static BOOL WiFiMenuApp_RestoreVoiceChat(WiFiMenuApp *param0);
static int WiFiMenuApp_StateHandleNewClient(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitCommInit(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateWaitDisconnectMessage(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateEndWifiMatch(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_StateSaveStateMain(WiFiMenuApp *param0, int param1);
static int WiFiMenuApp_CreateActivitySubMenu(WiFiMenuApp *param0, int param1);

static const s8 sWiFiMenuAppVoiceChatIconYOffsets[5] = {
    0xFFFFFFFFFFFFFFF8,
    0xFFFFFFFFFFFFFFF7,
    0xFFFFFFFFFFFFFFF6,
    0xFFFFFFFFFFFFFFF6,
    0xFFFFFFFFFFFFFFF7
};

static const u8 sWiFiMenuAppTouchButtonPressedAnims[3] = {
    0x0,
    0x2,
    0x4
};

static const u8 sWiFiMenuAppTouchButtonIdleAnims[3] = {
    0x1,
    0x3,
    0x5
};

static const TouchScreenHitTable sWiFiMenuAppTouchButtonsHitTable[3] = {
    { 0xA0, 0xC0, 0x8, 0x40 },
    { 0xA0, 0xC0, 0x50, 0xB0 },
    { 0xA0, 0xC0, 0xC0, 0xF8 }
};

static int (*sWiFiMenuAppStateHandlers[])(WiFiMenuApp *, int) = {
    WiFiMenuApp_StateConnectWifi,
    WiFiMenuApp_StateConfirmLogin,
    WiFiMenuApp_StateProcessLogin,
    WiFiMenuApp_StateConfirmWfcNotice,
    WiFiMenuApp_StateProcessWfcNotice,
    WiFiMenuApp_StateResetWifiData,
    WiFiMenuApp_StateLoginAfterReset,
    WiFiMenuApp_StateDismissError,
    WiFiMenuApp_StateTo9,
    WiFiMenuApp_StateTo11,
    WiFiMenuApp_StateWaitErrorAck,
    WiFiMenuApp_StateConfirmDisconnect,
    WiFiMenuApp_StateProcessDisconnect,
    WiFiMenuApp_StateHandleDisconnect,
    WiFiMenuApp_StateWaitWfcSetup,
    WiFiMenuApp_StateWaitBattleWifiLogin,
    WiFiMenuApp_StateShowConnecting,
    WiFiMenuApp_StateHandleBack,
    WiFiMenuApp_StateInitBoard,
    WiFiMenuApp_StateBoardInput,
    WiFiMenuApp_StateHandleNewClient,
    WiFiMenuApp_StateWaitForMatch,
    WiFiMenuApp_StateSelectFriend,
    WiFiMenuApp_StateConfirmFriend,
    WiFiMenuApp_StateFriendAction,
    WiFiMenuApp_StateConfirmLeave,
    WiFiMenuApp_StateProcessLeave,
    WiFiMenuApp_StateWaitBattleStart,
    WiFiMenuApp_StateCancelMatch,
    WiFiMenuApp_StateWaitThenLogin,
    WiFiMenuApp_StateNoop1,
    WiFiMenuApp_StateNoop2,
    WiFiMenuApp_StateNoop3,
    WiFiMenuApp_StateReturnFromMatch,
    WiFiMenuApp_StateWaitCommInit,
    WiFiMenuApp_StateWaitDisconnectMessage,
    WiFiMenuApp_CreateActivityListMenu,
    WiFiMenuApp_StateProcessActivityList,
    WiFiMenuApp_StateProcessActivitySubMenu,
    WiFiMenuApp_StateOpenActivityMenu,
    WiFiMenuApp_StateConfirmExitActivity,
    WiFiMenuApp_StateProcessExitActivity,
    WiFiMenuApp_StatePrepareFriendAction,
    WiFiMenuApp_StateCreateFriendActionMenu,
    WiFiMenuApp_StateProcessFriendAction,
    WiFiMenuApp_StateWaitMatchSynchronize,
    WiFiMenuApp_StateNoop6,
    WiFiMenuApp_StateNoop7,
    WiFiMenuApp_StateEvaluateMatchState,
    WiFiMenuApp_StateSyncWifiReady,
    WiFiMenuApp_StateSendTempData,
    WiFiMenuApp_StateReceiveTempData,
    WiFiMenuApp_StateSendPlayerInfo,
    WiFiMenuApp_StateFinishSync,
    WiFiMenuApp_StateWait55,
    WiFiMenuApp_StateWaitBeforeExit,
    WiFiMenuApp_StateReturnToBoard,
    WiFiMenuApp_StateConfirmQuit,
    WiFiMenuApp_StateProcessQuit,
    WiFiMenuApp_StateLogoutAndCompact,
    WiFiMenuApp_StateWaitExit,
    WiFiMenuApp_StateConfirmSyncExit,
    WiFiMenuApp_StateProcessSyncExit,
    WiFiMenuApp_StateConfirmFriendAction,
    WiFiMenuApp_StateProcessFriendActionConfirm,
    WiFiMenuApp_StateWaitMatchEnd,
    WiFiMenuApp_StateNoop4,
    WiFiMenuApp_StateNoop5,
    WiFiMenuApp_StateStartBattleMatch,
    WiFiMenuApp_StateSaveStateInit,
    WiFiMenuApp_StateEndWifiMatch,
    WiFiMenuApp_StateSaveStateMain
};

static const u8 sWiFiMenuAppDetailTextYOffsets[4] = {
    0x8,
    0x7,
    0x5,
    0x7
};

static const WindowTemplate sWiFiMenuAppYesNoWindowTemplate2 = {
    0x2,
    0x19,
    0xD,
    0x6,
    0x4,
    0xD,
    0x115
};

static BOOL WiFiMenuApp_IsBattleParkAccessed(WiFiMenuApp *param0)
{
    return SystemFlag_HandleFirstArrivalToZone(SaveData_GetVarsFlags(param0->saveData), HANDLE_FLAG_CHECK, FIRST_ARRIVAL_BATTLE_PARK);
}

static BOOL WiFiMenuApp_HasPoffinCase(WiFiMenuApp *param0)
{
    if (!Bag_GetItemQuantity(SaveData_GetBag(param0->saveData), ITEM_POFFIN_CASE, HEAP_ID_54)) {
        return 0;
    }

    return 1;
}

static BOOL WiFiMenuApp_CanAccessWifiClub(WiFiMenuApp *param0)
{
    return 1;
}

static u32 WiFiMenuApp_GetAdjustedCommState(WiFiMenuApp *param0, WFCTrainerInfo *param1)
{
    u32 v0 = param1->commState;

    if ((v0 == 20) || (v0 == 21)) {
        if (WiFiMenuApp_IsBattleParkAccessed(param0) == 0) {
            v0 = 29;
        }
    }

    if ((v0 == 22) || (v0 == 23) || (v0 == 24) || (v0 == 25) || (v0 == 26) || (v0 == 27)) {
        if (WiFiMenuApp_CanAccessWifiClub(param0) == 0) {
            v0 = 29;
        }
    }

    if ((v0 == 18) || (v0 == 19)) {
        if (WiFiMenuApp_HasPoffinCase(param0) == 0) {
            v0 = 29;
        }
    }

    return v0;
}

static BOOL WiFiMenuApp_IsWifiClubCommState(int param0)
{
    switch (param0) {
    case 19:
    case 18:
    case 23:
    case 22:
    case 27:
    case 26:
    case 25:
    case 24:
        return 1;
    default:
        return 0;
    }
}

static u32 WiFiMenuApp_GetWifiConnectionTypeFromState(int param0)
{
    switch (param0) {
    case 19:
    case 18:
        return 11;
    case 23:
    case 22:
        return 13;
    case 27:
    case 26:
        return 15;
    case 25:
    case 24:
        return 14;
    default:
        break;
    }

    GF_ASSERT(FALSE);
    return 0;
}

static BOOL WiFiMenuApp_IsBattleTowerCommState(int param0)
{
    switch (param0) {
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        return 1;
    default:
        return 0;
    }
}

static BOOL WiFiMenuApp_IsWifiBattleCommState(int param0)
{
    if (WiFiMenuApp_IsBattleTowerCommState(param0)) {
        return 1;
    }

    switch (param0) {
    case 15:
    case 19:
    case 21:
    case 23:
    case 27:
    case 25:
        return 1;
    }

    return 0;
}

static BOOL WiFiMenuApp_IsBattleModeCommState(int param0)
{
    switch (param0) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        return 1;
    default:
        return 0;
    }
}

static BOOL WiFiMenuApp_IsSingleBattleCommState(int param0)
{
    if (WiFiMenuApp_IsBattleModeCommState(param0)) {
        return 1;
    }

    switch (param0) {
    case 8:
    case 18:
    case 20:
    case 22:
    case 26:
    case 24:
    case 1:
        return 1;
    }

    return 0;
}

static BOOL WiFiMenuApp_IsTowerCommState(int param0)
{
    switch (param0) {
    case 15:
    case 12:
    case 13:
    case 14:
        return 1;
    }

    return 0;
}

static int WiFiMenuApp_GetPairedCommState(int param0)
{
    int v0 = 29;

    switch (param0) {
    case 19:
        v0 = 18;
        break;
    case 21:
        v0 = 20;
        break;
    case 23:
        v0 = 22;
        break;
    case 27:
        v0 = 26;
        break;
    case 25:
        v0 = 24;
        break;
    case 15:
        v0 = 8;
        break;
    case 9:
        v0 = 2;
        break;
    case 10:
        v0 = 3;
        break;
    case 11:
        v0 = 4;
        break;
    case 12:
        v0 = 5;
        break;
    case 13:
        v0 = 6;
        break;
    case 14:
        v0 = 7;
        break;
    case 16:
        v0 = 1;
        break;
    case 18:
        v0 = 19;
        break;
    case 20:
        v0 = 21;
        break;
    case 22:
        v0 = 23;
        break;
    case 26:
        v0 = 27;
        break;
    case 24:
        v0 = 25;
        break;
    case 8:
        v0 = 15;
        break;
    case 2:
        v0 = 9;
        break;
    case 3:
        v0 = 10;
        break;
    case 4:
        v0 = 11;
        break;
    case 5:
        v0 = 12;
        break;
    case 6:
        v0 = 13;
        break;
    case 7:
        v0 = 14;
        break;

    case 1:
        v0 = 16;
        break;
    }

    return v0;
}

static int WiFiMenuApp_GetUsablePartyCount(WiFiMenuApp *param0)
{
    Party *v0 = SaveData_GetParty(param0->saveData);
    Pokemon *v1;
    int v2 = Party_GetCurrentCount(v0);
    int v3, v4 = 0;

    for (v3 = 0; v3 < v2; v3++) {
        v1 = Party_GetPokemonBySlotIndex(v0, v3);

        if (Pokemon_GetValue(v1, MON_DATA_HP, NULL) == 0) {
            continue;
        }

        if (Pokemon_GetValue(v1, MON_DATA_IS_EGG, NULL)) {
            continue;
        }

        v4++;
    }

    return v4;
}

static void WiFiMenuApp_SetCommStateForSelection(int param0)
{
    if ((param0 == 19) || (18 == param0)) {
        CommManager_SetState_WifiPoffin();
    } else if (WiFiMenuApp_IsWifiClubCommState(param0)) {
        CommManager_SetState_WifiClub();
    } else if (param0 == 16) {
        CommManager_SetState_LoginWifi();
    } else if ((param0 == 21) || (param0 == 20)) {
        CommSys_SetRecvLimitEnabled(0);
        CommManager_SetState_FrontierWifi();
    } else {
        CommSys_SetRecvLimitEnabled(1);
        CommManager_SetState_SingleBattleWifi();
    }
}

static void WiFiMenuApp_InitGraphics(WiFiMenuApp *param0)
{
    NARC *v0;

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();
    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetAutorepeat(4, 8);

    v0 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, HEAP_ID_54);

    param0->unk_15C = BgConfig_New(HEAP_ID_54);
    param0->unk_164 = StringTemplate_Default(HEAP_ID_54);
    param0->unk_168 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0674, HEAP_ID_54);
    param0->unk_16C = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0695, HEAP_ID_54);

    WiFiMenuApp_SetGXBanks();
    WiFiMenuApp_InitBgLayers(param0->unk_15C);
    WiFiMenuApp_LoadMainBgGraphics(param0, v0);

    GlobalTerminal_InitPaletteBlend(&param0->unk_E2C, v0, 4, 54);

    SetVBlankCallback(WiFiMenuApp_VBlankCallback, param0);

    WiFiMenuApp_InitTransfers();
    WiFiMenuApp_InitSpriteManager(param0, v0);
    WiFiMenuApp_EnableObjLayer(param0);

    NARC_dtor(v0);
}

int WiFiMenuApp_Init(ApplicationManager *appMan, int *param1)
{
    WiFiMenuApp *v0;
    GTSMenuArgs *v1;
    u32 v2;

    switch (*param1) {
    case 0:
        v1 = ApplicationManager_Args(appMan);

        if (CommManager_IsConnectedToWifi()) {
            switch (v1->unk_04) {
            case 8:
            case 9:
            case 10:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 12:
            case 7:
                Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_PARTY_MENU1, 0x10000);
                break;
            default:
                break;
            }
        } else {
            Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_PARTY_MENU1, 0x10000);
        }

        Overlay_LoadByID(FS_OVERLAY_ID(wifi_2d_char), 2);

        if (v1->unk_04 == 1) {
            Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_54, 0x70000);
        } else {
            Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_54, 0xa0000);
        }

        v0 = ApplicationManager_NewData(appMan, sizeof(WiFiMenuApp), HEAP_ID_54);

        MI_CpuFill8(v0, 0, sizeof(WiFiMenuApp));
        VramTransfer_New(32, HEAP_ID_54);

        v0->unk_180 = 8;
        v0->saveData = v1->saveData;
        v0->unk_00 = SaveData_GetWiFiList(v0->saveData);
        v0->unk_3B4 = v1->unk_04;
        v0->unk_3AC = 8;
        v0->unk_3D0 = -1;

        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, 0);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3, 0);

        WiFiMenuApp_InitStrings(v0);
        WiFiMenuApp_InitGraphics(v0);

        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_54);

        if (CommManager_IsConnectedToWifi()) {
            NetworkIcon_Init();
        } else {
            Overlay_LoadWFCOverlay();
        }

        v2 = InitializeTouchPad(4);
        GF_ASSERT(v2 == 1);
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

int WiFiMenuApp_Main(ApplicationManager *appMan, int *param1)
{
    WiFiMenuApp *v0 = ApplicationManager_Data(appMan);

    switch (*param1) {
    case 0:
        if (IsScreenFadeDone()) {
            *param1 = 1;
        }
        break;
    case 1:
        if (sWiFiMenuAppStateHandlers[v0->unk_3A8] != NULL) {
            static int v1 = 0;

            if (v1 != v0->unk_3A8) {
                (void)0;
            }

            v1 = v0->unk_3A8;
            *param1 = (*sWiFiMenuAppStateHandlers[v0->unk_3A8])(v0, *param1);
        }
        break;
    case 2:
        if (IsScreenFadeDone()) {
            return 1;
        }
        break;
    }

    if (v0->unk_18C) {
        SpriteList_Update(v0->unk_18C);
    }

    if (WiFiMenuAppBoard_IsActive(&v0->unk_3EC) == 1) {
        WiFiMenuAppBoard_UpdateSprites(&v0->unk_3EC);
    }

    GlobalTerminal_PaletteBlendNoop(&v0->unk_E2C);

    return 0;
}

static void WiFiMenuApp_FreeGraphics(WiFiMenuApp *param0)
{
    int v0;

    SetVBlankCallback(NULL, NULL);

    GlobalTerminal_FreePaletteBlend(&param0->unk_E2C);

    if (WiFiMenuAppBoard_IsActive(&param0->unk_3EC) == 1) {
        WiFiMenuAppBoard_Free(&param0->unk_3EC);
    }

    if (WiFiMenuApp_IsTouchScreenActive(param0) == 1) {
        WiFiMenuApp_FreeTouchScreen(param0);
    }

    WiFiMenuApp_FreeScreenData(&param0->unk_BD0);
    FontOAMManager_Free(param0->unk_32C);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Delete(param0->unk_31C[v0]);
    }

    SpriteList_Delete(param0->unk_18C);
    RenderOam_Free();
    CharTransfer_Free();
    PlttTransfer_Free();

    WiFiMenuApp_FreeWindows(param0);
    WiFiMenuApp_FreeBgLayers(param0->unk_15C);

    MessageLoader_Free(param0->unk_16C);
    MessageLoader_Free(param0->unk_168);
    StringTemplate_Free(param0->unk_164);
    Overlay_UnloadByID(FS_OVERLAY_ID(wifi_2d_char));
}

int WiFiMenuApp_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiMenuApp *v0 = ApplicationManager_Data(appMan);
    GTSMenuArgs *v1;

    WiFiMenuApp_FreeGraphics(v0);

    v1 = ApplicationManager_Args(appMan);
    v1->unk_04 = v0->unk_3AC;

    if ((v0->unk_3AC == 8) || (v0->unk_3AC == 10)) {
        Overlay_UnloadWFCOverlay();
    } else {
        v1->unk_08 = NintendoWFC_GetHostFriendIdx();
    }

    WiFiMenuApp_FreeStrings(v0);

    ApplicationManager_FreeData(appMan);
    DisableTouchPad();
    VramTransfer_Free();
    Heap_Destroy(HEAP_ID_54);

    switch (v0->unk_3AC) {
    case 8:
    case 9:
    case 10:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 12:
    case 7:
        Heap_Destroy(HEAP_ID_PARTY_MENU1);
        break;
    default:
        break;
    }

    if (WiFiMenuApp_IsLobbyBgmPlaying() == 1) {
        Sound_SetInitialVolumeForHandle(SOUND_HANDLE_TYPE_FIELD_BGM, 120);
    }

    return 1;
}

static void WiFiMenuApp_VBlankCallback(void *param0)
{
    WiFiMenuApp *v0 = param0;

    Bg_RunScheduledUpdates(v0->unk_15C);
    VramTransfer_Process();
    RenderOam_Transfer();

    GlobalTerminal_PaletteBlendNoop2(&v0->unk_E2C);

    if (v0->unk_1158 == 1) {
        ResetScreenMasterBrightness(DS_SCREEN_MAIN);
        ResetScreenMasterBrightness(DS_SCREEN_SUB);
        v0->unk_1158 = 0;
    }
}

static void WiFiMenuApp_SetGXBanks(void)
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

static void WiFiMenuApp_InitBgLayers(BgConfig *param0)
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
            .bufferSize = 0x1000,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_512x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_0, &v1, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_54);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_0);
    }

    {
        BgTemplate v2 = {
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

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_1, &v2, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_54);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_1);
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
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_2, &v3, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_54);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_2);
    }

    {
        BgTemplate v4 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x18000,
            .bgExtPltt = GX_BG_EXTPLTT_23,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_MAIN_3, &v4, 0);
        Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_54);
        Bg_ClearTilemap(param0, BG_LAYER_MAIN_3);
    }

    {
        BgTemplate v5 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe000,
            .charBase = GX_BG_CHARBASE_0x00000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 3,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v5, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_0);
    }

    {
        BgTemplate v6 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xe800,
            .charBase = GX_BG_CHARBASE_0x08000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v6, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_1);
    }

    {
        BgTemplate v7 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf000,
            .charBase = GX_BG_CHARBASE_0x10000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 2,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_2, &v7, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_2);
    }

    {
        BgTemplate v8 = {
            .x = 0,
            .y = 0,
            .bufferSize = 0x800,
            .baseTile = 0,
            .screenSize = BG_SCREEN_SIZE_256x256,
            .colorMode = GX_BG_COLORMODE_16,
            .screenBase = GX_BG_SCRBASE_0xf800,
            .charBase = GX_BG_CHARBASE_0x18000,
            .bgExtPltt = GX_BG_EXTPLTT_01,
            .priority = 0,
            .areaOver = 0,
            .mosaic = FALSE,
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_3, &v8, 0);
        Bg_ClearTilemap(param0, BG_LAYER_SUB_3);
    }

    Bg_ClearTilesRange(BG_LAYER_MAIN_0, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(BG_LAYER_MAIN_1, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(BG_LAYER_MAIN_2, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(BG_LAYER_MAIN_3, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(4, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(5, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(6, 32, 0, HEAP_ID_54);
    Bg_ClearTilesRange(7, 32, 0, HEAP_ID_54);

    Bg_SetPriority(BG_LAYER_MAIN_0, 3);
    Bg_SetPriority(BG_LAYER_MAIN_1, 1);
    Bg_SetPriority(BG_LAYER_MAIN_3, 0);
    Bg_SetPriority(BG_LAYER_MAIN_2, 0);

    G2_BlendNone();
    G2S_BlendNone();
}

static void WiFiMenuApp_AddActor(WiFiMenuApp *param0, WiFiMenuAppActor *param1)
{
    int v0;

    for (v0 = 0; v0 < (32 + 1); v0++) {
        if (param0->unk_B4C[v0] == NULL) {
            param0->unk_B4C[v0] = param1;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void WiFiMenuApp_RemoveActor(WiFiMenuApp *param0, WiFiMenuAppActor *param1)
{
    int v0;

    for (v0 = 0; v0 < (32 + 1); v0++) {
        if (param0->unk_B4C[v0] == param1) {
            param0->unk_B4C[v0] = NULL;
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static WiFiMenuAppActor *WiFiMenuApp_GetActorByIndex(WiFiMenuApp *param0, u32 param1)
{
    int v0;

    for (v0 = 0; v0 < (32 + 1); v0++) {
        if (param0->unk_B4C[v0]) {
            if (WiFiMenuAppBoard_GetActorField(param0->unk_B4C[v0]) == param1) {
                return param0->unk_B4C[v0];
            }
        }
    }

    return NULL;
}

static void WiFiMenuApp_LoadScreenData(BgConfig *param0, WiFiMenuAppScreenData *param1, NARC *param2, u32 param3)
{
    Graphics_LoadPaletteFromOpenNARC(param2, 13, 0, 8 * 32, 2 * 32, param3);
    Graphics_LoadPaletteFromOpenNARC(param2, 13, 4, 13 * 32, 2 * 32, param3);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 12, param0, 1, 0, 0, 0, param3);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param2, 12, param0, 6, 0, 0, 0, param3);

    if (param1->unk_08 == NULL) {
        param1->unk_08 = Graphics_GetCharDataFromOpenNARC(param2, 12, 0, &param1->unk_0C, param3);
    }

    if (param1->unk_00 == NULL) {
        param1->unk_00 = Graphics_GetScrnDataFromOpenNARC(param2, 14, 0, &param1->unk_04, param3);
    }
}

static void WiFiMenuApp_FreeScreenData(WiFiMenuAppScreenData *param0)
{
    if (param0->unk_00 != NULL) {
        Heap_Free(param0->unk_00);
        param0->unk_00 = NULL;
    }

    if (param0->unk_08 != NULL) {
        Heap_Free(param0->unk_08);
        param0->unk_08 = NULL;
    }
}

static void WiFiMenuApp_DrawScreenDataTilemap(BgConfig *param0, WiFiMenuAppScreenData *param1, u32 param2, u8 param3, u8 param4, u32 param5, u32 param6)
{
    int v0;

    Bg_CopyToTilemapRect(param0, param2, param3, param4, 2, 2, param1->unk_04->rawData, 2 * param5, 0, param1->unk_04->screenWidth / 8, param1->unk_04->screenHeight / 8);

    v0 = WiFiMenuApp_GetBgPaletteOffset(param2);

    Bg_ChangeTilemapRectPalette(param0, param2, param3, param4, 2, 2, v0 + param6);
    Bg_ScheduleTilemapTransfer(param0, param2);
}

static void WiFiMenuApp_DrawStateIconToBg(BgConfig *param0, WiFiMenuAppScreenData *param1, u32 param2, u8 param3, u8 param4, u32 param5)
{
    u8 v0 = 0;
    u8 v1 = 0;

    switch (param5) {
    case 1:
        v1 = 3;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        v0 = 1;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        v1 = 6;
        break;
    case 15:
        v0 = 1;
    case 8:
        v1 = 7;
        break;
    case 23:
    case 25:
    case 27:
        v0 = 1;
    case 22:
    case 24:
    case 26:
        v1 = 10;
        break;
    case 19:
        v0 = 1;
    case 18:
        v1 = 9;
        break;
    case 21:
        v0 = 1;
    case 20:
        v1 = 11;
        break;
    case 16:
        v1 = 4;
        break;
    case 0:
        v1 = 8;
        break;
    case 29:
    case 28:
        v1 = 5;
        break;
    default:
        v1 = 5;
        break;
    }

    WiFiMenuApp_DrawScreenDataTilemap(param0, param1, param2, param3, param4, v1, v0);
}

static void WiFiMenuApp_DrawStateIconToWindow(Window *param0, WiFiMenuAppScreenData *param1, u16 param2, u16 param3, u32 param4, u32 param5)
{
    int v0;

    Window_BlitBitmapRect(param0, param1->unk_0C->pRawData, (2 * 8) * param4, 0, param1->unk_0C->W * 8, param1->unk_0C->H * 8, param2, param3, 2 * 8, 2 * 8);
    v0 = WiFiMenuApp_GetBgPaletteOffset(param0->bgLayer);
    Window_SetPalette(param0, v0 + param5);
}

static void WiFiMenuApp_DrawActorStateIcon(Window *param0, WiFiMenuAppScreenData *param1, u16 param2, u16 param3, u32 param4)
{
    u8 v0 = 0;
    u8 v1 = 0;

    switch (param4) {
    case 1:
        v1 = 3;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        v0 = 1;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        v1 = 6;
        break;
    case 15:
        v0 = 1;
    case 8:
        v1 = 7;
        break;
    case 23:
    case 25:
    case 27:
        v0 = 1;
    case 22:
    case 24:
    case 26:
        v1 = 10;
        break;
    case 19:
        v0 = 1;
    case 18:
        v1 = 9;
        break;
    case 21:
        v0 = 1;
    case 20:
        v1 = 11;
        break;
    case 16:
        v1 = 4;
        break;
    case 0:
        v1 = 8;
        break;
    case 29:
    case 28:
        v1 = 5;
        break;
    default:
        v1 = 5;
        break;
    }

    WiFiMenuApp_DrawStateIconToWindow(param0, param1, param2, param3, v1, v0);
}

static int WiFiMenuApp_GetBgPaletteOffset(u32 param0)
{
    if (param0 < 4) {
        return 8;
    }

    return 13;
}

static int WiFiMenuApp_StartFadeOutAndPlayBgm(void)
{
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_54);
    WiFiMenuApp_PlayLobbyBgm();

    return 18;
}

static void WiFiMenuApp_InitStrings(WiFiMenuApp *param0)
{
    int v0;
    int v1;

    param0->unk_174 = String_Init(190 * 2, HEAP_ID_54);
    param0->unk_17C = String_Init(190 * 2, HEAP_ID_54);
    param0->unk_170 = String_Init(190 * 2, HEAP_ID_54);
    param0->unk_178 = String_Init(90 * 2, HEAP_ID_54);
    param0->unk_3A8 = 0;
}

static void WiFiMenuApp_FreeStrings(WiFiMenuApp *param0)
{
    int v0;

    String_Free(param0->unk_178);
    String_Free(param0->unk_174);
    String_Free(param0->unk_17C);
    String_Free(param0->unk_170);
}

static void WiFiMenuApp_FreeBgLayers(BgConfig *param0)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_2);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0, BG_LAYER_MAIN_0);
    Heap_Free(param0);
}

static void WiFiMenuApp_LoadMainBgGraphics(WiFiMenuApp *param0, NARC *param1)
{
    BgConfig *v0 = param0->unk_15C;

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);

    Graphics_LoadPaletteFromOpenNARC(param1, 3, 0, 0, 0, HEAP_ID_54);
    Graphics_LoadPaletteFromOpenNARC(param1, 3, 4, 0, 0, HEAP_ID_54);

    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(13), HEAP_ID_54);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_MAIN_BG, PLTT_OFFSET(12), HEAP_ID_54);

    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 2, v0, 0, 0, 0, 0, HEAP_ID_54);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 5, v0, 0, 0, 0, 0, HEAP_ID_54);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 10, v0, 4, 0, 0, 0, HEAP_ID_54);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 11, v0, 4, 0, 0, 0, HEAP_ID_54);

    {
        int v1 = Options_Frame(SaveData_GetOptions(param0->saveData));

        LoadMessageBoxGraphics(v0, BG_LAYER_MAIN_2, 512 - (18 + 12), 10, v1, HEAP_ID_54);
        LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_2, (512 - (18 + 12)) - 9, 11, 0, HEAP_ID_54);
        LoadStandardWindowGraphics(v0, BG_LAYER_MAIN_1, (512 - (18 + 12)) - 9, 11, 0, HEAP_ID_54);
    }
}

static void WiFiMenuApp_InitTransfers(void)
{
    {
        CharTransferTemplate v0 = {
            20, 128 * 1024, 16 * 1024, 54
        };

        CharTransfer_InitWithVramModes(&v0, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K);
    }

    PlttTransfer_Init(20, HEAP_ID_54);
    CharTransfer_ClearBuffers();
    PlttTransfer_Clear();
    ReserveVramForWirelessIconChars(NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K);
    ReserveSlotsForWirelessIconPalette(NNS_G2D_VRAM_TYPE_2DMAIN);
}

static void WiFiMenuApp_InitSpriteManager(WiFiMenuApp *param0, NARC *param1)
{
    int v0;

    NNS_G2dInitOamManagerModule();
    RenderOam_Init(0, 126, 0, 32, 0, 126, 0, 32, 54);

    param0->unk_18C = SpriteList_InitRendering(8, &param0->unk_190, HEAP_ID_54);

    SetSubScreenViewRect(&param0->unk_190, 0, 256 * FX32_ONE);

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_31C[v0] = SpriteResourceCollection_New(1, v0, HEAP_ID_54);
    }

    param0->unk_32C = FontOAMManager_New(1, HEAP_ID_54);
}

static void WiFiMenuApp_EnableObjLayer(WiFiMenuApp *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, 1);
}

static void WiFiMenuApp_CreateHeaderWindow(WiFiMenuApp *param0)
{
    int v0, v1;

    if (Window_IsInUse(&param0->unk_350)) {
        Window_EraseStandardFrame(&param0->unk_350, 0);
        Window_Remove(&param0->unk_350);
    }

    Window_Add(param0->unk_15C, &param0->unk_350, 3, 5, 1, 22, 2, 13, 512 - 18 * 3);
    Window_FillTilemap(&param0->unk_350, 0x8000);
    MessageLoader_GetString(param0->unk_168, 21, param0->unk_178);

    {
        u32 v2 = Font_CalcCenterAlignment(FONT_SYSTEM, param0->unk_178, 0, 22 * 8);

        Text_AddPrinterWithParamsAndColor(&param0->unk_350, FONT_MESSAGE, param0->unk_178, v2, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    }

    Window_ScheduleCopyToVRAM(&param0->unk_350);
}

static void WiFiMenuApp_FreeWindows(WiFiMenuApp *param0)
{
    int v0;

    WiFiMenuApp_ClearMessage(param0);

    if (Window_IsInUse(&param0->unk_350)) {
        Window_Remove(&param0->unk_350);
    }

    if (Window_IsInUse(&param0->unk_330)) {
        Window_Remove(&param0->unk_330);
    }

    if (Window_IsInUse(&param0->unk_390)) {
        Window_Remove(&param0->unk_390);
    }

    if (Window_IsInUse(&param0->unk_340)) {
        Window_Remove(&param0->unk_340);
    }

    if (Window_IsInUse(&param0->unk_370)) {
        Window_Remove(&param0->unk_370);
    }

    if (param0->unk_150) {
        ListMenu_Free(param0->unk_150, NULL, NULL);
    }

    if (param0->unk_14C) {
        StringList_Free(param0->unk_14C);
        param0->unk_14C = NULL;
    }

    if (Window_IsInUse(&param0->unk_360)) {
        Window_Remove(&param0->unk_360);
    }
}

static const WindowTemplate sWiFiMenuAppYesNoWindowTemplate1 = {
    0x2,
    0x19,
    0xD,
    0x6,
    0x4,
    0xD,
    0x51
};

static const WindowTemplate sWiFiMenuAppYesNoWindowTemplate3 = {
    0x1,
    0x19,
    0x13,
    0x6,
    0x4,
    0xD,
    0x189
};

static int WiFiMenuApp_StateConnectWifi(WiFiMenuApp *param0, int param1)
{
    u32 v0;

    if (CommManager_IsConnectedToWifi()) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        param0->unk_04 = CommManager_GetUnk00();
        param0->unk_04->ownStatus.voiceChatEnabled = param0->unk_04->ownStatus.voiceChatEnabledBackup;

        v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);

        if ((v0 == 8) || (v0 == 18) || (v0 == 20) || (v0 == 22) || (v0 == 23) || (v0 == 24) || (v0 == 25) || (v0 == 26) || (v0 == 27) || (v0 == 19)) {
            WiFiMenuApp_SetCommState(param0, 16);
            CommInfo_Delete();
            CommManager_EndTradeWifiMatch();

            param0->unk_04 = CommManager_GetUnk00();
            param0->unk_04->ownStatus.voiceChatEnabled = param0->unk_04->ownStatus.voiceChatEnabledBackup;
            param0->unk_3BC = 20;
            param0->unk_3A8 = 65;
        } else {
            WiFiMenuApp_ShowMessage(param0, 77, 0);
            CommManager_SetErrorHandling(1, 1);
            CommTiming_StartSync(16);
            param0->unk_3A8 = 61;
        }
    } else {
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_11, SEQ_WIFILOBBY_sseq, 1);
        WiFiMenuApp_CreateHeaderWindow(param0);

        if (!DWC_CheckHasProfile(WiFiList_GetUserData(param0->unk_00))) {
            Bg_SetPriority(BG_LAYER_MAIN_0, 3);
            Bg_SetPriority(BG_LAYER_MAIN_1, 0);
            Bg_SetPriority(BG_LAYER_MAIN_3, 0);
            Bg_SetPriority(BG_LAYER_MAIN_2, 1);

            WiFiMenuApp_ShowMessageBox(param0, 18);

            param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate3, (512 - (18 + 12)) - 9, 11, 54);
            param0->unk_3A8 = 6;
        } else if (!DWC_CheckValidConsole(WiFiList_GetUserData(param0->unk_00))) {
            WiFiMenuApp_ShowMessageBox(param0, 20);
            param0->unk_3A8 = 3;
        } else {
            WiFiMenuApp_ShowMessage(param0, 17, 1);
            param0->unk_3A8 = 1;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmLogin(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate1, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 2;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessLogin(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        return param1;
    } else {
        if (v1 == 0) {
            param0->unk_04 = CommManager_LoginWifiBattleServer(param0->saveData, sizeof(WFCStatusBuffer));
            WiFiMenuApp_ShowMessage(param0, 23, 1);
            GF_ASSERT(param0->unk_188 == NULL);
            param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
            param0->unk_3A8 = 14;
        } else {
            param0->unk_3A8 = 34;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmWfcNotice(WiFiMenuApp *param0, int param1)
{
    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        WiFiMenuApp_ShowMessageBox(param0, 21);
        Bg_SetPriority(BG_LAYER_MAIN_3, 0);
        Bg_SetPriority(BG_LAYER_MAIN_2, 1);
        Bg_SetPriority(BG_LAYER_MAIN_1, 0);
        Bg_SetPriority(BG_LAYER_MAIN_0, 3);

        param0->unk_184 = Menu_MakeYesNoChoiceWithCursorAt(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate3, (512 - (18 + 12)) - 9, 11, 1, 54);
        param0->unk_3A8 = 4;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessWfcNotice(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        return param1;
    } else {
        Window_EraseMessageBox(&param0->unk_360, 0);
        Window_Remove(&param0->unk_360);

        if (v1 == 0) {
            WiFiMenuApp_ShowMessageBox(param0, 22);
            param0->unk_184 = Menu_MakeYesNoChoiceWithCursorAt(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate3, (512 - (18 + 12)) - 9, 11, 1, 54);
            param0->unk_3A8 = 5;
        } else {
            param0->unk_3A8 = 34;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateResetWifiData(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        return param1;
    } else {
        Bg_SetPriority(BG_LAYER_MAIN_3, 0);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Bg_SetPriority(BG_LAYER_MAIN_1, 1);
        Bg_SetPriority(BG_LAYER_MAIN_0, 3);
        Window_EraseMessageBox(&param0->unk_360, 0);
        Window_Remove(&param0->unk_360);

        if (v1 == 0) {
            WiFiList_Init(param0->unk_00);
            Email_Init(SaveData_SaveTable(param0->saveData, SAVE_TABLE_ENTRY_EMAIL));
            BattleFrontierSave_ClearAllWFCStats(SaveData_GetBattleFrontier(param0->saveData));
            param0->unk_3A8 = 14;
            param0->unk_04 = CommManager_LoginWifiBattleServer(param0->saveData, sizeof(WFCStatusBuffer));
            WiFiMenuApp_ShowMessage(param0, 23, 1);
            GF_ASSERT(param0->unk_188 == NULL);
            param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
            param0->unk_3C8 = 1;
        } else {
            param0->unk_3A8 = 34;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateLoginAfterReset(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        return param1;
    } else {
        Bg_SetPriority(BG_LAYER_MAIN_0, 3);
        Bg_SetPriority(BG_LAYER_MAIN_1, 1);
        Bg_SetPriority(BG_LAYER_MAIN_3, 0);
        Bg_SetPriority(BG_LAYER_MAIN_2, 0);
        Window_EraseMessageBox(&param0->unk_360, 0);
        Window_Remove(&param0->unk_360);

        if (v1 == 0) {
            param0->unk_3A8 = 14;
            param0->unk_04 = CommManager_LoginWifiBattleServer(param0->saveData, sizeof(WFCStatusBuffer));
            WiFiMenuApp_ShowMessage(param0, 23, 1);
            GF_ASSERT(param0->unk_188 == NULL);
            param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
            param0->unk_3C8 = 1;
        } else {
            param0->unk_3A8 = 34;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateWaitWfcSetup(WiFiMenuApp *param0, int param1)
{
    Bg_SetPriority(BG_LAYER_MAIN_0, 3);
    Bg_SetPriority(BG_LAYER_MAIN_1, 1);
    Bg_SetPriority(BG_LAYER_MAIN_3, 0);
    Bg_SetPriority(BG_LAYER_MAIN_2, 0);
    param0->unk_3A8 = 15;
    return param1;
}

static void WiFiMenuApp_SetupOwnStatus(WiFiMenuApp *param0, int param1)
{
    TrainerInfo *v0 = SaveData_GetTrainerInfo(param0->saveData);
    Pokedex *v1 = SaveData_GetPokedex(param0->saveData);
    Party *v2 = SaveData_GetParty(param0->saveData);
    WiFiHistory *wiFiHistory = SaveData_WiFiHistory(param0->saveData);
    int v4, v5;

    GF_ASSERT((sizeof(WFCTrainerInfo)) == sizeof(WFCTrainerInfo));

    v4 = Party_GetCurrentCount(v2);

    for (v5 = 0; v5 < v4; v5++) {
        Pokemon *v6 = Party_GetPokemonBySlotIndex(v2, v5);

        param0->unk_04->ownStatus.partySpecies[v5] = Pokemon_GetValue(v6, MON_DATA_SPECIES, NULL);
        param0->unk_04->ownStatus.partyHeldItems[v5] = Pokemon_GetValue(v6, MON_DATA_HELD_ITEM, NULL);
    }

    param0->unk_04->ownStatus.gameCode = TrainerInfo_GameCode(v0);
    param0->unk_04->ownStatus.language = TrainerInfo_Language(v0);
    param0->unk_04->ownStatus.isNationalDexObtained = Pokedex_IsNationalDexObtained(v1);
    param0->unk_04->ownStatus.commState = 29;

    WiFiMenuApp_UpdateCommState(param0, param1);

    param0->unk_04->ownStatus.unk_1C = 0;
    param0->unk_04->ownStatus.appearance = TrainerInfo_Appearance(v0);
    param0->unk_04->ownStatus.gender = TrainerInfo_Gender(v0);
    param0->unk_04->ownStatus.country = WiFiHistory_GetCountry(wiFiHistory);
    param0->unk_04->ownStatus.region = WiFiHistory_GetRegion(wiFiHistory);
    param0->unk_04->ownStatus.voiceChatEnabled = 1;
    param0->unk_04->ownStatus.voiceChatEnabledBackup = 1;

    NintendoWFC_SetStatusData((const char *)&param0->unk_04->ownStatus, sizeof(WFCTrainerInfo));
    NintendoWFC_SetFriendStatusesBuffer(&param0->unk_04->friendStatuses[0], sizeof(WFCTrainerInfo));
}

static int WiFiMenuApp_BuildVisibleFriendList(WiFiMenuApp *param0)
{
    int v0, v1 = 0;
    WFCTrainerInfo *v2;
    u32 v3;

    for (v0 = 0; v0 < 32; v0++) {
        param0->unk_0C[v0] = 0;

        if (param0->unk_115A > v0) {
            if (DWC_STATUS_OFFLINE != WiFiMenuApp_GetFriendOnlineStatus(v0)) {
                v2 = WiFiMenuApp_GetFriendStatus(param0, v0);
                v3 = WiFiMenuApp_GetAdjustedCommState(param0, v2);

                if ((v3 != 0) && (v3 != 28) && (v2->appearance != 0x0)) {
                    param0->unk_0C[v1] = v0 + 1;
                    v1++;
                } else {
                    if (v3 == 28) {
                        if (WiFiMenuApp_GetFriendListState(param0, v0 + 1) != 0) {
                            WiFiMenuApp_ClearFriendListState(param0, v0 + 1);
                        }
                    }
                }
            }
        }
    }

    return v1;
}

static int WiFiMenuApp_UpdateFriendActors(WiFiMenuApp *param0)
{
    int v0, v1 = 0;
    BOOL v2;
    BOOL v3;
    WiFiMenuAppActor *v4;
    WFCTrainerInfo *v5;
    u32 v6;

    for (v0 = 0; v0 < 32; v0++) {
        v5 = WiFiMenuApp_GetFriendStatus(param0, v0);
        v6 = WiFiMenuApp_GetAdjustedCommState(param0, v5);

        if ((param0->unk_4C[v0] != v6) || (param0->unk_CC[v0] != v5->voiceChatEnabled)) {
            v4 = WiFiMenuApp_GetActorByIndex(param0, v0 + 1);

            if (v4) {
                v2 = WiFiMenuApp_IsWifiBattleCommState(param0->unk_4C[v0]);
                v3 = WiFiMenuApp_IsWifiBattleCommState(v6);

                if ((v2 == 1) && (v3 == 0)) {
                    WiFiMenuAppBoard_SetActorState(&param0->unk_3EC, v4, 0);
                } else if ((v2 == 0) && (v3 == 1)) {
                    WiFiMenuAppBoard_SetActorState(&param0->unk_3EC, v4, 1);
                }

                param0->unk_4C[v0] = v6;
                param0->unk_CC[v0] = v5->voiceChatEnabled;

                WiFiList_SetFriendField(param0->unk_00, v0, 7, v5->appearance);
                WiFiList_SetFriendField(param0->unk_00, v0, 8, v5->gender);
                v1++;
            }
        }
    }

    return v1;
}

static void WiFiMenuApp_HandleWifiError(WiFiMenuApp *param0)
{
    WiFiCommErrorInfo *v0 = CommManager_GetUnk34();
    int v1, v2 = v0->unk_00;
    int v3 = NintendoWFC_GetErrorCode(v0->unk_00, v0->unk_04);

    if ((v3 == 11) || (v2 == ((DWC_ERROR_NUM) + 5))) {
        v1 = 14;
        v3 = 11;
    } else if (v2 == ((DWC_ERROR_NUM) + 6)) {
        v1 = 13;
        v3 = 12;
    } else {
        if (v3 >= 0) {
            v1 = 0 + v3;
        } else {
            v1 = 11;
        }
    }

    WiFiMenuApp_ClearMessage(param0);
    StringTemplate_SetNumber(param0->unk_164, 0, v2, 5, 2, 1);

    param0->unk_3BC = 30;

    WiFiMenuApp_ShowMessageBox(param0, v1);

    switch (v3) {
    case 1:
    case 4:
    case 5:
    case 11:
        param0->unk_3A8 = 10;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        param0->unk_3A8 = 10;
        break;
    case 10:
        param0->unk_3A8 = 10;
        break;
    case 0:
    case 2:
    case 3:
    default:
        param0->unk_3A8 = 35;
        break;
    }
}

static int WiFiMenuApp_StateDismissError(WiFiMenuApp *param0, int param1)
{
    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        if (Window_IsInUse(&param0->unk_360)) {
            Window_EraseMessageBox(&param0->unk_360, 0);
            Window_Remove(&param0->unk_360);
        }

        param0->unk_3A8 = 8;
    }

    return param1;
}

static int WiFiMenuApp_StateTo9(WiFiMenuApp *param0, int param1)
{
    param0->unk_3A8 = 9;
    return param1;
}

static int WiFiMenuApp_StateTo11(WiFiMenuApp *param0, int param1)
{
    param0->unk_3A8 = 11;
    return param1;
}

static int WiFiMenuApp_StateWaitErrorAck(WiFiMenuApp *param0, int param1)
{
    if (param0->unk_3BC > 0) {
        param0->unk_3BC--;
        return param1;
    }

    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        if (Window_IsInUse(&param0->unk_360)) {
            Window_EraseMessageBox(&param0->unk_360, 0);
            Window_Remove(&param0->unk_360);
        }

        WiFiMenuApp_ShowMessage(param0, 88, 0);
        param0->unk_3A8 = 11;
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmDisconnect(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 12;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessDisconnect(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        return param1;
    } else if (v1 == 0) {
        CommManager_LogoutWifi();
        WiFiMenuApp_SetCommState(param0, 16);
        param0->unk_3A8 = 13;
    } else {
        WiFiMenuApp_SetCommState(param0, 16);
        CommManager_LogoutWifi();
        CommInfo_Delete();
        param0->unk_3AC = 8;
        param0->unk_3A8 = 34;
    }

    WiFiMenuApp_ClearMessage(param0);
    return param1;
}

static int WiFiMenuApp_StateHandleDisconnect(WiFiMenuApp *param0, int param1)
{
    int v0;
    NARC *v1;

    if (!WirelessDriver_IsReady()) {
        if (WiFiMenuAppBoard_IsActive(&param0->unk_3EC) == 1) {
            SetScreenColorBrightness(DS_SCREEN_MAIN, COLOR_BLACK);
            SetScreenColorBrightness(DS_SCREEN_SUB, COLOR_BLACK);
            WiFiMenuAppBoard_Free(&param0->unk_3EC);

            for (v0 = 0; v0 < (32 + 1); v0++) {
                param0->unk_B4C[v0] = NULL;
            }

            RenderOam_ClearMain(54);
            RenderOam_ClearSub(54);
        }

        if (WiFiMenuApp_IsTouchScreenActive(param0) == 1) {
            WiFiMenuApp_FreeTouchScreen(param0);
        }

        if (Window_IsInUse(&param0->unk_350)) {
            Window_EraseStandardFrame(&param0->unk_350, 0);
            Window_Remove(&param0->unk_350);
        }

        if (Window_IsInUse(&param0->unk_340)) {
            Window_Remove(&param0->unk_340);
        }

        Bg_ClearTilemap(param0->unk_15C, BG_LAYER_MAIN_3);

        v1 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, HEAP_ID_54);
        WiFiMenuApp_LoadMainBgGraphics(param0, v1);
        NARC_dtor(v1);

        inline_ov96_0223BDEC(&param0->unk_E2C, 1);

        param0->unk_1158 = 1;

        if (param0->unk_14C) {
            Window_Remove(&param0->unk_370);
            ListMenu_Free(param0->unk_150, NULL, NULL);
            param0->unk_150 = NULL;
            StringList_Free(param0->unk_14C);
            param0->unk_14C = NULL;
        }

        MI_CpuClear8(param0->unk_0C, 32);
        MI_CpuClear8(param0->unk_2C, 32);
        MI_CpuClear8(param0->unk_4C, 32 * sizeof(int));
        MI_CpuClear8(param0->unk_CC, 32 * sizeof(int));

        WiFiMenuApp_CreateHeaderWindow(param0);
        param0->unk_04 = CommManager_LoginWifiBattleServer(param0->saveData, sizeof(WFCStatusBuffer));
        WiFiMenuApp_ShowMessage(param0, 23, 1);
        GF_ASSERT(param0->unk_188 == NULL);
        param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
        param0->unk_3A8 = 14;
    }

    return param1;
}

static int WiFiMenuApp_StateWaitBattleWifiLogin(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != FALSE) {
        return param1;
    }

    if (NintendoWFC_GetNeedsGameSave()) {
        param0->unk_3A8 = 69;
        WiFiMenuApp_ShowMessage(param0, 30, 1);
        GF_ASSERT(param0->unk_188 == NULL);
        param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
    }

    if (CommManager_IsLoginBattleWifi()) {
        if (param0->unk_3C8) {
            param0->unk_3A8 = 16;
        } else {
            WiFiMenuApp_SetupOwnStatus(param0, 16);
            WiFiMenuApp_BuildVisibleFriendList(param0);
            param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
        }
    } else if (CommManager_CheckWifiError() || CommManager_GetMatchmakingState() == 3) {
        WiFiMenuApp_HandleWifiError(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateSaveStateInit(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (NintendoWFC_GetNeedsGameSave()) {
        SaveData_SaveStateInit(param0->saveData, 0);
        param0->unk_3A8 = 71;
        return param1;
    }

    if (CommManager_IsLoginBattleWifi()) {
        if (param0->unk_3C8) {
            param0->unk_3A8 = 16;
        } else {
            WiFiMenuApp_SetupOwnStatus(param0, 16);
            WiFiMenuApp_BuildVisibleFriendList(param0);
            param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
        }
    } else if (CommManager_CheckWifiError() || (CommManager_GetMatchmakingState() == 3)) {
        WiFiMenuApp_HandleWifiError(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateSaveStateMain(WiFiMenuApp *param0, int param1)
{
    if (NintendoWFC_GetNeedsGameSave()) {
        int v0 = SaveData_SaveStateMain(param0->saveData);

        if ((v0 != 0) && (v0 != 1)) {
            NintendoWFC_ResetNeedsGameSave();
        } else {
            return param1;
        }
    }

    if (CommManager_IsLoginBattleWifi()) {
        if (param0->unk_3C8) {
            param0->unk_3A8 = 16;
        } else {
            WiFiMenuApp_SetupOwnStatus(param0, 16);
            WiFiMenuApp_BuildVisibleFriendList(param0);
            param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
        }
    } else if (CommManager_CheckWifiError() || (CommManager_GetMatchmakingState() == 3)) {
        WiFiMenuApp_HandleWifiError(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateWaitMatchEnd(WiFiMenuApp *param0, int param1)
{
    int v0;

    if (param0->unk_3BC > 0) {
        param0->unk_3BC--;
        return param1;
    }

    if (CommManager_IsLoginBattleMatchWifi()) {
        param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
    } else if (CommManager_CheckWifiError() || (CommManager_GetMatchmakingState() == 3)) {
        WiFiMenuApp_HandleWifiError(param0);
    } else if ((CommManager_GetMatchmakingState() >= 4) || CommManager_GetDisconnectedWifi() || !CommSys_IsPlayerConnected(0)) {
        CommManager_EndWifiMatch();
        param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
    }

    return param1;
}

static int WiFiMenuApp_StateShowConnecting(WiFiMenuApp *param0, int param1)
{
    WiFiMenuApp_ClearMessage(param0);
    WiFiMenuApp_ShowMessageBox(param0, 19);

    param0->unk_3A8 = 17;
    param0->unk_3C8 = 0;

    return param1;
}

static int WiFiMenuApp_StateHandleBack(WiFiMenuApp *param0, int param1)
{
    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        if (param0->unk_3B4 == 1) {
            param0->unk_3AC = 10;
            param0->unk_3A8 = 34;
            CommManager_LogoutWifi();
        } else if (0 == WiFiList_GetValidFriendsCount(param0->unk_00)) {
            WiFiMenuApp_ShowMessage(param0, 26, 1);
            param0->unk_3A8 = 59;
            param0->unk_3BC = 1;
        } else {
            WiFiMenuApp_SetupOwnStatus(param0, 16);
            WiFiMenuApp_BuildVisibleFriendList(param0);

            param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();

            if (Window_IsInUse(&param0->unk_360)) {
                Window_EraseMessageBox(&param0->unk_360, 0);
                Window_Remove(&param0->unk_360);
            }
        }
    }

    return param1;
}

static void WiFiMenuApp_DrawPlayerStatusWindow(WiFiMenuApp *param0)
{
    TextColor v0;
    int v1, v2, v3;
    TrainerInfo *v4 = SaveData_GetTrainerInfo(param0->saveData);
    String *v5 = TrainerInfo_NameNewString(v4, 54);
    u32 v6;

    if (!Window_IsInUse(&param0->unk_340)) {
        String_Free(v5);
        return;
    }

    Window_FillTilemap(&param0->unk_340, 0);

    v1 = TrainerInfo_Gender(v4);

    if (v1 == 0) {
        v0 = TEXT_COLOR(5, 6, 0);
    } else {
        v0 = TEXT_COLOR(3, 4, 0);
    }

    Text_AddPrinterWithParamsAndColor(&param0->unk_340, FONT_SYSTEM, v5, 32, 0, TEXT_SPEED_NO_TRANSFER, v0, NULL);
    String_Free(v5);

    v6 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);
    v3 = WiFiMenuApp_GetCommStateMessage(v6, &v0);

    if (v6 == 1) {
        if (NintendoWFC_GetHostFriendIdx() == -1) {
            MessageLoader_GetString(param0->unk_168, v3, param0->unk_170);
        } else {
            v1 = WiFiList_GetFriendField(param0->unk_00, NintendoWFC_GetHostFriendIdx(), 8);

            if (0 == v1) {
                v0 = TEXT_COLOR(5, 6, 0);
            } else if (1 == v1) {
                v0 = TEXT_COLOR(3, 4, 0);
            }

            String_CopyChars(param0->unk_170, WiFiList_GetFriendPlayerName(param0->unk_00, NintendoWFC_GetHostFriendIdx()));
        }
    } else {
        MessageLoader_GetString(param0->unk_168, v3, param0->unk_170);
    }

    Text_AddPrinterWithParamsAndColor(&param0->unk_340, FONT_SYSTEM, param0->unk_170, 102, 0, TEXT_SPEED_NO_TRANSFER, v0, NULL);
    WiFiMenuApp_DrawStateIconToBg(param0->unk_15C, &param0->unk_BD0, 1, 2, 1, v6);

    if (param0->unk_04->ownStatus.voiceChatEnabled) {
        v2 = 8;
    } else {
        v2 = 1;
    }

    WiFiMenuApp_DrawScreenDataTilemap(param0->unk_15C, &param0->unk_BD0, 1, 26, 1, v2, 0);
    Window_ScheduleCopyToVRAM(&param0->unk_340);
}

static void WiFiMenuApp_ListMenuSoundCallback(ListMenu *param0, u32 param1, u8 param2)
{
    if (param2 == 0) {
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
    }
}

static void WiFiMenuApp_CreateStatusWindows(WiFiMenuApp *param0)
{
    if (Window_IsInUse(&param0->unk_340)) {
        Window_Remove(&param0->unk_340);
    }

    if (Window_IsInUse(&param0->unk_350)) {
        Window_EraseStandardFrame(&param0->unk_350, 0);
        Window_Remove(&param0->unk_350);
    }

    Window_Add(param0->unk_15C, &param0->unk_340, 3, 1, 1, 28, 2, 13, (512 - 18 * 3) - (28 * 2));
    Window_Add(param0->unk_15C, &param0->unk_350, 1, 1, 1, 28, 2, 13, ((512 - (18 + 12)) - 9) - (28 * 2));
    Window_FillTilemap(&param0->unk_350, 15);
    Window_ScheduleCopyToVRAM(&param0->unk_350);
    Window_DrawStandardFrame(&param0->unk_350, 0, (512 - (18 + 12)) - 9, 11);
}

static int WiFiMenuApp_StateInitBoard(WiFiMenuApp *param0, int param1)
{
    int v0, v1;
    int v2 = 0;
    NARC *v3;
    WiFiMenuAppActor *v4;
    int v5;

    if (IsScreenFadeDone() == FALSE) {
        return param1;
    }

    if (CommManager_CheckWifiError() == 0) {
        if (!CommManager_IsLoginBattleMatchWifi()) {
            return param1;
        }
    }

    NintendoWFC_SetHostMatchCallback(WFCHostMatch_IsCompatible);

    inline_ov96_0223BDEC(&param0->unk_E2C, 0);

    v3 = NARC_ctor(NARC_INDEX_DATA__WIFIP2PMATCH, HEAP_ID_54);

    WiFiMenuApp_LoadScreenData(param0->unk_15C, &param0->unk_BD0, v3, 54);
    WiFiMenuApp_RestoreVoiceChat(param0);
    WiFiMenuApp_ClearMessage(param0);

    Bg_ClearTilemap(param0->unk_15C, BG_LAYER_MAIN_3);

    if (param0->unk_14C) {
        Window_Remove(&param0->unk_370);
        ListMenu_Free(param0->unk_150, NULL, NULL);
        param0->unk_150 = NULL;
        StringList_Free(param0->unk_14C);
        param0->unk_14C = NULL;
    }

    if (WiFiMenuAppBoard_IsActive(&param0->unk_3EC) == 0) {
        if (param0->unk_04->ownStatus.gender == 0) {
            v5 = 0x0;
        } else {
            v5 = 0x61;
        }

        param0->unk_115A = WiFiList_GetFriendListSize(param0->unk_00);

        WiFiMenuAppBoard_Init(&param0->unk_3EC, 54, v3, param0->unk_15C, v5, param0->unk_115A);
        v4 = WiFiMenuAppBoard_CreatePlayer(&param0->unk_3EC, v5);
        WiFiMenuApp_AddActor(param0, v4);
    }

    if (WiFiMenuApp_IsTouchScreenActive(param0) == 0) {
        WiFiMenuApp_InitTouchScreen(param0, v3, HEAP_ID_54);
    }

    WiFiMenuApp_RedrawTouchScreen(param0, HEAP_ID_54);
    WiFiMenuApp_ClearMessage(param0);
    WiFiMenuApp_BuildVisibleFriendList(param0);
    WiFiMenuApp_CreateStatusWindows(param0);
    WiFiMenuApp_SetCommState(param0, 16);

    CommManager_SetState_LoginWifi();
    param0->unk_3D0 = -1;

    NARC_dtor(v3);
    StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_54);
    param0->unk_3A8 = 19;

    CommManager_SetErrorHandling(0, 0);
    return param1;
}

static int WiFiMenuApp_IsMatchmakingStarted(WiFiMenuApp *param0)
{
    if (CommManager_GetMatchmakingState() == 1) {
        return 1;
    }

    return 0;
}

static BOOL WiFiMenuApp_HandleNewClient(WiFiMenuApp *param0)
{
    if (NintendoWFC_GetLatestNewClientFriendIdx() != WFC_NOT_A_FRIEND) {
        NintendoWFC_SetVoiceChatEnabled(param0->unk_04->ownStatus.voiceChatEnabled);
        return 1;
    }

    return 0;
}

static int WiFiMenuApp_UpdateBoardActors(WiFiMenuApp *param0)
{
    int v0;
    int v1, v2;
    WiFiMenuAppActor *v3;
    BOOL v4;
    WFCTrainerInfo *v5;
    BOOL v6;
    BOOL v7;

    v0 = WiFiMenuApp_BuildVisibleFriendList(param0);
    v6 = 0;
    v7 = 0;

    if (memcmp(param0->unk_0C, param0->unk_2C, sizeof(u8) * 32) != 0) {
        for (v1 = 0; v1 < 32; v1++) {
            v4 = 0;

            for (v2 = 0; v2 < 32; v2++) {
                if (param0->unk_0C[v2] == param0->unk_2C[v1]) {
                    v4 = 1;
                    break;
                }
            }

            if ((v4 == 0) && (param0->unk_2C[v1] != 0)) {
                v3 = WiFiMenuApp_GetActorByIndex(param0, param0->unk_2C[v1]);

                if (v3 != NULL) {
                    WiFiMenuAppBoard_RemoveActor(&param0->unk_3EC, v3);
                    WiFiMenuApp_RemoveActor(param0, v3);
                    WiFiMenuApp_ClearFriendListState(param0, param0->unk_2C[v1]);
                    WiFiMenuApp_ResetIfCurrentActor(param0, param0->unk_2C[v1], HEAP_ID_54);
                    v7 = 1;
                }
            }

            v4 = 0;

            for (v2 = 0; v2 < 32; v2++) {
                if (param0->unk_0C[v1] == param0->unk_2C[v2]) {
                    v4 = 1;
                    break;
                }
            }

            if ((v4 == 0) && (param0->unk_0C[v1] != 0)) {
                v5 = WiFiMenuApp_GetFriendStatus(param0, param0->unk_0C[v1] - 1);
                v3 = WiFiMenuAppBoard_CreateActor(&param0->unk_3EC, v5->appearance, param0->unk_0C[v1]);

                if (v3) {
                    WiFiMenuApp_SetFriendListState(param0, param0->unk_0C[v1], 2);
                    WiFiMenuApp_AddActor(param0, v3);
                    v6 = 1;
                } else {
                    WiFiMenuApp_SetFriendListState(param0, param0->unk_0C[v1], 1);
                    param0->unk_0C[v1] = 0;
                }
            }
        }

        memcpy(param0->unk_2C, param0->unk_0C, sizeof(u8) * 32);
        WiFiMenuApp_MarkTouchScreenDirty(param0);

        if (v6 == 1) {
            Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
        } else if (v7 == 1) {
            Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
        }
    }

    return v0;
}

static void WiFiMenuApp_RefreshActorList(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0;
    u32 v1;
    u32 v2;
    BOOL v3;
    int v4 = WiFiMenuApp_UpdateFriendActors(param0);

    if (v4 > 0) {
        WiFiMenuApp_RedrawTouchScreen(param0, heapID);
    }
}

static void WiFiMenuApp_UpdateAndRefreshActors(WiFiMenuApp *param0, enum HeapID heapID)
{
    WiFiMenuApp_UpdateBoardActors(param0);
    WiFiMenuApp_RefreshActorList(param0, heapID);
}

static int WiFiMenuApp_StateBoardInput(WiFiMenuApp *param0, int param1)
{
    u32 v0 = 0;
    int v1;
    u32 v2;
    WiFiMenuAppActor *v3;
    u32 v4;

    if (IsScreenFadeDone() == FALSE) {
        return param1;
    }

    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    if (CommManager_GetMatchmakingState() == 4) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 29;
        WiFiMenuApp_SetCommState(param0, 16);
        CommManager_EndWifiMatch();
        return param1;
    }

    WiFiMenuApp_UpdateAndRefreshActors(param0, HEAP_ID_54);
    WiFiMenuApp_UpdateTouchScreenCursor(param0);
    WiFiMenuAppBoard_ResetPalette(&param0->unk_3EC);

    if (WiFiMenuAppBoard_GetFlag(&param0->unk_3EC) == 0) {
        if (NintendoWFC_GetLatestNewClientFriendIdx() == WFC_NOT_A_FRIEND) {
            if (PAD_BUTTON_X & gSystem.pressedKeys) {
                if (WiFiMenuApp_ToggleVoiceChatBackup(param0)) {
                    WiFiMenuApp_ShowMessage(param0, 90, 0);
                } else {
                    WiFiMenuApp_ShowMessage(param0, 91, 0);
                }

                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                WiFiMenuApp_DrawPlayerStatusWindow(param0);
                param0->unk_3A8 = 20;
                WiFiMenuApp_ResetBoardAndRedraw(param0, HEAP_ID_54);
                return param1;
            }
        }

        v2 = WiFiMenuApp_UpdateTouchScreen(param0, HEAP_ID_54);
        v3 = WiFiMenuApp_GetActorByIndex(param0, v2);

        if (v2 != 0) {
            if (v3) {
                WiFiMenuAppBoard_UpdateActorPriority(&param0->unk_3EC, v3);
            } else {
                WiFiMenuAppBoard_ResetActors(&param0->unk_3EC);
            }
        } else {
            WiFiMenuAppBoard_ResetActors(&param0->unk_3EC);
        }
    }

    v1 = WiFiMenuApp_IsMatchmakingStarted(param0);

    if ((0 != v1) && (param0->unk_3D0 != -1)) {
        Sound_PlayEffect(SEQ_SE_DP_UG_020_sseq);
        param0->unk_3A8 = 48;
        return param1;
    }

    if ((param0->unk_3D0 == -1) && (NintendoWFC_GetLatestNewClientFriendIdx() != WFC_NOT_A_FRIEND)) {
        param0->unk_3D0 = NintendoWFC_GetLatestNewClientFriendIdx();
        WiFiMenuApp_SetFriendNameTemplate(param0, param0->unk_3D0);
        WiFiMenuApp_ShowMessage(param0, 76, 0);
        NintendoWFC_SetVoiceChatEnabled(param0->unk_04->ownStatus.voiceChatEnabled);
        param0->unk_3A4 = 0;
    } else if ((param0->unk_3D0 != -1) && (NintendoWFC_GetLatestNewClientFriendIdx() == WFC_NOT_A_FRIEND)) {
        NintendoWFC_SetVoiceChatEnabled(0);
        WiFiMenuApp_SetFriendNameTemplate(param0, param0->unk_3D0);
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        CommManager_EndWifiMatch();
        param0->unk_3A8 = 27;
        return param1;
    }

    if ((NintendoWFC_GetVoiceChatEnabled() == 1) && (NintendoWFC_GetLatestNewClientFriendIdx() == WFC_NOT_A_FRIEND)) {
        NintendoWFC_SetVoiceChatEnabled(0);
    }

    v4 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);

    if (param0->unk_3D0 == -1) {
        if (gSystem.pressedKeys & PAD_BUTTON_B) {
            if (WiFiMenuApp_IsWifiBattleCommState(v4)) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                param0->unk_3A8 = 39;
                WiFiMenuApp_ResetBoardAndRedraw(param0, HEAP_ID_54);
                return param1;
            }
        }

        v0 = WiFiMenuAppBoard_Update(&param0->unk_3EC);
        WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);
    }

    switch (v0) {
    case 0:
        return param1;
    case 1:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        if (WiFiMenuApp_IsWifiBattleCommState(v4)) {
            param0->unk_3A8 = 39;
        } else {
            param0->unk_3AC = 8;
            param0->unk_3A8 = 57;
            WiFiMenuApp_ShowMessage(param0, 25, 1);

            v0 = 0xfffffffe;
        }

        WiFiMenuApp_ResetBoardAndRedraw(param0, HEAP_ID_54);
        return param1;
    case 3:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        if (WiFiMenuApp_IsWifiBattleCommState(v4)) {
            WiFiMenuAppBoard_SetPlayerPalette(&param0->unk_3EC);
            param0->unk_3A8 = 39;
        } else {
            if (v4 == 16) {
                if (CommManager_IsLoginBattleMatchWifi() == 1) {
                    WiFiMenuAppBoard_SetPlayerPalette(&param0->unk_3EC);
                    param0->unk_3A8 = 36;
                }
            }
        }

        WiFiMenuApp_ResetBoardAndRedraw(param0, HEAP_ID_54);
        return param1;
        break;
    case 2:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        if (WiFiMenuApp_IsWifiBattleCommState(v4)) {
            param0->unk_3A8 = 39;
        } else {
            param0->unk_3A8 = 42;
        }

        WiFiMenuApp_ResetBoardAndRedraw(param0, HEAP_ID_54);
        return param1;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return param1;
}

static int WiFiMenuApp_StateHandleNewClient(WiFiMenuApp *param0, int param1)
{
    if (0 != WiFiMenuApp_HandleNewClient(param0)) {
        param0->unk_3A8 = 19;
        WiFiMenuApp_ClearBoardBusyFlag(param0);
    } else if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_3A8 = 19;

        WiFiMenuApp_ClearBoardBusyFlag(param0);
        WiFiMenuApp_ClearMessage(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateWaitForMatch(WiFiMenuApp *param0, int param1)
{
    WFCTrainerInfo *v0;
    int v1;
    int v2;

    v0 = WiFiMenuApp_GetFriendStatus(param0, param0->unk_3E2 - 1);
    v1 = v0->voiceChatEnabled;
    v2 = WiFiMenuApp_GetAdjustedCommState(param0, v0);

    param0->unk_3A0--;

    if (param0->unk_3A0 < 0) {
        param0->unk_3A8 = 70;
    } else if (CommManager_GetMatchmakingState() == 5) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 15, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_GetMatchmakingState() == 3) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 27;
    } else if ((CommManager_GetMatchmakingState() == 4) || (CommManager_GetDisconnectedWifi())) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 19, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
    } else if (v1 == 0) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 27;
    } else if (v2 != 16) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_GetMatchmakingState() == 1) {
        WiFiMenuApp_ClearMessage(param0);
        WiFiMenuApp_SetCommState(param0, 1);
        param0->unk_3A8 = 24;
        WiFiList_SetHostFriendCurrentDate(param0->unk_00, param0->unk_3E2 - 1);
    }

    return param1;
}

static int WiFiMenuApp_StateSelectFriend(WiFiMenuApp *param0, int param1)
{
    WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
    WiFiMenuApp_ShowMessage(param0, 14, 0);
    WiFiMenuApp_SetCommState(param0, 1);

    param0->unk_3A8 = 23;

    WiFiList_SetHostFriendCurrentDate(param0->unk_00, NintendoWFC_GetHostFriendIdx());

    return param1;
}

static int WiFiMenuApp_StateConfirmFriend(WiFiMenuApp *param0, int param1)
{
    WFCTrainerInfo *v0;
    int v1;
    int v2;

    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    if (NintendoWFC_GetHostFriendIdx() < 0) {
        WiFiMenuApp_ShowMessage(param0, 19, 0);
        param0->unk_3A8 = 27;
        return param1;
    }

    v0 = WiFiMenuApp_GetFriendStatus(param0, NintendoWFC_GetHostFriendIdx());
    v2 = WiFiMenuApp_GetAdjustedCommState(param0, v0);

    if ((v2 != 16) && (v2 != 1)) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 27;
        return param1;
    }

    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
            WiFiMenuApp_ClearMessage(param0);
            param0->unk_3A8 = 24;
        } else {
            WiFiMenuApp_StateFriendAction(param0, param1);
        }
    }

    return param1;
}

static int WiFiMenuApp_StateFriendAction(WiFiMenuApp *param0, int param1)
{
    WFCTrainerInfo *v0;
    int v1;

    if (NintendoWFC_GetHostFriendIdx() < 0) {
        WiFiMenuApp_ShowMessage(param0, 19, 0);
        param0->unk_3A8 = 27;
        return param1;
    }

    v0 = WiFiMenuApp_GetFriendStatus(param0, NintendoWFC_GetHostFriendIdx());
    v1 = WiFiMenuApp_GetAdjustedCommState(param0, v0);

    WiFiMenuApp_UpdateAndRefreshActors(param0, HEAP_ID_54);
    WiFiMenuApp_UpdateTouchScreenCursor(param0);

    if (CommManager_GetMatchmakingState() == 5) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 15, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_GetMatchmakingState() == 3) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 27;
    } else if ((CommManager_GetMatchmakingState() == 4) || (CommManager_GetDisconnectedWifi())) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 19, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
    } else if ((v1 != 16) && (v1 != 1)) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 27;
    } else if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        WiFiMenuApp_ShowMessage(param0, 20, 0);
        param0->unk_3A8 = 25;
    } else {
        if (NintendoWFC_IsPlayerSpeaking()) {
            WiFiMenuApp_DrawScreenDataTilemap(param0->unk_15C, &param0->unk_BD0, 1, 2, 1, 2, 0);
        } else {
            WiFiMenuApp_DrawScreenDataTilemap(param0->unk_15C, &param0->unk_BD0, 1, 2, 1, 3, 0);
        }
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmLeave(WiFiMenuApp *param0, int param1)
{
    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        WiFiList_SetHostFriendCurrentDate(param0->unk_00, NintendoWFC_GetHostFriendIdx());

        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 26;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessLeave(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (v1 == 0xffffffff) {
        if ((CommManager_GetMatchmakingState() >= 4) || CommManager_GetDisconnectedWifi() || !CommSys_IsPlayerConnected(0)) {
            WiFiMenuApp_ClearMessage(param0);

            WiFiMenuApp_SetCommState(param0, 16);
            Menu_DestroyForExit(param0->unk_184, 54);
            param0->unk_3D0 = -1;
            param0->unk_3BC = 20;
            param0->unk_3A8 = 65;
        } else if (CommManager_CheckWifiError()) {
            WiFiMenuApp_HandleWifiError(param0);
        }

        return param1;
    } else if (v1 == 0) {
        if (!CommManager_CheckWifiError()) {
            WiFiMenuApp_SetCommState(param0, 16);
            CommManager_EndBattleWifiMatch();
            param0->unk_3D0 = -1;
            param0->unk_3BC = 20;
            param0->unk_3A8 = 65;
        } else {
            WiFiMenuApp_HandleWifiError(param0);
        }
    } else {
        param0->unk_3A8 = 24;
    }

    WiFiMenuApp_ClearMessage(param0);
    return param1;
}

static int WiFiMenuApp_StateWaitBattleStart(WiFiMenuApp *param0, int param1)
{
    u32 v0;

    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);

    if (v0 != 16) {
        WiFiMenuApp_SetCommState(param0, 16);
    }

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        param0->unk_3BC = 30;
        return param1;
    }

    param0->unk_3BC--;

    if ((gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) || (param0->unk_3BC == 0)) {
        WiFiMenuApp_ClearMessage(param0);
        CommManager_EndWifiMatch();
        CommManager_SetState_LoginWifi();

        if (WiFiMenuAppBoard_IsActive(&param0->unk_3EC) == 0) {
            param0->unk_3BC = 20;
            param0->unk_3A8 = 65;
        } else {
            WiFiMenuApp_RestoreVoiceChat(param0);
            WiFiMenuApp_DrawPlayerStatusWindow(param0);

            param0->unk_3D0 = -1;
            param0->unk_3A8 = 19;

            WiFiMenuApp_ClearBoardBusyFlag(param0);
        }
    }

    return param1;
}

static int WiFiMenuApp_StateCancelMatch(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        WiFiMenuApp_ClearMessage(param0);
        WiFiMenuApp_SetCommState(param0, 16);
        CommManager_EndWifiMatch();
        param0->unk_3BC = 20;
        param0->unk_3A8 = 65;
    }

    return param1;
}

static int WiFiMenuApp_StateWaitThenLogin(WiFiMenuApp *param0, int param1)
{
    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        param0->unk_3BC = 30;
        return param1;
    }

    param0->unk_3BC--;

    if ((gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) || (param0->unk_3BC == 0)) {
        WiFiMenuApp_ClearMessage(param0);
        WiFiMenuApp_SetCommState(param0, 16);

        CommManager_SetState_LoginWifi();

        if (WiFiMenuAppBoard_IsActive(&param0->unk_3EC) == 0) {
            param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();
        } else {
            WiFiMenuApp_RestoreVoiceChat(param0);
            WiFiMenuApp_DrawPlayerStatusWindow(param0);

            param0->unk_3D0 = -1;
            param0->unk_3A8 = 19;

            WiFiMenuApp_ClearBoardBusyFlag(param0);
        }
    }

    return param1;
}

static int WiFiMenuApp_StateNoop1(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateNoop2(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateNoop3(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateWaitDisconnectMessage(WiFiMenuApp *param0, int param1)
{
    if (param0->unk_3BC > 0) {
        param0->unk_3BC--;
        return param1;
    }

    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        WiFiMenuApp_ShowMessage(param0, 26, 1);
        param0->unk_3A8 = 59;
        param0->unk_3BC = 1;
    }

    return param1;
}

static int WiFiMenuApp_StateOpenActivityMenu(WiFiMenuApp *param0, int param1)
{
    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);
    WiFiMenuApp_ShowMessage(param0, 10, 0);

    param0->unk_3A8 = 40;

    return param1;
}

static int WiFiMenuApp_StateConfirmExitActivity(WiFiMenuApp *param0, int param1)
{
    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 41;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessExitActivity(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    if ((param0->unk_3D0 == -1) && (NintendoWFC_GetLatestNewClientFriendIdx() != WFC_NOT_A_FRIEND)) {
        NintendoWFC_SetVoiceChatEnabled(param0->unk_04->ownStatus.voiceChatEnabled);

        if (v1 == 0xffffffff) {
            Menu_DestroyForExit(param0->unk_184, 54);
        }

        v1 = 1;
    }

    if (v1 == 0xffffffff) {
        return param1;
    } else if (v1 == 0) {
        WiFiMenuApp_SetCommState(param0, 16);
        CommManager_SetState_LoginWifi();
        WiFiMenuApp_ClearBoardBusyFlag(param0);
    } else {
        WiFiMenuApp_ClearBoardBusyFlag(param0);
        WiFiMenuApp_SetBoardBusyFlag(param0, 1);
    }

    param0->unk_3A8 = 19;

    return param1;
}

WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivityBaseEntries[10] = {
    { 0x5D, (u32)0 },
    { 0x5E, (u32)1 },
    { 0x1C, (u32)15 }
};

static WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivityWifiClubEntry = {
    0x22,
    (u32)29
};

static WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivityBattleParkEntry = {
    0x20,
    (u32)21
};

static WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivityPoffinEntry = {
    0x1E,
    (u32)19
};

static WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivityCancelEntry = {
    0x29,
    (u32)0xfffffffe
};

WiFiMenuAppActivityMenuEntry sWiFiMenuAppPlazaMinigameEntries[] = {
    { 0x47, (u32)23 },
    { 0x47, (u32)25 },
    { 0x47, (u32)27 },
    { 0x29, (u32)0xfffffffe }
};

WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivitySubMenu0Entries[] = {
    { 0x5F, (u32)11 },
    { 0x60, (u32)9 },
    { 0x61, (u32)10 },
    { 0x29, (u32)0xfffffffe }
};

WiFiMenuAppActivityMenuEntry sWiFiMenuAppActivitySubMenu1Entries[] = {
    { 0x62, (u32)14 },
    { 0x63, (u32)12 },
    { 0x64, (u32)13 },
    { 0x29, (u32)0xfffffffe }
};

static ListMenuTemplate sWiFiMenuAppActivityListTemplate = {
    NULL,
    WiFiMenuApp_ListMenuSoundCallback,
    NULL,
    NULL,
    0x3,
    0x3,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL
};

static const ListMenuTemplate sWiFiMenuAppBattleModeListTemplate = {
    NULL,
    WiFiMenuApp_ListMenuSoundCallback,
    NULL,
    NULL,
    NELEMS(sWiFiMenuAppActivitySubMenu0Entries),
    NELEMS(sWiFiMenuAppActivitySubMenu0Entries),
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL
};

static const ListMenuTemplate sWiFiMenuAppMinigameListTemplate = {
    NULL,
    WiFiMenuApp_ListMenuSoundCallback,
    NULL,
    NULL,
    NELEMS(sWiFiMenuAppPlazaMinigameEntries),
    NELEMS(sWiFiMenuAppPlazaMinigameEntries),
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL
};

static int WiFiMenuApp_CreateActivityListMenu(WiFiMenuApp *param0, int param1)
{
    int v0, v1;
    ListMenuTemplate v2;
    WiFiMenuAppActivityMenuEntry *v3;

    v1 = 3;
    v2 = sWiFiMenuAppActivityListTemplate;
    v3 = sWiFiMenuAppActivityBaseEntries;

    if (WiFiMenuApp_HasPoffinCase(param0) == 1) {
        v1++;
        v2.count++;
        v2.maxDisplay++;
        v3[v1 - 1] = sWiFiMenuAppActivityPoffinEntry;
    }

    if (WiFiMenuApp_IsBattleParkAccessed(param0) == 1) {
        v1++;
        v2.count++;
        v2.maxDisplay++;

        v3[v1 - 1] = sWiFiMenuAppActivityBattleParkEntry;
    }

    if (WiFiMenuApp_CanAccessWifiClub(param0) == 1) {
        v1++;
        v2.count++;
        v2.maxDisplay++;
        v3[v1 - 1] = sWiFiMenuAppActivityWifiClubEntry;
    }

    {
        v1++;
        v2.count++;
        v2.maxDisplay++;
        v3[v1 - 1] = sWiFiMenuAppActivityCancelEntry;
    }

    param0->unk_154 = StringList_New(v1, HEAP_ID_54);

    for (v0 = 0; v0 < v1; v0++) {
        StringList_AddFromMessageBank(param0->unk_154, param0->unk_168, v3[v0].unk_00, v3[v0].unk_04);
    }

    if (Window_IsInUse(&param0->unk_380)) {
        Window_EraseStandardFrame(&param0->unk_380, 0);
        Window_Remove(&param0->unk_380);
    }

    Window_Add(param0->unk_15C, &param0->unk_380, 2, 16, 3, 15, v1 * 2, 13, ((((((512 - (18 + 12)) - 9) - 10) - (18 + 12 + 24)) - (27 * 4)) - (11 * 22)) - v1 * 2);
    Window_DrawStandardFrame(&param0->unk_380, 1, (512 - (18 + 12)) - 9, 11);

    v2.choices = param0->unk_154;
    v2.window = &param0->unk_380;

    param0->unk_158 = ListMenu_New(&v2, 0, param0->unk_3D4, HEAP_ID_54);

    Window_ScheduleCopyToVRAM(&param0->unk_380);
    WiFiMenuApp_ShowMessage(param0, 8, 0);
    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    param0->unk_3A8 = 37;
    return param1;
}

static int WiFiMenuApp_StateProcessActivityList(WiFiMenuApp *param0, int param1)
{
    u32 v0;
    int v1 = WiFiMenuApp_GetUsablePartyCount(param0);
    int v2 = WiFiMenuApp_GetPoffinAvailability(param0);

    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        if (0 != WiFiMenuApp_HandleNewClient(param0)) {
            param0->unk_3A8 = 19;
            Window_EraseStandardFrame(&param0->unk_380, 0);
            Window_Remove(&param0->unk_380);
            ListMenu_Free(param0->unk_158, NULL, &param0->unk_3D4);
            StringList_Free(param0->unk_154);
            WiFiMenuApp_ClearMessage(param0);
        }

        return param1;
    }

    v0 = ListMenu_ProcessInput(param0->unk_158);

    if (0 != WiFiMenuApp_HandleNewClient(param0)) {
        v0 = 0xfffffffe;
    }

    switch (v0) {
    case 0xffffffff:
        return param1;
    case 0xfffffffe:
        param0->unk_3A8 = 19;
        WiFiMenuApp_ClearMessage(param0);
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        break;
    default:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        if ((v0 == 19) && (v2 != 0)) {
            if (v2 == 1) {
                WiFiMenuApp_ShowMessage(param0, 104, 0);
            } else if (v2 == 3) {
                WiFiMenuApp_ShowMessage(param0, 106, 0);
            } else {
                WiFiMenuApp_ShowMessage(param0, 105, 0);
            }

            param0->unk_3A8 = 29;
        } else if ((v0 == 15) && (2 > v1)) {
            WiFiMenuApp_ShowMessage(param0, 89, 0);
            param0->unk_3A8 = 29;
        } else if ((v0 == 1) && (2 > v1)) {
            WiFiMenuApp_ShowMessage(param0, 103, 0);
            param0->unk_3A8 = 29;
        } else if ((v0 == 0) || (v0 == 1) || (v0 == 29)) {
            Window_EraseStandardFrame(&param0->unk_380, 0);
            Window_Remove(&param0->unk_380);
            ListMenu_Free(param0->unk_158, NULL, &param0->unk_3D4);
            StringList_Free(param0->unk_154);
            WiFiMenuApp_CreateActivitySubMenu(param0, v0);
            param0->unk_3A8 = 38;
            return param1;
        } else {
            WiFiMenuApp_SetCommState(param0, v0);
            param0->unk_3A8 = 19;
            WiFiMenuApp_ClearMessage(param0);
        }

        {
            BOOL v3 = 1;

            if (WiFiMenuApp_IsWifiClubCommState(v0) && (param0->unk_3A8 == 19)) {
                param0->unk_3A8 = 68;
                WiFiMenuApp_StartWifiBattle(param0, -1, v0);
                WiFiMenuApp_SetCommStateForSelection(v0);
                WiFiMenuApp_SetCommState(param0, v0);
                param0->unk_3AC = WiFiMenuApp_GetWifiConnectionTypeFromState(v0);
                v3 = 0;
            } else {
                WiFiMenuApp_StartWifiBattle(param0, -1, v0);
                WiFiMenuApp_SetCommStateForSelection(v0);
            }

            if (param0->unk_3A8 == 19) {
                WiFiMenuApp_SetBoardBusyFlag(param0, v3);
            }
        }
        break;
    }

    Window_EraseStandardFrame(&param0->unk_380, 0);
    Window_Remove(&param0->unk_380);
    ListMenu_Free(param0->unk_158, NULL, &param0->unk_3D4);
    StringList_Free(param0->unk_154);

    return param1;
}

static int WiFiMenuApp_StateStartBattleMatch(WiFiMenuApp *param0, int param1)
{
    u32 v0;

    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    if (0 != WiFiMenuApp_HandleNewClient(param0)) {
        param0->unk_3A8 = 19;
    }

    if (CommManager_IsLoginBattleMatchWifi()) {
        CommManager_SetErrorHandling(0, 1);

        CommSys_SetRecvLimitEnabled(0);
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_54);

        param0->unk_3E4 = 0;

        CommInfo_Init(param0->saveData, NULL);

        CommInfo_SendPlayerInfo();

        CommInfo_MarkDataRead(CommSys_CurNetId());
        param1 = 2;
    }

    return param1;
}

static int WiFiMenuApp_CreateActivitySubMenu(WiFiMenuApp *param0, int param1)
{
    int v0, v1;
    ListMenuTemplate v2;
    WiFiMenuAppActivityMenuEntry *v3;

    switch (param1) {
    case 0:
        v3 = sWiFiMenuAppActivitySubMenu0Entries;
        v1 = NELEMS(sWiFiMenuAppActivitySubMenu0Entries);
        param0->unk_3DC = 1;
        v2 = sWiFiMenuAppBattleModeListTemplate;
        break;
    case 1:
        v3 = sWiFiMenuAppActivitySubMenu1Entries;
        v1 = NELEMS(sWiFiMenuAppActivitySubMenu1Entries);
        param0->unk_3DC = 0;
        v2 = sWiFiMenuAppBattleModeListTemplate;
        break;
    case 29:
        v3 = sWiFiMenuAppPlazaMinigameEntries;
        v1 = NELEMS(sWiFiMenuAppPlazaMinigameEntries);
        v2 = sWiFiMenuAppMinigameListTemplate;
        param0->unk_3DC = 2;
        break;
    }

    param0->unk_154 = StringList_New(v1, HEAP_ID_54);

    for (v0 = 0; v0 < v1; v0++) {
        if (v3[v0].unk_00 != 71) {
            StringList_AddFromMessageBank(param0->unk_154, param0->unk_168, v3[v0].unk_00, v3[v0].unk_04);
        } else {
            StringTemplate_SetPlazaMinigameName(param0->unk_164, 0, v0);
            MessageLoader_GetString(param0->unk_168, v3[v0].unk_00, param0->unk_170);
            StringTemplate_Format(param0->unk_164, param0->unk_178, param0->unk_170);
            StringList_AddFromString(param0->unk_154, param0->unk_178, v3[v0].unk_04);
        }
    }

    if (Window_IsInUse(&param0->unk_380)) {
        Window_EraseStandardFrame(&param0->unk_380, 0);
        Window_Remove(&param0->unk_380);
    }

    Window_Add(param0->unk_15C, &param0->unk_380, 2, 16, 9, 15, v1 * 2, 13, ((((((512 - (18 + 12)) - 9) - 10) - (18 + 12 + 24)) - (27 * 4)) - (11 * 22)) - v1 * 2);
    Window_DrawStandardFrame(&param0->unk_380, 1, (512 - (18 + 12)) - 9, 11);

    v2.choices = param0->unk_154;
    v2.window = &param0->unk_380;

    param0->unk_158 = ListMenu_New(&v2, 0, param0->unk_3D6[param0->unk_3DC], HEAP_ID_54);

    Window_ScheduleCopyToVRAM(&param0->unk_380);

    return 1;
}

static int WiFiMenuApp_StateProcessActivitySubMenu(WiFiMenuApp *param0, int param1)
{
    u32 v0;

    WiFiMenuAppBoard_UpdatePalette(&param0->unk_3EC);

    if (0 != WiFiMenuApp_HandleNewClient(param0)) {
        param0->unk_3A8 = 19;
        Window_EraseStandardFrame(&param0->unk_380, 0);
        Window_Remove(&param0->unk_380);
        ListMenu_Free(param0->unk_158, NULL, &param0->unk_3D6[param0->unk_3DC]);
        StringList_Free(param0->unk_154);
        WiFiMenuApp_ClearMessage(param0);
        return param1;
    }

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    v0 = ListMenu_ProcessInput(param0->unk_158);

    switch (v0) {
    case 0xffffffff:
        return param1;
    case 0xfffffffe:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        param0->unk_3A8 = 36;
        break;
    default:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        WiFiMenuApp_SetCommState(param0, v0);
        param0->unk_3A8 = 19;
        WiFiMenuApp_ClearMessage(param0);
        break;
    }

    if (param0->unk_3A8 == 19) {
        BOOL v1 = 1;

        if (WiFiMenuApp_IsWifiClubCommState(v0)) {
            param0->unk_3A8 = 68;
            WiFiMenuApp_StartWifiBattle(param0, -1, v0);
            WiFiMenuApp_SetCommStateForSelection(v0);
            WiFiMenuApp_SetCommState(param0, v0);
            param0->unk_3AC = WiFiMenuApp_GetWifiConnectionTypeFromState(v0);
            v1 = 0;
        } else {
            WiFiMenuApp_StartWifiBattle(param0, -1, v0);
            CommManager_SetState_SingleBattleWifi();
        }

        WiFiMenuApp_SetBoardBusyFlag(param0, v1);
    }

    Window_EraseStandardFrame(&param0->unk_380, 0);
    Window_Remove(&param0->unk_380);
    ListMenu_Free(param0->unk_158, NULL, &param0->unk_3D6[param0->unk_3DC]);
    StringList_Free(param0->unk_154);

    return param1;
}

static const struct {
    u32 unk_00;
    u32 unk_04;
} sWiFiMenuAppFriendActionEntries[] = {
    { 0x27, (u32)1 },
    { 0x29, (u32)0xfffffffe }
};

static const ListMenuTemplate sWiFiMenuAppFriendActionListTemplate = {
    NULL,
    WiFiMenuApp_ListMenuSoundCallback,
    NULL,
    NULL,
    NELEMS(sWiFiMenuAppFriendActionEntries),
    NELEMS(sWiFiMenuAppFriendActionEntries),
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x0,
    0x0,
    0x0,
    NULL
};

static int WiFiMenuApp_StatePrepareFriendAction(WiFiMenuApp *param0, int param1)
{
    int v0;
    u16 v1, v2;
    WFCTrainerInfo *v3;
    WiFiMenuAppActor *v4;
    WiFiMenuAppActor *v5;
    u32 v6;

    v1 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
    v4 = WiFiMenuApp_GetActorByIndex(param0, 0);

    GF_ASSERT(v4);

    v5 = WiFiMenuApp_GetActorByIndex(param0, v1);

    if (v5 == NULL) {
        WiFiMenuApp_SetFriendNameTemplate(param0, v1 - 1);
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 29;
        return param1;
    }

    v6 = WiFiMenuAppBoard_GetActorOppositeDirection(v4);

    WiFiMenuAppBoard_SetActorAnim(&param0->unk_3EC, v5, v6);

    v3 = WiFiMenuApp_GetFriendStatus(param0, v1 - 1);
    v2 = WiFiMenuApp_GetAdjustedCommState(param0, v3);

    param0->unk_3DE = v2;

    WiFiMenuApp_SetFriendNameTemplate(param0, v1 - 1);

    if (v2 == 15) {
        v0 = 3;
    } else if (v2 == 19) {
        v0 = 4;
    } else if (v2 == 18) {
        v0 = 83;
    } else if (v2 == 21) {
        v0 = 5;
    } else if (v2 == 20) {
        v0 = 84;
    } else if (v2 == 23) {
        StringTemplate_SetPlazaMinigameName(param0->unk_164, 1, WiFiPlazaLobbyActivity_00);
        v0 = 6;
    } else if (v2 == 22) {
        v0 = 85;
    } else if (v2 == 25) {
        StringTemplate_SetPlazaMinigameName(param0->unk_164, 1, WiFiPlazaLobbyActivity_01);
        v0 = 6;
    } else if (v2 == 24) {
        v0 = 85;
    } else if (v2 == 27) {
        StringTemplate_SetPlazaMinigameName(param0->unk_164, 1, WiFiPlazaLobbyActivity_02);
        v0 = 6;
    } else if (v2 == 26) {
        v0 = 85;
    } else if (WiFiMenuApp_IsBattleTowerCommState(v2)) {
        v0 = 2;
    } else if (v2 == 8) {
        v0 = 82;
    } else if (WiFiMenuApp_IsBattleModeCommState(v2)) {
        v0 = 81;
    } else if (v2 == 1) {
        v0 = 86;
    } else {
        v0 = 7;
    }

    WiFiMenuApp_ShowMessage(param0, v0, 0);
    param0->unk_3A8 = 43;

    return param1;
}

static int WiFiMenuApp_StateCreateFriendActionMenu(WiFiMenuApp *param0, int param1)
{
    WiFiMenuAppActor *v0;
    u32 v1;
    int v2, v3;
    WFCTrainerInfo *v4;

    if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    v2 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
    v0 = WiFiMenuApp_GetActorByIndex(param0, v2);
    v1 = WiFiMenuApp_HandleNewClient(param0);

    if (0 != v1) {
        WiFiMenuAppBoard_RestoreActorCallback(&param0->unk_3EC, v0);
        WiFiMenuApp_ClearMessage(param0);
        param0->unk_3A8 = 19;
        return param1;
    }

    if (v0 == NULL) {
        WiFiMenuAppBoard_RestoreActorCallback(&param0->unk_3EC, v0);
        ListMenu_Free(param0->unk_158, NULL, NULL);
        WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
        WiFiMenuApp_ShowMessage(param0, 16, 0);
        param0->unk_3A8 = 29;
        return param1;
    } else {
        v4 = WiFiMenuApp_GetFriendStatus(param0, v2 - 1);
        v3 = WiFiMenuApp_GetAdjustedCommState(param0, v4);

        if (param0->unk_3DE != v3) {
            WiFiMenuAppBoard_RestoreActorCallback(&param0->unk_3EC, v0);
            WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
            WiFiMenuApp_ShowMessage(param0, 16, 0);
            param0->unk_3A8 = 29;
            return param1;
        }
    }

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    {
        int v5, v6;
        ListMenuTemplate v7;
        u16 v8, v9, v10;
        WFCTrainerInfo *v11;

        v6 = NELEMS(sWiFiMenuAppFriendActionEntries);
        v7 = sWiFiMenuAppFriendActionListTemplate;
        v8 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
        v11 = WiFiMenuApp_GetFriendStatus(param0, v8 - 1);
        v9 = WiFiMenuApp_GetAdjustedCommState(param0, v11);
        v10 = v11->voiceChatEnabled;

        param0->unk_3E0 = v10;

        v10 += param0->unk_04->ownStatus.voiceChatEnabled;
        param0->unk_154 = StringList_New(v6, HEAP_ID_54);
        v5 = 0;

        for (v5 = 0; v5 < NELEMS(sWiFiMenuAppFriendActionEntries); v5++) {
            if (v5 == 0) {
                if (WiFiMenuApp_IsSingleBattleCommState(v9) || (v9 == 0) || (v9 == 28) || (v9 >= 29)) {
                    v7.maxDisplay -= 1;
                    v7.count -= 1;
                    v6 -= 1;
                } else if (v9 == 16) {
                    if (v10 == 2) {
                        StringList_AddFromMessageBank(param0->unk_154, param0->unk_168, 36, sWiFiMenuAppFriendActionEntries[v5].unk_04);
                    } else {
                        v7.maxDisplay -= 1;
                        v7.count -= 1;
                        v6 -= 1;
                    }
                } else {
                    StringList_AddFromMessageBank(param0->unk_154, param0->unk_168, sWiFiMenuAppFriendActionEntries[v5].unk_00, sWiFiMenuAppFriendActionEntries[v5].unk_04);
                }
            } else {
                StringList_AddFromMessageBank(param0->unk_154, param0->unk_168, sWiFiMenuAppFriendActionEntries[v5].unk_00, sWiFiMenuAppFriendActionEntries[v5].unk_04);
            }
        }

        Window_Add(param0->unk_15C, &param0->unk_380, 2, 16, 11 + ((3 - v6) * 2), 15, v6 * 2, 13, (((((512 - (18 + 12)) - 9) - 10) - (18 + 12 + 24)) - (27 * 4)) - (11 * 22));
        Window_DrawStandardFrame(&param0->unk_380, 1, (512 - (18 + 12)) - 9, 11);

        v7.choices = param0->unk_154;
        v7.window = &param0->unk_380;

        param0->unk_158 = ListMenu_New(&v7, 0, 0, HEAP_ID_54);

        Window_ScheduleCopyToVRAM(&param0->unk_380);
    }

    param0->unk_3A8 = 44;
    return param1;
}

static BOOL WiFiMenuApp_IsPartyValidForWifi(WFCTrainerInfo *param0)
{
    int v0;

    for (v0 = 0; v0 < 6; v0++) {
        if (495 == param0->partySpecies[v0]) {
            return 0;
        }

        if (495 < param0->partySpecies[v0]) {
            return 0;
        }

        if (467 < param0->partyHeldItems[v0]) {
            return 0;
        }
    }

    return 1;
}

static u32 WiFiMenuApp_GetPoffinAvailability(WiFiMenuApp *param0)
{
    if (!Bag_HasItemsInPocket(SaveData_GetBag(param0->saveData), POCKET_BERRIES)) {
        return 1;
    }

    if (!Bag_GetItemQuantity(SaveData_GetBag(param0->saveData), ITEM_POFFIN_CASE, HEAP_ID_54)) {
        return 3;
    }

    if (PoffinCase_CountFilledSlots(SaveData_GetPoffinCase(param0->saveData)) >= MAX_POFFINS) {
        return 2;
    }

    return 0;
}

static void WiFiMenuApp_PlayLobbyBgm(void)
{
    u32 bgmID;

    NintendoWFC_SetVoiceChatEnabled(0);

    if (WiFiMenuApp_IsLobbyBgmPlaying() == 0) {
        if (IsNight() == FALSE) {
            bgmID = SEQ_PC_01_sseq;
        } else {
            bgmID = SEQ_PC_02_sseq;
        }

        Sound_SetScene(SOUND_SCENE_NONE);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_11, bgmID, 1);
    } else {
        Sound_SetInitialVolumeForSequence(Sound_GetCurrentBGM(), 120);
    }
}

static BOOL WiFiMenuApp_IsLobbyBgmPlaying(void)
{
    u32 v0 = Sound_GetCurrentBGM();

    if ((v0 != 1085) && (v0 != 1086)) {
        return 0;
    }

    return 1;
}

static void WiFiMenuApp_SaveWifiClubJournalEvent(WiFiMenuApp *param0, u32 unused)
{
    JournalEntry *journalEntry = SaveData_GetJournal(param0->saveData);
    void *journalEntryOnlineEvent = JournalEntry_CreateEventMisc(54, ONLINE_EVENT_WIFI_CLUB);

    JournalEntry_SaveData(journalEntry, journalEntryOnlineEvent, JOURNAL_ONLINE_EVENT);
}

static int WiFiMenuApp_StateProcessFriendAction(WiFiMenuApp *param0, int param1)
{
    u32 v0;
    int v1, v2, v3 = 0, v4;
    u16 v5;
    int v6;
    WiFiMenuAppActor *v7;
    WFCTrainerInfo *v8;

    v0 = ListMenu_ProcessInput(param0->unk_158);
    v6 = WiFiMenuApp_HandleNewClient(param0);

    if (0 != v6) {
        v0 = 0xfffffffe;
    }

    v2 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
    v7 = WiFiMenuApp_GetActorByIndex(param0, v2);

    if (CommManager_CheckWifiError()) {
        Window_EraseStandardFrame(&param0->unk_380, 0);
        Window_Remove(&param0->unk_380);
        ListMenu_Free(param0->unk_158, NULL, NULL);
        StringList_Free(param0->unk_154);

        if (v7 != NULL) {
            WiFiMenuAppBoard_RestoreActorCallback(&param0->unk_3EC, v7);
        }

        WiFiMenuApp_HandleWifiError(param0);
        return param1;
    }

    switch (v0) {
    case 0xffffffff:
        if (v7 == NULL) {
            ListMenu_Free(param0->unk_158, NULL, NULL);
            WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
            WiFiMenuApp_ShowMessage(param0, 16, 0);
            param0->unk_3A8 = 29;
            v3 = 1;
            break;
        } else {
            v8 = WiFiMenuApp_GetFriendStatus(param0, v2 - 1);
            v1 = WiFiMenuApp_GetAdjustedCommState(param0, v8);
            v4 = v8->voiceChatEnabled;

            if ((param0->unk_3DE != v1) || ((WiFiMenuApp_IsWifiClubCommState(v1) == 0) && (param0->unk_3E0 != v4))) {
                WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                WiFiMenuApp_ShowMessage(param0, 16, 0);
                param0->unk_3A8 = 29;
                v3 = 1;
                break;
            }
        }

        return param1;

    case 0xfffffffe:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        param0->unk_3A8 = 19;
        break;
    default:
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        if (v0 == 1) {
            param0->unk_3A8 = 19;
            param0->unk_3E2 = v2;

            if (v2 != 0) {
                int v9 = WiFiMenuApp_GetUsablePartyCount(param0);
                int v10 = WiFiMenuApp_GetPoffinAvailability(param0);

                v8 = WiFiMenuApp_GetFriendStatus(param0, v2 - 1);
                v1 = WiFiMenuApp_GetAdjustedCommState(param0, v8);
                v4 = v8->voiceChatEnabled;

                if ((param0->unk_3DE != v1) || ((WiFiMenuApp_IsWifiClubCommState(v1) == 0) && (param0->unk_3E0 != v4))) {
                    WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                    WiFiMenuApp_ShowMessage(param0, 16, 0);
                    param0->unk_3A8 = 29;
                    v3 = 1;
                    break;
                }

                if (!WiFiMenuApp_IsPartyValidForWifi(v8)) {
                    WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                    WiFiMenuApp_ShowMessage(param0, 16, 0);
                    param0->unk_3A8 = 29;
                    v3 = 1;
                    break;
                }

                if (WiFiMenuApp_IsTowerCommState(v1) && (2 > v9)) {
                    if (15 == v1) {
                        WiFiMenuApp_ShowMessage(param0, 89, 0);
                    } else {
                        WiFiMenuApp_ShowMessage(param0, 103, 0);
                    }

                    param0->unk_3A8 = 29;
                    v3 = 1;
                    break;
                }

                if ((v1 == 19) && (v10 != 0)) {
                    if (v10 == 1) {
                        WiFiMenuApp_ShowMessage(param0, 104, 0);
                    } else if (v10 == 3) {
                        WiFiMenuApp_ShowMessage(param0, 106, 0);
                    } else {
                        WiFiMenuApp_ShowMessage(param0, 105, 0);
                    }

                    param0->unk_3A8 = 29;
                    v3 = 1;
                    break;
                }

                if (WiFiMenuApp_IsWifiClubCommState(v1) == 0) {
                    if (v4 != param0->unk_04->ownStatus.voiceChatEnabled) {
                        if (v4) {
                            WiFiMenuApp_ShowMessage(param0, 134, 0);
                        } else {
                            WiFiMenuApp_ShowMessage(param0, 135, 0);
                        }

                        WiFiMenuApp_SetCommState(param0, WiFiMenuApp_GetPairedCommState(v1));

                        param0->unk_3A8 = 63;
                        v3 = 1;
                        break;
                    }
                }

                v1 = WiFiMenuApp_GetPairedCommState(v1);

                if (29 == v1) {
                    break;
                }

                if (WiFiMenuApp_GetFriendOnlineStatus(v2 - 1) == DWC_STATUS_MATCH_SC_SV) {
                    if (WiFiMenuApp_StartWifiBattle(param0, v2 - 1, v1)) {
                        param0->unk_3A0 = (60 * 30);
                        WiFiMenuApp_SetCommStateForSelection(v1);
                        WiFiMenuApp_SetCommState(param0, v1);
                        WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                        WiFiMenuApp_ShowMessage(param0, 17, 0);
                        GF_ASSERT(param0->unk_188 == NULL);
                        param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));

                        if (v1 != 1) {
                            param0->unk_3A8 = 45;
                        } else {
                            param0->unk_3A0 = (60 * 30);
                            param0->unk_3A8 = 21;
                        }

                        v3 = 1;
                    } else {
                        WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                        WiFiMenuApp_ShowMessage(param0, 16, 0);
                        param0->unk_3A8 = 29;
                        v3 = 1;
                    }
                } else {
                    WiFiMenuApp_SetFriendNameTemplate(param0, v2 - 1);
                    WiFiMenuApp_ShowMessage(param0, 16, 0);
                    param0->unk_3A8 = 29;
                    v3 = 1;
                    break;
                }
            }
        } else if (v0 == 2) {
            param0->unk_3A8 = 54;
        }

        break;
    }

    if (v3 == 0) {
        WiFiMenuApp_ClearMessage(param0);
    }

    Window_EraseStandardFrame(&param0->unk_380, 0);
    Window_Remove(&param0->unk_380);
    ListMenu_Free(param0->unk_158, NULL, NULL);
    StringList_Free(param0->unk_154);

    if (v7 != NULL) {
        WiFiMenuAppBoard_RestoreActorCallback(&param0->unk_3EC, v7);
    }

    if (param0->unk_3A8 == 19) {
        (void)0;
    } else {
        (void)0;
    }

    return param1;
}

static int WiFiMenuApp_StateWaitMatchSynchronize(WiFiMenuApp *param0, int param1)
{
    int v0;

    param0->unk_3A0--;

    if (param0->unk_3A0 < 0) {
        param0->unk_3A8 = 70;
    } else if (CommManager_GetMatchmakingState() == 3) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_GetMatchmakingState() == 5) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 15, 0);
        param0->unk_3A8 = 27;
    } else if ((CommManager_GetMatchmakingState() == 4) || (CommManager_GetDisconnectedWifi())) {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
    } else if (CommManager_GetMatchmakingState() == 1) {
        v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);

        if (WiFiMenuApp_IsWifiClubCommState(v0) == 0) {
            param0->unk_3A8 = 49;
            WiFiMenuApp_ClearMessage(param0);
            CommInfo_Init(param0->saveData, NULL);
            param0->unk_3BC = 30;
        } else if (CommSys_IsPlayerConnected(0) == 1) {
            WiFiMenuApp_ClearMessage(param0);
            CommInfo_Init(param0->saveData, NULL);
            CommManager_SetErrorHandling(0, 1);
            WiFiMenuApp_SetCommStateForSelection(v0);

            param0->unk_3AC = WiFiMenuApp_GetWifiConnectionTypeFromState(v0);

            CommSys_SetRecvLimitEnabled(0);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_54);

            param0->unk_3E4 = 0;
            param1 = 2;
        } else {
            if (CommSys_WifiConnected() == 1) {
                WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
                WiFiMenuApp_ShowMessage(param0, 18, 0);
                param0->unk_3A8 = 27;
            }
        }
    }

    return param1;
}

static int WiFiMenuApp_StateNoop4(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateNoop5(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateEndWifiMatch(WiFiMenuApp *param0, int param1)
{
    WiFiMenuApp_RestoreVoiceChat(param0);
    WiFiMenuApp_SetCommState(param0, 16);

    CommManager_EndWifiMatch();

    param0->unk_3D0 = -1;
    param0->unk_3A8 = 19;

    WiFiMenuApp_ClearBoardBusyFlag(param0);
    WiFiMenuApp_ClearMessage(param0);

    return param1;
}

static int WiFiMenuApp_StateNoop6(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateNoop7(WiFiMenuApp *param0, int param1)
{
    return param1;
}

static int WiFiMenuApp_StateEvaluateMatchState(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1;
    WFCTrainerInfo *v2;
    int v3;

    v2 = WiFiMenuApp_GetFriendStatus(param0, NintendoWFC_GetHostFriendIdx());
    v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);
    v1 = WiFiMenuApp_GetAdjustedCommState(param0, v2);
    v3 = param0->unk_04->ownStatus.voiceChatEnabled;

    if ((v0 == 12) && (v1 == 5)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 13) && (v1 == 6)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 14) && (v1 == 7)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 9) && (v1 == 2)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 10) && (v1 == 3)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 11) && (v1 == 4)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 15) && (v1 == 8)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 19) && (v1 == 18)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 21) && (v1 == 20)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 23) && (v1 == 22)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 25) && (v1 == 24)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 27) && (v1 == 26)) {
        param0->unk_3A8 = 49;
    } else if ((v0 == 16) && (v1 == 1) && (v3 > 0)) {
        param0->unk_3A8 = 22;
        return param1;
    } else {
        WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 29;
        WiFiMenuApp_SetCommState(param0, 16);
        CommManager_EndWifiMatch();
        return param1;
    }

    WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
    WiFiMenuApp_ShowMessage(param0, 11, 0);

    CommInfo_Init(param0->saveData, NULL);

    param0->unk_3A8 = 49;
    param0->unk_3BC = 30;

    return param1;
}

static BOOL WiFiMenuApp_CheckMatchAborted(WiFiMenuApp *param0)
{
    if (CommManager_GetMatchmakingState() >= 3) {
        WiFiMenuApp_SetFriendNameTemplate(param0, param0->unk_3D0);
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        param0->unk_3A8 = 27;
    } else if (CommManager_CheckWifiError()) {
        WiFiMenuApp_HandleWifiError(param0);
    } else {
        return 0;
    }

    param0->unk_3E4 = 0;
    return 1;
}

static int WiFiMenuApp_StateSyncWifiReady(WiFiMenuApp *param0, int param1)
{
    if ((CommManager_GetMatchmakingState() >= 4) || CommManager_GetDisconnectedWifi() || !CommSys_IsPlayerConnected(0)) {
        if (param0->unk_3E4) {
            WiFiMenuApp_ShowMessage(param0, 101, 0);
        } else {
            WiFiMenuApp_SetFriendNameTemplate(param0, param0->unk_3D0);
            WiFiMenuApp_ShowMessage(param0, 18, 0);
        }

        param0->unk_3E4 = 0;
        param0->unk_3A8 = 27;
    } else if (WiFiMenuApp_CheckMatchAborted(param0)) {
        (void)0;
    } else {
        if (param0->unk_3BC == 0) {
            if (CommTiming_IsSyncState(13)) {
                CommTool_ClearReceivedTempDataAllPlayers();
                CommTiming_StartSync(14);

                param0->unk_3E4 = 0;
                param0->unk_3A8 = 50;
            }
        } else {
            param0->unk_3BC--;

            if (param0->unk_3BC == 0) {
                CommTiming_StartSync(13);
            }
        }
    }

    return param1;
}

static int WiFiMenuApp_StateSendTempData(WiFiMenuApp *param0, int param1)
{
    if (WiFiMenuApp_CheckMatchAborted(param0)) {
        (void)0;
    } else if (CommTiming_IsSyncState(14)) {
        u16 v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);
        BOOL v1;

        v1 = CommTool_SendTempData(CommSys_CurNetId(), &v0);

        if (v1) {
            param0->unk_3A8 = 51;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateReceiveTempData(WiFiMenuApp *param0, int param1)
{
    const u16 *v0;
    int v1 = 0;

    if (CommSys_CurNetId() == 0) {
        v1 = 1;
    } else {
        v1 = 0;
    }

    v0 = CommTool_GetReceivedTempData(v1);

    if (WiFiMenuApp_CheckMatchAborted(param0)) {
        (void)0;
    } else if (v0 != NULL) {
        u16 v2 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);
        u16 v3 = WiFiMenuApp_GetPairedCommState(v2);

        if ((v0[0] == v3) || (v0[0] == v2)) {
            CommTiming_StartSync(15);
            param0->unk_3A8 = 52;
        } else {
            WiFiMenuApp_SetFriendNameTemplate(param0, NintendoWFC_GetHostFriendIdx());
            WiFiMenuApp_ShowMessage(param0, 16, 0);
            param0->unk_3A8 = 27;
        }
    }

    return param1;
}

static int WiFiMenuApp_StateSendPlayerInfo(WiFiMenuApp *param0, int param1)
{
    int v0;

    if (WiFiMenuApp_CheckMatchAborted(param0)) {
        (void)0;
    } else if (CommTiming_IsSyncState(15)) {
        CommInfo_SendPlayerInfo();
        CommManager_SetErrorHandling(1, 1);
        CommTiming_StartSync(18);

        param0->unk_3A8 = 53;
    }

    return param1;
}

static BOOL WiFiMenuApp_IsTextIdle(WiFiMenuApp *param0)
{
    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        return 1;
    }

    if (Window_IsInUse(&param0->unk_330) == 0) {
        return 1;
    }

    return 0;
}

static int WiFiMenuApp_StateFinishSync(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1[8];
    WFCTrainerInfo *v2;

    if (WiFiMenuApp_CheckMatchAborted(param0)) {
        (void)0;
    } else if (CommTiming_IsSyncState(18) && (WiFiMenuApp_IsTextIdle(param0) == 1)) {
        WiFiFriend_UpdateConnectedPlayers(param0->saveData, v1, HEAP_ID_54);
        WiFiMenuApp_ClearMessage(param0);

        v2 = WiFiMenuApp_GetFriendStatus(param0, NintendoWFC_GetHostFriendIdx());
        v0 = WiFiMenuApp_GetAdjustedCommState(param0, v2);

        if ((v0 == 15) || (v0 == 8)) {
            v0 = 8;
            param0->unk_3AC = 7;
        } else if ((v0 == 19) || (v0 == 18)) {
            v0 = 18;
            param0->unk_3AC = 11;
        } else if ((v0 == 21) || (v0 == 20)) {
            v0 = 20;
            param0->unk_3AC = 12;
        } else if ((v0 == 23) || (v0 == 22)) {
            v0 = 22;
            param0->unk_3AC = 13;
        } else if ((v0 == 25) || (v0 == 24)) {
            v0 = 24;
            param0->unk_3AC = 14;
        } else if ((v0 == 27) || (v0 == 26)) {
            v0 = 26;
            param0->unk_3AC = 15;
        } else if ((v0 == 9) || (v0 == 2)) {
            v0 = 2;
            param0->unk_3AC = 1;
        } else if ((v0 == 10) || (v0 == 3)) {
            v0 = 3;
            param0->unk_3AC = 2;
        } else if ((v0 == 11) || (v0 == 4)) {
            v0 = 4;
            param0->unk_3AC = 3;
        } else if ((v0 == 12) || (v0 == 5)) {
            v0 = 5;
            param0->unk_3AC = 4;
        } else if ((v0 == 13) || (v0 == 6)) {
            v0 = 6;
            param0->unk_3AC = 5;
        } else if ((v0 == 14) || (v0 == 7)) {
            v0 = 7;
            param0->unk_3AC = 6;
        }

        WiFiMenuApp_SaveWifiClubJournalEvent(param0, NintendoWFC_GetHostFriendIdx());
        WiFiMenuApp_SetCommState(param0, v0);

        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_54);

        param1 = 2;
    }

    return param1;
}

static int WiFiMenuApp_StateReturnFromMatch(WiFiMenuApp *param0, int param1)
{
    Bg_ClearTilemap(param0->unk_15C, BG_LAYER_MAIN_3);

    param0->unk_3C4 = 0;
    param0->unk_3A8 = WiFiMenuApp_StartFadeOutAndPlayBgm();

    return param1;
}

static int WiFiMenuApp_StateWait55(WiFiMenuApp *param0, int param1)
{
    u16 v0, v1;
    int v2, v3, v4, v5;

    param0->unk_3A8 = 55;

    return param1;
}

static int WiFiMenuApp_StateWaitBeforeExit(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (0 != WiFiMenuApp_IsMatchmakingStarted(param0)) {
        param0->unk_3A8 = 56;
    }

    if (gSystem.pressedKeys & (PAD_BUTTON_B | PAD_BUTTON_A)) {
        param0->unk_3A8 = 56;
    }

    return param1;
}

static int WiFiMenuApp_StateReturnToBoard(WiFiMenuApp *param0, int param1)
{
    int v0, v1;
    int v2 = 0;

    WiFiMenuApp_ClearMessage(param0);
    param0->unk_3A8 = 19;

    return param1;
}

static int WiFiMenuApp_StateConfirmQuit(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 58;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessQuit(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (0 != WiFiMenuApp_HandleNewClient(param0)) {
        if (v1 == 0xffffffff) {
            Menu_DestroyForExit(param0->unk_184, 54);
        }

        v1 = 0xfffffffe;
    }

    if (v1 == 0xffffffff) {
        return param1;
    } else if (v1 == 0) {
        WiFiMenuApp_ShowMessage(param0, 26, 1);
        param0->unk_3A8 = 59;
        param0->unk_3BC = 1;
    } else {
        WiFiMenuApp_ClearMessage(param0);
        param0->unk_3A8 = 19;
        WiFiMenuApp_ClearBoardBusyFlag(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateLogoutAndCompact(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (param0->unk_3BC == 1) {
        param0->unk_3BC = 0;
        CommManager_LogoutWifi();
    }

    if (!CommManager_IsInitialized()) {
        WiFiList_CompactFriendList(param0->unk_00);
        WiFiMenuApp_ShowMessage(param0, 27, 1);

        param0->unk_3A8 = 60;
        param0->unk_3BC = 30;
    }

    return param1;
}

static int WiFiMenuApp_StateWaitExit(WiFiMenuApp *param0, int param1)
{
    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    param0->unk_3BC--;

    if (param0->unk_3BC == 0) {
        param0->unk_3AC = 8;
        param0->unk_3A8 = 34;
        WiFiMenuApp_ClearMessage(param0);
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmSyncExit(WiFiMenuApp *param0, int param1)
{
    if (CommTiming_IsSyncState(16) == 0) {
        return param1;
    }

    CommManager_SetErrorHandling(0, 1);

    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 62;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessSyncExit(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1;

    if (Text_IsPrinterActive(param0->unk_180) != 0) {
        return param1;
    }

    if (CommManager_IsLoginBattleWifi() || CommManager_GetDisconnectedWifi() || (CommManager_GetMatchmakingState() >= 3)) {
        Menu_DestroyForExit(param0->unk_184, 54);
        WiFiMenuApp_ShowMessage(param0, 101, 0);
        param0->unk_3A8 = 28;
    } else if (CommManager_CheckWifiError()) {
        Menu_DestroyForExit(param0->unk_184, 54);
        WiFiMenuApp_HandleWifiError(param0);
    } else {
        v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

        if (v1 == 0xffffffff) {
            return param1;
        } else if (v1 == 0) {
            WiFiMenuApp_ShowMessage(param0, 138, 0);
            GF_ASSERT(param0->unk_188 == NULL);
            param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));
            param0->unk_3E4 = 1;
            param0->unk_3A8 = 49;
            param0->unk_3BC = 30;
        } else {
            WiFiMenuApp_ClearMessage(param0);
            CommInfo_Delete();
            CommManager_EndBattleWifiMatch();
            param0->unk_3BC = 20;
            param0->unk_3A8 = 65;
        }

        param0->unk_04 = CommManager_GetUnk00();
        param0->unk_04->ownStatus.voiceChatEnabled = param0->unk_04->ownStatus.voiceChatEnabledBackup;
    }

    return param1;
}

static int WiFiMenuApp_StateConfirmFriendAction(WiFiMenuApp *param0, int param1)
{
    {
        int v0, v1, v2;
        WiFiMenuAppActor *v3;
        WFCTrainerInfo *v4;

        v1 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
        v3 = WiFiMenuApp_GetActorByIndex(param0, v1);

        if (v3 == NULL) {
            WiFiMenuApp_SetFriendNameTemplate(param0, v1 - 1);
            WiFiMenuApp_ShowMessage(param0, 16, 0);
            param0->unk_3A8 = 29;
            return param1;
        } else {
            v4 = WiFiMenuApp_GetFriendStatus(param0, v1 - 1);
            v0 = WiFiMenuApp_GetAdjustedCommState(param0, v4);
            v2 = v4->voiceChatEnabled;

            if ((param0->unk_3DE != v0) || (param0->unk_3E0 != v2)) {
                WiFiMenuApp_SetFriendNameTemplate(param0, v1 - 1);
                WiFiMenuApp_ShowMessage(param0, 16, 0);
                param0->unk_3A8 = 29;
                return param1;
            }
        }
    }

    if (Text_IsPrinterActive(param0->unk_180) == 0) {
        param0->unk_184 = Menu_MakeYesNoChoice(param0->unk_15C, &sWiFiMenuAppYesNoWindowTemplate2, (512 - (18 + 12)) - 9, 11, 54);
        param0->unk_3A8 = 64;
    }

    return param1;
}

static int WiFiMenuApp_StateProcessFriendActionConfirm(WiFiMenuApp *param0, int param1)
{
    int v0;
    int v1, v2;

    {
        int v3, v4;
        WiFiMenuAppActor *v5;
        WFCTrainerInfo *v6;

        v3 = WiFiMenuAppBoard_GetPlayerDirection(&param0->unk_3EC);
        v5 = WiFiMenuApp_GetActorByIndex(param0, v3);

        if (v5 == NULL) {
            Menu_DestroyForExit(param0->unk_184, 54);
            WiFiMenuApp_SetFriendNameTemplate(param0, v3 - 1);
            WiFiMenuApp_ShowMessage(param0, 16, 0);
            param0->unk_3A8 = 29;
            return param1;
        } else {
            v6 = WiFiMenuApp_GetFriendStatus(param0, v3 - 1);
            v2 = WiFiMenuApp_GetAdjustedCommState(param0, v6);
            v4 = v6->voiceChatEnabled;

            if ((param0->unk_3DE != v2) || (param0->unk_3E0 != v4)) {
                Menu_DestroyForExit(param0->unk_184, 54);
                WiFiMenuApp_SetFriendNameTemplate(param0, v3 - 1);
                WiFiMenuApp_ShowMessage(param0, 16, 0);
                param0->unk_3A8 = 29;
                return param1;
            }
        }
    }

    if (CommManager_GetMatchmakingState() >= 3) {
        Menu_DestroyForExit(param0->unk_184, 54);
        WiFiMenuApp_ShowMessage(param0, 18, 0);
        CommManager_EndWifiMatch();
        param0->unk_3A8 = 29;
        return param1;
    } else if (CommManager_CheckWifiError()) {
        Menu_DestroyForExit(param0->unk_184, 54);
        WiFiMenuApp_HandleWifiError(param0);
    } else {
        v1 = Menu_ProcessInputAndHandleExit(param0->unk_184, 54);

        if (v1 == 0xffffffff) {
            return param1;
        } else if (v1 == 0) {
            v2 = WiFiMenuApp_GetPairedCommState(param0->unk_3DE);

            if (29 == v2) {
                (void)0;
            } else if (WiFiMenuApp_GetFriendOnlineStatus(param0->unk_3E2 - 1) == DWC_STATUS_MATCH_SC_SV) {
                WiFiMenuApp_ToggleVoiceChat(param0);

                if (WiFiMenuApp_StartWifiBattle(param0, param0->unk_3E2 - 1, v2)) {
                    param0->unk_3A0 = (60 * 30);
                    WiFiMenuApp_SetCommStateForSelection(v2);

                    CommSys_SetRecvLimitEnabled(0);

                    WiFiMenuApp_SetCommState(param0, v2);
                    WiFiMenuApp_SetFriendNameTemplate(param0, param0->unk_3E2 - 1);
                    WiFiMenuApp_ShowMessage(param0, 17, 0);

                    GF_ASSERT(param0->unk_188 == NULL);
                    param0->unk_188 = Window_AddWaitDial(&param0->unk_330, 512 - (18 + 12));

                    if (v2 != 1) {
                        param0->unk_3A8 = 45;
                        return param1;
                    } else {
                        param0->unk_3A0 = (60 * 30);
                        param0->unk_3A8 = 21;

                        return param1;
                    }
                }
            }
        }

        WiFiMenuApp_ClearMessage(param0);
        WiFiMenuApp_SetCommState(param0, 16);
        WiFiMenuApp_RestoreVoiceChat(param0);
        WiFiMenuApp_DrawPlayerStatusWindow(param0);

        param0->unk_3A8 = 19;

        return param1;
    }

    return param1;
}

static int WiFiMenuApp_StateWaitCommInit(WiFiMenuApp *param0, int param1)
{
    if (!CommManager_IsInitialized()) {
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_54);
        param1 = 2;
    }

    return param1;
}

static void WiFiMenuApp_ShowMessage(WiFiMenuApp *param0, int param1, BOOL param2)
{
    u8 v0 = Options_TextFrameDelay(SaveData_GetOptions(param0->saveData));

    WiFiMenuApp_DestroyWaitDial(param0);

    if (Window_IsInUse(&param0->unk_360)) {
        Window_EraseMessageBox(&param0->unk_360, 0);
        Window_Remove(&param0->unk_360);
    }

    if (Window_IsInUse(&param0->unk_330)) {
        Window_EraseMessageBox(&param0->unk_330, 0);
        Window_Remove(&param0->unk_330);
    }

    if (param0->unk_180 != 8) {
        if (Text_IsPrinterActive(param0->unk_180) != 0) {
            Text_RemovePrinter(param0->unk_180);
            param0->unk_180 = 8;
        }
    }

    Window_Add(param0->unk_15C, &param0->unk_330, 2, 2, 19, 27, 4, 12, ((512 - (18 + 12)) - 73) - (27 * 4));

    if (param2) {
        MessageLoader_GetString(param0->unk_16C, param1, param0->unk_170);
    } else {
        MessageLoader_GetString(param0->unk_168, param1, param0->unk_170);
    }

    StringTemplate_Format(param0->unk_164, param0->unk_174, param0->unk_170);
    Window_FillTilemap(&param0->unk_330, 15);
    Window_DrawMessageBoxWithScrollCursor(&param0->unk_330, 1, 512 - (18 + 12), 10);
    RenderControlFlags_SetCanABSpeedUpPrint(TRUE);
    RenderControlFlags_SetAutoScrollFlags(AUTO_SCROLL_DISABLED);

    param0->unk_180 = Text_AddPrinterWithParams(&param0->unk_330, FONT_MESSAGE, param0->unk_174, 0, 0, v0, NULL);

    Window_ScheduleCopyToVRAM(&param0->unk_330);
}

static void WiFiMenuApp_ShowMessageBox(WiFiMenuApp *param0, int param1)
{
    WiFiMenuApp_DestroyWaitDial(param0);

    if (Window_IsInUse(&param0->unk_360)) {
        Window_EraseMessageBox(&param0->unk_360, 0);
        Window_Remove(&param0->unk_360);
    }

    if (Window_IsInUse(&param0->unk_330)) {
        Window_EraseMessageBox(&param0->unk_330, 0);
        Window_Remove(&param0->unk_330);
    }

    if (param0->unk_180 != 8) {
        if (Text_IsPrinterActive(param0->unk_180) != 0) {
            Text_RemovePrinter(param0->unk_180);
            param0->unk_180 = 8;
        }
    }

    Window_Add(param0->unk_15C, &param0->unk_360, 2, 4, 4, 23, 16, 12, ((512 - (18 + 12)) - 9) - (23 * 16));
    MessageLoader_GetString(param0->unk_16C, param1, param0->unk_170);
    StringTemplate_Format(param0->unk_164, param0->unk_174, param0->unk_170);

    Window_FillTilemap(&param0->unk_360, 15);
    Window_DrawStandardFrame(&param0->unk_360, 1, (512 - (18 + 12)) - 9, 11);

    param0->unk_180 = Text_AddPrinterWithParams(&param0->unk_360, 1, param0->unk_174, 0, 0, 0xff, NULL);
    Window_ScheduleCopyToVRAM(&param0->unk_360);
}

static void WiFiMenuApp_SetFriendNameTemplate(WiFiMenuApp *param0, int param1)
{
    if (param1 != -1) {
        TrainerInfo *v0 = TrainerInfo_New(HEAP_ID_54);

        TrainerInfo_SetName(v0, WiFiList_GetFriendPlayerName(param0->unk_00, param1));
        StringTemplate_SetPlayerName(param0->unk_164, 0, v0);
        Heap_Free(v0);
    }
}

static void WiFiMenuApp_ClearMessage(WiFiMenuApp *param0)
{
    WiFiMenuApp_DestroyWaitDial(param0);

    if (param0->unk_180 != 8) {
        if (Text_IsPrinterActive(param0->unk_180) != 0) {
            Text_RemovePrinter(param0->unk_180);
            param0->unk_180 = 8;
        }
    }

    if (Window_IsInUse(&param0->unk_330)) {
        Window_EraseMessageBox(&param0->unk_330, 0);
        Window_Remove(&param0->unk_330);
    }
}

static void WiFiMenuApp_SetCommState(WiFiMenuApp *param0, int param1)
{
    if (param0->unk_04 == NULL) {
        return;
    }

    WiFiMenuApp_UpdateCommState(param0, param1);
    NintendoWFC_SetStatusData(&(param0->unk_04->ownStatus), sizeof(WFCTrainerInfo));
}

static void WiFiMenuApp_UpdateCommState(WiFiMenuApp *param0, int param1)
{
    int v0;

    if (param0->unk_04 == NULL) {
        return;
    }

    v0 = WiFiMenuApp_GetAdjustedCommState(param0, &param0->unk_04->ownStatus);

    if (v0 != param1) {
        param0->unk_04->ownStatus.commState = param1;

        if (WiFiMenuApp_IsBattleModeCommState(param1) || (param1 == 8) || (param1 == 20) || (param1 == 22) || (param1 == 24) || (param1 == 26) || (param1 == 18)) {
            (void)0;
        } else if (param1 == 1) {
            Sound_FadeOutBGM(0, 30);
        } else if (param1 == 16) {
            NintendoWFC_SetVoiceChatEnabled(0);

            if (WiFiMenuApp_IsLobbyBgmPlaying() == 1) {
                Sound_FadeInBGM(120, 30, BGM_FADE_IN_TYPE_FROM_CURRENT);
            }
        }
    }

    WiFiMenuApp_DrawPlayerStatusWindow(param0);
}

static BOOL WiFiMenuApp_ToggleVoiceChat(WiFiMenuApp *param0)
{
    param0->unk_04->ownStatus.voiceChatEnabled = 1 - param0->unk_04->ownStatus.voiceChatEnabled;

    NintendoWFC_SetStatusData(&(param0->unk_04->ownStatus), sizeof(WFCTrainerInfo));
    return param0->unk_04->ownStatus.voiceChatEnabled;
}

static BOOL WiFiMenuApp_ToggleVoiceChatBackup(WiFiMenuApp *param0)
{
    param0->unk_04->ownStatus.voiceChatEnabledBackup = 1 - param0->unk_04->ownStatus.voiceChatEnabledBackup;
    param0->unk_04->ownStatus.voiceChatEnabled = param0->unk_04->ownStatus.voiceChatEnabledBackup;

    NintendoWFC_SetStatusData(&(param0->unk_04->ownStatus), sizeof(WFCTrainerInfo));
    return param0->unk_04->ownStatus.voiceChatEnabledBackup;
}

static BOOL WiFiMenuApp_RestoreVoiceChat(WiFiMenuApp *param0)
{
    param0->unk_04->ownStatus.voiceChatEnabled = param0->unk_04->ownStatus.voiceChatEnabledBackup;

    NintendoWFC_SetStatusData(&(param0->unk_04->ownStatus), sizeof(WFCTrainerInfo));
    return param0->unk_04->ownStatus.voiceChatEnabledBackup;
}

static void WiFiMenuApp_DestroyWaitDial(WiFiMenuApp *param0)
{
    if (param0->unk_188) {
        DestroyWaitDialTaskOnly(param0->unk_188);

        param0->unk_188 = NULL;

        if (Window_IsInUse(&param0->unk_330)) {
            Window_EraseMessageBox(&param0->unk_330, 0);
            Window_Remove(&param0->unk_330);
        }
    }
}

static void WiFiMenuApp_ResetBoardAndRedraw(WiFiMenuApp *param0, enum HeapID heapID)
{
    WiFiMenuApp_ResetTouchScreenSelection(param0);
    WiFiMenuAppBoard_ResetActors(&param0->unk_3EC);
    WiFiMenuApp_RedrawTouchScreen(param0, heapID);
}

static void WiFiMenuApp_ResetIfCurrentActor(WiFiMenuApp *param0, u32 param1, enum HeapID heapID)
{
    if (WiFiMenuApp_GetTouchScreenSelection(param0) == param1) {
        WiFiMenuApp_ResetBoardAndRedraw(param0, heapID);
    }
}

static BOOL WiFiMenuApp_IsTouchScreenActive(const WiFiMenuApp *param0)
{
    if (param0->unk_BE0.unk_4C == NULL) {
        return 0;
    }

    return 1;
}

static void WiFiMenuApp_InitTouchScreen(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID)
{
    static const TouchScreenHitTable v0[8] = {
        { 0, 47, 0, 119 },
        { 48, 95, 0, 119 },
        { 96, 143, 0, 119 },
        { 144, 191, 0, 119 },
        { 0, 47, 128, 255 },
        { 48, 95, 128, 255 },
        { 96, 143, 128, 255 },
        { 144, 191, 128, 255 }
    };

    memset(&param0->unk_BE0, 0, sizeof(WiFiMenuAppTouchScreen));

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);

    param0->unk_BE0.unk_4C = TouchScreenActions_RegisterHandler(v0, 8, WiFiMenuApp_TouchButtonCallback, param0, heapID);
    param0->unk_BE0.unk_00 = StringTemplate_Default(heapID);

    WiFiMenuApp_LoadTouchScreenGraphics(param0, param1, heapID);

    param0->unk_BE0.unk_78 = 1;

    WiFiMenuApp_UpdateTouchScreenPalette(param0);
    WiFiMenuApp_DrawFriendList(param0);
}

static void WiFiMenuApp_FreeTouchScreen(WiFiMenuApp *param0)
{
    if (WiFiMenuApp_IsTouchScreenActive(param0) == 0) {
        return;
    }

    WiFiMenuApp_FreeTouchScreenGraphics(param0);

    TouchScreenActions_Free(param0->unk_BE0.unk_4C);
    param0->unk_BE0.unk_4C = NULL;

    StringTemplate_Free(param0->unk_BE0.unk_00);
    param0->unk_BE0.unk_00 = NULL;

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
}

static u32 WiFiMenuApp_UpdateTouchScreen(WiFiMenuApp *param0, enum HeapID heapID)
{
    u32 v0, v1;
    u32 v2;
    BOOL v3;

    v0 = WiFiMenuAppBoard_GetPlayerTileFlags(&param0->unk_3EC);
    v1 = WiFiMenuAppBoard_GetTileFlagsBelowPlayer(&param0->unk_3EC);

    if ((v1 >= 3) && (v1 <= 6)) {
        v0 = v1;
    }

    if ((v0 >= 3) && (v0 <= 6)) {
        if (param0->unk_BE0.unk_70 != (v0 - 3)) {
            param0->unk_BE0.unk_70 = (v0 - 3);

            Sound_PlayEffect(SEQ_SE_DP_SELECT5_sseq);
            WiFiMenuApp_UpdateTouchScreenPalette(param0);

            param0->unk_BE0.unk_75 = 1;
            param0->unk_BE0.unk_78 = 1;
        }
    }

    if (param0->unk_BE0.unk_73 == 1) {
        param0->unk_BE0.unk_73 = 2;
        param0->unk_BE0.unk_74 = 0;

        WiFiMenuApp_DrawFriendDetail(param0, heapID);
        WiFiMenuApp_ShowTouchButtons(param0);
    }

    if (param0->unk_BE0.unk_73 == 0) {
        TouchScreenActions_HandleAction(param0->unk_BE0.unk_4C);
        WiFiMenuApp_UpdateTouchScreenAnim(param0);

        if (param0->unk_BE0.unk_75 == 1) {
            WiFiMenuApp_DrawFriendList(param0);
            param0->unk_BE0.unk_75 = 0;
        }
    }

    if ((param0->unk_BE0.unk_73 == 2) || (param0->unk_BE0.unk_73 == 3)) {
        v2 = WiFiMenuApp_UpdateTouchButtons(param0);
        v3 = WiFiMenuApp_IsTouchSelectionInput(param0, v2);

        if (v3 == 1) {
            param0->unk_BE0.unk_77 = param0->unk_BE0.unk_71;
            param0->unk_BE0.unk_71 = 0;
            param0->unk_BE0.unk_72 = 0;
            param0->unk_BE0.unk_75 = 1;
            param0->unk_BE0.unk_78 = 1;
            param0->unk_BE0.unk_73 = 0;

            WiFiMenuApp_HideTouchButtons(param0);
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        } else {
            if (v2 != 0) {
                Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
                WiFiMenuApp_ChangeTouchScreenPage(param0, v2);
                WiFiMenuApp_DrawFriendDetail(param0, heapID);
            }
        }
    }

    return param0->unk_BE0.unk_71;
}

static void WiFiMenuApp_UpdateTouchScreenCursor(WiFiMenuApp *param0)
{
    if (param0->unk_BE0.unk_73 == 0) {
        if (param0->unk_BE0.unk_75 == 1) {
            WiFiMenuApp_DrawFriendList(param0);
            param0->unk_BE0.unk_75 = 0;
        }
    }
}

static BOOL WiFiMenuApp_IsTouchSelectionInput(WiFiMenuApp *param0, u32 param1)
{
    if (param0->unk_BE0.unk_73 == 3) {
        return 0;
    }

    if ((gSystem.heldKeys & (PAD_KEY_LEFT | PAD_KEY_RIGHT | PAD_KEY_UP | PAD_KEY_DOWN)) || (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X)) || (param1 == 2)) {
        return 1;
    }

    return 0;
}

static u32 WiFiMenuApp_GetTouchScreenSelection(const WiFiMenuApp *param0)
{
    return param0->unk_BE0.unk_71;
}

static void WiFiMenuApp_ResetTouchScreenSelection(WiFiMenuApp *param0)
{
    if (WiFiMenuApp_IsTouchScreenActive(param0) == 1) {
        param0->unk_BE0.unk_71 = 0;
        param0->unk_BE0.unk_72 = 0;
        param0->unk_BE0.unk_73 = 0;
        param0->unk_BE0.unk_75 = 1;
        param0->unk_BE0.unk_78 = 1;

        WiFiMenuApp_HideTouchButtons(param0);
    }
}

static void WiFiMenuApp_ChangeTouchScreenPage(WiFiMenuApp *param0, u32 param1)
{
    u32 v0;

    if (WiFiMenuApp_IsBattleParkAccessed(param0) == 1) {
        v0 = 7;
    } else {
        v0 = 1 + 1;
    }

    if (param1 == 3) {
        param0->unk_BE0.unk_74 = (param0->unk_BE0.unk_74 + 1) % v0;
    } else {
        param0->unk_BE0.unk_74--;

        if (param0->unk_BE0.unk_74 < 0) {
            param0->unk_BE0.unk_74 += v0;
        }
    }
}

static void WiFiMenuApp_TouchButtonCallback(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    WiFiMenuApp *v0 = param2;
    u32 v1 = (v0->unk_BE0.unk_70 * 8) + param0;
    v1++;

    if (v0->unk_BE0.unk_50[v1 - 1] != 2) {
        return;
    }

    if (v0->unk_BE0.unk_71 != 0) {
        return;
    }

    switch (param1) {
    case TOUCH_BUTTON_PRESSED:
        v0->unk_BE0.unk_71 = v1;
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
        break;
    default:
        break;
    }
}

static void WiFiMenuApp_LoadTouchScreenGraphics(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID)
{
    int v0, v1;
    int v2, v3;

    Bg_ClearTilemap(param0->unk_15C, BG_LAYER_SUB_0);
    Graphics_LoadPaletteFromOpenNARC(param1, 16, 4, 0 * 32, 4 * 32, heapID);
    Graphics_LoadPaletteFromOpenNARC(param1, 19, 4, 4 * 32, 5 * 32, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 15, param0->unk_15C, 4, 0, 0, 0, heapID);
    Graphics_LoadTilesToBgLayerFromOpenNARC(param1, 18, param0->unk_15C, 6, 0 + 48, 0, 0, heapID);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(param1, 17, param0->unk_15C, 4, 0, 0, 0, heapID);

    param0->unk_BE0.unk_04 = Graphics_GetScrnDataFromOpenNARC(param1, 20, 0, &param0->unk_BE0.unk_08, heapID);

    WiFiMenuApp_OffsetScreenData(param0->unk_BE0.unk_08, 0 + 48);

    for (v0 = 0; v0 < 7; v0++) {
        param0->unk_BE0.unk_0C[v0] = Graphics_GetScrnDataFromOpenNARC(param1, 21 + v0, 0, &param0->unk_BE0.unk_28[v0], heapID);
        WiFiMenuApp_OffsetScreenData(param0->unk_BE0.unk_28[v0], 0 + 48);
    }

    param0->unk_BE0.unk_44 = Graphics_GetScrnDataFromOpenNARC(param1, 28, 0, &param0->unk_BE0.unk_48, heapID);

    WiFiMenuApp_OffsetScreenData(param0->unk_BE0.unk_48, 0 + 48);
    Font_LoadScreenIndicatorsPalette(PAL_LOAD_SUB_BG, PLTT_OFFSET(15), heapID);

    for (v0 = 0; v0 < 8; v0++) {
        v2 = v0 / 4;
        v3 = v0 % 4;

        Window_Init(&param0->unk_BE0.unk_7C[v0]);
        Window_Add(param0->unk_15C, &param0->unk_BE0.unk_7C[v0], 5, 4 + (16 * v2), 1 + (6 * v3), 9, 3, 15, 1 + ((9 * 3) * v0));
        Window_FillTilemap(&param0->unk_BE0.unk_7C[v0], 0);
        Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_7C[v0]);

        for (v1 = 0; v1 < 2; v1++) {
            Window_Init(&param0->unk_BE0.unk_FC[v0][v1]);
            Window_Add(param0->unk_15C, &param0->unk_BE0.unk_FC[v0][v1], 5, 1 + (16 * v2) + (v1 * 12), 1 + (6 * v3), 2, 3, 13, ((((9 * 3) * 8) + 1) + 1) + ((2 * 3) * ((v0 * 2) + v1)));
            Window_FillTilemap(&param0->unk_BE0.unk_FC[v0][v1], 0);
            Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_FC[v0][v1]);
        }
    }

    Window_Add(param0->unk_15C, &param0->unk_BE0.unk_1FC, 7, 1, 1, 30, 21, 15, 1);
    Window_FillTilemap(&param0->unk_BE0.unk_1FC, 0);
    Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_1FC);

    WiFiMenuApp_InitTouchScreenSprites(param0, param1, heapID);
}

static void WiFiMenuApp_FreeTouchScreenGraphics(WiFiMenuApp *param0)
{
    int v0, v1;

    WiFiMenuApp_FreeTouchScreenSprites(param0);

    for (v0 = 0; v0 < 8; v0++) {
        Window_Remove(&param0->unk_BE0.unk_7C[v0]);

        for (v1 = 0; v1 < 2; v1++) {
            Window_Remove(&param0->unk_BE0.unk_FC[v0][v1]);
        }
    }

    Window_Remove(&param0->unk_BE0.unk_1FC);
    Heap_Free(param0->unk_BE0.unk_04);

    for (v0 = 0; v0 < 7; v0++) {
        Heap_Free(param0->unk_BE0.unk_0C[v0]);
    }

    Heap_Free(param0->unk_BE0.unk_44);
}

static void WiFiMenuApp_OffsetScreenData(NNSG2dScreenData *param0, u8 param1)
{
    u16 *v0;
    int v1, v2;
    int v3, v4;

    v0 = (u16 *)param0->rawData;
    v3 = param0->screenWidth / 8;
    v4 = param0->screenHeight / 8;

    for (v1 = 0; v1 < v4; v1++) {
        for (v2 = 0; v2 < v3; v2++) {
            v0[(v1 * v3) + v2] += param1;
        }
    }
}

static void WiFiMenuApp_SetFriendListState(WiFiMenuApp *param0, u32 param1, u32 param2)
{
    GF_ASSERT(param1 > 0);
    GF_ASSERT(param2 > 0);
    GF_ASSERT(param2 < 3);

    param0->unk_BE0.unk_50[param1 - 1] = param2;
    param0->unk_BE0.unk_75 = 1;
}

static void WiFiMenuApp_ClearFriendListState(WiFiMenuApp *param0, u32 param1)
{
    GF_ASSERT(param1 > 0);

    param0->unk_BE0.unk_50[param1 - 1] = 0;
    param0->unk_BE0.unk_75 = 1;
}

static u32 WiFiMenuApp_GetFriendListState(const WiFiMenuApp *param0, u32 param1)
{
    GF_ASSERT(param1 > 0);
    return param0->unk_BE0.unk_50[param1 - 1];
}

static void WiFiMenuApp_RedrawTouchScreen(WiFiMenuApp *param0, enum HeapID heapID)
{
    if (param0->unk_BE0.unk_73 != 0) {
        WiFiMenuApp_DrawFriendDetail(param0, heapID);
    } else {
        param0->unk_BE0.unk_78 = 1;
        WiFiMenuApp_DrawFriendList(param0);
    }
}

static void WiFiMenuApp_MarkTouchScreenDirty(WiFiMenuApp *param0)
{
    param0->unk_BE0.unk_78 = 1;
    param0->unk_BE0.unk_75 = 1;
}

static void WiFiMenuApp_UpdateTouchScreenPalette(WiFiMenuApp *param0)
{
    Bg_ChangeTilemapRectPalette(param0->unk_15C, 4, 0, 0, 32, 24, param0->unk_BE0.unk_70 + 0);
    Bg_ScheduleTilemapTransfer(param0->unk_15C, 4);
}

static void WiFiMenuApp_DrawFriendList(WiFiMenuApp *param0)
{
    int v0, v1;
    int v2;
    int v3;
    int v4, v5;
    int v6;
    int v7;
    BOOL v8;
    BOOL v9;

    if (param0->unk_BE0.unk_78 == 1) {
        param0->unk_BE0.unk_78 = 0;
        v8 = 1;
        Bg_FillTilemapRect(param0->unk_15C, 6, 0, 0, 0, 32, 24, 0);
    } else {
        v8 = 0;
    }

    for (v0 = 0; v0 < 8; v0++) {
        v6 = (param0->unk_BE0.unk_70 * 8) + v0 + 1;

        if (param0->unk_BE0.unk_50[v6 - 1] != 0) {
            v2 = WiFiList_GetFriendField(param0->unk_00, v6 - 1, 8);

            if (v2 == 0) {
                v3 = 1;
            } else {
                v3 = 0;
            }
        } else {
            v3 = 2;
        }

        v4 = v0 / 4;
        v5 = v0 % 4;

        if (v6 == param0->unk_BE0.unk_71) {
            v7 = param0->unk_BE0.unk_72;
        } else {
            v7 = 0;
        }

        if ((v6 == param0->unk_BE0.unk_71) || (v6 == param0->unk_BE0.unk_77)) {
            v9 = 1;
        } else {
            v9 = 0;
        }

        if ((v8 == 1) || (v9 == 1)) {
            WiFiMenuApp_DrawFriendRow(param0, 0 + (16 * v4), 0 + (6 * v5), v3, v7);

            if (v3 != 2) {
                WiFiMenuApp_DrawFriendName(param0, &param0->unk_BE0.unk_7C[v0], v6, v7, v0);
                WiFiMenuApp_DrawFriendStatus(param0, param0->unk_BE0.unk_FC[v0], v6, v7, v0);
            } else {
                Window_FillTilemap(&param0->unk_BE0.unk_7C[v0], 0);
                Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_7C[v0]);

                for (v1 = 0; v1 < 2; v1++) {
                    Window_FillTilemap(&param0->unk_BE0.unk_FC[v0][v1], 0);
                    Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_FC[v0][v1]);
                }
            }
        }
    }

    Bg_ScheduleTilemapTransfer(param0->unk_15C, 6);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
}

static void WiFiMenuApp_DrawFriendDetail(WiFiMenuApp *param0, enum HeapID heapID)
{
    static void (*v0[7])(WiFiMenuApp *, enum HeapID) = {
        WiFiMenuApp_DrawFriendDetailPage0,
        WiFiMenuApp_DrawFriendDetailPage6,
        WiFiMenuApp_DrawFriendDetailPage1,
        WiFiMenuApp_DrawFriendDetailPage2,
        WiFiMenuApp_DrawFriendDetailPage3,
        WiFiMenuApp_DrawFriendDetailPage4,
        WiFiMenuApp_DrawFriendDetailPage5
    };
    int v1;
    int v2;

    v1 = WiFiList_GetFriendField(param0->unk_00, param0->unk_BE0.unk_71 - 1, 8);

    if (v1 == 1) {
        v2 = 4 + 3;
    } else {
        v2 = 4 + 4;
    }

    Bg_LoadTilemapBuffer(param0->unk_15C, 6, param0->unk_BE0.unk_28[param0->unk_BE0.unk_74]->rawData, param0->unk_BE0.unk_28[param0->unk_BE0.unk_74]->szByte);
    Bg_ChangeTilemapRectPalette(param0->unk_15C, 6, 0, 0, 32, 24, v2);
    Bg_ClearTilemap(param0->unk_15C, BG_LAYER_SUB_3);

    if (WiFiMenuApp_IsBattleParkAccessed(param0) == 0) {
        WiFiMenuApp_DrawFriendListHeader(param0);
    }

    Window_FillTilemap(&param0->unk_BE0.unk_1FC, 0x0);

    v0[param0->unk_BE0.unk_74](param0, heapID);

    Bg_ScheduleTilemapTransfer(param0->unk_15C, 6);
    Window_ScheduleCopyToVRAM(&param0->unk_BE0.unk_1FC);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
}

static void WiFiMenuApp_DrawFriendDetailPage0(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0 = param0->unk_BE0.unk_71 - 1;
    TextColor color;

    if (WiFiList_GetFriendField(param0->unk_00, v0, 8) == 0) {
        color = TEXT_COLOR(5, 6, 0);
    } else {
        color = TEXT_COLOR(3, 4, 0);
    }

    WiFiMenuApp_SetTouchScreenFriendName(param0, v0);
    MessageLoader_GetString(param0->unk_168, 42, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_MESSAGE, param0->unk_178, 32, 8, TEXT_SPEED_NO_TRANSFER, color, NULL);

    WFCTrainerInfo *v2 = WiFiMenuApp_GetFriendStatus(param0, v0);
    u32 v3 = WiFiMenuApp_GetAdjustedCommState(param0, v2);
    MessageLoader_GetString(param0->unk_168, WiFiMenuApp_GetCommStateMessage(v3, &color), param0->unk_170);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_170, 104, 8, TEXT_SPEED_NO_TRANSFER, color, NULL);

    TrainerInfo *trainerInfo = TrainerInfo_New(HEAP_ID_54);
    TrainerInfo_SetName(trainerInfo, WiFiList_GetFriendGroupName(param0->unk_00, v0));
    StringTemplate_SetPlayerName(param0->unk_BE0.unk_00, 0, trainerInfo);
    Heap_Free(trainerInfo);
    MessageLoader_GetString(param0->unk_168, 43, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 32, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 150, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    u32 xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 32, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 44, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 56, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, WiFiList_GetFriendField(param0->unk_00, v0, 1), 4, PADDING_MODE_SPACES, CHARSET_MODE_EN);
    MessageLoader_GetString(param0->unk_168, 45, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 120, 56, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, WiFiList_GetFriendField(param0->unk_00, v0, 2), 4, PADDING_MODE_SPACES, CHARSET_MODE_EN);
    MessageLoader_GetString(param0->unk_168, 46, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 56, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 47, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 80, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, WiFiList_GetFriendField(param0->unk_00, v0, 3), 4, PADDING_MODE_SPACES, CHARSET_MODE_EN);
    MessageLoader_GetString(param0->unk_168, 48, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 80, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    if (WiFiMenuApp_HasPoffinCase(param0) == TRUE) {
        MessageLoader_GetString(param0->unk_168, 49, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 104, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

        StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, WiFiList_GetFriendField(param0->unk_00, v0, 9), 4, PADDING_MODE_SPACES, CHARSET_MODE_EN);
        MessageLoader_GetString(param0->unk_168, 50, param0->unk_170);
        StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
        xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 104, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    MessageLoader_GetString(param0->unk_168, 51, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 128, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    u32 v4 = WiFiList_GetFriendField(param0->unk_00, v0, 6);
    if (v4 != 0) {
        StringTemplate_SetNumber(param0->unk_BE0.unk_00, 2, v4, 2, PADDING_MODE_NONE, CHARSET_MODE_EN);
        StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, WiFiList_GetFriendField(param0->unk_00, v0, 4), 4, PADDING_MODE_NONE, CHARSET_MODE_EN);
        StringTemplate_SetMonthName(param0->unk_BE0.unk_00, 1, WiFiList_GetFriendField(param0->unk_00, v0, 5));
        MessageLoader_GetString(param0->unk_168, 74, param0->unk_170);
        StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
        xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 128, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    WiFiMenuApp_DrawStateIconToBg(param0->unk_15C, &param0->unk_BD0, 6, 2, 2, v3);

    int v5;

    if (v2->voiceChatEnabled) {
        v5 = 8;
    } else {
        v5 = 1;
    }

    WiFiMenuApp_DrawScreenDataTilemap(param0->unk_15C, &param0->unk_BD0, 6, 28, 2, v5, 0);
}

static void WiFiMenuApp_DrawFriendDetailPage1(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0 = param0->unk_BE0.unk_71 - 1;

    {
        MessageLoader_GetString(param0->unk_168, 52, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    }

    {
        WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 0, v0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 65, 113, v0, 120, 24);
    }

    {
        MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 65, 112, v0, 120, 48);
    }
}

static void WiFiMenuApp_DrawFriendDetailPage2(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0 = param0->unk_BE0.unk_71 - 1;

    MessageLoader_GetString(param0->unk_168, 53, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 60, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 62, param0->unk_178);
    u32 xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 1, v0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_DrawFrontierStat(param0, 65, 115, v0, 104, 48);
    WiFiMenuApp_DrawFrontierStat(param0, 66, 117, v0, 212, 48);

    MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 64, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_DrawFrontierStat(param0, 65, 114, v0, 104, 64);
    WiFiMenuApp_DrawFrontierStat(param0, 66, 116, v0, 212, 64);

    MessageLoader_GetString(param0->unk_168, 61, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 88, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    MessageLoader_GetString(param0->unk_168, 62, param0->unk_178);
    xOffset = 232 - Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, xOffset, 88, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 2, v0);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 112, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_DrawFrontierStat(param0, 65, 119, v0, 104, 112);
    WiFiMenuApp_DrawFrontierStat(param0, 66, 121, v0, 212, 112);

    MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
    Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 128, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

    WiFiMenuApp_DrawFrontierStat(param0, 65, 118, v0, 104, 128);
    WiFiMenuApp_DrawFrontierStat(param0, 66, 120, v0, 212, 128);
}

static void WiFiMenuApp_DrawFriendDetailPage3(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0 = param0->unk_BE0.unk_71 - 1;

    {
        MessageLoader_GetString(param0->unk_168, 54, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
        MessageLoader_GetString(param0->unk_168, 63, param0->unk_178);

        {
            u32 v1 = 180 - (Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0) + 1) / 2;
            Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, v1, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        }
    }

    {
        WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 3, v0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 68, 135, v0, 104, 48);
        WiFiMenuApp_DrawFrontierStat(param0, 67, 136, v0, 212, 48);
    }

    {
        MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 80, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);

        WiFiMenuApp_DrawFrontierStat(param0, 68, 134, v0, 104, 80);
        WiFiMenuApp_DrawFrontierStat(param0, 67, 138, v0, 212, 80);
    }
}

static void WiFiMenuApp_DrawFriendDetailPage4(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0;
    int v1;
    BattleFrontierSave *frontier;
    String *v3;

    frontier = SaveData_GetBattleFrontier(param0->saveData);
    v0 = param0->unk_BE0.unk_71 - 1;

    {
        MessageLoader_GetString(param0->unk_168, 55, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);

        v1 = BattleFrontierSave_GetStat(frontier, STAT_HALL_LATEST_SPECIES_MULTI_WFC, v0);
        v3 = MessageUtil_SpeciesName(v1, heapID);

        {
            u32 v4 = 33 - (Font_CalcStringWidth(FONT_SYSTEM, v3, 0) + 1) / 2;
            Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, v3, v4, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        }

        String_Free(v3);
    }

    {
        WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 4, v0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 65, 123, v0, 108, 48);
    }

    {
        MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 80, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 65, 122, v0, 108, 80);
    }
}

static void WiFiMenuApp_DrawFriendDetailPage5(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0 = param0->unk_BE0.unk_71 - 1;

    {
        MessageLoader_GetString(param0->unk_168, 56, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    }

    {
        WiFiMenuApp_SetFrontierRecordMessage(param0, param0->unk_178, 5, v0);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 69, 143, v0, 112, 24);
    }

    {
        MessageLoader_GetString(param0->unk_168, 59, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawFrontierStat(param0, 69, 142, v0, 112, 48);
    }
}

static void WiFiMenuApp_DrawFriendDetailPage6(WiFiMenuApp *param0, enum HeapID heapID)
{
    int v0;
    WiFiList *v1 = SaveData_GetWiFiList(param0->saveData);

    v0 = param0->unk_BE0.unk_71 - 1;

    {
        MessageLoader_GetString(param0->unk_168, 70, param0->unk_178);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(15, 14, 0), NULL);
    }

    {
        StringTemplate_SetPlazaMinigameName(param0->unk_BE0.unk_00, 0, WiFiPlazaLobbyActivity_00);
        MessageLoader_GetString(param0->unk_168, 71, param0->unk_170);
        StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 24, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawCenteredNumber(param0, 72, WiFiList_GetFriendField(v1, v0, 10), 164, 24);
    }

    {
        StringTemplate_SetPlazaMinigameName(param0->unk_BE0.unk_00, 0, WiFiPlazaLobbyActivity_01);
        MessageLoader_GetString(param0->unk_168, 71, param0->unk_170);
        StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 48, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawCenteredNumber(param0, 72, WiFiList_GetFriendField(v1, v0, 11), 164, 48);
    }

    {
        StringTemplate_SetPlazaMinigameName(param0->unk_BE0.unk_00, 0, WiFiPlazaLobbyActivity_02);
        MessageLoader_GetString(param0->unk_168, 71, param0->unk_170);
        StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, 8, 72, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        WiFiMenuApp_DrawCenteredNumber(param0, 72, WiFiList_GetFriendField(v1, v0, 12), 164, 72);
    }
}

static void WiFiMenuApp_DrawFriendListHeader(WiFiMenuApp *param0)
{
    int v0;
    int v1 = 7 - 2;

    for (v0 = 0; v0 < v1; v0++) {
        Bg_CopyToTilemapRect(param0->unk_15C, 6, 0x1a + (0x1 * v0), 0, 0x1, 0x1, param0->unk_BE0.unk_48->rawData, 0, 0, param0->unk_BE0.unk_48->screenWidth / 8, param0->unk_BE0.unk_48->screenHeight / 8);
    }

    Bg_ChangeTilemapRectPalette(param0->unk_15C, 6, 0x1a, 0, 0x1 * v1, 0x1, 4 + 2);
}

static void WiFiMenuApp_DrawFrontierStat(WiFiMenuApp *param0, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5)
{
    int v0;
    BattleFrontierSave *frontier = SaveData_GetBattleFrontier(param0->saveData);
    v0 = BattleFrontierSave_GetStat(frontier, param2, param3);

    WiFiMenuApp_DrawCenteredNumber(param0, param1, v0, param4, param5);
}

static void WiFiMenuApp_SetFrontierRecordMessage(WiFiMenuApp *param0, String *param1, u32 param2, u32 param3)
{
    BattleFrontierSave *frontier;
    BOOL v1;
    u32 v2;
    static const u32 v3[6] = {
        100,
        102,
        104,
        108,
        106,
        110,
    };

    GF_ASSERT(param2 < 6);

    frontier = SaveData_GetBattleFrontier(param0->saveData);
    v1 = BattleFrontierSave_GetStat(frontier, v3[param2], param3);

    if (v1 == 0) {
        v2 = 57;
    } else {
        v2 = 58;
    }

    MessageLoader_GetString(param0->unk_168, v2, param1);
}

static void WiFiMenuApp_DrawCenteredNumber(WiFiMenuApp *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    StringTemplate_SetNumber(param0->unk_BE0.unk_00, 0, param2, 4, 1, 1);
    MessageLoader_GetString(param0->unk_168, param1, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);

    {
        u32 v0 = param3 - (Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0) + 1) / 2;
        Text_AddPrinterWithParamsAndColor(&param0->unk_BE0.unk_1FC, FONT_SYSTEM, param0->unk_178, v0, param4, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }
}

static void WiFiMenuApp_DrawFriendRow(WiFiMenuApp *param0, u8 param1, u8 param2, u8 param3, u8 param4)
{
    u16 v0, v1;
    u16 *v2;

    GF_ASSERT(param4 < 4);

    if (param4 == 3) {
        param4 = 1;
    }

    if (param4 < 2) {
        v0 = 16 * param4;
        v1 = 6 * param3;

        Bg_CopyToTilemapRect(param0->unk_15C, 6, param1, param2, 16, 6, param0->unk_BE0.unk_08->rawData, v0, v1, 32, 18);
    } else {
        v0 = 0;
        v1 = 6 * param3;
        v2 = (u16 *)param0->unk_BE0.unk_08->rawData;

        Bg_CopyToTilemapRect(param0->unk_15C, 6, param1, param2, 16, 6, &v2[32 * 18], v0, v1, 16, 18);
    }

    Bg_ChangeTilemapRectPalette(param0->unk_15C, 6, param1, param2, 16, 6, param3 + 4);
}

static u32 WiFiMenuApp_GetCommStateMessage(u32 param0, TextColor *param1)
{
    u32 v0;

    *param1 = TEXT_COLOR(1, 2, 0);

    switch (param0) {
    case 1:
        v0 = 36;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        v0 = 27;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 9:
        v0 = 96;
        break;
    case 10:
        v0 = 97;
        break;
    case 11:
        v0 = 95;
        break;
    case 12:
        v0 = 99;
        break;
    case 13:
        v0 = 100;
        break;
    case 14:
        v0 = 98;
        break;
    case 8:
        v0 = 29;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 15:
        v0 = 28;
        break;
    case 18:
        v0 = 31;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 19:
        v0 = 30;
        break;
    case 20:
        v0 = 33;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 21:
        v0 = 32;
        break;
    case 22:
    case 24:
    case 26:
        v0 = 35;
        *param1 = TEXT_COLOR(2, 14, 0);
        break;
    case 23:
    case 25:
    case 27:
        v0 = 34;
        break;
    case 16:
        v0 = 79;
        break;
    default:
        v0 = 92;
        break;
    }

    return v0;
}

static void WiFiMenuApp_DrawFriendName(WiFiMenuApp *param0, Window *param1, u32 param2, u32 param3, u32 param4)
{
    int v0;
    TextColor v1;
    int v2;

    Window_FillTilemap(param1, 0);

    v2 = sWiFiMenuAppDetailTextYOffsets[param3];
    v0 = WiFiList_GetFriendField(param0->unk_00, param2 - 1, 8);

    if (v0 == 0) {
        v1 = TEXT_COLOR(5, 6, 0);
    } else {
        v1 = TEXT_COLOR(3, 4, 0);
    }

    WiFiMenuApp_SetTouchScreenFriendName(param0, param2 - 1);

    MessageLoader_GetString(param0->unk_168, 42, param0->unk_170);
    StringTemplate_Format(param0->unk_BE0.unk_00, param0->unk_178, param0->unk_170);
    Text_AddPrinterWithParamsAndColor(param1, FONT_MESSAGE, param0->unk_178, 0, v2, TEXT_SPEED_NO_TRANSFER, v1, NULL);
    Window_ScheduleCopyToVRAM(param1);
}

static void WiFiMenuApp_DrawFriendStatus(WiFiMenuApp *param0, Window *param1, u32 param2, u32 param3, u32 param4)
{
    int v0;
    int v1;
    int v2;
    WFCTrainerInfo *v3;
    u32 v4;

    v3 = WiFiMenuApp_GetFriendStatus(param0, param2 - 1);
    v4 = WiFiMenuApp_GetAdjustedCommState(param0, v3);
    v0 = sWiFiMenuAppDetailTextYOffsets[param3];

    for (v1 = 0; v1 < 2; v1++) {
        Window_FillTilemap(&param1[v1], 0);

        if (v1 == 0) {
            WiFiMenuApp_DrawActorStateIcon(&param1[v1], &param0->unk_BD0, 0, v0, v4);
        } else {
            if (v3->voiceChatEnabled) {
                v2 = 8;
            } else {
                v2 = 1;
            }

            WiFiMenuApp_DrawStateIconToWindow(&param1[v1], &param0->unk_BD0, 0, v0, v2, 0);
        }

        Window_ScheduleCopyToVRAM(&param1[v1]);
    }
}

static void WiFiMenuApp_UpdateTouchScreenAnim(WiFiMenuApp *param0)
{
    static const u8 v0[4] = {
        0, 1, 2, 1
    };

    if (param0->unk_BE0.unk_71 == 0) {
        return;
    }

    param0->unk_BE0.unk_76++;

    if (param0->unk_BE0.unk_76 >= v0[param0->unk_BE0.unk_72]) {
        param0->unk_BE0.unk_76 = 0;
        param0->unk_BE0.unk_72++;

        param0->unk_BE0.unk_75 = 1;

        if (param0->unk_BE0.unk_72 >= 4) {
            param0->unk_BE0.unk_76 = 0;
            param0->unk_BE0.unk_72 = 0;
            param0->unk_BE0.unk_73 = 1;
        }
    }
}

static void WiFiMenuApp_InitTouchScreenSprites(WiFiMenuApp *param0, NARC *param1, enum HeapID heapID)
{
    BOOL v0;
    int v1;
    SpriteResourcesHeader v2;
    Window v3;
    String *v4;
    FontOAMWindow *v5;
    int v6;
    UnkStruct_020127E8 v7;
    u32 v8;
    AffineSpriteListTemplate v9[3] = {
        { NULL,
            NULL,
            { FX32_CONST(40), FX32_CONST(172) + (256 * FX32_ONE), 0 },
            { FX32_ONE, FX32_ONE, FX32_ONE },
            0,
            128,
            NNS_G2D_VRAM_TYPE_2DSUB,
            0 },
        { NULL,
            NULL,
            { FX32_CONST(128), FX32_CONST(172) + (256 * FX32_ONE), 0 },
            { FX32_ONE, FX32_ONE, FX32_ONE },
            0,
            128,
            NNS_G2D_VRAM_TYPE_2DSUB,
            0 },
        { NULL,
            NULL,
            { FX32_CONST(224), FX32_CONST(172) + (256 * FX32_ONE), 0 },
            { FX32_ONE, FX32_ONE, FX32_ONE },
            0,
            128,
            NNS_G2D_VRAM_TYPE_2DSUB,
            0 },
    };

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);

    param0->unk_BE0.unk_20C[0] = SpriteResourceCollection_AddTilesFrom(param0->unk_31C[0], param1, 42, 0, 30, NNS_G2D_VRAM_TYPE_2DSUB, heapID);
    param0->unk_BE0.unk_20C[1] = SpriteResourceCollection_AddPaletteFrom(param0->unk_31C[1], param1, 43, 0, 30, NNS_G2D_VRAM_TYPE_2DSUB, 8, heapID);
    param0->unk_BE0.unk_20C[2] = SpriteResourceCollection_AddFrom(param0->unk_31C[2], param1, 40, 0, 30, 2, heapID);
    param0->unk_BE0.unk_20C[3] = SpriteResourceCollection_AddFrom(param0->unk_31C[3], param1, 41, 0, 30, 3, heapID);

    v0 = SpriteTransfer_RequestCharAtEndWithHardwareMappingType(param0->unk_BE0.unk_20C[0]);
    GF_ASSERT(v0);

    v0 = SpriteTransfer_RequestPlttFreeSpace(param0->unk_BE0.unk_20C[1]);
    GF_ASSERT(v0);

    SpriteResource_ReleaseData(param0->unk_BE0.unk_20C[0]);
    SpriteResource_ReleaseData(param0->unk_BE0.unk_20C[1]);
    SpriteResourcesHeader_Init(&v2, 30, 30, 30, 30, 0xffffffff, 0xffffffff, 0, 0, param0->unk_31C[0], param0->unk_31C[1], param0->unk_31C[2], param0->unk_31C[3], NULL, NULL);

    for (v1 = 0; v1 < 3; v1++) {
        v9[v1].list = param0->unk_18C;
        v9[v1].resourceData = &v2;
        v9[v1].heapID = heapID;

        param0->unk_BE0.unk_21C[v1] = SpriteList_AddAffine(&v9[v1]);

        Sprite_SetAnim(param0->unk_BE0.unk_21C[v1], sWiFiMenuAppTouchButtonIdleAnims[v1]);
    }

    Font_InitManager(FONT_SUBSCREEN, heapID);
    Window_Init(&v3);
    Window_AddToTopLeftCorner(param0->unk_15C, &v3, 8, 2, 0, 0);

    v4 = String_Init(64, heapID);
    MessageLoader_GetString(param0->unk_168, 73, v4);

    {
        v8 = -((Font_CalcStringWidth(FONT_SYSTEM, param0->unk_178, 0) + 1) / 2);
        Text_AddPrinterWithParamsAndColor(&v3, FONT_SUBSCREEN, v4, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    }

    String_Free(v4);

    v5 = FontOAMWindow_New(&v3, heapID);
    v6 = FontOAMWindow_GetSize(v5, NNS_G2D_VRAM_TYPE_2DSUB);
    v0 = CharTransfer_AllocRange(v6, 1, NNS_G2D_VRAM_TYPE_2DSUB, &param0->unk_BE0.unk_228);

    GF_ASSERT(v0);

    v7.unk_00 = param0->unk_32C;
    v7.unk_04 = &v3;
    v7.unk_08 = param0->unk_18C;
    v7.unk_0C = SpriteTransfer_GetPaletteProxy(param0->unk_BE0.unk_20C[1], NULL);
    v7.unk_10 = param0->unk_BE0.unk_21C[1];
    v7.unk_14 = param0->unk_BE0.unk_228.offset;
    v7.unk_18 = v8;
    v7.unk_1C = -8;
    v7.unk_20 = 0;
    v7.unk_24 = 0;
    v7.unk_28 = NNS_G2D_VRAM_TYPE_2DSUB;
    v7.heapID = heapID;

    param0->unk_BE0.unk_234 = FontOAM_NewFromWindow(&v7, v5);

    FontOAMWindow_Free(v5);
    Window_Remove(&v3);
    Font_Free(FONT_SUBSCREEN);

    param0->unk_BE0.unk_244 = TouchScreenActions_RegisterHandler(sWiFiMenuAppTouchButtonsHitTable, 3, WiFiMenuApp_TouchButtonActionCallback, param0, heapID);
}

static void WiFiMenuApp_FreeTouchScreenSprites(WiFiMenuApp *param0)
{
    int v0;

    TouchScreenActions_Free(param0->unk_BE0.unk_244);
    FontOAM_Delete(param0->unk_BE0.unk_234);
    CharTransfer_ClearRange(&param0->unk_BE0.unk_228);

    for (v0 = 0; v0 < 3; v0++) {
        Sprite_Delete(param0->unk_BE0.unk_21C[v0]);
    }

    SpriteTransfer_ResetCharTransfer(param0->unk_BE0.unk_20C[0]);
    SpriteTransfer_ResetPlttTransfer(param0->unk_BE0.unk_20C[1]);

    for (v0 = 0; v0 < 4; v0++) {
        SpriteResourceCollection_Remove(param0->unk_31C[v0], param0->unk_BE0.unk_20C[v0]);
    }
}

static void WiFiMenuApp_ShowTouchButtons(WiFiMenuApp *param0)
{
    int v0;

    param0->unk_BE0.unk_238 = 1;
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 1);
    param0->unk_BE0.unk_23C = 0;

    for (v0 = 0; v0 < 3; v0++) {
        WiFiMenuApp_SetTouchButtonAnim(&param0->unk_BE0, v0);
    }
}

static void WiFiMenuApp_HideTouchButtons(WiFiMenuApp *param0)
{
    if (param0->unk_BE0.unk_238 == 2) {
        Sprite_SetDrawFlag(param0->unk_BE0.unk_21C[1], TRUE);
        FontOAM_SetDrawFlag(param0->unk_BE0.unk_234, 1);
    }

    param0->unk_BE0.unk_238 = 0;

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, 0);
}

static u32 WiFiMenuApp_UpdateTouchButtons(WiFiMenuApp *param0)
{
    int v0;
    BOOL v1;

    if (param0->unk_BE0.unk_238 == 0) {
        return 0;
    }

    param0->unk_BE0.unk_23C = 3;
    param0->unk_BE0.unk_240 = 0xff;

    TouchScreenActions_HandleAction(param0->unk_BE0.unk_244);

    for (v0 = 0; v0 < 3; v0++) {
        if ((param0->unk_BE0.unk_238 == 2) && (v0 == 1)) {
            continue;
        }

        v1 = WiFiMenuApp_UpdateTouchButtonAnim(&param0->unk_BE0, v0, param0->unk_BE0.unk_23C, param0->unk_BE0.unk_240);

        if (v1 == 1) {
            return 1 + v0;
        }
    }

    return 0;
}

static void WiFiMenuApp_TouchButtonActionCallback(u32 param0, enum TouchScreenButtonState param1, void *param2)
{
    WiFiMenuApp *v0 = param2;

    v0->unk_BE0.unk_23C = param0;
    v0->unk_BE0.unk_240 = param1;
}

static void WiFiMenuApp_SetTouchButtonAnim(WiFiMenuAppTouchScreen *param0, u32 param1)
{
    Sprite_SetAnim(param0->unk_21C[param1], sWiFiMenuAppTouchButtonIdleAnims[param1]);
    Sprite_SetAnimFrame(param0->unk_21C[param1], 5 - 1);

    if (param1 == 1) {
        FontOAM_SetXY(param0->unk_234, -18, sWiFiMenuAppVoiceChatIconYOffsets[0]);
    }
}

static BOOL WiFiMenuApp_UpdateTouchButtonAnim(WiFiMenuAppTouchScreen *param0, u32 param1, u32 param2, u32 param3)
{
    BOOL v0 = 0;
    u32 v1;
    u32 v2;

    if (param2 == param1) {
        v1 = Sprite_GetAnimFrame(param0->unk_21C[param1]);

        if ((param3 == 0) || (param3 == 2)) {
            if (param3 == 0) {
                Sprite_SetAnim(param0->unk_21C[param1], sWiFiMenuAppTouchButtonPressedAnims[param1]);
            }

            if (v1 < 3) {
                Sprite_UpdateAnim(param0->unk_21C[param1], FX32_CONST(2));
                v1 = Sprite_GetAnimFrame(param0->unk_21C[param1]);

                if (param1 == 1) {
                    FontOAM_SetXY(param0->unk_234, -18, sWiFiMenuAppVoiceChatIconYOffsets[v1]);
                }

                if (v1 >= 3) {
                    v0 = 1;
                }
            }
        } else if (param3 == 1) {
            if (v1 < 3) {
                v0 = 1;
            }
        }
    } else {
        v2 = Sprite_GetActiveAnim(param0->unk_21C[param1]);
        v1 = Sprite_GetAnimFrame(param0->unk_21C[param1]);

        if (v2 == sWiFiMenuAppTouchButtonPressedAnims[param1]) {
            Sprite_SetAnim(param0->unk_21C[param1], sWiFiMenuAppTouchButtonIdleAnims[param1]);
            Sprite_SetAnimFrame(param0->unk_21C[param1], (5 - 1) - v1);
        }

        Sprite_UpdateAnim(param0->unk_21C[param1], FX32_CONST(2));
    }

    return v0;
}

static void WiFiMenuApp_SetTouchScreenFriendName(WiFiMenuApp *param0, int param1)
{
    if (param1 != -1) {
        TrainerInfo *v0 = TrainerInfo_New(HEAP_ID_54);

        TrainerInfo_SetName(v0, WiFiList_GetFriendPlayerName(param0->unk_00, param1));
        StringTemplate_SetPlayerName(param0->unk_BE0.unk_00, 0, v0);
        Heap_Free(v0);
    }
}

static WFCTrainerInfo *WiFiMenuApp_GetFriendStatus(WiFiMenuApp *param0, u32 param1)
{
    GF_ASSERT(param1 < 32);

    return &param0->unk_04->friendStatuses[param1];
}

static u8 WiFiMenuApp_GetFriendOnlineStatus(int param0)
{
    return NintendoWFC_GetFriendStatus(param0);
}

static BOOL WiFiMenuApp_StartWifiBattle(WiFiMenuApp *param0, int param1, int param2)
{
    CommTool_Init(HEAP_ID_COMMUNICATION);
    NintendoWFC_SetVoiceChatEnabled(param0->unk_04->ownStatus.voiceChatEnabled);

    if (WiFiMenuApp_IsWifiClubCommState(param2) == 1) {
        NintendoWFC_ManageSecondaryHeap(1, HEAP_ID_PARTY_MENU1);
    } else {
        NintendoWFC_ManageSecondaryHeap(0, HEAP_ID_PARTY_MENU1);
    }

    WiFiComm_InitNoContext();

    return CommManager_StartWifiBattle(param1);
}

static void WiFiMenuApp_SetBoardBusyFlag(WiFiMenuApp *param0, BOOL param1)
{
    if (param0->unk_E28 == 0) {
        param0->unk_E28 = 1;
        WiFiMenuAppBoard_SetFlag(&param0->unk_3EC, 1);

        if (param1 == 1) {
            WiFiMenuApp_ShowMessage(param0, 9, 0);
        }
    }
}

static void WiFiMenuApp_ClearBoardBusyFlag(WiFiMenuApp *param0)
{
    if (param0->unk_E28 == 1) {
        param0->unk_E28 = 0;
        WiFiMenuApp_ClearMessage(param0);
        WiFiMenuAppBoard_SetFlag(&param0->unk_3EC, 0);
    }
}
