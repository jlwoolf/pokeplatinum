#ifndef POKEPLATINUM_POKEDEX_APP_H
#define POKEPLATINUM_POKEDEX_APP_H

#include "applications/pokedex/pokedex_graphics.h"
#include "applications/pokedex/pokedex_sort_data.h"
#include "applications/pokedex/pokedex_updater.h"
#include "applications/pokedex/struct_pokedex_screen_state_set_decl.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "pokedex_memory.h"

typedef struct PokedexApp {
    BOOL exitFlag;
    enum HeapID heapID;
    PokedexMemory *pokedexMemory;
    PokedexSortData sortData;
    PokedexGraphicData graphicData;
    int transitionRequest1;
    int transitionRequest2;
    int transitionRequest3;
    int transitionRequest4;
    PokedexScreenStateSet *screenStateSet1;
    PokedexScreenStateSet *screenStateSet2;
    PokedexScreenStateSet *screenStateSet3;
    PokedexScreenStateSet *screenStateSet4;
    PokedexScreenState baseScreenState;
    PokedexScreenManager screenManagers[10];
    PokedexScreenManager subScreenManagers[8];
    PokedexUpdater *updater1;
    PokedexUpdater *updater2;
    PokedexUpdater *updater3;
    PokedexUpdater *updater4;
} PokedexApp;

#endif // POKEPLATINUM_POKEDEX_APP_H
