#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket.h"

#include <nitro.h>
#include <string.h>

#include "nintendo_wfc/main.h"
#include "wifi_lobby_minigame/wifi_lobby_minigame.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_player_context.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_ranking.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_intro_screen_decl.h"
#include "wifi_lobby_minigame/struct_wifi_lobby_minigame_results_screen_decl.h"
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_score.h"
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_game.h"
#include "wifi_lobby_minigame_bucket/wifi_lobby_minigame_bucket_comm_cmd_handlers.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_args.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_score_decl.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_game_decl.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_mode.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_stage.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_throw_data.h"
#include "wifi_lobby_minigame_bucket/struct_wifi_lobby_minigame_bucket_final_scores.h"

#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "graphics.h"
#include "heap.h"
#include "narc.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "screen_fade.h"
#include "system.h"
#include "comm_tool.h"
#include "vram_transfer.h"

typedef struct WiFiLobbyMinigameBucketApp_t {
    WiFiLobbyMinigameIntroScreen *unk_00;
    WiFiLobbyMinigameResultsScreen *unk_04;
    WiFiLobbyMinigamePlayerContext unk_08;
    WiFiLobbyMinigameRanking unk_18;
    WiFiLobbyMinigameBucketScore *unk_30;
    WiFiLobbyMinigameBucketGame *unk_34;
    BOOL unk_38;
    BOOL unk_3C;
    BOOL unk_40;
    u16 unk_44;
    u16 unk_46;
    WiFiLobbyMinigameBucketStage unk_48;
    u32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    BOOL unk_80;
    u8 unk_84[4];
} WiFiLobbyMinigameBucketApp;

static void WiFiLobbyMinigameBucket_VBlankCallback(void *param0);
static void WiFiLobbyMinigameBucket_SendQueuedThrows(WiFiLobbyMinigameBucketApp *param0);
static void WiFiLobbyMinigameBucket_SendScorePeriodically(WiFiLobbyMinigameBucketApp *param0);
static void WiFiLobbyMinigameBucket_LoadStageData(WiFiLobbyMinigameBucketApp *param0, u32 param1);
static void WiFiLobbyMinigameBucket_FreeStageData(WiFiLobbyMinigameBucketApp *param0);
static void WiFiLobbyMinigameBucket_CleanupOnDisconnect(WiFiLobbyMinigameBucketApp *param0, WiFiLobbyMinigameBucketArgs *param1);
static BOOL WiFiLobbyMinigameBucket_SendData(WiFiLobbyMinigameBucketApp *param0, int param1, const void *param2, int param3);

int WiFiLobbyMinigameBucket_Init(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBucketApp *v0;
    WiFiLobbyMinigameBucketArgs *v1 = ApplicationManager_Args(appMan);
    BOOL v2;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_99, 0x60000);

    v0 = ApplicationManager_NewData(appMan, sizeof(WiFiLobbyMinigameBucketApp), HEAP_ID_99);
    memset(v0, 0, sizeof(WiFiLobbyMinigameBucketApp));

    WiFiLobbyMinigame_InitPlayerContext(&v0->unk_08, v1->unk_39, v1->saveData, v1->unk_38, &v1->unk_00);
    WiFiLobbyMinigameBucket_LoadStageData(v0, 99);

    return 1;
}

int WiFiLobbyMinigameBucket_Main(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBucketApp *v0 = ApplicationManager_Data(appMan);
    WiFiLobbyMinigameBucketArgs *v1 = ApplicationManager_Args(appMan);
    BOOL v2;
    u32 v3;

    if (WiFiLobbyMinigame_CheckDisconnected(&v0->unk_08) == 1) {
        switch (v0->unk_78) {
        case 0:

            if (IsScreenFadeDone() == TRUE) {
                FinishScreenFade();
            }

            SetColorBrightness(COLOR_BLACK);
            v0->unk_78++;
            break;
        case 1:
            if (WiFiLobbyMinigame_HandleDisconnect(&v0->unk_08) == 1) {
                v0->unk_78++;
            }
            break;
        case 2:
            WiFiLobbyMinigameBucket_CleanupOnDisconnect(v0, v1);
            return 1;
            GF_ASSERT(FALSE);
            return 1;
        }

        return 0;
    }

    switch (*param1) {
    case 0:

        v0->unk_00 = WiFiLobbyMinigame_CreateIntroScreen0(&v0->unk_08, HEAP_ID_99);

        (*param1)++;
        break;

    case 1:
        if (WiFiLobbyMinigame_IntroScreenIsDone(v0->unk_00) == 1) {
            v0->unk_70 = WiFiLobbyMinigame_IntroScreenGetResult(v0->unk_00);
            WiFiLobbyMinigame_FreeIntroScreen(v0->unk_00);
            v0->unk_00 = NULL;
            (*param1)++;
        }
        break;
    case 2:
        if (gSystem.heldKeys & PAD_BUTTON_A) {
            break;
        }

        SetVBlankCallback(WiFiLobbyMinigameBucket_VBlankCallback, v0);
        DisableHBlank();

        v0->unk_38 = 0;
        v0->unk_3C = 0;
        v0->unk_40 = 0;
        memset(v0->unk_84, 0, sizeof(u8) * 4);

        VramTransfer_New(32, HEAP_ID_99);
        WiFiLobbyMinigameBucket_InitCommCmd(v0);

        v0->unk_80 = 1;
        v0->unk_74 = CommInfo_CountReceived();

        GF_ASSERT(v0->unk_74 > 1);

        v0->unk_44 = CommSys_CurNetId();
        v0->unk_46 = WiFiLobbyMinigame_GetPlayerIndex(&v0->unk_08, v0->unk_44);

        if (v0->unk_44 == 0) {
            v0->unk_30 = WiFiLobbyMinigameBucket_CreateScore(HEAP_ID_99, (30 * 40), v0->unk_74, &v0->unk_48);
            v0->unk_7C = 1;
        }

        v0->unk_34 = WiFiLobbyMinigameBucket_CreateGame(HEAP_ID_99, (30 * 40), v0->unk_74, v0->unk_46, &v0->unk_48);
        NetworkIcon_Init();

        if (v1->unk_38) {
            NintendoWFC_StartVoiceChat(HEAP_ID_99);
        }

        {
            WiFiLobbyMinigameBucketMode v4;

            switch (v0->unk_70) {
            case 0:
                v4.unk_00 = 0;
                v4.unk_01 = 0;
                break;
            case 1:
                v4.unk_00 = 0;
                v4.unk_01 = 1;
                break;
            case 2:
                v4.unk_00 = 1;
                v4.unk_01 = 0;
                break;
            default:
                GF_ASSERT(FALSE);
                break;
            }

            WiFiLobbyMinigameBucket_SetMode(v0->unk_34, &v4);
        }

        CommTiming_StartSync(1);

        (*param1)++;
        break;
    case 3:
        if (!CommTiming_IsSyncState(1)) {
            break;
        }

        StartScreenFade(FADE_BOTH_SCREENS, 27, 27, 0xffff, 6, 1, HEAP_ID_99);
        (*param1)++;
        break;
    case 4:
        WiFiLobbyMinigameBucket_UpdateIntro(v0->unk_34, 0);

        if (IsScreenFadeDone()) {
            if (v0->unk_44 == 0) {
                v2 = CommSys_SendData(22, NULL, 0);

                if (v2) {
                    (*param1)++;
                }
            } else {
                (*param1)++;
            }
        }
        break;
    case 5:
        WiFiLobbyMinigameBucket_UpdateIntro(v0->unk_34, 0);

        if (v0->unk_38) {
            (*param1)++;
        }
        break;
    case 6:
        v2 = WiFiLobbyMinigameBucket_UpdateIntro(v0->unk_34, 1);

        if (v2 == 0) {
            (*param1)++;
        }
        break;
    case 7:
        if (v0->unk_3C) {
            u32 v5;

            v5 = WiFiLobbyMinigameBucket_GetScore(v0->unk_34);
            v2 = CommSys_SendData(25, &v5, sizeof(u32));

            if (v2) {
                (*param1)++;
            }
            break;
        }

        if (v0->unk_44 == 0) {
            v2 = WiFiLobbyMinigameBucket_UpdateScoreTracker(v0->unk_30);

            if (WiFiLobbyMinigameBucket_ScoreChanged(v0->unk_30)) {
                u32 v6;
                BOOL v7;

                v6 = WiFiLobbyMinigameBucket_GetScoreStage(v0->unk_30);
                v7 = WiFiLobbyMinigameBucket_SendData(v0, 27, &v6, sizeof(u32));

                if (v7 == 1) {
                    WiFiLobbyMinigameBucket_ClearScoreChanged(v0->unk_30);
                }
            }

            if (v2 == 0) {
                WiFiLobbyMinigameBucket_SendData(v0, 23, NULL, 0);
            }
        }

        WiFiLobbyMinigameBucket_UpdateGame(v0->unk_34);
        WiFiLobbyMinigameBucket_SendQueuedThrows(v0);
        WiFiLobbyMinigameBucket_SendScorePeriodically(v0);
        break;
    case 8:
        WiFiLobbyMinigameBucket_UpdateOutro(v0->unk_34, 0);

        if (v0->unk_44 == 0) {
            v2 = WiFiLobbyMinigameBucket_AllPlayersScored(v0->unk_30);

            if (v2 == 1) {
                WiFiLobbyMinigameBucketFinalScores v8;

                WiFiLobbyMinigameBucket_GetFinalScores(v0->unk_30, &v8);
                v2 = CommSys_SendData(26, &v8, sizeof(WiFiLobbyMinigameBucketFinalScores));

                if (v2) {
                    (*param1)++;
                }
            }
        } else {
            (*param1)++;
        }
        break;
    case 9:
        WiFiLobbyMinigameBucket_UpdateOutro(v0->unk_34, 0);

        if (v0->unk_40 == 1) {
            (*param1)++;
        }
        break;
    case 10:
        v2 = WiFiLobbyMinigameBucket_UpdateOutro(v0->unk_34, 1);

        if (v2 == 0) {
            (*param1)++;
        }
        break;
    case 11:
        StartScreenFade(FADE_BOTH_SCREENS, 26, 26, 0xffff, 6, 1, HEAP_ID_99);
        WiFiLobbyMinigameBucket_UpdateOutro(v0->unk_34, 1);
        (*param1)++;
        break;
    case 12:
        WiFiLobbyMinigameBucket_UpdateOutro(v0->unk_34, 1);

        if (IsScreenFadeDone()) {
            CommTiming_StartSync(3);
            (*param1)++;
        }
        break;
    case 13:
        if (!CommTiming_IsSyncState(3)) {
            return 0;
        }

        if (v1->unk_38) {
            NintendoWFC_TerminateVoiceChat();
        }

        if (v0->unk_44 == 0) {
            WiFiLobbyMinigameBucket_FreeScore(v0->unk_30);
            v0->unk_30 = NULL;
        }

        WiFiLobbyMinigameBucket_FreeGame(v0->unk_34);
        v0->unk_34 = NULL;
        SetVBlankCallback(NULL, NULL);
        DisableHBlank();
        VramTransfer_Free();
        (*param1)++;
        break;
    case 14: {
        u32 v9;

        WiFiLobbyMinigame_InitRanking(&v0->unk_18, v0->unk_08.unk_08);
        v9 = v0->unk_18.unk_10[v0->unk_46];
    }
        v0->unk_04 = WiFiLobbyMinigame_CreateResultsScreen0(&v0->unk_08, &v0->unk_18, HEAP_ID_99);
        (*param1)++;
        break;
    case 15: {
        BOOL v10;

        if (WiFiLobbyMinigame_ResultsScreenIsDone(v0->unk_04) == 1) {
            v10 = WiFiLobbyMinigame_ResultsScreenGetResult(v0->unk_04);

            WiFiLobbyMinigame_FreeResultsScreen(v0->unk_04);
            v0->unk_04 = NULL;

            if (v10 == 0) {
                return 1;
            } else {
                (*param1) = 0;
            }
        }
    } break;
    }

    return 0;
}

int WiFiLobbyMinigameBucket_Exit(ApplicationManager *appMan, int *param1)
{
    WiFiLobbyMinigameBucketApp *v0 = ApplicationManager_Data(appMan);
    WiFiLobbyMinigameBucketArgs *v1 = ApplicationManager_Args(appMan);
    BOOL v2;

    switch (*param1) {
    case 0:
        v2 = WiFiLobbyMinigame_CheckDisconnected(&v0->unk_08);

        WiFiLobbyMinigameBucket_FreeStageData(v0);

        ApplicationManager_FreeData(appMan);
        Heap_Destroy(HEAP_ID_99);
        CommManager_SetErrorHandling(0, 1);

        if (v2 == 1) {
            return 1;
        }

        CommTiming_StartSync(4);
        (*param1)++;
        break;
    case 1:
        if (CommTiming_IsSyncState(4) || (CommSys_ConnectedCount() < CommInfo_CountReceived())) {
            return 1;
        }
        break;
    default:
        break;
    }

    return 0;
}

void WiFiLobbyMinigameBucket_SetPlayerReady(WiFiLobbyMinigameBucketApp *param0)
{
    param0->unk_38 = 1;
}

void WiFiLobbyMinigameBucket_SetPlayerFinished(WiFiLobbyMinigameBucketApp *param0)
{
    param0->unk_3C = 1;
}

void WiFiLobbyMinigameBucket_HandleThrowResult(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketThrowData *param1, u32 param2)
{
    u32 v0 = WiFiLobbyMinigame_GetPlayerIndex(&param0->unk_08, param2);
    WiFiLobbyMinigameBucket_AdvanceScoreThreshold(param0->unk_30, param1, v0);
}

void WiFiLobbyMinigameBucket_HandleThrowData(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketThrowData *param1, u32 param2)
{
    WiFiLobbyMinigameBucket_HandleThrow(param0->unk_34, param1);
}

void WiFiLobbyMinigameBucket_HandleScoreUpdate(WiFiLobbyMinigameBucketApp *param0, u32 param1, u32 param2)
{
    u32 v0 = WiFiLobbyMinigame_GetPlayerIndex(&param0->unk_08, param2);

    if (param0->unk_30 != NULL) {
        WiFiLobbyMinigameBucket_SetPlayerScore(param0->unk_30, param1, v0);
    }
}

void WiFiLobbyMinigameBucket_HandleFinalScores(WiFiLobbyMinigameBucketApp *param0, const WiFiLobbyMinigameBucketFinalScores *param1, u32 param2)
{
    WiFiLobbyMinigameBucket_SetFinalScores(param0->unk_34, param1);
    param0->unk_40 = 1;

    {
        int v0;

        for (v0 = 0; v0 < 4; v0++) {
            param0->unk_18.unk_00[v0] = param1->scores[v0];
        }
    }
}

void WiFiLobbyMinigameBucket_HandleStageChange(WiFiLobbyMinigameBucketApp *param0, u32 param1)
{
    WiFiLobbyMinigameBucket_SetStage(param0->unk_34, param1);
}

void WiFiLobbyMinigameBucket_HandleHit(WiFiLobbyMinigameBucketApp *param0, u32 param1, u32 param2)
{
    u32 v0;
    int v1;

    v0 = WiFiLobbyMinigame_GetPlayerIndex(&param0->unk_08, param2);
    WiFiLobbyMinigameBucket_AddScore(param0->unk_34, param1, v0);

    param0->unk_84[v0]++;

    if (param0->unk_44 == 0) {
        BOOL v2 = 1;

        for (v1 = 0; v1 < param0->unk_74; v1++) {
            if (param0->unk_7C > param0->unk_84[v1]) {
                v2 = 0;
            }
        }

        if (v2 == 1) {
            param0->unk_7C++;
            CommSys_SendData(29, NULL, 0);
        }
    }
}

void WiFiLobbyMinigameBucket_OnSyncReady(WiFiLobbyMinigameBucketApp *param0)
{
    param0->unk_80 = 1;
}

static void WiFiLobbyMinigameBucket_VBlankCallback(void *param0)
{
    WiFiLobbyMinigameBucketApp *v0 = param0;

    WiFiLobbyMinigameBucket_VBlank(v0->unk_34);
}

static void WiFiLobbyMinigameBucket_SendQueuedThrows(WiFiLobbyMinigameBucketApp *param0)
{
    WiFiLobbyMinigameBucketThrowData v0;

    while (WiFiLobbyMinigameBucket_PopQueuedThrow(param0->unk_34, &v0) == 1) {
        WiFiLobbyMinigameBucket_SendData(param0, 24, &v0, sizeof(WiFiLobbyMinigameBucketThrowData));
    }
}

static void WiFiLobbyMinigameBucket_SendScorePeriodically(WiFiLobbyMinigameBucketApp *param0)
{
    s32 v0;
    u32 v1;
    BOOL v2;

    v0 = WiFiLobbyMinigameBucket_GetElapsedTime(param0->unk_34);

    if (v0 == 0) {
        return;
    }

    if ((v0 % 30) == 0) {
        if (param0->unk_80 == 1) {
            v1 = WiFiLobbyMinigameBucket_GetScore(param0->unk_34);
            v2 = WiFiLobbyMinigameBucket_SendData(param0, 28, &v1, sizeof(u32));
            GF_ASSERT(v2);

            param0->unk_80 = 0;
        }
    }
}

static void WiFiLobbyMinigameBucket_LoadStageData(WiFiLobbyMinigameBucketApp *param0, u32 param1)
{
    u32 v0;
    int v1;

    param0->unk_48.unk_04 = LoadMemberFromNARC_OutFileSize(NARC_INDEX_APPLICATION__BUCKET__BALLSLOW_DATA, 0, 0, param1, 0, &v0);
    param0->unk_48.unk_00 = v0 / sizeof(WiFiLobbyMinigameBucketStageData);

    for (v1 = 0; v1 < param0->unk_08.unk_08; v1++) {
        param0->unk_48.unk_08[v1] = WiFiLobbyMinigame_GetTrainerInfo(&param0->unk_08, v1);
        param0->unk_48.unk_18[v1] = WiFiLobbyMinigame_IsPlayerReady(&param0->unk_08, v1);
    }
}

static void WiFiLobbyMinigameBucket_FreeStageData(WiFiLobbyMinigameBucketApp *param0)
{
    Heap_Free(param0->unk_48.unk_04);
    param0->unk_48.unk_04 = NULL;
    param0->unk_48.unk_00 = 0;
}

static void WiFiLobbyMinigameBucket_CleanupOnDisconnect(WiFiLobbyMinigameBucketApp *param0, WiFiLobbyMinigameBucketArgs *param1)
{
    SetVBlankCallback(NULL, NULL);
    DisableHBlank();

    if (param0->unk_00 != NULL) {
        WiFiLobbyMinigame_FreeIntroScreen(param0->unk_00);
        param0->unk_00 = NULL;
    }

    if (param0->unk_34) {
        if (param0->unk_44 == 0) {
            WiFiLobbyMinigameBucket_FreeScore(param0->unk_30);
        }

        WiFiLobbyMinigameBucket_FreeGame(param0->unk_34);
        VramTransfer_Free();
    }

    if (param1->unk_38) {
        NintendoWFC_TerminateVoiceChat();
    }

    if (param0->unk_04 != NULL) {
        WiFiLobbyMinigame_FreeResultsScreen(param0->unk_04);
        param0->unk_04 = NULL;
    }
}

static BOOL WiFiLobbyMinigameBucket_SendData(WiFiLobbyMinigameBucketApp *param0, int param1, const void *param2, int param3)
{
    if (param0->unk_80 == 0) {
        return 0;
    }

    return CommSys_SendData(param1, param2, param3);
}
