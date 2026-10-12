#include "fieldmap/fieldmap_021F3284.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "field/field_system.h"
#include "fieldmap/field_effect_manager.h"

#include "billboard.h"
#include "map_object.h"
#include "overworld_anim_manager.h"

typedef struct {
    FieldEffectManager *unk_00;
} UnkStruct_fieldmap_021F32B0;

typedef struct {
    FieldSystem *fieldSystem;
    FieldEffectManager *unk_04;
    UnkStruct_fieldmap_021F32B0 *unk_08;
    MapObject *unk_0C;
} UnkStruct_fieldmap_021F331C;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    UnkStruct_fieldmap_021F331C unk_14;
    Billboard *unk_24;
} UnkStruct_fieldmap_021F336C;

static void FieldMap_021F32B0(UnkStruct_fieldmap_021F32B0 *param0);
static void FieldMap_021F32F4(UnkStruct_fieldmap_021F32B0 *param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200588;
const BillboardAnim Unk_FieldMap_0220059C[];

void *FieldMap_021F3284(FieldEffectManager *param0)
{
    UnkStruct_fieldmap_021F32B0 *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(UnkStruct_fieldmap_021F32B0)), 0, 0);
    v0->unk_00 = param0;

    FieldMap_021F32B0(v0);
    return v0;
}

void FieldMap_021F32A0(void *param0)
{
    UnkStruct_fieldmap_021F32B0 *v0 = param0;

    FieldMap_021F32F4(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F32B0(UnkStruct_fieldmap_021F32B0 *param0)
{
    FieldMap_021DF9E0(param0->unk_00, 3, 86);
    FieldMap_021DFA14(param0->unk_00, 2, 174);
    FieldMap_021DFA3C(param0->unk_00, 2, 5, 1);
    FieldMap_021DF864(param0->unk_00, 3, 3, 2, 2, 0, Unk_FieldMap_0220059C);
}

static void FieldMap_021F32F4(UnkStruct_fieldmap_021F32B0 *param0)
{
    FieldMap_021DFA08(param0->unk_00, 3);
    FieldMap_021DFA30(param0->unk_00, 2);
    FieldMap_021DFA7C(param0->unk_00, 2);
    FieldMap_021DF9D4(param0->unk_00, 3);
}

void FieldMap_021F331C(MapObject *param0, int param1)
{
    UnkStruct_fieldmap_021F331C v0;
    FieldEffectManager *v1;
    OverworldAnimManager *v2;

    v1 = MapObject_GetFieldEffectManager(param0);

    v0.fieldSystem = MapObject_FieldSystem(param0);
    v0.unk_04 = v1;
    v0.unk_08 = FieldEffectManager_GetRendererContext(v1, 21);
    v0.unk_0C = param0;

    {
        VecFx32 v3 = { 0, 0, 0 };
        int v4 = MapObject_CalculateTaskPriority(param0, 2);

        v2 = FieldEffectManager_InitAnimManager(v1, &Unk_FieldMap_02200588, &v3, param1, &v0, v4);
    }
}

static int FieldMap_021F336C(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0 = { 0, 0, 0 };
    UnkStruct_fieldmap_021F336C *v1;
    const UnkStruct_fieldmap_021F331C *v2;

    v1 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);

    v1->unk_14 = *v2;
    v1->unk_04 = MapObject_GetEffectiveGraphicsID(v1->unk_14.unk_0C);
    v1->unk_08 = MapObject_GetLocalID(v1->unk_14.unk_0C);
    v1->unk_0C = MapObject_GetMapHeaderID(v1->unk_14.unk_0C);

    OverworldAnimManager_SetPosition(param0, &v0);
    v1->unk_24 = FieldMap_021DF84C(v1->unk_14.unk_04, 3, &v0);

    return 1;
}

static void FieldMap_021F33C4(OverworldAnimManager *param0, void *param1)
{
    UnkStruct_fieldmap_021F336C *v0 = param1;
    Billboard_Delete(v0->unk_24);
}

static void FieldMap_021F33D0(OverworldAnimManager *param0, void *param1)
{
    int v0, v1;
    UnkStruct_fieldmap_021F336C *v2 = param1;
    MapObject *v3 = v2->unk_14.unk_0C;

    if (MapObject_MatchesGraphicsAndLocalID(v3, v2->unk_04, v2->unk_08, v2->unk_0C) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    v1 = OverworldAnimManager_GetUserInt(param0);

    if (v1 == 1) {
        if (MapObject_CheckStatus26(v3) == 0) {
            FieldEffectManager_FinishAnimManager(param0);
            return;
        }
    }

    switch (v2->unk_00) {
    case 0:
        Billboard_AdvanceAnim(v2->unk_24, FX32_ONE);
        v0 = Billboard_GetAnimFrameNum(v2->unk_24) / FX32_ONE;

        if (v0 >= 12) {
            if (v1 == 0) {
                FieldEffectManager_FinishAnimManager(param0);
                return;
            } else {
                Billboard_SetFrameNum(v2->unk_24, 0);
            }
        }
        break;
    }
}

static void FieldMap_021F3448(OverworldAnimManager *param0, void *param1)
{
    VecFx32 v0;
    UnkStruct_fieldmap_021F336C *v1 = param1;
    MapObject *v2 = v1->unk_14.unk_0C;

    if (MapObject_MatchesGraphicsAndLocalID(v2, v1->unk_04, v1->unk_08, v1->unk_0C) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    MapObject_GetPosPtr(v2, &v0);

    v0.z += FX32_ONE * 8;
    Billboard_SetPos(v1->unk_24, &v0);
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200588 = {
    (sizeof(UnkStruct_fieldmap_021F336C)),
    FieldMap_021F336C,
    FieldMap_021F33C4,
    FieldMap_021F33D0,
    FieldMap_021F3448
};

static const BillboardAnim Unk_FieldMap_0220059C[] = {
    { 0x0, 0xC, 0x1 },
    { 0x0, 0x0, 0x2 }
};
