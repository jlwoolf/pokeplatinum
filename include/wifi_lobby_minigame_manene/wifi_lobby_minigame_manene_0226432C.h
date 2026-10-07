#ifndef POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_0226432C_H
#define POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_0226432C_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

BOOL WiFiLobbyMinigameManene_TiltBall(WiFiLobbyMinigameManene3DObject *param0, int param1, int param2, int param3, int param4, f32 param5, BOOL param6);
BOOL WiFiLobbyMinigameManene_DecayBallTilt(WiFiLobbyMinigameManene3DObject *param0, f32 param1);
int WiFiLobbyMinigameManene_GetPlayerIndex(WiFiLobbyMinigameManeneApp *param0, int param1);
void WiFiLobbyMinigameManene_InitMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4);
BOOL WiFiLobbyMinigameManene_UpdateMotion(WiFiLobbyMinigameManeneMotion *param0);
void WiFiLobbyMinigameManene_InitLinearMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, s32 param3);
BOOL WiFiLobbyMinigameManene_UpdateLinearMotion(WiFiLobbyMinigameManeneMotion *param0);
void WiFiLobbyMinigameManene_SpawnSparkle(WiFiLobbyMinigameManeneGame *param0, s16 param1, s16 param2);
void WiFiLobbyMinigameManene_StartIntroAnimation(WiFiLobbyMinigameManeneGame *param0, BOOL *param1);
void WiFiLobbyMinigameManene_SetupIntroSequence(WiFiLobbyMinigameManeneGame *param0);
void WiFiLobbyMinigameManene_SetupResultsAnimation(WiFiLobbyMinigameManeneGame *param0);

#endif // POKEPLATINUM_WIFI_LOBBY_MINIGAME_MANENE_0226432C_H
