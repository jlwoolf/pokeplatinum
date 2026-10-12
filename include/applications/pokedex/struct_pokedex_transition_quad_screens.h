#ifndef POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H
#define POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

typedef struct {
    PokedexUpdater *unk_00;
    PokedexUpdater *unk_04;
    PokedexUpdater *unk_08;
    PokedexUpdater *unk_0C;
    PokedexScreenStateSet *unk_10;
    PokedexScreenStateSet *unk_14;
    PokedexScreenStateSet *unk_18;
    PokedexScreenStateSet *unk_1C;
    PokedexScreenManager *unk_20;
    PokedexScreenManager *unk_24;
    PokedexScreenManager *unk_28;
    PokedexScreenManager *unk_2C;
} PokedexTransitionQuadScreens;

#endif // POKEPLATINUM_STRUCT_POKEDEX_TRANSITION_QUAD_SCREENS_H
