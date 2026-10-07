#ifndef POKEPLATINUM_STRUCT_OV117_022605C0_H
#define POKEPLATINUM_STRUCT_OV117_022605C0_H

#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"

#include "overlay_manager.h"

typedef struct {
    WiFiLobbyMinigamePlayerContext unk_00;
    WiFiLobbyMinigameRanking unk_10;
    ApplicationManager *appMan;
    u8 unk_2C[4];
    u8 unk_30;
    u8 unk_31;
    u8 padding_32[2];
    int unk_34;
    BOOL unk_38;
    u8 unk_3C;
    u8 unk_3D;
    u8 unk_3E;
    u8 padding_3F;
} UnkStruct_ov117_022605C0;

#endif // POKEPLATINUM_STRUCT_OV117_022605C0_H
