#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexScreenManager *unk_00;
    PokedexUpdater *unk_04;
    PokedexScreenStateSet *unk_08;
} PokedexTransitionSingle;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_SINGLE_H
