#include "fieldmap/fieldmap_021F55CC.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "fx_util.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"
#include "sound_playback.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DAnimation anim;
} FieldEffectRenderer08Context;

typedef struct {
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer08Context *context;
} FieldEffectRenderer08Params;

typedef struct {
    Simple3DAnimation anim;
    Simple3DRenderObj renderObj;
    FieldEffectRenderer08Params params;
} FieldEffectRenderer08Anim;

static void FieldMap_021F55F8(FieldEffectRenderer08Context *param0);
static void FieldMap_021F5620(FieldEffectRenderer08Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B1C;

void *FieldMap_021F55CC(FieldEffectManager *param0)
{
    FieldEffectRenderer08Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer08Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F55F8(v0);
    return v0;
}

void FieldMap_021F55E8(void *param0)
{
    FieldEffectRenderer08Context *v0 = param0;

    FieldMap_021F5620(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F55F8(FieldEffectRenderer08Context *param0)
{
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 58, 0);
    FieldEffectManager_LoadAnimation(param0->fieldEffectManager, &param0->anim, 0, 162, 0);
}

static void FieldMap_021F5620(FieldEffectRenderer08Context *param0)
{
    Simple3D_FreeModel(&param0->model);
    Simple3D_FreeAnimation(&param0->anim);
}

void FieldMap_021F5634(FieldSystem *fieldSystem, int x, int unused, int z)
{
    FieldEffectRenderer08Params v2;
    VecFx32 v3;

    v2.fieldEffectManager = fieldSystem->fieldEffMan;
    v2.context = FieldEffectManager_GetRendererContext(v2.fieldEffectManager, 8);

    v3.x = ((x << 4) * FX32_ONE) + (FX32_ONE * 8);
    v3.y = (FX32_ONE * 10);
    v3.z = ((z << 4) * FX32_ONE);

    FieldEffectManager_InitAnimManager(v2.fieldEffectManager, &Unk_FieldMap_02200B1C, &v3, 0, &v2, 0xff);
    Sound_PlayEffect(SEQ_SE_DP_WIN_OPEN2_sseq);
}

static int FieldMap_021F5684(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer08Anim *v0 = param1;
    const FieldEffectRenderer08Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->params.fieldEffectManager, &v0->anim, &v0->params.context->model, &v0->params.context->anim, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->renderObj, &v0->params.context->model, &v0->anim);

    return 1;
}

static void FieldMap_021F56BC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer08Anim *v0 = param1;
    Simple3D_FreeAnimation(&v0->anim);
}

static void FieldMap_021F56C8(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer08Anim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->anim) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->anim, FX32_ONE, 0);
}

static void FieldMap_021F56F0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer08Anim *v0 = param1;

    {
        VecFx32 v1, v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
        MtxFx33 v3 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
        const MtxFx43 *v4 = NNS_G3dGlbGetInvCameraMtx();
        MtxFx33 v5;

        MTX_Rot33Angles(&v3, 90, 0, 0);

        MTX_Copy43To33(v4, &v5);
        MTX_Concat33(&v3, &v5, &v3);

        OverworldAnimManager_GetPosition(param0, &v1);
        Simple3D_DrawRenderObj(&v0->renderObj, &v1, &v2, &v3);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B1C = {
    sizeof(FieldEffectRenderer08Anim),
    FieldMap_021F5684,
    FieldMap_021F56BC,
    FieldMap_021F56C8,
    FieldMap_021F56F0
};
