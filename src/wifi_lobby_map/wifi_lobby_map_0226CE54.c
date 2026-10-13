#include "wifi_lobby_map/wifi_lobby_map_0226CE54.h"

#include <nitro.h>
#include <string.h>

#include "generated/species.h"

#include "wifi_2d_char/struct_wifi_2d_char_0222CC3C.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_lobby_map/wifi_lobby_map_0225C858.h"
#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"
#include "wifi_lobby_map/wifi_lobby_map_02261E10.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_grid_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_app_decl.h"
#include "wifi_lobby_map/struct_wifi_lobby_map_object_manager_decl.h"

#include "heap.h"
#include "math_util.h"
#include "sound_playback.h"

typedef struct {
    u16 active;
    u16 variant;
    union {
        struct {
            s16 frame;
            s16 duration;
            u16 amplitudeX;
            s16 amplitudeY;
            s16 cycles;
        } val1;
    } unk_04;
} WiFiLobbyMapFloatAnimation;

typedef struct WiFiLobbyMapFloatManager_t {
    WiFiLobbyMapApp *app;
    WiFiPlazaLobbyState *lobbyState;
    WiFiLobbyMapObjectManager *objectManager;
    WiFiLobbyMapGrid *grid;
    u8 flags[9][3];
    u8 unk_2B;
    WiFiLobbyMapFloatAnimation animations[9];
    WiFi2DCharPosition slotPositions[3];
    u16 unk_B6;
    u16 unk_B8;
    fx32 floatHeight;
    fx32 floatRange;
} WiFiLobbyMapFloatManager;

typedef struct {
    u16 species;
    u16 alternateSpecies;
    u16 midSound;
    u16 endSound;
    u16 midSoundAlt;
    u16 endSoundAlt;
} WiFiLobbyMapFloatConfig;

static void wifi_lobby_map_0226D020(WiFiLobbyMapFloatManager *param0, u32 param1);
static void wifi_lobby_map_0226D46C(WiFiLobbyMapFloatManager *param0, u32 param1);
static void wifi_lobby_map_0226D0E8(WiFiLobbyMapFloatManager *param0, u32 param1, BOOL param2, BOOL param3, u32 param4);
static void wifi_lobby_map_0226D24C(BOOL param0, BOOL param1, BOOL param2, u32 seqID);
static void wifi_lobby_map_0226D27C(BOOL param0, BOOL param1, BOOL param2, u32 species);
static BOOL wifi_lobby_map_0226D2A0(WiFiLobbyMapFloatAnimation *param0, u32 param1, WiFiLobbyMapObjectManager *param2, u32 param3);
static BOOL wifi_lobby_map_0226D2D8(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2);
static void wifi_lobby_map_0226D31C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2);
static void wifi_lobby_map_0226D33C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2);
static BOOL wifi_lobby_map_0226D35C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2);

static const WiFiLobbyMapFloatConfig Unk_wifi_lobby_map_0226E774[5] = {
    {
        .species = SPECIES_TORCHIC,
        .alternateSpecies = SPECIES_CHARIZARD,
        .midSound = 0xFFFE,
        .endSound = SEQ_SE_PL_FLOAT10_sseq,
        .midSoundAlt = SEQ_SE_PL_FIRE_sseq,
        .endSoundAlt = SEQ_SE_PL_FLOAT03_sseq,
    },
    {
        .species = SPECIES_PIPLUP,
        .alternateSpecies = SPECIES_GYARADOS,
        .midSound = SEQ_SE_PL_FLOAT10_sseq,
        .endSound = SEQ_SE_PL_FLOAT12_sseq,
        .midSoundAlt = SEQ_SE_PL_WATER_sseq,
        .endSoundAlt = SEQ_SE_PL_FLOAT10_sseq,
    },
    {
        .species = SPECIES_PIKACHU,
        .alternateSpecies = SPECIES_MAGNEZONE,
        .midSound = 0xFFFE,
        .endSound = SEQ_SE_PL_FLOAT10_sseq,
        .midSoundAlt = 0xFFFE,
        .endSoundAlt = SEQ_SE_PL_ELECTRO_sseq,
    },
    {
        .species = SPECIES_BULBASAUR,
        .alternateSpecies = SPECIES_CARNIVINE,
        .midSound = SEQ_SE_PL_WHIP_sseq,
        .endSound = SEQ_SE_PL_FLOAT11_sseq,
        .midSoundAlt = SEQ_SE_PL_FLOAT03_sseq,
        .endSoundAlt = SEQ_SE_PL_FLOAT10_sseq,
    },
    {
        .species = SPECIES_MEW,
        .alternateSpecies = SPECIES_MEW,
        .midSound = 0xFFFE,
        .endSound = SEQ_SE_PL_FLOAT10_sseq,
        .midSoundAlt = SEQ_SE_PL_KIRAKIRA4_sseq,
        .endSoundAlt = SEQ_SE_PL_FLOAT10_sseq,
    },
};

WiFiLobbyMapFloatManager *wifi_lobby_map_0226CE54(WiFiLobbyMapApp *param0, enum HeapID heapID)
{
    WiFiLobbyMapFloatManager *v0;
    int v1;
    u16 v2, v3;
    static const u8 v4[3] = {
        63,
        62,
        61,
    };

    v0 = Heap_Alloc(heapID, sizeof(WiFiLobbyMapFloatManager));
    memset(v0, 0, sizeof(WiFiLobbyMapFloatManager));

    v0->app = param0;
    v0->lobbyState = wifi_lobby_map_0225DEE8(param0);
    v0->objectManager = wifi_lobby_map_0225DEF8(param0);
    v0->grid = wifi_lobby_map_0225DF00(param0);
    v0->floatHeight = wifi_lobby_map_0225C8A8(v0->grid) + 6;
    v0->floatRange = -8 - v0->floatHeight;
    v0->floatHeight = (v0->floatHeight) * 16 * (FX32_ONE);
    v0->floatRange = (v0->floatRange) * 16 * (FX32_ONE);

    for (v1 = 0; v1 < 3; v1++) {
        wifi_lobby_map_0225C8D8(v0->grid, v4[v1], &v2, &v3, 0);
        v0->slotPositions[v1].x = (v2) * 16;
        v0->slotPositions[v1].y = (v3) * 16;
    }

    for (v1 = 0; v1 < 9; v1++) {
        wifi_lobby_map_022622B0(v0->objectManager, v1, v0->floatHeight);

        if (WiFiPlazaLobby_State_GetFloatState(v0->lobbyState, v1) == 1) {
            wifi_lobby_map_0226D020(v0, v1);
            wifi_lobby_map_0226D46C(v0, v1);
        }
    }

    return v0;
}

void wifi_lobby_map_0226CF38(WiFiLobbyMapFloatManager *param0)
{
    Heap_Free(param0);
}

void wifi_lobby_map_0226CF40(WiFiLobbyMapFloatManager *param0)
{
    int v0;
    BOOL v1;
    u32 v2;
    u32 v3;
    u32 v4;
    BOOL v5;
    BOOL v6;

    v4 = WiFiPlazaLobby_State_GetMySlotIndex(param0->lobbyState);
    v2 = WiFiPlazaLobby_State_FindFloatSlotByUserID(param0->lobbyState, v4);

    if (v2 == 0xffffffff) {
        v5 = 0;
    } else {
        WiFiPlazaLobby_State_FloatSlotToRowCol(v2, &v2, &v3);
        v5 = 1;
    }

    for (v0 = 0; v0 < 9; v0++) {
        if (WiFiPlazaLobby_State_GetFloatState(param0->lobbyState, v0) == 1) {
            wifi_lobby_map_022623C4(param0->objectManager, v0, 1);
            wifi_lobby_map_0226D020(param0, v0);
            wifi_lobby_map_0226D46C(param0, v0);

            if (v5) {
                if (v2 == v0) {
                    v6 = 1;
                } else {
                    v6 = 0;
                }
            }

            wifi_lobby_map_0226D0E8(param0, v0, v5, v6, v3);
        } else {
            wifi_lobby_map_022623C4(param0->objectManager, v0, 0);
        }
    }

    for (v0 = 0; v0 < 9; v0++) {
        v1 = wifi_lobby_map_0226241C(param0->objectManager, v0);
        param0->flags[v0][0] = v1;

        v1 = wifi_lobby_map_0226D2D8(&param0->animations[v0], param0->objectManager, v0);
        param0->flags[v0][1] = v1;

        v1 = wifi_lobby_map_02262444(param0->objectManager, v0);
        param0->flags[v0][2] = v1;
    }
}

BOOL wifi_lobby_map_0226CFFC(const WiFiLobbyMapFloatManager *param0, u32 param1, int param2)
{
    GF_ASSERT(param1 < 9);
    GF_ASSERT(param2 < 3);
    return param0->flags[param1][param2];
}

static void wifi_lobby_map_0226D020(WiFiLobbyMapFloatManager *param0, u32 param1)
{
    s32 v0;
    s32 v1;
    fx32 v2;
    fx32 v3;

    v0 = WiFiPlazaLobby_State_GetFloatTimer(param0->lobbyState, param1);
    v1 = WiFiPlazaLobby_State_GetFloatTimerMax(param0->lobbyState);
    v3 = FX_Div(param0->floatRange, FX32_CONST(2));
    v2 = FX_Div(FX_Mul(FX32_CONST(v0), v3), FX32_CONST(v1));
    v2 = FX_Mul(v2, FX32_CONST(2));
    v2 += param0->floatHeight;

    wifi_lobby_map_022622B0(param0->objectManager, param1, v2);
}

static void wifi_lobby_map_0226D0E8(WiFiLobbyMapFloatManager *param0, u32 param1, BOOL param2, BOOL param3, u32 param4)
{
    int v0;
    BOOL v1;
    BOOL v2 = 0;
    u32 v3;
    u32 v4;
    BOOL v5;

    v4 = WiFiPlazaLobby_State_GetLobbyRoomType(param0->lobbyState);
    v3 = WiFiPlazaLobby_State_GetLobbySeason(param0->lobbyState);

    for (v0 = 0; v0 < 3; v0++) {
        v1 = WiFiPlazaLobby_State_IsFloatSlotTriggered(param0->lobbyState, (param1 * 3) + v0);
        v5 = 0;

        if (param3 == 1) {
            if (v0 == param4) {
                v5 = 1;
            }
        }

        if (v1 == 1) {
            switch (v0) {
            case 0:
                v2 = wifi_lobby_map_02262374(param0->objectManager, param1);

                if (v2 == 1) {
                    if ((param1 % 3) == 2) {
                        wifi_lobby_map_0226D27C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].alternateSpecies);

                        if (Unk_wifi_lobby_map_0226E774[v4].midSoundAlt != 0xfffe) {
                            wifi_lobby_map_0226D24C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].midSoundAlt);
                        }
                    } else {
                        wifi_lobby_map_0226D27C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].species);

                        if (Unk_wifi_lobby_map_0226E774[v4].midSound != 0xfffe) {
                            wifi_lobby_map_0226D24C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].midSound);
                        }
                    }

                    WiFiPlazaLobby_State_ClearFloatSlotTrigger(param0->lobbyState, (param1 * 3) + v0);
                }
                break;
            case 1: {
                u32 v6;

                if ((param1 % 3) == 2) {
                    v6 = 1;
                } else {
                    v6 = 0;
                }

                v2 = wifi_lobby_map_0226D2A0(&param0->animations[param1], v6, param0->objectManager, param1);

                if (v2 == 1) {
                    WiFiPlazaLobby_State_ClearFloatSlotTrigger(param0->lobbyState, (param1 * 3) + v0);
                    wifi_lobby_map_0226D24C(param2, param3, v5, SEQ_SE_PL_FLOAT13_sseq);
                }
            } break;
            case 2:
                v2 = wifi_lobby_map_0226239C(param0->objectManager, param1);

                if (v2 == 1) {
                    WiFiPlazaLobby_State_ClearFloatSlotTrigger(param0->lobbyState, (param1 * 3) + v0);

                    if ((param1 % 3) == 2) {
                        wifi_lobby_map_0226D24C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].endSoundAlt);
                    } else {
                        wifi_lobby_map_0226D24C(param2, param3, v5, Unk_wifi_lobby_map_0226E774[v4].endSound);
                    }
                }
                break;
            }
        }
    }
}

static void wifi_lobby_map_0226D24C(BOOL param0, BOOL param1, BOOL param2, u32 seqID)
{
    if (param0) {
        if (param1) {
            if (param2) {
                Sound_PlayEffectOnPlayer(seqID, 5);
            } else {
                Sound_PlayEffect(seqID);
            }
        }
    } else {
        Sound_PlayEffect(seqID);
    }
}

static void wifi_lobby_map_0226D27C(BOOL param0, BOOL param1, BOOL param2, u32 species)
{
    if (param0) {
        if (param1) {
            Sound_PlayPokemonCry(species, 0);
        }
    } else {
        Sound_PlayPokemonCry(species, 0);
    }
}

static BOOL wifi_lobby_map_0226D2A0(WiFiLobbyMapFloatAnimation *param0, u32 param1, WiFiLobbyMapObjectManager *param2, u32 param3)
{
    static void (*const v0[])(WiFiLobbyMapFloatAnimation *, WiFiLobbyMapObjectManager *, u32) = {
        wifi_lobby_map_0226D31C,
        wifi_lobby_map_0226D33C
    };
    GF_ASSERT(param1 < 2);

    if (param0->active == 1) {
        return 0;
    }

    param0->variant = param1;
    param0->active = 1;
    v0[param1](param0, param2, param3);

    return 1;
}

static BOOL wifi_lobby_map_0226D2D8(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2)
{
    BOOL v0;

    static BOOL (*const v1[])(WiFiLobbyMapFloatAnimation *, WiFiLobbyMapObjectManager *, u32) = {
        wifi_lobby_map_0226D35C,
        wifi_lobby_map_0226D35C
    };

    if (param0->active) {
        v0 = v1[param0->variant](param0, param1, param2);

        if (v0 == 1) {
            memset(param0, 0, sizeof(WiFiLobbyMapFloatAnimation));
        }

        return 1;
    }

    return 0;
}

static void wifi_lobby_map_0226D31C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2)
{
    param0->unk_04.val1.frame = 0;
    param0->unk_04.val1.duration = 8;
    param0->unk_04.val1.amplitudeX = (CalcAngleRotationIdx_Wraparound(5));
    param0->unk_04.val1.amplitudeY = 2;
    param0->unk_04.val1.cycles = 4;
}

static void wifi_lobby_map_0226D33C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2)
{
    param0->unk_04.val1.frame = 0;
    param0->unk_04.val1.duration = 16;
    param0->unk_04.val1.amplitudeX = (CalcAngleRotationIdx_Wraparound(10));
    param0->unk_04.val1.amplitudeY = 4;
    param0->unk_04.val1.cycles = 2;
}

static BOOL wifi_lobby_map_0226D35C(WiFiLobbyMapFloatAnimation *param0, WiFiLobbyMapObjectManager *param1, u32 param2)
{
    VecFx32 v0 = { 0 };
    u16 v1;
    u16 v2;
    BOOL v3 = 0;

    if ((param0->unk_04.val1.frame + 1) < param0->unk_04.val1.duration) {
        param0->unk_04.val1.frame++;
    } else {
        param0->unk_04.val1.frame = 0;

        if ((param0->unk_04.val1.cycles - 1) > 0) {
            param0->unk_04.val1.cycles--;
        } else {
            v3 = 1;
        }
    }

    v2 = (param0->unk_04.val1.frame * 0xffff) / param0->unk_04.val1.duration;
    v1 = FX_Mul(FX_SinIdx(v2), FX32_CONST(param0->unk_04.val1.amplitudeX)) >> FX32_SHIFT;

    v0.y = FX_Mul(FX_SinIdx(v2), FX32_CONST(param0->unk_04.val1.amplitudeY));

    wifi_lobby_map_022623F0(param1, param2, v1);
    wifi_lobby_map_022622EC(param1, param2, &v0);

    return v3;
}

static void wifi_lobby_map_0226D46C(WiFiLobbyMapFloatManager *param0, u32 param1)
{
    int v0, v1;
    u32 v2;
    u32 v3;
    VecFx32 v4;
    fx32 v5;

    for (v0 = 0; v0 < 3; v0++) {
        v2 = (param1 * 3) + v0;
        v3 = WiFiPlazaLobby_State_GetFloatSlotPosition(param0->lobbyState, v2);

        wifi_lobby_map_02262318(param0->objectManager, param1, v0, &v4);

        for (v1 = v3; v1 < 3; v1++) {
            v5 = ((param0->slotPositions[v1].x + 16) * (FX32_ONE));

            if (v5 > v4.x) {
                WiFiPlazaLobby_State_SetFloatSlotPosition(param0->lobbyState, v2, v1);
            }
        }
    }
}
