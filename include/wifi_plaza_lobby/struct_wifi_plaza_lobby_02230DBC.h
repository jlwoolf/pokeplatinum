#ifndef POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H
#define POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H

#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222E294.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02232068.h"

#include "trainer_info.h"

typedef struct {
    u32 unk_00;
    WiFiPlazaLobbyQuestionnaireData unk_04;
    WiFiPlazaLobbyNewsPlayerFlags unk_08;
    BOOL unk_1C;
    TrainerInfo *unk_20[4];
    WiFiPlazaLobbyState *unk_30;
} WiFiPlazaLobbyMinigameParticipants;

#endif // POKEPLATINUM_STRUCT_WIFI_PLAZA_LOBBY_02230DBC_H
