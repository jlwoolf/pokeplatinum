#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_pair.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_score.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_score_ex.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"

typedef struct {
    int unk_00;
    union {
        WiFiLobbyMinigameBalloonPacketPair unk_04_val1;
        WiFiLobbyMinigameBalloonPacketPair unk_04_val2;
        WiFiLobbyMinigameBalloonPacketPair unk_04_val3;
        WiFiLobbyMinigameBalloonScorePacket unk_04_val4;
        WiFiLobbyMinigameBalloonPacketScore unk_04_val5;
        WiFiLobbyMinigameBalloonPacketScoreEx unk_04_val6;
    };
} WiFiLobbyMinigameBalloonPacket;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H
