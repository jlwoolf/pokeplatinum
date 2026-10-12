#ifndef POKEPLATINUM_STRUCT_BATTLE_MON_OBJ_DATA_H
#define POKEPLATINUM_STRUCT_BATTLE_MON_OBJ_DATA_H

#include "battle/pokemon_sprite_data.h"
#include "battle_anim/struct_sprite_system_context.h"

#include "pokemon_sprite.h"
#include "sprite_system.h"

typedef struct BattleMonOBJData {
    enum HeapID heapID;
    int battlerIdx;
    SpriteSystemContext spriteContext;
    int resourceIDs[4];
    ManagedSprite *managedSprites[4];
    PokemonSpriteData *pokemonSpriteDataArray[4];
    u8 battlerTypes[4];
    PokemonSprite *pokemonSprites[4];
} BattleMonOBJData;

#endif // POKEPLATINUM_STRUCT_BATTLE_MON_OBJ_DATA_H
