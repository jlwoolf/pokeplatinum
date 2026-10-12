#include "spear_pillar/spear_pillar_sprite.h"

#include <nitro.h>
#include <string.h>

#include "spear_pillar/struct_spear_pillar_sprite.h"

#include "math_util.h"
#include "sprite_system.h"
#include "sys_task_manager.h"

static BOOL SpearPillarSprite_MoveToward(s16 param0, s16 param1, f32 param2, f32 param3, f32 *param4, f32 *param5, f32 param6, s16 param7);
static BOOL SpearPillarSprite_MoveTowardTarget(SpearPillarSprite *param0, s16 param1, s16 param2, f32 param3, int param4);
static void SpearPillarSprite_StateApproach(SpearPillarSprite *param0);
static void SpearPillarSprite_StateOrbit(SpearPillarSprite *param0);
static void SpearPillarSprite_StateOrbitAround(SpearPillarSprite *param0, int param1, int param2, int param3, int param4);
static void SpearPillarSprite_StateWander(SpearPillarSprite *param0);
static void SpearPillarSprite_StateJitter(SpearPillarSprite *param0);
static void SpearPillarSprite_UpdateScale(SpearPillarSprite *param0);

static void (*const sSpearPillarSpriteStates[])(SpearPillarSprite *) = {
    SpearPillarSprite_StateApproach,
    SpearPillarSprite_StateOrbit,
    SpearPillarSprite_StateWander,
    SpearPillarSprite_StateJitter
};

static BOOL SpearPillarSprite_MoveToward(s16 param0, s16 param1, f32 param2, f32 param3, f32 *param4, f32 *param5, f32 param6, s16 param7)
{
    f32 v0;
    f32 v1;
    Vec2F32 v2;
    Vec2F32 v3;
    Vec2F32 v4;

    v4.x = 0;
    v4.y = 0;

    v3.x = (param0 - param2);
    v3.y = (param1 - param3);

    v2.x = 0;
    v2.y = 0;

    v1 = (v3.x * v3.x) + (v3.y * v3.y);
    v0 = FX_Sqrt(FX_F32_TO_FX32(v1));
    v0 = FX_FX32_TO_F32(v0);

    if ((v0 < param6) || (param7 > v0) || (v0 == 0)) {
        return 0;
    }

    v2.x = (v3.x * param6) / v0;
    v2.y = (v3.y * param6) / v0;

    *param4 = (v2.x + v4.x);
    *param5 = (v2.y + v4.y);

    return 1;
}

static BOOL SpearPillarSprite_MoveTowardTarget(SpearPillarSprite *param0, s16 param1, s16 param2, f32 param3, int param4)
{
    f32 v0;
    f32 v1;
    fx32 v2;
    fx32 v3;
    f32 v4;
    f32 v5;
    BOOL v6;
    fx32 v7, v8;

    ManagedSprite_GetPositionFxXYWithSubscreenOffset(param0->sprite, &v2, &v3, FX32_CONST(192));

    v0 = FX_FX32_TO_F32(v2);
    v1 = FX_FX32_TO_F32(v3);

    v6 = SpearPillarSprite_MoveToward(param1, param2, v0, v1, &v4, &v5, param3, param4);

    if (v6) {
        v7 = FX_F32_TO_FX32(v4);
        v8 = FX_F32_TO_FX32(v5);

        param0->wobbleAngle += 8;
        param0->wobbleAngle %= 360;

        v7 += (CalcSineDegrees_Wraparound(param0->wobbleAngle) * 1);
        v8 += (CalcCosineDegrees_Wraparound(param0->wobbleAngle) * 1);

        ManagedSprite_OffsetPositionFxXY(param0->sprite, v7, v8);
    }

    return v6;
}

static void SpearPillarSprite_StateApproach(SpearPillarSprite *param0)
{
    BOOL v0 = SpearPillarSprite_MoveTowardTarget(param0, 128, 40, 5.0f, 32);
}

static void SpearPillarSprite_StateOrbit(SpearPillarSprite *param0)
{
    fx32 v0, v1;

    param0->orbitAngle += 8;
    param0->orbitAngle %= 360;

    v0 = (128 << FX32_SHIFT) + (CalcSineDegrees_Wraparound(param0->orbitAngle) * 64);
    v1 = (48 << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(param0->orbitAngle) * 24);

    ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, v0, v1, FX32_CONST(192));

    param0->yPos = v1 / FX32_ONE;
}

static void SpearPillarSprite_StateOrbitAround(SpearPillarSprite *param0, int param1, int param2, int param3, int param4)
{
    fx32 v0, v1;

    param0->orbitAngle += 8;
    param0->orbitAngle %= 360;

    v0 = (param1 << FX32_SHIFT) + (CalcSineDegrees_Wraparound(param0->orbitAngle) * param3);
    v1 = (param2 << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(param0->orbitAngle) * param4);

    ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, v0, v1, FX32_CONST(192));
}

static void SpearPillarSprite_StateWander(SpearPillarSprite *param0)
{
    fx32 v0, v1;
    static s16 v2[][2] = {
        { 97, 80 },
        { 87, 106 },
        { 102, 94 },
        { 182, 83 },
        { 129, 116 },
        { 97, 116 },
        { 172, 84 },
        { 187, 99 },
        { 168, 123 },
        { 108, 93 },
    };
    BOOL v3 = SpearPillarSprite_MoveTowardTarget(param0, v2[param0->params[2]][0], v2[param0->params[2]][1], 3.0f, 10);

    if (v3 == 0) {
        param0->params[2]++;
        param0->params[2] %= NELEMS(v2);
        param0->params[2] = LCRNG_Next() % NELEMS(v2);
        param0->state = 3;
    }

    ManagedSprite_GetPositionFxXYWithSubscreenOffset(param0->sprite, &v0, &v1, FX32_CONST(192));

    param0->yPos = (v1 / FX32_ONE);
}

static void SpearPillarSprite_StateJitter(SpearPillarSprite *param0)
{
    fx32 v0, v1;

    param0->wobbleAngle += 8;
    param0->wobbleAngle %= 360;

    if (param0->wobbleAngle < 12) {
        param0->jitterRange++;
        param0->jitterRange %= 3;
        param0->params[0] = (LCRNG_Next() % param0->jitterRange) + 1;
        param0->params[1] = (LCRNG_Next() % param0->jitterRange) + 1;
        param0->state = 2;
    }

    ManagedSprite_GetPositionFxXYWithSubscreenOffset(param0->sprite, &v0, &v1, FX32_CONST(192));

    v0 += (CalcSineDegrees_Wraparound(param0->wobbleAngle) * (3 * param0->params[0]));
    v1 += (CalcCosineDegrees_Wraparound(param0->wobbleAngle) * (3 * param0->params[1]));

    ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, v0, v1, FX32_CONST(192));

    param0->yPos = v1 / FX32_ONE;
}

static void SpearPillarSprite_UpdateScale(SpearPillarSprite *param0)
{
    f32 v0;

    v0 = param0->yPos;
    v0 /= 100.0f;
    v0 = 0.8f - v0;

    if (v0 <= 0.2f) {
        v0 = 0.2f;
    }

    if (v0 >= 0.6f) {
        v0 = 0.6f;
    }

    ManagedSprite_SetAffineScale(param0->sprite, v0, v0);
    ManagedSprite_SetPriority(param0->sprite, param0->yPos);
}

void SpearPillarSprite_Task(SysTask *param0, void *param1)
{
    SpearPillarSprite *v0 = param1;

    sSpearPillarSpriteStates[v0->state](v0);

    SpearPillarSprite_UpdateScale(v0);
    ManagedSprite_TickTwoFrames(v0->sprite);
}

void SpearPillarSprite_ShadowTask(SysTask *param0, void *param1)
{
    SpearPillarSprite *v0 = param1;

    if (v0->state) {
        SpearPillarSprite_StateOrbitAround(v0, 128, 48 - 12, 32, 12);
    } else {
        s16 v1, v2;
        BOOL v3;

        if (v0->targetSprite && v0->followTarget) {
            ManagedSprite_GetPositionXY(v0->targetSprite, &v1, &v2);

            v3 = SpearPillarSprite_MoveTowardTarget(v0, v1, v2, 3.0f, 1);

            {
                f32 v4, v5;

                ManagedSprite_GetAffineScale(v0->sprite, &v4, &v5);

                if (v4 > 0.10f) {
                    v4 = v4 - 0.002f;
                }

                ManagedSprite_SetAffineScale(v0->sprite, v4, v4);
            }
        }
    }

    ManagedSprite_TickTwoFrames(v0->sprite);
}
