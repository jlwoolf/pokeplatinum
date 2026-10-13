#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexUpdater *updater1;
    PokedexUpdater *updater2;
    PokedexScreenStateSet *screenStateSet1;
    PokedexScreenStateSet *screenStateSet2;
    PokedexScreenManager *screenManager;
    PokedexScreenManager *subScreenManager;
} PokedexTransitionDual;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H
