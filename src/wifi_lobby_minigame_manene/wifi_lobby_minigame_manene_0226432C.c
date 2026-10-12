#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_0226432C.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02261870.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226139C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02262A8C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226469C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022647BC.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022649E4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226501C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_0226534C.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265470.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265AA4.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_02265D84.h"
#include "wifi_lobby_minigame_manene/struct_wifi_lobby_minigame_manene_022660A8.h"
#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_02266FEC.h"

#include "bg_window.h"
#include "easy3d_object.h"
#include "heap.h"
#include "inlines.h"
#include "math_util.h"
#include "palette.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task.h"
#include "sys_task_manager.h"

typedef struct {
    ManagedSprite *unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    fx32 unk_14;
    fx32 unk_18;
    fx32 unk_1C;
    fx32 unk_20;
    u8 unk_24;
    u8 unk_25;
    u8 unk_26;
    u8 unk_27;
    int unk_28;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
} WiFiLobbyMinigameManeneIntroSprite;

typedef struct {
    WiFiLobbyMinigameManeneGame *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    BOOL *unk_10;
    WiFiLobbyMinigameManeneIntroSprite unk_14[36];
} WiFiLobbyMinigameManeneIntroAnimation;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C[3];
    int unk_18[3];
    void *unk_24;
} WiFiLobbyMinigameManeneResultsStep;

static void SparkleTask(SysTask *param0, void *param1);
static inline void UpdateIntroSpriteRotation(WiFiLobbyMinigameManeneIntroSprite *param0);
static inline void MoveIntroSprite(WiFiLobbyMinigameManeneIntroSprite *wk, fx32 x, fx32 y);
static void IntroAnimationTask(SysTask *param0, void *param1);
static void IntroStep0(WiFiLobbyMinigameManeneIntroStep *param0);
static void IntroStep1(WiFiLobbyMinigameManeneIntroStep *param0);
static void IntroStep2(WiFiLobbyMinigameManeneIntroStep *param0);
static void IntroStep3(WiFiLobbyMinigameManeneIntroStep *param0);
static void IntroSequenceTask(SysTask *param0, void *param1);
static void ResultsScrollIn(WiFiLobbyMinigameManeneResultsAnimation *param0);
static void ResultsScrollOut(WiFiLobbyMinigameManeneResultsAnimation *param0);
static int GetAnimationDuration(int param0);
static void ResultsAnimationTask(SysTask *param0, void *param1);
static void ResultsStepA(SysTask *param0, void *param1);
static void ResetResultsSprite(WiFiLobbyMinigameManeneResultsSprite *param0);
static BOOL ResultsSpriteMove1(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3);
static BOOL ResultsSpriteMove2(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3);
static BOOL ResultsSpriteMove3(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3);
static BOOL ResultsSpriteOrbit(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3);
static void ResultsStepB(SysTask *param0, void *param1);
static void ResultsStepC(SysTask *param0, void *param1);
static void ResultsStepD(SysTask *param0, void *param1);
static void ResultsStepE(SysTask *param0, void *param1);
BOOL WiFiLobbyMinigameManene_TiltBall(WiFiLobbyMinigameManene3DObject *param0, int param1, int param2, int param3, int param4, f32 param5, BOOL param6);
BOOL WiFiLobbyMinigameManene_DecayBallTilt(WiFiLobbyMinigameManene3DObject *param0, f32 param1);
int WiFiLobbyMinigameManene_GetPlayerIndex(WiFiLobbyMinigameManeneApp *param0, int param1);
void WiFiLobbyMinigameManene_InitMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4);
BOOL WiFiLobbyMinigameManene_UpdateMotion(WiFiLobbyMinigameManeneMotion *param0);
void WiFiLobbyMinigameManene_InitLinearMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, s32 param3);
BOOL WiFiLobbyMinigameManene_UpdateLinearMotion(WiFiLobbyMinigameManeneMotion *param0);
void WiFiLobbyMinigameManene_SpawnSparkle(WiFiLobbyMinigameManeneGame *param0, s16 param1, s16 param2);
void WiFiLobbyMinigameManene_StartIntroAnimation(WiFiLobbyMinigameManeneGame *param0, BOOL *param1);
void WiFiLobbyMinigameManene_SetupIntroSequence(WiFiLobbyMinigameManeneGame *param0);
void WiFiLobbyMinigameManene_SetupResultsAnimation(WiFiLobbyMinigameManeneGame *param0);

BOOL WiFiLobbyMinigameManene_TiltBall(WiFiLobbyMinigameManene3DObject *param0, int param1, int param2, int param3, int param4, f32 param5, BOOL param6)
{
    f32 v0;
    fx32 v1;
    f32 v2, v3;

    v2 = (param1 - param3) * ((1.33) / 256) * param5;
    v3 = (param2 - param4) * ((1.00) / 192) * param5;

    if (param6) {
        param0->tiltX = v2;
        param0->tiltY = v3;
        param0->tiltFramesRemaining = 8;
        param0->tiltDecayX = param0->tiltX / param0->tiltFramesRemaining;
        param0->tiltDecayY = param0->tiltY / param0->tiltFramesRemaining;
    }

    {
        f32 v4 = ((v2 * v2) + (v3 * v3));
        fx32 v5 = FX_F32_TO_FX32(v4);

        v1 = FX_Sqrt(v5);
        v0 = FX_FX32_TO_F32(v1);
        v0 *= (1.00);
    }

    if (v0 != 0.0) {
        fx32 v6 = v1;
        fx64c v7 = FX_SinFx64c(v6);
        fx64c v8 = FX_CosFx64c(v6);
        f32 v9 = FX_FX64C_TO_F32(v7);
        f32 v10 = FX_FX64C_TO_F32(v8);
        f32 v11 = v9 / v0;
        WiFiLobbyMinigameManeneQuaternion v12;

        v12.val2[0] = v10;
        v12.val2[1] = v3 * v11;
        v12.val2[2] = v2 * v11;
        v12.val2[3] = 0.0;

        WiFiLobbyMinigameManene_QuaternionMultiply(&param0->rotation, &v12, &param0->previousRotation);
        WiFiLobbyMinigameManene_QuaternionToMatrix(&param0->rotationMatrix, &param0->rotation);
        WiFiLobbyMinigameManene_QuaternionCopy(&param0->previousRotation, &param0->rotation);
        WiFiLobbyMinigameManene_MatrixToMtx43(&param0->rotationMatrix, &param0->matrix);

        {
            WiFiLobbyMinigameManeneQuaternion v13;
            f32 v14 = WiFiLobbyMinigameManene_QuaternionMagnitude(&param0->rotation);

            v13 = param0->rotation;
            WiFiLobbyMinigameManene_QuaternionScale(&param0->rotation, &v13, v14);
        }

        return 1;
    }

    return 0;
}

BOOL WiFiLobbyMinigameManene_DecayBallTilt(WiFiLobbyMinigameManene3DObject *param0, f32 param1)
{
    f32 v0;
    fx32 v1;
    f32 v2, v3;

    v2 = param0->tiltX;
    v3 = param0->tiltY;

    param0->tiltX -= param0->tiltDecayX;
    param0->tiltY -= param0->tiltDecayY;
    param0->tiltFramesRemaining--;

    {
        f32 v4 = ((v2 * v2) + (v3 * v3));
        fx32 v5 = FX_F32_TO_FX32(v4);

        v1 = FX_Sqrt(v5);
        v0 = FX_FX32_TO_F32(v1);
        v0 *= (1.00);
    }

    if (v0 != 0.0) {
        fx32 v6 = v1;
        fx64c v7 = FX_SinFx64c(v6);
        fx64c v8 = FX_CosFx64c(v6);
        f32 v9 = FX_FX64C_TO_F32(v7);
        f32 v10 = FX_FX64C_TO_F32(v8);
        f32 v11 = v9 / v0;
        WiFiLobbyMinigameManeneQuaternion v12;

        v12.val2[0] = v10;
        v12.val2[1] = v3 * v11;
        v12.val2[2] = v2 * v11;
        v12.val2[3] = 0.0;

        WiFiLobbyMinigameManene_QuaternionMultiply(&param0->rotation, &v12, &param0->previousRotation);
        WiFiLobbyMinigameManene_QuaternionToMatrix(&param0->rotationMatrix, &param0->rotation);
        WiFiLobbyMinigameManene_QuaternionCopy(&param0->previousRotation, &param0->rotation);
        WiFiLobbyMinigameManene_MatrixToMtx43(&param0->rotationMatrix, &param0->matrix);

        return 1;
    }

    return 0;
}

int WiFiLobbyMinigameManene_GetPlayerIndex(WiFiLobbyMinigameManeneApp *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->playerNetIds[v0] == param1) {
            return v0;
        }
    }

    return 0xFF;
}

void WiFiLobbyMinigameManene_InitMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, fx32 param3, int param4)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v2 = param2 - param1;

    v0 = (param4 * param4) << FX32_SHIFT;
    v1 = FX_Mul(param3, param4 * FX32_ONE);
    v1 = v2 - v1;
    v1 = FX_Mul(v1, 2 * FX32_ONE);
    v3 = FX_Div(v1, v0);

    param0->value = param1;
    param0->startValue = param1;
    param0->velocity = param3;
    param0->acceleration = v3;
    param0->elapsedFrames = 0;
    param0->duration = param4;
}

BOOL WiFiLobbyMinigameManene_UpdateMotion(WiFiLobbyMinigameManeneMotion *param0)
{
    fx32 v0;
    fx32 v1;
    fx32 v2;
    fx32 v3;

    v3 = FX_Mul(param0->velocity, param0->elapsedFrames << FX32_SHIFT);
    v1 = (param0->elapsedFrames * param0->elapsedFrames) << FX32_SHIFT;
    v2 = FX_Mul(param0->acceleration, v1);
    v2 = FX_Div(v2, 2 * FX32_ONE);
    v0 = v3 + v2;

    param0->value = param0->startValue + v0;

    if ((param0->elapsedFrames + 1) <= param0->duration) {
        param0->elapsedFrames++;
        return 0;
    }

    param0->elapsedFrames = param0->duration;

    return 1;
}

void WiFiLobbyMinigameManene_InitLinearMotion(WiFiLobbyMinigameManeneMotion *param0, fx32 param1, fx32 param2, s32 param3)
{
    param0->value = param1;
    param0->startValue = param1;
    param0->acceleration = param2 - param1;
    param0->elapsedFrames = 0;
    param0->duration = param3;
}

BOOL WiFiLobbyMinigameManene_UpdateLinearMotion(WiFiLobbyMinigameManeneMotion *param0)
{
    s32 v0;
    BOOL v1;
    fx32 v2;

    if (param0->elapsedFrames >= param0->duration) {
        v0 = param0->duration;
        v1 = 1;
    } else {
        v0 = param0->elapsedFrames;
        param0->elapsedFrames++;
        v1 = 0;
    }

    v2 = FX_Mul(param0->acceleration, v0 << FX32_SHIFT);
    v2 = FX_Div(v2, param0->duration << FX32_SHIFT);
    v2 += param0->startValue;

    param0->value = v2;

    return v1;
}

static void SparkleTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManeneSparkle *v0 = param1;
    int v1;
    fx32 v2, v3;
    BOOL v4[4][2];
    BOOL v5 = 1;
    const fx32 v6[] = {
        FX32_CONST(-5),
        FX32_CONST(+3),
        FX32_CONST(+4),
        FX32_CONST(-3),
        FX32_CONST(+3),
        FX32_CONST(-2)
    };
    const fx32 v7[] = {
        FX32_CONST(+4),
        FX32_CONST(+5),
        FX32_CONST(-4),
        FX32_CONST(-5),
        FX32_CONST(-3),
        FX32_CONST(+2)
    };

    if ((IsScreenFadeDone() == FALSE) || (v0->resources->disconnectState.disconnected == 1)) {
        for (v1 = 0; v1 < 3; v1++) {
            Sprite_DeleteAndFreeResources(v0->sprites[v1]);
        }

        v0->active = 0;
        SysTask_Done(param0);

        return;
    }

    switch (v0->state) {
    case 0:
        for (v1 = 0; v1 < 3; v1++) {
            ManagedSprite_GetPositionFxXY(v0->sprites[v1], &v2, &v3);
            WiFiLobbyMinigameManene_InitMotion(&v0->motions[v1][0], v2, v2 + v6[v1], FX_F32_TO_FX32(0.3f), 8);
            WiFiLobbyMinigameManene_InitMotion(&v0->motions[v1][1], v3, v3 + v7[v1], FX_F32_TO_FX32(0.2f), 8);
        }

        v0->state++;
        break;
    case 1:
        for (v1 = 0; v1 < 3; v1++) {
            v4[v1][0] = WiFiLobbyMinigameManene_UpdateMotion(&v0->motions[v1][0]);
            v4[v1][1] = WiFiLobbyMinigameManene_UpdateMotion(&v0->motions[v1][1]);

            ManagedSprite_SetPositionFxXY(v0->sprites[v1], v0->motions[v1][0].value, v0->motions[v1][1].value);

            if ((v4[v1][0] == 0) || (v4[v1][1] == 0)) {
                v5 = 0;
            }

            ManagedSprite_TickFrame(v0->sprites[v1]);
        }
        if (v5) {
            v0->state++;
        }

        break;
    default:
        for (v1 = 0; v1 < 3; v1++) {
            Sprite_DeleteAndFreeResources(v0->sprites[v1]);
        }

        v0->active = 0;

        SysTask_Done(param0);
        break;
    }
}

void WiFiLobbyMinigameManene_SpawnSparkle(WiFiLobbyMinigameManeneGame *param0, s16 param1, s16 param2)
{
    int v0;
    int v1;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->sparkles[v0].active == 1) {
            continue;
        }

        param0->sparkles[v0].resources = param0->resources;
        param0->sparkles[v0].state = 0;
        param0->sparkles[v0].active = 1;

        for (v1 = 0; v1 < 3; v1++) {
            param0->sparkles[v0].sprites[v1] = WiFiLobbyMinigameManene_CreateSparkleSprite(param0, param1, param2);
            ManagedSprite_SetAnim(param0->sparkles[v0].sprites[v1], ((param1 * (v0 + 1)) + (param2 * (v1 + 1))) % 3);
        }

        SysTask_Start(SparkleTask, &param0->sparkles[v0], 4096);
        break;
    }
}

static inline void UpdateIntroSpriteRotation(WiFiLobbyMinigameManeneIntroSprite *param0)
{
    param0->unk_1C = FX_Mul(CalcSineDegrees_Wraparound(param0->unk_28), FX32_CONST(param0->unk_2E));
    param0->unk_20 = FX_Mul(CalcCosineDegrees_Wraparound(param0->unk_28), FX32_CONST(param0->unk_30));
}

static inline void MoveIntroSprite(WiFiLobbyMinigameManeneIntroSprite *wk, fx32 x, fx32 y)
{
    wk->unk_04 += x;
    wk->unk_08 += y;

    ManagedSprite_SetPositionFxXYWithSubscreenOffset(wk->unk_00, wk->unk_14 + wk->unk_0C + wk->unk_1C + wk->unk_04, wk->unk_18 + wk->unk_10 + wk->unk_20 + wk->unk_08, FX32_CONST(192 + 32));
}

static void IntroAnimationTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManeneIntroAnimation *v0 = param1;
    WiFiLobbyMinigameManeneResources *v1 = v0->unk_00->resources;

    if ((IsScreenFadeDone() == FALSE) || (v1->disconnectState.disconnected == 1)) {
        *v0->unk_10 = 0;
        SysTask_Done(param0);
        Heap_Free(v0);
        return;
    }

    switch (v0->unk_04) {
    case 0:
        v0->unk_0C = 0;
        v0->unk_04++;
    case 1: {
        int v2;
        s16 v3[][2] = {
            { 96, 58 }, { 230, 48 }, { 128, 32 }, { 40, 64 }, { 180, 48 }
        };
        u32 v4 = v3[v0->unk_0C][0];
        u32 v5 = v3[v0->unk_0C][1];

        v0->unk_08 = 0;

        for (v2 = 0; v2 < (3 * 12); v2++) {
            v0->unk_14[v2].unk_26 = v2 % 2;
            v0->unk_14[v2].unk_2E = 6 - (v2 % 3);
            v0->unk_14[v2].unk_30 = 6 - (v2 % 3);
            v0->unk_14[v2].unk_00 = v0->unk_00->backgroundSprites[v2];
            v0->unk_14[v2].unk_28 = ((v2 / 3) * (360 / 12));
            v0->unk_14[v2].unk_28 %= 360;
            v0->unk_14[v2].unk_2C = 0;
            v0->unk_14[v2].unk_32 = -((v2 % 3) * 2);
            v0->unk_14[v2].unk_0C = FX32_CONST(v4);
            v0->unk_14[v2].unk_10 = FX32_CONST(v5);
            v0->unk_14[v2].unk_1C = 0;
            v0->unk_14[v2].unk_20 = 0;
            v0->unk_14[v2].unk_04 = 0;
            v0->unk_14[v2].unk_08 = 0;
            v0->unk_14[v2].unk_14 = 0;
            v0->unk_14[v2].unk_18 = 0;
            v0->unk_14[v2].unk_24 = 0;
            v0->unk_14[v2].unk_25 = 1;
            v0->unk_14[v2].unk_27 = 0;

            if (v0->unk_14[v2].unk_28 == 180) {
                v0->unk_14[v2].unk_24 = 2;
            }

            if ((v0->unk_14[v2].unk_28 >= 270) && (v0->unk_14[v2].unk_28 <= 90)) {
                v0->unk_14[v2].unk_24 = 1;
            }

            UpdateIntroSpriteRotation(&v0->unk_14[v2]);
            MoveIntroSprite(&v0->unk_14[v2], FX32_CONST(0), FX32_CONST(v0->unk_14[v2].unk_2C));
        }
    }
        v0->unk_04++;
        break;

    case 2: {
        int v6;
        s16 v7, v8;
        BOOL v9 = 1;

        if (v0->unk_08 == 0) {
            v0->unk_08++;
            WiFiLobbyMinigameManene_SetBackgroundSpritesVisible(v0->unk_00, 1, 0);
            Sound_PlayEffect(SEQ_SE_PL_140_2_2_sseq);
        }

        if (v0->unk_08 > 30) {
            v0->unk_04 = 1;
            v0->unk_0C++;
            v0->unk_0C %= 5;
            WiFiLobbyMinigameManene_SetBackgroundSpritesVisible(v0->unk_00, 0, 1);
        } else {
            v0->unk_08++;

            for (v6 = 0; v6 < (3 * 12); v6++) {
                if ((++v0->unk_14[v6].unk_32) < 0) {
                    continue;
                }

                if (v0->unk_14[v6].unk_32 >= (10 + v0->unk_14[v6].unk_26)) {
                    if (v0->unk_14[v6].unk_32 == (10 + v0->unk_14[v6].unk_26)) {
                        ManagedSprite_SetAnim(v0->unk_14[v6].unk_00, 0);
                    }

                    if (v0->unk_14[v6].unk_32 == (18 + v0->unk_14[v6].unk_26)) {
                        v0->unk_14[v6].unk_25 = 0;
                    } else {
                        if (v0->unk_14[v6].unk_32 % 2) {
                            v0->unk_14[v6].unk_25 ^= 1;
                        }
                    }

                    ManagedSprite_SetDrawFlag(v0->unk_14[v6].unk_00, v0->unk_14[v6].unk_25);

                    switch (v0->unk_14[v6].unk_27) {
                    case 0:
                        v0->unk_14[v6].unk_14 = FX32_CONST(-1);
                        break;
                    case 1:
                        v0->unk_14[v6].unk_14 = FX32_CONST(+0);
                        break;
                    case 2:
                        v0->unk_14[v6].unk_14 = FX32_CONST(+1);
                        break;
                    }

                    v0->unk_14[v6].unk_27++;
                    v0->unk_14[v6].unk_27 %= 3;
                }
                if (v0->unk_14[v6].unk_32 > 5) {
                    switch (v0->unk_14[v6].unk_24) {
                    case 2:
                        v0->unk_14[v6].unk_2C = (v0->unk_14[v6].unk_32 + 5) / 6;
                        break;
                    case 1:
                        v0->unk_14[v6].unk_2C = (v0->unk_14[v6].unk_32 + 5) / 6;
                        break;
                    case 0:
                        v0->unk_14[v6].unk_2C = (v0->unk_14[v6].unk_32 + 5) / 7;
                        break;
                    }
                }

                switch (v0->unk_14[v6].unk_24) {
                case 2:
                    v7 = (30 - (v0->unk_14[v6].unk_32 + 5)) / 8;
                    v8 = (30 - (v0->unk_14[v6].unk_32 + 7)) / 8;
                    break;
                case 1:
                default:
                    v7 = (30 - (v0->unk_14[v6].unk_32 + 5)) / 8;
                    v8 = (30 - (v0->unk_14[v6].unk_32 + 6)) / 8;
                    break;
                case 0:
                    v7 = (30 - (v0->unk_14[v6].unk_32 + 5)) / 8;
                    v8 = (30 - (v0->unk_14[v6].unk_32 + 4)) / 8;
                    break;
                }

                if (v7 > 0) {
                    v0->unk_14[v6].unk_2E += v7;
                } else {
                    v0->unk_14[v6].unk_2E++;
                }

                if (v8 > 0) {
                    v0->unk_14[v6].unk_30 += v8;
                } else {
                    v0->unk_14[v6].unk_30++;
                }

                UpdateIntroSpriteRotation(&v0->unk_14[v6]);
                MoveIntroSprite(&v0->unk_14[v6], FX32_CONST(0), FX32_CONST(v0->unk_14[v6].unk_2C));
            }
        }
        if (*v0->unk_10) {
            v0->unk_04++;
        }
    } break;

    default:
        WiFiLobbyMinigameManene_SetBackgroundSpritesVisible(v0->unk_00, 0, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        break;
    }

    WiFiLobbyMinigameManene_TickBackgroundSprites(v0->unk_00);
}

void WiFiLobbyMinigameManene_StartIntroAnimation(WiFiLobbyMinigameManeneGame *param0, BOOL *param1)
{
    WiFiLobbyMinigameManeneIntroAnimation *v0 = Heap_Alloc(HEAP_ID_106, sizeof(WiFiLobbyMinigameManeneIntroAnimation));

    v0->unk_00 = param0;
    v0->unk_04 = 0;
    v0->unk_08 = 0;
    v0->unk_10 = param1;

    SysTask_Start(IntroAnimationTask, v0, 4096);
}

static void IntroStep0(WiFiLobbyMinigameManeneIntroStep *param0)
{
    WiFiLobbyMinigameManene3DObject *v0 = param0->objects[0];
    int *v1 = param0->objects[1];
    int *v2 = param0->objects[3];
    PaletteData *v3 = param0->objects[2];

    if (param0->active == 0) {
        return;
    }

    switch (param0->state) {
    case 0:
        if (*v1 < 4) {
            *v1 += 1;
        } else {
            *v1 = 4;
            param0->state++;
        }

        PaletteData_BlendMulti(v3, PLTTBUF_MAIN_BG, 0x1, *v1 + *v2, 0x0);
        PaletteData_BlendMulti(v3, PLTTBUF_SUB_BG, 0x1, *v1 + *v2, 0x0);
        break;

    case 1:
        Easy3DObject_SetVisible(&v0->object, 1);
        param0->timers[0] = 0;
        param0->state++;
        break;

    case 2:
        if (param0->flags[0] == 1) {
            if (++param0->timers[0] >= 15) {
                param0->state++;
            }
        }

        break;

    case 3:
        if (*v1 > 0) {
            *v1 -= 1;
        } else {
            *v1 = 0;
            param0->state++;
        }

        PaletteData_BlendMulti(v3, PLTTBUF_MAIN_BG, 0x1, *v1 + *v2, 0x0);
        PaletteData_BlendMulti(v3, PLTTBUF_SUB_BG, 0x1, *v1 + *v2, 0x0);
        break;

    default:
        param0->flags[0] = 0;
        param0->active = 0;
        param0->state = 0;

        Easy3DObject_SetVisible(&v0->object, 0);

        break;
    }
}

static void IntroStep1(WiFiLobbyMinigameManeneIntroStep *param0)
{
    int v0;
    s16 v1, v2;
    s16 v3[] = { 188, 188, 180, 180 };
    BOOL v4[4] = { 1, 1, 1, 1 };
    ManagedSprite *v5;

    if (param0->active == 0) {
        return;
    }

    switch (param0->state) {
    case 0:
        for (v0 = 0; v0 < 4; v0++) {
            v5 = param0->objects[v0];
            if (v5 == NULL) {
                continue;
            }

            ManagedSprite_GetPositionXY(v5, &v1, &v2);
            if (v2 > v3[v0]) {
                v2 -= 6;
                ManagedSprite_SetPositionXY(v5, v1, v2);
                v4[v0] = 0;
            }
        }
        if (v4[0] && v4[1] && v4[2] && v4[2]) {
            param0->timers[0] = 0;
            param0->flags[0] = 0;
            param0->state++;
        }

        break;

    case 1:
        if (param0->flags[0] == 1) {
            if (++param0->timers[0] >= 15) {
                param0->state++;
            }
        }

        break;

    case 2:
        for (v0 = 0; v0 < 4; v0++) {
            v5 = param0->objects[v0];
            if (v5 == NULL) {
                continue;
            }

            ManagedSprite_GetPositionXY(v5, &v1, &v2);
            if (v2 < (192 + 32)) {
                v2 += 6;
                ManagedSprite_SetPositionXY(v5, v1, v2);
                v4[v0] = 0;
            }
        }
        if (v4[0] && v4[1] && v4[2] && v4[2]) {
            param0->state++;
        }

        break;

    default:
        param0->flags[0] = 0;
        param0->active = 0;
        param0->state = 0;

        break;
    }

    for (v0 = 0; v0 < 4; v0++) {
        v5 = param0->objects[v0];
        if (v5 == NULL) {
            continue;
        }

        ManagedSprite_TickTwoFrames(v5);
    }
}

static void IntroStep2(WiFiLobbyMinigameManeneIntroStep *param0)
{
    int v0;

    if (param0->active == 0) {
        return;
    }

    switch (param0->state) {
    case 0:
        for (v0 = 0; v0 < 8; v0++) {
            WiFiLobbyMinigameManene3DObject *v1 = param0->objects[v0];

            Easy3DAnim_SetFrame(&v1->anims[0], (v0 * 20) % 40);
            Easy3DObject_SetVisible(&v1->object, 1);
        }

        param0->timers[9] = 0;
        param0->state++;
        break;
    case 1:
        if (param0->flags[0] == 1) {
            if (++param0->timers[9] >= 15) {
                param0->state++;
            }
        }
        break;
    default:
        for (v0 = 0; v0 < 8; v0++) {
            WiFiLobbyMinigameManene3DObject *v2 = param0->objects[v0];

            Easy3DObject_SetVisible(&v2->object, 0);
        }

        param0->flags[0] = 0;
        param0->active = 0;
        param0->state = 0;

        break;
    }
}

static void IntroStep3(WiFiLobbyMinigameManeneIntroStep *param0)
{
    if (param0->active == 0) {
        return;
    }

    switch (param0->state) {
    case 0:
        WiFiLobbyMinigameManene_StartIntroAnimation(param0->objects[0], &param0->flags[1]);
        param0->timers[0] = 0;
        param0->state++;
        break;
    case 1:
        if (param0->flags[0] == 1) {
            if (++param0->timers[0] >= 15) {
                param0->flags[1] = 1;
                param0->state++;
            }
        }
        break;
    default:
        if (param0->flags[1] == 0) {
            param0->flags[0] = 0;
            param0->active = 0;
            param0->state = 0;
        }
        break;
    }
}

static void IntroSequenceTask(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManeneIntroSequence *v0 = param1;
    WiFiLobbyMinigameManeneResources *v1 = v0->resources;

    if ((IsScreenFadeDone() == FALSE) || (v1->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);

        return;
    }

    switch (*v0->levelPtr) {
    case 5:
        if (v0->steps[4].active == 0) {
            v0->steps[4].active = 1;
            v0->steps[4].flags[0] = 0;
        }
    case 4:
        if (v0->steps[3].active == 0) {
            Sound_PlayEffect(SEQ_SE_DP_DENDOU_sseq);
            v0->steps[3].active = 1;
            v0->steps[3].flags[0] = 0;
        }
    case 3:
        if (v0->steps[2].active == 0) {
            v0->steps[2].active = 1;
            v0->steps[2].flags[0] = 0;
        }
    case 2:
        if (v0->steps[1].active == 0) {
            Sound_PlayEffect(SEQ_SE_PL_HAND_sseq);
            v0->steps[1].active = 1;
            v0->steps[1].flags[0] = 0;
        }
    case 1:
        if (v0->steps[0].active == 0) {
            v0->steps[0].active = 1;
            v0->steps[0].flags[0] = 0;
        }
        break;
    default:
        if (*v0->levelPtr != v0->currentStep) {
            v0->steps[0].flags[0] = 1;
            v0->steps[1].flags[0] = 1;
            v0->steps[2].flags[0] = 1;
            v0->steps[3].flags[0] = 1;
            v0->steps[4].flags[0] = 1;
            Sound_StopEffect(1393, 0);
        }
        break;
    }

    IntroStep0(&v0->steps[0]);
    IntroStep1(&v0->steps[1]);
    IntroStep2(&v0->steps[2]);
    IntroStep1(&v0->steps[3]);
    IntroStep3(&v0->steps[4]);

    v0->currentStep = *v0->levelPtr;
}

void WiFiLobbyMinigameManene_SetupIntroSequence(WiFiLobbyMinigameManeneGame *param0)
{
    int v0;

    param0->introSequence.resources = param0->resources;
    param0->introSequence.levelPtr = &param0->roundState.level;
    param0->introSequence.currentStep = *param0->introSequence.levelPtr;

    for (v0 = 0; v0 < 5; v0++) {
        WiFiLobbyMinigameManeneIntroStep *v1 = &param0->introSequence.steps[v0];

        v1->state = 0;
        v1->active = 0;

        switch (v0) {
        case 0:
            v1->objects[0] = &param0->introBallObject;
            v1->objects[1] = &param0->blendValueA;
            v1->objects[3] = &param0->blendValueB;
            v1->objects[2] = param0->resources->paletteData;
            break;
        case 1:
            v1->objects[0] = param0->playerSprites[0];
            v1->objects[1] = param0->playerSprites[1];
            v1->objects[2] = NULL;
            v1->objects[3] = NULL;
            {
                s16 v2, v3;

                ManagedSprite_GetPositionXY(param0->playerSprites[0], &v2, &v3);
                ManagedSprite_SetPositionXY(param0->playerSprites[0], v2, (192 + 32));
                ManagedSprite_GetPositionXY(param0->playerSprites[1], &v2, &v3);
                ManagedSprite_SetPositionXY(param0->playerSprites[1], v2, (192 + 32));
            }
            break;
        case 2: {
            int v4;

            for (v4 = 0; v4 < 8; v4++) {
                v1->objects[v4] = &param0->decorationObjects[v4];
            }
        } break;
        case 3:
            v1->objects[0] = NULL;
            v1->objects[1] = NULL;
            v1->objects[2] = param0->playerSprites[2];
            v1->objects[3] = param0->playerSprites[3];
            {
                s16 v5, v6;

                ManagedSprite_GetPositionXY(param0->playerSprites[2], &v5, &v6);
                ManagedSprite_SetPositionXY(param0->playerSprites[2], v5, (192 + 32));
                ManagedSprite_GetPositionXY(param0->playerSprites[3], &v5, &v6);
                ManagedSprite_SetPositionXY(param0->playerSprites[3], v5, (192 + 32));
            }
            break;
        case 4:
            v1->objects[0] = param0;
            break;
        }
    }

    param0->introSequence.task = SysTask_Start(IntroSequenceTask, &param0->introSequence, 4096);
}

static void ResultsScrollIn(WiFiLobbyMinigameManeneResultsAnimation *param0)
{
    int *v0 = param0->blendValuePtrA;
    int *v1 = param0->blendValuePtrB;
    BOOL v2[5];

    switch (param0->scrollState) {
    case 0:
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[0], FX32_CONST(0), FX32_CONST(+40), 10);
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[1], FX32_CONST(0), FX32_CONST(+80), 10);
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[2], FX32_CONST(0), FX32_CONST(-80), 10);

        param0->scrollState++;
        break;
    case 1: {
        int v3;

        for (v3 = 0; v3 < 3; v3++) {
            v2[v3] = WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->scrollMotions[v3]);
        }

        Bg_ScheduleScroll(param0->resources->bgConfig, 7, 3, param0->scrollMotions[0].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 5, 0, param0->scrollMotions[1].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 6, 0, param0->scrollMotions[2].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 1, 0, param0->scrollMotions[1].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 2, 0, param0->scrollMotions[2].value >> FX32_SHIFT);

        if (v2[0] && v2[1] && v2[2]) {
            param0->scrollState++;
        }
    } break;
    case 2:
        param0->scrollOn = 1;
        param0->scrollState = 0;
        break;
    }

    if (*v1 < 6) {
        *v1 += 1;
    } else {
        *v1 = 6;
    }

    PaletteData_BlendMulti(param0->resources->paletteData, PLTTBUF_MAIN_BG, 0x1, *v0 + *v1, 0x0);
    PaletteData_BlendMulti(param0->resources->paletteData, PLTTBUF_SUB_BG, 0x1, *v0 + *v1, 0x0);
}

static void ResultsScrollOut(WiFiLobbyMinigameManeneResultsAnimation *param0)
{
    int *v0 = param0->blendValuePtrA;
    int *v1 = param0->blendValuePtrB;
    BOOL v2[5];

    switch (param0->scrollState) {
    case 0:
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[0], FX32_CONST(+40), FX32_CONST(0), 10);
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[1], FX32_CONST(+80), FX32_CONST(0), 10);
        WiFiLobbyMinigameManene_InitLinearMotion(&param0->scrollMotions[2], FX32_CONST(-80), FX32_CONST(0), 10);
        param0->scrollState++;
        break;
    case 1: {
        int v3;

        for (v3 = 0; v3 < 3; v3++) {
            v2[v3] = WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->scrollMotions[v3]);
        }

        Bg_ScheduleScroll(param0->resources->bgConfig, 7, 3, param0->scrollMotions[0].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 5, 0, param0->scrollMotions[1].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 6, 0, param0->scrollMotions[2].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 1, 0, param0->scrollMotions[1].value >> FX32_SHIFT);
        Bg_ScheduleScroll(param0->resources->bgConfig, 2, 0, param0->scrollMotions[2].value >> FX32_SHIFT);

        if (v2[0] && v2[1] && v2[2]) {
            param0->scrollState++;
        }
    } break;
    case 2:
        param0->scrollOn = 0;
        param0->scrollState = 0;
        break;
    }

    if (*v1 > 4) {
        *v1 -= 1;
    } else {
        *v1 = 0;
    }

    PaletteData_BlendMulti(param0->resources->paletteData, PLTTBUF_MAIN_BG, 0x1, *v0 + *v1, 0x0);
    PaletteData_BlendMulti(param0->resources->paletteData, PLTTBUF_SUB_BG, 0x1, *v0 + *v1, 0x0);
}

static int GetAnimationDuration(int param0)
{
    switch (param0) {
    case 1:
        return 28;
    case 2:
        return 14;
    case 3:
        return 12;
    case 4:
        return 10;
    case 5:
        return 9;
    case 6:
        return 32 * 1;
    case 7:
        return 14 * 1;
    case 8:
        return 12 * 1;
    case 9:
        return 11 * 1;
    case 10:
        return 11 * 1;
    default:
        return 9;
    }
}

static const WiFiLobbyMinigameManeneResultsStep sResultsSteps[] = {
    {
        0x96,
        0x0,
        0x0,
        { 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0 },
        NULL,
    },
    {
        0x96,
        0x2,
        0x1,
        { 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0 },
        ResultsStepA,
    },
    {
        0x96,
        0x3,
        0x2,
        { 0x0, 0x0, 0x0 },
        { 0x0, 0x0, 0x0 },
        ResultsStepB,
    },
    {
        0x96,
        0x3,
        0x2,
        { 0x0, 0x1, 0x0 },
        { 0x1, 0x0, 0x0 },
        ResultsStepB,
    },
    {
        0x96,
        0x3,
        0x3,
        { 0x0, 0x1, 0x2 },
        { 0x2, 0x0, 0x0 },
        ResultsStepC,
    },
    {
        0x96,
        0x3,
        0x4,
        { 0x0, 0x1, 0x2 },
        { 0x2, 0x0, 0x0 },
        ResultsStepC,
    },
    {
        0x96,
        0x3,
        0x5,
        { 0x2, 0x1, 0x0 },
        { 0x1, 0x0, 0x0 },
        ResultsStepD,
    },
    {
        0x96,
        0x3,
        0x5,
        { 0x2, 0x1, 0x0 },
        { 0x2, 0x0, 0x0 },
        ResultsStepE,
    },
    {
        0x96,
        0x3,
        0x5,
        { 0x2, 0x1, 0x0 },
        { 0x2, 0x0, 0x0 },
        ResultsStepE,
    },
};

static void ResultsAnimationTask(SysTask *param0, void *param1)
{
    int v0;
    int v1;
    int v2;
    WiFiLobbyMinigameManeneResultsAnimation *v3 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v4 = &v3->sprites;

    v2 = *v3->resultsStepPtr;

    if ((IsScreenFadeDone() == FALSE) || (v3->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    if (v3->scrollingIn) {
        if (v3->scrollOn == 0) {
            ResultsScrollIn(v3);
        }

        if (v3->stepTimer == 0) {
            if (v2 && (v2 < (8 - 0))) {
                v3->stepTimer = sResultsSteps[v2].unk_00;
                v3->step = 0;
                v4->spriteCount = sResultsSteps[v2].unk_04 - 1;
                v4->animDurationA = sResultsSteps[v2].unk_08;
                v4->animDurationB = sResultsSteps[v2].unk_08 + 5;

                for (v0 = 0; v0 < 2; v0++) {
                    int v5 = sResultsSteps[v2].unk_0C[v0];

                    ManagedSprite_SetExplicitPaletteOffset(v4->spritesA[v0].sprite, 4 + v5);
                    v5 = sResultsSteps[v2].unk_18[v0];
                    ManagedSprite_SetExplicitPaletteOffset(v4->spritesB[v0].sprite, 0 + v5);
                }

                SysTask_Start(sResultsSteps[v2].unk_24, v3, 4097);
            }
        }
    } else if ((v3->scrollingIn == 0) && (v3->stepTimer == 0)) {
        if (v3->scrollOn == 1) {
            ResultsScrollOut(v3);
        }
    }

    if (v3->stepTimer) {
        v3->stepTimer--;
    }
}

void WiFiLobbyMinigameManene_SetupResultsAnimation(WiFiLobbyMinigameManeneGame *param0)
{
    param0->resultsAnimation.resultsStepPtr = &param0->roundState.resultsStep;
    param0->resultsAnimation.blendValuePtrA = &param0->blendValueA;
    param0->resultsAnimation.blendValuePtrB = &param0->blendValueB;
    param0->resultsAnimation.resources = param0->resources;
    param0->resultsAnimation.stepTimer = 0;
    param0->resultsAnimation.scrollState = 0;
    param0->resultsAnimation.scrollingIn = 0;

    {
        int v0;

        for (v0 = 0; v0 < 2; v0++) {
            param0->resultsAnimation.sprites.spritesA[v0].sprite = param0->resultSprites1[v0];
            param0->resultsAnimation.sprites.spritesB[v0].sprite = param0->resultSprites2[v0];
        }
    }

    param0->resultsAnimation.task = SysTask_Start(ResultsAnimationTask, &param0->resultsAnimation, 4096);
}

static void ResultsStepA(SysTask *param0, void *param1)
{
    WiFiLobbyMinigameManeneResultsAnimation *v0 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v1 = &v0->sprites;
    BOOL v2[2];
    fx32 v3, v4;
    fx32 v5, v6;

    if ((IsScreenFadeDone() == FALSE) || (v0->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    switch (v0->step) {
    case 0:
        v1->spritesA[0].angle = 0;
        v1->spritesA[0].baseX = 128;
        v1->spritesA[0].baseY = (128 + 32);
        v1->spritesA[0].radiusX = 64;
        v1->spritesA[0].radiusY = 24;

        ManagedSprite_SetDrawFlag(v1->spritesA[0].sprite, 1);

        v1->spritesB[0].angle = 0;
        v1->spritesB[0].baseX = 128;
        v1->spritesB[0].baseY = (128 + 32);
        v1->spritesB[0].radiusX = 64;
        v1->spritesB[0].radiusY = 24;

        ManagedSprite_SetDrawFlag(v1->spritesB[0].sprite, 1);

        {
            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v1->spritesA[0].sprite, &v5, &v6, ((192 + 64) << FX32_SHIFT));

            v3 = (v1->spritesA[0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v1->spritesA[0].angle) * v1->spritesA[0].radiusX);
            v4 = (v1->spritesA[0].baseY << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(v1->spritesA[0].angle) * v1->spritesA[0].radiusY);

            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v1->spritesA[0].sprite, v3, v4, ((192 + 64) << FX32_SHIFT));
            WiFiLobbyMinigameManene_InitLinearMotion(&v1->spritesA[0].motionX, v3, v3 + FX32_CONST(180), GetAnimationDuration(v1->animDurationB));
            WiFiLobbyMinigameManene_InitLinearMotion(&v1->spritesA[0].motionY, v4, v4 - FX32_CONST(24), GetAnimationDuration(v1->animDurationB));
            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v1->spritesB[0].sprite, &v5, &v6, ((192 + 64) << FX32_SHIFT));

            v3 = (v1->spritesB[0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v1->spritesB[0].angle) * v1->spritesB[0].radiusX);
            v4 = (v1->spritesB[0].baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(v1->spritesB[0].angle) * v1->spritesB[0].radiusY);

            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v1->spritesB[0].sprite, v3, v4, ((192 + 64) << FX32_SHIFT));
            WiFiLobbyMinigameManene_InitLinearMotion(&v1->spritesB[0].motionX, v3, v3 - FX32_CONST(180), GetAnimationDuration(v1->animDurationA));
            WiFiLobbyMinigameManene_InitLinearMotion(&v1->spritesB[0].motionY, v4, v4 + FX32_CONST(24), GetAnimationDuration(v1->animDurationA));
        }

        ResetResultsSprite(&v1->spritesB[0]);
        ResetResultsSprite(&v1->spritesA[0]);
        v0->step++;
    case 1:
        v2[0] = ResultsSpriteOrbit(&v1->spritesB[0], v1->animDurationA, 0, 1);
        v2[1] = ResultsSpriteMove3(&v1->spritesA[0], v1->animDurationB, 1, 3);

        if (v2[0] && v2[1]) {
            ResetResultsSprite(&v1->spritesB[0]);
            ResetResultsSprite(&v1->spritesA[0]);
            v0->step++;
        }
        break;
    case 2:
        v2[0] = ResultsSpriteMove1(&v1->spritesB[0], v1->animDurationA, 0, 3);
        v2[1] = ResultsSpriteMove1(&v1->spritesA[0], v1->animDurationB, 1, 2);
        if (v2[0] && v2[1]) {
            ResetResultsSprite(&v1->spritesB[0]);
            ResetResultsSprite(&v1->spritesA[0]);
            v0->step++;
        }

        break;
    case 3:
        v2[0] = ResultsSpriteMove2(&v1->spritesB[0], v1->animDurationA, 0, 2);
        v2[1] = ResultsSpriteMove3(&v1->spritesA[0], v1->animDurationB, 1, 3);
        if (v2[0] && v2[1]) {
            ResetResultsSprite(&v1->spritesB[0]);
            ResetResultsSprite(&v1->spritesA[0]);
            v0->step++;
        }

        break;
    case 4:
        v2[0] = ResultsSpriteOrbit(&v1->spritesB[0], v1->animDurationA, 0, 1);
        v2[1] = ResultsSpriteMove1(&v1->spritesA[0], v1->animDurationB, 1, 2);

        if (v2[0] && v2[1]) {
            ResetResultsSprite(&v1->spritesB[0]);
            ResetResultsSprite(&v1->spritesA[0]);
            v0->step++;
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void ResetResultsSprite(WiFiLobbyMinigameManeneResultsSprite *param0)
{
    param0->state = 0;
}

static BOOL ResultsSpriteMove1(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3)
{
    BOOL v0[2];
    fx32 v1, v2;
    fx32 v3, v4;

    switch (param0->state) {
    case 0:
        ManagedSprite_GetPositionFxXYWithSubscreenOffset(param0->sprite, &v1, &v2, ((192 + 64) << FX32_SHIFT));
        if (param2 == 0) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, v1, v1 - FX32_CONST(180), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, v1, v1 + FX32_CONST(180), GetAnimationDuration(param1));
        }

        if (param3 == 2) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, v2, v2 - FX32_CONST(24), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, v2, v2 + FX32_CONST(24), GetAnimationDuration(param1));
        }

        param0->state++;
    case 1:
        v0[0] = WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionX);
        WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionY);
        ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, param0->motionX.value, param0->motionY.value, ((192 + 64) << FX32_SHIFT));

        if (v0[0]) {
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL ResultsSpriteMove2(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3)
{
    BOOL v0[2];
    fx32 v1, v2;
    fx32 v3, v4;

    switch (param0->state) {
    case 0:
        if (param2 == 0) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, FX32_CONST(308), FX32_CONST(128), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, FX32_CONST(-62), FX32_CONST(128), GetAnimationDuration(param1));
        }

        if (param3 == 2) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, FX32_CONST(128 + 32), FX32_CONST((128 + 32) - 24), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, FX32_CONST(128 + 32), FX32_CONST((128 + 32) + 24), GetAnimationDuration(param1));
        }

        param0->state++;
    case 1:
        v0[0] = WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionX);
        WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionY);
        ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, param0->motionX.value, param0->motionY.value, ((192 + 64) << FX32_SHIFT));

        if (v0[0]) {
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL ResultsSpriteMove3(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3)
{
    BOOL v0[2];
    fx32 v1, v2;
    fx32 v3, v4;

    switch (param0->state) {
    case 0:
        if (param2 == 0) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, FX32_CONST(308), FX32_CONST(128), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionX, FX32_CONST(-62), FX32_CONST(128), GetAnimationDuration(param1));
        }

        if (param3 == 2) {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, FX32_CONST(96), FX32_CONST(96 - 24), GetAnimationDuration(param1));
        } else {
            WiFiLobbyMinigameManene_InitLinearMotion(&param0->motionY, FX32_CONST(96), FX32_CONST(96 + 24), GetAnimationDuration(param1));
        }

        param0->state++;
    case 1:
        v0[0] = WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionX);
        WiFiLobbyMinigameManene_UpdateLinearMotion(&param0->motionY);
        ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, param0->motionX.value, param0->motionY.value, ((192 + 64) << FX32_SHIFT));

        if (v0[0]) {
            return 1;
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static BOOL ResultsSpriteOrbit(WiFiLobbyMinigameManeneResultsSprite *param0, int param1, int param2, int param3)
{
    BOOL v0[2];
    fx32 v1, v2;
    fx32 v3, v4;

    switch (param0->state) {
    case 0:
        param0->orbitCount = 0;
        param0->angle = 0;
        param0->state++;
    case 1:
        param0->angle += (360 / GetAnimationDuration(param1));

        if (param0->angle >= 360) {
            param0->angle = 0;
        }

        ManagedSprite_GetPositionFxXYWithSubscreenOffset(param0->sprite, &v3, &v4, ((192 + 64) << FX32_SHIFT));

        if (param2 == 0) {
            v1 = (param0->baseX << FX32_SHIFT) - (CalcSineDegrees_Wraparound(param0->angle) * param0->radiusX);
            v2 = (param0->baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(param0->angle) * param0->radiusY);
        } else {
            v1 = (param0->baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(param0->angle) * param0->radiusX);
            v2 = (param0->baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(param0->angle) * param0->radiusY);
        }

        ManagedSprite_SetPositionFxXYWithSubscreenOffset(param0->sprite, v1, v2, ((192 + 64) << FX32_SHIFT));

        if (param0->angle == 0) {
            param0->orbitCount++;

            if (param0->orbitCount >= param3) {
                param0->state++;
                return 1;
            } else {
                param0->state = 1;
            }
        }
        break;
    default:
        return 1;
    }

    return 0;
}

static void ResultsStepB(SysTask *param0, void *param1)
{
    int v0;
    WiFiLobbyMinigameManeneResultsAnimation *v1 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v2 = &v1->sprites;
    BOOL v3[4] = { 1, 1, 1, 1 };
    fx32 v4, v5;
    fx32 v6, v7;

    if ((IsScreenFadeDone() == FALSE) || (v1->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    switch (v1->step) {
    case 0:
        for (v0 = 0; v0 < v2->spriteCount; v0++) {
            v2->spritesA[v0].angle = 0;
            v2->spritesA[v0].baseX = 128;
            v2->spritesA[v0].baseY = (128 + 32);
            v2->spritesA[v0].radiusX = 64;
            v2->spritesA[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesA[v0].sprite, 1);

            v2->spritesB[v0].angle = 0;
            v2->spritesB[v0].baseX = 128;
            v2->spritesB[v0].baseY = (128 + 32);
            v2->spritesB[v0].radiusX = 64;
            v2->spritesB[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesB[v0].sprite, 1);

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesA[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusX);
            v5 = (v2->spritesA[v0].baseY << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesB[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusX);
            v5 = (v2->spritesB[v0].baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));
        }

        ResetResultsSprite(&v2->spritesB[0]);
        ResetResultsSprite(&v2->spritesB[1]);
        ResetResultsSprite(&v2->spritesA[0]);
        ResetResultsSprite(&v2->spritesA[1]);
        ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 0);
        v1->step++;
    case 1:
        v3[0] = ResultsSpriteMove1(&v2->spritesB[0], v2->animDurationA, 0, 3);
        v3[1] = ResultsSpriteMove2(&v2->spritesB[1], v2->animDurationA, 0, 2);
        v3[2] = ResultsSpriteMove3(&v2->spritesA[0], v2->animDurationB, 1, 3);
        v3[3] = 1;

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 1);
            v1->step++;
        } else {
            break;
        }

    case 2:
        v3[0] = 1;
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 0, 1);
        v3[2] = ResultsSpriteMove1(&v2->spritesA[0], v2->animDurationB, 1, 2);
        v3[3] = ResultsSpriteMove3(&v2->spritesA[1], v2->animDurationB, 1, 3);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            v1->step++;
        } else {
            break;
        }

    case 3:
        v3[0] = ResultsSpriteMove2(&v2->spritesB[0], v2->animDurationA, 0, 2);
        v3[1] = ResultsSpriteMove1(&v2->spritesB[1], v2->animDurationA, 0, 3);
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            v1->step++;
        } else {
            break;
        }

    case 4:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 0, 1);
        v3[1] = 1;
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            if (v2->repeatCounter != 1) {
                v2->repeatCounter++;
                v1->step = 1;
            } else {
                v2->repeatCounter = 0;
                v1->step++;
            }
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void ResultsStepC(SysTask *param0, void *param1)
{
    int v0;
    WiFiLobbyMinigameManeneResultsAnimation *v1 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v2 = &v1->sprites;
    BOOL v3[4] = { 1, 1, 1, 1 };
    fx32 v4, v5;
    fx32 v6, v7;

    if ((IsScreenFadeDone() == FALSE) || (v1->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    switch (v1->step) {
    case 0:
        for (v0 = 0; v0 < v2->spriteCount; v0++) {
            v2->spritesA[v0].angle = 0;
            v2->spritesA[v0].baseX = 128;
            v2->spritesA[v0].baseY = (128 + 32);
            v2->spritesA[v0].radiusX = 64;
            v2->spritesA[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesA[v0].sprite, 1);

            v2->spritesB[v0].angle = 0;
            v2->spritesB[v0].baseX = 128;
            v2->spritesB[v0].baseY = (128 + 32);
            v2->spritesB[v0].radiusX = 64;
            v2->spritesB[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesB[v0].sprite, 1);

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesA[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusX);
            v5 = (v2->spritesA[v0].baseY << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesB[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusX);
            v5 = (v2->spritesB[v0].baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));
        }

        ResetResultsSprite(&v2->spritesB[0]);
        ResetResultsSprite(&v2->spritesB[1]);
        ResetResultsSprite(&v2->spritesA[0]);
        ResetResultsSprite(&v2->spritesA[1]);
        ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 0);
        v1->step++;
    case 1:
        v3[0] = ResultsSpriteMove1(&v2->spritesB[0], v2->animDurationA, 0, 3);
        v3[1] = ResultsSpriteMove2(&v2->spritesB[1], v2->animDurationA, 0, 2);
        v3[2] = ResultsSpriteMove3(&v2->spritesA[0], v2->animDurationB, 1, 3);
        v3[3] = 1;
        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 1);
            v1->step++;
        } else {
            break;
        }
    case 2:
        v3[0] = 1;
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 0, 2);
        v3[2] = ResultsSpriteMove1(&v2->spritesA[0], v2->animDurationB, 1, 2);
        v3[3] = ResultsSpriteMove3(&v2->spritesA[1], v2->animDurationB, 1, 3);
        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            v1->step++;
        } else {
            break;
        }
    case 3:
        v3[0] = ResultsSpriteMove2(&v2->spritesB[0], v2->animDurationA, 0, 2);
        v3[1] = ResultsSpriteMove1(&v2->spritesB[1], v2->animDurationA, 0, 3);
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);
        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            v1->step++;
        } else {
            break;
        }
    case 4:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 0, 2);
        v3[1] = 1;
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);
        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            if (v2->repeatCounter != 1) {
                v2->repeatCounter++;
                v1->step = 1;
            } else {
                v2->repeatCounter = 0;
                v1->step++;
            }
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void ResultsStepD(SysTask *param0, void *param1)
{
    int v0;
    WiFiLobbyMinigameManeneResultsAnimation *v1 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v2 = &v1->sprites;
    BOOL v3[4] = { 1, 1, 1, 1 };
    fx32 v4, v5;
    fx32 v6, v7;

    if ((IsScreenFadeDone() == FALSE) || (v1->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    switch (v1->step) {
    case 0:
        for (v0 = 0; v0 < v2->spriteCount; v0++) {
            v2->spritesA[v0].angle = 0;
            v2->spritesA[v0].baseX = 128;
            v2->spritesA[v0].baseY = (128 + 32);
            v2->spritesA[v0].radiusX = 64;
            v2->spritesA[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesA[v0].sprite, 1);

            v2->spritesB[v0].angle = 0;
            v2->spritesB[v0].baseX = 128;
            v2->spritesB[v0].baseY = (128 + 32);
            v2->spritesB[v0].radiusX = 64;
            v2->spritesB[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesB[v0].sprite, 1);

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesA[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusX);
            v5 = (v2->spritesA[v0].baseY << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesB[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusX);
            v5 = (v2->spritesB[v0].baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));
        }

        ResetResultsSprite(&v2->spritesB[0]);
        ResetResultsSprite(&v2->spritesB[1]);
        ResetResultsSprite(&v2->spritesA[0]);
        ResetResultsSprite(&v2->spritesA[1]);
        ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 0);
        v1->step++;

    case 1:
        v3[0] = ResultsSpriteMove1(&v2->spritesB[0], v2->animDurationA, 0, 3);
        v3[1] = ResultsSpriteMove2(&v2->spritesB[1], v2->animDurationA, 0, 2);
        v3[2] = ResultsSpriteMove3(&v2->spritesA[0], v2->animDurationB, 1, 3);
        v3[3] = 1;

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 1);
            v1->step++;
        } else {
            break;
        }

    case 2:
        v3[0] = 1;
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 0, 1);
        v3[2] = ResultsSpriteMove1(&v2->spritesA[0], v2->animDurationB, 1, 2);
        v3[3] = ResultsSpriteMove3(&v2->spritesA[1], v2->animDurationB, 1, 3);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            v1->step++;
        } else {
            break;
        }

    case 3:
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 1, 1);
        if (v3[1]) {
            ResetResultsSprite(&v2->spritesB[1]);
            v1->step++;
        } else {
            break;
        }

    case 4:
        v3[0] = ResultsSpriteMove2(&v2->spritesB[0], v2->animDurationA, 0, 2);
        v3[1] = ResultsSpriteMove1(&v2->spritesB[1], v2->animDurationA, 0, 3);
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            v1->step++;
        } else {
            break;
        }

    case 5:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 0, 1);
        v3[1] = 1;
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            v1->step++;
        } else {
            break;
        }

    case 6:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 1, 1);

        if (v3[0]) {
            ResetResultsSprite(&v2->spritesB[0]);
            if (v2->repeatCounter != 1) {
                v2->repeatCounter++;
                v1->step = 1;
            } else {
                v2->repeatCounter = 0;
                v1->step++;
            }
        }
        break;
    default:
        SysTask_Done(param0);
        break;
    }
}

static void ResultsStepE(SysTask *param0, void *param1)
{
    int v0;
    WiFiLobbyMinigameManeneResultsAnimation *v1 = param1;
    WiFiLobbyMinigameManeneResultsSprites *v2 = &v1->sprites;
    BOOL v3[4] = { 1, 1, 1, 1 };
    fx32 v4, v5;
    fx32 v6, v7;

    if ((IsScreenFadeDone() == FALSE) || (v1->resources->disconnectState.disconnected == 1)) {
        SysTask_Done(param0);
        return;
    }

    switch (v1->step) {
    case 0:
        for (v0 = 0; v0 < v2->spriteCount; v0++) {
            v2->spritesA[v0].angle = 0;
            v2->spritesA[v0].baseX = 128;
            v2->spritesA[v0].baseY = (128 + 32);
            v2->spritesA[v0].radiusX = 64;
            v2->spritesA[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesA[v0].sprite, 1);

            v2->spritesB[v0].angle = 0;
            v2->spritesB[v0].baseX = 128;
            v2->spritesB[v0].baseY = (128 + 32);
            v2->spritesB[v0].radiusX = 64;
            v2->spritesB[v0].radiusY = 24;

            ManagedSprite_SetDrawFlag(v2->spritesB[v0].sprite, 1);

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesA[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusX);
            v5 = (v2->spritesA[v0].baseY << FX32_SHIFT) + (CalcCosineDegrees_Wraparound(v2->spritesA[v0].angle) * v2->spritesA[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesA[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));

            ManagedSprite_GetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, &v6, &v7, ((192 + 64) << FX32_SHIFT));
            v4 = (v2->spritesB[v0].baseX << FX32_SHIFT) + (CalcSineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusX);
            v5 = (v2->spritesB[v0].baseY << FX32_SHIFT) - (CalcCosineDegrees_Wraparound(v2->spritesB[v0].angle) * v2->spritesB[v0].radiusY);
            ManagedSprite_SetPositionFxXYWithSubscreenOffset(v2->spritesB[v0].sprite, v4, v5, ((192 + 64) << FX32_SHIFT));
        }

        ResetResultsSprite(&v2->spritesB[0]);
        ResetResultsSprite(&v2->spritesB[1]);
        ResetResultsSprite(&v2->spritesA[0]);
        ResetResultsSprite(&v2->spritesA[1]);
        ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 0);
        v1->step++;
    case 1:
        v3[0] = ResultsSpriteMove1(&v2->spritesB[0], v2->animDurationA, 0, 3);
        v3[1] = ResultsSpriteMove2(&v2->spritesB[1], v2->animDurationA, 0, 2);
        v3[2] = ResultsSpriteMove3(&v2->spritesA[0], v2->animDurationB, 1, 3);
        v3[3] = 1;

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);
            ManagedSprite_SetDrawFlag(v2->spritesA[1].sprite, 1);
            v1->step++;
        } else {
            break;
        }

    case 2:
        v3[0] = 1;
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 0, 1);
        v3[2] = ResultsSpriteMove1(&v2->spritesA[0], v2->animDurationB, 1, 2);
        v3[3] = ResultsSpriteMove3(&v2->spritesA[1], v2->animDurationB, 1, 3);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            v1->step++;
        } else {
            break;
        }

    case 3:
        v3[1] = ResultsSpriteOrbit(&v2->spritesB[1], v2->animDurationA, 1, 1);

        if (v3[1]) {
            ResetResultsSprite(&v2->spritesB[1]);
            v1->step++;
        } else {
            break;
        }

    case 4:
        v3[0] = ResultsSpriteMove2(&v2->spritesB[0], v2->animDurationA, 0, 2);
        v3[1] = ResultsSpriteMove1(&v2->spritesB[1], v2->animDurationA, 0, 3);
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            v1->step++;
        } else {
            break;
        }

    case 5:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 0, 1);
        v3[1] = 1;
        v3[2] = 1;
        v3[3] = ResultsSpriteMove1(&v2->spritesA[1], v2->animDurationB, 1, 2);

        if (v3[0] && v3[1] && v3[2] && v3[3]) {
            ResetResultsSprite(&v2->spritesB[0]);
            ResetResultsSprite(&v2->spritesB[1]);
            ResetResultsSprite(&v2->spritesA[0]);
            ResetResultsSprite(&v2->spritesA[1]);

            v1->step++;
        } else {
            break;
        }

    case 6:
        v3[0] = ResultsSpriteOrbit(&v2->spritesB[0], v2->animDurationA, 1, 1);

        if (v3[0]) {
            ResetResultsSprite(&v2->spritesB[0]);

            if (v2->repeatCounter != 8) {
                v2->repeatCounter++;
                v1->step = 1;
            } else {
                v2->repeatCounter = 0;
                v1->step++;
            }
        }

        break;
    default:
        SysTask_Done(param0);
        break;
    }
}
