#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H

#include "slot_machine/struct_slot_machine_context_decl.h"

typedef struct {
    SlotMachineContext *unk_00;
    u16 unk_04[16];
    u16 unk_24[16];
    u16 unk_44[16];
    u16 unk_64[16];
    u16 unk_84[16];
    u16 unk_A4[5][16];
    u16 unk_144[5][16];
    u16 unk_1E4[5][16];
} SlotMachinePalette;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H
