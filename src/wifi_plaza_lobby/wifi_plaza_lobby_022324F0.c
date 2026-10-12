#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"

#include <dwc.h>
#include <nitro.h>
#include <ppwlobby/ppw_lobby.h>
#include <string.h>

#include "struct_decls/wi_fi_list.h"
#include "struct_defs/wi_fi_history.h"

#include "nintendo_wfc/main.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232B20.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022589B4.h"

#include "enums.h"
#include "error_handling.h"
#include "heap.h"
#include "savedata.h"
#include "wifi_history_save_data.h"
#include "wifi_list.h"

#include "res/text/bank/country_names.h"

typedef struct {
    u16 country;
    u8 region;
    u8 unk_03;
} WiFiPlazaLobbyNetworkCountryRegion;

typedef struct {
    s16 unk_00;
    u16 unk_02;
    s32 *unk_04;
} WiFiPlazaLobbyNetworkPlayerIdArray;

typedef struct {
    const WiFiPlazaLobbyNetworkMessageHandler *unk_00;
    u32 unk_04;
    void *unk_08;
} WiFiPlazaLobbyNetworkMessageHandlerState;

typedef struct {
    PPW_LobbyRecruitInfo lobbyRecruitInfo;
    u16 unk_44;
    u16 unk_46;
    s32 unk_48;
} WiFiPlazaLobbyNetworkRecruit;

typedef struct {
    PPW_LobbyVipRecord *lobbyVipRecord;
    u16 unk_04;
    u16 unk_06;
} WiFiPlazaLobbyNetworkVipRecordBuffer;

typedef struct {
    PPW_LobbyQuestionnaire lobbyQuestionnaire;
    u32 unk_2D8;
} WiFiPlazaLobbyNetworkQuestionnaire;

typedef struct {
    SaveData *saveData;
    WiFiList *wiFiList;
    WiFiHistory *wiFiHistory;
    WiFiPlazaLobbyNetworkCallbacks unk_0C;
    void *unk_20;
    u8 *unk_24;
    u32 unk_28;
    PPW_LobbySystemProfile sysProfile[20];
    WiFiPlazaLobbyNetworkPlayerIdArray unk_11C[2];
    u8 unk_12C;
    u8 unk_12D;
    u8 unk_12E;
    u8 unk_12F;
    u8 unk_130;
    u8 unk_131;
    u8 unk_132;
    u8 unk_133;
    WiFiPlazaLobbyNetworkCountryRegion unk_134[20];
    WiFiPlazaLobbyNetworkMessageHandlerState unk_184[2];
    PPW_LobbyTimeInfo timeInfo;
    u8 unk_1B4[1024];
    u32 unk_5B4;
    WiFiPlazaLobbyNetworkRecruit unk_5B8[3];
    u16 gameKind;
    u8 unk_69E;
    u8 unk_69F;
    WiFiPlazaLobbyNetworkVipRecordBuffer unk_6A0;
    WiFiPlazaLobbyNetworkQuestionnaire unk_6A8;
    PPW_LOBBY_RESULT result;
} WiFiPlazaLobbyNetworkContext;

static BOOL WiFiPlazaLobby_Network_CheckLobbyResult(PPW_LOBBY_RESULT param0);
static void WiFiPlazaLobby_Network_ClearErrorFlags(void);
static WiFiPlazaLobbyNetworkSubChannelKind WiFiPlazaLobby_Network_ChannelKindToSubChannel(PPW_LOBBY_CHANNEL_KIND lobbyChannelKind);
static PPW_LOBBY_CHANNEL_KIND WiFiPlazaLobby_Network_SubChannelToChannelKind(WiFiPlazaLobbyNetworkSubChannelKind param0);
static BOOL WiFiPlazaLobby_Network_AddCountryRegionToChannelData(WiFiPlazaLobbyNetworkContext *param0);
static void WiFiPlazaLobby_Network_AllocPlayerProfileBuffer(WiFiPlazaLobbyNetworkContext *unused, u32 param1, u32 heapID);
static void WiFiPlazaLobby_Network_FreePlayerProfileBuffer(WiFiPlazaLobbyNetworkContext *unused);
static void WiFiPlazaLobby_Network_SetPlayerData(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const void *param2);
static void WiFiPlazaLobby_Network_SetPlayerDataWithSize(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const void *param2, u32 param3);
static const void *WiFiPlazaLobby_Network_GetPlayerDataFromContext(const WiFiPlazaLobbyNetworkContext *param0, s32 param1);
static void WiFiPlazaLobby_Network_ClearPlayerData(WiFiPlazaLobbyNetworkContext *param0, s32 param1);
static void WiFiPlazaLobby_Network_SetPlayerSystemProfile(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const PPW_LobbySystemProfile *lobbySystemProfile);
static const PPW_LobbySystemProfile *WiFiPlazaLobby_Network_GetPlayerSystemProfile(const WiFiPlazaLobbyNetworkContext *param0, s32 param1);
static void WiFiPlazaLobby_Network_ClearPlayerSystemProfile(WiFiPlazaLobbyNetworkContext *param0, s32 param1);
static void WiFiPlazaLobby_Network_InitPlayerIdLists(WiFiPlazaLobbyNetworkContext *param0, u32 param1, u32 param2, u32 heapID);
static void WiFiPlazaLobby_Network_FreePlayerIdLists(WiFiPlazaLobbyNetworkContext *param0);
static void WiFiPlazaLobby_Network_ResetPlayerIdList(WiFiPlazaLobbyNetworkContext *param0, u32 param1);
static void WiFiPlazaLobby_Network_AddPlayerId(WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2);
static void WiFiPlazaLobby_Network_RemovePlayerId(WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2);
static s32 WiFiPlazaLobby_Network_FindPlayerIndex(const WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2);
static s32 WiFiPlazaLobby_Network_GetPlayerIdAt(const WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2);
static void WiFiPlazaLobby_Network_RebuildSubChannelPlayers(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkSubChannelKind param1);
static BOOL WiFiPlazaLobby_Network_HasSubChannelRoom(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkSubChannelKind param1);
static void WiFiPlazaLobby_Network_HandleJoinChannel(BOOL param0, PPW_LOBBY_CHANNEL_KIND lobbyChannelKind);
static void WiFiPlazaLobby_Network_HandlePlayerConnected(s32 userId, const PPW_LobbySystemProfile *param1, const u8 *param2, u32 param3);
static void WiFiPlazaLobby_Network_HandlePlayerDisconnected(s32 param0);
static void WiFiPlazaLobby_Network_HandleStringMessageReceived(s32 unused1, PPW_LOBBY_CHANNEL_KIND unused2, s32 unused3, const char *unused4);
static void WiFiPlazaLobby_Network_HandleBinaryMessageReceived(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, s32 param2, const u8 *param3, u32 param4);
static void WiFiPlazaLobby_Network_HandleGetChannelData(BOOL unused1, BOOL unused2, PPW_LOBBY_CHANNEL_KIND unused3, s32 unused4, const char *param4, const u8 *param5, u32 unused5, void *unused6);
static void WiFiPlazaLobby_Network_HandleSystemProfileUpdated(s32 param0, const PPW_LobbySystemProfile *sysProfile);
static void WiFiPlazaLobby_Network_HandleUserProfileUpdated(s32 param0, const u8 *param1, u32 unused);
static void WiFiPlazaLobby_Network_HandleRecruit(s32 param0, const PPW_LobbyRecruitInfo *recruitInfo);
static void WiFiPlazaLobby_Network_HandleRecruitStopped(s32 param0, const PPW_LobbyRecruitInfo *recruitInfo);
static void WiFiPlazaLobby_Network_HandleScheduleProgress(PPW_LOBBY_TIME_EVENT timeEvent);
static void WiFiPlazaLobby_Network_HandleCheckProfile(PPW_LOBBY_STATS_RESULT statsResult, const u8 *param1, u32 param2);
static BOOL WiFiPlazaLobby_Network_HandleNotifySchedule(PPW_LOBBY_STATS_RESULT statsResult, const PPW_LobbySchedule *unused);
static void WiFiPlazaLobby_Network_HandleGetVip(PPW_LOBBY_STATS_RESULT lobbyStatsResult, const PPW_LobbyVipRecord *lobbyVipRecord, u32 param2);
static void WiFiPlazaLobby_Network_HandleGetQuestionnaire(PPW_LOBBY_STATS_RESULT lobbyStatsResult, const PPW_LobbyQuestionnaire *lobbyQuestionnaire);
static void WiFiPlazaLobby_Network_HandleSubmitQuestionnaire(PPW_LOBBY_STATS_RESULT lobbyStatsResult);
static void WiFiPlazaLobby_Network_HandleExcessFlood(u32 unused);
static void WiFiPlazaLobby_Network_ResetRecruitInfo(WiFiPlazaLobbyNetworkContext *param0);
static void WiFiPlazaLobby_Network_SetRecruitInfo(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind gameKind, s32 param2, const PPW_LobbyRecruitInfo *lobbyRecruitInfo);
static BOOL WiFiPlazaLobby_Network_ClearRecruitInfo(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1, s32 param2);
static BOOL WiFiPlazaLobby_Network_IsRecruitActive(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1);
static u16 WiFiPlazaLobby_Network_GetRecruitRemainingTime(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1);
static const PPW_LobbyRecruitInfo *WiFiPlazaLobby_Network_GetRecruitInfo(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1);
static void WiFiPlazaLobby_Network_UpdateRecruitProgress(WiFiPlazaLobbyNetworkContext *unused);
static void WiFiPlazaLobby_Network_SetRecruitStartTime(PPW_LobbyRecruitInfo *lobbyRecruitInfo, const s64 *param1);
static void WiFiPlazaLobby_Network_GetRecruitStartTime(const PPW_LobbyRecruitInfo *lobbyRecruitInfo, s64 *param1);
static void WiFiPlazaLobby_Network_HandleNewClient(u16 unused1, void *unused2);
static void WiFiPlazaLobby_Network_HandleConnectionClosed(u16 param0, void *param1);
static u32 WiFiPlazaLobby_Network_GetScheduleEventTime(const PPW_LobbySchedule *lobbySchedule, PPW_LOBBY_TIME_EVENT lobbyTimeEvent);
static void WiFiPlazaLobby_Network_InitVipRecordBuffer(WiFiPlazaLobbyNetworkVipRecordBuffer *param0, u32 param1, u32 heapID);
static void WiFiPlazaLobby_Network_FreeVipRecordBuffer(WiFiPlazaLobbyNetworkVipRecordBuffer *param0);
static void WiFiPlazaLobby_Network_SetVipRecords(WiFiPlazaLobbyNetworkVipRecordBuffer *param0, const PPW_LobbyVipRecord *lobbyVipRecord, u32 param2);
static BOOL WiFiPlazaLobby_Network_ContainsVipProfile(const WiFiPlazaLobbyNetworkVipRecordBuffer *param0, s32 param1);
static s32 WiFiPlazaLobby_Network_FindVipKey(const WiFiPlazaLobbyNetworkVipRecordBuffer *param0, s32 param1);
static void WiFiPlazaLobby_Network_SetQuestionnaire(WiFiPlazaLobbyNetworkQuestionnaire *param0, const PPW_LobbyQuestionnaire *lobbyQuestionnaire);

static const char *sWorldDataArchiveName[1] = {
    "b_lby_wlddata"
};

static WiFiPlazaLobbyNetworkContext *sNetworkContext = NULL;

void WiFiPlazaLobby_Network_New(u32 heapID, SaveData *saveData, u32 param2, const WiFiPlazaLobbyNetworkCallbacks *param3, void *param4)
{
    GF_ASSERT(sNetworkContext == NULL);
    GF_ASSERT(param2 < PPW_LOBBY_MAX_BINARY_SIZE);

    sNetworkContext = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyNetworkContext));
    memset(sNetworkContext, 0, sizeof(WiFiPlazaLobbyNetworkContext));

    sNetworkContext->saveData = saveData;
    sNetworkContext->wiFiList = SaveData_GetWiFiList(saveData);
    sNetworkContext->wiFiHistory = SaveData_WiFiHistory(saveData);
    sNetworkContext->unk_0C = *param3;
    sNetworkContext->unk_20 = param4;

    WiFiPlazaLobby_Network_AllocPlayerProfileBuffer(sNetworkContext, param2, heapID);
    WiFiPlazaLobby_Network_InitPlayerIdLists(sNetworkContext, PPW_LOBBY_MAX_PLAYER_NUM_MAIN, PPW_LOBBY_MAX_PLAYER_NUM_FOOT, heapID);
    WiFiPlazaLobby_Network_ResetRecruitInfo(sNetworkContext);
    WiFiPlazaLobby_Network_InitVipRecordBuffer(&sNetworkContext->unk_6A0, 128, heapID);
}

void WiFiPlazaLobby_Network_Free(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    WiFiPlazaLobby_Network_FreeVipRecordBuffer(&sNetworkContext->unk_6A0);
    WiFiPlazaLobby_Network_FreePlayerIdLists(sNetworkContext);
    WiFiPlazaLobby_Network_FreePlayerProfileBuffer(sNetworkContext);

    Heap_Free(sNetworkContext);
    sNetworkContext = NULL;
}

WiFiPlazaLobbyNetworkLobbyState WiFiPlazaLobby_Network_Process(void)
{
    PPW_LOBBY_STATE lobbyState;

    if (sNetworkContext == NULL) {
        return WiFiPlazaLobbyNetworkLobbyState_00;
    }

    lobbyState = PPW_LobbyProcess();

    switch (lobbyState) {
    case PPW_LOBBY_STATE_NOTINITIALIZED:
        sNetworkContext->unk_12C = WiFiPlazaLobbyNetworkLobbyState_00;
        break;
    case PPW_LOBBY_STATE_CONNECTING:
    case PPW_LOBBY_STATE_CONNECTED:
    case PPW_LOBBY_STATE_DOWNLOAD:
    case PPW_LOBBY_STATE_DOWNLOAD_WAIT:
    case PPW_LOBBY_STATE_SEARCHINGCHANNEL:
    case PPW_LOBBY_STATE_ENTERMAINCHANNEL:
    case PPW_LOBBY_STATE_PREPARINGMAINCHANNEL:
        sNetworkContext->unk_12C = WiFiPlazaLobbyNetworkLobbyState_01;
        break;
    case PPW_LOBBY_STATE_READY:
        sNetworkContext->unk_12C = WiFiPlazaLobbyNetworkLobbyState_02;
        break;
    case PPW_LOBBY_STATE_CLOSING:
        sNetworkContext->unk_12C = WiFiPlazaLobbyNetworkLobbyState_03;
        break;
    case PPW_LOBBY_STATE_ERROR:
        sNetworkContext->unk_12C = WiFiPlazaLobbyNetworkLobbyState_04;
        break;
    }

    if (sNetworkContext->unk_12C == WiFiPlazaLobbyNetworkLobbyState_02) {
        WiFiPlazaLobby_Network_UpdateRecruitProgress(sNetworkContext);
        PPW_LobbyGetTimeInfo(&sNetworkContext->timeInfo);

        {
            PPW_LOBBY_CHANNEL_STATE v1;

            v1 = PPW_LobbyGetSubChannelState();

            switch (v1) {
            case PPW_LOBBY_CHANNEL_STATE_NONE:
                sNetworkContext->unk_12E = WiFiPlazaLobbyNetworkLobbyState_00;
                sNetworkContext->unk_12D = WiFiPlazaLobbyNetworkSubChannelKind_04;
                break;
            case PPW_LOBBY_CHANNEL_STATE_UNAVAILABLE:
                sNetworkContext->unk_12E = WiFiPlazaLobbyNetworkLobbyState_01;
                break;
            case PPW_LOBBY_CHANNEL_STATE_AVAILABLE:
                if (sNetworkContext->unk_12E != WiFiPlazaLobbyNetworkLobbyState_03) {
                    sNetworkContext->unk_12E = WiFiPlazaLobbyNetworkLobbyState_02;
                }
                break;
            case PPW_LOBBY_CHANNEL_STATE_ERROR:
                sNetworkContext->unk_12E = WiFiPlazaLobbyNetworkLobbyState_04;
                break;
            }
        }
    }

    return WiFiPlazaLobby_Network_GetState();
}

PPW_LOBBY_ERROR WiFiPlazaLobby_Network_GetLastError(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->result == 0) {
        return PPW_LobbyGetLastError();
    }

    return PPW_LobbyResultToError(sNetworkContext->result);
}

s32 WiFiPlazaLobby_Network_ToErrorCode(PPW_LOBBY_ERROR lobbyError)
{
    return PPW_LobbyToErrorCode(lobbyError);
}

BOOL WiFiPlazaLobby_Network_InitializeRelease(const void *param0)
{
    return WiFiPlazaLobby_Network_Initialize(param0, DWC_LOBBY_CHANNEL_PREFIX_RELEASE);
}

BOOL WiFiPlazaLobby_Network_Initialize(const void *param0, u32 param1)
{
    PPW_LobbyCallbacks v0;

    GF_ASSERT(sNetworkContext != NULL);

    {
        v0.lobbyJoinChannelCallback = WiFiPlazaLobby_Network_HandleJoinChannel;
        v0.lobbyPlayerConnectedCallback = WiFiPlazaLobby_Network_HandlePlayerConnected;
        v0.lobbyPlayerDisconnectedCallback = WiFiPlazaLobby_Network_HandlePlayerDisconnected;
        v0.lobbyStringMessageReceivedCallback = WiFiPlazaLobby_Network_HandleStringMessageReceived;
        v0.lobbyBinaryMessageReceivedCallback = WiFiPlazaLobby_Network_HandleBinaryMessageReceived;
        v0.lobbyGetChannelDataCallback = WiFiPlazaLobby_Network_HandleGetChannelData;
        v0.lobbySystemProfileUpdatedCallback = WiFiPlazaLobby_Network_HandleSystemProfileUpdated;
        v0.lobbyUserProfileUpdatedCallback = WiFiPlazaLobby_Network_HandleUserProfileUpdated;
        v0.lobbyRecruitCallback = WiFiPlazaLobby_Network_HandleRecruit;
        v0.lobbyRecruitStoppedCallback = WiFiPlazaLobby_Network_HandleRecruitStopped;
        v0.lobbyScheduleProgressCallback = WiFiPlazaLobby_Network_HandleScheduleProgress;
        v0.lobbyCheckProfileCallback = WiFiPlazaLobby_Network_HandleCheckProfile;
        v0.lobbyNotifyScheduleCallback = WiFiPlazaLobby_Network_HandleNotifySchedule;
        v0.lobbyGetVipCallback = WiFiPlazaLobby_Network_HandleGetVip;
        v0.lobbyGetQuestionnaireCallback = WiFiPlazaLobby_Network_HandleGetQuestionnaire;
        v0.lobbySubmitQuestionnaireCallback = WiFiPlazaLobby_Network_HandleSubmitQuestionnaire;
        v0.lobbyExcessFloodCallback = WiFiPlazaLobby_Network_HandleExcessFlood;
    }

    {
        DWCUserData *userData = WiFiList_GetUserData(sNetworkContext->wiFiList);
        sNetworkContext->result = PPW_LobbyInitializeAsync("pokemonplatds", "IIup73", param1, &v0, userData, param0, sNetworkContext->unk_28);
    }

    return WiFiPlazaLobby_Network_CheckLobbyResult(sNetworkContext->result);
}

BOOL WiFiPlazaLobby_Network_IsReady(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->unk_12C == WiFiPlazaLobbyNetworkLobbyState_02) {
        return 1;
    }

    return 0;
}

void WiFiPlazaLobby_Network_Shutdown(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    WiFiPlazaLobby_Network_ClearErrorFlags();

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyShutdownAsync();
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1);
}

BOOL WiFiPlazaLobby_Network_IsShutDown(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->unk_12C == WiFiPlazaLobbyNetworkLobbyState_00) {
        return 1;
    }

    return 0;
}

WiFiPlazaLobbyNetworkLobbyState WiFiPlazaLobby_Network_GetState(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->unk_12D != WiFiPlazaLobbyNetworkSubChannelKind_04) {
        if (sNetworkContext->unk_12E == WiFiPlazaLobbyNetworkLobbyState_04) {
            return WiFiPlazaLobbyNetworkLobbyState_04;
        }
    }

    if (sNetworkContext->unk_133) {
        return WiFiPlazaLobbyNetworkLobbyState_04;
    }

    if (sNetworkContext->unk_132) {
        return WiFiPlazaLobbyNetworkLobbyState_04;
    }

    return sNetworkContext->unk_12C;
}

BOOL WiFiPlazaLobby_Network_ConsumeExcessFlood(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    BOOL v0 = sNetworkContext->unk_131;

    sNetworkContext->unk_131 = 0;
    return v0;
}

s32 WiFiPlazaLobby_Network_GetMyUserId(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    return PPW_LobbyGetMyUserId();
}

void WiFiPlazaLobby_Network_SetMyProfile(const void *param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    WiFiPlazaLobby_Network_SetPlayerData(sNetworkContext, PPW_LobbyGetMyUserId(), param0);

    PPW_LobbyUpdateMyProfile(param0, sNetworkContext->unk_28, 0);
}

const void *WiFiPlazaLobby_Network_GetPlayerData(s32 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    return WiFiPlazaLobby_Network_GetPlayerDataFromContext(sNetworkContext, param0);
}

void WiFiPlazaLobby_Network_GetPlayerEnterTime(s32 param0, s64 *param1)
{
    GF_ASSERT(sNetworkContext != NULL);

    const PPW_LobbySystemProfile *sysProfile = WiFiPlazaLobby_Network_GetPlayerSystemProfile(sNetworkContext, param0);
    *param1 = sysProfile->enterTime;
}

s32 WiFiPlazaLobby_Network_FindFirstPlayer(void)
{
    int v0;
    s32 v1 = DWC_LOBBY_INVALID_USER_ID;
    s64 v2 = 0xfffffffffffffff;

    GF_ASSERT(sNetworkContext != NULL);

    for (v0 = 0; v0 < PPW_LOBBY_MAX_PLAYER_NUM_MAIN; v0++) {
        {
            s32 v3;
            s64 v4;

            v3 = WiFiPlazaLobby_Network_GetPlayerIdAt(sNetworkContext, v0, 0);

            if (v3 != DWC_LOBBY_INVALID_USER_ID) {
                WiFiPlazaLobby_Network_GetPlayerEnterTime(v3, &v4);

                if (v2 > v4) {
                    v2 = v4;
                    v1 = v3;
                }
            }
        }
    }

    return v1;
}

s32 WiFiPlazaLobby_Network_FindFirstPlayerExcept(s32 param0)
{
    int v0;
    s32 v1 = DWC_LOBBY_INVALID_USER_ID;
    s64 v2 = 0xfffffffffffffff;

    GF_ASSERT(sNetworkContext != NULL);

    for (v0 = 0; v0 < PPW_LOBBY_MAX_PLAYER_NUM_MAIN; v0++) {
        {
            s32 v3;
            s64 v4;

            v3 = WiFiPlazaLobby_Network_GetPlayerIdAt(sNetworkContext, v0, 0);

            if ((v3 != DWC_LOBBY_INVALID_USER_ID) && (v3 != param0)) {
                WiFiPlazaLobby_Network_GetPlayerEnterTime(v3, &v4);

                if (v2 > v4) {
                    v2 = v4;
                    v1 = v3;
                }
            }
        }
    }

    return v1;
}

BOOL WiFiPlazaLobby_Network_JoinSubChannel(WiFiPlazaLobbyNetworkSubChannelKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyJoinSubChannelAsync(WiFiPlazaLobby_Network_SubChannelToChannelKind(param0));
    BOOL v0 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    if (v0 == 1) {
        sNetworkContext->unk_12D = param0;
        sNetworkContext->unk_12F = WiFiPlazaLobbyNetworkSubChannelJoinState_00;
    }

    return v0;
}

WiFiPlazaLobbyNetworkSubChannelJoinState WiFiPlazaLobby_Network_GetSubChannelJoinState(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    return sNetworkContext->unk_12F;
}

BOOL WiFiPlazaLobby_Network_LeaveSubChannel(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyLeaveSubChannel();
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    if (v1 == 1) {
        sNetworkContext->unk_12E = WiFiPlazaLobbyNetworkLobbyState_03;
    }

    return v1;
}

BOOL WiFiPlazaLobby_Network_IsSubChannelInactive(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->unk_12E == WiFiPlazaLobbyNetworkLobbyState_00) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_Network_HasSubChannelSpace(WiFiPlazaLobbyNetworkSubChannelKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    return WiFiPlazaLobby_Network_HasSubChannelRoom(sNetworkContext, param0);
}

void WiFiPlazaLobby_Network_GetMainPlayerList(WiFiPlazaLobbyNetworkPlayerIdList *param0)
{
    GF_ASSERT(sNetworkContext != NULL);

    param0->unk_00 = sNetworkContext->unk_11C[0].unk_00;
    param0->unk_04 = sNetworkContext->unk_11C[0].unk_04;
}

void WiFiPlazaLobby_Network_GetSubChannelPlayerList(WiFiPlazaLobbyNetworkPlayerIdList *param0)
{
    GF_ASSERT(sNetworkContext != NULL);

    param0->unk_00 = sNetworkContext->unk_11C[1].unk_00;
    param0->unk_04 = sNetworkContext->unk_11C[1].unk_04;
}

u32 WiFiPlazaLobby_Network_FindMainPlayerIndex(s32 param0)
{
    return WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);
}

u32 WiFiPlazaLobby_Network_FindSubChannelPlayerIndex(s32 param0)
{
    return WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 1);
}

s32 WiFiPlazaLobby_Network_GetMainPlayerUserId(u32 param0)
{
    return WiFiPlazaLobby_Network_GetPlayerIdAt(sNetworkContext, param0, 0);
}

s32 WiFiPlazaLobby_Network_GetSubChannelPlayerUserId(u32 param0)
{
    return WiFiPlazaLobby_Network_GetPlayerIdAt(sNetworkContext, param0, 1);
}

void WiFiPlazaLobby_Network_GetCurrentTime(s64 *param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    *param0 = sNetworkContext->timeInfo.currentTime;
}

u32 WiFiPlazaLobby_Network_GetScheduleValue(WiFiPlazaLobbyNetworkScheduleField param0)
{
    u32 v0;

    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT((sNetworkContext->unk_12C == WiFiPlazaLobbyNetworkLobbyState_02) || (sNetworkContext->unk_12C == WiFiPlazaLobbyNetworkLobbyState_04));
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkScheduleField_08);

    PPW_LobbySchedule *lobbySchedule = (PPW_LobbySchedule *)sNetworkContext->unk_1B4;

    switch (param0) {
    case WiFiPlazaLobbyNetworkScheduleField_00:
        v0 = lobbySchedule->lockTime;
        break;
    case WiFiPlazaLobbyNetworkScheduleField_01:
        v0 = lobbySchedule->random;
        break;
    case WiFiPlazaLobbyNetworkScheduleField_02:
        v0 = lobbySchedule->roomType;
        break;
    case WiFiPlazaLobbyNetworkScheduleField_03:
        v0 = lobbySchedule->season;
        break;
    case WiFiPlazaLobbyNetworkScheduleField_04:
        if (lobbySchedule->roomFlag & PPW_LOBBY_ROOM_FLAG_ARCEUS) {
            v0 = 1;
        } else {
            v0 = 0;
        }
        break;
    case WiFiPlazaLobbyNetworkScheduleField_05:
        v0 = WiFiPlazaLobby_Network_GetScheduleEventTime(lobbySchedule, PPW_LOBBY_TIME_EVENT_CLOSE);
        break;
    case WiFiPlazaLobbyNetworkScheduleField_06:
        v0 = WiFiPlazaLobby_Network_GetScheduleEventTime(lobbySchedule, PPW_LOBBY_TIME_EVENT_FIRE_WORKS_START);
        break;
    case WiFiPlazaLobbyNetworkScheduleField_07:
        v0 = WiFiPlazaLobby_Network_GetScheduleEventTime(lobbySchedule, PPW_LOBBY_TIME_EVENT_FIRE_WORKS_END);
        break;
    }

    return v0;
}

BOOL WiFiPlazaLobby_Network_UpdateLocationChannelData(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    BOOL v0 = WiFiPlazaLobby_Network_AddCountryRegionToChannelData(sNetworkContext);

    if (v0) {
        sNetworkContext->unk_130 = 1;
    }

    return v0;
}

BOOL WiFiPlazaLobby_Network_IsLocationChannelDataSynced(void)
{
    if (sNetworkContext->unk_130 == 0) {
        return 1;
    }

    return 0;
}

u16 WiFiPlazaLobby_Network_GetPlayerCountry(u8 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < 20);

    return sNetworkContext->unk_134[param0].country;
}

u8 WiFiPlazaLobby_Network_GetPlayerRegion(u8 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < 20);

    return sNetworkContext->unk_134[param0].region;
}

void WiFiPlazaLobby_Network_SetMainMessageHandler(const WiFiPlazaLobbyNetworkMessageHandler *param0, u32 param1, void *param2)
{
    GF_ASSERT(sNetworkContext != NULL);

    sNetworkContext->unk_184[0].unk_00 = param0;
    sNetworkContext->unk_184[0].unk_04 = param1;
    sNetworkContext->unk_184[0].unk_08 = param2;
}

void WiFiPlazaLobby_Network_SetSubChannelMessageHandler(const WiFiPlazaLobbyNetworkMessageHandler *param0, u32 param1, void *param2)
{
    GF_ASSERT(sNetworkContext != NULL);

    sNetworkContext->unk_184[1].unk_00 = param0;
    sNetworkContext->unk_184[1].unk_04 = param1;
    sNetworkContext->unk_184[1].unk_08 = param2;
}

void WiFiPlazaLobby_Network_ClearMainMessageHandler(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    memset(&sNetworkContext->unk_184[0], 0, sizeof(WiFiPlazaLobbyNetworkMessageHandlerState));
}

void WiFiPlazaLobby_Network_ClearSubChannelMessageHandler(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    memset(&sNetworkContext->unk_184[1], 0, sizeof(WiFiPlazaLobbyNetworkMessageHandlerState));
}

void WiFiPlazaLobby_Network_SendMainChannelMessage(u32 param0, const void *param1, u32 param2)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(sNetworkContext->unk_184[0].unk_04 > param0);
    GF_ASSERT(sNetworkContext->unk_184[0].unk_00[param0].unk_04 == param2);

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbySendChannelBinaryMessage(PPW_LOBBY_CHANNEL_KIND_MAIN, param0, param1, param2);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1 == 1);
}

void WiFiPlazaLobby_Network_SendPlayerMessage(u32 param0, s32 param1, const void *param2, u32 param3)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(sNetworkContext->unk_184[0].unk_04 > param0);
    GF_ASSERT(sNetworkContext->unk_184[0].unk_00[param0].unk_04 == param3);

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbySendPlayerBinaryMessage(param1, param0, param2, param3);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1 == 1);
}

void WiFiPlazaLobby_Network_SendSubChannelMessage(u32 param0, const void *param1, u32 param2)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(sNetworkContext->unk_184[1].unk_04 > param0);
    GF_ASSERT(sNetworkContext->unk_184[1].unk_00[param0].unk_04 == param2);
    GF_ASSERT(sNetworkContext->unk_12D != WiFiPlazaLobbyNetworkSubChannelKind_04);

    u32 v2 = WiFiPlazaLobby_Network_SubChannelToChannelKind(sNetworkContext->unk_12D);
    PPW_LOBBY_RESULT lobbyResult = PPW_LobbySendChannelBinaryMessage(v2, param0, param1, param2);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1 == 1);
}

BOOL WiFiPlazaLobby_Network_StartGameRecruit(WiFiPlazaLobbyNetworkGameKind param0, u32 param1)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0) == 1) {
        return 0;
    }

    if (sNetworkContext->gameKind != WiFiPlazaLobbyNetworkGameKind_03) {
        return 0;
    }

    sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.gameKind = param0;
    sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.maxNum = param1;
    sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.currentNum = 1;
    sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.paramVal = 0;

    WiFiPlazaLobby_Network_SetRecruitStartTime(&sNetworkContext->unk_5B8[param0].lobbyRecruitInfo, &sNetworkContext->timeInfo.currentTime);

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyStartRecruit(&sNetworkContext->unk_5B8[param0].lobbyRecruitInfo);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1);

    sNetworkContext->unk_5B8[param0].unk_44 = 1;
    sNetworkContext->unk_5B8[param0].unk_48 = PPW_LobbyGetMyUserId();
    sNetworkContext->unk_5B8[param0].unk_46 = 60 * 30;
    sNetworkContext->gameKind = param0;
    sNetworkContext->unk_69E = 1;
    sNetworkContext->unk_69F = 0;

    if (NintendoWFC_StartPublicMatchmaking((u8 *)sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.matchMakingString, param1, 1, sNetworkContext->unk_5B8[param0].unk_46 / 30)) {
        (void)0;
    }

    NintendoWFC_SetNewClientCallback(WiFiPlazaLobby_Network_HandleNewClient, sNetworkContext);
    NintendoWFC_SetConnectionClosedCB(WiFiPlazaLobby_Network_HandleConnectionClosed, sNetworkContext);

    return 1;
}

void WiFiPlazaLobby_Network_StopGameRecruit(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->gameKind == WiFiPlazaLobbyNetworkGameKind_03) {
        return;
    }

    if (sNetworkContext->unk_69E == 0) {
        return;
    }

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyStopRecruit();
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);
    GF_ASSERT(v1);

    v1 = WiFiPlazaLobby_Network_ClearRecruitInfo(sNetworkContext, sNetworkContext->gameKind, PPW_LobbyGetMyUserId());
    GF_ASSERT(v1);

    sNetworkContext->unk_69E = 0;
}

void WiFiPlazaLobby_Network_UpdateRecruitInfo(void)
{
    GF_ASSERT(sNetworkContext);

    if (sNetworkContext->unk_69E == 0) {
        return;
    }

    sNetworkContext->unk_5B8[sNetworkContext->gameKind].lobbyRecruitInfo.paramVal = 1;

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbyUpdateRecruitInfo(&sNetworkContext->unk_5B8[sNetworkContext->gameKind].lobbyRecruitInfo);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);

    GF_ASSERT(v1);
}

BOOL WiFiPlazaLobby_Network_IsCurrentRecruitUpdated(void)
{
    GF_ASSERT(sNetworkContext);

    if (sNetworkContext->gameKind == WiFiPlazaLobbyNetworkGameKind_03) {
        return 0;
    }

    if (sNetworkContext->unk_5B8[sNetworkContext->gameKind].lobbyRecruitInfo.paramVal == 1) {
        return 1;
    }

    return 0;
}

BOOL WiFiPlazaLobby_Network_IsRecruitStopped(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    return sNetworkContext->unk_69F;
}

BOOL WiFiPlazaLobby_Network_IsGameRecruiting(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    return WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0);
}

BOOL WiFiPlazaLobby_Network_IsRecruitAcceptingPlayers(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext);

    if (WiFiPlazaLobby_Network_IsGameRecruiting(param0) == 0) {
        return 0;
    }

    if (sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.paramVal == 0) {
        return 1;
    }

    return 0;
}

u32 WiFiPlazaLobby_Network_GetRecruitOpenSlots(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkGameKind_03);

    if (WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0) == 0) {
        return 0;
    }

    const PPW_LobbyRecruitInfo *recruitInfo = WiFiPlazaLobby_Network_GetRecruitInfo(sNetworkContext, param0);

    return recruitInfo->maxNum - recruitInfo->currentNum;
}

u32 WiFiPlazaLobby_Network_GetRecruitPlayerCount(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkGameKind_03);

    if (WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0) == 0) {
        return 0;
    }

    const PPW_LobbyRecruitInfo *recruitInfo = WiFiPlazaLobby_Network_GetRecruitInfo(sNetworkContext, param0);

    return recruitInfo->currentNum;
}

BOOL WiFiPlazaLobby_Network_JoinGameRecruit(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0) == 0) {
        return 0;
    }

    if (sNetworkContext->gameKind != WiFiPlazaLobbyNetworkGameKind_03) {
        return 0;
    }

    if (sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.paramVal == 1) {
        return 0;
    }

    sNetworkContext->gameKind = param0;

    if (NintendoWFC_StartPublicMatchmaking((u8 *)sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.matchMakingString, sNetworkContext->unk_5B8[param0].lobbyRecruitInfo.maxNum, 0, sNetworkContext->unk_5B8[param0].unk_46 / 30)) {
        (void)0;
    }

    NintendoWFC_SetNewClientCallback(WiFiPlazaLobby_Network_HandleNewClient, sNetworkContext);
    NintendoWFC_SetConnectionClosedCB(WiFiPlazaLobby_Network_HandleConnectionClosed, sNetworkContext);

    return 1;
}

s32 WiFiPlazaLobby_Network_GetRecruitTimeLimit(WiFiPlazaLobbyNetworkGameKind param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkGameKind_03);

    if (WiFiPlazaLobby_Network_IsRecruitActive(sNetworkContext, param0) == 0) {
        return 60 * 30;
    }

    return sNetworkContext->unk_5B8[param0].unk_46;
}

s32 WiFiPlazaLobby_Network_GetRecruitHostUserId(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    if (sNetworkContext->gameKind == WiFiPlazaLobbyNetworkGameKind_03) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    return sNetworkContext->unk_5B8[sNetworkContext->gameKind].unk_48;
}

BOOL WiFiPlazaLobby_Network_IsRecruiting(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    return sNetworkContext->unk_69E;
}

BOOL WiFiPlazaLobby_Network_IsVipProfile(s32 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    return WiFiPlazaLobby_Network_ContainsVipProfile(&sNetworkContext->unk_6A0, param0);
}

s32 WiFiPlazaLobby_Network_GetVipKey(s32 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    return WiFiPlazaLobby_Network_FindVipKey(&sNetworkContext->unk_6A0, param0);
}

void WiFiPlazaLobby_Network_SubmitQuestionnaireAnswer(s32 param0)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < PPW_LOBBY_QUESTIONNAIRE_ANSWER_NUM);
    GF_ASSERT(sNetworkContext->unk_6A8.unk_2D8 != WiFiPlazaLobbyNetworkQuestionnaireSubmitState_01);

    u32 v0 = PPW_LobbySubmitQuestionnaire(param0);
    BOOL v1 = WiFiPlazaLobby_Network_CheckLobbyResult(v0);

    GF_ASSERT(v1 == 1);

    sNetworkContext->unk_6A8.unk_2D8 = WiFiPlazaLobbyNetworkQuestionnaireSubmitState_01;
}

WiFiPlazaLobbyNetworkQuestionnaireSubmitState WiFiPlazaLobby_Network_GetQuestionnaireSubmitState(void)
{
    GF_ASSERT(sNetworkContext != NULL);
    return sNetworkContext->unk_6A8.unk_2D8;
}

s32 WiFiPlazaLobby_Network_GetQuestionnaireField(WiFiPlazaLobbyNetworkQuestionnaireField param0)
{
    s32 v0;

    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkQuestionnaireField_11);

    switch (param0) {
    case WiFiPlazaLobbyNetworkQuestionnaireField_00:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.questionSerialNo;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_01:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.questionNo;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_02:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.isSpecialWeek;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_03:
        if (sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.questionNo >= PPW_LOBBY_FREE_QUESTION_START_NO) {
            v0 = 1;
        } else {
            v0 = 0;
        }
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_04:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.questionSerialNo;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_05:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.questionNo;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_06:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.isSpecialWeek;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_07:
        if (sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.questionNo >= PPW_LOBBY_FREE_QUESTION_START_NO) {
            v0 = 1;
        } else {
            v0 = 0;
        }
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireField_08:
    case WiFiPlazaLobbyNetworkQuestionnaireField_09:
    case WiFiPlazaLobbyNetworkQuestionnaireField_10:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastMultiResult[param0 - WiFiPlazaLobbyNetworkQuestionnaireField_08];
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

u16 *WiFiPlazaLobby_Network_GetQuestionnaireText(WiFiPlazaLobbyNetworkQuestionnaireText param0)
{
    u16 *v0;

    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkQuestionnaireText_08);

    switch (param0) {
    case WiFiPlazaLobbyNetworkQuestionnaireText_00:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.questionSentence;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireText_01:
    case WiFiPlazaLobbyNetworkQuestionnaireText_02:
    case WiFiPlazaLobbyNetworkQuestionnaireText_03:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.answer[param0 - WiFiPlazaLobbyNetworkQuestionnaireText_01];
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireText_04:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.questionSentence;
        break;
    case WiFiPlazaLobbyNetworkQuestionnaireText_05:
    case WiFiPlazaLobbyNetworkQuestionnaireText_06:
    case WiFiPlazaLobbyNetworkQuestionnaireText_07:
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.answer[param0 - WiFiPlazaLobbyNetworkQuestionnaireText_05];
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = NULL;
        break;
    }

    return v0;
}

BOOL WiFiPlazaLobby_Network_GetQuestionnaireLanguageFlag(WiFiPlazaLobbyNetworkQuestionnaireLanguage param0, u32 language)
{
    GF_ASSERT(sNetworkContext != NULL);
    GF_ASSERT(param0 < WiFiPlazaLobbyNetworkQuestionnaireLanguage_02);
    GF_ASSERT(language < 12);

    if (param0 >= WiFiPlazaLobbyNetworkQuestionnaireLanguage_02) {
        return 0;
    }

    if (language >= 12) {
        return 0;
    }

    BOOL v0;

    if (param0 == WiFiPlazaLobbyNetworkQuestionnaireLanguage_00) {
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.currentQuestionnaireRecord.multiLanguageSummarizeFlags[language];
    } else {
        v0 = sNetworkContext->unk_6A8.lobbyQuestionnaire.lastQuestionnaireRecord.multiLanguageSummarizeFlags[language];
    }

    return v0;
}

void WiFiPlazaLobby_Network_ResetMatchmaking(void)
{
    GF_ASSERT(sNetworkContext != NULL);

    NintendoWFC_SetNewClientCallback(NULL, NULL);
    NintendoWFC_SetConnectionClosedCB(NULL, NULL);

    sNetworkContext->gameKind = WiFiPlazaLobbyNetworkGameKind_03;
    sNetworkContext->unk_69E = 0;
    sNetworkContext->unk_69F = 0;
}

static BOOL WiFiPlazaLobby_Network_CheckLobbyResult(PPW_LOBBY_RESULT param0)
{
    BOOL v0 = 1;

    switch (param0) {
    case PPW_LOBBY_RESULT_SUCCESS:
        break;
    case PPW_LOBBY_RESULT_ERROR_ALLOC:
    case PPW_LOBBY_RESULT_ERROR_SESSION:
    case PPW_LOBBY_RESULT_ERROR_CHANNEL:
    case PPW_LOBBY_RESULT_ERROR_STATE:
        v0 = 0;
        break;
    case PPW_LOBBY_RESULT_ERROR_PARAM:
    case PPW_LOBBY_RESULT_ERROR_NODATA:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    case PPW_LOBBY_RESULT_ERROR_CONDITION:
        v0 = 0;
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

static void WiFiPlazaLobby_Network_ClearErrorFlags(void)
{
    sNetworkContext->unk_133 = 0;
    sNetworkContext->unk_132 = 0;
}

static WiFiPlazaLobbyNetworkSubChannelKind WiFiPlazaLobby_Network_ChannelKindToSubChannel(PPW_LOBBY_CHANNEL_KIND lobbyChannelKind)
{
    s32 v0 = lobbyChannelKind - 1;

    if (v0 < 0) {
        v0 = WiFiPlazaLobbyNetworkSubChannelKind_04;
    }

    return v0;
}

static PPW_LOBBY_CHANNEL_KIND WiFiPlazaLobby_Network_SubChannelToChannelKind(WiFiPlazaLobbyNetworkSubChannelKind param0)
{
    return param0 + 1;
}

static BOOL WiFiPlazaLobby_Network_AddCountryRegionToChannelData(WiFiPlazaLobbyNetworkContext *param0)
{
    u32 country = WiFiHistory_GetCountry(param0->wiFiHistory);
    u32 region = WiFiHistory_GetRegion(param0->wiFiHistory);

    if (country == Country_Text_None) {
        return 0;
    }

    int v2;

    for (v2 = 0; v2 < 20; v2++) {
        if (param0->unk_134[v2].unk_03 == 0) {
            break;
        }

        if ((param0->unk_134[v2].country == country) && (param0->unk_134[v2].region == region)) {
            return 0;
        }
    }

    if (v2 >= 20) {
        GF_ASSERT(FALSE);
        return 0;
    }

    param0->unk_134[v2].country = country;
    param0->unk_134[v2].region = region;
    param0->unk_134[v2].unk_03 = 1;

    PPW_LOBBY_RESULT lobbyResult = PPW_LobbySetChannelData(PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KIND_MAIN, sWorldDataArchiveName[0], (const u8 *)param0->unk_134, sizeof(WiFiPlazaLobbyNetworkCountryRegion) * 20);

    return WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult);
}

static void WiFiPlazaLobby_Network_AllocPlayerProfileBuffer(WiFiPlazaLobbyNetworkContext *unused, u32 param1, u32 heapID)
{
    sNetworkContext->unk_24 = Heap_Alloc(heapID, param1 * PPW_LOBBY_MAX_PLAYER_NUM_MAIN);
    memset(sNetworkContext->unk_24, 0, param1 * PPW_LOBBY_MAX_PLAYER_NUM_MAIN);
    sNetworkContext->unk_28 = param1;
}

static void WiFiPlazaLobby_Network_FreePlayerProfileBuffer(WiFiPlazaLobbyNetworkContext *unused)
{
    Heap_Free(sNetworkContext->unk_24);
}

static void WiFiPlazaLobby_Network_SetPlayerData(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const void *param2)
{
    WiFiPlazaLobby_Network_SetPlayerDataWithSize(param0, param1, param2, param0->unk_28);
}

static void WiFiPlazaLobby_Network_SetPlayerDataWithSize(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const void *param2, u32 param3)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    u8 *v1 = param0->unk_24;
    v1 = &v1[param0->unk_28 * v0];
    u32 v2;

    if (param0->unk_28 > param3) {
        v2 = param3;
        memset(v1, 0, param0->unk_28);
    } else {
        v2 = param0->unk_28;
    }

    memcpy(v1, param2, v2);
}

static const void *WiFiPlazaLobby_Network_GetPlayerDataFromContext(const WiFiPlazaLobbyNetworkContext *param0, s32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    const u8 *v1 = param0->unk_24;
    v1 = &v1[param0->unk_28 * v0];

    return v1;
}

static void WiFiPlazaLobby_Network_ClearPlayerData(WiFiPlazaLobbyNetworkContext *param0, s32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    u8 *v1 = param0->unk_24;
    v1 = &v1[param0->unk_28 * v0];

    memset(v1, 0, param0->unk_28);
}

static void WiFiPlazaLobby_Network_SetPlayerSystemProfile(WiFiPlazaLobbyNetworkContext *param0, s32 param1, const PPW_LobbySystemProfile *lobbySystemProfile)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    param0->sysProfile[v0] = *lobbySystemProfile;
}

static const PPW_LobbySystemProfile *WiFiPlazaLobby_Network_GetPlayerSystemProfile(const WiFiPlazaLobbyNetworkContext *param0, s32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    return &param0->sysProfile[v0];
}

static void WiFiPlazaLobby_Network_ClearPlayerSystemProfile(WiFiPlazaLobbyNetworkContext *param0, s32 param1)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, 0);
    GF_ASSERT(v0 != 0xffffffff);

    memset(&param0->sysProfile[v0], 0, sizeof(PPW_LobbySystemProfile));
}

static void WiFiPlazaLobby_Network_InitPlayerIdLists(WiFiPlazaLobbyNetworkContext *param0, u32 param1, u32 param2, u32 heapID)
{
    int v1;

    for (int i = 0; i < 2; i++) {
        GF_ASSERT(param0->unk_11C[i].unk_04 == NULL);

        if (i == 0) {
            v1 = param1;
        } else {
            v1 = param2;
        }

        param0->unk_11C[i].unk_00 = 0;
        param0->unk_11C[i].unk_04 = Heap_Alloc(heapID, sizeof(s32) * v1);
        param0->unk_11C[i].unk_02 = v1;

        WiFiPlazaLobby_Network_ResetPlayerIdList(param0, i);
    }
}

static void WiFiPlazaLobby_Network_FreePlayerIdLists(WiFiPlazaLobbyNetworkContext *param0)
{
    for (int i = 0; i < 2; i++) {
        GF_ASSERT(param0->unk_11C[i].unk_04 != NULL);
        Heap_Free(param0->unk_11C[i].unk_04);
        param0->unk_11C[i].unk_04 = NULL;
    }
}

static void WiFiPlazaLobby_Network_ResetPlayerIdList(WiFiPlazaLobbyNetworkContext *param0, u32 param1)
{
    param0->unk_11C[param1].unk_00 = 0;

    for (int i = 0; i < param0->unk_11C[param1].unk_02; i++) {
        param0->unk_11C[param1].unk_04[i] = DWC_LOBBY_INVALID_USER_ID;
    }
}

static void WiFiPlazaLobby_Network_AddPlayerId(WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2)
{
    if (WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, param2) != 0xffffffff) {
        return;
    }

    GF_ASSERT(param0->unk_11C[param2].unk_00 < param0->unk_11C[param2].unk_02);

    if (param0->unk_11C[param2].unk_00 >= param0->unk_11C[param2].unk_02) {
        return;
    }

    u32 v0;

    for (int i = 0; i < param0->unk_11C[param2].unk_02; i++) {
        if (param0->unk_11C[param2].unk_04[i] == DWC_LOBBY_INVALID_USER_ID) {
            v0 = i;
            break;
        }
    }

    param0->unk_11C[param2].unk_04[v0] = param1;
    param0->unk_11C[param2].unk_00++;
}

static void WiFiPlazaLobby_Network_RemovePlayerId(WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2)
{
    u32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(param0, param1, param2);

    if (v0 == 0xffffffff) {
        return;
    }

    param0->unk_11C[param2].unk_04[v0] = DWC_LOBBY_INVALID_USER_ID;
    param0->unk_11C[param2].unk_00--;
}

static s32 WiFiPlazaLobby_Network_FindPlayerIndex(const WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2)
{
    for (int i = 0; i < param0->unk_11C[param2].unk_02; i++) {
        if (param0->unk_11C[param2].unk_04[i] == param1) {
            return i;
        }
    }

    return 0xffffffff;
}

static s32 WiFiPlazaLobby_Network_GetPlayerIdAt(const WiFiPlazaLobbyNetworkContext *param0, s32 param1, u32 param2)
{
    GF_ASSERT(param1 < param0->unk_11C[param2].unk_02);
    return param0->unk_11C[param2].unk_04[param1];
}

static void WiFiPlazaLobby_Network_RebuildSubChannelPlayers(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkSubChannelKind param1)
{
    s32 v1;
    u32 v2 = WiFiPlazaLobby_Network_SubChannelToChannelKind(param1);
    WiFiPlazaLobby_Network_ResetPlayerIdList(param0, 1);

    for (int v0 = 0; v0 < param0->unk_11C[0].unk_02; v0++) {
        v1 = WiFiPlazaLobby_Network_GetPlayerIdAt(param0, v0, 0);

        if (v1 != 0xffffffff) {
            if (param0->sysProfile[v0].subChannelKind == v2) {
                WiFiPlazaLobby_Network_AddPlayerId(param0, v1, 1);
            }
        }
    }
}

static BOOL WiFiPlazaLobby_Network_HasSubChannelRoom(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkSubChannelKind param1)
{
    static const u8 v4[WiFiPlazaLobbyNetworkSubChannelKind_04] = {
        PPW_LOBBY_MAX_PLAYER_NUM_FOOT,
        PPW_LOBBY_MAX_PLAYER_NUM_FOOT,
        PPW_LOBBY_MAX_PLAYER_NUM_CLOCK,
        PPW_LOBBY_MAX_PLAYER_NUM_NEWS,
    };

    GF_ASSERT(param1 < WiFiPlazaLobbyNetworkSubChannelKind_04);

    u32 v3 = WiFiPlazaLobby_Network_SubChannelToChannelKind(param1);
    int v1 = 0;
    s32 v2;

    for (int i = 0; i < param0->unk_11C[0].unk_02; i++) {
        v2 = WiFiPlazaLobby_Network_GetPlayerIdAt(param0, i, 0);

        if (v2 != 0xffffffff) {
            if (param0->sysProfile[i].subChannelKind == v3) {
                v1++;
            }
        }
    }

    if (v4[param1] > v1) {
        return 1;
    }

    return 0;
}

static void WiFiPlazaLobby_Network_HandleJoinChannel(BOOL param0, PPW_LOBBY_CHANNEL_KIND lobbyChannelKind)
{
    if (lobbyChannelKind == PPW_LOBBY_CHANNEL_KIND_MAIN) {
        sNetworkContext->unk_5B4 = 1024;
        PPW_LOBBY_RESULT lobbyResult = PPW_LobbyGetSchedule((PPW_LobbySchedule *)sNetworkContext->unk_1B4, &sNetworkContext->unk_5B4);
        GF_ASSERT(WiFiPlazaLobby_Network_CheckLobbyResult(lobbyResult));

        PPW_LobbyGetChannelDataAsync(PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KIND_MAIN, sWorldDataArchiveName[0], NULL);
    } else {
        if (sNetworkContext->unk_12D == WiFiPlazaLobby_Network_ChannelKindToSubChannel(lobbyChannelKind)) {
            if (param0 == 1) {
                sNetworkContext->unk_12F = WiFiPlazaLobbyNetworkSubChannelJoinState_01;

                WiFiPlazaLobby_Network_RebuildSubChannelPlayers(sNetworkContext, sNetworkContext->unk_12D);
                WiFiPlazaLobby_Network_AddPlayerId(sNetworkContext, PPW_LobbyGetMyUserId(), 1);
            } else {
                sNetworkContext->unk_12F = WiFiPlazaLobbyNetworkSubChannelJoinState_02;
            }
        } else {
            GF_ASSERT(FALSE);
            WiFiPlazaLobby_Network_LeaveSubChannel();
        }
    }
}

static void WiFiPlazaLobby_Network_HandlePlayerConnected(s32 userId, const PPW_LobbySystemProfile *param1, const u8 *param2, u32 param3)
{
    BOOL v0;

    if (userId == PPW_LobbyGetMyUserId()) {
        {
            PPW_LobbyGetTimeInfo(&sNetworkContext->timeInfo);
        }

        v0 = 1;
    } else {
        v0 = 0;
    }

    WiFiPlazaLobby_Network_AddPlayerId(sNetworkContext, userId, 0);
    WiFiPlazaLobby_Network_SetPlayerDataWithSize(sNetworkContext, userId, param2, param3);
    WiFiPlazaLobby_Network_SetPlayerSystemProfile(sNetworkContext, userId, param1);

    sNetworkContext->unk_0C.unk_00(userId, WiFiPlazaLobby_Network_GetPlayerDataFromContext(sNetworkContext, userId), sNetworkContext->unk_20, v0);
}

static void WiFiPlazaLobby_Network_HandlePlayerDisconnected(s32 param0)
{
    if (WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0) == 0xffffffff) {
        return;
    }

    {
        for (int i = 0; i < WiFiPlazaLobbyNetworkGameKind_03; i++) {
            if (sNetworkContext->unk_5B8[i].unk_48 == param0) {
                WiFiPlazaLobby_Network_HandleRecruitStopped(param0, &sNetworkContext->unk_5B8[i].lobbyRecruitInfo);
            }
        }
    }

    sNetworkContext->unk_0C.unk_04(param0, sNetworkContext->unk_20);

    WiFiPlazaLobby_Network_ClearPlayerSystemProfile(sNetworkContext, param0);
    WiFiPlazaLobby_Network_ClearPlayerData(sNetworkContext, param0);

    WiFiPlazaLobby_Network_RemovePlayerId(sNetworkContext, param0, 0);
    WiFiPlazaLobby_Network_RemovePlayerId(sNetworkContext, param0, 1);
}

static void WiFiPlazaLobby_Network_HandleStringMessageReceived(s32 unused1, PPW_LOBBY_CHANNEL_KIND unused2, s32 unused3, const char *unused4)
{
}

static void WiFiPlazaLobby_Network_HandleBinaryMessageReceived(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, s32 param2, const u8 *param3, u32 param4)
{
    s32 v2 = WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);

    if (v2 == 0xffffffff) {
        return;
    }

    u32 v0;

    switch (param1) {
    case PPW_LOBBY_CHANNEL_KIND_MAIN:
        v0 = 0;
        break;
    case PPW_LOBBY_CHANNEL_KIND_FOOT1:
    case PPW_LOBBY_CHANNEL_KIND_FOOT2:
    case PPW_LOBBY_CHANNEL_KIND_CLOCK:
    case PPW_LOBBY_CHANNEL_KIND_NEWS:
        u32 v1 = WiFiPlazaLobby_Network_ChannelKindToSubChannel(param1);

        if (sNetworkContext->unk_12D == v1) {
            v0 = 1;
        } else {
            return;
        }
        break;
    case PPW_LOBBY_CHANNEL_KIND_INVALID:
        v0 = 0;
        break;
    default:
        return;
    }

    if (sNetworkContext->unk_184[v0].unk_04 > param2) {
        GF_ASSERT(sNetworkContext->unk_184[v0].unk_00[param2].unk_04 <= param4);
        sNetworkContext->unk_184[v0].unk_00[param2].unk_00(param0, param3, sNetworkContext->unk_184[v0].unk_00[param2].unk_04, sNetworkContext->unk_184[v0].unk_08);
    } else {
        (void)0;
    }
}

static void WiFiPlazaLobby_Network_HandleGetChannelData(BOOL unused1, BOOL unused2, PPW_LOBBY_CHANNEL_KIND unused3, s32 unused4, const char *param4, const u8 *param5, u32 unused5, void *unused6)
{
    if (strcmp(param4, sWorldDataArchiveName[0]) == 0) {
        memcpy(sNetworkContext->unk_134, param5, sizeof(WiFiPlazaLobbyNetworkCountryRegion) * 20);

        if (sNetworkContext->unk_130) {
            sNetworkContext->unk_130 = 0;
        }
    }
}

static void WiFiPlazaLobby_Network_HandleSystemProfileUpdated(s32 param0, const PPW_LobbySystemProfile *sysProfile)
{
    u32 channelKind2, channelKind1, v2;
    s32 v4 = WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);

    if (v4 == 0xffffffff) {
        return;
    }

    if (sNetworkContext->unk_12D != WiFiPlazaLobbyNetworkSubChannelKind_04) {
        const PPW_LobbySystemProfile *lobbySysProfile = WiFiPlazaLobby_Network_GetPlayerSystemProfile(sNetworkContext, param0);
        channelKind1 = lobbySysProfile->subChannelKind;
        channelKind2 = sysProfile->subChannelKind;
        v2 = WiFiPlazaLobby_Network_SubChannelToChannelKind(sNetworkContext->unk_12D);

        if ((channelKind1 == PPW_LOBBY_CHANNEL_KIND_INVALID) && (channelKind2 == v2)) {
            WiFiPlazaLobby_Network_AddPlayerId(sNetworkContext, param0, 1);
        } else if ((channelKind1 == v2) && (channelKind2 != v2)) {
            WiFiPlazaLobby_Network_RemovePlayerId(sNetworkContext, param0, 1);
        }
    }

    WiFiPlazaLobby_Network_SetPlayerSystemProfile(sNetworkContext, param0, sysProfile);
}

static void WiFiPlazaLobby_Network_HandleUserProfileUpdated(s32 param0, const u8 *param1, u32 unused)
{
    s32 v0 = WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);

    if (v0 == 0xffffffff) {
        return;
    }

    WiFiPlazaLobby_Network_SetPlayerData(sNetworkContext, param0, param1);

    sNetworkContext->unk_0C.unk_08(param0, param1, sNetworkContext->unk_20);
}

static void WiFiPlazaLobby_Network_HandleRecruit(s32 param0, const PPW_LobbyRecruitInfo *recruitInfo)
{
    s32 v3 = WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);

    if (v3 == 0xffffffff) {
        return;
    }

    u32 v0 = WiFiPlazaLobby_Network_GetMyUserId();

    if (v0 != param0) {
        if (sNetworkContext->unk_69E) {
            if (sNetworkContext->gameKind == recruitInfo->gameKind) {
                s64 v1, v2;
                WiFiPlazaLobby_Network_GetRecruitStartTime(&sNetworkContext->unk_5B8[sNetworkContext->gameKind].lobbyRecruitInfo, &v1);
                WiFiPlazaLobby_Network_GetRecruitStartTime(recruitInfo, &v2);

                if (v1 >= v2) {
                    sNetworkContext->unk_69F = 1;

                    WiFiPlazaLobby_Network_StopGameRecruit();
                } else {
                    return;
                }
            }
        }
    }

    WiFiPlazaLobby_Network_SetRecruitInfo(sNetworkContext, recruitInfo->gameKind, param0, recruitInfo);
}

static void WiFiPlazaLobby_Network_HandleRecruitStopped(s32 param0, const PPW_LobbyRecruitInfo *recruitInfo)
{
    s32 v1 = WiFiPlazaLobby_Network_FindPlayerIndex(sNetworkContext, param0, 0);

    if (v1 == 0xffffffff) {
        return;
    }

    BOOL v0 = WiFiPlazaLobby_Network_ClearRecruitInfo(sNetworkContext, recruitInfo->gameKind, param0);

    if ((sNetworkContext->gameKind == recruitInfo->gameKind) && (v0 == 1)) {
        sNetworkContext->unk_69F = 1;
    }
}

static void WiFiPlazaLobby_Network_HandleScheduleProgress(PPW_LOBBY_TIME_EVENT timeEvent)
{
    sNetworkContext->unk_0C.unk_0C(timeEvent, sNetworkContext->unk_20);
}

static void WiFiPlazaLobby_Network_HandleCheckProfile(PPW_LOBBY_STATS_RESULT statsResult, const u8 *param1, u32 param2)
{
    if (statsResult != PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sNetworkContext->unk_133 = 1;
    } else {
        sNetworkContext->unk_0C.unk_10(param1, param2, sNetworkContext->unk_20);
    }
}

static BOOL WiFiPlazaLobby_Network_HandleNotifySchedule(PPW_LOBBY_STATS_RESULT statsResult, const PPW_LobbySchedule *unused)
{
    if (statsResult == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        return 1;
    }

    sNetworkContext->unk_132 = 1;
    return 0;
}

static void WiFiPlazaLobby_Network_HandleGetVip(PPW_LOBBY_STATS_RESULT lobbyStatsResult, const PPW_LobbyVipRecord *lobbyVipRecord, u32 param2)
{
    if (lobbyStatsResult == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        WiFiPlazaLobby_Network_SetVipRecords(&sNetworkContext->unk_6A0, lobbyVipRecord, param2);
    } else {
        sNetworkContext->unk_132 = 1;
    }
}

static void WiFiPlazaLobby_Network_HandleGetQuestionnaire(PPW_LOBBY_STATS_RESULT lobbyStatsResult, const PPW_LobbyQuestionnaire *lobbyQuestionnaire)
{
    if (lobbyStatsResult == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        WiFiPlazaLobby_Network_SetQuestionnaire(&sNetworkContext->unk_6A8, lobbyQuestionnaire);
    } else {
        sNetworkContext->unk_132 = 1;
    }
}

static void WiFiPlazaLobby_Network_HandleSubmitQuestionnaire(PPW_LOBBY_STATS_RESULT lobbyStatsResult)
{
    GF_ASSERT(sNetworkContext->unk_6A8.unk_2D8 == WiFiPlazaLobbyNetworkQuestionnaireSubmitState_01);

    if (lobbyStatsResult == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sNetworkContext->unk_6A8.unk_2D8 = WiFiPlazaLobbyNetworkQuestionnaireSubmitState_02;
    } else {
        sNetworkContext->unk_6A8.unk_2D8 = WiFiPlazaLobbyNetworkQuestionnaireSubmitState_02;
    }
}

static void WiFiPlazaLobby_Network_HandleExcessFlood(u32 unused)
{
    sNetworkContext->unk_131 = 1;
}

static void WiFiPlazaLobby_Network_ResetRecruitInfo(WiFiPlazaLobbyNetworkContext *param0)
{
    memset(param0->unk_5B8, 0, sizeof(WiFiPlazaLobbyNetworkRecruit) * WiFiPlazaLobbyNetworkGameKind_03);
    param0->gameKind = WiFiPlazaLobbyNetworkGameKind_03;
}

static void WiFiPlazaLobby_Network_SetRecruitInfo(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind gameKind, s32 param2, const PPW_LobbyRecruitInfo *lobbyRecruitInfo)
{
    GF_ASSERT(gameKind < WiFiPlazaLobbyNetworkGameKind_03);

    if (WiFiPlazaLobby_Network_IsRecruitActive(param0, gameKind) == 1) {
        if (param0->unk_5B8[gameKind].unk_48 != param2) {
            return;
        }
    }

    param0->unk_5B8[gameKind].lobbyRecruitInfo = *lobbyRecruitInfo;

    if (param0->unk_5B8[gameKind].unk_44 == 0) {
        param0->unk_5B8[gameKind].unk_44 = 1;
        param0->unk_5B8[gameKind].unk_48 = param2;
        param0->unk_5B8[gameKind].unk_46 = WiFiPlazaLobby_Network_GetRecruitRemainingTime(param0, gameKind);
    }
}

static BOOL WiFiPlazaLobby_Network_ClearRecruitInfo(WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1, s32 param2)
{
    GF_ASSERT(param1 < WiFiPlazaLobbyNetworkGameKind_03);

    if (WiFiPlazaLobby_Network_IsRecruitActive(param0, param1) == 1) {
        if (param0->unk_5B8[param1].unk_48 == param2) {
            param0->unk_5B8[param1].unk_44 = 0;
            return 1;
        }
    }

    return 0;
}

static BOOL WiFiPlazaLobby_Network_IsRecruitActive(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1)
{
    GF_ASSERT(param1 < WiFiPlazaLobbyNetworkGameKind_03);
    return param0->unk_5B8[param1].unk_44;
}

static u16 WiFiPlazaLobby_Network_GetRecruitRemainingTime(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1)
{
    if (WiFiPlazaLobby_Network_IsRecruitActive(param0, param1) == 0) {
        return 0;
    }

    const PPW_LobbyRecruitInfo *recruitInfo = WiFiPlazaLobby_Network_GetRecruitInfo(param0, param1);
    s64 v0;
    WiFiPlazaLobby_Network_GetRecruitStartTime(recruitInfo, &v0);
    s64 v1 = param0->timeInfo.currentTime - v0;

    if (v1 > 30) {
        v1 = 30;
    } else if (v1 < 0) {
        v1 = 0;
    }

    return (60 - v1) * 30;
}

static const PPW_LobbyRecruitInfo *WiFiPlazaLobby_Network_GetRecruitInfo(const WiFiPlazaLobbyNetworkContext *param0, WiFiPlazaLobbyNetworkGameKind param1)
{
    GF_ASSERT(param1 < WiFiPlazaLobbyNetworkGameKind_03);
    GF_ASSERT(param0->unk_5B8[param1].unk_44 == 1);
    return &param0->unk_5B8[param1].lobbyRecruitInfo;
}

static void WiFiPlazaLobby_Network_UpdateRecruitProgress(WiFiPlazaLobbyNetworkContext *unused)
{
    if (sNetworkContext->unk_69E == 1) {
        u32 numConnections = NintendoWFC_GetNumConnections();
        GF_ASSERT(numConnections <= 4);
        WiFiPlazaLobbyNetworkRecruit *v2 = &sNetworkContext->unk_5B8[sNetworkContext->gameKind];

        if (v2->lobbyRecruitInfo.currentNum != numConnections) {
            v2->lobbyRecruitInfo.currentNum = numConnections;
            PPW_LobbyUpdateRecruitInfo(&v2->lobbyRecruitInfo);
        }
    }

    u16 v1;

    for (int i = 0; i < WiFiPlazaLobbyNetworkGameKind_03; i++) {
        if (sNetworkContext->unk_5B8[i].unk_44 == 1) {
            if (sNetworkContext->unk_5B8[i].unk_46 > 0) {
                sNetworkContext->unk_5B8[i].unk_46--;
            }

            v1 = WiFiPlazaLobby_Network_GetRecruitRemainingTime(sNetworkContext, i);

            if (v1 < sNetworkContext->unk_5B8[i].unk_46) {
                sNetworkContext->unk_5B8[i].unk_46 = v1;
            }
        }
    }
}

static void WiFiPlazaLobby_Network_SetRecruitStartTime(PPW_LobbyRecruitInfo *lobbyRecruitInfo, const s64 *param1)
{
    s64 *v0 = (s64 *)lobbyRecruitInfo->paramBuf;
    *v0 = *param1;
}

static void WiFiPlazaLobby_Network_GetRecruitStartTime(const PPW_LobbyRecruitInfo *lobbyRecruitInfo, s64 *param1)
{
    const s64 *v0 = (const s64 *)lobbyRecruitInfo->paramBuf;
    *param1 = *v0;
}

static void WiFiPlazaLobby_Network_HandleNewClient(u16 unused1, void *unused2)
{
}

static void WiFiPlazaLobby_Network_HandleConnectionClosed(u16 param0, void *param1)
{
    WiFiPlazaLobbyNetworkContext *v0 = param1;

    if (v0->unk_69E == 1) {
        WiFiPlazaLobby_Network_StopGameRecruit();
    } else {
        if (param0 == 0) {
            sNetworkContext->unk_69F = 1;
        }
    }
}

static u32 WiFiPlazaLobby_Network_GetScheduleEventTime(const PPW_LobbySchedule *lobbySchedule, PPW_LOBBY_TIME_EVENT lobbyTimeEvent)
{
    u32 time = 0;

    for (int i = 0; i < lobbySchedule->scheduleRecordNum; i++) {
        if (lobbySchedule->scheduleRecords[i].event == lobbyTimeEvent) {
            time = lobbySchedule->scheduleRecords[i].time;
        }
    }

    return time;
}

static void WiFiPlazaLobby_Network_InitVipRecordBuffer(WiFiPlazaLobbyNetworkVipRecordBuffer *param0, u32 param1, u32 heapID)
{
    param0->lobbyVipRecord = Heap_Alloc(heapID, sizeof(PPW_LobbyVipRecord) * param1);
    param0->unk_04 = param1;
    param0->unk_06 = 0;
}

static void WiFiPlazaLobby_Network_FreeVipRecordBuffer(WiFiPlazaLobbyNetworkVipRecordBuffer *param0)
{
    Heap_Free(param0->lobbyVipRecord);
    param0->lobbyVipRecord = NULL;
}

static void WiFiPlazaLobby_Network_SetVipRecords(WiFiPlazaLobbyNetworkVipRecordBuffer *param0, const PPW_LobbyVipRecord *lobbyVipRecord, u32 param2)
{
    GF_ASSERT(param2 < param0->unk_04);

    u32 v0;

    if (param2 < param0->unk_04) {
        v0 = param2;
    } else {
        v0 = param0->unk_04;
    }

    MI_CpuCopy32(lobbyVipRecord, param0->lobbyVipRecord, sizeof(PPW_LobbyVipRecord) * v0);
    param0->unk_06 = v0;
}

static BOOL WiFiPlazaLobby_Network_ContainsVipProfile(const WiFiPlazaLobbyNetworkVipRecordBuffer *param0, s32 param1)
{
    for (int i = 0; i < param0->unk_06; i++) {
        if (param0->lobbyVipRecord[i].profileId == param1) {
            return 1;
        }
    }

    return 0;
}

static s32 WiFiPlazaLobby_Network_FindVipKey(const WiFiPlazaLobbyNetworkVipRecordBuffer *param0, s32 param1)
{
    for (int i = 0; i < param0->unk_06; i++) {
        if (param0->lobbyVipRecord[i].profileId == param1) {
            return param0->lobbyVipRecord[i].key;
        }
    }

    return 0;
}

static void WiFiPlazaLobby_Network_SetQuestionnaire(WiFiPlazaLobbyNetworkQuestionnaire *param0, const PPW_LobbyQuestionnaire *lobbyQuestionnaire)
{
    memcpy(&param0->lobbyQuestionnaire, lobbyQuestionnaire, sizeof(PPW_LobbyQuestionnaire));
}
