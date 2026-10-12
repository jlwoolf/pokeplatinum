#ifndef PPWLOBBY_PROFILE_H
#define PPWLOBBY_PROFILE_H

// needs to be included first to match
// clang-format off
#include <vector>
// clang-format on
#include <functional>
#include <set>

#include "ilobby/dwci_lobbydata.h"
#include "ppwlobby/ppw_lobby.h"

template <class T>
class PPW_DirtyValue : public DWCi_LobbyObject {
    T unk_00;
    mutable BOOL unk_04;

public:
    PPW_DirtyValue()
        : unk_00()
        , unk_04(TRUE)
    {
    }

    PPW_DirtyValue(const T &param0)
        : unk_00(param0)
        , unk_04(TRUE)
    {
    }

    PPW_DirtyValue &operator=(const PPW_DirtyValue &param0)
    {
        if (!(unk_00 == param0.unk_00)) {
            unk_00 = param0.unk_00;
            unk_04 = TRUE;
        }

        return *this;
    }

    const PPW_DirtyValue &Assign(const PPW_DirtyValue &param0, BOOL param1)
    {
        if (param1) {
            unk_04 = TRUE;
        }

        return *this = param0;
    }

    const PPW_DirtyValue &Set(const T &param0, BOOL param1)
    {
        return this->Assign(PPW_DirtyValue<T>(param0), param1);
    }

    BOOL IsDirty() const
    {
        return unk_04;
    }

    const T &Consume() const
    {
        unk_04 = FALSE;
        return unk_00;
    }

    const T &Get() const
    {
        return unk_00;
    }
};

class PPW_PlayerProfile : public DWCi_LobbyObject {
public:
    struct SystemData {
        PPW_LOBBY_CHANNEL_KIND unk_00;
        s64 unk_04;
        BOOL unk_0C;

        SystemData()
            : unk_00(PPW_LOBBY_CHANNEL_KIND_INVALID)
            , unk_04()
            , unk_0C(FALSE)
        {
            unk_04 = PPW_GetCurrentTimeSeconds();
        }

        bool operator==(const SystemData &param0) const
        {
            return memcmp(this, &param0, sizeof(*this)) == 0;
        }

        PPW_LobbySystemProfile ToSystemProfile() const
        {
            PPW_LobbySystemProfile v0;
            v0.subChannelKind = unk_00;
            v0.enterTime = unk_04;
            return v0;
        }
    };

    struct UserData {
        std::vector<u8, PPW_Allocator<u8> > unk_00;

        UserData()
            : unk_00()
        {
        }

        UserData(const u8 *param0, u32 param1)
        {
            unk_00.assign(param0, param0 + param1);
        }

        bool operator==(const UserData &param0) const
        {
            return unk_00.size() == param0.unk_00.size() && (unk_00.empty() || memcmp(PPW_GetVectorData(unk_00), PPW_GetVectorData(param0.unk_00), unk_00.size()) == 0);
        }
    };

private:
    PPW_DirtyValue<SystemData> unk_00;
    PPW_DirtyValue<UserData> unk_14;
    int unk_24;
    int unk_28;
    BOOL unk_2C;
    BOOL unk_30;
    BOOL unk_34;

public:
    PPW_PlayerProfile()
        : unk_28(PPW_LOBBY_INVALID_USER_ID)
    {
    }

    PPW_PlayerProfile(int param0)
        : unk_00()
        , unk_14()
        , unk_24(0)
        , unk_28(param0)
        , unk_2C(FALSE)
        , unk_30(FALSE)
        , unk_34(FALSE)
    {
    }

    virtual ~PPW_PlayerProfile()
    {
    }

    bool operator<(const PPW_PlayerProfile &param0) const
    {
        return unk_28 < param0.unk_28;
    }

    struct PidMatcher : public std::unary_function<PPW_PlayerProfile *, bool> {
        const int unk_00;
        PidMatcher(int param0)
            : unk_00(param0)
        {
        }

        bool operator()(const PPW_PlayerProfile *param0) const
        {
            return unk_00 == param0->unk_28;
        }
    };

    void SetUserData(const u8 *param0, u32 param1, BOOL param2 = FALSE)
    {
        UserData v0(param0, param1);
        unk_14.Set(v0, param2);
        unk_30 = TRUE;
    }

    BOOL GetUserData(u8 *param0, u32 *param1) const
    {
        std::vector<u8, PPW_Allocator<u8> > v0 = unk_14.Get().unk_00;
        u32 v1 = *param1;

        *param1 = v0.size();

        if (*param1 == 0) {
            return TRUE;
        }

        if (v1 < v0.size() || param0 == NULL) {
            return FALSE;
        }

        MI_CpuCopy8(PPW_GetVectorData(v0), param0, v0.size());
        return TRUE;
    }

    const UserData &GetUserDataStore() const
    {
        return unk_14.Get();
    }

    const UserData &TakeUserData() const
    {
        return unk_14.Consume();
    }

    BOOL IsUserDataDirty() const
    {
        return unk_14.IsDirty();
    }

    void SetSystemData(const SystemData &param0)
    {
        unk_00 = param0;
        unk_2C = TRUE;
    }

    const SystemData &GetSystemData() const
    {
        return unk_00.Get();
    }

    const SystemData &TakeSystemData() const
    {
        return unk_00.Consume();
    }

    BOOL IsSystemDataDirty() const
    {
        return unk_00.IsDirty();
    }

    void SetUpdated()
    {
        unk_34 = TRUE;
    }

    BOOL IsUpdated() const
    {
        return unk_34;
    }

    int GetState() const
    {
        return unk_24;
    }

    int GetPid() const
    {
        return unk_28;
    }

    bool IsComplete() const
    {
        return unk_24 >= 1;
    }

    void Update();
};

class PPW_PlayerManager : public DWCi_LobbyObject {
    typedef std::set<PPW_PlayerProfile *, DWCi_LobbyObject::LessComparator<PPW_PlayerProfile>, PPW_Allocator<PPW_PlayerProfile *> > PlayerSet;
    PlayerSet unk_00;
    PPW_PlayerProfile unk_0C;

public:
    PPW_PlayerManager()
        : unk_00()
        , unk_0C()
    {
    }

    virtual ~PPW_PlayerManager()
    {
        ClearPlayers();
    }

    BOOL IsPlayerComplete(int param0)
    {
        PPW_PlayerProfile *v0 = FindPlayer(param0);
        return v0 && v0->IsUpdated();
    }

    PPW_PlayerProfile &GetMyProfile()
    {
        return unk_0C;
    }

    BOOL AddPlayer(int param0);
    BOOL RemovePlayer(int param0);
    PPW_PlayerProfile *FindPlayer(int param0);
    void ClearPlayers();
    BOOL IsFull() const;
    std::vector<s32, PPW_Allocator<s32> > GetConnectedPids() const;
    void SetMyProfile(s32 param0, const u8 *param1, u32 param2);
    BOOL AllPlayersComplete() const;
    void UpdatePlayers();
};

#endif // PPWLOBBY_PROFILE_H
