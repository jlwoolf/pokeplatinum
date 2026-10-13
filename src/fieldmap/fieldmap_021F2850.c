#include "fieldmap/fieldmap_021F2850.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "fx_util.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"
#include "sys_task_manager.h"

typedef struct {
    int refCount;
    int loaded;
    int unk_08;
    SysTask *unk_0C;
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DRenderObj renderObj;
} FieldEffectRenderer10Context;

typedef struct {
    int variant;
    FieldEffectManager *fieldEffectManager;
    FieldSystem *fieldSystem;
    FieldEffectRenderer10Context *context;
    MapObject *mapObject;
} FieldEffectRenderer10Params;

typedef struct {
    int done;
    int variant;
    int counter;
    int visible;
    FieldEffectRenderer10Params params;
} FieldEffectRenderer10Anim;

static void FieldMap_021F2874(FieldEffectRenderer10Context *param0);
static void FieldMap_021F287C(FieldEffectRenderer10Context *param0);
static void FieldMap_021F288C(FieldEffectRenderer10Context *param0);
static void FieldMap_021F28C0(FieldEffectRenderer10Context *param0);
static void FieldMap_021F28D4(FieldEffectRenderer10Context *param0);
static void FieldMap_021F28E4(FieldEffectRenderer10Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022004B0;

void *FieldMap_021F2850(FieldEffectManager *param0)
{
    FieldEffectRenderer10Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer10Context)), 0, 0);
    v0->fieldEffectManager = param0;

    return v0;
}

void FieldMap_021F2864(void *param0)
{
    FieldEffectRenderer10Context *v0 = param0;

    FieldMap_021F28C0(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F2874(FieldEffectRenderer10Context *param0)
{
    param0->refCount++;
}

static void FieldMap_021F287C(FieldEffectRenderer10Context *param0)
{
    param0->refCount--;

    GF_ASSERT(param0->refCount >= 0);
}

static void FieldMap_021F288C(FieldEffectRenderer10Context *param0)
{
    if (param0->loaded == 0) {
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 82, 1);
        Simple3D_CreateRenderObject(&param0->renderObj, &param0->model);
        param0->loaded = 1;
    }
}

static void FieldMap_021F28C0(FieldEffectRenderer10Context *param0)
{
    if (param0->loaded == 1) {
        param0->loaded = 0;
        Simple3D_FreeModel(&param0->model);
    }
}

static void FieldMap_021F28D4(FieldEffectRenderer10Context *param0)
{
    if (param0->refCount == 0) {
        FieldMap_021F288C(param0);
    }
}

static void FieldMap_021F28E4(FieldEffectRenderer10Context *param0)
{
    if (param0->refCount == 0) {
        FieldMap_021F28C0(param0);
    }
}

OverworldAnimManager *FieldMap_021F28F4(MapObject *param0, int param1, int param2, int param3, int param4)
{
    int v0;
    OverworldAnimManager *v1;
    FieldEffectRenderer10Params v2;
    VecFx32 v3 = { 0, 0, 0 };
    FieldEffectManager *v4 = MapObject_GetFieldEffectManager(param0);

    v2.variant = param3;
    v2.fieldEffectManager = v4;
    v2.fieldSystem = MapObject_FieldSystem(param0);
    v2.context = FieldEffectManager_GetRendererContext(v4, 16);
    v2.mapObject = param0;

    if (param4 == 0) {
        v3.x = (((param1) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);
        v3.z = (((param2) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);
        MapObject_RecalculatePositionHeight(v2.fieldSystem, &v3);
    } else {
        MapObject_GetPosPtr(param0, &v3);
    }

    v0 = MapObject_CalculateTaskPriority(param0, 2);
    v1 = FieldEffectManager_InitAnimManager(v4, &Unk_FieldMap_022004B0, &v3, param4, &v2, v0);

    return v1;
}

void FieldMap_021F2974(OverworldAnimManager *param0, int param1)
{
    FieldEffectRenderer10Anim *v0 = OverworldAnimManager_GetFuncsContext(param0);
    v0->visible = param1;
}

static int FieldMap_021F2980(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer10Anim *v0 = param1;
    const FieldEffectRenderer10Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;
    v0->variant = v1->variant;
    v0->visible = OverworldAnimManager_GetUserInt(param0);

    FieldMap_021F28D4(v0->params.context);
    FieldMap_021F2874(v0->params.context);

    return 1;
}

static void FieldMap_021F29BC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer10Anim *v0 = param1;

    FieldMap_021F287C(v0->params.context);
    FieldMap_021F28E4(v0->params.context);
}

static void FieldMap_021F29D0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer10Anim *v0 = param1;
    MapObject *v1 = v0->params.mapObject;

    if (v0->visible == 0) {
        return;
    }

    {
        VecFx32 v2 = { 0, 0, 0 };
        MapObject_SetSpritePosOffset(v1, &v2);
    }

    {
        VecFx32 v3;

        MapObject_GetPosPtr(v1, &v3);
        v3.y += 0;
        OverworldAnimManager_SetPosition(param0, &v3);
    }
}

static void FieldMap_021F2A04(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer10Anim *v0 = param1;

    if (v0->done == 1) {
        return;
    }

    {
        v0->counter++;
    }

    {
        u32 v1 = 0;
        MtxFx33 v2;
        VecFx32 v3, v4 = { FX32_ONE, FX32_ONE, FX32_ONE };
        Simple3DRenderObj *v5 = &v0->params.context->renderObj;

        switch (v0->variant) {
        case 0:
            v1 = 180;
            break;
        case 1:
            break;
        case 2:
            v1 = 270;
            break;
        case 3:
            v1 = 90;
            break;
        }

        MTX_Rot33Angles(&v2, 0, v1, 0);
        OverworldAnimManager_GetPosition(param0, &v3);
        Simple3D_DrawRenderObj(v5, &v3, &v4, &v2);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022004B0 = {
    sizeof(FieldEffectRenderer10Anim),
    FieldMap_021F2980,
    FieldMap_021F29BC,
    FieldMap_021F29D0,
    FieldMap_021F2A04
};
