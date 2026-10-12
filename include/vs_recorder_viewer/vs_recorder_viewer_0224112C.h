#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H

#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "global_terminal/global_terminal_0222B008.h"

VsRecorderViewerTransferContext *VsRecorderViewerTransfer_GetTransfer(VsRecorderViewerState *param0);
void VsRecorderViewerTransfer_Init(VsRecorderViewerState *param0);
BOOL VsRecorderViewerTransfer_IsIdle(VsRecorderViewerState *param0);
void VsRecorderViewerTransfer_Main(VsRecorderViewerState *param0);
void VsRecorderViewerTransfer_Free(VsRecorderViewerState *param0);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H
