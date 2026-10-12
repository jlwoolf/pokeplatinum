#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H

#include "poffin_cooking/struct_poffin_cooking_messages.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "bg_window.h"
#include "sys_task_manager.h"

typedef struct {
    int unk_00;
    BgConfig *unk_04;
    Window *unk_08[4];
    int unk_18;
    PoffinCookingMessages *unk_1C;
    int unk_20;
    PoffinCookingSession *unk_24;
    BOOL unk_28;
    SysTask *unk_2C;
    int unk_30;
    void *unk_34;
} PoffinCookingMessageBox;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_MESSAGE_BOX_H
