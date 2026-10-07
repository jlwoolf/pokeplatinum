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
    param0->unk_160 = 1;
    param0->unk_184 = param1;
    param0->unk_180 = 0;
    param0->unk_178 = param1[param0->unk_180].frameCount;
    param0->unk_17C = param1[param0->unk_180].frameCount;
    param0->unk_158 = param1[param0->unk_180].animID;
}

void SpearPillarObject_UpdateAnim(SpearPillarObject *param0)
{
    int v0;
    int v1;
    int v2;
    fx32 v3;
    fx32 v4 = Easy3DAnim_GetFrame(&param0->unk_88[0]);
    fx32 v5;

    v0 = v4 >> FX32_SHIFT;
    v0 %= 4;
    v5 = v4 + param0->unk_154;
    v1 = v5 >> FX32_SHIFT;
    v1 %= 4;
    v2 = sSpearPillarObjectAnimFrames[param0->unk_158 - 1][param0->unk_15C];

    if (v2 == 0xFF) {
        return;
    }

    if (v1 != v0) {
        param0->unk_15C++;
        v3 = FX32_CONST(v2 * 4);
    } else {
        v3 = v5;
    }

    Easy3DAnim_SetFrame(&param0->unk_88[0], v3);
}

void SpearPillarObject_UpdateMovement(SpearPillarObject *param0)
{
    int v0;
    SpearPillarObjectAnimStep *v1 = param0->unk_184;

    if ((param0->unk_178 == 0xFF) || (param0->unk_180 == 0xFF)) {
        return;
    }

    v0 = v1[param0->unk_180].animID;

    if (v0 == 0) {
        param0->unk_160 = 0;
        param0->unk_180 = 0xFF;
        param0->unk_178 = 0xFF;
        param0->unk_17C = 0xFF;
    } else {
        if (param0->unk_15C >= 4) {
            param0->unk_178--;
            param0->unk_15C = 0;

            if (param0->unk_178 == 0) {
                param0->unk_180++;
                param0->unk_158 = v1[param0->unk_180].animID;
                param0->unk_178 = v1[param0->unk_180].frameCount;
                param0->unk_17C = v1[param0->unk_180].frameCount;

                if (param0->unk_158 == 0) {
                    param0->unk_160 = 0;
                    param0->unk_180 = 0xFF;
                    param0->unk_178 = 0xFF;
                    param0->unk_17C = 0xFF;
                }
            }
        } else {
            if ((param0->unk_15C == 0) && (param0->unk_178 == param0->unk_17C)) {
                return;
            }

            switch (param0->unk_158) {
            case 1:
            case 2:
            case 9:
                param0->unk_00.position.z -= v1[param0->unk_180].moveDelta;
                break;
            case 4:
            case 3:
                param0->unk_00.position.x += v1[param0->unk_180].moveDelta;
                break;
            }
        }
    }
}
