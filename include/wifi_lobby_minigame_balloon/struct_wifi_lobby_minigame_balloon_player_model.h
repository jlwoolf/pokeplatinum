#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H

#include "easy3d_object.h"

typedef struct {
    Easy3DModel unk_00;
    Easy3DObject unk_10;
    Easy3DModel unk_88[4];
    struct {
        int unk_00;
        Easy3DObject unk_04;
        Easy3DAnim unk_7C;
    } unk_C8[8][4];
} WiFiLobbyMinigameBalloonPlayerModel;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H
