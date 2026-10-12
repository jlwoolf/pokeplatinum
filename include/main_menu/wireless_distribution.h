#ifndef POKEPLATINUM_MAIN_MENU_02238534_H
#define POKEPLATINUM_MAIN_MENU_02238534_H

#include "main_menu/funcptr_wireless_distribution.h"

BOOL WirelessDistribution_Stop(void);
BOOL WirelessDistribution_Start(void *param0, WirelessDistributionStateFunc param1, void *param2);
int WirelessDistribution_VerifyData(void);
int WirelessDistribution_GetContextSize(void);
void *WirelessDistribution_GetData(void);

#endif // POKEPLATINUM_MAIN_MENU_02238534_H
