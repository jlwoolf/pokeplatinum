#include "main_menu/wireless_comm_wm.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/wireless_comm_state.h"
#include "main_menu/wireless_comm_callbacks.h"
#include "main_menu/wireless_comm_requests.h"
#include "main_menu/struct_wireless_comm_manager.h"
#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"
#include "main_menu/struct_wireless_comm_packet.h"
#include "main_menu/struct_wireless_comm_connect_data.h"

static void WirelessComm_Abort(void)
{
    WirelessComm_SetState(4);
    (void)WirelessComm_Reset();
}

static WirelessCommBssidHigh WirelessComm_ReadBssidHigh(u8 *param0)
{
    return WirelessComm_MakeBssidHigh(param0);
}

static WirelessCommBssidLow WirelessComm_ReadBssidLow(u8 *param0)
{
    return WirelessComm_MakeBssidLow(param0);
}

static BOOL WirelessComm_CheckFinished(void)
{
    if (WirelessComm_GetCommRole() == 12) {
        WirelessCommManager *v0 = WirelessComm_GetManager();

        if (v0->unk_1C == 0) {
            (void)WirelessComm_Reset();
            v0->unk_1C = 1;
        }

        return 1;
    } else {
        return 0;
    }
}

static void WirelessComm_RemoveChild(u32 param0)
{
    WirelessCommChildList *v0 = WirelessComm_GetChildList();
    int v1;

    for (v1 = 0; v1 < 8; v1++) {
        if ((v0->unk_00[v1].unk_00.unk_00.val2) && (v0->unk_00[v1].unk_06 == param0)) {
            v0->unk_00[v1].unk_08 = 0;
            v0->unk_00[v1].unk_0A = 0;
        }
    }
}

static u32 WirelessComm_PopChannelEvent(void)
{
    WirelessCommChildList *v0 = WirelessComm_GetChildList();

    if (v0->unk_62 & 1) {
        v0->unk_62 &= ~1;
        return 1;
    } else if (v0->unk_62 & (1 << 6)) {
        v0->unk_62 &= ~(1 << 6);
        return 7;
    } else if (v0->unk_62 & (1 << 12)) {
        v0->unk_62 &= ~(1 << 12);
        return 13;
    } else {
        return 0;
    }
}

static BOOL WirelessComm_SetupChannelMeasure(void)
{
    WirelessCommChildList *v0 = WirelessComm_GetChildList();

    v0->unk_60 = 1;
    v0->unk_62 = WM_GetAllowedChannel();

    if ((v0->unk_62 == 0) || (v0->unk_62 == 0x8000)) {
        return 0;
    } else {
        v0->unk_61 = 102;
        v0->unk_64 = 0;
        return 1;
    }
}

static void WirelessComm_SetupParentParam(void)
{
    WMParentParam *v0 = WirelessComm_GetParentParam();

    v0->beaconPeriod = WM_GetDispersionBeaconPeriod();
    v0->tgid = WM_GetNextTgid();
}

static void WirelessComm_SetupScanParam(void)
{
    WMScanParam *v0 = WirelessComm_GetScanParam();

    v0->scanBuf = WirelessComm_GetScanResult();
    v0->channel = WirelessComm_GetParentParam()->channel;
    v0->maxChannelTime = WM_GetDispersionScanPeriod();
    v0->bssid[0] = 0xff;
    v0->bssid[1] = 0xff;
    v0->bssid[2] = 0xff;
    v0->bssid[3] = 0xff;
    v0->bssid[4] = 0xff;
    v0->bssid[5] = 0xff;
}

static void WirelessComm_AdvanceChannel(void)
{
    WMScanParam *v0 = WirelessComm_GetScanParam();
    u16 v1;
    s32 v2;

    v1 = WM_GetAllowedChannel();

    if (v1 == 0) {
        return;
    }

    for (v2 = 0; v2 < 16; v2++) {
        if (v1 & (0x1 << ((v0->channel + v2) % 16))) {
            v0->channel = (u16)(((v0->channel + v2) % 16) + 1);
            break;
        }
    }
}

void WirelessComm_IndCallback(void *param0)
{
    WMindCallback *v0 = (WMindCallback *)param0;
    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_FIFO_ERROR) {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_PortSendCallback(void *param0)
{
    WMPortSendCallback *v0 = (WMPortSendCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        (void)0;
    } else {
        WMPortSendCallback *v1 = (WMPortSendCallback *)v0;
        WirelessComm_OnError((WMErrCode)v0->errcode);
    }
}

void WirelessComm_EnableCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessComm_SetState(2);

        if (WirelessComm_GetCommRole() == 12) {
            WirelessComm_Disable();
            WirelessComm_SetState(2);
            return;
        }

        if (WirelessComm_PowerOn() == 0) {
            WirelessComm_Disable();
            WirelessComm_SetState(2);
            return;
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Disable();
    }
}

void WirelessComm_DisableCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        if (WirelessComm_GetCommRole() == 12) {
            WM_Finish();
            WirelessComm_SetState(12);
            WirelessComm_SetFinished(1);
            return;
        }

        WirelessComm_SetState(1);
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_SetState(4);
    }
}

void WirelessComm_MeasureChannelCallback(void *param0)
{
    WMMeasureChannelCallback *v0 = (WMMeasureChannelCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessCommChildList *v1 = WirelessComm_GetChildList();

        if (v1->unk_61 > v0->ccaBusyRatio) {
            v1->unk_61 = (u8)v0->ccaBusyRatio;
            v1->unk_64 = (u8)v0->channel;
        }

        {
            u32 v2 = WirelessComm_PopChannelEvent();

            if (v2) {
                if (WirelessComm_MeasureChannel(v2) == 0) {
                    WirelessComm_Abort();
                }
            } else {
                if (v1->unk_61 < 102) {
                    WirelessComm_SetupParentParam();

                    if (WirelessComm_SetParentParameter() == 0) {
                        WirelessComm_Abort();
                    }
                } else {
                    WirelessComm_Abort();
                }
            }
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_SetParentParamCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        if (WirelessComm_CheckFinished()) {
            return;
        }

        if (WirelessComm_StartParent() == 0) {
            WirelessComm_Abort();
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_StartParentCallback(void *param0)
{
    WMstartParentCallback *v0 = (WMstartParentCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessCommChildList *v1 = WirelessComm_GetChildList();

        WirelessComm_SetState(8);

        if (WirelessComm_CheckFinished()) {
            return;
        }

        if (v1->unk_60 == 1) {
            v1->unk_60 = 2;
        }

        switch (v0->state) {
        case WM_STATECODE_PARENT_START:
            if (WirelessComm_StartMP() == 0) {
                WirelessComm_Abort();
            } else {
                WirelessComm_SetAid(0);
            }
            break;
        case WM_STATECODE_CONNECTED:
            WirelessComm_OnChildList(WirelessComm_GetChildList());

            if (v1->unk_60 == 2) {
                WirelessCommConnectData *v2 = (WirelessCommConnectData *)v0->ssid;

                if ((v2->unk_00.unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v2->unk_00.unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8()) && (v2->unk_00.unk_04.unk_00_16 == WirelessComm_GetGameInfoField16())) {
                    int v3;
                    WirelessCommChildList *v4 = WirelessComm_GetChildList();
                    WirelessCommBssidHigh v5 = WirelessComm_ReadBssidHigh(v0->macAddress);
                    WirelessCommBssidLow v6 = WirelessComm_ReadBssidLow(v0->macAddress);

                    for (v3 = 0; v3 < 8; v3++) {
                        WirelessCommBssidHigh *v7 = &v4->unk_00[v3].unk_00;

                        if (v7->unk_00.val2 == v5.unk_00.val2) {
                            v4->unk_00[v3].unk_06 = v0->aid;
                            v4->unk_00[v3].unk_0A = 1;
                            break;
                        }

                        if (v7->unk_00.val2 == 0) {
                            v4->unk_00[v3].unk_00.unk_00.val2 = v5.unk_00.val2;
                            v4->unk_00[v3].unk_04.unk_00.val2 = v6.unk_00.val2;
                            v4->unk_00[v3].unk_06 = v0->aid;
                            v4->unk_00[v3].unk_0A = 1;
                            break;
                        }
                    }
                }
            }
            break;
        case WM_STATECODE_BEACON_SENT:
            break;
        case WM_STATECODE_DISCONNECTED:
            WirelessComm_RemoveChild((u32)v0->aid);
            break;
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

static BOOL WirelessComm_AddFoundParent(WMstartScanCallback *param0, WMBssDesc *param1)
{
    int v0;
    WirelessCommParentList *v1 = WirelessComm_GetParentList();
    WirelessCommBssidHigh v2 = WirelessComm_ReadBssidHigh(param1->bssid);
    WirelessCommBssidLow v3 = WirelessComm_ReadBssidLow(param1->bssid);

    for (v0 = 0; v0 < 8; v0++) {
        WirelessCommBssidHigh *v4 = &v1->unk_00[v0].unk_00;
        WirelessCommBssidLow *v5 = &v1->unk_00[v0].unk_34;

        if ((v4->unk_00.val2 == v2.unk_00.val2) && (v5->unk_00.val2 == v3.unk_00.val2)) {
            return 1;
        }

        if (v4->unk_00.val2 == 0) {
            v1->unk_00[v0].unk_00.unk_00.val2 = v2.unk_00.val2;
            v1->unk_00[v0].unk_04 = ((WirelessCommGameInfo *)param1->gameInfo.userGameInfo)->unk_08.unk_00;
            v1->unk_00[v0].unk_1C = ((WirelessCommGameInfo *)param1->gameInfo.userGameInfo)->unk_08.unk_18;
            v1->unk_00[v0].unk_34.unk_00.val2 = v3.unk_00.val2;
            v1->unk_00[v0].unk_36 = (u8)param0->linkLevel;
            return 1;
        }
    }

    return 0;
}

static void WirelessComm_RescanChannel(void)
{
    WirelessComm_AdvanceChannel();

    if (WirelessComm_StartScan() == 0) {
        WirelessComm_Abort();
    }
}

static BOOL WirelessComm_HandleScanResult(WMstartScanCallback *param0)
{
    WMBssDesc *v0 = WirelessComm_GetScanResult();
    WirelessCommParentList *v1 = WirelessComm_GetParentList();

    if (WirelessComm_CheckFinished()) {
        return 1;
    }

    {
        int v2 = 0;
        int v3;

        for (v3 = 0; v3 < 8; v3++) {
            WirelessCommBssidHigh *v4 = &v1->unk_00[v3].unk_00;

            if (v4->unk_00.val2) {
                v2 = 1;
                break;
            }
        }

        if ((v2 != 0) && (v1->unk_1C0 == 0)) {
            if (WirelessComm_EndScan() == 0) {
                WirelessComm_Abort();
            }

            return 1;
        }
    }

    DC_InvalidateRange(v0, sizeof(WMbssDesc));
    WirelessComm_OnParentList(WirelessComm_GetParentList());

    if ((param0->gameInfoLength >= 8) && (v0->gameInfo.ggid == WirelessComm_GetGameInfoGgid())) {
        WirelessCommGameInfo *v5 = (WirelessCommGameInfo *)v0->gameInfo.userGameInfo;

        if ((v5->unk_00.unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v5->unk_00.unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8()) && (v5->unk_00.unk_04.unk_00_16 == WirelessComm_GetGameInfoField16())) {
            if (WirelessComm_AddFoundParent(param0, v0)) {
                WirelessCommParentList *v6 = WirelessComm_GetParentList();

                if (++v6->unk_1C2 > 28) {
                    if (WirelessComm_EndScan() == 0) {
                        WirelessComm_Abort();
                        return 1;
                    }
                }
            } else {
                if (WirelessComm_EndScan() == 0) {
                    WirelessComm_Abort();
                }

                return 1;
            }
        }
    }

    return 0;
}

void WirelessComm_ScanCallback(void *param0)
{
    WMstartScanCallback *v0 = (WMstartScanCallback *)param0;
    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        {
            WMBssDesc *v1 = WirelessComm_GetScanResult();
            WirelessComm_OnBssDesc(v1);
        }

        WirelessComm_SetState(6);

        if (WirelessComm_CheckFinished()) {
            return;
        }

        switch (WirelessComm_GetLinkType()) {
        case 1: {
            WirelessCommParentList *v2 = WirelessComm_GetParentList();
            v2->unk_1C3_4 = 1;
        } break;
        }

        switch (v0->state) {
        case WM_STATECODE_PARENT_FOUND:
            if (WirelessComm_HandleScanResult(v0) != 0) {
                break;
            }
        case WM_STATECODE_PARENT_NOT_FOUND:
            WirelessComm_RescanChannel();
            break;
        default:
            WirelessComm_OnError((WMErrCode)v0->errcode);
            WirelessComm_Abort();
            break;
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

static BOOL WirelessComm_CheckScanParent(void)
{
    WMBssDesc *v0 = WirelessComm_GetScanResult();
    WirelessCommParentList *v1 = WirelessComm_GetParentList();
    WMParentParam *v2 = WirelessComm_GetParentParam();

    if (WirelessComm_CheckFinished()) {
        return 1;
    }

    DC_InvalidateRange(v0, sizeof(WMbssDesc));
    WirelessComm_OnParentList(WirelessComm_GetParentList());

    if ((v0->gameInfoLength >= 8) && (v0->gameInfo.ggid == WirelessComm_GetGameInfoGgid())) {
        WirelessCommGameInfo *v3 = (WirelessCommGameInfo *)v0->gameInfo.userGameInfo;

        if ((v3->unk_00.unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v3->unk_00.unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8()) && (v3->unk_00.unk_04.unk_00_16 == WirelessComm_GetGameInfoField16())) {
            WirelessCommBssidHigh v4 = WirelessComm_ReadBssidHigh(v0->bssid);
            WirelessCommBssidHigh *v5 = &v1->unk_00[v1->unk_1C3_0].unk_00;

            if (v5->unk_00.val2 == v4.unk_00.val2) {
                if (WirelessComm_EndScan() == 0) {
                    WirelessComm_Abort();
                }

                return 1;
            }
        }
    }

    return 0;
}

void WirelessComm_ScanSelectedParentCallback(void *param0)
{
    WMstartScanCallback *v0 = (WMstartScanCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessCommParentList *v1 = WirelessComm_GetParentList();

        v1->unk_1C3_4 = 2;
        WirelessComm_SetState(6);

        if (WirelessComm_CheckFinished()) {
            return;
        }

        switch (v0->state) {
        case WM_STATECODE_PARENT_FOUND:
            if (WirelessComm_CheckScanParent() != 0) {
                break;
            }
        case WM_STATECODE_PARENT_NOT_FOUND:
            WirelessComm_AdvanceChannel();

            if (WirelessComm_StartScanForParent() == 0) {
                WirelessComm_Abort();
            }
            break;
        default:
            WirelessComm_OnError((WMErrCode)v0->errcode);
            WirelessComm_Abort();
            break;
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_EndScanCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessComm_SetState(7);

        if (WirelessComm_CheckFinished()) {
            return;
        }

        if (WirelessComm_GetLinkType() == 1) {
            WirelessCommParentList *v1 = WirelessComm_GetParentList();

            if (v1->unk_1C3_4 == 2) {
                if (WirelessComm_StartConnect() == 0) {
                    WirelessComm_Abort();
                } else {
                    WirelessComm_SetState(3);
                }
            }
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_StartConnectCallback(void *param0)
{
    WMstartConnectCallback *v0 = (WMstartConnectCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessComm_SetState(9);

        if (WirelessComm_CheckFinished()) {
            return;
        }

        switch (v0->state) {
        case WM_STATECODE_CONNECT_START:
            break;
        case WM_STATECODE_CONNECTED:
            WirelessComm_SetAid(v0->aid);
            WirelessComm_SetConnected(1);
            WirelessComm_SetDisconnected(0);

            if (WirelessComm_StartMP() == 0) {
                WirelessComm_Abort();
            }
            break;
        case WM_STATECODE_BEACON_LOST:
            break;
        case WM_STATECODE_DISCONNECTED:
            if (WirelessComm_GetDisconnected()) {
                WirelessComm_SetDisconnected(1);
            }

            WirelessComm_SetConnected(0);
            break;
        default:
            WirelessComm_OnError((WMErrCode)v0->errcode);
            WirelessComm_Abort();
        }
    } else {
        if (v0->errcode == WM_ERRCODE_NO_ENTRY) {
            (void)0;
        }

        if (v0->errcode == WM_ERRCODE_OVER_MAX_ENTRY) {
            (void)0;
        }

        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

static void WirelessComm_StartCommStep(void)
{
    switch (WirelessComm_GetLinkType()) {
    case 2:
        if ((WirelessComm_SetupChannelMeasure() != 0) && (WirelessComm_MeasureChannel(WirelessComm_PopChannelEvent()) != 0)) {
            WirelessCommChildList *v0 = WirelessComm_GetChildList();
            v0->unk_60 = 1;
            WirelessComm_SetState(3);
        } else {
            WirelessComm_Abort();
        }
        break;
    case 1:
        WirelessComm_SetupScanParam();

        if (WirelessComm_StartScan() == 0) {
            WirelessComm_Abort();
        } else {
            WirelessComm_SetState(3);
        }
        break;
    }
}

void WirelessComm_StartMPCallback(void *param0)
{
    WMstartMPCallback *v0 = (WMstartMPCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        if (v0->apiid == WM_APIID_START_MP) {
            if (WirelessComm_CheckFinished()) {
                return;
            }
        }

        switch (WirelessComm_GetLinkType()) {
        case 2:
            WirelessComm_SetState(10);
            break;
        case 1:
            WirelessComm_SetState(11);
            break;
        }

        switch (v0->state) {
        case WM_STATECODE_MP_START:
            break;
        case WM_STATECODE_MPEND_IND:
            break;
        case WM_STATECODE_MP_IND:
            break;
        }
    } else {
        switch (v0->errcode) {
        case WM_ERRCODE_SEND_FAILED:
        case WM_ERRCODE_TIMEOUT:
            break;
        case WM_ERRCODE_INVALID_POLLBITMAP:
            break;
        default:
            WirelessComm_Abort();
        }
    }
}

static void WirelessComm_RecvPacket(WMPortRecvCallback *param0)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if (v0->unk_19 == 1) {
        WirelessCommPacket *v1 = (WirelessCommPacket *)v0->unk_0C;

        DC_FlushRange(param0->data, param0->length);
        MI_CpuCopy8(param0->data, v0->unk_0C, param0->length);

        if ((v1->unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v1->unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8())) {
            WirelessComm_DecryptPacket(v0->unk_0C);

            if (v1->unk_08.unk_00_0 != v0->unk_1C) {
                return;
            }

            WirelessComm_OnPacket((WirelessCommPacket *)v0->unk_0C);

            if ((WirelessComm_VerifyPacket(v0->unk_0C)) && (v1->unk_08.unk_00_8 != 1)) {
                v0->unk_19 = 2;
            } else {
                v0->unk_19 = 0;
            }
        }
    }
}

static void WirelessComm_RecvDataRequest(WMPortRecvCallback *param0)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if ((WirelessComm_GetLinkType() == 2) && (v0->unk_19 != 2)) {
        WirelessCommPacket *v1 = (WirelessCommPacket *)v0->unk_0C;

        DC_FlushRange(param0->data, param0->length);
        MI_CpuCopy8(param0->data, v0->unk_0C, param0->length);

        if ((v1->unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v1->unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8())) {
            WirelessComm_DecryptPacket(v0->unk_0C);

            if (v1->unk_08.unk_00_0 != 0xFD) {
                return;
            } else {
                WirelessCommChildList *v2 = WirelessComm_GetChildList();
                int v3;

                for (v3 = 0; v3 < 8; v3++) {
                    if (v2->unk_00[v3].unk_06 == param0->aid) {
                        v2->unk_00[v3].unk_08 = 1;
                        v2->unk_00[v3].unk_09 = 3;
                        v0->unk_1A = 180;
                        v0->unk_19 = 0;
                        break;
                    }
                }
            }
        }
    }
}

static void WirelessComm_RecvData(WMPortRecvCallback *param0)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if (v0->unk_1C == 0xFD) {
        WirelessComm_RecvDataRequest(param0);
    } else {
        if (((v0->unk_19 == 1) || (v0->unk_19 == 3)) && (v0->unk_1B == 0)) {
            WirelessCommPacket *v1 = (WirelessCommPacket *)v0->unk_0C;

            DC_FlushRange(param0->data, param0->length);
            MI_CpuCopy8(param0->data, v0->unk_0C, param0->length);

            if ((v1->unk_00.unk_00_0 == WirelessComm_GetGameInfoField0()) && (v1->unk_00.unk_00_8 <= WirelessComm_GetGameInfoField8())) {
                WirelessComm_DecryptPacket(v0->unk_0C);

                if (v1->unk_08.unk_00_0 != v0->unk_1C) {
                    return;
                }

                WirelessComm_OnPacket((WirelessCommPacket *)v0->unk_0C);

                v0->unk_19 = 0;

                if (WirelessComm_VerifyPacket(v0->unk_0C)) {
                    if (v1->unk_08.unk_00_0 == 0xFD) {
                        WirelessComm_RecvDataRequest(param0);
                    } else {
                        MI_CpuCopy8((u8 *)v0->unk_0C + v1->unk_0C.unk_00_0, v0->unk_04, v1->unk_0C.unk_00_8);
                    }

                    v1->unk_08.unk_00_8 = 0;
                    v0->unk_1B = 4;
                } else {
                    v1->unk_08.unk_00_8 = 1;
                }
            }
        }
    }
}

void WirelessComm_PortRecvCallback(void *param0)
{
    WMPortRecvCallback *v0 = (WMPortRecvCallback *)param0;

    WirelessComm_OnStateChange((WMStateCode)v0->state);

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        switch (v0->state) {
        case WM_STATECODE_PORT_RECV:
            switch (WirelessComm_GetState()) {
            case 10:
            case 11: {
                WirelessCommTransfer *v1 = WirelessComm_GetTransfer();

                switch (v1->unk_18) {
                case 1:
                    WirelessComm_RecvPacket(v0);
                    break;
                case 2:
                    WirelessComm_RecvData(v0);
                    break;
                }
            } break;
            }
            break;
        case WM_STATECODE_CONNECTED:
            WirelessComm_SetConnected(1);
            WirelessComm_SetDisconnected(0);
            break;
        case WM_STATECODE_DISCONNECTED:
            if (WirelessComm_GetDisconnected()) {
                WirelessComm_SetDisconnected(1);
            }

            switch (WirelessComm_GetState()) {
            case 10:
                WirelessComm_RemoveChild((u32)v0->aid);
                break;
            case 11:
                WirelessComm_SetConnected(0);
                break;
            }
            break;
        }
    } else {
        (void)0;
    }
}

void WirelessComm_PowerOnCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        if (WirelessComm_CheckFinished()) {
            return;
        }

        WirelessComm_StartCommStep();
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_SetState(4);
    }
}

void WirelessComm_PowerOffCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        if (WirelessComm_Disable() == 0) {
            (void)0;
        } else {
            WirelessComm_SetState(2);
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_Abort();
    }
}

void WirelessComm_ResetCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessComm_SetAid(0);

        if (WirelessComm_GetCommRole() == 12) {
            if (WirelessComm_End() == 0) {
                (void)0;
            } else {
                WirelessComm_SetState(3);
            }
        } else {
            if (WirelessComm_PowerOff() == 0) {
                (void)0;
            } else {
                WirelessComm_SetState(3);
            }
        }
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_SetState(4);
    }
}

void WirelessComm_EndCallback(void *param0)
{
    WMCallback *v0 = (WMCallback *)param0;

    if (v0->errcode == WM_ERRCODE_SUCCESS) {
        WirelessComm_SetState(12);
        WirelessComm_SetFinished(1);
    } else {
        WirelessComm_OnError((WMErrCode)v0->errcode);
        WirelessComm_SetState(4);
    }
}
