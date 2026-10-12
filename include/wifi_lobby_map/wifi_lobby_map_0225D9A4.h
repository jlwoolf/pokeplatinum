#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_camera_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_args.h"

#include "enums.h"
#include "list_menu.h"
#include "overlay_manager.h"
#include "string_gf.h"
#include "string_list.h"

int wifi_lobby_map_0225D9A4(ApplicationManager *appMan, int *param1);
int wifi_lobby_map_0225DB90(ApplicationManager *appMan, int *param1);
int wifi_lobby_map_0225DDF8(ApplicationManager *appMan, int *param1);
WiFiPlazaLobbyState *wifi_lobby_map_0225DEE8(WiFiLobbyMapApp *param0);
WiFiLobbyMapArgs *wifi_lobby_map_0225DEEC(WiFiLobbyMapApp *param0);
WiFiLobbyMapActorManager *wifi_lobby_map_0225DEF0(WiFiLobbyMapApp *param0);
WiFiLobbyMapObjectManager *wifi_lobby_map_0225DEF8(WiFiLobbyMapApp *param0);
WiFiLobbyMapGrid *wifi_lobby_map_0225DF00(WiFiLobbyMapApp *param0);
WiFiLobbyMapCamera *wifi_lobby_map_0225DF08(WiFiLobbyMapApp *param0);
WiFiLobbyMapTaskManager *wifi_lobby_map_0225DF10(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DF18(WiFiLobbyMapApp *param0, BOOL param1);
u32 wifi_lobby_map_0225DF2C(const WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225DF30(const WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DF34(WiFiLobbyMapApp *param0, BOOL param1);
void wifi_lobby_map_0225DF38(WiFiLobbyMapApp *param0, u8 param1);
void wifi_lobby_map_0225DF3C(WiFiLobbyMapApp *param0, u8 param1);
u8 wifi_lobby_map_0225DF40(const WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DF44(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DF4C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2);
BOOL wifi_lobby_map_0225DF64(const WiFiLobbyMapApp *param0, u8 param1);
void wifi_lobby_map_0225DF6C(WiFiLobbyMapApp *param0, u8 param1, BOOL param2);
BOOL wifi_lobby_map_0225DF84(const WiFiLobbyMapApp *param0, u8 param1);
void wifi_lobby_map_0225DF8C(WiFiLobbyMapApp *param0, const String *param1);
void wifi_lobby_map_0225DF9C(WiFiLobbyMapApp *param0, const String *param1);
BOOL wifi_lobby_map_0225DFAC(const WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DFBC(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DFCC(WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225DFDC(const WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DFEC(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225DFFC(WiFiLobbyMapApp *param0, const String *param1);
void wifi_lobby_map_0225E00C(WiFiLobbyMapApp *param0, u32 param1);
void wifi_lobby_map_0225E020(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E034(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E044(WiFiLobbyMapApp *param0, const String *param1, u32 param2);
const StringList *wifi_lobby_map_0225E054(const WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225E064(const WiFiLobbyMapApp *param0, u32 param1);
void wifi_lobby_map_0225E074(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3);
void wifi_lobby_map_0225E0A4(WiFiLobbyMapApp *param0, const ListMenuTemplate *param1, u16 param2, u16 param3, u8 param4, u8 param5, u8 param6);
u32 wifi_lobby_map_0225E0D4(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E0E4(WiFiLobbyMapApp *param0, u16 *param1, u16 *param2);
void wifi_lobby_map_0225E0F4(WiFiLobbyMapApp *param0, BOOL param1);
void wifi_lobby_map_0225E104(WiFiLobbyMapApp *param0, u8 param1, u8 param2, u8 param3, u8 param4);
void wifi_lobby_map_0225E12C(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E13C(WiFiLobbyMapApp *param0, const String *param1, u8 param2, u8 param3);
void wifi_lobby_map_0225E14C(WiFiLobbyMapApp *param0, u16 param1, u16 param2, u16 param3, u16 param4);
void wifi_lobby_map_0225E164(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E194(WiFiLobbyMapApp *param0);
int wifi_lobby_map_0225E1C4(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E1F8(WiFiLobbyMapApp *param0);
String *wifi_lobby_map_0225E20C(WiFiLobbyMapApp *param0, int param1, u32 param2);
void wifi_lobby_map_0225E21C(WiFiLobbyMapApp *param0, u32 param1, u32 param2, u32 param3, int param4);
void wifi_lobby_map_0225E234(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E27C(WiFiLobbyMapApp *param0, enum PlazaMinigame param1, u32 param2);
void wifi_lobby_map_0225E28C(WiFiLobbyMapApp *param0, int param1, u32 param2);
void wifi_lobby_map_0225E29C(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2AC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2BC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2CC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2DC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2EC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2FC(WiFiLobbyMapApp *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E30C(WiFiLobbyMapApp *param0, u32 param1, int param2);
void wifi_lobby_map_0225E328(WiFiLobbyMapApp *param0, u32 param1, BOOL param2);
void wifi_lobby_map_0225E378(WiFiLobbyMapApp *param0, u32 param1);
void wifi_lobby_map_0225E390(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E3D0(WiFiLobbyMapApp *param0);
u32 wifi_lobby_map_0225E3E0(const WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225E3F0(const WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225E400(const WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E410(WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225E420(const WiFiLobbyMapApp *param0, u32 param1);
void wifi_lobby_map_0225E430(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E43C(WiFiLobbyMapApp *param0, BOOL param1);
void wifi_lobby_map_0225E44C(WiFiLobbyMapApp *param0);
BOOL wifi_lobby_map_0225E45C(WiFiLobbyMapApp *param0);
void wifi_lobby_map_0225E46C(WiFiLobbyMapApp *param0, u32 param1);
BOOL wifi_lobby_map_0225E4AC(const WiFiLobbyMapApp *param0, u32 param1);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H
