#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_TILT_DOWN_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_TILT_DOWN_H

#include "camera.h"

typedef struct {
    CameraAngle cameraAngle;
    s32 angle;
    s16 step;
    u8 state;
    u8 unused_0F;
} FootprintStampCameraAnimTiltDown;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_TILT_DOWN_H
