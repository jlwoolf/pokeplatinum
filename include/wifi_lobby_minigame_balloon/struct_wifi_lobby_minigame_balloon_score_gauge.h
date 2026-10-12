#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_GAUGE_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_GAUGE_H

typedef struct {
    int active;
    int gaugeLevel;
    s32 currentScore;
    s32 targetScore;
    s32 pendingScore;
    s32 step;
    s32 playerScores[4];
    int scrollFlip;
    u8 showRequest;
    u8 hideRequest;
    u8 padding_2E[2];
} WiFiLobbyMinigameBalloonScoreGauge;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_GAUGE_H
