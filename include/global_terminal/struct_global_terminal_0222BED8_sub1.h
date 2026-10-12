#ifndef POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222BED8_SUB1_H
#define POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222BED8_SUB1_H

#include "global_terminal/struct_global_terminal_0222BED8_sub1_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4_sub1.h"

typedef struct {
    u16 species[12];
    u8 forms[12];
    u16 unused_24;
    u8 unused_26;
    u8 isSaved;
    GlobalTerminalRecordAltMon unused_28;
    u16 unused_48;
    u8 unused_4A[14];
    u64 recordingID;
    VsRecorderViewerBoxChecksum checksum;
} GlobalTerminalRecordAltData;

#endif // POKEPLATINUM_STRUCT_GLOBAL_TERMINAL_0222BED8_SUB1_H
