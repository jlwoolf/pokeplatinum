#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H

#include "poffin_cooking/struct_poffin_cooking_stir_state.h"
#include "poffin_cooking/struct_poffin_cooking_stir_stats.h"
#include "poffin_cooking/struct_poffin_cooking_cpu_input.h"
#include "poffin_cooking/struct_poffin_cooking_stir_level.h"
#include "poffin_cooking/struct_poffin_cooking_synchro_state.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    PoffinCookingCpuInput unk_0C;
    PoffinCookingStirState unk_1C;
    PoffinCookingStirStats unk_30;
    PoffinCookingStirLevel unk_4C;
    PoffinCookingSynchroState unk_58;
} PoffinCookingSimulation;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_SIMULATION_H
