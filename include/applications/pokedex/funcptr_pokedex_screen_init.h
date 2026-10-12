#ifndef POKEPLATINUM_FUNCPTR_POKEDEX_SCREEN_INIT_H
#define POKEPLATINUM_FUNCPTR_POKEDEX_SCREEN_INIT_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

typedef void (*PokedexScreenInitFunc)(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);

#endif // POKEPLATINUM_FUNCPTR_POKEDEX_SCREEN_INIT_H
