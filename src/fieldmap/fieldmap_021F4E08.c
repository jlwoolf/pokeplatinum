#include "fieldmap/fieldmap_021F4E08.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel models[33];
    Simple3DRenderObj renderObjs[33];
} FieldEffectRenderer03Context;

typedef struct {
    int x;
    int z;
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer03Context *context;
} FieldEffectRenderer03Params;

typedef struct {
    NNSG3dRenderObj unk_00;
    int textureIdx;
    float currentSize;
    float finalSize;
    int unk_60;
    int unk_64;
    int unk_68;
    FieldEffectRenderer03Params params;
} FieldEffectRenderer03Anim;

static void FieldMap_LoadFloorTextures(FieldEffectRenderer03Context *param0);
static void FieldMap_021F4E94(FieldEffectRenderer03Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200A0C;

void *FieldMap_021F4E08(FieldEffectManager *param0)
{
    FieldEffectRenderer03Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer03Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_LoadFloorTextures(v0);

    return v0;
}

void FieldMap_021F4E28(void *param0)
{
    FieldEffectRenderer03Context *v0 = param0;

    FieldMap_021F4E94(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_LoadFloorTextures(FieldEffectRenderer03Context *param0)
{
    int i;

    for (i = 0; i < FLOOR_TEXTURE_COUNT - 1; i++) {
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->models[i], 0, 26 + i, FALSE);
        Simple3D_CreateRenderObject(&param0->renderObjs[i], &param0->models[i]);
    }

    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->models[i], 0, 25, FALSE);
    Simple3D_CreateRenderObject(&param0->renderObjs[i], &param0->models[i]);
}

static void FieldMap_021F4E94(FieldEffectRenderer03Context *param0)
{
    int v0;

    for (v0 = 0; v0 < FLOOR_TEXTURE_COUNT; v0++) {
        Simple3D_FreeModel(&param0->models[v0]);
    }
}

OverworldAnimManager *FieldMap_DrawFloorTexture(FieldSystem *fieldSystem, int x, int z, int size, int textureIdx)
{
    FieldEffectManager *v3 = fieldSystem->fieldEffMan;

    FieldEffectRenderer03Params v2;
    v2.fieldEffectManager = v3;
    v2.context = FieldEffectManager_GetRendererContext(v3, 3);
    v2.x = x;
    v2.z = z;
    v2.fieldSystem = fieldSystem;

    VecFx32 v4;
    v4.x = (x << 4) * FX32_ONE + FX32_ONE * 9;
    v4.y = 0;
    v4.z = (z << 4) * FX32_ONE;

    OverworldAnimManager *v5 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200A0C, &v4, 0, &v2, 0xff);

    if (v5) {
        FieldEffectRenderer03Anim *v6 = OverworldAnimManager_GetFuncsContext(v5);
        v6->textureIdx = textureIdx;
        v6->currentSize = size;
        v6->finalSize = size;
    }

    return v5;
}

OverworldAnimManager *FieldMap_DrawGrowingFloorTexture(FieldSystem *fieldSystem, int x, int z, int finalSize, int textureIdx)
{
    OverworldAnimManager *v1 = FieldMap_DrawFloorTexture(fieldSystem, x, z, finalSize, textureIdx);

    if (v1) {
        FieldEffectRenderer03Anim *v0 = OverworldAnimManager_GetFuncsContext(v1);
        v0->currentSize = 0;
        v0->finalSize = finalSize;
    }

    return v1;
}

static int FieldMap_021F4F44(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer03Anim *v0;
    const FieldEffectRenderer03Params *v1;
    VecFx32 v2;

    v0 = param1;
    v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;

    v2.x = (((v0->params.x) << 4) * FX32_ONE) + (FX32_ONE * 9);
    v2.z = (((v0->params.z) << 4) * FX32_ONE);
    v2.y = 0;

    OverworldAnimManager_SetPosition(param0, &v2);

    return 1;
}

static void FieldMap_021F4F88(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F4F8C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer03Anim *v0 = param1;

    if (v0->currentSize < v0->finalSize) {
        v0->currentSize += 0.2;
    }
}

static void FieldMap_021F4FB8(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer03Anim *v0 = param1;

    {
        VecFx32 v1;
        VecFx32 v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
        MtxFx33 v3 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };
        Simple3DRenderObj *v4 = &v0->params.context->renderObjs[v0->textureIdx];

        OverworldAnimManager_GetPosition(param0, &v1);

        v2.x *= v0->currentSize;
        v2.y *= v0->currentSize;
        v2.z *= v0->currentSize;
        v1.x += -(FX32_ONE * 1) / 2;
        v1.y += -(FX32_ONE * 1);
        v1.z += (FX32_ONE * 5);

        Simple3D_DrawRenderObj(v4, &v1, &v2, &v3);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200A0C = {
    (sizeof(FieldEffectRenderer03Anim)),
    FieldMap_021F4F44,
    FieldMap_021F4F88,
    FieldMap_021F4F8C,
    FieldMap_021F4FB8
};
