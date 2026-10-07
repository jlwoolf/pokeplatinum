#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H

#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"

#include "overlay_manager.h"

typedef struct {
    WiFiLobbyMinigamePlayerContext unk_00; // Shared WiFi lobby minigame player context.
    WiFiLobbyMinigameRanking unk_10; // Player ranking.
    ApplicationManager *appMan;
    u8 unk_2C[4]; // Net ID per connected player slot.
    u8 unk_30; // Number of connected players.
    u8 screenState;
    u8 padding_32[2];
    int balloonLevel;
    BOOL unk_38; // Results screen outcome.
    u8 voiceChatEnabled;
    u8 disconnected;
    u8 disconnectState;
    u8 padding_3F;
} WiFiLobbyMinigameBalloonContext;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONTEXT_H
