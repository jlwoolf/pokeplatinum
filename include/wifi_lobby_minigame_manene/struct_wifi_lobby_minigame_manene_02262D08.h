#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

#include "sprite_system.h"

typedef struct {
    int unk_00;
    int unk_04;
    u8 padding_08[4];
    ManagedSprite *unk_0C;
    WiFiLobbyMinigameManeneMotion unk_10;
    int unk_28;
    int *unk_2C;
    BOOL unk_30;
    WiFiLobbyMinigameManene3DObject *unk_34;
    WiFiLobbyMinigameManene3DObject *unk_38;
    WiFiLobbyMinigameManeneResources *unk_3C;
    int unk_40;
} WiFiLobbyMinigameManenePlayerEffect;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262D08_H
