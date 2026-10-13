#include "fieldmap/fieldmap_021F5060.h"

#include <nitro.h>
#include <string.h>

#include "fieldmap/field_effect_manager.h"

#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DRenderObj renderObj;
} FieldEffectRenderer04Context;

static void FieldMap_021F508C(FieldEffectRenderer04Context *param0);
static void FieldMap_021F50B0(FieldEffectRenderer04Context *param0);

void *FieldMap_021F5060(FieldEffectManager *param0)
{
    FieldEffectRenderer04Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer04Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F508C(v0);

    return v0;
}

void FieldMap_021F507C(void *param0)
{
    FieldEffectRenderer04Context *v0 = param0;

    FieldMap_021F50B0(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F508C(FieldEffectRenderer04Context *param0)
{
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 21, 0);
    Simple3D_CreateRenderObject(&param0->renderObj, &param0->model);
}

static void FieldMap_021F50B0(FieldEffectRenderer04Context *param0)
{
    Simple3D_FreeModel(&param0->model);
}
