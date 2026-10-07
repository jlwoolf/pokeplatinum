#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_comm_cmd_handlers.h"

#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_graphics.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_score_packet.h"

#include "communication_system.h"

static void WiFiLobbyMinigameBalloon_HandleSync(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandleScorePacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandleBalloonLevel(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandleBalloonPop(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandlePlayerState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandleGameState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);
static void WiFiLobbyMinigameBalloon_HandleSync2(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1);

static void (*const sPacketHandlers[])(WiFiLobbyMinigameBalloonGame *, const WiFiLobbyMinigameBalloonPacket *) = {
    NULL,
    WiFiLobbyMinigameBalloon_HandleScorePacket,
    WiFiLobbyMinigameBalloon_HandleBalloonLevel,
    WiFiLobbyMinigameBalloon_HandleBalloonPop,
    WiFiLobbyMinigameBalloon_HandlePlayerState,
    WiFiLobbyMinigameBalloon_HandleGameState,
    WiFiLobbyMinigameBalloon_HandleSync,
    WiFiLobbyMinigameBalloon_HandleSync2,
};

#ifdef _NITRO
SDK_COMPILER_ASSERT(NELEMS(sPacketHandlers) == 8);
#endif

BOOL WiFiLobbyMinigameBalloon_HandlePacket(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPacket *param1)
{
    if (sPacketHandlers[param1->unk_00] != NULL) {
        sPacketHandlers[param1->unk_00](param0, param1);
        MI_CpuClear8(param1, sizeof(WiFiLobbyMinigameBalloonPacket));
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameBalloon_SendScorePacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonScorePacket *param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 1;
    v0.unk_04_val4 = *param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleScorePacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    if (param1->unk_04_val4.unk_00 == CommSys_CurNetId()) {
        return;
    }

    WiFiLobbyMinigameBalloon_SpawnPopEffect(param0, &param1->unk_04_val4);
}

void WiFiLobbyMinigameBalloon_SendBalloonLevel(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 2;
    v0.unk_04_val5.unk_00 = param1;
    v0.unk_04_val5.unk_02 = 5;
    v0.unk_04_val5.unk_03 = param2;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleBalloonLevel(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->popCount++;

    WiFiLobbyMinigameBalloon_StartConfetti(param0);
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val5.unk_02, param1->unk_04_val5.unk_03);
}

void WiFiLobbyMinigameBalloon_SendBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2, u8 param3)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 3;
    v0.unk_04_val6.unk_00 = param1;
    v0.unk_04_val6.unk_02 = param2;
    v0.unk_04_val6.unk_03 = 4;
    v0.unk_04_val6.unk_04 = param3;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleBalloonPop(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->balloonLevel = param1->unk_04_val6.unk_00;
    WiFiLobbyMinigameBalloon_StartScoreGauge(param0->unk_2C, param0->unk_00->unk_30, param1->unk_04_val6.unk_02, &param0->scoreGauge);
    param0->gaugeActive = 1;

    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val6.unk_03, param1->unk_04_val6.unk_04);
}

void WiFiLobbyMinigameBalloon_SendPlayerState(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 4;
    v0.unk_04_val1.unk_00 = 2;
    v0.unk_04_val1.unk_01 = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandlePlayerState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->unk_20 = 3;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val2.unk_00, param1->unk_04_val2.unk_01);
}

void WiFiLobbyMinigameBalloon_SendGameState(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 5;
    v0.unk_04_val3.unk_00 = 3;
    v0.unk_04_val3.unk_01 = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleGameState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->gameEnded = 1;
    param0->unk_20 = 6;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val3.unk_00, param1->unk_04_val3.unk_01);
}

void WiFiLobbyMinigameBalloon_SendSync(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 6;
    v0.unk_04_val1.unk_00 = param1;
    v0.unk_04_val1.unk_01 = param2;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleSync(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val1.unk_00, param1->unk_04_val1.unk_01);
}

void WiFiLobbyMinigameBalloon_SendSync2(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.unk_00 = 7;
    v0.unk_04_val1.unk_00 = 6;
    v0.unk_04_val1.unk_01 = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleSync2(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->unk_20 = 1;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->unk_04_val2.unk_00, param1->unk_04_val2.unk_01);
}
