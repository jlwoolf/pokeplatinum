#include "fieldmap/fieldmap_021F17B8.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"
#include "fieldmap/fieldmap_021EB1A0.h"
#include "fieldmap/fieldmap_021ECE40.h"

#include "berry_patch_graphics.h"
#include "billboard.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
} FieldEffectRenderer01Context;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer01Context *context;
    MapObject *mapObject;
} FieldEffectRenderer01Params;

typedef struct {
    int localID;
    int mapHeaderID;
    int graphicsID;
    int created;
    int variant;
    FieldEffectRenderer01Params params;
    Billboard *billboard;
    VecFx32 scale;
    fx32 scaleDelta;
} FieldEffectRenderer01Anim;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer01Context *context;
    BillboardResources resources;
    const Billboard *sourceBillboard;
} FieldEffectRenderer01AltContext;

typedef struct {
    int variant;
    FieldEffectRenderer01AltContext context;
    Billboard *billboard;
    VecFx32 scale;
    fx32 scaleDelta;
    VecFx32 basePosition;
} FieldEffectRenderer01AltAnim;

static void FieldMap_021F17E4(FieldEffectRenderer01Context *param0);
static void FieldMap_021F17F4(FieldEffectRenderer01Context *param0);
static void FieldMap_021F1A24(FieldEffectRenderer01Anim *param0, MapObject *param1, VecFx32 *param2);
static void FieldMap_021F1A8C(OverworldAnimManager *param0, FieldEffectRenderer01Anim *param1);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200338;

void *FieldMap_021F17B8(FieldEffectManager *param0)
{
    FieldEffectRenderer01Context *v0 = FieldEffectManager_HeapAllocInit(param0, sizeof(FieldEffectRenderer01Context), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F17E4(v0);
    return v0;
}

void FieldMap_021F17D4(void *param0)
{
    FieldEffectRenderer01Context *v0 = param0;

    FieldMap_021F17F4(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F17E4(FieldEffectRenderer01Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 2, 20);
}

static void FieldMap_021F17F4(FieldEffectRenderer01Context *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 2);
}

void FieldMap_021F1800(MapObject *param0, int param1)
{
    int v0;
    VecFx32 v1;
    FieldEffectRenderer01Params v2;
    OverworldAnimManager *v3;

    v2.fieldSystem = MapObject_FieldSystem(param0);
    v2.fieldEffectManager = MapObject_GetFieldEffectManager(param0);
    v2.context = FieldEffectManager_GetRendererContext(v2.fieldEffectManager, 1);
    v2.mapObject = param0;

    MapObject_GetPosPtr(param0, &v1);

    v0 = MapObject_CalculateTaskPriority(param0, 2);
    v3 = FieldEffectManager_InitAnimManager(v2.fieldEffectManager, &Unk_FieldMap_02200338, &v1, param1, &v2, v0);
}

static int FieldMap_021F184C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer01Anim *v1;
    const FieldEffectRenderer01Params *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);

    v1->params = *v2;
    v1->variant = OverworldAnimManager_GetUserInt(param0);
    v1->localID = MapObject_GetLocalID(v1->params.mapObject);
    v1->mapHeaderID = MapObject_GetMapHeaderID(v1->params.mapObject);
    v1->graphicsID = MapObject_GetGraphicsID(v1->params.mapObject);

    if (BerryPatchGraphics_IsBerryPatch(v1->graphicsID) == 1) {
        v1->graphicsID = BerryPatchGraphics_GetCurrentGraphicsResourceID(v1->params.mapObject);
    }

    v1->scale.x = FX32_ONE;
    v1->scale.y = FX32_ONE;
    v1->scale.z = FX32_ONE;
    v1->scaleDelta = (FX32_ONE / 64);

    if (v1->variant == 2) {
        v1->scaleDelta = 0;
    }

    FieldMap_021F1A24(v1, v1->params.mapObject, &v0);
    OverworldAnimManager_SetPosition(param0, &v0);
    FieldMap_021F1A8C(param0, v1);

    return 1;
}

static void FieldMap_021F18D0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer01Anim *v0 = param1;

    if (v0->created == 1) {
        Billboard_Delete(v0->billboard);
    }
}

static void FieldMap_021F18E0(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer01Anim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;
    v0 = MapObject_GetGraphicsID(v2);

    if (BerryPatchGraphics_IsBerryPatch(v0) == 1) {
        v0 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v1->params.mapObject);
    }

    if ((v1->graphicsID != v0) || (MapObject_MatchesLocalIDAndMap(v2, v1->localID, v1->mapHeaderID) == 0) || (MapObject_CheckStatus24(v2) == 0)) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    v1->scale.x += v1->scaleDelta;

    if (v1->scale.x >= (FX32_ONE + (FX32_ONE / 8))) {
        v1->scale.x = (FX32_ONE + (FX32_ONE / 8));
        v1->scaleDelta = -v1->scaleDelta;
    } else if (v1->scale.x <= (FX32_ONE - (FX32_ONE / 8))) {
        v1->scale.x = (FX32_ONE - (FX32_ONE / 8));
        v1->scaleDelta = -v1->scaleDelta;
    }

    {
        VecFx32 v3;

        FieldMap_021F1A24(v1, v2, &v3);
        OverworldAnimManager_SetPosition(param0, &v3);
    }

    {
        if (v1->created == 0) {
            FieldMap_021F1A8C(param0, v1);
        }
    }
}

static void FieldMap_021F1978(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer01Anim *v0 = param1;
    MapObject *v1 = v0->params.mapObject;

    {
        int v2 = MapObject_GetGraphicsID(v1);

        if (BerryPatchGraphics_IsBerryPatch(v2) == 1) {
            v2 = BerryPatchGraphics_GetCurrentGraphicsResourceID(v0->params.mapObject);
        }

        if ((v0->graphicsID != v2) || (MapObject_MatchesLocalIDAndMap(v1, v0->localID, v0->mapHeaderID) == 0) || (MapObject_CheckStatus24(v1) == 0)) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
    }

    if (v0->created == 0) {
        return;
    }

    if (MapObject_IsHidden(v1) == 1) {
        Billboard_SetDrawFlag(v0->billboard, 0);
    } else {
        Billboard_SetDrawFlag(v0->billboard, 1);
    }

    {
        VecFx32 v3;

        OverworldAnimManager_GetPosition(param0, &v3);
        Billboard_SetPos(v0->billboard, &v3);
    }

    Billboard_SetScale(v0->billboard, &v0->scale);

    {
        Billboard *v4 = FieldMap_021EB1A0(v0->params.mapObject);

        Billboard_SetAnimNum(v0->billboard, Billboard_GetAnimNum(v4));
        Billboard_SetFrameNum(v0->billboard, Billboard_GetFrameNum(v4));
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200338 = {
    sizeof(FieldEffectRenderer01Anim),
    FieldMap_021F184C,
    FieldMap_021F18D0,
    FieldMap_021F18E0,
    FieldMap_021F1978
};

static void FieldMap_021F1A24(FieldEffectRenderer01Anim *param0, MapObject *param1, VecFx32 *param2)
{
    int v0;
    fx32 v1, v2;
    fx32 v3[3] = {
        (FX32_ONE * 12),
        FX32_ONE * 16, (FX32_ONE * 12)
    };

    MapObject_GetSpriteJumpOffset(param1, param2);

    v1 = param2->x;
    v2 = -param2->z;

    MapObject_GetPosPtr(param1, param2);
    v0 = MapObject_RecalculatePositionHeight(param0->params.fieldSystem, param2);

    param2->x += v1;
    param2->z += v2 + (FX32_ONE * -7);

    if (v0 == 0) {
        param2->y = 0;
    } else {
        param2->y -= v3[param0->variant];
    }
}

static void FieldMap_021F1A8C(OverworldAnimManager *param0, FieldEffectRenderer01Anim *param1)
{
    int v0;
    void *v1;
    VecFx32 v2;
    BillboardResources v3;

    {
        const MapObjectManager *v4 = MapObject_MapObjectManager(param1->params.mapObject);

        if (FieldMap_021ED150(v4, param1->graphicsID, &v3) == 0) {
            return;
        }

        if (FieldMap_021EDD94(param1->params.mapObject) == 1) {
            return;
        }
    }

    v1 = FieldMap_021DF9FC(param1->params.fieldEffectManager, 2);
    v3.modelRes = v1;

    OverworldAnimManager_GetPosition(param0, &v2);

    param1->billboard = FieldMap_021DF7F8(param1->params.fieldEffectManager, &v3, &v2);
    param1->created = 1;
}

static const OverworldAnimManagerFuncs Unk_FieldMap_0220034C;

static void FieldMap_021F1AD8(OverworldAnimManager *param0, FieldEffectRenderer01AltAnim *param1)
{
    int v0;
    void *v1;
    VecFx32 v2;
    BillboardResources v3 = param1->context.resources;

    v1 = FieldMap_021DF9FC(param1->context.fieldEffectManager, 2);
    v3.modelRes = v1;

    OverworldAnimManager_GetPosition(param0, &v2);
    param1->billboard = FieldMap_021DF7F8(param1->context.fieldEffectManager, &v3, &v2);

    {
        const Billboard *v4 = param1->context.sourceBillboard;

        Billboard_SetAnimNum(param1->billboard, Billboard_GetAnimNum(v4));
        Billboard_SetAnimFrameNum(param1->billboard, Billboard_GetAnimFrameNum(v4));
        Billboard_SetFrameNum(param1->billboard, Billboard_GetFrameNum(v4));
        Billboard_AdvanceAnim(param1->billboard, 0);
        Billboard_TryRequestVRAMTransfer(param1->billboard);
    }
}

static void FieldMap_021F1B4C(FieldEffectRenderer01AltAnim *param0, VecFx32 *param1)
{
    int v0;
    VecFx32 v1;
    fx32 v2;
    fx32 v3[3] = {
        FX32_ONE * 12,
        FX32_ONE * 16,
        FX32_ONE * 12,
    };

    *param1 = param0->basePosition;
    v0 = MapObject_RecalculatePositionHeight(param0->context.fieldSystem, param1);
    param1->z += (FX32_ONE * -7);

    if (v0 == 0) {
        param1->y = 0;
    } else {
        param1->y -= v3[param0->variant];
    }
}

OverworldAnimManager *FieldMap_021F1BA4(FieldEffectManager *param0, const BillboardResources *param1, const Billboard *param2, const VecFx32 *param3, int param4, int param5)
{
    OverworldAnimManager *v0;
    FieldEffectRenderer01AltContext v1;

    v1.fieldSystem = FieldEffectManager_GetFieldSystem(param0);
    v1.fieldEffectManager = param0;
    v1.context = FieldEffectManager_GetRendererContext(param0, 1);
    v1.resources = *param1;
    v1.sourceBillboard = param2;

    v0 = FieldEffectManager_InitAnimManager(param0, &Unk_FieldMap_0220034C, param3, param4, &v1, param5);
    return v0;
}

static int FieldMap_021F1BEC(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer01AltAnim *v1;
    const FieldEffectRenderer01AltContext *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);

    v1->context = *v2;
    v1->variant = OverworldAnimManager_GetUserInt(param0);
    v1->scale.x = FX32_ONE;
    v1->scale.y = FX32_ONE;
    v1->scale.z = FX32_ONE;
    v1->scaleDelta = (FX32_ONE / 64);

    if (v1->variant == 2) {
        v1->scaleDelta = 0;
    }

    OverworldAnimManager_GetPosition(param0, &v1->basePosition);
    FieldMap_021F1B4C(v1, &v0);

    OverworldAnimManager_SetPosition(param0, &v0);
    FieldMap_021F1AD8(param0, v1);

    OverworldAnimManager_CallTickFunc(param0);
    return 1;
}

static void FieldMap_021F1C54(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer01AltAnim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F1C60(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer01AltAnim *v0 = param1;

    v0->scale.x += v0->scaleDelta;

    if (v0->scale.x >= (FX32_ONE + (FX32_ONE / 8))) {
        v0->scale.x = (FX32_ONE + (FX32_ONE / 8));
        v0->scaleDelta = -v0->scaleDelta;
    } else if (v0->scale.x <= (FX32_ONE - (FX32_ONE / 8))) {
        v0->scale.x = (FX32_ONE - (FX32_ONE / 8));
        v0->scaleDelta = -v0->scaleDelta;
    }

    {
        VecFx32 v1;

        FieldMap_021F1B4C(v0, &v1);
        OverworldAnimManager_SetPosition(param0, &v1);
    }
}

static void FieldMap_021F1CA4(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer01AltAnim *v0 = param1;

    {
        VecFx32 v1;

        OverworldAnimManager_GetPosition(param0, &v1);
        Billboard_SetPos(v0->billboard, &v1);
    }

    Billboard_SetScale(v0->billboard, &v0->scale);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_0220034C = {
    sizeof(FieldEffectRenderer01Anim),
    FieldMap_021F1BEC,
    FieldMap_021F1C54,
    FieldMap_021F1C60,
    FieldMap_021F1CA4
};
