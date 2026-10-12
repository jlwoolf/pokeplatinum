#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226139C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226139C_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231134.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_animation_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226048C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260494.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260498.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A44.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"

typedef struct {
    WiFiLobbyMinigameManeneCountdown *countdown;
    WiFiLobbyMinigameManeneGame *game;
    BOOL started;
    BOOL roundStarted;
    BOOL roundEnded;
    WiFiLobbyMinigameManeneSeed seedData;
    WiFiLobbyMinigameManeneScore score;
    WiFiLobbyMinigameManeneScores scores;
    u32 netId;
    WiFiLobbyMinigameManeneResources resources;
    u32 gameSeed;
    WiFiLobbyMinigameIntroAnimation *introAnimation;
    WiFiPlazaLobbyMinigameManeneArgs *args;
    WiFiLobbyMinigamePlayerContext playerContext;
    WiFiLobbyMinigameIntroScreen *introScreen;
    WiFiLobbyMinigameRanking ranking;
    WiFiLobbyMinigameResultsScreen *resultsScreen;
    int playerNetIds[4];
    BOOL replayRequested;
} WiFiLobbyMinigameManeneApp;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226139C_H
