#ifndef POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H
#define POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H

#include "slot_machine/struct_slot_machine_context_decl.h"

typedef struct {
    SlotMachineContext *context;
    u16 paletteA[16];
    u16 paletteB[16];
    u16 flashPaletteA[16];
    u16 flashPaletteB[16];
    u16 blendTarget[16];
    u16 baseReelPalettes[5][16];
    u16 litReelPalettes[5][16];
    u16 blendedReelPalettes[5][16];
} SlotMachinePalette;

#endif // POKEPLATINUM_STRUCT_SLOT_MACHINE_PALETTE_H
