#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB1_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB1_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02246BF4_sub1_sub1.h"

#include "sprite_system.h"
#include "touch_screen.h"

typedef struct {
    int unk_00;
    int unk_04;
    BOOL unk_08;
    ManagedSprite *unk_0C;
    TouchScreenRect *unk_10;
    VsRecorderViewerIdEntryButtonRect unk_14;
    u8 padding_1A[2];
} VsRecorderViewerIdEntryButton;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02246BF4_SUB1_H
