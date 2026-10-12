#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H

#include "poffin_cooking/struct_poffin_cooking_sprite_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_particle.h"

typedef struct {
    int unk_00;
    PoffinCookingSpriteManager *unk_04;
    PoffinCookingSpriteSet *unk_08;
    u32 unk_0C;
    PoffinCookingParticle unk_10[8];
    int unk_410;
} PoffinCookingParticleManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H
