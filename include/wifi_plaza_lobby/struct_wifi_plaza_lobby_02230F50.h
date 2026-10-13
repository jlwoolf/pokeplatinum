#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230F50_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230F50_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231560.h"

#include "savedata.h"

typedef struct {
    const WiFiPlazaLobbyPlaceList *placeList;
    SaveData *saveData;
    WiFiPlazaLobbyTime currentTime;
    WiFiPlazaLobbyState *state;
} WiFiPlazaLobbyEarthAppArgs;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230F50_H
