#ifndef POKEPLATINUM_BOX_CURSOR_SPRITE_H
#define POKEPLATINUM_BOX_CURSOR_SPRITE_H

#include <nitro/fx/fx.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_cursor_sprite.h"

#include "narc.h"
#include "sprite.h"

BOOL BoxCursorSprite_Load(BoxCursorSprite *param0, BoxGraphics *param1, const BoxApplication *param2, SpriteList *param3, NARC *param4);
void BoxCursorSprite_Init(BoxCursorSprite *param0, NARC *param1);
void BoxCursorSprite_Free(BoxCursorSprite *param0);
void BoxCursorSprite_MoveToPosition(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsMoveDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartPickUpAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsPickUpDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartPlaceAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsPlaceDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartSwapAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsSwapDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartPressAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsPressDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartReleasePressAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsReleasePressDone(BoxCursorSprite *param0);
void BoxCursorSprite_ResetPosition(BoxCursorSprite *param0);
void BoxCursorSprite_StartReleaseAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_UpdateReleaseAnimation(BoxCursorSprite *param0);
void BoxCursorSprite_SetPriorityHigh(BoxCursorSprite *param0);
void BoxCursorSprite_SetPriorityNormal(BoxCursorSprite *param0);
void BoxCursorSprite_UpdateHeldMonMarkings(BoxCursorSprite *param0);
void BoxCursorSprite_ApplyHeldMonTransparency(BoxCursorSprite *param0);
void BoxCursorSprite_UpdateHeldMonItem(BoxCursorSprite *param0, u32 param1);
void BoxCursorSprite_UpdateFastMode(BoxCursorSprite *param0);
void BoxGraphics_OpenMultiSelectCursor(BoxCursorSprite *param0);
void BoxCursorSprite_GetPosition(BoxCursorSprite *param0, VecFx32 *param1);
void BoxCursorSprite_StartPickUpItemAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsPickUpItemDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartPlaceItemAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsPlaceItemDone(BoxCursorSprite *param0);
void BoxCursorSprite_StartSwapItemAnimation(BoxCursorSprite *param0);
BOOL BoxCursorSprite_IsSwapItemDone(BoxCursorSprite *param0);
void BoxCursorSprite_HideHeldItem(BoxCursorSprite *param0);
void BoxCursorSprite_ShowHeldItem(BoxCursorSprite *param0);

#endif // POKEPLATINUM_BOX_CURSOR_SPRITE_H
