#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H

#include "spear_pillar/struct_spear_pillar_object_anim_step.h"

#include "easy3d_object.h"

typedef struct {
    Easy3DObject unk_00;
    Easy3DModel unk_78;
    Easy3DAnim unk_88[10];
    fx32 unk_150;
    fx32 unk_154;
    int unk_158;
    int unk_15C;
    BOOL unk_160;
    BOOL unk_164;
    BOOL unk_168;
    BOOL unk_16C;
    BOOL unk_170;
    BOOL unk_174;
    int unk_178;
    int unk_17C;
    int unk_180;
    SpearPillarObjectAnimStep *unk_184;
} SpearPillarObject;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_OBJECT_H
