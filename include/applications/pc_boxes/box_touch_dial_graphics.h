#ifndef POKEPLATINUM_BOX_TOUCH_DIAL_GRAPHICS_H
#define POKEPLATINUM_BOX_TOUCH_DIAL_GRAPHICS_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_touch_dial_graphics_decl.h"

#include "bg_window.h"
#include "narc.h"
#include "sprite.h"

BOOL BoxTouchDial_Load(BoxTouchDialGraphics **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4);
void BoxTouchDial_Free(BoxTouchDialGraphics *param0);
void BoxTouchDial_Init(BoxTouchDialGraphics *param0, NARC *param1);
void BoxTouchDial_ChangeSelected(BoxTouchDialGraphics *param0);
BOOL BoxTouchDial_IsChangeDone(BoxTouchDialGraphics *param0);
void BoxTouchDial_Update(BoxTouchDialGraphics *param0);
BOOL BoxTouchDial_IsUpdateDone(BoxTouchDialGraphics *param0);
void BoxTouchDial_Scroll(BoxTouchDialGraphics *param0);
BOOL BoxTouchDial_IsScrollDone(BoxTouchDialGraphics *param0);
void BoxTouchDial_UpdateMarkingIcons(BoxTouchDialGraphics *param0);

#endif // POKEPLATINUM_BOX_TOUCH_DIAL_GRAPHICS_H
