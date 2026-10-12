#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H

#include "poffin_cooking/struct_poffin_cooking_stir_state.h"
#include "poffin_cooking/struct_poffin_cooking_stir_stats.h"
#include "poffin_cooking/struct_poffin_cooking_cpu_input.h"
#include "poffin_cooking/struct_poffin_cooking_stir_level.h"
#include "poffin_cooking/struct_poffin_cooking_synchro_state.h"

typedef struct {
    u32 frameCount;
    u32 poffinValue;
    u32 poffinLevel;
    PoffinCookingCpuInput cpuInput;
    PoffinCookingStirState stirState;
    PoffinCookingStirStats stirStats;
    PoffinCookingStirLevel stirLevel;
    PoffinCookingSynchroState synchroState;
} PoffinCookingSimulation;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H
