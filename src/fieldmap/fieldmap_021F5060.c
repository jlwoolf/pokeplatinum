#include "fieldmap/fieldmap_021F5060.h"

#include <nitro.h>
#include <string.h>

#include "fieldmap/field_effect_manager.h"

#include "simple3d.h"

typedef struct {
    FieldEffectManager *unk_00;
    Simple3DModel unk_04;
    Simple3DRenderObj unk_18;
} FieldEffectRenderer04Context;

static void FieldMap_021F508C(FieldEffectRenderer04Context *param0);
static void FieldMap_021F50B0(FieldEffectRenderer04Context *param0);

void *FieldMap_021F5060(FieldEffectManager *param0)
{
    FieldEffectRenderer04Context *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer04Context)), 0, 0);
    v0->unk_00 = param0;

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
    FieldEffectManager_LoadModel(param0->unk_00, &param0->unk_04, 0, 21, 0);
    Simple3D_CreateRenderObject(&param0->unk_18, &param0->unk_04);
}

static void FieldMap_021F50B0(FieldEffectRenderer04Context *param0)
{
    Simple3D_FreeModel(&param0->unk_04);
}
