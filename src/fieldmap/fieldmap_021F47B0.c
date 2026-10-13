#include "fieldmap/fieldmap_021F47B0.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "heap.h"
#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel models[9];
    Simple3DAnimation anims[1];
} FieldEffectRenderer20Context;

typedef struct {
    int distance;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer20Context *context;
    const MapObject *mapObject;
} FieldEffectRenderer20Params;

typedef struct {
    s8 direction;
    s8 distance;
    u8 visible;
    u8 unk_03;
    VecFx32 startOffset;
    VecFx32 endOffset;
    Simple3DRotationAngles rotationAngles;
    FieldEffectRenderer20Params params;
    Simple3DRenderObj renderObj;
    Simple3DAnimation *anim;
} FieldEffectRenderer20Anim;

typedef struct {
    int distance;
    FieldEffectManager *fieldEffectManager;
    FieldEffectRenderer20Context *context;
    Simple3DRenderObj renderObj;
} FieldEffectRenderer20Anim2;

static void FieldMap_021F47DC(FieldEffectRenderer20Context *param0);
static void FieldMap_021F4820(FieldEffectRenderer20Context *param0);
static void FieldMap_021F49D0(OverworldAnimManager *param0, FieldEffectRenderer20Anim *param1);
static void FieldMap_021F4A24(OverworldAnimManager *param0, FieldEffectRenderer20Anim *param1);
static void FieldMap_021F4A80(u16 *param0, s16 param1);
static int FieldMap_021F4AB4(const MapObject *param0, int param1, VecFx32 *param2);
static void FieldMap_021F4B6C(int param0, int param1, const VecFx32 *param2, const VecFx32 *param3, VecFx32 *param4, VecFx32 *param5);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200754;
static const OverworldAnimManagerFuncs Unk_FieldMap_02200768;
static const u32 Unk_FieldMap_0220079C[9];
static const u32 Unk_FieldMap_02200750[1];
static const Simple3DRotationAngles Unk_FieldMap_0220077C[4];
static const VecFx32 Unk_FieldMap_022007C0[4][6];
static const VecFx32 Unk_FieldMap_022008E0[4][6];

void *FieldMap_021F47B0(FieldEffectManager *param0)
{
    FieldEffectRenderer20Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer20Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F47DC(v0);
    return v0;
}

void FieldMap_021F47CC(void *param0)
{
    FieldEffectRenderer20Context *v0 = param0;

    FieldMap_021F4820(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F47DC(FieldEffectRenderer20Context *param0)
{
    int v0;

    for (v0 = 0; v0 < 9; v0++) {
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->models[v0], 0, Unk_FieldMap_0220079C[v0], 0);
    }

    NNS_G3dMdlSetMdlFogEnableFlagAll(param0->models[0].g3DModel, 0);

    for (v0 = 0; v0 < 1; v0++) {
        FieldEffectManager_LoadAnimation(param0->fieldEffectManager, &param0->anims[v0], 0, Unk_FieldMap_02200750[v0], 0);
    }
}

static void FieldMap_021F4820(FieldEffectRenderer20Context *param0)
{
    int v0;

    for (v0 = 0; v0 < 9; v0++) {
        Simple3D_FreeModel(&param0->models[v0]);
    }

    for (v0 = 0; v0 < 1; v0++) {
        Simple3D_FreeAnimation(&param0->anims[v0]);
    }
}

OverworldAnimManager *FieldMap_021F4840(FieldEffectManager *param0, const MapObject *param1, int param2, int param3)
{
    int v0;
    OverworldAnimManager *v1;
    FieldEffectRenderer20Params v2;

    v2.distance = param2;
    v2.fieldEffectManager = param0;
    v2.context = FieldEffectManager_GetRendererContext(param0, 32);
    v2.mapObject = param1;

    v0 = MapObject_CalculateTaskPriority(param1, param3);
    v1 = FieldEffectManager_InitAnimManager(param0, &Unk_FieldMap_02200754, NULL, 0, &v2, v0);

    return v1;
}

static int FieldMap_021F487C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer20Anim *v0 = param1;
    const FieldEffectRenderer20Params *v1 = OverworldAnimManager_GetUserData(param0);

    v0->params = *v1;
    v0->direction = MapObject_GetFacingDir(v1->mapObject);
    v0->anim = FieldEffectManager_HeapAlloc(v1->fieldEffectManager, sizeof(Simple3DAnimation), 0);

    Simple3D_CreateRenderObject(&v0->renderObj, &v0->params.context->models[0]);
    FieldEffectManager_ApplyAnimCopyToModel(v0->params.fieldEffectManager, v0->anim, &v0->params.context->models[0], &v0->params.context->anims[0], 0);
    Simple3D_BindAnimToRenderObj(&v0->renderObj, v0->anim);
    FieldMap_021F4A24(param0, v0);

    return 1;
}

static void FieldMap_021F48F0(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer20Anim *v0 = param1;

    Simple3D_FreeAnimObject(v0->anim);
    Heap_Free(v0->anim);
}

static void FieldMap_021F4908(OverworldAnimManager *param0, void *param1)
{
    int v0;
    VecFx32 v1, v2;
    const VecFx32 *v3;
    FieldEffectRenderer20Anim *v4 = param1;
    const MapObject *v5 = v4->params.mapObject;
    int v6 = MapObject_GetFacingDir(v5);

    MapObject_GetPosPtr(v5, &v2);

    v0 = FieldMap_021F4AB4(v5, v4->params.distance, &v1);

    v4->direction = v6;
    v4->distance = v0;

    if (v4->distance == v4->params.distance) {
        FieldMap_021F4A24(param0, v4);
    } else {
        FieldMap_021F4B6C(v4->direction, v4->params.distance, &v1, &v2, &v4->startOffset, &v4->endOffset);
        FieldMap_021F49D0(param0, v4);
    }

    Simple3D_UpdateAnim(v4->anim, FX32_ONE, 1);
}

static void FieldMap_021F4974(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer20Anim *v0 = param1;

    if (v0->visible == 0) {
        Simple3DRotationAngles v1;
        VecFx32 v2;

        OverworldAnimManager_GetPosition(param0, &v2);

        v2.x += 0;
        v2.y += (FX32_ONE * 16);
        v2.z += (FX32_ONE * 0);

        v1 = v0->rotationAngles;

        FieldMap_021F4A80(&v1.alpha, 0);
        FieldMap_021F4A80(&v1.beta, 0);
        FieldMap_021F4A80(&v1.gamma, 0);

        Simple3D_DrawRenderObjRotationAngles(&v0->renderObj, &v2, &v0->endOffset, &v1);
    }
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200754 = {
    sizeof(FieldEffectRenderer20Anim),
    FieldMap_021F487C,
    FieldMap_021F48F0,
    FieldMap_021F4908,
    FieldMap_021F4974
};

static void FieldMap_021F49D0(OverworldAnimManager *param0, FieldEffectRenderer20Anim *param1)
{
    VecFx32 v0;
    const MapObject *v1 = param1->params.mapObject;

    param1->rotationAngles = Unk_FieldMap_0220077C[param1->direction];
    MapObject_GetPosPtr(param1->params.mapObject, &v0);

    v0.x += param1->startOffset.x;
    v0.y += param1->startOffset.y;
    v0.z += param1->startOffset.z;

    OverworldAnimManager_SetPosition(param0, &v0);
}

static void FieldMap_021F4A24(OverworldAnimManager *param0, FieldEffectRenderer20Anim *param1)
{
    VecFx32 v0;
    const MapObject *v1 = param1->params.mapObject;

    param1->endOffset = Unk_FieldMap_022007C0[param1->direction][param1->distance];
    param1->startOffset = Unk_FieldMap_022008E0[param1->direction][param1->distance];

    FieldMap_021F49D0(param0, param1);
}

static void FieldMap_021F4A80(u16 *param0, s16 param1)
{
    (*param0) += param1;

    if ((s16)(*param0) < 0) {
        do {
            (*param0) += 360;
        } while ((s16)(*param0) < 0);
    } else {
        (*param0) %= 360;
    }
}

static int FieldMap_021F4AB4(const MapObject *param0, int param1, VecFx32 *param2)
{
    u32 v0;
    VecFx32 v1;
    int v2, v3, v4, v5, v6;

    GF_ASSERT(param1);

    v4 = MapObject_GetX(param0);
    v5 = MapObject_GetY(param0);
    v6 = MapObject_GetZ(param0);
    v3 = MapObject_GetFacingDir(param0);

    MapObject_GetPosPtr(param0, &v1);

    for (v2 = 0; v2 < param1; v2++) {
        v4 += MapObject_GetDxFromDir(v3);
        v6 += MapObject_GetDzFromDir(v3);

        v0 = MapObject_CheckCollisionAtPos(param0, &v1, v4, v5, v6, v3);

        if ((v0 != 0) && (v0 != (1 << 0))) {
            if (v0 == (1 << 2)) {
                MapObject *v7;

                v7 = MapObjectMan_FindObjectAtCoords(MapObject_MapObjectManager(param0), v4, v6, 1);
                GF_ASSERT(v7 != NULL);
                MapObject_GetPosPtr(v7, param2);
            } else {
                VecFx32_SetPosFromMapCoords(v4, v6, param2);
            }

            return v2;
        }
    }

    VecFx32_SetPosFromMapCoords(v4, v6, param2);
    return v2;
}

static void FieldMap_021F4B6C(int param0, int param1, const VecFx32 *param2, const VecFx32 *param3, VecFx32 *param4, VecFx32 *param5)
{
    fx32 v0;
    int v1, v2, v3;
    const VecFx32 *v4, *v5;

    switch (param0) {
    case 0:
        v0 = (param3->z - param2->z);
        break;
    case 1:
        v0 = (param2->z - param3->z);
        break;
    case 2:
        v0 = (param3->x - param2->x);
        break;
    case 3:
        v0 = (param2->x - param3->x);
        break;
    }

    v1 = v0 / (16 * FX32_ONE);

    if (v1 < 0) {
        v1 = -v1;
    }

    if (v1 > param1) {
        v1 = param1;
    }

    v1--;

    if (v1 < 0) {
        v1 = 0;
    }

    v2 = v1;
    v0 %= (16 * FX32_ONE);

    if (v0 < 0) {
        v2--;
    } else if (v0 > 0) {
        v2++;
    }

    if (v2 < 0) {
        v2 = 0;
    } else if (v2 > param1) {
        v2 = param1;
    }

    v3 = v0 / ((16 * FX32_ONE) / 10);

    if (v3 < 0) {
        v3 = -v3;
    }

    v5 = &Unk_FieldMap_022008E0[param0][v2];
    *param4 = Unk_FieldMap_022008E0[param0][v1];

    v4 = &Unk_FieldMap_022007C0[param0][v2];
    *param5 = Unk_FieldMap_022007C0[param0][v1];

    param4->x += ((v5->x - param4->x) / 10) * v3;
    param4->y += ((v5->y - param4->y) / 10) * v3;
    param4->z += ((v5->z - param4->z) / 10) * v3;
    param5->x += ((v4->x - param5->x) / 10) * v3;
    param5->y += ((v4->y - param5->y) / 10) * v3;
    param5->z += ((v4->z - param5->z) / 10) * v3;
}

OverworldAnimManager *FieldMap_021F4CEC(FieldEffectManager *param0, int param1, int param2, int param3)
{
    OverworldAnimManager *v0;
    VecFx32 v1 = { 0, 0, 0 };

    GF_ASSERT(param3 < 8);

    VecFx32_SetPosFromMapCoords(param1, param2, &v1);
    MapObject_RecalculatePositionHeight(FieldEffectManager_GetFieldSystem(param0), &v1);

    v1.x += (FX32_ONE * 0);
    v1.y += (FX32_ONE * -3);
    v1.z += (FX32_ONE * -4);

    v0 = FieldEffectManager_InitAnimManager(param0, &Unk_FieldMap_02200768, &v1, param3, param0, 0);
    return v0;
}

static int FieldMap_021F4D50(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer20Anim2 *v0 = param1;

    v0->distance = OverworldAnimManager_GetUserInt(param0);
    v0->fieldEffectManager = (FieldEffectManager *)OverworldAnimManager_GetUserData(param0);
    v0->context = FieldEffectManager_GetRendererContext(v0->fieldEffectManager, 32);

    Simple3D_CreateRenderObject(&v0->renderObj, &v0->context->models[1 + v0->distance]);
    return 1;
}

static void FieldMap_021F4D88(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F4D8C(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F4D90(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer20Anim2 *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->renderObj, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200768 = {
    sizeof(FieldEffectRenderer20Anim2),
    FieldMap_021F4D50,
    FieldMap_021F4D88,
    FieldMap_021F4D8C,
    FieldMap_021F4D90
};

static const u32 Unk_FieldMap_0220079C[9] = {
    0x73,
    0x74,
    0x75,
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B
};

static const u32 Unk_FieldMap_02200750[1] = {
    0xC7
};

static const Simple3DRotationAngles Unk_FieldMap_0220077C[4] = {
    { 0x10E, 0xB4, 0x0 },
    { 0x5A, 0xB4, 0xB4 },
    { 0x0, 0x10E, 0x10E },
    { 0x0, 0x5A, 0x5A }
};

static const VecFx32 Unk_FieldMap_022007C0[4][6] = {
    {
        { 0xC00, 0x100, 0x1000 },
        { 0x1000, 0x500, 0x1000 },
        { 0x1000, 0x800, 0x1000 },
        { 0x1000, 0xC00, 0x1000 },
        { 0x1000, 0x1000, 0x1000 },
        { 0x1000, 0x1400, 0x1000 },
    },
    {
        { 0xC00, 0x100, 0x1000 },
        { 0x1000, 0x500, 0x1000 },
        { 0x1000, 0x800, 0x1000 },
        { 0x1000, 0xC00, 0x1000 },
        { 0x1000, 0x1000, 0x1000 },
        { 0x1000, 0x1400, 0x1000 },
    },
    {
        { 0x1000, 0x200, 0x1000 },
        { 0x1000, 0x600, 0x1000 },
        { 0x1000, 0xA00, 0x1000 },
        { 0x1000, 0xE00, 0x1000 },
        { 0x1000, 0x1200, 0x1000 },
        { 0x1000, 0x1400, 0x1000 },
    },
    {
        { 0x1000, 0x200, 0x1000 },
        { 0x1000, 0x600, 0x1000 },
        { 0x1000, 0xA00, 0x1000 },
        { 0x1000, 0xE00, 0x1000 },
        { 0x1000, 0x1200, 0x1000 },
        { 0x1000, 0x1400, 0x1000 },
    },
};

static const VecFx32 Unk_FieldMap_022008E0[4][6] = {
    {
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -15) },
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -31) },
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -47) },
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -63) },
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -79) },
        { (FX32_ONE * 0), (FX32_ONE * -15), (FX32_ONE * -95) },
    },
    {
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 13) },
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 27) },
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 44) },
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 60) },
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 78) },
        { (FX32_ONE * 0), (FX32_ONE * 0), (FX32_ONE * 93) },
    },
    {
        { (FX32_ONE * -13), (FX32_ONE * 0), (FX32_ONE * 6) },
        { (FX32_ONE * -29), (FX32_ONE * 0), (FX32_ONE * 9) },
        { (FX32_ONE * -45), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * -61), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * -78), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * -85), (FX32_ONE * 0), (FX32_ONE * 10) },
    },
    {
        { (FX32_ONE * 13), (FX32_ONE * 0), (FX32_ONE * 6) },
        { (FX32_ONE * 29), (FX32_ONE * 0), (FX32_ONE * 9) },
        { (FX32_ONE * 45), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * 61), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * 78), (FX32_ONE * 0), (FX32_ONE * 10) },
        { (FX32_ONE * 85), (FX32_ONE * 0), (FX32_ONE * 10) },
    },
};
