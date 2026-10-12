#ifndef POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H
#define POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H

#include "struct_decls/struct_02030A80_decl.h"
#include "struct_defs/dress_up_photo.h"

#include "global_terminal/struct_global_terminal_0222B138.h"
#include "global_terminal/struct_global_terminal_0222B2D8.h"
#include "global_terminal/struct_global_terminal_0222B920.h"
#include "vs_recorder_viewer/funcptr_vs_recorder_viewer_022349A8.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub2.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02241130.h"

#include "gds.h"
#include "message.h"
#include "pc_boxes.h"
#include "savedata.h"
#include "string_gf.h"
#include "string_template.h"

typedef struct {
    SaveData *saveData;
    VsRecorderViewerTransferStringFunc reportMessage;
    void *reportArg;
    VsRecorderViewerTransferConnection connection;
    enum HeapID heapID;
    int connectionState;
    int prevConnectionState;
    VsRecorderViewerTransferCallbacks callbacks;
    VsRecorderViewerTransferStatus status;
    void *heap;
    VsRecorderViewerTransferPayload payload;
    void *responseBuffer;
    int active;
    int handlerIndex;
    int handlerStep;
    BOOL initialized;
    BOOL unused_3C8;
    GlobalTerminalTaskState taskState;
    int unused_3D8;
    int unused_3DC;
    int errorCode;
    int errorType;
    int requestID;
    int pendingRequestID;
    int recordType;
    MessageLoader *messageLoader;
    StringTemplate *stringTemplate;
    String *string;
    GlobalTerminalTransferCallback callback;
    u8 unused_40D;
    u8 delayTimer;
} VsRecorderViewerTransferContext;

int GlobalTerminalTransfer_Init(VsRecorderViewerTransferContext *param0, const VsRecorderViewerTransferInitParams *param1);
void GlobalTerminalTransfer_Free(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadProfilePhoto(VsRecorderViewerTransferContext *param0, PlayerProfile *param1, DressUpPhoto *photo);
int GlobalTerminalTransfer_UploadProfile(VsRecorderViewerTransferContext *param0, int param1);
int GlobalTerminalTransfer_UploadProfileBox(VsRecorderViewerTransferContext *param0, int param1, PlayerProfile *param2, const PCBoxes *pcBoxes, int param4);
int GlobalTerminalTransfer_UploadBox(VsRecorderViewerTransferContext *param0, int param1);
int GlobalTerminalTransfer_UploadPlayTime(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadPlayTimeProfile(VsRecorderViewerTransferContext *param0, PlayerProfile *param1, GlobalTerminalPlayTimeEntry param2[]);
int GlobalTerminalTransfer_UploadBattleRecording(VsRecorderViewerTransferContext *param0, PlayerProfile *param1);
int GlobalTerminalTransfer_UploadRecord(VsRecorderViewerTransferContext *param0, u16 param1, u8 param2, u8 param3, u8 param4);
int GlobalTerminalTransfer_UploadRecordDefault(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadEmptyRecord(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadRecordAlt(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadRecordAlt2(VsRecorderViewerTransferContext *param0);
int GlobalTerminalTransfer_UploadId(VsRecorderViewerTransferContext *param0, u64 param1);
int GlobalTerminalTransfer_UploadId2(VsRecorderViewerTransferContext *param0, u64 param1);
int GlobalTerminalTransfer_Main(VsRecorderViewerTransferContext *param0);
BOOL GlobalTerminalTransfer_GetState(VsRecorderViewerTransferContext *param0, VsRecorderViewerTransferStatus **param1);
BOOL GlobalTerminalTransfer_IsIdle(VsRecorderViewerTransferContext *param0);

#endif // POKEPLATINUM_GLOBAL_TERMINAL_0222B008_H
