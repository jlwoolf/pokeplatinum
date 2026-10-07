#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/wifi_2d_char_0222CA88.h"
#include "wifi_2d_char/wifi_2d_char_0222D77C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BCE8_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BE18_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222BEC0_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CCB8.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D848_decl.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222D894.h"
#include "wifi_menu_app/struct_wifi_menu_app_022376D0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022343A8.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02234548_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02234798_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0225C894_decl.h"

#include "heap.h"
#include "math_util.h"
#include "sound_playback.h"
#include "system.h"

typedef struct {
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    u32 unk_0C;
} UnkStruct_wifi_lobby_map_0225D220;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s16 unk_04;
    s16 unk_06;
} UnkStruct_wifi_lobby_map_0225D93C;

typedef union {
    struct {
        s16 unk_00;
        s16 unk_02;
    } val1;
    struct {
        UnkStruct_wifi_lobby_map_0225D220 unk_00;
        u32 unk_10;
    } val2;
    struct {
        UnkStruct_wifi_lobby_map_0225D220 unk_00;
        u32 unk_10;
        fx32 unk_14;
    } val3;
    struct {
        s32 unk_00;
        VecFx32 unk_04;
    } val4;
} UnkStruct_wifi_lobby_map_0225CC54_sub1;

typedef struct UnkStruct_wifi_lobby_map_0225CC54_t {
    WiFi2DCharObject *unk_00;
    WiFiPlazaLobbyObject *unk_04;
    u16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    UnkStruct_wifi_lobby_map_0225CC54_sub1 unk_0C;
    void (*unk_24)(struct UnkStruct_wifi_lobby_map_0225CC54_t *, UnkStruct_wifi_lobby_map_0225CA20 *);
} UnkStruct_wifi_lobby_map_0225CC54;

typedef void (*UnkFuncPtr_wifi_lobby_map_0226D558)(struct UnkStruct_wifi_lobby_map_0225CC54_t *, UnkStruct_wifi_lobby_map_0225CA20 *);

typedef struct UnkStruct_wifi_lobby_map_0225CA20_t {
    WiFi2DCharObjectManager *unk_00;
    WiFiPlazaLobbyObjectManager *unk_04;
    UnkStruct_wifi_lobby_map_0225CC54 *unk_08;
    u16 unk_0C;
    u16 unk_0E;
    WiFi2DCharEventQueue *unk_10;
    const UnkStruct_wifi_lobby_map_0225C894 *unk_14;
    UnkStruct_wifi_lobby_map_0225D93C unk_18;
    UnkStruct_wifi_lobby_map_0225CC54 *unk_20;
    UnkStruct_wifi_lobby_map_0225CC54 *unk_24;
} UnkStruct_wifi_lobby_map_0225CA20;

typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} UnkStruct_wifi_lobby_map_0226D508;

static void wifi_lobby_map_0225D0D8(UnkStruct_wifi_lobby_map_0225CA20 *param0);
static void wifi_lobby_map_0225D17C(UnkStruct_wifi_lobby_map_0225CA20 *param0, s32 param1, s32 param2, s32 param3);
static u8 wifi_lobby_map_0225D194(const u8 *param0, u32 param1);
static BOOL wifi_lobby_map_0225D1A8(const UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1, int param2, u32 param3);
static void wifi_lobby_map_0225D220(UnkStruct_wifi_lobby_map_0225D220 *param0, fx32 param1, fx32 param2, u32 param3);
static BOOL wifi_lobby_map_0225D22C(UnkStruct_wifi_lobby_map_0225D220 *param0, u32 param1);
static fx32 wifi_lobby_map_0225D2BC(const UnkStruct_wifi_lobby_map_0225D220 *param0);
static UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225D2C0(UnkStruct_wifi_lobby_map_0225CA20 *param0);
static BOOL wifi_lobby_map_0225D2FC(const UnkStruct_wifi_lobby_map_0225CC54 *param0);
static void wifi_lobby_map_0225D30C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D310(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D3D8(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D4CC(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D57C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D634(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D640(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D64C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D658(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D664(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1, int param2);
static void wifi_lobby_map_0225D81C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D8F8(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1);
static void wifi_lobby_map_0225D920(UnkStruct_wifi_lobby_map_0225D93C *param0, WiFiPlazaLobbyObjectManager *param1, u32 param2);
static void wifi_lobby_map_0225D93C(UnkStruct_wifi_lobby_map_0225D93C *param0, u32 param1);
static BOOL wifi_lobby_map_0225D954(UnkStruct_wifi_lobby_map_0225D93C *param0, WiFiPlazaLobbyObjectManager *param1);

static const u8 Unk_wifi_lobby_map_0226D500[] = {
    0x20,
    0x40,
    0x80,
    0x90
};

static const u8 Unk_wifi_lobby_map_0226D4FC[] = {
    0x0,
    0x1,
    0x2,
    0x3
};

static const UnkStruct_wifi_lobby_map_0226D508 Unk_wifi_lobby_map_0226D508[] = {
    { 0x40, 0x2, 0xEB, 0xFF },
    { 0x41, 0x1, 0xEB, 0xFF },
    { 0x42, 0x1, 0xEA, 0xFF },
    { 0x61, 0x1, 0xEA, 0xFE }
};

static const UnkFuncPtr_wifi_lobby_map_0226D558 Unk_wifi_lobby_map_0226D558[10] = {
    wifi_lobby_map_0225D30C,
    wifi_lobby_map_0225D310,
    wifi_lobby_map_0225D3D8,
    wifi_lobby_map_0225D4CC,
    wifi_lobby_map_0225D57C,
    wifi_lobby_map_0225D64C,
    wifi_lobby_map_0225D658,
    wifi_lobby_map_0225D634,
    wifi_lobby_map_0225D640,
    wifi_lobby_map_0225D81C
};

static const UnkFuncPtr_wifi_lobby_map_0226D558 Unk_wifi_lobby_map_0226D530[10] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    wifi_lobby_map_0225D8F8
};

static const u32 Unk_wifi_lobby_map_0226D518[6] = {
    { 0x10 },
    { 0xC },
    { 0x8 },
    { 0x6 },
    { 0x0 },
    { 0x0 }
};

UnkStruct_wifi_lobby_map_0225CA20 *wifi_lobby_map_0225C9B4(u32 param0, u32 param1, const UnkStruct_wifi_lobby_map_0225C894 *param2, u32 heapID, u32 heapID2)
{
    UnkStruct_wifi_lobby_map_0225CA20 *v0 = Heap_Alloc(heapID, sizeof(UnkStruct_wifi_lobby_map_0225CA20));
    memset(v0, 0, sizeof(UnkStruct_wifi_lobby_map_0225CA20));

    v0->unk_00 = WiFi2DCharObjectManager_New(param0, heapID);
    v0->unk_04 = WiFiPlazaLobby_Object_ManagerNew(param0, param1, heapID, heapID2);
    v0->unk_10 = WiFi2DCharEventQueue_New(32, heapID);
    v0->unk_0C = param0;
    v0->unk_08 = Heap_Alloc(heapID, sizeof(UnkStruct_wifi_lobby_map_0225CC54) * param0);

    memset(v0->unk_08, 0, sizeof(UnkStruct_wifi_lobby_map_0225CC54) * param0);

    v0->unk_14 = param2;
    v0->unk_0E = param1;

    wifi_lobby_map_0225D0D8(v0);

    return v0;
}

void wifi_lobby_map_0225CA20(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    Heap_Free(param0->unk_08);

    WiFi2DCharEventQueue_Free(param0->unk_10);
    WiFiPlazaLobby_Object_ManagerFree(param0->unk_04);
    WiFi2DCharObjectManager_Free(param0->unk_00);

    Heap_Free(param0);
}

void wifi_lobby_map_0225CA44(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    WiFi2DCharObjectManager_Update(param0->unk_00);
    wifi_lobby_map_0225D954(&param0->unk_18, param0->unk_04);
}

void wifi_lobby_map_0225CA5C(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < param0->unk_0C; v0++) {
            if (wifi_lobby_map_0225D2FC(&param0->unk_08[v0]) == 0) {
                param0->unk_08[v0].unk_24(&param0->unk_08[v0], param0);
            }
        }
    }

    {
        WiFi2DCharEvent v1;
        WiFi2DCharMoveRequest v2;
        BOOL v3;
        const WiFi2DCharGrid *v4;

        v4 = wifi_lobby_map_0225C9B0(param0->unk_14);

        while (WiFi2DCharEventQueue_Pop(param0->unk_10, &v1) == 1) {
            v3 = WiFi2DCharAI_ChooseMove(v4, param0->unk_00, &v1, &v2);

            if (v3 == 1) {
                WiFi2DCharObjectManager_StartMove(param0->unk_00, &v2);
            }
        }
    }

    WiFiPlazaLobby_Object_ManagerUpdate(param0->unk_04);
}

void wifi_lobby_map_0225CAD4(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    WiFiPlazaLobby_Object_ManagerDraw(param0->unk_04);
}

void wifi_lobby_map_0225CAE0(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    WiFiPlazaLobby_Object_ManagerResetRedraw(param0->unk_04);
}

void wifi_lobby_map_0225CAEC(UnkStruct_wifi_lobby_map_0225CA20 *param0, int param1)
{
    wifi_lobby_map_0225D920(&param0->unk_18, param0->unk_04, Unk_wifi_lobby_map_0226D518[param1]);
}

void wifi_lobby_map_0225CB08(UnkStruct_wifi_lobby_map_0225CA20 *param0, int param1)
{
    wifi_lobby_map_0225D93C(&param0->unk_18, Unk_wifi_lobby_map_0226D518[param1]);
}

void wifi_lobby_map_0225CB1C(UnkStruct_wifi_lobby_map_0225CA20 *param0, const WiFi2DCharEvent *param1)
{
    WiFi2DCharEventQueue_Push(param0->unk_10, param1);
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CB28(UnkStruct_wifi_lobby_map_0225CA20 *param0, u32 param1)
{
    u16 v0, v1;
    BOOL v2 = wifi_lobby_map_0225C8D8(param0->unk_14, 3, &v0, &v1, 0);
    GF_ASSERT(v2);
    return wifi_lobby_map_0225CB5C(param0, param1, v0, v1);
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CB5C(UnkStruct_wifi_lobby_map_0225CA20 *param0, u32 param1, u32 param2, u32 param3)
{
    UnkStruct_wifi_lobby_map_0225CC54 *v0 = wifi_lobby_map_0225D2C0(param0);

    {
        WiFiMenuAppRect v1;

        v1.unk_00 = (param2) * 16;
        v1.unk_02 = (param3) * 16;
        v1.unk_04 = param1;
        v1.unk_06 = 0;
        v1.unk_08 = 0;

        if (param0->unk_0E == 0) {
            v1.unk_0A = 0x0;
        } else {
            v1.unk_0A = 0x61;
        }

        v0->unk_00 = WiFi2DCharObjectManager_AddObject(param0->unk_00, &v1);
    }

    {
        v0->unk_04 = WiFiPlazaLobby_Object_New(param0->unk_04, v0->unk_00);
    }

    param0->unk_20 = v0;
    wifi_lobby_map_0225CDEC(param0, v0, 0);

    return v0;
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CBB8(UnkStruct_wifi_lobby_map_0225CA20 *param0, u32 param1, u32 param2)
{
    UnkStruct_wifi_lobby_map_0225CC54 *v0 = wifi_lobby_map_0225D2C0(param0);

    {
        WiFiMenuAppRect v1;
        u16 v2, v3, v4;
        BOOL v5;
        BOOL v6 = 0;
        UnkStruct_wifi_lobby_map_0225CC54 *v7;

        v4 = 0;

        do {
            v5 = wifi_lobby_map_0225C8D8(param0->unk_14, 4 + param1, &v2, &v3, v4);

            if (v5 == 0) {
                return NULL;
            } else {
                v7 = wifi_lobby_map_0225CCAC(param0);

                if (v7 == NULL) {
                    v6 = 1;
                } else {
                    if (wifi_lobby_map_0225CEDC(v7, v2, v3) == 0) {
                        v6 = 1;
                    }
                }
            }

            v4++;
        } while (v6 == 0);

        v1.unk_00 = (v2) * 16;
        v1.unk_02 = (v3) * 16;
        v1.unk_04 = param1;
        v1.unk_06 = 0;
        v1.unk_08 = 1;
        v1.unk_0A = param2;
        v0->unk_00 = WiFi2DCharObjectManager_AddObject(param0->unk_00, &v1);
    }

    {
        v0->unk_04 = WiFiPlazaLobby_Object_New(param0->unk_04, v0->unk_00);
    }

    wifi_lobby_map_0225CDEC(param0, v0, 0);

    return v0;
}

void wifi_lobby_map_0225CC54(UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    WiFiPlazaLobby_Object_Free(param0->unk_04);
    WiFi2DCharObject_Reset(param0->unk_00);
    memset(param0, 0, sizeof(UnkStruct_wifi_lobby_map_0225CC54));
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CC70(UnkStruct_wifi_lobby_map_0225CA20 *param0, u32 param1)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->unk_0C; v0++) {
        if (param0->unk_08[v0].unk_00) {
            v1 = WiFi2DCharObject_GetField(param0->unk_08[v0].unk_00, 4);

            if (v1 == param1) {
                return &param0->unk_08[v0];
            }
        }
    }

    return NULL;
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CCAC(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    return param0->unk_20;
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CCB0(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    return param0->unk_24;
}

void wifi_lobby_map_0225CCB4(UnkStruct_wifi_lobby_map_0225CC54 *param0, WiFi2DCharPosition param1)
{
    GF_ASSERT(param0->unk_00);
    WiFi2DCharObject_SetPosition(param0->unk_00, param1);
    WiFi2DCharObject_SetTargetPosition(param0->unk_00, param1);
    WiFi2DCharObject_SetField(param0->unk_00, 5, 0);
}

void wifi_lobby_map_0225CD04(UnkStruct_wifi_lobby_map_0225CC54 *param0, WiFi2DCharPosition param1, int param2)
{
    wifi_lobby_map_0225CCB4(param0, param1);
    WiFi2DCharObject_SetField(param0->unk_00, 6, param2);
}

WiFi2DCharPosition wifi_lobby_map_0225CD34(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    GF_ASSERT(param0->unk_00);
    return WiFi2DCharObject_GetInterpolatedPosition(param0->unk_00);
}

u32 wifi_lobby_map_0225CD60(const UnkStruct_wifi_lobby_map_0225CC54 *param0, int param1)
{
    GF_ASSERT(param0->unk_00);
    return WiFi2DCharObject_GetField(param0->unk_00, param1);
}

void wifi_lobby_map_0225CD7C(UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1, int param2, int param3)
{
    u32 v0;
    u32 v1;

    v0 = WiFi2DCharObject_GetField(param1->unk_00, 5);
    GF_ASSERT(v0 == 0);
    v1 = WiFi2DCharObject_GetField(param1->unk_00, 4);
    wifi_lobby_map_0225D17C(param0, param2, param3, v1);
}

void wifi_lobby_map_0225CDAC(UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1, int param2, int param3)
{
    WiFi2DCharMoveRequest v0;

    v0.unk_00 = WiFi2DCharObject_GetPosition(param1->unk_00);
    v0.unk_04 = param2;
    v0.unk_06 = param3;
    v0.unk_07 = WiFi2DCharObject_GetField(param1->unk_00, 4);

    WiFi2DCharObjectManager_StartMove(param0->unk_00, &v0);
}

void wifi_lobby_map_0225CDEC(UnkStruct_wifi_lobby_map_0225CA20 *param0, UnkStruct_wifi_lobby_map_0225CC54 *param1, int param2)
{
    GF_ASSERT(param2 < 10);

    if (Unk_wifi_lobby_map_0226D530[param1->unk_0B] != NULL) {
        Unk_wifi_lobby_map_0226D530[param1->unk_0B](param1, param0);
    }

    param1->unk_08 = 0;
    param1->unk_0A = 0;
    param1->unk_0B = param2;

    memset(&param1->unk_0C, 0, sizeof(UnkStruct_wifi_lobby_map_0225CC54_sub1));

    param1->unk_24 = Unk_wifi_lobby_map_0226D558[param2];
}

BOOL wifi_lobby_map_0225CE38(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    return param0->unk_0A;
}

int wifi_lobby_map_0225CE3C(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    return param0->unk_0B;
}

UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CE40(UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1)
{
    const WiFi2DCharObject *v0;
    u32 v1;
    u32 v2;

    v1 = WiFi2DCharObject_GetField(param1->unk_00, 6);
    v0 = WiFi2DCharObjectManager_FindObjectAtOffset(param1->unk_00, param0->unk_00, v1);

    if (v0 == NULL) {
        return NULL;
    }

    v2 = WiFi2DCharObject_GetField(v0, 4);
    return wifi_lobby_map_0225CC70(param0, v2);
}

BOOL wifi_lobby_map_0225CE70(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    return WiFiPlazaLobby_Object_IsCulled(param0->unk_04);
}

const UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225CE7C(const UnkStruct_wifi_lobby_map_0225CA20 *param0, u16 param1, u16 param2)
{
    const WiFi2DCharObject *v0;
    int v1;
    WiFi2DCharPosition v2;

    v2.x = (param1) * 16;
    v2.y = (param2) * 16;

    v0 = WiFi2DCharObjectManager_FindObjectAtPosition(param0->unk_00, v2);

    if (v0 == NULL) {
        return NULL;
    }

    for (v1 = 0; v1 < param0->unk_0C; v1++) {
        if (param0->unk_08[v1].unk_00 == v0) {
            return &param0->unk_08[v1];
        }
    }

    GF_ASSERT(FALSE);
    return NULL;
}

BOOL wifi_lobby_map_0225CEDC(const UnkStruct_wifi_lobby_map_0225CC54 *param0, u16 param1, u16 param2)
{
    WiFi2DCharPosition v0;
    WiFi2DCharPosition v1;

    v0 = WiFi2DCharObject_GetPosition(param0->unk_00);
    v1 = WiFi2DCharObject_GetTargetPosition(param0->unk_00);

    if ((v0.x == (param1) * 16) && (v0.y == (param2) * 16)) {
        return 1;
    }

    if ((v1.x == (param1) * 16) && (v1.y == (param2) * 16)) {
        return 1;
    }

    return 0;
}

BOOL wifi_lobby_map_0225CF4C(UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1, u32 *param2, WiFi2DCharPosition *param3)
{
    static const u8 v0[4] = {
        3,
        2,
        1,
        0,
    };
    int v1;
    WiFi2DCharPosition v2;
    WiFi2DCharPosition v3;
    BOOL v4;
    u32 v5;
    const WiFi2DCharObject *v6;

    v2 = WiFi2DCharObject_GetPosition(param1->unk_00);

    for (v1 = 0; v1 < 4; v1++) {
        v3 = WiFi2DCharPosition_OffsetByDirection(v2, v0[v1]);
        v4 = wifi_lobby_map_0225C8AC(param0->unk_14, (v3.x) / 16, (v3.y) / 16);

        if (v4 == 1) {
            continue;
        }

        v5 = wifi_lobby_map_0225C8C4(param0->unk_14, (v3.x) / 16, (v3.y) / 16);

        if ((v5 != 0) && (v5 != 42)) {
            continue;
        }

        v6 = WiFi2DCharObjectManager_FindObjectAtPosition(param0->unk_00, v3);

        if (v6 != NULL) {
            continue;
        }

        *param2 = v0[v1];
        *param3 = v3;

        return 1;
    }

    return 0;
}

void wifi_lobby_map_0225D030(UnkStruct_wifi_lobby_map_0225CC54 *param0, BOOL param1)
{
    WiFiPlazaLobby_Object_SetActive(param0->unk_04, param1);
}

void wifi_lobby_map_0225D03C(UnkStruct_wifi_lobby_map_0225CC54 *param0, const WiFi2DCharPosition *param1)
{
    WiFiPlazaLobby_Object_SetPositionFromTileCoords(param0->unk_04, param1);
}

void wifi_lobby_map_0225D048(UnkStruct_wifi_lobby_map_0225CC54 *param0, const VecFx32 *param1)
{
    WiFiPlazaLobby_Object_SetPosition(param0->unk_04, param1);
}

void wifi_lobby_map_0225D054(const UnkStruct_wifi_lobby_map_0225CC54 *param0, VecFx32 *param1)
{
    WiFiPlazaLobby_Object_GetPosition(param0->unk_04, param1);
}

void wifi_lobby_map_0225D060(UnkStruct_wifi_lobby_map_0225CC54 *param0, int param1)
{
    WiFiPlazaLobby_Object_SetAnimation(param0->unk_04, param1);
}

void wifi_lobby_map_0225D06C(UnkStruct_wifi_lobby_map_0225CC54 *param0, BOOL param1)
{
    if (param1) {
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 1);
    } else {
        WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
    }
}

void wifi_lobby_map_0225D084(UnkStruct_wifi_lobby_map_0225CC54 *param0, BOOL param1)
{
    if (param1) {
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 0);
    } else {
        WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
    }
}

void wifi_lobby_map_0225D09C(UnkStruct_wifi_lobby_map_0225CC54 *param0, BOOL param1)
{
    if (param1) {
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 2);
    } else {
        WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
    }
}

void wifi_lobby_map_0225D0B4(UnkStruct_wifi_lobby_map_0225CC54 *param0, u32 param1)
{
    WiFiPlazaLobby_Object_SetLightEnableFlag(param0->unk_04, param1);
}

void wifi_lobby_map_0225D0C0(UnkStruct_wifi_lobby_map_0225CC54 *param0, BOOL param1)
{
    WiFiPlazaLobby_Object_SetVisible(param0->unk_04, param1);
}

BOOL wifi_lobby_map_0225D0CC(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    return WiFiPlazaLobby_Object_IsVisible(param0->unk_04);
}

static void wifi_lobby_map_0225D0D8(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    int v0;
    UnkStruct_wifi_lobby_map_0225CC54 *v1;
    u16 v2, v3;
    BOOL v4;
    u16 v5;

    for (v0 = 0; v0 < NELEMS(Unk_wifi_lobby_map_0226D508); v0++) {
        v5 = 0;

        while (wifi_lobby_map_0225C8D8(param0->unk_14, Unk_wifi_lobby_map_0226D508[v0].unk_00, &v2, &v3, v5) == 1) {
            v1 = wifi_lobby_map_0225D2C0(param0);

            {
                WiFiMenuAppRect v6;

                v6.unk_00 = (v2) * 16;
                v6.unk_02 = (v3) * 16;
                v6.unk_04 = Unk_wifi_lobby_map_0226D508[v0].unk_03;
                v6.unk_06 = 0;
                v6.unk_08 = Unk_wifi_lobby_map_0226D508[v0].unk_01;
                v6.unk_0A = Unk_wifi_lobby_map_0226D508[v0].unk_02;
                v1->unk_00 = WiFi2DCharObjectManager_AddObject(param0->unk_00, &v6);
            }

            {
                v1->unk_04 = WiFiPlazaLobby_Object_New(param0->unk_04, v1->unk_00);
            }

            wifi_lobby_map_0225CDEC(param0, v1, 0);

            if (Unk_wifi_lobby_map_0226D508[v0].unk_00 == 97) {
                param0->unk_24 = v1;
            }

            v5++;
        }
    }
}

static void wifi_lobby_map_0225D17C(UnkStruct_wifi_lobby_map_0225CA20 *param0, s32 param1, s32 param2, s32 param3)
{
    WiFi2DCharEvent v0;

    v0.unk_00 = param1;
    v0.unk_02 = param2;
    v0.unk_03 = param3;

    wifi_lobby_map_0225CB1C(param0, &v0);
}

static u8 wifi_lobby_map_0225D194(const u8 *param0, u32 param1)
{
    int v0 = MTRNG_Next() % param1;
    return param0[v0];
}

static BOOL wifi_lobby_map_0225D1A8(const UnkStruct_wifi_lobby_map_0225CA20 *param0, const UnkStruct_wifi_lobby_map_0225CC54 *param1, int param2, u32 param3)
{
    WiFi2DCharPosition v0;
    u32 v1;

    v0 = WiFi2DCharObject_GetPosition(param1->unk_00);
    v0 = WiFi2DCharPosition_OffsetByDirection(v0, param2);
    v1 = wifi_lobby_map_0225C8B8(param0->unk_14, (v0.x) / 16, (v0.y) / 16);

    if (v1 == param3) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0225D220(UnkStruct_wifi_lobby_map_0225D220 *param0, fx32 param1, fx32 param2, u32 param3)
{
    param0->unk_00 = param1;
    param0->unk_04 = param1;
    param0->unk_08 = param2 - param1;
    param0->unk_0C = param3;
}

static BOOL wifi_lobby_map_0225D22C(UnkStruct_wifi_lobby_map_0225D220 *param0, u32 param1)
{
    fx32 v0;

    v0 = FX_Mul(param0->unk_08, FX32_CONST(param1));
    v0 = FX_Div(v0, FX32_CONST(param0->unk_0C));

    param0->unk_00 = v0 + param0->unk_04;

    if (param1 >= param0->unk_0C) {
        return 1;
    }

    return 0;
}

static fx32 wifi_lobby_map_0225D2BC(const UnkStruct_wifi_lobby_map_0225D220 *param0)
{
    return param0->unk_00;
}

static UnkStruct_wifi_lobby_map_0225CC54 *wifi_lobby_map_0225D2C0(UnkStruct_wifi_lobby_map_0225CA20 *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_0C; v0++) {
        if (wifi_lobby_map_0225D2FC(&param0->unk_08[v0])) {
            return &param0->unk_08[v0];
        }
    }

    GF_ASSERT(FALSE);
    return &param0->unk_08[v0];
}

static BOOL wifi_lobby_map_0225D2FC(const UnkStruct_wifi_lobby_map_0225CC54 *param0)
{
    if (param0->unk_00 == NULL) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0225D30C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    return;
}

static void wifi_lobby_map_0225D310(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    s32 v0;
    s32 v1;
    s32 v2;
    s32 v3;
    const WiFi2DCharObject *v4;

    v0 = WiFi2DCharObject_GetField(param0->unk_00, 6);
    v1 = WiFi2DCharObject_GetField(param0->unk_00, 4);
    v2 = WiFi2DCharObject_GetField(param0->unk_00, 5);

    if (v2 != 0) {
        return;
    }

    if (gSystem.heldKeys & PAD_BUTTON_B) {
        v3 = 3;
    } else {
        v3 = 2;
    }

    if (gSystem.heldKeys & PAD_KEY_UP) {
        if (v0 == 0) {
            wifi_lobby_map_0225D17C(param1, v3, v0, v1);
        } else {
            wifi_lobby_map_0225D17C(param1, 1, 0, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_DOWN) {
        if (v0 == 1) {
            wifi_lobby_map_0225D17C(param1, v3, v0, v1);
        } else {
            wifi_lobby_map_0225D17C(param1, 1, 1, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_LEFT) {
        if (v0 == 2) {
            wifi_lobby_map_0225D17C(param1, v3, v0, v1);
        } else {
            wifi_lobby_map_0225D17C(param1, 1, 2, v1);
        }
    } else if (gSystem.heldKeys & PAD_KEY_RIGHT) {
        if (v0 == 3) {
            wifi_lobby_map_0225D17C(param1, v3, v0, v1);
        } else {
            wifi_lobby_map_0225D17C(param1, 1, 3, v1);
        }
    }
}

static void wifi_lobby_map_0225D3D8(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    switch (param0->unk_08) {
    case 0:
        param0->unk_0C.val1.unk_00 = wifi_lobby_map_0225D194(Unk_wifi_lobby_map_0226D500, NELEMS(Unk_wifi_lobby_map_0226D500));
        param0->unk_08++;
        break;
    case 1:
        param0->unk_0C.val1.unk_00--;

        if (param0->unk_0C.val1.unk_00 == 0) {
            param0->unk_08++;
        }
        break;
    case 2: {
        u32 v0;
        u32 v1;

        v0 = WiFi2DCharObject_GetField(param0->unk_00, 4);
        v1 = WiFi2DCharObject_GetField(param0->unk_00, 6);

        param0->unk_0C.val1.unk_02 = wifi_lobby_map_0225D194(Unk_wifi_lobby_map_0226D4FC, NELEMS(Unk_wifi_lobby_map_0226D4FC));

        if (wifi_lobby_map_0225D1A8(param1, param0, param0->unk_0C.val1.unk_02, 4 + v0) == 1) {
            if (v1 == param0->unk_0C.val1.unk_02) {
                wifi_lobby_map_0225CD7C(param1, param0, 2, param0->unk_0C.val1.unk_02);
                param0->unk_08 = 4;
            } else {
                wifi_lobby_map_0225CD7C(param1, param0, 1, param0->unk_0C.val1.unk_02);
                param0->unk_08 = 3;
            }
        } else {
            wifi_lobby_map_0225CD7C(param1, param0, 1, param0->unk_0C.val1.unk_02);
            param0->unk_08 = 4;
        }
    } break;
    case 3: {
        u32 v2;

        v2 = WiFi2DCharObject_GetField(param0->unk_00, 5);

        if (v2 == 0) {
            wifi_lobby_map_0225CD7C(param1, param0, 2, param0->unk_0C.val1.unk_02);
            param0->unk_08++;
        }
    } break;
    case 4: {
        u32 v3;

        v3 = WiFi2DCharObject_GetField(param0->unk_00, 5);

        if (v3 == 0) {
            param0->unk_08 = 0;
        }
    } break;
    }
}

static void wifi_lobby_map_0225D4CC(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    switch (param0->unk_08) {
    case 0:
        WiFiPlazaLobby_Object_SetActive(param0->unk_04, 0);
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 0);
        wifi_lobby_map_0225D220(&param0->unk_0C.val2.unk_00, (FX32_CONST(0)), (FX32_CONST(500)), 24);

        param0->unk_0C.val2.unk_10 = 32;
        param0->unk_08++;
    case 1:
        param0->unk_0C.val2.unk_10--;

        if (param0->unk_0C.val2.unk_10 == 0) {
            param0->unk_08++;
            param0->unk_0C.val2.unk_10 = 0;
            Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
        }
        break;
    case 2: {
        BOOL v0;
        VecFx32 v1;

        v0 = wifi_lobby_map_0225D22C(&param0->unk_0C.val2.unk_00, param0->unk_0C.val2.unk_10);

        param0->unk_0C.val2.unk_10++;

        WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &v1);
        v1.y = wifi_lobby_map_0225D2BC(&param0->unk_0C.val2.unk_00);
        WiFiPlazaLobby_Object_SetPosition(param0->unk_04, &v1);

        if (v0 == 1) {
            param0->unk_08++;
            WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
            param0->unk_0A = 1;
        }
    } break;
    case 3:
        break;
    }
}

static void wifi_lobby_map_0225D57C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    switch (param0->unk_08) {
    case 0:
        WiFiPlazaLobby_Object_SetActive(param0->unk_04, 0);
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 0);
        wifi_lobby_map_0225D220(&param0->unk_0C.val2.unk_00, (FX32_CONST(500)), (FX32_CONST(0)), 24);

        param0->unk_0C.val2.unk_10 = 0;
        param0->unk_08++;

        Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);
    case 1: {
        BOOL v0;
        VecFx32 v1;

        v0 = wifi_lobby_map_0225D22C(&param0->unk_0C.val2.unk_00, param0->unk_0C.val2.unk_10);

        param0->unk_0C.val2.unk_10++;

        WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &v1);
        v1.y = wifi_lobby_map_0225D2BC(&param0->unk_0C.val2.unk_00);
        WiFiPlazaLobby_Object_SetPosition(param0->unk_04, &v1);

        if (v0 == 1) {
            param0->unk_0C.val2.unk_10 = 32;
            param0->unk_08++;
        }
    } break;
    case 2:
        param0->unk_0C.val2.unk_10--;

        if (param0->unk_0C.val2.unk_10 == 0) {
            param0->unk_08++;

            WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
            WiFiPlazaLobby_Object_SetActive(param0->unk_04, 1);
            param0->unk_0A = 1;
        }
        break;
    case 3:
        break;
    }
}

static void wifi_lobby_map_0225D634(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    wifi_lobby_map_0225D664(param0, param1, 2);
}

static void wifi_lobby_map_0225D640(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    wifi_lobby_map_0225D664(param0, param1, 3);
}

static void wifi_lobby_map_0225D64C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    wifi_lobby_map_0225D664(param0, param1, 0);
}

static void wifi_lobby_map_0225D658(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    wifi_lobby_map_0225D664(param0, param1, 1);
}

static void wifi_lobby_map_0225D664(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1, int param2)
{
    switch (param0->unk_08) {
    case 0:
        WiFiPlazaLobby_Object_SetActive(param0->unk_04, 0);
        WiFiPlazaLobby_Object_StartAnimationLoop(param0->unk_04, 0);
        WiFiPlazaLobby_Object_SetAnimationLoopStep(param0->unk_04, 2);
        wifi_lobby_map_0225D220(&param0->unk_0C.val3.unk_00, 0, (16 * FX32_ONE), 4);

        {
            VecFx32 v0;

            WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &v0);

            switch (param2) {
            case 0:
            case 1:
                param0->unk_0C.val3.unk_14 = v0.z;
                break;
            case 2:
            case 3:
                param0->unk_0C.val3.unk_14 = v0.x;
                break;
            }
        }
        param0->unk_0C.val3.unk_10 = 0;
        param0->unk_08++;
    case 1: {
        BOOL v1;
        VecFx32 v2;

        v1 = wifi_lobby_map_0225D22C(&param0->unk_0C.val3.unk_00, param0->unk_0C.val3.unk_10);
        param0->unk_0C.val3.unk_10++;
        WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &v2);

        switch (param2) {
        case 0:
            v2.z = param0->unk_0C.val3.unk_14 - wifi_lobby_map_0225D2BC(&param0->unk_0C.val3.unk_00);
            break;
        case 1:
            v2.z = param0->unk_0C.val3.unk_14 + wifi_lobby_map_0225D2BC(&param0->unk_0C.val3.unk_00);
            break;
        case 2:
            v2.x = param0->unk_0C.val3.unk_14 - wifi_lobby_map_0225D2BC(&param0->unk_0C.val3.unk_00);
            break;
        case 3:
            v2.x = param0->unk_0C.val3.unk_14 + wifi_lobby_map_0225D2BC(&param0->unk_0C.val3.unk_00);
            break;
        }

        WiFiPlazaLobby_Object_SetPosition(param0->unk_04, &v2);

        if (v1 == 1) {
            u32 v3;

            v3 = WiFi2DChar_DirectionOpposite(param2);
            param0->unk_0C.val3.unk_10 = 4;

            switch (v3) {
            case 3:
                param0->unk_0C.val3.unk_10 += 2;
            case 0:
                param0->unk_0C.val3.unk_10 += 2;
            case 2:
                param0->unk_0C.val3.unk_10 += 2;
            case 1:
                break;
            }

            param0->unk_08++;
        }
    } break;
    case 2:
        param0->unk_0C.val3.unk_10--;

        if (param0->unk_0C.val3.unk_10 == 0) {
            param0->unk_08++;

            {
                WiFi2DCharPosition v4;
                u32 v5;

                v4 = WiFi2DCharObject_GetPosition(param0->unk_00);
                v4 = WiFi2DCharPosition_OffsetByDirection(v4, param2);
                v5 = WiFi2DChar_DirectionOpposite(param2);

                wifi_lobby_map_0225CD04(param0, v4, v5);
            }

            WiFiPlazaLobby_Object_StopAnimationLoop(param0->unk_04);
            WiFiPlazaLobby_Object_SetActive(param0->unk_04, 1);

            param0->unk_0A = 1;
        }
        break;
    case 3:
        break;
    }
}

static void wifi_lobby_map_0225D81C(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    switch (param0->unk_08) {
    case 0:
        WiFiPlazaLobby_Object_SetActive(param0->unk_04, 0);
        WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &param0->unk_0C.val4.unk_04);
        param0->unk_0C.val4.unk_00 = ((6 * 2) + 16);
        param0->unk_08++;
        break;
    case 1:
        param0->unk_0C.val4.unk_00--;

        if (param0->unk_0C.val4.unk_00 < 0) {
            param0->unk_0C.val4.unk_00 = ((6 * 2) + 16);
        }

        {
            u32 v0;
            VecFx32 v1;
            s16 v2;

            v1 = param0->unk_0C.val4.unk_04;
            v2 = param0->unk_0C.val4.unk_00 - 16;

            if (v2 > 0) {
                v2 = v2 % 6;
                v0 = (180 * v2) / 6;

                v1.z += FX_Mul(CalcSineDegrees(v0), -2 * FX32_ONE);
                v1.y += FX_Mul(CalcSineDegrees(v0), 10 * FX32_ONE);
            }

            WiFiPlazaLobby_Object_SetPosition(param0->unk_04, &v1);
            WiFiPlazaLobby_Object_SetAnimation(param0->unk_04, 1);
        }
        break;
    }
}

static void wifi_lobby_map_0225D8F8(UnkStruct_wifi_lobby_map_0225CC54 *param0, UnkStruct_wifi_lobby_map_0225CA20 *param1)
{
    VecFx32 v0;

    WiFiPlazaLobby_Object_SetActive(param0->unk_04, 1);
    WiFiPlazaLobby_Object_GetPosition(param0->unk_04, &v0);

    v0.y = (FX32_CONST(0));

    WiFiPlazaLobby_Object_SetPosition(param0->unk_04, &v0);
}

static void wifi_lobby_map_0225D920(UnkStruct_wifi_lobby_map_0225D93C *param0, WiFiPlazaLobbyObjectManager *param1, u32 param2)
{
    param0->unk_01 = param2;
    param0->unk_02 = param2;
    param0->unk_03 = 0;
    param0->unk_04 = 0;
    param0->unk_06 = 0;
    param0->unk_00 = 0;

    WiFiPlazaLobby_Object_ManagerSetAlpha(param1, param2);
}

static void wifi_lobby_map_0225D93C(UnkStruct_wifi_lobby_map_0225D93C *param0, u32 param1)
{
    param0->unk_00 = 1;
    param0->unk_02 = param0->unk_01;
    param0->unk_03 = param1 - param0->unk_01;
    param0->unk_04 = 0;
    param0->unk_06 = 60;
}

static BOOL wifi_lobby_map_0225D954(UnkStruct_wifi_lobby_map_0225D93C *param0, WiFiPlazaLobbyObjectManager *param1)
{
    if (param0->unk_00 == 0) {
        return 1;
    }

    param0->unk_04++;

    if (param0->unk_04 >= param0->unk_06) {
        param0->unk_00 = 0;
    }

    param0->unk_01 = (param0->unk_04 * param0->unk_03) / param0->unk_06;
    param0->unk_01 += param0->unk_02;

    WiFiPlazaLobby_Object_ManagerSetAlpha(param1, param0->unk_01);

    return 0;
}
