#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265470_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265470_H

typedef struct {
    int state;
    BOOL active;
    void *objects[8];
    int timers[10];
    BOOL flags[10];
} WiFiLobbyMinigameManeneIntroStep;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_02265470_H
