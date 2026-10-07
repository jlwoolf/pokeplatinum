#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H

typedef struct {
    u8 unk_00; // Number of models currently occupying this slot.
    u8 unk_01; // Number of models that have referenced this slot.
    u16 unk_02; // Padding.
} FootprintStampSlot;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H
