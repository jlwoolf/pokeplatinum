#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_spawn.h"

#include "sprite_system.h"

typedef struct {
    BOOL active;
    s16 netId;
    s16 balloonLevel;
    s32 score;
    s16 delay;
    u8 popType;
    u8 padding_0F[1];
    ManagedSprite *sprite;
    const WiFiLobbyMinigameBalloonSpawn *spawn;
} WiFiLobbyMinigameBalloonPopEffect;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H
