#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_sparkle.h"

#include "sprite_system.h"

typedef struct {
    ManagedSprite *unk_00;
    ManagedSprite *unk_04;
    ManagedSprite *unk_08;
    fx32 unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 padding_16[2];
    s32 unk_18;
    s16 unk_1C;
    s16 unk_1E;
    fx32 unk_20;
    fx32 unk_24;
    fx32 unk_28;
    fx32 unk_2C;
    WiFiLobbyMinigameBalloonSparkle unk_30;
} WiFiLobbyMinigameBalloonPlayerBalloon;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOON_H
