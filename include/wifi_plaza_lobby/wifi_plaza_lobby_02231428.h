#ifndef POKEPLATINUM_WIFI_PLAZA_LOBBY_02231428_H
#define POKEPLATINUM_WIFI_PLAZA_LOBBY_02231428_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231560.h"

void WiFiPlazaLobby_Time_SetFromSeconds(WiFiPlazaLobbyTime *param0, const s64 *param1);
void WiFiPlazaLobby_Time_Add(const WiFiPlazaLobbyTime *param0, const WiFiPlazaLobbyTime *param1, WiFiPlazaLobbyTime *param2);
void WiFiPlazaLobby_Time_Subtract(const WiFiPlazaLobbyTime *param0, const WiFiPlazaLobbyTime *param1, WiFiPlazaLobbyTime *param2);
void WiFiPlazaLobby_Time_AddPlace(WiFiPlazaLobbyPlaceList *param0, u16 param1, u8 param2, BOOL param3);
u16 WiFiPlazaLobby_Time_GetPlaceCountry(const WiFiPlazaLobbyPlaceList *param0, u8 param1);
u8 WiFiPlazaLobby_Time_GetPlaceRegion(const WiFiPlazaLobbyPlaceList *param0, u8 param1);
BOOL WiFiPlazaLobby_Time_GetPlaceIsSelf(const WiFiPlazaLobbyPlaceList *param0, u8 param1);
BOOL WiFiPlazaLobby_Time_IsPlaceActive(const WiFiPlazaLobbyPlaceList *param0, u8 param1);
void WiFiPlazaLobby_Time_SetupModelGlobalLighting(void *param0);
BOOL WiFiPlazaLobby_Time_IsValidCountryRegion(u16 param0, u16 param1);
u32 WiFiPlazaLobby_Time_GetTypeIconIndex(int param0);
int WiFiPlazaLobby_Time_GetWFCErrorMessageID(int param0, int param1);
int WiFiPlazaLobby_Time_IsWFCErrorRetryable(int param0, int param1);
BOOL WiFiPlazaLobby_Time_HasWifiError(void);

#endif // POKEPLATINUM_WIFI_PLAZA_LOBBY_02231428_H
