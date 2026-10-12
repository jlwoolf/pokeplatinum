#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H

typedef struct {
    fx32 value; // current interpolated value
    fx32 startValue; // start value
    fx32 velocity; // velocity (used by InitMotion)
    fx32 acceleration; // acceleration (InitMotion) or total delta (InitLinearMotion)
    int elapsedFrames; // elapsed frame
    int duration; // duration in frames
} WiFiLobbyMinigameManeneMotion;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H
