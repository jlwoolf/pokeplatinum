#ifndef POKEPLATINUM_IMAGE_CLIP_APP_02255D44_H
#define POKEPLATINUM_IMAGE_CLIP_APP_02255D44_H

#include "overlay_manager.h"

int VisualCompetitionApp_Init(ApplicationManager *appMan, int *param1);
int VisualCompetitionApp_Main(ApplicationManager *appMan, int *param1);
int VisualCompetitionApp_Exit(ApplicationManager *appMan, int *param1);
int VisualCompetition_Init(ApplicationManager *appMan, int *param1);
int VisualCompetition_Main(ApplicationManager *appMan, int *param1);
int VisualCompetition_Exit(ApplicationManager *appMan, int *param1);
void VisualCompetition_GetGridPoint(u32 param0, u32 param1, u32 param2, u32 param3, u32 param4, int *param5, int *param6);

#endif // POKEPLATINUM_IMAGE_CLIP_APP_02255D44_H
