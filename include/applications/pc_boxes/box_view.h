#ifndef POKEPLATINUM_BOX_VIEW_H
#define POKEPLATINUM_BOX_VIEW_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_customization.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_view.h"
#include "applications/pc_boxes/struct_box_mon_sprite.h"

#include "bg_window.h"
#include "sprite.h"

BOOL BoxView_Load(BoxView *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4);
void BoxView_Free(BoxView *param0);
void BoxView_DrawBackground(BoxView *param0);
void BoxView_LoadWallpaper(BoxView *param0, const BoxCustomization *BoxCustomization, int param2, BOOL param3);
void BoxView_StartBoxChange(BoxView *param0, const BoxCustomization *BoxCustomization, int param2);
BOOL BoxView_IsBoxChangeDone(BoxView *param0);
void BoxView_StartWallpaperTransition(BoxView *param0);
BOOL BoxView_UpdateWallpaperTransition(BoxView *param0);
void BoxView_PlaceMonSprite(BoxView *param0, u32 param1, s32 param2, BoxMonSprite *param3);
void BoxView_ReturnMonSprite(BoxView *param0, u32 param1, const BoxMonSprite *param2);
BoxMonSprite *BoxView_GetMonSprite(BoxView *param0, u32 param1);
void BoxView_DrawAllBoxMons(BoxView *param0);
void BoxView_StartReleaseMonAnimation(BoxView *param0, u32 param1);
BOOL BoxView_UpdateReleaseMonAnimation(BoxView *param0);
void BoxView_ApplyTransparencyToMons(BoxView *param0);
void BoxView_UpdateMonItem(BoxView *param0, u32 param1, u32 param2);
void BoxView_UpdateMonTransparency(BoxView *param0, u32 param1);
void BoxView_UpdateMonMarkings(BoxView *param0);
void BoxGraphics_ApplyMultiSelectMonShading(BoxView *param0);
void BoxView_ClearMultiSelectShading(BoxView *param0);

#endif // POKEPLATINUM_BOX_VIEW_H
