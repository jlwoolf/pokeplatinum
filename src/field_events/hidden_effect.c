#include "field_events/hidden_effect.h"

#include <nitro.h>
#include <string.h>

#include "struct_decls/map_object.h"
#include "struct_decls/map_object_manager.h"

#include "field/field_system.h"
#include "field/field_system_sub2_t.h"
#include "fieldmap/fieldmap_021D1A94.h"
#include "fieldmap/struct_field_effect_decl.h"
#include "field_events/struct_field_effect.h"

#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "map_object.h"
#include "narc.h"
#include "player_avatar.h"
#include "sound_playback.h"

typedef struct {
    Easy3DObject object;
    Easy3DModel model;
    Easy3DAnim anims[4];
    u32 animCount;
} HiddenEffectModel;

typedef struct {
    HiddenEffectModel model;
    NNSFndAllocator allocator;
    u32 state;
} HiddenEffectSingle;

typedef struct {
    HiddenEffectModel model;
    NNSFndAllocator allocator;
    u32 state;
} HiddenEffectDouble;

typedef struct HiddenEffectTransition_t {
    HiddenEffectModel models[2];
    NNSFndAllocator allocator;
    u32 state;
} HiddenEffectTransition;

typedef struct {
    Easy3DObject object;
    Easy3DAnim anims[4];
    u32 isActive;
} HiddenEffectParticle;

typedef struct {
    Easy3DModel model;
    HiddenEffectParticle particles[16];
    void *animData[4];
    FieldSystem *fieldSystem;
    int spawnTimer;
    fx32 spawnOffsetY;
    fx32 spawnOffsetZ;
    VecFx32 lastPlayerPos;
    NNSFndAllocator allocator;
    u32 state;
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

    Easy3DModel_LoadFrom(&param0->model, param1, param2, HEAP_ID_FIELD1);
    Easy3DObject_Init(&param0->object, &param0->model);

    param0->animCount = param4;

    for (v0 = 0; v0 < param0->animCount; v0++) {
        Easy3DAnim_LoadFrom(&param0->anims[v0], &param0->model, param1, param3 + v0, 4, param5);
        Easy3DObject_AddAnim(&param0->object, &param0->anims[v0]);
    }
}

static void HiddenEffectModel_Free(HiddenEffectModel *param0, NNSFndAllocator *param1)
{
    int v0;

    Easy3DModel_Release(&param0->model);

    for (v0 = 0; v0 < param0->animCount; v0++) {
        Easy3DAnim_Release(&param0->anims[v0], param1);
    }
}

static BOOL HiddenEffectModel_Update(HiddenEffectModel *param0)
{
    int v0;
    BOOL v1 = 1;

    for (v0 = 0; v0 < param0->animCount; v0++) {
        v1 &= Easy3DAnim_Update(&param0->anims[v0], FX32_ONE);
    }

    return v1;
}

static void HiddenEffectModel_UpdateLooped(HiddenEffectModel *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->animCount; v0++) {
        Easy3DAnim_UpdateLooped(&param0->anims[v0], FX32_ONE);
    }
}

static void HiddenEffectModel_Draw(HiddenEffectModel *param0)
{
    Easy3DObject_Draw(&param0->object);
}

static void HiddenEffectSingle_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectSingle));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->model, v2, 3, 0, 3, &v0->allocator);
    NARC_dtor(v2);

    HiddenEffect_SetPositionInFrontOfPlayer(fieldSystem->playerAvatar, &v0->model.object);
    Sound_PlayEffect(SEQ_SE_DP_FW015_sseq);

    v0->state = 0;
}

static void HiddenEffectSingle_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    HiddenEffectModel_Free(&v0->model, &v0->allocator);
}

static void HiddenEffectSingle_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    int v1;
    BOOL v2;

    switch (v0->state) {
    case 0:
        v2 = HiddenEffectModel_Update(&v0->model);

        if (v2 == 1) {
            Easy3DObject_SetVisible(&v0->model.object, 0);
            v0->state++;
        }
        break;
    case 1:
        break;
    default:
        break;
    }
}

static void HiddenEffectSingle_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectSingle *v0 = param2;
    HiddenEffectModel_Draw(&v0->model);
}

FieldEffect *HiddenEffectSingle_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024, sizeof(HiddenEffectSingle), HiddenEffectSingle_Init, HiddenEffectSingle_Free, HiddenEffectSingle_Update, HiddenEffectSingle_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectSingle_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

BOOL HiddenEffectSingle_IsFinished(FieldEffect *param0)
{
    HiddenEffectSingle *v0 = FieldMap_021D1C2C(param0);

    if (v0->state == 1) {
        return 1;
    }

    return 0;
}

static void HiddenEffectDouble_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectDouble));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->model, v2, 8, 4, 4, &v0->allocator);
    NARC_dtor(v2);

    HiddenEffect_SetPositionInFrontOfPlayer(fieldSystem->playerAvatar, &v0->model.object);
    Sound_PlayEffect(SEQ_SE_DP_FW088_sseq);

    v0->state = 0;
}

static void HiddenEffectDoubleAtMapObject_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectDouble));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->model, v2, 8, 4, 4, &v0->allocator);
    HiddenEffect_SetPositionAtMapObject(fieldSystem->mapObjMan, 0, &v0->model.object);

    Sound_PlayEffect(SEQ_SE_DP_FW088_sseq);
    NARC_dtor(v2);

    v0->state = 0;
}

static void HiddenEffectDouble_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    HiddenEffectModel_Free(&v0->model, &v0->allocator);
}

static void HiddenEffectDouble_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    int v1;
    BOOL v2;

    switch (v0->state) {
    case 0:
        v2 = HiddenEffectModel_Update(&v0->model);

        if (v2 == 1) {
            Easy3DObject_SetVisible(&v0->model.object, 0);
            v0->state++;
        }
        break;
    case 1:
        break;
    default:
        break;
    }
}

static void HiddenEffectDouble_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectDouble *v0 = param2;
    HiddenEffectModel_Draw(&v0->model);
}

FieldEffect *HiddenEffectDouble_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectDouble),
        HiddenEffectDouble_Init,
        HiddenEffectDouble_Free,
        HiddenEffectDouble_Update,
        HiddenEffectDouble_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

FieldEffect *HiddenEffectDoubleAtMapObject_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectDouble),
        HiddenEffectDoubleAtMapObject_Init,
        HiddenEffectDouble_Free,
        HiddenEffectDouble_Update,
        HiddenEffectDouble_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectDouble_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

BOOL HiddenEffectDouble_IsFinished(FieldEffect *param0)
{
    HiddenEffectDouble *v0 = FieldMap_021D1C2C(param0);

    if (v0->state == 1) {
        return 1;
    }

    return 0;
}

static void HiddenEffectTransition_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectTransition));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    HiddenEffectModel_Init(&v0->models[0], v2, 14, 12, 2, &v0->allocator);
    HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->models[0].object);

    NARC_dtor(v2);
    Sound_PlayEffect(SEQ_SE_DP_FW463_sseq);

    v0->state = 0;
}

static void HiddenEffectTransition_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        HiddenEffectModel_Free(&v0->models[v1], &v0->allocator);
    }
}

static void HiddenEffectTransition_Update(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    BOOL v1;
    NARC *v2;

    switch (v0->state) {
    case 0:
        v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);
        HiddenEffectModel_Init(&v0->models[1], v2, 11, 9, 2, &v0->allocator);
        NARC_dtor(v2);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->models[1].object);
        Easy3DObject_SetVisible(&v0->models[1].object, 0);
        v0->state++;
    case 1:
        v1 = HiddenEffectModel_Update(&v0->models[0]);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->models[0].object);

        if (v1 == 1) {
            Easy3DObject_SetVisible(&v0->models[1].object, 1);
            Easy3DObject_SetVisible(&v0->models[0].object, 0);
            HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->models[1].object);
            v0->state++;
        }
        break;
    case 2:
        HiddenEffectModel_UpdateLooped(&v0->models[1]);
        HiddenEffect_SetPositionAtPlayer(fieldSystem->playerAvatar, &v0->models[1].object);
        break;
    default:
        break;
    }
}

static void HiddenEffectTransition_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectTransition *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 2; v1++) {
        HiddenEffectModel_Draw(&v0->models[v1]);
    }
}

FieldEffect *HiddenEffectTransition_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectTransition),
        HiddenEffectTransition_Init,
        HiddenEffectTransition_Free,
        HiddenEffectTransition_Update,
        HiddenEffectTransition_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectTransition_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}

static void HiddenEffectParticle_Start(HiddenEffectParticle *param0, PlayerAvatar *const playerAvatar, fx32 param2, fx32 param3)
{
    VecFx32 v0;
    int v1;

    GF_ASSERT(param0->isActive == 0);

    PlayerAvatar_GetPosPtr(playerAvatar, &v0);
    Easy3DObject_SetPosition(&param0->object, v0.x, v0.y + param2, v0.z + param3);

    param0->isActive = 1;

    for (v1 = 0; v1 < 4; v1++) {
        Easy3DAnim_SetFrame(&param0->anims[v1], 0);
    }

    Easy3DObject_SetVisible(&param0->object, 1);
    Sound_PlayEffect(SEQ_SE_DP_UG_023_sseq);
}

static void HiddenEffectParticle_Update(HiddenEffectParticle *param0)
{
    int v0;
    BOOL v1;

    if (param0->isActive == 0) {
        return;
    }

    v1 = 1;

    for (v0 = 0; v0 < 4; v0++) {
        v1 &= Easy3DAnim_Update(&param0->anims[v0], FX32_ONE);
    }

    if (v1 == 1) {
        param0->isActive = 0;
        Easy3DObject_SetVisible(&param0->object, 0);
    }
}

static void HiddenEffectParticle_Init(HiddenEffectParticle *param0, Easy3DModel *param1, NNSFndAllocator *param2, void **param3)
{
    int v0;

    memset(param0, 0, sizeof(HiddenEffectParticle));
    Easy3DObject_Init(&param0->object, param1);

    for (v0 = 0; v0 < 4; v0++) {
        Easy3DAnim_LoadFromData(&param0->anims[v0], param1, param3[v0], param2);
        Easy3DObject_AddAnim(&param0->object, &param0->anims[v0]);
    }

    Easy3DObject_SetVisible(&param0->object, 0);
}

static void HiddenEffectParticle_Free(HiddenEffectParticle *param0, NNSFndAllocator *param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Easy3DAnim_Release(&param0->anims[v0], param1);
    }

    memset(param0, 0, sizeof(HiddenEffectParticle));
}

static void HiddenEffectParticles_UpdateSpawn(HiddenEffectParticles *param0)
{
    VecFx32 v0;

    PlayerAvatar_GetPosPtr(param0->fieldSystem->playerAvatar, &v0);

    if (((v0.x - param0->lastPlayerPos.x) == 0) && (v0.y < param0->lastPlayerPos.y) && (v0.z > param0->lastPlayerPos.z)) {
        param0->spawnOffsetY = 0;
        param0->spawnOffsetZ = (16 * FX32_ONE) * 2;
    } else {
        param0->spawnOffsetY = ((16 * FX32_ONE) * 2);
        param0->spawnOffsetZ = (16 * FX32_ONE);
    }

    param0->lastPlayerPos = v0;
}

static void HiddenEffectParticles_Spawn(HiddenEffectParticles *param0)
{
    int v0;

    HiddenEffectParticles_UpdateSpawn(param0);

    for (v0 = 0; v0 < 16; v0++) {
        if (param0->particles[v0].isActive == 0) {
            HiddenEffectParticle_Start(&param0->particles[v0], param0->fieldSystem->playerAvatar, param0->spawnOffsetY, param0->spawnOffsetZ);
            return;
        }
    }

    GF_ASSERT(FALSE);
}

static void HiddenEffectParticles_Update(HiddenEffectParticles *param0)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        HiddenEffectParticle_Update(&param0->particles[v0]);
    }
}

static void HiddenEffectParticles_Init(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;
    NARC *v2;

    memset(v0, 0, sizeof(HiddenEffectParticles));
    HeapExp_FndInitAllocator(&v0->allocator, HEAP_ID_FIELD1, 32);

    v2 = NARC_ctor(NARC_INDEX_GRAPHIC__HIDEN_EFFECT, HEAP_ID_FIELD1);

    Easy3DModel_LoadFrom(&v0->model, v2, 8, HEAP_ID_FIELD1);

    for (v1 = 0; v1 < 4; v1++) {
        v0->animData[v1] = LoadMemberFromOpenNARC(v2, 4 + v1, 0, HEAP_ID_FIELD1, 0);
    }

    for (v1 = 0; v1 < 16; v1++) {
        HiddenEffectParticle_Init(&v0->particles[v1], &v0->model, &v0->allocator, v0->animData);
    }

    v0->fieldSystem = fieldSystem;
    PlayerAvatar_GetPosPtr(v0->fieldSystem->playerAvatar, &v0->lastPlayerPos);

    v0->state = 0;
    NARC_dtor(v2);
}

static void HiddenEffectParticles_Free(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 16; v1++) {
        HiddenEffectParticle_Free(&v0->particles[v1], &v0->allocator);
    }

    Easy3DModel_Release(&v0->model);

    for (v1 = 0; v1 < 4; v1++) {
        Heap_Free(v0->animData[v1]);
    }
}

static void HiddenEffectParticles_TaskUpdate(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;

    switch (v0->state) {
    case 0:
        v0->spawnTimer--;

        if (v0->spawnTimer < 0) {
            v0->spawnTimer = 4;
            HiddenEffectParticles_Spawn(v0);
        }

        HiddenEffectParticles_Update(v0);
        break;
    default:
        break;
    }
}

static void HiddenEffectParticles_Draw(FieldEffect *param0, FieldSystem *fieldSystem, void *param2)
{
    HiddenEffectParticles *v0 = param2;
    int v1;

    for (v1 = 0; v1 < 16; v1++) {
        Easy3DObject_Draw(&v0->particles[v1].object);
    }
}

FieldEffect *HiddenEffectParticles_New(FieldSystem *fieldSystem)
{
    static const FieldEffectTemplate v0 = {
        1024,
        sizeof(HiddenEffectParticles),
        HiddenEffectParticles_Init,
        HiddenEffectParticles_Free,
        HiddenEffectParticles_TaskUpdate,
        HiddenEffectParticles_Draw
    };
    FieldEffect *v1 = FieldMap_021D1B6C(fieldSystem->unk_04->unk_04, &v0);
    return v1;
}

void HiddenEffectParticles_Delete(FieldEffect *param0)
{
    FieldMap_021D1BEC(param0);
}
