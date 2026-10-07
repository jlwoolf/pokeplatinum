#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_0223E824_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_0223E824_H

#include "poffin_cooking/struct_poffin_cooking_0223DEA0.h"
#include "poffin_cooking/struct_poffin_cooking_0223FE50.h"

#include "bg_window.h"
#include "sys_task_manager.h"

typedef struct {
    int unk_00;
    BgConfig *unk_04;
    Window *unk_08[4];
    int unk_18;
    UnkStruct_poffin_cooking_0223DEA0 *unk_1C;
    int unk_20;
    UnkStruct_poffin_cooking_0223FE50 *unk_24;
    BOOL unk_28;
    SysTask *unk_2C;
    int unk_30;
    void *unk_34;
} UnkStruct_poffin_cooking_0223E824;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_0223E824_H
