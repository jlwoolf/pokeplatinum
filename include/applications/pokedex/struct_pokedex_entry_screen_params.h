#ifndef POKEPLATINUM_STRUCT_POKEDEX_ENTRY_SCREEN_PARAMS_H
#define POKEPLATINUM_STRUCT_POKEDEX_ENTRY_SCREEN_PARAMS_H

#include "bg_window.h"
#include "palette.h"
#include "pokemon.h"

typedef struct PokedexEntryScreenParams {
    BgConfig *bgConfig;
    PaletteData *plttData;
    PokemonSpriteManager *monSpriteMan;
    enum HeapID heapID;
    Pokemon *mon;
    int hasNationalDex;
} PokedexEntryScreenParams;

#endif // POKEPLATINUM_STRUCT_POKEDEX_ENTRY_SCREEN_PARAMS_H
