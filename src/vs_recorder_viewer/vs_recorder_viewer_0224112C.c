#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_vs_recorder_viewer_state.h"

#include "global_terminal/global_terminal_0222B008.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02237D24.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02239D60.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0223CAEC.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02241204.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02241130.h"

#include "inlines.h"
#include "system_data.h"

static inline BOOL VsRecorderViewerTransfer_IsActive(VsRecorderViewerState *param0);

static inline BOOL VsRecorderViewerTransfer_IsActive(VsRecorderViewerState *param0)
{
    return param0->unk_14.unk_54.unk_3B8;
}

VsRecorderViewerTransferContext *VsRecorderViewerTransfer_GetTransfer(VsRecorderViewerState *param0)
{
    return &param0->unk_14.unk_54;
}

void VsRecorderViewerTransfer_Init(VsRecorderViewerState *param0)
{
    VsRecorderViewerTransferInitParams v0;

    v0.unk_00 = SystemData_GetDWCProfileId(SaveData_GetSystemData(param0->saveData));
    v0.heapID = HEAP_ID_102;
    v0.saveData = param0->saveData;
    v0.unk_0C.unk_00 = param0;
    v0.unk_0C.unk_04 = VsRecorderViewerProfile_ProfilePhotoCallback;
    v0.unk_0C.unk_08 = VsRecorderViewerProfile_ProfileCallback;
    v0.unk_0C.unk_0C = VsRecorderViewerBox_OnProfileBoxTransferComplete;
    v0.unk_0C.unk_10 = VsRecorderViewerBox_OnBoxTransferComplete;
    v0.unk_0C.unk_14 = VsRecorderViewerRankings_LoadPlayTime;
    v0.unk_0C.unk_18 = VsRecorderViewerRankings_LoadPlayTimeProfile;
    v0.unk_0C.unk_1C = VsRecorderViewerRecord_SetBattleRecordingId;
    v0.unk_0C.unk_20 = VsRecorderViewerList_LoadRecordList;
    v0.unk_0C.unk_24 = VsRecorderViewerRecord_LoadRecordAlt;
    v0.unk_0C.unk_28 = VsRecorderViewerRecord_Noop;
    v0.unk_3C = param0;
    v0.unk_38 = NULL;

    GlobalTerminalTransfer_Init(&param0->unk_14.unk_54, &v0);
}

BOOL VsRecorderViewerTransfer_IsIdle(VsRecorderViewerState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return 0;
    }

    return GlobalTerminalTransfer_IsIdle(VsRecorderViewerTransfer_GetTransfer(param0));
}

void VsRecorderViewerTransfer_Main(VsRecorderViewerState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return;
    }

    GlobalTerminalTransfer_Main(VsRecorderViewerTransfer_GetTransfer(param0));
}

void VsRecorderViewerTransfer_Free(VsRecorderViewerState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return;
    }

    GlobalTerminalTransfer_Free(VsRecorderViewerTransfer_GetTransfer(param0));
}
