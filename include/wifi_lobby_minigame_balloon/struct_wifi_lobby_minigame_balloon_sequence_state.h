#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SEQUENCE_STATE_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SEQUENCE_STATE_H

typedef struct {
    int sequenceIndex;
    u8 padding_04[8];
    int step;
    int unk_10;
    int delay;
    u8 syncId;
    u8 padding_19[3];
} WiFiLobbyMinigameBalloonSequenceState;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BALLOON_SEQUENCE_STATE_H
