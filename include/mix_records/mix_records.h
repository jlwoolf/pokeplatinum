#ifndef POKEPLATINUM_MIX_RECORDS_H
#define POKEPLATINUM_MIX_RECORDS_H

#include "struct_decls/struct_020961E8_decl.h"

#include "overlay_manager.h"

int MixRecords_Init(ApplicationManager *appMan, int *param1);
int MixRecords_Main(ApplicationManager *appMan, int *param1);
int MixRecords_Exit(ApplicationManager *appMan, int *param1);
void MixRecords_ShowDisconnectMessage(MixRecordsComm *param0);
void MixRecords_HandleCommState(MixRecordsComm *param0, int param1, u8 param2);
void MixRecords_HandlePlayerReady(MixRecordsComm *param0, int param1, u8 param2);
int MixRecords_GetConnectedPlayerCount(void);

#endif // POKEPLATINUM_MIX_RECORDS_H
