#ifndef POKEPLATINUM_WIFI_PLAZA_LOBBY_022343A8_H
#define POKEPLATINUM_WIFI_PLAZA_LOBBY_022343A8_H

#include <nitro/fx/fx.h>

#include "constants/heap.h"

#include "overlay063/struct_ov63_0222BEC0_decl.h"
#include "overlay063/struct_ov63_0222CC3C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02234548_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02234798_decl.h"

WiFiPlazaLobbyObjectManager *WiFiPlazaLobby_Object_ManagerNew(u32 param0, u32 param1, enum HeapID heapID, u32 heapID2);
void WiFiPlazaLobby_Object_ManagerFree(WiFiPlazaLobbyObjectManager *param0);
void WiFiPlazaLobby_Object_ManagerUpdate(WiFiPlazaLobbyObjectManager *param0);
void WiFiPlazaLobby_Object_ManagerDraw(WiFiPlazaLobbyObjectManager *param0);
void WiFiPlazaLobby_Object_ManagerResetRedraw(WiFiPlazaLobbyObjectManager *param0);
void WiFiPlazaLobby_Object_ManagerSetAlpha(WiFiPlazaLobbyObjectManager *param0, u32 param1);
WiFiPlazaLobbyObject *WiFiPlazaLobby_Object_New(WiFiPlazaLobbyObjectManager *param0, const UnkStruct_ov63_0222BEC0 *param1);
void WiFiPlazaLobby_Object_Free(WiFiPlazaLobbyObject *param0);
void WiFiPlazaLobby_Object_SetActive(WiFiPlazaLobbyObject *param0, BOOL param1);
void WiFiPlazaLobby_Object_SetLightEnableFlag(WiFiPlazaLobbyObject *param0, u32 param1);
BOOL WiFiPlazaLobby_Object_IsCulled(const WiFiPlazaLobbyObject *param0);
void WiFiPlazaLobby_Object_SetPositionFromTileCoords(WiFiPlazaLobbyObject *param0, const UnkStruct_ov63_0222CC3C *param1);
void WiFiPlazaLobby_Object_SetPosition(WiFiPlazaLobbyObject *param0, const VecFx32 *param1);
void WiFiPlazaLobby_Object_GetPosition(const WiFiPlazaLobbyObject *param0, VecFx32 *param1);
void WiFiPlazaLobby_Object_SetAnimation(WiFiPlazaLobbyObject *param0, int param1);
void WiFiPlazaLobby_Object_StartAnimationLoop(WiFiPlazaLobbyObject *param0, int param1);
void WiFiPlazaLobby_Object_StopAnimationLoop(WiFiPlazaLobbyObject *param0);
void WiFiPlazaLobby_Object_SetAnimationLoopStep(WiFiPlazaLobbyObject *param0, u8 param1);
void WiFiPlazaLobby_Object_SetVisible(WiFiPlazaLobbyObject *param0, BOOL param1);
BOOL WiFiPlazaLobby_Object_IsVisible(const WiFiPlazaLobbyObject *param0);

#endif // POKEPLATINUM_WIFI_PLAZA_LOBBY_022343A8_H
