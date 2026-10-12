#ifndef POKEPLATINUM_BALL_THROW_H
#define POKEPLATINUM_BALL_THROW_H

#include "battle_anim/struct_ball_rotation_decl.h"
#include "battle_anim/struct_ball_capsule_seal_effect_decl.h"
#include "battle_anim/struct_ball_capsule_config.h"
#include "battle_anim/struct_ball_particle_effect_decl.h"
#include "battle_anim/struct_ball_particle_effect_params.h"
#include "battle_anim/struct_ball_throw.h"

#include "spl.h"

BallCapsuleSealEffect *BallCapsuleSealEffect_Alloc(enum HeapID heapID);
BallCapsuleSealEffect *BallCapsuleSealEffect_New(enum HeapID heapID, const BallCapsuleConfig *ballCapCfg);
void BallCapsuleSealEffect_Init(BallCapsuleSealEffect *ballCapSealEff, const BallCapsuleConfig *ballCapCfg);
void BallCapsuleSealEffect_Start(BallCapsuleSealEffect *ballCapSealEff);
BOOL BallCapsuleSealEffect_IsReady(BallCapsuleSealEffect *ballCapSealEff);
void BallCapsuleSealEffect_Play(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1);
void BallCapsuleSealEffect_PlayDefault(BallCapsuleSealEffect *ballCapSealEff);
BOOL BallCapsuleSealEffect_IsActive(BallCapsuleSealEffect *ballCapSealEff);
void BallCapsuleSealEffect_Free(BallCapsuleSealEffect *ballCapSealEff);
BallParticleEffect *BallParticleEffect_New(BallParticleEffectParams *param0);
void BallParticleEffect_Start(BallParticleEffect *param0);
BOOL BallParticleEffect_Update(BallParticleEffect *param0);
void BallParticleEffect_Free(BallParticleEffect *param0);
void BallRotation_StartAction(BallRotation *param0, int param1);
BOOL BallRotation_UpdateAction(BallRotation *param0, int param1);
BallRotation *BallRotation_New(BallThrow *param0);
BOOL BallRotation_IsActive(BallRotation *param0);
BOOL BallRotation_IsDone(BallRotation *param0);
void BallRotation_SetState(BallRotation *param0, int param1);
BOOL BallRotation_IsState(BallRotation *param0, int param1);
void BallRotation_Free(BallRotation *param0);
void BallRotation_SetMode(BallRotation *param0, int param1);
int BallRotation_GetMode(BallRotation *param0);
void BallRotation_SetDrawFlag(BallRotation *param0, int param1);
void BallRotation_SetPosition(BallRotation *param0, s16 param1, s16 param2);
void BallRotation_SetZRotation(BallRotation *param0, u16 param1);
void BallRotation_SetFrameTicking(BallRotation *param0, BOOL param1);
void BallRotation_SetPriority(BallRotation *param0, int param1);
void BallRotation_SetExplicitPriority(BallRotation *param0, int param1);
void BallRotation_SetDelay(BallRotation *param0, int param1);

#endif // POKEPLATINUM_BALL_THROW_H
