#ifndef POKEPLATINUM_POFFIN_COOKING_H
#define POKEPLATINUM_POFFIN_COOKING_H

#include "poffin_cooking/struct_poffin_cooking_app.h"

#include "overlay_manager.h"

BOOL PoffinCooking_Init(ApplicationManager *appMan, int *state);
BOOL PoffinCooking_Main(ApplicationManager *appMan, int *state);
BOOL PoffinCooking_Exit(ApplicationManager *appMan, int *state);
void poffin_cooking_0223B774(PoffinCookingApp *param0, int param1);
void poffin_cooking_0223B77C(PoffinCookingApp *param0, int param1);
void poffin_cooking_0223B784(PoffinCookingApp *param0);

#endif // POKEPLATINUM_POFFIN_COOKING_H
