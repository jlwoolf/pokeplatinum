#include "main_menu/wireless_comm.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/wireless_comm_wm.h"
#include "main_menu/wireless_comm_state.h"
#include "main_menu/wireless_comm_requests.h"
#include "main_menu/struct_wireless_comm_manager.h"
#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_params.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_game_info_strings.h"
#include "main_menu/struct_wireless_comm_packet.h"
#include "main_menu/struct_wireless_comm_connect_data_head.h"

static BOOL WirelessComm_SetIndCallback(void)
{
    WMErrCode v0;

    v0 = WM_SetIndCallback(WirelessComm_IndCallback);

    if (v0 != WM_ERRCODE_SUCCESS) {
        WirelessComm_SetState(4);
        return 0;
    }

    return 1;
}

static void WirelessComm_EnableWireless(void)
{
    switch (WirelessComm_GetState()) {
    case 0:
    case 2:
    case 1:
        (void)WirelessComm_Enable();
        break;
    default:
        break;
    }
}

static void WirelessComm_SendPacket(const void *param0, u32 param1, u16 param2)
{
    const WMParentParam *v0 = WirelessComm_GetParentParam();

    if (param1 > v0->parentMaxSize) {
        return;
    }

    DC_FlushRange((void *)param0, param1);
    (void)WirelessComm_SendMPData(param0, param1, param2);
}

static u32 WirelessComm_GetParentBufferSize(void)
{
    u32 v0;
    u32 v1;
    u32 v2;

    v0 = (u32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(64, 9, 0);
    v1 = (u32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(64, 0);
    v2 = (v0 > v1) ? v0 : v1;

    return v2;
}

static u32 WirelessComm_GetChildBufferSize(void)
{
    u32 v0;
    u32 v1;
    u32 v2;

    v0 = (s32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(64, 9, 0);
    v1 = (s32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(64, 0);
    v2 = (v0 > v1) ? v0 : v1;

    return v2;
}

void WirelessComm_Init(WirelessCommParams *param0, void *param1)
{
    WMParentParam *v0 = WirelessComm_GetParentParam();
    WirelessCommManager *v1 = WirelessComm_GetManager();
    void *v2 = param1;
    u32 v3 = (u32)param1 & 0x1F;

    if (v3) {
        v3 = 0x20 - ((u32)param1 & 0x1F);
        param1 = (void *)((u32)param1 + v3);
    }

    v1->unk_00 = (u8)0;
    v1->unk_01 = (u8)0;
    v1->unk_02 = (u8)0;
    v1->unk_03 = 4;
    v1->unk_04 = 0x400131;
    v1->unk_0C = 0;

    v1->unk_34 = param1;
    (u8 *)param1 += WM_SYSTEM_BUF_SIZE;

    v1->unk_38 = param1;
    (u8 *)param1 += v1->unk_2C = WirelessComm_GetParentBufferSize();

    v1->unk_3C = param1;
    (u8 *)param1 += v1->unk_30 = WirelessComm_GetChildBufferSize();

    v1->unk_28 = param1;
    (u8 *)param1 += sizeof(WMBssDesc);

    v1->unk_24 = param1;
    (u8 *)param1 += sizeof(WMScanParam);

    (void)WM_Init(v1->unk_34, 2);

    v1->unk_10 = WirelessComm_SetIndCallback();
    v1->unk_14 = 0;
    v1->unk_18 = 0;
    v1->unk_1C = 0;
    v1->unk_20 = 0;
    v1->unk_40.unk_00.unk_00.unk_00_0 = 0xF;
    v1->unk_40.unk_00.unk_00.unk_00_8 = 0x1;
    v1->unk_40.unk_00.unk_00.unk_00_12 = 1;
    v1->unk_40.unk_00.unk_04.unk_00_0 = param0->unk_00_0;
    v1->unk_40.unk_00.unk_04.unk_00_8 = param0->unk_00_8;
    v1->unk_40.unk_00.unk_04.unk_00_12 = param0->unk_00_12;
    v1->unk_40.unk_00.unk_04.unk_00_16 = param0->unk_00_16;

    {
        const u16 *v4 = param0->unk_08;
        const u16 *v5 = param0->unk_04;
        u32 v6 = 0;

        while ((v4) && (v6 < 12)) {
            v1->unk_40.unk_08.unk_00.unk_00[v6] = *v4;
            v1->unk_40.unk_08.unk_18.unk_00[v6] = *v5;
            v6++;
            v4++;
            v5++;
        }
    }

    v1->unk_78.unk_00 = *(WirelessCommConnectDataHead *)&v1->unk_40.unk_00;

    WirelessComm_ResetTransfer();

    WirelessComm_GetTransfer()->unk_08 = param1;
    (u8 *)param1 += v1->unk_2C;

    WirelessComm_GetTransfer()->unk_0C = param1;
    (u8 *)param1 += v1->unk_30;

    (void)WM_GetNextTgid();
}

static void WirelessComm_SendStep(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if (v0->unk_19 == 1) {
        if (--v0->unk_1A > 0) {
            return;
        }

        v0->unk_19 = 0;
    }

    if (v0->unk_19 == 0) {
        u32 v1 = 64 - WirelessComm_GetPacketSize();
        u32 v2 = v1;
        int v3 = 3;

        WirelessComm_BuildPacket(v0->unk_08, v0->unk_04, v2, v3, v0->unk_1C);
        WirelessComm_SendPacket(v0->unk_08, v2 + WirelessComm_GetPacketSize(), 0xFFFF);

        v0->unk_19 = 1;
        v0->unk_1A = 60;
    }
}

static void WirelessComm_RequestStep(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if (v0->unk_19 == 0) {
        if (v0->unk_1C == (u8)0xFD) {
            WirelessCommChildList *v1 = WirelessComm_GetChildList();
            int v2;

            for (v2 = 0; v2 < 8; v2++) {
                if (v1->unk_00[v2].unk_09) {
                    int v3 = 0;
                    u16 v4 = (u16)(1 << v1->unk_00[v2].unk_06);

                    WirelessComm_BuildPacket(v0->unk_08, v0->unk_04, 0, v3, 0xFD);
                    WirelessComm_SendPacket(v0->unk_08, WirelessComm_GetPacketSize(), v4);

                    v1->unk_00[v2].unk_09--;
                    return;
                }
            }

            if (--v0->unk_1A == 0) {
                v0->unk_19 = 2;
            }
        } else {
            u32 v5 = WirelessComm_GetParentBufferSize() - WirelessComm_GetPacketSize();
            int v6;
            WirelessCommPacket *v7 = (WirelessCommPacket *)v0->unk_0C;

            v6 = (int)v7->unk_08.unk_00_8;

            if (v6 == 0) {
                if (v0->unk_1B == 0) {
                    v0->unk_19 = 2;
                    return;
                } else {
                    v0->unk_1B--;
                }
            }

            WirelessComm_BuildPacket(v0->unk_08, v0->unk_04, 0, v6, v0->unk_1C);
            WirelessComm_SendPacket(v0->unk_08, WirelessComm_GetPacketSize(), 0xFFFF);
        }
    }
}

static void WirelessComm_TransferStep(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    switch (v0->unk_18) {
    case 1:
        WirelessComm_SendStep();
        break;
    case 2:
        WirelessComm_RequestStep();
        break;
    }
}

static void WirelessComm_ParentUpdate(void)
{
    WirelessCommParentList *v0 = WirelessComm_GetParentList();

    switch (WirelessComm_GetState()) {
    case 6:
        if (v0->unk_1C0) {
            v0->unk_1C0--;
        }
        break;
    case 11:
        WirelessComm_TransferStep();
        break;
    default:
        break;
    }
}

static void WirelessComm_ChildUpdate(void)
{
    switch (WirelessComm_GetState()) {
    case 10:
        WirelessComm_TransferStep();
        break;
    default:
        break;
    }
}

void WirelessComm_Update(void)
{
    if (WirelessComm_GetState() == 12) {
        return;
    }

    if (WirelessComm_GetCommRole() == 12) {
        if (WirelessComm_GetState() == 7) {
            WirelessComm_Reset();
        }

        return;
    }

    switch (WirelessComm_GetLinkType()) {
    case 1:
        WirelessComm_ParentUpdate();
        break;
    case 2:
        WirelessComm_ChildUpdate();
        break;
    default: {
        WirelessCommManager *v0 = WirelessComm_GetManager();

        switch (WirelessComm_GetState()) {
        case 0:
            break;
        case 1:
            break;
        case 5:
            break;
        case 6:
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
        }
    }
    }
}

void WirelessComm_Start()
{
    WirelessComm_ResetParentList();
    WirelessComm_SetLinkType(1);
    WirelessComm_EnableWireless();
}

static u32 WirelessComm_CountFoundParents(void)
{
    int v0 = WirelessComm_GetLinkType();
    u32 v1 = 0;

    if (v0 == 1) {
        WirelessCommParentList *v2 = WirelessComm_GetParentList();

        if (v2->unk_1C3_4 == 1) {
            u32 v3;

            for (v3 = 0; v3 < 8; v3++) {
                if (v2->unk_00[v3].unk_00.unk_00.val2 != 0) {
                    v1++;
                }
            }
        }
    }

    return v1;
}

BOOL WirelessComm_IsParentAvailable(u32 param0)
{
    if ((WirelessComm_GetLinkType() == 1) && (WirelessComm_GetState() == 7)) {
        WirelessCommParentList *v0 = WirelessComm_GetParentList();

        if ((v0->unk_1C3_4 == 1) && (v0->unk_00[param0].unk_00.unk_00.val2)) {
            return 1;
        }
    }

    return 0;
}

void WirelessComm_SelectParent(u32 param0)
{
    if ((WirelessComm_GetLinkType() == 1) && (WirelessComm_GetState() == 7)) {
        WirelessCommParentList *v0 = WirelessComm_GetParentList();

        if ((v0->unk_1C3_4 == 1) && (v0->unk_00[param0].unk_00.unk_00.val2)) {
            v0->unk_1C3_0 = (u8)param0;
            v0->unk_1C0 = 120;

            WirelessComm_StartScanForParent();
        }
    }
}

static u32 WirelessComm_CountConnectedChildren(void)
{
    int v0 = WirelessComm_GetLinkType();
    u32 v1 = 0;

    if (v0 == 2) {
        WirelessCommChildList *v2 = WirelessComm_GetChildList();

        if (v2->unk_60 == 2) {
            u32 i;

            for (i = 0; i < 8; i++) {
                if ((v2->unk_00[i].unk_00.unk_00.val2 != 0) && (v2->unk_00[i].unk_0A)) {
                    v1++;
                }
            }
        }
    }

    return v1;
}

u32 WirelessComm_GetLinkLevel(void)
{
    WirelessCommManager *v0 = WirelessComm_GetManager();

    if (!v0->unk_20) {
        return (u32)WM_GetLinkLevel();
    } else {
        return 0;
    }
}

u32 WirelessComm_GetNumConnected(void)
{
    int v0 = WirelessComm_GetLinkType();
    u32 v1;

    switch (v0) {
    case 1:
        v1 = WirelessComm_CountFoundParents();
        break;
    case 2:
        v1 = WirelessComm_CountConnectedChildren();
        break;
    default:
        v1 = 0;
        break;
    }

    return v1;
}

void WirelessComm_StartSend(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();
    WirelessCommGameInfo *v1 = WirelessComm_GetGameInfo();

    if (WirelessComm_GetLinkType() == 1) {
        v0->unk_18 = 1;
        v0->unk_19 = 0;
        v0->unk_00 = (void *)&v1->unk_08;
        v0->unk_04 = (void *)&v1->unk_08;
        v0->unk_10 = 0;
        v0->unk_14 = 0;
        v0->unk_1A = 120;
        v0->unk_1B = 0;
        v0->unk_1C = (u8)0xFD;
    }
}

void WirelessComm_StartReceive(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();
    WirelessCommGameInfo *v1 = WirelessComm_GetGameInfo();

    v0->unk_18 = 1;
    v0->unk_19 = 0;
    v0->unk_00 = (void *)&v1->unk_08;
    v0->unk_04 = (void *)&v1->unk_08;
    v0->unk_10 = sizeof(WirelessCommGameInfoStrings);
    v0->unk_14 = sizeof(WirelessCommGameInfoStrings);
    v0->unk_1A = 120;
    v0->unk_1B = 0;
    v0->unk_1C = (u8)0xFE;
}

void WirelessComm_SendData(void *param0, u32 param1, u32 param2)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

    if ((int)param2 > 0xF0) {
        return;
    }

    v0->unk_18 = 2;
    v0->unk_19 = 3;
    v0->unk_00 = param0;
    v0->unk_04 = param0;
    v0->unk_10 = param1;
    v0->unk_14 = 0;
    v0->unk_1A = 120;
    v0->unk_1B = 0;
    v0->unk_1C = (u8)param2;
}

BOOL WirelessComm_IsReceiveComplete(void)
{
    u32 v0 = 0;

    switch (WirelessComm_GetLinkType()) {
    case 1:
    case 2: {
        switch (WirelessComm_GetState()) {
        case 11:
        case 10: {
            WirelessCommTransfer *v1 = WirelessComm_GetTransfer();

            if (v1->unk_19 == 2) {
                return 1;
            }
        } break;
        }
    } break;
    }

    return 0;
}

BOOL WirelessComm_IsSendComplete(void)
{
    u32 v0 = 0;

    switch (WirelessComm_GetLinkType()) {
    case 1:
    case 2: {
        switch (WirelessComm_GetState()) {
        case 11:
        case 10: {
            WirelessCommTransfer *v1 = WirelessComm_GetTransfer();

            if (v1->unk_19 == 2) {
                return 1;
            }
        } break;
        }
    } break;
    }

    return 0;
}

BOOL WirelessComm_IsAwaitingData(void)
{
    switch (WirelessComm_GetLinkType()) {
    case 1:
    case 2: {
        switch (WirelessComm_GetState()) {
        case 11:
        case 10: {
            WirelessCommTransfer *v0 = WirelessComm_GetTransfer();

            if (v0->unk_19 == 0) {
                WirelessCommPacket *v1 = (WirelessCommPacket *)v0->unk_0C;

                if ((v1->unk_08.unk_00_8 == 0) && (v0->unk_1B < 4)) {
                    return 1;
                }
            }
        } break;
        }
    } break;
    }

    return 0;
}

BOOL WirelessComm_IsLinkActive(void)
{
    switch (WirelessComm_GetLinkType()) {
    case 2: {
        WirelessCommChildList *v0 = WirelessComm_GetChildList();
        int v1;

        for (v1 = 0; v1 < 8; v1++) {
            if (v0->unk_00[v1].unk_00.unk_00.val2) {
                if (v0->unk_00[v1].unk_0A) {
                    return 1;
                }
            }
        }

        return 0;
    } break;

    default:
        return WirelessComm_GetDisconnected();
        break;
    }
}

void WirelessComm_Stop(void)
{
    WirelessComm_SetCommRole(12);

    switch (WirelessComm_GetState()) {
    case 0:
    case 1:
        WM_Finish();
        WirelessComm_SetFinished(1);
        break;
    case 9:
        if (!WirelessComm_GetDisconnected()) {
            WirelessCommManager *v0 = WirelessComm_GetManager();

            WirelessComm_Reset();
            v0->unk_1C = 1;
        }
        break;
    }
}

BOOL WirelessComm_HasStopped(void)
{
    WirelessCommManager *v0 = WirelessComm_GetManager();
    return v0->unk_20;
}
