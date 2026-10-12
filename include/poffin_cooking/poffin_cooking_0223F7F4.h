#ifndef POKEPLATINUM_POFFIN_COOKING_0223F7F4_H
#define POKEPLATINUM_POFFIN_COOKING_0223F7F4_H

#include "poffin_cooking/struct_poffin_cooking_touch_tracker.h"
#include "poffin_cooking/struct_poffin_cooking_touch_input.h"
#include "poffin_cooking/struct_poffin_cooking_stir_state.h"
#include "poffin_cooking/struct_poffin_cooking_stir_stats.h"
#include "poffin_cooking/struct_poffin_cooking_cpu_input.h"
#include "poffin_cooking/struct_poffin_cooking_stir_level.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"
#include "poffin_cooking/struct_poffin_cooking_simulation.h"
#include "poffin_cooking/struct_poffin_cooking_synchro_state.h"
#include "poffin_cooking/struct_poffin_cooking_session.h"

#include "poffin.h"

s32 poffin_cooking_0223F7F4(int param0, int param1, int param2, int param3, int param4, int param5);
void poffin_cooking_0223F820(PoffinCookingTouchTracker *param0);
void poffin_cooking_0223F83C(PoffinCookingTouchTracker *param0);
void poffin_cooking_0223F88C(PoffinCookingTouchInput *param0, PoffinCookingTouchTracker *param1);
u16 poffin_cooking_0223F900(PoffinCookingStirState *param0, const PoffinCookingSession *param1, u32 param2, u32 param3);
u16 poffin_cooking_0223FA84(const PoffinCookingStirState *param0);
u32 poffin_cooking_0223FA8C(const PoffinCookingStirState *param0);
void poffin_cooking_0223FA90(PoffinCookingStirState *param0, int param1);
s32 poffin_cooking_0223FAA8(const PoffinCookingStirState *param0);
void poffin_cooking_0223FAAC(PoffinCookingStirStats *param0, s32 param1, int param2);
BOOL poffin_cooking_0223FB30(s32 param0, int param1);
BOOL poffin_cooking_0223FB50(s32 param0, int param1);
fx32 poffin_cooking_0223FB68(u16 param0, int param1);
void poffin_cooking_0223FBA4(PoffinCookingCpuInput *param0);
void poffin_cooking_0223FBBC(PoffinCookingCpuInput *param0, int param1, s32 param2, BOOL param3);
BOOL poffin_cooking_0223FC3C(const PoffinCookingCpuInput *param0, s32 param1);
BOOL poffin_cooking_0223FC58(PoffinCookingStirLevel *param0, PoffinCookingStirState *param1);
void poffin_cooking_0223FCE8(PoffinCookingSynchroState *param0, const PoffinCookingSession *param1, int param2, s32 param3, int param4, BOOL param5, BOOL param6);
void poffin_cooking_0223FDB0(PoffinCookingSimulation *param0);
BOOL poffin_cooking_0223FDD8(PoffinCookingSimulation *param0, const PoffinCookingSession *param1, u32 param2);
void poffin_cooking_0223FE50(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2);
void poffin_cooking_0223FEC0(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2);
void poffin_cooking_0223FF44(PoffinCookingSimulation *param0, PoffinCookingBlendState *param1, int param2);
void poffin_cooking_0223FFA0(PoffinCookingSimulation *param0);
void poffin_cooking_0223FFD4(PoffinCookingSimulation *param0, Poffin *param1, const PoffinCookingSession *param2, u32 param3, u32 param4);
void poffin_cooking_022401AC(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2);

#endif // POKEPLATINUM_POFFIN_COOKING_0223F7F4_H
