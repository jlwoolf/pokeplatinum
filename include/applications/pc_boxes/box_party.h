#ifndef POKEPLATINUM_BOX_PARTY_H
#define POKEPLATINUM_BOX_PARTY_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_party.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"
#include "narc.h"
#include "sprite.h"

BOOL BoxParty_Load(BoxParty *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, NARC *param5);
void BoxParty_Free(BoxParty *param0);
void BoxParty_Show(BoxParty *param0);
void BoxParty_Hide(BoxParty *param0);
BOOL BoxParty_IsHideDone(BoxParty *param0);
void BoxParty_StartHide(BoxParty *param0);
BOOL BoxParty_IsShowDone(BoxParty *param0);
void BoxParty_ShiftMonsDown(BoxParty *param0);
BOOL BoxParty_IsShiftDone(BoxParty *param0);
void BoxParty_MoveCursorToLastMon(BoxParty *param0);
BOOL BoxParty_IsMoveDone(BoxParty *param0);
void BoxParty_ReloadMons(BoxParty *param0);
void BoxParty_StartReleaseAnimation(BoxParty *param0, u32 param1);
BOOL BoxParty_UpdateReleaseAnimation(BoxParty *param0);
void BoxParty_ApplyTransparency(BoxParty *param0);
void BoxParty_UpdateMonItem(BoxParty *param0, u32 param1, u32 param2);
void BoxParty_UpdateMonMarkings(BoxParty *param0);
void BoxParty_PlaceMonSprite(BoxParty *param0, u32 param1, u32 param2, BoxMonSprite *param3);
void BoxParty_AddMonSprite(BoxParty *param0, u32 param1, const BoxMonSprite *param2);
void BoxParty_SetMonSprite(BoxParty *param0, u32 param1, const BoxMonSprite *param2);
BoxMonSprite *BoxParty_GetMonSprite(BoxParty *param0, u32 param1);
void BoxParty_GetMonPosition(BoxParty *param0, u32 param1, s32 *param2, s32 *param3);

#endif // POKEPLATINUM_BOX_PARTY_H
