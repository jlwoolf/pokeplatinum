#include "fieldmap/fieldmap_021F2A7C.h"

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
} FieldEffectRenderer11Context;

typedef struct {
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer11Context *context;
} FieldEffectRenderer11Params;

typedef struct {
    Simple3DAnimation anim;
    Simple3DRenderObj renderObj;
    FieldEffectRenderer11Params params;
} FieldEffectRenderer11Anim;

static void FieldMap_021F2AA8(FieldEffectRenderer11Context *param0);
static void FieldMap_021F2AD0(FieldEffectRenderer11Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022004C4;

void *FieldMap_021F2A7C(FieldEffectManager *param0)
{
    FieldEffectRenderer11Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer11Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F2AA8(v0);
    return v0;
}

void FieldMap_021F2A98(void *param0)
{
    FieldEffectRenderer11Context *v0 = param0;

    FieldMap_021F2AD0(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F2AA8(FieldEffectRenderer11Context *param0)
{
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 15, 0);
    FieldEffectManager_LoadAnimation(param0->fieldEffectManager, &param0->anim, 0, 160, 0);
}

static void FieldMap_021F2AD0(FieldEffectRenderer11Context *param0)
{
    Simple3D_FreeModel(&param0->model);
    Simple3D_FreeAnimation(&param0->anim);
}

void FieldMap_021F2AE4(MapObject *param0, int param1, int param2, int param3)
{
    int v0, v1;
    FieldEffectRenderer11Params v2;
    VecFx32 v3;

    v2.fieldEffectManager = MapObject_GetFieldEffectManager(param0);
    v2.context = FieldEffectManager_GetRendererContext(v2.fieldEffectManager, 17);

    VecFx32_SetPosFromMapCoords(param1, param3, &v3);

    v3.z += ((param2) << 3) + (FX32_ONE * 1);
    v3.y = (((MapObject_GetYPrev(param0)) << 3) * FX32_ONE) + (-FX32_ONE * 8);

    v1 = 0;
    v0 = MapObject_CalculateTaskPriority(param0, 2);

    FieldEffectManager_InitAnimManager(v2.fieldEffectManager, &Unk_FieldMap_022004C4, &v3, v1, &v2, v0);
}

static int FieldMap_021F2B48(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer11Anim *v0 = param1;
    const FieldEffectRenderer11Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->params.fieldEffectManager, &v0->anim, &v0->params.context->model, &v0->params.context->anim, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->renderObj, &v0->params.context->model, &v0->anim);

    return 1;
}

static void FieldMap_021F2B80(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer11Anim *v0 = param1;

    Simple3D_FreeAnimation(&v0->anim);
}

static void FieldMap_021F2B8C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer11Anim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->anim) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->anim, FX32_ONE, 0);
}

static void FieldMap_021F2BB4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer11Anim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->renderObj, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022004C4 = {
    sizeof(FieldEffectRenderer11Anim),
    FieldMap_021F2B48,
    FieldMap_021F2B80,
    FieldMap_021F2B8C,
    FieldMap_021F2BB4
};
