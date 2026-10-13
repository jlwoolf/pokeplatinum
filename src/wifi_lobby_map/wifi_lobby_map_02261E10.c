#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"

#include <nitro.h>
#include <string.h>

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/wifi_lobby_map_02260B44.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_model_manager_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_effect_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_character_decl.h"

#include "enums.h"
#include "heap.h"
#include "sound_playback.h"

typedef struct {
    WiFiLobbyMapCharacter *character;
    u16 state;
    s16 counter;
    fx32 speed;
} WiFiLobbyMapObjectAnimController;

typedef struct {
    WiFiLobbyMapCharacter *primaryCharacters[3];
    WiFiLobbyMapCharacter *secondaryCharacters[3];
    BOOL activityTriggered;
    WiFiLobbyMapObjectAnimController controllers0[24];
    WiFiLobbyMapObjectAnimController controllers1[24];
    WiFiLobbyMapCharacter *characters0[24];
    WiFiLobbyMapObjectAnimController controllers2[24];
    u8 controller0Count;
    u8 controller1Count;
    u8 characterCount;
    u8 controller2Count;
    u32 phase;
} WiFiLobbyMapObjectPool;

typedef struct WiFiLobbyMapObjectManager_t {
    const WiFiLobbyMapGrid *grid;
    WiFiLobbyMapModelManager *modelManager;
    WiFiLobbyMapCharacter *characters[128];
    WiFiLobbyMapEffect *effects[9];
    WiFiLobbyMapObjectPool pool;
    u8 mapID;
    u8 variant;
    u8 characterCount;
    u8 effectCount;
} WiFiLobbyMapObjectManager;

typedef struct {
    u16 objectID;
    u16 modelIndex;
} WiFiLobbyMapObjectSpawn;

typedef struct {
    u16 modelIndex;
    u16 animIndex;
} WiFiLobbyMapEffectSpawn;

static BOOL wifi_lobby_map_022628C8(const WiFiLobbyMapCharacter *param0, u8 param1, u8 param2);
static void wifi_lobby_map_02262908(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_02262938(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_02262968(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_022629AC(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_022629DC(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_022629FC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapCharacter *param1);
static void wifi_lobby_map_02262A04(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262A50(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1, fx32 param2);
static void wifi_lobby_map_02262A80(WiFiLobbyMapObjectAnimController *param0);
static void wifi_lobby_map_02262AA4(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262AE0(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262B24(WiFiLobbyMapObjectAnimController *param0);
static BOOL wifi_lobby_map_02262B2C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262BD0(WiFiLobbyMapObjectAnimController *param0, fx32 param1);
static void wifi_lobby_map_02262BEC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262C64(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262C94(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262D0C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1);
static void wifi_lobby_map_02262D48(WiFiLobbyMapCharacter *param0, u32 param1);

static const WiFiLobbyMapObjectSpawn Unk_wifi_lobby_map_0226D944[] = {
    { 0x18, 0x0 },
    { 0x19, 0x1 },
    { 0x1A, 0x2 },
    { 0x1B, 0x3 },
    { 0x1B, 0x3 },
    { 0x1C, 0x4 },
    { 0x21, 0x5 },
    { 0x46, 0x6 },
    { 0x47, 0x7 },
    { 0x48, 0x8 },
    { 0x4C, 0x9 },
    { 0x49, 0xA },
    { 0x4A, 0xA },
    { 0x4B, 0xA },
    { 0x4D, 0xB },
    { 0x4E, 0xC },
    { 0x4D, 0xD },
    { 0x4E, 0xD },
    { 0x4D, 0xE },
    { 0x4E, 0xE },
    { 0x19, 0xF },
    { 0x1A, 0xF },
    { 0x1B, 0xF },
    { 0x1B, 0xF },
    { 0x1C, 0xF },
    { 0x19, 0x10 },
    { 0x1A, 0x10 },
    { 0x1B, 0x10 },
    { 0x1B, 0x10 },
    { 0x1C, 0x10 },
    { 0x5C, 0xD },
    { 0x5D, 0xD },
    { 0x5C, 0xE },
    { 0x5D, 0xE },
    { 0x62, 0x11 }
};

static const s32 Unk_wifi_lobby_map_0226D90C[2] = {
    0xFFFFFFFFFFFFFFF5,
    0xC
};

static const WiFi2DCharPosition Unk_wifi_lobby_map_0226D914[3] = {
    { 0xFFFFFFFFFFFFFFFE, 0xA },
    { 0xE, 0xA },
    { 0x1E, 0xA }
};

static const WiFiLobbyMapEffectSpawn Unk_wifi_lobby_map_0226D920[9] = {
    { 0x0, 0x0 },
    { 0x0, 0x0 },
    { 0x1, 0x0 },
    { 0x0, 0x1 },
    { 0x0, 0x1 },
    { 0x1, 0x1 },
    { 0x0, 0x2 },
    { 0x0, 0x2 },
    { 0x1, 0x2 }
};

WiFiLobbyMapObjectManager *wifi_lobby_map_02261E10(int param0, int param1, const WiFiLobbyMapGrid *param2, enum HeapID heapID, u32 heapID2)
{
    WiFiLobbyMapObjectManager *v0;
    int v1;

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapObjectManager));
    memset(v0, 0, sizeof(WiFiLobbyMapObjectManager));

    v0->grid = param2;
    v0->mapID = param0;
    v0->variant = param1;
    v0->modelManager = wifi_lobby_map_02260B44(9, 128, heapID, heapID2);

    wifi_lobby_map_02260CE4(v0->modelManager, param1, param0, heapID, heapID2);

    {
        int v2;
        u32 v3;
        u16 v4, v5;

        for (v2 = 0; v2 < NELEMS(Unk_wifi_lobby_map_0226D944); v2++) {
            v3 = 0;

            while (wifi_lobby_map_0225C8D8(v0->grid, Unk_wifi_lobby_map_0226D944[v2].objectID, &v4, &v5, v3) == 1) {
                v0->characters[v0->characterCount] = wifi_lobby_map_02260F90(
                    v0->modelManager, Unk_wifi_lobby_map_0226D944[v2].modelIndex, v4, v5);

                switch (Unk_wifi_lobby_map_0226D944[v2].modelIndex) {
                case 6:
                case 7:
                case 8:
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 0, 0);
                    v0->pool.primaryCharacters[Unk_wifi_lobby_map_0226D944[v2].modelIndex - 6] = v0->characters[v0->characterCount];
                    break;
                case 0:
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 0, 0);
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 1, 0);
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 2, 0);
                    break;
                case 10:
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 0, 2);
                    v0->pool.secondaryCharacters[Unk_wifi_lobby_map_0226D944[v2].objectID - 73] = v0->characters[v0->characterCount];
                    break;
                case 11:
                case 12:
                    wifi_lobby_map_0226110C(v0->modelManager, v0->characters[v0->characterCount], 0, 2);
                    break;
                case 13:
                    wifi_lobby_map_022629FC(&v0->pool.controllers0[v0->pool.controller0Count], v0->characters[v0->characterCount]);
                    v0->pool.controller0Count++;
                    GF_ASSERT(v0->pool.controller0Count <= 24);
                    wifi_lobby_map_0226138C(v0->characters[v0->characterCount], 0);

                    if ((Unk_wifi_lobby_map_0226D944[v2].objectID == 92) || (Unk_wifi_lobby_map_0226D944[v2].objectID == 93)) {
                        wifi_lobby_map_02262D48(v0->characters[v0->characterCount], Unk_wifi_lobby_map_0226D944[v2].objectID);
                    }
                    break;
                case 14:
                    wifi_lobby_map_022629FC(&v0->pool.controllers1[v0->pool.controller1Count], v0->characters[v0->characterCount]);
                    v0->pool.controller1Count++;
                    GF_ASSERT(v0->pool.controller0Count <= 24);
                    wifi_lobby_map_0226138C(v0->characters[v0->characterCount], 0);

                    if ((Unk_wifi_lobby_map_0226D944[v2].objectID == 92) || (Unk_wifi_lobby_map_0226D944[v2].objectID == 93)) {
                        wifi_lobby_map_02262D48(v0->characters[v0->characterCount], Unk_wifi_lobby_map_0226D944[v2].objectID);
                    }
                    break;
                case 15:
                    v0->pool.characters0[v0->pool.characterCount] = v0->characters[v0->characterCount];
                    v0->pool.characterCount++;
                    GF_ASSERT(v0->pool.characterCount <= 24);
                    wifi_lobby_map_0226138C(v0->characters[v0->characterCount], 0);
                    break;
                case 16:
                    wifi_lobby_map_022629FC(&v0->pool.controllers2[v0->pool.controller2Count], v0->characters[v0->characterCount]);
                    v0->pool.controller2Count++;
                    GF_ASSERT(v0->pool.controller2Count <= 24);
                    wifi_lobby_map_0226138C(v0->characters[v0->characterCount], 0);

                    {
                        WiFi2DCharPosition v6;

                        v6 = wifi_lobby_map_022610E4(v0->characters[v0->characterCount]);
                        v6.x += 8;
                        v6.y += 20;
                        wifi_lobby_map_022610BC(v0->characters[v0->characterCount], v6);
                    }
                    break;
                }

                v0->characterCount++;
                v3++;
            }
        }
    }

    {
        VecFx32 v7;

        v7.x = 0;
        v7.z = (FX32_CONST(40));
        v7.y = (FX32_CONST(0));

        for (v1 = 0; v1 < 9; v1++) {
            v0->effects[v1] = wifi_lobby_map_02260E20(v0->modelManager, Unk_wifi_lobby_map_0226D920[v1].modelIndex, Unk_wifi_lobby_map_0226D920[v1].animIndex, &v7);
            wifi_lobby_map_02260F38(v0->effects[v1], 0);
        }

        v0->effectCount = 9;
    }

    return v0;
}

void wifi_lobby_map_022621AC(WiFiLobbyMapObjectManager *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < param0->effectCount; v0++) {
            wifi_lobby_map_02260E8C(param0->effects[v0]);
        }
    }

    {
        int v1;

        for (v1 = 0; v1 < param0->characterCount; v1++) {
            wifi_lobby_map_02261058(param0->modelManager, param0->characters[v1]);
        }
    }

    wifi_lobby_map_02260D80(param0->modelManager);
    wifi_lobby_map_02260BB8(param0->modelManager);

    Heap_Free(param0);
}

void wifi_lobby_map_02262210(WiFiLobbyMapObjectManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->pool.controller0Count; v0++) {
        wifi_lobby_map_02262A04(&param0->pool.controllers0[v0], param0->modelManager);
    }

    for (v0 = 0; v0 < param0->pool.controller1Count; v0++) {
        wifi_lobby_map_02262BEC(&param0->pool.controllers1[v0], param0->modelManager);
    }

    for (v0 = 0; v0 < param0->pool.controller2Count; v0++) {
        wifi_lobby_map_02262C94(&param0->pool.controllers2[v0], param0->modelManager);
    }

    wifi_lobby_map_02260BE8(param0->modelManager);
}

void wifi_lobby_map_02262298(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260C50(param0->modelManager);
}

void wifi_lobby_map_022622A4(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260CE0(param0->modelManager);
}

void wifi_lobby_map_022622B0(WiFiLobbyMapObjectManager *param0, u32 param1, fx32 param2)
{
    VecFx32 v0;

    GF_ASSERT(param0->effectCount > param1);

    v0.x = param2;
    v0.z = (FX32_CONST(40));
    v0.y = (FX32_CONST(0));

    wifi_lobby_map_02260EA0(param0->effects[param1], &v0);
}

void wifi_lobby_map_022622EC(WiFiLobbyMapObjectManager *param0, u32 param1, const VecFx32 *param2)
{
    GF_ASSERT(param0->effectCount > param1);
    wifi_lobby_map_02260EE4(param0->effects[param1], param2);
}

void wifi_lobby_map_02262318(const WiFiLobbyMapObjectManager *param0, u32 param1, u32 param2, VecFx32 *param3)
{
    GF_ASSERT(param0->effectCount > param1);
    GF_ASSERT(param2 < 3);

    wifi_lobby_map_02260F28(param0->effects[param1], param3);

    param3->x += (Unk_wifi_lobby_map_0226D914[param2].x * (FX32_ONE));
    param3->z += (Unk_wifi_lobby_map_0226D914[param2].y * (FX32_ONE));
    param3->y = (FX32_CONST(40));
}

BOOL wifi_lobby_map_02262374(WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->effectCount > param1);
    return wifi_lobby_map_02260F44(param0->effects[param1]);
}

BOOL wifi_lobby_map_0226239C(WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->effectCount > param1);
    return wifi_lobby_map_02260F5C(param0->effects[param1]);
}

void wifi_lobby_map_022623C4(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param0->effectCount > param1);
    wifi_lobby_map_02260F38(param0->effects[param1], param2);
}

void wifi_lobby_map_022623F0(WiFiLobbyMapObjectManager *param0, u32 param1, u16 param2)
{
    GF_ASSERT(param0->effectCount > param1);
    wifi_lobby_map_02260F74(param0->effects[param1], param2);
}

BOOL wifi_lobby_map_0226241C(const WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->effectCount > param1);
    return wifi_lobby_map_02260F80(param0->effects[param1]);
}

BOOL wifi_lobby_map_02262444(const WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->effectCount > param1);
    return wifi_lobby_map_02260F88(param0->effects[param1]);
}

void wifi_lobby_map_0226246C(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260DC8(param0->modelManager);
}

void wifi_lobby_map_02262478(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260DF4(param0->modelManager);
}

void wifi_lobby_map_02262484(WiFiLobbyMapObjectManager *param0, u8 param1, u8 param2)
{
    int v0;
    BOOL v1[2];
    u32 v2;

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        v1[0] = wifi_lobby_map_022628C8(param0->characters[v0], param1 - 1, param2 - 1);
        v1[1] = wifi_lobby_map_022628C8(param0->characters[v0], param1, param2 - 1);

        if ((v1[0] == 1) || (v1[1] == 1)) {
            v2 = wifi_lobby_map_022610B8(param0->characters[v0]);

            switch (v2) {
            case 1:
            case 2:
            case 3:
            case 4:
                if (param0->variant == 4) {
                    wifi_lobby_map_022629AC(param0, param0->characters[v0]);
                } else {
                    wifi_lobby_map_02262968(param0, param0->characters[v0]);
                }
                break;
            default:
                break;
            }
        }
    }
}

void wifi_lobby_map_0226251C(WiFiLobbyMapObjectManager *param0, BOOL param1)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->characters[v0]);

        switch (v1) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (param1 == 1) {
                wifi_lobby_map_02261398(param0->modelManager, param0->characters[v0], 1 << 0);
            }
            break;
        case 15:
            if (param1 == 1) {
                wifi_lobby_map_022613C0(param0->characters[v0], FX32_HALF);
                wifi_lobby_map_0226110C(param0->modelManager, param0->characters[v0], 0, 6);
                wifi_lobby_map_0226110C(param0->modelManager, param0->characters[v0], 1, 6);
                wifi_lobby_map_0226110C(param0->modelManager, param0->characters[v0], 2, 6);
                wifi_lobby_map_0226138C(param0->characters[v0], 1);
            } else {
                wifi_lobby_map_02261220(param0->modelManager, param0->characters[v0], 0);
                wifi_lobby_map_02261220(param0->modelManager, param0->characters[v0], 1);
                wifi_lobby_map_02261220(param0->modelManager, param0->characters[v0], 2);
                wifi_lobby_map_0226138C(param0->characters[v0], 0);
            }
            break;
        default:
            break;
        }
    }
}

void wifi_lobby_map_022625D8(WiFiLobbyMapObjectManager *param0, fx32 param1)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->pool.controller2Count; v0++) {
        wifi_lobby_map_02262BD0(&param0->pool.controllers2[v0], param1);
    }
}

void wifi_lobby_map_0226260C(WiFiLobbyMapObjectManager *param0)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->characters[v0]);

        switch (v1) {
        case 1:
        case 2:
        case 3:
        case 4:
            wifi_lobby_map_02261398(param0->modelManager, param0->characters[v0], 1 << 0);
            break;
        default:
            break;
        }
    }
}

void wifi_lobby_map_02262658(WiFiLobbyMapObjectManager *param0, int param1)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->characterCount; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->characters[v0]);

        switch (v1) {
        case 11:
        case 12:
            switch (param1) {
            case 0:
                wifi_lobby_map_0226110C(param0->modelManager, param0->characters[v0], 0, 2);
                param0->pool.activityTriggered = 0;
                break;
            case 1:
                wifi_lobby_map_0226111C(param0->modelManager, param0->characters[v0], 0, 1, wifi_lobby_map_02262908);
                param0->pool.activityTriggered = 1;
                break;
            case 2:
                wifi_lobby_map_0226111C(param0->modelManager, param0->characters[v0], 0, 4, wifi_lobby_map_02262938);
                wifi_lobby_map_02261220(param0->modelManager, param0->characters[v0], 1);
                param0->pool.activityTriggered = 0;
                break;
            case 3:
                wifi_lobby_map_0226110C(param0->modelManager, param0->characters[v0], 1, 0);
                wifi_lobby_map_02261220(param0->modelManager, param0->characters[v0], 0);
                param0->pool.activityTriggered = 1;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

BOOL wifi_lobby_map_0226271C(const WiFiLobbyMapObjectManager *param0)
{
    return param0->pool.activityTriggered;
}

void wifi_lobby_map_02262724(WiFiLobbyMapObjectManager *param0, BOOL param1, fx32 param2)
{
    int v0;

    for (v0 = 0; v0 < param0->pool.controller0Count; v0++) {
        wifi_lobby_map_02262754(param0, v0, param1, param2);
    }
}

BOOL wifi_lobby_map_02262754(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2, fx32 param3)
{
    int v0;
    WiFiLobbyMapObjectAnimController *v1;

    if (param1 < param0->pool.controller0Count) {
        v1 = &param0->pool.controllers0[param1];

        if (param2) {
            wifi_lobby_map_02262A50(v1, param0->modelManager, param3);
        } else {
            wifi_lobby_map_02262A80(v1);
        }

        return 1;
    }

    return 0;
}

void wifi_lobby_map_0226278C(WiFiLobbyMapObjectManager *param0, fx32 param1)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->pool.controller1Count; v0++) {
        wifi_lobby_map_02262BD0(&param0->pool.controllers1[v0], param1);
    }
}

void wifi_lobby_map_022627BC(WiFiLobbyMapObjectManager *param0, enum PlazaMinigame param1, u32 param2, BOOL param3, BOOL param4, BOOL param5)
{
    BOOL v0;
    WiFiLobbyMapCharacter *v1;
    WiFiLobbyMapCharacter *v2;
    u32 v3 = param1 - WiFiPlazaLobbyActivity_00;
    v2 = param0->pool.primaryCharacters[v3];
    v1 = param0->pool.secondaryCharacters[v3];

    if ((param4 == 1) || (param3 == 1)) {
        if (wifi_lobby_map_02261348(v2, 1) == 0) {
            wifi_lobby_map_0226110C(param0->modelManager, v2, 1, 0);
        }

        if (param4 == 1) {
            wifi_lobby_map_022612F0(param0->modelManager, v1, 0, FX32_CONST((5 + param2 - 1) * 4));
        } else {
            param0->pool.phase = (param0->pool.phase + 1) % 28;

            if (param0->pool.phase < (28 / 2)) {
                wifi_lobby_map_022612F0(param0->modelManager, v1, 0, FX32_CONST((1 + param2 - 1) * 4));
            } else {
                wifi_lobby_map_022612F0(param0->modelManager, v1, 0, FX32_CONST(0 * 4));
            }
        }
    } else {
        if (param5) {
            wifi_lobby_map_0226128C(param0->modelManager, v2);
            wifi_lobby_map_0226128C(param0->modelManager, v1);
            wifi_lobby_map_02261398(param0->modelManager, v2, 1 << 0);
        } else {
            wifi_lobby_map_02261220(param0->modelManager, v2, 1);
            wifi_lobby_map_022612F0(param0->modelManager, v1, 0, 0);
        }
    }
}

static BOOL wifi_lobby_map_022628C8(const WiFiLobbyMapCharacter *param0, u8 param1, u8 param2)
{
    WiFi2DCharPosition v0;
    WiFi2DCharPosition v1;

    v1.x = param1 * 16;
    v1.y = param2 * 16;

    v0 = wifi_lobby_map_022610E4(param0);

    if ((v0.x == v1.x) && (v0.y == v1.y)) {
        return 1;
    }

    return 0;
}

static void wifi_lobby_map_02262908(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1)
{
    u32 v0 = wifi_lobby_map_022610B8(param1);
    GF_ASSERT((v0 == 11) || (v0 == 12));

    if ((v0 == 11) || (v0 == 12)) {
        wifi_lobby_map_0226110C(param0, param1, 1, 0);
    }
}

static void wifi_lobby_map_02262938(WiFiLobbyMapModelManager *param0, WiFiLobbyMapCharacter *param1)
{
    u32 v0 = wifi_lobby_map_022610B8(param1);
    GF_ASSERT((v0 == 11) || (v0 == 12));

    if ((v0 == 11) || (v0 == 12)) {
        wifi_lobby_map_0226110C(param0, param1, 0, 2);
    }
}

static void wifi_lobby_map_02262968(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1)
{
    fx32 v0;
    BOOL v1;
    int v2;

    v1 = 0;

    if (wifi_lobby_map_022612B4(param0->modelManager, param1, 0) == 0) {
        v1 = 1;
    } else {
        v0 = wifi_lobby_map_02261368(param1, 0);

        if (v0 > 0x2000) {
            v1 = 1;
        }
    }

    if (v1 == 1) {
        wifi_lobby_map_022629DC(param0, param1);
        Sound_PlayEffect(SEQ_SE_PL_EFF02_sseq);
    }
}

static void wifi_lobby_map_022629AC(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1)
{
    BOOL v0 = 0;

    if (wifi_lobby_map_022612B4(param0->modelManager, param1, 0) == 0) {
        v0 = 1;
    }

    if (v0 == 1) {
        wifi_lobby_map_022629DC(param0, param1);
        Sound_PlayEffect(SEQ_SE_PL_EFF04_sseq);
    }
}

static void wifi_lobby_map_022629DC(WiFiLobbyMapObjectManager *param0, WiFiLobbyMapCharacter *param1)
{
    int v0;

    for (v0 = 0; v0 < 3; v0++) {
        wifi_lobby_map_0226110C(param0->modelManager, param1, v0, 1);
    }
}

static void wifi_lobby_map_022629FC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapCharacter *param1)
{
    param0->character = param1;
    param0->state = 0;
}

static void wifi_lobby_map_02262A04(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->state) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262AA4(param0, param1);
        param0->state = 2;
        break;
    case 2:
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->state = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_02262AE0(param0, param1);
            param0->state = 0;
        }
        break;
    default:
        break;
    }
}

static void wifi_lobby_map_02262A50(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1, fx32 param2)
{
    if ((param0->state == 1) || (param0->state == 2)) {
        return;
    }

    if ((param0->state == 3) || (param0->state == 4)) {
        wifi_lobby_map_02262AE0(param0, param1);
    }

    param0->state = 1;
    param0->speed = param2;
}

static void wifi_lobby_map_02262A80(WiFiLobbyMapObjectAnimController *param0)
{
    if ((param0->state == 3) || (param0->state == 4)) {
        return;
    }

    if ((param0->state == 1) || (param0->state == 0)) {
        param0->state = 0;
        return;
    }

    param0->state = 3;
}

static void wifi_lobby_map_02262AA4(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->character, param0->speed);
    wifi_lobby_map_0226110C(param1, param0->character, 0, 0);
    wifi_lobby_map_0226110C(param1, param0->character, 1, 0);
    wifi_lobby_map_0226110C(param1, param0->character, 2, 0);
    wifi_lobby_map_0226138C(param0->character, 1);
}

static void wifi_lobby_map_02262AE0(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_02261220(param1, param0->character, 0);
    wifi_lobby_map_02261220(param1, param0->character, 1);
    wifi_lobby_map_02261220(param1, param0->character, 2);
    wifi_lobby_map_0226138C(param0->character, 0);
    wifi_lobby_map_022613E0(param0->character);
    wifi_lobby_map_022613E8(param0->character, FX32_ONE, FX32_ONE, FX32_ONE);
}

static void wifi_lobby_map_02262B24(WiFiLobbyMapObjectAnimController *param0)
{
    param0->counter = 0;
}

static BOOL wifi_lobby_map_02262B2C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    if (param0->counter < 10) {
        param0->counter++;

        {
            fx32 v0;
            fx32 v1;

            v0 = param0->speed - 0;
            v1 = FX_Mul(param0->counter << FX32_SHIFT, v0);
            v1 = FX_Div(v1, 10 << FX32_SHIFT);
            v1 += param0->speed;

            wifi_lobby_map_022613C0(param0->character, v1);
        }

        {
            u32 v2;

            v2 = (param0->counter * 31) / 10;
            v2 = 31 - v2;

            wifi_lobby_map_022613C8(param0->character, v2, 31);
        }

        {
            fx32 v3;

            v3 = FX_Mul(param0->counter << FX32_SHIFT, (FX32_CONST(0.180f)));
            v3 = FX_Div(v3, 10 << FX32_SHIFT);
            v3 = FX32_ONE + v3;

            wifi_lobby_map_022613E8(param0->character, v3, v3, v3);
        }

        return 0;
    }

    return 1;
}

static void wifi_lobby_map_02262BD0(WiFiLobbyMapObjectAnimController *param0, fx32 param1)
{
    if ((param0->state == 1) || (param0->state == 2)) {
        return;
    }

    param0->state = 1;
    param0->speed = param1;
}

static void wifi_lobby_map_02262BEC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->state) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262C64(param0, param1);
        param0->state = 2;
        break;
    case 2:
        if (wifi_lobby_map_022612B4(param1, param0->character, 0) == 0) {
            param0->state = 3;
        }
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->state = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_0226138C(param0->character, 0);
            wifi_lobby_map_022613E0(param0->character);
            wifi_lobby_map_022613E8(param0->character, FX32_ONE, FX32_ONE, FX32_ONE);

            param0->state = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void wifi_lobby_map_02262C64(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->character, param0->speed);
    wifi_lobby_map_0226110C(param1, param0->character, 0, 1);
    wifi_lobby_map_0226110C(param1, param0->character, 1, 1);
    wifi_lobby_map_0226138C(param0->character, 1);
}

static void wifi_lobby_map_02262C94(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->state) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262D0C(param0, param1);
        param0->state = 2;
        break;
    case 2:
        if (wifi_lobby_map_022612B4(param1, param0->character, 0) == 0) {
            param0->state = 3;
        }
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->state = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_0226138C(param0->character, 0);
            wifi_lobby_map_022613E0(param0->character);
            wifi_lobby_map_022613E8(param0->character, FX32_ONE, FX32_ONE, FX32_ONE);
            param0->state = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void wifi_lobby_map_02262D0C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->character, param0->speed);
    wifi_lobby_map_0226110C(param1, param0->character, 0, 1);
    wifi_lobby_map_0226110C(param1, param0->character, 1, 1);
    wifi_lobby_map_0226110C(param1, param0->character, 2, 1);
    wifi_lobby_map_0226138C(param0->character, 1);
}

static void wifi_lobby_map_02262D48(WiFiLobbyMapCharacter *param0, u32 param1)
{
    WiFi2DCharPosition v0;
    u32 v1;

    GF_ASSERT((param1 == 92) || (param1 == 93));

    v1 = param1 - 92;
    v0 = wifi_lobby_map_022610E4(param0);
    v0.x += Unk_wifi_lobby_map_0226D90C[v1];
    v0.y += -10;

    wifi_lobby_map_022610BC(param0, v0);
}
