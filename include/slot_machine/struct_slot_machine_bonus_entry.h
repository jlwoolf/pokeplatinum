#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_BONUS_ENTRY_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_BONUS_ENTRY_H

#include "enums.h"

typedef struct {
    u32 weight;
    SlotMachineBonusType bonusType;
    SlotMachineBonusKind bonusKind;
} SlotMachineBonusEntry;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_BONUS_ENTRY_H
