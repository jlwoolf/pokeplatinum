#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_TEXT_OAM_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_TEXT_OAM_H

#include "struct_decls/font_oam.h"

#include "char_transfer.h"

typedef struct {
    FontOAM *unk_00;
    CharTransferAllocation unk_04;
    u16 unk_10;
    u8 padding_12[2];
} WiFiLobbyMinigameBalloonTextOAM;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_TEXT_OAM_H
