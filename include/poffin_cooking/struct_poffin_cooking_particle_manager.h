#ifndef POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H
#define POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H

#include "poffin_cooking/struct_poffin_cooking_sprite_manager.h"
#include "poffin_cooking/struct_poffin_cooking_sprite_set.h"
#include "poffin_cooking/struct_poffin_cooking_particle.h"

typedef struct {
    int loaded;
    PoffinCookingSpriteManager *spriteManager;
    PoffinCookingSpriteSet *spriteSets;
    u32 heapID;
    PoffinCookingParticle particles[8];
    int nextSerial;
} PoffinCookingParticleManager;

#endif // POKEPLATINUM_STRUCT_POFFIN_COOKING_PARTICLE_MANAGER_H
