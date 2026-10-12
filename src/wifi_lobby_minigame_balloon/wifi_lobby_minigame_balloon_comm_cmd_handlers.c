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
    if (sPacketHandlers[param1->type] != NULL) {
        sPacketHandlers[param1->type](param0, param1);
        MI_CpuClear8(param1, sizeof(WiFiLobbyMinigameBalloonPacket));
        return 1;
    }

    return 0;
}

void WiFiLobbyMinigameBalloon_SendScorePacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonScorePacket *param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 1;
    v0.scorePacket = *param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleScorePacket(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    if (param1->scorePacket.netId == CommSys_CurNetId()) {
        return;
    }

    WiFiLobbyMinigameBalloon_SpawnPopEffect(param0, &param1->scorePacket);
}

void WiFiLobbyMinigameBalloon_SendBalloonLevel(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 2;
    v0.packetScore.balloonLevel = param1;
    v0.packetScore.syncState = 5;
    v0.packetScore.syncId = param2;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleBalloonLevel(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->popCount++;

    WiFiLobbyMinigameBalloon_StartConfetti(param0);
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->packetScore.syncState, param1->packetScore.syncId);
}

void WiFiLobbyMinigameBalloon_SendBalloonPop(WiFiLobbyMinigameBalloonGame *param0, int param1, int param2, u8 param3)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 3;
    v0.packetScoreEx.balloonLevel = param1;
    v0.packetScoreEx.gaugeLevel = param2;
    v0.packetScoreEx.syncState = 4;
    v0.packetScoreEx.syncId = param3;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleBalloonPop(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->balloonLevel = param1->packetScoreEx.balloonLevel;
    WiFiLobbyMinigameBalloon_StartScoreGauge(param0->bgConfig, param0->context->playerCount, param1->packetScoreEx.gaugeLevel, &param0->scoreGauge);
    param0->gaugeActive = 1;

    WiFiLobbyMinigameBalloon_StartSync(param0, param1->packetScoreEx.syncState, param1->packetScoreEx.syncId);
}

void WiFiLobbyMinigameBalloon_SendPlayerState(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 4;
    v0.statePair.syncState = 2;
    v0.statePair.syncId = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandlePlayerState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->phase = 3;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->statePair2.syncState, param1->statePair2.syncId);
}

void WiFiLobbyMinigameBalloon_SendGameState(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 5;
    v0.gameStatePair.syncState = 3;
    v0.gameStatePair.syncId = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleGameState(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->gameEnded = 1;
    param0->phase = 6;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->gameStatePair.syncState, param1->gameStatePair.syncId);
}

void WiFiLobbyMinigameBalloon_SendSync(WiFiLobbyMinigameBalloonGame *param0, int param1, u8 param2)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 6;
    v0.statePair.syncState = param1;
    v0.statePair.syncId = param2;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleSync(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->statePair.syncState, param1->statePair.syncId);
}

void WiFiLobbyMinigameBalloon_SendSync2(WiFiLobbyMinigameBalloonGame *param0, u8 param1)
{
    WiFiLobbyMinigameBalloonPacket v0;

    MI_CpuClear8(&v0, sizeof(WiFiLobbyMinigameBalloonPacket));

    v0.type = 7;
    v0.statePair.syncState = 6;
    v0.statePair.syncId = param1;

    WiFiLobbyMinigameBalloon_QueueSendPacket(param0, &v0);
}

static void WiFiLobbyMinigameBalloon_HandleSync2(WiFiLobbyMinigameBalloonGame *param0, const WiFiLobbyMinigameBalloonPacket *param1)
{
    param0->phase = 1;
    WiFiLobbyMinigameBalloon_StartSync(param0, param1->statePair2.syncState, param1->statePair2.syncId);
}
