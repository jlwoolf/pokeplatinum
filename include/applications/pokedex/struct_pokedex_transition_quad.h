#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_H

#include "applications/pokedex/pokedex_updater.h"

typedef struct {
    PokedexUpdater *updater1;
    PokedexUpdater *updater2;
    PokedexUpdater *updater3;
    PokedexUpdater *updater4;
    BOOL *exitFlag;
} PokedexTransitionQuad;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_H
