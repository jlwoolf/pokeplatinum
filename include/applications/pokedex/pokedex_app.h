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
    BOOL unk_00;
    enum HeapID heapID;
    PokedexMemory *pokedexMemory;
    PokedexSortData sortData;
    PokedexGraphicData graphicData;
    int unk_1A60;
    int unk_1A64;
    int unk_1A68;
    int unk_1A6C;
    PokedexScreenStateSet *unk_1A70;
    PokedexScreenStateSet *unk_1A74;
    PokedexScreenStateSet *unk_1A78;
    PokedexScreenStateSet *unk_1A7C;
    PokedexScreenState unk_1A80;
    PokedexScreenManager unk_1A94[10];
    PokedexScreenManager unk_1C24[8];
    PokedexUpdater *unk_1D64;
    PokedexUpdater *unk_1D68;
    PokedexUpdater *unk_1D6C;
    PokedexUpdater *unk_1D70;
} PokedexApp;

#endif // POKEPLATINUM_POKEDEX_APP_H
