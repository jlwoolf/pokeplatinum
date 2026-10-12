#include "main_menu/wireless_comm_callbacks.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/struct_wireless_comm_child_list.h"
#include "main_menu/struct_wireless_comm_parent_list.h"
#include "main_menu/struct_wireless_comm_packet.h"

void WirelessComm_OnError(WMErrCode param0)
{
#pragma unused(param0)
    return;
}

void WirelessComm_OnStateChange(WMStateCode param0)
{
#pragma unused(param0)
    return;
}

void WirelessComm_OnBssDesc(WMBssDesc *param0)
{
#pragma unused(param0)
    return;
}

void WirelessComm_OnParentList(WirelessCommParentList *param0)
{
#pragma unused(param0)
    return;
}

void WirelessComm_OnChildList(WirelessCommChildList *param0)
{
#pragma unused(param0)
    return;
}

void WirelessComm_OnPacket(WirelessCommPacket *param0)
{
#pragma unused(param0)
    return;
}
