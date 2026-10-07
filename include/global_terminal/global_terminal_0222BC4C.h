#ifndef POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H
#define POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H

#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/struct_global_terminal_0222B960.h"
#include "global_terminal/struct_global_terminal_0222BC90.h"
#include "global_terminal/struct_global_terminal_0222BCF8_sub1_sub1.h"
#include "global_terminal/struct_global_terminal_0222BDAC.h"
#include "global_terminal/struct_global_terminal_0222BDAC_1.h"
#include "global_terminal/struct_global_terminal_0222BE20.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223DF10.h"

int GlobalTerminalGds_HandleProfilePhoto(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_HandleProfile(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetProfilePhotoList(VsRecorderViewerTransferContext *param0, GlobalTerminalProfilePhoto **param1, int param2);
int GlobalTerminalGds_HandleProfileBox(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_HandleBox(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetBoxList(VsRecorderViewerTransferContext *param0, GlobalTerminalProfileBox **param1, int param2);
int GlobalTerminalGds_HandlePlayTime(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
void GlobalTerminalGds_GetPlayTime(VsRecorderViewerTransferContext *param0, VsRecorderViewerRankingsPlayTime **param1);
int GlobalTerminalGds_HandlePlayTimeProfile(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
void GlobalTerminalGds_GetPlayTimeProfile(VsRecorderViewerTransferContext *param0, GlobalTerminalPlayTimeData **param1, GlobalTerminalPlayTimeDataAlt **param2);
int GlobalTerminalGds_HandleBattleRecording(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
u64 GlobalTerminalGds_GetBattleRecording(VsRecorderViewerTransferContext *param0);
int GlobalTerminalGds_HandleRecord(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetRecordList(VsRecorderViewerTransferContext *param0, GlobalTerminalRecord **param1, int param2);
int GlobalTerminalGds_HandleRecordAlt(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);
int GlobalTerminalGds_GetRecordAlt(VsRecorderViewerTransferContext *param0, GlobalTerminalRecordAlt **param1);
int GlobalTerminalGds_HandleRecordAlt2(VsRecorderViewerTransferContext *param0, GlobalTerminalGdsResponse *param1);

#endif // POKEPLATINUM_GLOBAL_TERMINAL_0222BC4C_H
