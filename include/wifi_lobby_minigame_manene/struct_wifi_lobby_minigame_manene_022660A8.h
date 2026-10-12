#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265AA4.h"

#include "sys_task_manager.h"

typedef struct {
    WiFiLobbyMinigameManeneResultsSprites sprites;
    u8 padding_04[4];
    SysTask *task;
    int *resultsStepPtr;
    int *blendValuePtrA;
    int *blendValuePtrB;
    int stepTimer;
    int step;
    u8 padding_20[4];
    int scrollState;
    BOOL scrollingIn;
    BOOL scrollOn;
    WiFiLobbyMinigameManeneResources *resources;
    WiFiLobbyMinigameManeneMotion scrollMotions[5];
} WiFiLobbyMinigameManeneResultsAnimation;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H
