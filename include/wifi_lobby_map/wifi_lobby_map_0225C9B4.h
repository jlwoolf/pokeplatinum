#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_0225C9B4_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_0225C9B4_H

#include <nitro/fx/fx.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_decl.h"

WiFiLobbyMapActorManager *wifi_lobby_map_0225C9B4(u32 param0, u32 param1, const WiFiLobbyMapGrid *param2, u32 heapID, u32 heapID2);
void wifi_lobby_map_0225CA20(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CA44(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CA5C(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CAD4(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CAE0(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CAEC(WiFiLobbyMapActorManager *param0, int param1);
void wifi_lobby_map_0225CB08(WiFiLobbyMapActorManager *param0, int param1);
void wifi_lobby_map_0225CB1C(WiFiLobbyMapActorManager *param0, const WiFi2DCharEvent *param1);
WiFiLobbyMapActor *wifi_lobby_map_0225CB28(WiFiLobbyMapActorManager *param0, u32 param1);
WiFiLobbyMapActor *wifi_lobby_map_0225CB5C(WiFiLobbyMapActorManager *param0, u32 param1, u32 param2, u32 param3);
WiFiLobbyMapActor *wifi_lobby_map_0225CBB8(WiFiLobbyMapActorManager *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225CC54(WiFiLobbyMapActor *param0);
WiFiLobbyMapActor *wifi_lobby_map_0225CC70(WiFiLobbyMapActorManager *param0, u32 param1);
WiFiLobbyMapActor *wifi_lobby_map_0225CCAC(WiFiLobbyMapActorManager *param0);
WiFiLobbyMapActor *wifi_lobby_map_0225CCB0(WiFiLobbyMapActorManager *param0);
void wifi_lobby_map_0225CCB4(WiFiLobbyMapActor *param0, WiFi2DCharPosition param1);
void wifi_lobby_map_0225CD04(WiFiLobbyMapActor *param0, WiFi2DCharPosition param1, int param2);
WiFi2DCharPosition wifi_lobby_map_0225CD34(const WiFiLobbyMapActor *param0);
u32 wifi_lobby_map_0225CD60(const WiFiLobbyMapActor *param0, int param1);
void wifi_lobby_map_0225CD7C(WiFiLobbyMapActorManager *param0, const WiFiLobbyMapActor *param1, int param2, int param3);
void wifi_lobby_map_0225CDAC(WiFiLobbyMapActorManager *param0, const WiFiLobbyMapActor *param1, int param2, int param3);
void wifi_lobby_map_0225CDEC(WiFiLobbyMapActorManager *param0, WiFiLobbyMapActor *param1, int param2);
BOOL wifi_lobby_map_0225CE38(const WiFiLobbyMapActor *param0);
int wifi_lobby_map_0225CE3C(const WiFiLobbyMapActor *param0);
WiFiLobbyMapActor *wifi_lobby_map_0225CE40(WiFiLobbyMapActorManager *param0, const WiFiLobbyMapActor *param1);
BOOL wifi_lobby_map_0225CE70(const WiFiLobbyMapActor *param0);
const WiFiLobbyMapActor *wifi_lobby_map_0225CE7C(const WiFiLobbyMapActorManager *param0, u16 param1, u16 param2);
BOOL wifi_lobby_map_0225CEDC(const WiFiLobbyMapActor *param0, u16 param1, u16 param2);
BOOL wifi_lobby_map_0225CF4C(WiFiLobbyMapActorManager *param0, const WiFiLobbyMapActor *param1, u32 *param2, WiFi2DCharPosition *param3);
void wifi_lobby_map_0225D030(WiFiLobbyMapActor *param0, BOOL param1);
void wifi_lobby_map_0225D03C(WiFiLobbyMapActor *param0, const WiFi2DCharPosition *param1);
void wifi_lobby_map_0225D048(WiFiLobbyMapActor *param0, const VecFx32 *param1);
void wifi_lobby_map_0225D054(const WiFiLobbyMapActor *param0, VecFx32 *param1);
void wifi_lobby_map_0225D060(WiFiLobbyMapActor *param0, int param1);
void wifi_lobby_map_0225D06C(WiFiLobbyMapActor *param0, BOOL param1);
void wifi_lobby_map_0225D084(WiFiLobbyMapActor *param0, BOOL param1);
void wifi_lobby_map_0225D09C(WiFiLobbyMapActor *param0, BOOL param1);
void wifi_lobby_map_0225D0B4(WiFiLobbyMapActor *param0, u32 param1);
void wifi_lobby_map_0225D0C0(WiFiLobbyMapActor *param0, BOOL param1);
BOOL wifi_lobby_map_0225D0CC(const WiFiLobbyMapActor *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_0225C9B4_H
