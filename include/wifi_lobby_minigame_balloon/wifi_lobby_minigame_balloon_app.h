#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_BALLOON_APP_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_BALLOON_APP_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game_decl.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet.h"

#include "overlay_manager.h"

int WiFiLobbyMinigameBalloon_AppInit(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameBalloon_AppMain(ApplicationManager *appMan, int *param1);
int WiFiLobbyMinigameBalloon_AppExit(ApplicationManager *appMan, int *param1);
void WiFiLobbyMinigameBalloon_CreateParticleEmitter(WiFiLobbyMinigameBalloonGame *param0, int param1);
BOOL WiFiLobbyMinigameBalloon_SpawnBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1);
BOOL WiFiLobbyMinigameBalloon_IsLocalPlayer(WiFiLobbyMinigameBalloonGame *param0);
void WiFiLobbyMinigameBalloon_QueueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1, const WiFiLobbyMinigameBalloonPacket *param2);
WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueReceivedPacket(WiFiLobbyMinigameBalloonGame *param0, int param1);
void WiFiLobbyMinigameBalloon_QueueSendPacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
WiFiLobbyMinigameBalloonPacket *WiFiLobbyMinigameBalloon_DequeueSendPacket(WiFiLobbyMinigameBalloonGame *param0);
int WiFiLobbyMinigameBalloon_GetBalloonLevel(WiFiLobbyMinigameBalloonGame *param0);
int WiFiLobbyMinigameBalloon_GetPlayerSlot(WiFiLobbyMinigameBalloonGame *param0, int param1);
int WiFiLobbyMinigameBalloon_GetPlayerIndex(WiFiLobbyMinigameBalloonGame *param0, int param1);
void WiFiLobbyMinigameBalloon_StartSync(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_BALLOON_APP_H
