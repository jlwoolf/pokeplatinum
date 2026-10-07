#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "nintendo_wfc/main.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_app.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_screens.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_args.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_context.h"

#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "heap.h"
#include "overlay_manager.h"
#include "comm_tool.h"

static const ApplicationManagerTemplate sMainAppTemplate = {
    WiFiLobbyMinigameBalloon_AppInit,
    WiFiLobbyMinigameBalloon_AppMain,
    WiFiLobbyMinigameBalloon_AppExit,
    0xFFFFFFFF
};

static const ApplicationManagerTemplate sScreensAppTemplate = {
    WiFiLobbyMinigameBalloon_ScreensInit,
    WiFiLobbyMinigameBalloon_ScreensMain,
    WiFiLobbyMinigameBalloon_ScreensExit,
    0xFFFFFFFF
};

static void WiFiLobbyMinigameBalloon_InitPlayerContext(WiFiLobbyMinigameBalloonContext *param0, WiFiLobbyMinigameBalloonArgs *param1);
static BOOL WiFiLobbyMinigameBalloon_CheckDisconnected(WiFiLobbyMinigameBalloonContext *param0);

int WiFiLobbyMinigameBalloon_Init(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonArgs *v0 = ApplicationManager_Args(appMan);
    WiFiLobbyMinigameBalloonContext *v1;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_110, 0x60000);

    v1 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameBalloonContext), HEAP_ID_110);
    MI_CpuClear8(v1, sizeof(WiFiLobbyMinigameBalloonContext));
    WiFiLobbyMinigameBalloon_InitPlayerContext(v1, v0);

    return 1;
}

int WiFiLobbyMinigameBalloon_Main(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonContext *v0 = ApplicationManager_Data(appMan);
    WiFiLobbyMinigameBalloonArgs *v1 = ApplicationManager_Args(appMan);

    if (WiFiLobbyMinigameBalloon_CheckDisconnected(v0) == 1) {
        return 1;
    }

    switch (*param1) {
    case 0:
        v0->screenState = 0;
        v0->appMan = ApplicationManager_New(&sScreensAppTemplate, v0, HEAP_ID_110);
        (*param1)++;
        break;
    case 1:
        if (ApplicationManager_Exec(v0->appMan) == 1) {
            ApplicationManager_Free(v0->appMan);
            v0->appMan = NULL;
            (*param1)++;
        }
        break;
    case 2:
        v0->screenState = 1;
        v0->appMan = ApplicationManager_New(&sMainAppTemplate, v0, HEAP_ID_110);
        (*param1)++;
        break;
    case 3:
        if (ApplicationManager_Exec(v0->appMan) == 1) {
            ApplicationManager_Free(v0->appMan);
            v0->appMan = NULL;
            (*param1)++;
        }
        break;
    case 4:
        if (v1->unk_38) {
            NintendoWFC_TerminateVoiceChat();
        }

        v0->screenState = 2;
        v0->appMan = ApplicationManager_New(&sScreensAppTemplate, v0, HEAP_ID_110);
        (*param1)++;
        break;
    case 5:
        if (ApplicationManager_Exec(v0->appMan) == 1) {
            ApplicationManager_Free(v0->appMan);
            v0->appMan = NULL;

            if (v0->unk_38 == 1) {
                (*param1) = 0;
            } else {
                (*param1)++;
            }
        }
        break;
    case 6:
        CommManager_SetErrorHandling(0, 1);
        CommTiming_StartSync(222);
        (*param1)++;
        break;
    case 7:
        if ((CommTiming_IsSyncState(222) == 1) || (CommSys_ConnectedCount() < CommInfo_CountReceived())) {
            (*param1)++;
        }

        break;
    case 8:
    default:
        return 1;
    }

    return 0;
}

int WiFiLobbyMinigameBalloon_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonContext *v0 = ApplicationManager_Data(appMan);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_110);

    return 1;
}

static void WiFiLobbyMinigameBalloon_InitPlayerContext(WiFiLobbyMinigameBalloonContext *param0, WiFiLobbyMinigameBalloonArgs *param1)
{
    int v0, v1, v2, v3;

    v3 = CommSys_CurNetId();
    v2 = 0;
    v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if (CommInfo_TrainerInfo(v0) != NULL) {
            param0->unk_2C[v1] = v0;

            if (v0 == v3) {
                v2 = v1;
            }

            v1++;
        } else {
            param0->unk_2C[v0] = 0xffff;
        }
    }

    param0->unk_30 = v1;
    param0->voiceChatEnabled = param1->unk_38;

    WiFiLobbyMinigame_InitPlayerContext(&param0->unk_00, param1->unk_39, param1->saveData, param1->unk_38, &param1->unk_00);
}

static BOOL WiFiLobbyMinigameBalloon_CheckDisconnected(WiFiLobbyMinigameBalloonContext *param0)
{
    if (param0->disconnected == 0) {
        if (WiFiLobbyMinigame_CheckDisconnected(&param0->unk_00) == 1) {
            param0->disconnected = 1;
        }
    }

    if (param0->disconnected == 1) {
        if (param0->appMan == NULL) {
            return 1;
        }
    }

    return 0;
}
