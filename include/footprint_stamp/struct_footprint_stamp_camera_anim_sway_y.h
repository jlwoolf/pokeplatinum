#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SWAY_Y_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SWAY_Y_H

#include <nitro/fx/fx.h>

typedef struct {
    VecFx32 target;
    VecFx32 position;
    fx32 angle;
    u8 repeat;
    u8 state;
    u8 unused_1E[2];
} FootprintStampCameraAnimSwayY;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SWAY_Y_H
