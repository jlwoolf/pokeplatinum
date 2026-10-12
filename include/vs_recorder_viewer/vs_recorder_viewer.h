#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_H

#include "struct_defs/struct_vs_recorder_state.h"

void VsRecorderViewerMain_Init(VsRecorderState *param0);
void VsRecorderViewerMain_Free(VsRecorderState *param0);
void VsRecorderViewerMain_SetWhichScreenIs3D(int param0);
void VsRecorderViewerMain_InitBg2(VsRecorderState *param0);
void VsRecorderViewerMain_VBlankCallback(void *param0);
BOOL VsRecorderViewerMain_Update(VsRecorderState *param0, int *param1);
void VsRecorderViewerMain_AdvanceState(VsRecorderState *param0, int param1, BOOL param2, int *param3);
void VsRecorderViewerMain_SetState(VsRecorderState *param0, int param1);
void VsRecorderViewerMain_SetSubState(VsRecorderState *param0, int param1);
void VsRecorderViewerMain_RefreshMenu(VsRecorderState *param0);
BOOL VsRecorderViewerMain_PushMenu(VsRecorderState *param0);
BOOL VsRecorderViewerMain_PopMenu(VsRecorderState *param0);
void VsRecorderViewerMain_ExecuteMenuAction(VsRecorderState *param0);
BOOL VsRecorderViewerMain_CanExecuteAction(VsRecorderState *param0);
void VsRecorderViewerMain_InitTouchScreenActions(VsRecorderState *param0);
void VsRecorderViewerMain_UpdateTouchRects(VsRecorderState *param0);
void VsRecorderViewerMain_ClearTouchRects(VsRecorderState *param0);
void VsRecorderViewerMain_HandleTouchAction(VsRecorderState *param0);
void VsRecorderViewerMain_ReturnToParentMenu(VsRecorderState *param0);
void VsRecorderViewerMain_ResetSelection(VsRecorderState *param0);
BOOL VsRecorderViewerMain_HasPendingSelection(VsRecorderState *param0);
void VsRecorderViewerMain_SetPendingSelection(VsRecorderState *param0, int param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_H
