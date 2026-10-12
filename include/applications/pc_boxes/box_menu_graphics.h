#ifndef POKEPLATINUM_BOX_MENU_GRAPHICS_H
#define POKEPLATINUM_BOX_MENU_GRAPHICS_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/struct_box_menu.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_menu_graphics.h"

#include "bg_window.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"

BOOL BoxMenuGraphics_Load(BoxMenuGraphics *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, MessageLoader *param5, const StringTemplate *param6, int param7, NARC *param8);
void BoxMenuGraphics_Free(BoxMenuGraphics *param0);
void BoxMenuGraphics_InitWindows(BoxMenuGraphics *param0);
void BoxMenuGraphics_DrawMessage(BoxMenuGraphics *param0, u32 boxMessageID);
void BoxMenuGraphics_DrawMenu(BoxMenuGraphics *param0, const BoxMenu *menu);
void BoxMenuGraphics_Hide(BoxMenuGraphics *param0);
void BoxMenuGraphics_HideMenu(BoxMenuGraphics *param0);
void BoxGraphics_DrawMenuCursorBox(BoxMenuGraphics *param0, const BoxMenu *menu);
void BoxMenuGraphics_UpdateMarkings(BoxMenuGraphics *param0, const BoxMenu *menu);

#endif // POKEPLATINUM_BOX_MENU_GRAPHICS_H
