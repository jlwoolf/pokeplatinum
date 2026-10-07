#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_giratina_objects.h"
#include "spear_pillar/struct_spear_pillar_dialga_palkia_scale_task.h"
#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    SpearPillarGiratinaObjects unk_0C;
    SpearPillarContext *unk_1D28;
    SpearPillarTaskArgs *unk_1D2C;
    SpearPillarDialgaPalkiaScaleTask unk_1D30[2];
} SpearPillarDialgaPalkia;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_DIALGA_PALKIA_H
