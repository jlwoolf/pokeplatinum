#ifndef POKEPLATINUM_GROUP_CONFIRMATION_H
#define POKEPLATINUM_GROUP_CONFIRMATION_H

#include "spin_trade/struct_spin_trade_group_decl.h"

#include "overlay_manager.h"

int SpinTradeGroup_Init(ApplicationManager *appMan, int *param1);
int SpinTradeGroup_Main(ApplicationManager *appMan, int *param1);
int SpinTradeGroup_Exit(ApplicationManager *appMan, int *param1);
void SpinTradeGroup_HandleCommState(SpinTradeGroup *param0, int param1, u8 param2);
void SpinTradeGroup_HandleConfirm(SpinTradeGroup *param0, int param1, u8 param2);

#endif // POKEPLATINUM_GROUP_CONFIRMATION_H
