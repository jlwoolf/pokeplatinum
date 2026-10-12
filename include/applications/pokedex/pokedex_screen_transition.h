#ifndef POKEPLATINUM_POKEDEX_SCREEN_TRANSITION_H
#define POKEPLATINUM_POKEDEX_SCREEN_TRANSITION_H

#include "constants/heap.h"

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_state_data.h"
#include "applications/pokedex/struct_pokedex_screen_state.h"

BOOL PokedexTransitionSingle_Step(PokedexScreenStateData *param0);
BOOL PokedexTransitionQuad_Step(PokedexScreenStateData *param0);
BOOL PokedexTransitionQuadScreens_Step(PokedexScreenStateData *param0);
BOOL PokedexTransitionDual_Step(PokedexScreenStateData *param0);
void PokedexScreenState_Free(PokedexScreenState *param0);
void Pokedex_021D467C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4704(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D475C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D47F0(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4878(PokedexScreenState *param0, PokedexApp *param1, enum HeapID heapID, int param3);
void Pokedex_021D48B8(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D491C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4980(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D49E4(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4A3C(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4A94(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4AF8(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4B50(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);
void Pokedex_021D4BB4(enum HeapID heapID, PokedexScreenState *param1, PokedexApp *param2, int param3);

#endif // POKEPLATINUM_POKEDEX_SCREEN_TRANSITION_H
