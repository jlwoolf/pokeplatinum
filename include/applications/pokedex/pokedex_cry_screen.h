#ifndef POKEPLATINUM_POKEDEX_CRY_SCREEN_H
#define POKEPLATINUM_POKEDEX_CRY_SCREEN_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexCryScreen_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexCryScreen_Free(PokedexScreenManager *param0);
void PokedexCryScreen_SetWaveParams(PokedexScreenManager *param0, int param1, int param2);
void PokedexCryScreen_SetWaveParam2(PokedexScreenManager *param0, int param1);
void PokedexCryScreen_SetWaveParam3(PokedexScreenManager *param0, int param1);

#endif // POKEPLATINUM_POKEDEX_CRY_SCREEN_H
