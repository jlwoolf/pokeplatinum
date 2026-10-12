#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAMERA_ANIM_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAMERA_ANIM_H

#include <nitro/fx/fx.h>

#include "camera.h"

typedef struct {
    Camera *camera;
    VecFx32 *targetPos;
    int duration;
    s32 angleDeltaX;
    s32 angleDeltaY;
    s32 angleDeltaZ;
    fx32 posDeltaX;
    fx32 posDeltaY;
    fx32 posDeltaZ;
    s32 angleSteps[5];
    fx32 posSteps[5];
    CameraAngle cameraAngle;
} SpearPillarCameraAnim;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_CAMERA_ANIM_H
