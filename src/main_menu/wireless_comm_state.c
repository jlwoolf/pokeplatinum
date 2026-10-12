#include "main_menu/wireless_comm_state.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/wireless_comm_callbacks.h"
#include "main_menu/struct_wireless_comm_manager.h"
#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"
#include "main_menu/struct_wireless_comm_packet.h"
#include "main_menu/struct_wireless_comm_packet_header.h"
#include "main_menu/struct_wireless_comm_packet_config.h"
#include "main_menu/struct_wireless_comm_packet_meta.h"
#include "main_menu/struct_wireless_comm_packet_tail.h"
#include "main_menu/struct_wireless_comm_connect_data.h"
#include "main_menu/union_wireless_comm_connection.h"

static WirelessCommManager sWirelessCommManager;

__attribute__((aligned(32))) static WMParentParam sWirelessCommParentParam = {
    NULL,
    0x0,
    0x0,
    0x400131,
    0x0,
    0x1,
    0x9,
    0x0,
    0x0,
    0x0,
    0xC8,
    { 0x0, 0x0, 0x0, 0x0 },
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
    0x0,
    0x40,
    0x40
};

WMParentParam *WirelessComm_GetParentParam(void)
{
    return &sWirelessCommParentParam;
}

WirelessCommManager *WirelessComm_GetManager(void)
{
    return &sWirelessCommManager;
}

int WirelessComm_GetState(void)
{
    return (int)WirelessComm_GetManager()->unk_00;
}

void WirelessComm_SetState(int param0)
{
    WirelessComm_GetManager()->unk_00 = (u8)param0;
}

int WirelessComm_GetCommRole(void)
{
    return (int)WirelessComm_GetManager()->unk_01;
}

void WirelessComm_SetCommRole(int param0)
{
    WirelessComm_GetManager()->unk_01 = (u8)param0;
}

int WirelessComm_GetLinkType(void)
{
    return (int)WirelessComm_GetManager()->unk_02;
}

void WirelessComm_SetLinkType(int param0)
{
    WirelessComm_GetManager()->unk_02 = (u8)param0;
}

u32 WirelessComm_GetPacketPort(void)
{
    return (u32)WirelessComm_GetManager()->unk_03;
}

void WirelessComm_SetChannel(u32 param0)
{
    WirelessComm_GetParentParam()->channel = (u16)param0;
}

WMScanParam *WirelessComm_GetScanParam(void)
{
    return WirelessComm_GetManager()->unk_24;
}

u32 WirelessComm_GetParentSendSize(void)
{
    return WirelessComm_GetManager()->unk_2C;
}

u32 WirelessComm_GetChildSendSize(void)
{
    return WirelessComm_GetManager()->unk_30;
}

void *WirelessComm_GetParentSendBuffer(void)
{
    return WirelessComm_GetManager()->unk_38;
}

void *WirelessComm_GetChildSendBuffer(void)
{
    return WirelessComm_GetManager()->unk_3C;
}

WMBssDesc *WirelessComm_GetScanResult(void)
{
    return WirelessComm_GetManager()->unk_28;
}

void WirelessComm_SetAid(u16 param0)
{
    WirelessComm_GetManager()->unk_0C = param0;
}

BOOL WirelessComm_GetDisconnected(void)
{
    return WirelessComm_GetManager()->unk_14;
}

void WirelessComm_SetConnected(BOOL param0)
{
    WirelessComm_GetManager()->unk_14 = param0;
}

void WirelessComm_SetDisconnected(BOOL param0)
{
    WirelessComm_GetManager()->unk_18 = param0;
}

void WirelessComm_SetFinished(BOOL param0)
{
    WirelessComm_GetManager()->unk_20 = param0;
}

WirelessCommConnection *WirelessComm_GetConnectionUnion(void)
{
    return &WirelessComm_GetManager()->unk_90;
}

WirelessCommParentList *WirelessComm_GetParentList(void)
{
    return &WirelessComm_GetConnectionUnion()->val2;
}

WirelessCommChildList *WirelessComm_GetChildList(void)
{
    return &WirelessComm_GetConnectionUnion()->val1;
}

void WirelessComm_ResetParentList(void)
{
    WirelessCommParentList *v0 = WirelessComm_GetParentList();

    MI_CpuClear8(v0, sizeof(WirelessCommParentList));
    v0->unk_1C0 = 280;
}

WirelessCommTransfer *WirelessComm_GetTransfer(void)
{
    return &WirelessComm_GetManager()->unk_254;
}

void WirelessComm_ResetTransfer(void)
{
    WirelessCommTransfer *v0 = WirelessComm_GetTransfer();
    v0->unk_18 = 0;
}

u32 WirelessComm_GetGameInfoGgid(void)
{
    return WirelessComm_GetManager()->unk_04;
}

u32 WirelessComm_GetGameInfoField0(void)
{
    return (u32)WirelessComm_GetManager()->unk_40.unk_00.unk_00.unk_00_0;
}

u32 WirelessComm_GetGameInfoField8(void)
{
    return (u32)WirelessComm_GetManager()->unk_40.unk_00.unk_00.unk_00_8;
}

u32 WirelessComm_GetGameInfoField16(void)
{
    return (u32)WirelessComm_GetManager()->unk_40.unk_00.unk_04.unk_00_16;
}

u32 WirelessComm_GetGameInfoSize(void)
{
    return sizeof(WirelessCommGameInfo);
}

WirelessCommGameInfo *WirelessComm_GetGameInfo(void)
{
    return &WirelessComm_GetManager()->unk_40;
}

WirelessCommConnectData *WirelessComm_GetConnectData(void)
{
    return &WirelessComm_GetManager()->unk_78;
}

WirelessCommBssidHigh WirelessComm_MakeBssidHigh(u8 *param0)
{
    u32 v0;
    WirelessCommBssidHigh v1;

    v1.unk_00.val2 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        v1.unk_00.val1[v0] = param0[v0 + 2];
    }

    return v1;
}

WirelessCommBssidLow WirelessComm_MakeBssidLow(u8 *param0)
{
    u32 v0;
    WirelessCommBssidLow v1;

    v1.unk_00.val2 = 0;

    for (v0 = 0; v0 < 2; v0++) {
        v1.unk_00.val1[v0] = param0[v0];
    }

    return v1;
}

void WirelessComm_SplitNumber(u32 param0, u32 *param1, u32 *param2)
{
    *param1 = param0 % 10000;
    *param2 = (param0 / 10000) % 10000;
}

u32 WirelessComm_GetPacketSize(void)
{
    return sizeof(WirelessCommPacket);
}

static u32 WirelessComm_NextPacketId()
{
    return ((u32)(OS_GetTick() + GX_GetVCount()) & 0xFFFFFFFE) + 1;
}

static u32 WirelessComm_XorData(u32 param0, u32 param1, void *param2)
{
    u32 v0;
    u32 *v1 = (u32 *)param2;
    MATHRandContext16 v2;

    MATH_InitRand16(&v2, param0);

    for (v0 = 0; v0 < param1 / sizeof(u32); v0++) {
        (*v1) ^= ((MATH_Rand16(&v2, 0) << 16) | MATH_Rand16(&v2, 0));
        v1++;
    }

    return v2.x;
}

void WirelessComm_BuildPacket(void *param0, void *param1, u32 param2, int param3, u32 param4)
{
    WirelessCommPacket *v0 = (WirelessCommPacket *)param0;
    WirelessCommGameInfo *v1 = WirelessComm_GetGameInfo();

    v0->unk_00.unk_00_0 = v1->unk_00.unk_00.unk_00_0;
    v0->unk_00.unk_00_8 = v1->unk_00.unk_00.unk_00_8;
    v0->unk_00.unk_00_12 = v1->unk_00.unk_00.unk_00_12;
    v0->unk_00.unk_00_16 = (u16)WirelessComm_NextPacketId();
    v0->unk_04.unk_00_0 = v1->unk_00.unk_04.unk_00_0;
    v0->unk_04.unk_00_8 = v1->unk_00.unk_04.unk_00_8;
    v0->unk_04.unk_00_12 = v1->unk_00.unk_04.unk_00_12;
    v0->unk_04.unk_00_16 = 0;
    v0->unk_08.unk_00_0 = (u8)param4;
    v0->unk_08.unk_00_8 = param3;
    v0->unk_08.unk_00_16 = SVC_GetCRC16(0, param1, param2);
    v0->unk_0C.unk_00_0 = (u8)WirelessComm_GetPacketSize();
    v0->unk_0C.unk_00_8 = param2;

    if (param2) {
        MI_CpuCopy8(param1, ((u8 *)param0) + v0->unk_0C.unk_00_0, param2);
    }

    WirelessComm_OnPacket(v0);

    if ((int)v1->unk_00.unk_00.unk_00_12 == 1) {
        WirelessComm_XorData(v0->unk_00.unk_00_16, param2 + v0->unk_0C.unk_00_0 - sizeof(WirelessCommPacketHeader), &v0->unk_04);
    }
}

void WirelessComm_DecryptPacket(void *param0)
{
    WirelessCommPacket *v0 = (WirelessCommPacket *)param0;
    WirelessCommGameInfo *v1 = WirelessComm_GetGameInfo();

    if ((int)v0->unk_00.unk_00_12 == 1) {
        u32 v2;

        v2 = WirelessComm_XorData(v0->unk_00.unk_00_16, sizeof(WirelessCommPacketConfig) + sizeof(WirelessCommPacketMeta) + sizeof(WirelessCommPacketTail), &v0->unk_04);
        WirelessComm_XorData(v2, v0->unk_0C.unk_00_0 + v0->unk_0C.unk_00_8 - sizeof(WirelessCommPacket), (void *)((u32)param0 + sizeof(WirelessCommPacket)));
    }
}

BOOL WirelessComm_VerifyPacket(void *param0)
{
    WirelessCommPacket *v0 = (WirelessCommPacket *)param0;
    u16 v1 = SVC_GetCRC16(0, ((u8 *)param0) + v0->unk_0C.unk_00_0, v0->unk_0C.unk_00_8);

    if (v0->unk_08.unk_00_16 == v1) {
        return 1;
    } else {
        return 0;
    }
}
