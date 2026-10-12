#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230DBC.h"

#include "savedata.h"

typedef struct {
    WiFiPlazaLobbyMinigameParticipants participants; // WiFi lobby minigame connection data.
    SaveData *saveData;
    u8 voiceChatEnabled; // Whether voice chat is enabled.
    u8 fromLobby; // Whether the minigame was launched from the WiFi lobby.
    u8 padding[2];
} WiFiLobbyMinigameBalloonArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_ARGS_H
