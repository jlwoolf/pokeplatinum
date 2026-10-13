#ifndef POKEPLATINUM_STRUCT_POKEDEX_LIST_STATE_H
#define POKEPLATINUM_STRUCT_POKEDEX_LIST_STATE_H

#include "applications/pokedex/pokedex_sort_data.h"

typedef struct {
    int *transitionRequest;
    PokedexSortData *sortData;
    int scrollDirection;
    int scrollOffset;
    int skipTransition;
    BOOL useBlendTransition;
    BOOL skipTransitionRequest;
    BOOL updateGraphics;
    u32 scrollState;
    BOOL cancelFlag;
    BOOL sortMenuFlag;
    BOOL infoFlag;
    BOOL nationalDexFlag;
    BOOL exitFlag;
} PokedexListState;

#endif // POKEPLATINUM_STRUCT_POKEDEX_LIST_STATE_H
