#ifndef POKEPLATINUM_GLOBAL_TERMINAL_H
#define POKEPLATINUM_GLOBAL_TERMINAL_H

#include <nitro/types.h>

#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub3.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub5.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223D518_sub1.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    s32 unk_00;
    u8 unk_04;
    u8 language;
    char unk_06[301]; // DWC_SVL_TOKEN_LENGTH + 1
    u8 padding[5];
} VsRecorderViewerTransferConnection;

BOOL GlobalTerminalGds_StartConnection(VsRecorderViewerTransferConnection *param0);
void GlobalTerminalGds_EndConnection(void);
int GlobalTerminalGds_GetConnectionState(void);
int GlobalTerminalGds_GetErrorCode(void);
BOOL GlobalTerminalGds_UploadProfilePhoto(VsRecorderViewerTransferProfileData *param0, void *param1);
BOOL GlobalTerminalGds_UploadProfile(long param0, void *param1);
BOOL GlobalTerminalGds_UploadProfileBox(long param0, VsRecorderViewerTransferBoxData *param1, void *param2);
BOOL GlobalTerminalGds_UploadBox(long param0, void *param1);
BOOL GlobalTerminalGds_UploadPlayTime(void *param0);
BOOL GlobalTerminalGds_UploadPlayTimeProfile(VsRecorderViewerRankingsUploadProfile *param0, void *param1);
void *GlobalTerminalGds_GetResponseData(void);
long GlobalTerminalGds_GetResponseLength(void);
long GlobalTerminalGds_GetMaxResponseAllocSize(long param0);
BOOL GlobalTerminalGds_UploadBattleRecording(VsRecorderViewerTransferRecordData *param0, void *param1);
BOOL GlobalTerminalGds_UploadRecord(VsRecorderViewerTransferPlayTime *param0, void *param1);
BOOL GlobalTerminalGds_UploadRecordAlt(VsRecorderViewerTransferValue *param0, void *param1);
BOOL GlobalTerminalGds_UploadRecordAlt2(VsRecorderViewerTransferValue *param0, void *param1);
BOOL GlobalTerminalGds_UploadId(u64 param0, u32 param1, void *param2);
BOOL GlobalTerminalGds_UploadIdAlt(u64 param0, void *param1);

#ifdef __cplusplus
}
#endif

#endif // POKEPLATINUM_GLOBAL_TERMINAL_H
