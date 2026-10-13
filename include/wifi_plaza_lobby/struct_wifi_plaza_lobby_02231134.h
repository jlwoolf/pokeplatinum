#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231134_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231134_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230DBC.h"

#include "savedata.h"

typedef struct {
    WiFiPlazaLobbyMinigameParticipants participants;
    SaveData *saveData;
    BOOL fromLobby;
    u32 voiceChatEnabled;
} WiFiPlazaLobbyMinigameManeneArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231134_H
