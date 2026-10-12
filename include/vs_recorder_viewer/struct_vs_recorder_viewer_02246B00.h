#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H

#include "game_options.h"
#include "string_gf.h"

typedef struct {
    int digitCount;
    int categoryCounts[4];
    u8 padding_14[4];
    String *idString;
    Options *options;
} VsRecorderViewerIdEntryConfig;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H
