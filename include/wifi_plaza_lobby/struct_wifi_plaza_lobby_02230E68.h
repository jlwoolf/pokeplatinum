#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230E68_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230E68_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_args.h"

#include "savedata.h"

typedef struct {
    SaveData *saveData;
    int unk_04;
    int unk_08;
    WiFiLobbyMapArgs unk_0C;
    int unk_18;
    WiFiPlazaLobbyState *unk_1C;
} WiFiPlazaLobbyMainAppArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230E68_H
