#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02262A8C.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02261870.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_0226432C.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02260490.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262CB8.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262D08.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262DC0.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"

#include "communication_system.h"
#include "easy3d_object.h"
#include "heap.h"
#include "inlines.h"
#include "math_util.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "touch_screen.h"

static const s16 sUnusedData2[] = {
    -2,
    -2,
    -1,
    -1,
    -1,
    -1,
    0xEE,
    0x2,
    0x2,
    0x2,
    0x2,
    0x4,
    0x4,
    0x4,
    0x4,
    0x6,
    0x6,
    0x6,
    0x6,
    0xFF
};

static const s16 sUnusedData3[] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0xEE,
    0x0,
    0x0,
    0x4,
    0x4,
    0x4,
    0x4,
    0x4,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0xFF
};

static const s16 sUnusedData1[] = {
    -2,
    -2,
    -2,
    -2,
    -1,
    -1,
    0x3,
    0x3,
    0x4,
    0x4,
    0x6,
    0x6,
    0x7,
    0x7,
    0x8,
    0x8
};

static const s16 sLevelUpAnimationFrames[] = {
    -3,
    -3,
    -2,
    -2,
    -1,
    -1,
    0xEE,
    0x1,
    0x1,
    0x2,
    0x2,
    0x3,
    0x3,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0xFF
};

typedef struct {
    int unk_00;
    int unk_04;
} WiFiLobbyMinigameManeneRandomWeight;

static void StartPlayerFallTask(WiFiLobbyMinigameManeneGame *param0, int param1);
static void StartPlayerEffectTask(WiFiLobbyMinigameManeneGame *param0, int param1);
static void StartPlayerLevelUpTask(WiFiLobbyMinigameManeneGame *param0, int param1);
static void StartBallBounceTask(WiFiLobbyMinigameManeneGame *param0);
static void PlayerEffectTask(SysTask *param0, void *param1);
static void PlayerLevelUpTask(SysTask *param0, void *param1);
static void AddScore(WiFiLobbyMinigameManeneGame *param0);
static void AddBonusScore(WiFiLobbyMinigameManeneGame *param0);
static BOOL UpdateLevel(WiFiLobbyMinigameManeneGame *param0);
static BOOL CheckLevelChange(WiFiLobbyMinigameManeneGame *param0, int param1, int *param2);
static void UpdateOtherPlayers(WiFiLobbyMinigameManeneGame *param0);
static void UpdateLocalPlayer(WiFiLobbyMinigameManeneGame *param0);
static inline u32 Random(void);
static inline s8 RandomSign(void);
static inline s8 Sign(s16 val);
void IncludeUnusedData1(void);
void IncludeUnusedData2(void);
void IncludeUnusedData3(void);
void IncludeLevelUpAnimationFrames(void);

static const int sPlayerModelIds[][2] = {
    { 0x1F, 0x20 },
    { 0x21, 0x22 },
    { 0x23, 0x24 },
    { 0x25, 0x26 },
    { 0x25, 0x26 }
};

static const int sPlayerAnimIds[][2] = {
    { 0x27, 0x28 },
    { 0x29, 0x2A },
    { 0x29, 0x2A }
};

void IncludeUnusedData1(void)
{
    sUnusedData1[0];
}

void IncludeUnusedData2(void)
{
    sUnusedData2[0];
}

void IncludeUnusedData3(void)
{
    sUnusedData3[0];
}

void IncludeLevelUpAnimationFrames(void)
{
    sLevelUpAnimationFrames[0];
}

WiFiLobbyMinigameManeneGame *WiFiLobbyMinigameManene_CreateGame(int param0, u32 param1, WiFiLobbyMinigameManeneResources *param2)
{
    WiFiLobbyMinigameManeneGame *v0 = Heap_Alloc(HEAP_ID_106, sizeof(WiFiLobbyMinigameManeneGame));

    memset(v0, 0, sizeof(WiFiLobbyMinigameManeneGame));

    v0->unk_04 = param0;
    v0->unk_00 = param1;
    v0->unk_08 = 0;
    v0->unk_0C = 0;
    v0->unk_14 = param2;
    v0->unk_2874 = 0;

    {
        v0->unk_20C4.unk_00 = v0->unk_279C.unk_0C;
        v0->unk_20C4.unk_04 = &v0->unk_279C.unk_0C;
    }

    v0->unk_279C.unk_B4 = 0;
    WiFiLobbyMinigameManene_ResetGame(v0);

    return v0;
}

void WiFiLobbyMinigameManene_ResetGame(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    param0->unk_1FB0.x = 0;
    param0->unk_1FB0.y = (FX32_CONST(100));
    param0->unk_1FB0.z = 0;
    param0->unk_308[0].unk_1FC = 0.0f;
    param0->unk_308[0].unk_200 = 0.0f;
    param0->unk_FC.unk_1FC = 0.0f;
    param0->unk_FC.unk_200 = 0.0f;
    param0->unk_308[0].unk_1F8 = 0;
    param0->unk_FC.unk_1F8 = 0;

    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_FC.unk_190);
    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_FC.unk_1A0);
    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_308[0].unk_190);
    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_308[0].unk_1A0);
    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_92C.unk_190);
    WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_92C.unk_1A0);

    for (v0 = 0; v0 < 8; v0++) {
        WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_B38[v0].unk_190);
        WiFiLobbyMinigameManene_QuaternionIdentity(&param0->unk_B38[v0].unk_1A0);
        WiFiLobbyMinigameManene_TiltBall(&param0->unk_B38[v0], 0, 0, +5, +5, (0.80), 0);
        WiFiLobbyMinigameManene_TiltBall(&param0->unk_B38[v0], 0, 0, -5, -5, (0.80), 0);
    }

    WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, 0, 0, +5, +5, (2.35 * 0.80), 0);
    WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, 0, 0, -5, -5, (2.35 * 0.80), 0);
    WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], 0, 0, +5, +5, (0.80), 0);
    WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], 0, 0, -5, -5, (0.80), 0);
    WiFiLobbyMinigameManene_TiltBall(&param0->unk_92C, 0, 0, +5, +5, (2.35 * 0.80), 0);
    WiFiLobbyMinigameManene_TiltBall(&param0->unk_92C, 0, 0, -5, -5, (0.80), 0);
}

void WiFiLobbyMinigameManene_FreeGame(WiFiLobbyMinigameManeneGame *param0)
{
    Heap_Free(param0);
}

BOOL WiFiLobbyMinigameManene_IsBallLowEnough(WiFiLobbyMinigameManeneGame *param0, int *param1)
{
    int v0;
    int v1;

    v0 = param0->unk_1FB0.y >> FX32_SHIFT;
    v1 = (FX32_CONST(45)) >> FX32_SHIFT;

    if (v0 <= v1) {
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameManene_UpdateBallAnimByHeight(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1;
    int v2;

    v0 = param0->unk_1FB0.y >> FX32_SHIFT;
    v1 = (FX32_CONST(75)) >> FX32_SHIFT;
    v2 = (FX32_CONST(61)) >> FX32_SHIFT;

    if ((v0 < v1) && (v0 > v2)) {
        WiFiLobbyMinigameManene_SetBallAnim(param0, 1);
        return;
    }

    v1 = (FX32_CONST(60)) >> FX32_SHIFT;
    v2 = (FX32_CONST(46)) >> FX32_SHIFT;

    if ((v0 < v1) && (v0 > v2)) {
        WiFiLobbyMinigameManene_SetBallAnim(param0, 2);
        return;
    }

    WiFiLobbyMinigameManene_SetBallAnim(param0, 0);
}

static void StartPlayerFallTask(WiFiLobbyMinigameManeneGame *param0, int param1)
{
    WiFiLobbyMinigameManenePlayerFall *v0 = Heap_Alloc(HEAP_ID_106, sizeof(WiFiLobbyMinigameManenePlayerFall));

    memset(v0, 0, sizeof(WiFiLobbyMinigameManenePlayerFall));

    v0->unk_0C = param0->unk_1C[param0->unk_DC[param1]];
    v0->unk_10 = param0->unk_20[param0->unk_DC[param1]];
    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_2C = param0->unk_14;

    SysTask_Start(WiFiLobbyMinigameManene_PlayerFallTask, v0, 4096);
}

static void StartPlayerEffectTask(WiFiLobbyMinigameManeneGame *param0, int param1)
{
    WiFiLobbyMinigameManenePlayerEffect *v0 = &param0->unk_268C[param1];

    if (v0->unk_30 == 1) {
        return;
    }

    v0->unk_40 = param0->unk_2870;
    v0->unk_30 = 1;
    v0->unk_2C = &param0->unk_279C.unk_28[param1];
    v0->unk_28 = *v0->unk_2C;
    v0->unk_0C = param0->unk_24[param0->unk_DC[param1]];
    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_3C = param0->unk_14;

    SysTask_Start(PlayerEffectTask, v0, 4096);
}

static void StartPlayerLevelUpTask(WiFiLobbyMinigameManeneGame *param0, int param1)
{
    WiFiLobbyMinigameManenePlayerEffect *v0 = &param0->unk_268C[param1];

    if (v0->unk_30 == 1) {
        return;
    }

    v0->unk_40 = param0->unk_2870;
    v0->unk_30 = 1;
    v0->unk_2C = &param0->unk_279C.unk_0C;
    v0->unk_28 = *v0->unk_2C;
    v0->unk_34 = &param0->unk_1B98;
    v0->unk_38 = &param0->unk_1DA4;
    v0->unk_00 = 0;
    v0->unk_04 = 0;
    v0->unk_3C = param0->unk_14;

    SysTask_Start(PlayerLevelUpTask, v0, 4096);
}

static void StartBallBounceTask(WiFiLobbyMinigameManeneGame *param0)
{
    WiFiLobbyMinigameManeneBallBounce *v0 = Heap_Alloc(HEAP_ID_106, sizeof(WiFiLobbyMinigameManeneBallBounce));

    memset(v0, 0, sizeof(WiFiLobbyMinigameManeneBallBounce));

    v0->unk_0C = &param0->unk_F8;
    v0->unk_10 = &param0->unk_308[0];
    v0->unk_14 = &param0->unk_FC;
    v0->unk_20 = param0->unk_1FB0;
    v0->unk_74 = param0->unk_2870;
    v0->unk_78 = param0->unk_14;

    WiFiLobbyMinigameManene_SetBallAnim(param0, 0);

    Easy3DAnim_SetFrame(&param0->unk_308[0].unk_88[0], 0);
    Easy3DAnim_SetFrame(&param0->unk_308[1].unk_88[0], 0);
    Easy3DAnim_SetFrame(&param0->unk_308[2].unk_88[0], 0);
    SysTask_Start(WiFiLobbyMinigameManene_BallBounceTask, v0, 4096);
}

void WiFiLobbyMinigameManene_BallBounceTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManeneBallBounce *v0 = param1;
    s16 v1;
    s16 v2;
    s16 v3 = v0->unk_10->unk_1E0.y >> FX32_SHIFT;
    s16 v4 = v0->unk_10->unk_1E0.z >> FX32_SHIFT;
    s16 v5 = v0->unk_20.z >> FX32_SHIFT;
    fx32 v6;
    fx32 v7;
    fx32 v8;

    if (v0->unk_74) {
        v6 = FX32_CONST(16);
        v7 = FX32_CONST(12);
        v8 = FX32_CONST(48);
    } else {
        v6 = FX32_CONST(16);
        v7 = FX32_CONST(12);
        v8 = FX32_CONST(48);
    }

    if ((IsScreenFadeDone() == FALSE) || (v0->unk_78->unk_2C.unk_00 == 1)) {
        SysTask_Done(param0);
        Heap_Free(v0);
        return;
    }

    switch (v0->unk_00) {
    case 0:
        if (v0->unk_04 == 0) {
            WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_44, v0->unk_10->unk_1E0.y, v0->unk_10->unk_1E0.y + v7, 4);

            if (v5 > 0) {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z + v6, 4);
            } else {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z - v6, 4);
            }
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_44, v0->unk_10->unk_1E0.y, v0->unk_10->unk_1E0.y + v8, 8);

            if (v5 > 0) {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z - v6, 8);
            } else {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z + v6, 4);
            }
        }

        Sound_PlayEffect(SEQ_SE_DP_DANSA_sseq);

        v0->unk_08 = 0;
        v0->unk_00++;
        break;
    case 1: {
        BOOL v9[2];

        v9[0] = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_44);
        v9[1] = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_5C);
        v0->unk_10->unk_1E0.y = v0->unk_44.unk_00;
        v0->unk_10->unk_1E0.z = v0->unk_5C.unk_00;

        if (v9[0] && v9[1]) {
            if (v0->unk_04 == 0) {
                *v0->unk_0C = 1;
                WiFiLobbyMinigameManene_QuaternionIdentity(&v0->unk_10->unk_190);
                WiFiLobbyMinigameManene_QuaternionIdentity(&v0->unk_10->unk_1A0);
                WiFiLobbyMinigameManene_TiltBall(v0->unk_10, 0, 0, +5, +5, (0.80), 0);
                WiFiLobbyMinigameManene_TiltBall(v0->unk_10, 0, 0, -5, -5, (0.80), 0);
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_44, v0->unk_10->unk_1E0.y, v0->unk_10->unk_1E0.y - v8, 8);

                if (v5 > 0) {
                    WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z + v6, 8);
                } else {
                    WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z - v6, 8);
                }
            } else {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_44, v0->unk_10->unk_1E0.y, v0->unk_10->unk_1E0.y - v7, 4);

                if (v5 > 0) {
                    WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z - v6, 4);
                } else {
                    WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_5C, v0->unk_10->unk_1E0.z, v0->unk_10->unk_1E0.z + v6, 4);
                }
            }

            v0->unk_00++;
        }
    } break;
    case 2: {
        BOOL v10[2];

        v10[0] = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_44);
        v10[1] = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_5C);
        v0->unk_10->unk_1E0.y = v0->unk_44.unk_00;
        v0->unk_10->unk_1E0.z = v0->unk_5C.unk_00;

        if (v10[0] && v10[1]) {
            if (v0->unk_04 == 0) {
                Sound_PlayEffect(SEQ_SE_PL_SUTYA2_sseq_2);
            }
            v0->unk_00++;
        }
    } break;
    case 3:
        if (v0->unk_04 == 0) {
            if (v0->unk_08 == ((30 * 3) - 82)) {
                Sound_PlayEffect(SEQ_SE_PL_KIN_sseq);
            }

            if ((++v0->unk_08) >= ((30 * 3) - 50)) {
                *v0->unk_0C = 2;
                v0->unk_00++;
            }
        } else {
            v0->unk_00++;
        }
        break;
    default:
        if (v0->unk_04 == 0) {
            if ((++v0->unk_08) >= ((30 * 3) - 45)) {
                *v0->unk_0C = 0;
                Sound_PlayEffect(SEQ_SE_DP_DANSA_sseq);
                v0->unk_00 = 0;
                v0->unk_04++;
            }
        } else {
            if ((++v0->unk_08) >= 10) {
                if (v0->unk_74) {
                    v0->unk_10->unk_1E0.y = (-8 * FX32_ONE);
                } else {
                    v0->unk_10->unk_1E0.y = (-20 * FX32_ONE);
                }

                v0->unk_10->unk_1E0.z = (0 * FX32_ONE);
                SysTask_Done(param0);
                Heap_Free(v0);
            }
        }
        break;
    }
}

void WiFiLobbyMinigameManene_PlayerFallTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManenePlayerFall *v0 = param1;
    int v1 = ManagedSprite_GetAnimationFrame(v0->unk_0C);

    if ((IsScreenFadeDone() == FALSE) || (v0->unk_2C->unk_2C.unk_00 == 1)) {
        SysTask_Done(param0);
        Heap_Free(v0);
        return;
    }

    switch (v0->unk_00) {
    case 0: {
        fx32 v2, v3;
        fx32 v4;

        v0->unk_08 = 0;
        ManagedSprite_GetPositionFxXY(v0->unk_0C, &v2, &v3);

        if (v0->unk_04 == 0) {
            WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_14, v3, v3 + FX32_CONST(32), 16);
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_14, v3, v3 - FX32_CONST(32), 4);
        }

        v0->unk_00++;
    } break;
    case 1: {
        fx32 v5, v6;
        BOOL v7;

        v7 = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_14);
        ManagedSprite_GetPositionFxXY(v0->unk_0C, &v5, &v6);
        ManagedSprite_SetPositionFxXY(v0->unk_0C, v5, v0->unk_14.unk_00);

        if (v7) {
            v0->unk_00++;
        }
    } break;
    default:

        if (v0->unk_04 == 0) {
            if ((++v0->unk_08) >= 35) {
                v0->unk_04++;
                v0->unk_00 = 0;
            }
        } else {
            if ((++v0->unk_08) >= 10) {
                SysTask_Done(param0);
                Heap_Free(v0);
            }
        }
        break;
    }
}

static void PlayerEffectTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManenePlayerEffect *v0 = param1;

    if ((IsScreenFadeDone() == FALSE) || (v0->unk_3C->unk_2C.unk_00 == 1)) {
        v0->unk_30 = 0;
        SysTask_Done(param0);
        return;
    }

    switch (v0->unk_00) {
    case 0: {
        f32 v1, v2;

        ManagedSprite_SetAnim(v0->unk_0C, 7);
        ManagedSprite_SetPriority(v0->unk_0C, 0);
        ManagedSprite_SetAffineOverwriteMode(v0->unk_0C, AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_GetAffineScale(v0->unk_0C, &v1, &v2);
        WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_10, FX_F32_TO_FX32(v2), FX_F32_TO_FX32(2.0f), 2);

        {
            int v3 = (*v0->unk_2C) - 1;
            ManagedSprite_SetExplicitPaletteOffset(v0->unk_0C, v3);
        }

        v0->unk_00++;
    }
    case 1: {
        fx32 v4, v5;
        BOOL v6;

        v6 = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_10);
        ManagedSprite_SetAffineScale(v0->unk_0C, 1.0f, FX_FX32_TO_F32(v0->unk_10.unk_00));

        if (v6) {
            v0->unk_00++;
        }
    } break;
    case 2:
        WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_10, FX_F32_TO_FX32(2.0f), FX_F32_TO_FX32(0.4f), 4);
        v0->unk_00++;
    case 3: {
        fx32 v7, v8;
        BOOL v9;

        v9 = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_10);
        ManagedSprite_SetAffineScale(v0->unk_0C, 1.0f, FX_FX32_TO_F32(v0->unk_10.unk_00));

        if (v9) {
            v0->unk_00++;
        }
    } break;
    case 4:
        if (v0->unk_28 != *v0->unk_2C) {
            v0->unk_00 = 0;
        } else {
            if (v0->unk_04 == 0) {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_10, FX_F32_TO_FX32(0.4f), FX_F32_TO_FX32(0.8f), 2);
            } else {
                WiFiLobbyMinigameManene_InitLinearMotion(&v0->unk_10, FX_F32_TO_FX32(0.8f), FX_F32_TO_FX32(0.4f), 4);
            }

            v0->unk_00++;
        }

        v0->unk_28 = *v0->unk_2C;

        if (*v0->unk_2C == 0) {
            v0->unk_00 = 0xFF;
        }
        break;
    case 5: {
        BOOL v10 = WiFiLobbyMinigameManene_UpdateLinearMotion(&v0->unk_10);
        ManagedSprite_SetAffineScale(v0->unk_0C, 1.0f, FX_FX32_TO_F32(v0->unk_10.unk_00));

        if (v10) {
            v0->unk_00 = 4;
            v0->unk_04 ^= 1;
        }
    } break;
    default:
        ManagedSprite_SetAffineScale(v0->unk_0C, 1.0f, 1.0f);
        ManagedSprite_SetAnim(v0->unk_0C, 5);
        ManagedSprite_SetPriority(v0->unk_0C, AFFINE_OVERWRITE_MODE_DOUBLE);
        ManagedSprite_SetAffineOverwriteMode(v0->unk_0C, 0);

        v0->unk_30 = 0;

        SysTask_Done(param0);
        break;
    }
}

static void PlayerLevelUpTask(SysTask *param0, void *param1)
{
    int v0;
    WiFiLobbyMinigameManenePlayerEffect *v1 = param1;
    WiFiLobbyMinigameManene3DObject *v2 = v1->unk_34;
    WiFiLobbyMinigameManene3DObject *v3 = v1->unk_38;

    if ((IsScreenFadeDone() == FALSE) || (v1->unk_3C->unk_2C.unk_00 == 1)) {
        WiFiLobbyMinigameManene_Release3DModel(v2);
        WiFiLobbyMinigameManene_Release3DModel(v3);

        Easy3DAnim_Release(&v2->unk_88[0], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v2->unk_88[1], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v3->unk_88[0], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v3->unk_88[1], &v1->unk_3C->unk_24);

        v1->unk_30 = 0;

        SysTask_Done(param0);
        return;
    }

    v0 = (*v1->unk_2C) - 1;

    if ((v0 < 0) || (v0 > 4)) {
        v0 = 0;
    }

    switch (v1->unk_00) {
    case 0:
        WiFiLobbyMinigameManene_Load3DModel(v2, v1->unk_3C->unk_00, sPlayerModelIds[v0][0]);
        WiFiLobbyMinigameManene_Init3DObject(v2, v1->unk_40);
        v1->unk_00++;
        break;
    case 1:
        Easy3DAnim_LoadFrom(&v2->unk_88[0], &v2->unk_78, v1->unk_3C->unk_00, sPlayerAnimIds[0][0], 106, &v1->unk_3C->unk_24);
        Easy3DAnim_LoadFrom(&v2->unk_88[1], &v2->unk_78, v1->unk_3C->unk_00, sPlayerAnimIds[0][1], 106, &v1->unk_3C->unk_24);
        Easy3DObject_AddAnim(&v2->unk_00, &v2->unk_88[0]);
        Easy3DObject_AddAnim(&v2->unk_00, &v2->unk_88[1]);
        Easy3DAnim_SetFrame(&v2->unk_88[0], 0);
        Easy3DAnim_SetFrame(&v2->unk_88[1], 0);
        Easy3DObject_SetVisible(&v2->unk_00, 0);

        v2->unk_1EC = 0;

        WiFiLobbyMinigameManene_QuaternionIdentity(&v2->unk_190);
        WiFiLobbyMinigameManene_QuaternionIdentity(&v2->unk_1A0);
        WiFiLobbyMinigameManene_TiltBall(v2, 0, 0, +5, +5, (0.80), 0);
        WiFiLobbyMinigameManene_TiltBall(v2, 0, 0, -5, -5, (0.80), 0);

        v1->unk_00++;
        break;
    case 2:
        WiFiLobbyMinigameManene_Load3DModel(v3, v1->unk_3C->unk_00, sPlayerModelIds[v0][1]);
        WiFiLobbyMinigameManene_Init3DObject(v3, v1->unk_40);
        v1->unk_00++;
        break;
    case 3:

        Easy3DAnim_LoadFrom(&v3->unk_88[0], &v3->unk_78, v1->unk_3C->unk_00, sPlayerAnimIds[1][0], 106, &v1->unk_3C->unk_24);
        Easy3DAnim_LoadFrom(&v3->unk_88[1], &v3->unk_78, v1->unk_3C->unk_00, sPlayerAnimIds[1][1], 106, &v1->unk_3C->unk_24);
        Easy3DObject_AddAnim(&v3->unk_00, &v3->unk_88[0]);
        Easy3DObject_AddAnim(&v3->unk_00, &v3->unk_88[1]);
        Easy3DAnim_SetFrame(&v3->unk_88[0], 0);
        Easy3DAnim_SetFrame(&v3->unk_88[1], 0);
        Easy3DObject_SetVisible(&v3->unk_00, 1);

        v3->unk_1EC = 1;

        WiFiLobbyMinigameManene_QuaternionIdentity(&v3->unk_190);
        WiFiLobbyMinigameManene_QuaternionIdentity(&v3->unk_1A0);
        WiFiLobbyMinigameManene_TiltBall(v3, 0, 0, +5, +5, (0.80), 0);
        WiFiLobbyMinigameManene_TiltBall(v3, 0, 0, -5, -5, (0.80), 0);

        if (v1->unk_40) {
            Easy3DObject_SetPosition(&v2->unk_00, 0, (-8 * FX32_ONE), 0);
            Easy3DObject_SetPosition(&v3->unk_00, 0, (-8 * FX32_ONE), 0);
            v2->unk_1E0.y = (-8 * FX32_ONE);
            v3->unk_1E0.y = (-8 * FX32_ONE);
        }

        v1->unk_00++;
        break;
    case 4:
        if (v3->unk_1EC == 0) {
            Easy3DObject_SetVisible(&v2->unk_00, 1);
            Easy3DObject_SetVisible(&v3->unk_00, 0);
            v2->unk_1EC = 1;
            v1->unk_00++;
        }
        break;
    case 5:
        if (*v1->unk_2C == 0) {
            v1->unk_00 = 0xFF;
        } else if (v1->unk_28 != *v1->unk_2C) {
            WiFiLobbyMinigameManene_Release3DModel(v2);
            WiFiLobbyMinigameManene_Release3DModel(v3);
            Easy3DAnim_Release(&v2->unk_88[0], &v1->unk_3C->unk_24);
            Easy3DAnim_Release(&v2->unk_88[1], &v1->unk_3C->unk_24);
            Easy3DAnim_Release(&v3->unk_88[0], &v1->unk_3C->unk_24);
            Easy3DAnim_Release(&v3->unk_88[1], &v1->unk_3C->unk_24);
            v1->unk_00 = 0;
        }
        v1->unk_28 = *v1->unk_2C;
        break;
    default:
        WiFiLobbyMinigameManene_Release3DModel(v2);
        WiFiLobbyMinigameManene_Release3DModel(v3);

        Easy3DAnim_Release(&v2->unk_88[0], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v2->unk_88[1], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v3->unk_88[0], &v1->unk_3C->unk_24);
        Easy3DAnim_Release(&v3->unk_88[1], &v1->unk_3C->unk_24);

        v1->unk_30 = 0;
        SysTask_Done(param0);

        break;
    }
}

static void AddScore(WiFiLobbyMinigameManeneGame *param0)
{
    const u16 v0[] = { 0x1, 0x2, 0x3, 0x4 };
    param0->unk_279C.unk_10 += v0[param0->unk_279C.unk_0C];
}

static void AddBonusScore(WiFiLobbyMinigameManeneGame *param0)
{
    const u16 v0[] = { 700, 1400, 2100, 2800 };
    param0->unk_279C.unk_10 += v0[param0->unk_279C.unk_0C - 1];
}

static BOOL UpdateLevel(WiFiLobbyMinigameManeneGame *param0)
{
    switch (param0->unk_279C.unk_38) {
    case ((4 * 30) - 1):
        param0->unk_279C.unk_08 = 1;
        break;
    case ((9 * 30) - 1):
        param0->unk_279C.unk_08 = 2;
        break;
    case ((14 * 30) - 1):
        param0->unk_279C.unk_08 = 3;
        break;
    case ((19 * 30) - 1):
        param0->unk_279C.unk_08 = 4;
        break;
    case ((24 * 30) - 1):
        param0->unk_279C.unk_08 = 5;
        break;
    case 0:
        param0->unk_279C.unk_08 = 0;
        break;
    }

    return CheckLevelChange(param0, param0->unk_279C.unk_38, &param0->unk_279C.unk_0C);
}

static BOOL CheckLevelChange(WiFiLobbyMinigameManeneGame *param0, int param1, int *param2)
{
    switch (param1) {
    case ((30 * 10) - 1):
        *param2 = 1;
        return 1;
    case ((30 * 20) - 1):
        *param2 = 2;
        return 1;
    case ((30 * 30) - 1):
        *param2 = 3;
        return 1;
    case ((30 * 40) - 1):
        *param2 = 4;
        return 1;
    case 0:
        *param2 = 0;
        break;
    }

    return 0;
}

static void UpdateOtherPlayers(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1 = param0->unk_04;

    for (v0 = 0; v0 < v1; v0++) {
        if (v0 == param0->unk_00) {
            continue;
        }

        switch (param0->unk_2858[v0].state) {
        case 0:
            if (WiFiLobbyMinigameManene_GetPlayerSpriteAnim(param0, v0) != 1) {
                WiFiLobbyMinigameManene_SetPlayerSpriteAnim(param0, v0, 1);
            }

            if (CheckLevelChange(param0, param0->unk_279C.unk_20[v0], &param0->unk_279C.unk_28[v0])) {
                StartPlayerEffectTask(param0, v0);
            }

            param0->unk_279C.unk_20[v0]++;
            break;
        case 1:
            param0->unk_279C.unk_1E = 0;
            param0->unk_279C.unk_20[v0] = 0;
            param0->unk_279C.unk_28[v0] = 0;
            param0->unk_2018.unk_28 = 0;

            if (WiFiLobbyMinigameManene_GetPlayerSpriteAnim(param0, v0) != 3) {
                if (param0->unk_2874 == 0) {
                    WiFiLobbyMinigameManene_SetPlayerSpriteAnim(param0, v0, 3);
                    StartPlayerFallTask(param0, v0);
                    param0->unk_2874 = 1;
                }
            }
            break;
        case 2:
            param0->unk_2874 = 0;
            param0->unk_279C.unk_1E = 0;
            param0->unk_279C.unk_20[v0] = 0;
            param0->unk_279C.unk_28[v0] = 0;
            param0->unk_2858[v0].state = 0;
            break;
        }
    }
}

static void UpdateLocalPlayer(WiFiLobbyMinigameManeneGame *param0)
{
    switch (param0->unk_2858[param0->unk_00].state) {
    case 0:
        if (WiFiLobbyMinigameManene_IsBallLowEnough(param0, NULL)) {
            param0->unk_279C.unk_1C = 0;
            StartBallBounceTask(param0);
            WiFiLobbyMinigameManene_ResetRoundState(param0);
            param0->unk_2858[param0->unk_00].state = 1;

            CommSys_SendData(24, &param0->unk_2858[param0->unk_00], sizeof(WiFiLobbyMinigameManenePlayerState));

            param0->unk_279C.unk_38 = 0;
            param0->unk_279C.unk_1E = 0;
            param0->unk_2018.unk_28 = 0;
        } else {
            WiFiLobbyMinigameManene_UpdateBallAnimByHeight(param0);
            WiFiLobbyMinigameManene_HandleTouchInput(param0);
            WiFiLobbyMinigameManene_UpdateBallMovement(param0);
            AddScore(param0);
            param0->unk_279C.unk_20[param0->unk_00]++;
        }
        break;
    case 1:
        if ((++param0->unk_279C.unk_1C) >= (30 * 3)) {
            param0->unk_2858[param0->unk_00].state = 2;
        }

        param0->unk_279C.unk_38 = 0;
        param0->unk_279C.unk_1E = 0;
        param0->unk_279C.unk_20[param0->unk_00] = 0;
        break;
    case 2:
        if (param0->unk_279C.unk_1C != 0) {
            param0->unk_279C.unk_38 = 0;
            param0->unk_279C.unk_1E = 0;
            param0->unk_279C.unk_1C = 0;
            param0->unk_279C.unk_20[param0->unk_00] = 0;

            if (param0->unk_279C.unk_18 != param0->unk_279C.unk_14) {
                param0->unk_279C.unk_14 = param0->unk_279C.unk_18;
            }

            WiFiLobbyMinigameManene_ResetGame(param0);
            CommSys_SendData(24, &param0->unk_2858[param0->unk_00], sizeof(WiFiLobbyMinigameManenePlayerState));
        } else {
            param0->unk_2858[param0->unk_00].state = 0;
        }
        break;
    case 3:
        if ((++param0->unk_279C.unk_1C) >= NELEMS(sLevelUpAnimationFrames)) {
            param0->unk_279C.unk_1C = 0;
            WiFiLobbyMinigameManene_ResetGame(param0);
            param0->unk_2858[param0->unk_00].state = 0;
        }

        break;
    }
}

void WiFiLobbyMinigameManene_UpdateGame(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;
    int v1 = param0->unk_04;

    if (param0->unk_279C.unk_04 < ((30 * 40) - 0)) {
        UpdateLocalPlayer(param0);
        UpdateOtherPlayers(param0);

        if (UpdateLevel(param0) == 1) {
            if (param0->unk_2858[param0->unk_00].state == 0) {
                (void)0;
            }

            StartPlayerLevelUpTask(param0, param0->unk_00);
            AddBonusScore(param0);
            Sound_PlayEffect(SEQ_SE_PL_LV_UP_sseq);
        }

        WiFiLobbyMinigameManene_AdvanceLevelTimer(param0);

        param0->unk_279C.unk_38++;
        param0->unk_279C.unk_04++;
        param0->unk_279C.unk_1E++;
    }
}

static const TouchScreenHitTable sTouchHitTableSmall[] = {
    { TOUCHSCREEN_USE_CIRCLE, 0x80, 0x80, 0x30 },
    { TOUCHSCREEN_TABLE_TERMINATOR, 0x0, 0x0, 0x0 }
};

static const TouchScreenHitTable sTouchHitTableLarge[] = {
    { TOUCHSCREEN_USE_CIRCLE, 0x80, 0x80, 0x40 },
    { TOUCHSCREEN_TABLE_TERMINATOR, 0x0, 0x0, 0x0 }
};

void WiFiLobbyMinigameManene_HandleTouchInput(WiFiLobbyMinigameManeneGame *param0)
{
    {
        u32 v0, v1;
        s16 v2, v3;
        BOOL v4;
        BOOL v5 = TouchScreen_GetHoldState(&v0, &v1);
        TouchScreenHitTable *v6;
        int v7;

        param0->unk_279C.unk_A4 = 0;

        if (param0->unk_2870) {
            v7 = TouchScreen_CheckTouchedHitTableID(sTouchHitTableLarge, v0, v1);
        } else {
            v7 = TouchScreen_CheckTouchedHitTableID(sTouchHitTableSmall, v0, v1);
        }

        if (v7 == 0xffffffff) {
            param0->unk_1FBC.unk_00 = 0;
            param0->unk_1FBC.unk_04 = 0;

            if (param0->unk_FC.unk_1F8 != 0) {
                WiFiLobbyMinigameManene_DecayBallTilt(&param0->unk_FC, 1.0f);
                v4 = WiFiLobbyMinigameManene_DecayBallTilt(&param0->unk_308[0], 0.5f);

                if (v4 = 1) {
                    VecFx32 v8 = { 0, (FX32_CONST(100)), 0 };
                    VecFx32 v9;

                    MTX_MultVec43(&v8, &param0->unk_308[0].unk_1B0, &param0->unk_1FB0);
                    param0->unk_279C.unk_A4 = 1;
                }
            } else {
                param0->unk_FC.unk_1FC = 0.0f;
                param0->unk_FC.unk_200 = 0.0f;
                WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, (2.35 * 0.80), 0);
                WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, (0.22), 0);
            }
        } else {
            f32 v10 = ((100 - (param0->unk_1FB0.y >> FX32_SHIFT)) / 40);

            if ((param0->unk_1FB0.y >> FX32_SHIFT) >= 95) {
                v10 = 0.1f;
            }

            if (v10 >= (0.22)) {
                v10 = (0.22);
            } else {
                v10 = (0.22) - v10;
            }

            if (param0->unk_1FBC.unk_00 == 0) {
                param0->unk_1FBC.unk_00 = v0;
                param0->unk_1FBC.unk_04 = v1;
            }

            WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, v0, v1, param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, (2.50 * 0.80), 1);
            v4 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], v0, v1, param0->unk_1FBC.unk_00, param0->unk_1FBC.unk_04, v10, 1);

            if (v4 = 1) {
                VecFx32 v11 = { 0, (FX32_CONST(100)), 0 };
                VecFx32 v12;

                MTX_MultVec43(&v11, &param0->unk_308[0].unk_1B0, &param0->unk_1FB0);
                param0->unk_279C.unk_A4 = 1;

                if (param0->unk_279C.unk_B4 == 0) {
                    param0->unk_279C.unk_B4 = 1;
                }
            }

            if (v0 != 0) {
                if (Sound_IsEffectPlaying(1394) == 0) {
                    Sound_PlayEffect(SEQ_SE_PL_KIRAKIRA_sseq);
                }

                WiFiLobbyMinigameManene_SpawnSparkle(param0, v0, v1);
            }

            param0->unk_1FBC.unk_00 = v0;
            param0->unk_1FBC.unk_04 = v1;
        }
    }
}

static const WiFiLobbyMinigameManeneRandomWeight sRandomWeights[][4] = {
    {
        { 0x13, 0x2D },
        { 0x13, 0x2D },
        { 0x13, 0x5 },
        { 0x13, 0x5 },
    },
    {
        { 0x14, 0x1E },
        { 0x14, 0x32 },
        { 0x19, 0x14 },
        { 0x19, 0xA },
    },
    {
        { 0x14, 0x12 },
        { 0x1E, 0x28 },
        { 0x23, 0x1E },
        { 0x28, 0xC },
    },
    {
        { 0x14, 0xF },
        { 0x1E, 0x1E },
        { 0x23, 0x28 },
        { 0x2D, 0xF },
    },
};

static inline u32 Random(void)
{
    u32 v0 = LCRNG_GetSeed();
    u32 v1 = LCRNG_Next();
    LCRNG_SetSeed(v0);

    return v1;
}

static inline s8 RandomSign(void)
{
    if (LCRNG_Next() % 2) {
        return +1;
    } else {
        return -1;
    }
}

static inline s8 Sign(s16 param0)
{
    if (param0 >= 0) {
        return +1;
    } else {
        return -1;
    }
}

void WiFiLobbyMinigameManene_ResetRoundState(WiFiLobbyMinigameManeneGame *param0)
{
    param0->unk_279C.unk_40 = 0;
    param0->unk_279C.unk_00 = 0;
    param0->unk_279C.unk_A4 = 0;
    param0->unk_279C.unk_A8 = 0;
    param0->unk_279C.unk_AC = 0;
    param0->unk_279C.unk_B0 = 0;
    param0->unk_279C.unk_0C = 0;
}

void WiFiLobbyMinigameManene_AdvanceLevelTimer(WiFiLobbyMinigameManeneGame *param0)
{
    BOOL v0 = 1;

    if (param0->unk_279C.unk_1E < ((30 * 5) - 1)) {
        return;
    }

    if (param0->unk_279C.unk_14 == 8) {
        return;
    }

    param0->unk_279C.unk_18 = param0->unk_279C.unk_14;
    param0->unk_279C.unk_14++;
    param0->unk_279C.unk_1E = 0;
    param0->unk_2018.unk_28 = 1;
}

void WiFiLobbyMinigameManene_UpdateBallMovement(WiFiLobbyMinigameManeneGame *param0)
{
    BOOL v0;
    BOOL v1;
    BOOL v2;
    BOOL v3;
    fx32 v4;
    fx32 v5;
    s16 v6 = 0;
    s16 v7 = 0;
    s16 v8[] = { (30 * 4), (30 * 3), (30 * 2), (30 * 1.5) };

    param0->unk_279C.unk_00++;

    if (param0->unk_279C.unk_40 != 0) {
        if (param0->unk_279C.unk_42 < (8 + 2) - 1) {
            if (param0->unk_279C.unk_42 <= 8) {
                v4 = param0->unk_279C.unk_74.unk_00;
                v5 = param0->unk_279C.unk_8C.unk_00;
                v2 = WiFiLobbyMinigameManene_UpdateMotion(&param0->unk_279C.unk_74);
                v3 = WiFiLobbyMinigameManene_UpdateMotion(&param0->unk_279C.unk_8C);
                v6 = (param0->unk_279C.unk_74.unk_00 - v4) >> FX32_SHIFT;
                v7 = (param0->unk_279C.unk_8C.unk_00 - v5) >> FX32_SHIFT;

                if ((v2 == 1) || (v3 == 1)) {
                    param0->unk_279C.unk_74.unk_00 -= v4;
                    param0->unk_279C.unk_8C.unk_00 -= v5;
                }
            } else {
                v6 = param0->unk_279C.unk_74.unk_00 >> FX32_SHIFT;
                v7 = param0->unk_279C.unk_8C.unk_00 >> FX32_SHIFT;
            }
        } else {
            v4 = param0->unk_279C.unk_44.unk_00;
            v5 = param0->unk_279C.unk_5C.unk_00;
            v2 = WiFiLobbyMinigameManene_UpdateMotion(&param0->unk_279C.unk_44);
            v3 = WiFiLobbyMinigameManene_UpdateMotion(&param0->unk_279C.unk_5C);
            v6 = (param0->unk_279C.unk_44.unk_00 - v4) >> FX32_SHIFT;
            v7 = (param0->unk_279C.unk_5C.unk_00 - v5) >> FX32_SHIFT;

            if ((v2 == 1) || (v3 == 1)) {
                if (param0->unk_279C.unk_A8 == 0) {
                    param0->unk_279C.unk_A8 = 1;
                    param0->unk_279C.unk_44.unk_00 -= v4;
                    param0->unk_279C.unk_5C.unk_00 -= v5;
                }
            }
        }

        v0 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, 0, 0, v6, v7, (2.35 * 0.80), 0);
        v1 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], 0, 0, v6, v7, (0.80), 0);

        if (v1) {
            VecFx32 v9 = { 0, (FX32_CONST(100)), 0 };
            VecFx32 v10;
            MTX_MultVec43(&v9, &param0->unk_308[0].unk_1B0, &param0->unk_1FB0);
        }

        param0->unk_279C.unk_42++;
        param0->unk_279C.unk_40--;
    } else {
        if ((param0->unk_279C.unk_00 % v8[param0->unk_279C.unk_0C]) == 0) {
            param0->unk_279C.unk_00 = 0;
            param0->unk_279C.unk_AC = 1;
        }

        if ((param0->unk_279C.unk_A4 == 0) && (param0->unk_279C.unk_A8 == 1)) {
            v6 = param0->unk_279C.unk_44.unk_00 >> FX32_SHIFT;
            v7 = param0->unk_279C.unk_5C.unk_00 >> FX32_SHIFT;
            v0 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, 0, 0, v6, v7, (2.35 * 0.80), 0);
            v1 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], 0, 0, v6, v7, (0.80), 0);

            if (v1) {
                VecFx32 v11 = { 0, (FX32_CONST(100)), 0 };
                VecFx32 v12;

                MTX_MultVec43(&v11, &param0->unk_308[0].unk_1B0, &param0->unk_1FB0);
            }
        } else if ((param0->unk_279C.unk_A4 == 1) && (param0->unk_279C.unk_A8 == 1)) {
            v6 = param0->unk_279C.unk_44.unk_00 >> FX32_SHIFT;
            v7 = param0->unk_279C.unk_5C.unk_00 >> FX32_SHIFT;
            v0 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_FC, 0, 0, v6, v7, (2.35 * 0.80), 0);
            v1 = WiFiLobbyMinigameManene_TiltBall(&param0->unk_308[0], 0, 0, v6, v7, (0.80), 0);

            if (v1) {
                VecFx32 v13 = { 0, (FX32_CONST(100)), 0 };
                VecFx32 v14;
                MTX_MultVec43(&v13, &param0->unk_308[0].unk_1B0, &param0->unk_1FB0);
            }
        }

        if ((param0->unk_279C.unk_B0 == 0) || ((param0->unk_279C.unk_AC == 1) && (param0->unk_279C.unk_A8 == 1))) {
            int v15 = Random() % 100;
            int v16 = 0;
            int v17;
            int v18 = sRandomWeights[param0->unk_279C.unk_0C][0].unk_04;
            s16 v19, v20;
            s16 v21, v22;
            s16 v23, v24, v25;

            v19 = v20 = 0;

            for (v17 = 0; v17 < 3; v17++) {
                if (v15 < v18) {
                    break;
                }

                v18 += sRandomWeights[param0->unk_279C.unk_0C][v17 + 1].unk_04;
            }

            v16 = sRandomWeights[param0->unk_279C.unk_0C][v17].unk_00;
            v16 *= 1;

            {
                v23 = param0->unk_1FB0.x >> FX32_SHIFT;
                v25 = param0->unk_1FB0.y >> FX32_SHIFT;
                v24 = param0->unk_1FB0.z >> FX32_SHIFT;

                if (param0->unk_1FB0.z == FX32_CONST(0)) {
                    v24 = RandomSign();
                } else {
                    v24 = -Sign(v24);
                }

                if (param0->unk_1FB0.x == FX32_CONST(0)) {
                    v23 = RandomSign();
                } else {
                    v23 = Sign(v23);

                    if (v24 < 0) {
                        v23 *= -1;
                    }
                }

                if (param0->unk_279C.unk_0C == 0) {
                    v23 = 0;
                }

                v19 = v16 * v23;
                v20 = v16 * v24;
            }

            v21 = 20 * v23;
            v22 = 20 * v24;

            param0->unk_279C.unk_B8 = v19;
            param0->unk_279C.unk_BA = v20;

            WiFiLobbyMinigameManene_InitMotion(&param0->unk_279C.unk_74, FX32_CONST(0), FX32_CONST(v21), FX32_CONST(0), 8);
            WiFiLobbyMinigameManene_InitMotion(&param0->unk_279C.unk_8C, FX32_CONST(0), FX32_CONST(v22), FX32_CONST(0), 8);
            WiFiLobbyMinigameManene_InitMotion(&param0->unk_279C.unk_44, FX32_CONST(0), FX32_CONST(v19), FX32_CONST(0), 12);
            WiFiLobbyMinigameManene_InitMotion(&param0->unk_279C.unk_5C, FX32_CONST(0), FX32_CONST(v20), FX32_CONST(0), 12);

            param0->unk_279C.unk_40 = 12 + (8 + 2);
            param0->unk_279C.unk_42 = 0;
            param0->unk_279C.unk_3C = v19;
            param0->unk_279C.unk_3E = v20;
            param0->unk_279C.unk_A4 = 0;
            param0->unk_279C.unk_AC = 0;
            param0->unk_279C.unk_A8 = 0;
            param0->unk_279C.unk_B0 = 1;
        }
    }
}
