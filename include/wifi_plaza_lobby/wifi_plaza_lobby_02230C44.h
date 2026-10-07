#ifndef POKEPLATINUM_WIFI_PLAZA_LOBBY_02230C44_H
#define POKEPLATINUM_WIFI_PLAZA_LOBBY_02230C44_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0_sub1.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230C90_decl.h"

#include "savedata.h"

WiFiPlazaLobbyAppManager *WiFiPlazaLobby_AppManager_New(BOOL param0, SaveData *saveData, WiFiPlazaLobbyCooldownTimestamp *param2, WiFiPlazaLobbyState *param3, u32 heapID);
void WiFiPlazaLobby_AppManager_Free(WiFiPlazaLobbyAppManager *param0);
void WiFiPlazaLobby_AppManager_ConnectToWifiPlaza(WiFiPlazaLobbyAppManager *param0);
int WiFiPlazaLobby_AppManager_Update(WiFiPlazaLobbyAppManager *param0);
void WiFiPlazaLobby_AppManager_VBlankUpdate(WiFiPlazaLobbyAppManager *param0);

#endif // POKEPLATINUM_WIFI_PLAZA_LOBBY_02230C44_H
