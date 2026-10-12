#ifndef POKEPLATINUM_POKEDEX_SCREEN_STATE_SET_H
#define POKEPLATINUM_POKEDEX_SCREEN_STATE_SET_H

#include "constants/heap.h"

#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"

PokedexScreenStateSet *PokedexScreenStateSet_New(enum HeapID heapID);
void PokedexScreenStateSet_SetStates(PokedexScreenStateSet *param0, PokedexScreenState *param1, int param2);
const PokedexScreenState *PokedexScreenStateSet_Update(PokedexScreenStateSet *param0, int param1);
BOOL PokedexScreenStateSet_IsActive(PokedexScreenStateSet *param0);

#endif // POKEPLATINUM_POKEDEX_SCREEN_STATE_SET_H
