#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_H

#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_app_decl.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_throw_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_final_scores.h"

#include "overlay_manager.h"

int WiFiLobbyMinigameBucket_Init(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameBucket_Main(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameBucket_Exit(ApplicationManager *appMan, int *param1);
void WiFiLobbyMinigameBucket_SetPlayerReady(WiFiLobbyMinigameBucketApp *param0);
void WiFiLobbyMinigameBucket_SetPlayerFinished(WiFiLobbyMinigameBucketApp *param0);
void WiFiLobbyMinigameBucket_HandleThrowResult(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketThrowData *param1, u32 param2);
void WiFiLobbyMinigameBucket_HandleThrowData(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketThrowData *param1, u32 param2);
void WiFiLobbyMinigameBucket_HandleScoreUpdate(WiFiLobbyMinigameBucketApp *param0, u32 param1, u32 param2);
void WiFiLobbyMinigameBucket_HandleFinalScores(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketFinalScores *param1, u32 param2);
void WiFiLobbyMinigameBucket_HandleStageChange(WiFiLobbyMinigameBucketApp *param0, u32 param1);
void WiFiLobbyMinigameBucket_HandleHit(WiFiLobbyMinigameBucketApp *param0, u32 param1, u32 param2);
void WiFiLobbyMinigameBucket_OnSyncReady(WiFiLobbyMinigameBucketApp *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_H
