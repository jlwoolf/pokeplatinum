#include "fieldmap/fieldmap_021ECA70.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/fieldmap_021ECE40.h"
#include "fieldmap/struct_map_object_billboard_state_decl.h"
#include "fieldmap/struct_billboard_anim_state.h"

#include "billboard.h"
#include "map_object.h"

typedef struct MapObjectBillboardState_t {
    Billboard *unk_00;
    BillboardAnimState unk_04;
};

static void FieldMap_021ECB90(MapObject *param0);
static void FieldMap_021ECBA4(MapObject *param0);
static void FieldMap_021ECBCC(MapObject *param0, Billboard *param1);
static void FieldMap_021ECC0C(MapObject *param0);

void FieldMap_021ECA70(MapObject *param0)
{
    VecFx32 v0;

    FieldMap_021ECB90(param0);

    v0.x = 0;
    v0.y = (FX32_CONST(0));
    v0.z = 0;

    MapObject_SetSpritePosOffset(param0, &v0);
}

void FieldMap_021ECA90(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);
    Billboard *v1 = v0->unk_00;

    if (FieldMap_021EDD94(param0) == 1) {
        return;
    }

    if (v1 == NULL) {
        return;
    }

    FieldMap_021ECBA4(param0);
    Billboard_AdvanceAnim(v1, FX32_ONE);
}

void FieldMap_021ECABC(MapObject *param0)
{
    FieldMap_021ECC0C(param0);
}

void FieldMap_021ECAC4(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);

    if (v0->unk_00 != NULL) {
        FieldMap_021ED01C(v0->unk_00, &v0->unk_04);
    }

    FieldMap_021ECFA4(param0, &v0->unk_00);
    MapObject_SetStatusFlagOn(param0, MAP_OBJ_STATUS_21);
}

void FieldMap_021ECAF0(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);

    if (FieldMap_021EDD94(param0) == 1) {
        return;
    }

    if (v0->unk_00 == NULL) {
        FieldMap_021ECF04(param0, &v0->unk_00);
    }

    if (v0->unk_00 != NULL) {
        FieldMap_021ED03C(v0->unk_00, &v0->unk_04);
        FieldMap_021EDEB4(param0, v0->unk_00);
        MapObject_SetStatusFlagOff(param0, MAP_OBJ_STATUS_21);
    }
}

void FieldMap_021ECB34(MapObject *param0)
{
    VecFx32 v0;

    FieldMap_021ECB90(param0);

    v0.x = 0;
    v0.y = (FX32_CONST(24));
    v0.z = 0;

    MapObject_SetSpritePosOffset(param0, &v0);
}

void FieldMap_021ECB58(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);
    Billboard *v1 = v0->unk_00;

    if (FieldMap_021EDD94(param0) == 1) {
        return;
    }

    if (v1 == NULL) {
        return;
    }

    FieldMap_021ECBA4(param0);
}

void FieldMap_021ECB78(MapObject *param0)
{
    FieldMap_021ECC0C(param0);
}

Billboard *FieldMap_021ECB80(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);
    return FieldMap_021ECB8C(v0);
}

Billboard *FieldMap_021ECB8C(MapObjectBillboardState *param0)
{
    return param0->unk_00;
}

static void FieldMap_021ECB90(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_InitUnk108(param0, (sizeof(MapObjectBillboardState)));

    FieldMap_021ECF04(param0, &v0->unk_00);
}

static void FieldMap_021ECBA4(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);
    Billboard *v1 = v0->unk_00;

    FieldMap_021EDEB4(param0, v1);
    Billboard_AdvanceAnim(v1, (FX32_ONE));
    FieldMap_021ECBCC(param0, v1);
}

static void FieldMap_021ECBCC(MapObject *param0, Billboard *param1)
{
    int v0 = 1;

    if (MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_HIDE) == 1) {
        v0 = 0;
    }

    if (MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_12) == 1) {
        if (!MapObject_CheckStatusFlag(param0, MAP_OBJ_STATUS_13)) {
            v0 = 0;
        }
    }

    Billboard_SetDrawFlag(param1, v0);
}

static void FieldMap_021ECC0C(MapObject *param0)
{
    MapObjectBillboardState *v0 = MapObject_GetUnk108(param0);
    FieldMap_021ECFA4(param0, &v0->unk_00);
}
