#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02260440.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226048C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260490.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260494.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260498.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"

#include "math_util.h"
#include "comm_cmd.h"

static void CommCmd_HandleSeed(int param0, int param1, void *param2, void *param3);
static void CommCmd_HandleStart(int param0, int param1, void *param2, void *param3);
static void CommCmd_HandlePlayerState(int param0, int param1, void *param2, void *param3);
static void CommCmd_HandleScore(int param0, int param1, void *param2, void *param3);
static void CommCmd_HandleNoop(int param0, int param1, void *param2, void *param3);
static int CommCmd_SizeNoop(void);
static int CommCmd_SizeSeed(void);
static int CommCmd_SizePlayerState(void);
static int CommCmd_SizeScore(void);
static int CommCmd_SizeScores(void);

static const CommCmdTable sCommCmdTable[] = {
    { CommCmd_HandleSeed, CommCmd_SizeSeed, NULL },
    { CommCmd_HandleStart, CommCmd_SizeNoop, NULL },
    { CommCmd_HandlePlayerState, CommCmd_SizePlayerState, NULL },
    { CommCmd_HandleScore, CommCmd_SizeScore, NULL },
    { CommCmd_HandleNoop, CommCmd_SizeScores, NULL }
};

static void CommCmd_HandleSeed(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameManeneApp *v0 = param3;

    v0->unk_14 = *((WiFiLobbyMinigameManeneSeed *)param2);

    LCRNG_SetSeed(v0->unk_14.seed);
    WiFiLobbyMinigameManene_SetStarted(v0);
}

static void CommCmd_HandleStart(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameManeneApp *v0 = param3;
    WiFiLobbyMinigameManene_SetRoundStarted(v0);
}

static void CommCmd_HandlePlayerState(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameManeneApp *v0 = param3;
    WiFiLobbyMinigameManenePlayerState *v1 = ((WiFiLobbyMinigameManenePlayerState *)param2);
    v0->unk_04->unk_2858[param0].state = v1->state;
}

static void CommCmd_HandleScore(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameManeneApp *v0 = param3;
    WiFiLobbyMinigameManeneScore *v1 = ((WiFiLobbyMinigameManeneScore *)param2);
    v0->unk_24.scores[param0].score = v1->score;
}

static void CommCmd_HandleNoop(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameManeneApp *v0 = param3;
}

static int CommCmd_SizeNoop(void)
{
    return 0;
}

static int CommCmd_SizeSeed(void)
{
    return sizeof(WiFiLobbyMinigameManeneSeed);
}

static int CommCmd_SizePlayerState(void)
{
    return sizeof(WiFiLobbyMinigameManenePlayerState);
}

static int CommCmd_SizeScore(void)
{
    return sizeof(WiFiLobbyMinigameManeneScore);
}

static int CommCmd_SizeScores(void)
{
    return sizeof(WiFiLobbyMinigameManeneScores);
}

const CommCmdTable *WiFiLobbyMinigameManene_GetCommCmdTable(void)
{
    return sCommCmdTable;
}

int WiFiLobbyMinigameManene_GetCommCmdCount(void)
{
    return sizeof(sCommCmdTable) / sizeof(CommCmdTable);
}

void WiFiLobbyMinigameManene_InitCommCmd(WiFiLobbyMinigameManeneApp *param0)
{
    CommCmd_Init(WiFiLobbyMinigameManene_GetCommCmdTable(), WiFiLobbyMinigameManene_GetCommCmdCount(), param0);
}
