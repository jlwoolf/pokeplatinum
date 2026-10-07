#include "wifi_comm.h"

#include <nitro.h>
#include <string.h>

#include "wifi_menu_app/wifi_menu_app_0223648C.h"
#include "wifi_menu_app/struct_wifi_menu_app_022366E4.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236744_decl.h"
#include "wifi_menu_app/struct_wifi_menu_app_02236760.h"

#include "comm_cmd.h"
#include "wifi_comm_cmd.h"

// Communication commands shared by the wifi_menu_app WiFi apps (the Nintendo WFC
// menu, WiFi battles and the Poffin/WiFi Plaza activity app). The command
// manager indexes the table returned by WiFiCommCmd_GetTable() with (cmd - 22), so its
// three entries are commands 22, 23 and 24:
//   22: player join/leave status (WiFiCommPlayerStatus, fixed size)
//   23: sync request, no payload
//   24: voice chat enable flags (WiFiCommVoiceChatFlags, fixed size)
// Each handler forwards the packet to wifi_menu_app along with the app state that
// was registered by WiFiComm_Init.

// Registers the WiFi command table with the given app state as the context that
// the command manager passes back to every handler.
void WiFiComm_Init(WiFiCommApp *app)
{
    CommCmd_Init(WiFiCommCmd_GetTable(), WiFiCommCmd_GetTableCount(), app);
}

// Registers the same table with no context, so any command that arrives while
// no WiFi app is running is dropped by the NULL checks below. Called before a
// WiFi battle starts, when no WiFi app state is registered yet.
void WiFiComm_InitNoContext(void)
{
    CommCmd_Init(WiFiCommCmd_GetTable(), WiFiCommCmd_GetTableCount(), NULL);
}

// Packet-size callbacks for the command table. Commands 22 and 24 carry a
// fixed struct; command 23 has no payload.

int WiFiComm_SyncPacketSize(void)
{
    return 0;
}

int WiFiComm_PlayerStatusPacketSize(void)
{
    return sizeof(WiFiCommPlayerStatus);
}

int WiFiComm_VoiceChatPacketSize(void)
{
    return sizeof(WiFiCommVoiceChatFlags);
}

// Command 22: a player joined, left or changed connection state.
void WiFiComm_RecvPlayerStatus(int netId, int size, void *data, void *context)
{
    WiFiCommApp *app = context;
    WiFiCommPlayerStatus *packet = data;

    if (app == NULL) {
        return;
    }

    WiFiCommApp_HandlePlayerStatus(app, packet);
}

// Command 23: asks all players to begin the WiFi sync.
void WiFiComm_RecvSyncRequest(int netId, int size, void *data, void *context)
{
    WiFiCommApp *app = context;

    if (app == NULL) {
        return;
    }

    WiFiCommApp_RequestSync(app);
}

// Command 24: carries the four players' voice chat enable flags.
void WiFiComm_RecvVoiceChat(int netId, int size, void *data, void *context)
{
    WiFiCommApp *app = context;

    if (app == NULL) {
        return;
    }

    WiFiCommApp_HandleVoiceChatFlags(app, data);
}
