#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H

typedef struct {
    u8 count; // Number of models currently occupying this slot.
    u8 refCount; // Number of models that have referenced this slot.
    u16 padding; // Padding.
} FootprintStampSlot;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_SLOT_H
