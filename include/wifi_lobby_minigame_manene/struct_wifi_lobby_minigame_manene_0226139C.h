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
    WiFiLobbyMinigameManeneCountdown *unk_00;
    WiFiLobbyMinigameManeneGame *unk_04;
    BOOL unk_08;
    BOOL unk_0C;
    BOOL unk_10;
    WiFiLobbyMinigameManeneSeed unk_14;
    WiFiLobbyMinigameManeneScore unk_1C;
    WiFiLobbyMinigameManeneScores unk_24;
    u32 unk_44;
    WiFiLobbyMinigameManeneResources unk_48;
    u32 unk_78;
    WiFiLobbyMinigameIntroAnimation *unk_7C;
    WiFiPlazaLobbyMinigameManeneArgs *unk_80;
    WiFiLobbyMinigamePlayerContext unk_84;
    WiFiLobbyMinigameIntroScreen *unk_94;
    WiFiLobbyMinigameRanking unk_98;
    WiFiLobbyMinigameResultsScreen *unk_B0;
    int unk_B4[4];
    BOOL unk_C4;
} WiFiLobbyMinigameManeneApp;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226139C_H
