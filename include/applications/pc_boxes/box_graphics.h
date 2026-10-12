#ifndef POKEPLATINUM_BOX_GRAPHICS_H
#define POKEPLATINUM_BOX_GRAPHICS_H

#include <nnsys.h>

#include "applications/pc_boxes/box_app_manager.h"
#include "applications/pc_boxes/box_application.h"
#include "applications/pc_boxes/box_graphics_callback.h"
#include "applications/pc_boxes/box_graphics_decl.h"
#include "applications/pc_boxes/struct_box_view.h"
#include "applications/pc_boxes/struct_box_cursor_sprite.h"
#include "applications/pc_boxes/struct_box_mon_sprite_manager.h"
#include "applications/pc_boxes/struct_box_selection_popup.h"
#include "applications/pc_boxes/struct_box_party.h"
#include "applications/pc_boxes/struct_box_held_item_icons_decl.h"

#include "sprite.h"
#include "sys_task_manager.h"

enum BoxGraphicsFunctions {
    FUNC_BoxGraphics_SetupScene,
    FUNC_BoxGraphics_ScreenFadeBothToBlack0,
    FUNC_BoxGraphics_ScreenFadeBothToBlack1,
    FUNC_BoxGraphics_ScreenFadeBothToBlack2,
    FUNC_BoxGraphics_ChangeToNewBox,
    FUNC_BoxGraphics_MoveCursor,
    FUNC_BoxGraphics_PreviewMon,
    FUNC_BoxGraphics_UpdatePreviewedMonMarkings,
    FUNC_BoxGraphics_ClearMonPreview,
    FUNC_BoxGraphics_PickUpMonIntoCursor,
    FUNC_BoxGraphics_PlaceMonDownFromCursor,
    FUNC_BoxGraphics_SwapMonsInBox,
    FUNC_BoxGraphics_ReloadBoxMons,
    FUNC_BoxGraphics_ReloadPartyMons,
    FUNC_BoxGraphics_PlayReleaseCursorMonAnimation,
    FUNC_BoxGraphics_PlayReleaseBoxMonAnimation,
    FUNC_BoxGraphics_PlayReleasePartyMonAnimation,
    FUNC_BoxGraphics_DisplayItemInfo,
    FUNC_BoxGraphics_CloseItemInfo,
    FUNC_BoxGraphics_PickUpItemIntoCursor,
    FUNC_BoxGraphics_PlaceItemDownFromCursor,
    FUNC_BoxGraphics_SwapItems,
    FUNC_BoxGraphics_UpdateHeldItemDisplay,
    FUNC_BoxGraphics_ItemShrinkToNothing,
    FUNC_BoxGraphics_DisplayBoxMessage,
    FUNC_BoxGraphics_ShowMenu,
    FUNC_BoxGraphics_CloseMessageBox,
    FUNC_BoxGraphics_HideMenu,
    FUNC_BoxGraphics_UpdateMenuCursor,
    FUNC_BoxGraphics_UpdateMarkings,
    FUNC_BoxGraphics_ShowBoxSelectionPopup,
    FUNC_BoxGraphics_ScrollBoxSelectionPopup,
    FUNC_BoxGraphics_HideBoxSelectionPopup,
    FUNC_BoxGraphics_TransitionWallpaper,
    FUNC_BoxGraphics_PressBoxButton,
    FUNC_BoxGraphics_OpenPartyPopup,
    FUNC_BoxGraphics_ClosePartyPopup,
    FUNC_BoxGraphics_PlayAdjustPartyAnimation,
    FUNC_BoxGraphics_MovePartyCursor,
    FUNC_BoxGraphics_SetMonMarkingsTransparency,
    FUNC_BoxGraphics_OpenOrCloseSelectedTouchDial,
    FUNC_BoxGraphics_ScrollTouchDial,
    FUNC_BoxGraphics_UpdateMarkingsTouchButton,
    FUNC_BoxGraphics_UpdateCursorFastMode,
    FUNC_BoxGraphics_StartDrawMultiSelect,
    FUNC_BoxGraphics_ClearMultiSelectShading,
    FUNC_BoxGraphics_ApplyMultiSelectMonShadingTask,
    FUNC_BoxGraphics_BounceCursor,
    FUNC_BoxGraphics_SetCompareButtonUnpressed,
    FUNC_BoxGraphics_SetCompareButtonPressed,
    FUNC_BoxGraphics_SwitchCompareMode,
    FUNC_BoxGraphics_ScreenFadeBothToBlackLogOff,
};

BOOL BoxGraphics_Load(BoxGraphics **param0, const BoxApplication *param1, const BoxApplicationManager *param2);
void BoxGraphics_Free(BoxGraphics *param0);
void BoxGraphics_TaskHandler(BoxGraphics *param0, enum BoxGraphicsFunctions function);
BOOL BoxGraphics_IsSysTaskDone(BoxGraphics *param0, enum BoxGraphicsFunctions function);
BOOL BoxGraphics_CheckAllTasksDone(BoxGraphics *param0);
SysTask *BoxGraphics_StartVBlankTask(SysTaskFunc param0, void *param1, u32 param2);
NNSG2dImagePaletteProxy *BoxGraphics_GetPaletteProxy(BoxGraphics *param0);
BoxMonSpriteManager *BoxGraphics_GetBoxMonSpriteManager(BoxGraphics *param0);
BoxView *BoxGraphics_GetBoxView(BoxGraphics *param0);
BoxParty *BoxGraphics_GetBoxParty(BoxGraphics *param0);
BoxCursorSprite *BoxGraphics_GetCursorSprite(BoxGraphics *param0);
BoxHeldItemIcons *BoxGraphics_GetHeldItemIcons(BoxGraphics *param0);
BoxSelectionPopup *BoxGraphics_GetBoxSelectionPopup(BoxGraphics *param0);
PokemonSpriteManager *BoxGraphics_GetPokemonSpriteManager(BoxGraphics *param0);
int BoxGraphics_GetCompareXOffset(BoxGraphics *param0);
void BoxGraphics_InitSpriteResources(SpriteResourcesHeader *param0, NNSG2dImageProxy *param1, NNSG2dImagePaletteProxy *param2, NNSG2dCellDataBank *param3, NNSG2dCellAnimBankData *param4, u32 param5);
Sprite *BoxGraphics_CreateSprite(SpriteList *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3, u32 param4, int param5);
void BoxGraphics_SetSpritePriority(Sprite *sprite, u32 priority);
void BoxGraphics_BlendPalette(const u16 *param0, u16 *param1, u32 param2, u16 param3, u32 param4);
const BoxApplicationManager *BoxGraphics_GetAppManager(BoxGraphics *param0);
void BoxGraphics_DeferFree(void *param0, BoxGraphicsDeferredFreeCallback param1, void *param2);

#endif // POKEPLATINUM_BOX_GRAPHICS_H
