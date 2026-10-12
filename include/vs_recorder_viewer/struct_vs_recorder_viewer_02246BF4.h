#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H

#include "struct_defs/struct_vs_recorder_state.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246B00.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub3.h"

typedef struct {
    VsRecorderViewerIdEntryButton itemButtons[12];
    VsRecorderViewerIdEntryButton separatorButtons[2];
    VsRecorderViewerIdEntryButton cursorButtons[3];
    s16 categoryXPositions[4];
    u16 categoryRanges[4][2];
    int step;
    int unused_1F8;
    int animState;
    int animTimer;
    int itemCount;
    int category;
    int prevCategory;
    int firstItemIndex;
    int lastItemIndex;
    int prevFirstItemIndex;
    int prevLastItemIndex;
    VsRecorderViewerIdEntryGraphics graphics;
    VsRecorderViewerIdEntrySelection selection;
    VsRecorderViewerIdEntryConfig config;
    BOOL confirmed;
    u64 idValue;
    VsRecorderState *state;
} VsRecorderViewerIdEntryState;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_H
