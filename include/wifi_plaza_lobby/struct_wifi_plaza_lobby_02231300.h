#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231300_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231300_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"

#include "savedata.h"

typedef struct {
    SaveData *saveData;
    WiFiPlazaLobbyState *state;
    BOOL forced;
} WiFiPlazaLobbyP2PMatchDisconnectArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231300_H
