#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H

#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"

#include "overlay_manager.h"

typedef struct {
    WiFiLobbyMinigamePlayerContext playerContext; // Shared WiFi lobby minigame player context.
    WiFiLobbyMinigameRanking ranking; // Player ranking.
    ApplicationManager *appMan;
    u8 netIds[4]; // Net ID per connected player slot.
    u8 playerCount; // Number of connected players.
    u8 screenState;
    u8 padding_32[2];
    int balloonLevel;
    BOOL results; // Results screen outcome.
    u8 voiceChatEnabled;
    u8 disconnected;
    u8 disconnectState;
    u8 padding_3F;
} WiFiLobbyMinigameBalloonContext;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H
