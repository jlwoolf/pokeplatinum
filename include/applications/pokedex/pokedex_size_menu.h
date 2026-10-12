#ifndef POKEPLATINUM_POKEDEX_SIZE_MENU_H
#define POKEPLATINUM_POKEDEX_SIZE_MENU_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexSizeMenu_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexSizeMenu_Free(PokedexScreenManager *param0);

#endif // POKEPLATINUM_POKEDEX_SIZE_MENU_H
