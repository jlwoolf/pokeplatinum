#include "battle_anim/particle_effect.h"

#include <nitro.h>
#include <string.h>

#include "battle_anim/battle_anim_system.h"
#include "battle_anim/battle_particle_util.h"
#include "battle_anim/struct_particle_effect_config.h"
#include "battle_anim/struct_particle_effect_template.h"

#include "heap.h"
#include "particle_system.h"
#include "spl.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct ParticleEffect {
    int unk_00;
    enum HeapID heapID;
    ParticleEffectTemplate particleEffectTemplate;
    ParticleSystem *unk_10;
    SPLEmitter *unk_14;
    SysTask *unk_18;
    int unk_1C;
    BOOL unk_20;
} ParticleEffect;

typedef struct ParticleEffectContext {
    enum HeapID heapID;
    ParticleEffectConfig unk_04;
    ParticleEffect *unk_08[16];
} ParticleEffectContext;

static void ParticleEffect_UpdateTask(SysTask *param0, void *param1);
static void ParticleEffect_CreateEmitters(ParticleEffect *param0, SPLEmitterCallback param1);
static void ParticleEffect_EmitterCallback(SPLEmitter *param0);
static int ParticleEffect_GetEmitterCount(int param0);

ParticleEffectContext *ParticleEffectContext_New(enum HeapID heapID, ParticleEffectConfig *param1)
{
    ParticleEffectContext *v0 = NULL;
    v0 = Heap_Alloc(heapID, sizeof(ParticleEffectContext));

    if (v0 == NULL) {
        GF_ASSERT(FALSE);
        return NULL;
    }

    BattleAnimSystem_SetDefaultAlphaBlending();

    v0->heapID = heapID;

    if (param1 != NULL) {
        v0->unk_04 = *param1;
    }

    {
        int v1;

        for (v1 = 0; v1 < 16; v1++) {
            v0->unk_08[v1] = NULL;
        }
    }

    return v0;
}

ParticleEffect *ParticleEffectContext_CreateEffect(ParticleEffectContext *param0, ParticleEffectTemplate *particleEffectTemplate)
{
    int v0;
    ParticleEffect *v1 = NULL;

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->unk_08[v0] != NULL) {
            continue;
        }

        param0->unk_08[v0] = ParticleEffect_New(param0->heapID, particleEffectTemplate);
        param0->unk_08[v0]->unk_18 = NULL;

        v1 = param0->unk_08[v0];
        v1->unk_00 = v0;

        break;
    }

    if (v1 == NULL) {
        GF_ASSERT(FALSE);
    }

    return v1;
}

void ParticleEffectContext_Free(ParticleEffectContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->unk_08[v0] == NULL) {
            continue;
        }

        Heap_Free(param0->unk_08[v0]);
    }

    Heap_Free(param0);
}

void ParticleEffectContext_FreeEffects(ParticleEffectContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->unk_08[v0] == NULL) {
            continue;
        }

        BattleParticleUtil_FreeParticleSystem(param0->unk_08[v0]->unk_10);

        if (param0->unk_08[v0]->unk_20 == 0) {
            continue;
        }

        if (param0->unk_08[v0]->unk_18 == NULL) {
            continue;
        }

        SysTask_Done(param0->unk_08[v0]->unk_18);
    }
}

ParticleEffect *ParticleEffect_New(enum HeapID heapID, ParticleEffectTemplate *particleEffectTemplate)
{
    ParticleEffect *v0;

    v0 == NULL;

    v0 = Heap_Alloc(heapID, sizeof(ParticleEffect));

    if (v0 == NULL) {
        GF_ASSERT(FALSE);
        return NULL;
    }

    v0->heapID = heapID;
    v0->particleEffectTemplate = *particleEffectTemplate;
    v0->unk_1C = ParticleEffect_GetEmitterCount(v0->particleEffectTemplate.resourceID);
    v0->unk_10 = BattleParticleUtil_CreateParticleSystem(v0->heapID, v0->particleEffectTemplate.resourceID, 1);

    return v0;
}

void ParticleEffect_Start(ParticleEffect *param0)
{
    param0->unk_20 = 1;
    ParticleEffect_CreateEmitters(param0, ParticleEffect_EmitterCallback);
    param0->unk_18 = SysTask_Start(ParticleEffect_UpdateTask, param0, 1000);
}

BOOL ParticleEffect_IsActive(ParticleEffect *param0)
{
    return param0->unk_20;
}

static void ParticleEffect_UpdateTask(SysTask *param0, void *param1)
{
    ParticleEffect *v0 = (ParticleEffect *)param1;
    int v1 = 0;

    v1 = ParticleSystem_GetActiveEmitterCount(v0->unk_10);

    if (v1 != 0) {
        return;
    }

    v0->unk_20 = 0;

    BattleParticleUtil_FreeParticleSystem(v0->unk_10);
    SysTask_Done(param0);
}

static void ParticleEffect_CreateEmitters(ParticleEffect *param0, SPLEmitterCallback param1)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_1C; v0++) {
        ParticleSystem_CreateEmitterWithCallback(param0->unk_10, v0, param1, param0);
    }

    ParticleSystem_SetCameraProjection(param0->unk_10, param0->particleEffectTemplate.cameraProjection);
}

static void ParticleEffect_EmitterCallback(SPLEmitter *param0)
{
    ParticleEffect *v0 = ParticleSystem_GetEmitterCallbackParam();
}

static int ParticleEffect_GetEmitterCount(int param0)
{
    const int v0[] = {
        0x5,
        0xB,
        0x6,
        0x7,
        0x2,
        0x1,
        0x2,
        0x1,
        0x1,
        0x4,
        0x3,
        0x3,
        0x2,
        0x9,
        0x1,
        0x1,
        0x1,
        0x2,
        0x1,
        0x1,
        0x1,
        0x1
    };
    int v1 = param0 - 5;

    if (v1 >= NELEMS(v0)) {
        GF_ASSERT(FALSE);
        return 0;
    }

    return v0[v1];
}
