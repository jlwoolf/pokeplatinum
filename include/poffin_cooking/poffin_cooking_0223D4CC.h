#ifndef POKEPLATINUM_POFFIN_COOKING_0223D4CC_H
#define POKEPLATINUM_POFFIN_COOKING_0223D4CC_H

#include "constants/heap.h"

#include "struct_defs/comm_cmd_table.h"

#include "poffin_cooking/struct_poffin_cooking_comm_decl.h"

PoffinCookingComm *poffin_cooking_0223D4CC(const CommCmdTable *param0, int param1, void *param2, int param3, enum HeapID heapID);
BOOL poffin_cooking_0223D508(int param0, const void *param1, int param2, PoffinCookingComm *param3);
void poffin_cooking_0223D558(PoffinCookingComm *param0);
int poffin_cooking_0223D570(PoffinCookingComm *param0);

#endif // POKEPLATINUM_POFFIN_COOKING_0223D4CC_H
