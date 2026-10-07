#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231024_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231024_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0_sub1.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"

#include "savedata.h"

typedef struct {
    SaveData *saveData;
    WiFiPlazaLobbyState *unk_04;
    BOOL unk_08;
    WiFiPlazaLobbyCooldownTimestamp *unk_0C;
    BOOL unk_10;
} WiFiPlazaLobbyP2PMatchConnectArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02231024_H
