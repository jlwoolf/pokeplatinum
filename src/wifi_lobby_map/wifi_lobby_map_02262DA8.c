#include "wifi_lobby_map/wifi_lobby_map_02262DA8.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_map/funcptr_wifi_lobby_map_0226DA18.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0225DEE8_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_0226DA18.h"

#include "heap.h"

typedef struct {
    const UnkStruct_wifi_lobby_map_0226DA18 *unk_00;
    void *unk_04;
    void *unk_08;
    u32 unk_0C;
} UnkStruct_wifi_lobby_map_0226308C;

typedef struct UnkStruct_wifi_lobby_map_02263344_t {
    u16 heapID;
    u8 unk_02;
    u8 unk_03;
    UnkStruct_wifi_lobby_map_0226308C unk_04;
    UnkStruct_wifi_lobby_map_0226308C unk_14;
} UnkStruct_wifi_lobby_map_02263344;

typedef struct UnkStruct_wifi_lobby_map_022630A4_t {
    u32 unk_00;
    UnkStruct_wifi_lobby_map_0225DEE8 *unk_04;
    UnkStruct_wifi_lobby_map_02263344 unk_08[20];
    UnkStruct_wifi_lobby_map_02263344 unk_2D8;
} UnkStruct_wifi_lobby_map_022630A4;

static void wifi_lobby_map_02262F14(UnkStruct_wifi_lobby_map_022630A4 *param0, u32 param1);
static void wifi_lobby_map_02262F64(UnkStruct_wifi_lobby_map_02263344 *param0, u32 param1, enum HeapID heapID);
static void wifi_lobby_map_02262F70(UnkStruct_wifi_lobby_map_02263344 *param0);
static void wifi_lobby_map_02262F94(UnkStruct_wifi_lobby_map_02263344 *param0, UnkStruct_wifi_lobby_map_022630A4 *param1, u32 param2, u32 param3);
static void wifi_lobby_map_02262FD4(UnkStruct_wifi_lobby_map_02263344 *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2);
static void wifi_lobby_map_02263008(UnkStruct_wifi_lobby_map_02263344 *param0, BOOL param1);
static void wifi_lobby_map_0226300C(UnkStruct_wifi_lobby_map_02263344 *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2);
static void wifi_lobby_map_02263044(UnkStruct_wifi_lobby_map_02263344 *param0);
static BOOL wifi_lobby_map_0226306C(const UnkStruct_wifi_lobby_map_02263344 *param0);
static BOOL wifi_lobby_map_0226307C(const UnkStruct_wifi_lobby_map_02263344 *param0);
static void wifi_lobby_map_0226308C(UnkStruct_wifi_lobby_map_0226308C *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2, u32 param3, void *param4);
static void wifi_lobby_map_02263098(UnkStruct_wifi_lobby_map_0226308C *param0);

UnkStruct_wifi_lobby_map_022630A4 *wifi_lobby_map_02262DA8(UnkStruct_wifi_lobby_map_0225DEE8 *param0, enum HeapID heapID)
{
    UnkStruct_wifi_lobby_map_022630A4 *v0 = Heap_Alloc(heapID, sizeof(UnkStruct_wifi_lobby_map_022630A4));
    memset(v0, 0, sizeof(UnkStruct_wifi_lobby_map_022630A4));

    v0->unk_00 = heapID;
    v0->unk_04 = param0;

    {
        int v1;

        for (v1 = 0; v1 < 20; v1++) {
            wifi_lobby_map_02262F64(&v0->unk_08[v1], v1, heapID);
        }
    }

    wifi_lobby_map_02262F64(&v0->unk_2D8, 0, heapID);

    return v0;
}

void wifi_lobby_map_02262DF4(UnkStruct_wifi_lobby_map_022630A4 *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 20; v0++) {
            wifi_lobby_map_02262F70(&param0->unk_08[v0]);
        }
    }

    wifi_lobby_map_02262F70(&param0->unk_2D8);
    Heap_Free(param0);
}

void wifi_lobby_map_02262E20(UnkStruct_wifi_lobby_map_022630A4 *param0)
{
    wifi_lobby_map_02262F14(param0, 0);
}

void wifi_lobby_map_02262E2C(UnkStruct_wifi_lobby_map_022630A4 *param0)
{
    wifi_lobby_map_02262F14(param0, 1);
}

void *wifi_lobby_map_02262E38(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    return param0->unk_04.unk_08;
}

void *wifi_lobby_map_02262E3C(UnkStruct_wifi_lobby_map_02263344 *param0, u32 param1)
{
    GF_ASSERT(param0->unk_04.unk_04 == NULL);

    param0->unk_04.unk_04 = Heap_Alloc(param0->heapID, param1);
    memset(param0->unk_04.unk_04, 0, param1);

    return param0->unk_04.unk_04;
}

void wifi_lobby_map_02262E64(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    GF_ASSERT(param0->unk_04.unk_04 != NULL);
    Heap_Free(param0->unk_04.unk_04);
    param0->unk_04.unk_04 = NULL;
}

void *wifi_lobby_map_02262E80(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    return param0->unk_04.unk_04;
}

u32 wifi_lobby_map_02262E84(const UnkStruct_wifi_lobby_map_02263344 *param0)
{
    return param0->unk_04.unk_0C;
}

void wifi_lobby_map_02262E88(UnkStruct_wifi_lobby_map_02263344 *param0, u32 param1)
{
    param0->unk_04.unk_0C = param1;
}

void wifi_lobby_map_02262E8C(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    param0->unk_04.unk_0C++;
}

void wifi_lobby_map_02262E94(UnkStruct_wifi_lobby_map_022630A4 *param0, u32 param1, const UnkStruct_wifi_lobby_map_0226DA18 *param2, void *param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_02262FD4(&param0->unk_08[param1], param2, param3);
}

void wifi_lobby_map_02262EC0(UnkStruct_wifi_lobby_map_022630A4 *param0, u32 param1, const UnkStruct_wifi_lobby_map_0226DA18 *param2, void *param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_0226300C(&param0->unk_08[param1], param2, param3);
}

void wifi_lobby_map_02262EEC(UnkStruct_wifi_lobby_map_022630A4 *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_02263008(&param0->unk_08[param1], param2);
}

static void wifi_lobby_map_02262F14(UnkStruct_wifi_lobby_map_022630A4 *param0, u32 param1)
{
    if (wifi_lobby_map_0226307C(&param0->unk_2D8) == 1) {
        wifi_lobby_map_02262F94(&param0->unk_2D8, param0, param1, 0);
        return;
    }

    {
        int v0;

        for (v0 = 0; v0 < 20; v0++) {
            if (wifi_lobby_map_0226307C(&param0->unk_08[v0]) == 1) {
                wifi_lobby_map_02262F94(&param0->unk_08[v0], param0, param1, v0);
            }
        }
    }
}

static void wifi_lobby_map_02262F64(UnkStruct_wifi_lobby_map_02263344 *param0, u32 param1, enum HeapID heapID)
{
    param0->heapID = heapID;
    param0->unk_02 = 1;
    param0->unk_03 = param1;
}

static void wifi_lobby_map_02262F70(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    if (param0->unk_04.unk_04 != NULL) {
        Heap_Free(param0->unk_04.unk_04);
    }

    if (param0->unk_14.unk_04 != NULL) {
        Heap_Free(param0->unk_14.unk_04);
    }

    memset(param0, 0, sizeof(UnkStruct_wifi_lobby_map_02263344));
}

static void wifi_lobby_map_02262F94(UnkStruct_wifi_lobby_map_02263344 *param0, UnkStruct_wifi_lobby_map_022630A4 *param1, u32 param2, u32 param3)
{
    BOOL v0;
    UnkFuncPtr_wifi_lobby_map_0226DA18 v1;

    if (param0->unk_02 == 0) {
        return;
    }

    switch (param2) {
    case 0:
        v1 = param0->unk_04.unk_00->unk_00;
        break;
    case 1:
        v1 = param0->unk_04.unk_00->unk_04;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    if (v1 != NULL) {
        v0 = v1(param0, param1->unk_04, param3);

        if (v0 == 1) {
            wifi_lobby_map_02263044(param0);
        }
    }
}

static void wifi_lobby_map_02262FD4(UnkStruct_wifi_lobby_map_02263344 *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2)
{
    GF_ASSERT(wifi_lobby_map_0226306C(param0) == 1);
    GF_ASSERT(param0->unk_04.unk_04 == NULL);

    wifi_lobby_map_0226308C(&param0->unk_04, param1, param2, 0, NULL);
}

static void wifi_lobby_map_02263008(UnkStruct_wifi_lobby_map_02263344 *param0, BOOL param1)
{
    param0->unk_02 = param1;
}

static void wifi_lobby_map_0226300C(UnkStruct_wifi_lobby_map_02263344 *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2)
{
    GF_ASSERT(wifi_lobby_map_0226306C(param0) == 1);
    param0->unk_14 = param0->unk_04;

    wifi_lobby_map_0226308C(&param0->unk_04, param1, param2, 0, NULL);
}

static void wifi_lobby_map_02263044(UnkStruct_wifi_lobby_map_02263344 *param0)
{
    GF_ASSERT(param0->unk_04.unk_04 == NULL);
    param0->unk_04 = param0->unk_14;

    wifi_lobby_map_02263098(&param0->unk_14);
}

static BOOL wifi_lobby_map_0226306C(const UnkStruct_wifi_lobby_map_02263344 *param0)
{
    if (param0->unk_14.unk_00 == NULL) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226307C(const UnkStruct_wifi_lobby_map_02263344 *param0)
{
    if (param0->unk_04.unk_00 == NULL) {
        return 0;
    }

    return 1;
}

static void wifi_lobby_map_0226308C(UnkStruct_wifi_lobby_map_0226308C *param0, const UnkStruct_wifi_lobby_map_0226DA18 *param1, void *param2, u32 param3, void *param4)
{
    param0->unk_00 = param1;
    param0->unk_0C = param3;
    param0->unk_04 = param4;
    param0->unk_08 = param2;
}

static void wifi_lobby_map_02263098(UnkStruct_wifi_lobby_map_0226308C *param0)
{
    param0->unk_00 = NULL;
    param0->unk_0C = 0;
    param0->unk_04 = NULL;
    param0->unk_08 = NULL;
}
