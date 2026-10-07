#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H

typedef struct {
    fx32 unk_00; // current interpolated value
    fx32 unk_04; // start value
    fx32 unk_08; // velocity (used by InitMotion)
    fx32 unk_0C; // acceleration (InitMotion) or total delta (InitLinearMotion)
    int unk_10; // elapsed frame
    int unk_14; // duration in frames
} WiFiLobbyMinigameManeneMotion;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_MANENE_0226469C_H
