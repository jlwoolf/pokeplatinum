#ifndef POKEPLATINUM_BOX_HELD_ITEM_ICONS_H
#define POKEPLATINUM_BOX_HELD_ITEM_ICONS_H

#include <nitro/fx/fx.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_held_item_icons_decl.h"

#include "bg_window.h"
#include "sprite.h"

BOOL BoxHeldItem_Load(BoxHeldItemIcons **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4);
void BoxHeldItem_Free(BoxHeldItemIcons *param0);
void BoxHeldItem_Show(BoxHeldItemIcons *param0);
void BoxHeldItem_Refresh(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsAnimDone(BoxHeldItemIcons *param0);
void BoxHeldItem_StartReturnToPreview(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsReturnToPreviewDone(BoxHeldItemIcons *param0);
void BoxHeldItem_StartReturnToMon(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsReturnToMonDone(BoxHeldItemIcons *param0);
void BoxHeldItem_StartReturnToCursor(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsReturnToCursorDone(BoxHeldItemIcons *param0);
void BoxHeldItem_StartSwap(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsSwapDone(BoxHeldItemIcons *param0);
void BoxHeldItem_StartShrink(BoxHeldItemIcons *param0);
BOOL BoxHeldItem_IsShrinkDone(BoxHeldItemIcons *param0);
void BoxHeldItem_SetPosition(BoxHeldItemIcons *param0, const VecFx32 *param1);
void BoxHeldItem_SetPriority(BoxHeldItemIcons *param0, u32 param1);

#endif // POKEPLATINUM_BOX_HELD_ITEM_ICONS_H
