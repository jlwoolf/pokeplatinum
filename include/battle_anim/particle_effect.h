#ifndef POKEPLATINUM_PARTICLE_EFFECT_H
#define POKEPLATINUM_PARTICLE_EFFECT_H

#include "constants/heap.h"

#include "battle_anim/struct_particle_effect_config.h"
#include "battle_anim/struct_particle_effect_template.h"
#include "battle_anim/struct_particle_effect_context_decl.h"
#include "battle_anim/struct_particle_effect_decl.h"

ParticleEffectContext *ParticleEffectContext_New(enum HeapID heapID, ParticleEffectConfig *param1);
ParticleEffect *ParticleEffectContext_CreateEffect(ParticleEffectContext *param0, ParticleEffectTemplate *param1);
void ParticleEffectContext_Free(ParticleEffectContext *param0);
void ParticleEffectContext_FreeEffects(ParticleEffectContext *param0);
ParticleEffect *ParticleEffect_New(enum HeapID heapID, ParticleEffectTemplate *param1);
void ParticleEffect_Start(ParticleEffect *param0);
BOOL ParticleEffect_IsActive(ParticleEffect *param0);

#endif // POKEPLATINUM_PARTICLE_EFFECT_H
