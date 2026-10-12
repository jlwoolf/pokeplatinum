#include "spear_pillar/spear_pillar_common.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_020985E4.h"

#include "spear_pillar/spear_pillar_object_anim.h"
#include "spear_pillar/struct_spear_pillar_context.h"
#include "spear_pillar/struct_spear_pillar_camera_anim.h"
#include "spear_pillar/struct_spear_pillar_object.h"
#include "spear_pillar/struct_spear_pillar.h"

#include "bg_window.h"
#include "camera.h"
#include "easy3d_object.h"
#include "game_options.h"
#include "gx_layers.h"
#include "message.h"
#include "narc.h"
#include "palette.h"
#include "render_window.h"
#include "string_gf.h"
#include "string_template.h"
#include "system.h"
#include "text.h"
#include "trainer_info.h"

int SpearPillar_PrintMessage(SpearPillarContext *param0, SpearPillarTaskArgs *param1, int param2)
{
    int v0;
    MessageLoader *v1;
    String *v2;
    String *v3 = String_Init(511, HEAP_ID_111);
    u8 v4 = 0;

    v1 = param0->messageLoader;
    v2 = MessageLoader_GetNewString(v1, param2);

    if (param2 == 22) {
        String *v5 = TrainerInfo_NameNewString(param1->trainerInfo, 111);
        StringTemplate *v6 = StringTemplate_Default(HEAP_ID_111);

        StringTemplate_SetString(v6, 0, v5, 0, 1, GAME_LANGUAGE);
        StringTemplate_Format(v6, v3, v2);
        String_Free(v5);
        StringTemplate_Free(v6);
    } else {
        String_Copy(v3, v2);
    }

    v4 = Options_TextFrameDelay(param1->options);
    Window_FillTilemap(&param0->window, 0xFF);

    v0 = Text_AddPrinterWithParams(&param0->window, FONT_MESSAGE, v3, 0, 0, v4, NULL);
    Window_CopyToVRAM(&param0->window);

    Window_DrawMessageBoxWithScrollCursor(&param0->window, 0, 500, 15);
    String_Free(v2);
    String_Free(v3);

    param0->textPrinter = v0;

    return v0;
}

void SpearPillar_EraseMessage(SpearPillarContext *param0)
{
    Window_EraseMessageBox(&param0->window, 1);
    Window_ClearAndCopyToVRAM(&param0->window);
}

void SpearPillar_SetupLighting(SpearPillarContext *param0)
{
    VecFx32 v0 = { 0, -FX32_ONE, -FX32_ONE };
    VecFx32 v1 = { -2043, -3548, 110 };

    VEC_Normalize(&v0, &v0);
    NNS_G3dGlbLightVector(0, v0.x, v0.y, v0.z);
    NNS_G3dGlbLightColor(0, GX_RGB(31, 31, 31));

    VEC_Normalize(&v1, &v1);
    NNS_G3dGlbLightVector(1, v1.x, v1.y, v1.z);
    NNS_G3dGlbLightColor(1, GX_RGB(23, 23, 25));

    NNS_G3dGlbMaterialColorDiffAmb(GX_RGB(16, 16, 16), GX_RGB(14, 14, 14), 0);
    NNS_G3dGlbMaterialColorSpecEmi(GX_RGB(20, 20, 20), GX_RGB(16, 16, 16), 0);
}

void SpearPillar_UpdateCamera(SpearPillarContext *param0)
{
    CameraAngle v0 = Camera_GetAngle(param0->camera);
    VecFx32 v1 = Camera_GetPosition(param0->camera);

    Camera_SetPosition(&v1, param0->camera);
    Camera_SetAngleAroundTarget(&v0, param0->camera);
}

void SpearPillar_StartCameraAnim(SpearPillarCameraAnim *param0)
{
    CameraAngle v0;

    param0->angleSteps[0] = param0->duration;
    param0->angleSteps[1] = ((65535 / 360) * param0->angleDeltaX / param0->duration);
    param0->angleSteps[2] = ((65535 / 360) * param0->angleDeltaY / param0->duration);
    param0->angleSteps[3] = ((65535 / 360) * param0->angleDeltaZ / param0->duration);

    param0->posSteps[1] = param0->posDeltaX / param0->duration;
    param0->posSteps[2] = param0->posDeltaY / param0->duration;
    param0->posSteps[3] = param0->posDeltaZ / param0->duration;

    v0 = Camera_GetAngle(param0->camera);

    param0->cameraAngle.x = v0.x + ((65535 / 360) * param0->angleDeltaX);
    param0->cameraAngle.y = v0.y + ((65535 / 360) * param0->angleDeltaY);
    param0->cameraAngle.z = v0.z + ((65535 / 360) * param0->angleDeltaZ);
}

BOOL SpearPillar_UpdateCameraAnim(SpearPillarCameraAnim *param0)
{
    BOOL v0 = 0;
    CameraAngle v1 = Camera_GetAngle(param0->camera);

    if (param0->angleSteps[0] == 0) {
        return 1;
    }

    if ((--param0->angleSteps[0]) == 0) {
        v1.x = param0->cameraAngle.x;
        v1.y = param0->cameraAngle.y;
        v1.z = param0->cameraAngle.z;
        v0 = 1;
    } else {
        v1.x += (param0->angleSteps[1]);
        v1.y += (param0->angleSteps[2]);
        v1.z += (param0->angleSteps[3]);

        param0->targetPos->x += param0->posSteps[1];
        param0->targetPos->y += param0->posSteps[2];
        param0->targetPos->z += param0->posSteps[3];
    }

    Camera_SetAngleAroundTarget(&v1, param0->camera);

    return v0;
}

void SpearPillar_DrawObject(SpearPillarObject *param0)
{
    if (param0->isLoaded == 0) {
        return;
    }

    if (param0->isAnimating) {
        BOOL v0 = 0;

        if (param0->useAnimation) {
            if (param0->animID == 0) {
                Easy3DAnim_UpdateLooped(&param0->anims[0], param0->animSpeed);
            } else {
                SpearPillarObject_UpdateMovement(param0);
                SpearPillarObject_UpdateAnim(param0);
            }
        } else {
            if (param0->updateAllAnims) {
                int v1;

                for (v1 = 0; v1 < 4; v1++) {
                    v0 = Easy3DAnim_Update(&param0->anims[v1], param0->animSpeed);
                }
            } else {
                v0 = Easy3DAnim_Update(&param0->anims[0], param0->animSpeed);
            }
        }

        if (param0->loopAnim1) {
            Easy3DAnim_UpdateLooped(&param0->anims[1], param0->animSpeed);
        }

        if (param0->updateAnim1) {
            Easy3DAnim_Update(&param0->anims[1], param0->animSpeed);
        }

        if (v0 == 1) {
            param0->isAnimating = 0;
        }
    }

    NNS_G3dGePushMtx();
    Easy3DObject_Draw(&param0->object);
    NNS_G3dGePopMtx(1);
}

void SpearPillar_ReleaseModel(SpearPillarObject *param0)
{
    Easy3DModel_Release(&param0->model);
}

void SpearPillar_ReleaseAnim(int param0, SpearPillarObject *param1, NNSFndAllocator *param2)
{
    Easy3DAnim_Release(&param1->anims[param0], param2);
}

void SpearPillar_FreeObject(SpearPillarObject *param0, NNSFndAllocator *param1, int param2)
{
    int v0;

    SpearPillar_ReleaseModel(param0);

    for (v0 = 0; v0 < param2; v0++) {
        SpearPillar_ReleaseAnim(v0, param0, param1);
    }
}

void SpearPillar_LoadObject(SpearPillarObject *param0, int param1, NARC *param2)
{
    Easy3DModel_LoadFrom(&param0->model, param2, param1, HEAP_ID_111);
    Easy3DObject_Init(&param0->object, &param0->model);
    Easy3DObject_SetPosition(&param0->object, 0, 0, 0);
    Easy3DObject_SetScale(&param0->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&param0->object, 1);

    param0->isLoaded = 1;
}

void SpearPillar_CloneObject(SpearPillarObject *param0, SpearPillarObject *param1, int param2, NARC *param3)
{
    Easy3DObject_Init(&param1->object, &param0->model);
    Easy3DObject_SetPosition(&param1->object, 0, 0, 0);
    Easy3DObject_SetScale(&param1->object, FX32_CONST(1.00f), FX32_CONST(1.00f), FX32_CONST(1.00f));
    Easy3DObject_SetVisible(&param1->object, 1);

    param1->isLoaded = 1;
}

void SpearPillar_LoadObjectAnim(int param0, SpearPillarObject *param1, int param2, NARC *param3, NNSFndAllocator *param4)
{
    Easy3DAnim_LoadFrom(&param1->anims[param0], &param1->model, param3, param2, 111, param4);
    Easy3DAnim_SetFrame(&param1->anims[param0], 0);
    Easy3DObject_AddAnim(&param1->object, &param1->anims[param0]);

    param1->animSpeed = FX32_CONST(1);
    param1->stepIndex = 0xFF;
    param1->framesRemaining = 0xFF;
}

void SpearPillar_CloneObjectAnim(int param0, SpearPillarObject *param1, SpearPillarObject *param2, int param3, NARC *param4, NNSFndAllocator *param5)
{
    Easy3DAnim_LoadFrom(&param2->anims[param0], &param1->model, param4, param3, 111, param5);
    Easy3DAnim_SetFrame(&param2->anims[param0], 0);
    Easy3DObject_AddAnim(&param2->object, &param2->anims[param0]);

    param2->animSpeed = FX32_CONST(1);
    param2->stepIndex = 0xFF;
    param2->framesRemaining = 0xFF;
}

void SpearPillar_BlendBg(SpearPillarContext *param0)
{
    if (param0->blendPhase == 0) {
        if (param0->blendLevel < 31) {
            param0->blendLevel++;
        } else {
            param0->blendPhase ^= 1;
        }
    } else {
        if (param0->blendLevel > 0) {
            param0->blendLevel--;
        } else {
            param0->blendPhase ^= 1;
        }
    }

    PaletteData_Blend(param0->paletteData, PLTTBUF_SUB_BG, 0, 4, param0->blendLevel / 8, 0xCCCC);
    PaletteData_Blend(param0->paletteData, PLTTBUF_SUB_BG, 4, 6, param0->blendLevel / 8, 0xCCCC);
}

void SpearPillar_BlendBgByScene(SpearPillarContext *param0, int param1)
{
    int v0;
    const u8 v1[] = {
        4,
        4,
        4,
    };
    const v2[][2] = {
        { 0, 31 },
        { 0, 31 },
        { 0, 31 },
    };
    const u8 v3[][2] = {
        { 0, 32 },
        { 0, 32 },
        { 0, 32 },
    };
    const int v4[] = {
        0x10,
        0x10,
        0x10,
    };

    v0 = param1;

    if (param1 >= NELEMS(v4)) {
        v0 = NELEMS(v4) - 1;
    }

    if (param0->blendPhase == 2) {
        if (param0->blendTimer < ((v0 + 1) * 2)) {
            param0->blendTimer++;
        } else {
            param0->blendPhase = 0;
            param0->blendTimer = 0;
        }

        return;
    }

    if (param0->blendPhase == 0) {
        if (param0->blendLevel < v2[v0][1]) {
            param0->blendLevel++;
        } else {
            param0->blendPhase++;
        }
    } else {
        if (param0->blendLevel > v2[v0][0]) {
            param0->blendLevel--;
        } else {
            param0->blendPhase++;
        }
    }

    PaletteData_Blend(param0->paletteData, PLTTBUF_SUB_BG, v3[v0][0], v3[v0][1], param0->blendLevel / v1[v0], v4[v0]);
}

void SpearPillar_Set3DScreen(int param0)
{
    gSystem.whichScreenIs3D = param0;
    GXLayers_SwapDisplay();
}

void SpearPillar_SetBrightness(SpearPillar *param0, int param1)
{
    param0->context.blend.brightness = param1;
    G2_SetBlendBrightness((GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), param0->context.blend.brightness);
    G2S_SetBlendBrightness((GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), param0->context.blend.brightness);
}
