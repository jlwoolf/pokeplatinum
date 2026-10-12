#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H

#include <nnsys.h>

#include "poffin_cooking/struct_poffin_cooking_messages.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"

typedef struct {
    int unk_00;
    BgConfig *unk_04;
    Window *unk_08;
    Window *unk_0C;
    int unk_10;
    int unk_14;
    PoffinCookingMessages *unk_18;
    PoffinCookingSession *unk_1C;
    void *unk_20;
    NNSG2dScreenData *unk_24;
    void *unk_28;
    NNSG2dScreenData *unk_2C;
    BOOL unk_30;
} PoffinCookingPlayerListDisplay;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H
