#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_0225C858_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_0225C858_H

#include "constants/heap.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"

WiFiLobbyMapGrid *wifi_lobby_map_0225C858(enum HeapID heapID);
void wifi_lobby_map_0225C894(WiFiLobbyMapGrid *param0);
u16 wifi_lobby_map_0225C8A8(const WiFiLobbyMapGrid *param0);
BOOL wifi_lobby_map_0225C8AC(const WiFiLobbyMapGrid *param0, u16 param1, u16 param2);
u32 wifi_lobby_map_0225C8B8(const WiFiLobbyMapGrid *param0, u16 param1, u16 param2);
u32 wifi_lobby_map_0225C8C4(const WiFiLobbyMapGrid *param0, u16 param1, u16 param2);
BOOL wifi_lobby_map_0225C8D8(const WiFiLobbyMapGrid *param0, u32 param1, u16 *param2, u16 *param3, u32 param4);
BOOL wifi_lobby_map_0225C930(u32 param0);
BOOL wifi_lobby_map_0225C950(u32 param0);
BOOL wifi_lobby_map_0225C970(u32 param0);
BOOL wifi_lobby_map_0225C990(u32 param0);
const WiFi2DCharGrid *wifi_lobby_map_0225C9B0(const WiFiLobbyMapGrid *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_0225C858_H
