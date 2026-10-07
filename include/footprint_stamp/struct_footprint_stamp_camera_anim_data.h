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
    FootprintStampCameraAnimZoomIn unk_00;
    FootprintStampCameraAnimShake unk_08;
    FootprintStampCameraAnimRotateLeft unk_18;
    FootprintStampCameraAnimRotateRight unk_28;
    FootprintStampCameraAnimTiltUp unk_38;
    FootprintStampCameraAnimSpin unk_48;
    FootprintStampCameraAnimZoomOut unk_58;
    FootprintStampCameraAnimSwayX unk_60;
    FootprintStampCameraAnimSwayY unk_80;
    FootprintStampCameraAnimTiltDown unk_A0;
} FootprintStampCameraAnimData;

#endif // POKEPLATINUM_STRUCT_FOOTPRINT_STAMP_CAMERA_ANIM_DATA_H
