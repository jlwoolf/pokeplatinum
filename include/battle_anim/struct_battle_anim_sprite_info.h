#ifndef POKEPLATINUM_STRUCT_BATTLE_ANIM_SPRITE_INFO_H
#define POKEPLATINUM_STRUCT_BATTLE_ANIM_SPRITE_INFO_H

#include "math_util.h"
#include "pokemon_sprite.h"
#include "sprite.h"

typedef struct BattleAnimSpriteInfo {
    Point2D basePos;
    Point2D pos;
    PokemonSprite *monSprite;
    ManagedSprite *hwSprite;
    int battler;
} BattleAnimSpriteInfo;

#endif // POKEPLATINUM_STRUCT_BATTLE_ANIM_SPRITE_INFO_H
