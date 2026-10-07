#ifndef POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_STAGE_H
#define POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_STAGE_H

#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage_data.h"

#include "trainer_info.h"

typedef struct {
    u32 unk_00;
    WiFiLobbyMinigameBucketStageData *unk_04;
    const TrainerInfo *unk_08[4];
    u32 unk_18[4];
} WiFiLobbyMinigameBucketStage;

#endif // POKEPLATINUM_STRUCT_WIFI_LOBBY_MINIGAME_BUCKET_STAGE_H
