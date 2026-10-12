#ifndef ILOBBY_LOBBYDATA_H
#define ILOBBY_LOBBYDATA_H

// needs to be included first to match
// clang-format off
#include <vector>
// clang-format on
#include <functional>
#include <map>
#include <set>

#include "lobby/dwci_lobby.h"

// include order necessary to match
// clang-format off
#include "ilobby/dwci_lobbybase.h"
#include "ilobby/dwci_lobbycallback.h"
#include "ilobby/dwci_lobby_timer.h"
#include "ilobby/dwci_lobby_util.h"
// clang-format on

static const char sChannelPrefix[] = "#GSP";

class DWCi_LobbyManager : public DWCi_LobbyObject {
    CHAT unk_00;
    DWCi_LOBBY_STATE unk_04;
    const s32 unk_08;
    PPWString unk_0C;
    const PPWString unk_18;
    const PPWString unk_24;
    const PPWString unk_30;
    const PPWString unk_3C;
    PPWString unk_48;
    u32 unk_54;
    DWCi_LOBBY_ERROR unk_58;
    u32 unk_5C;
    BOOL unk_60;
    const DWCi_LobbyGlobalCallbacks unk_64;

    typedef std::map<s32, PPWString, std::less<s32>, PPW_Allocator<std::pair<s32, PPWString> > > UserNickMap;
    UserNickMap unk_70;

    typedef std::set<s32, std::less<s32>, PPW_Allocator<s32> > UserPidSet;

    struct ChannelInfo : public DWCi_LobbyObject {
        BOOL unk_00;
        UserPidSet unk_04;
        s32 unk_10;
        const DWCi_LobbyChannelCallbacks unk_14;

        ChannelInfo()
            : unk_14()
        {
        }

        ChannelInfo(const DWCi_LobbyChannelCallbacks &param0, s32 param1)
            : unk_00(FALSE)
            , unk_04()
            , unk_10(param1)
            , unk_14(param0)
        {
        }
    };
    typedef std::map<PPWString, ChannelInfo, std::less<PPWString>, PPW_Allocator<std::pair<PPWString, ChannelInfo> > > ChannelInfoMap;
    ChannelInfoMap unk_80;

    DWCi_LobbyCallbackList unk_90;
    DWCi_LobbyTimerManager unk_9C;

public:
    DWCi_LobbyManager(const PPWString &param0, const PPWString &param1, DWC_LOBBY_CHANNEL_PREFIX param2, s32 param3, const PPWString &param4, const PPWString &param5, const PPWString &param6, const DWCi_LobbyGlobalCallbacks *param7);

    ~DWCi_LobbyManager();

    CHAT GetChatSession() const
    {
        return unk_00;
    }

    void SetChatSession(CHAT param0)
    {
        unk_00 = param0;
    }

    DWCi_LOBBY_STATE GetState() const
    {
        return unk_04;
    }

    void SetState(DWCi_LOBBY_STATE param0)
    {
        if (!(unk_04 == DWCi_LOBBY_STATE_ERROR && param0 != DWCi_LOBBY_STATE_CLOSING)) {
            unk_04 = param0;
        }
    }

    s32 GetPid() const
    {
        return unk_08;
    }

    PPWString GetNickName() const
    {
        return unk_0C;
    }

    void SetNickName(const PPWString &param0)
    {
        unk_0C = param0;
    }

    PPWString GetLoginName() const
    {
        return unk_18;
    }

    PPWString GetUserName() const
    {
        return unk_24;
    }

    PPWString GetGameName() const
    {
        return unk_30;
    }

    PPWString GetSecretKey() const
    {
        return unk_3C;
    }

    PPWString MakeFullChannelName(const PPWString &param0) const;

    PPWString StripChannelPrefix(const PPWString &param0) const;

    std::vector<char *, PPW_Allocator<char *> > StripChannelList(int param0, const char **param1) const;

    u32 GetRetryCount() const
    {
        return unk_54;
    }

    void ClearRetryCount()
    {
        unk_54 = 0;
    }

    DWCi_LobbyGlobalCallbacks GetGlobalCallbacks() const
    {
        return unk_64;
    }

    DWCi_LOBBY_ERROR GetLastError() const
    {
        return unk_58;
    }

    void SetError(DWCi_LOBBY_ERROR param0)
    {
        unk_58 = param0;
        unk_04 = DWCi_LOBBY_STATE_ERROR;
    }

    BOOL UpdateConnectingWait()
    {
        if (unk_5C++ == DWCi_LOBBY_CONNECTINGWAIT_TIME) {
            unk_5C = 0;
            SetState(DWCi_LOBBY_STATE_CONNECTED);
            return TRUE;
        } else {
            return FALSE;
        }
    }

    BOOL IsDisconnected() const
    {
        return unk_60;
    }

    void SetDisconnected()
    {
        unk_60 = TRUE;
    }

    DWCi_LobbyCallbackList &GetCallbacks()
    {
        return unk_90;
    }

    DWCi_LobbyTimerManager &GetTimers()
    {
        return unk_9C;
    }

    void UpdateTimers()
    {
        unk_9C.Update();
    }

    static PPWString MakeNickName(s32 param0);
    static s32 ParsePidFromNick(const PPWString &param0);
    BOOL AddChannel(const PPWString param0, const DWCi_LobbyChannelCallbacks &param1, s32 param2);
    const DWCi_LobbyChannelCallbacks *FindChannel(const PPWString &param0) const;
    s32 AddUserToChannel(const PPWString &param0, const PPWString &param1);
    std::vector<s32, PPW_Allocator<s32> > AddUsersToChannel(int param0, const char **param1, const PPWString &param2);

private:
    struct ChannelContainsUser : public std::unary_function<ChannelInfoMap::value_type, bool> {
        const s32 unk_00;
        ChannelContainsUser(s32 param0)
            : unk_00(param0)
        {
        }

        bool operator()(const ChannelInfoMap::value_type &param0) const
        {
            return param0.second.unk_04.find(unk_00) != param0.second.unk_04.end();
        }
    };

    BOOL RemoveUserIfAbsent(s32 param0);

public:
    BOOL RemoveUserFromChannel(const PPWString &param0, const PPWString &param1);
    BOOL RemoveChannel(const PPWString &param0);
    s32 FindPidByNick(const PPWString &param0) const;
    PPWString FindNickByPid(s32 param0) const;
    s32 ChangeNick(const PPWString &param0, const PPWString &param1);
    BOOL IsChannelJoined(const PPWString &param0) const;
    BOOL SetChannelJoined(const PPWString &param0);
    s32 GetChannelLimit(const PPWString &param0);
};

#endif // ILOBBY_LOBBYDATA_H
