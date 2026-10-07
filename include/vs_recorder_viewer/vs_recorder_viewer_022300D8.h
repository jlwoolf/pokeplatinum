#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H

#include "struct_decls/struct_020F3DCC_decl.h"
#include "struct_defs/struct_0208C06C.h"

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022307C0_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223118C.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022312B0.h"

#include "sprite_system.h"
#include "sys_task_manager.h"

void VsRecorderViewerMenu_LoadBackground(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_LoadBgPanel(UnkStruct_0208C06C *param0, int param1, BOOL param2);
void VsRecorderViewerMenu_LoadBgPanelAlt(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMenu_LoadEntrySpriteResources(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_CreateDecorativeSprites(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_FreeDecorativeSprites(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_StopDecorativeSpriteTasks(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_LoadEntryIconResources(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_FreeEntryIconResources(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_PositionMenuEntries(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_CreateMenuEntries(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_UpdateSubEntryLabels(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_AttachEntryLabelSprites(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_UpdateMainEntryLabels(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_FreeMenuEntries(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_SetMenuEntriesVisible(UnkStruct_0208C06C *param0, BOOL param1);
void VsRecorderViewerMenu_AnimatedSpriteTask(SysTask *param0, void *param1);
void VsRecorderViewerMenu_SetSpritePositionWithOffset(ManagedSprite *param0, s16 param1, s16 param2);
void VsRecorderViewerMenu_GetSpritePositionWithOffset(ManagedSprite *param0, s16 *param1, s16 *param2);
void VsRecorderViewerMenu_CreateEntryLabels(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_RenderEntryLabel(UnkStruct_0208C06C *param0, VsRecorderViewerMenuEntry *param1, int param2, const VsRecorderMenuEntry *param3);
void VsRecorderViewerMenu_FreeEntryLabels(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_InitLabelOAM(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2);
void VsRecorderViewerMenu_SetLabelOAMText(VsRecorderViewerTextSprite *param0, VsRecorderViewerMenuContext *param1, int param2);
void VsRecorderViewerMenu_FreeLabelOAM(VsRecorderViewerTextSprite *param0);
void VsRecorderViewerMenu_LoadSpriteResourceSetA(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMenu_LoadCursorSpriteResources(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMenu_LoadSpriteResourceSetB(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMenu_FreeCursorSpriteResources(UnkStruct_0208C06C *param0);
ManagedSprite *VsRecorderViewerMenu_CreateCursorSprite(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMenu_HideAndFreeMenu(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_InitMenu(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_InitMenuWithExtraEntry(UnkStruct_0208C06C *param0);
void VsRecorderViewerMenu_SetBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6);
void VsRecorderViewerMenu_UpdateBlendAlpha(int *param0, int *param1, int param2, int param3, int param4, int param5, int param6);
void VsRecorderViewerMenu_SetDefaultBlendAlpha(int *param0, int *param1, int param2);
BOOL VsRecorderViewerMenu_StepBlendAlpha(int *param0, int *param1, int param2, int param3);
BOOL VsRecorderViewerMenu_StepFadeValue(int *param0, int param1);
void VsRecorderViewerMenu_ResetFadeValue(int *param0);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_022300D8_H
