#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_ARGS_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_ARGS_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230DBC.h"

#include "savedata.h"

typedef struct {
    WiFiPlazaLobbyMinigameParticipants unk_00;
    SaveData *saveData;
    u8 unk_38;
    u8 unk_39;
    u8 padding[2];
} WiFiLobbyMinigameBucketArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_ARGS_H
