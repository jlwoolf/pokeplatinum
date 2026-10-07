#ifndef POKEPLATINUM_SPIN_TRADE_H
#define POKEPLATINUM_SPIN_TRADE_H

#include "struct_defs/struct_0209C0F0.h"

#include "spin_trade/struct_spin_trade_decl.h"
#include "spin_trade/struct_spin_trade_order.h"
#include "spin_trade/struct_spin_trade_result.h"

#include "overlay_manager.h"

int SpinTrade_Init(ApplicationManager *appMan, int *param1);
int SpinTrade_Exit(ApplicationManager *appMan, int *param1);
int SpinTrade_Main(ApplicationManager *appMan, int *param1);
void SpinTrade_SetState(SpinTrade *param0, u32 param1);
void SpinTrade_HandleSpinTradePos(SpinTrade *param0, const UnionRoomCommSpinTradePos *param1);
void SpinTrade_HandleOrder(SpinTrade *param0, const SpinTradeOrder *param1);
void SpinTrade_SetPlayerCount(SpinTrade *param0, int param1);
void SpinTrade_SetMonSlot(SpinTrade *param0, int param1, int param2);
void SpinTrade_HandleResult(SpinTrade *param0, const SpinTradeResult *param1);

#endif // POKEPLATINUM_SPIN_TRADE_H
