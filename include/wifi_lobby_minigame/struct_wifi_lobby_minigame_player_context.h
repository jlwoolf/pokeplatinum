#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_PLAYER_CONTEXT_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_PLAYER_CONTEXT_H

#include "overlay066/struct_ov66_02230DBC.h"

#include "savedata.h"

typedef struct {
    SaveData *saveData;
    u8 unk_04[4];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    UnkStruct_ov66_02230DBC *unk_0C;
} WiFiLobbyMinigamePlayerContext;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_PLAYER_CONTEXT_H
