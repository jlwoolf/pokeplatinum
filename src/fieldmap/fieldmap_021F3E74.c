#include "fieldmap/fieldmap_021F3E74.h"

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
} FieldEffectRenderer1BContext;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer1BContext *context;
    MapObject *mapObject;
} FieldEffectRenderer1BParams;

typedef struct {
    int animIndex;
    int localID;
    int mapHeaderID;
    int unk_0C;
    FieldEffectRenderer1BParams params;
    Billboard *billboard;
} FieldEffectRenderer1BAnim;

static void FieldMap_021F3EA0(FieldEffectRenderer1BContext *param0);
static void FieldMap_021F3EE8(FieldEffectRenderer1BContext *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_0220069C;
const BillboardAnim Unk_FieldMap_022006B0[];

void *FieldMap_021F3E74(FieldEffectManager *param0)
{
    FieldEffectRenderer1BContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer1BContext)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F3EA0(v0);
    return v0;
}

void FieldMap_021F3E90(void *param0)
{
    FieldEffectRenderer1BContext *v0 = param0;

    FieldMap_021F3EE8(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F3EA0(FieldEffectRenderer1BContext *param0)
{
    FieldMap_021DF9E0(param0->fieldEffectManager, 9, 107);
    FieldMap_021DFA14(param0->fieldEffectManager, 9, 180);
    FieldMap_021DFA3C(param0->fieldEffectManager, 10, 12, 1);

    FieldMap_021DF864(param0->fieldEffectManager, 11, 9, 9, 10, 0, Unk_FieldMap_022006B0);
}

static void FieldMap_021F3EE8(FieldEffectRenderer1BContext *param0)
{
    FieldMap_021DFA08(param0->fieldEffectManager, 9);
    FieldMap_021DFA30(param0->fieldEffectManager, 9);
    FieldMap_021DFA7C(param0->fieldEffectManager, 10);
    FieldMap_021DF9D4(param0->fieldEffectManager, 11);
}

void FieldMap_021F3F10(MapObject *param0)
{
    FieldEffectRenderer1BParams v0;
    FieldEffectManager *v1;
    OverworldAnimManager *v2;
    VecFx32 v3;
    int v4;

    v1 = MapObject_GetFieldEffectManager(param0);

    v0.fieldSystem = MapObject_FieldSystem(param0);
    v0.fieldEffectManager = v1;
    v0.context = FieldEffectManager_GetRendererContext(v1, 27);
    v0.mapObject = param0;

    MapObject_GetPosPtr(param0, &v3);
    VecFx32_SetPosFromMapCoords(MapObject_GetX(param0), MapObject_GetZ(param0), &v3);

    v4 = MapObject_CalculateTaskPriority(param0, 2);
    v2 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_0220069C, &v3, 0, &v0, v4);
}

static int FieldMap_021F3F74(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer1BAnim *v1;
    const FieldEffectRenderer1BParams *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);

    v1->params = *v2;
    v1->localID = MapObject_GetLocalID(v1->params.mapObject);
    v1->mapHeaderID = MapObject_GetMapHeaderID(v1->params.mapObject);

    OverworldAnimManager_GetPosition(param0, &v0);

    v1->billboard = FieldMap_021DF84C(v1->params.fieldEffectManager, 11, &v0);

    return 1;
}

static void FieldMap_021F3FB8(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer1BAnim *v0 = param1;
    Billboard_Delete(v0->billboard);
}

static void FieldMap_021F3FC4(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer1BAnim *v1 = param1;
    MapObject *v2 = v1->params.mapObject;

    switch (v1->animIndex) {
    case 0:
        Billboard_AdvanceAnim(v1->billboard, FX32_ONE);
        v0 = Billboard_GetAnimFrameNum(v1->billboard) / FX32_ONE;

        if (v0 >= 7) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
        break;
    }
}

static void FieldMap_021F3FF4(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0, v1;
    FieldEffectRenderer1BAnim *v2 = param1;
    MapObject *v3 = v2->params.mapObject;

    OverworldAnimManager_GetPosition(param0, &v0);
    v0.z += (FX32_ONE * 8);
    Billboard_SetPos(v2->billboard, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_0220069C = {
    (sizeof(FieldEffectRenderer1BAnim)),
    FieldMap_021F3F74,
    FieldMap_021F3FB8,
    FieldMap_021F3FC4,
    FieldMap_021F3FF4
};

static const BillboardAnim Unk_FieldMap_022006B0[] = {
    { 0x0, 0x7, 0x1 },
    { 0x0, 0x0, 0x2 }
};
