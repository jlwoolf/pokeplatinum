#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_SUB2_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_SUB2_H

#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"

typedef struct {
    int frameCounter;
    int elapsedFrames;
    int level;
    int levelIndex;
    int score;
    int resultsStep;
    int pendingResultsStep;
    s16 stateTimer;
    s16 levelTimer;
    s16 playerTimers[4];
    int playerLevels[4];
    int levelFrameCounter;
    s16 ballVelocityX;
    s16 ballVelocityY;
    s16 ballMoveTimer;
    s16 ballMoveFrame;
    WiFiLobbyMinigameManeneMotion ballMotionX;
    WiFiLobbyMinigameManeneMotion ballMotionY;
    WiFiLobbyMinigameManeneMotion ballMotionAltX;
    WiFiLobbyMinigameManeneMotion ballMotionAltY;
    BOOL ballTilted;
    BOOL ballMotionDone;
    BOOL ballPushReady;
    BOOL ballPushActive;
    BOOL ballTouched;
    s16 ballPushVelocityX;
    s16 ballPushVelocityY;
} WiFiLobbyMinigameManeneRoundState;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02262A8C_SUB2_H
