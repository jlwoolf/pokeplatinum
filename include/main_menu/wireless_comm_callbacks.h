#ifndef POKEPLATINUM_MAIN_MENU_022337FC_H
#define POKEPLATINUM_MAIN_MENU_022337FC_H

#include <nitro/wm.h>

#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_packet.h"

void WirelessComm_OnError(WMErrCode param0);
void WirelessComm_OnStateChange(WMStateCode param0);
void WirelessComm_OnBssDesc(WMBssDesc *param0);
void WirelessComm_OnParentList(WirelessCommParentList *param0);
void WirelessComm_OnChildList(WirelessCommChildList *param0);
void WirelessComm_OnPacket(WirelessCommPacket *param0);

#endif // POKEPLATINUM_MAIN_MENU_022337FC_H
