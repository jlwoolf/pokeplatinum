#include "battle_anim/ball_throw.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/seal_case.h"

#include "applications/capsule_menu/main.h"
#include "battle_anim/battle_anim_helpers.h"
#include "battle_anim/battle_anim_system.h"
#include "battle_anim/battle_anim_util.h"
#include "battle_anim/battle_particle_util.h"
#include "battle_anim/seal_anim.h"
#include "battle_anim/struct_battle_mon_obj_data.h"
#include "battle_anim/struct_ball_capsule_config.h"
#include "battle_anim/struct_ball_particle_effect_params.h"
#include "battle_anim/struct_ball_throw.h"

#include "ball_seal_info.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "sound_playback.h"
#include "spl.h"
#include "sprite.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"

#include "res/graphics/battle/sprites.naix"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    BOOL *unk_0C;
    ParticleSystem *unk_10;
    BallSeal *unk_14;
    SPLEmitterCallback unk_18;
} BallSealEmitterSpawnTask;

typedef struct BallCapsuleSealEffect_t {
    enum HeapID heapID;
    BallCapsuleConfig ballCapCfg;
    int sealCount;
    ParticleSystem *sealParticleSystems[9];
    BallSeal *seals[9];
    BOOL sealActiveFlags[9];
    SPLEmitter *emitter;
    SysTask *task;
    BOOL isActive;
    NARC *particleNarc;
    int state;
    int hasCapsule;
    int ballType;
    int capsuleID;
    BallCapsule capsule;
} BallCapsuleSealEffect;

typedef struct BallParticleEffect {
    BallParticleEffectParams unk_00;
    SPLEmitter *unk_14;
    ParticleSystem *unk_18;
    int unk_1C;
    int unk_20;
} BallParticleEffect;

typedef struct {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    int unk_08;
    int unk_0C;
    int unk_10;
} BallThrowTrajectory;

typedef struct BallRotation {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    BOOL unk_1C;
    u8 unk_20;
    u8 unk_21;
    s8 unk_22;
    BOOL unk_24;
    BOOL unk_28;
    SpriteManager *unk_2C;
    ManagedSprite *unk_30;
    ValueLerpContext unk_34;
    XYTransformContext unk_48[2];
    BallThrow unk_90;
    BallThrowTrajectory unk_B8;
    SysTask *unk_CC;
    BallParticleEffect *unk_D0;
    PaletteFadeContext *unk_D4;
    BattleMonOBJData *unk_D8;
    int unk_DC;
} BallRotation;

static void BallCapsuleSealEffect_UpdateTask(SysTask *param0, void *param1);
static void BallCapsuleSealEffect_CreateEmitters(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1);
static void BallCapsuleSealEffect_SetEmitterPosition(SPLEmitter *param0);
static void BallCapsuleSealEffect_SetSealEmitterPosition(SPLEmitter *param0);
static void BallRotation_LoadGraphics(BallRotation *param0);
static void BallRotation_CreateSprite(BallRotation *param0);
static void BallRotation_InitTargetPosition(BallRotation *param0);
static void BallRotation_GetStartPosition(BallRotation *param0, s16 *param1, s16 *param2);
static BOOL BallRotation_ModeSendOut(BallRotation *param0);
static BOOL BallRotation_ModeSendOutQuick(BallRotation *param0);
static BOOL BallRotation_ModeUnused(BallRotation *param0);
static BOOL BallRotation_ModeThrow(BallRotation *param0);
static BOOL BallRotation_ModeTrainerSendOut(BallRotation *param0);
static BOOL BallRotation_ModeRecall(BallRotation *param0);

// clang-format off
static const int sBallThrowGraphics[][4] = {
    { ball_throws_master_ball_NCGR_lz,  ball_throws_master_ball_NCLR,  ball_throws_shared_cell_NCER_lz_2,  ball_throws_shared_anim_NANR_lz_1          },
    { ball_throws_ultra_ball_NCGR_lz,   ball_throws_ultra_ball_NCLR,   ball_throws_shared_cell_NCER_lz_3,  ball_throws_shared_anim_NANR_lz_2          },
    { ball_throws_great_ball_NCGR_lz,   ball_throws_great_ball_NCLR,   ball_throws_shared_cell_NCER_lz_4,  ball_throws_shared_anim_NANR_lz_3          },
    { ball_throws_poke_ball_NCGR_lz,    ball_throws_poke_ball_NCLR,    ball_throws_shared_cell_NCER_lz_1,  ball_throws_shared_anim_NANR_lz            },
    { ball_throws_safari_ball_NCGR_lz,  ball_throws_safari_ball_NCLR,  ball_throws_shared_cell_NCER_lz_5,  ball_throws_shared_anim_NANR_lz_4          },
    { ball_throws_net_ball_NCGR_lz,     ball_throws_net_ball_NCLR,     ball_throws_shared_cell_NCER_lz_6,  ball_throws_shared_anim_NANR_lz_5          },
    { ball_throws_dive_ball_NCGR_lz,    ball_throws_dive_ball_NCLR,    ball_throws_shared_cell_NCER_lz_7,  ball_throws_shared_anim_NANR_lz_6          },
    { ball_throws_nest_ball_NCGR_lz,    ball_throws_nest_ball_NCLR,    ball_throws_shared_cell_NCER_lz_8,  ball_throws_shared_anim_NANR_lz_7          },
    { ball_throws_repeat_ball_NCGR_lz,  ball_throws_repeat_ball_NCLR,  ball_throws_shared_cell_NCER_lz_9,  ball_throws_shared_anim_NANR_lz_8          },
    { ball_throws_timer_ball_NCGR_lz,   ball_throws_timer_ball_NCLR,   ball_throws_shared_cell_NCER_lz_10, ball_throws_shared_anim_NANR_lz_9          },
    { ball_throws_luxury_ball_NCGR_lz,  ball_throws_luxury_ball_NCLR,  ball_throws_shared_cell_NCER_lz_11, ball_throws_shared_anim_NANR_lz_10         },
    { ball_throws_premier_ball_NCGR_lz, ball_throws_premier_ball_NCLR, ball_throws_shared_cell_NCER_lz_12, ball_throws_shared_anim_NANR_lz_11         },
    { ball_throws_dusk_ball_NCGR_lz,    ball_throws_dusk_ball_NCLR,    ball_throws_shared_cell_NCER_lz_14, ball_throws_quick_dusk_heal_anim_NANR_lz_1 },
    { ball_throws_heal_ball_NCGR_lz,    ball_throws_heal_ball_NCLR,    ball_throws_shared_cell_NCER_lz_15, ball_throws_quick_dusk_heal_anim_NANR_lz_2 },
    { ball_throws_quick_ball_NCGR_lz,   ball_throws_quick_ball_NCLR,   ball_throws_shared_cell_NCER_lz_13, ball_throws_quick_dusk_heal_anim_NANR_lz   },
    { ball_throws_cherish_ball_NCGR_lz, ball_throws_cherish_ball_NCLR, ball_throws_shared_cell_NCER_lz_16, ball_throws_shared_anim_NANR_lz_12         },
    { ball_throws_park_ball_NCGR_lz,    ball_throws_park_ball_NCLR,    ball_throws_shared_cell_NCER_lz_17, ball_throws_shared_anim_NANR_lz_13         },
    { ball_throws_mud_NCGR_lz,          ball_throws_mud_NCLR,          ball_throws_mud_cell_NCER_lz,       ball_throws_mud_anim_NANR_lz               },
    { ball_throws_bait_NCGR_lz,         ball_throws_bait_NCLR,         ball_throws_shared_cell_NCER_lz_18, ball_throws_bait_anim_NANR_lz              },
    { ball_throws_bait_NCGR_lz,         ball_throws_bait_NCLR,         ball_throws_shared_cell_NCER_lz_18, ball_throws_bait_anim_NANR_lz              },
};
// clang-format on

static const int sBallOpenParticleData[][2] = {
    { 0x1, 0x5 },
    { 0x2, 0x4 },
    { 0x3, 0x3 },
    { 0x4, 0x3 },
    { 0x5, 0x3 },
    { 0x6, 0x4 },
    { 0x7, 0x3 },
    { 0x8, 0x4 },
    { 0x9, 0x3 },
    { 0xA, 0x5 },
    { 0xB, 0x4 },
    { 0xC, 0x3 },
    { 0xD, 0x3 },
    { 0xE, 0x3 },
    { 0xF, 0x4 },
    { 0x10, 0x4 },
    { 0x11, 0x3 },
    { 0x1, 0x5 },
    { 0x1, 0x5 },
    { 0x24, 0x2 }
};

static const int sBallParticleData[][3] = {
    { 0x13, 0x0, 0x5 },
    { 0x14, 0x2, 0x5 },
    { 0x15, 0x1, 0x5 },
    { 0x16, 0x3, 0x5 },
    { 0x17, 0x1, 0x5 },
    { 0x18, 0x1, 0x6 },
    { 0x19, 0x1, 0x5 },
    { 0x1A, 0x1, 0x5 },
    { 0x1B, 0x2, 0x5 },
    { 0x1C, 0x3, 0x7 },
    { 0x1D, 0x1, 0x6 },
    { 0x1E, 0x0, 0x5 },
    { 0x1F, 0x1, 0x5 },
    { 0x20, 0x0, 0x5 },
    { 0x21, 0x1, 0x6 },
    { 0x22, 0x1, 0x6 },
    { 0x23, 0x3, 0x5 },
    { 0x13, 0x0, 0x5 },
    { 0x13, 0x0, 0x5 },
    { 0x24, 0xFF, 0x2 }
};

static int BallThrow_GetBallIndex(int param0)
{
    int v0;

    if ((param0 < 1) || (param0 > (0xFF + 20))) {
        v0 = 4;
    } else if (param0 >= 0xFF) {
        v0 = param0 - 0xFF;
    } else {
        v0 = param0;
    }

    return v0 - 1;
}

static BOOL BallThrow_TypeRotates(int param0)
{
    int v0;
    BOOL v1;
    int v2[] = {
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        15,
        16,
        17,
    };

    v1 = 0;

    for (v0 = 0; v0 < NELEMS(v2); v0++) {
        if (v2[v0] != param0) {
            continue;
        }

        v1 = 1;
        break;
    }

    return v1;
}

static BOOL BallThrow_TypeFades(int param0)
{
    int v0;
    BOOL v1;
    int v2[] = {
        6,
        7,
        8,
        9,
        10,
        11,
    };

    v1 = 0;

    for (v0 = 0; v0 < NELEMS(v2); v0++) {
        if (v2[v0] != param0) {
            continue;
        }

        v1 = 1;
        break;
    }

    return v1;
}

static BOOL BallThrow_TypeAnimatesFrame(int param0)
{
    int v0;
    BOOL v1;
    int v2[] = {
        3,
        5,
        1,
    };

    v1 = 1;

    for (v0 = 0; v0 < NELEMS(v2); v0++) {
        if (v2[v0] != param0) {
            continue;
        }

        v1 = 0;
        break;
    }

    return v1;
}

static int BallThrow_GetOpenParticleIndex(int param0)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallOpenParticleData[v0][0];
}

static int BallThrow_GetOpenEmitterCount(int param0)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallOpenParticleData[v0][1];
}

static int BallThrow_GetParticleIndex(int param0)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallParticleData[v0][0];
}

static int BallThrow_GetEmitterCount(int param0)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallParticleData[v0][2];
}

static int BallThrow_GetExcludedEmitter(int param0)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallParticleData[v0][1];
}

static int BallThrow_GetGraphics(int param0, int param1)
{
    int v0 = BallThrow_GetBallIndex(param0);
    return sBallThrowGraphics[v0][param1];
}

BallCapsuleSealEffect *BallCapsuleSealEffect_Alloc(enum HeapID heapID)
{
    BallCapsuleSealEffect *ballCapSealEff = NULL;

    ballCapSealEff = Heap_Alloc(heapID, sizeof(BallCapsuleSealEffect));

    if (ballCapSealEff == NULL) {
        GF_ASSERT(FALSE);
        return NULL;
    }

    ballCapSealEff->heapID = heapID;
    ballCapSealEff->isActive = 0;

    return ballCapSealEff;
}

BallCapsuleSealEffect *BallCapsuleSealEffect_New(enum HeapID heapID, const BallCapsuleConfig *ballCapCfg)
{
    BallCapsuleSealEffect *ballCapSealEff = NULL;

    ballCapSealEff = BallCapsuleSealEffect_Alloc(heapID);
    BallCapsuleSealEffect_Init(ballCapSealEff, ballCapCfg);

    {
        int v1;

        ballCapSealEff->sealCount = 0;

        for (v1 = 0; v1 < 9; v1++) {
            ballCapSealEff->sealParticleSystems[v1] = NULL;
            ballCapSealEff->seals[v1] = NULL;
            ballCapSealEff->sealActiveFlags[v1] = 0;
        }
    }

    return ballCapSealEff;
}

void BallCapsuleSealEffect_Init(BallCapsuleSealEffect *ballCapSealEff, const BallCapsuleConfig *ballCapCfgPtr)
{
    ballCapSealEff->ballCapCfg = *ballCapCfgPtr;
    ballCapSealEff->capsuleID = Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_BALL_CAPSULE_ID, NULL);

    GF_ASSERT(ballCapSealEff->capsuleID < 12 + 1);

    if (ballCapSealEff->capsuleID == 0) {
        ballCapSealEff->hasCapsule = 0;

        if (ballCapSealEff->ballCapCfg.ballTypeOverride != 0) {
            ballCapSealEff->ballType = ballCapSealEff->ballCapCfg.ballTypeOverride;
        } else {
            ballCapSealEff->ballType = Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_POKEBALL, NULL);
        }
    } else {
        ballCapSealEff->hasCapsule = 1;
        Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_BALL_CAPSULE, &ballCapSealEff->capsule);
    }
}

static void BallCapsuleSealEffect_LoadSealsTask(SysTask *param0, void *ballCapSealEffPtr)
{
    BallCapsuleSealEffect *ballCapSealEff = ballCapSealEffPtr;
    int i;
    int v2;
    int v3;
    int v4;
    BallSeal *v5;

    switch (ballCapSealEff->state) {
    case 0:
        ballCapSealEff->particleNarc = NARC_ctor(NARC_INDEX_WAZAEFFECT__EFFECTDATA__BALL_PARTICLE, ballCapSealEff->heapID);

        for (i = 0; i < 2; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= SEAL_ID_MAX) {
                continue;
            }

            v3 = CapsuleMenu_GetSealParticleIndex(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 1:
        for (i = 2; i < 4; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = CapsuleMenu_GetSealParticleIndex(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 2:
        for (i = 4; i < 6; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = CapsuleMenu_GetSealParticleIndex(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 3:
        for (i = 6; i < 8; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = CapsuleMenu_GetSealParticleIndex(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state = 0xFF;

        NARC_dtor(ballCapSealEff->particleNarc);
        SysTask_Done(param0);
        break;
    default:
        break;
    }
}

void BallCapsuleSealEffect_Start(BallCapsuleSealEffect *ballCapSealEff)
{
    int v0;
    int v1;
    int v2;
    int v3;
    BallSeal *v4;

    if (ballCapSealEff->hasCapsule == 0) {
        v3 = BallThrow_GetOpenParticleIndex(ballCapSealEff->ballType);

        ballCapSealEff->sealCount = 1;
        ballCapSealEff->sealParticleSystems[0] = BattleParticleUtil_CreateParticleSystemEx(ballCapSealEff->heapID, 99, v3, 0);
        ballCapSealEff->state = 0xFF;
    } else {
        ballCapSealEff->sealCount = 0;
        ballCapSealEff->state = 0;

        {
            SysTask *v5;

            v5 = SysTask_Start(BallCapsuleSealEffect_LoadSealsTask, ballCapSealEff, 1000);
            BallCapsuleSealEffect_LoadSealsTask(v5, ballCapSealEff);
        }
    }
}

BOOL BallCapsuleSealEffect_IsReady(BallCapsuleSealEffect *ballCapSealEff)
{
    if (ballCapSealEff->state == 0xFF) {
        return 1;
    }

    return 0;
}

void BallCapsuleSealEffect_Play(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1)
{
    ballCapSealEff->isActive = 1;

    BattleAnimSystem_SetDefaultAlphaBlending();
    BallCapsuleSealEffect_CreateEmitters(ballCapSealEff, param1);

    ballCapSealEff->task = SysTask_Start(BallCapsuleSealEffect_UpdateTask, ballCapSealEff, 1000);
}

void BallCapsuleSealEffect_PlayDefault(BallCapsuleSealEffect *ballCapSealEff)
{
    BallCapsuleSealEffect_Play(ballCapSealEff, BallCapsuleSealEffect_SetEmitterPosition);
}

BOOL BallCapsuleSealEffect_IsActive(BallCapsuleSealEffect *ballCapSealEff)
{
    return ballCapSealEff->isActive;
}

static void BallCapsuleSealEffect_UpdateTask(SysTask *param0, void *ballCapSealEffPtr)
{
    int v0;
    BOOL v1;
    BallCapsuleSealEffect *ballCapSealEff = (BallCapsuleSealEffect *)ballCapSealEffPtr;

    v1 = 0;

    GF_ASSERT(ballCapSealEff->sealCount <= 9);

    for (v0 = 0; v0 < ballCapSealEff->sealCount; v0++) {
        if (ballCapSealEff->sealParticleSystems[v0] == NULL) {
            continue;
        }

        if ((ParticleSystem_GetActiveEmitterCount(ballCapSealEff->sealParticleSystems[v0]) == 0) && (ballCapSealEff->sealActiveFlags[v0] != 0)) {
            BattleParticleUtil_FreeParticleSystem(ballCapSealEff->sealParticleSystems[v0]);
            ballCapSealEff->sealParticleSystems[v0] = NULL;
            ballCapSealEff->sealActiveFlags[v0] = 0;
            continue;
        }

        v1 = 1;
    }

    if (v1 == 0) {
        ballCapSealEff->isActive = 0;
        SysTask_Done(param0);
    }
}

void BallCapsuleSealEffect_Free(BallCapsuleSealEffect *ballCapSealEff)
{
    Heap_Free(ballCapSealEff);
}

static void BallCapsuleSealEffect_EmitTask(SysTask *param0, void *param1)
{
    BallSealEmitterSpawnTask *v0 = (BallSealEmitterSpawnTask *)param1;

    if (v0->unk_04 == 0) {
        *(v0->unk_0C) = 1;
        ParticleSystem_CreateEmitterWithCallback(v0->unk_10, 0, v0->unk_18, v0);
        ParticleSystem_SetCameraProjection(v0->unk_10, 1);
        SysTask_Done(param0);
        Heap_Free(v0);
    } else {
        v0->unk_04--;
    }
}

static void BallCapsuleSealEffect_CreateEmitters(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1)
{
    int v0, v1;
    int v2;
    int v3;

    if (ballCapSealEff->hasCapsule == 0) {
        v3 = BallThrow_GetOpenEmitterCount(ballCapSealEff->ballType);

        for (v0 = 0; v0 < v3; v0++) {
            ParticleSystem_CreateEmitterWithCallback(ballCapSealEff->sealParticleSystems[0], v0, param1, ballCapSealEff);
        }

        ballCapSealEff->sealActiveFlags[0] = 1;
        ParticleSystem_SetCameraProjection(ballCapSealEff->sealParticleSystems[0], 1);
    } else {
        for (v0 = 0; v0 < ballCapSealEff->sealCount; v0++) {
            BallSealEmitterSpawnTask *v4 = Heap_Alloc(ballCapSealEff->heapID, sizeof(BallSealEmitterSpawnTask));

            GF_ASSERT(v4 != NULL);

            v4->unk_00 = v0;
            v4->unk_08 = ballCapSealEff->ballCapCfg.battlerType;
            v4->unk_18 = BallCapsuleSealEffect_SetSealEmitterPosition;

            ballCapSealEff->sealActiveFlags[v0] = 0;

            v4->unk_0C = &ballCapSealEff->sealActiveFlags[v0];
            v4->unk_10 = ballCapSealEff->sealParticleSystems[v0];
            v4->unk_14 = ballCapSealEff->seals[v0];

            GF_ASSERT(v4->unk_14 != NULL);
            v4->unk_04 = SealAnim_GetSpawnDelay(v4->unk_14);

            SysTask_Start(BallCapsuleSealEffect_EmitTask, v4, 1001);
        }
    }
}

static void BallCapsuleSealEffect_GetEmitterPosition(int param0, VecFx32 *param1)
{
    BattleAnimUtil_GetBattlerTypeWorldPos(param0, param1, 0, 1);

    {
        int v0;
        int v1;
        s16 v2;
        s16 v3;
        VecFx32 v4;

        switch (param0) {
        case 0:
            v2 = 0;
            v3 = -16;
            break;
        case 1:
            v2 = -15;
            v3 = -25;
            break;
        case 2:
            v2 = -8;
            v3 = -12;
            break;
        case 3:
            v2 = -14;
            v3 = -25;
            break;
        case 4:
            v2 = -8;
            v3 = -12;
            break;
        case 5:
        default:
            v2 = -16;
            v3 = -29;
            break;
        }

        v0 = 172 * ((+10) + v2);
        v1 = 172 * (32 + v3);

        VEC_Set(&v4, v0, v1, 0);

        param1->x -= v4.x;
        param1->y -= v4.y;
    }
}

static void BallCapsuleSealEffect_SetEmitterPosition(SPLEmitter *param0)
{
    int v0;
    BallCapsuleSealEffect *ballCapSealEff = ParticleSystem_GetEmitterCallbackParam();
    v0 = ballCapSealEff->ballCapCfg.battlerType;

    {
        VecFx32 v2;

        BallCapsuleSealEffect_GetEmitterPosition(v0, &v2);
        SPLEmitter_SetPos(param0, &v2);
    }
}

static void BallCapsuleSealEffect_SetSealEmitterPosition(SPLEmitter *param0)
{
    VecFx32 v0;
    int v1;
    BallCapsuleSealEffect *unused;
    BallSealEmitterSpawnTask *v3 = ParticleSystem_GetEmitterCallbackParam();
    v1 = v3->unk_08;

    BallCapsuleSealEffect_GetEmitterPosition(v1, &v0);

    {
        u8 v4;
        u8 v5, v6;
        s16 v7, v8;
        int v9, v10;
        VecFx32 v11;

        v4 = BallSeal_GetSealType(v3->unk_14);

        if (CapsuleMenu_IsAlphabetSeal(v4) == 1) {
            v5 = BallSeal_GetX(v3->unk_14);
            v6 = BallSeal_GetY(v3->unk_14);
            v7 = (v5 - 190);
            v8 = (70 - v6 + (+30));
            v9 = v7 * 172;
            v10 = v8 * 172;

            VEC_Set(&v11, v9, v10, 0);

            v0.x += v11.x;
            v0.y += v11.y;
            v0.z += v11.z;
        } else {
            v5 = BallSeal_GetX(v3->unk_14);
            v6 = BallSeal_GetY(v3->unk_14);
            v7 = (v5 - 190);
            v8 = (70 - v6 + (+30));
            v9 = v7 * 172;
            v10 = v8 * 172;

            VEC_Set(&v11, v9, v10, 0);

            v0.x += v11.x;
            v0.y += v11.y;
            v0.z += v11.z;
        }
    }

    SPLEmitter_SetPos(param0, &v0);
}

static void BallParticleEffect_SetEmitterPosition(SPLEmitter *param0)
{
    BallParticleEffect *v0 = ParticleSystem_GetEmitterCallbackParam();

    {
        VecFx32 v1;
        int v2, v3;
        s16 v4, v5;

        v4 = (v0->unk_00.unk_00 - 190 + 61);
        v5 = (70 - v0->unk_00.unk_02 + (+30));
        v2 = v4 * 172;
        v3 = v5 * 172;

        VEC_Set(&v1, v2, v3, 0);
        SPLEmitter_SetPos(param0, &v1);
    }
}

BallParticleEffect *BallParticleEffect_New(BallParticleEffectParams *param0)
{
    BallParticleEffect *v0 = Heap_Alloc(param0->heapID, sizeof(BallParticleEffect));
    GF_ASSERT(v0 != NULL);

    v0->unk_00 = *param0;

    if (v0->unk_00.unk_10) {
        v0->unk_20 = BallThrow_GetParticleIndex(0xFF + 20);
        v0->unk_1C = BallThrow_GetEmitterCount(0xFF + 20);
    } else {
        v0->unk_20 = BallThrow_GetParticleIndex(v0->unk_00.unk_04);
        v0->unk_1C = BallThrow_GetEmitterCount(v0->unk_00.unk_04);
    }

    v0->unk_18 = BattleParticleUtil_CreateParticleSystemEx(v0->unk_00.heapID, 99, v0->unk_20, 0);

    return v0;
}

void BallParticleEffect_Start(BallParticleEffect *param0)
{
    int v0;
    int v1;
    BallParticleEffect *v2 = param0;

    if (v2->unk_00.unk_0C == 0xFF) {
        if (v2->unk_00.unk_10) {
            for (v0 = 0; v0 < v2->unk_1C; v0++) {
                ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v0, BallParticleEffect_SetEmitterPosition, v2);
            }
        } else {
            for (v0 = 0; v0 < v2->unk_1C; v0++) {
                if (v0 == BallThrow_GetExcludedEmitter(v2->unk_00.unk_04)) {
                    continue;
                }

                ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v0, BallParticleEffect_SetEmitterPosition, v2);
            }
        }
    } else {
        v1 = v2->unk_00.unk_0C;
        ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v1, BallParticleEffect_SetEmitterPosition, v2);
    }

    ParticleSystem_SetCameraProjection(v2->unk_18, 1);
}

BOOL BallParticleEffect_Update(BallParticleEffect *param0)
{
    BallParticleEffect *v0 = param0;

    if (ParticleSystem_GetActiveEmitterCount(v0->unk_18) == 0) {
        BattleParticleUtil_FreeParticleSystem(v0->unk_18);
        return 0;
    }

    return 1;
}

void BallParticleEffect_Free(BallParticleEffect *param0)
{
    Heap_Free(param0);
}

static BOOL (*const sBallThrowModeHandlers[])(BallRotation *) = {
    BallRotation_ModeSendOut,
    BallRotation_ModeSendOutQuick,
    BallRotation_ModeUnused,
    BallRotation_ModeThrow,
    BallRotation_ModeTrainerSendOut,
    BallRotation_ModeRecall
};

static BOOL BallRotation_Action0(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 1);
    }

    v0 = BallRotation_IsState(param0, 2);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action1(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 3);
    }

    v0 = BallRotation_IsState(param0, 4);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action2(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 5);
    }

    v0 = BallRotation_IsState(param0, 6);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action3(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 7);
    }

    v0 = BallRotation_IsState(param0, 14);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action4(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 15);
    }

    v0 = BallRotation_IsState(param0, 18);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action5(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 19);
    }

    v0 = BallRotation_IsState(param0, 27);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action6(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 21);
    }

    v0 = BallRotation_IsState(param0, 22);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL BallRotation_Action7(BallRotation *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        BallRotation_SetState(param0, 23);
    }

    v0 = BallRotation_IsState(param0, 27);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL (*const sBallRotationActionHandlers[])(BallRotation *) = {
    BallRotation_Action0,
    BallRotation_Action1,
    BallRotation_Action2,
    BallRotation_Action3,
    BallRotation_Action4,
    BallRotation_Action5,
    BallRotation_Action6,
    BallRotation_Action7
};

void BallRotation_StartAction(BallRotation *param0, int param1)
{
    param0->unk_00 = param1;
    param0->unk_04 = 0;
}

BOOL BallRotation_UpdateAction(BallRotation *param0, int param1)
{
    BOOL v0 = sBallRotationActionHandlers[param0->unk_00](param0);
    return v0;
}

static void BallRotation_SetSubState(BallRotation *param0, int param1)
{
    param0->unk_14 = param1;
    param0->unk_08 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = 0;
}

static BOOL BallRotation_ThrowStep0(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep1(BallRotation *param0)
{
    BOOL v0 = BallRotation_ModeSendOut(param0);

    if (v0 == 0) {
        BallRotation_SetSubState(param0, 2);
    }

    return 1;
}

static BOOL BallRotation_ThrowStep2(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 3);
    return 1;
}

static BOOL BallRotation_ThrowStep3(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        ManagedSprite_SetAnim(param0->unk_30, 1);
        {
            BallParticleEffectParams v0;

            v0.unk_04 = param0->unk_90.ballID;
            v0.heapID = param0->unk_90.heapID;
            v0.unk_0C = 0xFF;
            v0.unk_10 = 0;

            ManagedSprite_GetPositionXY(param0->unk_30, &v0.unk_00, &v0.unk_02);

            param0->unk_D8 = BattleMonOBJData_NewAll(param0->unk_90.battleSys, param0->unk_90.heapID);
            param0->unk_D0 = BallParticleEffect_New(&v0);
        }
        param0->unk_08++;
        break;
    case 1: {
        int v1 = ManagedSprite_GetAnimationFrame(param0->unk_30);

        if (v1 >= 2) {
            param0->unk_24 = 0;
            param0->unk_08++;
        }
    } break;
    case 2:
        BallParticleEffect_Start(param0->unk_D0);
        BattleMonOBJData_Free(param0->unk_D8);
        param0->unk_08++;
        break;
    case 3: {
        if (BallParticleEffect_Update(param0->unk_D0) == 0) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, 0);
            BallParticleEffect_Free(param0->unk_D0);
            param0->unk_08++;
        }
    } break;
    default:
        BallRotation_SetSubState(param0, 4);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep4(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep5(BallRotation *param0)
{
    BOOL v0;

    switch (param0->unk_0C) {
    case 0:
        ManagedSprite_GetPositionXY(param0->unk_30, &param0->unk_B8.unk_00, &param0->unk_B8.unk_02);
        param0->unk_B8.unk_04 = 60;
        param0->unk_B8.unk_06 = 180;
        param0->unk_B8.unk_08 = 10;
        param0->unk_B8.unk_10 = 12;
        param0->unk_0C++;
        break;
    default: {
        v0 = BallRotation_ModeSendOut(param0);

        if (v0 == 0) {
            BallRotation_SetSubState(param0, 6);
        }
    } break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep6(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep7(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 8);
    return 1;
}

static BOOL BallRotation_ThrowStep8(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 9);
    return 1;
}

static BOOL BallRotation_ThrowStep9(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:

    {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
        PaletteData_StartFade(param0->unk_90.paletteSys, 0x4, 1 << v0, -1, 0, 12, 0x37F);

        param0->unk_08++;
    } break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->unk_90.paletteSys) != 0) {
            break;
        }

        {
            int v1;

            v1 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
            PaletteData_StartFade(param0->unk_90.paletteSys, 0x4, 1 << v1, -1, 12, 0, 0x37F);
        }

        param0->unk_08++;
        break;
    default:
        if (PaletteData_GetSelectedBuffersMask(param0->unk_90.paletteSys) != 0) {
            break;
        }

        BallRotation_SetSubState(param0, 10);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep10(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 11);
    return 1;
}

static BOOL BallRotation_ThrowStep11(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        if ((++param0->unk_0C) < 1) {
            break;
        }

        {
            s16 v0, v1;

            ManagedSprite_GetPositionXY(param0->unk_30, &v0, &v1);
            PosLerpContext_Init(&param0->unk_48[0], v0, v0, v1, v1 + 32, 32 / 3);

            param0->unk_08++;
        }
        break;
    case 1:
        if (PosLerpContext_UpdateAndApplyToSprite(&param0->unk_48[0], param0->unk_30) == 0) {
            param0->unk_08++;

            BallRotation_SetSubState(param0, 13);
        }
        break;
    default:
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep12(BallRotation *param0)
{
    return 1;
}

static const s16 sBallWobbleOffsets[][3] = {
    { 0x0, -7, 0x1 },
    { 0x1, -5, 0x0 },
    { 0x0, -3, 0x0 },
    { 0x1, -2, 0x0 },
    { 0x1, 0x2, 0x0 },
    { 0x1, 0x3, 0x0 },
    { 0x0, 0x5, 0x0 },
    { 0x1, 0x7, 0x1 },
    { 0x0, -5, 0x1 },
    { 0x0, -3, 0x0 },
    { 0x1, -2, 0x0 },
    { 0x1, 0x2, 0x0 },
    { 0x0, 0x3, 0x0 },
    { 0x0, 0x5, 0x1 },
    { 0x0, -2, 0x0 },
    { 0x1, -1, 0x0 },
    { 0x0, 0x1, 0x0 },
    { 0x0, 0x2, 0x0 },
    { 0x0, -2, 0x1 },
    { 0x0, 0x2, 0x1 },
    { 0xFF, 0xFF, 0x0 }
};

static const int sBallWobbleSounds[][2] = {
    { 0x1, SEQ_SE_DP_KON_sseq },
    { 0x8, SEQ_SE_DP_KON_sseq },
    { 0xE, SEQ_SE_DP_KON2_sseq },
    { 0x12, SEQ_SE_DP_KON3_sseq },
    { 0x14, SEQ_SE_DP_KON4_sseq }
};

static BOOL BallRotation_ThrowStep13(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        ManagedSprite_SetAnim(param0->unk_30, 1);
        ManagedSprite_SetAnimationFrame(param0->unk_30, 0);
        param0->unk_08++;
    case 1: {
        s16 v0, v1;
        int v2;

        v0 = 0;
        v1 = sBallWobbleOffsets[param0->unk_0C][1];
        v2 = sBallWobbleOffsets[param0->unk_0C][2];

        ManagedSprite_SetAnimationFrame(param0->unk_30, v2);

        param0->unk_0C++;

        {
            int v3;

            for (v3 = 0; v3 < 5; v3++) {
                if (sBallWobbleSounds[v3][0] == param0->unk_0C) {
                    Sound_PlayPannedEffect(sBallWobbleSounds[v3][1], 117);
                }
            }
        }

        if ((param0->unk_0C > 20) || (v0 == 0xFF) || (v1 == 0xFF)) {
            param0->unk_08++;
        } else {
            ManagedSprite_OffsetPositionXY(param0->unk_30, v0, v1);
        }
    } break;
    default:
        BallRotation_SetSubState(param0, 14);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep14(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep15(BallRotation *param0)
{
    param0->unk_0C++;

    if (param0->unk_0C >= 14) {
        param0->unk_08++;
        param0->unk_0C = 0;
        BallRotation_SetSubState(param0, 16);
    }

    return 1;
}

static BOOL BallRotation_ThrowStep16(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 17);
    return 1;
}

static const s16 sBallShakeOffsets[][12] = {
    { -2, -0, 0x2, 0x2, 0x0, -2, 0xFF, 0xFF, 0xFF },
    { -1, -0, 0x1, 0x1, 0x0, -1, 0xFF, 0xFF, 0xFF },
    { -1, 0x0, 0x1, 0x1, 0x0, -1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF }
};

static BOOL BallRotation_ThrowStep17(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        GF_ASSERT(param0->unk_18 < 3);
        param0->unk_08++;
    case 1: {
        s16 v0;

        v0 = sBallShakeOffsets[param0->unk_18][param0->unk_0C];
        param0->unk_0C++;

        if ((param0->unk_0C > 11) || (v0 == 0xFF)) {
            param0->unk_08++;
            param0->unk_18++;
            ManagedSprite_SetAffineZRotation(param0->unk_30, 0);
            BallRotation_SetSubState(param0, 18);
            return 1;
        } else {
            if (param0->unk_0C == 5) {
                Sound_PlayPannedEffect(SEQ_SE_DP_BOWA_sseq, 117);
            }

            ManagedSprite_OffsetPositionXY(param0->unk_30, v0, 0);
            ManagedSprite_OffsetAffineZRotation(param0->unk_30, (((v0) * 2) * 0xffff) / 360);
        }
    } break;
    default:
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep18(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep19(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 20);
    return 1;
}

static BOOL BallRotation_ThrowStep20(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 27);
    return 1;
}

static BOOL BallRotation_ThrowStep21(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:

    {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
        PaletteData_StartFade(param0->unk_90.paletteSys, 0x4, 1 << v0, -5, 0, 10, 0x0);

        param0->unk_08++;
    } break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->unk_90.paletteSys) != 0) {
            break;
        }

        {
            BallParticleEffectParams v1;

            v1.unk_04 = param0->unk_90.ballID;
            v1.heapID = param0->unk_90.heapID;
            v1.unk_0C = BallThrow_GetExcludedEmitter(v1.unk_04);
            v1.unk_10 = 0;

            ManagedSprite_GetPositionXY(param0->unk_30, &v1.unk_00, &v1.unk_02);
            param0->unk_D0 = BallParticleEffect_New(&v1);
        }
        param0->unk_08++;
        break;
    case 2:
        BallParticleEffect_Start(param0->unk_D0);
        param0->unk_08++;
        break;
    case 3: {
        if (BallParticleEffect_Update(param0->unk_D0) == 0) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, 0);
            BallParticleEffect_Free(param0->unk_D0);
            param0->unk_08++;
        }
    } break;
    default:
        if (PaletteData_GetSelectedBuffersMask(param0->unk_90.paletteSys) != 0) {
            break;
        }

        BallRotation_SetSubState(param0, 22);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep22(BallRotation *param0)
{
    return 1;
}

static BOOL BallRotation_ThrowStep23(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0: {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
        PaletteData_StartFade(param0->unk_90.paletteSys, 0x4, 1 << v0, -5, 10, 0, 0x0);
    }
        param0->unk_08++;
        break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->unk_90.paletteSys) != 0) {
            break;
        }

        param0->unk_08++;
        break;
    default:
        BallRotation_SetSubState(param0, 24);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep24(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 25);
    return 1;
}

static BOOL BallRotation_ThrowStep25(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        ManagedSprite_SetExplicitOamMode(param0->unk_30, GX_OAM_MODE_XLU);
        param0->unk_08++;
    case 1:
        if (param0->unk_20 > 0) {
            param0->unk_20--;
            param0->unk_21++;
        } else {
            param0->unk_20 = 0;
            param0->unk_21 = 15;
            ManagedSprite_SetDrawFlag(param0->unk_30, 0);
            param0->unk_08++;
        }

        G2_ChangeBlendAlpha(param0->unk_20, param0->unk_21);
        break;
    default:
        BallRotation_SetSubState(param0, 26);
        break;
    }

    return 1;
}

static BOOL BallRotation_ThrowStep26(BallRotation *param0)
{
    BallRotation_SetSubState(param0, 27);
    return 1;
}

static BOOL BallRotation_ThrowStep27(BallRotation *param0)
{
    return 0;
}

static BOOL (*const sBallThrowStepHandlers[])(BallRotation *) = {
    BallRotation_ThrowStep0,
    BallRotation_ThrowStep1,
    BallRotation_ThrowStep2,
    BallRotation_ThrowStep3,
    BallRotation_ThrowStep4,
    BallRotation_ThrowStep5,
    BallRotation_ThrowStep6,
    BallRotation_ThrowStep7,
    BallRotation_ThrowStep8,
    BallRotation_ThrowStep9,
    BallRotation_ThrowStep10,
    BallRotation_ThrowStep11,
    BallRotation_ThrowStep12,
    BallRotation_ThrowStep13,
    BallRotation_ThrowStep14,
    BallRotation_ThrowStep15,
    BallRotation_ThrowStep16,
    BallRotation_ThrowStep17,
    BallRotation_ThrowStep18,
    BallRotation_ThrowStep19,
    BallRotation_ThrowStep20,
    BallRotation_ThrowStep21,
    BallRotation_ThrowStep22,
    BallRotation_ThrowStep23,
    BallRotation_ThrowStep24,
    BallRotation_ThrowStep25,
    BallRotation_ThrowStep26,
    BallRotation_ThrowStep27
};

static BOOL BallRotation_ModeThrow(BallRotation *param0)
{
    BOOL v0 = sBallThrowStepHandlers[param0->unk_14](param0);
    return v0;
}

static BOOL BallRotation_ModeSendOut(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        XYTransformContext_InitParabolic(&param0->unk_48[0], &param0->unk_48[1], param0->unk_B8.unk_00, param0->unk_B8.unk_04, param0->unk_B8.unk_02, param0->unk_B8.unk_06, param0->unk_B8.unk_08, param0->unk_B8.unk_10 * FX32_ONE);

        param0->unk_B8.unk_0C = 0;
        param0->unk_08++;
        param0->unk_D4 = NULL;

        {
            int v0;

            if (BallThrow_TypeRotates(param0->unk_90.type) == 1) {
                v0 = (LCRNG_Next() % 20) + 10;

                ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000 * v0);
            }
        }
        break;
    case 1:
        if (BallThrow_TypeRotates(param0->unk_90.type) == 1) {
            ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000);

            if (param0->unk_B8.unk_0C > ((param0->unk_B8.unk_08 / 2) + 10)) {
                ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000);
            }

            if (BallThrow_TypeFades(param0->unk_90.type) == 1) {
                if (param0->unk_B8.unk_0C == ((param0->unk_B8.unk_08 / 2) + 10)) {
                    int v1;

                    v1 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
                    param0->unk_D4 = PaletteFadeContext_New(param0->unk_90.paletteSys, param0->unk_90.heapID, 2, v1 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
                }
            }
        }

        param0->unk_B8.unk_0C++;

        if ((param0->unk_90.type >= 6) && (param0->unk_90.type <= 8)) {
            if ((param0->unk_B8.unk_0C > (param0->unk_B8.unk_08 / 2)) && (param0->unk_B8.unk_0C < ((param0->unk_B8.unk_08 / 2) + 5))) {
                break;
            }
        }

        if (XYTransformContext_UpdateAndApplyParabolic(&param0->unk_48[0], &param0->unk_48[1], param0->unk_30) == 0) {
            BallRotation_SetZRotation(param0, 0);
            param0->unk_08++;
        }
        break;
    case 2:
        if ((BallThrow_TypeFades(param0->unk_90.type) == 1) && (param0->unk_D4 != NULL)) {
            if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(param0->unk_D4);
            param0->unk_28 = 1;

            return 0;
        } else {
            if (param0->unk_90.type >= 15) {
                param0->unk_28 = 1;
                return 0;
            }

            if (param0->unk_90.ballID == (0xFF + 18)) {
                Sound_PlayPannedEffect(SEQ_SE_DP_W202B_sseq, 117);
            }

            param0->unk_08++;
        }
        break;
    case 3:
        ManagedSprite_SetAnim(param0->unk_30, 1);
        BallRotation_SetFrameTicking(param0, 1);
        param0->unk_B8.unk_0C = 0;
        param0->unk_08++;
        break;
    default:
        if (param0->unk_B8.unk_0C == 5) {
            {
                int v2;

                if ((param0->unk_90.type != 12) && (param0->unk_90.type != 13)) {
                    v2 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
                    param0->unk_D4 = PaletteFadeContext_New(param0->unk_90.paletteSys, param0->unk_90.heapID, 2, v2 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
                }
            }
            param0->unk_28 = 1;
        }

        if ((++param0->unk_B8.unk_0C) <= 15) {
            break;
        }

        if ((param0->unk_90.type != 12) && (param0->unk_90.type != 13)) {
            if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(param0->unk_D4);
        }

        return 0;
    }

    return 1;
}

static BOOL BallRotation_ModeSendOutQuick(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        XYTransformContext_InitParabolic(&param0->unk_48[0], &param0->unk_48[1], param0->unk_B8.unk_00, param0->unk_B8.unk_04, param0->unk_B8.unk_02, param0->unk_B8.unk_06, param0->unk_B8.unk_08, param0->unk_B8.unk_10 * FX32_ONE);

        param0->unk_B8.unk_0C = 0;
        param0->unk_08++;
        param0->unk_D4 = NULL;

        {
            int v0;

            if (BallThrow_TypeRotates(param0->unk_90.type) == 1) {
                v0 = (LCRNG_Next() % 20) + 10;

                ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000 * v0);
            }
        }
        break;
    case 1:
        if (BallThrow_TypeRotates(param0->unk_90.type) == 1) {
            ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000);

            if (param0->unk_B8.unk_0C > ((param0->unk_B8.unk_08 / 2) + 10)) {
                ManagedSprite_OffsetAffineZRotation(param0->unk_30, 0x2000);
            }

            if (BallThrow_TypeFades(param0->unk_90.type) == 1) {
                if (param0->unk_B8.unk_0C == ((param0->unk_B8.unk_08 / 2) + 10)) {
                    int v1;

                    v1 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
                    param0->unk_D4 = PaletteFadeContext_New(param0->unk_90.paletteSys, param0->unk_90.heapID, 2, v1 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
                }
            }
        }

        param0->unk_B8.unk_0C++;

        if ((param0->unk_90.type >= 6) && (param0->unk_90.type <= 8)) {
            if ((param0->unk_B8.unk_0C > (param0->unk_B8.unk_08 / 2)) && (param0->unk_B8.unk_0C < ((param0->unk_B8.unk_08 / 2) + 5))) {
                break;
            }
        }

        if (XYTransformContext_UpdateAndApplyParabolic(&param0->unk_48[0], &param0->unk_48[1], param0->unk_30) == 0) {
            BallRotation_SetZRotation(param0, 0);
            param0->unk_08++;
        }
        break;
    case 2:
        if ((BallThrow_TypeFades(param0->unk_90.type) == 1) && (param0->unk_D4 != NULL)) {
            if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(param0->unk_D4);
            param0->unk_28 = 1;

            return 0;
        } else {
            if (param0->unk_90.type >= 15) {
                param0->unk_28 = 1;

                return 0;
            }

            param0->unk_08++;
        }
        break;
    case 3:
        ManagedSprite_SetAnim(param0->unk_30, 1);
        BallRotation_SetFrameTicking(param0, 0);
        param0->unk_B8.unk_0C = 0;
        param0->unk_08++;
        break;
    default:
        if (param0->unk_B8.unk_0C == 5) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, 2);

            {
                int v2;

                v2 = ManagedSprite_GetExplicitPaletteOffset(param0->unk_30);
                param0->unk_D4 = PaletteFadeContext_New(param0->unk_90.paletteSys, param0->unk_90.heapID, 2, v2 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
            }

            param0->unk_28 = 1;
        }

        if ((++param0->unk_B8.unk_0C) <= 15) {
            break;
        }

        if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
            break;
        }

        PaletteFadeContext_Free(param0->unk_D4);

        return 0;
    }

    return 1;
}

static const int sBallRecallFrameData[][2] = {
    { 0x0, 0x2 },
    { 0x2, 0x2 },
    { 0x2, 0x6 },
    { 0x1, 0x6 },
    { 0x0, 0x6 }
};

static BOOL BallRotation_ModeRecall(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0:
        BallRotation_SetFrameTicking(param0, 0);
        ManagedSprite_SetAnim(param0->unk_30, 1);
        param0->unk_B8.unk_0C++;

        if (param0->unk_B8.unk_0C >= sBallRecallFrameData[0][1]) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, sBallRecallFrameData[0][0]);
            param0->unk_B8.unk_0C = 0;
            param0->unk_08++;
        }
        break;
    case 1:
        param0->unk_B8.unk_0C++;

        if (param0->unk_B8.unk_0C >= sBallRecallFrameData[1][1]) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, sBallRecallFrameData[1][0]);
            param0->unk_B8.unk_0C = 0;
            param0->unk_08++;
        }
        break;
    case 2: {
        BallParticleEffectParams v0;

        v0.unk_04 = param0->unk_90.ballID;
        v0.heapID = param0->unk_90.heapID;
        v0.unk_0C = 0xFF;
        v0.unk_10 = 1;

        ManagedSprite_GetPositionXY(param0->unk_30, &v0.unk_00, &v0.unk_02);
        param0->unk_D0 = BallParticleEffect_New(&v0);
    }
        param0->unk_08++;
        break;
    case 3:
        BallParticleEffect_Start(param0->unk_D0);
        param0->unk_08++;
        break;
    case 4:
        param0->unk_B8.unk_0C++;

        if (param0->unk_B8.unk_0C >= sBallRecallFrameData[2][1]) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, sBallRecallFrameData[2][0]);
            param0->unk_B8.unk_0C = 0;
            param0->unk_08++;
        }
        break;
    case 5:
        param0->unk_B8.unk_0C++;

        if (param0->unk_B8.unk_0C >= sBallRecallFrameData[3][1]) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, sBallRecallFrameData[3][0]);
            param0->unk_B8.unk_0C = 0;
            param0->unk_08++;
        }
        break;
    case 6:
        param0->unk_B8.unk_0C++;

        if (param0->unk_B8.unk_0C >= sBallRecallFrameData[4][1]) {
            ManagedSprite_SetAnimationFrame(param0->unk_30, sBallRecallFrameData[4][0]);
            param0->unk_B8.unk_0C = 0;
            param0->unk_08++;
        }
        break;
    case 7:
        if (BallParticleEffect_Update(param0->unk_D0) == 0) {
            BallParticleEffect_Free(param0->unk_D0);
            param0->unk_08++;
        }
        break;
    default:
        return 0;
        break;
    }

    return 1;
}

static BOOL BallRotation_ModeUnused(BallRotation *param0)
{
    switch (param0->unk_08) {
    case 0: {
        if (param0->unk_10 == 0) {
            ValueLerpContext_Init(&param0->unk_34, -((45 * 0xffff) / 360), +((45 * 0xffff) / 360), 10);
        } else {
            ValueLerpContext_Init(&param0->unk_34, +((45 * 0xffff) / 360), -((45 * 0xffff) / 360), 10);
        }

        param0->unk_10 ^= 1;
    }
        param0->unk_08++;
        break;
    case 1:
        ManagedSprite_SetAffineZRotation(param0->unk_30, param0->unk_34.value);

        if (ValueLerpContext_Update(&param0->unk_34) == 0) {
            if (param0->unk_0C >= 1) {
                param0->unk_08++;
            } else {
                param0->unk_0C++;
                param0->unk_08--;
            }
        }
        break;
    default:
        param0->unk_B8.unk_0C = 0;
        return 0;
        break;
    }

    return 1;
}

static BOOL BallRotation_ModeTrainerSendOut(BallRotation *param0)
{
    if (param0->unk_08 == 0xFF) {
        return 0;
    }

    if (param0->unk_30 != NULL) {
        s16 v0, v1;

        ManagedSprite_GetPositionXY(param0->unk_30, &v0, &v1);

        param0->unk_B8.unk_00 = v0;
        param0->unk_B8.unk_02 = v1;
    }

    return 1;
}

static void BallRotation_UpdateTask(SysTask *param0, void *param1)
{
    BOOL v0;
    BallRotation *v1 = (BallRotation *)param1;

    if (v1->unk_1C == 0) {
        return;
    }

    if (v1->unk_DC > 0) {
        v1->unk_DC--;
        SpriteSystem_DrawSprites(v1->unk_2C);
        return;
    }

    v0 = sBallThrowModeHandlers[v1->unk_90.mode](v1);

    if (v0 == 0) {
        v1->unk_1C = 0;
    }

    if (v1->unk_24 == 1) {
        ManagedSprite_TickFrame(v1->unk_30);
    }

    SpriteSystem_DrawSprites(v1->unk_2C);
}

BallRotation *BallRotation_New(BallThrow *param0)
{
    BallRotation *v0 = NULL;

    v0 = Heap_Alloc(param0->heapID, sizeof(BallRotation));
    MI_CpuClear8(v0, sizeof(BallRotation));

    GF_ASSERT(v0 != NULL);

    v0->unk_90 = (*param0);
    v0->unk_08 = 0;
    v0->unk_10 = 0;
    v0->unk_0C = 0;
    v0->unk_14 = 0;
    v0->unk_18 = 0;
    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_2C = SpriteManager_New(v0->unk_90.cellActorSys);
    v0->unk_DC = 0;
    v0->unk_24 = BallThrow_TypeAnimatesFrame(v0->unk_90.type);
    v0->unk_B8.unk_0C = 0;
    v0->unk_20 = 16;
    v0->unk_21 = 0;

    BattleAnimSystem_SetDefaultAlphaBlending();

    {
        int v1;

        v1 = LCRNG_Next() % 2;

        if (v1) {
            v0->unk_22 = +1;
        } else {
            v0->unk_22 = -1;
        }
    }

    BallRotation_LoadGraphics(v0);
    BallRotation_CreateSprite(v0);
    BallRotation_InitTargetPosition(v0);

    v0->unk_1C = 1;
    v0->unk_28 = 0;
    v0->unk_CC = SysTask_Start(BallRotation_UpdateTask, v0, 1000);

    return v0;
}

BOOL BallRotation_IsActive(BallRotation *param0)
{
    GF_ASSERT(param0 != NULL);
    return param0->unk_1C ? 1 : 0;
}

BOOL BallRotation_IsDone(BallRotation *param0)
{
    GF_ASSERT(param0 != NULL);
    return param0->unk_28 ? 1 : 0;
}

void BallRotation_SetState(BallRotation *param0, int param1)
{
    param0->unk_14 = param1;
}

BOOL BallRotation_IsState(BallRotation *param0, int param1)
{
    return (param0->unk_14 == param1) ? 1 : 0;
}

void BallRotation_Free(BallRotation *param0)
{
    int v0 = param0->unk_90.heapID;

    GF_ASSERT(param0 != NULL);

    SpriteSystem_FreeResourcesAndManager(param0->unk_90.cellActorSys, param0->unk_2C);
    Sprite_DeleteAndFreeResources(param0->unk_30);
    SysTask_Done(param0->unk_CC);
    Heap_Free(param0);
}

void BallRotation_SetMode(BallRotation *param0, int param1)
{
    param0->unk_90.mode = param1;
    param0->unk_08 = 0;
    param0->unk_0C = 0;
    param0->unk_10 = 0;
    param0->unk_1C = 1;

    ManagedSprite_GetPositionXY(param0->unk_30, &param0->unk_B8.unk_00, &param0->unk_B8.unk_02);
}

int BallRotation_GetMode(BallRotation *param0)
{
    GF_ASSERT(param0 != NULL);

    return param0->unk_90.mode;
}

static void BallRotation_InitTargetPosition(BallRotation *param0)
{
    ManagedSprite_GetPositionXY(param0->unk_30, &param0->unk_B8.unk_00, &param0->unk_B8.unk_02);

    switch (param0->unk_90.type) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        ManagedSprite_GetPositionXY(param0->unk_30, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 0;
        param0->unk_B8.unk_08 = 12;
        return;
    case 6:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 7:
        ManagedSprite_GetPositionXY(param0->unk_30, &param0->unk_B8.unk_00, &param0->unk_B8.unk_02);
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 4, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 8:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 2, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 9:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 1, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 10:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 3, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 11:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 5, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 48;
        param0->unk_B8.unk_06 += 32;
        break;
    case 12:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 1, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 16;
        param0->unk_B8.unk_06 += 16;
        param0->unk_B8.unk_08 = 12;
        return;
    case 13:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 1, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 32;
        param0->unk_B8.unk_04 -= 20;
        param0->unk_B8.unk_06 += 38;
        param0->unk_B8.unk_08 = 16;
        return;
    case 14:
        param0->unk_B8.unk_04 = 128;
        param0->unk_B8.unk_06 = (96 - 32);
        param0->unk_B8.unk_10 = 32;
        param0->unk_B8.unk_06 += 32;
        break;
    case 15:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 1, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 64;
        param0->unk_B8.unk_06 += 8;
        param0->unk_B8.unk_08 = 16;
        return;
    case 16:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 3, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 64;
        param0->unk_B8.unk_06 += 8;
        param0->unk_B8.unk_08 = 16;
        return;
    case 17:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 5, &param0->unk_B8.unk_04, &param0->unk_B8.unk_06);
        param0->unk_B8.unk_10 = 64;
        param0->unk_B8.unk_06 += 8;
        param0->unk_B8.unk_08 = 16;
        return;
    default:
        break;
    }

    param0->unk_B8.unk_08 = 20;
}

static void BallRotation_GetStartPosition(BallRotation *param0, s16 *param1, s16 *param2)
{
    switch (param0->unk_90.type) {
    case 0:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        (*param2) += (32 + 8);
        break;
    case 1:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 1, param1, param2);
        (*param2) += 38;
        break;
    case 2:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 2, param1, param2);
        (*param2) += (32 + 8);
        break;
    case 4:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 4, param1, param2);
        (*param2) += (32 + 8);
        break;
    case 3:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 3, param1, param2);
        (*param2) += 38;
        break;
    case 5:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(1, 5, param1, param2);
        (*param2) += 38;
        break;
    case 6:
        *param1 = 10;
        *param2 = 100;
        break;
    case 7:
        *param1 = 10;
        *param2 = 100;
        break;
    case 8:
        *param1 = 10;
        *param2 = 100;
        break;
    case 9:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        break;
    case 10:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        break;
    case 11:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        break;
    case 12:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        break;
    case 13:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(0, 0, param1, param2);
        break;
    case 14:
        *param1 = 230;
        *param2 = 32;
        break;
    case 15:
    case 16:
    case 17:
        *param1 = -30;
        *param2 = 160;
        break;
    default:
        break;
    }
}

static void BallRotation_LoadGraphics(BallRotation *param0)
{
    int v0;
    int v1;
    int v2;
    int v3;

    SpriteSystem_InitSprites(param0->unk_90.cellActorSys, param0->unk_2C, 10);

    if (param0->unk_90.surface == 0) {
        SetSubScreenViewRect(SpriteSystem_GetRenderer(param0->unk_90.cellActorSys), 0, (192 + 80) << FX32_SHIFT);
    }

    {
        int v4;
        SpriteResourceCapacities v5;

        for (v4 = 0; v4 < 6; v4++) {
            v5.asArray[v4] = 10;
        }

        v5.asArray[4] = 0;
        v5.asArray[5] = 0;

        SpriteSystem_InitManagerWithCapacities(param0->unk_90.cellActorSys, param0->unk_2C, &v5);
    }

    v0 = BallThrow_GetGraphics(param0->unk_90.ballID, 0);
    v1 = BallThrow_GetGraphics(param0->unk_90.ballID, 1);
    v2 = BallThrow_GetGraphics(param0->unk_90.ballID, 2);
    v3 = BallThrow_GetGraphics(param0->unk_90.ballID, 3);

    {
        NARC *v6;

        v6 = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__PL_BATT_OBJ, param0->unk_90.heapID);

        SpriteSystem_LoadCharResObjFromOpenNarc(param0->unk_90.cellActorSys, param0->unk_2C, v6, v0, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, param0->unk_90.target + 6000);
        SpriteSystem_LoadPaletteBufferFromOpenNarc(param0->unk_90.paletteSys, 2, param0->unk_90.cellActorSys, param0->unk_2C, v6, v1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, param0->unk_90.target + 6000);
        SpriteSystem_LoadCellResObjFromOpenNarc(param0->unk_90.cellActorSys, param0->unk_2C, v6, v2, TRUE, param0->unk_90.target + 6000);
        SpriteSystem_LoadAnimResObjFromOpenNarc(param0->unk_90.cellActorSys, param0->unk_2C, v6, v3, TRUE, param0->unk_90.target + 6000);
        NARC_dtor(v6);
    }
}

static void BallRotation_CreateSprite(BallRotation *param0)
{
    int v0;
    SpriteTemplate v1;
    int v2;

    BallRotation_GetStartPosition(param0, &v1.x, &v1.y);

    v1.z = 0;
    v1.animIdx = 0;
    v1.priority = 0;
    v1.plttIdx = 0;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    v1.bgPriority = param0->unk_90.bgPrio;
    v1.vramTransfer = FALSE;

    for (v0 = 0; v0 < 6; v0++) {
        v1.resources[v0] = param0->unk_90.target + 6000;
    }

    param0->unk_30 = SpriteSystem_NewSprite(param0->unk_90.cellActorSys, param0->unk_2C, &v1);

    ManagedSprite_SetDrawFlag(param0->unk_30, TRUE);
    ManagedSprite_SetAffineOverwriteMode(param0->unk_30, AFFINE_OVERWRITE_MODE_DOUBLE);
    ManagedSprite_SetAnimationFrame(param0->unk_30, 0);
    ManagedSprite_SetAnim(param0->unk_30, 0);
    ManagedSprite_TickFrame(param0->unk_30);

    BattleAnimSystem_SetDefaultAlphaBlending();
}

void BallRotation_SetDrawFlag(BallRotation *param0, int param1)
{
    ManagedSprite_SetDrawFlag(param0->unk_30, param1);
}

void BallRotation_SetPosition(BallRotation *param0, s16 param1, s16 param2)
{
    ManagedSprite_SetPositionXY(param0->unk_30, param1, param2);
}

void BallRotation_SetZRotation(BallRotation *param0, u16 param1)
{
    ManagedSprite_SetAffineZRotation(param0->unk_30, param1);
}

void BallRotation_SetFrameTicking(BallRotation *param0, BOOL param1)
{
    param0->unk_24 = param1;
}

void BallRotation_SetPriority(BallRotation *param0, int param1)
{
    ManagedSprite_SetPriority(param0->unk_30, param1);
}

void BallRotation_SetExplicitPriority(BallRotation *param0, int param1)
{
    ManagedSprite_SetExplicitPriority(param0->unk_30, param1);
}

void BallRotation_SetDelay(BallRotation *param0, int param1)
{
    param0->unk_DC = param1;
}
