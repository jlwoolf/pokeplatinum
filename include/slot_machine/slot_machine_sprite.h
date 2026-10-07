#ifndef POKEPLATINUM_SLOT_MACHINE_SPRITE_H
#define POKEPLATINUM_SLOT_MACHINE_SPRITE_H

#include <nitro/fx/fx.h>

#include "slot_machine/struct_slot_machine_sprite_manager_decl.h"
#include "slot_machine/struct_slot_machine_sprite.h"

#include "narc.h"
#include "sprite.h"

SlotMachineSpriteManager *SlotMachineSprite_New(u32 heapID, u32 param1, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8, u32 param9, u32 param10);
void SlotMachineSprite_Free(SlotMachineSpriteManager *param0);
void SlotMachineSprite_Update(SlotMachineSpriteManager *param0);
void SlotMachineSprite_AddTiles(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4);
void SlotMachineSprite_RequestChar(SlotMachineSpriteManager *param0, u32 param1);
void SlotMachineSprite_ReleaseChar(SlotMachineSpriteManager *param0, u32 param1);
void SlotMachineSprite_AddPalette(SlotMachineSpriteManager *param0, u32 param1, NARC *param2, u32 param3, u32 param4);
void SlotMachineSprite_RequestPltt(SlotMachineSpriteManager *param0, u32 param1);
void SlotMachineSprite_ReleasePltt(SlotMachineSpriteManager *param0, u32 param1);
void SlotMachineSprite_AddCell(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3);
void SlotMachineSprite_AddAnim(SlotMachineSpriteManager *param0, NARC *param1, u32 param2, u32 param3);
void SlotMachineSprite_RemoveResources(SlotMachineSpriteManager *param0, u32 param1, u32 param2, u32 param3, u32 param4);
void SlotMachineSprite_CreateSprite(SlotMachineSpriteManager *param0, SlotMachineSprite *param1, const VecFx32 *param2, u32 param3, int param4, u32 param5, u32 param6, u32 param7, u32 param8, int param9, int param10);
void SlotMachineSprite_DeleteSprite(SlotMachineSprite *param0);
void SlotMachineSprite_GetPosition(Sprite *param0, VecFx32 *param1);
void SlotMachineSprite_GetScale(Sprite *param0, VecFx32 *param1);

#endif // POKEPLATINUM_SLOT_MACHINE_SPRITE_H
