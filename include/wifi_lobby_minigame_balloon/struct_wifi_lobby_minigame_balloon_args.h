#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H

#include "overlay066/struct_ov66_02230DBC.h"

#include "savedata.h"

typedef struct {
    UnkStruct_ov66_02230DBC unk_00; // WiFi lobby minigame connection data.
    SaveData *saveData;
    u8 unk_38; // Whether voice chat is enabled.
    u8 unk_39; // Whether the minigame was launched from the WiFi lobby.
    u8 padding[2];
} WiFiLobbyMinigameBalloonArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H
