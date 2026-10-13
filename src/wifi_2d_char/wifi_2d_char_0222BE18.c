#include "wifi_2d_char/wifi_2d_char_0222BE18.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_menu_app/struct_wifi_menu_app_022376D0.h"

#include "heap.h"

typedef struct WiFi2DCharObject {
    BOOL unk_00;
    WiFi2DCharPosition unk_04;
    WiFi2DCharPosition unk_08;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u16 unk_16;
} WiFi2DCharObject;

typedef struct WiFi2DCharObjectManager {
    WiFi2DCharObject *unk_00;
    u32 unk_04;
} WiFi2DCharObjectManager;

static WiFi2DCharObject *WiFi2DCharObjectManager_AllocObject(WiFi2DCharObjectManager *param0);
static void WiFi2DCharObject_StartMove(WiFi2DCharObject *param0, const WiFi2DCharMoveRequest *param1);
static void WiFi2DCharObject_UpdateMove(WiFi2DCharObject *param0);
static void WiFi2DCharObject_MoveState0(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState1(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState2(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState3(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState4(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState5(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState6(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState7(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState8(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState9(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState10(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static void WiFi2DCharObject_MoveState11(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2);
static BOOL WiFi2DCharObject_MoveDone0(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone1(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone2(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone3(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone4(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone5(WiFi2DCharObject *param0);
static BOOL WiFi2DCharObject_MoveDone6(WiFi2DCharObject *param0);
static void WiFi2DCharObject_FinishMove(WiFi2DCharObject *param0);
static WiFi2DCharPosition WiFi2DCharObject_OffsetPositionByDirection(WiFi2DCharPosition param0, int param1);
static BOOL WiFi2DCharObject_AdvanceMoveProgress(WiFi2DCharObject *param0);

WiFi2DCharObjectManager *WiFi2DCharObjectManager_New(u32 param0, enum HeapID heapID)
{
    WiFi2DCharObjectManager *v0 = Heap_Alloc(heapID, sizeof(WiFi2DCharObjectManager));
    GF_ASSERT(v0);

    v0->unk_04 = param0;
    v0->unk_00 = Heap_Alloc(heapID, sizeof(WiFi2DCharObject) * v0->unk_04);
    GF_ASSERT(v0->unk_00);

    memset(v0->unk_00, 0, sizeof(WiFi2DCharObject) * v0->unk_04);

    return v0;
}

void WiFi2DCharObjectManager_Free(WiFi2DCharObjectManager *param0)
{
    GF_ASSERT(param0);
    Heap_Free(param0->unk_00);
    Heap_Free(param0);
}

void WiFi2DCharObjectManager_StartMove(WiFi2DCharObjectManager *param0, const WiFi2DCharMoveRequest *param1)
{
    WiFi2DCharObject *v0 = WiFi2DCharObjectManager_FindObjectByID(param0, param1->unk_07);
    WiFi2DCharObject_StartMove(v0, param1);
}

void WiFi2DCharObjectManager_Update(WiFi2DCharObjectManager *param0)
{
    int v0;
    WiFi2DCharObject *v1;
    u32 v2 = WiFi2DCharObjectManager_GetCapacity(param0);

    for (v0 = 0; v0 < v2; v0++) {
        v1 = WiFi2DCharObjectManager_GetObject(param0, v0);

        if (v1) {
            WiFi2DCharObject_UpdateMove(v1);
        }
    }
}

u32 WiFi2DCharObjectManager_GetCapacity(const WiFi2DCharObjectManager *param0)
{
    GF_ASSERT(param0);
    return param0->unk_04;
}

WiFi2DCharObject *WiFi2DCharObjectManager_AddObject(WiFi2DCharObjectManager *param0, const WiFiMenuAppRect *param1)
{
    WiFi2DCharObject *v0;

    GF_ASSERT(param0);
    GF_ASSERT(param1);

    v0 = WiFi2DCharObjectManager_AllocObject(param0);

    v0->unk_04.x = param1->x;
    v0->unk_04.y = param1->y;
    v0->unk_08.x = param1->x;
    v0->unk_08.y = param1->y;
    v0->unk_0C = param1->objectID;
    v0->unk_15 = param1->moveState;
    v0->unk_14 = param1->variant;
    v0->unk_0E = param1->gfxID;
    v0->unk_00 = 1;

    return v0;
}

void WiFi2DCharObject_Reset(WiFi2DCharObject *param0)
{
    memset(param0, 0, sizeof(WiFi2DCharObject));
}

WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectByID(WiFi2DCharObjectManager *param0, u16 param1)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_00[v0].unk_00 == 1) {
            if (param0->unk_00[v0].unk_0C == param1) {
                return &param0->unk_00[v0];
            }
        }
    }

    return NULL;
}

WiFi2DCharObject *WiFi2DCharObjectManager_GetObject(WiFi2DCharObjectManager *param0, u16 param1)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < param0->unk_04);

    if (param0->unk_00[param1].unk_00 == 1) {
        return &param0->unk_00[param1];
    }

    return NULL;
}

const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectByIDConst(const WiFi2DCharObjectManager *param0, u16 param1)
{
    return WiFi2DCharObjectManager_FindObjectByID((WiFi2DCharObjectManager *)param0, param1);
}

const WiFi2DCharObject *WiFi2DCharObjectManager_GetObjectConst(const WiFi2DCharObjectManager *param0, u16 param1)
{
    return WiFi2DCharObjectManager_GetObject((WiFi2DCharObjectManager *)param0, param1);
}

s32 WiFi2DCharObject_GetField(const WiFi2DCharObject *param0, int param1)
{
    s32 v0;

    GF_ASSERT(param0);

    switch (param1) {
    case 0:
        v0 = param0->unk_04.x;
        break;
    case 1:
        v0 = param0->unk_04.y;
        break;
    case 2:
        v0 = param0->unk_08.x;
        break;
    case 3:
        v0 = param0->unk_08.y;
        break;
    case 4:
        v0 = param0->unk_0C;
        break;
    case 5:
        v0 = param0->unk_15;
        break;
    case 6:
        v0 = param0->unk_14;
        break;
    case 7:
        v0 = param0->unk_0E;
        break;
    case 8:
        v0 = param0->unk_10;
        break;
    case 9:
        v0 = param0->unk_12;
        break;
    case 10:
        v0 = param0->unk_16;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return v0;
}

void WiFi2DCharObject_SetField(WiFi2DCharObject *param0, int param1, s32 param2)
{
    GF_ASSERT(param0);

    switch (param1) {
    case 0:
        param0->unk_04.x = param2;
        break;
    case 1:
        param0->unk_04.y = param2;
        break;
    case 2:
        param0->unk_08.x = param2;
        break;
    case 3:
        param0->unk_08.y = param2;
        break;
    case 4:
        param0->unk_0C = param2;
        break;
    case 5:
        GF_ASSERT(param2 < 12);
        param0->unk_15 = param2;
        break;
    case 6:
        GF_ASSERT(param2 < 4);
        param0->unk_14 = param2;
        break;
    case 7:
        param0->unk_0E = param2;
        break;
    case 8:
        param0->unk_10 = param2;
        break;
    case 9:
        param0->unk_12 = param2;
        break;
    case 10:
        param0->unk_16 = param2;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

WiFi2DCharPosition WiFi2DCharPosition_OffsetByDirection(WiFi2DCharPosition param0, int param1)
{
    static const s8 v0[4][2] = {
        { 0, -16 },
        { 0, 16 },
        { -16, 0 },
        { 16, 0 },
    };

    param0.x += v0[param1][0];
    param0.y += v0[param1][1];

    return param0;
}

int WiFi2DChar_DirectionOpposite(int param0)
{
    static const u8 v0[4] = {
        1,
        0,
        3,
        2,
    };

    return v0[param0];
}

static WiFi2DCharObject *WiFi2DCharObjectManager_AllocObject(WiFi2DCharObjectManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_04; v0++) {
        if (param0->unk_00[v0].unk_00 == 0) {
            return &param0->unk_00[v0];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

WiFi2DCharPosition WiFi2DCharObject_GetPosition(const WiFi2DCharObject *param0)
{
    return param0->unk_04;
}

WiFi2DCharPosition WiFi2DCharObject_GetTargetPosition(const WiFi2DCharObject *param0)
{
    return param0->unk_08;
}

WiFi2DCharPosition WiFi2DCharObject_GetInterpolatedPosition(const WiFi2DCharObject *param0)
{
    s32 v0;
    s32 v1;
    WiFi2DCharPosition v2, v3;

    v0 = WiFi2DCharObject_GetField(param0, 8);
    v1 = WiFi2DCharObject_GetField(param0, 9);
    v2 = WiFi2DCharObject_GetPosition(param0);
    v3 = WiFi2DCharObject_GetTargetPosition(param0);

    v2.x -= v3.x;
    v2.y -= v3.y;

    if (v0 > 0) {
        v2.x = (v0 * v2.x) / v1;
        v2.y = (v0 * v2.y) / v1;
    } else {
        v2.x = 0;
        v2.y = 0;
    }

    v2.x += v3.x;
    v2.y += v3.y;

    return v2;
}

void WiFi2DCharObject_SetPosition(WiFi2DCharObject *param0, WiFi2DCharPosition param1)
{
    param0->unk_04 = param1;
}

void WiFi2DCharObject_SetTargetPosition(WiFi2DCharObject *param0, WiFi2DCharPosition param1)
{
    param0->unk_08 = param1;
}

const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectAtOffset(const WiFi2DCharObject *param0, const WiFi2DCharObjectManager *param1, int param2)
{
    int v0;
    u32 v1;
    WiFi2DCharPosition v2, v3;
    u32 v4, v5;
    const WiFi2DCharObject *v6;

    v2 = WiFi2DCharObject_GetPosition(param0);
    v2 = WiFi2DCharPosition_OffsetByDirection(v2, param2);
    v4 = WiFi2DCharObject_GetField(param0, 4);
    v1 = WiFi2DCharObjectManager_GetCapacity(param1);

    for (v0 = 0; v0 < v1; v0++) {
        v6 = WiFi2DCharObjectManager_GetObjectConst(param1, v0);

        if (v6 == NULL) {
            continue;
        }

        v5 = WiFi2DCharObject_GetField(v6, 4);

        if (v5 != v4) {
            v3 = WiFi2DCharObject_GetPosition(v6);

            if ((v3.x == v2.x) && (v3.y == v2.y)) {
                return v6;
            }

            v3 = WiFi2DCharObject_GetTargetPosition(v6);

            if ((v3.x == v2.x) && (v3.y == v2.y)) {
                return v6;
            }
        }
    }

    return NULL;
}

const WiFi2DCharObject *WiFi2DCharObjectManager_FindObjectAtPosition(const WiFi2DCharObjectManager *param0, WiFi2DCharPosition param1)
{
    int v0;
    u32 v1;
    WiFi2DCharPosition v2;
    const WiFi2DCharObject *v3;

    v1 = WiFi2DCharObjectManager_GetCapacity(param0);

    for (v0 = 0; v0 < v1; v0++) {
        v3 = WiFi2DCharObjectManager_GetObjectConst(param0, v0);

        if (v3 == NULL) {
            continue;
        }

        v2 = WiFi2DCharObject_GetPosition(v3);

        if ((v2.x == param1.x) && (v2.y == param1.y)) {
            return v3;
        }

        v2 = WiFi2DCharObject_GetTargetPosition(v3);

        if ((v2.x == param1.x) && (v2.y == param1.y)) {
            return v3;
        }
    }

    return NULL;
}

static void WiFi2DCharObject_StartMove(WiFi2DCharObject *param0, const WiFi2DCharMoveRequest *param1)
{
    int v0;

    static void (*const v1[12])(WiFi2DCharObject *, WiFi2DCharPosition, int) = {
        WiFi2DCharObject_MoveState0,
        WiFi2DCharObject_MoveState1,
        WiFi2DCharObject_MoveState2,
        WiFi2DCharObject_MoveState3,
        WiFi2DCharObject_MoveState4,
        WiFi2DCharObject_MoveState5,
        WiFi2DCharObject_MoveState6,
        WiFi2DCharObject_MoveState7,
        WiFi2DCharObject_MoveState8,
        WiFi2DCharObject_MoveState9,
        WiFi2DCharObject_MoveState10,
        WiFi2DCharObject_MoveState11,
    };

    v1[param1->unk_04](param0, param1->unk_00, param1->unk_06);
    param0->unk_16 = 0;
}

static void WiFi2DCharObject_UpdateMove(WiFi2DCharObject *param0)
{
    static BOOL (*const v0[12])(WiFi2DCharObject *) = {
        WiFi2DCharObject_MoveDone0,
        WiFi2DCharObject_MoveDone1,
        WiFi2DCharObject_MoveDone2,
        WiFi2DCharObject_MoveDone3,
        WiFi2DCharObject_MoveDone4,
        WiFi2DCharObject_MoveDone5,
        WiFi2DCharObject_MoveDone2,
        WiFi2DCharObject_MoveDone2,
        WiFi2DCharObject_MoveDone6,
        WiFi2DCharObject_MoveDone6,
        WiFi2DCharObject_MoveDone6,
        WiFi2DCharObject_MoveDone6,
    };

    u32 v1 = WiFi2DCharObject_GetField(param0, 5);
    BOOL v2 = v0[v1](param0);
    param0->unk_16++;

    if (v2 == 1) {
        WiFi2DCharObject_FinishMove(param0);
        param0->unk_16 = 0;
    }
}

static void WiFi2DCharObject_MoveState0(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 0);
}

static void WiFi2DCharObject_MoveState1(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 1);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 2);
}

static void WiFi2DCharObject_MoveState2(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0);
    v0 = WiFi2DCharObject_OffsetPositionByDirection(param1, param2);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, v0);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 2);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 8);
}

static void WiFi2DCharObject_MoveState3(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0);
    v0 = WiFi2DCharObject_OffsetPositionByDirection(param1, param2);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, v0);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 3);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 4);
}

static void WiFi2DCharObject_MoveState4(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 4);
}

static void WiFi2DCharObject_MoveState5(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 5);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 16);
}

static void WiFi2DCharObject_MoveState6(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0);
    v0 = WiFi2DCharObject_OffsetPositionByDirection(param1, param2);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, v0);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 6);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 16);
}

static void WiFi2DCharObject_MoveState7(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    WiFi2DCharPosition v0;

    GF_ASSERT(param0);
    v0 = WiFi2DCharObject_OffsetPositionByDirection(param1, param2);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, v0);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 7);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 4);
}

static void WiFi2DCharObject_MoveState8(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 8);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 2);
}

static void WiFi2DCharObject_MoveState9(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 9);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 4);
}

static void WiFi2DCharObject_MoveState10(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 10);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 8);
}

static void WiFi2DCharObject_MoveState11(WiFi2DCharObject *param0, WiFi2DCharPosition param1, int param2)
{
    GF_ASSERT(param0);

    WiFi2DCharObject_SetTargetPosition(param0, param1);
    WiFi2DCharObject_SetPosition(param0, param1);
    WiFi2DCharObject_SetField(param0, 6, param2);
    WiFi2DCharObject_SetField(param0, 5, 11);
    WiFi2DCharObject_SetField(param0, 8, 0);
    WiFi2DCharObject_SetField(param0, 9, 16);
}

static BOOL WiFi2DCharObject_MoveDone0(WiFi2DCharObject *param0)
{
    return 0;
}

static BOOL WiFi2DCharObject_MoveDone1(WiFi2DCharObject *param0)
{
    return WiFi2DCharObject_AdvanceMoveProgress(param0);
}

static BOOL WiFi2DCharObject_MoveDone2(WiFi2DCharObject *param0)
{
    BOOL v0;
    WiFi2DCharPosition v1;

    v0 = WiFi2DCharObject_AdvanceMoveProgress(param0);

    if (v0 == 1) {
        v1 = WiFi2DCharObject_GetPosition(param0);
        WiFi2DCharObject_SetTargetPosition(param0, v1);
    }

    return v0;
}

static BOOL WiFi2DCharObject_MoveDone3(WiFi2DCharObject *param0)
{
    BOOL v0;
    WiFi2DCharPosition v1;

    v0 = WiFi2DCharObject_AdvanceMoveProgress(param0);

    if (v0 == 1) {
        v1 = WiFi2DCharObject_GetPosition(param0);
        WiFi2DCharObject_SetTargetPosition(param0, v1);
    }

    return v0;
}

static BOOL WiFi2DCharObject_MoveDone4(WiFi2DCharObject *param0)
{
    return 0;
}

static BOOL WiFi2DCharObject_MoveDone5(WiFi2DCharObject *param0)
{
    return WiFi2DCharObject_AdvanceMoveProgress(param0);
}

static BOOL WiFi2DCharObject_MoveDone6(WiFi2DCharObject *param0)
{
    return WiFi2DCharObject_AdvanceMoveProgress(param0);
}

static WiFi2DCharPosition WiFi2DCharObject_OffsetPositionByDirection(WiFi2DCharPosition param0, int param1)
{
    return WiFi2DCharPosition_OffsetByDirection(param0, param1);
}

static BOOL WiFi2DCharObject_AdvanceMoveProgress(WiFi2DCharObject *param0)
{
    s32 v0;
    s32 v1;

    v0 = WiFi2DCharObject_GetField(param0, 8);
    v1 = WiFi2DCharObject_GetField(param0, 9);

    if (v0 < v1) {
        v0++;
        WiFi2DCharObject_SetField(param0, 8, v0);

        if (v0 < v1) {
            return 0;
        }
    }

    return 1;
}

static void WiFi2DCharObject_FinishMove(WiFi2DCharObject *param0)
{
    WiFi2DCharPosition v0;
    int v1;

    v0 = WiFi2DCharObject_GetPosition(param0);
    v1 = WiFi2DCharObject_GetField(param0, 6);

    WiFi2DCharObject_MoveState0(param0, v0, v1);
}
