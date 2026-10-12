#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02248CDC_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02248CDC_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02249380.h"

#include "touch_screen.h"

typedef struct {
    const VsRecorderViewerListEntry *entries;
    int entryCount;
    int lineCount;
    int tilemapLeft;
    int tilemapTop;
    int width;
    int height;
    int baseTile;
    int bgLayer;
    u32 visibleRows;
    const TouchScreenRect *touchRects;
} VsRecorderViewerListConfig;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02248CDC_H
