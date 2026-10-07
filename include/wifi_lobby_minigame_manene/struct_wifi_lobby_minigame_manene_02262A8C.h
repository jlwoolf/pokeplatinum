#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_H

#include <nitro/fx/fx.h>

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260490.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C_sub1.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C_sub2.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262D08.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022647BC.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226534C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022660A8.h"

#include "bg_window.h"
#include "sprite_system.h"

typedef struct {
    u32 unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    u8 padding_10[4];
    WiFiLobbyMinigameManeneResources *unk_14;
    u8 padding_18[4];
    ManagedSprite *unk_1C[3];
    ManagedSprite *unk_20[3];
    ManagedSprite *unk_24[3];
    ManagedSprite *unk_28[36];
    ManagedSprite *unk_B8[4];
    ManagedSprite *unk_C8[2];
    ManagedSprite *unk_D0[2];
    ManagedSprite *unk_D8;
    u16 unk_DC[4];
    u8 padding_E4[12];
    int unk_F0;
    int unk_F4;
    int unk_F8;
    WiFiLobbyMinigameManene3DObject unk_FC;
    WiFiLobbyMinigameManene3DObject unk_308[3];
    WiFiLobbyMinigameManene3DObject unk_92C;
    WiFiLobbyMinigameManene3DObject unk_B38[8];
    WiFiLobbyMinigameManene3DObject unk_1B98;
    WiFiLobbyMinigameManene3DObject unk_1DA4;
    VecFx32 unk_1FB0;
    WiFiLobbyMinigameManeneTouchInput unk_1FBC;
    Window unk_1FC8;
    Window unk_1FD8[4];
    WiFiLobbyMinigameManeneResultsAnimation unk_2018;
    WiFiLobbyMinigameManeneIntroSequence unk_20C4;
    WiFiLobbyMinigameManeneSparkle unk_214C[8];
    WiFiLobbyMinigameManenePlayerEffect unk_268C[4];
    WiFiLobbyMinigameManeneRoundState unk_279C;
    WiFiLobbyMinigameManenePlayerState unk_2858[4];
    u8 padding_2868[4];
    u32 unk_286C;
    int unk_2870;
    BOOL unk_2874;
} WiFiLobbyMinigameManeneGame;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_H
