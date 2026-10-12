#include "wifi_lobby_map/wifi_lobby_map_02262DA8.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_map/funcptr_wifi_lobby_map_0226DA18.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_callbacks.h"

#include "heap.h"

typedef struct {
    const WiFiLobbyMapTaskCallbacks *unk_00;
    void *unk_04;
    void *unk_08;
    u32 unk_0C;
} WiFiLobbyMapTaskContext;

typedef struct WiFiLobbyMapTask_t {
    u16 heapID;
    u8 unk_02;
    u8 unk_03;
    WiFiLobbyMapTaskContext unk_04;
    WiFiLobbyMapTaskContext unk_14;
} WiFiLobbyMapTask;

typedef struct WiFiLobbyMapTaskManager_t {
    u32 unk_00;
    WiFiLobbyMapApp *unk_04;
    WiFiLobbyMapTask unk_08[20];
    WiFiLobbyMapTask unk_2D8;
} WiFiLobbyMapTaskManager;

static void wifi_lobby_map_02262F14(WiFiLobbyMapTaskManager *param0, u32 param1);
static void wifi_lobby_map_02262F64(WiFiLobbyMapTask *param0, u32 param1, enum HeapID heapID);
static void wifi_lobby_map_02262F70(WiFiLobbyMapTask *param0);
static void wifi_lobby_map_02262F94(WiFiLobbyMapTask *param0, WiFiLobbyMapTaskManager *param1, u32 param2, u32 param3);
static void wifi_lobby_map_02262FD4(WiFiLobbyMapTask *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2);
static void wifi_lobby_map_02263008(WiFiLobbyMapTask *param0, BOOL param1);
static void wifi_lobby_map_0226300C(WiFiLobbyMapTask *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2);
static void wifi_lobby_map_02263044(WiFiLobbyMapTask *param0);
static BOOL wifi_lobby_map_0226306C(const WiFiLobbyMapTask *param0);
static BOOL wifi_lobby_map_0226307C(const WiFiLobbyMapTask *param0);
static void wifi_lobby_map_0226308C(WiFiLobbyMapTaskContext *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2, u32 param3, void *param4);
static void wifi_lobby_map_02263098(WiFiLobbyMapTaskContext *param0);

WiFiLobbyMapTaskManager *wifi_lobby_map_02262DA8(WiFiLobbyMapApp *param0, enum HeapID heapID)
{
    WiFiLobbyMapTaskManager *v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapTaskManager));
    memset(v0, 0, sizeof(WiFiLobbyMapTaskManager));

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

void wifi_lobby_map_02262DF4(WiFiLobbyMapTaskManager *param0)
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

void wifi_lobby_map_02262E20(WiFiLobbyMapTaskManager *param0)
{
    wifi_lobby_map_02262F14(param0, 0);
}

void wifi_lobby_map_02262E2C(WiFiLobbyMapTaskManager *param0)
{
    wifi_lobby_map_02262F14(param0, 1);
}

void *wifi_lobby_map_02262E38(WiFiLobbyMapTask *param0)
{
    return param0->unk_04.unk_08;
}

void *wifi_lobby_map_02262E3C(WiFiLobbyMapTask *param0, u32 param1)
{
    GF_ASSERT(param0->unk_04.unk_04 == NULL);

    param0->unk_04.unk_04 = Heap_Alloc(param0->heapID, param1);
    memset(param0->unk_04.unk_04, 0, param1);

    return param0->unk_04.unk_04;
}

void wifi_lobby_map_02262E64(WiFiLobbyMapTask *param0)
{
    GF_ASSERT(param0->unk_04.unk_04 != NULL);
    Heap_Free(param0->unk_04.unk_04);
    param0->unk_04.unk_04 = NULL;
}

void *wifi_lobby_map_02262E80(WiFiLobbyMapTask *param0)
{
    return param0->unk_04.unk_04;
}

u32 wifi_lobby_map_02262E84(const WiFiLobbyMapTask *param0)
{
    return param0->unk_04.unk_0C;
}

void wifi_lobby_map_02262E88(WiFiLobbyMapTask *param0, u32 param1)
{
    param0->unk_04.unk_0C = param1;
}

void wifi_lobby_map_02262E8C(WiFiLobbyMapTask *param0)
{
    param0->unk_04.unk_0C++;
}

void wifi_lobby_map_02262E94(WiFiLobbyMapTaskManager *param0, u32 param1, const WiFiLobbyMapTaskCallbacks *param2, void *param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_02262FD4(&param0->unk_08[param1], param2, param3);
}

void wifi_lobby_map_02262EC0(WiFiLobbyMapTaskManager *param0, u32 param1, const WiFiLobbyMapTaskCallbacks *param2, void *param3)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_0226300C(&param0->unk_08[param1], param2, param3);
}

void wifi_lobby_map_02262EEC(WiFiLobbyMapTaskManager *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param0);
    GF_ASSERT(param1 < 20);

    wifi_lobby_map_02263008(&param0->unk_08[param1], param2);
}

static void wifi_lobby_map_02262F14(WiFiLobbyMapTaskManager *param0, u32 param1)
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

static void wifi_lobby_map_02262F64(WiFiLobbyMapTask *param0, u32 param1, enum HeapID heapID)
{
    param0->heapID = heapID;
    param0->unk_02 = 1;
    param0->unk_03 = param1;
}

static void wifi_lobby_map_02262F70(WiFiLobbyMapTask *param0)
{
    if (param0->unk_04.unk_04 != NULL) {
        Heap_Free(param0->unk_04.unk_04);
    }

    if (param0->unk_14.unk_04 != NULL) {
        Heap_Free(param0->unk_14.unk_04);
    }

    memset(param0, 0, sizeof(WiFiLobbyMapTask));
}

static void wifi_lobby_map_02262F94(WiFiLobbyMapTask *param0, WiFiLobbyMapTaskManager *param1, u32 param2, u32 param3)
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

static void wifi_lobby_map_02262FD4(WiFiLobbyMapTask *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2)
{
    GF_ASSERT(wifi_lobby_map_0226306C(param0) == 1);
    GF_ASSERT(param0->unk_04.unk_04 == NULL);

    wifi_lobby_map_0226308C(&param0->unk_04, param1, param2, 0, NULL);
}

static void wifi_lobby_map_02263008(WiFiLobbyMapTask *param0, BOOL param1)
{
    param0->unk_02 = param1;
}

static void wifi_lobby_map_0226300C(WiFiLobbyMapTask *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2)
{
    GF_ASSERT(wifi_lobby_map_0226306C(param0) == 1);
    param0->unk_14 = param0->unk_04;

    wifi_lobby_map_0226308C(&param0->unk_04, param1, param2, 0, NULL);
}

static void wifi_lobby_map_02263044(WiFiLobbyMapTask *param0)
{
    GF_ASSERT(param0->unk_04.unk_04 == NULL);
    param0->unk_04 = param0->unk_14;

    wifi_lobby_map_02263098(&param0->unk_14);
}

static BOOL wifi_lobby_map_0226306C(const WiFiLobbyMapTask *param0)
{
    if (param0->unk_14.unk_00 == NULL) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226307C(const WiFiLobbyMapTask *param0)
{
    if (param0->unk_04.unk_00 == NULL) {
        return 0;
    }

    return 1;
}

static void wifi_lobby_map_0226308C(WiFiLobbyMapTaskContext *param0, const WiFiLobbyMapTaskCallbacks *param1, void *param2, u32 param3, void *param4)
{
    param0->unk_00 = param1;
    param0->unk_0C = param3;
    param0->unk_04 = param4;
    param0->unk_08 = param2;
}

static void wifi_lobby_map_02263098(WiFiLobbyMapTaskContext *param0)
{
    param0->unk_00 = NULL;
    param0->unk_0C = 0;
    param0->unk_04 = NULL;
    param0->unk_08 = NULL;
}
