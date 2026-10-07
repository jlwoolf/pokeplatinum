#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_comm_cmd.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_game.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_packet.h"

#include "communication_system.h"
#include "comm_cmd.h"

static void WiFiLobbyMinigameBalloon_CommCmdReceivePacket(int param0, int param1, void *param2, void *param3);
static void WiFiLobbyMinigameBalloon_CommCmdReceiveReady(int param0, int param1, void *param2, void *param3);
static void WiFiLobbyMinigameBalloon_CommCmdReceiveScore(int param0, int param1, void *param2, void *param3);
static int WiFiLobbyMinigameBalloon_CommPacketSize(void);
static int WiFiLobbyMinigameBalloon_CommPacketSizeU32(void);

static const CommCmdTable sCommCmdTable[] = {
    { NULL, CommPacketSizeOf_Nothing, NULL },
    { WiFiLobbyMinigameBalloon_CommCmdReceiveScore, WiFiLobbyMinigameBalloon_CommPacketSizeU32, NULL },
    { WiFiLobbyMinigameBalloon_CommCmdReceivePacket, WiFiLobbyMinigameBalloon_CommPacketSize, NULL },
    { WiFiLobbyMinigameBalloon_CommCmdReceiveReady, CommPacketSizeOf_Nothing, NULL }
};

void WiFiLobbyMinigameBalloon_InitCommCmd(void *param0)
{
    int v0 = sizeof(sCommCmdTable) / sizeof(CommCmdTable);

    CommCmd_Init(sCommCmdTable, v0, param0);
    GF_ASSERT(sizeof(WiFiLobbyMinigameBalloonPacket) < 256);
}

static int WiFiLobbyMinigameBalloon_CommPacketSize(void)
{
    return sizeof(WiFiLobbyMinigameBalloonPacket);
}

static int WiFiLobbyMinigameBalloon_CommPacketSizeU32(void)
{
    return sizeof(u32);
}

static void WiFiLobbyMinigameBalloon_CommCmdReceivePacket(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBalloonGame *v0 = param3;
    WiFiLobbyMinigameBalloon_QueueReceivedPacket(v0, param0, param2);
}

BOOL WiFiLobbyMinigameBalloon_SendPacket(WiFiLobbyMinigameBalloonGame *param0, WiFiLobbyMinigameBalloonPacket *param1)
{
    if (CommSys_SendData(24, param1, sizeof(WiFiLobbyMinigameBalloonPacket)) == 1) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_CommCmdReceiveReady(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBalloonGame *v0 = param3;
    v0->readyReceived = 1;
}

BOOL WiFiLobbyMinigameBalloon_SendReady(WiFiLobbyMinigameBalloonGame *param0)
{
    if (CommSys_SendData(25, NULL, 0) == 1) {
        return 1;
    }

    return 0;
}

static void WiFiLobbyMinigameBalloon_CommCmdReceiveScore(int param0, int param1, void *param2, void *param3)
{
    WiFiLobbyMinigameBalloonGame *v0 = param3;
    u32 *v1 = param2;
    u32 v2;
    int v3;

    v2 = v1[0];

    for (v3 = 0; v3 < v0->unk_00->unk_30; v3++) {
        if (v0->unk_00->unk_2C[v3] == param0) {
            v0->unk_0C[v3] = v2;
            break;
        }
    }

    GF_ASSERT(v3 < v0->unk_00->unk_30);
    v0->unk_08++;
}

BOOL WiFiLobbyMinigameBalloon_SendScore(WiFiLobbyMinigameBalloonGame *param0)
{
    u32 v0 = 100;

    if (CommSys_SendData(23, &v0, sizeof(u32)) == 1) {
        return 1;
    }

    return 0;
}
