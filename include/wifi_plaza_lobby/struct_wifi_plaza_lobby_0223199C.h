#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0223199C_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0223199C_H

#include "enums.h"
#include "trainer_info.h"

typedef struct {
    enum PlazaMinigame minigame;
    u32 count;
    const TrainerInfo *trainerInfo;
    u16 slot;
} WiFiPlazaLobbyNewsMinigameQuickEntry;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_0223199C_H
