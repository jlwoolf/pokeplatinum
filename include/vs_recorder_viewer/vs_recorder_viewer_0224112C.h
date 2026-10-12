#ifndef POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H
#define POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H

#include "struct_defs/struct_vs_recorder_state.h"

#include "global_terminal/global_terminal_0222B008.h"

VsRecorderViewerTransferContext *VsRecorderViewerTransfer_GetTransfer(VsRecorderState *param0);
void VsRecorderViewerTransfer_Init(VsRecorderState *param0);
BOOL VsRecorderViewerTransfer_IsIdle(VsRecorderState *param0);
void VsRecorderViewerTransfer_Main(VsRecorderState *param0);
void VsRecorderViewerTransfer_Free(VsRecorderState *param0);

#endif // POKEPLATINUM_VS_RECORDER_VIEWER_0224112C_H
