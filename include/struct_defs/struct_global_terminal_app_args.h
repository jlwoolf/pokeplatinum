#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_APP_ARGS_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_APP_ARGS_H

#include "field/field_system_decl.h"

#include "savedata.h"

typedef struct {
    FieldSystem *fieldSystem;
    SaveData *saveData;
    int unk_08;
    u8 unk_0C;
    u8 padding_0D[3];
} GlobalTerminalAppArgs;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_APP_ARGS_H
