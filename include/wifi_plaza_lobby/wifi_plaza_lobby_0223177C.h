#ifndef POKEPLATINUM_WIFI_PLAZA_LOBBY_0223177C_H
#define POKEPLATINUM_WIFI_PLAZA_LOBBY_0223177C_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223177C_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223185C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022318AC.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231908.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223199C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_022319FC.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231A58.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231AB4.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231B24.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231B80.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"

#include "enums.h"
#include "string_gf.h"

WiFiPlazaLobbyNews *WiFiPlazaLobby_News_New(u32 heapID);
void WiFiPlazaLobby_News_Free(WiFiPlazaLobbyNews *param0);
void WiFiPlazaLobby_News_Reset(WiFiPlazaLobbyNews *param0);
void WiFiPlazaLobby_News_SetPlazaInfo(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyTime *param1);
void WiFiPlazaLobby_News_SetResult(WiFiPlazaLobbyNews *param0, u32 param1, u32 param2, WiFiPlazaLobbyNewsResultFlags param3);
BOOL WiFiPlazaLobby_News_TakeResultFlag(WiFiPlazaLobbyNews *param0, u32 param1);
void WiFiPlazaLobby_News_SelectResult(WiFiPlazaLobbyNews *param0, u32 param1);
void WiFiPlazaLobby_News_AddDuoEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntry *param1);
void WiFiPlazaLobby_News_AddDuoEntryRanked(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsDuoEntryRanked *param1);
void WiFiPlazaLobby_News_AddMinigameEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameEntry *param1);
void WiFiPlazaLobby_News_AddMinigameQuickEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameQuickEntry *param1);
void WiFiPlazaLobby_News_AddFourTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntry *param1);
void WiFiPlazaLobby_News_AddFourTrainerEntryB(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsFourTrainerEntryB *param1);
void WiFiPlazaLobby_News_AddEventEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsEventEntry *param1);
void WiFiPlazaLobby_News_AddTrainerEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsTrainerEntry *param1, const WiFiPlazaLobbyNewsPlayerFlags *param2);
void WiFiPlazaLobby_News_AddMinigameResultEntry(WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsMinigameResultEntry *param1);
void WiFiPlazaLobby_News_ClearQueue(WiFiPlazaLobbyNews *param0);
BOOL WiFiPlazaLobby_News_GetPlazaInfo(const WiFiPlazaLobbyNews *param0, WiFiPlazaLobbyTime *param1);
BOOL WiFiPlazaLobby_News_IsResultSet(const WiFiPlazaLobbyNews *param0, u32 param1);
u32 WiFiPlazaLobby_News_GetResult(const WiFiPlazaLobbyNews *param0, u32 param1);
BOOL WiFiPlazaLobby_News_HasResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1);
BOOL WiFiPlazaLobby_News_HasNewResultFlag(const WiFiPlazaLobbyNews *param0, u32 param1);
BOOL WiFiPlazaLobby_News_IsCurrentResult(const WiFiPlazaLobbyNews *param0, u32 param1);
WiFiPlazaLobbyNewsState WiFiPlazaLobby_News_GetState(const WiFiPlazaLobbyNews *param0);
BOOL WiFiPlazaLobby_News_HasHeadline(const WiFiPlazaLobbyNews *param0);
int WiFiPlazaLobby_News_GetHeadlineType(const WiFiPlazaLobbyNews *param0);
BOOL WiFiPlazaLobby_News_FormatHeadline(const WiFiPlazaLobbyNews *param0, const WiFiPlazaLobbyNewsPlayerFlags *param1, int param2, String *param3, u32 heapID);
u32 WiFiPlazaLobby_News_GetHeadlineValue(const WiFiPlazaLobbyNews *param0, int param1, u32 param2);

#endif // POKEPLATINUM_WIFI_PLAZA_LOBBY_0223177C_H
