#include "main_menu/wireless_comm_requests.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/wireless_comm_wm.h"
#include "main_menu/wireless_comm_state.h"
#include "main_menu/wireless_comm_callbacks.h"
#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_connect_data.h"

BOOL WirelessComm_SendMPData(const void *param0, u32 param1, u16 param2)
{
    WMErrCode v0;

    v0 = WM_SetMPDataToPort(WirelessComm_PortSendCallback, param0, (u16)param1, param2, (u16)WirelessComm_GetPacketPort(), 2);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_Enable(void)
{
    WMErrCode v0;

    v0 = WM_Enable(WirelessComm_EnableCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_Disable(void)
{
    WMErrCode v0;

    v0 = WM_Disable(WirelessComm_DisableCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        OS_Terminate();
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_MeasureChannel(u32 param0)
{
    WMErrCode v0;

    v0 = WM_MeasureChannel(WirelessComm_MeasureChannelCallback, 3, 17, (u16)param0, 30);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_SetParentParameter(void)
{
    WMErrCode v0;
    WMParentParam *v1 = WirelessComm_GetParentParam();
    WirelessCommGameInfo *v2 = WirelessComm_GetGameInfo();
    WirelessCommChildList *v3 = WirelessComm_GetChildList();

    v1->channel = v3->unk_64;
    v1->userGameInfo = (u16 *)v2;
    v1->userGameInfoLength = (u16)WirelessComm_GetGameInfoSize();

    v0 = WM_SetParentParameter(WirelessComm_SetParentParamCallback, v1);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_StartParent(void)
{
    WMErrCode v0;

    v0 = WM_StartParent(WirelessComm_StartParentCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_StartScan(void)
{
    WMErrCode v0;

    v0 = WM_StartScan(WirelessComm_ScanCallback, WirelessComm_GetScanParam());

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_StartScanForParent(void)
{
    WMErrCode v0;

    {
        WMScanParam *v1 = WirelessComm_GetScanParam();
        WirelessCommParentList *v2 = WirelessComm_GetParentList();

        v1->bssid[0] = v2->unk_00[v2->unk_1C3_0].unk_34.unk_00.val1[0];
        v1->bssid[1] = v2->unk_00[v2->unk_1C3_0].unk_34.unk_00.val1[1];
        v1->bssid[2] = v2->unk_00[v2->unk_1C3_0].unk_00.unk_00.val1[0];
        v1->bssid[3] = v2->unk_00[v2->unk_1C3_0].unk_00.unk_00.val1[1];
        v1->bssid[4] = v2->unk_00[v2->unk_1C3_0].unk_00.unk_00.val1[2];
        v1->bssid[5] = v2->unk_00[v2->unk_1C3_0].unk_00.unk_00.val1[3];
    }

    v0 = WM_StartScan(WirelessComm_ScanSelectedParentCallback, WirelessComm_GetScanParam());

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_EndScan(void)
{
    WMErrCode v0;

    v0 = WM_EndScan(WirelessComm_EndScanCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_StartConnect(void)
{
    WMErrCode v0;
    WirelessCommConnectData *v1 = WirelessComm_GetConnectData();

    v0 = WM_StartConnect(WirelessComm_StartConnectCallback, WirelessComm_GetScanResult(), (const u8 *)v1);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_StartMP(void)
{
    WMErrCode v0;

    v0 = WM_SetPortCallback(4, WirelessComm_PortRecvCallback, NULL);

    if (v0 == WM_ERRCODE_SUCCESS) {
        (void)0;
    } else {
        WirelessComm_OnError(v0);
        return 0;
    }

    v0 = WM_StartMP(WirelessComm_StartMPCallback, WirelessComm_GetChildSendBuffer(), (u16)WirelessComm_GetChildSendSize(), WirelessComm_GetParentSendBuffer(), (u16)WirelessComm_GetParentSendSize(), (u16)(WirelessComm_GetParentParam()->CS_Flag ? 0 : 1));

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_PowerOn(void)
{
    WMErrCode v0;

    v0 = WM_PowerOn(WirelessComm_PowerOnCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_PowerOff(void)
{
    WMErrCode v0;

    v0 = WM_PowerOff(WirelessComm_PowerOffCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        OS_Terminate();
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_Reset(void)
{
    WMErrCode v0;

    v0 = WM_Reset(WirelessComm_ResetCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        OS_Terminate();
        return 0;
    } else {
        return 1;
    }
}

BOOL WirelessComm_End(void)
{
    WMErrCode v0;

    v0 = WM_End(WirelessComm_EndCallback);

    if (v0 != WM_ERRCODE_OPERATING) {
        WirelessComm_OnError(v0);
        OS_Terminate();
        return 0;
    } else {
        return 1;
    }
}
