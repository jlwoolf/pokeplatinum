#ifndef POKEPLATINUM_STRUCT_MIX_RECORDS_ANIMATION_H
#define POKEPLATINUM_STRUCT_MIX_RECORDS_ANIMATION_H

#include <nnsys.h>

typedef struct {
    int active;
    int frameIndex;
    int frameTimer;
    void *paletteBuffer;
    NNSG2dPaletteData *paletteData;
} MixRecordsAnimation;

#endif // POKEPLATINUM_STRUCT_MIX_RECORDS_ANIMATION_H
