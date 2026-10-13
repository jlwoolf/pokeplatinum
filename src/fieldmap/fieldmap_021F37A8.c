#include "fieldmap/fieldmap_021F37A8.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "billboard.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
} FieldEffectRenderer18Context;

typedef struct {
    int x;
    int y;
    int z;
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer18Context *context;
    MapObject *mapObject;
} FieldEffectRenderer18Params;

typedef struct {
    int state;
    int graphicsID;
    int localID;
    int mapHeaderID;
    int unk_10;
    int groundHeight;
    FieldEffectRenderer18Params params;
    Billboard *billboard;
} FieldEffectRenderer18Anim;

static void FieldMap_021F37D4(FieldEffectRenderer18Context *param0);
static void FieldMap_021F381C(FieldEffectRenderer18Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200620;
const BillboardAnim Unk_FieldMap_02200634[];

void *FieldMap_021F37A8(FieldEffectManager *param0)
{
    FieldEffectRenderer18Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer18Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F37D4(v0);
    return v0;
}

void FieldMap_021F37C4(void *param0)
{
    FieldEffectRenderer18Context *v0 = param0;

    FieldMap_021F381C(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F37D4(FieldEffectRenderer18Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 7, 89);
    FieldMap_021DFA14(param0->fieldEffectManager, 7, 176);
    FieldMap_021DFA3C(param0->fieldEffectManager, 8, 8, 1);
    FieldMap_021DF864(param0->fieldEffectManager, 9, 7, 7, 8, 0, Unk_FieldMap_02200634);
}

static void FieldMap_021F381C(FieldEffectRenderer18Context *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 7);
    FieldMap_021DFA30(param0->fieldEffectManager, 7);
    FieldMap_021DFA7C(param0->fieldEffectManager, 8);
    FieldMap_021DF9D4(param0->fieldEffectManager, 9);
}

void FieldMap_021F3844(MapObject *param0, int param1)
{
    int v0;
    VecFx32 v1;
    FieldEffectRenderer18Params v2;
    FieldEffectManager *v3;
    OverworldAnimManager *v4;

    v3 = MapObject_GetFieldEffectManager(param0);

    v2.x = MapObject_GetX(param0);
    v2.y = MapObject_GetY(param0);
    v2.z = MapObject_GetZ(param0);
    v2.fieldEffectManager = v3;
    v2.fieldSystem = FieldEffectManager_GetFieldSystem(v3);
    v2.context = FieldEffectManager_GetRendererContext(v3, 24);
    v2.mapObject = param0;

    MapObject_GetPosPtr(param0, &v1);

    v0 = MapObject_CalculateTaskPriority(param0, 2);
    v4 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200620, &v1, param1, &v2, v0);
}

static int FieldMap_021F38AC(OverworldAnimManager *param0, void *param1)
{
    int v0, v1;
    VecFx32 v2;
    FieldEffectRenderer18Anim *v3;
    const FieldEffectRenderer18Params *v4;

    v3 = param1;
    v4 = OverworldAnimManager_GetUserData(param0);

    v3->params = *v4;
    v3->graphicsID = MapObject_GetEffectiveGraphicsID(v3->params.mapObject);
    v3->localID = MapObject_GetLocalID(v3->params.mapObject);
    v3->mapHeaderID = MapObject_GetMapHeaderID(v3->params.mapObject);

    v2.x = (((v3->params.x) << 4) * FX32_ONE);
    v2.z = (((v3->params.z) << 4) * FX32_ONE);
    v2.y = MapObject_GetPosY(v3->params.mapObject);

    v3->groundHeight = MapObject_RecalculatePositionHeight(v3->params.fieldSystem, &v2);

    v2.x += ((16 * FX32_ONE) >> 1);
    v2.z += (((16 * FX32_ONE) >> 1) + (FX32_ONE * 6) + (FX32_ONE * 4));

    OverworldAnimManager_SetPosition(param0, &v2);
    v3->billboard = FieldMap_021DF84C(v3->params.fieldEffectManager, 9, &v2);

    if (OverworldAnimManager_GetUserInt(param0) == 0) {
        v3->state = 1;
    }

    return 1;
}

static void FieldMap_021F3940(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer18Anim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F394C(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer18Anim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;

    if (MapObject_MatchesGraphicsAndLocalID(v2, v1->graphicsID, v1->localID, v1->mapHeaderID) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    if (v1->groundHeight == 0) {
        VecFx32 v3, v4;

        OverworldAnimManager_GetPosition(param0, &v3);

        v4.x = (((v1->params.x) << 4) * FX32_ONE);
        v4.z = (((v1->params.z) << 4) * FX32_ONE);
        v4.y = v3.y;

        v1->groundHeight = MapObject_RecalculatePositionHeight(v1->params.fieldSystem, &v4);

        if (v1->groundHeight == 1) {
            v3.y = v4.y;
            OverworldAnimManager_SetPosition(param0, &v3);
        }
    }

    switch (v1->state) {
    case 0:
        Billboard_AdvanceAnim(v1->billboard, FX32_ONE);
        v0 = (Billboard_GetAnimFrameNum(v1->billboard) / FX32_ONE);

        if (v0 >= 12) {
            v1->state = 1;
        }
        break;
    case 1:
        Billboard_SetFrameNum(v1->billboard, (FX32_ONE * 12));
        Billboard_AdvanceAnim(v1->billboard, 0);
        v1->state = 2;
    case 2: {
        int v5 = MapObject_GetX(v2);
        int v6 = MapObject_GetZ(v2);

        if ((v1->params.x != v5) || (v1->params.z != v6)) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
    } break;
    }
}

static void FieldMap_021F3A18(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer18Anim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;

    if (MapObject_MatchesGraphicsAndLocalID(v2, v1->graphicsID, v1->localID, v1->mapHeaderID) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    OverworldAnimManager_GetPosition(param0, &v0);
    Billboard_SetPos(v1->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200620 = {
    (sizeof(FieldEffectRenderer18Anim)),
    FieldMap_021F38AC,
    FieldMap_021F3940,
    FieldMap_021F394C,
    FieldMap_021F3A18
};

static const BillboardAnim Unk_FieldMap_02200634[] = {
    { 0x0, 0xC, 0x0 },
    { 0x0, 0x0, 0x2 }
};
