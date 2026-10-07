#ifndef POKEPLATINUM_FRONTIER_SCRIPT_MANAGER_H
#define POKEPLATINUM_FRONTIER_SCRIPT_MANAGER_H

#include "constants/heap.h"

#include "struct_decls/battle_frontier_decl.h"

#include "frontier_facilities/defs.h"
#include "frontier_facilities/frontier_graphics.h"
#include "frontier_facilities/struct_frontier_facilities_0222E8C8.h"

FrontierScriptManager *FrontierScriptManager_New(BattleFrontier *frontier, enum HeapID heapID, int scene);
BOOL FrontierScriptManager_RunScript(FrontierScriptManager *scriptMan);
void FrontierScriptManager_Free(FrontierScriptManager *scriptMan);
void FrontierScriptManager_Load(FrontierScriptManager *scriptMan, int scene, int offsetID);
void FrontierScriptManager_UpdateMessageLoader(FrontierScriptManager *scriptMan, int scene, enum HeapID heapID);
FrontierScriptLocalVars *FrontierFacilities_SaveScriptLocalVars(FrontierScriptManager *param0, enum HeapID heapID);
void FrontierFacilities_RestoreScriptLocalVars(FrontierScriptManager *param0, FrontierScriptLocalVars *param1);
u16 *FrontierFacilities_GetScriptVarPointer(FrontierScriptManager *param0, int param1);
FrontierGraphics *FrontierScriptManager_GetGraphics(FrontierScriptManager *scriptMan);

#endif // POKEPLATINUM_FRONTIER_SCRIPT_MANAGER_H
