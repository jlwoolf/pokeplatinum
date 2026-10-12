#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_SCALE_TASK_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_SCALE_TASK_H

#include "spear_pillar/struct_spear_pillar_object.h"

typedef struct {
    int state;
    int frameIndex;
    int species;
    s16 pan;
    SpearPillarObject *object;
    SpearPillarObject *shadowObject;
} SpearPillarDialgaPalkiaScaleTask;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_SCALE_TASK_H
