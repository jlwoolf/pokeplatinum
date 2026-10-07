#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_spawn.h"

#include "sprite_system.h"

typedef struct {
    BOOL unk_00;
    s16 unk_04;
    s16 unk_06;
    s32 unk_08;
    s16 unk_0C;
    u8 unk_0E;
    u8 padding_0F[1];
    ManagedSprite *unk_10;
    const WiFiLobbyMinigameBalloonSpawn *unk_14;
} WiFiLobbyMinigameBalloonPopEffect;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_POP_EFFECT_H
