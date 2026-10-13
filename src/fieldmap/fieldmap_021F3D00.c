#include "fieldmap/fieldmap_021F3D00.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"
#include "map_object_movement.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel models[4];
    Simple3DRenderObj renderObjs[4];
} FieldEffectRenderer1AContext;

typedef struct {
    int variant;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer1AContext *context;
    MapObject *mapObject;
    Simple3DRenderObj *renderObj;
} FieldEffectRenderer1AParams;

typedef struct {
    int unk_00;
    int done;
    int localID;
    int mapHeaderID;
    FieldEffectRenderer1AParams params;
} FieldEffectRenderer1AAnim;

static void FieldMap_021F3D2C(FieldEffectRenderer1AContext *param0);
static void FieldMap_021F3D6C(FieldEffectRenderer1AContext *param0);
static Simple3DRenderObj *FieldMap_021F3D84(FieldEffectRenderer1AContext *param0, int param1);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200688;
static const u32 Unk_FieldMap_02200678[4];

void *FieldMap_021F3D00(FieldEffectManager *param0)
{
    FieldEffectRenderer1AContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer1AContext)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F3D2C(v0);
    return v0;
}

void FieldMap_021F3D1C(void *param0)
{
    FieldEffectRenderer1AContext *v0 = param0;

    FieldMap_021F3D6C(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F3D2C(FieldEffectRenderer1AContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->models[v0], 0, Unk_FieldMap_02200678[v0], 0);
        Simple3D_CreateRenderObject(&param0->renderObjs[v0], &param0->models[v0]);
    }
}

static void FieldMap_021F3D6C(FieldEffectRenderer1AContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Simple3D_FreeModel(&param0->models[v0]);
    }
}

static Simple3DRenderObj *FieldMap_021F3D84(FieldEffectRenderer1AContext *param0, int param1)
{
    return &param0->renderObjs[param1];
}

OverworldAnimManager *FieldMap_021F3D90(MapObject *param0, int param1)
{
    VecFx32 v0;
    OverworldAnimManager *v1;
    FieldEffectRenderer1AParams v2;
    FieldEffectManager *v3 = MapObject_GetFieldEffectManager(param0);

    {
        FieldSystem *fieldSystem = FieldEffectManager_GetFieldSystem(v3);
        int v5 = MapObject_GetX(param0);
        int v6 = MapObject_GetZ(param0);

        VecFx32_SetPosFromMapCoords(v5, v6, &v0);
        MapObject_RecalculatePositionHeight(fieldSystem, &v0);
    }

    {
        v2.variant = param1;
        v2.fieldEffectManager = v3;
        v2.context = FieldEffectManager_GetRendererContext(v3, 26);
        v2.mapObject = param0;
        v2.renderObj = FieldMap_021F3D84(v2.context, param1);
    }

    {
        int v7 = MapObject_CalculateTaskPriority(param0, 2);
        v1 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200688, &v0, 0, &v2, v7);
    }

    return v1;
}

static int FieldMap_021F3E00(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer1AAnim *v0 = param1;
    const FieldEffectRenderer1AParams *v1 = OverworldAnimManager_GetUserData(param0);
    MapObject *v2 = v1->mapObject;

    v0->params = *v1;
    v0->localID = MapObject_GetLocalID(v2);
    v0->mapHeaderID = MapObject_GetMapHeaderID(v2);

    return 1;
}

static void FieldMap_021F3E30(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer1AAnim *v0 = param1;
    MapObject *v1 = v0->params.mapObject;

    if (MapObject_MatchesLocalIDAndMap(v1, v0->localID, v0->mapHeaderID) == 1) {
        Disguise_SetAnimManager(v1, NULL);
    }
}

static void FieldMap_021F3E50(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer1AAnim *v0 = param1;
}

static void FieldMap_021F3E54(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer1AAnim *v0 = param1;

    if (v0->done == 1) {
        return;
    }

    {
        VecFx32 v1;

        OverworldAnimManager_GetPosition(param0, &v1);
        Simple3D_DrawRenderObjWithPos(v0->params.renderObj, &v1);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200688 = {
    (sizeof(FieldEffectRenderer1AAnim)),
    FieldMap_021F3E00,
    FieldMap_021F3E30,
    FieldMap_021F3E50,
    FieldMap_021F3E54
};

static const u32 Unk_FieldMap_02200678[4] = {
    0x67,
    0x68,
    0x69,
    0x6A
};
