#include "fieldmap/fieldmap_021F2BD0.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *unk_00;
    Simple3DModel unk_04;
    Simple3DAnimation unk_18;
} FieldEffectRenderer12Context;

typedef struct {
    FieldEffectManager *unk_00;
    FieldEffectRenderer12Context *unk_04;
} FieldEffectRenderer12Params;

typedef struct {
    Simple3DAnimation unk_00;
    Simple3DRenderObj unk_24;
    FieldEffectRenderer12Params unk_78;
} FieldEffectRenderer12Anim;

static void FieldMap_021F2BFC(FieldEffectRenderer12Context *param0);
static void FieldMap_021F2C24(FieldEffectRenderer12Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022004D8;

void *FieldMap_021F2BD0(FieldEffectManager *param0)
{
    FieldEffectRenderer12Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer12Context)), 0, 0);
    v0->unk_00 = param0;

    FieldMap_021F2BFC(v0);
    return v0;
}

void FieldMap_021F2BEC(void *param0)
{
    FieldEffectRenderer12Context *v0 = param0;

    FieldMap_021F2C24(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F2BFC(FieldEffectRenderer12Context *param0)
{
    FieldEffectManager_LoadModel(param0->unk_00, &param0->unk_04, 0, 16, 0);
    FieldEffectManager_LoadAnimation(param0->unk_00, &param0->unk_18, 0, 161, 0);
}

static void FieldMap_021F2C24(FieldEffectRenderer12Context *param0)
{
    Simple3D_FreeModel(&param0->unk_04);
    Simple3D_FreeAnimation(&param0->unk_18);
}

void FieldMap_021F2C38(MapObject *param0, int param1, int param2, int param3)
{
    int v0, v1;
    FieldEffectRenderer12Params v2;
    VecFx32 v3;

    v2.unk_00 = MapObject_GetFieldEffectManager(param0);
    v2.unk_04 = FieldEffectManager_GetRendererContext(v2.unk_00, 18);

    VecFx32_SetPosFromMapCoords(param1, param3, &v3);

    v3.z += ((param2) << 3) + (FX32_ONE * 0);
    v3.y = (((MapObject_GetYPrev(param0)) << 3) * FX32_ONE) + (-FX32_ONE * 8);

    v1 = 0;
    v0 = MapObject_CalculateTaskPriority(param0, 2);

    FieldEffectManager_InitAnimManager(v2.unk_00, &Unk_FieldMap_022004D8, &v3, v1, &v2, v0);
}

static int FieldMap_021F2C98(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;
    const FieldEffectRenderer12Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->unk_78 = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->unk_78.unk_00, &v0->unk_00, &v0->unk_78.unk_04->unk_04, &v0->unk_78.unk_04->unk_18, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->unk_24, &v0->unk_78.unk_04->unk_04, &v0->unk_00);

    return 1;
}

static void FieldMap_021F2CD0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;
    Simple3D_FreeAnimation(&v0->unk_00);
}

static void FieldMap_021F2CDC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->unk_00) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->unk_00, FX32_ONE, 0);
}

static void FieldMap_021F2D04(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer12Anim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->unk_24, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022004D8 = {
    sizeof(FieldEffectRenderer12Anim),
    FieldMap_021F2C98,
    FieldMap_021F2CD0,
    FieldMap_021F2CDC,
    FieldMap_021F2D04
};
