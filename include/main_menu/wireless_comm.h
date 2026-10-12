#ifndef POKEPLATINUM_MAIN_MENU_02232DC8_H
#define POKEPLATINUM_MAIN_MENU_02232DC8_H

#include "main_menu/struct_wireless_comm_params.h"

void WirelessComm_Init(WirelessCommParams *param0, void *param1);
void WirelessComm_Update(void);
void WirelessComm_Start(void);
BOOL WirelessComm_IsParentAvailable(u32 param0);
void WirelessComm_SelectParent(u32 param0);
u32 WirelessComm_GetLinkLevel(void);
u32 WirelessComm_GetNumConnected(void);
void WirelessComm_StartSend(void);
void WirelessComm_StartReceive(void);
void WirelessComm_SendData(void *param0, u32 param1, u32 param2);
BOOL WirelessComm_IsReceiveComplete(void);
BOOL WirelessComm_IsSendComplete(void);
BOOL WirelessComm_IsAwaitingData(void);
BOOL WirelessComm_IsLinkActive(void);
void WirelessComm_Stop(void);
BOOL WirelessComm_HasStopped(void);

#endif // POKEPLATINUM_MAIN_MENU_02232DC8_H
