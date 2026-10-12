#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H

#include "poffin_cooking/struct_poffin_cooking_sprite_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_arrow.h"

typedef struct {
    PoffinCookingSpriteManager *spriteManager;
    PoffinCookingSpriteSet spriteSet;
    PoffinCookingArrow arrows[4];
    int loaded;
} PoffinCookingArrowManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H
