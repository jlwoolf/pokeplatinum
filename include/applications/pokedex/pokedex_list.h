#ifndef POKEPLATINUM_POKEDEX_LIST_H
#define POKEPLATINUM_POKEDEX_LIST_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_list_state.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexList_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexList_Free(PokedexScreenManager *param0);
BOOL PokedexList_IsActive(const PokedexListState *param0);

#endif // POKEPLATINUM_POKEDEX_LIST_H
