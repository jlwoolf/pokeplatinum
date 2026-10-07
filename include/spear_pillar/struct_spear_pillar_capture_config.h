#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAPTURE_CONFIG_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAPTURE_CONFIG_H

#include <nitro/gx.h>

typedef struct {
    GXDispMode dispMode;
    GXBGMode bgMode;
    GXBG0As bg0As;
    GXCaptureSize captureSize;
    GXCaptureMode captureMode;
    GXCaptureSrcA captureSrcA;
    GXCaptureSrcB captureSrcB;
    GXCaptureDest captureDest;
    int unk_20;
    int unk_24;
    int unk_28;
} SpearPillarCaptureConfig;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAPTURE_CONFIG_H
