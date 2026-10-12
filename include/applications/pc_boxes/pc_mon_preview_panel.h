#ifndef POKEPLATINUM_PC_MON_PREVIEW_PANEL_H
#define POKEPLATINUM_PC_MON_PREVIEW_PANEL_H

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_pc_mon_preview_panel.h"

#include "bg_window.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"

BOOL PCMonPreviewPanel_Load(PCMonPreviewPanel *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, const MessageLoader *param5, NARC *param6);
void PCMonPreviewPanel_Free(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_UpdateSprites(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_CreateSprite(PCMonPreviewPanel *param0);
BOOL PCMonPreviewPanel_DeleteSprite(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_InitWindows(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_Draw(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_DrawWithSprite(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_Hide(PCMonPreviewPanel *param0);
BOOL PCMonPreviewPanel_IsDrawDone(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_UpdateMarkings(PCMonPreviewPanel *param0);
void PCMonPreviewPanel_DrawHeldItem(PCMonPreviewPanel *param0);

#endif // POKEPLATINUM_PC_MON_PREVIEW_PANEL_H
