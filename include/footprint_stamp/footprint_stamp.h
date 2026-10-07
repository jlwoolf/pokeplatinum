#ifndef POKEPLATINUM_FOOTPRINT_STAMP_H
#define POKEPLATINUM_FOOTPRINT_STAMP_H

#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_comm_state.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

#include "overlay_manager.h"

int FootprintStamp_Init(ApplicationManager *appMan, int *param1);
int FootprintStamp_Main(ApplicationManager *appMan, int *param1);
int FootprintStamp_Exit(ApplicationManager *appMan, int *param1);
FootprintStampCommState *FootprintStamp_GetCommState(FootprintStampApp *param0);
BOOL FootprintStamp_AddEntry(FootprintStampApp *param0, const FootprintStampEntry *param1, s32 param2);
void FootprintStamp_DrawPlayerName(FootprintStampApp *param0, s32 param1);
void FootprintStamp_ClearPlayerName(FootprintStampApp *param0, u32 param1);

#endif // POKEPLATINUM_FOOTPRINT_STAMP_H
