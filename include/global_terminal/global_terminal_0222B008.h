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
    VsRecorderViewerTransferStringFunc unk_04;
    void *unk_08;
    VsRecorderViewerTransferConnection unk_0C;
    enum HeapID heapID;
    int unk_148;
    int unk_14C;
    VsRecorderViewerTransferCallbacks unk_150;
    VsRecorderViewerTransferStatus unk_17C;
    void *unk_18C;
    VsRecorderViewerTransferPayload unk_190;
    void *unk_3B4;
    int unk_3B8;
    int unk_3BC;
    int unk_3C0;
    BOOL unk_3C4;
    BOOL unk_3C8;
    GlobalTerminalTaskState unk_3CC;
    int unk_3D8;
    int unk_3DC;
    int unk_3E0;
    int unk_3E4;
    int unk_3E8;
    int unk_3EC;
    int unk_3F0;
    MessageLoader *unk_3F4;
    StringTemplate *unk_3F8;
    String *unk_3FC;
    GlobalTerminalTransferCallback unk_400;
    u8 unk_40D;
    u8 unk_40E;
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
