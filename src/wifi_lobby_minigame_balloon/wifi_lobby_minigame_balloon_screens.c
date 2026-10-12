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
    WiFiLobbyMinigameBalloonContext *context;
    WiFiLobbyMinigameIntroScreen *introScreen;
    WiFiLobbyMinigameResultsScreen *resultsScreen;
} WiFiLobbyMinigameBalloonScreens;

int WiFiLobbyMinigameBalloon_ScreensInit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonScreens *v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameBalloonScreens), HEAP_ID_110);
    MI_CpuClear8(v0, sizeof(WiFiLobbyMinigameBalloonScreens));
    v0->context = ApplicationManager_Args(appMan);

    return 1;
}

int WiFiLobbyMinigameBalloon_ScreensMain(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBalloonScreens *v0 = ApplicationManager_Data(appMan);

    if (v0->context->disconnected == 1) {
        switch (v0->context->disconnectState) {
        case 0:
            if (IsScreenFadeDone() == TRUE) {
                FinishScreenFade();
            }

            SetColorBrightness(COLOR_BLACK);
            v0->context->disconnectState++;
            break;
        case 1:
            if (WiFiLobbyMinigame_HandleDisconnect(&v0->context->playerContext) == 1) {
                v0->context->disconnectState++;
            }
            break;
        default:
        case 2:
            if (v0->introScreen != NULL) {
                WiFiLobbyMinigame_FreeIntroScreen(v0->introScreen);
                v0->introScreen = NULL;
            }

            if (v0->resultsScreen != NULL) {
                WiFiLobbyMinigame_FreeResultsScreen(v0->resultsScreen);
                v0->resultsScreen = NULL;
            }

            return 1;
        }

        return 0;
    }

    switch (*param1) {
    case 0:
        if (v0->context->screenState == 0) {
            *param1 = 1;
        } else {
            *param1 = 3;
        }
        break;
    case 1:
        v0->introScreen = WiFiLobbyMinigame_CreateIntroScreen2(&v0->context->playerContext, HEAP_ID_110);
        (*param1)++;
        break;
    case 2:
        if (WiFiLobbyMinigame_IntroScreenIsDone(v0->introScreen) == 1) {
            v0->context->balloonLevel = WiFiLobbyMinigame_IntroScreenGetResult(v0->introScreen);
            WiFiLobbyMinigame_FreeIntroScreen(v0->introScreen);
            v0->introScreen = NULL;
            (*param1) = 5;
        }
        break;
    case 3:
        v0->resultsScreen = WiFiLobbyMinigame_CreateResultsScreen2(&v0->context->playerContext, &v0->context->ranking, HEAP_ID_110);
        (*param1)++;
        break;
    case 4:
        if (WiFiLobbyMinigame_ResultsScreenIsDone(v0->resultsScreen) == 1) {
            v0->context->results = WiFiLobbyMinigame_ResultsScreenGetResult(v0->resultsScreen);
            WiFiLobbyMinigame_FreeResultsScreen(v0->resultsScreen);
            v0->resultsScreen = NULL;
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
