#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPARKLE_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPARKLE_H

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprites[2];
    fx32 offsetX[2];
    fx32 offsetY[2];
    u8 state;
    u8 timer;
    u8 padding_1A[2];
} WiFiLobbyMinigameBalloonSparkle;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPARKLE_H
