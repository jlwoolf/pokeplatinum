#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H

#include "poffin_cooking/struct_poffin_cooking_messages.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"
#include "sys_task_manager.h"

typedef struct {
    int heapID;
    BgConfig *bgConfig;
    Window *windows[4];
    int frameType;
    PoffinCookingMessages *messages;
    int playerCount;
    PoffinCookingSession *session;
    BOOL loaded;
    SysTask *task;
    int timer;
    void *waitDial;
} PoffinCookingMessageBox;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H
