#include "contest_competition/contest_competition_02251D6C.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_0223F118.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/contest_competition_02250744.h"
#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"
#include "contest_competition/struct_contest_final_scoring.h"
#include "contest_competition/struct_contest_final_scoring_scores.h"
#include "contest_competition/struct_contest_final_scoring_results.h"
#include "contest_competition/struct_final_scoring_start_task.h"
#include "contest_competition/struct_final_scoring_announce_task.h"
#include "contest_competition/struct_final_scoring_contestant_task.h"
#include "contest_competition/struct_final_scoring_message_task.h"
#include "contest_competition/struct_final_scoring_score_reveal_task.h"
#include "contest_competition/struct_final_scoring_winner_task.h"
#include "contest_competition/struct_final_scoring_placement_task.h"
#include "contest_competition/struct_final_scoring_done_task.h"
#include "contest_competition/struct_contest_packet_handler.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "heap.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "render_window.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"

static int contest_competition_02251DAC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02251DC0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02251DD0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
static int contest_competition_02251E54(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02251E68(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02251EAC(SysTask *param0, void *param1);
static int contest_competition_02252008(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0225201C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02252060(SysTask *param0, void *param1);
static int contest_competition_022521E4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022521F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02252210(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02252224(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0225228C(SysTask *param0, void *param1);
static int contest_competition_02252344(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02252358(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022523AC(SysTask *param0, void *param1);
static int contest_competition_0225260C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02252620(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0225266C(SysTask *param0, void *param1);
static int contest_competition_02252514(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02252528(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02252580(SysTask *param0, void *param1);
static int contest_competition_02251DD4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02251DE8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02252798(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022527AC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02252858(SysTask *param0, void *param1);
static int contest_competition_02252970(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02252984(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022529C8(SysTask *param0, void *param1);

static const ContestPacketHandler Unk_contest_competition_02254D18[] = {
    { contest_competition_02251DAC, contest_competition_02251DC0, contest_competition_02251DD0 },
    { contest_competition_02251DD4, contest_competition_02251DE8, NULL },
    { contest_competition_02251E54, contest_competition_02251E68, NULL },
    { contest_competition_02252008, contest_competition_0225201C, NULL },
    { contest_competition_022521E4, contest_competition_022521F8, NULL },
    { contest_competition_02252210, contest_competition_02252224, NULL },
    { contest_competition_02252344, contest_competition_02252358, NULL },
    { contest_competition_02252514, contest_competition_02252528, NULL },
    { contest_competition_0225260C, contest_competition_02252620, NULL },
    { contest_competition_02252798, contest_competition_022527AC, NULL },
    { contest_competition_02252970, contest_competition_02252984, NULL }
};

__attribute__((aligned(4))) static const s8 Unk_contest_competition_02254CF8[] = {
    0xF,
    0xB,
    0x7,
    0x3,
    0xFFFFFFFFFFFFFFFF
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_02254D00[] = {
    0x20,
    0x28,
    0x30,
    0x38,
    0xA0,
    0xA8,
    0xB0,
    0xB8,
    0x120,
    0x128,
    0x130,
    0x138
};

void contest_competition_02251D6C(ContestFinalScoring *param0)
{
    ContestPacketQueueConfig v0;

    v0.handlers = Unk_contest_competition_02254D18;
    v0.handlerCount = NELEMS(Unk_contest_competition_02254D18);
    v0.playerContestantID = param0->contest->data.playerContestantID;
    v0.selfContestantID = param0->contest->data.leaderContestantID;
    v0.isLinkContest = param0->contest->isLinkContest;

    contest_competition_0224F18C(&param0->packetQueue, &v0);
}

static int contest_competition_02251DAC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02251DC0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static void contest_competition_02251DD0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4)
{
    ContestFinalScoring *v0 = param1;
    return;
}

static int contest_competition_02251DD4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringScores));
    return v1;
}

static void contest_competition_02251DE8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    ContestFinalScoringScores *v1 = param3;
    int v2;

    v0->scores = *v1;

    for (v2 = 0; v2 < 4; v2++) {
        v0->contest->data.results[v2] = v1->results[v2];
    }

    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_02251E54(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02251E68(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    FinalScoringStartTask *v1 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringStartTask));
    MI_CpuClear8(v1, sizeof(FinalScoringStartTask));

    v1->finalScoring = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_02251EAC, v1, 30000);
}

static void contest_competition_02251EAC(SysTask *param0, void *param1)
{
    FinalScoringStartTask *v0 = param1;

    switch (v0->state) {
    case 0:

        if (v0->holdDelay > 0) {
            v0->holdDelay--;
            break;
        }

        if (v0->stepDelay > 0) {
            v0->stepDelay--;
            break;
        }

        v0->stepDelay = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;

            v1 = Bg_GetTilemapBuffer(v0->finalScoring->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                if (Unk_contest_competition_02254CF8[v0->row] + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (Unk_contest_competition_02254CF8[v0->row] + v4)];
                v7 = Unk_contest_competition_02254D00[v0->column] + 32 * v4;
                v5 = 0;

                for (v6 = 0; v6 < 32 / 8; v6++) {
                    for (v3 = 0; v3 < 8; v3++) {
                        v2[v5 + v3] &= 0xfc00;
                        v2[v5 + v3] |= v7 + v3;
                    }

                    v5 += 8;
                }
            }

            {
                if ((v0->row > 0) && (v0->column == 0)) {
                    v2 = &v1[32 * Unk_contest_competition_02254CF8[v0->row - 1]];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->finalScoring->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_02254D00)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_02254CF8)) {
                v0->state++;
            }
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02252008(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0225201C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    FinalScoringAnnounceTask *v1 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringAnnounceTask));
    MI_CpuClear8(v1, sizeof(FinalScoringAnnounceTask));

    v1->finalScoring = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_02252060, v1, 30000);
}

static void contest_competition_02252060(SysTask *param0, void *param1)
{
    FinalScoringAnnounceTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->holdDelay > 0) {
            v0->holdDelay--;
            break;
        }

        if (v0->stepDelay > 0) {
            v0->stepDelay--;
            break;
        }

        v0->stepDelay = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;
            int v8;

            v1 = Bg_GetTilemapBuffer(v0->finalScoring->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                v8 = Unk_contest_competition_02254CF8[NELEMS(Unk_contest_competition_02254CF8) - 1 - v0->row];

                if (v8 + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (v8 + v4)];
                v7 = Unk_contest_competition_02254D00[NELEMS(Unk_contest_competition_02254D00) - 1 - v0->column] + 32 * v4;
                v5 = 0;

                for (v6 = 0; v6 < 32 / 8; v6++) {
                    for (v3 = 0; v3 < 8; v3++) {
                        v2[v5 + v3] &= 0xfc00;
                        v2[v5 + v3] |= v7 + v3;
                    }

                    v5 += 8;
                }
            }

            {
                if ((v0->row > 0) && (v0->column == 0)) {
                    v8 = Unk_contest_competition_02254CF8[NELEMS(Unk_contest_competition_02254CF8) - 1 - v0->row + 1];
                    v8 += 4 - 1;
                    v2 = &v1[v8 * 32];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                        v2[v6] |= 0x200 + (v6 % 8);
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->finalScoring->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_02254D00)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_02254CF8)) {
                v0->state++;
            }
        }

        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022521E4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_022521F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;

    v0->scoringDone = 1;
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_02252210(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringResults));
    return v1;
}

static void contest_competition_02252224(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    ContestFinalScoringResults *v1 = param3;
    FinalScoringContestantTask *v2 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringContestantTask));
    MI_CpuClear8(v2, sizeof(FinalScoringContestantTask));

    v2->finalScoring = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->messageType;
    v2->messageArgs = v1->messageArgs;
    v2->announcerMessagesID = v1->announcerMessagesID;
    v2->messageState = v1->categoryState;
    v2->flag = v1->showCategories;
    v2->delay = v1->messageState;

    SysTask_Start(contest_competition_0225228C, v2, 30000);
}

static void contest_competition_0225228C(SysTask *param0, void *param1)
{
    FinalScoringContestantTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->announcerMessagesID != 0) {
            if (v0->messageState == 0) {
                Window_DrawMessageBoxWithScrollCursor(&v0->finalScoring->scene.windows[0], 1, 1, 14);
                Bg_ScheduleTilemapTransfer(v0->finalScoring->scene.bgConfig, 1);
            }

            contest_competition_02250968(v0->finalScoring, v0->announcerMessagesID, &v0->messageArgs);
            v0->state++;
        } else {
            v0->state = 100;
        }
        break;
    case 1:
        if (contest_competition_0225099C(v0->finalScoring) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->flag == 1) {
            v0->state++;
        } else if (v0->timer >= v0->delay) {
            Window_EraseMessageBox(&v0->finalScoring->scene.windows[0], 1);
            Bg_ScheduleTilemapTransfer(v0->finalScoring->scene.bgConfig, 1);
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02252344(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringScores));
    return v1;
}

static void contest_competition_02252358(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    FinalScoringMessageTask *v1;

    v0->scores = *((ContestFinalScoringScores *)param3);

    v1 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringMessageTask));
    MI_CpuClear8(v1, sizeof(FinalScoringMessageTask));

    v1->finalScoring = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_022523AC, v1, 1000);
}

static void contest_competition_022523AC(SysTask *param0, void *param1)
{
    FinalScoringMessageTask *v0 = param1;

    switch (v0->state) {
    case 0:
        contest_competition_0223F744(v0->finalScoring->paletteFadeTask);
        v0->state++;
        break;
    case 1:
        if (contest_competition_0223F760() == 1) {
            v0->state++;
        }
        break;
    case 2:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 6, 1, HEAP_ID_24);
        Sound_StopBGM(CONTEST_DRESSING_ROOM_sseq, 30);
        v0->state++;
        break;
    case 3:
        if (IsScreenFadeDone() == TRUE) {
            v0->state++;
        }
        break;
    case 4:
        contest_competition_02250A84(v0->finalScoring);
        contest_competition_02250AD8(v0->finalScoring);

        contest_competition_02250B00(v0->finalScoring);
        contest_competition_02250D28(v0->finalScoring);

        contest_competition_02250CEC(v0->finalScoring);

        Window_DrawMessageBoxWithScrollCursor(&v0->finalScoring->scene.windows[0], 0, 1, 14);

        Window_FillTilemap(&v0->finalScoring->scene.windows[0], 0xff);
        Window_CopyToVRAM(&v0->finalScoring->scene.windows[0]);

        {
            int v1;

            for (v1 = 0; v1 < 4; v1++) {
                PokemonSprite_SetAttribute(v0->finalScoring->scene.pokemonSprites[v1], MON_SPRITE_HIDE, 1);
            }
        }

        v0->finalScoring->enableHBlank = 1;
        v0->state++;
        break;
    case 5:
        if (Sound_IsFadeActive() == FALSE) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 6, 1, HEAP_ID_24);
            v0->state++;
        }
        break;
    case 6:
        if (IsScreenFadeDone() == TRUE) {
            Sound_PlayBGM(SEQ_CO_KEKKA_sseq);
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02252514(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringResults));
    return v1;
}

static void contest_competition_02252528(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    ContestFinalScoringResults *v1 = param3;
    FinalScoringScoreRevealTask *v2;
    int v3;

    v2 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringScoreRevealTask));
    MI_CpuClear8(v2, sizeof(FinalScoringScoreRevealTask));

    v2->finalScoring = v0;
    v2->header = *param2;
    v2->packetQueue = param0;

    for (v3 = 0; v3 < 4; v3++) {
        v2->contestantIDs[v3] = v1->placements[v3];
    }

    SysTask_Start(contest_competition_02252580, v2, 30000);
}

static void contest_competition_02252580(SysTask *param0, void *param1)
{
    FinalScoringScoreRevealTask *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->state++;
        break;
    case 1:
        contest_competition_0225131C(v0->finalScoring, v0->contestantIDs[4 - 1 - v0->index], 4 - 1 - v0->index);
        v0->index++;
        v0->state++;
        break;
    case 2:
        v0->timer++;

        if (v0->timer > 30) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 3:
        if (v0->index < 4) {
            v0->state = 1;
        } else {
            v0->state++;
        }
        break;
    case 4:
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0225260C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringResults));
    return v1;
}

static void contest_competition_02252620(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    ContestFinalScoringResults *v1 = param3;
    FinalScoringWinnerTask *v2 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringWinnerTask));
    MI_CpuClear8(v2, sizeof(FinalScoringWinnerTask));

    v2->finalScoring = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->winningContestantID = v1->winningContestantID;

    SysTask_Start(contest_competition_0225266C, v2, 30000);
}

static void contest_competition_0225266C(SysTask *param0, void *param1)
{
    FinalScoringWinnerTask *v0 = param1;

    switch (v0->state) {
    case 0:
        contest_competition_02250FE4(v0->finalScoring);
        contest_competition_02251598(v0->finalScoring, 0, &v0->animationDone);
        Sound_PlayBGM(SEQ_CO_FANFA_sseq);
        Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
        v0->state++;
        break;
    case 1:
        if (v0->animationDone == 1) {
            v0->state++;
        }
        break;
    case 2:
        contest_competition_02251718(v0->finalScoring, v0->winningContestantID, 0, &v0->animationDone2);
        v0->state++;
        break;
    case 3:
        if (v0->animationDone2 == 1) {
            v0->state++;
        }
        break;
    case 4: {
        int species = Pokemon_GetValue(v0->finalScoring->scene.contestData->contestMons[v0->winningContestantID], MON_DATA_SPECIES, NULL);
        int form = Pokemon_GetValue(v0->finalScoring->scene.contestData->contestMons[v0->winningContestantID], MON_DATA_FORM, NULL);
        PlayCryWithParams(v0->finalScoring->contest->chatotCry[v0->winningContestantID], POKECRY_NORMAL, species, form, 0, 127, NULL, HEAP_ID_24);
    }
        v0->state++;
        break;
    case 5:
        if (Sound_IsPokemonCryPlaying() == FALSE) {
            v0->state++;
        }
        break;
    case 6:
        v0->timer++;

        if (v0->timer > 60) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02252798(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ContestFinalScoringResults));
    return v1;
}

static void contest_competition_022527AC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    ContestFinalScoringResults *v1 = param3;
    FinalScoringPlacementTask *v2;
    int v3;

    v2 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringPlacementTask));
    MI_CpuClear8(v2, sizeof(FinalScoringPlacementTask));

    v2->finalScoring = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->competitionType;

    switch (v1->competitionType) {
    case 0:
        for (v3 = 0; v3 < 4; v3++) {
            v2->placements[v3] = v0->scores.visualPoints[v3];
        }
        break;
    case 1:
        for (v3 = 0; v3 < 4; v3++) {
            v2->placements[v3] = v0->scores.dancePoints[v3];
        }
        break;
    case 2:
        for (v3 = 0; v3 < 4; v3++) {
            v2->placements[v3] = v0->scores.actingPoints[v3];
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }

    SysTask_Start(contest_competition_02252858, v2, 30000);
}

static void contest_competition_02252858(SysTask *param0, void *param1)
{
    FinalScoringPlacementTask *v0 = param1;
    int v1, v2, v3;

    switch (v0->state) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_CON_033_sseq);
        v0->state++;
        break;
    case 1:
        v0->timer++;

        if (v0->timer > 45) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 2:
        for (v1 = 0; v1 < 4; v1++) {
            if (v0->placements[v1] > 0) {
                Sound_PlayEffect(SEQ_SE_PL_CON_034_sseq_1);
                break;
            }
        }

        v0->state++;
    case 3:
        v0->timer++;

        if (v0->timer < 1) {
            break;
        }

        v0->timer = 0;
        v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            v3 = v0->finalScoring->scores.placementOrder[v1];
            v0->scores[v3]++;

            if (v0->scores[v3] <= v0->placements[v3]) {
                contest_competition_022513F4(v0->finalScoring, v3, v0->contestantID, v0->scores[v3], v1);
            } else {
                v2++;
            }
        }

        if (v2 >= 4) {
            v0->state++;
        }
        break;
    case 4:
        for (v1 = 0; v1 < 4; v1++) {
            if (v0->placements[v1] > 0) {
                Sound_PlayEffect(SEQ_SE_DP_CON_032_sseq);
                break;
            }
        }

        Sound_StopEffect(1786, 0);
        v0->state++;
        break;
    case 5:
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02252970(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02252984(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ContestFinalScoring *v0 = param1;
    FinalScoringDoneTask *v1 = Heap_Alloc(HEAP_ID_24, sizeof(FinalScoringDoneTask));
    MI_CpuClear8(v1, sizeof(FinalScoringDoneTask));

    v1->finalScoring = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_022529C8, v1, 30000);
}

static void contest_competition_022529C8(SysTask *param0, void *param1)
{
    FinalScoringDoneTask *v0 = param1;

    switch (v0->state) {
    case 0:
        BrightnessController_StartTransition(90, 16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_BOTH_SCREENS);
        Sound_StopBGM(SEQ_CO_FANFA_sseq, 90);
        v0->state++;
        break;
    case 1:
        if ((BrightnessController_IsTransitionComplete(BRIGHTNESS_BOTH_SCREENS) == TRUE) && (Sound_IsFadeActive() == FALSE)) {
            contest_competition_02251020(v0->finalScoring);
            GX_SetMasterBrightness(16);
            GXS_SetMasterBrightness(16);
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->timer > 60) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}
