#ifndef POKEPLATINUM_POKEDEX_INFO_MENU_H
#define POKEPLATINUM_POKEDEX_INFO_MENU_H

#include "applications/pokedex/pokedex_app.h"
#include "applications/pokedex/struct_pokedex_screen_manager.h"

#include "heap.h"

void PokedexInfoMenu_Init(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexInfoMenu_Free(PokedexScreenManager *param0);
BOOL PokedexInfoMenu_IsActive(const PokedexScreenManager *param0);
void PokedexInfoMenu_InitSub(PokedexScreenManager *param0, PokedexApp *param1, enum HeapID heapID);
void PokedexInfoMenu_FreeSub(PokedexScreenManager *param0);
BOOL PokedexInfoMenu_IsSubActive1(const PokedexScreenManager *param0);
BOOL PokedexInfoMenu_IsSubActive2(const PokedexScreenManager *param0);
void PokedexInfoMenu_SetSubActive(PokedexScreenManager *param0, BOOL param1);
BOOL PokedexInfoMenu_IsSubActive3(const PokedexScreenManager *param0);

#endif // POKEPLATINUM_POKEDEX_INFO_MENU_H
