#include "fieldmap/fieldmap_021EB1A0.h"

#include <nitro.h>
#include <string.h>

#include "generated/object_events_gfx.h"

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"
#include "fieldmap/object_event_gfx_data.h"
#include "fieldmap/fieldmap_021ECA70.h"
#include "fieldmap/fieldmap_021ECC20.h"
#include "fieldmap/fieldmap_021ECE40.h"
#include "fieldmap/fieldmap_021F10E8.h"
#include "fieldmap/fieldmap_021F23D0.h"
#include "fieldmap/struct_billboard_anim_state.h"

#include "billboard.h"
#include "map_object.h"
#include "math_util.h"
#include "overworld_anim_manager.h"

typedef struct {
    s16 unk_00;
    s8 unk_02;
    s8 unk_03;
    Billboard *unk_04;
    BillboardAnimState unk_08;
} MapObjectBillboard;

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    Billboard *unk_04;
    BillboardAnimState unk_08;
} MagikarpBillboard;

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    u8 unk_03_0 : 1;
    u8 unk_03_1 : 7;
    Billboard *unk_04;
    BillboardAnimState unk_08;
} PlayerBillboard;

typedef struct {
    OverworldAnimManager *unk_00;
} MapObjectAnimManager;

typedef struct {
    s16 unk_00;
    s8 unk_02;
    s8 unk_03;
    Billboard *unk_04;
    BillboardAnimState unk_08;
    u32 unk_10;
} DistWorldMespritBillboard;

typedef struct {
    int unk_00;
    fx32 unk_04;
    Billboard *unk_08;
    BillboardAnimState unk_0C;
} MapObjectBillboardOffset;

void FieldMap_021EB2EC(MapObject *mapObj);
void FieldMap_021EB314(MapObject *mapObj);
void FieldMap_021EB328(MapObject *mapObj);
void FieldMap_021EB354(MapObject *mapObj);
void FieldMap_021EB398(MapObject *mapObj);
void FieldMap_021EB40C(MapObject *mapObj);
static void FieldMap_021EB478(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB4AC(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB4E8(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB524(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB560(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB59C(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EB620(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3);
static void FieldMap_021EC068(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3);
static void FieldMap_021EC0E4(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3);
void FieldMap_021EC734(MapObject *mapObj);
void FieldMap_021EC75C(MapObject *mapObj);
void FieldMap_021EC760(MapObject *mapObj);
void FieldMap_021EC778(MapObject *mapObj);
void FieldMap_021EC790(MapObject *mapObj);
static void FieldMap_021EC638(Billboard *param0, int param1);
static void FieldMap_021EC668(Billboard *param0);
static void FieldMap_021EC674(Billboard *param0, int param1, int param2);
static void FieldMap_021EC69C(Billboard *param0, int param1);
static void FieldMap_021EC6C0(MapObject *mapObj, Billboard *param1);
static void FieldMap_021EC374(MapObject *mapObj, Billboard *param1, int param2);

void (*const Unk_FieldMap_021FF3D4[])(MapObject *, Billboard *, MapObjectBillboard *, int);
void (*const Unk_FieldMap_021FF420[])(MapObject *, Billboard *, MapObjectBillboard *, int);
void (*const Unk_FieldMap_021FF3F8[])(MapObject *, Billboard *, PlayerBillboard *, int);
static void (*const Unk_FieldMap_021FF448[11])(MapObject *, Billboard *, PlayerBillboard *, int);

Billboard *FieldMap_021EB1A0(MapObject *mapObj)
{
    int v0 = MapObject_GetGraphicsID(mapObj);

    switch (v0) {
    case OBJ_EVENT_GFX_PLAYER_M:
    case OBJ_EVENT_GFX_PLAYER_F:
    case OBJ_EVENT_GFX_PLAYER_M_BIKE:
    case OBJ_EVENT_GFX_PLAYER_F_BIKE:
    case OBJ_EVENT_GFX_PLAYER_M_HOLDING_POKE_BALL:
    case OBJ_EVENT_GFX_PLAYER_F_HOLDING_POKE_BALL:
    case OBJ_EVENT_GFX_PLAYER_M_SURF:
    case OBJ_EVENT_GFX_PLAYER_F_SURF:
    case OBJ_EVENT_GFX_PLAYER_M_SPRAYDUCK:
    case OBJ_EVENT_GFX_PLAYER_F_SPRAYDUCK:
    case OBJ_EVENT_GFX_PLAYER_M_SAVE:
    case OBJ_EVENT_GFX_PLAYER_F_SAVE:
    case OBJ_EVENT_GFX_PLAYER_M_CONTEST:
    case OBJ_EVENT_GFX_PLAYER_F_CONTEST:
    case OBJ_EVENT_GFX_PLAYER_M_FISHING:
    case OBJ_EVENT_GFX_PLAYER_F_FISHING:
    case OBJ_EVENT_GFX_PLAYER_M_POKETCH:
    case OBJ_EVENT_GFX_PLAYER_F_POKETCH:
    case OBJ_EVENT_GFX_PLAYER_M_POKECENTER_HEAL:
    case OBJ_EVENT_GFX_PLAYER_F_POKECENTER_HEAL:
    case OBJ_EVENT_GFX_PLAYER_M_HEARTHOME_GYM:
    case OBJ_EVENT_GFX_PLAYER_F_HEARTHOME_GYM:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_M:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_F:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_M_SAVE:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_F_SAVE:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_M_POKETCH:
    case OBJ_EVENT_GFX_DIST_WORLD_PLAYER_F_POKETCH:
    case OBJ_EVENT_GFX_PLAYER_M_SAVE_HEARTHOME_GYM:
    case OBJ_EVENT_GFX_PLAYER_F_SAVE_HEARTHOME_GYM:
    case OBJ_EVENT_GFX_PLAYER_M_POKETCH_HEARTHOME_GYM:
    case OBJ_EVENT_GFX_PLAYER_F_POKETCH_HEARTHOME_GYM: {
        PlayerBillboard *v1;

        v1 = MapObject_GetUnk108(mapObj);
        return v1->unk_04;
    }
    case OBJ_EVENT_GFX_MAGIKARP: {
        MagikarpBillboard *v2;

        v2 = MapObject_GetUnk108(mapObj);
        return v2->unk_04;
    }
    case OBJ_EVENT_GFX_UXIE:
    case OBJ_EVENT_GFX_MESPRIT:
    case OBJ_EVENT_GFX_AZELF: {
        return FieldMap_021ECB80(mapObj);
    }
    case OBJ_EVENT_GFX_DIST_WORLD_B1F_MESPRIT: {
        DistWorldMespritBillboard *v3;

        v3 = MapObject_GetUnk108(mapObj);
        return v3->unk_04;
    }
    case OBJ_EVENT_GFX_BERRY_SOIL: {
        return NULL;
    }
    default: {
        const ObjectEventGfxRenderDetailsEntry *v4;

        v4 = FieldMap_021ECD04(mapObj);

        if (v4->modelType == 1) {
            MapObjectBillboard *v5;

            v5 = MapObject_GetUnk108(mapObj);
            return v5->unk_04;
        }
    }
    }

    return NULL;
}

void FieldMap_021EB2EC(MapObject *mapObj)
{
    MapObjectBillboard *v0 = MapObject_InitUnk108(mapObj, (sizeof(MapObjectBillboard)));
    v0->unk_02 = -1;

    FieldMap_021ECF04(mapObj, &v0->unk_04);

    if (v0->unk_04 != NULL) {
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021EB314(MapObject *mapObj)
{
    MapObjectBillboard *v0 = MapObject_GetUnk108(mapObj);
    FieldMap_021ECFA4(mapObj, &v0->unk_04);
}

void FieldMap_021EB328(MapObject *mapObj)
{
    MapObjectBillboard *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_04 != NULL) {
        FieldMap_021ED01C(v0->unk_04, &v0->unk_08);
    }

    FieldMap_021ECFA4(mapObj, &v0->unk_04);
    MapObject_SetStatusFlagOn(mapObj, MAP_OBJ_STATUS_21);
}

void FieldMap_021EB354(MapObject *mapObj)
{
    int v0;
    MapObjectBillboard *v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v1->unk_04 == NULL) {
        FieldMap_021ECF04(mapObj, &v1->unk_04);
    }

    if (v1->unk_04 != NULL) {
        FieldMap_021ED03C(v1->unk_04, &v1->unk_08);
        FieldMap_021EDEB4(mapObj, v1->unk_04);

        MapObject_SetStatusFlagOff(mapObj, MAP_OBJ_STATUS_21);
    }
}

void FieldMap_021EB398(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    GF_ASSERT(v1 < (0x8 + 1));
    Unk_FieldMap_021FF3D4[v1](mapObj, v3, v2, v0);

    v2->unk_02 = v0;
    v2->unk_03 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EB40C(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboard *v2;
    Billboard *v3;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    v3 = v2->unk_04;

    if (v3 == NULL) {
        return;
    }

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EB438(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboard *v2;
    Billboard *v3;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    v3 = v2->unk_04;

    if (v3 == NULL) {
        return;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(v3, (FX32_ONE));
    }

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EB478(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else {
        FieldMap_021EC668(param1);
    }

    Billboard_AdvanceAnim(param1, 0);
}

static void FieldMap_021EB4AC(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) / 2));
    }
}

static void FieldMap_021EB4E8(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, (FX32_ONE));
    }
}

static void FieldMap_021EB524(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) * 2));
    }
}

static void FieldMap_021EB560(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) * 4));
    }
}

static void FieldMap_021EB59C(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);

        param2->unk_00 = 0;
    }

    if (param2->unk_03 != 0x6) {
        param2->unk_00 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            (FX32_ONE),
            (FX32_ONE),
            ((FX32_ONE) * 2),
            (FX32_ONE),
            (FX32_ONE),
            ((FX32_ONE) * 2),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_00]);
        param2->unk_00++;

        if (v1[param2->unk_00] == 0) {
            param2->unk_00 = 0;
        }
    }
}

static void FieldMap_021EB620(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);

        param2->unk_00 = 0;
    }

    if (param2->unk_03 != 0x7) {
        param2->unk_00 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            ((FX32_ONE) * 3),
            ((FX32_ONE) * 2),
            ((FX32_ONE) * 3),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_00]);
        param2->unk_00++;

        if (v1[param2->unk_00] == 0) {
            param2->unk_00 = 0;
        }
    }
}

static void FieldMap_021EB69C(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param3 != param2->unk_02) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);

        param2->unk_00 = 0;
    }

    if (param2->unk_03 != 0x8) {
        param2->unk_00 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            ((FX32_ONE) * 2),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_00]);

        param2->unk_00++;
        if (v1[param2->unk_00] == 0) {
            param2->unk_00 = 0;
        }
    }
}

static void (*const Unk_FieldMap_021FF3D4[])(
    MapObject *, Billboard *, MapObjectBillboard *, int)
    = {
          FieldMap_021EB478,
          FieldMap_021EB4AC,
          FieldMap_021EB4AC,
          FieldMap_021EB4E8,
          FieldMap_021EB524,
          FieldMap_021EB560,
          FieldMap_021EB59C,
          FieldMap_021EB620,
          FieldMap_021EB69C
      };

void FieldMap_021EB720(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    GF_ASSERT(v1 < (0x9 + 1));

    Unk_FieldMap_021FF420[v1](mapObj, v3, v2, v0);

    v2->unk_02 = v0;
    v2->unk_03 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EB794(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if ((param3 != param2->unk_02) || (param2->unk_03 == 0x9)) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else {
        FieldMap_021EC668(param1);
    }

    Billboard_AdvanceAnim(param1, 0);
}

static void FieldMap_021EB7D0(MapObject *mapObj, Billboard *param1, MapObjectBillboard *param2, int param3)
{
    if (param2->unk_03 != 0x9) {
        Billboard_SetAnimNum(param1, 4);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    Billboard_AdvanceAnim(param1, (FX32_ONE));
}

static void (*const Unk_FieldMap_021FF420[])(MapObject *, Billboard *, MapObjectBillboard *, int) = {
    FieldMap_021EB794,
    FieldMap_021EB4AC,
    FieldMap_021EB4AC,
    FieldMap_021EB4E8,
    FieldMap_021EB524,
    FieldMap_021EB560,
    FieldMap_021EB59C,
    FieldMap_021EB620,
    FieldMap_021EB69C,
    FieldMap_021EB7D0
};

void FieldMap_021EB7F8(MapObject *mapObj)
{
    MagikarpBillboard *v0 = MapObject_InitUnk108(mapObj, (sizeof(MagikarpBillboard)));

    v0->unk_00 = -1;
    v0->unk_02 = LCRNG_Next() % 16;

    FieldMap_021ECF04(mapObj, &v0->unk_04);

    if (v0->unk_04 != NULL) {
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021EB834(MapObject *mapObj)
{
    MagikarpBillboard *v0 = MapObject_GetUnk108(mapObj);
    FieldMap_021ECFA4(mapObj, &v0->unk_04);
}

void FieldMap_021EB848(MapObject *mapObj)
{
    MagikarpBillboard *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_04 != NULL) {
        FieldMap_021ED01C(v0->unk_04, &v0->unk_08);
    }

    FieldMap_021ECFA4(mapObj, &v0->unk_04);
    MapObject_SetStatusFlagOn(mapObj, MAP_OBJ_STATUS_21);
}

void FieldMap_021EB874(MapObject *mapObj)
{
    int v0;
    MagikarpBillboard *v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v1->unk_04 == NULL) {
        FieldMap_021ECF04(mapObj, &v1->unk_04);
    }

    if (v1->unk_04 != NULL) {
        FieldMap_021ED03C(v1->unk_04, &v1->unk_08);
        FieldMap_021EDEB4(mapObj, v1->unk_04);
        MapObject_SetStatusFlagOff(mapObj, MAP_OBJ_STATUS_21);
    }
}

void FieldMap_021EB8B8(MapObject *mapObj)
{
    int v0, v1;
    MagikarpBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    if (v2->unk_02) {
        v2->unk_02--;
        Billboard_AdvanceAnim(v3, 0);
    } else {
        Billboard_AdvanceAnim(v3, (FX32_ONE));
        v2->unk_01++;

        if (v2->unk_01 >= 32) {
            v2->unk_01 = 0;
            v2->unk_02 = LCRNG_Next() % 16;
        }
    }

    v2->unk_00 = v0;
    v2->unk_03 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EB944(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    switch (v1) {
    case 0x0: {
        int v4;

        if ((v0 == 0) || (v0 == 1)) {
            v4 = 0;
        } else {
            v4 = 1;
        }

        if ((Billboard_GetAnimNum(v3) != v4) || (v2->unk_03 == 0x0)) {
            Billboard_SetAnimNum(v3, v4);
            Billboard_SetAnimFrameNum(v3, 0);
            Billboard_AdvanceAnim(v3, 0);
        }

        Billboard_AdvanceAnim(v3, 0);
    } break;
    default: {
        int v5;
        fx32 v6 = 0;

        if ((v0 == 0) || (v0 == 1)) {
            v5 = 0;
        } else {
            v5 = 1;
        }

        if (Billboard_GetAnimNum(v3) != v5) {
            Billboard_SetAnimNum(v3, v5);
            Billboard_SetAnimFrameNum(v3, 0);
        }

        Billboard_AdvanceAnim(v3, FX32_ONE );
    } break;
    }

    v2->unk_02 = v0;
    v2->unk_03 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EBA0C(MapObject *mapObj)
{
    PlayerBillboard *v0 = MapObject_InitUnk108(mapObj, (sizeof(PlayerBillboard)));
    v0->unk_00 = -1;

    FieldMap_021ECF04(mapObj, &v0->unk_04);

    if (v0->unk_04 != NULL) {
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021EBA34(MapObject *mapObj)
{
    PlayerBillboard *v0;
    VecFx32 v1 = { 0, 0, 0 };

    v0 = MapObject_GetUnk108(mapObj);

    FieldMap_021ECFA4(mapObj, &v0->unk_04);
    MapObject_SetSpriteJumpOffset(mapObj, &v1);
}

void FieldMap_021EBA60(MapObject *mapObj)
{
    PlayerBillboard *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_04 != NULL) {
        FieldMap_021ED01C(v0->unk_04, &v0->unk_08);
    }

    FieldMap_021ECFA4(mapObj, &v0->unk_04);
    MapObject_SetStatusFlagOn(mapObj, MAP_OBJ_STATUS_21);
}

void FieldMap_021EBA8C(MapObject *mapObj)
{
    int v0;
    PlayerBillboard *v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v1->unk_04 == NULL) {
        FieldMap_021ECF04(mapObj, &v1->unk_04);
    }

    if (v1->unk_04 != NULL) {
        FieldMap_021ED03C(v1->unk_04, &v1->unk_08);
        FieldMap_021EDEB4(mapObj, v1->unk_04);
        MapObject_SetStatusFlagOff(mapObj, MAP_OBJ_STATUS_21);
    }
}

void FieldMap_021EBAD0(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    GF_ASSERT(v1 < ((0x8 + 1) + 1));
    Unk_FieldMap_021FF3F8[v1](mapObj, v3, v2, v0);

    v2->unk_00 = v0;
    v2->unk_02 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EBB44(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_03_0 = 0;
    } else if (param2->unk_02 == (0x8 + 1)) {
        param2->unk_03_0 = 1;
    } else if (param2->unk_03_0 == 1) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
        param2->unk_03_0 = 0;
    } else {
        FieldMap_021EC668(param1);
    }
}

static void FieldMap_021EBBB4(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0;

    if (param3 != param2->unk_00) {
        v0 = FieldMap_021EDF18(param3);
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 == (0x8 + 1)) {
        param2->unk_03_0 = 1;
        return;
    } else if (param2->unk_03_0 == 1) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
        param2->unk_03_0 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) / 2));
    }
}

static void FieldMap_021EBC28(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0;

    if (param3 != param2->unk_00) {
        v0 = FieldMap_021EDF18(param3);
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, (FX32_ONE));
    }
}

static void FieldMap_021EBC7C(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) * 2));
    }
}

static void FieldMap_021EBCD0(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) * 4));
    }
}

static void FieldMap_021EBD24(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_01 = 0;
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (param2->unk_02 != 0x6) {
        param2->unk_01 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            (FX32_ONE),
            (FX32_ONE),
            ((FX32_ONE) * 2),
            (FX32_ONE),
            (FX32_ONE),
            ((FX32_ONE) * 2),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_01]);
        param2->unk_01++;

        if (v1[param2->unk_01] == 0) {
            param2->unk_01 = 0;
        }
    }
}

static void FieldMap_021EBDC4(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_01 = 0;
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (param2->unk_02 != 0x7) {
        param2->unk_01 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            ((FX32_ONE) * 3),
            ((FX32_ONE) * 2),
            ((FX32_ONE) * 3),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_01]);
        param2->unk_01++;

        if (v1[param2->unk_01] == 0) {
            param2->unk_01 = 0;
        }
    }
}

static void FieldMap_021EBE5C(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    if (param3 != param2->unk_00) {
        int v0 = FieldMap_021EDF18(param3);

        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_01 = 0;
    } else if (param2->unk_02 == (0x8 + 1)) {
        FieldMap_021EC69C(param1, FieldMap_021EDF18(param3));
    }

    if (param2->unk_02 != 0x8) {
        param2->unk_01 = 0;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        fx32 v1[] = {
            ((FX32_ONE) * 2),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            (FX32_ONE),
            0
        };

        Billboard_AdvanceAnim(param1, v1[param2->unk_01]);
        param2->unk_01++;

        if (v1[param2->unk_01] == 0) {
            param2->unk_01 = 0;
        }
    }
}

static void FieldMap_021EBEFC(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0;

    if (param3 != param2->unk_00) {
        v0 = FieldMap_021EDF24(param3);
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 != (0x8 + 1)) {
        FieldMap_021EC674(
            param1, FieldMap_021EDF24(param3), 4);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, (FX32_ONE));
    }
}

static void (*const Unk_FieldMap_021FF3F8[])(
    MapObject *, Billboard *, PlayerBillboard *, int)
    = {
          FieldMap_021EBB44,
          FieldMap_021EBBB4,
          FieldMap_021EBBB4,
          FieldMap_021EBC28,
          FieldMap_021EBC7C,
          FieldMap_021EBCD0,
          FieldMap_021EBD24,
          FieldMap_021EBDC4,
          FieldMap_021EBE5C,
          FieldMap_021EBEFC
      };

void FieldMap_021EBF50(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    GF_ASSERT(v1 < (((0x8 + 1) + 1) + 1));

    if ((v2->unk_02 == 0x0) && (v1 != v2->unk_02) && (v2->unk_03_0 == 0)) {
        v2->unk_00 = -1;
    }

    Unk_FieldMap_021FF448[v1](mapObj, v3, v2, v0);

    v2->unk_00 = v0;
    v2->unk_02 = v1;

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EBFDC(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0[4] = { 6, 7, 8, 9 };
    int v1 = v0[param3];

    if (param3 != param2->unk_00) {
        Billboard_SetAnimNum(param1, v1);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_03_0 = 0;
    } else if (param2->unk_02 != 0x0) {
        param2->unk_03_0 = 1;
    } else if (param2->unk_03_0 == 1) {
        Billboard_SetAnimNum(param1, v1);
        Billboard_SetAnimFrameNum(param1, 0);
        param2->unk_03_0 = 0;
    } else {
        Billboard_AdvanceAnim(param1, (FX32_ONE));
    }
}

static void FieldMap_021EC068(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0 = FieldMap_021EDF30(param3);

    if ((param3 != param2->unk_00) || (param2->unk_02 != 0x0)) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 != (0x8 + 1)) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (Billboard_GetAnimNum(param1) != v0) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, ((FX32_ONE) / 2));
    }
}

static void FieldMap_021EC0E4(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    int v0 = FieldMap_021EDF30(param3);

    if (param3 != param2->unk_00) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (param2->unk_02 != ((0x8 + 1) + 1)) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    } else if (Billboard_GetAnimNum(param1) != v0) {
        Billboard_SetAnimNum(param1, v0);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(param1, (FX32_ONE));
    }
}

static void (*const Unk_FieldMap_021FF448[11])(
    MapObject *, Billboard *, PlayerBillboard *, int)
    = {
          FieldMap_021EBFDC,
          FieldMap_021EBBB4,
          FieldMap_021EBBB4,
          FieldMap_021EBC28,
          FieldMap_021EBC7C,
          FieldMap_021EBCD0,
          FieldMap_021EBD24,
          FieldMap_021EBDC4,
          FieldMap_021EBE5C,
          FieldMap_021EC068,
          FieldMap_021EC0E4
      };

void (*const Unk_FieldMap_021FF31C[])(MapObject *, Billboard *, PlayerBillboard *, int);

static const int Unk_FieldMap_021FF34C[] = {
    0x0,
    0x1,
    0x2,
    0x3
};

void FieldMap_021EC15C(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if ((v3 == NULL) || (FieldMap_021EDD94(mapObj) == 1)) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    GF_ASSERT(v1 < (0x3 + 1));

    Unk_FieldMap_021FF31C[v1](mapObj, v3, v2, v0);
    FieldMap_021EC374(mapObj, v3, v0);

    v2->unk_00 = v0;
    v2->unk_02 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EC1D8(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    fx32 v0;

    if ((param3 != param2->unk_00) || (param2->unk_02 != 0x0)) {
        Billboard_SetAnimNum(param1, Unk_FieldMap_021FF34C[param3]);
        Billboard_SetAnimFrameNum(param1, (FX32_ONE * 15));
    }

    v0 = Billboard_GetAnimFrameNum(param1);
    v0 -= (FX32_ONE);

    if (v0 < 0) {
        v0 = 0;
    }

    Billboard_SetAnimFrameNum(param1, v0);
    Billboard_AdvanceAnim(param1, 0);
}

static void FieldMap_021EC228(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    fx32 v0;

    if ((param3 != param2->unk_00) || (param2->unk_02 != 0x1)) {
        Billboard_SetAnimNum(param1, Unk_FieldMap_021FF34C[param3]);
        Billboard_SetAnimFrameNum(param1, 0);
    }

    Billboard_AdvanceAnim(param1, (FX32_ONE));
}

static void FieldMap_021EC260(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    fx32 v0;

    if ((param3 != param2->unk_00) || (param2->unk_02 != 0x2)) {
        Billboard_SetAnimNum(param1, Unk_FieldMap_021FF34C[param3]);
        Billboard_SetAnimFrameNum(param1, (FX32_ONE * 15));
        param2->unk_03_1 = 0;
    }

    v0 = Billboard_GetAnimFrameNum(param1);

    switch (param2->unk_03_1) {
    case 0:
        v0 -= (FX32_ONE);

        if (v0 <= (FX32_ONE * 10)) {
            param2->unk_03_1++;
        }
        break;
    case 1:
        v0 += (FX32_ONE);

        if (v0 >= (FX32_ONE * 15)) {
            param2->unk_03_1++;
            param2->unk_01 = 0;
        }
        break;
    case 2:
        param2->unk_01++;

        if (param2->unk_01 >= 30) {
            param2->unk_01 = 0;
            param2->unk_03_1 = 0;
        }
    }

    Billboard_SetAnimFrameNum(param1, v0);
    Billboard_AdvanceAnim(param1, 0);
}

static void FieldMap_021EC324(MapObject *mapObj, Billboard *param1, PlayerBillboard *param2, int param3)
{
    fx32 v0;

    if ((param3 != param2->unk_00) || (param2->unk_02 != 0x3)) {
        Billboard_SetAnimNum(param1, Unk_FieldMap_021FF34C[param3]);
        Billboard_SetAnimFrameNum(param1, (FX32_ONE * 15));
    }

    v0 = Billboard_GetAnimFrameNum(param1) - (FX32_ONE);

    if (v0 < 0) {
        v0 = 0;
    }

    Billboard_SetAnimFrameNum(param1, v0);
    Billboard_AdvanceAnim(param1, 0);
}

static void FieldMap_021EC374(MapObject *mapObj, Billboard *param1, int param2)
{
    VecFx32 v0 = { 0, 0, 0 };
    int v1 = (Billboard_GetFrameNum(param1) / FX32_ONE);

    switch (param2) {
    case 0:
        break;
    case 1:
        if (v1 >= 24) {
            v0.z = (FX32_ONE * 6);
        }
        break;
    case 2:
        if (v1 < 40) {
            v0.x = (FX32_ONE * 1);
        } else {
            v0.x = (FX32_ONE * -5);
        }
        break;
    case 3:
        if (v1 < 56) {
            v0.x = (FX32_ONE * -1);
        } else {
            v0.x = (FX32_ONE * 5);
        }
        break;
    }

    MapObject_SetSpriteJumpOffset(mapObj, &v0);
}

static void (*const Unk_FieldMap_021FF31C[])(MapObject *, Billboard *, PlayerBillboard *, int) = {
    FieldMap_021EC1D8,
    FieldMap_021EC228,
    FieldMap_021EC260,
    FieldMap_021EC324
};

void FieldMap_021EC3F0(MapObject *mapObj)
{
    int v0;
    PlayerBillboard *v1 = MapObject_GetUnk108(mapObj);
    Billboard *v2 = v1->unk_04;

    v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v2 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);

    v1->unk_00 = v0;
    v1->unk_02 = MapObject_GetUnkA0(mapObj);

    {
        int v3 = FieldMap_021EDF18(v0);

        Billboard_SetAnimNum(v2, v3);
        Billboard_SetAnimFrameNum(v2, 0);
        Billboard_AdvanceAnim(v2, 0);
    }

    FieldMap_021EDEB4(mapObj, v2);
    FieldMap_021EC6C0(mapObj, v2);
}

void FieldMap_021EC454(MapObject *mapObj)
{
    int v0;
    PlayerBillboard *v1 = MapObject_GetUnk108(mapObj);
    Billboard *v2 = v1->unk_04;

    v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v2 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);

    v1->unk_00 = v0;
    v1->unk_02 = MapObject_GetUnkA0(mapObj);

    if (Billboard_GetAnimNum(v2) != 0) {
        Billboard_SetAnimNum(v2, 0);
        Billboard_SetAnimFrameNum(v2, 0);
    }

    Billboard_AdvanceAnim(v2, (FX32_ONE));

    FieldMap_021EDEB4(mapObj, v2);
    FieldMap_021EC6C0(mapObj, v2);
}

void FieldMap_021EC4BC(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    switch (v1) {
    case 0x0:
        if (Billboard_GetAnimNum(v3) != 1) {
            Billboard_SetAnimNum(v3, 1);
            Billboard_SetAnimFrameNum(v3, 0);
        }

        Billboard_AdvanceAnim(v3, (FX32_ONE));
        break;
    default:
        if (Billboard_GetAnimNum(v3) != 0) {
            Billboard_SetAnimNum(v3, 0);
            Billboard_SetAnimFrameNum(v3, 0);
        }

        Billboard_AdvanceAnim(v3, (FX32_ONE));
    }

    v2->unk_00 = v0;
    v2->unk_02 = MapObject_GetUnkA0(mapObj);

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EC554(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);

    if (v0 != v2->unk_00) {
        v1 = FieldMap_021EDF18(v0);
        Billboard_SetAnimNum(v3, v1);
        Billboard_SetAnimFrameNum(v3, 0);
    }

    Billboard_AdvanceAnim(v3, (FX32_ONE));
    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);

    v2->unk_00 = v0;
    v2->unk_02 = MapObject_GetUnkA0(mapObj);
}

void FieldMap_021EC5C0(MapObject *mapObj)
{
    int v0, v1;
    PlayerBillboard *v2 = MapObject_GetUnk108(mapObj);
    Billboard *v3 = v2->unk_04;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v3 == NULL) {
        return;
    }

    v0 = MapObject_GetFacingDir(mapObj);
    v1 = MapObject_GetUnkA0(mapObj);

    if (v1 != v2->unk_02) {
        if (v1 == 0x0) {
            Billboard_SetAnimNum(v3, 0);
        } else {
            Billboard_SetAnimNum(v3, 1);
        }

        Billboard_SetAnimFrameNum(v3, 0);
    }

    Billboard_AdvanceAnim(v3, (FX32_ONE));

    v2->unk_00 = v0;
    v2->unk_02 = v1;

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

static void FieldMap_021EC638(Billboard *param0, int param1)
{
    fx32 v0, v1;

    v0 = Billboard_GetAnimFrameNum(param0);
    v0 /= FX32_ONE;
    v1 = v0 % param1;
    v0 -= v1;
    v0 *= FX32_ONE;

    Billboard_SetAnimFrameNum(param0, v0);
    Billboard_AdvanceAnim(param0, 0);
}

static void FieldMap_021EC668(Billboard *param0)
{
    FieldMap_021EC638(param0, 8);
}

static void FieldMap_021EC674(Billboard *param0, int param1, int param2)
{
    fx32 v0;

    FieldMap_021EC638(param0, param2);
    v0 = Billboard_GetAnimFrameNum(param0);

    Billboard_SetAnimNum(param0, param1);
    Billboard_SetAnimFrameNum(param0, v0);
}

static void FieldMap_021EC69C(Billboard *param0, int param1)
{
    fx32 v0;

    FieldMap_021EC668(param0);
    v0 = Billboard_GetAnimFrameNum(param0);

    Billboard_SetAnimNum(param0, param1);
    Billboard_SetAnimFrameNum(param0, v0);
}

static void FieldMap_021EC6C0(MapObject *mapObj, Billboard *param1)
{
    int v0 = 1;

    if (MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_HIDE) == 1) {
        v0 = 0;
    }

    if (MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_12) == 1) {
        if (!MapObject_CheckStatusFlag(mapObj, MAP_OBJ_STATUS_13)) {
            v0 = 0;
        }
    }

    Billboard_SetDrawFlag(param1, v0);
}

static void FieldMap_021EC700(u32 param0, VecFx32 *param1)
{
    const ObjectEventGfxFieldAnimsInitialPosEntry *v0 = gObjectEventGfxOverworldAnimsInitialPosTable;

    while (v0->graphicsID != 0xffff) {
        if (v0->graphicsID == param0) {
            *param1 = v0->initialPos;
            return;
        }

        v0++;
    }

    GF_ASSERT(FALSE);
}

void FieldMap_021EC734(MapObject *mapObj)
{
    VecFx32 v0;
    MapObjectAnimManager *v1 = MapObject_InitUnk108(mapObj, (sizeof(MapObjectAnimManager)));
    FieldMap_021EC700(MapObject_GetEffectiveGraphicsID(mapObj), &v0);
    v1->unk_00 = FieldMap_021F121C(mapObj, &v0);
}

void FieldMap_021EC75C(MapObject *mapObj)
{
    return;
}

void FieldMap_021EC760(MapObject *mapObj)
{
    MapObjectAnimManager *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_00 != NULL) {
        FieldEffectManager_FinishAnimManager(v0->unk_00);
        v0->unk_00 = NULL;
    }
}

void FieldMap_021EC778(MapObject *mapObj)
{
    MapObjectAnimManager *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_00 != NULL) {
        FieldEffectManager_FinishAnimManager(v0->unk_00);
        v0->unk_00 = NULL;
    }
}

void FieldMap_021EC790(MapObject *mapObj)
{
    VecFx32 v0;
    MapObjectAnimManager *v1 = MapObject_GetUnk108(mapObj);
    FieldMap_021EC700(MapObject_GetEffectiveGraphicsID(mapObj), &v0);
    v1->unk_00 = FieldMap_021F121C(mapObj, &v0);
}

void FieldMap_021EC7B8(MapObject *mapObj)
{
    MapObjectAnimManager *v0 = MapObject_InitUnk108(mapObj, (sizeof(MapObjectAnimManager)));
    v0->unk_00 = FieldMap_021F2438(mapObj);
}

void FieldMap_021EC7D0(MapObject *mapObj)
{
    MapObjectAnimManager *v0 = MapObject_GetUnk108(mapObj);
    GF_ASSERT(v0->unk_00 == NULL);
    v0->unk_00 = FieldMap_021F2438(mapObj);
}

void FieldMap_021EC7F0(MapObject *mapObj)
{
    MapObjectAnimManager *v0 = MapObject_GetUnk108(mapObj);
    FieldMap_021F247C(v0->unk_00);
    v0->unk_00 = NULL;
}

static void FieldMap_021EC804(Billboard *param0, void *param1)
{
    DistWorldMespritBillboard *v0 = param1;
    NNSG3dResMdl *v1 = Billboard_GetModel(param0);

    NNS_G3dMdlUseMdlAlpha(v1);
    NNS_G3dMdlSetMdlAlphaAll(v1, v0->unk_10);
}

void FieldMap_021EC824(MapObject *mapObj)
{
    DistWorldMespritBillboard *v0 = MapObject_InitUnk108(mapObj, sizeof(DistWorldMespritBillboard));
    v0->unk_02 = -1;

    FieldMap_021ECF04(mapObj, &v0->unk_04);

    if (v0->unk_04 != NULL) {
        Billboard_SetCallback(v0->unk_04, FieldMap_021EC804, v0);
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021EC858(MapObject *mapObj)
{
    DistWorldMespritBillboard *v0 = MapObject_GetUnk108(mapObj);
    FieldMap_021ECFA4(mapObj, &v0->unk_04);
}

void FieldMap_021EC86C(MapObject *mapObj)
{
    DistWorldMespritBillboard *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_04 != NULL) {
        FieldMap_021ED01C(v0->unk_04, &v0->unk_08);
    }

    FieldMap_021ECFA4(mapObj, &v0->unk_04);
    MapObject_SetStatusFlagOn(mapObj, MAP_OBJ_STATUS_21);
}

void FieldMap_021EC898(MapObject *mapObj)
{
    int v0;
    MapObjectBillboard *v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v1->unk_04 == NULL) {
        FieldMap_021ECF04(mapObj, &v1->unk_04);
    }

    if (v1->unk_04 != NULL) {
        FieldMap_021ED03C(v1->unk_04, &v1->unk_08);
        FieldMap_021EDEB4(mapObj, v1->unk_04);
        MapObject_SetStatusFlagOff(mapObj, MAP_OBJ_STATUS_21);
        Billboard_SetCallback(v1->unk_04, FieldMap_021EC804, v1);
    }
}

void FieldMap_021EC8EC(MapObject *mapObj)
{
    int v0, v1;
    DistWorldMespritBillboard *v2;
    Billboard *v3;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    v3 = v2->unk_04;

    if (v3 == NULL) {
        return;
    }

    if (v2->unk_10 < 31) {
        v2->unk_10++;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(v3, (FX32_ONE));
    }

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}

void FieldMap_021EC938(MapObject *mapObj)
{
    MapObjectBillboardOffset *v0 = MapObject_InitUnk108(mapObj, (sizeof(MapObjectBillboardOffset)));
    FieldMap_021ECF04(mapObj, &v0->unk_08);

    if (v0->unk_08 != NULL) {
        MapObject_CallRendererDraw(mapObj);
    }
}

void FieldMap_021EC95C(MapObject *mapObj)
{
    MapObjectBillboardOffset *v0 = MapObject_GetUnk108(mapObj);
    FieldMap_021ECFA4(mapObj, &v0->unk_08);
}

void FieldMap_021EC970(MapObject *mapObj)
{
    MapObjectBillboardOffset *v0 = MapObject_GetUnk108(mapObj);

    if (v0->unk_08 != NULL) {
        FieldMap_021ED01C(v0->unk_08, &v0->unk_0C);
    }

    FieldMap_021ECFA4(mapObj, &v0->unk_08);
    MapObject_SetStatusFlagOn(mapObj, MAP_OBJ_STATUS_21);
}

void FieldMap_021EC9A0(MapObject *mapObj)
{
    int v0;
    MapObjectBillboardOffset *v1 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    if (v1->unk_08 == NULL) {
        FieldMap_021ECF04(mapObj, &v1->unk_08);
    }

    if (v1->unk_08 != NULL) {
        FieldMap_021ED03C(v1->unk_08, &v1->unk_0C);
        FieldMap_021EDEB4(mapObj, v1->unk_08);
        MapObject_SetStatusFlagOff(mapObj, MAP_OBJ_STATUS_21);
    }
}

void FieldMap_021EC9E8(MapObject *mapObj)
{
    int v0, v1;
    MapObjectBillboardOffset *v2;
    Billboard *v3;

    v2 = MapObject_GetUnk108(mapObj);

    if (FieldMap_021EDD94(mapObj) == 1) {
        return;
    }

    v3 = v2->unk_08;

    if (v3 == NULL) {
        return;
    }

    if (FieldMap_021ECD38(mapObj) == 0) {
        Billboard_AdvanceAnim(v3, (FX32_ONE));
    }

    {
        VecFx32 v4;
        fx32 v5[16] = {
            0x0,
            0x800,
            0x1000,
            0x2000,
            0x4000,
            0x5800,
            0x7000,
            0x8000,
            0x7800,
            0x6800,
            0x5000,
            0x3000,
            0x2000,
            0x1000,
            0x800,
            0x0
        };

        MapObject_GetSpriteJumpOffset(mapObj, &v4);

        if (v4.y == v2->unk_04) {
            v4.y = v5[v2->unk_00 >> 1];
            v2->unk_00 = (v2->unk_00 + 1) & 0x1f;
            v2->unk_04 = v4.y;

            MapObject_SetSpriteJumpOffset(mapObj, &v4);
        }
    }

    FieldMap_021EDEB4(mapObj, v3);
    FieldMap_021EC6C0(mapObj, v3);
}
