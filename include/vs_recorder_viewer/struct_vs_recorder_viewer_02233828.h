#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233828_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233828_H

#include "global_terminal/struct_global_terminal_0222BE20.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"

typedef struct {
    GlobalTerminalRecordAlt *record;
    GlobalTerminalRecordAlt recordCopy;
    u8 recordFlag;
    u8 padding_1D55[3];
    GlobalTerminalRecord *records[30];
    GlobalTerminalRecord recordCopies[30];
    int recordCount;
    u8 recordFlags[32];
} VsRecorderViewerListRecordStore;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233828_H
