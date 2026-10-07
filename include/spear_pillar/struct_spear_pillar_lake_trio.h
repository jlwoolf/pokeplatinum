#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_lake_trio_sprites.h"
#include "spear_pillar/struct_spear_pillar_lake_trio_objects.h"
#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    SpearPillarLakeTrioSprites unk_0C;
    SpearPillarLakeTrioObjects unk_1A4;
    SpearPillarContext *unk_7C4;
    SpearPillarTaskArgs *unk_7C8;
} SpearPillarLakeTrio;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H
