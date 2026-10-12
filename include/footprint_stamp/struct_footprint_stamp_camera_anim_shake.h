#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SHAKE_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SHAKE_H

#include <nitro/fx/fx.h>

typedef struct {
    VecFx32 up;
    u8 state;
    u8 step;
    u8 repeat;
    u8 unused_0F;
} FootprintStampCameraAnimShake;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SHAKE_H
