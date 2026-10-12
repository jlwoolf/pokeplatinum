#include <lobby/dwci_lobby.h>

// include order necessary to match
// clang-format off
#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobbydata.h"
#include "ilobby/dwci_lobbycallback.h"
#include "ilobby/dwci_lobbynewhandler.h"
// clang-format on

static DWCi_LobbyManager *sLobbyManager = NULL;

static void ChatRawCallback(CHAT param0, const char *param1, void *param2)
{
    if (!sLobbyManager) {
        return;
    }
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }
}

static void ChatDisconnectedCallback(CHAT param0, const char *param1, void *param2)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    sLobbyManager->GetTimers().Remove(0);

    if (sLobbyManager->GetState() == DWCi_LOBBY_STATE_CLOSING) {
        if (sLobbyManager) {
            delete sLobbyManager;
            sLobbyManager = NULL;
        }
    } else {
        sLobbyManager->SetError(DWCi_LOBBY_ERROR_SESSION);
        sLobbyManager->SetDisconnected();
    }
}

static void ChatPrivateMessageCallback(CHAT param0, const char *param1, const char *param2, int param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (PPW_StrniCmpCStr(param1, "SERVER", 6) == 0) {
        if (PPW_StrniCmpCStr(param2, "Excess Flood", 12) != 0) {
            return;
        }

        std::vector<PPWString, PPW_Allocator<PPWString> > v0 = PPW_SplitStringAnyOf<PPWString>(param2, " :");
        if (v0.empty()) {
            return;
        }

        u32 v1 = (u32)atoi(v0.back().c_str());
        if (v1 == 0) {
            return;
        }

        sLobbyManager->GetGlobalCallbacks().lobbyExcessFloodCallback(v1, param4);
        return;
    }

    if (param3 != CHAT_UTM) {
        return;
    }

    s32 v2 = sLobbyManager->FindPidByNick(param1);
    if (v2 != DWC_LOBBY_INVALID_USER_ID) {
        sLobbyManager->GetGlobalCallbacks().lobbyUserMessageReceivedCallback(v2, param2, param4);
    }
}

static void ChatInvitedCallback(CHAT param0, const char *param1, const char *param2, void *param3)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }
}

static void ChatChannelMessageCallback(CHAT param0, const char *param1, const char *param2, const char *param3, int param4, void *param5)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (param4 != CHAT_UTM) {
        return;
    }

    s32 v0 = sLobbyManager->FindPidByNick(param2);

    const DWCi_LobbyChannelCallbacks *v1 = sLobbyManager->FindChannel(param1);

    v1->lobbyChannelMessageReceivedCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), v0, param3, v1->param);
}

static void ChatKickedCallback(CHAT param0, const char *param1, const char *param2, const char *param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    sLobbyManager->RemoveChannel(param1);
}

static void ChatUserJoinedCallback(CHAT param0, const char *param1, const char *param2, int param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    s32 v0 = sLobbyManager->GetChannelLimit(param1);

    if (v0 != 0 && chatGetChannelNumUsers(sLobbyManager->GetChatSession(), param1) > v0) {
        return;
    }

    PPWString v1 = sLobbyManager->FindNickByPid(DWCi_LobbyManager::ParsePidFromNick(param2));

    if (sLobbyManager->RemoveUserFromChannel(v1, param1)) {
        const DWCi_LobbyChannelCallbacks *v2 = sLobbyManager->FindChannel(param1);

        v2->lobbyPlayerDisconnectedCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), DWCi_LobbyManager::ParsePidFromNick(param2), v2->param);
    }

    s32 v3 = sLobbyManager->AddUserToChannel(param2, param1);

    if (v3 == DWC_LOBBY_INVALID_USER_ID) {
        return;
    }

    if (sLobbyManager->IsChannelJoined(param1)) {
        const DWCi_LobbyChannelCallbacks *v4 = sLobbyManager->FindChannel(param1);

        v4->lobbyPlayerConnectedCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), v3, v4->param);
    }
}

static void ChatUserPartedCallback(CHAT param0, const char *param1, const char *param2, int param3, const char *param4, const char *param5, void *param6)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    s32 v0 = sLobbyManager->FindPidByNick(param2);

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return;
    }

    const DWCi_LobbyChannelCallbacks *v1 = sLobbyManager->FindChannel(param1);

    v1->lobbyPlayerDisconnectedCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), v0, v1->param);

    sLobbyManager->RemoveUserFromChannel(param2, param1);
}

static void ChatUserChangedNickCallback(CHAT param0, const char *param1, const char *param2, const char *param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    sLobbyManager->ChangeNick(param2, param3);
}

static void ChatUserModeChangedCallback(CHAT param0, const char *param1, const char *param2, int param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    PPWString unused;
    switch (param3) {
    case CHAT_NORMAL:
        unused = "normal";
        break;
    case CHAT_VOICE:
        unused = "voice";
        break;
    case CHAT_OP:
        unused = "ops";
        break;
    case (CHAT_VOICE | CHAT_OP):
        unused = "voice+ops";
        break;
    default:
        unused = "invalid";
        break;
    }
}

static void ChatTopicChangedCallback(CHAT param0, const char *param1, const char *param2, void *param3)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    const DWCi_LobbyChannelCallbacks *v0 = sLobbyManager->FindChannel(param1);

    v0->lobbyTopicChangedCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), param2, v0->param);
}

static void ChatChannelModeChangedCallback(CHAT param0, const char *param1, CHATChannelMode *param2, void *param3)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }
}

static void ChatUserListUpdatedCallback(CHAT param0, const char *param1, void *param2)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }
}

static void ChatConnectResultCallback(CHAT param0, CHATBool param1, int param2, void *param3)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    sLobbyManager->GetTimers().Remove(0);

    if (param1 == CHATFalse) {
        sLobbyManager->SetError(DWCi_LOBBY_ERROR_SESSION);
        sLobbyManager->SetDisconnected();
    } else {
        sLobbyManager->SetState(DWCi_LOBBY_STATE_CONNECTINGWAIT);
    }
}

static void ChatUniqueNickCallback(CHAT param0, unsigned int param1, char param2[128], void *param3)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    strncpy(param2, sLobbyManager->GetLoginName().c_str(), 128 - 1);
}

static void ChatConnectStateChangedCallback(CHAT param0, int param1, const char *param2, int param3, const char **param4, void *param5)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (param1 == CHAT_IN_USE) {
        sLobbyManager->SetNickName(DWCi_LobbyManager::MakeNickName(sLobbyManager->GetPid()));
        chatRetryWithNick(param0, sLobbyManager->GetNickName().c_str());
    } else if (param1 == CHAT_INVALID) {
        sLobbyManager->SetNickName(DWCi_LobbyManager::MakeNickName(sLobbyManager->GetPid()));
        chatRetryWithNick(param0, sLobbyManager->GetNickName().c_str());
    } else if ((param1 == CHAT_UNIQUENICK_EXPIRED) || (param1 == CHAT_NO_UNIQUENICK)) {
        sLobbyManager->SetNickName(DWCi_LobbyManager::MakeNickName(sLobbyManager->GetPid()));
        chatRegisterUniqueNick(param0, 2, sLobbyManager->GetNickName().c_str(), "");
    } else if (param1 == CHAT_INVALID_UNIQUENICK) {
        return;
    } else if (param1 == CHAT_NICK_TOO_LONG) {
        sLobbyManager->SetNickName(DWCi_LobbyManager::MakeNickName(sLobbyManager->GetPid()));
        chatRetryWithNick(param0, sLobbyManager->GetNickName().c_str());
    }
}

static void ChatEnumChannelsCallback(CHAT param0, CHATBool param1, int param2, const char **param3, const char **param4, int *param5, void *param6)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    std::vector<char *, PPW_Allocator<char *> > v0 = sLobbyManager->StripChannelList(param2, param3);

    DWCi_LobbyTypedCallback<DWCi_LobbyEnumChannelsCallback> *v1 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyEnumChannelsCallback>((u32)param6);
    v1->Get()(param1 == CHATTrue, param2, (const char **)PPW_GetVectorData(v0), param4, (s32 *)param5, v1->GetParam());
    sLobbyManager->GetCallbacks().Remove((u32)param6);
}

static void ChatEnumChannelsProgressCallback(CHAT param0, CHATBool param1, int param2, const char *param3, const char *param4, int param5, void *param6)
{
    if (!param1) {
        return;
    }
}

static void ChatEnumUsersCallback(CHAT param0, CHATBool param1, const char *param2, int param3, const char **param4, int *param5, void *param6)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    std::vector<s32, PPW_Allocator<s32> > v0;

    if (param3 != 0) {
        v0 = sLobbyManager->AddUsersToChannel(param3, param4, param2);
    }

    DWCi_LobbyTypedCallback<DWCi_LobbyEnumUsersCallback> *v1 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyEnumUsersCallback>((u32)param6);
    v1->Get()(param1 == CHATTrue, sLobbyManager->StripChannelPrefix(param2).c_str(), (s32)v0.size(), PPW_GetVectorData(v0), v1->GetParam());
    sLobbyManager->GetCallbacks().Remove((u32)param6);
}

static void ChatEnumUsersJoinCallback(CHAT param0, CHATBool param1, const char *param2, int param3, const char **param4, int *param5, void *param6)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (param1 == CHATTrue) {
        sLobbyManager->AddUsersToChannel(param3, param4, param2);
    }

    sLobbyManager->SetChannelJoined(param2);

    const DWCi_LobbyTypedCallback<DWCi_LobbyJoinChannelCallback> *v0 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyJoinChannelCallback>((u32)param6);
    v0->Get()(param1 == CHATTrue, DWCi_LOBBY_ENTER_RESULT_SUCCESS, sLobbyManager->StripChannelPrefix(param2).c_str(), v0->GetParam());
    sLobbyManager->GetCallbacks().Remove((u32)param6);

    if (param1 == CHATFalse) {
        DWCi_LobbyLeaveChannel(sLobbyManager->StripChannelPrefix(param2).c_str());
    }
}

static void ChatEnterChannelCallback(CHAT param0, CHATBool param1, CHATEnterResult param2, const char *param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (param1 == CHATTrue) {
        s32 v0 = sLobbyManager->GetChannelLimit(param3);

        if (v0 != 0) {
            s32 v1 = chatGetChannelNumUsers(sLobbyManager->GetChatSession(), param3);

            if (v0 == -1) {
                param1 = CHATFalse;
                param2 = CHATEnterTimedOut;
            } else if (v1 > v0 || v1 == -1) {
                param1 = CHATFalse;
                param2 = CHATChannelIsFull;
            } else {
                chatSetChannelLimit(sLobbyManager->GetChatSession(), param3, v0);
            }
        }
    }

    if (param1 == CHATTrue) {
        sLobbyManager->AddUserToChannel(sLobbyManager->GetNickName(), param3);
        chatEnumUsers(param0, param3, ChatEnumUsersJoinCallback, param4, CHATFalse);
    } else {
        DWCi_LobbyLeaveChannel(sLobbyManager->StripChannelPrefix(param3).c_str());

        const DWCi_LobbyTypedCallback<DWCi_LobbyJoinChannelCallback> *v2 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyJoinChannelCallback>((u32)param4);
        v2->Get()(FALSE, (DWCi_LOBBY_ENTER_RESULT)param2, sLobbyManager->StripChannelPrefix(param3).c_str(), v2->GetParam());
        sLobbyManager->GetCallbacks().Remove((u32)param4);
    }
}

static void ChatGetChannelKeysCallback(CHAT param0, CHATBool param1, const char *param2, const char *param3, int param4, const char **param5, const char **param6, void *param7)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (!param2) {
        return;
    }

    s32 v0;

    if (param3) {
        v0 = sLobbyManager->FindPidByNick(param3);
    } else {
        v0 = DWC_LOBBY_INVALID_USER_ID;
    }

    DWCi_LobbyTypedCallback<DWCi_LobbyGetChannelDataCallback> *v1 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyGetChannelDataCallback>((u32)param7);

    char *v2 = NULL;
    char *v3 = NULL;
    if (param1 == CHATTrue && param4 > 0) {
        v2 = (char *)param5[0];
        v3 = (char *)param6[0];
    }
    v1->Get()(param1 == CHATTrue, sLobbyManager->StripChannelPrefix(param2).c_str(), v0, v2, v3, v1->GetParam());

    sLobbyManager->GetCallbacks().Remove((u32)param7);
}

static void ChatBroadcastKeyChangedCallback(CHAT param0, const char *param1, const char *param2, const char *param3, const char *param4, void *param5)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    s32 v0;

    if (param2) {
        v0 = sLobbyManager->FindPidByNick(param2);
    } else {
        v0 = DWC_LOBBY_INVALID_USER_ID;
    }

    const DWCi_LobbyChannelCallbacks *v1 = sLobbyManager->FindChannel(param1);

    v1->lobbyBroadcastDataCallback(sLobbyManager->StripChannelPrefix(param1).c_str(), v0, param3, param4, v1->param);
}

static void ChatGetChannelModeCallback(CHAT param0, CHATBool param1, const char *param2, CHATChannelMode *param3, void *param4)
{
    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return;
    }

    if (param1) {
        ChatChannelModeChangedCallback(param0, param2, param3, param4);
    } else {
        return;
    }

    DWCi_LobbyTypedCallback<DWCi_LobbyGetChannelModeCallback> *v0 = sLobbyManager->GetCallbacks().Find<DWCi_LobbyGetChannelModeCallback>((u32)param4);
    v0->Get()(param1 == CHATTrue, sLobbyManager->StripChannelPrefix(param2).c_str(), (DWCi_LobbyChannelMode *)param3, v0->GetParam());
    sLobbyManager->GetCallbacks().Remove((u32)param4);
}

static BOOL ChatConnectTimeoutCallback(void *param0)
{
    sLobbyManager->SetError(DWCi_LOBBY_ERROR_SESSION);

    return FALSE;
}

DWCi_LOBBY_STATE DWCi_LobbyProcess()
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_STATE_NOTINITIALIZED;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_STATE_ERROR;
    }

    if (sLobbyManager->GetChatSession()) {
        chatThink(sLobbyManager->GetChatSession());
    }

    sLobbyManager->UpdateTimers();

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_STATE_ERROR;
    }

    if (sLobbyManager->GetRetryCount() >= 3) {
        sLobbyManager->ClearRetryCount();
        sLobbyManager->SetError(DWCi_LOBBY_ERROR_SESSION);
        return sLobbyManager->GetState();
    }

    switch (sLobbyManager->GetState()) {
    case DWCi_LOBBY_STATE_NOTINITIALIZED:
    case DWCi_LOBBY_STATE_CONNECTING:
        break;
    case DWCi_LOBBY_STATE_CONNECTINGWAIT:
        sLobbyManager->UpdateConnectingWait();
        break;
    case DWCi_LOBBY_STATE_CONNECTED:
    case DWCi_LOBBY_STATE_CLOSING:
    default:
        break;
    }

    return sLobbyManager->GetState();
}

DWCi_LOBBY_ERROR DWCi_LobbyGetLastError()
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_ERROR_NONE;
    }

    return sLobbyManager->GetLastError();
}

s32 DWCi_LobbyToErrorCode(DWCi_LOBBY_ERROR err)
{
    return err + DWCi_LOBBY_ERROR_CODE_BASE;
}

BOOL DWCi_LobbyInChannel(const char *channelName)
{
    if (!sLobbyManager) {
        return FALSE;
    }

    return chatInChannel(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str()) == CHATTrue;
}

DWCi_LOBBY_RESULT DWCi_LobbyInitializePidAsync(const char *gameName, const char *secretKey, DWC_LOBBY_CHANNEL_PREFIX prefix, const DWCi_LobbyGlobalCallbacks *globalCallbacks, s32 pid)
{
    if (sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    PPWString v0(DWCi_LobbyManager::MakeNickName(pid));
    PPWString v1("DWCUser");
    PPWString v2("DWCName");
    CHAT v3 = NULL;

    sLobbyManager = new DWCi_LobbyManager(gameName, secretKey, prefix, pid, v0, v1, v2, globalCallbacks);
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_ALLOC;
    }

    DWCi_LOBBY_RESULT v4 = DWCi_LOBBY_RESULT_SUCCESS;

    if (!DWCi_LobbySetupNewHandler(sLobbyManager)) {
        v4 = DWCi_LOBBY_RESULT_ERROR_ALLOC;
        goto ERROR_ALLOC;
    }

    chatGlobalCallbacks gsGlobalCallbacks;
    MI_CpuClear8(&gsGlobalCallbacks, sizeof(chatGlobalCallbacks));
    gsGlobalCallbacks.raw = ChatRawCallback;
    gsGlobalCallbacks.disconnected = ChatDisconnectedCallback;
    gsGlobalCallbacks.privateMessage = ChatPrivateMessageCallback;
    gsGlobalCallbacks.invited = ChatInvitedCallback;
    gsGlobalCallbacks.param = globalCallbacks->param;

    v3 = chatConnectSecure((sLobbyManager->GetGameName() + "." + DWCi_LOBBY_SERVER_DOMAIN).c_str(), 6667, sLobbyManager->GetNickName().c_str(), sLobbyManager->GetUserName().c_str(), sLobbyManager->GetGameName().c_str(), sLobbyManager->GetSecretKey().c_str(), &gsGlobalCallbacks, ChatConnectStateChangedCallback, ChatUniqueNickCallback, ChatConnectResultCallback, globalCallbacks->param, CHATFalse);
    if (!v3) {
        v4 = DWCi_LOBBY_RESULT_ERROR_SESSION;
        goto ERROR_ALLOC;
    }

    sLobbyManager->SetChatSession(v3);
    sLobbyManager->SetState(DWCi_LOBBY_STATE_CONNECTING);

    sLobbyManager->GetTimers().Add(0, 30, ChatConnectTimeoutCallback, sLobbyManager, FALSE);

    return DWCi_LOBBY_RESULT_SUCCESS;

ERROR_ALLOC:
    DWCi_LobbyShutdownNewHandler();

    if (sLobbyManager) {
        delete sLobbyManager;
        sLobbyManager = NULL;
    }

    return v4;
}

DWCi_LOBBY_RESULT DWCi_LobbyShutdownAsync()
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_SUCCESS;
    }

    if (sLobbyManager->GetState() == DWCi_LOBBY_STATE_CLOSING) {
        return DWCi_LOBBY_RESULT_SUCCESS;
    }

    DWCi_LobbyShutdownNewHandler();

    if (sLobbyManager->IsDisconnected()) {
        chatDisconnect(sLobbyManager->GetChatSession());
        if (sLobbyManager) {
            delete sLobbyManager;
            sLobbyManager = NULL;
        }
    } else {
        sLobbyManager->SetState(DWCi_LOBBY_STATE_CLOSING);
        chatDisconnect(sLobbyManager->GetChatSession());
    }

    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyJoinChannelLimitAsync(const char *channelName, const char *password, s32 limit, const DWCi_LobbyChannelCallbacks *channelCallbacks, DWCi_LobbyJoinChannelCallback callback, void *param)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    BOOL unused = strlen(channelName) + 1 > DWC_LOBBY_MAX_CHANNEL_NAME_SIZE;

    u32 v0 = sLobbyManager->GetCallbacks().Add(callback, param);

    sLobbyManager->AddChannel(sLobbyManager->MakeFullChannelName(channelName).c_str(), *channelCallbacks, limit);

    chatChannelCallbacks v1;
    MI_CpuClear8(&v1, sizeof(chatChannelCallbacks));
    v1.channelMessage = ChatChannelMessageCallback;
    v1.channelModeChanged = ChatChannelModeChangedCallback;
    v1.kicked = ChatKickedCallback;
    v1.topicChanged = ChatTopicChangedCallback;
    v1.userParted = ChatUserPartedCallback;
    v1.userJoined = ChatUserJoinedCallback;
    v1.userListUpdated = ChatUserListUpdatedCallback;
    v1.userModeChanged = ChatUserModeChangedCallback;
    v1.userChangedNick = ChatUserChangedNickCallback;
    v1.broadcastKeyChanged = ChatBroadcastKeyChangedCallback;
    v1.param = (void *)channelCallbacks->param;

    chatEnterChannel(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), password, &v1, ChatEnterChannelCallback, (void *)v0, CHATFalse);

    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyLeaveChannel(const char *channelName)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    chatLeaveChannel(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), NULL);

    sLobbyManager->RemoveChannel(sLobbyManager->MakeFullChannelName(channelName));

    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbySendChannelMessage(const char *channelName, const char *message)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (strlen(message) + 1 > DWC_LOBBY_MAX_STRING_SIZE) {
        return DWCi_LOBBY_RESULT_ERROR_PARAM;
    }

    chatSendChannelMessage(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), message, CHAT_UTM);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbySendUserMessage(s32 userId, const char *message)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (strlen(message) + 1 > DWC_LOBBY_MAX_STRING_SIZE) {
        return DWCi_LOBBY_RESULT_ERROR_PARAM;
    }

    PPWString v0 = sLobbyManager->FindNickByPid(userId);
    if (v0 == "") {
        return DWCi_LOBBY_RESULT_ERROR_PARAM;
    }

    chatSendUserMessage(sLobbyManager->GetChatSession(), v0.c_str(), message, CHAT_UTM);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbySetChannelData(const char *channelName, s32 userId, const char *key, const char *value)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (strlen(value) + 1 > DWC_LOBBY_MAX_STRING_SIZE || strlen(key) + 1 > DWC_LOBBY_MAX_CHANNEL_KEY_SIZE) {
        return DWCi_LOBBY_RESULT_ERROR_PARAM;
    }

    PPWString v0 = "";
    if (userId == DWC_LOBBY_INVALID_USER_ID) {
        v0 = "";
    } else {
        v0 = sLobbyManager->FindNickByPid(userId);
        if (v0 == "") {
            return DWCi_LOBBY_RESULT_ERROR_PARAM;
        }
    }

    chatSetChannelKeys(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), v0.c_str(), 1, &key, &value);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyGetChannelDataAsync(const char *channelName, s32 userId, const char *key, DWCi_LobbyGetChannelDataCallback callback, void *param)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (strlen(key) + 1 > DWC_LOBBY_MAX_CHANNEL_KEY_SIZE) {
        return DWCi_LOBBY_RESULT_ERROR_PARAM;
    }

    PPWString v0 = "";
    if (userId == DWC_LOBBY_INVALID_USER_ID) {
        v0 = "";
    } else {
        v0 = sLobbyManager->FindNickByPid(userId);
        if (v0 == "") {
            return DWCi_LOBBY_RESULT_ERROR_PARAM;
        }
    }

    u32 v1 = sLobbyManager->GetCallbacks().Add(callback, param);

    chatGetChannelKeys(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), v0.c_str(), 1, &key, ChatGetChannelKeysCallback, (void *)v1, CHATFalse);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyEnumChannelsAsync(const char *filter, DWCi_LobbyEnumChannelsCallback callback, void *param)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    u32 v0 = sLobbyManager->GetCallbacks().Add(callback, param);

    chatEnumChannels(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(filter).c_str(), ChatEnumChannelsProgressCallback, ChatEnumChannelsCallback, reinterpret_cast<void *>(v0), CHATFalse);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyEnumUsersAsync(const char *channelName, DWCi_LobbyEnumUsersCallback callback, void *param)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (!chatInChannel(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str())) {
        return DWCi_LOBBY_RESULT_ERROR_CHANNEL;
    }

    u32 v0 = sLobbyManager->GetCallbacks().Add(callback, param);

    chatEnumUsers(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), ChatEnumUsersCallback, reinterpret_cast<void *>(v0), CHATFalse);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbySetChannelMode(const char *channelName, const DWCi_LobbyChannelMode *mode)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    chatSetChannelMode(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), (CHATChannelMode *)mode);
    return DWCi_LOBBY_RESULT_SUCCESS;
}

DWCi_LOBBY_RESULT DWCi_LobbyGetChannelModeAsync(const char *channelName, DWCi_LobbyGetChannelModeCallback callback, void *param)
{
    if (!sLobbyManager) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    if (sLobbyManager && sLobbyManager->GetState() == DWCi_LOBBY_STATE_ERROR) {
        return DWCi_LOBBY_RESULT_ERROR_CONDITION;
    }

    if (sLobbyManager && sLobbyManager->GetState() != DWCi_LOBBY_STATE_CONNECTED) {
        return DWCi_LOBBY_RESULT_ERROR_STATE;
    }

    u32 v0 = sLobbyManager->GetCallbacks().Add(callback, param);

    chatGetChannelMode(sLobbyManager->GetChatSession(), sLobbyManager->MakeFullChannelName(channelName).c_str(), ChatGetChannelModeCallback, reinterpret_cast<void *>(v0), CHATFalse);
    return DWCi_LOBBY_RESULT_SUCCESS;
}
