#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H

#include <nitro/fx/fx.h>

#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_022671EC.h"

#include "easy3d_object.h"

typedef struct {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[10];
    WiFiLobbyMinigameManeneMatrix rotationMatrix;
    WiFiLobbyMinigameManeneQuaternion rotation;
    WiFiLobbyMinigameManeneQuaternion previousRotation;
    MtxFx43 matrix;
    VecFx32 position;
    BOOL animationActive;
    BOOL modelLoaded;
    int animIndex;
    int tiltFramesRemaining;
    f32 tiltX;
    f32 tiltY;
    f32 tiltDecayX;
    f32 tiltDecayY;
} WiFiLobbyMinigameManene3DObject;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H
