#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon_screens.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_context.h"

#include "overlay_manager.h"
#include "screen_fade.h"

typedef struct {
    WiFiLobbyMinigameBalloonContext *unk_00;
    WiFiLobbyMinigameIntroScreen *unk_04;
    WiFiLobbyMinigameResultsScreen *unk_08;
} WiFiLobbyMinigameBalloonScreens;

int WiFiLobbyMinigameBalloon_ScreensInit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonScreens *v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameBalloonScreens), HEAP_ID_110);
    MI_CpuClear8(v0, sizeof(WiFiLobbyMinigameBalloonScreens));
    v0->unk_00 = ApplicationManager_Args(appMan);

    return 1;
}

int WiFiLobbyMinigameBalloon_ScreensMain(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonScreens *v0 = ApplicationManager_Data(appMan);

    if (v0->unk_00->disconnected == 1) {
        switch (v0->unk_00->disconnectState) {
        case 0:
            if (IsScreenFadeDone() == TRUE) {
                FinishScreenFade();
            }

            SetColorBrightness(COLOR_BLACK);
            v0->unk_00->disconnectState++;
            break;
        case 1:
            if (WiFiLobbyMinigame_HandleDisconnect(&v0->unk_00->unk_00) == 1) {
                v0->unk_00->disconnectState++;
            }
            break;
        default:
        case 2:
            if (v0->unk_04 != NULL) {
                WiFiLobbyMinigame_FreeIntroScreen(v0->unk_04);
                v0->unk_04 = NULL;
            }

            if (v0->unk_08 != NULL) {
                WiFiLobbyMinigame_FreeResultsScreen(v0->unk_08);
                v0->unk_08 = NULL;
            }

            return 1;
        }

        return 0;
    }

    switch (*param1) {
    case 0:
        if (v0->unk_00->screenState == 0) {
            *param1 = 1;
        } else {
            *param1 = 3;
        }
        break;
    case 1:
        v0->unk_04 = WiFiLobbyMinigame_CreateIntroScreen2(&v0->unk_00->unk_00, HEAP_ID_110);
        (*param1)++;
        break;
    case 2:
        if (WiFiLobbyMinigame_IntroScreenIsDone(v0->unk_04) == 1) {
            v0->unk_00->balloonLevel = WiFiLobbyMinigame_IntroScreenGetResult(v0->unk_04);
            WiFiLobbyMinigame_FreeIntroScreen(v0->unk_04);
            v0->unk_04 = NULL;
            (*param1) = 5;
        }
        break;
    case 3:
        v0->unk_08 = WiFiLobbyMinigame_CreateResultsScreen2(&v0->unk_00->unk_00, &v0->unk_00->unk_10, HEAP_ID_110);
        (*param1)++;
        break;
    case 4:
        if (WiFiLobbyMinigame_ResultsScreenIsDone(v0->unk_08) == 1) {
            v0->unk_00->unk_38 = WiFiLobbyMinigame_ResultsScreenGetResult(v0->unk_08);
            WiFiLobbyMinigame_FreeResultsScreen(v0->unk_08);
            v0->unk_08 = NULL;
            (*param1) = 5;
        }

        break;
    case 5:
    default:
        return 1;
    }

    return 0;
}

int WiFiLobbyMinigameBalloon_ScreensExit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonScreens *v0 = ApplicationManager_Data(appMan);
    ApplicationManager_FreeData(appMan);

    return 1;
}
