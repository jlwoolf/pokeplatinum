#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_sparkle.h"

#include "sprite_system.h"

typedef struct {
    ManagedSprite *balloonSprite;
    ManagedSprite *shadowSprite;
    ManagedSprite *highlightSprite;
    fx32 angleOffset;
    u8 state;
    u8 phase;
    u8 timer;
    u8 timerThreshold;
    u8 balloonLevel;
    u8 active;
    u8 padding_16[2];
    s32 popDuration;
    s16 startX;
    s16 startY;
    fx32 velocityX;
    fx32 velocityY;
    fx32 x;
    fx32 y;
    WiFiLobbyMinigameBalloonSparkle sparkle;
} WiFiLobbyMinigameBalloonPlayerBalloon;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H
