#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_comm_cmd.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_comm_cmd_handlers.h"

static const CommCmdTable sCommCmdTable[] = {
    { WiFiLobbyMinigameBucket_CommCmd_PlayerReady, WiFiLobbyMinigameBucket_CommCmd_Noop, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_PlayerFinished, WiFiLobbyMinigameBucket_CommCmd_Noop, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_Throw, WiFiLobbyMinigameBucket_GetThrowDataSize, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_Score, WiFiLobbyMinigameBucket_GetScoreSize, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_FinalScores, WiFiLobbyMinigameBucket_GetFinalScoresSize, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_Stage, WiFiLobbyMinigameBucket_GetStageSize, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_Hit, WiFiLobbyMinigameBucket_GetScoreSize, NULL },
    { WiFiLobbyMinigameBucket_CommCmd_SyncReady, WiFiLobbyMinigameBucket_CommCmd_Noop, NULL },
};

const CommCmdTable *WiFiLobbyMinigameBucket_GetCommCmdTable(void)
{
    return sCommCmdTable;
}

int WiFiLobbyMinigameBucket_GetCommCmdCount(void)
{
    return sizeof(sCommCmdTable) / sizeof(CommCmdTable);
}
