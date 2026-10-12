#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPAWN_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPAWN_H

typedef struct {
    s16 x;
    s16 y;
    u16 anim;
    u8 palette;
    u8 direction;
    u8 padding_08[2];
} WiFiLobbyMinigameBalloonSpawn;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SPAWN_H
