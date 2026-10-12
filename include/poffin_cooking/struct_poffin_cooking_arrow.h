#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_H

#include "sprite.h"

typedef struct {
    Sprite *sprite;
    int frame;
    int framesRemaining;
    BOOL active;
} PoffinCookingArrow;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_ARROW_H
