#include "vs_recorder_viewer/vs_recorder_viewer_0224112C.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_vs_recorder_state.h"

#include "global_terminal/global_terminal_0222B008.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02231690.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02237D24.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02239D60.h"
#include "vs_recorder_viewer/vs_recorder_viewer_0223CAEC.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02241204.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02241130.h"

#include "inlines.h"
#include "system_data.h"

static inline BOOL VsRecorderViewerTransfer_IsActive(VsRecorderState *param0);

static inline BOOL VsRecorderViewerTransfer_IsActive(VsRecorderState *param0)
{
    return param0->menuContext.transferContext.active;
}

VsRecorderViewerTransferContext *VsRecorderViewerTransfer_GetTransfer(VsRecorderState *param0)
{
    return &param0->menuContext.transferContext;
}

void VsRecorderViewerTransfer_Init(VsRecorderState *param0)
{
    VsRecorderViewerTransferInitParams v0;

    v0.profileId = SystemData_GetDWCProfileId(SaveData_GetSystemData(param0->saveData));
    v0.heapID = HEAP_ID_102;
    v0.saveData = param0->saveData;
    v0.callbacks.userData = param0;
    v0.callbacks.profilePhotoCallback = VsRecorderViewerProfile_ProfilePhotoCallback;
    v0.callbacks.profileCallback = VsRecorderViewerProfile_ProfileCallback;
    v0.callbacks.profileBoxCompleteCallback = VsRecorderViewerBox_OnProfileBoxTransferComplete;
    v0.callbacks.boxCompleteCallback = VsRecorderViewerBox_OnBoxTransferComplete;
    v0.callbacks.loadPlayTimeCallback = VsRecorderViewerRankings_LoadPlayTime;
    v0.callbacks.loadPlayTimeProfileCallback = VsRecorderViewerRankings_LoadPlayTimeProfile;
    v0.callbacks.setBattleRecordingIdCallback = VsRecorderViewerRecord_SetBattleRecordingId;
    v0.callbacks.loadRecordListCallback = VsRecorderViewerList_LoadRecordList;
    v0.callbacks.loadRecordAltCallback = VsRecorderViewerRecord_LoadRecordAlt;
    v0.callbacks.noopCallback = VsRecorderViewerRecord_Noop;
    v0.userData = param0;
    v0.stringFunc = NULL;

    GlobalTerminalTransfer_Init(&param0->menuContext.transferContext, &v0);
}

BOOL VsRecorderViewerTransfer_IsIdle(VsRecorderState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return 0;
    }

    return GlobalTerminalTransfer_IsIdle(VsRecorderViewerTransfer_GetTransfer(param0));
}

void VsRecorderViewerTransfer_Main(VsRecorderState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return;
    }

    GlobalTerminalTransfer_Main(VsRecorderViewerTransfer_GetTransfer(param0));
}

void VsRecorderViewerTransfer_Free(VsRecorderState *param0)
{
    if (VsRecorderViewerTransfer_IsActive(param0) == 0) {
        return;
    }

    GlobalTerminalTransfer_Free(VsRecorderViewerTransfer_GetTransfer(param0));
}
