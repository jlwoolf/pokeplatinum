#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_COMM_CMD_HANDLERS_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_COMM_CMD_HANDLERS_H

#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"

void WiFiLobbyMinigame_InitCommCmdResults(WiFiLobbyMinigameResultsScreen *param0);
void WiFiLobbyMinigame_InitCommCmdIntro(WiFiLobbyMinigameIntroScreen *param0);
int WiFiLobbyMinigame_CommCmdGetSize0(void);
int WiFiLobbyMinigame_CommCmdGetSize4(void);
void WiFiLobbyMinigame_CommCmdSetIntroResult(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigame_CommCmdSetPlayerReady(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigame_CommCmdSetPlayerNotReady(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigame_CommCmdSetAllReady(int param0, int param1, void *param2, void *param3);
void WiFiLobbyMinigame_CommCmdSetNotAllReady(int param0, int param1, void *param2, void *param3);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_COMM_CMD_HANDLERS_H
