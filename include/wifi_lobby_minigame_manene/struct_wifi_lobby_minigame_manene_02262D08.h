#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

#include "sprite_system.h"

typedef struct {
    int state;
    int phase;
    u8 padding_08[4];
    ManagedSprite *sprite;
    WiFiLobbyMinigameManeneMotion scaleMotion;
    int savedLevel;
    int *levelPtr;
    BOOL active;
    WiFiLobbyMinigameManene3DObject *objectA;
    WiFiLobbyMinigameManene3DObject *objectB;
    WiFiLobbyMinigameManeneResources *resources;
    int objectParam;
} WiFiLobbyMinigameManenePlayerEffect;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H
