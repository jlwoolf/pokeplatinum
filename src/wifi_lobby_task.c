#include "wifi_lobby_task.h"

#include <nitro.h>
#include <string.h>

#include "field/field_system.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0.h"

#include "field_task.h"
#include "heap.h"

FS_EXTERN_OVERLAY(wifi_plaza_lobby);

// Field task that opens the Wi-Fi lobby (wifi_plaza_lobby, the PPW / Wi-Fi Plaza
// lobby). It is started by the ScrCmd_2F7 script command once the player has a
// valid Nintendo WFC login.
typedef struct {
    // State machine state (see WiFiLobbyTask_Task).
    u16 state;
    // Result reported by the preceding WiFi menu (ScrCmd_0B3), forwarded to the
    // lobby app arguments.
    u16 wifiMenuResult;
    // Arguments handed to the wifi_plaza_lobby lobby app.
    WiFiPlazaLobbyAppArgs appArgs;
} WiFiLobbyTaskWork;

static BOOL WiFiLobbyTask_Task(FieldTask *task);

// The wifi_plaza_lobby lobby app (WiFiPlazaLobby_Init) that the task launches as a child
// process.
static const ApplicationManagerTemplate sWiFiLobbyAppTemplate = {
    WiFiPlazaLobby_Init,
    WiFiPlazaLobby_Main,
    WiFiPlazaLobby_Exit,
    FS_OVERLAY_ID(wifi_plaza_lobby)
};

// Starts the Wi-Fi lobby field task. `wifiMenuResult` is the result reported by
// the preceding WiFi menu and is forwarded to the lobby app.
void WiFiLobbyTask_Start(FieldTask *task, BOOL wifiMenuResult)
{
    WiFiLobbyTaskWork *work = Heap_AllocAtEnd(HEAP_ID_FIELD2, sizeof(WiFiLobbyTaskWork));
    memset(work, 0, sizeof(WiFiLobbyTaskWork));

    work->wifiMenuResult = wifiMenuResult;
    FieldTask_InitCall(task, WiFiLobbyTask_Task, work);
}

static BOOL WiFiLobbyTask_Task(FieldTask *task)
{
    FieldSystem *fieldSystem = FieldTask_GetFieldSystem(task);
    WiFiLobbyTaskWork *work = FieldTask_GetEnv(task);

    switch (work->state) {
    case 0: {
        work->appArgs.saveData = fieldSystem->saveData;
        work->appArgs.unk_08 = work->wifiMenuResult;
        work->appArgs.unk_00 = &fieldSystem->unk_C4;
        FieldTask_RunApplication(task, &sWiFiLobbyAppTemplate, &work->appArgs);
        work->state++;
    } break;
    case 1:
        Heap_Free(work);
        return 1;
    }

    return 0;
}
