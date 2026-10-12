#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_OPPONENT_BALLOON_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_OPPONENT_BALLOON_H

#include "sprite_system.h"

typedef struct {
    ManagedSprite *balloonSprite;
    ManagedSprite *shadowSprite;
    fx32 x;
    fx32 y;
    s16 targetY;
    u8 balloonLevel;
    u8 state;
    u8 timer;
    u8 active;
    s16 delay;
} WiFiLobbyMinigameBalloonOpponentBalloon;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_OPPONENT_BALLOON_H
