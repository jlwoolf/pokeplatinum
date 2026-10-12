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
    u32 localPlayerIndex;
    int playerCount;
    int previousBallFrame;
    int ballAnimCycle;
    u8 padding_10[4];
    WiFiLobbyMinigameManeneResources *resources;
    u8 padding_18[4];
    ManagedSprite *playerSpritesLayer1[3];
    ManagedSprite *playerSpritesLayer2[3];
    ManagedSprite *playerSpritesLayer3[3];
    ManagedSprite *backgroundSprites[36];
    ManagedSprite *playerSprites[4];
    ManagedSprite *resultSprites2[2];
    ManagedSprite *resultSprites1[2];
    ManagedSprite *ballSprite;
    u16 playerRowIndex[4];
    u8 padding_E4[12];
    int blendValueA;
    int blendValueB;
    int ballAnimState;
    WiFiLobbyMinigameManene3DObject ballObject;
    WiFiLobbyMinigameManene3DObject ballObjects[3];
    WiFiLobbyMinigameManene3DObject introBallObject;
    WiFiLobbyMinigameManene3DObject decorationObjects[8];
    WiFiLobbyMinigameManene3DObject levelUpObject1;
    WiFiLobbyMinigameManene3DObject levelUpObject2;
    VecFx32 ballPosition;
    WiFiLobbyMinigameManeneTouchInput touchInput;
    Window messageWindow;
    Window playerNameWindows[4];
    WiFiLobbyMinigameManeneResultsAnimation resultsAnimation;
    WiFiLobbyMinigameManeneIntroSequence introSequence;
    WiFiLobbyMinigameManeneSparkle sparkles[8];
    WiFiLobbyMinigameManenePlayerEffect playerEffects[4];
    WiFiLobbyMinigameManeneRoundState roundState;
    WiFiLobbyMinigameManenePlayerState playerStates[4];
    u8 padding_2868[4];
    u32 gameSeed;
    int introScreenResult;
    BOOL otherPlayerFalling;
} WiFiLobbyMinigameManeneGame;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_H
