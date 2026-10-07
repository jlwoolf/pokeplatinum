#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H

#include <nitro/fx/fx.h>

#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_022671EC.h"

#include "easy3d_object.h"

typedef struct {
    Easy3DObject unk_00;
    Easy3DModel unk_78;
    Easy3DAnim unk_88[10];
    WiFiLobbyMinigameManeneMatrix unk_150;
    WiFiLobbyMinigameManeneQuaternion unk_190;
    WiFiLobbyMinigameManeneQuaternion unk_1A0;
    MtxFx43 unk_1B0;
    VecFx32 unk_1E0;
    BOOL unk_1EC;
    BOOL unk_1F0;
    int unk_1F4;
    int unk_1F8;
    f32 unk_1FC;
    f32 unk_200;
    f32 unk_204;
    f32 unk_208;
} WiFiLobbyMinigameManene3DObject;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226501C_H
