#include "fieldmap/fieldmap_021F5428.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "fx_util.h"
#include "map_object.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    int unk_00;
    int unk_04;
    FieldEffectManager *unk_08;
    Simple3DModel unk_0C;
    Simple3DRenderObj unk_20;
    MapObject *unk_74;
} FieldEffectRenderer07Context;

typedef struct {
    FieldEffectManager *unk_00;
    FieldEffectRenderer07Context *unk_04;
    MapObject *unk_08;
} FieldEffectRenderer07Params;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    VecFx32 unk_18;
    VecFx32 unk_24;
    int unk_30;
    FieldEffectRenderer07Params unk_34;
} FieldEffectRenderer07Anim;

static void FieldMap_021F5454(FieldEffectRenderer07Context *param0);
static void FieldMap_021F547C(FieldEffectRenderer07Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200AD8;

void *FieldMap_021F5428(FieldEffectManager *param0)
{
    FieldEffectRenderer07Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer07Context)), 0, 0);
    v0->unk_08 = param0;

    FieldMap_021F5454(v0);
    return v0;
}

void FieldMap_021F5444(void *param0)
{
    FieldEffectRenderer07Context *v0 = param0;

    FieldMap_021F547C(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F5454(FieldEffectRenderer07Context *param0)
{
    FieldEffectManager_LoadModel(param0->unk_08, &param0->unk_0C, 0, 24, 0);
    Simple3D_CreateRenderObject(&param0->unk_20, &param0->unk_0C);
}

static void FieldMap_021F547C(FieldEffectRenderer07Context *param0)
{
    Simple3D_FreeModel(&param0->unk_0C);
}

OverworldAnimManager *FieldMap_021F5488(MapObject *param0)
{
    int v0, v1;
    FieldEffectRenderer07Params v2;
    FieldEffectManager *v3;
    VecFx32 v4;
    OverworldAnimManager *v5;
    FieldEffectRenderer07Anim *v6;

    v3 = MapObject_GetFieldEffectManager(param0);

    v2.unk_00 = v3;
    v2.unk_04 = FieldEffectManager_GetRendererContext(v3, 7);
    v2.unk_08 = param0;

    MapObject_GetPosPtr(param0, &v4);

    v0 = 0;
    v5 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200AD8, &v4, v0, &v2, 0xff);

    return v5;
}

static int FieldMap_021F54C4(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer07Anim *v0;
    const FieldEffectRenderer07Params *v1;
    VecFx32 v2;

    v0 = param1;
    v1 = OverworldAnimManager_GetUserData(param0);

    v0->unk_34 = *v1;
    v0->unk_08 = MapObject_GetLocalID(v0->unk_34.unk_08);
    v0->unk_0C = MapObject_GetMapHeaderID(v0->unk_34.unk_08);
    v0->unk_24.y = (FX32_ONE * 6);

    MapObject_GetPosPtr(v0->unk_34.unk_08, &v2);
    OverworldAnimManager_SetPosition(param0, &v2);

    v0->unk_30 = 60;

    return 1;
}

static void FieldMap_021F5510(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F5514(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer07Anim *v0;
    MapObject *v1;
    VecFx32 v2;

    v0 = param1;

    if (v0->unk_30 != 0) {
        v0->unk_30--;
    } else {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    v1 = v0->unk_34.unk_08;
    MapObject_GetPosPtr(v1, &v2);

    v2.z += (FX32_ONE * -10);
    OverworldAnimManager_SetPosition(param0, &v2);
}

static void FieldMap_021F554C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer07Anim *v0 = param1;

    {
        VecFx32 v1;
        VecFx32 v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
        MtxFx33 v3 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };

        OverworldAnimManager_GetPosition(param0, &v1);

        v1.y += (FX32_ONE * 25);
        v1.z += -(FX32_ONE * 5);

        {
            const MtxFx43 *v4 = NNS_G3dGlbGetInvCameraMtx();
            MtxFx33 v5;

            MTX_Rot33Angles(&v3, 90, 0, 0);

            MTX_Copy43To33(v4, &v5);
            MTX_Concat33(&v3, &v5, &v3);
        }

        Simple3D_DrawRenderObjSimple(&v0->unk_34.unk_04->unk_20, &v1, &v2, &v3);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200AD8 = {
    (sizeof(FieldEffectRenderer07Anim)),
    FieldMap_021F54C4,
    FieldMap_021F5510,
    FieldMap_021F5514,
    FieldMap_021F554C
};
