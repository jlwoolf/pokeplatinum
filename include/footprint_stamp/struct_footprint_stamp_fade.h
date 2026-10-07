#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H

typedef struct {
    u8 unk_00; // Fade state machine step.
    u8 unk_01; // Number of fade cycles completed.
    s16 unk_02; // Current master-brightness value.
} FootprintStampFade;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H
