#ifndef POKEPLATINUM_POKEDEX_SIZE_COMPARISON_H
#define POKEPLATINUM_POKEDEX_SIZE_COMPARISON_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexSizeComparison_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexSizeComparison_Free(PokedexScreenManager *param0);

#endif // POKEPLATINUM_POKEDEX_SIZE_COMPARISON_H
