#ifndef POKEPLATINUM_STRUCT_POKEDEX_SCREEN_MANAGER_H
#define POKEPLATINUM_STRUCT_POKEDEX_SCREEN_MANAGER_H

#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"

typedef struct PokedexScreenManager {
    void *pageData;
    void *pageGraphics;
    PokedexDataFunction dataFunc[3];
    PokedexGraphicsFunction graphicsFunc[3];
    PokedexScreenState *screenStates;
    int numStates;
} PokedexScreenManager;

#endif // POKEPLATINUM_STRUCT_POKEDEX_SCREEN_MANAGER_H
