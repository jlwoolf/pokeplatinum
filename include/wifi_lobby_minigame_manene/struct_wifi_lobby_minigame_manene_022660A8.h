#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265AA4.h"

#include "sys_task_manager.h"

typedef struct {
    WiFiLobbyMinigameManeneResultsSprites unk_00;
    u8 padding_04[4];
    SysTask *unk_08;
    int *unk_0C;
    int *unk_10;
    int *unk_14;
    int unk_18;
    int unk_1C;
    u8 padding_20[4];
    int unk_24;
    BOOL unk_28;
    BOOL unk_2C;
    WiFiLobbyMinigameManeneResources *unk_30;
    WiFiLobbyMinigameManeneMotion unk_34[5];
} WiFiLobbyMinigameManeneResultsAnimation;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022660A8_H
