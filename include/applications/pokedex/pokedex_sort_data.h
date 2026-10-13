#ifndef POKEPLATINUM_POKEDEX_SORT_DATA_H
#define POKEPLATINUM_POKEDEX_SORT_DATA_H

#include "applications/pokedex/sorted_pokedex.h"

#include "pokedex.h"
#include "pokedex_heightweight.h"
#include "string_gf.h"

typedef struct {
    const Pokedex *pokedex;
    SortedPokedex sortedPokedex;
    int isNationalDex;
    BOOL isNationalDexUnlocked;
    int numEncountered;
    int numCaught;
    BOOL isFiltered;
    int timeOfDay;
    HeightWeightData *HWData;
    u32 trainerGameCode;
    u32 trainerGender;
    String *trainerName;
    int inputState;
    u16 currentSpecies;
    u16 bootMode;
    BOOL fullmoonIslandVisible;
    BOOL newmoonIslandVisible;
    BOOL springPathVisible;
    BOOL seabreakPathVisible;
} PokedexSortData;

#endif // POKEPLATINUM_POKEDEX_SORT_DATA_H
