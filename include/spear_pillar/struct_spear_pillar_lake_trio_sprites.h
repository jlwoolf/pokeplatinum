#ifndef POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_SPRITES_H
#define POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_SPRITES_H

#include "spear_pillar/struct_spear_pillar_sprite.h"
#include "spear_pillar/struct_spear_pillar_screen_scroll.h"

typedef struct {
    SpearPillarScreenScroll screenScroll;
    SpearPillarSprite pokemonSprites[3];
    SpearPillarSprite shadowSprites[3];
} SpearPillarLakeTrioSprites;

#endif // POKEPLATINUM_STRUCT_SPEAR_PILLAR_LAKE_TRIO_SPRITES_H
