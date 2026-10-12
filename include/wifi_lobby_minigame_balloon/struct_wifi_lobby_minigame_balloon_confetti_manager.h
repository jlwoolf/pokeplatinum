#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_confetti.h"

typedef struct {
    BOOL active;
    WiFiLobbyMinigameBalloonConfetti confetti[36];
    WiFiLobbyMinigameBalloonConfetti bursts[8];
    WiFiLobbyMinigameBalloonConfetti gaugeBursts[3];
    u8 padding_970[4];
} WiFiLobbyMinigameBalloonConfettiManager;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H
