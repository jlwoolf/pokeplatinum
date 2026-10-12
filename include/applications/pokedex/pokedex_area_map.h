#ifndef POKEPLATINUM_POKEDEX_AREA_MAP_H
#define POKEPLATINUM_POKEDEX_AREA_MAP_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexAreaMap_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexAreaMap_Free(PokedexScreenManager *param0);
int PokedexAreaMap_GetEncounterTime(const PokedexScreenManager *param0);
void PokedexAreaMap_SetEncounterTime(PokedexScreenManager *param0, int param1);
void PokedexAreaMap_SetTransitionParams(PokedexScreenManager *param0, int param1, int param2);
void PokedexAreaMap_SetTransitionType(PokedexScreenManager *param0, int param1);
void PokedexAreaMap_SetTransitionSpeed(PokedexScreenManager *param0, int param1);

#endif // POKEPLATINUM_POKEDEX_AREA_MAP_H
