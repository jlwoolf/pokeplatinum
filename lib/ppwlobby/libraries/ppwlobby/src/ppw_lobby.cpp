#include <lobby/dwci_lobby.h>

// include order necessary to match
// clang-format off
#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobby_util.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "ppwlobby/ppw_lobby_impl.h"
#include "ppwlobby/ppw_parser.h"
#include "ppwlobby/dwci_encsession.h"
// clang-format on

static const char *const PPW_LOBBY_CHANNEL_PREFIX_NAMES[] = {
    "M",
    "F1",
    "F2",
    "C",
    "N",
    "Invalid"
};

static const char *sEncInitData = "uLMOGEiiJogofchScpXb000244fd00006015100000005b440e7epokemondpds";

typedef enum ENC_SERVER_RESPONSE_CODE {
    ENC_SERVER_RESPONSE_CODE_OK = 0,
    ENC_SERVER_RESPONSE_CODE_INVALID_PARAM = 6,
    ENC_SERVER_RESPONSE_CODE_INTERNAL_ERROR = 7,
    ENC_SERVER_RESPONSE_CODE_DATABASE_ERROR = 8,
    ENC_SERVER_RESPONSE_CODE_MAINTENANCE = 9,
    ENC_SERVER_RESPONSE_CODE_UNKNOWN_ERROR = 10
} ENC_SERVER_RESPONSE_CODE;

static const char *sEncCheckProfilePath = "/web/enc/lobby/checkProfile.asp";

static const char *sEncGetSchedulePath = "/web/enc/lobby/getSchedule.asp";

static const char *sEncGetVipPath = "/web/enc/lobby/getVIP.asp";

static const char *sEncGetQuestionnairePath = "/web/enc/lobby/getQuestionnaire.asp";

static const char *sEncSubmitQuestionnairePath = "/web/enc/lobby/submitQuestionnaire.asp";

static const u32 PPW_LOBBY_TIMER_ID_SYSTEM_CHANNEL_DATA = 1;
static const u32 PPW_LOBBY_TIMER_ID_USER_CHANNEL_DATA = 2;
static const u32 PPW_LOBBY_TIMER_ID_RECRUIT = 3;
static const u32 PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_MODE = 4;
static const u32 PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_SYSTEMDATA = 5;
static const u32 PPW_LOBBY_TIMER_ID_CHECK_LOBBY_INFO = 6;

static const u32 PPW_LOBBY_TIMER_INTERVAL_SYSTEM_CHANNEL_DATA = 3;
static const u32 PPW_LOBBY_TIMER_INTERVAL_USER_CHANNEL_DATA = 4;
static const u32 PPW_LOBBY_TIMER_INTERVAL_RECRUIT = 5;
static const u32 PPW_LOBBY_TIMER_INTERVAL_CHECK_MAINCHANNEL_MODE = 3;
static const u32 PPW_LOBBY_TIMER_INTERVAL_CHECK_MAINCHANNEL_SYSTEMDATA = 4;
static const u32 PPW_LOBBY_TIMER_INTERVAL_CHECK_LOBBY_INFO = 4;

static PPW_LobbyImpl *sLobbyImpl = NULL;

PPW_LobbyImpl *PPW_LobbyGetImpl()
{
    return sLobbyImpl;
}

static PPW_LOBBY_RESULT PPW_LobbyInitialize(const char *param0, const char *param1, DWC_LOBBY_CHANNEL_PREFIX param2, const PPW_LobbyCallbacks *param3, s32 param4, const u8 *param5, u32 param6, BOOL param7);
static PPW_LOBBY_RESULT PPW_LobbyEnterMainChannel();
static void PPW_LobbyRequestCheckProfile();
static PPWString PPW_LobbyMakeChannelName(PPW_LOBBY_CHANNEL_KIND param0, const PPWString &param1);
static BOOL PPW_LobbyIsMainChannelReady();
static BOOL PPW_LobbyHandleChannelKey(BOOL param0, BOOL param1, PPW_LOBBY_CHANNEL_KIND param2, s32 param3, const char *param4, const u8 *param5, u32 param6, void *param7);
static BOOL PPW_LobbySendRecruit(void *param0);
static void PPW_LobbyOnCheckProfile(BOOL param0, const u8 *param1, u32 param2, void *param3);
static void PPW_LobbyOnSchedule(BOOL param0, const u8 *param1, u32 param2, void *param3);
static void PPW_LobbyOnVip(BOOL param0, const u8 *param1, u32 param2, void *param3);
static void PPW_LobbyOnQuestionnaire(BOOL param0, const u8 *param1, u32 param2, void *param3);
static void PPW_LobbyOnSubmitQuestionnaire(BOOL param0, const u8 *param1, u32 param2, void *param3);
static void PPW_LobbyOnEnterMainChannel(BOOL param0, DWCi_LOBBY_ENTER_RESULT param1, const char *param2, void *param3);
static void PPW_LobbyOnEnterSubChannel(BOOL param0, DWCi_LOBBY_ENTER_RESULT param1, const char *param2, void *param3);
static void PPW_LobbyOnPlayerConnected(const char *param0, s32 param1, void *param2);
static void PPW_LobbyOnPlayerDisconnected(const char *param0, s32 param1, void *param2);
static void PPW_LobbyOnChannelMessage(const char *param0, s32 param1, const char *param2, void *param3);
static void PPW_LobbyOnUserMessage(s32 param0, const char *param1, void *param2);
static void PPW_LobbyOnExcessFlood(u32 param0, void *param1);
static void PPW_LobbyOnBroadcastData(const char *param0, s32 param1, const char *param2, const char *param3, void *param4);
static void PPW_LobbyOnChannelData(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5);
static void PPW_LobbyOnEnumChannels(BOOL param0, s32 param1, const char **param2, const char **param3, const s32 *param4, void *param5);
static void PPW_LobbyOnEnumUsers(BOOL param0, const char *param1, s32 param2, const s32 *param3, void *param4);
static void PPW_LobbyOnChannelMode(BOOL param0, const char *param1, const DWCi_LobbyChannelMode *param2, void *param3);
static void PPW_LobbyOnChannelTime(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5);
static void PPW_LobbyOnChannelLobby(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5);
static void PPW_LobbyOnTopicChanged(const char *param0, const char *param1, void *param2);

static inline PPW_LOBBY_RESULT PPW_LobbyApplyResult(DWCi_LOBBY_RESULT param0)
{
    PPW_STATIC_ASSERT(DWCi_LOBBY_RESULT_MAX == PPW_LOBBY_RESULT_MAX);

    PPW_LOBBY_RESULT v0 = (PPW_LOBBY_RESULT)param0;

    sLobbyImpl->SetResultError(v0);

    return v0;
}

class EncCommonRequest : public DWCi_LobbyObject {
    s32 pid;
    u16 requestVersion;
    u8 romVersion;
    u8 language;
    u8 macAddr[6];
    u16 reserve1;
    u32 reserve2;

public:
    EncCommonRequest()
    {
        const PPW_PlayerProfile::UserData &v0 = sLobbyImpl->GetPlayers().GetMyProfile().GetUserDataStore();
        const WiFiPlazaProfile *v1 = (const WiFiPlazaProfile *)PPW_GetVectorData(v0.unk_00);

        pid = sLobbyImpl->GetPid();
        requestVersion = PPW_LOBBY_ENC_REQUEST_VERSION;
        romVersion = v1->gameVersion;
        language = v1->language;
        OS_GetMacAddress(macAddr);
    }

    ~EncCommonRequest()
    {
    }
};

PPW_LOBBY_RESULT PPW_LobbyInitializeAsync(const char *gameName, const char *secretKey, DWC_LOBBY_CHANNEL_PREFIX prefix, const PPW_LobbyCallbacks *lobbyCallbacks, const DWCUserData *dwcUserData, const u8 *userProfile, u32 userProfileSize)
{
    if (!DWC_CheckUserData(dwcUserData) || !DWC_CheckHasProfile(dwcUserData)) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    return PPW_LobbyInitialize(gameName, secretKey, prefix, lobbyCallbacks, dwcUserData->gs_profile_id, userProfile, userProfileSize, TRUE);
}

PPW_LOBBY_RESULT PPW_LobbyInitializePidAsync(const char *gameName, const char *secretKey, DWC_LOBBY_CHANNEL_PREFIX prefix, const PPW_LobbyCallbacks *lobbyCallbacks, s32 pid, const u8 *userProfile, u32 userProfileSize)
{
    return PPW_LobbyInitialize(gameName, secretKey, prefix, lobbyCallbacks, pid, userProfile, userProfileSize, FALSE);
}

static PPW_LOBBY_RESULT PPW_LobbyInitialize(const char *param0, const char *param1, DWC_LOBBY_CHANNEL_PREFIX param2, const PPW_LobbyCallbacks *param3, s32 param4, const u8 *param5, u32 param6, BOOL param7)
{
    if (sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    DWCi_LobbyGlobalCallbacks v0;
    v0.lobbyUserMessageReceivedCallback = PPW_LobbyOnUserMessage;
    v0.lobbyExcessFloodCallback = PPW_LobbyOnExcessFlood;
    v0.param = (void *)PPW_LOBBY_CHANNEL_KIND_INVALID;

    sLobbyImpl = new PPW_LobbyImpl(*param3, param4, param2, param7);
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_ALLOC;
    }

    PPW_LOBBY_RESULT v1 = PPW_LobbyApplyResult(DWCi_LobbyInitializePidAsync(param0, param1, param2, &v0, param4));
    if (v1 != PPW_LOBBY_RESULT_SUCCESS) {
        if (sLobbyImpl) {
            delete sLobbyImpl;
            sLobbyImpl = NULL;
        }
        return v1;
    }

    sLobbyImpl->GetPlayers().SetMyProfile(param4, param5, param6);

    PPW_LobbyRequestCheckProfile();

    sLobbyImpl->SetState(PPW_LOBBY_STATE_CONNECTING);
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyShutdownAsync()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_SUCCESS;
    }

    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return PPW_LOBBY_RESULT_SUCCESS;
    }

    sLobbyImpl->GetTimers().Clear();

    sLobbyImpl->SetState(PPW_LOBBY_STATE_CLOSING);
    return PPW_LobbyApplyResult(DWCi_LobbyShutdownAsync());
}

PPW_LOBBY_STATE PPW_LobbyProcess()
{
    BOOL v0 = PPW_EncSession::ProcessActive();

    if (v0) {
        if (!sLobbyImpl) {
            return PPW_LOBBY_STATE_CLOSING;
        }
    } else {
        if (!sLobbyImpl) {
            return PPW_LOBBY_STATE_NOTINITIALIZED;
        }
    }

    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_STATE_ERROR;
    }

    switch (DWCi_LobbyProcess()) {
    case DWCi_LOBBY_STATE_NOTINITIALIZED:
        PPW_LobbyShutdownAsync();
        if (sLobbyImpl) {
            delete sLobbyImpl;
            sLobbyImpl = NULL;
        }
        return PPW_LOBBY_STATE_CLOSING;
    case DWCi_LOBBY_STATE_CONNECTING:
        break;
    case DWCi_LOBBY_STATE_CONNECTINGWAIT:
        break;
    case DWCi_LOBBY_STATE_CONNECTED:
        if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CONNECTING) {
            sLobbyImpl->SetState(PPW_LOBBY_STATE_CONNECTED);
        }
        break;
    case DWCi_LOBBY_STATE_CLOSING:
        break;
    case DWCi_LOBBY_STATE_ERROR:
        sLobbyImpl->SetDwcError(DWCi_LobbyGetLastError());
        break;
    default:
        break;
    }

    sLobbyImpl->Update();

    switch (sLobbyImpl->GetState()) {
    case PPW_LOBBY_STATE_NOTINITIALIZED:
        return PPW_LOBBY_STATE_CLOSING;
    case PPW_LOBBY_STATE_CONNECTING:
        break;
    case PPW_LOBBY_STATE_CONNECTED:
        sLobbyImpl->SetState(PPW_LOBBY_STATE_DOWNLOAD);
        break;
    case PPW_LOBBY_STATE_DOWNLOAD:
        if (sLobbyImpl->GetInnerInfo().IsQuestionnaireReceived()) {
            sLobbyImpl->SetState(PPW_LOBBY_STATE_DOWNLOAD_WAIT);
        }
        break;
    case PPW_LOBBY_STATE_DOWNLOAD_WAIT:
        DWCi_LobbyEnumChannelsAsync((PPW_LobbyMakeChannelName(PPW_LOBBY_CHANNEL_KIND_MAIN, "*")).c_str(), PPW_LobbyOnEnumChannels, NULL);
        sLobbyImpl->SetState(PPW_LOBBY_STATE_SEARCHINGCHANNEL);
        break;
    case PPW_LOBBY_STATE_SEARCHINGCHANNEL:
        break;
    case PPW_LOBBY_STATE_ENTERMAINCHANNEL: {
        PPW_LOBBY_RESULT v1 = PPW_LobbyEnterMainChannel();
        if (v1 != PPW_LOBBY_RESULT_SUCCESS) {
            sLobbyImpl->SetResultError(v1);
        } else {
            sLobbyImpl->SetState(PPW_LOBBY_STATE_PREPARINGMAINCHANNEL);
        }
    } break;
    case PPW_LOBBY_STATE_PREPARINGMAINCHANNEL:
        if (PPW_LobbyIsMainChannelReady()) {
            PPW_PlayerProfile &v2 = sLobbyImpl->GetPlayers().GetMyProfile();
            PPW_PlayerProfile::SystemData v3 = v2.TakeSystemData();
            v3.unk_0C = TRUE;
            v2.SetSystemData(v3);

            sLobbyImpl->SetState(PPW_LOBBY_STATE_READY);
            sLobbyImpl->GetCallbacks().lobbyJoinChannelCallback(TRUE, PPW_LOBBY_CHANNEL_KIND_MAIN);
        }
        break;
    case PPW_LOBBY_STATE_READY:
        break;
    case PPW_LOBBY_STATE_CLOSING:
        break;
    case PPW_LOBBY_STATE_ERROR:
        break;
    default:
        break;
    }

    return sLobbyImpl->GetState();
}

PPW_LOBBY_RESULT PPW_LobbyJoinSubChannelAsync(PPW_LOBBY_CHANNEL_KIND channelKind)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyImpl && sLobbyImpl->GetSubChannel().IsValid()) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    DWCi_LobbyChannelCallbacks v0;
    v0.lobbyPlayerConnectedCallback = PPW_LobbyOnPlayerConnected;
    v0.lobbyPlayerDisconnectedCallback = PPW_LobbyOnPlayerDisconnected;
    v0.lobbyChannelMessageReceivedCallback = PPW_LobbyOnChannelMessage;
    v0.lobbyBroadcastDataCallback = PPW_LobbyOnBroadcastData;
    v0.lobbyTopicChangedCallback = PPW_LobbyOnTopicChanged;
    v0.param = (void *)channelKind;

    PPWString v1 = PPW_LobbyMakeChannelName(channelKind, sLobbyImpl->GetChannelName());
    const DWCi_LobbyChannelMode *v2 = PPW_GetLobbyChannelMode(channelKind);
    PPW_LOBBY_RESULT v3 = PPW_LobbyApplyResult(DWCi_LobbyJoinChannelLimitAsync(v1.c_str(), NULL, v2->limit, &v0, PPW_LobbyOnEnterSubChannel, (void *)channelKind));
    if (v3 != PPW_LOBBY_RESULT_SUCCESS) {
        return v3;
    }
    sLobbyImpl->SetSubChannel(PPW_ChannelInfo(channelKind, v1));
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyLeaveSubChannel()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    if (!(sLobbyImpl && sLobbyImpl->GetSubChannel().IsValid())) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    PPW_LOBBY_RESULT unused = PPW_LobbyApplyResult(DWCi_LobbyLeaveChannel(sLobbyImpl->GetSubChannel().GetName().c_str()));

    sLobbyImpl->GetSubChannel().Reset();

    PPW_PlayerProfile &v0 = sLobbyImpl->GetPlayers().GetMyProfile();
    PPW_PlayerProfile::SystemData v1 = v0.TakeSystemData();
    v1.unk_00 = PPW_LOBBY_CHANNEL_KIND_INVALID;
    v0.SetSystemData(v1);

    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyGetTimeInfo(PPW_LobbyTimeInfo *timeInfo)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    sLobbyImpl->GetInnerInfo().GetTimeInfo(*timeInfo);

    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbySetSchedule(const PPW_LobbySchedule *schedule, u32 scheduleSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }

    return sLobbyImpl->GetInnerInfo().SetSchedule((u8 *)schedule, scheduleSize) ? PPW_LOBBY_RESULT_SUCCESS : PPW_LOBBY_RESULT_ERROR_PARAM;
}

PPW_LOBBY_RESULT PPW_LobbyGetSchedule(PPW_LobbySchedule *schedule, u32 *scheduleSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return sLobbyImpl->GetInnerInfo().GetSchedule(schedule, *scheduleSize) ? PPW_LOBBY_RESULT_SUCCESS : PPW_LOBBY_RESULT_ERROR_PARAM;
}

PPW_LOBBY_CHANNEL_STATE PPW_LobbyGetSubChannelState()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }

    if (!sLobbyImpl->GetSubChannel().IsValid()) {
        return PPW_LOBBY_CHANNEL_STATE_NONE;
    }

    BOOL v0 = DWCi_LobbyInChannel(sLobbyImpl->GetSubChannel().GetName().c_str());
    return v0 ? PPW_LOBBY_CHANNEL_STATE_AVAILABLE : PPW_LOBBY_CHANNEL_STATE_UNAVAILABLE;
}

PPW_LOBBY_RESULT PPW_LobbySetChannelData(s32 userId, PPW_LOBBY_CHANNEL_KIND channelKind, const char *key, const u8 *data, u32 dataSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return PPW_LobbySetChannelDataImpl(userId, channelKind, key, data, dataSize);
}

PPW_LOBBY_RESULT PPW_LobbyGetChannelDataAsync(s32 userId, PPW_LOBBY_CHANNEL_KIND channelKind, const char *key, void *param)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    PPWString v0 = sLobbyImpl->GetChannelPair().GetName(channelKind);
    if (v0 == "") {
        return PPW_LOBBY_RESULT_ERROR_CHANNEL;
    }

    return PPW_LobbyApplyResult(DWCi_LobbyGetChannelDataAsync(v0.c_str(), userId, key, PPW_LobbyOnChannelData, param));
}

PPW_LOBBY_RESULT PPW_LobbySendChannelStringMessage(PPW_LOBBY_CHANNEL_KIND channelKind, s32 type, const char *message)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return PPW_LobbySendMessage(PPW_LOBBY_INVALID_USER_ID, channelKind, 0, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER, type, (u8 *)message, strlen(message) + 1);
}

PPW_LOBBY_RESULT PPW_LobbySendPlayerStringMessage(s32 userId, s32 type, const char *message)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return PPW_LobbySendMessage(userId, PPW_LOBBY_CHANNEL_KIND_INVALID, 0, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER, type, (u8 *)message, strlen(message) + 1);
}

PPW_LOBBY_RESULT PPW_LobbySendChannelBinaryMessage(PPW_LOBBY_CHANNEL_KIND channelKind, s32 type, const u8 *data, u32 dataSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return PPW_LobbySendMessage(PPW_LOBBY_INVALID_USER_ID, channelKind, 1, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER, type, data, dataSize);
}

PPW_LOBBY_RESULT PPW_LobbySendPlayerBinaryMessage(s32 userId, s32 type, const u8 *data, u32 dataSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    return PPW_LobbySendMessage(userId, PPW_LOBBY_CHANNEL_KIND_INVALID, 1, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER, type, data, dataSize);
}

s32 PPW_LobbyGetMyUserId()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_INVALID_USER_ID;
    }
    return sLobbyImpl->GetPid();
}

PPW_LOBBY_RESULT PPW_LobbyEnumUserId(s32 *userIds, u32 *num)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    u32 v0 = *num;

    std::vector<s32, PPW_Allocator<s32> > v1 = sLobbyImpl->GetPlayers().GetConnectedPids();
    *num = v1.size();
    if (*num == 0) {
        return PPW_LOBBY_RESULT_SUCCESS;
    }

    if (v0 < *num || userIds == NULL) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    MI_CpuCopy8(PPW_GetVectorData(v1), userIds, v1.size() * sizeof(v1[0]));
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyGetProfile(s32 userId, u8 *userProfile, u32 *userProfileSize)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    if (userId == PPW_LOBBY_INVALID_USER_ID) {
        userId = sLobbyImpl->GetPid();
    }

    PPW_PlayerProfile *v0 = sLobbyImpl->GetPlayers().FindPlayer(userId);
    if (!v0) {
        return PPW_LOBBY_RESULT_ERROR_NODATA;
    }

    return v0->GetUserData(userProfile, userProfileSize) ? PPW_LOBBY_RESULT_SUCCESS : PPW_LOBBY_RESULT_ERROR_PARAM;
}

PPW_LOBBY_RESULT PPW_LobbyUpdateMyProfile(const u8 *userProfile, u32 userProfileSize, BOOL force)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    PPW_PlayerProfile &v0 = sLobbyImpl->GetPlayers().GetMyProfile();

    v0.SetUserData(userProfile, userProfileSize, force);

    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyStartRecruit(PPW_LobbyRecruitInfo *recruitInfo)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    PPWString v0;
    if (!sLobbyImpl->StartRecruit(*recruitInfo, v0)) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    strncpy(recruitInfo->matchMakingString, v0.c_str(), PPW_LOBBY_MAX_MATCHMAKING_STRING_LENGTH - 1);

    sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_RECRUIT, PPW_LOBBY_TIMER_INTERVAL_RECRUIT, PPW_LobbySendRecruit, NULL, TRUE);

    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyUpdateRecruitInfo(const PPW_LobbyRecruitInfo *recruitInfo)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    if (!sLobbyImpl->UpdateRecruitInfo(*recruitInfo)) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbyStopRecruit()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    if (!sLobbyImpl->StopRecruit()) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    PPW_LobbySendMessage(sLobbyImpl->GetPid(), PPW_LOBBY_CHANNEL_KIND_MAIN, 1, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM, 2, (u8 *)&sLobbyImpl->GetRecruitInfo(), sizeof(PPW_LobbyRecruitInfo));

    sLobbyImpl->GetTimers().Remove(PPW_LOBBY_TIMER_ID_RECRUIT);
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_RESULT PPW_LobbySubmitQuestionnaire(s32 answerNo)
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (sLobbyImpl && sLobbyImpl->GetState() == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (answerNo < 0 || answerNo > 2) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    PPW_LobbyQuestionnaire v0;
    if (!sLobbyImpl->GetInnerInfo().GetQuestionnaire(&v0) || sLobbyImpl->IsSubmittingQuestionnaire()) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }

    const PPW_PlayerProfile::UserData &v1 = sLobbyImpl->GetPlayers().GetMyProfile().GetUserDataStore();
    const WiFiPlazaProfile *v2 = (const WiFiPlazaProfile *)PPW_GetVectorData(v1.unk_00);

    struct QuestionnaireSubmitRequest {
        EncCommonRequest unk_00;
        s32 unk_14;
        s32 unk_18;
        s32 unk_1C;
        u32 unk_20;
        s32 unk_24;
        u16 unk_28;
        u16 unk_2A;
    } v3 = {
        EncCommonRequest(),
        v0.currentQuestionnaireRecord.questionSerialNo,
        v0.currentQuestionnaireRecord.questionNo,
        answerNo,
        v2->trainerID,
        v2->trainerGender,
        v2->country,
        v2->region
    };

    PPW_EncSession::Create(sLobbyImpl->GetServerKind(), sEncInitData, sEncSubmitQuestionnairePath, sLobbyImpl->GetPid(), (u8 *)&v3, sizeof(v3), 3, PPW_LobbyOnSubmitQuestionnaire, NULL);

    sLobbyImpl->SetSubmittingQuestionnaire(TRUE);
    return PPW_LOBBY_RESULT_SUCCESS;
}

PPW_LOBBY_ERROR PPW_LobbyGetLastError()
{
    if (!sLobbyImpl) {
        return PPW_LOBBY_ERROR_NONE;
    }

    return sLobbyImpl->GetError();
}

s32 PPW_LobbyToErrorCode(PPW_LOBBY_ERROR err)
{
    if (err >= DWCi_LOBBY_ERROR_MAX) {
        return err + PPW_LOBBY_ERROR_CODE_BASE;
    } else {
        return DWCi_LobbyToErrorCode((DWCi_LOBBY_ERROR)err);
    }
}

PPW_LOBBY_ERROR PPW_LobbyResultToError(PPW_LOBBY_RESULT param0)
{
    switch (param0) {
    case PPW_LOBBY_RESULT_SUCCESS:
        return PPW_LOBBY_ERROR_NONE;
    case PPW_LOBBY_RESULT_ERROR_ALLOC:
        return PPW_LOBBY_ERROR_ALLOC;
    case PPW_LOBBY_RESULT_ERROR_SESSION:
        return PPW_LOBBY_ERROR_SESSION;
    default:
        return PPW_LOBBY_ERROR_UNKNOWN;
    }
}

BOOL PPW_IsConnectedUserId(const DWCFriendsMatchControl *dwcFriendMatchCtrl, s32 userId)
{
    if (!sLobbyImpl) {
        return FALSE;
    }

    int v0 = DWC_GetNumConnectionHost();
    if (v0 == 0 || !dwcFriendMatchCtrl) {
        return FALSE;
    }

    if (userId == sLobbyImpl->GetPid()) {
        return TRUE;
    }

    const int *v1 = dwcFriendMatchCtrl->matchcnt.sbPidList;
    const int *v2 = std::find(v1, v1 + v0, userId);

    return v2 != v1 + v0;
}

void PPW_LobbySetEncInitData(const char *initData)
{
    sEncInitData = initData;
}

PPW_LOBBY_RESULT PPW_LobbySendMessage(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, int param2, PPW_MessageParser::MessageKind param3, s32 param4, const u8 *param5, u32 param6)
{
    if (param0 == PPW_LOBBY_INVALID_USER_ID && param1 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    PPWString v0;
    if (!PPW_MessageParser::Build(param2, param3, param4, (const char *)param5, param6, v0)) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    if (param1 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return PPW_LobbyApplyResult(DWCi_LobbySendUserMessage(param0, v0.c_str()));
    } else {
        PPWString v1 = sLobbyImpl->GetChannelPair().GetName(param1);
        if (v1 == "") {
            return PPW_LOBBY_RESULT_ERROR_CHANNEL;
        }
        return PPW_LobbyApplyResult(DWCi_LobbySendChannelMessage(v1.c_str(), v0.c_str()));
    }
}

PPW_LOBBY_RESULT PPW_LobbySetChannelDataImpl(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, const char *param2, const u8 *param3, u32 param4)
{
    PPWString v0 = sLobbyImpl->GetChannelPair().GetName(param1);
    if (v0 == "") {
        return PPW_LOBBY_RESULT_ERROR_CHANNEL;
    }

    if (param4 > PPW_LOBBY_MAX_BINARY_SIZE) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }

    std::vector<char, PPW_Allocator<char> > v1((((param4 + 2) / 3) << 2) + 1);
    int v2 = DWC_Base64Encode((char *)param3, param4, PPW_GetVectorData(v1), v1.size());

    v1[(std::size_t)v2] = '\0';

    return PPW_LobbyApplyResult(DWCi_LobbySetChannelData(v0.c_str(), param0, param2, PPW_GetVectorData(v1)));
}

static void PPW_LobbyRequestCheckProfile()
{
    const PPW_PlayerProfile::UserData &v0 = sLobbyImpl->GetPlayers().GetMyProfile().GetUserDataStore();
    const WiFiPlazaProfile *v1 = (const WiFiPlazaProfile *)PPW_GetVectorData(v0.unk_00);

    struct CheckProfileRequest {
        EncCommonRequest unk_00;
        WiFiPlazaProfile unk_14;
    } v2;
    v2.unk_14 = *v1;

    PPW_EncSession::Create(sLobbyImpl->GetServerKind(), sEncInitData, sEncCheckProfilePath, sLobbyImpl->GetPid(), (u8 *)&v2, sizeof(v2), 3, PPW_LobbyOnCheckProfile, NULL);
}

static PPWString PPW_LobbyMakeChannelName(PPW_LOBBY_CHANNEL_KIND param0, const PPWString &param1)
{
    return PPWString(PPW_LOBBY_CHANNEL_PREFIX_NAMES[param0]) + DWCi_LOBBY_CHANNEL_NAME_SEPARATOR + param1;
}

static PPWString PPW_LobbyMakeNewChannelName()
{
    return PPW_FormatStringAlloc<PPWString>("C%d_%u", sLobbyImpl->GetPid(), (u32)current_time() % 1000);
}

static PPW_LOBBY_RESULT PPW_LobbyEnterMainChannel()
{
    DWCi_LobbyChannelCallbacks v0;
    v0.lobbyPlayerConnectedCallback = PPW_LobbyOnPlayerConnected;
    v0.lobbyPlayerDisconnectedCallback = PPW_LobbyOnPlayerDisconnected;
    v0.lobbyChannelMessageReceivedCallback = PPW_LobbyOnChannelMessage;
    v0.lobbyBroadcastDataCallback = PPW_LobbyOnBroadcastData;
    v0.lobbyTopicChangedCallback = PPW_LobbyOnTopicChanged;
    v0.param = (void *)PPW_LOBBY_CHANNEL_KIND_MAIN;

    PPWString v1 = PPW_LobbyMakeChannelName(PPW_LOBBY_CHANNEL_KIND_MAIN, sLobbyImpl->GetChannelName());
    PPW_LOBBY_RESULT v2 = PPW_LobbyApplyResult(DWCi_LobbyJoinChannelLimitAsync(v1.c_str(), NULL, PPW_LOBBY_MAX_PLAYER_NUM_MAIN, &v0, PPW_LobbyOnEnterMainChannel, (void *)PPW_LOBBY_CHANNEL_KIND_MAIN));
    if (v2 != PPW_LOBBY_RESULT_SUCCESS) {
        return v2;
    }

    sLobbyImpl->SetMainChannel(PPW_ChannelInfo(PPW_LOBBY_CHANNEL_KIND_MAIN, v1));
    return v2;
}

static void PPW_LobbyHandleChannelData(BOOL param0, BOOL param1, const char *param2, s32 param3, const char *param4, const char *param5, void *param6)
{
    PPW_LOBBY_CHANNEL_KIND v0 = sLobbyImpl->GetChannelPair().FindKind(param2);
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    std::vector<u8, PPW_Allocator<u8> > v1;
    if (!PPW_Base64DecodeToVector(param5, v1)) {
        return;
    }

    if (v1.empty()) {
        return;
    }

    if (PPW_LobbyHandleChannelKey(param0, param1, v0, param3, param4, PPW_GetVectorData(v1), v1.size(), param6)) {
        return;
    }

    if (param3 != PPW_LOBBY_INVALID_USER_ID && !sLobbyImpl->GetPlayers().IsPlayerComplete(param3)) {
        return;
    }

    sLobbyImpl->GetCallbacks().lobbyGetChannelDataCallback(param0, param1, v0, param3, param4, PPW_GetVectorData(v1), v1.size(), param6);
}

static BOOL PPW_LobbyHandleChannelKey(BOOL param0, BOOL param1, PPW_LOBBY_CHANNEL_KIND param2, s32 param3, const char *param4, const u8 *param5, u32 param6, void *param7)
{
    if (param2 != PPW_LOBBY_CHANNEL_KIND_MAIN) {
        return FALSE;
    }

    if (strcmp(param4, PPW_LOBBY_CHANNEL_KEY_USER) == 0) {
        if (param3 == sLobbyImpl->GetPid()) {
            return TRUE;
        }

        PPW_PlayerProfile *v0 = sLobbyImpl->GetPlayers().FindPlayer(param3);
        if (!v0) {
            return TRUE;
        }

        v0->SetUserData(param5, (u32)param6);

        if (v0->IsUpdated()) {
            sLobbyImpl->GetCallbacks().lobbyUserProfileUpdatedCallback(param3, param5, param6);
        }

        return TRUE;
    } else if (strcmp(param4, PPW_LOBBY_CHANNEL_KEY_SYSTEM) == 0) {
        if (param3 == sLobbyImpl->GetPid()) {
            return TRUE;
        }

        if (param6 != sizeof(PPW_PlayerProfile::SystemData)) {
            return TRUE;
        }

        PPW_PlayerProfile *v1 = sLobbyImpl->GetPlayers().FindPlayer(param3);
        if (!v1) {
            return TRUE;
        }
        v1->SetSystemData(*(PPW_PlayerProfile::SystemData *)param5);

        if (v1->IsUpdated() && v1->IsSystemDataDirty()) {
            const PPW_PlayerProfile::SystemData &v2 = v1->TakeSystemData();
            PPW_LobbySystemProfile v3 = v2.ToSystemProfile();
            sLobbyImpl->GetCallbacks().lobbySystemProfileUpdatedCallback(param3, &v3);
        }

        return TRUE;
    } else if (strcmp(param4, PPW_LOBBY_CHANNEL_KEY_CHANNEL_TIME) == 0) {
        if (param6 != sizeof(PPW_LobbyInnerInfo::OpenedTime)) {
            return TRUE;
        }
        PPW_LobbyInnerInfo::OpenedTime *v4 = (PPW_LobbyInnerInfo::OpenedTime *)param5;

        sLobbyImpl->GetInnerInfo().SetOpenedTime(*v4);
        return TRUE;
    } else if (strcmp(param4, PPW_LOBBY_CHANNEL_KEY_CHANNEL_LOBBY) == 0) {
        if (!sLobbyImpl->GetInnerInfo().SetSchedule(param5, param6)) {
            return TRUE;
        }
        sLobbyImpl->GetInnerInfo().SetScheduleReceived();
        return TRUE;
    }

    return FALSE;
}

static BOOL PPW_LobbyHandleSystemMessage(const PPW_MessageParser::ParsedMessage &param0, s32 param1, PPW_LOBBY_CHANNEL_KIND param2, u8 *param3, u32 param4)
{
    if (param2 != PPW_LOBBY_CHANNEL_KIND_MAIN) {
        return TRUE;
    }

    switch (param0.unk_10) {
    case 1:
        if (sLobbyImpl->GetPid() == param1) {
            break;
        }

        if (!sLobbyImpl->GetPlayers().IsPlayerComplete(param1)) {
            break;
        }

        if (param0.unk_08 == 1 && param4 == sizeof(PPW_LobbyRecruitInfo)) {
            sLobbyImpl->GetCallbacks().lobbyRecruitCallback(param1, (PPW_LobbyRecruitInfo *)param3);
        }
        break;
    case 2:
        if (sLobbyImpl->GetPid() == param1) {
            break;
        }

        if (!sLobbyImpl->GetPlayers().IsPlayerComplete(param1)) {
            break;
        }

        if (param0.unk_08 == 1 && param4 == sizeof(PPW_LobbyRecruitInfo)) {
            sLobbyImpl->GetCallbacks().lobbyRecruitStoppedCallback(param1, (PPW_LobbyRecruitInfo *)param3);
        }

        break;
    case 0:
        if (param0.unk_08 == 1 && param4 == sizeof(PPW_LobbyEmptyMessage)) {
            sLobbyImpl->GetInnerInfo().ProgressSchedule();
        }

        break;
    default:
        break;
    }
    return TRUE;
}

static BOOL PPW_LobbyIsMainChannelReady()
{
    if (!DWCi_LobbyInChannel(sLobbyImpl->GetMainChannel().GetName().c_str())) {
        return FALSE;
    }

    if (!sLobbyImpl->GetMainChannel().IsEntered()) {
        return FALSE;
    }

    if (!sLobbyImpl->GetMainChannel().IsModeChecked()) {
        return FALSE;
    }

    if (!sLobbyImpl->GetInnerInfo().IsOpenedTimeSet()) {
        return FALSE;
    }

    if (!sLobbyImpl->GetInnerInfo().IsScheduleReceived()) {
        return FALSE;
    }

    if (!sLobbyImpl->GetPlayers().AllPlayersComplete()) {
        return FALSE;
    }
    return TRUE;
}

static BOOL PPW_LobbySendUserData(void *param0)
{
    PPW_PlayerProfile &v0 = sLobbyImpl->GetPlayers().GetMyProfile();

    if (!v0.IsUserDataDirty()) {
        return TRUE;
    }

    const PPW_PlayerProfile::UserData &v1 = v0.TakeUserData();

    PPW_LobbySetChannelDataImpl(sLobbyImpl->GetPid(), PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_CHANNEL_KEY_USER, (u8 *)PPW_GetVectorData(v1.unk_00), v1.unk_00.size());

    return TRUE;
}

static BOOL PPW_LobbySendSystemData(void *param0)
{
    PPW_PlayerProfile &v0 = sLobbyImpl->GetPlayers().GetMyProfile();

    if (!v0.IsSystemDataDirty()) {
        return TRUE;
    }

    const PPW_PlayerProfile::SystemData &v1 = v0.TakeSystemData();

    PPW_LobbySetChannelDataImpl(sLobbyImpl->GetPid(), PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_CHANNEL_KEY_SYSTEM, (u8 *)&v1, sizeof(v1));

    return TRUE;
}

static BOOL PPW_LobbySendRecruit(void *param0)
{
    if (!sLobbyImpl->IsRecruiting()) {
        return FALSE;
    }

    PPW_LobbySendMessage(sLobbyImpl->GetPid(), PPW_LOBBY_CHANNEL_KIND_MAIN, 1, PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM, 1, (u8 *)&sLobbyImpl->GetRecruitInfo(), sizeof(PPW_LobbyRecruitInfo));

    return TRUE;
}

static BOOL PPW_LobbyRequestChannelMode(void *param0)
{
    DWCi_LobbyGetChannelModeAsync(sLobbyImpl->GetMainChannel().GetName().c_str(), PPW_LobbyOnChannelMode, NULL);

    return TRUE;
}

static BOOL PPW_LobbyRequestChannelTime(void *param0)
{
    if (sLobbyImpl->GetInnerInfo().IsOpenedTimeSet()) {
        return FALSE;
    }

    DWCi_LobbyGetChannelDataAsync(sLobbyImpl->GetMainChannel().GetName().c_str(), PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KEY_CHANNEL_TIME, PPW_LobbyOnChannelTime, NULL);

    return TRUE;
}

static BOOL PPW_LobbyRequestChannelLobby(void *param0)
{
    if (sLobbyImpl->GetInnerInfo().IsScheduleReceived()) {
        return FALSE;
    }

    DWCi_LobbyGetChannelDataAsync(sLobbyImpl->GetMainChannel().GetName().c_str(), PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KEY_CHANNEL_LOBBY, PPW_LobbyOnChannelLobby, NULL);

    return TRUE;
}

static PPW_LOBBY_STATS_RESULT PPW_LobbyStatsResultFromCode(u32 param0)
{
    switch (param0) {
    case ENC_SERVER_RESPONSE_CODE_OK:
        return PPW_LOBBY_STATS_RESULT_SUCCESS;
    case ENC_SERVER_RESPONSE_CODE_INVALID_PARAM:
        return PPW_LOBBY_STATS_RESULT_INVALID_PARAM;
    case ENC_SERVER_RESPONSE_CODE_INTERNAL_ERROR:
    case ENC_SERVER_RESPONSE_CODE_DATABASE_ERROR:
    case ENC_SERVER_RESPONSE_CODE_MAINTENANCE:
    case ENC_SERVER_RESPONSE_CODE_UNKNOWN_ERROR:
        return PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    default:
        return PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }
}

static PPW_LOBBY_STATS_RESULT PPW_LobbyParseStatsResponse(BOOL param0, const u8 *param1, u32 param2, const u8 **param3, u32 *param4)
{
    PPW_LOBBY_STATS_RESULT v0 = PPW_LOBBY_STATS_RESULT_SUCCESS;
    *param3 = NULL;
    *param4 = 0;

    if (!param0) {
        return PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }

    if (param2 < sizeof(u32)) {
        return PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }

    u32 v1 = (u32)*param1;
    v0 = PPW_LobbyStatsResultFromCode(v1);
    if (v0 == PPW_LOBBY_STATS_RESULT_SERVER_ERROR) {
        return v0;
    } else if (v0 == PPW_LOBBY_STATS_RESULT_INVALID_PARAM) {
        return v0;
    }

    *param3 = param1 + sizeof(u32);
    *param4 = param2 - sizeof(u32);

    return v0;
}

static void PPW_LobbyOnCheckProfile(BOOL param0, const u8 *param1, u32 param2, void *param3)
{
    if (!sLobbyImpl) {
        return;
    }
    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return;
    }

    const u8 *v0 = NULL;
    u32 v1 = 0;
    PPW_LOBBY_STATS_RESULT v2 = PPW_LobbyParseStatsResponse(param0, param1, param2, &v0, &v1);

    if (v2 == PPW_LOBBY_STATS_RESULT_SUCCESS && v1 != sizeof(WiFiPlazaProfile)) {
        v2 = PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }

    if (v2 == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        PPW_LobbyUpdateMyProfile(v0, v1, FALSE);
    }

    sLobbyImpl->GetCallbacks().lobbyCheckProfileCallback(v2, v0, v1);

    if (v2 != PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sLobbyImpl->SetError(PPW_LOBBY_ERROR_STATS_CHECKPROFILE);
        return;
    }

    EncCommonRequest v3;
    PPW_EncSession::Create(sLobbyImpl->GetServerKind(), sEncInitData, sEncGetSchedulePath, sLobbyImpl->GetPid(), (u8 *)&v3, sizeof(v3), 3, PPW_LobbyOnSchedule, NULL, TRUE);
}

static void PPW_LobbyOnSchedule(BOOL param0, const u8 *param1, u32 param2, void *param3)
{
    if (!sLobbyImpl) {
        return;
    }
    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return;
    }

    const u8 *v0 = NULL;
    u32 v1 = 0;
    PPW_LOBBY_STATS_RESULT v2 = PPW_LobbyParseStatsResponse(param0, param1, param2, &v0, &v1);

    if (v2 == PPW_LOBBY_STATS_RESULT_SUCCESS) {
        if (!sLobbyImpl->GetInnerInfo().ValidateSchedule(v0, v1)) {
            v2 = PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
        }
    }

    BOOL v3 = sLobbyImpl->GetCallbacks().lobbyNotifyScheduleCallback(v2, (PPW_LobbySchedule *)v0);

    if (v2 != PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sLobbyImpl->SetError(PPW_LOBBY_ERROR_STATS_SCHEDULE);
        return;
    }

    if (v3) {
        sLobbyImpl->GetInnerInfo().SetSchedule(v0, v1);
    }

    const PPW_PlayerProfile::UserData &v4 = sLobbyImpl->GetPlayers().GetMyProfile().GetUserDataStore();
    const WiFiPlazaProfile *v5 = (const WiFiPlazaProfile *)PPW_GetVectorData(v4.unk_00);

    struct GetVipRequest {
        EncCommonRequest unk_00;
        u32 unk_14;
    } v6 = {
        EncCommonRequest(),
        v5->trainerID
    };
    ;

    PPW_EncSession::Create(sLobbyImpl->GetServerKind(), sEncInitData, sEncGetVipPath, sLobbyImpl->GetPid(), (u8 *)&v6, sizeof(v6), 3, PPW_LobbyOnVip, NULL, TRUE);
}

static void PPW_LobbyOnVip(BOOL param0, const u8 *param1, u32 param2, void *param3)
{
    if (!sLobbyImpl) {
        return;
    }
    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return;
    }

    const u8 *v0 = NULL;
    u32 v1 = 0;
    PPW_LOBBY_STATS_RESULT v2 = PPW_LobbyParseStatsResponse(param0, param1, param2, &v0, &v1);

    if (!sLobbyImpl->GetInnerInfo().ValidateVip(v0, v1)) {
        v2 = PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }

    if (v2 != PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sLobbyImpl->SetError(PPW_LOBBY_ERROR_STATS_VIP);
        return;
    }

    sLobbyImpl->GetInnerInfo().SetVip(v0, v1);

    sLobbyImpl->GetCallbacks().lobbyGetVipCallback(v2, (PPW_LobbyVipRecord *)v0, v1 / sizeof(PPW_LobbyVipRecord));

    EncCommonRequest v3;
    PPW_EncSession::Create(sLobbyImpl->GetServerKind(), sEncInitData, sEncGetQuestionnairePath, sLobbyImpl->GetPid(), (u8 *)&v3, sizeof(v3), 3, PPW_LobbyOnQuestionnaire, NULL, TRUE);
}

static void PPW_LobbyOnQuestionnaire(BOOL param0, const u8 *param1, u32 param2, void *param3)
{
    if (!sLobbyImpl) {
        return;
    }
    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return;
    }

    const u8 *v0 = NULL;
    u32 v1 = 0;
    PPW_LOBBY_STATS_RESULT v2 = PPW_LobbyParseStatsResponse(param0, param1, param2, &v0, &v1);

    if (v1 != sizeof(PPW_LobbyQuestionnaire)) {
        v2 = PPW_LOBBY_STATS_RESULT_SERVER_ERROR;
    }

    if (v2 != PPW_LOBBY_STATS_RESULT_SUCCESS) {
        sLobbyImpl->SetError(PPW_LOBBY_ERROR_STATS_QUESTIONNAIRE);
        return;
    }

    sLobbyImpl->GetInnerInfo().SetQuestionnaire((PPW_LobbyQuestionnaire *)v0);

    sLobbyImpl->GetCallbacks().lobbyGetQuestionnaireCallback(v2, (PPW_LobbyQuestionnaire *)v0);

    sLobbyImpl->GetInnerInfo().SetQuestionnaireReceived();
}

static void PPW_LobbyOnSubmitQuestionnaire(BOOL param0, const u8 *param1, u32 param2, void *param3)
{
    if (!sLobbyImpl) {
        return;
    }
    if (sLobbyImpl->GetState() == PPW_LOBBY_STATE_CLOSING) {
        return;
    }

    sLobbyImpl->SetSubmittingQuestionnaire(FALSE);
    sLobbyImpl->GetCallbacks().lobbySubmitQuestionnaireCallback(param0 ? PPW_LOBBY_STATS_RESULT_SUCCESS : PPW_LOBBY_STATS_RESULT_SERVER_ERROR);
}

static void PPW_LobbyOnEnterMainChannel(BOOL param0, DWCi_LOBBY_ENTER_RESULT param1, const char *param2, void *param3)
{
    PPW_LOBBY_CHANNEL_KIND v0 = (PPW_LOBBY_CHANNEL_KIND)(u32)param3;
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    if (param0) {
        sLobbyImpl->ResetRetry();

        sLobbyImpl->GetPlayers().GetMyProfile().SetSystemData(PPW_PlayerProfile::SystemData());

        DWCi_LobbyEnumUsersAsync(param2, PPW_LobbyOnEnumUsers, (void *)v0);

        sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_SYSTEM_CHANNEL_DATA, PPW_LOBBY_TIMER_INTERVAL_SYSTEM_CHANNEL_DATA, PPW_LobbySendSystemData, NULL, TRUE);
        sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_USER_CHANNEL_DATA, PPW_LOBBY_TIMER_INTERVAL_USER_CHANNEL_DATA, PPW_LobbySendUserData, NULL, TRUE);

        sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_SYSTEMDATA, PPW_LOBBY_TIMER_INTERVAL_CHECK_MAINCHANNEL_SYSTEMDATA, PPW_LobbyRequestChannelTime, NULL, TRUE);

        sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_MODE, PPW_LOBBY_TIMER_INTERVAL_CHECK_MAINCHANNEL_MODE, PPW_LobbyRequestChannelMode, NULL, TRUE);

        sLobbyImpl->GetTimers().Add(PPW_LOBBY_TIMER_ID_CHECK_LOBBY_INFO, PPW_LOBBY_TIMER_INTERVAL_CHECK_LOBBY_INFO, PPW_LobbyRequestChannelLobby, NULL, TRUE);

        const PPW_PlayerProfile &v1 = sLobbyImpl->GetPlayers().GetMyProfile();
        const PPW_PlayerProfile::SystemData &v2 = v1.GetSystemData();
        const PPW_PlayerProfile::UserData &v3 = v1.GetUserDataStore();
        PPW_LobbySystemProfile v4 = v2.ToSystemProfile();
        sLobbyImpl->GetCallbacks().lobbyPlayerConnectedCallback(v1.GetPid(), &v4, PPW_GetVectorData(v3.unk_00), v3.unk_00.size());
    } else {
        sLobbyImpl->GetMainChannel().Reset();

        if (sLobbyImpl->TryIncrementRetry()) {
            sLobbyImpl->SetState(PPW_LOBBY_STATE_DOWNLOAD_WAIT);
        } else {
            sLobbyImpl->SetError(PPW_LOBBY_ERROR_SESSION);
        }
    }
}

static void PPW_LobbyOnEnterSubChannel(BOOL param0, DWCi_LOBBY_ENTER_RESULT param1, const char *param2, void *param3)
{
    PPW_LOBBY_CHANNEL_KIND v0 = (PPW_LOBBY_CHANNEL_KIND)(u32)param3;
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    if (param0) {
        const DWCi_LobbyChannelMode *v1 = PPW_GetLobbyChannelMode(v0);
        if (!v1) {
            sLobbyImpl->SetError(PPW_LOBBY_ERROR_UNKNOWN);
        }
        DWCi_LobbySetChannelMode(param2, v1);

        PPW_PlayerProfile &v2 = sLobbyImpl->GetPlayers().GetMyProfile();
        PPW_PlayerProfile::SystemData v3 = v2.TakeSystemData();
        v3.unk_00 = v0;
        v2.SetSystemData(v3);
    } else {
        sLobbyImpl->GetSubChannel().Reset();
    }

    sLobbyImpl->GetCallbacks().lobbyJoinChannelCallback(param0, (PPW_LOBBY_CHANNEL_KIND)(u32)param3);
}

static void PPW_LobbyOnPlayerConnected(const char *param0, s32 param1, void *param2)
{
    PPW_LOBBY_CHANNEL_KIND v0 = sLobbyImpl->GetChannelPair().FindKind(param0);
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    if (v0 == PPW_LOBBY_CHANNEL_KIND_MAIN) {
        sLobbyImpl->GetPlayers().AddPlayer(param1);
    } else {
        PPW_PlayerProfile *v1 = sLobbyImpl->GetPlayers().FindPlayer(param1);
        if (!v1) {
            sLobbyImpl->GetPlayers().AddPlayer(param1);
            v1 = sLobbyImpl->GetPlayers().FindPlayer(param1);
        }
        PPW_PlayerProfile::SystemData v2 = v1->TakeSystemData();
        v2.unk_00 = v0;
        v1->SetSystemData(v2);

        const PPW_PlayerProfile::SystemData &v3 = v1->TakeSystemData();
        PPW_LobbySystemProfile v4 = v3.ToSystemProfile();

        if (v1->IsUpdated()) {
            sLobbyImpl->GetCallbacks().lobbySystemProfileUpdatedCallback(param1, &v4);
        }
    }
}

static void PPW_LobbyOnPlayerDisconnected(const char *param0, s32 param1, void *param2)
{
    PPW_LOBBY_CHANNEL_KIND v0 = sLobbyImpl->GetChannelPair().FindKind(param0);
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    if (v0 == PPW_LOBBY_CHANNEL_KIND_MAIN) {
        PPW_PlayerProfile *v1 = sLobbyImpl->GetPlayers().FindPlayer(param1);
        if (!v1 || !v1->IsUpdated()) {
            return;
        }

        sLobbyImpl->GetCallbacks().lobbyPlayerDisconnectedCallback(param1);
        sLobbyImpl->GetPlayers().RemovePlayer(param1);
    } else {
        PPW_PlayerProfile *v1 = sLobbyImpl->GetPlayers().FindPlayer(param1);
        if (!v1) {
            return;
        }

        PPW_PlayerProfile::SystemData v2 = v1->TakeSystemData();
        v2.unk_00 = PPW_LOBBY_CHANNEL_KIND_INVALID;
        v1->SetSystemData(v2);

        const PPW_PlayerProfile::SystemData &v3 = v1->TakeSystemData();
        PPW_LobbySystemProfile v4 = v3.ToSystemProfile();

        if (v1->IsUpdated()) {
            sLobbyImpl->GetCallbacks().lobbySystemProfileUpdatedCallback(param1, &v4);
        }
    }
}

static void PPW_LobbyOnUserMessage(s32 param0, const char *param1, void *param2)
{
    PPW_LobbyOnChannelMessage(NULL, param0, param1, param2);
}

static void PPW_LobbyOnChannelMessage(const char *param0, s32 param1, const char *param2, void *param3)
{
    PPW_LOBBY_CHANNEL_KIND v0 = PPW_LOBBY_CHANNEL_KIND_INVALID;
    if (param0) {
        v0 = sLobbyImpl->GetChannelPair().FindKind(param0);
    }

    if (param0 != NULL && v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    PPW_MessageParser::ParsedMessage v1;
    if (!PPW_MessageParser::Parse(param2, v1)) {
        return;
    }

    switch (v1.unk_0C) {
    case PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_USER:
        if (!sLobbyImpl->GetPlayers().IsPlayerComplete(param1)) {
            return;
        }

        switch (v1.unk_08) {
        case 1:
            sLobbyImpl->GetCallbacks().lobbyBinaryMessageReceivedCallback(param1, v0, v1.unk_10, (u8 *)PPW_GetVectorData(v1.unk_18), v1.unk_18.size());
            break;
        case 0:
            sLobbyImpl->GetCallbacks().lobbyStringMessageReceivedCallback(param1, v0, v1.unk_10, (char *)PPW_GetVectorData(v1.unk_18));
            break;
        default:
            break;
        }

        break;
    case PPW_MessageParser::PPW_LOBBY_MESSAGE_KIND_SYSTEM:
        PPW_LobbyHandleSystemMessage(v1, param1, v0, (u8 *)PPW_GetVectorData(v1.unk_18), v1.unk_18.size());
        break;
    default:
        break;
    }
}

static void PPW_LobbyOnExcessFlood(u32 param0, void *param1)
{
    sLobbyImpl->GetCallbacks().lobbyExcessFloodCallback(param0);
}

static void PPW_LobbyOnBroadcastData(const char *param0, s32 param1, const char *param2, const char *param3, void *param4)
{
    PPW_LobbyHandleChannelData(TRUE, TRUE, param0, param1, param2, param3, NULL);
}

static void PPW_LobbyOnChannelData(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5)
{
    PPW_LobbyHandleChannelData(param0, FALSE, param1, param2, param3, param4, param5);
}

static void PPW_LobbyOnEnumChannels(BOOL param0, s32 param1, const char **param2, const char **param3, const s32 *param4, void *param5)
{
    if (!param0) {
        return;
    }

    for (int i = 0; i < param1; i++) {
        if (param4[i] < PPW_LOBBY_MAX_PLAYER_NUM_MAIN) {
            std::vector<PPWString, PPW_Allocator<PPWString> > v0 = PPW_SplitString<PPWString>(param2[i], DWCi_LOBBY_CHANNEL_NAME_SEPARATOR);
            if (v0.size() < 2) {
                continue;
            }

            sLobbyImpl->SetChannelName(v0[1].c_str());
            sLobbyImpl->SetCreatingNewChannel(FALSE);
            sLobbyImpl->SetState(PPW_LOBBY_STATE_ENTERMAINCHANNEL);
            return;
        }
    }

    sLobbyImpl->SetChannelName(PPW_LobbyMakeNewChannelName());
    sLobbyImpl->SetCreatingNewChannel(TRUE);
    sLobbyImpl->SetState(PPW_LOBBY_STATE_ENTERMAINCHANNEL);
}

static void PPW_LobbyOnEnumUsers(BOOL param0, const char *param1, s32 param2, const s32 *param3, void *param4)
{
    if (!param0) {
        return;
    }

    PPW_LOBBY_CHANNEL_KIND v0 = sLobbyImpl->GetChannelPair().FindKind(param1);
    if (v0 == PPW_LOBBY_CHANNEL_KIND_INVALID) {
        return;
    }

    if (v0 == PPW_LOBBY_CHANNEL_KIND_MAIN) {
        for (int i = 0; i < param2; i++) {
            if (param3[i] == sLobbyImpl->GetPid()) {
                continue;
            }
            sLobbyImpl->GetPlayers().AddPlayer(param3[i]);
            DWCi_LobbyGetChannelDataAsync(param1, param3[i], PPW_LOBBY_CHANNEL_KEY_USER, PPW_LobbyOnChannelData, NULL);
            DWCi_LobbyGetChannelDataAsync(param1, param3[i], PPW_LOBBY_CHANNEL_KEY_SYSTEM, PPW_LobbyOnChannelData, NULL);
        }

        sLobbyImpl->GetMainChannel().SetEntered();
    }
}

static void PPW_LobbyOnChannelMode(BOOL param0, const char *param1, const DWCi_LobbyChannelMode *param2, void *param3)
{
    if (!param0) {
        return;
    }

    if (param2->limit == PPW_LOBBY_MAX_PLAYER_NUM_MAIN) {
        sLobbyImpl->GetMainChannel().SetModeChecked();
        sLobbyImpl->GetTimers().Remove(PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_MODE);
    } else {
        DWCi_LobbySetChannelMode(param1, &PPW_LOBBY_CHANNEL_MODE_MAIN);
    }
}

static void PPW_LobbyOnChannelTime(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5)
{
    if (!param0) {
        return;
    }

    std::vector<u8, PPW_Allocator<u8> > v0;
    BOOL v1 = PPW_Base64DecodeToVector(param4, v0);
    if (!v1 || v0.size() != sizeof(PPW_LobbyInnerInfo::OpenedTime)) {
        PPW_LobbyInnerInfo::OpenedTime v2 = sLobbyImpl->GetInnerInfo().RefreshOpenedTime();
        PPW_LobbySetChannelDataImpl(PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_CHANNEL_KEY_CHANNEL_TIME, (u8 *)&v2, sizeof(v2));
        return;
    } else {
        PPW_LobbyInnerInfo::OpenedTime *v2 = (PPW_LobbyInnerInfo::OpenedTime *)PPW_GetVectorData(v0);
        sLobbyImpl->GetInnerInfo().SetOpenedTime(*v2);
        sLobbyImpl->GetTimers().Remove(PPW_LOBBY_TIMER_ID_CHECK_MAINCHANNEL_SYSTEMDATA);
    }
}

static void PPW_LobbyOnChannelLobby(BOOL param0, const char *param1, s32 param2, const char *param3, const char *param4, void *param5)
{
    if (!param0) {
        return;
    }

    std::vector<u8, PPW_Allocator<u8> > v0;
    BOOL v1 = PPW_Base64DecodeToVector(param4, v0);

    if (!v1 || v0.empty() || !sLobbyImpl->GetInnerInfo().SetSchedule(PPW_GetVectorData(v0), v0.size())) {
        std::vector<u8, PPW_Allocator<u8> > v2 = sLobbyImpl->GetInnerInfo().SerializeSchedule();
        PPW_LobbySetChannelDataImpl(PPW_LOBBY_INVALID_USER_ID, PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_CHANNEL_KEY_CHANNEL_LOBBY, PPW_GetVectorData(v2), v2.size());
        return;
    } else {
        sLobbyImpl->GetInnerInfo().SetScheduleReceived();
        sLobbyImpl->GetTimers().Remove(PPW_LOBBY_TIMER_ID_CHECK_LOBBY_INFO);
    }
}

static void PPW_LobbyOnTopicChanged(const char *param0, const char *param1, void *param2)
{
    return;
}
