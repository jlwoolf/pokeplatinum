#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_MANAGER_H

#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_util.h"

typedef struct {
    SpriteList *spriteList;
    G2dRenderer renderer;
    SpriteResourceCollection *resourceCollections[4];
} PoffinCookingSpriteManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_MANAGER_H
