#ifndef POKEPLATINUM_GTS_H
#define POKEPLATINUM_GTS_H

#include "gts/struct_gts.h"

int GTS_Init(ApplicationManager *appMan, int *param1);
int GTS_Main(ApplicationManager *appMan, int *param1);
int GTS_Exit(ApplicationManager *appMan, int *param1);
void GTS_SetNextApp(GTSState *param0, int param1, int param2);
void GTS_RequestExit(GTSState *param0);
void GTS_SetNextScreen(GTSState *param0, int param1);
int GTS_GetNextScreen(GTSState *param0);
void GTS_SaveEmailString(GTSState *param0);
void GTS_SaveRegistrationValues(GTSState *param0);
void GTS_SaveEmailValue(GTSState *param0);
void GTS_InitTrainer(GTSState *param0);
void GTS_LoadTrainerEmail(GTSState *param0);
void GTS_SetRegistrationCode(GTSState *param0);
void GTS_SetTrainerId(GTSState *param0, u32 param1);
u32 GTS_GetRegistrationCode(GTSState *param0);
u32 GTS_GetEmailValue(GTSState *param0);
void GTS_SetResult(GTSState *param0, int param1);
int GTS_GetResult(GTSState *param0);

#endif // POKEPLATINUM_GTS_H
