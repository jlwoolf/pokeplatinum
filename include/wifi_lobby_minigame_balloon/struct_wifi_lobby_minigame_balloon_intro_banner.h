#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_INTRO_BANNER_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_INTRO_BANNER_H

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprite;
    s16 state;
    s16 timer;
    s16 unk_08;
    s16 unk_0A;
    int x;
    int y;
    int touchHeld;
    int touchPressed;
    BOOL finished;
} WiFiLobbyMinigameBalloonIntroBanner;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_INTRO_BANNER_H
