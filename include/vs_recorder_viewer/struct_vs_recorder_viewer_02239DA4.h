#ifndef POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02239DA4_H
#define POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02239DA4_H

#include "vs_recorder_viewer/struct_vs_recorder_viewer_02239DA4_sub1.h"

typedef struct {
    u16 boxName[20];
    u16 species[30];
    u32 personality[30];
    u32 otId[30];
    u32 eggFlags;
    u8 form[30];
    u8 wallpaper;
    u8 version;
    u8 unused_178[32];
    VsRecorderViewerBoxChecksum checksum;
} VsRecorderViewerBoxData;

#endif // POKEPLATINUM_STRUCT_VS_RECORDER_VIEWER_02239DA4_H
