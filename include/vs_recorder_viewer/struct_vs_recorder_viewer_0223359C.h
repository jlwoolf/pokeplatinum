#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223359C_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223359C_H

#include "sprite_system.h"

typedef struct {
    int holdTimer;
    BOOL active;
    u32 holdX;
    u32 holdY;
    s16 direction;
    u8 padding_12[2];
    BOOL visible;
    ManagedSprite *sprites[2];
} VsRecorderViewerListScrollBar;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_0223359C_H
