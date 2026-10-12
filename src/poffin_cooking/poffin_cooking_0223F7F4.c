#include "poffin_cooking/poffin_cooking_0223F7F4.h"

#include <nitro.h>
#include <string.h>

#include "poffin_cooking/struct_poffin_cooking_berry_item.h"
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
#include "poffin_cooking/struct_poffin_cooking_result.h"

#include "berry_data.h"
#include "heap.h"
#include "int_distance.h"
#include "math_util.h"
#include "poffin.h"
#include "system.h"

s32 poffin_cooking_0223F7F4(int param0, int param1, int param2, int param3, int param4, int param5)
{
    int v0;
    int v1;
    s32 v2;
    s32 v3;

    param0 -= param4;
    param1 -= param5;
    param2 -= param4;
    param3 -= param5;

    v3 = ApproximateArcLength(param2, param3, param0, param1, 0);
    v3 = ((v3) * 160);

    return v3;
}

void poffin_cooking_0223F820(PoffinCookingTouchTracker *param0)
{
    memset(param0, 0, sizeof(PoffinCookingTouchTracker));

    param0->x = 128;
    param0->y = 96;
    param0->prevX = 128;
    param0->prevY = 96;
}

void poffin_cooking_0223F83C(PoffinCookingTouchTracker *param0)
{
    s32 v0;

    if (gSystem.touchHeld) {
        param0->x = gSystem.touchX;
        param0->y = gSystem.touchY;

        if (param0->held == 0) {
            param0->prevX = param0->x;
            param0->prevY = param0->y;
        }
    }

    param0->delta = poffin_cooking_0223F7F4(param0->x, param0->y, param0->prevX, param0->prevY, 128, 96);
    param0->prevX = param0->x;
    param0->prevY = param0->y;
    param0->held = gSystem.touchHeld;
}

void poffin_cooking_0223F88C(PoffinCookingTouchInput *param0, PoffinCookingTouchTracker *param1)
{
    param0->x = param1->x;
    param0->y = param1->y;

    if (param1->delta < 0) {
        param0->distance = (-param1->delta);
        param0->direction = 1;
    } else {
        param0->distance = param1->delta;
        param0->direction = 0;
    }
}

static const u8 Unk_poffin_cooking_02240590[3] = {
    8,
    7,
    7,
};

static const u16 Unk_poffin_cooking_0224059C[3] = {
    64,
    72,
    80,
};

static u32 poffin_cooking_0223F8AC(PoffinCookingStirState *param0, int param1, int param2)
{
    fx32 v0;
    u32 v1;
    u32 v2;
    u32 v3 = CalcDistance2D(
        param1, param2, 128, 96);

    if (param0->speed >= 0) {
        v1 = param0->speed;
    } else {
        v1 = -param0->speed;
    }

    v0 = poffin_cooking_0223FB68(v1, param0->stirLevel);
    v2 = FX_Mul(v0, 64 * FX32_ONE) >> FX32_SHIFT;
    v2 += 8;

    if (v3 < 16) {
        return 1;
    } else if (v3 > v2) {
        return 2;
    }

    return 0;
}

u16 poffin_cooking_0223F900(PoffinCookingStirState *param0, const PoffinCookingSession *param1, u32 param2, u32 param3)
{
    int v0;
    s32 v1;
    s32 v2;
    int v3;
    fx32 v4;
    s32 v5;
    u16 v6;
    u32 v7;

    param0->onTrack = 1;
    v1 = 0;

    for (v0 = 0; v0 < param2; v0++) {
        v3 = param1->playerNetIDs[v0];
        v7 = poffin_cooking_0223F8AC(param0, param1->participants[v3].touchInput.x, param1->participants[v3].touchInput.y);

        switch (v7) {
        case 0:
            v6 = param1->participants[v3].touchInput.distance;
            break;
        case 1:
            v6 = param1->participants[v3].touchInput.distance / 2;
            param0->onTrack = 0;
            break;
        case 2:
            v6 = 0;
            param0->onTrack = 0;
            break;
        }

        if (param1->participants[v3].touchInput.direction == 0) {
            v1 += v6;
        } else {
            v1 -= v6;
        }
    }

    v2 = param2;
    v1 = v1 / v2;
    v4 = FX_Div(Unk_poffin_cooking_02240590[param0->stirLevel] * FX32_ONE, 204 * FX32_ONE);
    v1 = FX_Mul(v1 * FX32_ONE, v4) >> FX32_SHIFT;

    param0->speed += v1;

    if (param0->speed > 0) {
        param0->speed -= Unk_poffin_cooking_0224059C[param0->stirLevel];

        if (param0->speed < 0) {
            param0->speed = 0;
        }
    } else if (param0->speed < 0) {
        param0->speed += Unk_poffin_cooking_0224059C[param0->stirLevel];

        if (param0->speed > 0) {
            param0->speed = 0;
        }
    }

    if (param0->speed > 3640) {
        param0->speed = 3640;
    } else if (param0->speed < -3640) {
        param0->speed = -3640;
    }

    v5 = param0->angle;
    param0->angle += CalcRadialAngle(68, ((param0->speed) / 160));

    if (((param3 == 0) && (param0->speed >= 0)) || ((param3 == 1) && (param0->speed < 0))) {
        if (param3 == 0) {
            if ((v5 & 0xffff) > (param0->angle & 0xffff)) {
                param0->revolutions++;
            }
        } else {
            if ((v5 & 0xffff) < (param0->angle & 0xffff)) {
                param0->revolutions++;
            }
        }
    }

    return param0->angle & 0xffff;
}

u16 poffin_cooking_0223FA84(const PoffinCookingStirState *param0)
{
    return param0->angle & 0xffff;
}

u32 poffin_cooking_0223FA8C(const PoffinCookingStirState *param0)
{
    return param0->revolutions;
}

void poffin_cooking_0223FA90(PoffinCookingStirState *param0, int param1)
{
    GF_ASSERT(param1 < 3);
    param0->stirLevel = param1;
    param0->revolutions = 0;
}

s32 poffin_cooking_0223FAA8(const PoffinCookingStirState *param0)
{
    return param0->speed;
}

void poffin_cooking_0223FAAC(PoffinCookingStirStats *param0, s32 param1, int param2)
{
    param0->greatStirTriggered = 0;
    param0->messageType = 0;

    if (poffin_cooking_0223FB30(param1, param2)) {
        param0->greatStirTimer++;

        if (param0->greatStirTimer >= 30) {
            if (param0->greatStirCount < 9999) {
                param0->greatStirCount++;
            }

            param0->greatStirTriggered = 1;
            param0->greatStirTimer = 0;
        }

        param0->messageToggle = 0;
    } else if (poffin_cooking_0223FB50(param1, param2)) {
        param0->goodStirTimer++;

        if (param0->goodStirTimer >= (30 * 3)) {
            param0->goodStirTimer = 0;

            if (param0->messageToggle == 0) {
                param0->messageType = 2;
                param0->messageToggle = 1;
            } else {
                param0->messageType = 1;

                if (param0->goodStirCount < 9999) {
                    param0->goodStirCount++;
                }
            }
        }
    } else {
        param0->messageToggle = 0;
    }
}

BOOL poffin_cooking_0223FB30(s32 param0, int param1)
{
    int v0 = MATH_IAbs(param0);

    if (param1 == 2) {
        return 0;
    }

    if (v0 >= 3640) {
        return 1;
    }

    return 0;
}

BOOL poffin_cooking_0223FB50(s32 param0, int param1)
{
    int v0 = MATH_IAbs(param0);

    if (v0 <= 910) {
        return 1;
    }

    return 0;
}

fx32 poffin_cooking_0223FB68(u16 param0, int param1)
{
    fx32 v0;
    fx32 v1;
    s32 v2 = param0 - 910;

    if (v2 < 0) {
        v2 = 0;
    }

    v0 = FX_Mul((FX32_CONST(0.25f)), v2 * FX32_ONE);
    v1 = FX_Div(v0, (3640 - 910) * FX32_ONE);

    return v1 + FX32_ONE;
}

void poffin_cooking_0223FBA4(PoffinCookingCpuInput *param0)
{
    memset(param0, 0, sizeof(PoffinCookingCpuInput));
    param0->skillLevel = 2;
    param0->timer = -1;
}

void poffin_cooking_0223FBBC(PoffinCookingCpuInput *param0, int param1, s32 param2, BOOL param3)
{
    int v0;
    u32 v1;
    u32 v2;
    static u8 v3[3] = {
        { 30 * 5 },
        { 30 * 4 },
        { 30 * 3 },
    };

    param0->changed = 0;

    if ((poffin_cooking_0223FC3C(param0, param2) == 1) || (param3 == 1)) {
        return;
    }

    if (param0->timer < 0) {
        v1 = MTRNG_Next();
        v2 = (v1 % 5);

        if (v2 <= param0->skillLevel) {
            v0 = 1;
            param0->changed = 1;
        } else {
            v0 = 0;
            param0->changed = 1;
        }

        if (v0 == param0->direction) {
            if (param0->direction == 1) {
                if ((param0->skillLevel - 1) >= 0) {
                    param0->skillLevel--;
                }
            } else {
                if ((param0->skillLevel + 1) < 5) {
                    param0->skillLevel++;
                }
            }
        } else {
            param0->direction = v0;
            param0->skillLevel = 2;
        }

        param0->timer = v3[param1] + (v1 % (2 * 30));
    }

    param0->timer--;
}

BOOL poffin_cooking_0223FC3C(const PoffinCookingCpuInput *param0, s32 param1)
{
    if (((param1 < 0) && (param0->direction == 0)) || ((param1 > 0) && (param0->direction == 1))) {
        return 1;
    }

    return 0;
}

BOOL poffin_cooking_0223FC58(PoffinCookingStirLevel *param0, PoffinCookingStirState *param1)
{
    static const u8 v0[3] = {
        16, 16, 16
    };
    int v1 = 31;
    int v2 = 31;
    int v3 = poffin_cooking_0223FA8C(param1);
    int v4;
    int v5;

    if (param0->level >= 3) {
        return 1;
    }

    if ((param0->timer == (20 * 30)) || (v3 >= v0[param0->level])) {
        param0->level++;
        param0->timer = 0;

        v3 = 0;

        if (param0->level >= 3) {
            return 1;
        }

        poffin_cooking_0223FA90(param1, param0->level);
    }

    v4 = ((20 * 30) - param0->timer);

    if (v4 <= (2 * 30)) {
        v1 = 31 * v4;
        v1 = v1 / (2 * 30);
    }

    v5 = (v0[param0->level] - v3);

    if (v5 <= 5) {
        v2 = 31 * v5;
        v2 = v2 / 5;
    }

    if (v1 < v2) {
        param0->alpha = v1;
    } else {
        param0->alpha = v2;
    }

    param0->timer++;

    return 0;
}

void poffin_cooking_0223FCE8(PoffinCookingSynchroState *param0, const PoffinCookingSession *param1, int param2, s32 param3, int param4, BOOL param5, BOOL param6)
{
    u32 v0;
    const PoffinCookingBlendState *v1 = &param1->participants[0].blendState;
    const PoffinCookingTouchInput *v2;
    int v3;
    int v4;

    param0->triggered = 0;

    if ((poffin_cooking_0223FB50(param3, param4) == 1) || (poffin_cooking_0223FB30(param3, param4) == 1) || (param5 == 0)) {
        param0->readyCount = 0;
        param0->synchronized = 0;
        return;
    }

    if (param2 <= 1) {
        param0->readyCount = 0;
        param0->synchronized = 0;
        return;
    }

    if (param6 == 1) {
        return;
    }

    for (v3 = 0; v3 < param2; v3++) {
        v4 = param1->playerNetIDs[v3];
        v2 = &param1->participants[v4].touchInput;

        if (v2->distance <= 600) {
            return;
        }
    }

    for (v3 = 1; v3 < param2; v3++) {
        v4 = param1->playerNetIDs[v3];
        v0 = CalcDistance2D(v1->posX[0], v1->posY[0], v1->posX[v4], v1->posY[v4]);

        if (v0 > 32) {
            param0->readyCount = 0;
            param0->synchronized = 0;
            return;
        }
    }

    if (param0->readyCount < 4) {
        param0->readyCount++;
    } else {
        if ((param0->timer % 1) == 0) {
            param0->triggered = 1;
        }

        param0->timer++;
        param0->synchronized = 1;
    }
}

void poffin_cooking_0223FDB0(PoffinCookingSimulation *param0)
{
    memset(param0, 0, sizeof(PoffinCookingSimulation));
    poffin_cooking_0223FBA4(&param0->cpuInput);
    param0->stirLevel.alpha = 31;
    poffin_cooking_0223FBBC(&param0->cpuInput, 0, 0, 0);
}

BOOL poffin_cooking_0223FDD8(PoffinCookingSimulation *param0, const PoffinCookingSession *param1, u32 param2)
{
    s32 v0;
    BOOL v1 = poffin_cooking_0223FC58(&param0->stirLevel, &param0->stirState);

    if (v1 == 1) {
        return 1;
    }

    poffin_cooking_0223F900(&param0->stirState, param1, param2, param0->cpuInput.direction);

    v0 = poffin_cooking_0223FAA8(&param0->stirState);

    poffin_cooking_0223FAAC(&param0->stirStats, v0, param0->stirLevel.level);
    poffin_cooking_0223FCE8(&param0->synchroState, param1, param2, v0, param0->stirLevel.level, param0->stirState.onTrack, poffin_cooking_0223FC3C(&param0->cpuInput, v0));
    poffin_cooking_0223FBBC(&param0->cpuInput, param0->stirLevel.level, v0, param0->synchroState.synchronized);

    return 0;
}

void poffin_cooking_0223FE50(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2)
{
    int v0;
    PoffinCookingBlendState *v1 = &param1->localParticipant.blendState;
    s32 v2;

    for (v0 = 0; v0 < 4; v0++) {
        v1->posX[v0] = param1->participants[v0].touchInput.x;
        v1->posY[v0] = param1->participants[v0].touchInput.y;
    }

    v2 = poffin_cooking_0223FAA8(&param0->stirState);

    if (v2 >= 0) {
        v1->stirSpeed = v2 & 0xffff;
        v1->direction = 0;
    } else {
        v1->stirSpeed = (-v2) & 0xffff;
        v1->direction = 1;
    }

    v1->angle = poffin_cooking_0223FA84(&param0->stirState);
    v1->stirChain = param0->stirStats.messageType;
    v1->perfectStir = param0->stirStats.greatStirTriggered;
    v1->arrowSide = param0->cpuInput.direction;
    v1->releaseFlag = param0->cpuInput.changed;

    if (param0->stirLevel.level < 3) {
        v1->stirLevel = param0->stirLevel.level;
    } else {
        v1->stirLevel = 2;
    }

    v1->alpha = param0->stirLevel.alpha;
    v1->sparkleTrigger = param0->synchroState.triggered;
}

void poffin_cooking_0223FEC0(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2)
{
    int v0;
    PoffinCookingBlendState *v1 = &param1->localParticipant.blendState;
    s32 v2;

    for (v0 = 0; v0 < 4; v0++) {
        v1->posX[v0] = param1->participants[v0].touchInput.x;
        v1->posY[v0] = param1->participants[v0].touchInput.y;
    }

    v2 = poffin_cooking_0223FAA8(&param0->stirState);

    if (v2 >= 0) {
        v1->stirSpeed = v2 & 0xffff;
        v1->direction = 0;
    } else {
        v1->stirSpeed = (-v2) & 0xffff;
        v1->direction = 1;
    }

    v1->angle = poffin_cooking_0223FA84(&param0->stirState);

    if (param0->stirStats.messageType != 0) {
        v1->stirChain = param0->stirStats.messageType;
    }

    if (v1->perfectStir == 0) {
        v1->perfectStir = param0->stirStats.greatStirTriggered;
    }

    if (param0->cpuInput.changed == 1) {
        v1->arrowSide = param0->cpuInput.direction;
        v1->releaseFlag = param0->cpuInput.changed;
    }

    if (param0->stirLevel.level < 3) {
        v1->stirLevel = param0->stirLevel.level;
    } else {
        v1->stirLevel = 2;
    }

    v1->alpha = param0->stirLevel.alpha;

    if (v1->sparkleTrigger == 0) {
        v1->sparkleTrigger = param0->synchroState.triggered;
    }
}

void poffin_cooking_0223FF44(PoffinCookingSimulation *param0, PoffinCookingBlendState *param1, int param2)
{
    int v0;
    s32 v1;

    for (v0 = 0; v0 < 4; v0++) {
        param1->posX[v0] = 128;
        param1->posY[v0] = 96;
    }

    v1 = poffin_cooking_0223FAA8(&param0->stirState);

    if (v1 >= 0) {
        param1->stirSpeed = v1 & 0xffff;
        param1->direction = 0;
    } else {
        param1->stirSpeed = (-v1) & 0xffff;
        param1->direction = 1;
    }

    param1->angle = poffin_cooking_0223FA84(&param0->stirState);
    param1->stirChain = param0->stirStats.messageType;
    param1->perfectStir = param0->stirStats.greatStirTriggered;
    param1->arrowSide = param0->cpuInput.direction;
    param1->releaseFlag = param0->cpuInput.changed;
    param1->stirLevel = param0->stirLevel.level;
    param1->alpha = param0->stirLevel.alpha;
    param1->sparkleTrigger = param0->synchroState.triggered;
}

void poffin_cooking_0223FFA0(PoffinCookingSimulation *param0)
{
    param0->frameCount++;
}

static const u8 Unk_poffin_cooking_02240598[4] = {
    0,
    1,
    5,
    10
};

static int poffin_cooking_0223FFA8(u32 param0, u32 param1)
{
    int v0 = ((param0 / 6) * Unk_poffin_cooking_02240598[param1 - 1]) / 10;

    if (v0 > 9999) {
        v0 = 9999;
    }

    return v0;
}

void poffin_cooking_0223FFD4(PoffinCookingSimulation *param0, Poffin *param1, const PoffinCookingSession *param2, u32 param3, u32 param4)
{
    BerryData *v0;
    int v1, v2;
    const PoffinCookingBerryItem *v3 = param2->berryPacket.berries;
    s32 v4[5] = { 0, 0, 0, 0, 0 };
    s32 v5 = 0;
    s32 v6[5];
    s32 v7;
    int v8;
    int v9;
    BOOL v10;
    int v11;
    int v12;
    int v13;
    int v14;
    int v15;
    u8 v16[5];
    int v17, v18;

    v9 = 0;

    for (v1 = 0; v1 < param3; v1++) {
        v17 = param2->playerNetIDs[v1];
        v0 = BerryData_LoadDataByItemID(v3[v17].itemID, param4);

        v8 = 0;

        for (v2 = 0; v2 < param3; v2++) {
            v18 = param2->playerNetIDs[v2];

            if (v3[v17].itemID == v3[v18].itemID) {
                v8++;
            }
        }

        if (v8 > v9) {
            v9 = v8;
        }

        for (v2 = 0; v2 < 5; v2++) {
            v4[v2] += BerryData_GetAttribute(v0, 5 + v2);
        }

        v5 += BerryData_GetAttribute(v0, 10);

        Heap_Free(v0);
    }

    if ((v9 >= 2) && (param3 > 1)) {
        v10 = 1;
    } else {
        v10 = 0;
    }

    v7 = (v5 / param3) - param3;
    v13 = 0;

    for (v1 = 0; v1 < 5; v1++) {
        v11 = (v1 + 1) % 5;
        v6[v1] = v4[v1] - v4[v11];

        if (v6[v1] < 0) {
            v13++;
        }
    }

    for (v1 = 0; v1 < 5; v1++) {
        v6[v1] -= v13;
    }

    if (v13 >= 4) {
        v10 = 1;
    }

    v14 = (((20 * 30) * 3) * 1000) / param0->frameCount;

    if ((v14 % 10) >= 5) {
        v14 += 10;
    }

    v14 /= 10;

    for (v1 = 0; v1 < 5; v1++) {
        v15 = v6[v1] * v14;

        if ((v15 % 100) >= 50) {
            v15 += 100;
        }

        v15 = v15 / 100;
        v6[v1] = v15 - (param0->stirStats.goodStirCount + param0->stirStats.greatStirCount);

        if (v6[v1] < 0) {
            v6[v1] = 0;
        }
    }

    if (param3 > 1) {
        v12 = poffin_cooking_0223FFA8(param0->synchroState.timer, param3);

        if (v12 > 10) {
            v12 = 10;
        }

        v7 -= v12;
    }

    if (v7 < 15) {
        v7 = 15;
    }

    for (v1 = 0; v1 < 5; v1++) {
        v16[v1] = v6[v1];
    }

    param0->poffinValue = Poffin_MakePoffin(param1, v16, v7, v10);
    param0->poffinLevel = Poffin_CalcLevel(param1);
}

void poffin_cooking_022401AC(PoffinCookingSimulation *param0, PoffinCookingSession *param1, int param2)
{
    PoffinCookingResult *v0 = &param1->result;
    int v1;

    v0->greatStirCount = param0->stirStats.greatStirCount;
    v0->goodStirCount = param0->stirStats.goodStirCount;
    v0->smoothness = poffin_cooking_0223FFA8(param0->synchroState.timer, param2);
    v0->poffinSpecies = param0->poffinValue;
    v0->level = param0->poffinLevel;

    v1 = param0->frameCount;
    v0->minutes = v1 / (60 * 30);
    v1 -= v0->minutes * (60 * 30);
    v0->seconds = v1 / 30;
    v1 -= v0->seconds * 30;
    v0->centiseconds = (100 * v1) / 30;
}
