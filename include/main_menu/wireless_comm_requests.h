#ifndef POKEPLATINUM_MAIN_MENU_02233814_H
#define POKEPLATINUM_MAIN_MENU_02233814_H

BOOL WirelessComm_SendMPData(const void *param0, u32 param1, u16 param2);
BOOL WirelessComm_Enable(void);
BOOL WirelessComm_Disable(void);
BOOL WirelessComm_MeasureChannel(u32 param0);
BOOL WirelessComm_SetParentParameter(void);
BOOL WirelessComm_StartParent(void);
BOOL WirelessComm_StartScan(void);
BOOL WirelessComm_StartScanForParent(void);
BOOL WirelessComm_EndScan(void);
BOOL WirelessComm_StartConnect(void);
BOOL WirelessComm_StartMP(void);
BOOL WirelessComm_PowerOn(void);
BOOL WirelessComm_PowerOff(void);
BOOL WirelessComm_Reset(void);
BOOL WirelessComm_End(void);

#endif // POKEPLATINUM_MAIN_MENU_02233814_H
