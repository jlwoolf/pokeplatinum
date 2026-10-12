#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_02261E10_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_02261E10_H

#include <nitro/fx/fx.h>

#include "constants/heap.h"

#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"

#include "enums.h"

WiFiLobbyMapObjectManager *wifi_lobby_map_02261E10(int param0, int param1, const WiFiLobbyMapGrid *param2, enum HeapID heapID, u32 heapID2);
void wifi_lobby_map_022621AC(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262210(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262298(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_022622A4(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_022622B0(WiFiLobbyMapObjectManager *param0, u32 param1, fx32 param2);
void wifi_lobby_map_022622EC(WiFiLobbyMapObjectManager *param0, u32 param1, const VecFx32 *param2);
void wifi_lobby_map_02262318(const WiFiLobbyMapObjectManager *param0, u32 param1, u32 param2, VecFx32 *param3);
BOOL wifi_lobby_map_02262374(WiFiLobbyMapObjectManager *param0, u32 param1);
BOOL wifi_lobby_map_0226239C(WiFiLobbyMapObjectManager *param0, u32 param1);
void wifi_lobby_map_022623C4(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2);
void wifi_lobby_map_022623F0(WiFiLobbyMapObjectManager *param0, u32 param1, u16 param2);
BOOL wifi_lobby_map_0226241C(const WiFiLobbyMapObjectManager *param0, u32 param1);
BOOL wifi_lobby_map_02262444(const WiFiLobbyMapObjectManager *param0, u32 param1);
void wifi_lobby_map_0226246C(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262478(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262484(WiFiLobbyMapObjectManager *param0, u8 param1, u8 param2);
void wifi_lobby_map_0226251C(WiFiLobbyMapObjectManager *param0, BOOL param1);
void wifi_lobby_map_022625D8(WiFiLobbyMapObjectManager *param0, fx32 param1);
void wifi_lobby_map_0226260C(WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262658(WiFiLobbyMapObjectManager *param0, int param1);
BOOL wifi_lobby_map_0226271C(const WiFiLobbyMapObjectManager *param0);
void wifi_lobby_map_02262724(WiFiLobbyMapObjectManager *param0, BOOL param1, fx32 param2);
BOOL wifi_lobby_map_02262754(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2, fx32 param3);
void wifi_lobby_map_0226278C(WiFiLobbyMapObjectManager *param0, fx32 param1);
void wifi_lobby_map_022627BC(WiFiLobbyMapObjectManager *param0, enum PlazaMinigame param1, u32 param2, BOOL param3, BOOL param4, BOOL param5);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_02261E10_H
