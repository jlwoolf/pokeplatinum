#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022647BC_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022647BC_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"

#include "sprite_system.h"

typedef struct {
    BOOL active;
    int state;
    ManagedSprite *sprites[3];
    WiFiLobbyMinigameManeneMotion motions[3][2];
    WiFiLobbyMinigameManeneResources *resources;
} WiFiLobbyMinigameManeneSparkle;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_022647BC_H
