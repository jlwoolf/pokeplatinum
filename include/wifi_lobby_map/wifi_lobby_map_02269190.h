#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_02269190_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_02269190_H

#include "constants/heap.h"

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_camera_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_attraction_manager_decl.h"

WiFiLobbyMapAttractionManager *wifi_lobby_map_02269190(WiFiPlazaLobbyState *param0, WiFiLobbyMapGrid *param1, WiFiLobbyMapCamera *param2, WiFiLobbyMapActorManager *param3, enum HeapID heapID, u32 heapID2);
void wifi_lobby_map_02269204(WiFiLobbyMapAttractionManager *param0);
void wifi_lobby_map_02269220(WiFiLobbyMapAttractionManager *param0);
void wifi_lobby_map_02269240(WiFiLobbyMapAttractionManager *param0);
void wifi_lobby_map_02269268(WiFiLobbyMapAttractionManager *param0, u32 param1, u32 param2);
BOOL wifi_lobby_map_02269298(const WiFiLobbyMapAttractionManager *param0, u32 param1);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_02269190_H
