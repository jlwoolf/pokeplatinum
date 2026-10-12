#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H

#include "poffin_cooking/struct_poffin_cooking_sprite_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_arrow.h"

typedef struct {
    PoffinCookingSpriteManager *unk_00;
    PoffinCookingSpriteSet unk_04;
    PoffinCookingArrow unk_3C[4];
    int unk_7C;
} PoffinCookingArrowManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_MANAGER_H
