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
    WiFiLobbyMapCharacter *unk_00;
    u16 unk_04;
    s16 unk_06;
    fx32 unk_08;
} WiFiLobbyMapObjectAnimController;

typedef struct {
    WiFiLobbyMapCharacter *unk_00[3];
    WiFiLobbyMapCharacter *unk_0C[3];
    BOOL unk_18;
    WiFiLobbyMapObjectAnimController unk_1C[24];
    WiFiLobbyMapObjectAnimController unk_13C[24];
    WiFiLobbyMapCharacter *unk_25C[24];
    WiFiLobbyMapObjectAnimController unk_2BC[24];
    u8 unk_3DC;
    u8 unk_3DD;
    u8 unk_3DE;
    u8 unk_3DF;
    u32 unk_3E0;
} WiFiLobbyMapObjectPool;

typedef struct WiFiLobbyMapObjectManager_t {
    const WiFiLobbyMapGrid *unk_00;
    WiFiLobbyMapModelManager *unk_04;
    WiFiLobbyMapCharacter *unk_08[128];
    WiFiLobbyMapEffect *unk_208[9];
    WiFiLobbyMapObjectPool unk_22C;
    u8 unk_610;
    u8 unk_611;
    u8 unk_612;
    u8 unk_613;
} WiFiLobbyMapObjectManager;

typedef struct {
    u16 unk_00;
    u16 unk_02;
} WiFiLobbyMapObjectSpawn;

typedef struct {
    u16 unk_00;
    u16 unk_02;
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

    v0->unk_00 = param2;
    v0->unk_610 = param0;
    v0->unk_611 = param1;
    v0->unk_04 = wifi_lobby_map_02260B44(9, 128, heapID, heapID2);

    wifi_lobby_map_02260CE4(v0->unk_04, param1, param0, heapID, heapID2);

    {
        int v2;
        u32 v3;
        u16 v4, v5;

        for (v2 = 0; v2 < NELEMS(Unk_wifi_lobby_map_0226D944); v2++) {
            v3 = 0;

            while (wifi_lobby_map_0225C8D8(v0->unk_00, Unk_wifi_lobby_map_0226D944[v2].unk_00, &v4, &v5, v3) == 1) {
                v0->unk_08[v0->unk_612] = wifi_lobby_map_02260F90(
                    v0->unk_04, Unk_wifi_lobby_map_0226D944[v2].unk_02, v4, v5);

                switch (Unk_wifi_lobby_map_0226D944[v2].unk_02) {
                case 6:
                case 7:
                case 8:
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 0, 0);
                    v0->unk_22C.unk_00[Unk_wifi_lobby_map_0226D944[v2].unk_02 - 6] = v0->unk_08[v0->unk_612];
                    break;
                case 0:
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 0, 0);
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 1, 0);
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 2, 0);
                    break;
                case 10:
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 0, 2);
                    v0->unk_22C.unk_0C[Unk_wifi_lobby_map_0226D944[v2].unk_00 - 73] = v0->unk_08[v0->unk_612];
                    break;
                case 11:
                case 12:
                    wifi_lobby_map_0226110C(v0->unk_04, v0->unk_08[v0->unk_612], 0, 2);
                    break;
                case 13:
                    wifi_lobby_map_022629FC(&v0->unk_22C.unk_1C[v0->unk_22C.unk_3DC], v0->unk_08[v0->unk_612]);
                    v0->unk_22C.unk_3DC++;
                    GF_ASSERT(v0->unk_22C.unk_3DC <= 24);
                    wifi_lobby_map_0226138C(v0->unk_08[v0->unk_612], 0);

                    if ((Unk_wifi_lobby_map_0226D944[v2].unk_00 == 92) || (Unk_wifi_lobby_map_0226D944[v2].unk_00 == 93)) {
                        wifi_lobby_map_02262D48(v0->unk_08[v0->unk_612], Unk_wifi_lobby_map_0226D944[v2].unk_00);
                    }
                    break;
                case 14:
                    wifi_lobby_map_022629FC(&v0->unk_22C.unk_13C[v0->unk_22C.unk_3DD], v0->unk_08[v0->unk_612]);
                    v0->unk_22C.unk_3DD++;
                    GF_ASSERT(v0->unk_22C.unk_3DC <= 24);
                    wifi_lobby_map_0226138C(v0->unk_08[v0->unk_612], 0);

                    if ((Unk_wifi_lobby_map_0226D944[v2].unk_00 == 92) || (Unk_wifi_lobby_map_0226D944[v2].unk_00 == 93)) {
                        wifi_lobby_map_02262D48(v0->unk_08[v0->unk_612], Unk_wifi_lobby_map_0226D944[v2].unk_00);
                    }
                    break;
                case 15:
                    v0->unk_22C.unk_25C[v0->unk_22C.unk_3DE] = v0->unk_08[v0->unk_612];
                    v0->unk_22C.unk_3DE++;
                    GF_ASSERT(v0->unk_22C.unk_3DE <= 24);
                    wifi_lobby_map_0226138C(v0->unk_08[v0->unk_612], 0);
                    break;
                case 16:
                    wifi_lobby_map_022629FC(&v0->unk_22C.unk_2BC[v0->unk_22C.unk_3DF], v0->unk_08[v0->unk_612]);
                    v0->unk_22C.unk_3DF++;
                    GF_ASSERT(v0->unk_22C.unk_3DF <= 24);
                    wifi_lobby_map_0226138C(v0->unk_08[v0->unk_612], 0);

                    {
                        WiFi2DCharPosition v6;

                        v6 = wifi_lobby_map_022610E4(v0->unk_08[v0->unk_612]);
                        v6.x += 8;
                        v6.y += 20;
                        wifi_lobby_map_022610BC(v0->unk_08[v0->unk_612], v6);
                    }
                    break;
                }

                v0->unk_612++;
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
            v0->unk_208[v1] = wifi_lobby_map_02260E20(v0->unk_04, Unk_wifi_lobby_map_0226D920[v1].unk_00, Unk_wifi_lobby_map_0226D920[v1].unk_02, &v7);
            wifi_lobby_map_02260F38(v0->unk_208[v1], 0);
        }

        v0->unk_613 = 9;
    }

    return v0;
}

void wifi_lobby_map_022621AC(WiFiLobbyMapObjectManager *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < param0->unk_613; v0++) {
            wifi_lobby_map_02260E8C(param0->unk_208[v0]);
        }
    }

    {
        int v1;

        for (v1 = 0; v1 < param0->unk_612; v1++) {
            wifi_lobby_map_02261058(param0->unk_04, param0->unk_08[v1]);
        }
    }

    wifi_lobby_map_02260D80(param0->unk_04);
    wifi_lobby_map_02260BB8(param0->unk_04);

    Heap_Free(param0);
}

void wifi_lobby_map_02262210(WiFiLobbyMapObjectManager *param0)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_22C.unk_3DC; v0++) {
        wifi_lobby_map_02262A04(&param0->unk_22C.unk_1C[v0], param0->unk_04);
    }

    for (v0 = 0; v0 < param0->unk_22C.unk_3DD; v0++) {
        wifi_lobby_map_02262BEC(&param0->unk_22C.unk_13C[v0], param0->unk_04);
    }

    for (v0 = 0; v0 < param0->unk_22C.unk_3DF; v0++) {
        wifi_lobby_map_02262C94(&param0->unk_22C.unk_2BC[v0], param0->unk_04);
    }

    wifi_lobby_map_02260BE8(param0->unk_04);
}

void wifi_lobby_map_02262298(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260C50(param0->unk_04);
}

void wifi_lobby_map_022622A4(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260CE0(param0->unk_04);
}

void wifi_lobby_map_022622B0(WiFiLobbyMapObjectManager *param0, u32 param1, fx32 param2)
{
    VecFx32 v0;

    GF_ASSERT(param0->unk_613 > param1);

    v0.x = param2;
    v0.z = (FX32_CONST(40));
    v0.y = (FX32_CONST(0));

    wifi_lobby_map_02260EA0(param0->unk_208[param1], &v0);
}

void wifi_lobby_map_022622EC(WiFiLobbyMapObjectManager *param0, u32 param1, const VecFx32 *param2)
{
    GF_ASSERT(param0->unk_613 > param1);
    wifi_lobby_map_02260EE4(param0->unk_208[param1], param2);
}

void wifi_lobby_map_02262318(const WiFiLobbyMapObjectManager *param0, u32 param1, u32 param2, VecFx32 *param3)
{
    GF_ASSERT(param0->unk_613 > param1);
    GF_ASSERT(param2 < 3);

    wifi_lobby_map_02260F28(param0->unk_208[param1], param3);

    param3->x += (Unk_wifi_lobby_map_0226D914[param2].x * (FX32_ONE));
    param3->z += (Unk_wifi_lobby_map_0226D914[param2].y * (FX32_ONE));
    param3->y = (FX32_CONST(40));
}

BOOL wifi_lobby_map_02262374(WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->unk_613 > param1);
    return wifi_lobby_map_02260F44(param0->unk_208[param1]);
}

BOOL wifi_lobby_map_0226239C(WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->unk_613 > param1);
    return wifi_lobby_map_02260F5C(param0->unk_208[param1]);
}

void wifi_lobby_map_022623C4(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2)
{
    GF_ASSERT(param0->unk_613 > param1);
    wifi_lobby_map_02260F38(param0->unk_208[param1], param2);
}

void wifi_lobby_map_022623F0(WiFiLobbyMapObjectManager *param0, u32 param1, u16 param2)
{
    GF_ASSERT(param0->unk_613 > param1);
    wifi_lobby_map_02260F74(param0->unk_208[param1], param2);
}

BOOL wifi_lobby_map_0226241C(const WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->unk_613 > param1);
    return wifi_lobby_map_02260F80(param0->unk_208[param1]);
}

BOOL wifi_lobby_map_02262444(const WiFiLobbyMapObjectManager *param0, u32 param1)
{
    GF_ASSERT(param0->unk_613 > param1);
    return wifi_lobby_map_02260F88(param0->unk_208[param1]);
}

void wifi_lobby_map_0226246C(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260DC8(param0->unk_04);
}

void wifi_lobby_map_02262478(WiFiLobbyMapObjectManager *param0)
{
    wifi_lobby_map_02260DF4(param0->unk_04);
}

void wifi_lobby_map_02262484(WiFiLobbyMapObjectManager *param0, u8 param1, u8 param2)
{
    int v0;
    BOOL v1[2];
    u32 v2;

    for (v0 = 0; v0 < param0->unk_612; v0++) {
        v1[0] = wifi_lobby_map_022628C8(param0->unk_08[v0], param1 - 1, param2 - 1);
        v1[1] = wifi_lobby_map_022628C8(param0->unk_08[v0], param1, param2 - 1);

        if ((v1[0] == 1) || (v1[1] == 1)) {
            v2 = wifi_lobby_map_022610B8(param0->unk_08[v0]);

            switch (v2) {
            case 1:
            case 2:
            case 3:
            case 4:
                if (param0->unk_611 == 4) {
                    wifi_lobby_map_022629AC(param0, param0->unk_08[v0]);
                } else {
                    wifi_lobby_map_02262968(param0, param0->unk_08[v0]);
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

    for (v0 = 0; v0 < param0->unk_612; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->unk_08[v0]);

        switch (v1) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (param1 == 1) {
                wifi_lobby_map_02261398(param0->unk_04, param0->unk_08[v0], 1 << 0);
            }
            break;
        case 15:
            if (param1 == 1) {
                wifi_lobby_map_022613C0(param0->unk_08[v0], FX32_HALF);
                wifi_lobby_map_0226110C(param0->unk_04, param0->unk_08[v0], 0, 6);
                wifi_lobby_map_0226110C(param0->unk_04, param0->unk_08[v0], 1, 6);
                wifi_lobby_map_0226110C(param0->unk_04, param0->unk_08[v0], 2, 6);
                wifi_lobby_map_0226138C(param0->unk_08[v0], 1);
            } else {
                wifi_lobby_map_02261220(param0->unk_04, param0->unk_08[v0], 0);
                wifi_lobby_map_02261220(param0->unk_04, param0->unk_08[v0], 1);
                wifi_lobby_map_02261220(param0->unk_04, param0->unk_08[v0], 2);
                wifi_lobby_map_0226138C(param0->unk_08[v0], 0);
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

    for (v0 = 0; v0 < param0->unk_22C.unk_3DF; v0++) {
        wifi_lobby_map_02262BD0(&param0->unk_22C.unk_2BC[v0], param1);
    }
}

void wifi_lobby_map_0226260C(WiFiLobbyMapObjectManager *param0)
{
    int v0;
    u32 v1;

    for (v0 = 0; v0 < param0->unk_612; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->unk_08[v0]);

        switch (v1) {
        case 1:
        case 2:
        case 3:
        case 4:
            wifi_lobby_map_02261398(param0->unk_04, param0->unk_08[v0], 1 << 0);
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

    for (v0 = 0; v0 < param0->unk_612; v0++) {
        v1 = wifi_lobby_map_022610B8(param0->unk_08[v0]);

        switch (v1) {
        case 11:
        case 12:
            switch (param1) {
            case 0:
                wifi_lobby_map_0226110C(param0->unk_04, param0->unk_08[v0], 0, 2);
                param0->unk_22C.unk_18 = 0;
                break;
            case 1:
                wifi_lobby_map_0226111C(param0->unk_04, param0->unk_08[v0], 0, 1, wifi_lobby_map_02262908);
                param0->unk_22C.unk_18 = 1;
                break;
            case 2:
                wifi_lobby_map_0226111C(param0->unk_04, param0->unk_08[v0], 0, 4, wifi_lobby_map_02262938);
                wifi_lobby_map_02261220(param0->unk_04, param0->unk_08[v0], 1);
                param0->unk_22C.unk_18 = 0;
                break;
            case 3:
                wifi_lobby_map_0226110C(param0->unk_04, param0->unk_08[v0], 1, 0);
                wifi_lobby_map_02261220(param0->unk_04, param0->unk_08[v0], 0);
                param0->unk_22C.unk_18 = 1;
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
    return param0->unk_22C.unk_18;
}

void wifi_lobby_map_02262724(WiFiLobbyMapObjectManager *param0, BOOL param1, fx32 param2)
{
    int v0;

    for (v0 = 0; v0 < param0->unk_22C.unk_3DC; v0++) {
        wifi_lobby_map_02262754(param0, v0, param1, param2);
    }
}

BOOL wifi_lobby_map_02262754(WiFiLobbyMapObjectManager *param0, u32 param1, BOOL param2, fx32 param3)
{
    int v0;
    WiFiLobbyMapObjectAnimController *v1;

    if (param1 < param0->unk_22C.unk_3DC) {
        v1 = &param0->unk_22C.unk_1C[param1];

        if (param2) {
            wifi_lobby_map_02262A50(v1, param0->unk_04, param3);
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

    for (v0 = 0; v0 < param0->unk_22C.unk_3DD; v0++) {
        wifi_lobby_map_02262BD0(&param0->unk_22C.unk_13C[v0], param1);
    }
}

void wifi_lobby_map_022627BC(WiFiLobbyMapObjectManager *param0, enum PlazaMinigame param1, u32 param2, BOOL param3, BOOL param4, BOOL param5)
{
    BOOL v0;
    WiFiLobbyMapCharacter *v1;
    WiFiLobbyMapCharacter *v2;
    u32 v3 = param1 - WiFiPlazaLobbyActivity_00;
    v2 = param0->unk_22C.unk_00[v3];
    v1 = param0->unk_22C.unk_0C[v3];

    if ((param4 == 1) || (param3 == 1)) {
        if (wifi_lobby_map_02261348(v2, 1) == 0) {
            wifi_lobby_map_0226110C(param0->unk_04, v2, 1, 0);
        }

        if (param4 == 1) {
            wifi_lobby_map_022612F0(param0->unk_04, v1, 0, FX32_CONST((5 + param2 - 1) * 4));
        } else {
            param0->unk_22C.unk_3E0 = (param0->unk_22C.unk_3E0 + 1) % 28;

            if (param0->unk_22C.unk_3E0 < (28 / 2)) {
                wifi_lobby_map_022612F0(param0->unk_04, v1, 0, FX32_CONST((1 + param2 - 1) * 4));
            } else {
                wifi_lobby_map_022612F0(param0->unk_04, v1, 0, FX32_CONST(0 * 4));
            }
        }
    } else {
        if (param5) {
            wifi_lobby_map_0226128C(param0->unk_04, v2);
            wifi_lobby_map_0226128C(param0->unk_04, v1);
            wifi_lobby_map_02261398(param0->unk_04, v2, 1 << 0);
        } else {
            wifi_lobby_map_02261220(param0->unk_04, v2, 1);
            wifi_lobby_map_022612F0(param0->unk_04, v1, 0, 0);
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

    if (wifi_lobby_map_022612B4(param0->unk_04, param1, 0) == 0) {
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

    if (wifi_lobby_map_022612B4(param0->unk_04, param1, 0) == 0) {
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
        wifi_lobby_map_0226110C(param0->unk_04, param1, v0, 1);
    }
}

static void wifi_lobby_map_022629FC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapCharacter *param1)
{
    param0->unk_00 = param1;
    param0->unk_04 = 0;
}

static void wifi_lobby_map_02262A04(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->unk_04) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262AA4(param0, param1);
        param0->unk_04 = 2;
        break;
    case 2:
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->unk_04 = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_02262AE0(param0, param1);
            param0->unk_04 = 0;
        }
        break;
    default:
        break;
    }
}

static void wifi_lobby_map_02262A50(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1, fx32 param2)
{
    if ((param0->unk_04 == 1) || (param0->unk_04 == 2)) {
        return;
    }

    if ((param0->unk_04 == 3) || (param0->unk_04 == 4)) {
        wifi_lobby_map_02262AE0(param0, param1);
    }

    param0->unk_04 = 1;
    param0->unk_08 = param2;
}

static void wifi_lobby_map_02262A80(WiFiLobbyMapObjectAnimController *param0)
{
    if ((param0->unk_04 == 3) || (param0->unk_04 == 4)) {
        return;
    }

    if ((param0->unk_04 == 1) || (param0->unk_04 == 0)) {
        param0->unk_04 = 0;
        return;
    }

    param0->unk_04 = 3;
}

static void wifi_lobby_map_02262AA4(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->unk_00, param0->unk_08);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 0, 0);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 1, 0);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 2, 0);
    wifi_lobby_map_0226138C(param0->unk_00, 1);
}

static void wifi_lobby_map_02262AE0(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_02261220(param1, param0->unk_00, 0);
    wifi_lobby_map_02261220(param1, param0->unk_00, 1);
    wifi_lobby_map_02261220(param1, param0->unk_00, 2);
    wifi_lobby_map_0226138C(param0->unk_00, 0);
    wifi_lobby_map_022613E0(param0->unk_00);
    wifi_lobby_map_022613E8(param0->unk_00, FX32_ONE, FX32_ONE, FX32_ONE);
}

static void wifi_lobby_map_02262B24(WiFiLobbyMapObjectAnimController *param0)
{
    param0->unk_06 = 0;
}

static BOOL wifi_lobby_map_02262B2C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    if (param0->unk_06 < 10) {
        param0->unk_06++;

        {
            fx32 v0;
            fx32 v1;

            v0 = param0->unk_08 - 0;
            v1 = FX_Mul(param0->unk_06 << FX32_SHIFT, v0);
            v1 = FX_Div(v1, 10 << FX32_SHIFT);
            v1 += param0->unk_08;

            wifi_lobby_map_022613C0(param0->unk_00, v1);
        }

        {
            u32 v2;

            v2 = (param0->unk_06 * 31) / 10;
            v2 = 31 - v2;

            wifi_lobby_map_022613C8(param0->unk_00, v2, 31);
        }

        {
            fx32 v3;

            v3 = FX_Mul(param0->unk_06 << FX32_SHIFT, (FX32_CONST(0.180f)));
            v3 = FX_Div(v3, 10 << FX32_SHIFT);
            v3 = FX32_ONE + v3;

            wifi_lobby_map_022613E8(param0->unk_00, v3, v3, v3);
        }

        return 0;
    }

    return 1;
}

static void wifi_lobby_map_02262BD0(WiFiLobbyMapObjectAnimController *param0, fx32 param1)
{
    if ((param0->unk_04 == 1) || (param0->unk_04 == 2)) {
        return;
    }

    param0->unk_04 = 1;
    param0->unk_08 = param1;
}

static void wifi_lobby_map_02262BEC(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->unk_04) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262C64(param0, param1);
        param0->unk_04 = 2;
        break;
    case 2:
        if (wifi_lobby_map_022612B4(param1, param0->unk_00, 0) == 0) {
            param0->unk_04 = 3;
        }
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->unk_04 = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_0226138C(param0->unk_00, 0);
            wifi_lobby_map_022613E0(param0->unk_00);
            wifi_lobby_map_022613E8(param0->unk_00, FX32_ONE, FX32_ONE, FX32_ONE);

            param0->unk_04 = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void wifi_lobby_map_02262C64(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->unk_00, param0->unk_08);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 0, 1);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 1, 1);
    wifi_lobby_map_0226138C(param0->unk_00, 1);
}

static void wifi_lobby_map_02262C94(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    switch (param0->unk_04) {
    case 0:
        break;
    case 1:
        wifi_lobby_map_02262D0C(param0, param1);
        param0->unk_04 = 2;
        break;
    case 2:
        if (wifi_lobby_map_022612B4(param1, param0->unk_00, 0) == 0) {
            param0->unk_04 = 3;
        }
        break;
    case 3:
        wifi_lobby_map_02262B24(param0);
        param0->unk_04 = 4;
        break;
    case 4:
        if (wifi_lobby_map_02262B2C(param0, param1) == 1) {
            wifi_lobby_map_0226138C(param0->unk_00, 0);
            wifi_lobby_map_022613E0(param0->unk_00);
            wifi_lobby_map_022613E8(param0->unk_00, FX32_ONE, FX32_ONE, FX32_ONE);
            param0->unk_04 = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
}

static void wifi_lobby_map_02262D0C(WiFiLobbyMapObjectAnimController *param0, WiFiLobbyMapModelManager *param1)
{
    wifi_lobby_map_022613C0(param0->unk_00, param0->unk_08);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 0, 1);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 1, 1);
    wifi_lobby_map_0226110C(param1, param0->unk_00, 2, 1);
    wifi_lobby_map_0226138C(param0->unk_00, 1);
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
