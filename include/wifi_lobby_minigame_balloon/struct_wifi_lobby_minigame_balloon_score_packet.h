#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    s32 unk_04;
    s32 unk_08;
    u8 unk_0C;
    u8 padding_0D[3];
} WiFiLobbyMinigameBalloonScorePacket;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SCORE_PACKET_H
