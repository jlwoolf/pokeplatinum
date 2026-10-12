#include "global_terminal/global_terminal_0222B008.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "struct_defs/dress_up_photo.h"
#include "struct_defs/struct_02030A80.h"

#include "nintendo_wfc/main.h"
#include "global_terminal/global_terminal_0222AE60.h"
#include "global_terminal/global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222AFC0.h"
#include "global_terminal/struct_global_terminal_0222B138.h"
#include "global_terminal/struct_global_terminal_0222B2D8.h"
#include "global_terminal/struct_global_terminal_0222B920.h"
#include "global_terminal/struct_global_terminal_0222B960.h"
#include "global_terminal/struct_global_terminal_0222BDC8.h"
#include "vs_recorder_viewer/vs_recorder_viewer_02248408.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub3.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_022349A8_sub3_sub5.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223CAA4.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_0223D518_sub1_sub1.h"
#include "vs_recorder_viewer/struct_vs_recorder_viewer_02241130.h"

#include "comm_manager.h"
#include "gds.h"
#include "heap.h"
#include "message.h"
#include "pc_boxes.h"
#include "play_time.h"
#include "save_player.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "battle_recording.h"

typedef int (*GlobalTerminalTransferHandler)(VsRecorderViewerTransferContext *, GlobalTerminalTaskState *);

static int GlobalTerminalTransfer_StateCleanup(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1);
static int GlobalTerminalTransfer_StateDisconnect(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1);
static int GlobalTerminalTransfer_StateError(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1);
static int GlobalTerminalTransfer_StateWaitInput(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1);
static int GlobalTerminalTransfer_ProcessRequest(VsRecorderViewerTransferContext *param0);
static int GlobalTerminalTransfer_ProcessConnection(VsRecorderViewerTransferContext *param0);
static int GlobalTerminalTransfer_GetConnectionState(VsRecorderViewerTransferContext *param0);
static void GlobalTerminalTransfer_ReportMessage(VsRecorderViewerTransferContext *param0, String *param1);
static void GlobalTerminalTransfer_FormatError(VsRecorderViewerTransferContext *param0, int param1, int param2);
static int GlobalTerminalTransfer_Dispatch(VsRecorderViewerTransferContext *param0);
static void *GlobalTerminalTransfer_InitHeap(enum HeapID heapID);
static void GlobalTerminalTransfer_ClearHeap(void);
static BOOL GlobalTerminalTransfer_OnComplete(void *param0, void *param1);
static BOOL GlobalTerminalTransfer_OnCompleteAlt(void *param0, void *param1);
static BOOL GlobalTerminalTransfer_OnCompleteSave(void *param0, void *param1);
static BOOL GlobalTerminalTransfer_OnFail(void *param0, void *param1);
static BOOL GlobalTerminalTransfer_OnFailAlt(void *param0, void *param1);
static BOOL GlobalTerminalTransfer_OnFailReport(void *param0, void *param1);

static const GlobalTerminalTransferHandler sGlobalTerminalTransferHandlers[] = {
    GlobalTerminalTransfer_StateDisconnect,
    GlobalTerminalTransfer_StateCleanup,
    GlobalTerminalTransfer_StateError,
    GlobalTerminalTransfer_StateWaitInput,
    NULL
};

static const GlobalTerminalTransferHandler sGlobalTerminalTransferHandlersEmpty[] = {
    NULL
};

static const GlobalTerminalTransferHandler *const sGlobalTerminalTransferHandlerTable[] = {
    NULL,
    sGlobalTerminalTransferHandlers,
    sGlobalTerminalTransferHandlersEmpty
};

int GlobalTerminalTransfer_Init(VsRecorderViewerTransferContext *param0, const VsRecorderViewerTransferInitParams *param1)
{
    int v0;

    MI_CpuClear8(param0, sizeof(VsRecorderViewerTransferContext));

    param0->heapID = param1->heapID;
    param0->saveData = param1->saveData;
    param0->callbacks = param1->callbacks;
    param0->reportArg = param1->userData;
    param0->reportMessage = param1->stringFunc;
    param0->prevConnectionState = -1;
    param0->requestID = 23004;
    param0->pendingRequestID = 23004;
    param0->responseBuffer = Heap_Alloc(param1->heapID, GlobalTerminalGds_GetMaxResponseAllocSize(-1));

    MI_CpuClear8(param0->responseBuffer, GlobalTerminalGds_GetMaxResponseAllocSize(-1));

    param0->messageLoader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0695, param1->heapID);
    param0->stringTemplate = StringTemplate_Default(param1->heapID);
    param0->string = String_Init((16 * 8 * 2), param1->heapID);
    param0->heap = GlobalTerminalTransfer_InitHeap(param1->heapID);
    param0->connection.unk_00 = param1->profileId;
    param0->connection.unk_04 = GAME_VERSION;
    param0->connection.language = GAME_LANGUAGE;

    v0 = GlobalTerminalGds_StartConnection(&param0->connection);
    GF_ASSERT(v0 == 1);

    param0->initialized = 1;
    param0->active = 1;

    return 1;
}

void GlobalTerminalTransfer_Free(VsRecorderViewerTransferContext *param0)
{
    GlobalTerminalGds_EndConnection();

    param0->initialized = 0;

    String_Free(param0->string);
    StringTemplate_Free(param0->stringTemplate);
    MessageLoader_Free(param0->messageLoader);
    Heap_Free(param0->responseBuffer);
    GlobalTerminalTransfer_ClearHeap();
    Heap_Free(param0->heap);
}

static int GlobalTerminalTransfer_StateCleanup(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    GlobalTerminalGds_EndConnection();
    param0->initialized = 0;
    return 1;
}

static int GlobalTerminalTransfer_StateDisconnect(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    DWC_ClearError();
    DWC_CleanupInet();

    CommManager_EndGlobalWifi();
    param0->unused_3C8 = 0;

    return 1;
}

static int GlobalTerminalTransfer_StateError(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    int v0, v1;

    v0 = NintendoWFC_GetErrorCode(-param0->errorCode, param0->errorType);
    GlobalTerminalTransfer_FormatError(param0, v0, -param0->errorCode);

    return 1;
}

static int GlobalTerminalTransfer_StateWaitInput(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    if ((gSystem.pressedKeys & PAD_BUTTON_A) || (gSystem.pressedKeys & PAD_BUTTON_B)) {
        GlobalTerminalTransfer_ReportMessage(param0, NULL);
        return 1;
    }

    return 0;
}

int GlobalTerminalTransfer_UploadProfilePhoto(VsRecorderViewerTransferContext *param0, PlayerProfile *param1, DressUpPhoto *photo)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    GlobalTerminal_SerializePlayerProfile(param0->saveData, param1, &param0->payload.profilePhotoData.profile);
    GlobalTerminal_SerializeDressUpPhoto(param0->saveData, photo, &param0->payload.profilePhotoData.photo);

    param0->delayTimer = 60;
    param0->requestID = 20000;

    return 1;
}

int GlobalTerminalTransfer_UploadProfile(VsRecorderViewerTransferContext *param0, int param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->payload.uploadParams.val2.id = param1;
    param0->requestID = 20001;

    return 1;
}

int GlobalTerminalTransfer_UploadProfileBox(VsRecorderViewerTransferContext *param0, int param1, PlayerProfile *param2, const PCBoxes *pcBoxes, int param4)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->payload.uploadParams.val1.id = param1;
    param0->payload.uploadParams.val1.box = param4;

    GlobalTerminal_SerializePlayerProfile(param0->saveData, param2, &param0->payload.boxData.profile);
    GlobalTerminal_SerializePCBox(param0->saveData, pcBoxes, param4, &param0->payload.boxData.box, param0->heapID);
    GlobalTerminal_UpdatePCBoxChecksum(param0->saveData, &param0->payload.boxData.box, param1);

    param0->delayTimer = 60;
    param0->requestID = 21000;

    return 1;
}

int GlobalTerminalTransfer_UploadBox(VsRecorderViewerTransferContext *param0, int param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->payload.uploadParams.val1.id = param1;
    param0->requestID = 21001;

    return 1;
}

int GlobalTerminalTransfer_UploadPlayTime(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->requestID = 22000;
    return 1;
}

int GlobalTerminalTransfer_UploadPlayTimeProfile(VsRecorderViewerTransferContext *param0, PlayerProfile *param1, GlobalTerminalPlayTimeEntry param2[])
{
    PlayTime *playTime;
    int v1;

    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    playTime = SaveData_GetPlayTime(param0->saveData);
    MI_CpuCopy8(playTime, &param0->payload.rankingsProfile.playTime, sizeof(VsRecorderViewerRankingsPlayTimeStamp));
    GlobalTerminal_SerializeProfileSummary(param0->saveData, param1, &param0->payload.rankingsProfile.summary);

    for (v1 = 0; v1 < 3; v1++) {
        param0->payload.rankingsProfile.entries[v1] = param2[v1];
    }

    param0->requestID = 22001;
    return 1;
}

int GlobalTerminalTransfer_UploadBattleRecording(VsRecorderViewerTransferContext *param0, PlayerProfile *param1)
{
    PlayerProfile *v0;

    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    GF_ASSERT((BattleRecording_SaveSize() - sizeof(u32)) == sizeof(VsRecorderViewerTransferRecordData));
    GF_ASSERT(sizeof(GlobalTerminalPlayerProfile) == sizeof(PlayerProfile));

    param0->payload.recordData = (VsRecorderViewerTransferRecordData *)BattleRecording_GetData();

    VsRecorderViewerRecording_EncodeData(param0->saveData);

    v0 = BattleRecording_GetHeader();
    MI_CpuCopy8(param1, v0, sizeof(GlobalTerminalPlayerProfile));

    param0->delayTimer = 60;
    param0->requestID = 23000;

    return 1;
}

int GlobalTerminalTransfer_UploadRecord(VsRecorderViewerTransferContext *param0, u16 param1, u8 param2, u8 param3, u8 param4)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->payload.playTime, sizeof(VsRecorderViewerTransferPlayTime));

    param0->payload.playTime.recordId = param1;
    param0->payload.playTime.result = param2;
    param0->payload.playTime.value1 = param3;
    param0->payload.playTime.value2 = param4;
    param0->payload.playTime.size = 0x140;
    param0->recordType = 0;
    param0->requestID = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordDefault(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->payload.playTime, sizeof(VsRecorderViewerTransferPlayTime));

    param0->payload.playTime.recordId = 0xffff;
    param0->payload.playTime.result = UnkEnum_0202F510_37;
    param0->payload.playTime.value1 = 0xff;
    param0->payload.playTime.value2 = 0xff;
    param0->payload.playTime.size = 0x140;
    param0->recordType = 0;
    param0->requestID = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadEmptyRecord(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->payload.playTime, sizeof(VsRecorderViewerTransferPlayTime));

    param0->payload.playTime.recordId = 0xffff;
    param0->payload.playTime.result = 0xff;
    param0->payload.playTime.value1 = 0xff;
    param0->payload.playTime.value2 = 0xff;
    param0->payload.playTime.size = 0x140;
    param0->recordType = 0;
    param0->requestID = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordAlt(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->payload.value, sizeof(VsRecorderViewerTransferValue));
    param0->payload.value.value = 0x140;
    param0->recordType = 1;
    param0->requestID = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordAlt2(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->payload.value, sizeof(VsRecorderViewerTransferValue));

    param0->payload.value.value = 0x140;
    param0->recordType = 2;
    param0->requestID = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadId(VsRecorderViewerTransferContext *param0, u64 param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->payload.uploadParams.val3.value = param1;
    param0->requestID = 23002;

    return 1;
}

int GlobalTerminalTransfer_UploadId2(VsRecorderViewerTransferContext *param0, u64 param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->payload.uploadParams.val3.value = param1;
    param0->requestID = 23003;

    return 1;
}

int GlobalTerminalTransfer_Main(VsRecorderViewerTransferContext *param0)
{
    int v0;

    if (param0->initialized == 1) {
        if (param0->requestID != 23004) {
            if (param0->delayTimer > 0) {
                param0->delayTimer--;
            } else {
                switch (GlobalTerminalGds_GetConnectionState()) {
                case 1:
                case 7:
                case 8:
                case 9:
                    v0 = GlobalTerminalTransfer_ProcessRequest(param0);

                    if (v0 == 1) {
                        param0->requestID = 23004;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        GlobalTerminalTransfer_ProcessConnection(param0);

        if (param0->callback.process != NULL) {
            if (param0->callback.process(param0, &param0->callback) == 1) {
                param0->callback.process = NULL;

                if (param0->callback.onComplete != NULL) {
                    param0->callback.onComplete(param0->callbacks.userData, &param0->status);
                    param0->callback.onComplete = NULL;
                }

                MI_CpuClear8(&param0->callback, sizeof(GlobalTerminalTransferCallback));
                param0->pendingRequestID = 23004;
            }
        }
    }

    if (sGlobalTerminalTransferHandlerTable[param0->handlerIndex] != NULL) {
        int v1;

        v1 = sGlobalTerminalTransferHandlerTable[param0->handlerIndex][param0->handlerStep](param0, &param0->taskState);

        switch (v1) {
        case 0:
            break;
        case 1:
            MI_CpuClear8(&param0->taskState, sizeof(GlobalTerminalTaskState));
            param0->handlerStep++;
            MI_CpuClear8(&param0->taskState, sizeof(GlobalTerminalTaskState));

            if (sGlobalTerminalTransferHandlerTable[param0->handlerIndex][param0->handlerStep] == NULL) {
                param0->handlerStep = 0;
                param0->handlerIndex = 0;
            }
            break;
        case 2:
            MI_CpuClear8(&param0->taskState, sizeof(GlobalTerminalTaskState));
            param0->handlerStep = 0;
            break;
        }
    }

    return 1;
}

static int GlobalTerminalTransfer_ProcessRequest(VsRecorderViewerTransferContext *param0)
{
    int v0 = 0;

    switch (param0->requestID) {
    case 20000:
        v0 = GlobalTerminalGds_UploadProfilePhoto(&param0->payload.profilePhotoData, param0->responseBuffer);
        break;
    case 20001:
        v0 = GlobalTerminalGds_UploadProfile(param0->payload.uploadParams.val2.id, param0->responseBuffer);
        break;
    case 21000:
        v0 = GlobalTerminalGds_UploadProfileBox(param0->payload.uploadParams.val1.id, &param0->payload.boxData, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 21001:
        v0 = GlobalTerminalGds_UploadBox(param0->payload.uploadParams.val1.id, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 22000:
        v0 = GlobalTerminalGds_UploadPlayTime(param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 22001:
        v0 = GlobalTerminalGds_UploadPlayTimeProfile(&param0->payload.rankingsProfile, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23000:
        v0 = GlobalTerminalGds_UploadBattleRecording(param0->payload.recordData, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23001:
        switch (param0->recordType) {
        case 0:
            v0 = GlobalTerminalGds_UploadRecord(&param0->payload.playTime, param0->responseBuffer);
            break;
        case 1:
            v0 = GlobalTerminalGds_UploadRecordAlt(&param0->payload.value, param0->responseBuffer);
            break;
        case 2:
            v0 = GlobalTerminalGds_UploadRecordAlt2(
                &param0->payload.value, param0->responseBuffer);
            break;
        }

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23002:
        v0 = GlobalTerminalGds_UploadId(param0->payload.uploadParams.val3.value, 0x140, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23003:
        v0 = GlobalTerminalGds_UploadIdAlt(param0->payload.uploadParams.val3.value, param0->responseBuffer);

        if (v0 == 1) {
            (void)0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    if (v0 == 1) {
        param0->pendingRequestID = param0->requestID;
    } else {
        (void)0;
    }

    return v0;
}

static int GlobalTerminalTransfer_ProcessConnection(VsRecorderViewerTransferContext *param0)
{
    if (param0->pendingRequestID == 23004) {
        return 1;
    }

    param0->connectionState = GlobalTerminalGds_GetConnectionState();

    if (param0->connectionState != param0->prevConnectionState) {
        switch (param0->connectionState) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            param0->status.category = 1;
            param0->status.value = 0;
            param0->status.index = 7;
            param0->status.done = 1;
            param0->callback.process = GlobalTerminalTransfer_OnFailReport;
            break;
        case 8:
            param0->callback.process = GlobalTerminalTransfer_OnComplete;
            GlobalTerminalTransfer_Dispatch(param0);
            break;
        case 9:
            param0->status.category = 0;
            param0->status.value = 0;
            param0->status.index = GlobalTerminalGds_GetErrorCode();
            param0->status.done = 1;
            param0->callback.process = GlobalTerminalTransfer_OnFailReport;
            break;
        }

        param0->prevConnectionState = param0->connectionState;
    }

    return 1;
}

static BOOL GlobalTerminalTransfer_OnComplete(void *param0, void *param1)
{
    VsRecorderViewerTransferContext *v0 = param0;
    GlobalTerminalTransferCallback *v1 = param1;
    return 1;
}

static BOOL GlobalTerminalTransfer_OnCompleteAlt(void *param0, void *param1)
{
    return 1;
}

static BOOL GlobalTerminalTransfer_OnCompleteSave(void *param0, void *param1)
{
    VsRecorderViewerTransferContext *v0 = param0;
    GlobalTerminalTransferCallback *v1 = param1;
    GlobalTerminalGdsResponse *v2;
    GlobalTerminalBattleRecordingResult *v3;
    int v4;

    v2 = GlobalTerminalGds_GetResponseData();
    v3 = (GlobalTerminalBattleRecordingResult *)(v2->data);
    v4 = VsRecorderViewerRecording_SaveWithIdStep(v0->saveData, v3->recordingID, &v1->saveStep, &v1->saveResult);

    if ((v4 == 2) || (v4 == 3)) {
        return 1;
    }

    return 0;
}

static BOOL GlobalTerminalTransfer_OnFail(void *param0, void *param1)
{
    return 1;
}

static BOOL GlobalTerminalTransfer_OnFailAlt(void *param0, void *param1)
{
    return 1;
}

static BOOL GlobalTerminalTransfer_OnFailReport(void *param0, void *param1)
{
    VsRecorderViewerTransferContext *v0 = param0;
    GlobalTerminalTransferCallback *v1 = param1;

    return 1;
}

static int GlobalTerminalTransfer_Dispatch(VsRecorderViewerTransferContext *param0)
{
    GlobalTerminalGdsResponse *v0;
    int v1;
    int v2 = 1;

    v0 = GlobalTerminalGds_GetResponseData();
    v1 = GlobalTerminalGds_GetResponseLength();

    GF_ASSERT(param0->pendingRequestID == v0->requestId);

    param0->callback.onComplete = NULL;

    switch (v0->requestId) {
    case 20000:
        v2 = GlobalTerminalGds_HandleProfilePhoto(param0, v0);
        param0->callback.onComplete = param0->callbacks.profilePhotoCallback;

        if (v2 == 0) {
            param0->callback.process = GlobalTerminalTransfer_OnFail;
        }
        break;
    case 20001:
        v2 = GlobalTerminalGds_HandleProfile(param0, v0);
        param0->callback.onComplete = param0->callbacks.profileCallback;
        break;
    case 21000:
        v2 = GlobalTerminalGds_HandleProfileBox(param0, v0);
        param0->callback.onComplete = param0->callbacks.profileBoxCompleteCallback;

        if (v2 == 0) {
            param0->callback.process = GlobalTerminalTransfer_OnFailAlt;
        }
        break;
    case 21001:
        v2 = GlobalTerminalGds_HandleBox(param0, v0);
        param0->callback.onComplete = param0->callbacks.boxCompleteCallback;
        break;
    case 22000:
        v2 = GlobalTerminalGds_HandlePlayTime(param0, v0);
        param0->callback.onComplete = param0->callbacks.loadPlayTimeCallback;
        break;
    case 22001:
        v2 = GlobalTerminalGds_HandlePlayTimeProfile(param0, v0);
        param0->callback.onComplete = param0->callbacks.loadPlayTimeProfileCallback;
        break;
    case 23000:
        v2 = GlobalTerminalGds_HandleBattleRecording(param0, v0);
        param0->callback.onComplete = param0->callbacks.setBattleRecordingIdCallback;

        if (v2 == 0) {
            param0->callback.process = GlobalTerminalTransfer_OnCompleteAlt;
        } else {
            param0->callback.process = GlobalTerminalTransfer_OnCompleteSave;
        }
        break;
    case 23001:
        v2 = GlobalTerminalGds_HandleRecord(param0, v0);
        param0->callback.onComplete = param0->callbacks.loadRecordListCallback;
        break;
    case 23002:
        v2 = GlobalTerminalGds_HandleRecordAlt(param0, v0);
        param0->callback.onComplete = param0->callbacks.loadRecordAltCallback;
        break;
    case 23003:
        v2 = GlobalTerminalGds_HandleRecordAlt2(param0, v0);
        param0->callback.onComplete = param0->callbacks.noopCallback;
        break;
    case 0:
    default:
        break;
    }

    if (v2 == 0) {
        param0->status.category = 2;
        param0->status.value = v0->requestId;
        param0->status.index = v0->status;
        param0->status.done = 1;
    } else {
        param0->status.done = 0;
    }

    return v2;
}

BOOL GlobalTerminalTransfer_GetState(VsRecorderViewerTransferContext *param0, VsRecorderViewerTransferStatus **param1)
{
    *param1 = &param0->status;
    return param0->status.done;
}

static void GlobalTerminalTransfer_ReportMessage(VsRecorderViewerTransferContext *param0, String *param1)
{
    param0->reportMessage(param0->reportArg, param1);
}

static void GlobalTerminalTransfer_FormatError(VsRecorderViewerTransferContext *param0, int param1, int param2)
{
    int v0;
    String *v1;

    if (param1 != -1) {
        v0 = 0 + param1;
    } else {
        v0 = 11;
    }

    StringTemplate_SetNumber(param0->stringTemplate, 0, param2, 5, 2, 1);
    v1 = MessageLoader_GetNewString(param0->messageLoader, v0);
    StringTemplate_Format(param0->stringTemplate, param0->string, v1);
    String_Free(v1);
    GlobalTerminalTransfer_ReportMessage(param0, param0->string);
}

BOOL GlobalTerminalTransfer_IsIdle(VsRecorderViewerTransferContext *param0)
{
    if ((GlobalTerminalTransfer_GetConnectionState(param0) == 0) && (param0->requestID == 23004) && (param0->pendingRequestID == 23004)) {
        return 1;
    }

    return 0;
}

static int GlobalTerminalTransfer_GetConnectionState(VsRecorderViewerTransferContext *param0)
{
    return param0->handlerIndex;
}

static OSHeapHandle sGlobalTerminalHeap;

static void *GlobalTerminalTransfer_InitHeap(enum HeapID heapID)
{
    void *v0;
    void *v1;
    void *v2;
    int v3 = 0x2000;

    v0 = Heap_Alloc(heapID, v3);
    v2 = v0;
    v1 = (void *)((u32)v0 + v3);
    v0 = OS_InitAlloc(OS_ARENA_MAIN, v0, v1, 1);

    OS_SetArenaLo(OS_ARENA_MAIN, v0);

    v0 = (void *)(((u32)(v0) + 32 - 1) & ~(32 - 1));
    v1 = (void *)(((u32)(v1) + 32 - 1) & ~(32 - 1));

    sGlobalTerminalHeap = OS_CreateHeap(OS_ARENA_MAIN, v0, v1);
    OS_SetCurrentHeap(OS_ARENA_MAIN, sGlobalTerminalHeap);

    return v2;
}

static void GlobalTerminalTransfer_ClearHeap(void)
{
    OS_ClearAlloc(OS_ARENA_MAIN);
}
