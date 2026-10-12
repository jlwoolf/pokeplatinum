#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_lake_trio_sprites.h"
#include "spear_pillar/struct_spear_pillar_lake_trio_objects.h"
#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    int state;
    int frameCounter;
    int index;
    SpearPillarLakeTrioSprites sprites;
    SpearPillarLakeTrioObjects objects;
    SpearPillarContext *context;
    SpearPillarTaskArgs *taskArgs;
} SpearPillarLakeTrio;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_H
