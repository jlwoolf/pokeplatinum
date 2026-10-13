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
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DAnimation anim;
} FieldEffectRenderer12Context;

typedef struct {
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer12Context *context;
} FieldEffectRenderer12Params;

typedef struct {
    Simple3DAnimation anim;
    Simple3DRenderObj renderObj;
    FieldEffectRenderer12Params params;
} FieldEffectRenderer12Anim;

static void FieldMap_021F2BFC(FieldEffectRenderer12Context *param0);
static void FieldMap_021F2C24(FieldEffectRenderer12Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022004D8;

void *FieldMap_021F2BD0(FieldEffectManager *param0)
{
    FieldEffectRenderer12Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer12Context)), 0, 0);
    v0->fieldEffectManager = param0;

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
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 16, 0);
    FieldEffectManager_LoadAnimation(param0->fieldEffectManager, &param0->anim, 0, 161, 0);
}

static void FieldMap_021F2C24(FieldEffectRenderer12Context *param0)
{
    Simple3D_FreeModel(&param0->model);
    Simple3D_FreeAnimation(&param0->anim);
}

void FieldMap_021F2C38(MapObject *param0, int param1, int param2, int param3)
{
    int v0, v1;
    FieldEffectRenderer12Params v2;
    VecFx32 v3;

    v2.fieldEffectManager = MapObject_GetFieldEffectManager(param0);
    v2.context = FieldEffectManager_GetRendererContext(v2.fieldEffectManager, 18);

    VecFx32_SetPosFromMapCoords(param1, param3, &v3);

    v3.z += ((param2) << 3) + (FX32_ONE * 0);
    v3.y = (((MapObject_GetYPrev(param0)) << 3) * FX32_ONE) + (-FX32_ONE * 8);

    v1 = 0;
    v0 = MapObject_CalculateTaskPriority(param0, 2);

    FieldEffectManager_InitAnimManager(v2.fieldEffectManager, &Unk_FieldMap_022004D8, &v3, v1, &v2, v0);
}

static int FieldMap_021F2C98(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;
    const FieldEffectRenderer12Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->params.fieldEffectManager, &v0->anim, &v0->params.context->model, &v0->params.context->anim, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->renderObj, &v0->params.context->model, &v0->anim);

    return 1;
}

static void FieldMap_021F2CD0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;
    Simple3D_FreeAnimation(&v0->anim);
}

static void FieldMap_021F2CDC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer12Anim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->anim) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->anim, FX32_ONE, 0);
}

static void FieldMap_021F2D04(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer12Anim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->renderObj, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022004D8 = {
    sizeof(FieldEffectRenderer12Anim),
    FieldMap_021F2C98,
    FieldMap_021F2CD0,
    FieldMap_021F2CDC,
    FieldMap_021F2D04
};
