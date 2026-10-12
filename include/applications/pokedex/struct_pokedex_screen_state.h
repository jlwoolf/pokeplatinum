#ifndef POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H
#define POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H

#include "applications/pokedex/struct_pokedex_screen_state_data.h"

typedef struct {
    int unk_00;

    // clang-format off
    BOOL (* unk_04)(PokedexScreenStateData * param0);
    // clang-format on

    PokedexScreenStateData unk_08;
} PokedexScreenState;

#endif // POKEPLATINUM_STRUCT_POKEDEX_SCREEN_STATE_H
