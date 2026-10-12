#include "main_menu/wireless_distribution.h"

#include <crypto.h>
#include <nitro.h>
#include <nitro/cht.h>
#include <nitro/wm.h>
#include <string.h>

#include "main_menu/funcptr_wireless_distribution.h"

typedef struct {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u8 unk_08[104];
} WirelessDistributionChunk;

typedef struct {
    u8 unk_00[3840] ATTRIBUTE_ALIGN(32);
    WMbssDesc unk_F00 ATTRIBUTE_ALIGN(32);
    WMscanParam unk_1034 ATTRIBUTE_ALIGN(32);
    u8 unk_1054[104];
    int unk_10BC;
    CRYPTORC4Context unk_10C0;
    int unk_11C4;
    int unk_11C8;
    u16 unk_11CC;
    u16 unk_11CE;
    u16 unk_11D0;
    u16 unk_11D2;
    u32 unk_11D4;
    u32 unk_11D8;
    int unk_11DC;
    int unk_11E0;
    u8 unk_11E4[6];
    u16 unk_11EA;
    u8 *unk_11EC;
    WirelessDistributionStateFunc unk_11F0;
    u8 unk_11F4[1261];
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
        sWirelessDistributionPrint("%s -> ", v0[(*sWirelessDistribution).unk_11C4]);
    }

    (*sWirelessDistribution).unk_11C4 = param0;

    if (sWirelessDistributionPrint) {
        sWirelessDistributionPrint("%s\n", v0[(*sWirelessDistribution).unk_11C4]);
    }
}

static void WirelessDistribution_SetError(int param0)
{
    if (((*sWirelessDistribution).unk_11C4 == 9) || ((*sWirelessDistribution).unk_11C4 == 10)) {
        return;
    }

    (*sWirelessDistribution).unk_11C8 = param0;
}

static BOOL WirelessDistribution_StartScan(void)
{
    sWirelessDistribution->unk_11C4 != 4 ? (void)0 : OS_Terminate();

    WirelessDistribution_SetState(2);

    *(u16 *)(&((*sWirelessDistribution).unk_1034).bssid[4]) = 0xffff;
    *(u16 *)(&((*sWirelessDistribution).unk_1034).bssid[2]) = 0xffff;
    *(u16 *)(&((*sWirelessDistribution).unk_1034).bssid[0]) = 0xffff;

    if (!WirelessDistribution_BeginScan()) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
        }

        return 0;
    }

    (*sWirelessDistribution).unk_11CC = 2;

    if ((*sWirelessDistribution).unk_11F0 != NULL) {
        (*sWirelessDistribution).unk_11F0(0);
    }

    return 1;
}

static BOOL WirelessDistribution_BeginScan(void)
{
    WMErrCode v0;
    u16 v1;

    (void)(((*sWirelessDistribution).unk_11C4 == 2) || (OS_Terminate(), 0));

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

    if ((*sWirelessDistribution).unk_11EA >= 16) {
        int v2 = (*sWirelessDistribution).unk_11EA - 16;
        int v3;

        for (v3 = 0; v3 < 13; v3++) {
            v2 = (v2 + 1) % 13;

            if (v1 & (1 << v2)) {
                break;
            }
        }

        (*sWirelessDistribution).unk_11EA = (u16)(16 + v2);
        (*sWirelessDistribution).unk_1034.channel = (u16)(v2 + 1);
    } else {
        (*sWirelessDistribution).unk_1034.channel = (*sWirelessDistribution).unk_11EA;
    }

    (*sWirelessDistribution).unk_1034.maxChannelTime = 220;
    (*sWirelessDistribution).unk_1034.scanBuf = &((*sWirelessDistribution).unk_F00);

    if ((*sWirelessDistribution).unk_11CC == 3) {
        int v4;

        for (v4 = 0; v4 < 6; v4++) {
            (*sWirelessDistribution).unk_1034.bssid[v4] = (*sWirelessDistribution).unk_11E4[v4];
        }
    }

    v0 = WM_StartScan(WirelessDistribution_ScanCallback, &((*sWirelessDistribution).unk_1034));

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

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
        }

        return;
    }

    if ((*sWirelessDistribution).unk_11C4 != 2) {
        if (!WirelessDistribution_EndScan()) {
            WirelessDistribution_SetState(9);

            if ((*sWirelessDistribution).unk_11F0 != NULL) {
                (*sWirelessDistribution).unk_11F0(4);
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
        DC_InvalidateRange(&((*sWirelessDistribution).unk_F00), sizeof(WMbssDesc));

        if ((v0->gameInfoLength < 8) || (v0->gameInfo.ggid != 0x400318)) {
            if (sWirelessDistributionPrint) {
                sWirelessDistributionPrint("not my parent ggid (%d != %d)\n", v0->gameInfo.ggid, 0x400318);
            }
            break;
        }

        (*sWirelessDistribution).unk_11E0 = v0->linkLevel;

        if ((*sWirelessDistribution).unk_11CC == 2) {
            WirelessDistribution_InitTransfer((WirelessDistributionChunk *)&(v0->gameInfo.userGameInfo[0]));

            {
                int v1;

                for (v1 = 0; v1 < 6; v1++) {
                    (*sWirelessDistribution).unk_11E4[v1] = v0->macAddress[v1];
                }
            }

            (*sWirelessDistribution).unk_11EA = (u16)((*sWirelessDistribution).unk_11EA - 16 + 1);

            if ((*sWirelessDistribution).unk_11F0 != NULL) {
                (*sWirelessDistribution).unk_11F0(1);
            }
        }

        if (WirelessDistribution_ReceiveChunk((WirelessDistributionChunk *)&(v0->gameInfo.userGameInfo[0]))) {
            (*sWirelessDistribution).unk_11CC = 4;
            WirelessDistribution_Stop();

            return;
        }
        break;
    }

    if (!WirelessDistribution_BeginScan()) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
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

    if ((*sWirelessDistribution).unk_11F0 != NULL) {
        (*sWirelessDistribution).unk_11F0(3);
    }
}

static BOOL WirelessDistribution_Init(void)
{
    (*sWirelessDistribution).unk_11C8 = WM_ERRCODE_SUCCESS;

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

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
        }
    }
}

static BOOL WirelessDistribution_Initialize(void)
{
    WMErrCode v0;

    WirelessDistribution_SetState(3);
    v0 = WM_Initialize(&((*sWirelessDistribution).unk_00[0]), WirelessDistribution_InitCallback, 2);

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
    (void)(((*sWirelessDistribution).unk_11C4 == 1) || (OS_Terminate(), 0));

    WirelessDistribution_SetState(3);

    if (WM_End(WirelessDistribution_EndCallback) != WM_ERRCODE_OPERATING) {
        WirelessDistribution_SetState(9);

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
        }

        return 0;
    }

    return 1;
}

BOOL WirelessDistribution_Stop(void)
{
    if ((*sWirelessDistribution).unk_11C4 == 1) {
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

        if ((*sWirelessDistribution).unk_11F0 != NULL) {
            (*sWirelessDistribution).unk_11F0(4);
        }

        return;
    }

    WirelessDistribution_SetState(1);
    WirelessDistribution_Finalize();
}

BOOL WirelessDistribution_Start(void *param0, WirelessDistributionStateFunc param1, void *param2)
{
    sWirelessDistribution = (WirelessDistributionContext *)(((u32)param2 + 31) / 32 * 32);
    (*sWirelessDistribution).unk_11C4 = 0;
    (*sWirelessDistribution).unk_11CC = 1;
    (*sWirelessDistribution).unk_11EC = (u8 *)param0;
    (*sWirelessDistribution).unk_11D0 = 0;
    (*sWirelessDistribution).unk_11D2 = 0;
    (*sWirelessDistribution).unk_11F0 = param1;
    (*sWirelessDistribution).unk_11EA = 16 + 0;
    (*sWirelessDistribution).unk_10BC = 0;
    (*sWirelessDistribution).unk_11E0 = -1;

    return WirelessDistribution_Init();
}

static void WirelessDistribution_InitTransfer(WirelessDistributionChunk *param0)
{
    int v0;

    (*sWirelessDistribution).unk_10BC = 0;
    (*sWirelessDistribution).unk_11CC = 3;
    (*sWirelessDistribution).unk_11CE = param0->unk_00;
    (*sWirelessDistribution).unk_11D4 = param0->unk_04;
    (*sWirelessDistribution).unk_11D0 = (u16)(((*sWirelessDistribution).unk_11D4 - 1) / (WM_SIZE_USER_GAMEINFO - 8) + 1);
    (*sWirelessDistribution).unk_11D2 = 0;
    (*sWirelessDistribution).unk_11D8 = 0;

    for (v0 = 0; v0 < (*sWirelessDistribution).unk_11D0; v0++) {
        (*sWirelessDistribution).unk_11F4[v0] = 0;
    }
}

static int WirelessDistribution_ReceiveChunk(WirelessDistributionChunk *param0)
{
    if (((*sWirelessDistribution).unk_11CE != param0->unk_00) || ((*sWirelessDistribution).unk_11D4 != param0->unk_04)) {
        if ((*sWirelessDistribution).unk_11D8++ >= 16) {
            WirelessDistribution_InitTransfer(param0);

            if ((*sWirelessDistribution).unk_11F0 != NULL) {
                (*sWirelessDistribution).unk_11F0(5);
            }
        } else {
            return 0;
        }
    }

    if (param0->unk_02 == 0xffff) {
        MI_CpuCopy32(&(param0->unk_08[0]), &((*sWirelessDistribution).unk_1054[0]), (WM_SIZE_USER_GAMEINFO - 8));
        (*sWirelessDistribution).unk_10BC = 1;
    } else {
        (*sWirelessDistribution).unk_11DC = param0->unk_02;

        if (param0->unk_02 >= (*sWirelessDistribution).unk_11D0) {
            if ((*sWirelessDistribution).unk_11F0 != NULL) {
                (*sWirelessDistribution).unk_11F0(4);
            }

            WirelessDistribution_SetState(9);
        }

        if ((*sWirelessDistribution).unk_11F4[param0->unk_02] == 0) {
            (*sWirelessDistribution).unk_11F4[param0->unk_02] = 1;

            if (param0->unk_02 == (*sWirelessDistribution).unk_11D0 - 1) {
                MI_CpuCopy32(&(param0->unk_08[0]), &((*sWirelessDistribution).unk_11EC[param0->unk_02 * (WM_SIZE_USER_GAMEINFO - 8)]), (*sWirelessDistribution).unk_11D4 - param0->unk_02 * (WM_SIZE_USER_GAMEINFO - 8));
            } else {
                MI_CpuCopy32(&(param0->unk_08[0]), &((*sWirelessDistribution).unk_11EC[param0->unk_02 * (WM_SIZE_USER_GAMEINFO - 8)]), (WM_SIZE_USER_GAMEINFO - 8));
            }

            (*sWirelessDistribution).unk_11D2++;

            if ((*sWirelessDistribution).unk_11D2 == (*sWirelessDistribution).unk_11D0) {
                if ((*sWirelessDistribution).unk_11F0 != NULL) {
                    (*sWirelessDistribution).unk_11F0(2);
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

        v1 = (u16 *)&((*sWirelessDistribution).unk_11E4[0]);
        v0[0] = v1[0];
        v0[3] = v1[1];
        v0[2] = v1[2];
        v0[1] = (*sWirelessDistribution).unk_11CE;

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

        CRYPTO_RC4Init(&((*sWirelessDistribution).unk_10C0), &(v0[0]), 8);
        CRYPTO_RC4Encrypt(&((*sWirelessDistribution).unk_10C0), (*sWirelessDistribution).unk_11EC, (*sWirelessDistribution).unk_11D4, (*sWirelessDistribution).unk_11EC);

        MI_CpuClear32(&((*sWirelessDistribution).unk_10C0), sizeof((*sWirelessDistribution).unk_10C0));
    }

    return WirelessDistribution_Checksum((*sWirelessDistribution).unk_11EC, (*sWirelessDistribution).unk_11D4) == (*sWirelessDistribution).unk_11CE;
}

int WirelessDistribution_GetContextSize(void)
{
    return sizeof(WirelessDistributionContext) + 32;
}

void *WirelessDistribution_GetData(void)
{
    if ((*sWirelessDistribution).unk_10BC) {
        return &((*sWirelessDistribution).unk_1054[0]);
    }

    return NULL;
}
