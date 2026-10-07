#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_player_balloon.h"

typedef struct {
    WiFiLobbyMinigameBalloonPlayerBalloon unk_00[3];
    fx32 unk_E4;
    fx32 unk_E8;
    u32 unk_EC;
    u8 unk_F0;
    u8 unk_F1;
    u8 unk_F2;
    u8 unk_F3;
    u8 unk_F4;
    u8 padding_F5[3];
} WiFiLobbyMinigameBalloonPlayerBalloons;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_BALLOONS_H
