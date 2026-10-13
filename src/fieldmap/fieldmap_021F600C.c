#include "fieldmap/fieldmap_021F600C.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "billboard.h"
#include "map_object.h"
#include "overworld_anim_manager.h"

typedef struct FieldEffectRenderer16Context_t {
    FieldEffectManager *fieldEffectManager;
} FieldEffectRenderer16Context;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer16Context *context;
    MapObject *mapObject;
} FieldEffectRenderer16Params;

typedef struct {
    int unk_00;
    int localID;
    int mapHeaderID;
    int unk_0C;
    FieldEffectRenderer16Params params;
    Billboard *billboard;
} FieldEffectRenderer16Anim;

static void FieldMap_021F6038(FieldEffectRenderer16Context *param0);
static void FieldMap_021F6074(FieldEffectRenderer16Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200BD8;
const BillboardAnim Unk_FieldMap_02200BEC[];

void *FieldMap_021F600C(FieldEffectManager *param0)
{
    FieldEffectRenderer16Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer16Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F6038(v0);
    return v0;
}

void FieldMap_021F6028(void *param0)
{
    FieldEffectRenderer16Context *v0 = param0;

    FieldMap_021F6074(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F6038(FieldEffectRenderer16Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 4, 87);
    FieldMap_021DFA3C(param0->fieldEffectManager, 3, 6, 1);
    FieldMap_021DF864(param0->fieldEffectManager, 4, 4, 0, 3, 0, Unk_FieldMap_02200BEC);
}

static void FieldMap_021F6074(FieldEffectRenderer16Context *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 4);
    FieldMap_021DFA7C(param0->fieldEffectManager, 3);
    FieldMap_021DF9D4(param0->fieldEffectManager, 4);
}

OverworldAnimManager *FieldMap_021F6094(MapObject *param0)
{
    FieldEffectRenderer16Params v0;
    FieldEffectManager *v1;
    OverworldAnimManager *v2;

    v1 = MapObject_GetFieldEffectManager(param0);

    v0.fieldSystem = MapObject_FieldSystem(param0);
    v0.fieldEffectManager = v1;
    v0.context = FieldEffectManager_GetRendererContext(v1, 22);
    v0.mapObject = param0;

    {
        VecFx32 v3 = { 0, 0, 0 };
        int v4 = MapObject_CalculateTaskPriority(param0, 2);

        v2 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_02200BD8, &v3, 0, &v0, v4);
    }

    return v2;
}

static int FieldMap_021F60E4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0 = { 0, 0, 0 };
    FieldEffectRenderer16Anim *v1;
    const FieldEffectRenderer16Params *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);

    v1->params = *v2;
    v1->localID = MapObject_GetLocalID(v1->params.mapObject);
    v1->mapHeaderID = MapObject_GetMapHeaderID(v1->params.mapObject);

    OverworldAnimManager_SetPosition(param0, &v0);
    v1->billboard = FieldMap_021DF84C(v1->params.fieldEffectManager, 4, &v0);

    return 1;
}

static void FieldMap_021F6134(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer16Anim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F6140(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer16Anim *v0 = param1;
    MapObject *v1 = v0->params.mapObject;

    if (MapObject_MatchesLocalIDAndMap(v1, v0->localID, v0->mapHeaderID) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }
}

static void FieldMap_021F615C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0, v1;
    FieldEffectRenderer16Anim *v2 = param1;
    MapObject *v3 = v2->params.mapObject;

    if (MapObject_MatchesLocalIDAndMap(v3, v2->localID, v2->mapHeaderID) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    MapObject_GetPosPtr(v3, &v0);
    MapObject_GetSpriteJumpOffset(v3, &v1);

    v0.x += v1.x;
    v0.y += v1.y;
    v0.z += v1.z;
    v0.z += FX32_ONE * 12;

    Billboard_SetPos(v2->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200BD8 = {
    sizeof(FieldEffectRenderer16Anim),
    FieldMap_021F60E4,
    FieldMap_021F6134,
    FieldMap_021F6140,
    FieldMap_021F615C
};

static const BillboardAnim Unk_FieldMap_02200BEC[] = {
    { 0x0, 0x1, 0x1 },
    { 0x0, 0x0, 0x2 }
};
