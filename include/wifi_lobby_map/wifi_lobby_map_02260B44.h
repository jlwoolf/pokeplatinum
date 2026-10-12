#ifndef POKEPLATINUM_WIFI_LOBBY_MAP_02260B44_H
#define POKEPLATINUM_WIFI_LOBBY_MAP_02260B44_H

#include <nitro/fx/fx.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_lobby_map/funcptr_wifi_lobby_map_02261C60.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_model_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_effect_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_character_decl.h"

WiFiLobbyMapModelManager *wifi_lobby_map_02260B44(u32 param0, u32 param1, u32 heapID, u32 heapID2);
void wifi_lobby_map_02260BB8(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260BE8(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260C50(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260CE0(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260CE4(WiFiLobbyMapModelManager *param0, int param1, int param2, u32 heapID, u32 heapID2);
void wifi_lobby_map_02260D80(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260DC8(WiFiLobbyMapModelManager *param0);
void wifi_lobby_map_02260DF4(WiFiLobbyMapModelManager *param0);
WiFiLobbyMapEffect *wifi_lobby_map_02260E20(WiFiLobbyMapModelManager *param0, int param1, int param2, const VecFx32 *param3);
void wifi_lobby_map_02260E8C(WiFiLobbyMapEffect *param0);
void wifi_lobby_map_02260EA0(WiFiLobbyMapEffect *param0, const VecFx32 *param1);
void wifi_lobby_map_02260EE4(WiFiLobbyMapEffect *param0, const VecFx32 *param1);
void wifi_lobby_map_02260F28(const WiFiLobbyMapEffect *param0, VecFx32 *param1);
void wifi_lobby_map_02260F38(WiFiLobbyMapEffect *param0, BOOL param1);
BOOL wifi_lobby_map_02260F44(WiFiLobbyMapEffect *param0);
BOOL wifi_lobby_map_02260F5C(WiFiLobbyMapEffect *param0);
void wifi_lobby_map_02260F74(WiFiLobbyMapEffect *param0, u16 param1);
BOOL wifi_lobby_map_02260F80(const WiFiLobbyMapEffect *param0);
BOOL wifi_lobby_map_02260F88(const WiFiLobbyMapEffect *param0);
WiFiLobbyMapCharacter *wifi_lobby_map_02260F90(WiFiLobbyMapModelManager *param0, int param1, u32 param2, u32 param3);
void wifi_lobby_map_02261058(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1);
int wifi_lobby_map_022610B8(const WiFiLobbyMapCharacter *param0);
void wifi_lobby_map_022610BC(WiFiLobbyMapCharacter *param0, WiFi2DCharPosition param1);
WiFi2DCharPosition wifi_lobby_map_022610E4(const WiFiLobbyMapCharacter *param0);
void wifi_lobby_map_0226110C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, int param3);
void wifi_lobby_map_0226111C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, int param3, UnkFuncPtr_wifi_lobby_map_02261C60 param4);
void wifi_lobby_map_02261220(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2);
void wifi_lobby_map_0226128C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1);
BOOL wifi_lobby_map_022612B4(const WiFiLobbyMapModelManager *param0, const WiFiLobbyMapCharacter *param1, int param2);
void wifi_lobby_map_022612F0(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, fx32 param3);
BOOL wifi_lobby_map_02261348(const WiFiLobbyMapCharacter *param0, int param1);
fx32 wifi_lobby_map_02261368(const WiFiLobbyMapCharacter *param0, int param1);
void wifi_lobby_map_0226138C(WiFiLobbyMapCharacter *param0, BOOL param1);
void wifi_lobby_map_02261398(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, u32 param2);
void wifi_lobby_map_022613C0(WiFiLobbyMapCharacter *param0, fx32 param1);
void wifi_lobby_map_022613C8(WiFiLobbyMapCharacter *param0, u8 param1, u8 param2);
void wifi_lobby_map_022613E0(WiFiLobbyMapCharacter *param0);
void wifi_lobby_map_022613E8(WiFiLobbyMapCharacter *param0, fx32 param1, fx32 param2, fx32 param3);

#endif // POKEPLATINUM_WIFI_LOBBY_MAP_02260B44_H
