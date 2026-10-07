#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_ENTRY_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_ENTRY_H

typedef struct {
    u16 stampColor; // Palette color derived from the Pokémon's OT ID.
    u16 species;
    u32 personality;
    u8 form;
    u8 touchX; // X position where the footprint was stamped on the touch screen.
    u8 touchY; // Y position where the footprint was stamped on the touch screen.
    u8 padding;
} FootprintStampEntry;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_ENTRY_H
