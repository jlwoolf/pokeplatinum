#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_lake_trio_sprites.h"
#include "spear_pillar/struct_spear_pillar_giratina_objects.h"
#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    int state;
    int frameCounter;
    SpearPillarLakeTrioSprites sprites;
    SpearPillarGiratinaObjects objects;
    SpearPillarContext *context;
    SpearPillarTaskArgs *taskArgs;
} SpearPillarGiratina;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H
