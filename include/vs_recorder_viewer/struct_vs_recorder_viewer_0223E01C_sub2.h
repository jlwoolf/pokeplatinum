#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB2_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB2_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223E01C_sub1_sub1.h"

#include "narc.h"

typedef struct {
    NARC *narc;
    int lastScroll;
    int spriteIndex;
    VsRecorderViewerRankingIconCell cells[5][6];
} VsRecorderViewerRankingIconGrid;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223E01C_SUB2_H
