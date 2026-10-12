#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226534C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226534C_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265470.h"

#include "sys_task_manager.h"

typedef struct {
    int currentStep;
    int *levelPtr;
    WiFiLobbyMinigameManeneIntroStep steps[5];
    SysTask *task;
    WiFiLobbyMinigameManeneResources *resources;
} WiFiLobbyMinigameManeneIntroSequence;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226534C_H
