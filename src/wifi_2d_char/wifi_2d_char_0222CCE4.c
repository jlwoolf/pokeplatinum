#include "wifi_2d_char/wifi_2d_char_0222CCE4.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char.h"
#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BB38_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CD2C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CE44.h"
#include "wifi_note/struct_wifi_note_sprite_params.h"

#include "heap.h"
#include "palette.h"
#include "sprite.h"

static BOOL WiFi2DCharRenderer_IsSlotFree(const WiFi2DCharRenderObject *param0);
static WiFi2DCharRenderObject *WiFi2DCharRenderer_AllocSlot(WiFi2DCharRenderer *param0);
static int WiFi2DChar_GetAnimForMoveState(const WiFi2DCharSprite *param0, int param1);
static void WiFi2DCharRenderer_GetObjectInterpolatedPosition(const WiFi2DCharRenderObject *param0, s16 *param1, s16 *param2);
static void WiFi2DCharRenderer_ApplyObjectAnim(WiFi2DCharRenderObject *param0, int param1, int param2);

WiFi2DCharRenderer *WiFi2DCharRenderer_New(SpriteList *param0, PaletteData *param1, u32 param2, u32 param3, u32 heapID)
{
    WiFi2DCharRenderer *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharRenderer));
    v0->unk_00 = WiFi2DCharManager_New(param0, param1, param2, heapID);
    v0->unk_08 = param2;
    v0->unk_04 = Heap_Alloc(heapID, sizeof(WiFi2DCharRenderObject) * v0->unk_08);

    memset(v0->unk_04, 0, sizeof(WiFi2DCharRenderObject) * v0->unk_08);

    v0->unk_0A = 2;
    v0->unk_0B = param3;

    return v0;
}

WiFi2DCharRenderer *WiFi2DCharRenderer_NewWithShadow(SpriteList *param0, PaletteData *param1, u32 param2, u32 param3, int param4, u32 param5, u32 heapID)
{
    WiFi2DCharRenderer *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharRenderer));
    v0->unk_00 = WiFi2DCharManager_New(param0, param1, param2, heapID);
    v0->unk_08 = param2;
    v0->unk_04 = Heap_Alloc(heapID, sizeof(WiFi2DCharRenderObject) * v0->unk_08);

    memset(v0->unk_04, 0, sizeof(WiFi2DCharRenderObject) * v0->unk_08);

    v0->unk_0A = 2;
    v0->unk_0B = param5;

    WiFi2DCharManager_LoadSpecies(v0->unk_00, param3, v0->unk_0B, param4, heapID);
    WiFi2DCharManager_LoadShadow(v0->unk_00, v0->unk_0B, 40001, heapID);

    return v0;
}

void WiFi2DCharRenderer_Free(WiFi2DCharRenderer *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_08; v0++) {
        if (WiFi2DCharRenderer_IsSlotFree(&param0->unk_04[v0]) == 0) {
            WiFi2DCharRenderer_RemoveObject(&param0->unk_04[v0]);
        }
    }

    WiFi2DCharManager_UnloadShadow(param0->unk_00);
    WiFi2DCharRenderer_UnloadAllSpecies(param0);
    WiFi2DCharManager_Free(param0->unk_00);

    Heap_Free(param0->unk_04);
    Heap_Free(param0);
}

void WiFi2DCharRenderer_LoadSpecies(WiFi2DCharRenderer *param0, u32 param1, int param2, u32 heapID)
{
    if (WiFi2DCharManager_IsSpeciesLoaded(param0->unk_00, param1) == 0) {
        WiFi2DCharManager_LoadSpecies(param0->unk_00, param1, param0->unk_0B, param2, heapID);
    }
}

void WiFi2DCharRenderer_UnloadSpecies(WiFi2DCharRenderer *param0, u32 param1)
{
    WiFi2DCharManager_UnloadSpecies(param0->unk_00, param1);
}

BOOL WiFi2DCharRenderer_IsSpeciesLoaded(const WiFi2DCharRenderer *param0, u32 param1)
{
    return WiFi2DCharManager_IsSpeciesLoaded(param0->unk_00, param1);
}

void WiFi2DCharRenderer_UnloadAllSpecies(WiFi2DCharRenderer *param0)
{
    WiFi2DCharManager_UnloadAllSpecies(param0->unk_00);
}

void WiFi2DCharRenderer_LoadShadowResources(WiFi2DCharRenderer *param0, int param1, u32 heapID)
{
    WiFi2DCharManager_LoadShadowResources(param0->unk_00, param0->unk_0B, param1, heapID);
}

WiFi2DCharRenderObject *WiFi2DCharRenderer_AddObject(WiFi2DCharRenderer *param0, const WiFi2DCharObject *param1, BOOL param2, u32 heapID)
{
    WiFi2DCharRenderObject *v0;
    WiFiNoteSpriteParams v1;
    s32 v2;

    v0 = WiFi2DCharRenderer_AllocSlot(param0);

    v0->unk_08 = WiFi2DCharObject_GetField(param1, 5);
    v0->unk_0A = WiFi2DCharObject_GetField(param1, 6);
    v0->unk_0C = WiFi2DCharObject_GetField(param1, 4);
    v0->unk_00 = param1;
    v0->unk_12 = param2;
    v0->unk_13 = 1;
    v0->unk_0E = 0;
    v0->unk_10 = 0;

    v1.x = WiFi2DCharObject_GetField(param1, 0);
    v1.y = WiFi2DCharObject_GetField(param1, 1);
    v1.priority = WiFi2DChar_GetPriorityForY(v1.y, v0->unk_12);
    v1.explicitPriority = param0->unk_0A;

    v2 = WiFi2DCharObject_GetField(param1, 7);
    v0->unk_04 = WiFi2DCharSprite_New(param0->unk_00, &v1, v2, heapID);

    WiFi2DCharRenderer_UpdateObject(v0);

    return v0;
}

void WiFi2DCharRenderer_RemoveObject(WiFi2DCharRenderObject *param0)
{
    WiFi2DCharSprite_Delete(param0->unk_04);
    memset(param0, 0, sizeof(WiFi2DCharRenderObject));
}

void WiFi2DCharRenderer_UpdateAll(WiFi2DCharRenderer *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_08; v0++) {
        if (WiFi2DCharRenderer_IsSlotFree(&param0->unk_04[v0]) == 0) {
            WiFi2DCharRenderer_UpdateObject(&param0->unk_04[v0]);
        }
    }
}

void WiFi2DCharRenderer_UpdateObject(WiFi2DCharRenderObject *param0)
{
    s32 v0;
    s32 v1;
    s16 v2, v3;
    s16 v4;
    u16 v5;
    int v6;

    if (param0->unk_13 == 0) {
        return;
    }

    v0 = WiFi2DCharObject_GetField(param0->unk_00, 5);
    v1 = WiFi2DCharObject_GetField(param0->unk_00, 6);
    v4 = WiFi2DCharObject_GetField(param0->unk_00, 8);

    if ((param0->unk_08 != v0) || (param0->unk_0A != v1) || (v4 == 0)) {
        param0->unk_08 = v0;
        param0->unk_0A = v1;

        v6 = WiFi2DChar_GetAnimForMoveState(param0->unk_04, v0);
        WiFi2DCharRenderer_ApplyObjectAnim(param0, v6, v1);
    }

    WiFi2DCharRenderer_GetObjectInterpolatedPosition(param0, &v2, &v3);
    WiFi2DCharSprite_SetPosition(param0->unk_04, v2, v3);

    v5 = WiFi2DChar_GetPriorityForY(v3, param0->unk_12);

    WiFi2DCharSprite_SetPriority(param0->unk_04, v5);
    WiFi2DCharSprite_UpdateAnim(param0->unk_04);
}

void WiFi2DCharRenderer_SetObjectEnabled(WiFi2DCharRenderObject *param0, BOOL param1)
{
    param0->unk_13 = param1;
}

void WiFi2DCharRenderer_ResetObjectAnim(WiFi2DCharRenderObject *param0)
{
    WiFi2DCharRenderer_ApplyObjectAnim(param0, 1, param0->unk_0A);
}

void WiFi2DCharRenderer_UpdateObjectAnim(WiFi2DCharRenderObject *param0)
{
    WiFi2DCharSprite_UpdateAnim(param0->unk_04);
}

void WiFi2DCharRenderer_RefreshObject(WiFi2DCharRenderObject *param0)
{
    int v0 = WiFi2DChar_GetAnimForMoveState(param0->unk_04, param0->unk_08);

    WiFi2DCharRenderer_ApplyObjectAnim(param0, v0, param0->unk_0A);
    WiFi2DCharRenderer_UpdateObject(param0);
}

void WiFi2DCharRenderer_SetObjectPosition(WiFi2DCharRenderObject *param0, WiFi2DCharPosition param1)
{
    WiFi2DCharSprite_SetPosition(param0->unk_04, param1.x, param1.y);
}

BOOL WiFi2DCharRenderer_IsObjectVisible(const WiFi2DCharRenderObject *param0)
{
    return WiFi2DCharSprite_IsVisible(param0->unk_04);
}

void WiFi2DCharRenderer_SetObjectVisible(WiFi2DCharRenderObject *param0, BOOL param1)
{
    WiFi2DCharSprite_SetVisible(param0->unk_04, param1);
}

u16 WiFi2DCharRenderer_GetObjectPriority(const WiFi2DCharRenderObject *param0)
{
    return WiFi2DCharSprite_GetPriority(param0->unk_04);
}

void WiFi2DCharRenderer_SetObjectAnim(WiFi2DCharRenderObject *param0, int param1)
{
    WiFi2DCharRenderer_ApplyObjectAnim(param0, 0, param1);
    WiFi2DCharSprite_UpdateAnim(param0->unk_04);
}

u32 WiFi2DChar_GetPriorityForY(s16 param0, BOOL param1)
{
    if (param1 == 1) {
        return 20000 - (param0 * 2) + 20000;
    }

    return (20000 - (param0 * 2) + 20000) + 1;
}

u32 WiFi2DCharRenderer_GetObjectPaletteOffset(const WiFi2DCharRenderObject *param0)
{
    return Sprite_GetExplicitPaletteOffset(WiFi2DCharSprite_GetSprite(param0->unk_04));
}

void WiFi2DCharRenderer_SetObjectShadowPosition(WiFi2DCharRenderObject *param0, WiFi2DCharPosition param1)
{
    WiFi2DCharSprite_SetShadowPosition(param0->unk_04, param1.x, param1.y);
}

static BOOL WiFi2DCharRenderer_IsSlotFree(const WiFi2DCharRenderObject *param0)
{
    if (param0->unk_04 == NULL) {
        return 1;
    }

    return 0;
}

static WiFi2DCharRenderObject *WiFi2DCharRenderer_AllocSlot(WiFi2DCharRenderer *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_08; v0++) {
        if (WiFi2DCharRenderer_IsSlotFree(&param0->unk_04[v0]) == 1) {
            return &param0->unk_04[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

static int WiFi2DChar_GetAnimForMoveState(const WiFi2DCharSprite *param0, int param1)
{
    static const u8 v0[12] = {
        0,
        3,
        2,
        4,
        0,
        5,
        6,
        8,
        7,
        8,
        2,
        6,
    };
    int v1 = WiFi2DCharSprite_GetResourceType(param0);

    if (v1 == 2) {
        return 0;
    }

    return v0[param1];
}

static void WiFi2DCharRenderer_GetObjectInterpolatedPosition(const WiFi2DCharRenderObject *param0, s16 *param1, s16 *param2)
{
    WiFi2DCharPosition v0;

    v0 = WiFi2DCharObject_GetInterpolatedPosition(param0->unk_00);

    *param1 = v0.x;
    *param2 = v0.y;
}

static void WiFi2DCharRenderer_ApplyObjectAnim(WiFi2DCharRenderObject *param0, int param1, int param2)
{
    u16 v0;
    u16 v1;
    static const u8 v2[10] = {
        0,
        0,
        1,
        0,
        1,
        1,
        1,
        1,
        1,
        0,
    };

    v0 = WiFi2DCharSprite_GetAnimFrame(param0->unk_04);
    v1 = WiFi2DCharSprite_GetAnimState(param0->unk_04);

    WiFi2DCharSprite_SetAnim(param0->unk_04, param1, param2);

    if (v1 != param1) {
        if (v2[param1] == 1) {
            if (param0->unk_10 == param1) {
                WiFi2DCharSprite_SetAnimFrame(param0->unk_04, param0->unk_0E);
            }
        }

        if (v2[v1] == 1) {
            param0->unk_10 = v1;
            param0->unk_0E = v0;
        }
    }
}
