#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H

#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_confetti.h"

typedef struct {
    BOOL unk_00;
    WiFiLobbyMinigameBalloonConfetti unk_04[36];
    WiFiLobbyMinigameBalloonConfetti unk_868[8];
    WiFiLobbyMinigameBalloonConfetti unk_928[3];
    u8 padding_970[4];
} WiFiLobbyMinigameBalloonConfettiManager;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_CONFETTI_MANAGER_H
