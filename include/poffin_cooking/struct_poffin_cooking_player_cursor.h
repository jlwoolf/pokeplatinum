#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H

#include "poffin_cooking/struct_poffin_cooking_comm_decl.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "sprite.h"

typedef struct {
    BOOL active;
    Sprite *sprites[4];
    const PoffinCookingSession *session;
    u32 playerCount;
    PoffinCookingComm *comm;
} PoffinCookingPlayerCursor;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_CURSOR_H
