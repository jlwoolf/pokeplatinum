#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    BOOL unk_00;
    int sceneIndex;
    void *sceneData;
    SpearPillarContext context;
    SpearPillarTaskArgs *taskArgs;
} SpearPillar;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_H
