#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H

#include "game_records.h"

typedef struct {
    int *coins;
    int machineMode;
    GameRecords *records;
    int consecutiveBonusRoundWins;
    int msgBoxFrame;
} SlotMachineAppArgs;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_APP_ARGS_H
