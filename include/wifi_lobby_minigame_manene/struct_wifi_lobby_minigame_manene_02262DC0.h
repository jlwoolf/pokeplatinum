#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H

#include <nitro/fx/fx.h>

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int *unk_0C;
    WiFiLobbyMinigameManene3DObject *unk_10;
    WiFiLobbyMinigameManene3DObject *unk_14;
    u8 padding_18[8];
    VecFx32 unk_20;
    u8 padding_2C[24];
    WiFiLobbyMinigameManeneMotion unk_44;
    WiFiLobbyMinigameManeneMotion unk_5C;
    int unk_74;
    WiFiLobbyMinigameManeneResources *unk_78;
} WiFiLobbyMinigameManeneBallBounce;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H
