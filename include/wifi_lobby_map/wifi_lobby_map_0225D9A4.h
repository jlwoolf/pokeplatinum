#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0225C894_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0225CA20_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0225DEE8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_02260AD4_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_02261E10_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_022630A4_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_02263910.h"

#include "enums.h"
#include "list_menu.h"
#include "overlay_manager.h"
#include "string_gf.h"
#include "string_list.h"

int wifi_lobby_map_0225D9A4(ApplicationManager *appMan, int *param1);
int wifi_lobby_map_0225DB90(ApplicationManager *appMan, int *param1);
int wifi_lobby_map_0225DDF8(ApplicationManager *appMan, int *param1);
WiFiPlazaLobbyState *wifi_lobby_map_0225DEE8(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_02263910 *wifi_lobby_map_0225DEEC(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_0225CA20 *wifi_lobby_map_0225DEF0(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_02261E10 *wifi_lobby_map_0225DEF8(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_0225C894 *wifi_lobby_map_0225DF00(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_02260AD4 *wifi_lobby_map_0225DF08(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
UnkStruct_wifi_lobby_map_022630A4 *wifi_lobby_map_0225DF10(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DF18(UnkStruct_wifi_lobby_map_0225DEE8 *param0, BOOL param1);
u32 wifi_lobby_map_0225DF2C(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225DF30(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DF34(UnkStruct_wifi_lobby_map_0225DEE8 *param0, BOOL param1);
void wifi_lobby_map_0225DF38(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1);
void wifi_lobby_map_0225DF3C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1);
u8 wifi_lobby_map_0225DF40(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DF44(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DF4C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1, BOOL param2);
BOOL wifi_lobby_map_0225DF64(const UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1);
void wifi_lobby_map_0225DF6C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1, BOOL param2);
BOOL wifi_lobby_map_0225DF84(const UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1);
void wifi_lobby_map_0225DF8C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const String *param1);
void wifi_lobby_map_0225DF9C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const String *param1);
BOOL wifi_lobby_map_0225DFAC(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DFBC(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DFCC(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225DFDC(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DFEC(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225DFFC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const String *param1);
void wifi_lobby_map_0225E00C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);
void wifi_lobby_map_0225E020(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E034(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E044(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const String *param1, u32 param2);
const StringList *wifi_lobby_map_0225E054(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225E064(const UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);
void wifi_lobby_map_0225E074(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const ListMenuTemplate *param1, u16 param2, u16 param3);
void wifi_lobby_map_0225E0A4(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const ListMenuTemplate *param1, u16 param2, u16 param3, u8 param4, u8 param5, u8 param6);
u32 wifi_lobby_map_0225E0D4(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E0E4(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u16 *param1, u16 *param2);
void wifi_lobby_map_0225E0F4(UnkStruct_wifi_lobby_map_0225DEE8 *param0, BOOL param1);
void wifi_lobby_map_0225E104(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u8 param1, u8 param2, u8 param3, u8 param4);
void wifi_lobby_map_0225E12C(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E13C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, const String *param1, u8 param2, u8 param3);
void wifi_lobby_map_0225E14C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u16 param1, u16 param2, u16 param3, u16 param4);
void wifi_lobby_map_0225E164(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E194(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
int wifi_lobby_map_0225E1C4(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E1F8(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
String *wifi_lobby_map_0225E20C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, int param1, u32 param2);
void wifi_lobby_map_0225E21C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2, u32 param3, int param4);
void wifi_lobby_map_0225E234(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E27C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, enum PlazaMinigame param1, u32 param2);
void wifi_lobby_map_0225E28C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, int param1, u32 param2);
void wifi_lobby_map_0225E29C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2AC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2BC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2CC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2DC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2EC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E2FC(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, u32 param2);
void wifi_lobby_map_0225E30C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, int param2);
void wifi_lobby_map_0225E328(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1, BOOL param2);
void wifi_lobby_map_0225E378(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);
void wifi_lobby_map_0225E390(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E3D0(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
u32 wifi_lobby_map_0225E3E0(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225E3F0(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225E400(const UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E410(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225E420(const UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);
void wifi_lobby_map_0225E430(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E43C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, BOOL param1);
void wifi_lobby_map_0225E44C(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
BOOL wifi_lobby_map_0225E45C(UnkStruct_wifi_lobby_map_0225DEE8 *param0);
void wifi_lobby_map_0225E46C(UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);
BOOL wifi_lobby_map_0225E4AC(const UnkStruct_wifi_lobby_map_0225DEE8 *param0, u32 param1);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_0225D9A4_H
