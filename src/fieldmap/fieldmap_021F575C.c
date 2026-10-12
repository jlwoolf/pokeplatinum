#include "fieldmap/fieldmap_021F575C.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "overworld_anim_manager.h"
#include "simple3d.h"

typedef struct {
    int unk_00;
    FieldEffectManager *unk_04;
    Simple3DModel unk_08;
    Simple3DAnimation unk_1C;
} UnkStruct_021F5788;

typedef struct {
    FieldEffectManager *unk_00;
    UnkStruct_021F5788 *unk_04;
} BuriedSphereSparkleParams;

typedef struct {
    Simple3DAnimation unk_00;
    Simple3DRenderObj unk_24;
    BuriedSphereSparkleParams unk_78;
} BuriedSphereSparkleAnim;

static void FieldMap_021F5788(UnkStruct_021F5788 *param0);
static void FieldMap_021F57B4(UnkStruct_021F5788 *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B54;

void *FieldMap_021F575C(FieldEffectManager *param0)
{
    UnkStruct_021F5788 *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(UnkStruct_021F5788)), 0, 0);
    v0->unk_04 = param0;

    FieldMap_021F5788(v0);
    return v0;
}

void FieldMap_021F5778(void *param0)
{
    UnkStruct_021F5788 *v0 = param0;

    FieldMap_021F57B4(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F5788(UnkStruct_021F5788 *param0)
{
    FieldEffectManager_LoadModel(param0->unk_04, &param0->unk_08, 0, 92, 0);
    FieldEffectManager_LoadAnimation(param0->unk_04, &param0->unk_1C, 0, 164, 0);
}

static void FieldMap_021F57B4(UnkStruct_021F5788 *param0)
{
    Simple3D_FreeModel(&param0->unk_08);
    Simple3D_FreeAnimation(&param0->unk_1C);
}

void FieldMap_DisplayBuriedSphereSparkle(FieldSystem *fieldSystem, int x, int z)
{
    BuriedSphereSparkleParams v2;
    VecFx32 v3;

    v2.unk_00 = fieldSystem->fieldEffMan;
    v2.unk_04 = FieldEffectManager_GetRendererContext(v2.unk_00, 9);

    v3.x = ((x << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);
    v3.y = 0;
    v3.z = ((z << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1);

    FieldEffectManager_InitAnimManager(v2.unk_00, &Unk_FieldMap_02200B54, &v3, 0, &v2, 0xff);
}

static int FieldMap_021F580C(OverworldAnimManager *param0, void *param1)
{
    BuriedSphereSparkleAnim *v0 = param1;
    const BuriedSphereSparkleParams *v1 = OverworldAnimManager_GetUserData(param0);

    v0->unk_78 = *v1;

    FieldEffectManager_ApplyAnimCopyToModel(v0->unk_78.unk_00, &v0->unk_00, &v0->unk_78.unk_04->unk_08, &v0->unk_78.unk_04->unk_1C, 0);
    Simple3D_CreateRenderObjectWithAnim(&v0->unk_24, &v0->unk_78.unk_04->unk_08, &v0->unk_00);

    return 1;
}

static void FieldMap_021F5844(OverworldAnimManager *param0, void *param1)
{
    BuriedSphereSparkleAnim *v0 = param1;
    Simple3D_FreeAnimation(&v0->unk_00);
}

static void FieldMap_021F5850(OverworldAnimManager *param0, void *param1)
{
    BuriedSphereSparkleAnim *v0 = param1;

    if (Simple3D_HasAnimationReachedEnd(&v0->unk_00) == 1) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    Simple3D_UpdateAnim(&v0->unk_00, FX32_ONE, 0);
}

static void FieldMap_021F5878(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    BuriedSphereSparkleAnim *v1 = param1;

    OverworldAnimManager_GetPosition(param0, &v0);
    Simple3D_DrawRenderObjWithPos(&v1->unk_24, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200B54 = {
    (sizeof(BuriedSphereSparkleAnim)),
    FieldMap_021F580C,
    FieldMap_021F5844,
    FieldMap_021F5850,
    FieldMap_021F5878
};
