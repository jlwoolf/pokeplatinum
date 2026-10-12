#ifndef POKEPLATINUM_MAIN_MENU_02233408_H
#define POKEPLATINUM_MAIN_MENU_02233408_H

#include <nitro/wm.h>

#include "main_menu/struct_wireless_comm_manager.h"
#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_transfer.h"
#include "main_menu/struct_wireless_comm_game_info.h"
#include "main_menu/struct_wireless_comm_bssid_high.h"
#include "main_menu/struct_wireless_comm_bssid_low.h"
#include "main_menu/struct_wireless_comm_connect_data.h"
#include "main_menu/union_wireless_comm_connection.h"

WMParentParam *WirelessComm_GetParentParam(void);
WirelessCommManager *WirelessComm_GetManager(void);
int WirelessComm_GetState(void);
void WirelessComm_SetState(int param0);
int WirelessComm_GetCommRole(void);
void WirelessComm_SetCommRole(int param0);
int WirelessComm_GetLinkType(void);
void WirelessComm_SetLinkType(int param0);
u32 WirelessComm_GetPacketPort(void);
void WirelessComm_SetChannel(u32 param0);
WMScanParam *WirelessComm_GetScanParam(void);
u32 WirelessComm_GetParentSendSize(void);
u32 WirelessComm_GetChildSendSize(void);
void *WirelessComm_GetParentSendBuffer(void);
void *WirelessComm_GetChildSendBuffer(void);
WMBssDesc *WirelessComm_GetScanResult(void);
void WirelessComm_SetAid(u16 param0);
BOOL WirelessComm_GetDisconnected(void);
void WirelessComm_SetConnected(BOOL param0);
void WirelessComm_SetDisconnected(BOOL param0);
void WirelessComm_SetFinished(BOOL param0);
WirelessCommConnection *WirelessComm_GetConnectionUnion(void);
WirelessCommParentList *WirelessComm_GetParentList(void);
WirelessCommChildList *WirelessComm_GetChildList(void);
void WirelessComm_ResetParentList(void);
WirelessCommTransfer *WirelessComm_GetTransfer(void);
void WirelessComm_ResetTransfer(void);
u32 WirelessComm_GetGameInfoGgid(void);
u32 WirelessComm_GetGameInfoField0(void);
u32 WirelessComm_GetGameInfoField8(void);
u32 WirelessComm_GetGameInfoField16(void);
u32 WirelessComm_GetGameInfoSize(void);
WirelessCommGameInfo *WirelessComm_GetGameInfo(void);
WirelessCommConnectData *WirelessComm_GetConnectData(void);
WirelessCommBssidHigh WirelessComm_MakeBssidHigh(u8 *param0);
WirelessCommBssidLow WirelessComm_MakeBssidLow(u8 *param0);
void WirelessComm_SplitNumber(u32 param0, u32 *param1, u32 *param2);
u32 WirelessComm_GetPacketSize(void);
void WirelessComm_BuildPacket(void *param0, void *param1, u32 param2, int param3, u32 param4);
void WirelessComm_DecryptPacket(void *param0);
BOOL WirelessComm_VerifyPacket(void *param0);

#endif // POKEPLATINUM_MAIN_MENU_02233408_H
