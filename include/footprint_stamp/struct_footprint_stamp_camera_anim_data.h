#ifndef POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_DATA_H
#define POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_DATA_H

#include "footprint_stamp/struct_footprint_stamp_camera_anim_zoom_in.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_shake.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_rotate_left.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_rotate_right.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_tilt_up.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_spin.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_zoom_out.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_sway_x.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_sway_y.h"
#include "footprint_stamp/struct_footprint_stamp_camera_anim_tilt_down.h"

typedef struct {
    FootprintStampCameraAnimZoomIn zoomIn;
    FootprintStampCameraAnimShake shake;
    FootprintStampCameraAnimRotateLeft rotateLeft;
    FootprintStampCameraAnimRotateRight rotateRight;
    FootprintStampCameraAnimTiltUp tiltUp;
    FootprintStampCameraAnimSpin spin;
    FootprintStampCameraAnimZoomOut zoomOut;
    FootprintStampCameraAnimSwayX swayX;
    FootprintStampCameraAnimSwayY swayY;
    FootprintStampCameraAnimTiltDown tiltDown;
} FootprintStampCameraAnimData;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_DATA_H
