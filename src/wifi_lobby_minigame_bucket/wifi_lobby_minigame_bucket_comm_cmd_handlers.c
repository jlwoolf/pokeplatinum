#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_comm_cmd_handlers.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket.h"
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_comm_cmd.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_app_decl.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_throw_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_final_scores.h"

#include "communication_system.h"
#include "comm_cmd.h"

void WiFiLobbyMinigameBucket_InitCommCmd(WiFiLobbyMinigameBucketApp *param0)
{
    CommCmd_Init(WiFiLobbyMinigameBucket_GetCommCmdTable(), WiFiLobbyMinigameBucket_GetCommCmdCount(), param0);
}

int WiFiLobbyMinigameBucket_CommCmd_Noop(void)
{
    return 0;
}

void WiFiLobbyMinigameBucket_CommCmd_PlayerReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    WiFiLobbyMinigameBucket_SetPlayerReady(v0);
}

void WiFiLobbyMinigameBucket_CommCmd_PlayerFinished(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    WiFiLobbyMinigameBucket_SetPlayerFinished(v0);
}

void WiFiLobbyMinigameBucket_CommCmd_Throw(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;

    WiFiLobbyMinigameBucket_HandleThrowData(v0, param2, param0);

    if (CommSys_CurNetId() == 0) {
        WiFiLobbyMinigameBucket_HandleThrowResult(v0, param2, param0);
    }
}

void WiFiLobbyMinigameBucket_CommCmd_Score(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;

    WiFiLobbyMinigameBucket_HandleScoreUpdate(v0, *((u32 *)param2), param0);
}

void WiFiLobbyMinigameBucket_CommCmd_FinalScores(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    WiFiLobbyMinigameBucket_HandleFinalScores(v0, param2, param0);
}

void WiFiLobbyMinigameBucket_CommCmd_Hit(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    u32 v1 = *((u32 *)param2);
    WiFiLobbyMinigameBucket_HandleHit(v0, v1, param0);
}

void WiFiLobbyMinigameBucket_CommCmd_SyncReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    WiFiLobbyMinigameBucket_OnSyncReady(v0);
}

void WiFiLobbyMinigameBucket_CommCmd_Stage(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBucketApp *v0 = param3;
    u32 v1 = *((u32 *)param2);

    if (param0 == 0) {
        WiFiLobbyMinigameBucket_HandleStageChange(v0, v1);
    }
}

int WiFiLobbyMinigameBucket_GetThrowDataSize(void)
{
    return sizeof(WiFiLobbyMinigameBucketThrowData);
}

int WiFiLobbyMinigameBucket_GetFinalScoresSize(void)
{
    return sizeof(WiFiLobbyMinigameBucketFinalScores);
}

int WiFiLobbyMinigameBucket_GetScoreSize(void)
{
    return sizeof(u32);
}

int WiFiLobbyMinigameBucket_GetStageSize(void)
{
    return sizeof(u32);
}
