#ifndef PPWLOBBY_PPW_LOBBY_IMPL_H
#define PPWLOBBY_PPW_LOBBY_IMPL_H

#include "ilobby/dwci_lobby_timer.h"
#include "ilobby/dwci_lobbydata.h"

// include order necessary to match
// clang-format off
#include "ppwlobby/ppw_lobby_channel.h"
#include "ppwlobby/ppw_channel.h"
#include "ppwlobby/ppw_profile.h"
#include "ppwlobby/dwci_encsession.h"
#include "ppwlobby/ppw_innerinfo.h"
// clang-format on

class PPW_LobbyImpl : public DWCi_LobbyObject {
private:
    PPW_LOBBY_STATE unk_00;
    PPW_LOBBY_ERROR unk_04;
    const PPW_LobbyCallbacks unk_08;
    const s32 unk_4C;
    const DWC_LOBBY_CHANNEL_PREFIX unk_50;
    const BOOL unk_54;
    PPWString unk_58;
    BOOL unk_64;
    BOOL unk_68;
    BOOL unk_6C;
    s32 unk_70;
    PPW_LobbyRecruitInfo unk_74;
    PPW_ChannelPair unk_B8;
    PPW_PlayerManager unk_E8;
    DWCi_LobbyTimerManager unk_134;
    PPW_LobbyInnerInfo unk_144;

public:
    PPW_LobbyImpl(const PPW_LobbyCallbacks &param0, s32 param1, DWC_LOBBY_CHANNEL_PREFIX param2, BOOL param3)
        : unk_00(PPW_LOBBY_STATE_NOTINITIALIZED)
        , unk_04(PPW_LOBBY_ERROR_NONE)
        , unk_08(param0)
        , unk_4C(param1)
        , unk_50(param2)
        , unk_54(param3)
        , unk_58()
        , unk_64(FALSE)
        , unk_68(FALSE)
        , unk_6C(FALSE)
        , unk_70(0)
        , unk_74()
        , unk_B8()
        , unk_E8()
        , unk_134()
        , unk_144()
    {
    }

    ~PPW_LobbyImpl()
    {
    }

    PPW_LOBBY_STATE GetState() const
    {
        return unk_00;
    }

    void SetState(PPW_LOBBY_STATE param0)
    {
        unk_00 = param0;
    }

    const PPW_LobbyCallbacks &GetCallbacks() const
    {
        return unk_08;
    }

    s32 GetPid() const
    {
        return unk_4C;
    }

    enum DWCi_EncServerKind GetServerKind() const
    {
        return unk_50 == DWC_LOBBY_CHANNEL_PREFIX_RELEASE ? DWCi_ENC_SERVER_KIND_RELEASE : DWCi_ENC_SERVER_KIND_DEBUG;
    }

    PPW_LOBBY_ERROR GetError() const
    {
        return unk_04;
    }

    void SetError(PPW_LOBBY_ERROR param0)
    {
        if (param0 != PPW_LOBBY_ERROR_NONE) {
            unk_04 = param0;
            unk_00 = PPW_LOBBY_STATE_ERROR;
        }
    }

    void SetDwcError(DWCi_LOBBY_ERROR param0)
    {
        SetError((PPW_LOBBY_ERROR)param0);
    }

    void SetResultError(PPW_LOBBY_RESULT param0)
    {
        PPW_LOBBY_ERROR v0;
        switch (param0) {
        case PPW_LOBBY_RESULT_ERROR_ALLOC:
            v0 = PPW_LOBBY_ERROR_ALLOC;
            break;
        case PPW_LOBBY_RESULT_ERROR_SESSION:
            v0 = PPW_LOBBY_ERROR_SESSION;
            break;
        default:
            v0 = PPW_LOBBY_ERROR_NONE;
            break;
        }

        SetError(v0);
    }

    void SetCreatingNewChannel(BOOL param0)
    {
        unk_64 = param0;
    }

    PPWString GetChannelName() const
    {
        return unk_58;
    }

    BOOL TryIncrementRetry()
    {
        if (unk_70 >= 3) {
            return FALSE;
        } else {
            unk_70++;
            return TRUE;
        }
    }

    void ResetRetry()
    {
        unk_70 = 0;
    }

    void SetChannelName(const PPWString &param0)
    {
        unk_58 = param0;
    }

    BOOL StartRecruit(const PPW_LobbyRecruitInfo &param0, PPWString &param1)
    {
        if (unk_68) {
            return FALSE;
        } else {
            unk_68 = TRUE;
            unk_74 = param0;
            param1 = PPW_FormatStringTrunc<PPWString>(PPW_LOBBY_MAX_MATCHMAKING_STRING_LENGTH, "M%d_%u", unk_4C, (unsigned long)current_time() % 1000);
            strncpy(unk_74.matchMakingString, param1.c_str(), PPW_LOBBY_MAX_MATCHMAKING_STRING_LENGTH - 1);
            return TRUE;
        }
    }

    BOOL IsRecruiting() const
    {
        return unk_68;
    }

    const PPW_LobbyRecruitInfo &GetRecruitInfo() const
    {
        return unk_74;
    }

    BOOL UpdateRecruitInfo(const PPW_LobbyRecruitInfo &_recruitInfo)
    {
        if (!unk_68) {
            return FALSE;
        } else {
            unk_74 = _recruitInfo;
            return TRUE;
        }
    }

    BOOL StopRecruit()
    {
        if (!unk_68) {
            return FALSE;
        } else {
            unk_68 = FALSE;
            return TRUE;
        }
    }

    void SetSubmittingQuestionnaire(BOOL param0)
    {
        unk_6C = param0;
    }

    BOOL IsSubmittingQuestionnaire() const
    {
        return unk_6C;
    }

    void Update()
    {
        unk_134.Update();
        unk_E8.UpdatePlayers();
        unk_144.Update();
    }

    PPW_ChannelPair &GetChannelPair()
    {
        return unk_B8;
    }

    PPW_ChannelInfo &GetMainChannel()
    {
        return unk_B8.Get(0);
    }

    PPW_ChannelInfo &GetSubChannel()
    {
        return unk_B8.Get(1);
    }

    void SetMainChannel(const PPW_ChannelInfo &param0)
    {
        unk_B8.Set(0, param0);
    }

    void SetSubChannel(const PPW_ChannelInfo &param0)
    {
        unk_B8.Set(1, param0);
    }

    PPW_PlayerManager &GetPlayers()
    {
        return unk_E8;
    }

    DWCi_LobbyTimerManager &GetTimers()
    {
        return unk_134;
    }

    PPW_LobbyInnerInfo &GetInnerInfo()
    {
        return unk_144;
    }
};

PPW_LobbyImpl *PPW_LobbyGetImpl();

#endif // PPWLOBBY_PPW_LOBBY_IMPL_H
