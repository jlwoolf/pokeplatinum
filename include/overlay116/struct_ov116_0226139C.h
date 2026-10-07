#ifndef POKEPLATINUM_STRUCT_OV116_0226139C_H
#define POKEPLATINUM_STRUCT_OV116_0226139C_H

#include "overlay066/struct_ov66_02231134.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_animation_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"
#include "overlay116/struct_ov116_0226048C.h"
#include "overlay116/struct_ov116_02260494.h"
#include "overlay116/struct_ov116_02260498.h"
#include "overlay116/struct_ov116_02262A44.h"
#include "overlay116/struct_ov116_02262A8C.h"
#include "overlay116/struct_ov116_022649E4.h"

typedef struct {
    UnkStruct_ov116_02262A44 *unk_00;
    UnkStruct_ov116_02262A8C *unk_04;
    BOOL unk_08;
    BOOL unk_0C;
    BOOL unk_10;
    UnkStruct_ov116_0226048C unk_14;
    UnkStruct_ov116_02260494 unk_1C;
    UnkStruct_ov116_02260498 unk_24;
    u32 unk_44;
    UnkStruct_ov116_022649E4 unk_48;
    u32 unk_78;
    WiFiLobbyMinigameIntroAnimation *unk_7C;
    UnkStruct_ov66_02231134 *unk_80;
    WiFiLobbyMinigamePlayerContext unk_84;
    WiFiLobbyMinigameIntroScreen *unk_94;
    WiFiLobbyMinigameRanking unk_98;
    WiFiLobbyMinigameResultsScreen *unk_B0;
    int unk_B4[4];
    BOOL unk_C4;
} UnkStruct_ov116_0226139C;

#endif // POKEPLATINUM_STRUCT_OV116_0226139C_H
