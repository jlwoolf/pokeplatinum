#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H

#include "poffin_cooking/struct_poffin_cooking_comm_decl.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "sprite.h"

typedef struct {
    BOOL unk_00;
    Sprite *unk_04[4];
    const PoffinCookingSession *unk_14;
    u32 unk_18;
    PoffinCookingComm *unk_1C;
} PoffinCookingPlayerCursor;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H
