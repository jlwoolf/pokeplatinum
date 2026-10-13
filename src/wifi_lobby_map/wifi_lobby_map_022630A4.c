#include "wifi_lobby_map/wifi_lobby_map_022630A4.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/wifi_2d_char_0222BE18.h"
#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C700.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C9B4.h"
#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"
#include "wifi_lobby_map/wifi_lobby_map_02260A70.h"
#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"
#include "wifi_lobby_map/wifi_lobby_map_02262DA8.h"
#include "wifi_lobby_map/wifi_lobby_map_02265F38.h"
#include "wifi_lobby_map/wifi_lobby_map_02266E9C.h"
#include "wifi_lobby_map/wifi_lobby_map_0226CC74.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_actor_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_camera_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_args.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_recruit_substate.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_task_callbacks.h"

#include "enums.h"
#include "list_menu.h"
#include "math_util.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "system.h"

typedef struct {
    fx32 rotation;
    s8 timer;
    u8 direction;
    u8 remaining;
    u8 active;
} WiFiLobbyMapCameraAnim;

typedef struct {
    u16 nextState;
    u16 cosmeticID;
    s32 timer;
    ListMenuTemplate listTemplate;
    u16 type1;
    u16 type2;
} WiFiLobbyMapStatusTaskState;

typedef struct {
    u32 unk_00;
} WiFiLobbyMapInteractionState;

typedef struct {
    s32 nextState;
    u16 messageID;
    u16 flag;
    u32 activity;
} WiFiLobbyMapJoinTaskState;

typedef struct {
    WiFiLobbyMapRecruitSubstate substate;
} WiFiLobbyMapRecruitTaskState;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiLobbyMapVenueTaskState;

typedef struct {
    u32 floatSlot;
    u16 unk_04;
    u16 unk_06;
    s16 timer;
    u8 unk_0A;
    u8 frame;
    WiFiLobbyMapActor *actor;
    WiFiLobbyMapCameraAnim cameraAnim;
} WiFiLobbyMapCameraFollowTaskState;

typedef struct {
    u8 tileX;
    u8 tileY;
    u8 slot;
    u8 chatPending;
    u8 activity;
    u8 unk_05[3];
} WiFiLobbyMapPlayerJoinState;

typedef struct {
    WiFiLobbyMapPlayerJoinState unk_00;
} WiFiLobbyMapPlayerJoinTaskState;

typedef struct {
    WiFiLobbyMapActor *actor;
    u32 unk_04;
    u32 unk_08;
    fx32 targetY;
    fx32 targetX;
    s32 frame;
    WiFiLobbyMapCameraAnim cameraAnim;
} WiFiLobbyMapBoardingTaskState;

typedef void (*UnkFuncPtr_wifi_lobby_map_0226DBB8)(WiFiLobbyMapInteractionState *, WiFiLobbyMapApp *, u32, u32);

typedef struct {
    u8 unk_00[8];
    u32 unk_08;
    WiFiLobbyMapTaskCallbacks unk_0C;
    UnkFuncPtr_wifi_lobby_map_0226DBB8 unk_14;
} WiFiLobbyMapObjectInteraction;

static BOOL wifi_lobby_map_02263120(int param0);
static WiFiLobbyMapActor *wifi_lobby_map_022631F8(WiFiLobbyMapApp *param0, u32 param1);
static void wifi_lobby_map_02263230(WiFiLobbyMapApp *param0, u32 param1, u32 param2, u32 param3, int param4);
static void wifi_lobby_map_02263270(WiFiLobbyMapCameraAnim *param0);
static fx32 wifi_lobby_map_02263290(WiFiLobbyMapCameraAnim *param0);
static void wifi_lobby_map_0226332C(WiFiLobbyMapCameraAnim *param0);
static BOOL wifi_lobby_map_02263334(const WiFiLobbyMapCameraAnim *param0);
static BOOL wifi_lobby_map_02263344(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02263414(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02263910(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02263A58(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02263BA4(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static void wifi_lobby_map_0226315C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2, const WiFiLobbyMapObjectInteraction *param3, u32 param4);
static BOOL wifi_lobby_map_02263CC8(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_0226412C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02264150(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02264324(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_022646C8(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02264974(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static u32 wifi_lobby_map_02264B64(u32 param0);
static u32 wifi_lobby_map_02264BCC(u32 param0);
static u32 wifi_lobby_map_02264C34(u32 param0);
static BOOL wifi_lobby_map_02264C9C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02264D38(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static void wifi_lobby_map_022650E4(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapCamera *param1);
static BOOL wifi_lobby_map_02265104(const WiFiLobbyMapCameraFollowTaskState *param0, const WiFiLobbyMapObjectManager *param1);
static BOOL wifi_lobby_map_02265144(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapCamera *param2);
static BOOL wifi_lobby_map_022652BC(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1);
static void wifi_lobby_map_02265344(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapApp *param2);
static void wifi_lobby_map_02265370(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapApp *param2);
static void wifi_lobby_map_022653DC(WiFiLobbyMapStatusTaskState *param0, WiFiLobbyMapApp *param1);
static void wifi_lobby_map_02265450(WiFiLobbyMapStatusTaskState *param0, WiFiLobbyMapApp *param1);
static BOOL wifi_lobby_map_0226545C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02265630(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_022657D0(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02265840(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02265A84(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2);
static BOOL wifi_lobby_map_02265CCC(WiFiLobbyMapPlayerJoinState *param0, WiFiPlazaLobbyState *param1, WiFiLobbyMapApp *param2, WiFiLobbyMapActor *param3, u8 param4, int param5);
static BOOL wifi_lobby_map_02265ED0(const WiFiLobbyMapGrid *param0, const WiFiLobbyMapActorManager *param1, const u32 *param2, u32 param3, WiFi2DCharPosition *param4);

static const ListMenuTemplate Unk_wifi_lobby_map_0226DA98 = {
    NULL,
    NULL,
    NULL,
    NULL,
    0x12,
    0x7,
    0x0,
    0x8,
    0x0,
    0x0,
    0x1,
    0xF,
    0x2,
    0x0,
    0x10,
    0x1,
    0x0,
    0x0,
    NULL
};

static const u32 Unk_wifi_lobby_map_0226DA28[4] = {
    0x4F,
    0x50,
    0x51,
    0x52
};

static const u32 Unk_wifi_lobby_map_0226DA58[4] = {
    0x53,
    0x54,
    0x55,
    0x56
};

static const u32 Unk_wifi_lobby_map_0226DA38[4] = {
    0x57,
    0x58,
    0x59,
    0x5A
};

static const u32 Unk_wifi_lobby_map_0226DA68[4] = {
    0x36,
    0x37,
    0x38,
    0x39
};

static const u32 Unk_wifi_lobby_map_0226DA48[4] = {
    0x32,
    0x33,
    0x34,
    0x35
};

static const u32 Unk_wifi_lobby_map_0226DAB8[8] = {
    0x22,
    0x23,
    0x24,
    0x25,
    0x26,
    0x27,
    0x28,
    0x29
};

static const u32 Unk_wifi_lobby_map_0226DAD8[8] = {
    0x2A,
    0x2B,
    0x2C,
    0x2D,
    0x2E,
    0x2F,
    0x30,
    0x31
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA18 = {
    wifi_lobby_map_02263344,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA78[4] = {
    { wifi_lobby_map_02263414, NULL },
    { wifi_lobby_map_02263910, NULL },
    { wifi_lobby_map_02263A58, NULL },
    { wifi_lobby_map_02263BA4, NULL }
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9D0 = {
    wifi_lobby_map_02263CC8,
    wifi_lobby_map_0226412C
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA20 = {
    wifi_lobby_map_02265F38,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA00 = {
    wifi_lobby_map_022669B8,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA10 = {
    wifi_lobby_map_0226545C,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9D8 = {
    wifi_lobby_map_02265630,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9E0 = {
    wifi_lobby_map_022657D0,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9E8 = {
    wifi_lobby_map_02265840,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9F0 = {
    wifi_lobby_map_02265A84,
    NULL
};

static const WiFiLobbyMapObjectInteraction Unk_wifi_lobby_map_0226DBB8[] = {
    {
        { 0x1, 0xFF },
        0x0,
        { wifi_lobby_map_02264150, NULL },
        NULL,
    },
    {
        { 0x16, 0x17, 0x18, 0x19, 0xFF },
        0x0,
        { wifi_lobby_map_02264324, NULL },
        NULL,
    },
    {
        { 0x1A, 0x1B, 0x1C, 0x1D, 0xFF },
        0x0,
        { wifi_lobby_map_02264324, NULL },
        NULL,
    },
    {
        { 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD },
        0x0,
        { wifi_lobby_map_02264324, NULL },
        NULL,
    },
    {
        { 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15 },
        0x0,
        { wifi_lobby_map_02264324, NULL },
        NULL,
    },
    {
        { 0x21, 0x22, 0x23, 0xFF },
        0x0,
        { wifi_lobby_map_02264D38, NULL },
        NULL,
    },
    {
        { 0x1E, 0x1F, 0x20, 0xFF },
        0x0,
        { wifi_lobby_map_022646C8, NULL },
        NULL,
    },
    {
        { 0x2C, 0xFF },
        0x0,
        { wifi_lobby_map_02264974, NULL },
        NULL,
    },
    {
        { 0xFF },
        0x3,
        { NULL, NULL },
        NULL,
    },
};

static const WiFiLobbyMapObjectInteraction Unk_wifi_lobby_map_0226DB28[] = {
    {
        { 0x24, 0xFF },
        0x1,
        { wifi_lobby_map_02264C9C, NULL },
        NULL,
    },
    {
        { 0x25, 0xFF },
        0x1,
        { wifi_lobby_map_02268390, NULL },
        NULL,
    },
    {
        { 0x26, 0xFF },
        0x1,
        { wifi_lobby_map_0226889C, NULL },
        NULL,
    },
    {
        { 0x27, 0x28, 0x29, 0xFF },
        0x1,
        { wifi_lobby_map_022669FC, NULL },
        NULL,
    },
    {
        { 0x2B, 0xFF },
        0x1,
        { wifi_lobby_map_0226CC74, NULL },
        NULL,
    },
    {
        { 0xFF },
        0x3,
        { NULL, NULL },
        NULL,
    },
};

static const WiFiLobbyMapObjectInteraction Unk_wifi_lobby_map_0226DAF8[] = {
    {
        { 0x27, 0x28, 0x29, 0xFF },
        0x1,
        { wifi_lobby_map_022669FC, NULL },
        NULL,
    },
    {
        { 0xFF },
        0x3,
        { NULL, NULL },
        NULL,
    },
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226D9F8 = {
    wifi_lobby_map_02266E9C,
    NULL
};

static const WiFiLobbyMapTaskCallbacks Unk_wifi_lobby_map_0226DA08 = {
    wifi_lobby_map_02267A44,
    NULL
};

void wifi_lobby_map_022630A4(WiFiLobbyMapApp *param0)
{
    WiFiLobbyMapArgs *v0;
    WiFiLobbyMapTaskManager *v1;
    u32 v2;
    u32 v3;

    v0 = wifi_lobby_map_0225DEEC(param0);
    v1 = wifi_lobby_map_0225DF10(param0);
    v2 = wifi_lobby_map_0225DF2C(param0);

    WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param0), 1);
    GF_ASSERT(v0->taskType < 4);
    wifi_lobby_map_02262E94(v1, v2, &Unk_wifi_lobby_map_0226DA78[v0->taskType], NULL);
}

void wifi_lobby_map_022630EC(WiFiLobbyMapApp *param0)
{
    int v0;
    u32 v1;
    WiFiLobbyMapTaskManager *v2;

    v1 = wifi_lobby_map_0225DF2C(param0);
    v2 = wifi_lobby_map_0225DF10(param0);

    for (v0 = 0; v0 < 20; v0++) {
        if (v1 != v0) {
            wifi_lobby_map_02262E94(v2, v0, &Unk_wifi_lobby_map_0226DA10, NULL);
        }
    }
}

static BOOL wifi_lobby_map_02263120(int param0)
{
    u32 v0;

    switch (param0) {
    case 0:
        v0 = PAD_KEY_UP;
        break;
    case 1:
        v0 = PAD_KEY_DOWN;
        break;
    case 2:
        v0 = PAD_KEY_LEFT;
        break;
    case 3:
        v0 = PAD_KEY_RIGHT;
        break;
    }

    if (gSystem.heldKeys & v0) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0226315C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2, const WiFiLobbyMapObjectInteraction *param3, u32 param4)
{
    int v0;
    int v1;
    WiFiLobbyMapInteractionState *v2;
    WiFiLobbyMapTaskManager *v3;

    v2 = wifi_lobby_map_02262E80(param0);

    {
        v3 = wifi_lobby_map_0225DF10(param1);
    }

    v0 = 0;

    while (param3[v0].unk_08 != 3) {
        for (v1 = 0; v1 < 8; v1++) {
            if (param3[v0].unk_00[v1] == 0xff) {
                break;
            }

            if (param3[v0].unk_00[v1] == param4) {
                switch (param3[v0].unk_08) {
                case 0:
                    wifi_lobby_map_02262E64(param0);
                    wifi_lobby_map_02262E94(v3, param2, &param3[v0].unk_0C, NULL);
                    break;
                case 1:
                    if (param3[v0].unk_14) {
                        param3[v0].unk_14(v2, param1, param2, param3[v0].unk_00[v1]);
                    }

                    wifi_lobby_map_02262EC0(v3, param2, &param3[v0].unk_0C, NULL);
                    break;
                }

                return;
            }
        }

        v0++;
    }

    GF_ASSERT(FALSE);
    return;
}

static WiFiLobbyMapActor *wifi_lobby_map_022631F8(WiFiLobbyMapApp *param0, u32 param1)
{
    WiFiLobbyMapActor *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiLobbyMapCamera *v2;
    VecFx32 v3;

    v1 = wifi_lobby_map_0225DEF0(param0);
    v0 = wifi_lobby_map_0225CB28(v1, param1);
    v2 = wifi_lobby_map_0225DF08(param0);

    wifi_lobby_map_0225D054(v0, &v3);
    wifi_lobby_map_02260B20(v2, v3.x, v3.y, v3.z);

    return v0;
}

static void wifi_lobby_map_02263230(WiFiLobbyMapApp *param0, u32 param1, u32 param2, u32 param3, int param4)
{
    WiFiLobbyMapActor *v0;
    WiFiLobbyMapActorManager *v1 = wifi_lobby_map_0225DEF0(param0);
    WiFiLobbyMapCamera *v2 = wifi_lobby_map_0225DF08(param0);
    v0 = wifi_lobby_map_0225CB5C(v1, param1, param2, param3);

    wifi_lobby_map_0225CD7C(v1, v0, 0, param4);
    wifi_lobby_map_02260B38(v2, v0);
}

static void wifi_lobby_map_02263270(WiFiLobbyMapCameraAnim *param0)
{
    param0->rotation = 0;
    param0->timer = 0;
    param0->direction = 1;
    param0->remaining = MTRNG_Next() % 4;
    param0->active = 1;
}

static fx32 wifi_lobby_map_02263290(WiFiLobbyMapCameraAnim *param0)
{
    u16 v0;

    switch (param0->direction) {
    case 0:
        param0->rotation = 0;
        break;
    case 1:
        if ((param0->remaining - 1) > 0) {
            param0->remaining--;
        } else {
            param0->direction = 2;
        }
        break;
    case 2:
        param0->timer++;

        v0 = (param0->timer * 0x7fff) / 4;
        param0->rotation = FX_Mul(FX_SinIdx(v0), (FX32_CONST(6)));

        if (param0->timer >= 4) {
            if (param0->active == 1) {
                param0->timer = 0;
                param0->direction = 1;
                param0->remaining = MTRNG_Next() % 4;
            } else {
                param0->direction = 0;
            }
        }
        break;
    }

    return param0->rotation;
}

static void wifi_lobby_map_0226332C(WiFiLobbyMapCameraAnim *param0)
{
    param0->active = 0;
}

static BOOL wifi_lobby_map_02263334(const WiFiLobbyMapCameraAnim *param0)
{
    if (param0->direction == 0) {
        return 0;
    }

    return 1;
}

static BOOL wifi_lobby_map_02263344(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActorManager *v0 = wifi_lobby_map_0225DEF0(param1);
    WiFiLobbyMapActor *v1 = wifi_lobby_map_0225CC70(v0, param2);
    WiFiPlazaLobbyState *v2 = wifi_lobby_map_0225DEE8(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        wifi_lobby_map_0225E46C(param1, param2);
        wifi_lobby_map_02262E88(param0, 1);

        if (param2 == WiFiPlazaLobby_State_GetMySlotIndex(v2)) {
            wifi_lobby_map_0225E43C(param1, 0);
        }
        break;
    case 1:
        if (wifi_lobby_map_0225E4AC(param1, param2) == 1) {
            wifi_lobby_map_02262E88(param0, 2);
        }
        break;
    case 2:
        if (param2 == WiFiPlazaLobby_State_GetMySlotIndex(v2)) {
            wifi_lobby_map_0225CDEC(v0, v1, 1);
        } else {
            if (wifi_lobby_map_0225E3F0(param1) == 1) {
                if (param2 != wifi_lobby_map_0225E3E0(param1)) {
                    wifi_lobby_map_0225CDEC(v0, v1, 2);
                }
            } else {
                wifi_lobby_map_0225CDEC(v0, v1, 2);
            }

            wifi_lobby_map_0225DF4C(param1, param2, 0);
        }

        wifi_lobby_map_0225E44C(param1);

        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_02263414(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapStatusTaskState *v0;
    WiFiLobbyMapActor *v1;
    WiFiLobbyMapActorManager *v2;
    WiFiPlazaLobbyState *v3;
    String *v4;

    v3 = wifi_lobby_map_0225DEE8(param1);
    v2 = wifi_lobby_map_0225DEF0(param1);
    v1 = wifi_lobby_map_0225CCAC(v2);
    v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapStatusTaskState));

        wifi_lobby_map_022653DC(v0, param1);
        WiFiPlazaLobby_State_PlayLobbyBGM(v3);

        {
            v0->cosmeticID = WiFiPlazaLobby_State_ChooseCosmeticID(v3);
            WiFiPlazaLobby_State_SetAppearanceRank(v3, v0->cosmeticID);
        }

        v1 = wifi_lobby_map_022631F8(param1, param2);

        wifi_lobby_map_0225CDEC(v2, v1, 4);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1:
        if ((wifi_lobby_map_0225DF30(param1) == 0) && (wifi_lobby_map_0225CE38(v1) == 1)) {
            wifi_lobby_map_0225CDEC(v2, v1, 0);

            {
                WiFiLobbyMapCamera *v5;

                v5 = wifi_lobby_map_0225DF08(param1);
                wifi_lobby_map_02260B38(v5, v1);
            }

            v0->timer = 16;
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 2:
        v0->timer--;

        if (v0->timer == 0) {
            wifi_lobby_map_0225DF18(param1, 1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 3:
        wifi_lobby_map_0225CD7C(v2, v1, 2, 0);
        v0->nextState = 4;
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 4:
        wifi_lobby_map_0225CD7C(v2, v1, 2, 0);
        v0->nextState = 5;
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 5:
        wifi_lobby_map_0225CD7C(v2, v1, 1, 3);
        v0->nextState = 6;
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 6:
        wifi_lobby_map_0225CD7C(v2, v1, 2, 3);
        v0->nextState = 8;
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 7:
        if (wifi_lobby_map_0225CD60(v1, 5) == 0) {
            wifi_lobby_map_02262E88(param0, v0->nextState);
        }
        break;
    case 8:
        v4 = wifi_lobby_map_0225E20C(param1, 1, 0);
        wifi_lobby_map_0225DF8C(param1, v4);
        v0->nextState = 16;
        wifi_lobby_map_02262E88(param0, 21);
        break;
    case 9:
        v4 = wifi_lobby_map_0225E20C(param1, 1, 5);
        wifi_lobby_map_0225DF9C(param1, v4);
        wifi_lobby_map_0225E074(param1, &v0->listTemplate, 0, 0);
        wifi_lobby_map_0225E0F4(param1, 1);
        wifi_lobby_map_02262E88(param0, 10);
        break;
    case 10: {
        u32 v6;
        u32 v7;
        BOOL v8 = 0;

        v6 = wifi_lobby_map_0225E0D4(param1);

        switch (v6) {
        case 0xffffffff:
            break;
        case 0xfffffffe:
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
        case 0:
            v0->type1 = 0;
            v8 = 1;
            break;
        default:
            v0->type1 = v6;
            v8 = 1;
            wifi_lobby_map_0225E30C(param1, 0, v6);
            v7 = 8;
            break;
        }

        if (v8 == 1) {
            wifi_lobby_map_0225E0E4(param1, NULL, NULL);

            if (v0->type1 != 0) {
                v4 = wifi_lobby_map_0225E20C(param1, 1, v7);
                wifi_lobby_map_0225DF9C(param1, v4);
                wifi_lobby_map_0225E164(param1);
                wifi_lobby_map_02262E88(param0, 11);
            } else {
                wifi_lobby_map_02262E88(param0, 17);
            }
        }
    } break;
    case 11: {
        int v9;

        v9 = wifi_lobby_map_0225E1C4(param1);

        switch (v9) {
        case 0:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 12);
            WiFiPlazaLobby_State_SetPokemonTypes(v3, v0->type1, v0->type2);
            wifi_lobby_map_0225E390(param1);
            Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
            break;
        case 1:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 9);
            break;
        default:
            break;
        }
    } break;
    case 12:
        v4 = wifi_lobby_map_0225E20C(param1, 1, 10);
        wifi_lobby_map_0225DF9C(param1, v4);
        wifi_lobby_map_0225E074(param1, &v0->listTemplate, 0, 0);
        wifi_lobby_map_0225E0F4(param1, 1);
        wifi_lobby_map_02262E88(param0, 13);
        break;
    case 13: {
        u32 v10;
        u32 v11;
        BOOL v12 = 0;

        v10 = wifi_lobby_map_0225E0D4(param1);

        switch (v10) {
        case 0xffffffff:
            break;
        case 0xfffffffe:
            Sound_PlayEffect(SE_CONFIRM_sseq_3);
        case 0:
            v0->type2 = 0;
            v12 = 1;
            break;
        default:
            v0->type2 = v10;
            v12 = 1;
            wifi_lobby_map_0225E30C(param1, 0, v10);
            v11 = 8;
            break;
        }

        if (v12 == 1) {
            wifi_lobby_map_0225E0E4(param1, NULL, NULL);

            if (v0->type2 != 0) {
                v4 = wifi_lobby_map_0225E20C(param1, 1, v11);
                wifi_lobby_map_0225DF9C(param1, v4);
                wifi_lobby_map_0225E164(param1);
                wifi_lobby_map_02262E88(param0, 15);
            } else {
                wifi_lobby_map_02262E88(param0, 19);
            }
        }
    } break;
    case 15: {
        int v13;

        v13 = wifi_lobby_map_0225E1C4(param1);

        switch (v13) {
        case 0:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 20);
            WiFiPlazaLobby_State_SetPokemonTypes(v3, v0->type1, v0->type2);
            wifi_lobby_map_0225E390(param1);
            Sound_PlayEffect(SEQ_SE_DP_BUTTON3_sseq);
            break;
        case 1:
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_02262E88(param0, 12);
            break;
        default:
            break;
        }
    } break;
    case 16:
        Sound_PlayEffect(SEQ_SE_PL_EFF03_4_sseq);
        wifi_lobby_map_0225E430(param1);
        wifi_lobby_map_0225E234(param1, param2, 0);
        wifi_lobby_map_0225E29C(param1, v0->cosmeticID, 1);
        {
            BOOL v14;

            v14 = WiFiPlazaLobby_State_IsMemberPresent(v3, param2);

            if (v14 == 0) {
                v4 = wifi_lobby_map_0225E20C(param1, 1, 1);
            } else {
                v4 = wifi_lobby_map_0225E20C(param1, 1, 124);
            }
        }
        wifi_lobby_map_0225DF8C(param1, v4);
        v0->nextState = 18;
        wifi_lobby_map_02262E88(param0, 21);
        break;
    case 17:
        v4 = wifi_lobby_map_0225E20C(param1, 1, 2);
        wifi_lobby_map_0225DF8C(param1, v4);
        v0->nextState = 22;
        wifi_lobby_map_02262E88(param0, 21);
        break;
    case 18:
        if (!((Sound_IsEffectPlaying(1448) == 0) && (gSystem.pressedKeys & (PAD_BUTTON_A | PAD_BUTTON_B)))) {
            break;
        }

        Sound_PlayEffect(SE_CONFIRM_sseq_3);

        v4 = wifi_lobby_map_0225E20C(param1, 1, 4);
        wifi_lobby_map_0225DF8C(param1, v4);

        v0->nextState = 9;
        wifi_lobby_map_02262E88(param0, 21);

        WiFiPlazaLobby_State_SetPokemonTypes(v3, v0->type1, v0->type2);
        wifi_lobby_map_0225E328(param1, param2, 0);
        break;
    case 19:
        wifi_lobby_map_0225E30C(param1, 0, v0->type1);
        v4 = wifi_lobby_map_0225E20C(param1, 1, 12);

        wifi_lobby_map_0225DF8C(param1, v4);
        v0->nextState = 17;

        wifi_lobby_map_02262E88(param0, 21);
        break;
    case 20:
        wifi_lobby_map_0225E30C(param1, 0, v0->type1);
        wifi_lobby_map_0225E30C(param1, 1, v0->type2);

        v4 = wifi_lobby_map_0225E20C(param1, 1, 11);
        wifi_lobby_map_0225DF8C(param1, v4);

        v0->nextState = 17;
        wifi_lobby_map_02262E88(param0, 21);
        break;

    case 21:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_02262E88(param0, v0->nextState);
        }
        break;
    case 22:
        wifi_lobby_map_0225CDEC(v2, v1, 1);
        wifi_lobby_map_0225DFEC(param1);
        wifi_lobby_map_02265450(v0, param1);
        wifi_lobby_map_02262E64(param0);

        {
            WiFiLobbyMapTaskManager *v15;
            u32 v16;

            v15 = wifi_lobby_map_0225DF10(param1);
            v16 = wifi_lobby_map_0225DF2C(param1);

            wifi_lobby_map_02262E94(v15, v16, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02263910(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActor *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiPlazaLobbyState *v3 = wifi_lobby_map_0225DEE8(param1);
    WiFiLobbyMapArgs *v2 = wifi_lobby_map_0225DEEC(param1);
    v1 = wifi_lobby_map_0225DEF0(param1);
    v0 = wifi_lobby_map_0225CCAC(v1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        wifi_lobby_map_02263230(param1, param2, v2->spawnX, v2->spawnY, 1);

        if (WiFiPlazaLobby_Time_HasWifiError() == 0) {
            WiFiPlazaLobby_Network_LeaveSubChannel();
        }

        WiFiPlazaLobby_State_SetBGMVolumeDucked(v3, 0);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1:
        if (WiFiPlazaLobby_Time_HasWifiError() == 0) {
            if (WiFiPlazaLobby_Network_IsSubChannelInactive() == 0) {
                break;
            }
        }

        v2 = wifi_lobby_map_0225DEEC(param1);

        if (wifi_lobby_map_0225DF30(param1) == 0) {
            wifi_lobby_map_02262E8C(param0);
            wifi_lobby_map_0225CDAC(v1, v0, 2, v2->direction);
        }
        break;
    case 2: {
        u32 v4;

        v4 = wifi_lobby_map_0225CD60(v0, 5);

        if (v4 == 0) {
            wifi_lobby_map_0225DF18(param1, 1);

            if (WiFiPlazaLobby_State_IsPlayerWarpPending(v3) == 1) {
                wifi_lobby_map_02262E8C(param0);
            } else {
                wifi_lobby_map_02262E88(param0, 5);
            }
        }
    } break;
    case 3: {
        String *v5;

        wifi_lobby_map_0225E27C(param1, v2->venue, 0);

        v5 = wifi_lobby_map_0225E20C(param1, 0, 21);

        wifi_lobby_map_0225DF8C(param1, v5);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 4:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_0225DFEC(param1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 5:
        wifi_lobby_map_0225CDEC(v1, v0, 1);

        {
            WiFiLobbyMapTaskManager *v6;
            u32 v7;

            v6 = wifi_lobby_map_0225DF10(param1);
            v7 = wifi_lobby_map_0225DF2C(param1);

            wifi_lobby_map_02262E94(v6, v7, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02263A58(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActor *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiLobbyMapTaskManager *v2;
    WiFiLobbyMapArgs *v3;
    WiFiPlazaLobbyState *v4;

    v2 = wifi_lobby_map_0225DF10(param1);
    v1 = wifi_lobby_map_0225DEF0(param1);
    v0 = wifi_lobby_map_0225CCAC(v1);
    v4 = wifi_lobby_map_0225DEE8(param1);
    v3 = wifi_lobby_map_0225DEEC(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0: {
        wifi_lobby_map_02263230(param1, param2, v3->spawnX, v3->spawnY, 1);
        wifi_lobby_map_02262E8C(param0);
        wifi_lobby_map_02262EC0(v2, param2, &Unk_wifi_lobby_map_0226DA00, NULL);
        WiFiPlazaLobby_State_SetBGMSuppressed(v4, 0);
        WiFiPlazaLobby_State_PlayLobbyBGM(v4);
    } break;
    case 1:

    {
        WiFiLobbyMapArgs *v5;

        v5 = wifi_lobby_map_0225DEEC(param1);

        if (wifi_lobby_map_0225DF30(param1) == 0) {
            wifi_lobby_map_02262E8C(param0);
            wifi_lobby_map_0225CDAC(v1, v0, 2, v5->direction);
        }
    } break;
    case 2: {
        u32 v6;

        v6 = wifi_lobby_map_0225CD60(v0, 5);

        if (v6 == 0) {
            wifi_lobby_map_0225DF18(param1, 1);

            if (WiFiPlazaLobby_State_IsTrainerInfoValid(v4) == 1) {
                wifi_lobby_map_02262E88(param0, 3);
            } else {
                wifi_lobby_map_02262E88(param0, 5);
            }
        }
    } break;
    case 3: {
        String *v7;

        wifi_lobby_map_0225E27C(param1, v3->venue, 0);
        v7 = wifi_lobby_map_0225E20C(param1, 0, 8);
        wifi_lobby_map_0225DF8C(param1, v7);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 4:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_0225DFEC(param1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 5:
        wifi_lobby_map_0225CDEC(v1, v0, 1);

        {
            WiFiLobbyMapTaskManager *v8;
            u32 v9;

            v8 = wifi_lobby_map_0225DF10(param1);
            v9 = wifi_lobby_map_0225DF2C(param1);

            wifi_lobby_map_02262E94(v8, v9, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02263BA4(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActor *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiPlazaLobbyState *v3 = wifi_lobby_map_0225DEE8(param1);
    WiFiLobbyMapArgs *v2 = wifi_lobby_map_0225DEEC(param1);
    v1 = wifi_lobby_map_0225DEF0(param1);
    v0 = wifi_lobby_map_0225CCAC(v1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        wifi_lobby_map_02263230(param1, param2, v2->spawnX, v2->spawnY, 1);
        WiFiPlazaLobby_State_SetBGMVolumeDucked(v3, 0);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1:
        v2 = wifi_lobby_map_0225DEEC(param1);

        if (wifi_lobby_map_0225DF30(param1) == 0) {
            wifi_lobby_map_02262E8C(param0);
            wifi_lobby_map_0225CDAC(v1, v0, 2, v2->direction);
        }
        break;
    case 2: {
        u32 v4;
        v4 = wifi_lobby_map_0225CD60(v0, 5);

        if (v4 == 0) {
            wifi_lobby_map_0225DF18(param1, 1);

            if (WiFiPlazaLobby_State_IsPlayerWarpPending(v3) == 1) {
                wifi_lobby_map_02262E8C(param0);
            } else {
                wifi_lobby_map_02262E88(param0, 5);
            }
        }
    } break;

    case 3: {
        String *v5;

        v5 = wifi_lobby_map_0225E20C(param1, 1, 91);

        wifi_lobby_map_0225DF8C(param1, v5);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 4:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_0225DFEC(param1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 5:
        wifi_lobby_map_0225CDEC(v1, v0, 1);

        {
            WiFiLobbyMapTaskManager *v6;
            u32 v7;

            v6 = wifi_lobby_map_0225DF10(param1);
            v7 = wifi_lobby_map_0225DF2C(param1);

            wifi_lobby_map_02262E94(v6, v7, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02263CC8(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapInteractionState *v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapInteractionState));
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1:
        wifi_lobby_map_0225E43C(param1, 0);

        {
            u32 v1;
            u32 v2;
            WiFiLobbyMapActor *v3;
            WiFi2DCharPosition v4, v5;
            u32 v6, v7;
            WiFiLobbyMapActorManager *v8;
            WiFiLobbyMapObjectManager *v9;
            WiFiLobbyMapGrid *v10;
            WiFiPlazaLobbyState *v11;
            WiFiLobbyMapTaskManager *v12;
            WiFiLobbyMapActor *v13;

            v12 = wifi_lobby_map_0225DF10(param1);
            v11 = wifi_lobby_map_0225DEE8(param1);
            v8 = wifi_lobby_map_0225DEF0(param1);
            v10 = wifi_lobby_map_0225DF00(param1);
            v9 = wifi_lobby_map_0225DEF8(param1);
            v13 = wifi_lobby_map_0225CCB0(v8);

            if (v13 != NULL) {
                if ((WiFiPlazaLobby_State_IsLobbyClosed(v11) == 0) && (WiFiPlazaLobby_State_IsNeonTransitionComplete(v11) == 1) && (WiFiPlazaLobby_State_IsQuestionAcknowledged(v11) == 0)) {
                    if (wifi_lobby_map_0225CE3C(v13) != 9) {
                        wifi_lobby_map_0225CDEC(v8, v13, 9);
                    }
                } else {
                    if (wifi_lobby_map_0225CE3C(v13) != 0) {
                        wifi_lobby_map_0225CDEC(v8, v13, 0);
                    }
                }
            }

            v3 = wifi_lobby_map_0225CCAC(v8);
            v1 = wifi_lobby_map_0225CD60(v3, 5);
            v2 = wifi_lobby_map_0225CD60(v3, 6);
            v4 = wifi_lobby_map_0225CD34(v3);
            v5 = WiFi2DCharPosition_OffsetByDirection(v4, v2);
            v6 = wifi_lobby_map_0225C8C4(v10, (v4.x) / 16, (v4.y) / 16);
            v7 = wifi_lobby_map_0225C8C4(v10, (v5.x) / 16, (v5.y) / 16);

            {
                u32 v14;

                v14 = wifi_lobby_map_0225E3E0(param1);

                if (v14 != param2) {
                    if (wifi_lobby_map_0225DF84(param1, v14)) {
                        wifi_lobby_map_0225E3D0(param1);
                    }
                }
            }

            if (v1 != 0) {
                if (wifi_lobby_map_0225E400(param1) == 1) {
                    WiFiLobbyMapActor *v15;
                    u32 v16;

                    if ((v1 == 2) || (v1 == 3) || (v1 == 1)) {
                        v16 = wifi_lobby_map_0225E3E0(param1);

                        if (v16 != param2) {
                            v15 = wifi_lobby_map_0225CC70(v8, v16);

                            if (v15) {
                                if (wifi_lobby_map_0225CE3C(v15) == 0) {
                                    wifi_lobby_map_0225CDEC(v8, v15, v0->unk_00);
                                }
                            }
                        }

                        wifi_lobby_map_0225E3D0(param1);
                    }
                }
            } else {
                wifi_lobby_map_0225E43C(param1, 0);

                if (wifi_lobby_map_0225C930(v6) == 1) {
                    wifi_lobby_map_0226315C(param0, param1, param2, Unk_wifi_lobby_map_0226DBB8, v6);
                    wifi_lobby_map_0225CDEC(v8, v3, 0);
                    wifi_lobby_map_0225DF3C(param1, v6);
                    wifi_lobby_map_0225E43C(param1, 1);
                    return 0;
                }

                if (wifi_lobby_map_0225E45C(param1) == 1) {
                    wifi_lobby_map_0225CDEC(v8, v3, 0);
                    wifi_lobby_map_02262EC0(v12, param2, &Unk_wifi_lobby_map_0226DA18, NULL);
                    wifi_lobby_map_0225E43C(param1, 1);
                    return 0;
                }

                if (WiFiPlazaLobby_State_IsChatRequested(v11)) {
                    wifi_lobby_map_02262EC0(v12, param2, &Unk_wifi_lobby_map_0226DA08, NULL);
                    wifi_lobby_map_0225CDEC(v8, v3, 0);
                    wifi_lobby_map_0225E43C(param1, 1);
                    return 0;
                }

                if (gSystem.pressedKeys & PAD_BUTTON_A) {
                    {
                        WiFiLobbyMapActor *v17;
                        u32 v18;
                        BOOL v19;
                        u32 v20;

                        v17 = wifi_lobby_map_0225CE40(v8, v3);

                        if (v17) {
                            v18 = wifi_lobby_map_0225CD60(v17, 5);
                            v20 = wifi_lobby_map_0225CD60(v17, 4);

                            if (v20 != 0xfe) {
                                v19 = wifi_lobby_map_0225DF64(param1, v20);

                                if ((v18 == 0) && (v19 == 0)) {
                                    wifi_lobby_map_02262EC0(v12, param2, &Unk_wifi_lobby_map_0226D9F8, NULL);
                                    wifi_lobby_map_0225CDEC(v8, v3, 0);
                                    wifi_lobby_map_0225CDEC(v8, v17, 0);
                                    wifi_lobby_map_0225E43C(param1, 1);
                                    return 0;
                                }
                            }
                        }
                    }

                    if (wifi_lobby_map_0225C990(v7) == 1) {
                        u32 v21;

                        v21 = wifi_lobby_map_0225CD60(v3, 6);

                        if (v21 == 0) {
                            wifi_lobby_map_02262484(v9, (v5.x) / 16, (v5.y) / 16);
                            wifi_lobby_map_0225DF3C(param1, v7);
                            wifi_lobby_map_0225E43C(param1, 1);

                            return 0;
                        }
                    }

                    if (wifi_lobby_map_0225C970(v7) == 1) {
                        wifi_lobby_map_0226315C(param0, param1, param2, Unk_wifi_lobby_map_0226DB28, v7);
                        wifi_lobby_map_0225CDEC(v8, v3, 0);
                        wifi_lobby_map_0225DF3C(param1, v7);
                        wifi_lobby_map_0225E43C(param1, 1);

                        return 0;
                    }
                }

                if (wifi_lobby_map_02263120(v2) == 1) {
                    if (v2 == 0) {
                        if (wifi_lobby_map_0225C950(v7) == 1) {
                            wifi_lobby_map_0226315C(param0, param1, param2, Unk_wifi_lobby_map_0226DAF8, v7);
                            wifi_lobby_map_0225CDEC(v8, v3, 0);
                            wifi_lobby_map_0225DF3C(param1, v7);
                            wifi_lobby_map_0225E43C(param1, 1);

                            return 0;
                        }
                    }

                    {
                        WiFiLobbyMapActor *v22;
                        u32 v23;
                        u32 v24;

                        v22 = wifi_lobby_map_0225CE40(v8, v3);

                        if (v22) {
                            v23 = wifi_lobby_map_0225CD60(v22, 4);

                            if (v23 != 0xfe) {
                                if (wifi_lobby_map_0225E3F0(param1) == 0) {
                                    if (wifi_lobby_map_0225DF84(param1, v23) == 0) {
                                        wifi_lobby_map_0225E328(param1, v23, 1);
                                        v0->unk_00 = wifi_lobby_map_0225CE3C(v22);
                                        wifi_lobby_map_0225CDEC(v8, v22, 0);

                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                }

                if (gSystem.pressedKeys & PAD_BUTTON_X) {
                    if (wifi_lobby_map_0225E3F0(param1) == 0) {
                        wifi_lobby_map_0225E328(param1, WiFiPlazaLobby_State_GetMySlotIndex(v11), 0);
                        Sound_PlayEffect(SE_CONFIRM_sseq_3);
                    } else {
                        u32 v25;

                        v25 = wifi_lobby_map_0225E3E0(param1);

                        if (v25 == param2) {
                            wifi_lobby_map_0225E3D0(param1);
                            Sound_PlayEffect(SE_CONFIRM_sseq_3);
                        }
                    }

                    return 0;
                }
            }
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_0226412C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    u32 v0;
    WiFiLobbyMapActorManager *v2 = wifi_lobby_map_0225DEF0(param1);
    WiFiLobbyMapActor *v1 = wifi_lobby_map_0225CCAC(v2);
    v0 = wifi_lobby_map_0225CD60(v1, 5);

    if (v0 != 0) {
        wifi_lobby_map_0225E43C(param1, 1);
    }

    return 0;
}

static BOOL wifi_lobby_map_02264150(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:

    {
        WiFiLobbyMapActorManager *v0;
        WiFiLobbyMapActor *v1;

        v0 = wifi_lobby_map_0225DEF0(param1);
        v1 = wifi_lobby_map_0225CCAC(v0);
        wifi_lobby_map_0225CDEC(v0, v1, 0);
    }

        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 11);
        Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);

        {
            String *v2;

            v2 = wifi_lobby_map_0225E20C(param1, 1, 65);

            wifi_lobby_map_0225DF8C(param1, v2);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 1:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 2: {
        String *v3;

        v3 = wifi_lobby_map_0225E20C(param1, 2, 25);

        wifi_lobby_map_0225DF8C(param1, v3);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 3:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 4:
        wifi_lobby_map_0225E194(param1);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 5: {
        u32 v4;
        BOOL v5 = 0;

        v4 = wifi_lobby_map_0225E1C4(param1);

        switch (v4) {
        case 0:
            wifi_lobby_map_02262E88(param0, 6);
            v5 = 1;
            break;
        case 1:
            wifi_lobby_map_02262E88(param0, 8);
            v5 = 1;
            break;
        default:
        case 2:
            break;
        }

        if (v5 == 1) {
            wifi_lobby_map_0225E1F8(param1);
            wifi_lobby_map_0225DFEC(param1);
        }
    } break;
    case 6:
        wifi_lobby_map_0225DF18(param1, 0);

        {
            WiFiLobbyMapCamera *v6;
            WiFiLobbyMapActorManager *v7;
            WiFiLobbyMapActor *v8;

            v7 = wifi_lobby_map_0225DEF0(param1);
            v8 = wifi_lobby_map_0225CCAC(v7);
            v6 = wifi_lobby_map_0225DF08(param1);

            wifi_lobby_map_02260B3C(v6);
            wifi_lobby_map_0225CDEC(v7, v8, 3);
        }

        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 7: {
        WiFiLobbyMapActorManager *v9;
        WiFiLobbyMapActor *v10;

        v9 = wifi_lobby_map_0225DEF0(param1);
        v10 = wifi_lobby_map_0225CCAC(v9);

        if (wifi_lobby_map_0225CE38(v10) == 1) {
            wifi_lobby_map_0225DF34(param1, 1);
            wifi_lobby_map_0225DF38(param1, 0);
            WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 11);

            return 1;
        }
    } break;
    case 8: {
        WiFiLobbyMapActorManager *v11;
        WiFiLobbyMapActor *v12;

        v11 = wifi_lobby_map_0225DEF0(param1);
        v12 = wifi_lobby_map_0225CCAC(v11);

        wifi_lobby_map_0225CDAC(v11, v12, 2, 0);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 9:

    {
        WiFiLobbyMapActorManager *v13;
        WiFiLobbyMapActor *v14;
        WiFiLobbyMapTaskManager *v15;
        u32 v16;

        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 1);

        v13 = wifi_lobby_map_0225DEF0(param1);
        v15 = wifi_lobby_map_0225DF10(param1);
        v14 = wifi_lobby_map_0225CCAC(v13);
        v16 = wifi_lobby_map_0225CD60(v14, 5);

        if (v16 == 0) {
            wifi_lobby_map_0225CDEC(v13, v14, 1);
            wifi_lobby_map_02262E94(v15, param2, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
    } break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02264324(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActorManager *v0;
    WiFiLobbyMapActor *v1;
    WiFiPlazaLobbyState *v2;
    u32 v3;
    WiFiLobbyMapJoinTaskState *v4;

    v0 = wifi_lobby_map_0225DEF0(param1);
    v1 = wifi_lobby_map_0225CC70(v0, param2);
    v3 = wifi_lobby_map_0225DF40(param1);
    v4 = wifi_lobby_map_02262E80(param0);
    v2 = wifi_lobby_map_0225DEE8(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v4 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapJoinTaskState));

        {
            u8 v5;
            v5 = wifi_lobby_map_02264B64(v3);

            switch (v5) {
            case WiFiPlazaLobbyNetworkSubChannelKind_00:
                v4->activity = WiFiPlazaLobbyActivity_03;
                break;
            case WiFiPlazaLobbyNetworkSubChannelKind_01:
                v4->activity = WiFiPlazaLobbyActivity_04;
                break;
            case WiFiPlazaLobbyNetworkSubChannelKind_02:
                v4->activity = WiFiPlazaLobbyActivity_05;
                break;
            case WiFiPlazaLobbyNetworkSubChannelKind_03:
                v4->activity = WiFiPlazaLobbyActivity_06;
                break;
            default:
                GF_ASSERT(FALSE);
                v4->activity = WiFiPlazaLobbyActivity_05;
                break;
            }
        }

        if (WiFiPlazaLobby_State_IsLobbyClosed(v2) == 1) {
            v4->messageID = 22;
            v4->flag = 0;
            wifi_lobby_map_02262E88(param0, 5);
            break;
        }

        if (WiFiPlazaLobby_State_CheckNetworkEvent(v2) == 1) {
            v4->messageID = 72;
            v4->flag = 1;
            wifi_lobby_map_02262E88(param0, 5);
            break;
        }

        {
            BOOL v6;
            u8 v7;

            v7 = wifi_lobby_map_02264B64(v3);

            if (WiFiPlazaLobby_Network_HasSubChannelSpace(v7) == 0) {
                v4->messageID = 20;
                v4->flag = 0;
                wifi_lobby_map_02262E88(param0, 3);
                break;
            }

            v6 = WiFiPlazaLobby_Network_JoinSubChannel(v7);
            GF_ASSERT(v6);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 1: {
        WiFiPlazaLobbyNetworkSubChannelJoinState v8;

        v8 = WiFiPlazaLobby_Network_GetSubChannelJoinState();

        if (v8 == WiFiPlazaLobbyNetworkSubChannelJoinState_01) {
            wifi_lobby_map_02262E88(param0, 2);

            {
                u8 v9;
                u8 v10;
                int v11;
                u8 v12[4] = { 0 };
                u32 v13;
                u8 v14;
                WiFiPlazaLobbyState *v15;

                v15 = wifi_lobby_map_0225DEE8(param1);
                v9 = WiFiPlazaLobby_State_GetSecondaryMemberCount(v15);

                if ((v4->activity == WiFiPlazaLobbyActivity_05) || (v4->activity == WiFiPlazaLobbyActivity_06)) {
                    v14 = 0;

                    for (v11 = 0; v11 < 4; v11++) {
                        v13 = WiFiPlazaLobby_State_GetSecondaryMemberSlot(v15, v11);

                        if (v13 != 0xffffffff) {
                            if (v14 < 4) {
                                v12[v14] = v13;
                            }

                            v14++;
                        }
                    }
                } else {
                    v12[0] = param2;
                }

                WiFiPlazaLobby_State_SendMinigameProfileViewMessage(v15, v4->activity, v9, v12[0], v12[1], v12[2], v12[3], 0);
            }
        } else if (v8 == WiFiPlazaLobbyNetworkSubChannelJoinState_02) {
            v4->messageID = 20;
            v4->flag = 0;
            wifi_lobby_map_02262E88(param0, 3);
        }
    } break;
    case 2: {
        u32 v16;
        u32 v17;
        u32 v18;

        v16 = wifi_lobby_map_02264BCC(v3);
        v17 = wifi_lobby_map_02264C34(v3);

        wifi_lobby_map_0225DF34(param1, 1);
        wifi_lobby_map_0225DF38(param1, v16);

        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), v17);
        WiFiPlazaLobby_State_RecordMinigameJournal(v2, v4->activity);

        switch (v4->activity) {
        case WiFiPlazaLobbyActivity_03:
        case WiFiPlazaLobbyActivity_04:
            v18 = 5;
            break;
        case WiFiPlazaLobbyActivity_05:
            v18 = 3;
            break;
        case WiFiPlazaLobbyActivity_06:
            v18 = 4;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }

        WiFiPlazaLobby_State_MarkActivityDone(v2, v18);

        {
            WiFi2DCharPosition v19;
            WiFiLobbyMapArgs *v20;
            int v21;

            v21 = wifi_lobby_map_0225CD60(v1, 6);
            v21 = WiFi2DChar_DirectionOpposite(v21);
            v20 = wifi_lobby_map_0225DEEC(param1);
            v19 = wifi_lobby_map_0225CD34(v1);

            v20->taskType = 1;
            v20->spawnX = (v19.x) / 16;
            v20->spawnY = (v19.y) / 16;
            v20->direction = v21;
            v20->venue = v4->activity;
        }

        wifi_lobby_map_02262E64(param0);

        return 1;
    } break;
    case 3: {
        u8 v22;
        u8 v23;

        v23 = wifi_lobby_map_0225CD60(v1, 6);

        switch (v23) {
        case 0:
            v22 = 6;
            break;
        case 1:
            v22 = 5;
            break;
        case 2:
            v22 = 8;
            break;
        case 3:
            v22 = 7;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }

        wifi_lobby_map_0225CDEC(v0, v1, v22);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 4: {
        BOOL v24;

        v24 = wifi_lobby_map_0225CE38(v1);

        if (v24 == 1) {
            v4->nextState = 8;
            wifi_lobby_map_02262E88(param0, 7);
        }
    } break;
    case 5: {
        u8 v25;

        v25 = wifi_lobby_map_0225CD60(v1, 6);
        v25 = WiFi2DChar_DirectionOpposite(v25);

        wifi_lobby_map_0225CDAC(v0, v1, 2, v25);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 6: {
        u32 v26;

        v26 = wifi_lobby_map_0225CD60(v1, 5);

        if (v26 == 0) {
            v4->nextState = 8;
            wifi_lobby_map_02262E88(param0, 7);
        }
    } break;
    case 7:
        v4->nextState--;

        if (v4->nextState <= 0) {
            String *v27;

            wifi_lobby_map_0225E27C(param1, v4->activity, 0);
            v27 = wifi_lobby_map_0225E20C(param1, v4->flag, v4->messageID);
            wifi_lobby_map_0225DF8C(param1, v27);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 8: {
        BOOL v28;

        v28 = wifi_lobby_map_0225DFAC(param1);

        if (v28) {
            wifi_lobby_map_02262E64(param0);
            wifi_lobby_map_0225CDEC(v0, v1, 1);
            wifi_lobby_map_0225DFEC(param1);

            {
                WiFiLobbyMapTaskManager *v29;

                v29 = wifi_lobby_map_0225DF10(param1);
                wifi_lobby_map_02262E94(v29, param2, &Unk_wifi_lobby_map_0226D9D0, NULL);
            }
        }
    } break;
    }

    return 0;
}

static BOOL wifi_lobby_map_022646C8(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapRecruitTaskState *v0;
    WiFiLobbyMapTaskManager *v1;
    WiFiLobbyMapActorManager *v2;
    WiFiLobbyMapActor *v3;
    WiFiPlazaLobbyState *v4;

    v0 = wifi_lobby_map_02262E80(param0);
    v1 = wifi_lobby_map_0225DF10(param1);
    v2 = wifi_lobby_map_0225DEF0(param1);
    v3 = wifi_lobby_map_0225CCAC(v2);
    v4 = wifi_lobby_map_0225DEE8(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapRecruitTaskState));

        wifi_lobby_map_0225CDEC(v2, v3, 0);
        wifi_lobby_map_02262E8C(param0);

        v0->substate.state = 0;
        {
            u32 v5;

            v5 = wifi_lobby_map_0225DF40(param1);

            switch (v5) {
            case 30:
                v0->substate.network = WiFiPlazaLobbyNetworkGameKind_00;
                v0->substate.activity = WiFiPlazaLobbyActivity_00;
                v0->substate.venue = 2;
                break;
            case 31:
                v0->substate.network = WiFiPlazaLobbyNetworkGameKind_01;
                v0->substate.activity = WiFiPlazaLobbyActivity_01;
                v0->substate.venue = 3;
                break;
            case 32:
                v0->substate.network = WiFiPlazaLobbyNetworkGameKind_02;
                v0->substate.activity = WiFiPlazaLobbyActivity_02;
                v0->substate.venue = 4;
                break;
            default:
                GF_ASSERT(FALSE);
                break;
            }

            WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 12);
        }

        wifi_lobby_map_02262EC0(v1, param2, &Unk_wifi_lobby_map_0226DA20, &v0->substate);
        break;
    case 1:
        if (v0->substate.state == 8) {
            wifi_lobby_map_02262E88(param0, 2);
        } else {
            wifi_lobby_map_02262E88(param0, 3);
        }
        break;
    case 2: {
        u32 v6;
        u32 v7;
        u32 v8;
        u32 v9;

        v8 = wifi_lobby_map_0225DF40(param1);

        switch (v8) {
        case 30:
            v6 = 3;
            v9 = 0;
            break;
        case 31:
            v6 = 4;
            v9 = 1;
            break;
        case 32:
            v6 = 5;
            v9 = 2;
            break;
        }

        wifi_lobby_map_0225DF34(param1, 1);
        wifi_lobby_map_0225DF38(param1, v6);

        WiFiPlazaLobby_State_RecordMinigameJournal(v4, v0->substate.activity);
        WiFiPlazaLobby_State_IncrementMinigameRecord(v4);
        WiFiPlazaLobby_State_MarkActivityDone(v4, v9);

        {
            WiFi2DCharPosition v10;
            WiFiLobbyMapArgs *v11;
            int v12;

            v12 = wifi_lobby_map_0225CD60(v3, 6);
            v12 = WiFi2DChar_DirectionOpposite(v12);
            v11 = wifi_lobby_map_0225DEEC(param1);
            v10 = wifi_lobby_map_0225CD34(v3);

            v11->taskType = 2;
            v11->spawnX = (v10.x) / 16;
            v11->spawnY = (v10.y) / 16;
            v11->direction = v12;
            v11->venue = v0->substate.activity;
        }

        WiFiPlazaLobby_State_SetBGMSuppressed(wifi_lobby_map_0225DEE8(param1), 1);
        wifi_lobby_map_02262E64(param0);

        return 1;
    } break;
    case 3: {
        WiFi2DCharPosition v13;
        int v14;

        v14 = wifi_lobby_map_0225CD60(v3, 6);
        v14 = WiFi2DChar_DirectionOpposite(v14);

        wifi_lobby_map_0225CDAC(v2, v3, 2, v14);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 4: {
        u32 v15;

        v15 = wifi_lobby_map_0225CD60(v3, 5);

        if (v15 == 0) {
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 5: {
        String *v16;
        u32 v17;
        BOOL v18 = 1;

        switch (v0->substate.state) {
        case 0:
            wifi_lobby_map_0225E27C(param1, v0->substate.activity, 0);
            v17 = 4;
            break;
        case 1:
            v17 = 5;
            break;
        case 2:
            wifi_lobby_map_0225E27C(param1, v0->substate.activity, 0);
            v17 = 6;
            break;
        case 3:
            v17 = 19;
            break;
        case 4:
            v17 = 17;
            break;
        case 6:
            v17 = 29;
            break;
        case 7:
            v17 = 7;
            break;
        default:
        case 5:
            v18 = 0;
            break;
        }

        if (v18) {
            v16 = wifi_lobby_map_0225E20C(param1, 0, v17);
            wifi_lobby_map_0225DF8C(param1, v16);
            wifi_lobby_map_02262E8C(param0);
        } else {
            wifi_lobby_map_02262E88(param0, 7);
        }
    } break;
    case 6:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_0225DFEC(param1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 7:
        wifi_lobby_map_02262E64(param0);
        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 1);
        wifi_lobby_map_0225CDEC(v2, v3, 1);

        {
            WiFiLobbyMapTaskManager *v19;

            v19 = wifi_lobby_map_0225DF10(param1);
            wifi_lobby_map_02262E94(v19, param2, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02264974(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapVenueTaskState *v0;
    WiFiLobbyMapTaskManager *v1;
    WiFiLobbyMapActorManager *v2;
    WiFiLobbyMapActor *v3;
    WiFiPlazaLobbyState *v4;
    String *v5;

    v0 = wifi_lobby_map_02262E80(param0);
    v1 = wifi_lobby_map_0225DF10(param1);
    v2 = wifi_lobby_map_0225DEF0(param1);
    v3 = wifi_lobby_map_0225CCAC(v2);
    v4 = wifi_lobby_map_0225DEE8(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapJoinTaskState));
        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 13);

        if (WiFiPlazaLobby_State_IsLobbyClosed(v4) == 1) {
            v0->unk_00 = 122;
            wifi_lobby_map_02262E88(param0, 2);
            break;
        }

        if (WiFiPlazaLobby_State_IsNeonTransitionComplete(v4) == 1) {
            v0->unk_02 = 10;
        } else {
            if (WiFiPlazaLobby_State_IsQuestionAnswered(v4) == 1) {
                v0->unk_00 = 98;
                wifi_lobby_map_02262E88(param0, 2);
                break;
            } else {
                v0->unk_02 = 9;
            }
        }

        wifi_lobby_map_02262E88(param0, 1);
        break;
    case 1: {
        u32 v6;
        u32 v7;

        if (v0->unk_02 == 9) {
            v6 = 9;
        } else {
            v6 = 10;

            WiFiPlazaLobby_State_MarkQuestionAcknowledged(v4);
        }

        wifi_lobby_map_0225DF34(param1, 1);
        wifi_lobby_map_0225DF38(param1, v6);
        WiFiPlazaLobby_State_SetAttendee(v4, 23, DWC_LOBBY_INVALID_USER_ID);

        {
            WiFi2DCharPosition v8;
            WiFiLobbyMapArgs *v9;
            int v10;

            v10 = wifi_lobby_map_0225CD60(v3, 6);
            v10 = WiFi2DChar_DirectionOpposite(v10);
            v9 = wifi_lobby_map_0225DEEC(param1);
            v8 = wifi_lobby_map_0225CD34(v3);

            v9->taskType = 3;
            v9->spawnX = (v8.x) / 16;
            v9->spawnY = (v8.y) / 16;
            v9->direction = v10;
            v9->venue = 0;
        }

        wifi_lobby_map_02262E64(param0);

        return 1;
    } break;
    case 2: {
        WiFi2DCharPosition v11;
        int v12;

        v12 = wifi_lobby_map_0225CD60(v3, 6);
        v12 = WiFi2DChar_DirectionOpposite(v12);

        wifi_lobby_map_0225CDAC(v2, v3, 2, v12);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 3: {
        u32 v13;

        v13 = wifi_lobby_map_0225CD60(v3, 5);

        if (v13 == 0) {
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 4:
        v5 = wifi_lobby_map_0225E20C(param1, 1, v0->unk_00);
        wifi_lobby_map_0225DF8C(param1, v5);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 5:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_0225DFEC(param1);
            wifi_lobby_map_02262E8C(param0);
        }
        break;
    case 6:
        wifi_lobby_map_02262E64(param0);
        WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 1);
        wifi_lobby_map_0225CDEC(v2, v3, 1);

        {
            WiFiLobbyMapTaskManager *v14;

            v14 = wifi_lobby_map_0225DF10(param1);
            wifi_lobby_map_02262E94(v14, param2, &Unk_wifi_lobby_map_0226D9D0, NULL);
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static u32 wifi_lobby_map_02264B64(u32 param0)
{
    u32 v0;

    switch (param0) {
    case 22:
    case 23:
    case 24:
    case 25:
        v0 = WiFiPlazaLobbyNetworkSubChannelKind_02;
        break;
    case 26:
    case 27:
    case 28:
    case 29:
        v0 = WiFiPlazaLobbyNetworkSubChannelKind_03;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        v0 = WiFiPlazaLobbyNetworkSubChannelKind_00;
        break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        v0 = WiFiPlazaLobbyNetworkSubChannelKind_01;
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

static u32 wifi_lobby_map_02264BCC(u32 param0)
{
    u32 v0;

    switch (param0) {
    case 22:
    case 23:
    case 24:
    case 25:
        v0 = 1;
        break;
    case 26:
    case 27:
    case 28:
    case 29:
        v0 = 2;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        v0 = 6;
        break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        v0 = 7;
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

static u32 wifi_lobby_map_02264C34(u32 param0)
{
    u32 v0;

    switch (param0) {
    case 22:
    case 23:
    case 24:
    case 25:
        v0 = 7;
        break;
    case 26:
    case 27:
    case 28:
    case 29:
        v0 = 8;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        v0 = 5;
        break;
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
        v0 = 6;
        break;
    default:
        GF_ASSERT(FALSE);
        v0 = 0;
        break;
    }

    return v0;
}

static BOOL wifi_lobby_map_02264C9C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    switch (wifi_lobby_map_02262E84(param0)) {
    case 0: {
        String *v0;
        WiFiPlazaLobbyState *v1;

        v1 = wifi_lobby_map_0225DEE8(param1);

        if (WiFiPlazaLobby_State_IsLobbyClosed(v1) == 1) {
            v0 = wifi_lobby_map_0225E20C(param1, 1, 3);
        } else {
            if (WiFiPlazaLobby_State_IsParadeFinished(v1) == 1) {
                v0 = wifi_lobby_map_0225E20C(param1, 1, 78);
            } else {
                v0 = wifi_lobby_map_0225E20C(param1, 1, 2);
            }
        }

        wifi_lobby_map_0225DF8C(param1, v0);
        Sound_PlayEffect(SE_CONFIRM_sseq_3);
        wifi_lobby_map_02262E8C(param0);
    } break;
    case 1:
        if (wifi_lobby_map_0225DFAC(param1)) {
            wifi_lobby_map_0225DFEC(param1);
            {
                WiFiLobbyMapActorManager *v2;
                WiFiLobbyMapActor *v3;

                v2 = wifi_lobby_map_0225DEF0(param1);
                v3 = wifi_lobby_map_0225CCAC(v2);

                wifi_lobby_map_0225CDEC(v2, v3, 1);
            }
            return 1;
        }

        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02264D38(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapCameraFollowTaskState *v0;
    WiFiLobbyMapObjectManager *v1;
    WiFiLobbyMapActorManager *v2;
    WiFiLobbyMapCamera *v3;
    WiFiPlazaLobbyState *v4;
    BOOL v5;
    String *v6;

    v2 = wifi_lobby_map_0225DEF0(param1);
    v1 = wifi_lobby_map_0225DEF8(param1);
    v3 = wifi_lobby_map_0225DF08(param1);
    v4 = wifi_lobby_map_0225DEE8(param1);
    v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0: {
        u32 v7;

        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapCameraFollowTaskState));
        v0->actor = wifi_lobby_map_0225CC70(v2, param2);

        v7 = wifi_lobby_map_0225DF40(param1);

        switch (v7) {
        case 33:
            v0->unk_06 = 2;
            break;
        case 34:
            v0->unk_06 = 1;
            break;
        case 35:
            v0->unk_06 = 0;
            break;
        default:
            GF_ASSERT(FALSE);
            break;
        }
    }
        wifi_lobby_map_02262E88(param0, 1);
        break;
    case 1:
        if (WiFiPlazaLobby_State_IsParadeFinished(v4) == 0) {
            v0->unk_04 = 8;
            wifi_lobby_map_02262E88(param0, 6);
        } else {
            if (WiFiPlazaLobby_State_IsLobbyClosed(v4) == 1) {
                v0->unk_04 = 10;
                wifi_lobby_map_02262E88(param0, 6);
            } else {
                v0->floatSlot = WiFiPlazaLobby_State_AllocateFloatSlot(v4, param2, v0->unk_06);

                if (v0->floatSlot != 0xffffffff) {
                    wifi_lobby_map_02262E88(param0, 2);
                    v6 = wifi_lobby_map_0225E20C(param1, 0, 31);
                    wifi_lobby_map_0225DF9C(param1, v6);
                    wifi_lobby_map_0225DFBC(param1);
                } else {
                    v0->unk_04 = 9;
                    wifi_lobby_map_02262E88(param0, 6);
                }
            }
        }
        break;
    case 2:
        if ((gSystem.pressedKeys & PAD_BUTTON_B) || (gSystem.pressedKeys & PAD_KEY_DOWN)) {
            WiFiPlazaLobby_State_FreeFloatSlot(v4, param2);
            wifi_lobby_map_0225DFCC(param1);
            v0->unk_0A = 6;
            v0->unk_04 = 15;
            wifi_lobby_map_02262E88(param0, 12);
        } else {
            if (wifi_lobby_map_02265104(v0, v1) == 1) {
                wifi_lobby_map_0225DFCC(param1);
                WiFiPlazaLobby_State_SendFloatJoinEvent(v4);

                v0->timer = 0;

                WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 10);
                wifi_lobby_map_0225DF44(param1);
                wifi_lobby_map_02260B3C(v3);
                wifi_lobby_map_0225D030(v0->actor, 0);
                wifi_lobby_map_0225D06C(v0->actor, 1);
                Sound_PlayEffect(SEQ_SE_PL_DANSA5_sseq);
                wifi_lobby_map_0225E410(param1);

                v0->unk_0A = 3;

                wifi_lobby_map_02262E88(param0, 12);
                WiFiPlazaLobby_State_RecordParadeJournal(v4);
            }
        }
        break;
    case 3:
        v5 = wifi_lobby_map_02265144(v0, v1, v3);

        if (v5 == 1) {
            wifi_lobby_map_0225D06C(v0->actor, 0);
            wifi_lobby_map_0225D060(v0->actor, 2);
            wifi_lobby_map_0225D0B4(v0->actor, 1 << 3);
            wifi_lobby_map_02262E88(param0, 4);

            v0->timer = 0;
        }
        break;
    case 4:
        wifi_lobby_map_02265344(v0, v1, param1);
        wifi_lobby_map_022650E4(v0, v3);

        v5 = wifi_lobby_map_022652BC(v0, v1);

        if (v5 == 1) {
            wifi_lobby_map_02262E88(param0, 5);
            wifi_lobby_map_0225E43C(param1, 0);
        }
        break;
    case 5: {
        VecFx32 v8;

        wifi_lobby_map_02265344(v0, v1, param1);
        wifi_lobby_map_022650E4(v0, v3);
        wifi_lobby_map_0225D054(v0->actor, &v8);
        wifi_lobby_map_02265370(v0, v1, param1);

        if (v8.x < (FX32_CONST(96))) {
            v0->frame = 0;
            wifi_lobby_map_02262E88(param0, 13);
        }
    } break;
    case 6:
        wifi_lobby_map_0225CDAC(v2, v0->actor, 2, 1);
        wifi_lobby_map_02262E88(param0, 7);
        break;
    case 7:
        if (wifi_lobby_map_0225CD60(v0->actor, 5) == 0) {
            wifi_lobby_map_02262E88(param0, v0->unk_04);
        }
        break;
    case 8:
        v6 = wifi_lobby_map_0225E20C(param1, 0, 30);
        wifi_lobby_map_0225DF8C(param1, v6);
        v0->unk_04 = 15;
        wifi_lobby_map_02262E88(param0, 11);
        break;
    case 9:
        v6 = wifi_lobby_map_0225E20C(param1, 0, 32);
        wifi_lobby_map_0225DF8C(param1, v6);
        v0->unk_04 = 15;
        wifi_lobby_map_02262E88(param0, 11);
        break;
    case 10:
        v6 = wifi_lobby_map_0225E20C(param1, 0, 33);
        wifi_lobby_map_0225DF8C(param1, v6);
        v0->unk_04 = 15;
        wifi_lobby_map_02262E88(param0, 11);
        break;
    case 11:
        if (wifi_lobby_map_0225DFAC(param1) == 1) {
            wifi_lobby_map_02262E88(param0, v0->unk_04);
        }
        break;
    case 12:
        wifi_lobby_map_0225DFEC(param1);
        wifi_lobby_map_02262E88(param0, v0->unk_0A);
        break;
    case 13:
        wifi_lobby_map_02265344(v0, v1, param1);
        wifi_lobby_map_02265370(v0, v1, param1);
        v0->frame++;

        if (v0->frame > 120) {
            wifi_lobby_map_0225DF34(param1, 1);
            wifi_lobby_map_0225DF38(param1, 0);
            wifi_lobby_map_0225DFEC(param1);
            WiFiPlazaLobby_State_SetCurrentVenue(wifi_lobby_map_0225DEE8(param1), 11);
            wifi_lobby_map_02262E88(param0, 14);
        }
        break;
    case 14:
        wifi_lobby_map_02265344(v0, v1, param1);
        wifi_lobby_map_02265370(v0, v1, param1);
        break;
    case 15: {
        WiFiLobbyMapTaskManager *v9;

        v9 = wifi_lobby_map_0225DF10(param1);

        wifi_lobby_map_0225DFEC(param1);
        wifi_lobby_map_0225CDEC(v2, v0->actor, 1);
        wifi_lobby_map_02262E64(param0);
        wifi_lobby_map_02262E94(v9, param2, &Unk_wifi_lobby_map_0226D9D0, NULL);
    } break;
    }

    return 0;
}

static void wifi_lobby_map_022650E4(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapCamera *param1)
{
    VecFx32 v0;

    wifi_lobby_map_0225D054(param0->actor, &v0);
    wifi_lobby_map_02260B18(param1, v0.x, v0.y, v0.z);
}

static BOOL wifi_lobby_map_02265104(const WiFiLobbyMapCameraFollowTaskState *param0, const WiFiLobbyMapObjectManager *param1)
{
    VecFx32 v0;
    VecFx32 v1;
    u32 v2, v3;

    WiFiPlazaLobby_State_FloatSlotToRowCol(param0->floatSlot, &v2, &v3);
    wifi_lobby_map_02262318(param1, v2, v3, &v1);
    wifi_lobby_map_0225D054(param0->actor, &v0);

    if ((v0.x + (FX32_CONST(16))) >= v1.x) {
        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_02265144(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapCamera *param2)
{
    VecFx32 v0;
    VecFx32 v1;
    u32 v2, v3;
    WiFi2DCharPosition v4;
    VecFx32 v5;
    u16 v6;
    BOOL v7;

    param0->timer++;

    if (param0->timer < 24) {
        v7 = 0;
    } else {
        param0->timer = 24;
        v7 = 1;
    }

    WiFiPlazaLobby_State_FloatSlotToRowCol(param0->floatSlot, &v2, &v3);
    wifi_lobby_map_02262318(param1, v2, v3, &v1);

    v4 = wifi_lobby_map_0225CD34(param0->actor);
    wifi_lobby_map_0225C700(&v4, &v0);

    v5.x = 0;
    v5.y = FX_Div(FX_Mul(FX32_CONST(param0->timer), (v1.y - v0.y)), FX32_CONST(24));

    if (param0->timer >= 4) {
        v5.z = FX_Div(FX_Mul(FX32_CONST(param0->timer - 4), (v1.z - v0.z)), FX32_CONST(20));
    } else {
        v5.z = 0;
    }

    VEC_Add(&v5, &v0, &v5);
    wifi_lobby_map_02260B18(param2, v5.x, v5.y, v5.z);

    v6 = (param0->timer * 0x7fff) / 24;
    v5.y += FX_Mul(FX_SinIdx(v6), (FX32_CONST(16)));

    wifi_lobby_map_0225D048(param0->actor, &v5);

    return v7;
}

static BOOL wifi_lobby_map_022652BC(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1)
{
    s32 v0;
    BOOL v1;
    u16 v2;
    fx32 v3;
    VecFx32 v4;

    param0->timer++;

    if (param0->timer < 16) {
        v1 = 0;
    } else {
        param0->timer = 16;
        v1 = 1;
    }

    v0 = param0->timer % 8;
    v2 = (v0 * 0x7fff) / 8;
    v3 = FX_Mul(FX_SinIdx(v2), (FX32_CONST(3)));

    wifi_lobby_map_0225D054(param0->actor, &v4);
    v4.y += v3;
    wifi_lobby_map_0225D048(param0->actor, &v4);

    return v1;
}

static void wifi_lobby_map_02265344(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapApp *param2)
{
    VecFx32 v0;
    u32 v1;
    u32 v2;

    WiFiPlazaLobby_State_FloatSlotToRowCol(param0->floatSlot, &v2, &v1);
    wifi_lobby_map_02262318(param1, v2, v1, &v0);
    wifi_lobby_map_0225D048(param0->actor, &v0);
}

static void wifi_lobby_map_02265370(WiFiLobbyMapCameraFollowTaskState *param0, WiFiLobbyMapObjectManager *param1, WiFiLobbyMapApp *param2)
{
    VecFx32 v0;
    fx32 v1;
    u32 v2, v3;

    WiFiPlazaLobby_State_FloatSlotToRowCol(param0->floatSlot, &v2, &v3);

    if (wifi_lobby_map_0225E420(param2, v2) == 1) {
        if (wifi_lobby_map_02263334(&param0->cameraAnim) == 0) {
            wifi_lobby_map_02263270(&param0->cameraAnim);
        }
    } else {
        if (wifi_lobby_map_02263334(&param0->cameraAnim) == 1) {
            wifi_lobby_map_0226332C(&param0->cameraAnim);
        }
    }

    v1 = wifi_lobby_map_02263290(&param0->cameraAnim);

    wifi_lobby_map_0225D054(param0->actor, &v0);
    v0.y += v1;
    wifi_lobby_map_0225D048(param0->actor, &v0);
}

static void wifi_lobby_map_022653DC(WiFiLobbyMapStatusTaskState *param0, WiFiLobbyMapApp *param1)
{
    int v0;
    const String *v1;

    wifi_lobby_map_0225E00C(param1, 18);

    for (v0 = 1; v0 < 18; v0++) {
        wifi_lobby_map_0225E30C(param1, 0, v0);
        v1 = wifi_lobby_map_0225E20C(param1, 1, 6);
        wifi_lobby_map_0225E044(param1, v1, v0);
    }

    v1 = wifi_lobby_map_0225E20C(param1, 1, 7);
    wifi_lobby_map_0225E044(param1, v1, 0);

    param0->listTemplate = Unk_wifi_lobby_map_0226DA98;
    param0->listTemplate.choices = wifi_lobby_map_0225E054(param1);
}

static void wifi_lobby_map_02265450(WiFiLobbyMapStatusTaskState *param0, WiFiLobbyMapApp *param1)
{
    wifi_lobby_map_0225E034(param1);
}

static BOOL wifi_lobby_map_0226545C(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapPlayerJoinTaskState *v0;
    WiFiLobbyMapActor *v1;
    WiFiPlazaLobbyState *v2;
    WiFiLobbyMapActorManager *v3;
    WiFiLobbyMapTaskManager *v4;

    v2 = wifi_lobby_map_0225DEE8(param1);
    v3 = wifi_lobby_map_0225DEF0(param1);
    v1 = wifi_lobby_map_0225CC70(v3, param2);
    v0 = wifi_lobby_map_02262E80(param0);
    v4 = wifi_lobby_map_0225DF10(param1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapPlayerJoinTaskState));
        wifi_lobby_map_02262E88(param0, 1);
    case 1: {
        BOOL v5, v6;

        v5 = WiFiPlazaLobby_State_PopPlayerJoined(v2, param2);
        v6 = WiFiPlazaLobby_State_IsPlayerSlotOccupied(v2, param2);

        if ((v5 == 1) || (v6 == 1)) {
            wifi_lobby_map_02262E88(param0, 2);
        }
    } break;
    case 2: {
        const WiFiPlazaProfile *v7;
        u32 v8;

        v7 = WiFiPlazaLobby_State_GetProfileBySlot(v2, param2);

        if (v7 == NULL) {
            wifi_lobby_map_02262E88(param0, 1);
            break;
        }

        if (WiFiPlazaLobby_State_IsAppearanceRankSet(v7) == 1) {
            v1 = wifi_lobby_map_0225CBB8(v3, param2, WiFiPlazaProfile_GetTrainerAppearanceGraphicsID(v7));

            if (v1) {
                wifi_lobby_map_0225D0C0(v1, 0);

                wifi_lobby_map_02262E88(param0, 3);
            }
        }
    } break;
    case 3: {
        u32 v9;
        const WiFiPlazaProfile *v10;
        BOOL v11;

        v10 = WiFiPlazaLobby_State_GetProfileBySlot(v2, param2);

        if (v10 == NULL) {
            if (v1 != NULL) {
                wifi_lobby_map_0225CC54(v1);
            }

            wifi_lobby_map_02262E88(param0, 1);
            break;
        }

        v9 = WiFiPlazaLobby_State_GetVenueIndex(v10);
        v11 = wifi_lobby_map_02265CCC(&v0->unk_00, v2, param1, v1, v9, 1);

        if (v11) {
            wifi_lobby_map_02262E88(param0, 5);
            wifi_lobby_map_0225CDEC(v3, v1, 0);
            wifi_lobby_map_0225DF6C(param1, param2, 1);
            wifi_lobby_map_0225DF4C(param1, param2, 1);
            wifi_lobby_map_0225D030(v1, 0);
            wifi_lobby_map_02262EC0(v4, param2, &Unk_wifi_lobby_map_0226D9F0, &v0->unk_00);
        } else {
            wifi_lobby_map_0225CDEC(v3, v1, 4);
            wifi_lobby_map_02262E88(param0, 4);
            wifi_lobby_map_0225DF4C(param1, param2, 1);
            wifi_lobby_map_0225DF6C(param1, param2, 1);
            wifi_lobby_map_0225D0C0(v1, 1);
        }
    } break;
    case 4: {
        BOOL v12;

        v12 = wifi_lobby_map_0225CE38(v1);

        if (v12 == 1) {
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 5:
        wifi_lobby_map_02262E64(param0);
        wifi_lobby_map_0225CDEC(v3, v1, 2);
        wifi_lobby_map_02262E94(v4, param2, &Unk_wifi_lobby_map_0226D9D8, NULL);
        wifi_lobby_map_0225DF4C(param1, param2, 0);
        wifi_lobby_map_0225DF6C(param1, param2, 0);
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02265630(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapPlayerJoinTaskState *v0;
    WiFiLobbyMapActor *v1;
    WiFiLobbyMapActor *v2;
    WiFiPlazaLobbyState *v3 = wifi_lobby_map_0225DEE8(param1);
    WiFiLobbyMapActorManager *v4 = wifi_lobby_map_0225DEF0(param1);
    WiFiLobbyMapTaskManager *v5 = wifi_lobby_map_0225DF10(param1);
    v1 = wifi_lobby_map_0225CC70(v4, param2);
    v2 = wifi_lobby_map_0225CCAC(v4);
    v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapPlayerJoinTaskState));
        wifi_lobby_map_02262E88(param0, 1);
    case 1:
        if (WiFiPlazaLobby_State_PopPlayerLeft(v3, param2)) {
            wifi_lobby_map_02262E64(param0);
            wifi_lobby_map_0225CDEC(v4, v1, 0);
            wifi_lobby_map_0225DF6C(param1, param2, 1);
            wifi_lobby_map_0225DF4C(param1, param2, 1);
            wifi_lobby_map_02262E94(v5, param2, &Unk_wifi_lobby_map_0226D9E0, NULL);
            break;
        }

        if (WiFiPlazaLobby_State_PopPlayerUpdated(v3, param2)) {
            (void)0;
        }

        if (WiFiPlazaLobby_State_IsParadeFinished(v3) == 1) {
            u32 v6;

            v6 = WiFiPlazaLobby_State_FindFloatSlotByUserID(v3, param2);

            if (v6 != 0xffffffff) {
                wifi_lobby_map_0225CDEC(v4, v1, 0);
                wifi_lobby_map_0225DF6C(param1, param2, 1);
                wifi_lobby_map_0225DF4C(param1, param2, 1);
                wifi_lobby_map_0225D030(v1, 0);
                wifi_lobby_map_02262E64(param0);
                wifi_lobby_map_02262E94(v5, param2, &Unk_wifi_lobby_map_0226D9E8, &v0->unk_00);
                break;
            }
        }

        {
            u32 v7;
            const WiFiPlazaProfile *v8;
            BOOL v9;

            v8 = WiFiPlazaLobby_State_GetProfileBySlot(v3, param2);
            v7 = WiFiPlazaLobby_State_GetVenueIndex(v8);
            v9 = wifi_lobby_map_02265CCC(&v0->unk_00, v3, param1, v1, v7, 0);

            if (v9) {
                wifi_lobby_map_0225CDEC(v4, v1, 0);
                wifi_lobby_map_0225DF6C(param1, param2, 1);
                wifi_lobby_map_0225DF4C(param1, param2, 1);
                wifi_lobby_map_0225D030(v1, 0);
                wifi_lobby_map_02262EC0(v5, param2, &Unk_wifi_lobby_map_0226D9F0, &v0->unk_00);
                break;
            }

            if (WiFiPlazaLobby_State_IsMemberCosmeticKnown(v3, param2) == 1) {
                wifi_lobby_map_0225CDEC(v4, v1, 0);
                wifi_lobby_map_0225DF4C(param1, param2, 1);
                wifi_lobby_map_02262EC0(v5, param2, &Unk_wifi_lobby_map_0226DA18, NULL);
                break;
            }
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_022657D0(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapActorManager *v1 = wifi_lobby_map_0225DEF0(param1);
    WiFiLobbyMapActor *v0 = wifi_lobby_map_0225CC70(v1, param2);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        wifi_lobby_map_0225CDEC(v1, v0, 3);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 1: {
        BOOL v2;

        v2 = wifi_lobby_map_0225CE38(v0);

        if (v2) {
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 2:
        wifi_lobby_map_0225CC54(v0);

        {
            WiFiLobbyMapTaskManager *v3;

            v3 = wifi_lobby_map_0225DF10(param1);
            wifi_lobby_map_02262E94(v3, param2, &Unk_wifi_lobby_map_0226DA10, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02265840(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapBoardingTaskState *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiLobbyMapObjectManager *v2;
    WiFiPlazaLobbyState *v3 = wifi_lobby_map_0225DEE8(param1);
    v1 = wifi_lobby_map_0225DEF0(param1);
    v2 = wifi_lobby_map_0225DEF8(param1);
    v0 = wifi_lobby_map_02262E80(param0);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0: {
        v0 = wifi_lobby_map_02262E3C(param0, sizeof(WiFiLobbyMapBoardingTaskState));
        v0->actor = wifi_lobby_map_0225CC70(v1, param2);
        v0->unk_04 = WiFiPlazaLobby_State_FindFloatSlotByUserID(v3, param2);

        GF_ASSERT(v0->unk_04 != 0xffffffff);

        WiFiPlazaLobby_State_FloatSlotToRowCol(v0->unk_04, &v0->unk_04, &v0->unk_08);
        wifi_lobby_map_0225CDEC(v1, v0->actor, 3);
        wifi_lobby_map_02262E88(param0, 1);
    } break;

    case 1:
        if (wifi_lobby_map_0225CE38(v0->actor)) {
            {
                VecFx32 v4;

                wifi_lobby_map_02262318(v2, v0->unk_04, v0->unk_08, &v4);
                v0->targetX = v4.x + (FX32_CONST(-16));
                wifi_lobby_map_0225D054(v0->actor, &v4);
                v0->targetY = v4.y;
                v0->frame = 0;
            }

            {
                WiFi2DCharPosition v5 = { 0 };
                wifi_lobby_map_0225CCB4(v0->actor, v5);
            }

            Sound_PlayEffect(SEQ_SE_DP_TELE2_sseq);

            wifi_lobby_map_0225D084(v0->actor, 1);
            wifi_lobby_map_02262E88(param0, 2);
        }
        break;
    case 2: {
        VecFx32 v6;
        VecFx32 v7;
        BOOL v8 = 0;

        v0->frame++;

        if (v0->frame >= 24) {
            v0->frame = 24;
            v8 = 1;
        }

        wifi_lobby_map_02262318(v2, v0->unk_04, v0->unk_08, &v6);

        v7.z = v6.z;
        v7.x = v0->targetX;
        v7.y = FX_Div(FX_Mul(FX32_CONST(v0->frame), (v6.y - v0->targetY)), FX32_CONST(24));
        v7.y += v0->targetY;

        wifi_lobby_map_0225D048(v0->actor, &v7);

        if (v8 == 1) {
            wifi_lobby_map_0225D084(v0->actor, 0);
            wifi_lobby_map_0225D0B4(v0->actor, 1 << 3);
            wifi_lobby_map_0225D060(v0->actor, 2);
            wifi_lobby_map_02262E88(param0, 3);
        }
    } break;

    case 3: {
        VecFx32 v9;
        fx32 v10;

        if (wifi_lobby_map_0225E420(param1, v0->unk_04) == 1) {
            if (wifi_lobby_map_02263334(&v0->cameraAnim) == 0) {
                wifi_lobby_map_02263270(&v0->cameraAnim);
            }
        } else {
            if (wifi_lobby_map_02263334(&v0->cameraAnim) == 1) {
                wifi_lobby_map_0226332C(&v0->cameraAnim);
            }
        }

        v10 = wifi_lobby_map_02263290(&v0->cameraAnim);
        wifi_lobby_map_02262318(v2, v0->unk_04, v0->unk_08, &v9);
        v9.y += v10;
        wifi_lobby_map_0225D048(v0->actor, &v9);

        if (WiFiPlazaLobby_State_GetFloatState(v3, v0->unk_04) == 2) {
            wifi_lobby_map_02262E88(param0, 4);
        }
    } break;
    case 4:
        wifi_lobby_map_0225CC54(v0->actor);
        wifi_lobby_map_02262E64(param0);

        {
            WiFiLobbyMapTaskManager *v11;

            v11 = wifi_lobby_map_0225DF10(param1);
            wifi_lobby_map_02262E94(v11, param2, &Unk_wifi_lobby_map_0226DA10, NULL);
        }
        break;
    }

    return 0;
}

static BOOL wifi_lobby_map_02265A84(WiFiLobbyMapTask *param0, WiFiLobbyMapApp *param1, u32 param2)
{
    WiFiLobbyMapPlayerJoinState *v0;
    WiFiLobbyMapActorManager *v1;
    WiFiLobbyMapActor *v2;
    WiFiLobbyMapActor *v3;
    WiFiPlazaLobbyState *v4;

    v0 = wifi_lobby_map_02262E38(param0);
    v4 = wifi_lobby_map_0225DEE8(param1);
    v1 = wifi_lobby_map_0225DEF0(param1);
    v2 = wifi_lobby_map_0225CC70(v1, param2);
    v3 = wifi_lobby_map_0225CCAC(v1);

    switch (wifi_lobby_map_02262E84(param0)) {
    case 0:
        if (v0->activity == 0) {
            wifi_lobby_map_02262E8C(param0);
        } else {
            wifi_lobby_map_02262E88(param0, 3);
        }
        break;
    case 1:
        wifi_lobby_map_0225CDEC(v1, v2, 3);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 2:
    case 7:
    case 9: {
        BOOL v5;

        v5 = wifi_lobby_map_0225CE38(v2);

        if (v5 == 1) {
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 3:

    {
        WiFi2DCharPosition v6;

        v6 = wifi_lobby_map_0225CD34(v2);
        wifi_lobby_map_0225D03C(v2, &v6);
    }

        if (wifi_lobby_map_0225D0CC(v2) == 0) {
            wifi_lobby_map_0225D0C0(v2, 1);
        }

        wifi_lobby_map_0225CDEC(v1, v2, 4);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 4: {
        BOOL v7;

        v7 = wifi_lobby_map_0225CE38(v2);

        if (v7 == 1) {
            wifi_lobby_map_02262E8C(param0);
            wifi_lobby_map_0225CDEC(v1, v2, 0);
            wifi_lobby_map_0225DF4C(param1, param2, 0);
            wifi_lobby_map_0225DF6C(param1, param2, 0);
        }
    } break;
    case 5: {
        const WiFiPlazaProfile *v8;
        const WiFiPlazaProfile *v9;
        BOOL v10 = 0;

        if ((v0->chatPending == 1) && (WiFiPlazaLobby_State_IsChatPending(v4) == 0)) {
            u32 v11;
            u32 v12;
            u32 v13;

            v9 = WiFiPlazaLobby_State_GetOwnProfile(v4);
            v13 = WiFiPlazaLobby_State_GetVenueIndex(v9);

            if (v13 == 9) {
                WiFiPlazaLobby_State_SetChatPending(v4);

                v12 = wifi_lobby_map_0225CD60(v2, 6);
                v11 = WiFi2DChar_DirectionOpposite(v12);

                wifi_lobby_map_0225CDAC(v1, v3, 0, v11);
            }
        }

        v8 = WiFiPlazaLobby_State_GetProfileBySlot(v4, param2);

        do {
            if (v8 == NULL) {
                v10 = 1;
                break;
            }

            if (v0->chatPending == 1) {
                if (WiFiPlazaLobby_State_IsChatActive(v4) == 0) {
                    v10 = 1;
                    break;
                }
            }

            if (WiFiPlazaLobby_State_PopPlayerUpdated(v4, param2)) {
                u32 v14;

                v14 = WiFiPlazaLobby_State_GetVenueIndex(v8);

                if (v14 != v0->slot) {
                    v10 = 1;
                    break;
                }
            }
        } while (0);

        if (v10 == 1) {
            wifi_lobby_map_02262E8C(param0);
            wifi_lobby_map_0225DF4C(param1, param2, 1);
            wifi_lobby_map_0225DF6C(param1, param2, 1);
        }
    } break;
    case 6:
        wifi_lobby_map_0225CDEC(v1, v2, 3);
        wifi_lobby_map_02262E8C(param0);
        break;
    case 8: {
        WiFiLobbyMapActor *v15;
        WiFi2DCharPosition v16;

        v15 = wifi_lobby_map_0225CCAC(v1);

        if (wifi_lobby_map_0225CEDC(v15, v0->tileX, v0->tileY) == 0) {
            v16.x = (v0->tileX) * 16;
            v16.y = (v0->tileY) * 16;

            wifi_lobby_map_0225CCB4(v2, v16);
            wifi_lobby_map_0225D03C(v2, &v16);
            wifi_lobby_map_0225CDEC(v1, v2, 4);
            wifi_lobby_map_02262E8C(param0);
        }
    } break;
    case 10:
        wifi_lobby_map_0225CDEC(v1, v2, 2);
        wifi_lobby_map_0225DF4C(param1, param2, 0);
        wifi_lobby_map_0225DF6C(param1, param2, 0);

        return 1;
    }

    return 0;
}

static BOOL wifi_lobby_map_02265CCC(WiFiLobbyMapPlayerJoinState *param0, WiFiPlazaLobbyState *param1, WiFiLobbyMapApp *param2, WiFiLobbyMapActor *param3, u8 param4, int param5)
{
    u32 v0;
    u32 v1;
    WiFi2DCharPosition v2;
    WiFiLobbyMapActorManager *v3;
    WiFiLobbyMapActor *v4;
    WiFiLobbyMapGrid *v5;
    BOOL v6 = 0;
    BOOL v7;

    v3 = wifi_lobby_map_0225DEF0(param2);
    v4 = wifi_lobby_map_0225CCAC(v3);
    v5 = wifi_lobby_map_0225DF00(param2);
    v0 = wifi_lobby_map_0225CD60(param3, 4);
    v1 = 1;

    switch (param4) {
    case 2:
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DA28, 4, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 3:
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DA58, 4, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 4:
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DA38, 4, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 5:
        v1 = 0;
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DAB8, 8, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 6:
        v1 = 0;
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DAD8, 8, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 7:
        v1 = 3;
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DA48, 4, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 8:
        v1 = 0;
        v7 = wifi_lobby_map_02265ED0(v5, v3, Unk_wifi_lobby_map_0226DA68, 4, &v2);

        if (v7 == 0) {
            return 0;
        }
        break;
    case 10:
        return 0;
    case 9:
        if (WiFiPlazaLobby_State_IsChatActive(param1) == 0) {
            return 0;
        }

        if (WiFiPlazaLobby_State_IsChatRequested(param1) == 0) {
            return 0;
        }

        if (WiFiPlazaLobby_State_GetChatPartner(param1) != v0) {
            return 0;
        }

        v7 = wifi_lobby_map_0225CF4C(v3, v4, &v1, &v2);
        GF_ASSERT(v7 == 1);

        v1 = WiFi2DChar_DirectionOpposite(v1);
        v6 = 1;
        break;
    case 0:
    case 1:
    case 11:
    case 14:
    case 12:
    case 13:
        return 0;
    }

    {
        WiFi2DCharPosition v8;

        v8 = wifi_lobby_map_0225CD34(param3);

        wifi_lobby_map_0225CD04(param3, v2, v1);

        param0->tileX = (v8.x) / 16;
        param0->tileY = (v8.y) / 16;
        param0->slot = param4;
        param0->chatPending = v6;
        param0->activity = param5;
    }

    return 1;
}

static BOOL wifi_lobby_map_02265ED0(const WiFiLobbyMapGrid *param0, const WiFiLobbyMapActorManager *param1, const u32 *param2, u32 param3, WiFi2DCharPosition *param4)
{
    u16 v0, v1;
    int v2;
    BOOL v3;

    for (v2 = 0; v2 < param3; v2++) {
        v3 = wifi_lobby_map_0225C8D8(param0, param2[v2], &v0, &v1, 0);

        if (v3 == 1) {
            if (wifi_lobby_map_0225CE7C(param1, v0, v1) == NULL) {
                param4->x = (v0) * 16;
                param4->y = (v1) * 16;
                return 1;
            }
        }
    }

    return 0;
}
