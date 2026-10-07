#include "wifi_lobby_minigame/wifi_lobby_minigame_comm_cmd.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "wifi_lobby_minigame/wifi_lobby_minigame_comm_cmd_handlers.h"

static const CommCmdTable sCommCmdTable[] = {
    { WiFiLobbyMinigame_CommCmdSetPlayerReady, WiFiLobbyMinigame_CommCmdGetSize0, NULL },
    { WiFiLobbyMinigame_CommCmdSetPlayerNotReady, WiFiLobbyMinigame_CommCmdGetSize0, NULL },
    { WiFiLobbyMinigame_CommCmdSetAllReady, WiFiLobbyMinigame_CommCmdGetSize0, NULL },
    { WiFiLobbyMinigame_CommCmdSetNotAllReady, WiFiLobbyMinigame_CommCmdGetSize0, NULL },
    { WiFiLobbyMinigame_CommCmdSetIntroResult, WiFiLobbyMinigame_CommCmdGetSize4, NULL },
};

const CommCmdTable *WiFiLobbyMinigame_GetCommCmdTable(void)
{
    return sCommCmdTable;
}

int WiFiLobbyMinigame_GetCommCmdTableSize(void)
{
    return sizeof(sCommCmdTable) / sizeof(CommCmdTable);
}
