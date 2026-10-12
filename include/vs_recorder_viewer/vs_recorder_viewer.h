#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_H

#include "struct_defs/struct_vs_recorder_viewer_state.h"

void VsRecorderViewerMain_Init(VsRecorderViewerState *param0);
void VsRecorderViewerMain_Free(VsRecorderViewerState *param0);
void VsRecorderViewerMain_SetWhichScreenIs3D(int param0);
void VsRecorderViewerMain_InitBg2(VsRecorderViewerState *param0);
void VsRecorderViewerMain_VBlankCallback(void *param0);
BOOL VsRecorderViewerMain_Update(VsRecorderViewerState *param0, int *param1);
void VsRecorderViewerMain_AdvanceState(VsRecorderViewerState *param0, int param1, BOOL param2, int *param3);
void VsRecorderViewerMain_SetState(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMain_SetSubState(VsRecorderViewerState *param0, int param1);
void VsRecorderViewerMain_RefreshMenu(VsRecorderViewerState *param0);
BOOL VsRecorderViewerMain_PushMenu(VsRecorderViewerState *param0);
BOOL VsRecorderViewerMain_PopMenu(VsRecorderViewerState *param0);
void VsRecorderViewerMain_ExecuteMenuAction(VsRecorderViewerState *param0);
BOOL VsRecorderViewerMain_CanExecuteAction(VsRecorderViewerState *param0);
void VsRecorderViewerMain_InitTouchScreenActions(VsRecorderViewerState *param0);
void VsRecorderViewerMain_UpdateTouchRects(VsRecorderViewerState *param0);
void VsRecorderViewerMain_ClearTouchRects(VsRecorderViewerState *param0);
void VsRecorderViewerMain_HandleTouchAction(VsRecorderViewerState *param0);
void VsRecorderViewerMain_ReturnToParentMenu(VsRecorderViewerState *param0);
void VsRecorderViewerMain_ResetSelection(VsRecorderViewerState *param0);
BOOL VsRecorderViewerMain_HasPendingSelection(VsRecorderViewerState *param0);
void VsRecorderViewerMain_SetPendingSelection(VsRecorderViewerState *param0, int param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_H
