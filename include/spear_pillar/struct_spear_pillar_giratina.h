#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/struct_spear_pillar_lake_trio_sprites.h"
#include "spear_pillar/struct_spear_pillar_giratina_objects.h"
#include "spear_pillar/struct_spear_pillar_context.h"

typedef struct {
    int unk_00;
    int unk_04;
    SpearPillarLakeTrioSprites unk_08;
    SpearPillarGiratinaObjects unk_1A0;
    SpearPillarContext *unk_1EBC;
    SpearPillarTaskArgs *unk_1EC0;
} SpearPillarGiratina;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_GIRATINA_H
