#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222DCE0_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222DCE0_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0_sub1.h"

#include "savedata.h"

typedef struct {
    WiFiPlazaLobbyCooldownTimestamp *cooldownTimestamp;
    SaveData *saveData;
    BOOL wifiMenuResult;
} WiFiPlazaLobbyAppArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0222DCE0_H
