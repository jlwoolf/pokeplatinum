#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022354A4_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022354A4_H

#include "struct_decls/font_oam.h"
#include "struct_defs/struct_0208B878.h"

#include "sprite_system.h"

typedef struct {
    s16 startX;
    s16 startY;
    s16 targetX;
    s16 targetY;
    s16 stepX;
    s16 stepY;
    u8 padding_0C[16];
    u8 stepCount;
    u8 state;
    u8 padding_1E[2];
    ManagedSprite *sprite;
    FontOAM *fontOAM;
    VsRecorderRing *ring;
    BOOL *done;
    BOOL *ringDone;
} VsRecorderViewerSlideShowSlideAnim;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_022354A4_H
