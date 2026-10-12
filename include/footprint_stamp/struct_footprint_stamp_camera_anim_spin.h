#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SPIN_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SPIN_H

#include "camera.h"

typedef struct {
    CameraAngle cameraAngle;
    fx32 angle;
    u8 repeat;
    u8 state;
    u8 unused_0E[2];
} FootprintStampCameraAnimSpin;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_SPIN_H
