#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H

typedef struct {
    u8 state; // Fade state machine step.
    u8 cycleCount; // Number of fade cycles completed.
    s16 brightness; // Current master-brightness value.
} FootprintStampFade;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_FADE_H
