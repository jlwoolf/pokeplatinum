#ifndef PPWLOBBY_PPW_LOBBY_CHANNEL_H
#define PPWLOBBY_PPW_LOBBY_CHANNEL_H

#include <lobby/dwci_lobby.h>

#include "ppwlobby/ppw_parser.h"

const DWCi_LobbyChannelMode PPW_LOBBY_CHANNEL_MODE_MAIN = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, PPW_LOBBY_MAX_PLAYER_NUM_MAIN };
const DWCi_LobbyChannelMode PPW_LOBBY_CHANNEL_MODE_MAIN_LOCK = { FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, PPW_LOBBY_MAX_PLAYER_NUM_MAIN };
const DWCi_LobbyChannelMode PPW_LOBBY_CHANNEL_MODE_FOOT = { FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, PPW_LOBBY_MAX_PLAYER_NUM_FOOT };
const DWCi_LobbyChannelMode PPW_LOBBY_CHANNEL_MODE_CLOCK = { FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, PPW_LOBBY_MAX_PLAYER_NUM_CLOCK };
const DWCi_LobbyChannelMode PPW_LOBBY_CHANNEL_MODE_NEWS = { FALSE, FALSE, TRUE, FALSE, TRUE, TRUE, TRUE, PPW_LOBBY_MAX_PLAYER_NUM_NEWS };

typedef struct PPW_LobbyEmptyMessage {
    u32 unk_00;
    PPW_LobbyEmptyMessage()
        : unk_00(0)
    {
    }
} PPW_LobbyEmptyMessage;

inline const DWCi_LobbyChannelMode *PPW_GetLobbyChannelMode(PPW_LOBBY_CHANNEL_KIND param0)
{
    switch (param0) {
    case PPW_LOBBY_CHANNEL_KIND_FOOT1:
    case PPW_LOBBY_CHANNEL_KIND_FOOT2:
        return &PPW_LOBBY_CHANNEL_MODE_FOOT;
    case PPW_LOBBY_CHANNEL_KIND_CLOCK:
        return &PPW_LOBBY_CHANNEL_MODE_CLOCK;
    case PPW_LOBBY_CHANNEL_KIND_NEWS:
        return &PPW_LOBBY_CHANNEL_MODE_NEWS;
    default:
        return NULL;
    }
}

PPW_LOBBY_RESULT PPW_LobbySendMessage(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, int param2, PPW_MessageParser::MessageKind param3, s32 param4, const u8 *param5, u32 param6);
PPW_LOBBY_RESULT PPW_LobbySetChannelDataImpl(s32 param0, PPW_LOBBY_CHANNEL_KIND param1, const char *param2, const u8 *param3, u32 param4);

#endif // PPWLOBBY_PPW_LOBBY_CHANNEL_H
