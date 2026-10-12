#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265D84_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265D84_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprite;
    int state;
    s16 angle;
    u8 padding_0A[6];
    int orbitCount;
    s16 baseX;
    s16 baseY;
    int radiusX;
    int radiusY;
    WiFiLobbyMinigameManeneMotion motionX;
    WiFiLobbyMinigameManeneMotion motionY;
} WiFiLobbyMinigameManeneResultsSprite;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265D84_H
