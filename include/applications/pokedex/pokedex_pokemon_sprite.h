#ifndef POKEPLATINUM_POKEDEX_POKEMON_SPRITE_H
#define POKEPLATINUM_POKEDEX_POKEMON_SPRITE_H

#include "applications/pokedex/struct_pokedex_pokemon_sprite_decl.h"
#include "applications/pokedex/struct_pokedex_entry_screen_params.h"

#include "pokemon_sprite.h"

PokedexPokemonSprite *PokedexPokemonSprite_New(const PokedexEntryScreenParams *param0);
void PokedexPokemonSprite_Free(PokedexPokemonSprite *param0);
BOOL PokedexPokemonSprite_IsReady(const PokedexPokemonSprite *param0);
PokemonSprite *PokedexPokemonSprite_GetSprite(PokedexPokemonSprite *param0);
void PokedexPokemonSprite_SetActive(PokedexPokemonSprite *param0, BOOL param1);

#endif // POKEPLATINUM_POKEDEX_POKEMON_SPRITE_H
