#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233310_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"

#include "bg_window.h"
#include "message.h"
#include "sprite_system.h"

typedef struct {
    int unk_00;
    int unk_04;
    s16 unk_08;
    u8 padding_0A[2];
    int unk_0C;
    int unk_10;
    int unk_14;
    Window unk_18;
    const VsRecorderViewerListConfig *unk_28;
    ManagedSprite *unk_2C[2];
    MessageLoader *unk_34;
    VsRecorderViewerListScrollState unk_38;
    BOOL unk_48;
    u8 padding_4C[4];
} VsRecorderViewerListWindow;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H
