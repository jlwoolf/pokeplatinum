#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene_02266FEC.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_02266FEC.h"
#include "wifi_lobby_minigame_manene/union_wifi_lobby_minigame_manene_022671EC.h"

void WiFiLobbyMinigameManene_QuaternionIdentity(WiFiLobbyMinigameManeneQuaternion *param0)
{
    param0->val1_00 = 1.0;
    param0->val1_04 = 0;
    param0->val1_08 = 0;
    param0->val1_0C = 0;
}

void WiFiLobbyMinigameManene_QuaternionCopy(WiFiLobbyMinigameManeneQuaternion *param0, WiFiLobbyMinigameManeneQuaternion *param1)
{
    *param0 = *param1;
}

void WiFiLobbyMinigameManene_QuaternionMultiply(WiFiLobbyMinigameManeneQuaternion *param0, const WiFiLobbyMinigameManeneQuaternion *param1, const WiFiLobbyMinigameManeneQuaternion *param2)
{
    param0->val1_00 = (param1->val1_00 * param2->val1_00) - (param1->val1_04 * param2->val1_04) - (param1->val1_08 * param2->val1_08) - (param1->val1_0C * param2->val1_0C);
    param0->val1_04 = (param1->val1_00 * param2->val1_04) + (param1->val1_04 * param2->val1_00) + (param1->val1_08 * param2->val1_0C) - (param1->val1_0C * param2->val1_08);
    param0->val1_08 = (param1->val1_00 * param2->val1_08) - (param1->val1_04 * param2->val1_0C) + (param1->val1_08 * param2->val1_00) + (param1->val1_0C * param2->val1_04);
    param0->val1_0C = (param1->val1_00 * param2->val1_0C) + (param1->val1_04 * param2->val1_08) - (param1->val1_08 * param2->val1_04) + (param1->val1_0C * param2->val1_00);
}

f32 WiFiLobbyMinigameManene_QuaternionMagnitudeSquared(const WiFiLobbyMinigameManeneQuaternion *param0)
{
    return (param0->val1_00 * param0->val1_00) + (param0->val1_04 + param0->val1_04) + (param0->val1_08 + param0->val1_08) + (param0->val1_0C + param0->val1_0C);
}

f32 WiFiLobbyMinigameManene_QuaternionMagnitude(const WiFiLobbyMinigameManeneQuaternion *param0)
{
    fx32 v0;

    v0 = FX_F32_TO_FX32(WiFiLobbyMinigameManene_QuaternionMagnitudeSquared(param0));
    return FX_FX32_TO_F32(FX_Sqrt(v0));
}

void WiFiLobbyMinigameManene_QuaternionScale(WiFiLobbyMinigameManeneQuaternion *param0, const WiFiLobbyMinigameManeneQuaternion *param1, f32 param2)
{
    param0->val1_00 = param1->val1_00 / param2;
    param0->val1_04 = param1->val1_04 / param2;
    param0->val1_08 = param1->val1_08 / param2;
    param0->val1_0C = param1->val1_0C / param2;
}

void WiFiLobbyMinigameManene_QuaternionToMatrix(WiFiLobbyMinigameManeneMatrix *param0, const WiFiLobbyMinigameManeneQuaternion *param1)
{
    f32 v0 = param1->val1_04 * param1->val1_04 * 2.0;
    f32 v1 = param1->val1_08 * param1->val1_08 * 2.0;
    f32 v2 = param1->val1_0C * param1->val1_0C * 2.0;
    f32 v3 = param1->val1_04 * param1->val1_08 * 2.0;
    f32 v4 = param1->val1_08 * param1->val1_0C * 2.0;
    f32 v5 = param1->val1_0C * param1->val1_04 * 2.0;
    f32 v6 = param1->val1_04 * param1->val1_00 * 2.0;
    f32 v7 = param1->val1_08 * param1->val1_00 * 2.0;
    f32 v8 = param1->val1_0C * param1->val1_00 * 2.0;

    param0->val1_00 = 1.0 - v1 - v2;
    param0->val1_04 = v3 + v8;
    param0->val1_08 = v5 - v7;
    param0->val1_0C = 0.0;
    param0->val1_10 = v3 - v8;
    param0->val1_14 = 1.0 - v2 - v0;
    param0->val1_18 = v4 + v6;
    param0->val1_1C = 0.0;
    param0->val1_20 = v5 + v7;
    param0->val1_24 = v4 - v6;
    param0->val1_28 = 1.0 - v0 - v1;
    param0->val1_2C = 0.0;
    param0->val1_30 = 0.0;
    param0->val1_34 = 0.0;
    param0->val1_38 = 0.0;
    param0->val1_3C = 1.0;
}

void WiFiLobbyMinigameManene_MatrixToMtx44(const WiFiLobbyMinigameManeneMatrix *param0, MtxFx44 *param1)
{
    param1->_00 = FX32_CONST(param0->val1_00);
    param1->_01 = FX32_CONST(param0->val1_04);
    param1->_02 = FX32_CONST(param0->val1_08);
    param1->_03 = FX32_CONST(param0->val1_0C);
    param1->_10 = FX32_CONST(param0->val1_10);
    param1->_11 = FX32_CONST(param0->val1_14);
    param1->_12 = FX32_CONST(param0->val1_18);
    param1->_13 = FX32_CONST(param0->val1_1C);
    param1->_20 = FX32_CONST(param0->val1_20);
    param1->_21 = FX32_CONST(param0->val1_24);
    param1->_22 = FX32_CONST(param0->val1_28);
    param1->_23 = FX32_CONST(param0->val1_2C);
    param1->_30 = FX32_CONST(param0->val1_30);
    param1->_31 = FX32_CONST(param0->val1_34);
    param1->_32 = FX32_CONST(param0->val1_38);
    param1->_33 = FX32_CONST(param0->val1_3C);
}

void WiFiLobbyMinigameManene_MatrixToMtx43(const WiFiLobbyMinigameManeneMatrix *param0, MtxFx43 *param1)
{
    MtxFx44 v0;

    WiFiLobbyMinigameManene_MatrixToMtx44(param0, &v0);
    MTX_Copy44To43(&v0, param1);
}
