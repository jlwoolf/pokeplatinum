#ifndef POKEPLATINUM_POKEDEX_SEARCH_SCREEN_H
#define POKEPLATINUM_POKEDEX_SEARCH_SCREEN_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexSearchScreen_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexSearchScreen_Free(PokedexScreenManager *param0);

#endif // POKEPLATINUM_POKEDEX_SEARCH_SCREEN_H
