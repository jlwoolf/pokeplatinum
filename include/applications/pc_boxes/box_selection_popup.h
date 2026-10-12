#ifndef POKEPLATINUM_BOX_SELECTION_POPUP_H
#define POKEPLATINUM_BOX_SELECTION_POPUP_H

#include <nnsys.h>

#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_selection_popup.h"

#include "bg_window.h"
#include "narc.h"
#include "sprite.h"

BOOL BoxSelectionPopup_Load(BoxSelectionPopup *param0, BoxGraphics *param1, const BoxApplication *param2, BgConfig *param3, SpriteList *param4, NARC *param5);
void BoxSelectionPopup_InitWindows(BoxSelectionPopup *param0);
void BoxSelectionPopup_Free(BoxSelectionPopup *param0);
void BoxSelectionPopup_Show(BoxSelectionPopup *param0);
BOOL BoxSelectionPopup_IsShowDone(BoxSelectionPopup *param0);
void BoxSelectionPopup_Update(BoxSelectionPopup *param0);
void BoxSelectionPopup_Hide(BoxSelectionPopup *param0);
BOOL BoxSelectionPopup_IsHideDone(BoxSelectionPopup *param0);
void BoxSelectionPopup_DrawBoxIcon(BoxSelectionPopup *param0, u32 param1, u32 param2, NNS_G2D_VRAM_TYPE param3, NNSG2dImageProxy *param4);
NNSG2dCellDataBank *BoxSelectionPopup_GetCellBank(BoxSelectionPopup *param0);
void BoxSelectionPopup_ShowItemInfo(BoxSelectionPopup *param0);
BOOL BoxSelectionPopup_IsItemInfoDone(BoxSelectionPopup *param0);
void BoxSelectionPopup_HideItemInfo(BoxSelectionPopup *param0);
BOOL BoxSelectionPopup_IsHideItemInfoDone(BoxSelectionPopup *param0);

#endif // POKEPLATINUM_BOX_SELECTION_POPUP_H
