#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H

#include "easy3d_object.h"

typedef struct {
    Easy3DModel model;
    Easy3DObject object;
    Easy3DModel popModels[4];
    struct {
        int active;
        Easy3DObject object;
        Easy3DAnim anim;
    } popAnims[8][4];
} WiFiLobbyMinigameBalloonPlayerModel;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PLAYER_MODEL_H
