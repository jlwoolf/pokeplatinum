#ifndef POKEPLATINUM_BOX_MON_SPRITE_MANAGER_H
#define POKEPLATINUM_BOX_MON_SPRITE_MANAGER_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "narc.h"
#include "pokemon.h"
#include "sprite.h"

BOOL BoxMonSprite_LoadManager(BoxMonSpriteManager *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4);
void BoxMonSprite_FreeManager(BoxMonSpriteManager *param0);
void BoxMonSprite_InitSlots(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_DeleteSlots(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_CopySlot(const BoxMonSprite *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_CreateFromBoxMon(BoxMonSpriteManager *param0, BoxPokemon *boxMon, s32 param2, s32 param3, u32 param4, u32 param5, u32 param6, BoxMonSprite *param7);
void BoxMonSprite_CreateFromCharacterData(BoxMonSpriteManager *param0, BoxPokemon *boxMon, u32 param2, u32 param3, u8 *param4, s32 param5, s32 param6, u32 param7, u32 param8, u32 param9, BoxMonSprite *param10);
void BoxMonSprite_UpdateTransparency(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_SetMarkings(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_SetHeldItem(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_UpdateFormIcon(BoxMonSpriteManager *param0, BoxMonSprite *param1, BOOL param2);
void BoxMonSprite_ReadIcon(BoxMonSpriteManager *param0, void *param1, u32 param2, u32 param3);
void BoxMonSprite_LoadIcon(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
void BoxMonSprite_SetAnim(BoxMonSpriteManager *param0, BoxMonSprite *param1, u32 param2);
BOOL BoxMonSprite_IsAnimDone(BoxMonSpriteManager *param0, BoxMonSprite *param1);
void BoxGraphics_ApplyMonInMultiSelectShading(BoxMonSpriteManager *param0, BoxMonSprite *param1, BOOL isSelected);
NNSG2dCellDataBank *BoxMonSprite_GetCellBank(BoxMonSpriteManager *param0);
NNSG2dAnimBankData *BoxMonSprite_GetAnimBank(BoxMonSpriteManager *param0);

#endif // POKEPLATINUM_BOX_MON_SPRITE_MANAGER_H
