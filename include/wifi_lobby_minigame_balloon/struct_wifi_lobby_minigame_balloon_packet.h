#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_pair.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_score.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet_score_ex.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"

typedef struct {
    int type;
    union {
        WiFiLobbyMinigameBalloonPacketPair statePair;
        WiFiLobbyMinigameBalloonPacketPair statePair2;
        WiFiLobbyMinigameBalloonPacketPair gameStatePair;
        WiFiLobbyMinigameBalloonScorePacket scorePacket;
        WiFiLobbyMinigameBalloonPacketScore packetScore;
        WiFiLobbyMinigameBalloonPacketScoreEx packetScoreEx;
    };
} WiFiLobbyMinigameBalloonPacket;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_PACKET_H
