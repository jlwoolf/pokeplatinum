#ifndef POKEPLATINUM_WIFI_MENU_APP_02235060_H
#define POKEPLATINUM_WIFI_MENU_APP_02235060_H

#include "wifi_menu_app/struct_wifi_menu_app_02235130_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_022354D8.h"

#include "bg_window.h"
#include "narc.h"

void WiFiMenuAppBoard_Init(WiFiMenuAppBoard *param0, enum HeapID heapID, NARC *param2, BgConfig *param3, u32 param4, u32 param5);
void WiFiMenuAppBoard_Free(WiFiMenuAppBoard *param0);
BOOL WiFiMenuAppBoard_IsActive(const WiFiMenuAppBoard *param0);
u32 WiFiMenuAppBoard_Update(WiFiMenuAppBoard *param0);
void WiFiMenuAppBoard_UpdateSprites(WiFiMenuAppBoard *param0);
u8 WiFiMenuAppBoard_GetPlayerDirection(const WiFiMenuAppBoard *param0);
u32 WiFiMenuAppBoard_GetPlayerTileFlags(const WiFiMenuAppBoard *param0);
u32 WiFiMenuAppBoard_GetTileFlagsBelowPlayer(const WiFiMenuAppBoard *param0);
void WiFiMenuAppBoard_UpdateActorPriority(WiFiMenuAppBoard *param0, const WiFiMenuAppActor *param1);
void WiFiMenuAppBoard_ResetActors(WiFiMenuAppBoard *param0);
void WiFiMenuAppBoard_SetFlag(WiFiMenuAppBoard *param0, BOOL param1);
BOOL WiFiMenuAppBoard_GetFlag(const WiFiMenuAppBoard *param0);
WiFiMenuAppActor *WiFiMenuAppBoard_CreatePlayer(WiFiMenuAppBoard *param0, u32 param1);
WiFiMenuAppActor *WiFiMenuAppBoard_CreateActor(WiFiMenuAppBoard *param0, u32 param1, u8 param2);
void WiFiMenuAppBoard_RemoveActor(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
void WiFiMenuAppBoard_DestroyActor(WiFiMenuAppActor *param0);
u8 WiFiMenuAppBoard_GetActorField(const WiFiMenuAppActor *param0);
int WiFiMenuAppBoard_GetActorOppositeDirection(const WiFiMenuAppActor *param0);
void WiFiMenuAppBoard_SetActorAnim(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2);
void WiFiMenuAppBoard_RestoreActorCallback(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1);
void WiFiMenuAppBoard_SetActorState(WiFiMenuAppBoard *param0, WiFiMenuAppActor *param1, int param2);
void WiFiMenuAppBoard_SetPlayerPalette(WiFiMenuAppBoard *param0);
void WiFiMenuAppBoard_ResetPalette(WiFiMenuAppBoard *param0);
void WiFiMenuAppBoard_UpdatePalette(WiFiMenuAppBoard *param0);

#endif // POKEPLATINUM_WIFI_MENU_APP_02235060_H
