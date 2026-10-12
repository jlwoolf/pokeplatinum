#ifndef POKEPLATINUM_PC_COMPARE_SCREEN_H
#define POKEPLATINUM_PC_COMPARE_SCREEN_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_pc_compare_screen_decl.h"

#include "bg_window.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"

BOOL PCCompare_Load(PCCompareScreen **param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, MessageLoader *param5, NARC *param6);
void PCCompare_Free(PCCompareScreen *param0);
void PCCompare_Init(PCCompareScreen *param0, NARC *param1);
void PCCompare_SetButtonState(PCCompareScreen *param0, BOOL param1);
void PCCompare_DrawMonInfo(PCCompareScreen *param0);
BOOL PCCompare_IsDrawDone(PCCompareScreen *param0);
void PCCompare_StartModeSwitch(PCCompareScreen *param0);
BOOL PCCompare_UpdateModeSwitch(PCCompareScreen *param0);

#endif // POKEPLATINUM_PC_COMPARE_SCREEN_H
