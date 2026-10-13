#include "wifi_lobby_map/wifi_lobby_map_02260B44.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_lobby_map/funcptr_wifi_lobby_map_02261C60.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C700.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_model_table.h"

#include "easy3d.h"
#include "easy3d_object.h"
#include "graphics.h"
#include "heap.h"
#include "math_util.h"
#include "narc.h"

typedef struct {
    BOOL initialized;
    Easy3DObject objects[2];
    u32 animAdded[5];
    fx32 animFrame[5];
} WiFiLobbyMapObjectSet;

typedef struct {
    Easy3DModel models[2];
    Easy3DAnim anims[5];
    BOOL animLoaded[5];
} WiFiLobbyMapModelSet;

typedef struct WiFiLobbyMapEffect_t {
    u8 active;
    u8 animIndex;
    u8 modelIndex;
    u8 unk_03;
    Easy3DObject object;
    u32 animFlags[4];
    fx32 animFrames[4];
    VecFx32 basePos;
    VecFx32 offset;
} WiFiLobbyMapEffect;

typedef struct {
    Easy3DModel models[2];
    void *data[2][3];
    Easy3DAnim anims[2][4];
} WiFiLobbyMapEffectModelSet;

typedef struct WiFiLobbyMapCharacter_t {
    u16 active;
    u16 modelIndex;
    Easy3DObject object;
    Easy3DAnim anims[3];
    u8 animActive[3];
    u8 unk_BB;
    u8 animMode[3];
    u8 unk_BF;
    fx32 animFrame[3];
    u8 delayRange;
    u8 animDelay[3];
    UnkFuncPtr_wifi_lobby_map_02261C60 animCallback[3];
    fx32 animSpeed;
    u8 alphaOverride;
    u8 drawAlpha;
    u8 restoreAlpha;
    u8 unk_E3;
} WiFiLobbyMapCharacter;

typedef struct {
    Easy3DModel models[18];
    void *data[18][3];
} WiFiLobbyMapCharacterModelSet;

typedef struct WiFiLobbyMapModelManager_t {
    WiFiLobbyMapObjectSet objects;
    WiFiLobbyMapEffect *effects;
    WiFiLobbyMapCharacter *characters;
    u8 effectCount;
    u8 characterCount;
    u8 lobbyStyle;
    u8 lobbyType;
    BOOL loaded;
    WiFiLobbyMapModelSet models;
    WiFiLobbyMapEffectModelSet effectModels;
    WiFiLobbyMapCharacterModelSet characterModels;
    NNSFndAllocator allocator;
} WiFiLobbyMapModelManager;

static WiFiLobbyMapModelTable *wifi_lobby_map_022613F4(int param0, int param1, enum HeapID heapID);
static void wifi_lobby_map_02261418(WiFiLobbyMapModelTable *param0);
static void wifi_lobby_map_0226146C(Easy3DModel *param0);
static void wifi_lobby_map_02261474(fx32 *param0, const Easy3DAnim *param1, fx32 param2);
static BOOL wifi_lobby_map_02261498(fx32 *param0, const Easy3DAnim *param1, fx32 param2);
static void wifi_lobby_map_022614C0(fx32 *param0, const Easy3DAnim *param1, fx32 param2);
static BOOL wifi_lobby_map_022614DC(fx32 *param0, const Easy3DAnim *param1, fx32 param2);
static void wifi_lobby_map_022614F4(WiFiLobbyMapModelSet *param0, NARC *param1, const WiFiLobbyMapModelTable *param2, u32 heapID, NNSFndAllocator *param4);
static void wifi_lobby_map_022615A4(WiFiLobbyMapModelSet *param0, NNSFndAllocator *param1);
static void wifi_lobby_map_022615E8(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1);
static void wifi_lobby_map_02261664(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1);
static void wifi_lobby_map_022616B0(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1);
static void wifi_lobby_map_022616FC(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1);
static WiFiLobbyMapEffect *wifi_lobby_map_02261718(WiFiLobbyMapModelManager *param0);
static void wifi_lobby_map_0226174C(WiFiLobbyMapEffectModelSet *param0, NARC *param1, NNSFndAllocator *param2, const WiFiLobbyMapModelTable *param3, u32 param4);
static void wifi_lobby_map_022618C8(WiFiLobbyMapEffectModelSet *param0, NNSFndAllocator *param1);
static void wifi_lobby_map_02261968(WiFiLobbyMapEffect *param0, WiFiLobbyMapEffectModelSet *param1);
static void wifi_lobby_map_022619F4(WiFiLobbyMapEffect *param0, WiFiLobbyMapEffectModelSet *param1);
static WiFiLobbyMapCharacter *wifi_lobby_map_02261AF0(WiFiLobbyMapModelManager *param0);
static void wifi_lobby_map_02261B24(WiFiLobbyMapCharacterModelSet *param0, NARC *param1, NNSFndAllocator *param2, const WiFiLobbyMapModelTable *param3, u32 param4);
static void wifi_lobby_map_02261BB4(WiFiLobbyMapCharacterModelSet *param0, NNSFndAllocator *param1);
static void wifi_lobby_map_02261C04(WiFiLobbyMapCharacterModelSet *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_02261C60(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1);

WiFiLobbyMapModelManager *wifi_lobby_map_02260B44(u32 param0, u32 param1, u32 heapID, u32 heapID2)
{
    WiFiLobbyMapModelManager *v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapModelManager));
    memset(v0, 0, sizeof(WiFiLobbyMapModelManager));

    v0->effects = Heap_Alloc(heapID, sizeof(WiFiLobbyMapEffect) * param0);
    v0->characters = Heap_Alloc(heapID, sizeof(WiFiLobbyMapCharacter) * param1);

    memset(v0->effects, 0, sizeof(WiFiLobbyMapEffect) * param0);
    memset(v0->characters, 0, sizeof(WiFiLobbyMapCharacter) * param1);

    v0->effectCount = param0;
    v0->characterCount = param1;

    return v0;
}

void wifi_lobby_map_02260BB8(WiFiLobbyMapModelManager *param0)
{
    if (param0->loaded) {
        wifi_lobby_map_02260D80(param0);
    }

    Heap_Free(param0->effects);
    Heap_Free(param0->characters);
    Heap_Free(param0);
}

void wifi_lobby_map_02260BE8(WiFiLobbyMapModelManager *param0)
{
    wifi_lobby_map_022616B0(&param0->objects, &param0->models);

    {
        int v0;

        for (v0 = 0; v0 < param0->effectCount; v0++) {
            wifi_lobby_map_02261968(&param0->effects[v0], &param0->effectModels);
        }
    }

    {
        int v1;

        for (v1 = 0; v1 < param0->characterCount; v1++) {
            wifi_lobby_map_02261C60(param0, &param0->characters[v1]);
        }
    }
}

void wifi_lobby_map_02260C50(WiFiLobbyMapModelManager *param0)
{
    int v0;

    GF_ASSERT(param0);
    GF_ASSERT(param0->characters);
    GF_ASSERT(param0->effects);

    wifi_lobby_map_022616FC(&param0->objects, &param0->models);

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        wifi_lobby_map_02261C04(&param0->characterModels, &param0->characters[v0]);
    }

    for (v0 = 0; v0 < param0->effectCount; v0++) {
        wifi_lobby_map_022619F4(&param0->effects[v0], &param0->effectModels);
    }
}

void wifi_lobby_map_02260CE0(WiFiLobbyMapModelManager *param0)
{
    return;
}

void wifi_lobby_map_02260CE4(WiFiLobbyMapModelManager *param0, int param1, int param2, u32 heapID, u32 heapID2)
{
    NARC *v0;
    WiFiLobbyMapModelTable *v1;

    param0->lobbyType = param2;
    param0->lobbyStyle = param1;

    v1 = wifi_lobby_map_022613F4(param1, param2, heapID);
    v0 = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_LOBBY, heapID);

    HeapExp_FndInitAllocator(&param0->allocator, heapID2, 4);

    wifi_lobby_map_022614F4(&param0->models, v0, v1, heapID2, &param0->allocator);
    wifi_lobby_map_02261B24(&param0->characterModels, v0, &param0->allocator, v1, heapID2);
    wifi_lobby_map_0226174C(&param0->effectModels, v0, &param0->allocator, v1, heapID2);

    NARC_dtor(v0);

    wifi_lobby_map_02261418(v1);
    wifi_lobby_map_022615E8(&param0->objects, &param0->models);

    param0->loaded = 1;
}

void wifi_lobby_map_02260D80(WiFiLobbyMapModelManager *param0)
{
    wifi_lobby_map_02261664(&param0->objects, &param0->models);
    wifi_lobby_map_022615A4(&param0->models, &param0->allocator);
    wifi_lobby_map_02261BB4(&param0->characterModels, &param0->allocator);
    wifi_lobby_map_022618C8(&param0->effectModels, &param0->allocator);

    param0->loaded = 0;
}

void wifi_lobby_map_02260DC8(WiFiLobbyMapModelManager *param0)
{
    if (param0->models.animLoaded[4] == 1) {
        if (param0->objects.animAdded[4] == 0) {
            param0->objects.animAdded[4] = 1;
            Easy3DObject_AddAnim(&param0->objects.objects[0], &param0->models.anims[4]);
        }
    }
}

void wifi_lobby_map_02260DF4(WiFiLobbyMapModelManager *param0)
{
    if (param0->models.animLoaded[4] == 1) {
        if (param0->objects.animAdded[4] == 1) {
            Easy3DObject_RemoveAnim(&param0->objects.objects[0], &param0->models.anims[4]);
            param0->objects.animAdded[4] = 0;
        }
    }
}

WiFiLobbyMapEffect *wifi_lobby_map_02260E20(WiFiLobbyMapModelManager *param0, int param1, int param2, const VecFx32 *param3)
{
    WiFiLobbyMapEffect *v0;

    GF_ASSERT(param1 <= 2);
    GF_ASSERT(param2 <= 3);

    v0 = wifi_lobby_map_02261718(param0);

    Easy3DObject_Init(&v0->object, &param0->effectModels.models[param1]);
    Easy3DObject_SetVisible(&v0->object, 1);

    wifi_lobby_map_02260EA0(v0, param3);
    {
        VecFx32 v1 = { 0, 0, 0 };
        wifi_lobby_map_02260EE4(v0, &v1);
    }

    v0->animIndex = param2;
    v0->modelIndex = param1;
    v0->active = 1;

    {
        v0->animFlags[0] = 1;
        v0->animFlags[2] = 1;
    }

    return v0;
}

void wifi_lobby_map_02260E8C(WiFiLobbyMapEffect *param0)
{
    Easy3DObject_SetVisible(&param0->object, 0);

    param0->active = 0;
}

void wifi_lobby_map_02260EA0(WiFiLobbyMapEffect *param0, const VecFx32 *param1)
{
    param0->basePos = *param1;
    Easy3DObject_SetPosition(&param0->object, param0->basePos.x + param0->offset.x, param0->basePos.y + param0->offset.y, param0->basePos.z + param0->offset.z);
}

void wifi_lobby_map_02260EE4(WiFiLobbyMapEffect *param0, const VecFx32 *param1)
{
    param0->offset = *param1;
    Easy3DObject_SetPosition(&param0->object, param0->basePos.x + param0->offset.x, param0->basePos.y + param0->offset.y, param0->basePos.z + param0->offset.z);
}

void wifi_lobby_map_02260F28(const WiFiLobbyMapEffect *param0, VecFx32 *param1)
{
    Easy3DObject_GetPosition(&param0->object, &param1->x, &param1->y, &param1->z);
}

void wifi_lobby_map_02260F38(WiFiLobbyMapEffect *param0, BOOL param1)
{
    Easy3DObject_SetVisible(&param0->object, param1);
}

BOOL wifi_lobby_map_02260F44(WiFiLobbyMapEffect *param0)
{
    if (param0->animFlags[1] == 0) {
        param0->animFlags[1] = 1;
        return 1;
    }

    return 0;
}

BOOL wifi_lobby_map_02260F5C(WiFiLobbyMapEffect *param0)
{
    if (param0->animFlags[3] == 0) {
        param0->animFlags[3] = 1;
        return 1;
    }

    return 0;
}

void wifi_lobby_map_02260F74(WiFiLobbyMapEffect *param0, u16 param1)
{
    Easy3DObject_SetRotation(&param0->object, param1, 0);
}

BOOL wifi_lobby_map_02260F80(const WiFiLobbyMapEffect *param0)
{
    return param0->animFlags[1];
}

BOOL wifi_lobby_map_02260F88(const WiFiLobbyMapEffect *param0)
{
    return param0->animFlags[3];
}

WiFiLobbyMapCharacter *wifi_lobby_map_02260F90(WiFiLobbyMapModelManager *param0, int param1, u32 param2, u32 param3)
{
    WiFiLobbyMapCharacter *v0;
    int v1;

    v0 = wifi_lobby_map_02261AF0(param0);

    Easy3DObject_Init(&v0->object, &param0->characterModels.models[param1]);

    for (v1 = 0; v1 < 3; v1++) {
        if (param0->characterModels.data[param1][v1] != NULL) {
            Easy3DAnim_LoadFromData(&v0->anims[v1], &param0->characterModels.models[param1], param0->characterModels.data[param1][v1], &param0->allocator);
        }
    }

    Easy3DObject_SetVisible(&v0->object, 1);

    {
        WiFi2DCharPosition v2;

        v2.x = (param2) * 16;
        v2.y = (param3) * 16;

        wifi_lobby_map_022610BC(v0, v2);
    }

    v0->active = 1;
    v0->modelIndex = param1;
    v0->delayRange = 20;
    v0->animSpeed = FX32_ONE;
    v0->alphaOverride = 0;
    v0->drawAlpha = 31;
    v0->restoreAlpha = 31;

    return v0;
}

void wifi_lobby_map_02261058(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1)
{
    int v0;

    Easy3DObject_SetVisible(&param1->object, 0);

    for (v0 = 0; v0 < 3; v0++) {
        if (param0->characterModels.data[param1->modelIndex][v0] != NULL) {
            Easy3DAnim_LoadFromData(&param1->anims[v0], &param0->characterModels.models[param1->modelIndex], param0->characterModels.data[param1->modelIndex][v0], &param0->allocator);
        }
    }

    param1->active = 0;
}

int wifi_lobby_map_022610B8(const WiFiLobbyMapCharacter *param0)
{
    return param0->modelIndex;
}

void wifi_lobby_map_022610BC(WiFiLobbyMapCharacter *param0, WiFi2DCharPosition param1)
{
    VecFx32 v0;

    wifi_lobby_map_0225C700(&param1, &v0);
    Easy3DObject_SetPosition(&param0->object, v0.x, v0.y, v0.z);
}

WiFi2DCharPosition wifi_lobby_map_022610E4(const WiFiLobbyMapCharacter *param0)
{
    VecFx32 v0;
    WiFi2DCharPosition v1;

    Easy3DObject_GetPosition(&param0->object, &v0.x, &v0.y, &v0.z);
    wifi_lobby_map_0225C714(&v0, &v1);

    return v1;
}

void wifi_lobby_map_0226110C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, int param3)
{
    wifi_lobby_map_0226111C(param0, param1, param2, param3, NULL);
}

void wifi_lobby_map_0226111C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, int param3, UnkFuncPtr_wifi_lobby_map_02261C60 param4)
{
    GF_ASSERT(param2 < 3);
    GF_ASSERT(param3 < 7);
    GF_ASSERT(param1->modelIndex < 18);

    if (param0->characterModels.data[param1->modelIndex][param2] != NULL) {
        if (param1->animActive[param2] == 0) {
            Easy3DObject_AddAnim(&param1->object, &param1->anims[param2]);
        }

        param1->animActive[param2] = 1;
        param1->animMode[param2] = param3;
        param1->animCallback[param2] = param4;
        param1->animDelay[param2] = 0;

        switch (param3) {
        case 0:
        case 1:
        case 2:
            param1->animFrame[param2] = 0;
            break;
        case 3:
        case 4:
            param1->animFrame[param2] = Easy3DAnim_GetFrameCount(&param1->anims[param2]);
            break;
        case 5:
            param1->animFrame[param2] = 0;
            param1->animDelay[param2] = MTRNG_Next() % param1->delayRange;
            break;
        case 6:
            param1->animFrame[param2] = 0;
            param1->animDelay[param2] = MTRNG_Next() % param1->delayRange;
            break;
        }

        Easy3DAnim_SetFrame(&param1->anims[param2], param1->animFrame[param2]);
    }
}

void wifi_lobby_map_02261220(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2)
{
    GF_ASSERT(param2 < 3);
    GF_ASSERT(param1->modelIndex < 18);

    if ((param0->characterModels.data[param1->modelIndex][param2] != NULL) && (param1->animActive[param2] == 1)) {
        Easy3DObject_RemoveAnim(&param1->object, &param1->anims[param2]);

        param1->animActive[param2] = 0;
        param1->animFrame[param2] = 0;
        param1->animMode[param2] = 0;
        param1->animDelay[param2] = 0;
        param1->animCallback[param2] = NULL;
    }
}

void wifi_lobby_map_0226128C(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        if (wifi_lobby_map_02261348(param1, v0) == 1) {
            wifi_lobby_map_02261220(param0, param1, v0);
        }
    }
}

BOOL wifi_lobby_map_022612B4(const WiFiLobbyMapModelManager *param0, const WiFiLobbyMapCharacter *param1, int param2)
{
    GF_ASSERT(param2 < 3);
    GF_ASSERT(param1->modelIndex < 18);

    if (param0->characterModels.data[param1->modelIndex][param2] != NULL) {
        return param1->animActive[param2];
    }

    return 0;
}

void wifi_lobby_map_022612F0(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, int param2, fx32 param3)
{
    GF_ASSERT(param2 < 3);
    GF_ASSERT(param1->modelIndex < 18);
    GF_ASSERT(param0->characterModels.data[param1->modelIndex][param2] != NULL);

    if (param1->animMode[param2] != 2) {
        return;
    }

    param1->animFrame[param2] = param3;
    Easy3DAnim_SetFrame(&param1->anims[param2], param1->animFrame[param2]);
}

BOOL wifi_lobby_map_02261348(const WiFiLobbyMapCharacter *param0, int param1)
{
    GF_ASSERT(param1 < 3);
    GF_ASSERT(param0->modelIndex < 18);
    return param0->animActive[param1];
}

fx32 wifi_lobby_map_02261368(const WiFiLobbyMapCharacter *param0, int param1)
{
    GF_ASSERT(param1 < 3);
    GF_ASSERT(param0->modelIndex < 18);
    return param0->animFrame[param1];
}

void wifi_lobby_map_0226138C(WiFiLobbyMapCharacter *param0, BOOL param1)
{
    Easy3DObject_SetVisible(&param0->object, param1);
}

void wifi_lobby_map_02261398(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1, u32 param2)
{
    GF_ASSERT(param1->modelIndex < 18);
    NNS_G3dMdlSetMdlLightEnableFlagAll(param0->characterModels.models[param1->modelIndex].model, param2);
}

void wifi_lobby_map_022613C0(WiFiLobbyMapCharacter *param0, fx32 param1)
{
    param0->animSpeed = param1;
}

void wifi_lobby_map_022613C8(WiFiLobbyMapCharacter *param0, u8 param1, u8 param2)
{
    param0->alphaOverride = 1;
    param0->drawAlpha = param1;
    param0->restoreAlpha = param2;
}

void wifi_lobby_map_022613E0(WiFiLobbyMapCharacter *param0)
{
    param0->alphaOverride = 0;
}

void wifi_lobby_map_022613E8(WiFiLobbyMapCharacter *param0, fx32 param1, fx32 param2, fx32 param3)
{
    Easy3DObject_SetScale(&param0->object, param1, param2, param3);
}

static WiFiLobbyMapModelTable *wifi_lobby_map_022613F4(int param0, int param1, enum HeapID heapID)
{
    void *v0;
    u32 v1 = (param1 * 5) + param0;
    GF_ASSERT(v1 < (5 * 5));
    v0 = LoadMemberFromNARC(NARC_INDEX_APPLICATION__WIFI_LOBBY__MAP_CONV__WFLBY_MAP, 1 + v1, 0, heapID, 1);

    return v0;
}

static void wifi_lobby_map_02261418(WiFiLobbyMapModelTable *param0)
{
    Heap_Free(param0);
}

static void wifi_lobby_map_02261420(Easy3DModel *param0, NARC *param1, u32 param2, u32 heapID)
{
    wifi_lobby_map_0225C730(&param0->data, param1, param2, heapID);

    {
        param0->set = NNS_G3dGetMdlSet(param0->data);
        param0->model = NNS_G3dGetMdlByIdx(param0->set, 0);
        param0->texture = NNS_G3dGetTex(param0->data);
    }

    {
        Easy3D_BindTextureToResource(param0->data, param0->texture);
    }
}

static void wifi_lobby_map_0226146C(Easy3DModel *param0)
{
    Easy3DModel_Release(param0);
}

static void wifi_lobby_map_02261474(fx32 *param0, const Easy3DAnim *param1, fx32 param2)
{
    fx32 v0;

    v0 = Easy3DAnim_GetFrameCount(param1);

    if (((*param0) + param2) < v0) {
        (*param0) += param2;
    } else {
        (*param0) = ((*param0) + param2) % v0;
    }
}

static BOOL wifi_lobby_map_02261498(fx32 *param0, const Easy3DAnim *param1, fx32 param2)
{
    fx32 v0;
    BOOL v1;

    v0 = Easy3DAnim_GetFrameCount(param1);

    if (((*param0) + param2) < v0) {
        (*param0) += param2;
        v1 = 0;
    } else {
        (*param0) = v0 - FX32_HALF;
        v1 = 1;
    }

    return v1;
}

static void wifi_lobby_map_022614C0(fx32 *param0, const Easy3DAnim *param1, fx32 param2)
{
    fx32 v0;

    v0 = Easy3DAnim_GetFrameCount(param1);

    if (((*param0) - param2) >= 0) {
        (*param0) -= param2;
    } else {
        (*param0) = ((*param0) - param2) + v0;
    }
}

static BOOL wifi_lobby_map_022614DC(fx32 *param0, const Easy3DAnim *param1, fx32 param2)
{
    BOOL v0;

    if (((*param0) - param2) > 0) {
        (*param0) -= param2;
        v0 = 0;
    } else {
        (*param0) = 0;
        v0 = 1;
    }

    return v0;
}

static void wifi_lobby_map_022614F4(WiFiLobbyMapModelSet *param0, NARC *param1, const WiFiLobbyMapModelTable *param2, u32 heapID, NNSFndAllocator *param4)
{
    int v0, v1;

    for (v0 = 0; v0 < 2; v0++) {
        wifi_lobby_map_02261420(&param0->models[v0], param1, param2->unk_180[v0], heapID);
        WiFiPlazaLobby_Time_SetupModelGlobalLighting(param0->models[v0].data);
    }

    for (v0 = 0; v0 < 5; v0++) {
        if (param2->unk_18C[v0] == param2->unk_180[0]) {
            param0->animLoaded[v0] = 0;
        } else {
            param0->animLoaded[v0] = 1;

            if (v0 != 3) {
                Easy3DAnim_LoadFrom(&param0->anims[v0], &param0->models[0], param1, param2->unk_18C[v0], heapID, param4);
            } else {
                Easy3DAnim_LoadFrom(&param0->anims[v0], &param0->models[1], param1, param2->unk_18C[v0], heapID, param4);
            }
        }
    }
}

static void wifi_lobby_map_022615A4(WiFiLobbyMapModelSet *param0, NNSFndAllocator *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->animLoaded[v0]) {
            Easy3DAnim_Release(&param0->anims[v0], param1);
            param0->animLoaded[v0] = 0;
        }
    }

    for (v0 = 0; v0 < 2; v0++) {
        wifi_lobby_map_0226146C(&param0->models[v0]);
    }
}

static void wifi_lobby_map_022615E8(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1)
{
    int v0;

    param0->initialized = 1;

    for (v0 = 0; v0 < 2; v0++) {
        Easy3DObject_Init(&param0->objects[v0], &param1->models[v0]);
        Easy3DObject_SetVisible(&param0->objects[v0], 1);
    }

    for (v0 = 0; v0 < 5 - 1; v0++) {
        if (param1->animLoaded[v0] == 1) {
            param0->animAdded[v0] = 1;

            if (v0 != 3) {
                Easy3DObject_AddAnim(&param0->objects[0], &param1->anims[v0]);
            } else {
                Easy3DObject_AddAnim(&param0->objects[1], &param1->anims[v0]);
            }
        }
    }
}

static void wifi_lobby_map_02261664(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1)
{
    int v0;

    for (v0 = 0; v0 < 5 - 1; v0++) {
        if (param0->animAdded[v0] == 1) {
            param0->animAdded[v0] = 0;

            if (v0 != 3) {
                Easy3DObject_RemoveAnim(&param0->objects[0], &param1->anims[v0]);
            } else {
                Easy3DObject_RemoveAnim(&param0->objects[1], &param1->anims[v0]);
            }
        }
    }

    param0->initialized = 0;
}

static void wifi_lobby_map_022616B0(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1)
{
    int v0;

    for (v0 = 0; v0 < 5; v0++) {
        if (param0->animAdded[v0]) {
            wifi_lobby_map_02261474(&param0->animFrame[v0], &param1->anims[v0], FX32_ONE);
            Easy3DAnim_SetFrame(&param1->anims[v0], param0->animFrame[v0]);
        }
    }
}

static void wifi_lobby_map_022616FC(WiFiLobbyMapObjectSet *param0, WiFiLobbyMapModelSet *param1)
{
    int v0, v1;

    if (param0->initialized) {
        for (v0 = 0; v0 < 2; v0++) {
            Easy3DObject_Draw(&param0->objects[v0]);
        }
    }
}

static WiFiLobbyMapEffect *wifi_lobby_map_02261718(WiFiLobbyMapModelManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->effectCount; v0++) {
        if (param0->effects[v0].active == 0) {
            return &param0->effects[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static void wifi_lobby_map_0226174C(WiFiLobbyMapEffectModelSet *param0, NARC *param1, NNSFndAllocator *param2, const WiFiLobbyMapModelTable *param3, u32 heapID)
{
    int v0, v1, v2;

    {
        for (v0 = 0; v0 < 2; v0++) {
            for (v1 = 0; v1 < 3; v1++) {
                wifi_lobby_map_0225C730(&param0->data[v0][v1], param1, param3->unk_128[v0][v1], heapID);
            }
        }
    }

    {
        for (v0 = 0; v0 < 2; v0++) {
            param0->models[v0].data = LoadMemberFromOpenNARC(param1, param3->unk_120[v0], 0, heapID, 0);
            param0->models[v0].set = NNS_G3dGetMdlSet(param0->models[v0].data);
            param0->models[v0].model = NNS_G3dGetMdlByIdx(param0->models[v0].set, 0);
            param0->models[v0].texture = NNS_G3dGetTex(param0->data[v0][0]);
        }
    }

    {
        for (v0 = 0; v0 < 2; v0++) {
            for (v1 = 0; v1 < 4; v1++) {
                if (param3->unk_120[0] != param3->unk_140[v0][v1]) {
                    Easy3DAnim_LoadFrom(&param0->anims[v0][v1], &param0->models[v0], param1, param3->unk_140[v0][v1], heapID, param2);

                    if (v1 >= 1) {
                        for (v2 = 0; v2 < param3->unk_160[v0]; v2++) {
                            if (param3->unk_168[v0][v1 - 1] != v2) {
                                NNS_G3dAnmObjDisableID(param0->anims[v0][v1].animObj, v2);
                            }
                        }
                    }
                }
            }
        }
    }
}

static void wifi_lobby_map_022618C8(WiFiLobbyMapEffectModelSet *param0, NNSFndAllocator *param1)
{
    int v0, v1;

    {
        for (v0 = 0; v0 < 2; v0++) {
            for (v1 = 0; v1 < 4; v1++) {
                Easy3DAnim_Release(&param0->anims[v0][v1], param1);
            }
        }
    }

    {
        for (v0 = 0; v0 < 2; v0++) {
            Heap_Free(param0->models[v0].data);
        }
    }

    {
        NNSG3dTexKey v2;
        NNSG3dTexKey v3;
        NNSG3dPlttKey v4;
        NNSG3dResTex *v5;

        for (v0 = 0; v0 < 2; v0++) {
            for (v1 = 0; v1 < 3; v1++) {
                v5 = NNS_G3dGetTex(param0->data[v0][v1]);

                NNS_G3dTexReleaseTexKey(v5, &v2, &v3);
                NNS_GfdFreeTexVram(v2);
                NNS_GfdFreeTexVram(v3);

                v4 = NNS_G3dPlttReleasePlttKey(v5);
                NNS_GfdFreePlttVram(v4);

                Heap_Free(param0->data[v0][v1]);
            }
        }
    }
}

static void wifi_lobby_map_02261968(WiFiLobbyMapEffect *param0, WiFiLobbyMapEffectModelSet *param1)
{
    int v0;

    {
        fx32 v1;

        for (v0 = 0; v0 < 4; v0++) {
            if (param0->animFlags[v0]) {
                switch (v0) {
                case 0:
                case 2:
                    wifi_lobby_map_02261474(&param0->animFrames[v0], &param1->anims[param0->modelIndex][v0], FX32_ONE);
                    break;
                case 1:
                case 3: {
                    BOOL v2;

                    v2 = wifi_lobby_map_02261498(&param0->animFrames[v0], &param1->anims[param0->modelIndex][v0], FX32_ONE);

                    if (v2 == 1) {
                        param0->animFlags[v0] = 0;
                        param0->animFrames[v0] = 0;
                    }
                } break;
                default:
                    GF_ASSERT(FALSE);
                    break;
                }
            }
        }
    }
}

static void wifi_lobby_map_022619F4(WiFiLobbyMapEffect *param0, WiFiLobbyMapEffectModelSet *param1)
{
    BOOL v0;
    int v1;

    if (param0->active == 0) {
        return;
    }

    if (wifi_lobby_map_0225C7A0(&param1->models[param0->modelIndex], &param0->object) == 0) {
        return;
    }

    GF_ASSERT(param0->animIndex < 3);
    GF_ASSERT(param0->modelIndex < 2);

    param1->models[param0->modelIndex].texture = NNS_G3dGetTex(param1->data[param0->modelIndex][param0->animIndex]);
    v0 = NNS_G3dBindMdlSet(param1->models[param0->modelIndex].set, param1->models[param0->modelIndex].texture);

    GF_ASSERT(v0);

    for (v1 = 0; v1 < 4; v1++) {
        if (param0->animFlags[v1]) {
            Easy3DObject_AddAnim(&param0->object, &param1->anims[param0->modelIndex][v1]);
            Easy3DAnim_SetFrame(&param1->anims[param0->modelIndex][v1], param0->animFrames[v1]);
        }
    }

    Easy3DObject_Draw(&param0->object);

    for (v1 = 0; v1 < 4; v1++) {
        if (param0->animFlags[v1]) {
            Easy3DObject_RemoveAnim(&param0->object, &param1->anims[param0->modelIndex][v1]);
        }
    }

    NNS_G3dReleaseMdlSet(param1->models[param0->modelIndex].set);
}

static WiFiLobbyMapCharacter *wifi_lobby_map_02261AF0(WiFiLobbyMapModelManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        if (param0->characters[v0].active == 0) {
            return &param0->characters[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static void wifi_lobby_map_02261B24(WiFiLobbyMapCharacterModelSet *param0, NARC *param1, NNSFndAllocator *param2, const WiFiLobbyMapModelTable *param3, u32 heapID)
{
    int v0, v1;

    for (v0 = 0; v0 < 18; v0++) {
        wifi_lobby_map_02261420(&param0->models[v0], param1, param3->unk_00[v0], heapID);

        if ((v0 != 11) && (v0 != 12)) {
            WiFiPlazaLobby_Time_SetupModelGlobalLighting(param0->models[v0].data);
        }

        for (v1 = 0; v1 < 3; v1++) {
            if (param3->unk_48[v0][v1] != param3->unk_00[v0]) {
                param0->data[v0][v1] = LoadMemberFromOpenNARC(param1, param3->unk_48[v0][v1], 0, heapID, 0);
            } else {
                param0->data[v0][v1] = NULL;
            }
        }
    }
}

static void wifi_lobby_map_02261BB4(WiFiLobbyMapCharacterModelSet *param0, NNSFndAllocator *param1)
{
    int v0, v1;

    for (v0 = 0; v0 < 18; v0++) {
        for (v1 = 0; v1 < 3; v1++) {
            if (param0->data[v0][v1] != NULL) {
                Heap_Free(param0->data[v0][v1]);
                param0->data[v0][v1] = NULL;
            }
        }

        wifi_lobby_map_0226146C(&param0->models[v0]);
    }
}

static void wifi_lobby_map_02261C04(WiFiLobbyMapCharacterModelSet *param0, WiFiLobbyMapCharacter *param1)
{
    int v0;

    if (param1->active == 0) {
        return;
    }

    if (wifi_lobby_map_0225C7A0(&param0->models[param1->modelIndex], &param1->object) == 0) {
        return;
    }

    if (param1->alphaOverride == 1) {
        NNS_G3dMdlSetMdlAlphaAll(param0->models[param1->modelIndex].model, param1->drawAlpha);
    }

    Easy3DObject_Draw(&param1->object);

    if (param1->alphaOverride == 1) {
        NNS_G3dMdlSetMdlAlphaAll(param0->models[param1->modelIndex].model, param1->restoreAlpha);
    }
}

static void wifi_lobby_map_02261C60(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1)
{
    int v0;
    BOOL v1;
    UnkFuncPtr_wifi_lobby_map_02261C60 v2;

    for (v0 = 0; v0 < 3; v0++) {
        if (param1->animActive[v0]) {
            switch (param1->animMode[v0]) {
            case 0:
                wifi_lobby_map_02261474(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);
                Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);
                break;
            case 1:
                v1 = wifi_lobby_map_02261498(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);
                Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);

                if (v1 == 1) {
                    v2 = param1->animCallback[v0];

                    wifi_lobby_map_02261220(param0, param1, v0);

                    if (v2) {
                        v2(param0, param1);
                    }
                }
                break;
            case 3:
                wifi_lobby_map_022614C0(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);
                Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);
                break;
            case 4:
                v1 = wifi_lobby_map_022614DC(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);
                Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);

                if (v1 == 1) {
                    v2 = param1->animCallback[v0];

                    wifi_lobby_map_02261220(param0, param1, v0);

                    if (v2) {
                        v2(param0, param1);
                    }
                }
                break;
            case 5:
                if (param1->animDelay[v0] > 0) {
                    param1->animDelay[v0]--;
                } else {
                    v1 = wifi_lobby_map_02261498(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);

                    if (v1 == 1) {
                        param1->animDelay[v0] = MTRNG_Next() % param1->delayRange;
                        param1->animFrame[v0] = 0;
                    }

                    Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);
                }
                break;
            case 6:
                if (param1->animDelay[v0] > 0) {
                    param1->animDelay[v0]--;
                } else {
                    wifi_lobby_map_02261474(&param1->animFrame[v0], &param1->anims[v0], param1->animSpeed);
                    Easy3DAnim_SetFrame(&param1->anims[v0], param1->animFrame[v0]);
                }
                break;
            case 2:
            default:
                break;
            }
        }
    }
}
