#include "wifi_plaza_lobby/wifi_plaza_lobby_022343A8.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C700.h"

#include "billboard.h"
#include "easy3d.h"
#include "easy3d_object.h"
#include "gfx_box_test.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "resource_collection.h"

typedef struct {
    u16 graphicID;
    u16 resourceID : 15;
    u16 withoutKeys : 1;
} WiFiPlazaLobbyObjectTextureEntry;

typedef struct {
    Easy3DModel model;
    u32 alpha;
} WiFiPlazaLobbyObjectModel;

typedef struct WiFiPlazaLobbyObject_t {
    u8 active : 4;
    u8 culled : 2;
    u8 visible : 2;
    u8 loopAnimActive : 1;
    u8 loopAnimMode : 7;
    u8 loopAnimFrame;
    u8 loopAnimStep;
    const WiFi2DCharObject *charObject;
    Billboard *billboard;
    Easy3DObject object;
    u8 animMode;
    u8 lastAnimNum;
    u16 lastFieldValue;
    fx32 savedAnimFrame;
    int lightEnableFlag;
} WiFiPlazaLobbyObject;

typedef struct WiFiPlazaLobbyObjectManager_t {
    ResourceCollection *globalResources;
    ResourceCollection *objectResources;
    TextureResourceManager *textureManager;
    BillboardList *billboardList;
    WiFiPlazaLobbyObject *objects;
    u32 objectCount;
    WiFiPlazaLobbyObjectModel model;
    int lightEnableFlag;
} WiFiPlazaLobbyObjectManager;

static const WiFiPlazaLobbyObjectTextureEntry *WiFiPlazaLobby_Object_FindTextureEntry(u32 param0);
static u32 WiFiPlazaLobby_Object_GetAnimationIndex(BOOL param0, u32 param1);
static fx32 WiFiPlazaLobby_Object_CalcAnimationProgress(u16 param0, u16 param1, u32 param2);
static void WiFiPlazaLobby_Object_ModelLoad(WiFiPlazaLobbyObjectModel *param0, NARC *param1, u32 param2, enum HeapID heapID);
static void WiFiPlazaLobby_Object_ModelFree(WiFiPlazaLobbyObjectModel *param0);
static void WiFiPlazaLobby_Object_ModelSetAlpha(WiFiPlazaLobbyObjectModel *param0, u32 param1);
static u32 WiFiPlazaLobby_Object_ModelGetAlpha(const WiFiPlazaLobbyObjectModel *param0);
static void WiFiPlazaLobby_Object_ModelInitObject(WiFiPlazaLobbyObjectModel *param0, Easy3DObject *param1);
static WiFiPlazaLobbyObject *WiFiPlazaLobby_Object_Alloc(WiFiPlazaLobbyObjectManager *param0);
static BOOL WiFiPlazaLobby_Object_IsAllocated(const WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_Init(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_Draw(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_Update(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_AnimModeStatic(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_AnimModeProgress(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_AnimModeHold(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_AnimModeProgressReverse(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_UpdateLoopAnimation(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_LoopAnimCycle(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_LoopAnimPlayOnce(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_LoopAnimTwoPhase(WiFiPlazaLobbyObject *param0);
static BOOL WiFiPlazaLobby_Object_IsPersistentAnimMode(u32 param0);
static void WiFiPlazaLobby_Object_UpdateCulling(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_ApplyVisibility(WiFiPlazaLobbyObject *param0);
static void WiFiPlazaLobby_Object_BillboardDrawCallback(Billboard *param0, void *param1);
static BOOL WiFiPlazaLobby_Object_IsBillboardInView(Billboard *param0);

static const u8 sObjectAnimationIndices[4] = {
    0x1,
    0x2,
    0x0,
    0x3
};

static const u16 sObjectResourceIds[2] = {
    0x1BD,
    0x1BE
};

static const BillboardAnim sBillboardAnim[] = {
    { 0x0, 0xF, 0x0 },
    { 0x10, 0x1F, 0x0 },
    { 0x20, 0x2F, 0x0 },
    { 0x30, 0x3F, 0x0 },
    { 0x40, 0x4F, 0x0 },
    { 0x50, 0x5F, 0x0 },
    { 0x60, 0x6F, 0x0 },
    { 0x70, 0x7F, 0x0 },
    { 0x0, 0x0, 0x2 }
};

static const WiFiPlazaLobbyObjectTextureEntry sObjectTextureEntries[20] = {
    { 0x0, 0x5A, 0x1 },
    { 0x61, 0x5B, 0x1 },
    { 0x3, 0x2, 0x0 },
    { 0x5, 0x4, 0x0 },
    { 0xB, 0xA, 0x0 },
    { 0x1F, 0x1D, 0x0 },
    { 0x32, 0x30, 0x0 },
    { 0x33, 0x31, 0x0 },
    { 0x3E, 0x3C, 0x0 },
    { 0x46, 0x44, 0x0 },
    { 0x6, 0x5, 0x0 },
    { 0x7, 0x6, 0x0 },
    { 0xD, 0xC, 0x0 },
    { 0xE, 0xD, 0x0 },
    { 0x23, 0x21, 0x0 },
    { 0x25, 0x23, 0x0 },
    { 0x2A, 0x28, 0x0 },
    { 0x3F, 0x3D, 0x0 },
    { 0xEB, 0x18E, 0x0 },
    { 0xEA, 0x18D, 0x0 }
};

WiFiPlazaLobbyObjectManager *WiFiPlazaLobby_Object_ManagerNew(u32 param0, u32 param1, enum HeapID heapID, u32 heapID2)
{
    WiFiPlazaLobbyObjectManager *v0 = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyObjectManager));
    memset(v0, 0, sizeof(WiFiPlazaLobbyObjectManager));

    {
        int v1;

        v0->objects = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyObject) * param0);
        v0->objectCount = param0;

        for (v1 = 0; v1 < v0->objectCount; v1++) {
            WiFiPlazaLobby_Object_Init(&v0->objects[v1]);
        }
    }

    v0->globalResources = ResourceCollection_New(1, heapID);
    v0->objectResources = ResourceCollection_New(2, heapID);
    v0->textureManager = TextureResourceManager_New(20, heapID);

    {
        BillboardListParams v2;

        BillboardLists_Create(1, heapID);

        v2.maxElements = param0;
        v2.heapID = heapID;
        v0->billboardList = BillboardList_New(&v2);
    }

    {
        NARC *v3;
        NARC *v4;
        void *v5;
        int v6;

        v3 = NARC_ctor(NARC_INDEX_DATA__MMODEL__MMODEL, heapID);
        v4 = NARC_ctor(NARC_INDEX_GRAPHIC__WIFI_LOBBY_OTHER, heapID);

        {
            v5 = LoadMemberFromOpenNARC(v4, 127, 0, heapID2, 0);
            ResourceCollection_Add(v0->globalResources, v5, 127);
            WiFiPlazaLobby_Time_SetupModelGlobalLighting(v5);

            {
                NNSG3dResMdlSet *v7;
                NNSG3dResMdl *v8;

                v7 = NNS_G3dGetMdlSet(v5);
                v8 = NNS_G3dGetMdlByIdx(v7, 0);
                v0->lightEnableFlag = NNS_G3dMdlGetMdlLightEnableFlag(v8, 0);
            }
        }

        {
            for (v6 = 0; v6 < 2; v6++) {
                v5 = LoadMemberFromOpenNARC(v3, sObjectResourceIds[v6], 0, heapID2, 0);
                ResourceCollection_Add(v0->objectResources, v5, sObjectResourceIds[v6]);
            }
        }

        {
            TextureResource *v9;
            int v10;
            BOOL v11;

            if (param1 == 0) {
                v10 = 1;
            } else {
                v10 = 0;
            }

            for (v6 = 0; v6 < 20; v6++) {
                if (v10 == v6) {
                    continue;
                }

                if (sObjectTextureEntries[v6].withoutKeys == 0) {
                    v11 = 1;
                } else {
                    v11 = 0;
                }

                v5 = LoadMemberFromOpenNARC(v3, sObjectTextureEntries[v6].resourceID, 0, heapID2, 0);
                v9 = TextureResourceManager_AddTexture(v0->textureManager, v5, sObjectTextureEntries[v6].resourceID, v11, heapID2);

                if (v11 == 1) {
                    TextureResource_AllocVRam(v9);
                    TextureResource_UploadToVRam(v9);
                    TextureResource_DiscardTextureData(v9);
                }
            }
        }

        WiFiPlazaLobby_Object_ModelLoad(&v0->model, v4, 128, heapID2);

        NARC_dtor(v3);
        NARC_dtor(v4);
    }
    return v0;
}

void WiFiPlazaLobby_Object_ManagerFree(WiFiPlazaLobbyObjectManager *param0)
{
    {
        WiFiPlazaLobby_Object_ModelFree(&param0->model);
        TextureResourceManager_Clear(param0->textureManager);
        ResourceCollection_Clear(param0->globalResources);
        ResourceCollection_Clear(param0->objectResources);
    }

    {
        BillboardList_Delete(param0->billboardList);
        BillboardLists_Delete();
    }

    TextureResourceManager_Delete(param0->textureManager);
    ResourceCollection_Delete(param0->globalResources);
    ResourceCollection_Delete(param0->objectResources);
    Heap_Free(param0->objects);
    Heap_Free(param0);
}

void WiFiPlazaLobby_Object_ManagerUpdate(WiFiPlazaLobbyObjectManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->objectCount; v0++) {
        WiFiPlazaLobby_Object_Update(&param0->objects[v0]);
        WiFiPlazaLobby_Object_UpdateLoopAnimation(&param0->objects[v0]);
        WiFiPlazaLobby_Object_UpdateCulling(&param0->objects[v0]);
    }
}

void WiFiPlazaLobby_Object_ManagerDraw(WiFiPlazaLobbyObjectManager *param0)
{
    int v0;

    BillboardLists_Draw();

    if (WiFiPlazaLobby_Object_ModelGetAlpha(&param0->model) > 0) {
        for (v0 = 0; v0 < param0->objectCount; v0++) {
            if (WiFiPlazaLobby_Object_IsAllocated(&param0->objects[v0]) == 1) {
                WiFiPlazaLobby_Object_Draw(&param0->objects[v0]);
            }
        }
    }
}

void WiFiPlazaLobby_Object_ManagerResetRedraw(WiFiPlazaLobbyObjectManager *param0)
{
    BillboardList_ResetRedraw(param0->billboardList);
}

void WiFiPlazaLobby_Object_ManagerSetAlpha(WiFiPlazaLobbyObjectManager *param0, u32 param1)
{
    WiFiPlazaLobby_Object_ModelSetAlpha(&param0->model, param1);
}

WiFiPlazaLobbyObject *WiFiPlazaLobby_Object_New(WiFiPlazaLobbyObjectManager *param0, const WiFi2DCharObject *param1)
{
    WiFiPlazaLobbyObject *v0 = WiFiPlazaLobby_Object_Alloc(param0);
    v0->charObject = param1;

    {
        const WiFiPlazaLobbyObjectTextureEntry *v1;
        BillboardResources v2;
        BillboardTemplate v3;
        Resource *v4;
        TextureResource *v5;
        u32 v6;
        void *v7;
        const NNSG3dResTex *v8;
        BillboardGfxSequence v9;
        NNSGfdTexKey v10;
        NNSGfdTexKey v11;
        NNSGfdPlttKey v12;
        VecFx32 v13 = { 0, 0, 0 };
        VecFx32 v14 = { FX32_ONE, FX32_ONE, FX32_ONE };

        v6 = WiFi2DCharObject_GetField(param1, 7);
        v1 = WiFiPlazaLobby_Object_FindTextureEntry(v6);

        {
            v4 = ResourceCollection_FindResource(param0->globalResources, 127);
            v7 = Resource_GetData(v4);
        }

        {
            v5 = TextureResourceManager_FindTextureResource(param0->textureManager, v1->resourceID);
            v8 = TextureResource_GetUnderlyingResource(v5);
        }

        {
            u32 v15;
            const void *v16;

            if (v1->withoutKeys == 1) {
                v15 = sObjectResourceIds[1];
            } else {
                v15 = sObjectResourceIds[0];
            }

            v4 = ResourceCollection_FindResource(param0->objectResources, v15);
            v16 = Resource_GetData(v4);

            BillboardGfxSequence_SetData(v16, &v9);
        }

        if (v1->withoutKeys == 1) {
            BillboardResources_SetWithoutKeys(&v2, v7, v8, sBillboardAnim, &v9);
        } else {
            v10 = TextureResource_GetTexKey(v5);
            v11 = TextureResource_GetTex4x4Key(v5);
            v12 = TextureResource_GetPaletteKey(v5);

            BillboardResources_Set(&v2, v7, v8, sBillboardAnim, &v9, v10, v11, v12);
        }

        {
            WiFi2DCharPosition v17;

            v17 = WiFi2DCharObject_GetPosition(param1);
            wifi_lobby_map_0225C700(&v17, &v13);
            v13.z += (FX32_CONST(16));
        }

        v3.list = param0->billboardList;
        v3.resources = &v2;
        v3.pos = v13;
        v3.scale = v14;
        v0->billboard = BillboardList_Append(&v3);

        Billboard_SetCallback(v0->billboard, WiFiPlazaLobby_Object_BillboardDrawCallback, v0);
        WiFiPlazaLobby_Object_ModelInitObject(&param0->model, &v0->object);
        Easy3DObject_SetPosition(&v0->object, v13.x + 0, ((FX32_CONST(0)) + FX32_CONST(2)), v13.z + (FX32_CONST(-8)));
    }

    v0->active = 1;
    v0->visible = 1;
    v0->culled = 0;
    v0->lightEnableFlag = param0->lightEnableFlag;

    return v0;
}

void WiFiPlazaLobby_Object_Free(WiFiPlazaLobbyObject *param0)
{
    Billboard_Delete(param0->billboard);
    memset(param0, 0, sizeof(WiFiPlazaLobbyObject));
}

void WiFiPlazaLobby_Object_SetActive(WiFiPlazaLobbyObject *param0, BOOL param1)
{
    param0->active = param1;
}

void WiFiPlazaLobby_Object_SetLightEnableFlag(WiFiPlazaLobbyObject *param0, u32 param1)
{
    param0->lightEnableFlag = param1;
}

BOOL WiFiPlazaLobby_Object_IsCulled(const WiFiPlazaLobbyObject *param0)
{
    return param0->culled;
}

void WiFiPlazaLobby_Object_SetPositionFromTileCoords(WiFiPlazaLobbyObject *param0, const WiFi2DCharPosition *param1)
{
    VecFx32 v0;

    wifi_lobby_map_0225C700(param1, &v0);
    v0.z += (FX32_CONST(16));
    WiFiPlazaLobby_Object_SetPosition(param0, &v0);
}

void WiFiPlazaLobby_Object_SetPosition(WiFiPlazaLobbyObject *param0, const VecFx32 *param1)
{
    Billboard_SetPos(param0->billboard, param1);
    Easy3DObject_SetPosition(&param0->object, param1->x + 0, ((FX32_CONST(0)) + FX32_CONST(2)), param1->z + (FX32_CONST(-8)));
}

void WiFiPlazaLobby_Object_GetPosition(const WiFiPlazaLobbyObject *param0, VecFx32 *param1)
{
    const VecFx32 *v0 = Billboard_GetPos(param0->billboard);
    *param1 = *v0;
}

void WiFiPlazaLobby_Object_SetAnimation(WiFiPlazaLobbyObject *param0, int param1)
{
    u32 v0 = WiFiPlazaLobby_Object_GetAnimationIndex(1, param1);

    Billboard_SetAnimNum(param0->billboard, v0);
    Billboard_SetAnimFrameNum(param0->billboard, 0);
}

void WiFiPlazaLobby_Object_StartAnimationLoop(WiFiPlazaLobbyObject *param0, int param1)
{
    param0->loopAnimActive = 1;
    param0->loopAnimMode = param1;
    param0->loopAnimFrame = 0;
    param0->loopAnimStep = 1;
}

void WiFiPlazaLobby_Object_StopAnimationLoop(WiFiPlazaLobbyObject *param0)
{
    param0->loopAnimActive = 0;
}

void WiFiPlazaLobby_Object_SetAnimationLoopStep(WiFiPlazaLobbyObject *param0, u8 param1)
{
    param0->loopAnimStep = param1;
}

void WiFiPlazaLobby_Object_SetVisible(WiFiPlazaLobbyObject *param0, BOOL param1)
{
    param0->visible = param1;
    WiFiPlazaLobby_Object_ApplyVisibility(param0);
}

BOOL WiFiPlazaLobby_Object_IsVisible(const WiFiPlazaLobbyObject *param0)
{
    return param0->visible;
}

static const WiFiPlazaLobbyObjectTextureEntry *WiFiPlazaLobby_Object_FindTextureEntry(u32 param0)
{
    int v0;

    for (v0 = 0; v0 < 20; v0++) {
        if (sObjectTextureEntries[v0].graphicID == param0) {
            return &sObjectTextureEntries[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static u32 WiFiPlazaLobby_Object_GetAnimationIndex(BOOL param0, u32 param1)
{
    if (param0) {
        return 0 + param1;
    }

    return 4 + param1;
}

static fx32 WiFiPlazaLobby_Object_CalcAnimationProgress(u16 param0, u16 param1, u32 param2)
{
    fx32 v0;

    param1++;

    v0 = (param1 * param2) / param0;
    v0 *= FX32_ONE;

    return v0;
}

static void WiFiPlazaLobby_Object_ModelLoad(WiFiPlazaLobbyObjectModel *param0, NARC *param1, u32 param2, enum HeapID heapID)
{
    void *v0;

    wifi_lobby_map_0225C730(&v0, param1, param2, heapID);

    param0->model.data = v0;
    param0->model.set = NNS_G3dGetMdlSet(param0->model.data);
    param0->model.model = NNS_G3dGetMdlByIdx(param0->model.set, 0);
    param0->model.texture = NNS_G3dGetTex(param0->model.data);

    Easy3D_BindTextureToResource(param0->model.data, param0->model.texture);

    NNS_G3dMdlSetMdlPolygonIDAll(param0->model.model, 20);
}

static void WiFiPlazaLobby_Object_ModelFree(WiFiPlazaLobbyObjectModel *param0)
{
    Easy3DModel_Release(&param0->model);
}

static void WiFiPlazaLobby_Object_ModelSetAlpha(WiFiPlazaLobbyObjectModel *param0, u32 param1)
{
    param0->alpha = param1;
    NNS_G3dMdlSetMdlAlphaAll(param0->model.model, param0->alpha);
}

static u32 WiFiPlazaLobby_Object_ModelGetAlpha(const WiFiPlazaLobbyObjectModel *param0)
{
    return param0->alpha;
}

static void WiFiPlazaLobby_Object_ModelInitObject(WiFiPlazaLobbyObjectModel *param0, Easy3DObject *param1)
{
    Easy3DObject_Init(param1, &param0->model);
}

static WiFiPlazaLobbyObject *WiFiPlazaLobby_Object_Alloc(WiFiPlazaLobbyObjectManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->objectCount; v0++) {
        if (WiFiPlazaLobby_Object_IsAllocated(&param0->objects[v0]) == 0) {
            return &param0->objects[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static BOOL WiFiPlazaLobby_Object_IsAllocated(const WiFiPlazaLobbyObject *param0)
{
    if (param0->charObject == NULL) {
        return 0;
    }

    return 1;
}

static void WiFiPlazaLobby_Object_Init(WiFiPlazaLobbyObject *param0)
{
    memset(param0, 0, sizeof(WiFiPlazaLobbyObject));
}

static void WiFiPlazaLobby_Object_Draw(WiFiPlazaLobbyObject *param0)
{
    Easy3DObject_Draw(&param0->object);
}

static void WiFiPlazaLobby_Object_Update(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;
    WiFi2DCharPosition v2;
    static void (*v3[12])(WiFiPlazaLobbyObject *) = {
        WiFiPlazaLobby_Object_AnimModeStatic,
        WiFiPlazaLobby_Object_AnimModeHold,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgressReverse,
        WiFiPlazaLobby_Object_AnimModeStatic,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgress,
        WiFiPlazaLobby_Object_AnimModeProgress
    };

    if (param0->active == 0) {
        return;
    }

    v0 = WiFi2DCharObject_GetField(param0->charObject, 5);
    v1 = WiFi2DCharObject_GetField(param0->charObject, 8);

    if ((param0->lastFieldValue > v1) || (param0->animMode != v0)) {
        if (WiFiPlazaLobby_Object_IsPersistentAnimMode(param0->animMode) == 1) {
            param0->lastAnimNum = Billboard_GetAnimNum(param0->billboard);
            param0->savedAnimFrame = Billboard_GetAnimFrameNum(param0->billboard);
        }

        param0->animMode = v0;
    }

    param0->lastFieldValue = v1;

    v3[v0](param0);

    v2 = WiFi2DCharObject_GetInterpolatedPosition(param0->charObject);
    WiFiPlazaLobby_Object_SetPositionFromTileCoords(param0, &v2);
}

static void WiFiPlazaLobby_Object_AnimModeStatic(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;

    v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
    v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);

    Billboard_SetAnimNum(param0->billboard, v1);
    Billboard_SetAnimFrameNum(param0->billboard, 0);
}

static void WiFiPlazaLobby_Object_AnimModeProgress(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;
    fx32 v2;
    u16 v3;
    u16 v4;

    v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
    v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);
    v3 = WiFi2DCharObject_GetField(param0->charObject, 9);
    v4 = WiFi2DCharObject_GetField(param0->charObject, 8);
    v2 = WiFiPlazaLobby_Object_CalcAnimationProgress(v3, v4, 8);

    Billboard_SetAnimNum(param0->billboard, v1);

    if (param0->lastAnimNum == v1) {
        Billboard_SetAnimFrameNum(param0->billboard, 0);
        Billboard_AdvanceAnim(param0->billboard, v2 + param0->savedAnimFrame);
    } else {
        Billboard_SetAnimFrameNum(param0->billboard, 0);
        Billboard_AdvanceAnim(param0->billboard, v2);
    }
}

static void WiFiPlazaLobby_Object_AnimModeHold(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;
    u16 v2 = WiFi2DCharObject_GetField(param0->charObject, 8);

    if (v2 < 4) {
        Billboard_SetAnimFrameNum(param0->billboard, 4 * FX32_ONE);
    } else {
        v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
        v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);

        Billboard_SetAnimNum(param0->billboard, v1);
        Billboard_SetAnimFrameNum(param0->billboard, 0);
    }
}

static void WiFiPlazaLobby_Object_AnimModeProgressReverse(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;
    fx32 v2;
    u16 v3;
    u16 v4;

    v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
    v1 = WiFiPlazaLobby_Object_GetAnimationIndex(0, v0);
    v3 = WiFi2DCharObject_GetField(param0->charObject, 9);
    v4 = WiFi2DCharObject_GetField(param0->charObject, 8);
    v2 = WiFiPlazaLobby_Object_CalcAnimationProgress(v3, v4, 4);

    Billboard_SetAnimNum(param0->billboard, v1);

    if (param0->lastAnimNum == v1) {
        Billboard_SetAnimFrameNum(param0->billboard, 0);
        Billboard_AdvanceAnim(param0->billboard, v2 + param0->savedAnimFrame);
    } else {
        Billboard_SetAnimFrameNum(param0->billboard, 0);
        Billboard_AdvanceAnim(param0->billboard, v2);
    }
}

static void WiFiPlazaLobby_Object_UpdateLoopAnimation(WiFiPlazaLobbyObject *param0)
{
    static void (*v0[3])(WiFiPlazaLobbyObject *) = {
        WiFiPlazaLobby_Object_LoopAnimCycle,
        WiFiPlazaLobby_Object_LoopAnimPlayOnce,
        WiFiPlazaLobby_Object_LoopAnimTwoPhase
    };

    if ((param0->active == 0) && (param0->loopAnimActive == 1)) {
        v0[param0->loopAnimMode](param0);
    }
}

static void WiFiPlazaLobby_Object_LoopAnimCycle(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;

    if ((param0->loopAnimFrame % 4) == 0) {
        v0 = param0->loopAnimFrame / 4;
        v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, sObjectAnimationIndices[v0]);

        Billboard_SetAnimNum(param0->billboard, v1);
        Billboard_SetAnimFrameNum(param0->billboard, 0);
    }

    if ((param0->loopAnimFrame + param0->loopAnimStep) < (4 * 4)) {
        param0->loopAnimFrame += param0->loopAnimStep;
    } else {
        param0->loopAnimFrame = 0;
    }
}

static void WiFiPlazaLobby_Object_LoopAnimPlayOnce(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;

    if (param0->loopAnimFrame == 0) {
        v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
        v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
        v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);

        Billboard_SetAnimNum(param0->billboard, v1);
        Billboard_SetAnimFrameNum(param0->billboard, 4 * FX32_ONE);

        param0->loopAnimFrame++;
    }
}

static void WiFiPlazaLobby_Object_LoopAnimTwoPhase(WiFiPlazaLobbyObject *param0)
{
    u32 v0;
    u32 v1;

    if (param0->loopAnimFrame == 0) {
        v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
        v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);

        Billboard_SetAnimNum(param0->billboard, v1);
        Billboard_SetAnimFrameNum(param0->billboard, 4 * FX32_ONE);
    } else if (param0->loopAnimFrame == 4) {
        v0 = WiFi2DCharObject_GetField(param0->charObject, 6);
        v1 = WiFiPlazaLobby_Object_GetAnimationIndex(1, v0);

        Billboard_SetAnimNum(param0->billboard, v1);
        Billboard_SetAnimFrameNum(param0->billboard, (4 * 3) * FX32_ONE);
    }

    param0->loopAnimFrame = (param0->loopAnimFrame + 1) % (4 * 2);
}

static BOOL WiFiPlazaLobby_Object_IsPersistentAnimMode(u32 param0)
{
    switch (param0) {
    case 2:
    case 3:
    case 5:
    case 6:
    case 10:
    case 11:
        return 1;
    default:
        break;
    }

    return 0;
}

static void WiFiPlazaLobby_Object_UpdateCulling(WiFiPlazaLobbyObject *param0)
{
    BOOL v0;

    if (WiFiPlazaLobby_Object_IsAllocated(param0)) {
        v0 = WiFiPlazaLobby_Object_IsBillboardInView(param0->billboard);

        if (v0 == 0) {
            param0->culled = 1;
        } else {
            param0->culled = 0;
        }

        WiFiPlazaLobby_Object_ApplyVisibility(param0);
    }
}

static void WiFiPlazaLobby_Object_ApplyVisibility(WiFiPlazaLobbyObject *param0)
{
    if ((param0->culled == 0) && (param0->visible == 1)) {
        Billboard_SetDrawFlag(param0->billboard, 1);
        Easy3DObject_SetVisible(&param0->object, 1);
    } else {
        Billboard_SetDrawFlag(param0->billboard, 0);
        Easy3DObject_SetVisible(&param0->object, 0);
    }
}

static void WiFiPlazaLobby_Object_BillboardDrawCallback(Billboard *param0, void *param1)
{
    WiFiPlazaLobbyObject *v0 = param1;
    NNSG3dResMdl *v1 = Billboard_GetModel2(param0);
    NNS_G3dMdlSetMdlLightEnableFlagAll(v1, v0->lightEnableFlag);
}

static BOOL WiFiPlazaLobby_Object_IsBillboardInView(Billboard *param0)
{
    BOOL v0;
    VecFx32 v1;
    NNSG3dResMdlInfo *v2;
    NNSG3dResMdl *v3;
    GFXTestBox v4;
    MtxFx33 v5;

    v3 = Billboard_GetModel(param0);
    v2 = NNS_G3dGetMdlInfo(v3);
    v1 = *Billboard_GetPos(param0);

    v4.width = v2->boxW;
    v4.height = v2->boxH;
    v4.depth = v2->boxH;
    v4.xScale = v2->boxPosScale >> FX32_SHIFT;
    v4.yScale = v2->boxPosScale >> FX32_SHIFT;
    v4.zScale = v2->boxPosScale >> FX32_SHIFT;

    v1.x += FX_Mul(v2->boxX, v2->boxPosScale);
    v1.y += FX_Mul(v2->boxY, v2->boxPosScale);
    v1.z += FX_Mul(v2->boxZ, v2->boxPosScale);
    v1.z -= FX_Mul(v2->boxH, v2->boxPosScale);

    MTX_Identity33(&v5);
    NNS_G3dGlbSetBaseRot(&v5);
    NNS_G3dGlbSetBaseScale(Billboard_GetScale(param0));

    v0 = GFXBoxTest_IsBoxAtPositionInView(&v1, &v4);

    if (v0 == 0) {
        return 0;
    }

    return 1;
}
