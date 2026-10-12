#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H

#include <nnsys.h>

#include "poffin_cooking/struct_poffin_cooking_messages.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"

typedef struct {
    int heapID;
    BgConfig *bgConfig;
    Window *messageWindow;
    Window *nameWindow;
    int frameType;
    int playerCount;
    PoffinCookingMessages *messages;
    PoffinCookingSession *session;
    void *screenData;
    NNSG2dScreenData *screenDataHeader;
    void *nameScreenData;
    NNSG2dScreenData *nameScreenDataHeader;
    BOOL loaded;
} PoffinCookingPlayerListDisplay;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PLAYER_LIST_DISPLAY_H
