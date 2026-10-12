#ifndef POKEPLATINUM_BATTLER_SPRITE_H
#define POKEPLATINUM_BATTLER_SPRITE_H

#include "battle_anim/struct_battler_sprite_context.h"

extern const s16 gEncounterCoords[][3];
extern const s16 gSlideTrainerInCoords[][3];

void BattlerSprite_LoadMonSprite(BattlerSpriteContext *battlerSpriteCtx, enum HeapID heapID);
void BattlerSprite_LoadMonSpriteAlt(BattlerSpriteContext *battlerSpriteCtx, enum HeapID heapID);
void BattlerSprite_PopMonSprite(BattlerSpriteContext *battlerSpriteCtx, enum HeapID heapID);
void BattlerSprite_LoadSubstituteSprite(BattlerSpriteContext *battlerSpriteCtx, enum HeapID heapID);
s16 BattlerSprite_GetEncounterOffset(int battlerType, int coordIndex);

#endif // POKEPLATINUM_BATTLER_SPRITE_H
