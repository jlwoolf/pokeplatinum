#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H

#include "struct_decls/struct_020F3DCC_decl.h"
#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223118C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

void VsRecorderViewerMenu_LoadBackground(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_LoadBgPanel(VsRecorderViewerState *param0, int param1, BOOL param2);
void VsRecorderViewerMenu_LoadBgPanelAlt(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMenu_LoadEntrySpriteResources(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_CreateDecorativeSprites(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_FreeDecorativeSprites(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_StopDecorativeSpriteTasks(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_LoadEntryIconResources(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_FreeEntryIconResources(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_PositionMenuEntries(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_CreateMenuEntries(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_UpdateSubEntryLabels(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_AttachEntryLabelSprites(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_UpdateMainEntryLabels(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_FreeMenuEntries(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_SetMenuEntriesVisible(VsRecorderViewerState *param0, BOOL param1);
void VsRecorderViewerMenu_AnimatedSpriteTask(SysTask *param0, void *param1);
void VsRecorderViewerMenu_SetSpritePositionWithOffset(ManagedSprite *param0, s16 param1, s16 param2);
void VsRecorderViewerMenu_GetSpritePositionWithOffset(ManagedSprite *param0, s16 *param1, s16 *param2);
void VsRecorderViewerMenu_CreateEntryLabels(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_RenderEntryLabel(VsRecorderViewerState *param0, VsRecorderViewerMenuEntry *param1, int param2, const VsRecorderMenuEntry *param3);
void VsRecorderViewerMenu_FreeEntryLabels(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_InitLabelOAM(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2);
void VsRecorderViewerMenu_SetLabelOAMText(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2);
void VsRecorderViewerMenu_FreeLabelOAM(VsRecorderViewerTextSprite *param0);
void VsRecorderViewerMenu_LoadSpriteResourceSetA(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMenu_LoadCursorSpriteResources(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMenu_LoadSpriteResourceSetB(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMenu_FreeCursorSpriteResources(VsRecorderViewerState *param0);
ManagedSprite *VsRecorderViewerMenu_CreateCursorSprite(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMenu_HideAndFreeMenu(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_InitMenu(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_InitMenuWithExtraEntry(VsRecorderViewerState *param0);
void VsRecorderViewerMenu_SetBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6);
void VsRecorderViewerMenu_UpdateBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6);
void VsRecorderViewerMenu_SetDefaultBlendAlpha(int *param0, int *param1, int param2);
BOOL VsRecorderViewerMenu_StepBlendAlpha(int *param0, int *param1, int param2, int param3);
BOOL VsRecorderViewerMenu_StepFadeValue(int *param0, int param1);
void VsRecorderViewerMenu_ResetFadeValue(int *param0);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H
