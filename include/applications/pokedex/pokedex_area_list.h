#ifndef POKEPLATINUM_POKEDEX_AREA_LIST_H
#define POKEPLATINUM_POKEDEX_AREA_LIST_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexAreaList_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexAreaList_Free(PokedexScreenManager *param0);

#endif // POKEPLATINUM_POKEDEX_AREA_LIST_H
