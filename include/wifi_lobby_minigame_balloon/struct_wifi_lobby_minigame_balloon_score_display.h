#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_text_oam.h"

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprite;
    WiFiLobbyMinigameBalloonTextOAM digitReel[6][2];
    WiFiLobbyMinigameBalloonTextOAM labelText;
    WiFiLobbyMinigameBalloonTextOAM scoreDigits[6];
    u8 currentDigit[6];
    u8 targetDigit[6];
    u8 newDigits[6];
    u8 digitState[6];
    s8 digitDelay[6];
    s8 rollPause;
    u8 settledCount;
    u8 rollState;
    u8 padding_1A1[3];
} WiFiLobbyMinigameBalloonScoreDisplay;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_DISPLAY_H
