#ifndef POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H
#define POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H

#include "applications/pokedex/struct_pokedex_screen_state_data.h"

typedef struct {
    int transitionMask;

    // clang-format off
    BOOL (* stepFunc)(PokedexScreenStateData * param0);
    // clang-format on

    PokedexScreenStateData stepData;
} PokedexScreenState;

#endif // POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H
