#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloon.h"

typedef struct {
    WiFiLobbyMinigameBalloonPlayerBalloon balloons[3];
    fx32 angle;
    fx32 angleStep;
    u32 frameCounter;
    u8 slot;
    u8 idle;
    u8 pauseTimer;
    u8 rotationStep;
    u8 speedStage;
    u8 padding_F5[3];
} WiFiLobbyMinigameBalloonPlayerBalloons;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H
