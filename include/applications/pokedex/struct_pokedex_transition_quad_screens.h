#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexUpdater *updater1;
    PokedexUpdater *updater2;
    PokedexUpdater *updater3;
    PokedexUpdater *updater4;
    PokedexScreenStateSet *screenStateSet1;
    PokedexScreenStateSet *screenStateSet2;
    PokedexScreenStateSet *screenStateSet3;
    PokedexScreenStateSet *screenStateSet4;
    PokedexScreenManager *screenManager1;
    PokedexScreenManager *subScreenManager1;
    PokedexScreenManager *screenManager2;
    PokedexScreenManager *subScreenManager2;
} PokedexTransitionQuadScreens;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H
