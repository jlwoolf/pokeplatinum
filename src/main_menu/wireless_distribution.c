#include "main_menu/wireless_distribution.h"

#include <crypto.h>
#include <nitro.h>
#include <nitro/cht.h>
#include <nitro/wm.h>
#include <string.h>

#include "main_menu/funcptr_wireless_distribution.h"

typedef struct {
    u16 checksum;
    u16 chunkIndex;
    u32 totalSize;
    u8 data[104];
} WirelessDistributionChunk;

typedef struct {
    u8 wmSystemBuffer[3840] ATTRIBUTE_ALIGN(32);
    WMbssDesc bssDesc ATTRIBUTE_ALIGN(32);
    WMscanParam scanParam ATTRIBUTE_ALIGN(32);
    u8 recvBuffer[104];
    int hasReceivedChunk;
    CRYPTORC4Context rc4Context;
    int state;
    int error;
    u16 mode;
    u16 checksum;
    u16 totalChunks;
    u16 receivedChunkCount;
    u32 dataSize;
    u32 retryCount;
    int currentChunkIndex;
    int linkLevel;
    u8 peerMacAddress[6];
    u16 channelIndex;
    u8 *dataBuffer;
    WirelessDistributionStateFunc stateFunc;
    u8 receivedChunkFlags[1261];
} WirelessDistributionContext;

typedef void (*WirelessManagerScanFunc)(WMBssDesc *);

static void WirelessDistribution_InitTransfer(WirelessDistributionChunk *param0);
static int WirelessDistribution_ReceiveChunk(WirelessDistributionChunk *param0);
static void WirelessDistribution_IndCallback(void *param0);
static BOOL WirelessDistribution_Initialize(void);
static void WirelessDistribution_InitCallback(void *param0);
static BOOL WirelessDistribution_BeginScan(void);
static void WirelessDistribution_ScanCallback(void *param0);
static BOOL WirelessDistribution_EndScan(void);
static void WirelessDistribution_EndScanCallback(void *param0);
static void WirelessDistribution_EndCallback(void *param0);
static BOOL WirelessDistribution_Reset(void);
static void WirelessDistribution_ResetCallback(void *param0);

static WirelessDistributionContext *sWirelessDistribution;
static void (*sWirelessDistributionPrint)(const char *, ...) = NULL;

static void WirelessDistribution_SetState(int param0)
{
    static const char *v0[] = {
        "mywh_SYSSTATE_STOP",
        "mywh_SYSSTATE_IDLE",
        "mywh_SYSSTATE_SCANNING",
        "mywh_SYSSTATE_BUSY",
        "mywh_SYSSTATE_CONNECTED",
        "mywh_SYSSTATE_DATASHARING",
        "mywh_SYSSTATE_KEYSHARING",
        "mywh_SYSSTATE_MEASURECHANNEL",
        "mywh_SYSSTATE_CONNECT_FAIL",
        "mywh_SYSSTATE_ERROR"
    };

    if (sWirelessDistributionPrint) {
        sWirelessDistributionPrint("%s -> ", v0[(*sWirelessDistribution).state]);
    }

    (*sWirelessDistribution).state = param0;

    if (sWirelessDistributionPrint) {
        sWirelessDistributionPrint("%s\n", v0[(*sWirelessDistribution).state]);
    }
}

static void WirelessDistribution_SetError(int param0)
{
    if (((*sWirelessDistribution).state == 9) || ((*sWirelessDistribution).state == 10)) {
        return;
    }

    (*sWirelessDistribution).error = param0;
}

static BOOL WirelessDistribution_StartScan(void)
{
    sWirelessDistribution->state != 4 ? (void)0 : OS_Terminate();

    WirelessDistribution_SetState(2);

    *(u16 *)(&((*sWirelessDistribution).scanParam).bssid[4]) = 0xffff;
    *(u16 *)(&((*sWirelessDistribution).scanParam).bssid[2]) = 0xffff;
    *(u16 *)(&((*sWirelessDistribution).scanParam).bssid[0]) = 0xffff;

    if (!WirelessDistribution_BeginScan()) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }

        return 0;
    }

    (*sWirelessDistribution).mode = 2;

    if ((*sWirelessDistribution).stateFunc != NULL) {
        (*sWirelessDistribution).stateFunc(0);
    }

    return 1;
}

static BOOL WirelessDistribution_BeginScan(void)
{
    WMErrCode v0;
    u16 v1;

    (void)(((*sWirelessDistribution).state == 2) || (OS_Terminate(), 0));

    v1 = WM_GetAllowedChannel();

    if (v1 == 0x8000) {
        do {
            WirelessDistribution_SetError(WM_ERRCODE_ILLEGAL_STATE);
        } while (0);

        return 0;
    }

    if (v1 == 0) {
        do {
            WirelessDistribution_SetError(22);
        } while (0);

        return 0;
    }

    if ((*sWirelessDistribution).channelIndex >= 16) {
        int v2 = (*sWirelessDistribution).channelIndex - 16;
        int v3;

        for (v3 = 0; v3 < 13; v3++) {
            v2 = (v2 + 1) % 13;

            if (v1 & (1 << v2)) {
                break;
            }
        }

        (*sWirelessDistribution).channelIndex = (u16)(16 + v2);
        (*sWirelessDistribution).scanParam.channel = (u16)(v2 + 1);
    } else {
        (*sWirelessDistribution).scanParam.channel = (*sWirelessDistribution).channelIndex;
    }

    (*sWirelessDistribution).scanParam.maxChannelTime = 220;
    (*sWirelessDistribution).scanParam.scanBuf = &((*sWirelessDistribution).bssDesc);

    if ((*sWirelessDistribution).mode == 3) {
        int v4;

        for (v4 = 0; v4 < 6; v4++) {
            (*sWirelessDistribution).scanParam.bssid[v4] = (*sWirelessDistribution).peerMacAddress[v4];
        }
    }

    v0 = WM_StartScan(WirelessDistribution_ScanCallback, &((*sWirelessDistribution).scanParam));

    if (v0 != WM_ERRCODE_OPERATING) {
        do {
            WirelessDistribution_SetError(v0);
        } while (0);

        return 0;
    }

    return 1;
}

static void WirelessDistribution_ScanCallback(void *param0)
{
    WMstartScanCallback *v0 = (WMstartScanCallback *)param0;

    if (v0->errcode != WM_ERRCODE_SUCCESS) {
        do {
            WirelessDistribution_SetError(v0->errcode);
        } while (0);

        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }

        return;
    }

    if ((*sWirelessDistribution).state != 2) {
        if (!WirelessDistribution_EndScan()) {
            WirelessDistribution_SetState(9);

            if ((*sWirelessDistribution).stateFunc != NULL) {
                (*sWirelessDistribution).stateFunc(4);
            }
        }

        return;
    }

    switch (v0->state) {
    case WM_STATECODE_SCAN_START:
        return;
    case WM_STATECODE_PARENT_NOT_FOUND:
        break;
    case WM_STATECODE_PARENT_FOUND:
        DC_InvalidateRange(&((*sWirelessDistribution).bssDesc), sizeof(WMbssDesc));

        if ((v0->gameInfoLength < 8) || (v0->gameInfo.ggid != 0x400318)) {
            if (sWirelessDistributionPrint) {
                sWirelessDistributionPrint("not my parent ggid (%d != %d)\n", v0->gameInfo.ggid, 0x400318);
            }
            break;
        }

        (*sWirelessDistribution).linkLevel = v0->linkLevel;

        if ((*sWirelessDistribution).mode == 2) {
            WirelessDistribution_InitTransfer((WirelessDistributionChunk *)&(v0->gameInfo.userGameInfo[0]));

            {
                int v1;

                for (v1 = 0; v1 < 6; v1++) {
                    (*sWirelessDistribution).peerMacAddress[v1] = v0->macAddress[v1];
                }
            }

            (*sWirelessDistribution).channelIndex = (u16)((*sWirelessDistribution).channelIndex - 16 + 1);

            if ((*sWirelessDistribution).stateFunc != NULL) {
                (*sWirelessDistribution).stateFunc(1);
            }
        }

        if (WirelessDistribution_ReceiveChunk((WirelessDistributionChunk *)&(v0->gameInfo.userGameInfo[0]))) {
            (*sWirelessDistribution).mode = 4;
            WirelessDistribution_Stop();

            return;
        }
        break;
    }

    if (!WirelessDistribution_BeginScan()) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }
    }
}

static BOOL WirelessDistribution_EndScan(void)
{
    WMErrCode v0;

    v0 = WM_EndScan(WirelessDistribution_EndScanCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        do {
            WirelessDistribution_SetError(v0);
        } while (0);

        return 0;
    }

    return 1;
}

static void WirelessDistribution_EndScanCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode != WM_ERRCODE_SUCCESS) {
        do {
            WirelessDistribution_SetError(v0->errcode);
        } while (0);

        return;
    }

    WirelessDistribution_SetState(1);
}

static void WirelessDistribution_EndCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode != WM_ERRCODE_SUCCESS) {
        WirelessDistribution_SetState(10);
        return;
    }

    WirelessDistribution_SetState(0);

    if ((*sWirelessDistribution).stateFunc != NULL) {
        (*sWirelessDistribution).stateFunc(3);
    }
}

static BOOL WirelessDistribution_Init(void)
{
    (*sWirelessDistribution).error = WM_ERRCODE_SUCCESS;

    if (!WirelessDistribution_Initialize()) {
        return 0;
    }

    return 1;
}

static void WirelessDistribution_IndCallback(void *param0)
{
    WMindCallback *v0 = (WMindCallback *)param0;

    if (v0->errcode == WM_ERRCODE_FIFO_ERROR) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }
    }
}

static BOOL WirelessDistribution_Initialize(void)
{
    WMErrCode v0;

    WirelessDistribution_SetState(3);
    v0 = WM_Initialize(&((*sWirelessDistribution).wmSystemBuffer[0]), WirelessDistribution_InitCallback, 2);

    if (v0 != WM_ERRCODE_OPERATING) {
        do {
            WirelessDistribution_SetError(v0);
        } while (0);

        WirelessDistribution_SetState(10);
        return 0;
    }

    return 1;
}

static void WirelessDistribution_InitCallback(void *param0)
{
    WMErrCode v0;
    WMCallback *v1 = (WMCallback *)param0;

    if (v1->errcode != WM_ERRCODE_SUCCESS) {
        do {
            WirelessDistribution_SetError(v1->errcode);
        } while (0);

        WirelessDistribution_SetState(10);
        return;
    }

    v0 = WM_SetIndCallback(WirelessDistribution_IndCallback);

    if (v0 != WM_ERRCODE_SUCCESS) {
        do {
            WirelessDistribution_SetError(v0);
        } while (0);

        WirelessDistribution_SetState(10);
        return;
    }

    WirelessDistribution_SetState(1);
    (void)WirelessDistribution_StartScan();
}

static BOOL WirelessDistribution_Finalize(void)
{
    (void)(((*sWirelessDistribution).state == 1) || (OS_Terminate(), 0));

    WirelessDistribution_SetState(3);

    if (WM_End(WirelessDistribution_EndCallback) != WM_ERRCODE_OPERATING) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }

        return 0;
    }

    return 1;
}

BOOL WirelessDistribution_Stop(void)
{
    if ((*sWirelessDistribution).state == 1) {
        return WirelessDistribution_Finalize();
    }

    return WirelessDistribution_Reset();
}

static BOOL WirelessDistribution_Reset(void)
{
    WMErrCode v0;

    WirelessDistribution_SetState(3);
    v0 = WM_Reset(WirelessDistribution_ResetCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        do {
            WirelessDistribution_SetError(v0);
        } while (0);

        return 0;
    }

    return 1;
}

static void WirelessDistribution_ResetCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode != WM_ERRCODE_SUCCESS) {
        WirelessDistribution_SetState(9);
        do {
            WirelessDistribution_SetError(v0->errcode);
        } while (0);

        if ((*sWirelessDistribution).stateFunc != NULL) {
            (*sWirelessDistribution).stateFunc(4);
        }

        return;
    }

    WirelessDistribution_SetState(1);
    WirelessDistribution_Finalize();
}

BOOL WirelessDistribution_Start(void *param0, WirelessDistributionStateFunc param1, void *param2)
{
    sWirelessDistribution = (WirelessDistributionContext *)(((u32)param2 + 31) / 32 * 32);
    (*sWirelessDistribution).state = 0;
    (*sWirelessDistribution).mode = 1;
    (*sWirelessDistribution).dataBuffer = (u8 *)param0;
    (*sWirelessDistribution).totalChunks = 0;
    (*sWirelessDistribution).receivedChunkCount = 0;
    (*sWirelessDistribution).stateFunc = param1;
    (*sWirelessDistribution).channelIndex = 16 + 0;
    (*sWirelessDistribution).hasReceivedChunk = 0;
    (*sWirelessDistribution).linkLevel = -1;

    return WirelessDistribution_Init();
}

static void WirelessDistribution_InitTransfer(WirelessDistributionChunk *param0)
{
    int v0;

    (*sWirelessDistribution).hasReceivedChunk = 0;
    (*sWirelessDistribution).mode = 3;
    (*sWirelessDistribution).checksum = param0->checksum;
    (*sWirelessDistribution).dataSize = param0->totalSize;
    (*sWirelessDistribution).totalChunks = (u16)(((*sWirelessDistribution).dataSize - 1) / (WM_SIZE_USER_GAMEINFO - 8) + 1);
    (*sWirelessDistribution).receivedChunkCount = 0;
    (*sWirelessDistribution).retryCount = 0;

    for (v0 = 0; v0 < (*sWirelessDistribution).totalChunks; v0++) {
        (*sWirelessDistribution).receivedChunkFlags[v0] = 0;
    }
}

static int WirelessDistribution_ReceiveChunk(WirelessDistributionChunk *param0)
{
    if (((*sWirelessDistribution).checksum != param0->checksum) || ((*sWirelessDistribution).dataSize != param0->totalSize)) {
        if ((*sWirelessDistribution).retryCount++ >= 16) {
            WirelessDistribution_InitTransfer(param0);

            if ((*sWirelessDistribution).stateFunc != NULL) {
                (*sWirelessDistribution).stateFunc(5);
            }
        } else {
            return 0;
        }
    }

    if (param0->chunkIndex == 0xffff) {
        MI_CpuCopy32(&(param0->data[0]), &((*sWirelessDistribution).recvBuffer[0]), (WM_SIZE_USER_GAMEINFO - 8));
        (*sWirelessDistribution).hasReceivedChunk = 1;
    } else {
        (*sWirelessDistribution).currentChunkIndex = param0->chunkIndex;

        if (param0->chunkIndex >= (*sWirelessDistribution).totalChunks) {
            if ((*sWirelessDistribution).stateFunc != NULL) {
                (*sWirelessDistribution).stateFunc(4);
            }

            WirelessDistribution_SetState(9);
        }

        if ((*sWirelessDistribution).receivedChunkFlags[param0->chunkIndex] == 0) {
            (*sWirelessDistribution).receivedChunkFlags[param0->chunkIndex] = 1;

            if (param0->chunkIndex == (*sWirelessDistribution).totalChunks - 1) {
                MI_CpuCopy32(&(param0->data[0]), &((*sWirelessDistribution).dataBuffer[param0->chunkIndex * (WM_SIZE_USER_GAMEINFO - 8)]), (*sWirelessDistribution).dataSize - param0->chunkIndex * (WM_SIZE_USER_GAMEINFO - 8));
            } else {
                MI_CpuCopy32(&(param0->data[0]), &((*sWirelessDistribution).dataBuffer[param0->chunkIndex * (WM_SIZE_USER_GAMEINFO - 8)]), (WM_SIZE_USER_GAMEINFO - 8));
            }

            (*sWirelessDistribution).receivedChunkCount++;

            if ((*sWirelessDistribution).receivedChunkCount == (*sWirelessDistribution).totalChunks) {
                if ((*sWirelessDistribution).stateFunc != NULL) {
                    (*sWirelessDistribution).stateFunc(2);
                }

                return 1;
            }
        }
    }

    return 0;
}

static u16 WirelessDistribution_Checksum(u8 *param0, u32 param1)
{
    u16 v0, v1;
    u16 *v2 = (u16 *)param0;

    v0 = 0;

    for (v1 = 0; v1 < param1 / 2; v1++) {
        v0 += v2[v1];
        v0 = (u16)((v0 << 1) | (v0 >> 15));
    }

    return v0;
}

int WirelessDistribution_VerifyData(void)
{
    {
        u16 v0[4];
        u16 *v1;

        v1 = (u16 *)&((*sWirelessDistribution).peerMacAddress[0]);
        v0[0] = v1[0];
        v0[3] = v1[1];
        v0[2] = v1[2];
        v0[1] = (*sWirelessDistribution).checksum;

        {
            int v2;
            u16 v5 = 0x3fa2;

            for (v2 = 0; v2 < 4; v2++) {
                v0[v2] = v0[v2] ^ v5;
                v5 = v0[v2];
            }
        }

        {
            u8 *v3 = (u8 *)&(v0[0]);
            int v4;

            for (v4 = 0; v4 < 8; v4++) {
                (void)0;
            }
        }

        CRYPTO_RC4Init(&((*sWirelessDistribution).rc4Context), &(v0[0]), 8);
        CRYPTO_RC4Encrypt(&((*sWirelessDistribution).rc4Context), (*sWirelessDistribution).dataBuffer, (*sWirelessDistribution).dataSize, (*sWirelessDistribution).dataBuffer);

        MI_CpuClear32(&((*sWirelessDistribution).rc4Context), sizeof((*sWirelessDistribution).rc4Context));
    }

    return WirelessDistribution_Checksum((*sWirelessDistribution).dataBuffer, (*sWirelessDistribution).dataSize) == (*sWirelessDistribution).checksum;
}

int WirelessDistribution_GetContextSize(void)
{
    return sizeof(WirelessDistributionContext) + 32;
}

void *WirelessDistribution_GetData(void)
{
    if ((*sWirelessDistribution).hasReceivedChunk) {
        return &((*sWirelessDistribution).recvBuffer[0]);
    }

    return NULL;
}
