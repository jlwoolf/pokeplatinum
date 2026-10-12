#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_H

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprite;
    fx32 radius;
    fx32 radiusVelocity;
    fx32 angle;
    fx32 angleVelocity;
    s16 lifetime;
    u8 padding_16[2];
} WiFiLobbyMinigameBalloonConfetti;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_H
