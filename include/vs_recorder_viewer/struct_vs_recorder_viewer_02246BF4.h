#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H

#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub3.h"

typedef struct {
    VsRecorderViewerIdEntryButton unk_00[12];
    VsRecorderViewerIdEntryButton unk_150[2];
    VsRecorderViewerIdEntryButton unk_188[3];
    s16 unk_1DC[4];
    u16 unk_1E4[4][2];
    int unk_1F4;
    int unk_1F8;
    int unk_1FC;
    int unk_200;
    int unk_204;
    int unk_208;
    int unk_20C;
    int unk_210;
    int unk_214;
    int unk_218;
    int unk_21C;
    VsRecorderViewerIdEntryGraphics unk_220;
    VsRecorderViewerIdEntrySelection unk_29C;
    VsRecorderViewerIdEntryConfig unk_2A8;
    BOOL unk_2C8;
    u64 unk_2CC;
    VsRecorderViewerState *unk_2D4;
} VsRecorderViewerIdEntryState;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H
