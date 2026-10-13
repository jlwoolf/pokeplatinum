#include "fieldmap/fieldmap_021F5894.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "map_object.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DAnimation anim;
} FieldEffectRenderer0AContext;

typedef struct {
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer0AContext *context;
} FieldEffectRenderer0AParams;

typedef struct {
    Simple3DAnimation anim;
    Simple3DRenderObj renderObj;
    FieldEffectRenderer0AParams params;
} FieldEffectRenderer0AAnim;

static void FieldMap_021F58C0(FieldEffectRenderer0AContext *param0);
static void FieldMap_021F58E8(FieldEffectRenderer0AContext *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B68;

void *FieldMap_021F5894(FieldEffectManager *param0)
{
    FieldEffectRenderer0AContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer0AContext)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F58C0(v0);
    return v0;
}

void FieldMap_021F58B0(void *param0)
{
    FieldEffectRenderer0AContext *v0 = param0;

    FieldMap_021F58E8(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F58C0(FieldEffectRenderer0AContext *param0)
{
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 91, 0);
    FieldEffectManager_LoadAnimation(param0->fieldEffectManager, &param0->anim, 0, 163, 0);
}

static void FieldMap_021F58E8(FieldEffectRenderer0AContext *param0)
{
    Simple3D_FreeModel(&param0->model);
    Simple3D_FreeAnimation(&param0->anim);
}

void FieldMap_021F58FC(MapObject *param0, int param1, int param2, int param3)
{
    int v0, v1, v2;
    FieldEffectRenderer0AParams v3;
    VecFx32 v4;

    v3.fieldEffectManager = MapObject_GetFieldEffectManager(param0);
    v3.context = FieldEffectManager_GetRendererContext(v3.fieldEffectManager, 10);

    MapObject_GetPosPtr(param0, &v4);

    v2 = MapObject_GetFacingDir(param0);

    switch (v2) {
    case 0:
        v4.z -= (16 * FX32_ONE);
        break;
    case 1:
        v4.z += (16 * FX32_ONE);
        break;
    case 3:
        v4.x += (16 * FX32_ONE);
        break;
    case 2:
        v4.x -= (16 * FX32_ONE);
        break;
    }

    v1 = 0;
    v0 = MapObject_CalculateTaskPriority(param0, 2);

    FieldEffectManager_InitAnimManager(v3.fieldEffectManager, &Unk_FieldMap_02200B68, &v4, v1, &v3, v0);
}

static int FieldMap_021F5988(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0AAnim *v0 = param1;
    const FieldEffectRenderer0AParams *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->params.fieldEffectManager, &v0->anim, &v0->params.context->model, &v0->params.context->anim, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->renderObj, &v0->params.context->model, &v0->anim);

    return 1;
}

static void FieldMap_021F59C0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0AAnim *v0 = param1;

    Simple3D_FreeAnimation(&v0->anim);
}

static void FieldMap_021F59CC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0AAnim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->anim) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->anim, FX32_ONE, 0);
}

static void FieldMap_021F59F4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer0AAnim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->renderObj, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B68 = {
    (sizeof(FieldEffectRenderer0AAnim)),
    FieldMap_021F5988,
    FieldMap_021F59C0,
    FieldMap_021F59CC,
    FieldMap_021F59F4
};
