#ifndef POKEPLATINUM_SLOT_MACHINE_ANIM_H
#define POKEPLATINUM_SLOT_MACHINE_ANIM_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "overworld_anim_manager.h"

void SlotMachine_InitReelSprites(SlotMachineContext *param0);
void SlotMachine_InitPayoutDigits(SlotMachineContext *param0);
void SlotMachine_InitCreditDigits(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateReel(SlotMachineContext *param0, SlotMachineReelType param1);
void SlotMachine_SetReelState(OverworldAnimManager *param0, SlotMachineReelStateEnum param1);
void SlotMachine_SetReelVisible(OverworldAnimManager *param0, int param1);
int SlotMachine_IsReelDone(OverworldAnimManager *param0);
OverworldAnimManager *SlotMachine_CreateSymbol(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateWinSymbol(SlotMachineContext *param0, SlotMachineWinType param1);
void SlotMachine_SetWinSymbolState(OverworldAnimManager *param0, SlotMachineWinSymbolState param1);
int SlotMachine_IsWinSymbolDone(OverworldAnimManager *param0);
OverworldAnimManager *SlotMachine_CreateBonus(SlotMachineContext *param0);
int SlotMachine_IsBonusDone(OverworldAnimManager *param0);
OverworldAnimManager *SlotMachine_CreateButton(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateButton2(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateButton3(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateButton4(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateCreditDigit(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreatePayoutDigit(SlotMachineContext *param0);
OverworldAnimManager *SlotMachine_CreateNumber(SlotMachineContext *param0, SlotMachineNumberType param1);
OverworldAnimManager *SlotMachine_CreateNumber2(SlotMachineContext *param0, u32 param1);
OverworldAnimManager *SlotMachine_CreateJackpot(SlotMachineContext *param0);

#endif // POKEPLATINUM_SLOT_MACHINE_ANIM_H
