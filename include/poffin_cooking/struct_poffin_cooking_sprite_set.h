#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_SET_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_SET_H

#include "sprite.h"
#include "sprite_resource.h"

typedef struct {
    SpriteResource *resources[4];
    BOOL sharedPalette;
    SpriteResourcesHeader header;
} PoffinCookingSpriteSet;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SPRITE_SET_H
