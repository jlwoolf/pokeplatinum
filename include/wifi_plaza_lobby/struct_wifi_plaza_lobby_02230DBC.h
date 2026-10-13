#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E294.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"

#include "trainer_info.h"

typedef struct {
    u32 appearanceRank;
    WiFiPlazaLobbyQuestionnaireData userIDs;
    WiFiPlazaLobbyNewsPlayerFlags presentFlags;
    BOOL trainerInfoValid;
    TrainerInfo *trainerInfos[4];
    WiFiPlazaLobbyState *state;
} WiFiPlazaLobbyMinigameParticipants;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H
