#include "field_events/hidden_effect.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "overlay005/ov5_021D1A94.h"
#include "overlay005/struct_ov5_021D1BEC_decl.h"
#include "field_events/struct_field_effect.h"

#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "map_object.h"
#include "narc.h"
#include "player_avatar.h"
#include "sound_playback.h"

typedef struct {
    Easy3DObject unk_00;
    Easy3DModel unk_78;
    Easy3DAnim unk_88[4];
    u32 unk_D8;
} HiddenEffectModel;

typedef struct {
    HiddenEffectModel unk_00;
    NNSFndAllocator unk_DC;
    u32 unk_EC;
} HiddenEffectSingle;

typedef struct {
    HiddenEffectModel unk_00;
    NNSFndAllocator unk_DC;
    u32 unk_EC;
} HiddenEffectDouble;

typedef struct HiddenEffectTransition_t {
    HiddenEffectModel unk_00[2];
    NNSFndAllocator unk_1B8;
    u32 unk_1C8;
} HiddenEffectTransition;

typedef struct {
    Easy3DObject unk_00;
    Easy3DAnim unk_78[4];
    u32 unk_C8;
} HiddenEffectParticle;

typedef struct {
    Easy3DModel unk_00;
    HiddenEffectParticle unk_10[16];
    void *unk_CD0[4];
    FieldSystem *fieldSystem;
    int unk_CE4;
    fx32 unk_CE8;
    fx32 unk_CEC;
    VecFx32 unk_CF0;
    NNSFndAllocator unk_CFC;
    u32 unk_D0C;
} HiddenEffectParticles;

static void HiddenEffect_SetPositionAtMapObject(MapObjectManager *param0, u32 param1, Easy3DObject *param2)
{
    int v0;
    int v1, v2;
    VecFx32 v3;
    MapObject *v4 = MapObjMan_LocalMapObjByIndex(param0, param1);

    MapObject_GetPosPtr(v4, &v3);

    v1 = MapObject_GetX(v4);
    v2 = MapObject_GetZ(v4);
    v0 = MapObject_GetFacingDir(v4);

    switch (v0) {
    case 0:
        v2--;
        break;
    case 1:
        v2++;
        break;
    case 2:
        v1--;
        break;
    case 3:
        v1++;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    Easy3DObject_SetPosition(param2, (((v1) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1), v3.y, (((v2) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1));
}

static void HiddenEffect_SetPositionInFrontOfPlayer(PlayerAvatar *const playerAvatar, Easy3DObject *param1)
{
    int v0;
    int v1, v2;
    VecFx32 v3;

    PlayerAvatar_GetPosPtr(playerAvatar, &v3);

    v1 = PlayerAvatar_GetXPos(playerAvatar);
    v2 = PlayerAvatar_GetZPos(playerAvatar);
    v0 = PlayerAvatar_GetFacingDir(playerAvatar);

    switch (v0) {
    case 0:
        v2--;
        break;
    case 1:
        v2++;
        break;
    case 2:
        v1--;
        break;
    case 3:
        v1++;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    Easy3DObject_SetPosition(param1, (((v1) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1), v3.y, (((v2) << 4) * FX32_ONE) + ((16 * FX32_ONE) >> 1));
}

static void HiddenEffect_SetPositionAtPlayer(PlayerAvatar *const playerAvatar, Easy3DObject *param1)
{
    VecFx32 v0;

    PlayerAvatar_GetPosPtr(playerAvatar, &v0);
    Easy3DObject_SetPosition(param1, v0.x, v0.y, v0.z);
}

static void HiddenEffectModel_Init(HiddenEffectModel *param0, NARC *param1, u32 param2, u32 param3, int param4, NNSFndAllocator *param5)
{
    int v0;

    memset(param0, 0, sizeof(HiddenEffectModel));

    Easy3DModel_LoadFrom(&param0->unk_78, param1, param2, HEAP_ID_FIELD1);
    Easy3DObject_Init(&param0->unk_00, &param0->unk_78);

    param0->unk_D8 = param4;

    for (v0 = 0; v0 < param0->unk_D8; v0++) {
        Easy3DAnim_LoadFrom(&param0->unk_88[v0], &param0->unk_78, param1, param3 + v0, 4, param5);
        Easy3DObject_AddAnim(&param0->unk_00, &param0->unk_88[v0]);
    }
}

static void HiddenEffectModel_Free(HiddenEffectModel *param0, NNSFndAllocator *param1)
{
    int v0;

    Easy3DModel_Release(&param0->unk_78);

    for (v0 = 0; v0 < param0->unk_D8; v0++) {
        Easy3DAnim_Release(&param0->unk_88[v0], param1);
    }
}

static BOOL HiddenEffectModel_Update(HiddenEffectModel *param0)
{
    int v0;
    BOOL v1 = 1;

    for (v0 = 0; v0 < param0->unk_D8; v0++) {
        v1 &= Easy3DAnim_Update(&param0->unk_88[v0], FX32_ONE);
    }

    return v1;
}

static void HiddenEffectModel_UpdateLooped(HiddenEffectModel *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_D8; v0++) {
        Easy3DAnim_UpdateLooped(&param0->unk_88[v0], FX32_ONE);
    }
}

static void HiddenEffectModel_Draw(HiddenEffectModel *param0)
{
    Easy3DObject_Draw(&param0->unk_00);
}

static void HiddenEffectSingle_Init(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectSingle));
    HeapExp_FndInitAllocator(&v0->unk_DC, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->unk_00, v2, 3, 0, 3, &v0->unk_DC);
    NARC_dtor(v2);

    HiddenEffect_SetPositionInFrontOfPlayer(fieldSystem->playerAvatar, &v0->unk_00.unk_00);
    Sound_PlayEffect(SEQ_SE_DP_FW015_sseq);

    v0->unk_EC = 0;
}

static void HiddenEffectSingle_Free(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    HiddenEffectModel_Free(&v0->unk_00, &v0->unk_DC);
}

static void HiddenEffectSingle_Update(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    int v1;
    BOOL v2;

    switch (v0->unk_EC) {
    case 0:
        v2 = HiddenEffectModel_Update(&v0->unk_00);

        if (v2 == 1) {
            Easy3DObject_SetVisible(&v0->unk_00.unk_00, 0);
            v0->unk_EC++;
        }
        break;
    case 1:
        break;
    default:
        break;
    }
}

static void HiddenEffectSingle_Draw(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    HiddenEffectModel_Draw(&v0->unk_00);
}

UnkStruct_ov5_021D1BEC *HiddenEffectSingle_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024, sizeof(HiddenEffectSingle), HiddenEffectSingle_Init, HiddenEffectSingle_Free, HiddenEffectSingle_Update, HiddenEffectSingle_Draw
    };
    UnkStruct_ov5_021D1BEC *v1 = ov5_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectSingle_Delete(UnkStruct_ov5_021D1BEC *param0)
{
    ov5_021D1BEC(param0);
}

BOOL HiddenEffectSingle_IsFinished(UnkStruct_ov5_021D1BEC *param0)
{
    HiddenEffectSingle *v0 = ov5_021D1C2C(param0);

    if (v0->unk_EC == 1) {
        return 1;
    }

    return 0;
}

static void HiddenEffectDouble_Init(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectDouble));
    HeapExp_FndInitAllocator(&v0->unk_DC, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->unk_00, v2, 8, 4, 4, &v0->unk_DC);
    NARC_dtor(v2);

    HiddenEffect_SetPositionInFrontOfPlayer(fieldSystem->playerAvatar, &v0->unk_00.unk_00);
    Sound_PlayEffect(SEQ_SE_DP_FW088_sseq);

    v0->unk_EC = 0;
}

static void HiddenEffectDoubleAtMapObject_Init(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectDouble));
    HeapExp_FndInitAllocator(&v0->unk_DC, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->unk_00, v2, 8, 4, 4, &v0->unk_DC);
    HiddenEffect_SetPositionAtMapObject(fieldSystem->mapObjMan, 0, &v0->unk_00.unk_00);

    Sound_PlayEffect(SEQ_SE_DP_FW088_sseq);
    NARC_dtor(v2);

    v0->unk_EC = 0;
}

static void HiddenEffectDouble_Free(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    HiddenEffectModel_Free(&v0->unk_00, &v0->unk_DC);
}

static void HiddenEffectDouble_Update(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    BOOL v2;

    switch (v0->unk_EC) {
    case 0:
        v2 = HiddenEffectModel_Update(&v0->unk_00);

        if (v2 == 1) {
            Easy3DObject_SetVisible(&v0->unk_00.unk_00, 0);
            v0->unk_EC++;
        }
        break;
    case 1:
        break;
    default:
        break;
    }
}

static void HiddenEffectDouble_Draw(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    HiddenEffectModel_Draw(&v0->unk_00);
}

UnkStruct_ov5_021D1BEC *HiddenEffectDouble_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectDouble),
        HiddenEffectDouble_Init,
        HiddenEffectDouble_Free,
        HiddenEffectDouble_Update,
        HiddenEffectDouble_Draw
    };
    UnkStruct_ov5_021D1BEC *v1 = ov5_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

UnkStruct_ov5_021D1BEC *HiddenEffectDoubleAtMapObject_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectDouble),
        HiddenEffectDoubleAtMapObject_Init,
        HiddenEffectDouble_Free,
        HiddenEffectDouble_Update,
        HiddenEffectDouble_Draw
    };
    UnkStruct_ov5_021D1BEC *v1 = ov5_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectDouble_Delete(UnkStruct_ov5_021D1BEC *param0)
{
    ov5_021D1BEC(param0);
}

BOOL HiddenEffectDouble_IsFinished(UnkStruct_ov5_021D1BEC *param0)
{
    HiddenEffectDouble *v0 = ov5_021D1C2C(param0);

    if (v0->unk_EC == 1) {
        return 1;
    }

    return 0;
}

static void HiddenEffectTransition_Init(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectTransition));
    HeapExp_FndInitAllocator(&v0->unk_1B8, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->unk_00[0], v2, 14, 12, 2, &v0->unk_1B8);
    HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->unk_00[0].unk_00);

    NARC_dtor(v2);
    Sound_PlayEffect(SEQ_SE_DP_FW463_sseq);

    v0->unk_1C8 = 0;
}

static void HiddenEffectTransition_Free(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        HiddenEffectModel_Free(&v0->unk_00[v1], &v0->unk_1B8);
    }
}

static void HiddenEffectTransition_Update(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    BOOL v1;
    NARC *v2;

    switch (v0->unk_1C8) {
    case 0:
        v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);
        HiddenEffectModel_Init(&v0->unk_00[1], v2, 11, 9, 2, &v0->unk_1B8);
        NARC_dtor(v2);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->unk_00[1].unk_00);
        Easy3DObject_SetVisible(&v0->unk_00[1].unk_00, 0);
        v0->unk_1C8++;
    case 1:
        v1 = HiddenEffectModel_Update(&v0->unk_00[0]);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->unk_00[0].unk_00);

        if (v1 == 1) {
            Easy3DObject_SetVisible(&v0->unk_00[1].unk_00, 1);
            Easy3DObject_SetVisible(&v0->unk_00[0].unk_00, 0);
            HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->unk_00[1].unk_00);
            v0->unk_1C8++;
        }
        break;
    case 2:
        HiddenEffectModel_UpdateLooped(&v0->unk_00[1]);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->unk_00[1].unk_00);
        break;
    default:
        break;
    }
}

static void HiddenEffectTransition_Draw(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        HiddenEffectModel_Draw(&v0->unk_00[v1]);
    }
}

UnkStruct_ov5_021D1BEC *HiddenEffectTransition_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectTransition),
        HiddenEffectTransition_Init,
        HiddenEffectTransition_Free,
        HiddenEffectTransition_Update,
        HiddenEffectTransition_Draw
    };
    UnkStruct_ov5_021D1BEC *v1 = ov5_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectTransition_Delete(UnkStruct_ov5_021D1BEC *param0)
{
    ov5_021D1BEC(param0);
}

static void HiddenEffectParticle_Start(HiddenEffectParticle *param0, PlayerAvatar *const playerAvatar, fx32 param2, fx32 param3)
{
    VecFx32 v0;
    int v1;

    GF_ASSERT(param0->unk_C8 == 0);

    PlayerAvatar_GetPosPtr(playerAvatar, &v0);
    Easy3DObject_SetPosition(&param0->unk_00, v0.x, v0.y + param2, v0.z + param3);

    param0->unk_C8 = 1;

    for (v1 = 0; v1 < 4; v1++) {
        Easy3DAnim_SetFrame(&param0->unk_78[v1], 0);
    }

    Easy3DObject_SetVisible(&param0->unk_00, 1);
    Sound_PlayEffect(SEQ_SE_DP_UG_023_sseq);
}

static void HiddenEffectParticle_Update(HiddenEffectParticle *param0)
{
    int v0;
    BOOL v1;

    if (param0->unk_C8 == 0) {
        return;
    }

    v1 = 1;

    for (v0 = 0; v0 < 4; v0++) {
        v1 &= Easy3DAnim_Update(&param0->unk_78[v0], FX32_ONE);
    }

    if (v1 == 1) {
        param0->unk_C8 = 0;
        Easy3DObject_SetVisible(&param0->unk_00, 0);
    }
}

static void HiddenEffectParticle_Init(HiddenEffectParticle *param0, Easy3DModel *param1, NNSFndAllocator *param2, void **param3)
{
    int v0;

    memset(param0, 0, sizeof(HiddenEffectParticle));
    Easy3DObject_Init(&param0->unk_00, param1);

    for (v0 = 0; v0 < 4; v0++) {
        Easy3DAnim_LoadFromData(&param0->unk_78[v0], param1, param3[v0], param2);
        Easy3DObject_AddAnim(&param0->unk_00, &param0->unk_78[v0]);
    }

    Easy3DObject_SetVisible(&param0->unk_00, 0);
}

static void HiddenEffectParticle_Free(HiddenEffectParticle *param0, NNSFndAllocator *param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Easy3DAnim_Release(&param0->unk_78[v0], param1);
    }

    memset(param0, 0, sizeof(HiddenEffectParticle));
}

static void HiddenEffectParticles_UpdateSpawn(HiddenEffectParticles *param0)
{
    VecFx32 v0;

    PlayerAvatar_GetPosPtr(param0->fieldSystem->playerAvatar, &v0);

    if (((v0.x - param0->unk_CF0.x) == 0) && (v0.y < param0->unk_CF0.y) && (v0.z > param0->unk_CF0.z)) {
        param0->unk_CE8 = 0;
        param0->unk_CEC = (16 * FX32_ONE) * 2;
    } else {
        param0->unk_CE8 = ((16 * FX32_ONE) * 2);
        param0->unk_CEC = (16 * FX32_ONE);
    }

    param0->unk_CF0 = v0;
}

static void HiddenEffectParticles_Spawn(HiddenEffectParticles *param0)
{
    int v0;

    HiddenEffectParticles_UpdateSpawn(param0);

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->unk_10[v0].unk_C8 == 0) {
            HiddenEffectParticle_Start(&param0->unk_10[v0], param0->fieldSystem->playerAvatar, param0->unk_CE8, param0->unk_CEC);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void HiddenEffectParticles_Update(HiddenEffectParticles *param0)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        HiddenEffectParticle_Update(&param0->unk_10[v0]);
    }
}

static void HiddenEffectParticles_Init(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectParticles));
    HeapExp_FndInitAllocator(&v0->unk_CFC, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    Easy3DModel_LoadFrom(&v0->unk_00, v2, 8, HEAP_ID_FIELD1);

    for (v1 = 0; v1 < 4; v1++) {
        v0->unk_CD0[v1] = LoadMemberFromOpenNARC(v2, 4 + v1, 0, HEAP_ID_FIELD1, 0);
    }

    for (v1 = 0; v1 < 16; v1++) {
        HiddenEffectParticle_Init(&v0->unk_10[v1], &v0->unk_00, &v0->unk_CFC, v0->unk_CD0);
    }

    v0->fieldSystem = fieldSystem;
    PlayerAvatar_GetPosPtr(v0->fieldSystem->playerAvatar, &v0->unk_CF0);

    v0->unk_D0C = 0;
    NARC_dtor(v2);
}

static void HiddenEffectParticles_Free(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 16; v1++) {
        HiddenEffectParticle_Free(&v0->unk_10[v1], &v0->unk_CFC);
    }

    Easy3DModel_Release(&v0->unk_00);

    for (v1 = 0; v1 < 4; v1++) {
        Heap_Free(v0->unk_CD0[v1]);
    }
}

static void HiddenEffectParticles_TaskUpdate(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;

    switch (v0->unk_D0C) {
    case 0:
        v0->unk_CE4--;

        if (v0->unk_CE4 < 0) {
            v0->unk_CE4 = 4;
            HiddenEffectParticles_Spawn(v0);
        }

        HiddenEffectParticles_Update(v0);
        break;
    default:
        break;
    }
}

static void HiddenEffectParticles_Draw(UnkStruct_ov5_021D1BEC *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 16; v1++) {
        Easy3DObject_Draw(&v0->unk_10[v1].unk_00);
    }
}

UnkStruct_ov5_021D1BEC *HiddenEffectParticles_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectParticles),
        HiddenEffectParticles_Init,
        HiddenEffectParticles_Free,
        HiddenEffectParticles_TaskUpdate,
        HiddenEffectParticles_Draw
    };
    UnkStruct_ov5_021D1BEC *v1 = ov5_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectParticles_Delete(UnkStruct_ov5_021D1BEC *param0)
{
    ov5_021D1BEC(param0);
}
