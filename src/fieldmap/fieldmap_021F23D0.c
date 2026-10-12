#include "fieldmap/fieldmap_021F23D0.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "map_object.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *unk_00;
    Simple3DModel unk_04;
    Simple3DAnimation unk_18;
} FieldEffectRenderer0DContext;

typedef struct {
    FieldEffectManager *unk_00;
    FieldEffectRenderer0DContext *unk_04;
    MapObject *unk_08;
} FieldEffectRenderer0DParams;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    FieldEffectRenderer0DParams unk_10;
    Simple3DAnimation unk_1C;
    Simple3DRenderObj unk_40;
} FieldEffectRenderer0DAnim;

static void FieldMap_021F23FC(FieldEffectRenderer0DContext *param0);
static void FieldMap_021F2424(FieldEffectRenderer0DContext *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200464;

void *FieldMap_021F23D0(FieldEffectManager *param0)
{
    FieldEffectRenderer0DContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer0DContext)), 0, 0);
    v0->unk_00 = param0;

    FieldMap_021F23FC(v0);
    return v0;
}

void FieldMap_021F23EC(void *param0)
{
    FieldEffectRenderer0DContext *v0 = param0;

    FieldMap_021F2424(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F23FC(FieldEffectRenderer0DContext *param0)
{
    FieldEffectManager_LoadModel(param0->unk_00, &param0->unk_04, 0, 78, 0);
    FieldEffectManager_LoadAnimation(param0->unk_00, &param0->unk_18, 0, 165, 0);
}

static void FieldMap_021F2424(FieldEffectRenderer0DContext *param0)
{
    Simple3D_FreeModel(&param0->unk_04);
    Simple3D_FreeAnimation(&param0->unk_18);
}

OverworldAnimManager *FieldMap_021F2438(MapObject *param0)
{
    OverworldAnimManager *v0;
    FieldEffectManager *v1;
    FieldEffectRenderer0DContext *v2;
    FieldEffectRenderer0DParams v3;

    v1 = MapObject_GetFieldEffectManager(param0);
    v2 = FieldEffectManager_GetRendererContext(v1, 13);

    v3.unk_00 = v1;
    v3.unk_04 = v2;
    v3.unk_08 = param0;

    {
        VecFx32 v4 = { 0, 0, 0 };
        int v5 = MapObject_CalculateTaskPriority(param0, 2);

        v0 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_02200464, &v4, 0, &v3, v5);
    }

    return v0;
}

void FieldMap_021F247C(OverworldAnimManager *param0)
{
    FieldEffectRenderer0DAnim *v0 = OverworldAnimManager_GetFuncsContext(param0);

    v0->unk_0C = 1;
}

static int FieldMap_021F2488(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0DAnim *v0;
    const FieldEffectRenderer0DParams *v1;

    v0 = param1;
    v1 = OverworldAnimManager_GetUserData(param0);

    v0->unk_10 = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->unk_10.unk_00, &v0->unk_1C, &v0->unk_10.unk_04->unk_04, &v0->unk_10.unk_04->unk_18, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->unk_40, &v0->unk_10.unk_04->unk_04, &v0->unk_1C);

    v0->unk_04 = MapObject_GetLocalID(v0->unk_10.unk_08);
    v0->unk_08 = MapObject_GetMapHeaderID(v0->unk_10.unk_08);

    {
        VecFx32 v2, v3;
        MapObject *v4 = v0->unk_10.unk_08;

        MapObject_GetPosPtr(v4, &v2);
        MapObject_GetSpriteJumpOffset(v4, &v3);

        v2.x += v3.x + 0;
        v2.y += v3.y + 0;
        v2.z += v3.z + (FX32_ONE * 6) - (FX32_ONE * 6);

        OverworldAnimManager_SetPosition(param0, &v2);
    }

    return 1;
}

static void FieldMap_021F2510(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0DAnim *v0 = param1;
    Simple3D_FreeAnimation(&v0->unk_1C);
}

static void FieldMap_021F251C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0DAnim *v0 = param1;
    MapObject *v1 = v0->unk_10.unk_08;

    if (v0->unk_0C == 0) {
        if (MapObject_MatchesLocalIDAndMap(v1, v0->unk_04, v0->unk_08) == 0) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
    } else {
        if (Simple3D_HasAnimationReachedEnd(&v0->unk_1C) == 1) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }

        Simple3D_UpdateAnim(&v0->unk_1C, FX32_ONE, 0);
    }

    if (v0->unk_0C == 0) {
        VecFx32 v2, v3;

        MapObject_GetPosPtr(v1, &v2);
        MapObject_GetSpriteJumpOffset(v1, &v3);

        v2.x += v3.x + 0;
        v2.y += v3.y + 0;
        v2.z += v3.z + (FX32_ONE * 6) - (FX32_ONE * 6);

        OverworldAnimManager_SetPosition(param0, &v2);
    }
}

static void FieldMap_021F25A4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer0DAnim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->unk_40, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200464 = {
    sizeof(FieldEffectRenderer0DAnim),
    FieldMap_021F2488,
    FieldMap_021F2510,
    FieldMap_021F251C,
    FieldMap_021F25A4
};
