#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H

#include "game_records.h"

typedef struct {
    int *unk_00;
    int unk_04;
    GameRecords *records;
    int unk_0C;
    int msgBoxFrame;
} SlotMachineAppArgs;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H
