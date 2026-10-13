#include "wifi_lobby_map/wifi_lobby_map_0226C8B4.h"

#include <nitro.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"

#include "heap.h"
#include "sound_playback.h"

typedef struct {
    u32 frameThreshold;
    fx32 speed;
} WiFiLobbyMapFireworksEffect;

typedef union {
    struct {
        u32 unk_00;
    } val1;
    struct {
        u32 unk_00;
    } val2;
    struct {
        u32 unk_00;
    } val3;
} WiFiLobbyMapFireworksState;

typedef struct {
    const u8 *ids;
    u32 count;
} WiFiLobbyMapObjectIdList;

typedef struct WiFiLobbyMapFireworks_t {
    const WiFiPlazaLobbyState *lobbyState;
    WiFiLobbyMapObjectManager *objectManager;
    u8 eventStage;
    u8 soundPlaying;
    u16 state;
    WiFiLobbyMapFireworksState stateData;
} WiFiLobbyMapFireworks;

static void wifi_lobby_map_0226C984(WiFiLobbyMapFireworks *param0, u32 param1, u32 param2);
static void wifi_lobby_map_0226C9AC(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226C9B0(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226C9B4(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CA38(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CAD4(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CB1C(WiFiLobbyMapFireworks *param0, u32 param1, u32 param2);
static void wifi_lobby_map_0226CB54(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CB64(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CB74(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CB84(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CB94(WiFiLobbyMapFireworks *param0, u32 param1);
static void wifi_lobby_map_0226CBB4(u32 param0, WiFiLobbyMapObjectIdList *param1);
static void wifi_lobby_map_0226CC3C(WiFiLobbyMapFireworks *param0);
static void wifi_lobby_map_0226CC58(WiFiLobbyMapFireworks *param0);

static const u8 Unk_wifi_lobby_map_0226E74C[] = {
    0x6,
    0xD,
    0x5,
    0xB,
    0x7,
    0xE,
    0x8,
    0xC,
    0x1,
    0x0,
    0x2,
    0xA,
    0x10,
    0x9,
    0x4,
    0x3,
    0xF
};

static const u8 Unk_wifi_lobby_map_0226E6CC[] = {
    0x5,
    0xD,
    0x6,
    0x7,
    0xE,
    0x8
};

static const u8 Unk_wifi_lobby_map_0226E6C4[] = {
    0xB,
    0xC
};

static const u8 Unk_wifi_lobby_map_0226E6BC[] = {
    0xF,
    0x10
};

static const u8 Unk_wifi_lobby_map_0226E6B4[] = {
    0x4
};

static const u8 Unk_wifi_lobby_map_0226E6B8[] = {
    0x3
};

static const u8 Unk_wifi_lobby_map_0226E6C0[] = {
    0x9,
    0xA
};

static const u8 Unk_wifi_lobby_map_0226E6C8[] = {
    0x1,
    0x2,
    0x0
};

static const u8 Unk_wifi_lobby_map_0226E6D4[7][2] = {
    { 0x0, 0x5 },
    { 0x1, 0x6 },
    { 0x2, 0x0 },
    { 0x3, 0x1 },
    { 0x4, 0x2 },
    { 0x5, 0x3 },
    { 0x6, 0x4 }
};

static const WiFiLobbyMapFireworksEffect Unk_wifi_lobby_map_0226E6FC[3] = {
    { 0xA, FX32_ONE },
    { 0x2D, FX32_ONE },
    { 0x50, FX32_HALF }
};

WiFiLobbyMapFireworks *wifi_lobby_map_0226C8B4(const WiFiPlazaLobbyState *param0, WiFiLobbyMapObjectManager *param1, u32 heapID)
{
    WiFiLobbyMapFireworks *v0;
    u32 v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapFireworks));
    memset(v0, 0, sizeof(WiFiLobbyMapFireworks));

    v0->lobbyState = param0;
    v0->objectManager = param1;
    v1 = WiFiPlazaLobby_State_GetFireworksEventStage(param0);
    v0->state = WiFiPlazaLobby_State_GetFireworksState(param0);

    if ((0 != v0->state) && (v1 != 0)) {
        u32 v2;

        wifi_lobby_map_0226251C(param1, 1);
        wifi_lobby_map_0226CC3C(v0);

        v2 = WiFiPlazaLobby_State_GetFireworksFrame(param0);
        wifi_lobby_map_0226CB1C(v0, v1, v2);
    }

    return v0;
}

void wifi_lobby_map_0226C914(WiFiLobbyMapFireworks *param0)
{
    wifi_lobby_map_0226CC58(param0);
    Heap_Free(param0);
}

void wifi_lobby_map_0226C924(WiFiLobbyMapFireworks *param0)
{
    u32 v0;
    u32 v1;
    u32 v2;

    v1 = WiFiPlazaLobby_State_GetFireworksEventStage(param0->lobbyState);
    v2 = WiFiPlazaLobby_State_GetFireworksFrame(param0->lobbyState);
    v0 = WiFiPlazaLobby_State_GetFireworksState(param0->lobbyState);

    if (param0->state != v0) {
        param0->state = v0;

        if (v0 == 1) {
            wifi_lobby_map_0226251C(param0->objectManager, 1);
            wifi_lobby_map_0226CB1C(param0, v1, v2);
            wifi_lobby_map_0226CC3C(param0);
        }
    }

    if (v0 != 0) {
        if (param0->eventStage != v1) {
            wifi_lobby_map_0226CB1C(param0, v1, v2);
        }

        wifi_lobby_map_0226C984(param0, v1, v2);
    }
}

static void wifi_lobby_map_0226C984(WiFiLobbyMapFireworks *param0, u32 param1, u32 param2)
{
    static void (*const v0[])(WiFiLobbyMapFireworks *, u32) = {
        wifi_lobby_map_0226C9AC,
        wifi_lobby_map_0226C9AC,
        wifi_lobby_map_0226C9B0,
        wifi_lobby_map_0226C9B4,
        wifi_lobby_map_0226CA38,
        wifi_lobby_map_0226CAD4
    };

    GF_ASSERT(param1 < 6);

    if (param1 < 6) {
        v0[param1](param0, param2);
    }
}

static void wifi_lobby_map_0226C9AC(WiFiLobbyMapFireworks *param0, u32 param1)
{
    return;
}

static void wifi_lobby_map_0226C9B0(WiFiLobbyMapFireworks *param0, u32 param1)
{
    return;
}

static void wifi_lobby_map_0226C9B4(WiFiLobbyMapFireworks *param0, u32 param1)
{
    BOOL v0;
    u32 v1;
    BOOL v2;
    BOOL v3;
    u32 v4;
    static const u32 v5[4][2] = {
        { 0, 2 },
        { 1, 3 },
        { 2, 0 },
        { 3, 1 },
    };

    if ((param1 % 14) == 0) {
        v1 = 0;

        do {
            v3 = 0;

            if ((v1 % 4) == v5[param0->stateData.val1.unk_00][0]) {
                v2 = 1;
                v3 = 1;
            } else if ((v1 % 4) == v5[param0->stateData.val1.unk_00][1]) {
                v2 = 0;
                v3 = 1;
            }

            if (v3 == 1) {
                if (v1 < NELEMS(Unk_wifi_lobby_map_0226E74C)) {
                    v4 = Unk_wifi_lobby_map_0226E74C[v1];
                    v0 = wifi_lobby_map_02262754(param0->objectManager, v4, v2, (FX32_ONE));
                    GF_ASSERT(v0 == 1);
                } else {
                    v0 = 0;
                }
            } else {
                v0 = 1;
            }

            v1++;
        } while (v0 == 1);

        param0->stateData.val1.unk_00 = (param0->stateData.val1.unk_00 + 1) % 4;
    }
}

static void wifi_lobby_map_0226CA38(WiFiLobbyMapFireworks *param0, u32 param1)
{
    int v0;
    u32 v1, v2;
    WiFiLobbyMapObjectIdList v3;
    BOOL v4;

    if ((param1 % 6) == 0) {
        v1 = Unk_wifi_lobby_map_0226E6D4[param0->stateData.val2.unk_00][1];
        v2 = Unk_wifi_lobby_map_0226E6D4[param0->stateData.val2.unk_00][0];

        wifi_lobby_map_0226CBB4(v1, &v3);

        for (v0 = 0; v0 < v3.count; v0++) {
            v4 = wifi_lobby_map_02262754(param0->objectManager, v3.ids[v0], 0, (FX32_ONE));
            GF_ASSERT(v4 == 1);
        }

        wifi_lobby_map_0226CBB4(v2, &v3);

        for (v0 = 0; v0 < v3.count; v0++) {
            v4 = wifi_lobby_map_02262754(param0->objectManager, v3.ids[v0], 1, (FX32_ONE));
            GF_ASSERT(v4 == 1);
        }

        param0->stateData.val2.unk_00 = (param0->stateData.val2.unk_00 + 1) % 7;
    }
}

static void wifi_lobby_map_0226CAD4(WiFiLobbyMapFireworks *param0, u32 param1)
{
    if (param0->stateData.val3.unk_00 < 3) {
        if (Unk_wifi_lobby_map_0226E6FC[param0->stateData.val3.unk_00].frameThreshold < param1) {
            wifi_lobby_map_0226278C(param0->objectManager, Unk_wifi_lobby_map_0226E6FC[param0->stateData.val3.unk_00].speed);
            wifi_lobby_map_022625D8(param0->objectManager, Unk_wifi_lobby_map_0226E6FC[param0->stateData.val3.unk_00].speed);
            Sound_PlayEffect(SEQ_SE_PL_140_2_sseq);

            param0->stateData.val3.unk_00++;
        }
    }
}

static void wifi_lobby_map_0226CB1C(WiFiLobbyMapFireworks *param0, u32 param1, u32 param2)
{
    static void (*const v0[])(WiFiLobbyMapFireworks *, u32) = {
        wifi_lobby_map_0226CB54,
        wifi_lobby_map_0226CB54,
        wifi_lobby_map_0226CB64,
        wifi_lobby_map_0226CB74,
        wifi_lobby_map_0226CB84,
        wifi_lobby_map_0226CB94
    };

    GF_ASSERT(param1 < 6);

    if (param1 < 6) {
        memset(&param0->stateData, 0, sizeof(WiFiLobbyMapFireworksState));

        v0[param1](param0, param2);
        param0->eventStage = param1;
    }
}

static void wifi_lobby_map_0226CB54(WiFiLobbyMapFireworks *param0, u32 param1)
{
    wifi_lobby_map_02262724(param0->objectManager, 0, FX32_ONE);
}

static void wifi_lobby_map_0226CB64(WiFiLobbyMapFireworks *param0, u32 param1)
{
    wifi_lobby_map_02262724(param0->objectManager, 1, FX32_ONE);
}

static void wifi_lobby_map_0226CB74(WiFiLobbyMapFireworks *param0, u32 param1)
{
    wifi_lobby_map_02262724(param0->objectManager, 0, FX32_ONE);
}

static void wifi_lobby_map_0226CB84(WiFiLobbyMapFireworks *param0, u32 param1)
{
    wifi_lobby_map_02262724(param0->objectManager, 0, FX32_ONE);
}

static void wifi_lobby_map_0226CB94(WiFiLobbyMapFireworks *param0, u32 param1)
{
    wifi_lobby_map_0226CC58(param0);

    wifi_lobby_map_02262724(param0->objectManager, 0, FX32_ONE);
    wifi_lobby_map_0226251C(param0->objectManager, 0);
}

static void wifi_lobby_map_0226CBB4(u32 param0, WiFiLobbyMapObjectIdList *param1)
{
    switch (param0) {
    case 0:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6CC);
        param1->ids = Unk_wifi_lobby_map_0226E6CC;
        break;
    case 1:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6C4);
        param1->ids = Unk_wifi_lobby_map_0226E6C4;
        break;
    case 2:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6BC);
        param1->ids = Unk_wifi_lobby_map_0226E6BC;
        break;
    case 3:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6B4);
        param1->ids = Unk_wifi_lobby_map_0226E6B4;
        break;
    case 4:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6B8);
        param1->ids = Unk_wifi_lobby_map_0226E6B8;
        break;
    case 5:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6C0);
        param1->ids = Unk_wifi_lobby_map_0226E6C0;
        break;
    case 6:
        param1->count = NELEMS(Unk_wifi_lobby_map_0226E6C8);
        param1->ids = Unk_wifi_lobby_map_0226E6C8;
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void wifi_lobby_map_0226CC3C(WiFiLobbyMapFireworks *param0)
{
    if (param0->soundPlaying == 0) {
        Sound_PlayEffect(SEQ_SE_PL_140_3_sseq);
        param0->soundPlaying = 1;
    }
}

static void wifi_lobby_map_0226CC58(WiFiLobbyMapFireworks *param0)
{
    if (param0->soundPlaying) {
        Sound_StopEffect(1438, 0);
        param0->soundPlaying = 0;
    }
}
