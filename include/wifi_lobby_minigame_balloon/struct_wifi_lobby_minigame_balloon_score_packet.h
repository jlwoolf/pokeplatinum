#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H

typedef struct {
    u8 netId;
    u8 multiplier;
    u16 balloonLevel;
    s32 baseScore;
    s32 score;
    u8 applied;
    u8 padding_0D[3];
} WiFiLobbyMinigameBalloonScorePacket;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H
