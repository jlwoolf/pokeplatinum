#include "wifi_lobby_minigame/wifi_lobby_minigame_comm_cmd_handlers.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame_comm_cmd.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"

#include "comm_cmd.h"

void WiFiLobbyMinigame_InitCommCmdResults(WiFiLobbyMinigameResultsScreen *param0)
{
    CommCmd_Init(WiFiLobbyMinigame_GetCommCmdTable(), WiFiLobbyMinigame_GetCommCmdTableSize(), param0);
}

void WiFiLobbyMinigame_InitCommCmdIntro(WiFiLobbyMinigameIntroScreen *param0)
{
    CommCmd_Init(WiFiLobbyMinigame_GetCommCmdTable(), WiFiLobbyMinigame_GetCommCmdTableSize(), param0);
}

int WiFiLobbyMinigame_CommCmdGetSize0(void)
{
    return 0;
}

int WiFiLobbyMinigame_CommCmdGetSize4(void)
{
    return sizeof(u32);
}

void WiFiLobbyMinigame_CommCmdSetIntroResult(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigame_IntroScreenSetResult(param3, *((u32 *)param2));
}

void WiFiLobbyMinigame_CommCmdSetPlayerReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigame_ResultsScreenSetPlayerReady(param3, param0, 1);
}

void WiFiLobbyMinigame_CommCmdSetPlayerNotReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigame_ResultsScreenSetPlayerReady(param3, param0, 0);
}

void WiFiLobbyMinigame_CommCmdSetAllReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigame_ResultsScreenSetAllReady(param3, 1);
}

void WiFiLobbyMinigame_CommCmdSetNotAllReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigame_ResultsScreenSetAllReady(param3, 0);
}
