#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_H

#include "struct_defs/struct_0208C06C.h"

void VsRecorderViewerMain_Init(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_Free(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_SetWhichScreenIs3D(int param0);
void VsRecorderViewerMain_InitBg2(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_VBlankCallback(void *param0);
BOOL VsRecorderViewerMain_Update(UnkStruct_0208C06C *param0, int *param1);
void VsRecorderViewerMain_AdvanceState(UnkStruct_0208C06C *param0, int param1, BOOL param2, int *param3);
void VsRecorderViewerMain_SetState(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMain_SetSubState(UnkStruct_0208C06C *param0, int param1);
void VsRecorderViewerMain_RefreshMenu(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerMain_PushMenu(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerMain_PopMenu(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_ExecuteMenuAction(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerMain_CanExecuteAction(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_InitTouchScreenActions(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_UpdateTouchRects(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_ClearTouchRects(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_HandleTouchAction(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_ReturnToParentMenu(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_ResetSelection(UnkStruct_0208C06C *param0);
BOOL VsRecorderViewerMain_HasPendingSelection(UnkStruct_0208C06C *param0);
void VsRecorderViewerMain_SetPendingSelection(UnkStruct_0208C06C *param0, int param1);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_H
