#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexUpdater *unk_00;
    PokedexUpdater *unk_04;
    PokedexScreenStateSet *unk_08;
    PokedexScreenStateSet *unk_0C;
    PokedexScreenManager *unk_10;
    PokedexScreenManager *unk_14;
} PokedexTransitionDual;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_DUAL_H
