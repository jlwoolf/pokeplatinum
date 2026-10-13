#include "fieldmap/fieldmap_021F2D20.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "billboard.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"

typedef struct FieldEffectRenderer13Context_t {
    FieldEffectManager *fieldEffectManager;
} FieldEffectRenderer13Context;

typedef struct {
    int x;
    int y;
    int z;
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer13Context *context;
    MapObject *mapObject;
} FieldEffectRenderer13Params;

typedef struct {
    int state;
    int graphicsID;
    int localID;
    int mapHeaderID;
    int unk_10;
    int groundHeight;
    FieldEffectRenderer13Params params;
    Billboard *billboard;
} FieldEffectRenderer13Anim;

typedef struct {
    int x;
    int z;
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer13Context *context;
} FieldEffectRenderer13Params2;

typedef struct {
    int state;
    int done;
    FieldEffectRenderer13Params2 params;
    Billboard *billboard;
} FieldEffectRenderer13Anim2;

typedef struct {
    int x;
    int z;
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer13Context *context;
} FieldEffectRenderer13Params3;

typedef struct {
    int state;
    int variant;
    int unk_08;
    int effectVariant;
    FieldEffectRenderer13Params3 params;
    Billboard *billboard;
} FieldEffectRenderer13Anim3;

void include_unk_FieldMap_02200500(void);

static void FieldMap_021F2D4C(FieldEffectRenderer13Context *param0);
static void FieldMap_021F2E2C(FieldEffectRenderer13Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022004EC;
const BillboardAnim Unk_FieldMap_02200540[];
const BillboardAnim Unk_FieldMap_02200558[];
const BillboardAnim Unk_FieldMap_02200528[];
const BillboardAnim Unk_FieldMap_02200570[];

void *FieldMap_021F2D20(FieldEffectManager *param0)
{
    FieldEffectRenderer13Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer13Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F2D4C(v0);
    return v0;
}

void FieldMap_021F2D3C(void *param0)
{
    FieldEffectRenderer13Context *v0 = param0;

    FieldMap_021F2E2C(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F2D4C(FieldEffectRenderer13Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 0, 83);
    FieldMap_021DF9E0(param0->fieldEffectManager, 5, 84);

    FieldMap_021DFA14(param0->fieldEffectManager, 0, 170);
    FieldMap_021DFA14(param0->fieldEffectManager, 3, 171);
    FieldMap_021DFA14(param0->fieldEffectManager, 4, 172);
    FieldMap_021DFA14(param0->fieldEffectManager, 5, 173);

    FieldMap_021DFA3C(param0->fieldEffectManager, 0, 0, 1);
    FieldMap_021DFA3C(param0->fieldEffectManager, 4, 1, 1);
    FieldMap_021DFA3C(param0->fieldEffectManager, 5, 2, 1);
    FieldMap_021DFA3C(param0->fieldEffectManager, 6, 3, 1);

    FieldMap_021DF864(param0->fieldEffectManager, 0, 0, 0, 0, 0, Unk_FieldMap_02200540);
    FieldMap_021DF864(param0->fieldEffectManager, 5, 5, 3, 4, 0, Unk_FieldMap_02200558);
    FieldMap_021DF864(param0->fieldEffectManager, 6, 5, 4, 5, 0, Unk_FieldMap_02200528);
    FieldMap_021DF864(param0->fieldEffectManager, 7, 5, 5, 6, 0, Unk_FieldMap_02200570);
}

static void FieldMap_021F2E2C(FieldEffectRenderer13Context *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 0);
    FieldMap_021DFA08(param0->fieldEffectManager, 5);

    FieldMap_021DFA30(param0->fieldEffectManager, 0);
    FieldMap_021DFA30(param0->fieldEffectManager, 3);

    FieldMap_021DFA30(param0->fieldEffectManager, 4);
    FieldMap_021DFA30(param0->fieldEffectManager, 5);

    FieldMap_021DFA7C(param0->fieldEffectManager, 0);
    FieldMap_021DFA7C(param0->fieldEffectManager, 4);
    FieldMap_021DFA7C(param0->fieldEffectManager, 5);
    FieldMap_021DFA7C(param0->fieldEffectManager, 6);

    FieldMap_021DF9D4(param0->fieldEffectManager, 0);
    FieldMap_021DF9D4(param0->fieldEffectManager, 5);
    FieldMap_021DF9D4(param0->fieldEffectManager, 6);
    FieldMap_021DF9D4(param0->fieldEffectManager, 7);
}

void FieldMap_021F2EA4(MapObject *param0, int param1)
{
    int v0;
    VecFx32 v1;
    FieldEffectRenderer13Params v2;
    FieldEffectManager *v3;
    OverworldAnimManager *v4;

    v3 = MapObject_GetFieldEffectManager(param0);

    v2.x = MapObject_GetX(param0);
    v2.y = MapObject_GetY(param0);
    v2.z = MapObject_GetZ(param0);
    v2.fieldEffectManager = v3;
    v2.fieldSystem = FieldEffectManager_GetFieldSystem(v3);
    v2.context = FieldEffectManager_GetRendererContext(v3, 19);
    v2.mapObject = param0;

    MapObject_GetPosPtr(param0, &v1);

    v0 = MapObject_CalculateTaskPriority(param0, 2);
    v4 = FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_022004EC, &v1, param1, &v2, v0);
}

static int FieldMap_021F2F0C(OverworldAnimManager *param0, void *param1)
{
    int v0, v1;
    VecFx32 v2;
    FieldEffectRenderer13Anim *v3;
    const FieldEffectRenderer13Params *v4;

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

    v3->billboard = FieldMap_021DF84C(v3->params.fieldEffectManager, 0, &v2);

    if (OverworldAnimManager_GetUserInt(param0) == 0) {
        v3->state = 1;
    }

    return 1;
}

static void FieldMap_021F2FA0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer13Anim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F2FAC(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer13Anim *v1 = param1;
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
        v0 = Billboard_GetAnimFrameNum(v1->billboard) / FX32_ONE;

        if (v0 >= 12) {
            v1->state = 1;
        }
        break;
    case 1:
        Billboard_SetFrameNum(v1->billboard, (12 * FX32_ONE));
        v1->state = 2;
    case 2:
        if (MapObject_MatchesGraphicsAndLocalID(v2, v1->graphicsID, v1->localID, v1->mapHeaderID) == 0) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }

        {
            int v5, v6;

            v5 = MapObject_GetX(v2);
            v6 = MapObject_GetZ(v2);

            if ((v1->params.x != v5) || (v1->params.z != v6)) {
                FieldEffectManager_FinishAnimManager(param0);
                return;
            }
        }
        break;
    }
}

static void FieldMap_021F308C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer13Anim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;

    if (MapObject_MatchesGraphicsAndLocalID(v2, v1->graphicsID, v1->localID, v1->mapHeaderID) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    OverworldAnimManager_GetPosition(param0, &v0);
    Billboard_SetPos(v1->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022004EC = {
    (sizeof(FieldEffectRenderer13Anim)),
    FieldMap_021F2F0C,
    FieldMap_021F2FA0,
    FieldMap_021F2FAC,
    FieldMap_021F308C
};

static const BillboardAnim Unk_FieldMap_02200540[] = {
    { 0x0, 0xC, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const OverworldAnimManagerFuncs Unk_FieldMap_02200500;

void include_unk_FieldMap_02200500(void)
{
    int dummy = Unk_FieldMap_02200500.ctxSize;
}

static int FieldMap_021F30C4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer13Anim2 *v1;
    const FieldEffectRenderer13Params2 *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);
    v1->params = *v2;

    OverworldAnimManager_GetPosition(param0, &v0);
    v1->billboard = FieldMap_021DF84C(v1->params.fieldEffectManager, 0, &v0);

    return 1;
}

static void FieldMap_021F30FC(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer13Anim2 *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F3108(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer13Anim2 *v1 = param1;

    switch (v1->state) {
    case 0:
        Billboard_AdvanceAnim(v1->billboard, FX32_ONE);
        v0 = Billboard_GetAnimFrameNum(v1->billboard) / FX32_ONE;

        if (v0 >= 12) {
            v1->done = 1;
            v1->state = 1;
        }
        break;
    case 1:
        break;
    }
}

static void FieldMap_021F313C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer13Anim2 *v1 = param1;
    OverworldAnimManager_GetPosition(param0, &v0);
    Billboard_SetPos(v1->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200500 = {
    (sizeof(FieldEffectRenderer13Anim2)),
    FieldMap_021F30C4,
    FieldMap_021F30FC,
    FieldMap_021F3108,
    FieldMap_021F313C
};

static const OverworldAnimManagerFuncs Unk_FieldMap_02200514;

static const BillboardAnim Unk_FieldMap_02200558[] = {
    { 0x0, 0x28, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_FieldMap_02200528[] = {
    { 0x0, 0x18, 0x1 },
    { 0x0, 0x0, 0x2 }
};

static const BillboardAnim Unk_FieldMap_02200570[] = {
    { 0x0, 0x28, 0x1 },
    { 0x0, 0x0, 0x2 }
};

OverworldAnimManager *FieldMap_021F3154(FieldSystem *fieldSystem, int param1, int param2, int param3)
{
    VecFx32 v0;
    FieldEffectRenderer13Params3 v1;
    FieldEffectManager *v2;
    OverworldAnimManager *v3;

    v2 = fieldSystem->fieldEffMan;

    v1.x = param1;
    v1.z = param2;
    v1.fieldEffectManager = v2;
    v1.fieldSystem = fieldSystem;
    v1.context = FieldEffectManager_GetRendererContext(v2, 19);

    v0.x = (((param1) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);
    v0.y = 0;
    v0.z = (((param2) << 4) * FX32_ONE) + ((((16 * FX32_ONE) >> 1) + (FX32_ONE * 6) + (FX32_ONE * 4)) / 2);

    v3 = FieldEffectManager_InitAnimManager(v2, &Unk_FieldMap_02200514, &v0, param3, &v1, 0xff);
    return v3;
}

int FieldMap_021F31A8(OverworldAnimManager *param0)
{
    FieldEffectRenderer13Anim3 *v0 = OverworldAnimManager_GetFuncsContext(param0);
    return v0->variant;
}

static int FieldMap_021F31B4(OverworldAnimManager *param0, void *param1)
{
    int v0;
    VecFx32 v1;
    FieldEffectRenderer13Anim3 *v2;
    const FieldEffectRenderer13Params3 *v3;

    v2 = param1;
    v3 = OverworldAnimManager_GetUserData(param0);
    v2->params = *v3;
    v2->effectVariant = OverworldAnimManager_GetUserInt(param0);

    v1.x = (((v2->params.x) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);
    v1.z = (((v2->params.z) << 4) * FX32_ONE) + ((((16 * FX32_ONE) >> 1) + (FX32_ONE * 6) + (FX32_ONE * 4)) / 2);

    v1.y = 0;
    MapObject_RecalculatePositionHeight(v2->params.fieldSystem, &v1);
    v1.y += (FX32_ONE);

    OverworldAnimManager_SetPosition(param0, &v1);

    switch (v2->effectVariant) {
    case 0:
        v0 = 5;
        break;
    case 1:
        v0 = 6;
        break;
    case 2:
    default:
        v0 = 7;
    }

    v2->billboard = FieldMap_021DF84C(v2->params.fieldEffectManager, v0, &v1);
    return 1;
}

static void FieldMap_021F3238(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer13Anim3 *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F3244(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer13Anim3 *v1 = param1;

    switch (v1->state) {
    case 0:
        if (Billboard_AdvanceAnim(v1->billboard, FX32_ONE) == 1) {
            v1->variant = 1;
            v1->state++;
        }
        break;
    case 1:
        break;
    }
}

static void FieldMap_021F326C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer13Anim3 *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Billboard_SetPos(v1->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200514 = {
    (sizeof(FieldEffectRenderer13Anim3)),
    FieldMap_021F31B4,
    FieldMap_021F3238,
    FieldMap_021F3244,
    FieldMap_021F326C
};
