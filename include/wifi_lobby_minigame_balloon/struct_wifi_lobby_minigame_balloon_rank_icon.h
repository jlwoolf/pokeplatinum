#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_RANK_ICON_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_RANK_ICON_H

#include "sprite_system.h"

typedef struct {
    ManagedSprite *sprite;
    u8 anim;
    u8 state;
    u8 slot;
    u8 padding_07;
    s16 progress;
    u8 padding_0A[2];
} WiFiLobbyMinigameBalloonRankIcon;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_RANK_ICON_H
