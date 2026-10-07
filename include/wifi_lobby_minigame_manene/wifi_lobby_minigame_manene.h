#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_022604C4_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_022604C4_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"

#include "overlay_manager.h"

int WiFiLobbyMinigameManene_Init(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameManene_Main(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameManene_Exit(ApplicationManager *appMan, int *param1);
void WiFiLobbyMinigameManene_FreeGraphics(WiFiLobbyMinigameManeneApp *param0);
BOOL WiFiLobbyMinigameManene_IsHost(WiFiLobbyMinigameManeneApp *param0);
void WiFiLobbyMinigameManene_SetStarted(WiFiLobbyMinigameManeneApp *param0);
void WiFiLobbyMinigameManene_SetRoundStarted(WiFiLobbyMinigameManeneApp *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_022604C4_H
