#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_MANAGER_H

#include "poffin_cooking/struct_poffin_cooking_sparkle.h"

typedef struct {
    int loaded;
    int maxSparkles;
    int nextSparkle;
    PoffinCookingSparkle sparkles[32];
} PoffinCookingSparkleManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SPARKLE_MANAGER_H
