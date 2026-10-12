#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02233310_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02248CDC.h"

#include "bg_window.h"
#include "message.h"
#include "sprite_system.h"

typedef struct {
    int unused_00;
    int entryCount;
    s16 scroll;
    u8 padding_0A[2];
    int lastDrawn;
    int visibleRows;
    int pageCount;
    Window window;
    const VsRecorderViewerListConfig *config;
    ManagedSprite *arrowSprites[2];
    MessageLoader *messageLoader;
    VsRecorderViewerListScrollState scrollState;
    BOOL twoColumn;
    u8 padding_4C[4];
} VsRecorderViewerListWindow;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02233310_H
