#include "fieldmap/fieldmap_021F61BC.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"

#include "fieldmap/field_effect_manager.h"

#include "fx_util.h"
#include "map_object.h"
#include "map_object_move.h"
#include "map_tile_behavior.h"
#include "overworld_anim_manager.h"
#include "player_avatar.h"
#include "simple3d.h"

typedef struct {
    FieldEffectManager *unk_00;
    Simple3DModel unk_04;
    Simple3DRenderObj unk_18;
} FieldEffectRenderer0EContext;

typedef struct {
    FieldEffectManager *unk_00;
    FieldEffectRenderer0EContext *unk_04;
    PlayerAvatar *playerAvatar;
} FieldEffectRenderer0EParams;

typedef struct {
    int unk_00;
    int unk_04;
    u8 unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    FieldEffectRenderer0EParams unk_24;
} FieldEffectRenderer0EAnim;

static void FieldMap_021F61E8(FieldEffectRenderer0EContext *param0);
static void FieldMap_021F620C(FieldEffectRenderer0EContext *param0);
static int FieldMap_021F6414(u8 param0);

static const OverworldAnimManagerFuncs Unk_FieldMap_02200C10;
static const VecFx32 Unk_FieldMap_02200C24[4][2];

void *FieldMap_021F61BC(FieldEffectManager *param0)
{
    FieldEffectRenderer0EContext *v0 = FieldEffectManager_HeapAllocInit(param0, (sizeof(FieldEffectRenderer0EContext)), 0, 0);
    v0->unk_00 = param0;

    FieldMap_021F61E8(v0);

    return v0;
}

void FieldMap_021F61D8(void *param0)
{
    FieldEffectRenderer0EContext *v0 = param0;

    FieldMap_021F620C(v0);
    FieldEffectManager_HeapFree(v0);
}

static void FieldMap_021F61E8(FieldEffectRenderer0EContext *param0)
{
    FieldEffectManager_LoadModel(param0->unk_00, &param0->unk_04, 0, 80, 0);
    Simple3D_CreateRenderObject(&param0->unk_18, &param0->unk_04);
}

static void FieldMap_021F620C(FieldEffectRenderer0EContext *param0)
{
    Simple3D_FreeModel(&param0->unk_04);
}

void FieldMap_021F6218(PlayerAvatar *playerAvatar)
{
    int v0 = 0, v1;
    FieldEffectRenderer0EParams v2;
    FieldEffectManager *v3;
    MapObject *v4;
    VecFx32 v5 = { 0, 0, 0 };

    v4 = PlayerAvatar_GetMapObject(playerAvatar);
    v3 = MapObject_GetFieldEffectManager(v4);

    v2.unk_00 = v3;
    v2.unk_04 = FieldEffectManager_GetRendererContext(v3, 14);
    v2.playerAvatar = playerAvatar;

    v1 = MapObject_CalculateTaskPriority(v4, 2);
    FieldEffectManager_InitAnimManager(v3, &Unk_FieldMap_02200C10, &v5, v0, &v2, v1);
}

static int FieldMap_021F6264(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0EAnim *v0;
    MapObject *v1;
    const FieldEffectRenderer0EParams *v2;

    v0 = param1;
    v2 = OverworldAnimManager_GetUserData(param0);
    v0->unk_24 = *v2;
    v1 = PlayerAvatar_GetMapObject(v2->playerAvatar);

    v0->unk_04 = -1;
    v0->unk_14 = MapObject_GetLocalID(v1);
    v0->unk_18 = MapObject_GetMapHeaderID(v1);

    return 1;
}

static void FieldMap_021F629C(OverworldAnimManager *param0, void *param1)
{
    return;
}

static void FieldMap_021F62A0(OverworldAnimManager *param0, void *param1)
{
    int v0;
    FieldEffectRenderer0EAnim *v1 = param1;
    PlayerAvatar *playerAvatar = v1->unk_24.playerAvatar;
    MapObject *v3 = PlayerAvatar_GetMapObject(playerAvatar);

    if (MapObject_MatchesLocalIDAndMap(v3, v1->unk_14, v1->unk_18) == 0) {
        FieldEffectManager_FinishAnimManager(param0);
        return;
    }

    v0 = v1->unk_04;

    v1->unk_08 = MapObject_GetCurrTileBehavior(v3);
    v1->unk_04 = FieldMap_021F6414(v1->unk_08);
    v1->unk_00 = 0;

    if ((v1->unk_04 == -1) || (v1->unk_04 != PlayerAvatar_GetFacingDir(playerAvatar))) {
        v1->unk_1C = 0;
        v1->unk_20 = 0;
        v1->unk_00 = 1;
        return;
    }

    if (v0 != v1->unk_04) {
        v1->unk_1C = 0;
        v1->unk_20 = 0;
    }

    {
        VecFx32 v4, v5;
        int v6 = MapObject_GetX(v3) + MapObject_GetDxFromDir(v1->unk_04);
        int v7 = MapObject_GetZ(v3) + MapObject_GetDzFromDir(v1->unk_04);

        VecFx32_SetPosFromMapCoords(v6, v7, &v5);
        MapObject_GetPosPtr(v3, &v4);
        v5.y = v4.y;
        OverworldAnimManager_SetPosition(param0, &v5);
    }

    {
        v1->unk_1C++;

        if (v1->unk_1C > 15) {
            v1->unk_1C = 0;
            v1->unk_20++;
            v1->unk_20 %= 2;
        }
    }
}

static void FieldMap_021F636C(OverworldAnimManager *param0, void *param1)
{
    FieldEffectRenderer0EAnim *v0 = param1;

    if ((v0->unk_00 == 1) || (v0->unk_04 == -1)) {
        return;
    }

    {
        u32 v1 = 0;
        MtxFx33 v2;
        VecFx32 v3, v4 = { FX32_ONE, FX32_ONE, FX32_ONE };
        Simple3DRenderObj *v5 = &v0->unk_24.unk_04->unk_18;
        const VecFx32 *v6 = &Unk_FieldMap_02200C24[v0->unk_04][v0->unk_20];

        switch (v0->unk_04) {
        case 0:
            v1 = 180;
            break;
        case 1:
            break;
        case 2:
            v1 = 270;
            break;
        case 3:
            v1 = 90;
            break;
        }

        MTX_Rot33Angles(&v2, 0, v1, 0);
        OverworldAnimManager_GetPosition(param0, &v3);

        v3.x += v6->x;
        v3.y += v6->y;
        v3.z += v6->z;

        Simple3D_DrawRenderObj(v5, &v3, &v4, &v2);
    }
}

static int FieldMap_021F6414(u8 param0)
{
    if (TileBehavior_IsWarpEntranceNorth(param0)) {
        return 0;
    }

    if (TileBehavior_IsWarpEntranceSouth(param0)) {
        return 1;
    }

    if (TileBehavior_IsWarpEntranceWest(param0)) {
        return 2;
    }

    if (TileBehavior_IsWarpEntranceEast(param0)) {
        return 3;
    }

    return -1;
}

static const OverworldAnimManagerFuncs Unk_FieldMap_02200C10 = {
    (sizeof(FieldEffectRenderer0EAnim)),
    FieldMap_021F6264,
    FieldMap_021F629C,
    FieldMap_021F62A0,
    FieldMap_021F636C
};

static const VecFx32 Unk_FieldMap_02200C24[4][2] = {
    {
        { 0x0, 0x0, 0x0 },
        { 0x0, 0x0, -(FX32_ONE * 2) },
    },
    {
        { 0x0, 0x0, 0x0 },
        { 0x0, 0x0, (FX32_ONE * 2) },
    },
    {
        { 0x0, 0x0, 0x0 },
        { -(FX32_ONE * 2), 0x0, 0x0 },
    },
    {
        { 0x0, 0x0, 0x0 },
        { (FX32_ONE * 2), 0x0, 0x0 },
    },
};
