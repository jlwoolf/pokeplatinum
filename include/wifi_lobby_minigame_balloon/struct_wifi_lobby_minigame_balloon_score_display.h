#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_text_oam.h"

#include "sprite_system.h"

typedef struct {
    ManagedSprite *unk_00;
    WiFiLobbyMinigameBalloonTextOAM unk_04[6][2];
    WiFiLobbyMinigameBalloonTextOAM unk_F4;
    WiFiLobbyMinigameBalloonTextOAM unk_108[6];
    u8 unk_180[6];
    u8 unk_186[6];
    u8 unk_18C[6];
    u8 unk_192[6];
    s8 unk_198[6];
    s8 unk_19E;
    u8 unk_19F;
    u8 unk_1A0;
    u8 padding_1A1[3];
} WiFiLobbyMinigameBalloonScoreDisplay;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H
