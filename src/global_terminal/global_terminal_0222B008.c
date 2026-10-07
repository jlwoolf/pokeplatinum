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
    param0->unk_150 = param1->unk_0C;
    param0->unk_08 = param1->unk_3C;
    param0->unk_04 = param1->unk_38;
    param0->unk_14C = -1;
    param0->unk_3E8 = 23004;
    param0->unk_3EC = 23004;
    param0->unk_3B4 = Heap_Alloc(param1->heapID, ov61_0222DE8C(-1));

    MI_CpuClear8(param0->unk_3B4, ov61_0222DE8C(-1));

    param0->unk_3F4 = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0695, param1->heapID);
    param0->unk_3F8 = StringTemplate_Default(param1->heapID);
    param0->unk_3FC = String_Init((16 * 8 * 2), param1->heapID);
    param0->unk_18C = GlobalTerminalTransfer_InitHeap(param1->heapID);
    param0->unk_0C.unk_00 = param1->unk_00;
    param0->unk_0C.unk_04 = GAME_VERSION;
    param0->unk_0C.language = GAME_LANGUAGE;

    v0 = ov61_0222DCDC(&param0->unk_0C);
    GF_ASSERT(v0 == 1);

    param0->unk_3C4 = 1;
    param0->unk_3B8 = 1;

    return 1;
}

void GlobalTerminalTransfer_Free(VsRecorderViewerTransferContext *param0)
{
    ov61_0222DCFC();

    param0->unk_3C4 = 0;

    String_Free(param0->unk_3FC);
    StringTemplate_Free(param0->unk_3F8);
    MessageLoader_Free(param0->unk_3F4);
    Heap_Free(param0->unk_3B4);
    GlobalTerminalTransfer_ClearHeap();
    Heap_Free(param0->unk_18C);
}

static int GlobalTerminalTransfer_StateCleanup(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    ov61_0222DCFC();
    param0->unk_3C4 = 0;
    return 1;
}

static int GlobalTerminalTransfer_StateDisconnect(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    DWC_ClearError();
    DWC_CleanupInet();

    CommManager_EndGlobalWifi();
    param0->unk_3C8 = 0;

    return 1;
}

static int GlobalTerminalTransfer_StateError(VsRecorderViewerTransferContext *param0, GlobalTerminalTaskState *param1)
{
    int v0, v1;

    v0 = NintendoWFC_GetErrorCode(-param0->unk_3E0, param0->unk_3E4);
    GlobalTerminalTransfer_FormatError(param0, v0, -param0->unk_3E0);

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

    GlobalTerminal_SerializePlayerProfile(param0->saveData, param1, &param0->unk_190.unk_00_val1.unk_00);
    GlobalTerminal_SerializeDressUpPhoto(param0->saveData, photo, &param0->unk_190.unk_00_val1.unk_80);

    param0->unk_40E = 60;
    param0->unk_3E8 = 20000;

    return 1;
}

int GlobalTerminalTransfer_UploadProfile(VsRecorderViewerTransferContext *param0, int param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_190.unk_21C.val2.unk_00 = param1;
    param0->unk_3E8 = 20001;

    return 1;
}

int GlobalTerminalTransfer_UploadProfileBox(VsRecorderViewerTransferContext *param0, int param1, PlayerProfile *param2, const PCBoxes *pcBoxes, int param4)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_190.unk_21C.val1.unk_00 = param1;
    param0->unk_190.unk_21C.val1.unk_01 = param4;

    GlobalTerminal_SerializePlayerProfile(param0->saveData, param2, &param0->unk_190.unk_00_val2.unk_00);
    GlobalTerminal_SerializePCBox(param0->saveData, pcBoxes, param4, &param0->unk_190.unk_00_val2.unk_80, param0->heapID);
    GlobalTerminal_UpdatePCBoxChecksum(param0->saveData, &param0->unk_190.unk_00_val2.unk_80, param1);

    param0->unk_40E = 60;
    param0->unk_3E8 = 21000;

    return 1;
}

int GlobalTerminalTransfer_UploadBox(VsRecorderViewerTransferContext *param0, int param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_190.unk_21C.val1.unk_00 = param1;
    param0->unk_3E8 = 21001;

    return 1;
}

int GlobalTerminalTransfer_UploadPlayTime(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_3E8 = 22000;
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
    MI_CpuCopy8(playTime, &param0->unk_190.unk_00_val3.unk_08, sizeof(VsRecorderViewerRankingsPlayTimeStamp));
    GlobalTerminal_SerializeProfileSummary(param0->saveData, param1, &param0->unk_190.unk_00_val3.unk_00);

    for (v1 = 0; v1 < 3; v1++) {
        param0->unk_190.unk_00_val3.unk_0C[v1] = param2[v1];
    }

    param0->unk_3E8 = 22001;
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

    param0->unk_190.unk_00_val4 = (VsRecorderViewerTransferRecordData *)BattleRecording_GetData();

    VsRecorderViewerRecording_EncodeData(param0->saveData);

    v0 = BattleRecording_GetHeader();
    MI_CpuCopy8(param1, v0, sizeof(GlobalTerminalPlayerProfile));

    param0->unk_40E = 60;
    param0->unk_3E8 = 23000;

    return 1;
}

int GlobalTerminalTransfer_UploadRecord(VsRecorderViewerTransferContext *param0, u16 param1, u8 param2, u8 param3, u8 param4)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->unk_190.unk_00_val5, sizeof(VsRecorderViewerTransferPlayTime));

    param0->unk_190.unk_00_val5.unk_00 = param1;
    param0->unk_190.unk_00_val5.unk_02 = param2;
    param0->unk_190.unk_00_val5.unk_03 = param3;
    param0->unk_190.unk_00_val5.unk_04 = param4;
    param0->unk_190.unk_00_val5.unk_08 = 0x140;
    param0->unk_3F0 = 0;
    param0->unk_3E8 = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordDefault(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->unk_190.unk_00_val5, sizeof(VsRecorderViewerTransferPlayTime));

    param0->unk_190.unk_00_val5.unk_00 = 0xffff;
    param0->unk_190.unk_00_val5.unk_02 = UnkEnum_0202F510_37;
    param0->unk_190.unk_00_val5.unk_03 = 0xff;
    param0->unk_190.unk_00_val5.unk_04 = 0xff;
    param0->unk_190.unk_00_val5.unk_08 = 0x140;
    param0->unk_3F0 = 0;
    param0->unk_3E8 = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadEmptyRecord(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->unk_190.unk_00_val5, sizeof(VsRecorderViewerTransferPlayTime));

    param0->unk_190.unk_00_val5.unk_00 = 0xffff;
    param0->unk_190.unk_00_val5.unk_02 = 0xff;
    param0->unk_190.unk_00_val5.unk_03 = 0xff;
    param0->unk_190.unk_00_val5.unk_04 = 0xff;
    param0->unk_190.unk_00_val5.unk_08 = 0x140;
    param0->unk_3F0 = 0;
    param0->unk_3E8 = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordAlt(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->unk_190.unk_00_val6, sizeof(VsRecorderViewerTransferValue));
    param0->unk_190.unk_00_val6.unk_00 = 0x140;
    param0->unk_3F0 = 1;
    param0->unk_3E8 = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadRecordAlt2(VsRecorderViewerTransferContext *param0)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    MI_CpuClear8(&param0->unk_190.unk_00_val6, sizeof(VsRecorderViewerTransferValue));

    param0->unk_190.unk_00_val6.unk_00 = 0x140;
    param0->unk_3F0 = 2;
    param0->unk_3E8 = 23001;

    return 1;
}

int GlobalTerminalTransfer_UploadId(VsRecorderViewerTransferContext *param0, u64 param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_190.unk_21C.val3.unk_00 = param1;
    param0->unk_3E8 = 23002;

    return 1;
}

int GlobalTerminalTransfer_UploadId2(VsRecorderViewerTransferContext *param0, u64 param1)
{
    if (GlobalTerminalTransfer_IsIdle(param0) == 0) {
        return 0;
    }

    param0->unk_190.unk_21C.val3.unk_00 = param1;
    param0->unk_3E8 = 23003;

    return 1;
}

int GlobalTerminalTransfer_Main(VsRecorderViewerTransferContext *param0)
{
    int v0;

    if (param0->unk_3C4 == 1) {
        if (param0->unk_3E8 != 23004) {
            if (param0->unk_40E > 0) {
                param0->unk_40E--;
            } else {
                switch (ov61_0222DD08()) {
                case 1:
                case 7:
                case 8:
                case 9:
                    v0 = GlobalTerminalTransfer_ProcessRequest(param0);

                    if (v0 == 1) {
                        param0->unk_3E8 = 23004;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        GlobalTerminalTransfer_ProcessConnection(param0);

        if (param0->unk_400.unk_0C != NULL) {
            if (param0->unk_400.unk_0C(param0, &param0->unk_400) == 1) {
                param0->unk_400.unk_0C = NULL;

                if (param0->unk_400.unk_00 != NULL) {
                    param0->unk_400.unk_00(param0->unk_150.unk_00, &param0->unk_17C);
                    param0->unk_400.unk_00 = NULL;
                }

                MI_CpuClear8(&param0->unk_400, sizeof(GlobalTerminalTransferCallback));
                param0->unk_3EC = 23004;
            }
        }
    }

    if (sGlobalTerminalTransferHandlerTable[param0->unk_3BC] != NULL) {
        int v1;

        v1 = sGlobalTerminalTransferHandlerTable[param0->unk_3BC][param0->unk_3C0](param0, &param0->unk_3CC);

        switch (v1) {
        case 0:
            break;
        case 1:
            MI_CpuClear8(&param0->unk_3CC, sizeof(GlobalTerminalTaskState));
            param0->unk_3C0++;
            MI_CpuClear8(&param0->unk_3CC, sizeof(GlobalTerminalTaskState));

            if (sGlobalTerminalTransferHandlerTable[param0->unk_3BC][param0->unk_3C0] == NULL) {
                param0->unk_3C0 = 0;
                param0->unk_3BC = 0;
            }
            break;
        case 2:
            MI_CpuClear8(&param0->unk_3CC, sizeof(GlobalTerminalTaskState));
            param0->unk_3C0 = 0;
            break;
        }
    }

    return 1;
}

static int GlobalTerminalTransfer_ProcessRequest(VsRecorderViewerTransferContext *param0)
{
    int v0 = 0;

    switch (param0->unk_3E8) {
    case 20000:
        v0 = ov61_0222DD30(&param0->unk_190.unk_00_val1, param0->unk_3B4);
        break;
    case 20001:
        v0 = ov61_0222DD8C(param0->unk_190.unk_21C.val2.unk_00, param0->unk_3B4);
        break;
    case 21000:
        v0 = ov61_0222DDCC(param0->unk_190.unk_21C.val1.unk_00, &param0->unk_190.unk_00_val2, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 21001:
        v0 = ov61_0222DE34(param0->unk_190.unk_21C.val1.unk_00, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 22000:
        v0 = ov61_0222DE98(param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 22001:
        v0 = ov61_0222DEB8(&param0->unk_190.unk_00_val3, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23000:
        v0 = ov61_0222DF08(param0->unk_190.unk_00_val4, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23001:
        switch (param0->unk_3F0) {
        case 0:
            v0 = ov61_0222DF60(&param0->unk_190.unk_00_val5, param0->unk_3B4);
            break;
        case 1:
            v0 = ov61_0222DFA8(&param0->unk_190.unk_00_val6, param0->unk_3B4);
            break;
        case 2:
            v0 = ov61_0222E000(
                &param0->unk_190.unk_00_val6, param0->unk_3B4);
            break;
        }

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23002:
        v0 = ov61_0222E058(param0->unk_190.unk_21C.val3.unk_00, 0x140, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    case 23003:
        v0 = ov61_0222E08C(param0->unk_190.unk_21C.val3.unk_00, param0->unk_3B4);

        if (v0 == 1) {
            (void)0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    if (v0 == 1) {
        param0->unk_3EC = param0->unk_3E8;
    } else {
        (void)0;
    }

    return v0;
}

static int GlobalTerminalTransfer_ProcessConnection(VsRecorderViewerTransferContext *param0)
{
    if (param0->unk_3EC == 23004) {
        return 1;
    }

    param0->unk_148 = ov61_0222DD08();

    if (param0->unk_148 != param0->unk_14C) {
        switch (param0->unk_148) {
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
            param0->unk_17C.unk_04 = 1;
            param0->unk_17C.unk_08 = 0;
            param0->unk_17C.unk_0C = 7;
            param0->unk_17C.unk_00 = 1;
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnFailReport;
            break;
        case 8:
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnComplete;
            GlobalTerminalTransfer_Dispatch(param0);
            break;
        case 9:
            param0->unk_17C.unk_04 = 0;
            param0->unk_17C.unk_08 = 0;
            param0->unk_17C.unk_0C = ov61_0222DD24();
            param0->unk_17C.unk_00 = 1;
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnFailReport;
            break;
        }

        param0->unk_14C = param0->unk_148;
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

    v2 = ov61_0222DE80();
    v3 = (GlobalTerminalBattleRecordingResult *)(v2->unk_04);
    v4 = VsRecorderViewerRecording_SaveWithIdStep(v0->saveData, v3->unk_00, &v1->unk_04, &v1->unk_06);

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

    v0 = ov61_0222DE80();
    v1 = ov61_0222DE74();

    GF_ASSERT(param0->unk_3EC == v0->unk_00);

    param0->unk_400.unk_00 = NULL;

    switch (v0->unk_00) {
    case 20000:
        v2 = GlobalTerminalGds_HandleProfilePhoto(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_04;

        if (v2 == 0) {
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnFail;
        }
        break;
    case 20001:
        v2 = GlobalTerminalGds_HandleProfile(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_08;
        break;
    case 21000:
        v2 = GlobalTerminalGds_HandleProfileBox(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_0C;

        if (v2 == 0) {
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnFailAlt;
        }
        break;
    case 21001:
        v2 = GlobalTerminalGds_HandleBox(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_10;
        break;
    case 22000:
        v2 = GlobalTerminalGds_HandlePlayTime(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_14;
        break;
    case 22001:
        v2 = GlobalTerminalGds_HandlePlayTimeProfile(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_18;
        break;
    case 23000:
        v2 = GlobalTerminalGds_HandleBattleRecording(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_1C;

        if (v2 == 0) {
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnCompleteAlt;
        } else {
            param0->unk_400.unk_0C = GlobalTerminalTransfer_OnCompleteSave;
        }
        break;
    case 23001:
        v2 = GlobalTerminalGds_HandleRecord(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_20;
        break;
    case 23002:
        v2 = GlobalTerminalGds_HandleRecordAlt(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_24;
        break;
    case 23003:
        v2 = GlobalTerminalGds_HandleRecordAlt2(param0, v0);
        param0->unk_400.unk_00 = param0->unk_150.unk_28;
        break;
    case 0:
    default:
        break;
    }

    if (v2 == 0) {
        param0->unk_17C.unk_04 = 2;
        param0->unk_17C.unk_08 = v0->unk_00;
        param0->unk_17C.unk_0C = v0->unk_02;
        param0->unk_17C.unk_00 = 1;
    } else {
        param0->unk_17C.unk_00 = 0;
    }

    return v2;
}

BOOL GlobalTerminalTransfer_GetState(VsRecorderViewerTransferContext *param0, VsRecorderViewerTransferStatus **param1)
{
    *param1 = &param0->unk_17C;
    return param0->unk_17C.unk_00;
}

static void GlobalTerminalTransfer_ReportMessage(VsRecorderViewerTransferContext *param0, String *param1)
{
    param0->unk_04(param0->unk_08, param1);
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

    StringTemplate_SetNumber(param0->unk_3F8, 0, param2, 5, 2, 1);
    v1 = MessageLoader_GetNewString(param0->unk_3F4, v0);
    StringTemplate_Format(param0->unk_3F8, param0->unk_3FC, v1);
    String_Free(v1);
    GlobalTerminalTransfer_ReportMessage(param0, param0->unk_3FC);
}

BOOL GlobalTerminalTransfer_IsIdle(VsRecorderViewerTransferContext *param0)
{
    if ((GlobalTerminalTransfer_GetConnectionState(param0) == 0) && (param0->unk_3E8 == 23004) && (param0->unk_3EC == 23004)) {
        return 1;
    }

    return 0;
}

static int GlobalTerminalTransfer_GetConnectionState(VsRecorderViewerTransferContext *param0)
{
    return param0->unk_3BC;
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
