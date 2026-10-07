#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_H

#include "overlay066/struct_ov66_02230DBC.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_animation_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"

#include "savedata.h"
#include "sprite.h"
#include "trainer_info.h"

void WiFiLobbyMinigame_InitPlayerContext(WiFiLobbyMinigamePlayerContext *param0, BOOL param1, SaveData *saveData, BOOL param3, UnkStruct_ov66_02230DBC *param4);
u32 WiFiLobbyMinigame_GetPlayerIndex(const WiFiLobbyMinigamePlayerContext *param0, u32 param1);
u32 WiFiLobbyMinigame_GetNetIdByIndex(const WiFiLobbyMinigamePlayerContext *param0, u32 param1);
BOOL WiFiLobbyMinigame_IsPlayerReady(const WiFiLobbyMinigamePlayerContext *param0, u32 param1);
TrainerInfo *WiFiLobbyMinigame_GetTrainerInfo(const WiFiLobbyMinigamePlayerContext *param0, u32 param1);
WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen0(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID);
WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen1(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID);
WiFiLobbyMinigameIntroScreen *WiFiLobbyMinigame_CreateIntroScreen2(const WiFiLobbyMinigamePlayerContext *param0, u32 heapID);
void WiFiLobbyMinigame_FreeIntroScreen(WiFiLobbyMinigameIntroScreen *param0);
BOOL WiFiLobbyMinigame_IntroScreenIsDone(const WiFiLobbyMinigameIntroScreen *param0);
int WiFiLobbyMinigame_IntroScreenGetResult(const WiFiLobbyMinigameIntroScreen *param0);
WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen0(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID);
WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen1(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID);
WiFiLobbyMinigameResultsScreen *WiFiLobbyMinigame_CreateResultsScreen2(const WiFiLobbyMinigamePlayerContext *param0, const WiFiLobbyMinigameRanking *param1, u32 heapID);
void WiFiLobbyMinigame_FreeResultsScreen(WiFiLobbyMinigameResultsScreen *param0);
BOOL WiFiLobbyMinigame_ResultsScreenIsDone(const WiFiLobbyMinigameResultsScreen *param0);
BOOL WiFiLobbyMinigame_ResultsScreenGetResult(const WiFiLobbyMinigameResultsScreen *param0);
void WiFiLobbyMinigame_InitRanking(WiFiLobbyMinigameRanking *param0, u32 param1);
void WiFiLobbyMinigame_IntroScreenSetResult(WiFiLobbyMinigameIntroScreen *param0, int param1);
void WiFiLobbyMinigame_ResultsScreenSetPlayerReady(WiFiLobbyMinigameResultsScreen *param0, u32 param1, BOOL param2);
void WiFiLobbyMinigame_ResultsScreenSetAllReady(WiFiLobbyMinigameResultsScreen *param0, BOOL param1);
BOOL WiFiLobbyMinigame_CheckDisconnected(WiFiLobbyMinigamePlayerContext *param0);
BOOL WiFiLobbyMinigame_HandleDisconnect(const WiFiLobbyMinigamePlayerContext *param0);
WiFiLobbyMinigameIntroAnimation *WiFiLobbyMinigame_CreateIntroAnimation(SpriteList *param0, u32 heapID);
void WiFiLobbyMinigame_FreeIntroAnimation(WiFiLobbyMinigameIntroAnimation *param0);
int WiFiLobbyMinigame_GetIntroAnimationPaletteOffset(WiFiLobbyMinigameIntroAnimation *param0);
void WiFiLobbyMinigame_StartIntroAnimationRoll(WiFiLobbyMinigameIntroAnimation *param0);
void WiFiLobbyMinigame_StartIntroAnimationPop(WiFiLobbyMinigameIntroAnimation *param0);
BOOL WiFiLobbyMinigame_IntroAnimationIsDone(const WiFiLobbyMinigameIntroAnimation *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_H
