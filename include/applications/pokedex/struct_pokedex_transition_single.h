#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexScreenManager *screenManager;
    PokedexUpdater *updater;
    PokedexScreenStateSet *screenStateSet;
} PokedexTransitionSingle;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H
