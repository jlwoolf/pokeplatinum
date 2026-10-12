#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_CAMERA_SHAKE_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_CAMERA_SHAKE_H

#include "spear_pillar/struct_spear_pillar_camera_anim.h"

typedef struct {
    int intensity;
    int state;
    int direction;
    int unk_0C;
    SpearPillarCameraAnim *cameraAnim;
} SpearPillarDialgaPalkiaCameraShake;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_CAMERA_SHAKE_H
