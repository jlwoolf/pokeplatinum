#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_SCORE_EX_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_SCORE_EX_H

typedef struct {
    u16 balloonLevel;
    u8 gaugeLevel;
    u8 syncState;
    u8 syncId;
    u8 padding_05[3];
} WiFiLobbyMinigameBalloonPacketScoreEx;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_SCORE_EX_H
