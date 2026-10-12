#include "fieldmap/fieldmap_021F50BC.h"

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
} FieldEffectRenderer05Context;

typedef struct {
    FieldEffectManager *unk_00;
    FieldEffectRenderer05Context *unk_04;
    MapObject *unk_08;
} FieldEffectRenderer05Params;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    enum MapHeaderID unk_0C;
    int unk_10;
    int unk_14;
    VecFx32 unk_18;
    VecFx32 unk_24;
    FieldEffectRenderer05Params unk_30;
} FieldEffectRenderer05Anim;

static void FieldMap_021F50E8(FieldEffectRenderer05Context *param0);
static void FieldMap_021F5110(FieldEffectRenderer05Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200A50;

void *FieldMap_021F50BC(FieldEffectManager *param0)
{
    FieldEffectRenderer05Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer05Context)), 0, 0);
    v0->unk_08 = param0;

    FieldMap_021F50E8(v0);
    return v0;
}

void FieldMap_021F50D8(void *param0)
{
    FieldEffectRenderer05Context *v0 = param0;

    FieldMap_021F5110(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F50E8(FieldEffectRenderer05Context *param0)
{
    FieldEffectManager_LoadModel(param0->unk_08, &param0->unk_0C, 0, 22, 0);
    Simple3D_CreateRenderObject(&param0->unk_20, &param0->unk_0C);
}

static void FieldMap_021F5110(FieldEffectRenderer05Context *param0)
{
    Simple3D_FreeModel(&param0->unk_0C);
}

OverworldAnimManager *FieldMap_021F511C(MapObject *param0)
{
    int v0, v1;
    FieldEffectRenderer05Params v2;
    FieldEffectManager *v3;
    VecFx32 v4;
    OverworldAnimManager *v5;

    v3 = MapObject_GetFieldEffectManager(param0);

    v2.unk_00 = v3;
    v2.unk_04 = FieldEffectManager_GetRendererContext(v3, 5);
    v2.unk_08 = param0;

    MapObject_GetPosPtr(param0, &v4);

    v0 = 0;
    v5 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200A50, &v4, v0, &v2, 0xff);

    return v5;
}

static int FieldMap_021F5158(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v2;

    FieldEffectRenderer05Anim *v0 = param1;
    const FieldEffectRenderer05Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->unk_30 = *v1;
    v0->unk_08 = MapObject_GetLocalID(v0->unk_30.unk_08);
    v0->unk_0C = MapObject_GetMapHeaderID(v0->unk_30.unk_08);
    v0->unk_24.y = (FX32_ONE * 6);

    MapObject_GetPosPtr(v0->unk_30.unk_08, &v2);
    OverworldAnimManager_SetPosition(param0, &v2);

    return 1;
}

static void FieldMap_021F51A0(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F51A4(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer05Anim *v0;
    MapObject *v1;
    VecFx32 v2;

    v0 = param1;
    v1 = v0->unk_30.unk_08;

    GF_ASSERT(MapObject_MatchesLocalIDAndMap(v1, v0->unk_08, v0->unk_0C) != 0);

    switch (v0->unk_00) {
    case 0:
        MapObject_GetPosPtr(v1, &v2);
        v2.z += (FX32_ONE * -10);
        OverworldAnimManager_SetPosition(param0, &v2);
        break;
    case 1:
        v0->unk_04++;

        if (v0->unk_04 >= 30) {
            v0->unk_00++;
        }
        break;
    case 2:
        break;
    }
}

static void FieldMap_021F5204(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer05Anim *v0 = param1;

    {
        VecFx32 v1, v2 = { FX32_ONE, FX32_ONE, FX32_ONE };
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

        Simple3D_DrawRenderObjSimple(&v0->unk_30.unk_04->unk_20, &v1, &v2, &v3);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200A50 = {
    (sizeof(FieldEffectRenderer05Anim)),
    FieldMap_021F5158,
    FieldMap_021F51A0,
    FieldMap_021F51A4,
    FieldMap_021F5204
};
