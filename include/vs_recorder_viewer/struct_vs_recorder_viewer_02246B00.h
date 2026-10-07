#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H

#include "game_options.h"
#include "string_gf.h"

typedef struct {
    int unk_00;
    int unk_04[4];
    u8 padding_14[4];
    String *unk_18;
    Options *options;
} VsRecorderViewerIdEntryConfig;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246B00_H
