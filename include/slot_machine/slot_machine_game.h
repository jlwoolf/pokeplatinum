#ifndef POKEPLATINUM_SLOT_MACHINE_GAME_H
#define POKEPLATINUM_SLOT_MACHINE_GAME_H

#include "slot_machine/struct_slot_machine_context_decl.h"

#include "enums.h"

void SlotMachine_InitGame(SlotMachineContext *param0);
void SlotMachine_FreeGame(SlotMachineContext *param0);
int SlotMachine_Update(SlotMachineContext *param0);
SlotMachineSymbol SlotMachine_GetReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2);
SlotMachineSymbol SlotMachine_GetVisibleReelSymbol(SlotMachineContext *param0, SlotMachineReelIndex param1, int param2);

#endif // POKEPLATINUM_SLOT_MACHINE_GAME_H
