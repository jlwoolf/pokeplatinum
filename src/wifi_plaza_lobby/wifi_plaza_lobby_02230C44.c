#include "wifi_plaza_lobby/wifi_plaza_lobby_02230C44.h"

#include <nitro.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_0222DDF0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DCE0_sub1.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0222DFF8_decl.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230DBC.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230E68.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230F50.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02230FA0.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231024.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231134.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_0223127C.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231300.h"
#include "wifi_plaza_lobby/struct_wifi_plaza_lobby_02231374.h"
#include "wifi_p2p_match/wifi_p2p_match.h"
#include "wifi_lobby_questionnaire/wifi_lobby_questionnaire.h"
#include "wifi_earth/wifi_earth.h"
#include "wifi_lobby_map/wifi_lobby_map_0225D9A4.h"
#include "wifi_lobby_news/wifi_lobby_news.h"
#include "footprint_stamp/footprint_stamp.h"
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_args.h"
#include "wifi_lobby_minigame_manene/wifi_lobby_minigame_manene.h"
#include "wifi_lobby_minigame_balloon/wifi_lobby_minigame_balloon.h"
#include "wifi_lobby_minigame_balloon/struct_wifi_lobby_minigame_balloon_args.h"

#include "game_overlay.h"
#include "heap.h"
#include "overlay_manager.h"
#include "savedata.h"
#include "trainer_info.h"

FS_EXTERN_OVERLAY(wifi_p2p_match);
FS_EXTERN_OVERLAY(wifi_lobby_questionnaire);
FS_EXTERN_OVERLAY(wifi_earth);
FS_EXTERN_OVERLAY(wifi_lobby_map);
FS_EXTERN_OVERLAY(wifi_lobby_news);
FS_EXTERN_OVERLAY(footprint_stamp);
FS_EXTERN_OVERLAY(wifi_lobby_minigame);
FS_EXTERN_OVERLAY(wifi_lobby_minigame_bucket);
FS_EXTERN_OVERLAY(wifi_lobby_minigame_manene);
FS_EXTERN_OVERLAY(wifi_lobby_minigame_balloon);

typedef struct {
    void *data;
} WiFiPlazaLobbySubAppSlot;

typedef struct WiFiPlazaLobbyAppManager_t {
    ApplicationManager *appMan;
    WiFiPlazaLobbySubAppSlot subApps[13];
    u8 currentSubApp;
    u8 wifiMenuResult;
    u16 heapID;
    WiFiPlazaLobbyState *state;
    SaveData *saveData;
    WiFiPlazaLobbyCooldownTimestamp *cooldownTimestamp;
} WiFiPlazaLobbyAppManager;

static void WiFiPlazaLobby_AppManager_CreateSubApp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, const ApplicationManagerTemplate *param2);
static void WiFiPlazaLobby_AppManager_InitSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1);
static void WiFiPlazaLobby_AppManager_StartSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1);
static int WiFiPlazaLobby_AppManager_UpdateSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1);
static void WiFiPlazaLobby_AppManager_InitParticipants(WiFiPlazaLobbyMinigameParticipants *param0, u32 param1);
static void WiFiPlazaLobby_AppManager_FreeParticipants(WiFiPlazaLobbyMinigameParticipants *param0);
static void WiFiPlazaLobby_AppManager_SetupParticipants(WiFiPlazaLobbyMinigameParticipants *param0, WiFiPlazaLobbyState *param1, u32 param2);
static void WiFiPlazaLobby_AppManager_InitMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeMainPlaza(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeEarth(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeNews(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeP2PMatchConnect(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeMinigameBucket(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeMinigameManene(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeMinigameBalloon(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitFootprintStamp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeFootprintStamp(WiFiPlazaLobbySubAppSlot *param0);
static int WiFiPlazaLobby_AppManager_UpdateFootprintStamp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet0(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet1(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_InitP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeP2PMatchDisconnect(WiFiPlazaLobbySubAppSlot *param0);
static int WiFiPlazaLobby_AppManager_UpdateP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectDefault(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectForced(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, BOOL param2);
static void WiFiPlazaLobby_AppManager_InitQuestionnaireAnswerSelection(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_InitQuestionnaireResults(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID);
static void WiFiPlazaLobby_AppManager_FreeQuestionnaire(WiFiPlazaLobbySubAppSlot *param0);
static void WiFiPlazaLobby_AppManager_LaunchQuestionnaire(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);
static int WiFiPlazaLobby_AppManager_UpdateQuestionnaire(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1);

WiFiPlazaLobbyAppManager *WiFiPlazaLobby_AppManager_New(BOOL param0, SaveData *saveData, WiFiPlazaLobbyCooldownTimestamp *param2, WiFiPlazaLobbyState *param3, u32 heapID)
{
    WiFiPlazaLobbyAppManager *v0 = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyAppManager));
    memset(v0, 0, sizeof(WiFiPlazaLobbyAppManager));

    v0->state = param3;
    v0->saveData = saveData;
    v0->cooldownTimestamp = param2;
    v0->wifiMenuResult = param0;
    v0->heapID = heapID;

    {
        int v1;

        for (v1 = 0; v1 < 13; v1++) {
            WiFiPlazaLobby_AppManager_InitSubApp(v0, v1, heapID);
        }
    }

    return v0;
}

void WiFiPlazaLobby_AppManager_Free(WiFiPlazaLobbyAppManager *param0)
{
    {
        int v0;

        for (v0 = 0; v0 < 13; v0++) {
            WiFiPlazaLobby_AppManager_FreeSubApp(param0, v0);
        }
    }

    Heap_Free(param0);
}

void WiFiPlazaLobby_AppManager_ConnectToWifiPlaza(WiFiPlazaLobbyAppManager *param0)
{
    WiFiPlazaLobby_AppManager_StartSubApp(param0, 5);
}

int WiFiPlazaLobby_AppManager_Update(WiFiPlazaLobbyAppManager *param0)
{
    BOOL v0;
    u32 v1 = 0;

    if (param0->appMan) {
        v0 = ApplicationManager_Exec(param0->appMan);

        if (v0) {
            ApplicationManager_Free(param0->appMan);
            param0->appMan = NULL;
            v1 = WiFiPlazaLobby_AppManager_UpdateSubApp(param0, param0->currentSubApp);
        }
    }

    return v1;
}

void WiFiPlazaLobby_AppManager_VBlankUpdate(WiFiPlazaLobbyAppManager *param0)
{
    return;
}

static void WiFiPlazaLobby_AppManager_CreateSubApp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, const ApplicationManagerTemplate *param2)
{
    GF_ASSERT(param0->appMan == NULL);
    param0->appMan = ApplicationManager_New(param2, param1->data, param0->heapID);
}

static void WiFiPlazaLobby_AppManager_InitSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1, u32 heapID)
{
    static void (*v0[])(WiFiPlazaLobbyAppManager *, WiFiPlazaLobbySubAppSlot *, u32) = {
        WiFiPlazaLobby_AppManager_InitMainPlaza,
        WiFiPlazaLobby_AppManager_InitEarth,
        WiFiPlazaLobby_AppManager_InitNews,
        WiFiPlazaLobby_AppManager_InitFootprintStamp,
        WiFiPlazaLobby_AppManager_InitFootprintStamp,
        WiFiPlazaLobby_AppManager_InitP2PMatchConnect,
        WiFiPlazaLobby_AppManager_InitMinigameBucket,
        WiFiPlazaLobby_AppManager_InitMinigameManene,
        WiFiPlazaLobby_AppManager_InitMinigameBalloon,
        WiFiPlazaLobby_AppManager_InitP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_InitP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_InitQuestionnaireAnswerSelection,
        WiFiPlazaLobby_AppManager_InitQuestionnaireResults
    };

    GF_ASSERT(param1 < 13);
    v0[param1](param0, &param0->subApps[param1], heapID);
}

static void WiFiPlazaLobby_AppManager_FreeSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1)
{
    static void (*v0[])(WiFiPlazaLobbySubAppSlot *) = {
        WiFiPlazaLobby_AppManager_FreeMainPlaza,
        WiFiPlazaLobby_AppManager_FreeEarth,
        WiFiPlazaLobby_AppManager_FreeNews,
        WiFiPlazaLobby_AppManager_FreeFootprintStamp,
        WiFiPlazaLobby_AppManager_FreeFootprintStamp,
        WiFiPlazaLobby_AppManager_FreeP2PMatchConnect,
        WiFiPlazaLobby_AppManager_FreeMinigameBucket,
        WiFiPlazaLobby_AppManager_FreeMinigameManene,
        WiFiPlazaLobby_AppManager_FreeMinigameBalloon,
        WiFiPlazaLobby_AppManager_FreeP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_FreeP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_FreeQuestionnaire,
        WiFiPlazaLobby_AppManager_FreeQuestionnaire
    };

    GF_ASSERT(param1 < 13);
    v0[param1](&param0->subApps[param1]);
}

static void WiFiPlazaLobby_AppManager_StartSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1)
{
    static void (*v0[])(WiFiPlazaLobbyAppManager *, WiFiPlazaLobbySubAppSlot *) = {
        WiFiPlazaLobby_AppManager_LaunchMainPlaza,
        WiFiPlazaLobby_AppManager_LaunchEarth,
        WiFiPlazaLobby_AppManager_LaunchNews,
        WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet0,
        WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet1,
        WiFiPlazaLobby_AppManager_LaunchP2PMatchConnect,
        WiFiPlazaLobby_AppManager_LaunchMinigameBucket,
        WiFiPlazaLobby_AppManager_LaunchMinigameManene,
        WiFiPlazaLobby_AppManager_LaunchMinigameBalloon,
        WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectDefault,
        WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectForced,
        WiFiPlazaLobby_AppManager_LaunchQuestionnaire,
        WiFiPlazaLobby_AppManager_LaunchQuestionnaire
    };

    GF_ASSERT(param1 < 13);
    v0[param1](param0, &param0->subApps[param1]);

    param0->currentSubApp = param1;
}

static int WiFiPlazaLobby_AppManager_UpdateSubApp(WiFiPlazaLobbyAppManager *param0, u32 param1)
{
    static int (*v0[])(WiFiPlazaLobbyAppManager *, WiFiPlazaLobbySubAppSlot *) = {
        WiFiPlazaLobby_AppManager_UpdateMainPlaza,
        WiFiPlazaLobby_AppManager_UpdateEarth,
        WiFiPlazaLobby_AppManager_UpdateNews,
        WiFiPlazaLobby_AppManager_UpdateFootprintStamp,
        WiFiPlazaLobby_AppManager_UpdateFootprintStamp,
        WiFiPlazaLobby_AppManager_UpdateP2PMatchConnect,
        WiFiPlazaLobby_AppManager_UpdateMinigameBucket,
        WiFiPlazaLobby_AppManager_UpdateMinigameManene,
        WiFiPlazaLobby_AppManager_UpdateMinigameBalloon,
        WiFiPlazaLobby_AppManager_UpdateP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_UpdateP2PMatchDisconnect,
        WiFiPlazaLobby_AppManager_UpdateQuestionnaire,
        WiFiPlazaLobby_AppManager_UpdateQuestionnaire
    };

    GF_ASSERT(param1 < 13);
    return v0[param1](param0, &param0->subApps[param1]);
}

static void WiFiPlazaLobby_AppManager_InitParticipants(WiFiPlazaLobbyMinigameParticipants *param0, u32 heapID)
{
    int i;

    for (i = 0; i < 4; i++) {
        param0->trainerInfos[i] = TrainerInfo_New(heapID);
    }
}

static void WiFiPlazaLobby_AppManager_FreeParticipants(WiFiPlazaLobbyMinigameParticipants *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        Heap_Free(param0->trainerInfos[v0]);
        param0->trainerInfos[v0] = NULL;
    }
}

static void WiFiPlazaLobby_AppManager_SetupParticipants(WiFiPlazaLobbyMinigameParticipants *param0, WiFiPlazaLobbyState *param1, u32 param2)
{
    const WiFiPlazaProfile *v0;
    const WiFiPlazaProfile *v1;
    int v2;

    v0 = WiFiPlazaLobby_State_GetOwnProfile(param1);
    param0->appearanceRank = WiFiPlazaLobby_State_GetAppearanceRank(v0);

    WiFiPlazaLobby_State_GetMemberPresentBitmap(param1, &param0->presentFlags);
    WiFiPlazaLobby_State_GetUserIDTable(param1, &param0->userIDs);

    param0->state = param1;
    param0->trainerInfoValid = 0;

    for (v2 = 0; v2 < 4; v2++) {
        v1 = WiFiPlazaLobby_State_GetProfileBySlot(param1, param0->userIDs.playerIndices[v2]);

        if (v1 != NULL) {
            WiFiPlazaLobby_State_ApplyProfileToTrainerInfo(v1, param0->trainerInfos[v2], param2);
        }
    }
}

static void WiFiPlazaLobby_AppManager_InitMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyMainAppArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyMainAppArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyMainAppArgs));

    v0 = param1->data;
    v0->saveData = param0->saveData;
    v0->state = param0->state;
}

static void WiFiPlazaLobby_AppManager_FreeMainPlaza(WiFiPlazaLobbySubAppSlot *param0)
{
    GF_ASSERT(param0->data);
    Heap_Free(param0->data);
    param0->data = NULL;
}

static void WiFiPlazaLobby_AppManager_LaunchMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyMainAppArgs *v0;

    FS_EXTERN_OVERLAY(wifi_lobby_map);

    static const ApplicationManagerTemplate v1 = {
        wifi_lobby_map_0225D9A4, wifi_lobby_map_0225DB90, wifi_lobby_map_0225DDF8, FS_OVERLAY_ID(wifi_lobby_map)
    };

    v0 = param1->data;
    v0->season = WiFiPlazaLobby_State_GetLobbySeason(param0->state);
    v0->roomType = WiFiPlazaLobby_State_GetLobbyRoomType(param0->state);

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v1);
}

static int WiFiPlazaLobby_AppManager_UpdateMainPlaza(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyMainAppArgs *v0 = param1->data;

    switch (v0->exitCode) {
    case 0:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 9);
        break;
    case 1:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 1);
        break;
    case 2:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 2);
        break;
    case 6:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 3);
        break;
    case 7:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 4);
        break;
    case 3:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 6);
        break;
    case 4:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 7);
        break;
    case 5:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 8);
        break;
    case 8:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 10);
        break;
    case 9:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 11);
        break;
    case 10:
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 12);
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyEarthAppArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyEarthAppArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyEarthAppArgs));

    v0 = param1->data;

    v0->saveData = param0->saveData;
    v0->state = param0->state;
}

static void WiFiPlazaLobby_AppManager_FreeEarth(WiFiPlazaLobbySubAppSlot *param0)
{
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyEarthAppArgs *v0;

    FS_EXTERN_OVERLAY(wifi_earth);

    static const ApplicationManagerTemplate v1 = {
        WiFiEarth_Init, WiFiEarth_Main, WiFiEarth_Exit, FS_OVERLAY_ID(wifi_earth)
    };

    v0 = param1->data;

    v0->placeList = WiFiPlazaLobby_State_GetPlayerCountryTable(param0->state);
    v0->currentTime = *(WiFiPlazaLobby_State_GetCurrentTime(param0->state));

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v1);
}

static int WiFiPlazaLobby_AppManager_UpdateEarth(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    if (WiFiPlazaLobby_State_IsLobbyCloseFinished(param0->state)) {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 10);
    } else {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);
    }

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyNewsAppArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyNewsAppArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyNewsAppArgs));

    v0 = param1->data;

    v0->news = WiFiPlazaLobby_State_GetNewsManager(param0->state);
    v0->currentTime = WiFiPlazaLobby_State_GetCurrentTime(param0->state);
    v0->state = param0->state;
}

static void WiFiPlazaLobby_AppManager_FreeNews(WiFiPlazaLobbySubAppSlot *param0)
{
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_news);

    static const ApplicationManagerTemplate v0 = {
        WiFiLobbyNews_Init, WiFiLobbyNews_Main, WiFiLobbyNews_Exit, FS_OVERLAY_ID(wifi_lobby_news)
    };

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateNews(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    if (WiFiPlazaLobby_State_IsLobbyCloseFinished(param0->state)) {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 10);
    } else {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);
    }

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyP2PMatchConnectArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyP2PMatchConnectArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyP2PMatchConnectArgs));

    v0 = param1->data;

    v0->saveData = param0->saveData;
    v0->state = param0->state;
    v0->wifiMenuResult = param0->wifiMenuResult;
    v0->cooldownTimestamp = param0->cooldownTimestamp;
}

static void WiFiPlazaLobby_AppManager_FreeP2PMatchConnect(WiFiPlazaLobbySubAppSlot *param0)
{
    WiFiPlazaLobbyP2PMatchConnectArgs *v0 = param0->data;
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_p2p_match);

    static const ApplicationManagerTemplate v0 = {
        WifiP2PMatch_InitConnect, WifiP2PMatch_MainConnect, WifiP2PMatch_ExitConnect, FS_OVERLAY_ID(wifi_p2p_match)
    };

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateP2PMatchConnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyP2PMatchConnectArgs *v0 = param1->data;

    if (v0->loginComplete == 0) {
        return 1;
    }

    WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);
    return 0;
}

static void WiFiPlazaLobby_AppManager_InitMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiLobbyMinigameBucketArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameBucketArgs));
    memset(param1->data, 0, sizeof(WiFiLobbyMinigameBucketArgs));

    v0 = param1->data;

    v0->unk_38 = 0;
    v0->unk_39 = 1;
    v0->saveData = param0->saveData;

    WiFiPlazaLobby_AppManager_InitParticipants(&v0->unk_00, heapID);
}

static void WiFiPlazaLobby_AppManager_FreeMinigameBucket(WiFiPlazaLobbySubAppSlot *param0)
{
    WiFiLobbyMinigameBucketArgs *v0 = param0->data;

    WiFiPlazaLobby_AppManager_FreeParticipants(&v0->unk_00);
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame_bucket);
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);

    static const ApplicationManagerTemplate v0 = {
        WiFiLobbyMinigameBucket_Init,
        WiFiLobbyMinigameBucket_Main,
        WiFiLobbyMinigameBucket_Exit,
        FS_OVERLAY_ID(wifi_lobby_minigame_bucket),
    };

    Overlay_LoadByID(FS_OVERLAY_ID(wifi_lobby_minigame), 2);

    {
        WiFiLobbyMinigameBucketArgs *v1;

        v1 = param1->data;
        WiFiPlazaLobby_AppManager_SetupParticipants(&v1->unk_00, param0->state, param0->heapID);
    }

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateMinigameBucket(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);
    Overlay_UnloadByID(FS_OVERLAY_ID(wifi_lobby_minigame));

    {
        WiFiLobbyMinigameBucketArgs *v0;

        v0 = param1->data;

        WiFiPlazaLobby_State_SetTrainerInfoValid(param0->state, v0->unk_00.trainerInfoValid);
        WiFiPlazaLobby_State_SetAppearanceRank(param0->state, v0->unk_00.appearanceRank);
    }

    WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyMinigameManeneArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyMinigameManeneArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyMinigameManeneArgs));

    v0 = param1->data;

    v0->voiceChatEnabled = 0;
    v0->fromLobby = 1;
    v0->saveData = param0->saveData;

    WiFiPlazaLobby_AppManager_InitParticipants(&v0->participants, heapID);
}

static void WiFiPlazaLobby_AppManager_FreeMinigameManene(WiFiPlazaLobbySubAppSlot *param0)
{
    WiFiPlazaLobbyMinigameManeneArgs *v0 = param0->data;

    WiFiPlazaLobby_AppManager_FreeParticipants(&v0->participants);
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame_manene);
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);

    static const ApplicationManagerTemplate v0 = {
        WiFiLobbyMinigameManene_Init,
        WiFiLobbyMinigameManene_Main,
        WiFiLobbyMinigameManene_Exit,
        FS_OVERLAY_ID(wifi_lobby_minigame_manene),
    };

    Overlay_LoadByID(FS_OVERLAY_ID(wifi_lobby_minigame), 2);

    {
        WiFiPlazaLobbyMinigameManeneArgs *v1;

        v1 = param1->data;
        WiFiPlazaLobby_AppManager_SetupParticipants(&v1->participants, param0->state, param0->heapID);
    }

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateMinigameManene(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);
    Overlay_UnloadByID(FS_OVERLAY_ID(wifi_lobby_minigame));

    {
        WiFiPlazaLobbyMinigameManeneArgs *v0;

        v0 = param1->data;

        WiFiPlazaLobby_State_SetTrainerInfoValid(param0->state, v0->participants.trainerInfoValid);
        WiFiPlazaLobby_State_SetAppearanceRank(param0->state, v0->participants.appearanceRank);
    }

    WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiLobbyMinigameBalloonArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiLobbyMinigameBalloonArgs));
    memset(param1->data, 0, sizeof(WiFiLobbyMinigameBalloonArgs));

    v0 = param1->data;
    v0->voiceChatEnabled = 0;
    v0->fromLobby = 1;
    v0->saveData = param0->saveData;

    WiFiPlazaLobby_AppManager_InitParticipants(&v0->participants, heapID);
}

static void WiFiPlazaLobby_AppManager_FreeMinigameBalloon(WiFiPlazaLobbySubAppSlot *param0)
{
    WiFiLobbyMinigameBalloonArgs *v0 = param0->data;

    WiFiPlazaLobby_AppManager_FreeParticipants(&v0->participants);
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame_balloon);
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);

    static const ApplicationManagerTemplate v0 = {
        WiFiLobbyMinigameBalloon_Init,
        WiFiLobbyMinigameBalloon_Main,
        WiFiLobbyMinigameBalloon_Exit,
        FS_OVERLAY_ID(wifi_lobby_minigame_balloon),
    };

    Overlay_LoadByID(FS_OVERLAY_ID(wifi_lobby_minigame), 2);

    {
        WiFiLobbyMinigameBalloonArgs *v1;

        v1 = param1->data;
        WiFiPlazaLobby_AppManager_SetupParticipants(&v1->participants, param0->state, param0->heapID);
    }

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateMinigameBalloon(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_minigame);
    Overlay_UnloadByID(FS_OVERLAY_ID(wifi_lobby_minigame));

    {
        WiFiLobbyMinigameBalloonArgs *v0;

        v0 = param1->data;

        WiFiPlazaLobby_State_SetTrainerInfoValid(param0->state, v0->participants.trainerInfoValid);
        WiFiPlazaLobby_State_SetAppearanceRank(param0->state, v0->participants.appearanceRank);
    }

    WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);

    return 0;
}

static void WiFiPlazaLobby_AppManager_InitFootprintStamp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyFootprintStampArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyFootprintStampArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyFootprintStampArgs));

    v0 = param1->data;
    v0->state = param0->state;
}

static void WiFiPlazaLobby_AppManager_FreeFootprintStamp(WiFiPlazaLobbySubAppSlot *param0)
{
    Heap_Free(param0->data);
}

static int WiFiPlazaLobby_AppManager_UpdateFootprintStamp(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    if (WiFiPlazaLobby_State_IsLobbyCloseFinished(param0->state)) {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 10);
    } else {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);
    }

    return 0;
}

static void WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet0(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyFootprintStampArgs *v0;

    FS_EXTERN_OVERLAY(footprint_stamp);

    static const ApplicationManagerTemplate v1 = {
        FootprintStamp_Init,
        FootprintStamp_Main,
        FootprintStamp_Exit,
        FS_OVERLAY_ID(footprint_stamp),
    };

    v0 = param1->data;
    v0->paletteSet = 0;

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v1);
}

static void WiFiPlazaLobby_AppManager_LaunchFootprintStampPaletteSet1(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobbyFootprintStampArgs *v0;

    FS_EXTERN_OVERLAY(footprint_stamp);

    static const ApplicationManagerTemplate v1 = {
        FootprintStamp_Init,
        FootprintStamp_Main,
        FootprintStamp_Exit,
        FS_OVERLAY_ID(footprint_stamp),
    };

    v0 = param1->data;
    v0->paletteSet = 1;

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v1);
}

static void WiFiPlazaLobby_AppManager_InitP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyP2PMatchDisconnectArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyP2PMatchDisconnectArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyP2PMatchDisconnectArgs));

    v0 = param1->data;
    v0->saveData = param0->saveData;
    v0->state = param0->state;
}

static void WiFiPlazaLobby_AppManager_FreeP2PMatchDisconnect(WiFiPlazaLobbySubAppSlot *param0)
{
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectDefault(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnect(param0, param1, 0);
}

static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnectForced(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnect(param0, param1, 1);
}

static void WiFiPlazaLobby_AppManager_LaunchP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, BOOL param2)
{
    FS_EXTERN_OVERLAY(wifi_p2p_match);

    static const ApplicationManagerTemplate v0 = {
        WifiP2PMatch_InitDisconnect, WifiP2PMatch_MainDisconnect, WifiP2PMatch_ExitDisconnect, FS_OVERLAY_ID(wifi_p2p_match)
    };

    {
        WiFiPlazaLobbyP2PMatchDisconnectArgs *v1;

        v1 = param1->data;
        v1->forced = param2;
    }

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateP2PMatchDisconnect(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    return 1;
}

static void WiFiPlazaLobby_AppManager_InitQuestionnaireAnswerSelection(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyQuestionnaireArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyQuestionnaireArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyQuestionnaireArgs));

    v0 = param1->data;
    v0->saveData = param0->saveData;
    v0->state = param0->state;
    v0->showResults = 0;
}

static void WiFiPlazaLobby_AppManager_InitQuestionnaireResults(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1, u32 heapID)
{
    WiFiPlazaLobbyQuestionnaireArgs *v0;

    param1->data = Heap_Alloc(heapID, sizeof(WiFiPlazaLobbyQuestionnaireArgs));
    memset(param1->data, 0, sizeof(WiFiPlazaLobbyQuestionnaireArgs));

    v0 = param1->data;
    v0->saveData = param0->saveData;
    v0->state = param0->state;
    v0->showResults = 1;
}

static void WiFiPlazaLobby_AppManager_FreeQuestionnaire(WiFiPlazaLobbySubAppSlot *param0)
{
    Heap_Free(param0->data);
}

static void WiFiPlazaLobby_AppManager_LaunchQuestionnaire(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    FS_EXTERN_OVERLAY(wifi_lobby_questionnaire);

    static const ApplicationManagerTemplate v0 = {
        WiFiLobbyQuestionnaire_Init, WiFiLobbyQuestionnaire_Main, WiFiLobbyQuestionnaire_Exit, FS_OVERLAY_ID(wifi_lobby_questionnaire)
    };

    WiFiPlazaLobby_AppManager_CreateSubApp(param0, param1, &v0);
}

static int WiFiPlazaLobby_AppManager_UpdateQuestionnaire(WiFiPlazaLobbyAppManager *param0, WiFiPlazaLobbySubAppSlot *param1)
{
    if (WiFiPlazaLobby_State_IsLobbyCloseFinished(param0->state)) {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 10);
    } else {
        WiFiPlazaLobby_AppManager_StartSubApp(param0, 0);
    }

    return 0;
}
