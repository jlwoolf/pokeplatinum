#ifndef POKEPLATINUM_SLOT_MACHINE_H
#define POKEPLATINUM_SLOT_MACHINE_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"
#include "overlay_manager.h"

int SlotMachine_Init(ApplicationManager *appMan, int *param1);
int SlotMachine_Main(ApplicationManager *appMan, int *param1);
int SlotMachine_Exit(ApplicationManager *appMan, int *param1);
void SlotMachine_InitMessageBox(SlotMachineContext *param0);
void SlotMachine_ShowMessage(SlotMachineContext *param0, u32 param1);
void SlotMachine_HideMessage(SlotMachineContext *param0);
void SlotMachine_SetBgmMode(SlotMachineContext *param0, SlotMachineBgmMode param1);
void *SlotMachine_Alloc(u32 param0);
void *SlotMachine_ReadNarcMember(SlotMachineContext *param0, u32 param1, int param2);

#endif // POKEPLATINUM_SLOT_MACHINE_H
