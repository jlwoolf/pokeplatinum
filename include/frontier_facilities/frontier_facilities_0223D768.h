#ifndef POKEPLATINUM_FRONTIER_FACILITIES_0223D768_H
#define POKEPLATINUM_FRONTIER_FACILITIES_0223D768_H

#include "narc.h"
#include "palette.h"
#include "sprite_system.h"

void FrontierFacilities_LoadObjectSpriteResources(SpriteSystem *param0, SpriteManager *param1, NARC *param2, PaletteData *param3, u16 param4);
void FrontierFacilities_UnloadObjectSpriteResources(SpriteManager *param0, u16 param1);
ManagedSprite *FrontierFacilities_CreateObjectSprite(SpriteSystem *param0, SpriteManager *param1, u16 param2);
void FrontierFacilities_DeleteObjectSprite(ManagedSprite *param0);

#endif // POKEPLATINUM_FRONTIER_FACILITIES_0223D768_H
