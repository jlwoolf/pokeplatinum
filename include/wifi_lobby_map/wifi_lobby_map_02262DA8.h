#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_02262DA8_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_02262DA8_H

#include "constants/heap.h"

#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_callbacks.h"

WiFiLobbyMapTaskManager *wifi_lobby_map_02262DA8(WiFiLobbyMapApp *param0, enum HeapID heapID);
void wifi_lobby_map_02262DF4(WiFiLobbyMapTaskManager *param0);
void wifi_lobby_map_02262E20(WiFiLobbyMapTaskManager *param0);
void wifi_lobby_map_02262E2C(WiFiLobbyMapTaskManager *param0);
void *wifi_lobby_map_02262E38(WiFiLobbyMapTask *param0);
void *wifi_lobby_map_02262E3C(WiFiLobbyMapTask *param0, u32 param1);
void wifi_lobby_map_02262E64(WiFiLobbyMapTask *param0);
void *wifi_lobby_map_02262E80(WiFiLobbyMapTask *param0);
u32 wifi_lobby_map_02262E84(const WiFiLobbyMapTask *param0);
void wifi_lobby_map_02262E88(WiFiLobbyMapTask *param0, u32 param1);
void wifi_lobby_map_02262E8C(WiFiLobbyMapTask *param0);
void wifi_lobby_map_02262E94(WiFiLobbyMapTaskManager *param0, u32 param1, const WiFiLobbyMapTaskCallbacks *param2, void *param3);
void wifi_lobby_map_02262EC0(WiFiLobbyMapTaskManager *param0, u32 param1, const WiFiLobbyMapTaskCallbacks *param2, void *param3);
void wifi_lobby_map_02262EEC(WiFiLobbyMapTaskManager *param0, u32 param1, BOOL param2);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_02262DA8_H
