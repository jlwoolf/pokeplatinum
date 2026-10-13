#include "fieldmap/fieldmap_021F1CC8.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "map_object.h"
#include "map_object_move.h"
#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel modelsA[10];
    Simple3DModel modelsB[10];
    Simple3DRenderObj renderObjsA[10];
    Simple3DRenderObj renderObjsB[10];
} FieldEffectRenderer0BContext;

typedef struct {
    int variant;
    Simple3DModel *model;
    Simple3DRenderObj *renderObj;
} FieldEffectRenderer0BParams;

typedef struct {
    int state;
    int timer;
    int visible;
    int alpha;
    int variant;
    Simple3DModel *model;
    Simple3DRenderObj *renderObj;
} FieldEffectRenderer0BAnim;

static void FieldMap_021F1CF8(FieldEffectRenderer0BContext *param0);
static void FieldMap_021F1D80(FieldEffectRenderer0BContext *param0);
static Simple3DRenderObj *FieldMap_021F1DA4(FieldEffectRenderer0BContext *param0, int param1, int param2, int param3);
static Simple3DModel *FieldMap_021F1E24(FieldEffectRenderer0BContext *param0, int param1, int param2, int param3);
static OverworldAnimManager *FieldMap_021F1ECC(const MapObject *param0, int param1);

static const u32 Unk_FieldMap_0220039C[10];
static const u32 Unk_FieldMap_02200374[10];
static const int Unk_FieldMap_022003C4[4][4];
static const OverworldAnimManagerFuncs Unk_FieldMap_02200360;

void *FieldMap_021F1CC8(FieldEffectManager *param0)
{
    FieldEffectRenderer0BContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer0BContext)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F1CF8(v0);
    return v0;
}

void FieldMap_021F1CE8(void *param0)
{
    FieldEffectRenderer0BContext *v0 = param0;

    FieldMap_021F1D80(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F1CF8(FieldEffectRenderer0BContext *param0)
{
    u32 v0, v1;

    for (v0 = 0; v0 < 10; v0++) {
        v1 = Unk_FieldMap_0220039C[v0];
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->modelsA[v0], 0, v1, 0);
        Simple3D_CreateRenderObject(&param0->renderObjsA[v0], &param0->modelsA[v0]);

        v1 = Unk_FieldMap_02200374[v0];
        FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->modelsB[v0], 0, v1, 0);
        Simple3D_CreateRenderObject(&param0->renderObjsB[v0], &param0->modelsB[v0]);
    }
}

static void FieldMap_021F1D80(FieldEffectRenderer0BContext *param0)
{
    int v0;

    for (v0 = 0; v0 < 10; v0++) {
        Simple3D_FreeModel(&param0->modelsA[v0]);
        Simple3D_FreeModel(&param0->modelsB[v0]);
    }
}

static Simple3DRenderObj *FieldMap_021F1DA4(FieldEffectRenderer0BContext *param0, int param1, int param2, int param3)
{
    int v0;
    Simple3DRenderObj *v1 = NULL;

    switch (param1) {
    case 0:
        v0 = 0 + param2;
        v1 = &param0->renderObjsA[v0];
        break;
    case 1:
        v0 = Unk_FieldMap_022003C4[param3][param2];
        v1 = &param0->renderObjsA[v0];
        break;
    case 2:
    case 4:
        v0 = 0 + param2;
        v1 = &param0->renderObjsB[v0];
        break;
    case 3:
        v0 = Unk_FieldMap_022003C4[param3][param2];
        v1 = &param0->renderObjsB[v0];
        break;
    }

    GF_ASSERT(v1 != NULL);
    return v1;
}

static Simple3DModel *FieldMap_021F1E24(FieldEffectRenderer0BContext *param0, int param1, int param2, int param3)
{
    int v0 = 0;
    Simple3DModel *v1 = NULL;

    switch (param1) {
    case 0:
        v0 = 0 + param2;
        v1 = &param0->modelsA[v0];
        break;
    case 1:
        v0 = Unk_FieldMap_022003C4[param3][param2];
        v1 = &param0->modelsA[v0];
        break;
    case 2:
    case 4:
        v0 = 0 + param2;
        v1 = &param0->modelsB[v0];
        break;
    case 3:
        v0 = Unk_FieldMap_022003C4[param3][param2];
        v1 = &param0->modelsB[v0];
        break;
    }

    GF_ASSERT(v1 != NULL);
    return v1;
}

OverworldAnimManager *FieldMap_021F1E8C(const MapObject *param0)
{
    return FieldMap_021F1ECC(param0, 0);
}

OverworldAnimManager *FieldMap_021F1E98(const MapObject *param0)
{
    return FieldMap_021F1ECC(param0, 1);
}

OverworldAnimManager *FieldMap_021F1EA4(const MapObject *param0)
{
    return FieldMap_021F1ECC(param0, 2);
}

OverworldAnimManager *FieldMap_021F1EB0(const MapObject *param0)
{
    return FieldMap_021F1ECC(param0, 3);
}

OverworldAnimManager *FieldMap_021F1EBC(const MapObject *param0)
{
    return FieldMap_021F1ECC(param0, 4);
}

OverworldAnimManager *FieldMap_021F1EC8(const MapObject *param0)
{
    return NULL;
}

static OverworldAnimManager *FieldMap_021F1ECC(const MapObject *param0, int param1)
{
    VecFx32 v0;
    OverworldAnimManager *v1;
    FieldEffectRenderer0BParams v2;
    int v3 = MapObject_GetXPrev(param0);
    int v4 = MapObject_GetZPrev(param0);
    fx32 v5 = MapObject_GetPosY(param0);
    int v6 = MapObject_GetFacingDir(param0);
    int v7 = MapObject_GetPrevFacingDir(param0);
    int v8 = MapObject_CalculateTaskPriority(param0, 2);
    FieldEffectManager *v9 = MapObject_GetFieldEffectManager(param0);
    FieldEffectRenderer0BContext *v10 = FieldEffectManager_GetRendererContext(v9, 11);

    v2.variant = param1;
    v2.renderObj = FieldMap_021F1DA4(v10, param1, v6, v7);
    v2.model = FieldMap_021F1E24(v10, param1, v6, v7);

    VecFx32_SetPosFromMapCoords(v3, v4, &v0);
    v0.y = v5;

    switch (param1) {
    case 0:
    case 1:
    case 4:
    case 5:
        v0.y += (FX32_ONE * -8);

        if ((param1 == 2) || (param1 == 3)) {
            v0.z += (FX32_ONE * -2);
        } else {
            v0.z += (FX32_ONE * 1);
        }
        break;
    case 2:
    case 3:
        v0.y += (FX32_ONE * -10);

        if ((param1 == 2) || (param1 == 3)) {
            v0.z += (FX32_ONE * -2);
        } else {
            v0.z += (FX32_ONE * 2);
        }
    }

    v1 = FieldEffectManager_InitAnimManager(v9, &Unk_FieldMap_02200360, &v0, 0, &v2, v8);

    return v1;
}

static int FieldMap_021F1FB8(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    FieldEffectRenderer0BAnim *v1;
    const FieldEffectRenderer0BParams *v2;

    v1 = param1;
    v1->variant = OverworldAnimManager_GetUserInt(param0);

    v2 = OverworldAnimManager_GetUserData(param0);
    v1->renderObj = v2->renderObj;
    v1->model = v2->model;
    v1->alpha = 31;
    v1->variant = v2->variant;

    return 1;
}

static void FieldMap_021F1FE0(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F1FE4(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0BAnim *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->timer++;

        if (v0->timer >= 16) {
            v0->state++;
        }
        break;
    case 1:
        v0->alpha -= 2;

        if (v0->alpha < 0) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
    }
}

static void FieldMap_021F2014(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0BAnim *v0 = param1;

    if (v0->visible == 0) {
        VecFx32 v1;

        OverworldAnimManager_GetPosition(param0, &v1);

        NNS_G3dMdlUseMdlAlpha(v0->model->g3DModel);
        NNS_G3dMdlSetMdlAlphaAll(v0->model->g3DModel, v0->alpha);

        Simple3D_DrawRenderObjWithPos(v0->renderObj, &v1);
    }
}

static const u32 Unk_FieldMap_0220039C[10] = {
    0x3B,
    0x3C,
    0x3D,
    0x3E,
    0x3F,
    0x40,
    0x41,
    0x42,
    0x43,
    0x44
};

static const u32 Unk_FieldMap_02200374[10] = {
    0x5D,
    0x5E,
    0x5F,
    0x60,
    0x61,
    0x62,
    0x63,
    0x64,
    0x65,
    0x66
};

static const int Unk_FieldMap_022003C4[4][4] = {
    { 0x4, 0x4, 0x7, 0x6 },
    { 0x4, 0x4, 0x9, 0x8 },
    { 0x8, 0x6, 0x5, 0x5 },
    { 0x9, 0x7, 0x5, 0x5 }
};

static const OverworldAnimManagerFuncs Unk_FieldMap_02200360 = {
    (sizeof(FieldEffectRenderer0BAnim)),
    FieldMap_021F1FB8,
    FieldMap_021F1FE0,
    FieldMap_021F1FE4,
    FieldMap_021F2014
};
