#include "wifi_plaza_lobby/wifi_plaza_lobby.h"

#include <nitro.h>
#include <ppwlobby/ppw_lobby.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_02230C44.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230C90_decl.h"

#include "game_overlay.h"
#include "heap.h"
#include "overlay_manager.h"
#include "savedata.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"
#include "wifi_overlays.h"

FS_EXTERN_OVERLAY(wifi_2d_char);

typedef struct {
    SaveData *saveData;
    WiFiPlazaLobbyState *state;
    WiFiPlazaLobbyAppManager *appManager;
    SysTask *vblankTask;
} WiFiPlazaLobbyAppData;

static void WiFiPlazaLobby_VBlankTask(SysTask *param0, void *param1);

int WiFiPlazaLobby_Init(ApplicationManager *appMan, int *param1)
{
    WiFiPlazaLobbyAppData *v0;
    WiFiPlazaLobbyAppArgs *v1;

    {
        FS_EXTERN_OVERLAY(wifi_2d_char);
        Overlay_LoadByID(FS_OVERLAY_ID(wifi_2d_char), 2);
        Overlay_LoadWFCOverlay();
        Overlay_LoadHttpOverlay();
    }

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_104, 0x5000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiPlazaLobbyAppData), HEAP_ID_104);
    memset(v0, 0, sizeof(WiFiPlazaLobbyAppData));

    v1 = ApplicationManager_Args(appMan);

    v0->saveData = v1->saveData;
    v0->state = WiFiPlazaLobby_State_Create(v0->saveData, HEAP_ID_104);
    v0->appManager = WiFiPlazaLobby_AppManager_New(v1->wifiMenuResult, v1->saveData, v1->cooldownTimestamp, v0->state, HEAP_ID_104);

    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    v0->vblankTask = SysTask_ExecuteAfterVBlank(WiFiPlazaLobby_VBlankTask, v0, 0);

    WiFiPlazaLobby_AppManager_ConnectToWifiPlaza(v0->appManager);

    return 1;
}

int WiFiPlazaLobby_Main(ApplicationManager *appMan, int *param1)
{
    WiFiPlazaLobbyAppData *v0;
    int v1;

    v0 = ApplicationManager_Data(appMan);
    v1 = WiFiPlazaLobby_AppManager_Update(v0->appManager);

    WiFiPlazaLobby_State_Init(v0->state);

    if (v1 == 1) {
        return 1;
    }

    return 0;
}

int WiFiPlazaLobby_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiPlazaLobbyAppData *v0 = ApplicationManager_Data(appMan);

    SysTask_Done(v0->vblankTask);
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    WiFiPlazaLobby_AppManager_Free(v0->appManager);
    WiFiPlazaLobby_State_Destroy(v0->state);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_104);

    {
        FS_EXTERN_OVERLAY(wifi_2d_char);
        Overlay_UnloadByID(FS_OVERLAY_ID(wifi_2d_char));
        Overlay_UnloadHttpOverlay();
        Overlay_UnloadWFCOverlay();
    }

    return 1;
}

static void WiFiPlazaLobby_VBlankTask(SysTask *param0, void *param1)
{
    WiFiPlazaLobbyAppData *v0 = param1;

    WiFiPlazaLobby_AppManager_VBlankUpdate(v0->appManager);
    WiFiPlazaLobby_State_UpdateNoop(v0->state);
}
