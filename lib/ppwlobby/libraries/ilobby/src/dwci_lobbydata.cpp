#include "ilobby/dwci_lobbydata.h"

DWCi_LobbyManager::DWCi_LobbyManager(const PPWString &param0, const PPWString &param1, DWC_LOBBY_CHANNEL_PREFIX param2, s32 param3, const PPWString &param4, const PPWString &param5, const PPWString &param6, const DWCi_LobbyGlobalCallbacks *param7)
    : unk_00(NULL)
    , unk_04(DWCi_LOBBY_STATE_NOTINITIALIZED)
    , unk_08(param3)
    , unk_0C(param4)
    , unk_18(param5)
    , unk_24(param6)
    , unk_30(param0)
    , unk_3C(param1)
    , unk_48()
    , unk_54(0)
    , unk_58(DWCi_LOBBY_ERROR_NONE)
    , unk_5C(0)
    , unk_60(FALSE)
    , unk_64(*param7)
    , unk_70()
    , unk_80()
    , unk_90()
    , unk_9C()
{
    const char *const sChannelTypeNames[] = {
        "R",
        "D",
        "D1",
        "D2",
        "D3",
        "D4",
        "D5",
        "D6",
        "D7",
        "D8",
        "D9",
        "T"
    };

    unk_48 = PPWString(sChannelPrefix) + DWCi_LOBBY_CHANNEL_NAME_SEPARATOR
        + unk_30 + DWCi_LOBBY_CHANNEL_NAME_SEPARATOR
        + PPWString(sChannelTypeNames[param2]) + DWCi_LOBBY_CHANNEL_NAME_SEPARATOR;
}

DWCi_LobbyManager::~DWCi_LobbyManager()
{
    return;
}

PPWString DWCi_LobbyManager::MakeFullChannelName(const PPWString &param0) const
{
    return unk_48 + param0;
}

PPWString DWCi_LobbyManager::StripChannelPrefix(const PPWString &param0) const
{
    return param0.substr(unk_48.length());
}

std::vector<char *, PPW_Allocator<char *> > DWCi_LobbyManager::StripChannelList(int param0, const char **param1) const
{
    std::vector<char *, PPW_Allocator<char *> > v0;

    for (int i = 0; i < param0; i++) {
        v0.push_back((char *)(param1[i] + unk_48.length()));
    }

    return v0;
}

PPWString DWCi_LobbyManager::MakeNickName(s32 param0)
{
    return PPW_FormatStringTrunc<PPWString>(DWCi_MAX_CHAT_NICK_SIZE, _T("N_%d_%u"), param0, (u32)current_time() % 1000);
}

s32 DWCi_LobbyManager::ParsePidFromNick(const PPWString &param0)
{
    std::vector<PPWString, PPW_Allocator<PPWString> > v0(PPW_SplitStringAnyOf<PPWString>(param0, "_"));
    if (v0.size() < 2) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    int v1 = atoi(v0[1].c_str());
    if (v1 == 0) {
        return DWC_LOBBY_INVALID_USER_ID;
    }
    return v1;
}

BOOL DWCi_LobbyManager::AddChannel(const PPWString param0, const DWCi_LobbyChannelCallbacks &param1, s32 param2)
{
    std::pair<ChannelInfoMap::iterator, bool> v0;
    v0 = unk_80.insert(std::make_pair(param0, ChannelInfo(param1, param2)));
    return (BOOL)v0.second;
}

const DWCi_LobbyChannelCallbacks *DWCi_LobbyManager::FindChannel(const PPWString &param0) const
{
    ChannelInfoMap::const_iterator v0 = unk_80.find(param0);
    if (v0 == unk_80.end()) {
        return NULL;
    }
    return &v0->second.unk_14;
}

s32 DWCi_LobbyManager::AddUserToChannel(const PPWString &param0, const PPWString &param1)
{
    s32 v0 = ParsePidFromNick(param0);

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    ChannelInfoMap::iterator v1 = unk_80.find(param1);
    if (v1 == unk_80.end()) {
        return DWC_LOBBY_INVALID_USER_ID;
    }
    v1->second.unk_04.insert(v0);

    unk_70[v0] = param0;
    return v0;
}

std::vector<s32, PPW_Allocator<s32> > DWCi_LobbyManager::AddUsersToChannel(int param0, const char **param1, const PPWString &param2)
{
    std::vector<s32, PPW_Allocator<s32> > v0;
    v0.reserve((std::size_t)param0);
    for (int i = 0; i < param0; i++) {
        if (ParsePidFromNick(param1[i]) == GetPid() && GetNickName() != param1[i]) {
            continue;
        }

        s32 v2 = AddUserToChannel(param1[i], param2);
        if (v2 != DWC_LOBBY_INVALID_USER_ID) {
            v0.push_back(v2);
        }
    }

    return v0;
}

BOOL DWCi_LobbyManager::RemoveUserIfAbsent(s32 param0)
{
    ChannelInfoMap::const_iterator v0 = std::find_if(unk_80.begin(), unk_80.end(), ChannelContainsUser(param0));
    if (v0 == unk_80.end()) {
        unk_70.erase(param0);
        return TRUE;
    }
    return FALSE;
}

BOOL DWCi_LobbyManager::RemoveUserFromChannel(const PPWString &param0, const PPWString &param1)
{
    s32 v0 = ParsePidFromNick(param0);

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return FALSE;
    }

    ChannelInfoMap::iterator v1 = unk_80.find(param1);
    if (v1 == unk_80.end()) {
        return FALSE;
    }

    if (!v1->second.unk_04.erase(v0)) {
        return FALSE;
    }

    RemoveUserIfAbsent(v0);
    return TRUE;
}

BOOL DWCi_LobbyManager::RemoveChannel(const PPWString &param0)
{
    ChannelInfoMap::iterator v0 = unk_80.find(param0);
    if (v0 == unk_80.end()) {
        return FALSE;
    }

    std::vector<s32, PPW_Allocator<s32> > v1;
    v1.assign(v0->second.unk_04.begin(), v0->second.unk_04.end());

    unk_80.erase(param0);

    std::for_each(v1.begin(), v1.end(), std::bind1st(std::mem_fun(&DWCi_LobbyManager::RemoveUserIfAbsent), this));
    return TRUE;
}

s32 DWCi_LobbyManager::FindPidByNick(const PPWString &param0) const
{
    s32 v0 = ParsePidFromNick(param0);

    if (v0 == DWC_LOBBY_INVALID_USER_ID) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    UserNickMap::const_iterator v1 = unk_70.find(v0);
    if (v1 == unk_70.end()) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    if (v1->second != param0) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    return v0;
}

PPWString DWCi_LobbyManager::FindNickByPid(s32 param0) const
{
    UserNickMap::const_iterator v0 = unk_70.find(param0);
    if (v0 == unk_70.end()) {
        return "";
    }
    return v0->second;
}

s32 DWCi_LobbyManager::ChangeNick(const PPWString &param0, const PPWString &param1)
{
    s32 v0 = FindPidByNick(param0);
    unk_70.erase(v0);

    std::pair<UserNickMap::iterator, bool> v1;
    v1 = unk_70.insert(std::make_pair(v0, param1));
    if (!v1.second) {
        return DWC_LOBBY_INVALID_USER_ID;
    }

    return v0;
}

BOOL DWCi_LobbyManager::IsChannelJoined(const PPWString &param0) const
{
    ChannelInfoMap::const_iterator v0 = unk_80.find(param0);
    if (v0 == unk_80.end()) {
        return FALSE;
    }
    return v0->second.unk_00;
}

BOOL DWCi_LobbyManager::SetChannelJoined(const PPWString &param0)
{
    ChannelInfoMap::iterator v0 = unk_80.find(param0);
    if (v0 == unk_80.end()) {
        return FALSE;
    }
    v0->second.unk_00 = TRUE;
    return TRUE;
}

s32 DWCi_LobbyManager::GetChannelLimit(const PPWString &param0)
{
    ChannelInfoMap::iterator v0 = unk_80.find(param0);
    if (v0 == unk_80.end()) {
        return -1;
    }
    return v0->second.unk_10;
}
