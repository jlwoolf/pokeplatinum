#include "spear_pillar/spear_pillar_object_anim.h"

#include <nitro.h>
#include <string.h>

#include "spear_pillar/struct_spear_pillar_object.h"
#include "spear_pillar/struct_spear_pillar_object_anim_step.h"

#include "easy3d_object.h"

void SpearPillarObject_StartAnim(SpearPillarObject *param0, SpearPillarObjectAnimStep *param1);
void SpearPillarObject_UpdateAnim(SpearPillarObject *param0);
void SpearPillarObject_UpdateMovement(SpearPillarObject *param0);

static const int sSpearPillarObjectAnimFrames[][5] = {
    { 0x1, 0x2, 0x3, 0x2, 0xFF },
    { 0x5, 0x6, 0x7, 0x6, 0xFF },
    { 0x9, 0xA, 0xB, 0xA, 0xFF },
    { 0xD, 0xE, 0xF, 0xE, 0xFF },
    { 0x0, 0x0, 0x0, 0x0, 0xFF },
    { 0x4, 0x4, 0x4, 0x4, 0xFF },
    { 0xA, 0xA, 0xA, 0xA, 0xFF },
    { 0xE, 0xE, 0xE, 0xE, 0xFF },
    { 0x0, 0x0, 0x0, 0x0, 0xFF },
    { 0x0, 0x1, 0x2, 0x3, 0xFF },
    { 0x4, 0x5, 0x6, 0x7, 0xFF },
    { 0x8, 0x9, 0xA, 0xB, 0xFF },
    { 0xC, 0xD, 0xE, 0xF, 0xFF }
};

void SpearPillarObject_StartAnim(SpearPillarObject *param0, SpearPillarObjectAnimStep *param1)
{
    param0->isAnimating = 1;
    param0->animSteps = param1;
    param0->stepIndex = 0;
    param0->framesRemaining = param1[param0->stepIndex].frameCount;
    param0->stepFrameCount = param1[param0->stepIndex].frameCount;
    param0->animID = param1[param0->stepIndex].animID;
}

void SpearPillarObject_UpdateAnim(SpearPillarObject *param0)
{
    int v0;
    int v1;
    int v2;
    fx32 v3;
    fx32 v4 = Easy3DAnim_GetFrame(&param0->anims[0]);
    fx32 v5;

    v0 = v4 >> FX32_SHIFT;
    v0 %= 4;
    v5 = v4 + param0->animSpeed;
    v1 = v5 >> FX32_SHIFT;
    v1 %= 4;
    v2 = sSpearPillarObjectAnimFrames[param0->animID - 1][param0->animFrame];

    if (v2 == 0xFF) {
        return;
    }

    if (v1 != v0) {
        param0->animFrame++;
        v3 = FX32_CONST(v2 * 4);
    } else {
        v3 = v5;
    }

    Easy3DAnim_SetFrame(&param0->anims[0], v3);
}

void SpearPillarObject_UpdateMovement(SpearPillarObject *param0)
{
    int v0;
    SpearPillarObjectAnimStep *v1 = param0->animSteps;

    if ((param0->framesRemaining == 0xFF) || (param0->stepIndex == 0xFF)) {
        return;
    }

    v0 = v1[param0->stepIndex].animID;

    if (v0 == 0) {
        param0->isAnimating = 0;
        param0->stepIndex = 0xFF;
        param0->framesRemaining = 0xFF;
        param0->stepFrameCount = 0xFF;
    } else {
        if (param0->animFrame >= 4) {
            param0->framesRemaining--;
            param0->animFrame = 0;

            if (param0->framesRemaining == 0) {
                param0->stepIndex++;
                param0->animID = v1[param0->stepIndex].animID;
                param0->framesRemaining = v1[param0->stepIndex].frameCount;
                param0->stepFrameCount = v1[param0->stepIndex].frameCount;

                if (param0->animID == 0) {
                    param0->isAnimating = 0;
                    param0->stepIndex = 0xFF;
                    param0->framesRemaining = 0xFF;
                    param0->stepFrameCount = 0xFF;
                }
            }
        } else {
            if ((param0->animFrame == 0) && (param0->framesRemaining == param0->stepFrameCount)) {
                return;
            }

            switch (param0->animID) {
            case 1:
            case 2:
            case 9:
                param0->object.position.z -= v1[param0->stepIndex].moveDelta;
                break;
            case 4:
            case 3:
                param0->object.position.x += v1[param0->stepIndex].moveDelta;
                break;
            }
        }
    }
}
