#ifndef PPWLOBBY_PPW_CHANNEL_H
#define PPWLOBBY_PPW_CHANNEL_H

#include "ilobby/dwci_lobbydata.h"
#include "ppwlobby/ppw_lobby.h"

class PPW_ChannelInfo : public DWCi_LobbyObject {
    PPW_LOBBY_CHANNEL_KIND unk_00;
    PPWString unk_04;
    BOOL unk_10;
    BOOL unk_14;

public:
    PPW_ChannelInfo()
        : unk_00(PPW_LOBBY_CHANNEL_KIND_INVALID)
        , unk_04()
    {
    }

    PPW_ChannelInfo(PPW_LOBBY_CHANNEL_KIND param0, const PPWString &param1)
        : unk_00(param0)
        , unk_04(param1)
        , unk_10(FALSE)
        , unk_14(FALSE)
    {
    }

    BOOL IsValid() const
    {
        if (unk_00 != PPW_LOBBY_CHANNEL_KIND_INVALID) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    PPW_LOBBY_CHANNEL_KIND GetKind() const
    {
        return unk_00;
    }

    PPWString GetName() const
    {
        return unk_04;
    }

    void SetEntered()
    {
        unk_10 = TRUE;
    }

    BOOL IsEntered() const
    {
        return unk_10;
    }

    void SetModeChecked()
    {
        unk_14 = TRUE;
    }

    BOOL IsModeChecked() const
    {
        return unk_14;
    }

    void Set(PPW_LOBBY_CHANNEL_KIND param0, const PPWString &param1)
    {
        unk_00 = param0;
        unk_04 = param1;
        unk_10 = FALSE;
        unk_14 = FALSE;
    }

    void Reset()
    {
        Set(PPW_LOBBY_CHANNEL_KIND_INVALID, PPWString());
    }
};

class PPW_ChannelPair : public DWCi_LobbyObject {
private:
    PPW_ChannelInfo unk_00;
    PPW_ChannelInfo unk_18;

public:
    PPW_ChannelPair()
        : unk_00()
        , unk_18()
    {
    }

    PPW_ChannelInfo &Get(int param0)
    {
        switch (param0) {
        case 0:
            return unk_00;
        case 1:
            return unk_18;
        default:
            return unk_00;
        }
    }

    void Set(int param0, const PPW_ChannelInfo &param1)
    {
        switch (param0) {
        case 0:
            unk_00 = param1;
            break;
        case 1:
            unk_18 = param1;
            break;
        default:
            break;
        }
    }

    PPWString GetName(PPW_LOBBY_CHANNEL_KIND param0) const
    {
        if (param0 == PPW_LOBBY_CHANNEL_KIND_MAIN) {
            return unk_00.GetName();
        } else {
            return unk_18.GetName();
        }
    }

    PPW_LOBBY_CHANNEL_KIND FindKind(const PPWString &param0) const
    {
        if (unk_00.GetName() == param0) {
            return unk_00.GetKind();
        }

        if (unk_18.GetName() == param0) {
            return unk_18.GetKind();
        }

        return PPW_LOBBY_CHANNEL_KIND_INVALID;
    }
};

#endif // PPWLOBBY_PPW_CHANNEL_H
