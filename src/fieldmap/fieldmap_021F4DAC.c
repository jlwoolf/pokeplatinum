#include "fieldmap/fieldmap_021F4DAC.h"

#include <nitro.h>
#include <string.h>

#include "fieldmap/field_effect_manager.h"

#include "simple3d.h"

typedef struct {
    FieldEffectManager *fieldEffectManager;
    Simple3DModel model;
    Simple3DRenderObj renderObj;
} FieldEffectRenderer02Context;

static void FieldMap_021F4DD8(FieldEffectRenderer02Context *param0);
static void FieldMap_021F4DFC(FieldEffectRenderer02Context *param0);

void *FieldMap_021F4DAC(FieldEffectManager *param0)
{
    FieldEffectRenderer02Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer02Context)), 0, 0);
    v0->fieldEffectManager = param0;

    FieldMap_021F4DD8(v0);

    return v0;
}

void FieldMap_021F4DC8(void *param0)
{
    FieldEffectRenderer02Context *v0 = param0;

    FieldMap_021F4DFC(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F4DD8(FieldEffectRenderer02Context *param0)
{
    FieldEffectManager_LoadModel(param0->fieldEffectManager, &param0->model, 0, 17, 0);
    Simple3D_CreateRenderObject(&param0->renderObj, &param0->model);
}

static void FieldMap_021F4DFC(FieldEffectRenderer02Context *param0)
{
    Simple3D_FreeModel(&param0->model);
}
