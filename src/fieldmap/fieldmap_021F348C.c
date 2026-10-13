#include "fieldmap/fieldmap_021F348C.h"

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
    u32 loaded;
    FieldEffectManager *fieldEffectManager;
} FieldEffectRenderer17Context;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer17Context *context;
    MapObject *mapObject;
} FieldEffectRenderer17Params;

typedef struct {
    int animIndex;
    int localID;
    int mapHeaderID;
    int unk_0C;
    FieldEffectRenderer17Params params;
    Billboard *billboard;
} FieldEffectRenderer17Anim;

static void FieldMap_021F34D0(FieldEffectRenderer17Context *param0);
static void FieldMap_021F3518(FieldEffectRenderer17Context *param0);
static void FieldMap_021F358C(FieldEffectRenderer17Context *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_022005C4;
const BillboardAnim Unk_FieldMap_022005D8[];

void *FieldMap_021F348C(FieldEffectManager *param0)
{
    FieldEffectRenderer17Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer17Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F34D0(v0);
    return v0;
}

void FieldMap_021F34A8(void *param0)
{
    FieldEffectRenderer17Context *v0 = param0;

    FieldMap_021F358C(v0);
    FieldEffectManager_HeapFree(v0);
}

void FieldMap_021F34B8(FieldEffectManager *param0)
{
    FieldEffectRenderer17Context *v0 = FieldEffectManager_GetRendererContext(param0, 23);

    if (v0->loaded != 1) {
        v0->loaded = 1;
        FieldMap_021F3518(v0);
    }
}

static void FieldMap_021F34D0(FieldEffectRenderer17Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 6, 88);
    FieldMap_021DFA14(param0->fieldEffectManager, 6, 175);
    FieldMap_021DFA3C(param0->fieldEffectManager, 7, 7, 1);
    FieldMap_021DF864(param0->fieldEffectManager, 8, 6, 6, 7, 0, Unk_FieldMap_022005D8);
}

static void FieldMap_021F3518(FieldEffectRenderer17Context *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 12, 159);
    FieldMap_021DF9E0(param0->fieldEffectManager, 13, 157);
    FieldMap_021DF9E0(param0->fieldEffectManager, 14, 158);

    FieldMap_021DF864(param0->fieldEffectManager, 14, 12, 6, 7, 0, Unk_FieldMap_022005D8);
    FieldMap_021DF864(param0->fieldEffectManager, 15, 13, 6, 7, 0, Unk_FieldMap_022005D8);
    FieldMap_021DF864(param0->fieldEffectManager, 16, 14, 6, 7, 0, Unk_FieldMap_022005D8);
}

static void FieldMap_021F358C(FieldEffectRenderer17Context *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 6);
    FieldMap_021DFA30(param0->fieldEffectManager, 6);
    FieldMap_021DFA7C(param0->fieldEffectManager, 7);
    FieldMap_021DF9D4(param0->fieldEffectManager, 8);

    if (param0->loaded == 1) {
        FieldMap_021DFA08(param0->fieldEffectManager, 12);
        FieldMap_021DFA08(param0->fieldEffectManager, 13);
        FieldMap_021DFA08(param0->fieldEffectManager, 14);
        FieldMap_021DF9D4(param0->fieldEffectManager, 14);
        FieldMap_021DF9D4(param0->fieldEffectManager, 15);
        FieldMap_021DF9D4(param0->fieldEffectManager, 16);
    }
}

static void FieldMap_021F35E8(FieldEffectManager *param0, MapObject *param1, FieldEffectRenderer17Params *param2, VecFx32 *param3, int *param4)
{
    param2->fieldSystem = MapObject_FieldSystem(param1);
    param2->fieldEffectManager = param0;
    param2->context = FieldEffectManager_GetRendererContext(param0, 23);
    param2->mapObject = param1;

    MapObject_GetPosPtr(param1, param3);
    VecFx32_SetPosFromMapCoords(MapObject_GetX(param1), MapObject_GetZ(param1), param3);

    *param4 = MapObject_CalculateTaskPriority(param1, 2);
}

void FieldMap_021F3638(MapObject *param0)
{
    int v0;
    FieldEffectManager *v1;
    OverworldAnimManager *v2;
    VecFx32 v3;
    FieldEffectRenderer17Params v4;

    v1 = MapObject_GetFieldEffectManager(param0);
    FieldMap_021F35E8(v1, param0, &v4, &v3, &v0);
    v3.z += (FX32_ONE * 8);
    v2 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_022005C4, &v3, 0, &v4, v0);
}

void FieldMap_021F3678(MapObject *param0, int param1)
{
    int v0;
    FieldEffectManager *v1;
    OverworldAnimManager *v2;
    VecFx32 v3;
    FieldEffectRenderer17Params v4;
    VecFx32 v5[4] = {
        {
            0,
            0,
            (FX32_ONE * 8),
        },
        {
            (FX32_ONE * 11),
            (FX32_ONE * 14),
            (FX32_ONE * 17),
        },
        {
            (FX32_ONE * -11),
            (FX32_ONE * 14),
            (FX32_ONE * 17),
        },
        {
            0,
            (FX32_ONE * 32),
            (FX32_ONE * 8),
        },
    };

    v1 = MapObject_GetFieldEffectManager(param0);

    FieldMap_021F35E8(v1, param0, &v4, &v3, &v0);
    GF_ASSERT(v4.context->loaded == 1);

    v3.x += v5[param1].x;
    v3.y += v5[param1].y;
    v3.z += v5[param1].z;

    v2 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_022005C4, &v3, param1, &v4, v0);
}

static int FieldMap_021F36F4(OverworldAnimManager *param0, void *param1)
{
    int v0;
    VecFx32 v1;
    FieldEffectRenderer17Anim *v2;
    const FieldEffectRenderer17Params *v3;

    v2 = param1;
    v3 = OverworldAnimManager_GetUserData(param0);

    v2->params = *v3;
    v2->localID = MapObject_GetLocalID(v2->params.mapObject);
    v2->mapHeaderID = MapObject_GetMapHeaderID(v2->params.mapObject);

    OverworldAnimManager_GetPosition(param0, &v1);

    {
        u32 v4[4] = { 8, 14, 15, 16 };
        int v5 = OverworldAnimManager_GetUserInt(param0);

        v2->billboard = FieldMap_021DF84C(v2->params.fieldEffectManager, v4[v5], &v1);
    }

    return 1;
}

static void FieldMap_021F3754(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer17Anim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F3760(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer17Anim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;

    switch (v1->animIndex) {
    case 0:
        Billboard_AdvanceAnim(v1->billboard, FX32_ONE);
        v0 = Billboard_GetAnimFrameNum(v1->billboard) / FX32_ONE;

        if (v0 >= 9) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
        break;
    }
}

static void FieldMap_021F3790(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0, v1;
    FieldEffectRenderer17Anim *v2 = param1;
    MapObject *v3 = v2->params.mapObject;

    OverworldAnimManager_GetPosition(param0, &v0);
    Billboard_SetPos(v2->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_022005C4 = {
    (sizeof(FieldEffectRenderer17Anim)),
    FieldMap_021F36F4,
    FieldMap_021F3754,
    FieldMap_021F3760,
    FieldMap_021F3790
};

static const BillboardAnim Unk_FieldMap_022005D8[] = {
    { 0x0, 0x9, 0x1 },
    { 0x0, 0x0, 0x2 }
};
