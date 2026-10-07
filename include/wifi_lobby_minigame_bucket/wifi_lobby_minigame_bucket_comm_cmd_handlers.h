#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_COMM_CMD_HANDLERS_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_COMM_CMD_HANDLERS_H

#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_app_decl.h"

void WiFiLobbyMinigameBucket_InitCommCmd(WiFiLobbyMinigameBucketApp *param0);
int WiFiLobbyMinigameBucket_CommCmd_Noop(void);
void WiFiLobbyMinigameBucket_CommCmd_PlayerReady(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_PlayerFinished(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_Throw(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_Score(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_FinalScores(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_Hit(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_SyncReady(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigameBucket_CommCmd_Stage(int param0, int param1, void *param2, void *param3);
int WiFiLobbyMinigameBucket_GetThrowDataSize(void);
int WiFiLobbyMinigameBucket_GetFinalScoresSize(void);
int WiFiLobbyMinigameBucket_GetScoreSize(void);
int WiFiLobbyMinigameBucket_GetStageSize(void);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_BUCKET_COMM_CMD_HANDLERS_H
