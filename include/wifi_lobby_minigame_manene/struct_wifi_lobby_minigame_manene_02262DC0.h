#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H

#include <nitro/fx/fx.h>

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

typedef struct {
    int state;
    int phase;
    int frameCounter;
    int *ballStatePtr;
    WiFiLobbyMinigameManene3DObject *ballObject;
    WiFiLobbyMinigameManene3DObject *ballObject2;
    u8 padding_18[8];
    VecFx32 ballPosition;
    u8 padding_2C[24];
    WiFiLobbyMinigameManeneMotion motionY;
    WiFiLobbyMinigameManeneMotion motionZ;
    int objectParam;
    WiFiLobbyMinigameManeneResources *resources;
} WiFiLobbyMinigameManeneBallBounce;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262DC0_H
