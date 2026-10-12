#include "contest_competition/contest_competition_0224CFB8.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_0223DAD0.h"
#include "contest_competition/contest_competition_022492DC.h"
#include "contest_competition/contest_competition_0224A0FC.h"
#include "contest_competition/contest_competition_0224E930.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_dance_move_command.h"
#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_start_task.h"
#include "contest_competition/struct_dance_contestant_enter_task.h"
#include "contest_competition/struct_dance_turn_task.h"
#include "contest_competition/struct_dance_contestant_task.h"
#include "contest_competition/struct_dance_round_state.h"
#include "contest_competition/struct_dance_judge_task.h"
#include "contest_competition/struct_dance_move_scores.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_score_state.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_dance_move_task.h"
#include "contest_competition/struct_dance_contestant_info.h"
#include "contest_competition/struct_dance_performance_task.h"
#include "contest_competition/struct_dance_performance_result_task.h"
#include "contest_competition/struct_dance_judge_vote_task.h"
#include "contest_competition/struct_dance_contestant_score_task.h"
#include "contest_competition/struct_dance_packet.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"
#include "contest_competition/struct_contest_packet_handler.h"
#include "image_clip_app/image_clip_app_0225AF8C.h"

#include "bg_window.h"
#include "communication_system.h"
#include "heap.h"
#include "palette.h"
#include "pokemon.h"
#include "render_window.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "contest_util.h"

static int contest_competition_0224CFF8(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D00C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224D01C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
static int contest_competition_0224D020(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D034(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224D078(SysTask *param0, void *param1);
static int contest_competition_0224D1D4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D1E8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224D240(SysTask *param0, void *param1);
static int contest_competition_0224DF88(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224DF9C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224DFF8(SysTask *param0, void *param1);
static void contest_competition_0224E1F4(SysTask *param0, void *param1);
static int contest_competition_0224D544(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D558(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224D710(SysTask *param0, void *param1);
static void contest_competition_0224DF84(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
static int contest_competition_0224D4EC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D500(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_0224DC1C(DanceJudgeTask *param0, int *param1, int param2, int param3);
static DanceContestantTask *contest_competition_0224D668(DanceCompetition *param0, int param1);
static void contest_competition_0224D69C(DanceContestantTask *param0);
static void contest_competition_0224D6CC(SysTask *param0, void *param1);
static int contest_competition_0224E43C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E450(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224E4A8(SysTask *param0, void *param1);
static int contest_competition_0224E518(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E52C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224E584(SysTask *param0, void *param1);
static int contest_competition_0224E648(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E65C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224E6C8(SysTask *param0, void *param1);
static int contest_competition_0224E77C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E790(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_0224E7B4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E7C8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_0224D3C4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D3D8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224D41C(SysTask *param0, void *param1);
static void contest_competition_0224DF54(DanceCompetition *param0);
static int contest_competition_0224E800(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E814(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224E86C(SysTask *param0, void *param1);

static const ContestPacketHandler Unk_contest_competition_022549E4[] = {
    { contest_competition_0224CFF8, contest_competition_0224D00C, contest_competition_0224D01C },
    { contest_competition_0224D020, contest_competition_0224D034, NULL },
    { contest_competition_0224D1D4, contest_competition_0224D1E8, NULL },
    { contest_competition_0224D3C4, contest_competition_0224D3D8, NULL },
    { contest_competition_0224D4EC, contest_competition_0224D500, NULL },
    { contest_competition_0224D544, contest_competition_0224D558, contest_competition_0224DF84 },
    { contest_competition_0224DF88, contest_competition_0224DF9C, NULL },
    { contest_competition_0224E43C, contest_competition_0224E450, NULL },
    { contest_competition_0224E518, contest_competition_0224E52C, NULL },
    { contest_competition_0224E648, contest_competition_0224E65C, NULL },
    { contest_competition_0224E77C, contest_competition_0224E790, NULL },
    { contest_competition_0224E7B4, contest_competition_0224E7C8, NULL },
    { contest_competition_0224E800, contest_competition_0224E814, NULL }
};

__attribute__((aligned(4))) static const s8 Unk_contest_competition_022549C4[] = {
    0xF,
    0xB,
    0x7,
    0x3,
    0xFFFFFFFFFFFFFFFF
};

__attribute__((aligned(4))) static const u16 Unk_contest_competition_022549CC[] = {
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

void contest_competition_0224CFB8(DanceCompetition *param0)
{
    ContestPacketQueueConfig v0;

    v0.handlers = Unk_contest_competition_022549E4;
    v0.handlerCount = NELEMS(Unk_contest_competition_022549E4);
    v0.playerContestantID = param0->contest->data.playerContestantID;
    v0.selfContestantID = param0->contest->data.leaderContestantID;
    v0.isLinkContest = param0->contest->isLinkContest;

    contest_competition_0224F18C(&param0->packetQueue, &v0);
}

static int contest_competition_0224CFF8(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D00C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static void contest_competition_0224D01C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4)
{
    DanceCompetition *v0 = param1;
    return;
}

static int contest_competition_0224D020(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D034(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceStartTask *v1 = Heap_Alloc(HEAP_ID_23, sizeof(DanceStartTask));
    MI_CpuClear8(v1, sizeof(DanceStartTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_0224D078, v1, 30000);
}

static void contest_competition_0224D078(SysTask *param0, void *param1)
{
    DanceStartTask *v0 = param1;

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

            v1 = Bg_GetTilemapBuffer(v0->competition->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                if (Unk_contest_competition_022549C4[v0->row] + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (Unk_contest_competition_022549C4[v0->row] + v4)];
                v7 = Unk_contest_competition_022549CC[v0->column] + 32 * v4;
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
                    v2 = &v1[32 * Unk_contest_competition_022549C4[v0->row - 1]];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_022549CC)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_022549C4)) {
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

static int contest_competition_0224D1D4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D1E8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceContestantEnterTask *v1 = Heap_Alloc(HEAP_ID_23, sizeof(DanceContestantEnterTask));
    MI_CpuClear8(v1, sizeof(DanceContestantEnterTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_0224D240, v1, 30000);
    v0->flag = 0;
    Sound_PlayBGM(CONTEST_DRESSING_ROOM_sseq);
}

static void contest_competition_0224D240(SysTask *param0, void *param1)
{
    DanceContestantEnterTask *v0 = param1;

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

            v1 = Bg_GetTilemapBuffer(v0->competition->scene.bgConfig, 2);

            for (v4 = 0; v4 < 4; v4++) {
                v8 = Unk_contest_competition_022549C4[NELEMS(Unk_contest_competition_022549C4) - 1 - v0->row];

                if (v8 + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (v8 + v4)];
                v7 = Unk_contest_competition_022549CC[NELEMS(Unk_contest_competition_022549CC) - 1 - v0->column] + 32 * v4;
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
                    v8 = Unk_contest_competition_022549C4[NELEMS(Unk_contest_competition_022549C4) - 1 - v0->row + 1];
                    v8 += 4 - 1;
                    v2 = &v1[v8 * 32];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                        v2[v6] |= 0x200 + (v6 % 8);
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 2);
        }

        v0->column++;

        if (v0->column >= NELEMS(Unk_contest_competition_022549CC)) {
            v0->column = 0;
            v0->row++;
            v0->holdDelay = 0;

            if (v0->row >= NELEMS(Unk_contest_competition_022549C4)) {
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

static int contest_competition_0224D3C4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D3D8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceTurnTask *v1 = Heap_Alloc(HEAP_ID_23, sizeof(DanceTurnTask));
    MI_CpuClear8(v1, sizeof(DanceTurnTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;

    SysTask_Start(contest_competition_0224D41C, v1, 30000);
}

static void contest_competition_0224D41C(SysTask *param0, void *param1)
{
    DanceTurnTask *v0 = param1;

    switch (v0->state) {
    case 0:
        Sound_StopBGM(1135, 30);
        v0->state++;
        break;
    case 1:
        if (Sound_IsFadeActive() == FALSE) {
            v0->state++;
        }
        break;
    case 2:
        G2_BlendNone();
        contest_competition_0224C84C();
        contest_competition_0224ABDC(&v0->competition->scene, 1);
        Sound_PlayEffect(SEQ_SE_DP_CON_019_sseq);
        v0->state++;
        break;
    case 3:
        v0->turn++;

        if (v0->turn > 30) {
            v0->turn = 0;
            v0->state++;
        }
        break;
    case 4:
        contest_competition_0224C6B0(v0->competition, v0->competition->contest->data.playerContestantID, &v0->contestantID);
        v0->state++;
        break;
    case 5:
        if (v0->contestantID == 1) {
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

static int contest_competition_0224D4EC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveCommand));
    return v1;
}

static void contest_competition_0224D500(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveCommand *v1 = param3;
    int v2;

    v0->initialized = 1;

    for (v2 = 0; v2 < 4; v2++) {
        v0->contest->contestantOrder[v2] = v1->command[v2];
    }

    if (Contest_IsPlayerLeader(v0->contest) == FALSE) {
        contest_competition_0224F26C(param0, param2, NULL, 0);
    }
}

static int contest_competition_0224D544(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224D558(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveState *v1 = param3;
    DanceRoundState *v2;
    int contestantID, v4;

    v2 = Heap_Alloc(HEAP_ID_23, sizeof(DanceRoundState));
    MI_CpuClear8(v2, sizeof(DanceRoundState));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->moveState = *v1;
    v2->judgeTask.competition = v0;

    SysTask_Start(contest_competition_0224D710, v2, 30000);

    for (contestantID = 0; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
        if (contestantID < v0->contest->data.connectionCount) {
            v2->contestantTasks[contestantID] = contest_competition_0224D668(v0, 0);
        } else {
            v2->contestantTasks[contestantID] = contest_competition_0224D668(v0, 1);
        }
    }

    {
        for (v4 = 0; v4 < 4; v4++) {
            if (v2->moveState.contestantIDs[v4] == v2->competition->contest->data.playerContestantID) {
                v2->competition->scene.playerContestantID = v4;
                break;
            }
        }
    }

    contest_competition_0224DF54(v0);

    for (contestantID = v0->contest->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
        {
            for (v4 = 0; v4 < CONTEST_NUM_PARTICIPANTS; v4++) {
                if (v2->moveState.contestantIDs[v4] == contestantID) {
                    break;
                }
            }
        }
        contest_competition_0224E930(&v2->performanceResults[contestantID], contestantID, v4, v1->moveIDs[contestantID], v0->contest->data.cameraFlashVariant[contestantID]);
    }
}

static DanceContestantTask *contest_competition_0224D668(DanceCompetition *param0, int param1)
{
    DanceContestantTask *v0 = Heap_Alloc(HEAP_ID_23, sizeof(DanceContestantTask));
    MI_CpuClear8(v0, sizeof(DanceContestantTask));

    v0->competition = param0;
    v0->state = param1;
    v0->task = SysTask_Start(contest_competition_0224D6CC, v0, (30000 + 100));

    return v0;
}

static void contest_competition_0224D69C(DanceContestantTask *param0)
{
    SysTask_Done(param0->task);
    Heap_Free(param0);
}

void contest_competition_0224D6B0(DanceContestantTask *param0, const DancePacket *param1)
{
    param0->packet = *param1;
    param0->flag = 1;
}

static void contest_competition_0224D6CC(SysTask *param0, void *param1)
{
    DanceContestantTask *v0 = param1;

    if (v0->flag == 0) {
        return;
    }

    if (v0->competition->contest->isLinkContest == FALSE || v0->state == 1) {
        contest_competition_0224B20C(v0->competition, &v0->packet);
        v0->flag = 0;
    } else {
        if (CommSys_SendDataFixedSize(25, &v0->packet) == 1) {
            v0->flag = 0;
        }
    }
}

static void contest_competition_0224D710(SysTask *param0, void *param1)
{
    DanceRoundState *v0 = param1;
    int v1, v2, v3;
    u32 v4;
    int v5;

    if (v0->competition->contest->data.playerContestantID == v0->moveState.state) {
        v2 = 0;
    } else {
        v2 = 1;
    }

    v4 = v0->competition->timestamp - v0->competition->prevTimestamp;

    if (v4 < (v0->moveState.beatInterval >> 1)) {
        v5 = 0;
    } else {
        v5 = 1;
    }

    switch (v0->state) {
    case 0:
        contest_competition_0224B068(&v0->competition->scene, 0);
        contest_competition_0224BC4C(v0->competition);
        contest_competition_0224E990(v0->competition, &v0->performanceResults[v0->moveState.state], v0->moveState.beatInterval, v0->moveState.duration);
        contest_competition_0224C54C(v0->competition->scene.comboTask, v0->competition->scoreState.contestRank);
        contest_competition_0224C47C(&v0->competition->scene.scoreTask, 1);
        contest_competition_0224C864(v0->competition, 0);
        contest_competition_0224C9A4(v0->competition);

        {
            DanceMessageArgs v6;

            v6.moveSlot = v0->moveState.moveDefinition.beatCount;

            if (v2 == 0) {
                contest_competition_0224C5A0(v0->competition, 4, &v6);
            } else {
                contest_competition_0224C5A0(v0->competition, 5, &v6);
            }
        }

        v0->state++;
        break;
    case 1:
        if (contest_competition_0224C6A8(v0->competition, &(v0->moveState.moveDefinition), v0->moveState.moveIndex) <= 0) {
            contest_competition_0224C640(v0->competition);

            v0->competition->prevTimestamp = v0->competition->timestamp + contest_competition_0224C6A8(v0->competition, &(v0->moveState.moveDefinition), v0->moveState.moveIndex);

            if (v2 == 0) {
                contest_competition_0224C9F0(v0->competition, v2);
                v0->contestantID++;
            }

            contest_competition_0224CDC0(v0->competition, v0->moveState.state, 0);
            v0->state++;
        } else {
            (void)0;
        }
        break;
    case 2: {
        contest_competition_0224A368(&v0->competition->scene, v0->competition->timestamp - v0->competition->prevTimestamp, v0->moveState.beatInterval, v0->competition->scoreState.contestRank);
        contest_competition_0224C49C(v0->competition->scene.comboTask, v0->competition->timestamp - v0->competition->prevTimestamp, v0->moveState.beatInterval, v0->competition->scoreState.contestRank);
        contest_competition_0224C434(&v0->competition->scene.scoreTask, v0->competition->timestamp - v0->competition->prevTimestamp, v0->moveState.beatInterval, v0->competition->scoreState.contestRank);
    }

        {
            if (v4 >= v0->moveState.beatInterval) {
                v0->moveIndex++;
                v0->competition->prevTimestamp = v0->competition->timestamp;
                v0->contestantID = 0;
                v0->flag = 0;

                contest_competition_0224DF54(v0->competition);

                v0->beatIndex = 0;

                for (int contestantID = v0->competition->contest->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
                    contest_competition_0224E958(&v0->performanceResults[contestantID]);
                }

                contest_competition_0224A580(&v0->competition->scene);
                contest_competition_0224BC4C(v0->competition);
                contest_competition_0224E990(v0->competition, &v0->performanceResults[v0->moveState.state], v0->moveState.beatInterval, v0->moveState.duration);
                contest_competition_0224C864(v0->competition, 0);

                if (v0->moveIndex >= v0->moveState.moveDefinition.duration) {
                    contest_competition_0224CE08(v0->competition);
                    contest_competition_0224B068(&v0->competition->scene, 2);
                    v0->state++;
                    break;
                } else {
                    contest_competition_0224CDC0(v0->competition, v0->moveState.state, 0);

                    if (v2 == 0) {
                        if (v0->contestantID == 0) {
                            contest_competition_0224C9F0(v0->competition, v2);
                            v0->contestantID++;
                        }
                    }
                }
                break;
            }
        }

        {
            v3 = v0->competition->scene.playerContestantID;
        }

        {
            DancePacket v8;
            int v9;

            if (v4 < (v0->moveState.beatInterval >> 1)) {
                v9 = 0;
            } else {
                v9 = 1;
            }

            if (v2 == 0) {
                if ((v9 == 0) && (v0->beatIndex < v0->moveState.moveDefinition.beatCount) && (v4 < v0->moveState.beatInterval / 2 - (v0->moveState.duration / 2 / 2) / 10000)) {
                    contest_competition_0224DC1C(&v0->judgeTask, &v1, 0, 0);
                } else {
                    contest_competition_0224DC1C(&v0->judgeTask, &v1, 1, 1);
                }

                if (v1 != 0xffffffff) {
                    contest_competition_0224DE54(v0->competition->contest->data.playerContestantID, v1, v4, v0->moveState.duration, &v0->moveState.moveDefinition.scores, &v8, NULL, v3, v0->beatIndex, v0->moveState.moveDefinition.beatCount, v0->competition->scoreState.contestRank);
                    contest_competition_0224D6B0(v0->contestantTasks[v0->competition->contest->data.playerContestantID], &v8);
                    v0->beatIndex++;
                }
            } else {
                if ((v9 == 1) && (v0->beatIndex < v0->moveState.moveDefinition.beatCount) && (v4 < v0->moveState.beatInterval - (v0->moveState.duration / 2 / 2) / 10000)) {
                    contest_competition_0224DC1C(&v0->judgeTask, &v1, 0, 0);

                    if (v0->contestantID == 0) {
                        contest_competition_0224C9F0(v0->competition, v2);
                        v0->contestantID++;
                    }
                } else {
                    contest_competition_0224DC1C(&v0->judgeTask, &v1, 1, 1);
                }

                if (v1 != 0xffffffff) {
                    contest_competition_0224DE54(v0->competition->contest->data.playerContestantID, v1, v4, v0->moveState.duration, &v0->moveState.moveDefinition.scores, &v8, v0->competition->movePackets, v3, v0->beatIndex, v0->moveState.moveDefinition.beatCount, v0->competition->scoreState.contestRank);
                    contest_competition_0224D6B0(v0->contestantTasks[v0->competition->contest->data.playerContestantID], &v8);
                    v0->beatIndex++;
                }
            }
        }

        for (int contestantID = v0->competition->contest->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
            contest_competition_0224ED8C(v5, v0->competition, &v0->performanceResults[contestantID], v4, v0->moveState.beatInterval, v0->moveState.duration, &v0->moveState.moveDefinition, v0->contestantTasks[contestantID]);
        }

        if ((v5 == 1) && (v0->flag == 0)) {
            contest_competition_0224CDC0(v0->competition, v0->moveState.state, 1);
            v0->flag++;
        }

        if (v5 == 1) {
            contest_competition_0224C8E8(v0->competition, v4);
        }

        break;
    case 3:
        if (contest_competition_0224DC1C(&v0->judgeTask, &v1, 1, 0) == 1) {
            contest_competition_0224A580(&v0->competition->scene);
            contest_competition_0224A368(&v0->competition->scene, 0, v0->moveState.beatInterval, v0->competition->scoreState.contestRank);
            contest_competition_0224C540(v0->competition->scene.comboTask);
            contest_competition_0224C47C(&v0->competition->scene.scoreTask, 0);
            contest_competition_0224B068(&v0->competition->scene, 2);
            contest_competition_0224C864(v0->competition, 0);
            contest_competition_0224C9D4(v0->competition);

            if (contest_competition_02249814(v0->competition->moveSelectScreen) != 0) {
                contest_competition_0224A0E0(v0->competition->moveSelectScreen, 0x0, 6);
            }

            v0->state++;
        }
        break;
    default:
        if (1) {
            contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);

            {
                int v11;

                for (v11 = 0; v11 < 4; v11++) {
                    contest_competition_0224D69C(v0->contestantTasks[v11]);
                }
            }

            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_0224DC1C(DanceJudgeTask *param0, int *param1, int param2, int param3)
{
    int v0 = 0;
    *param1 = 0xffffffff;

    if ((param2 == 0) && (param0->timer > 0)) {
        param0->timer--;

        if (param0->timer == 0) {
            contest_competition_0224A0E0(param0->competition->moveSelectScreen, 0x0, 0);
        }
    }

    switch (param0->state) {
    case 0:
        if ((param2 == 0) && (param3 == 0)) {
            param0->timer = 0;

            contest_competition_0224A0E0(param0->competition->moveSelectScreen, 0x0, 0);
            param0->state++;
        } else {
            v0 = 1;
        }
        break;
    case 1:
        if ((param2 == 1) || (param0->timer > 0)) {
            v0 = 1;
            break;
        }

        *param1 = contest_competition_02249760(param0->competition->moveSelectScreen);

        if (*param1 != 0xffffffff) {
            param0->timer = param0->competition->scoreState.maxScore / 10000;
            param0->timer -= 2;
            param0->state++;
        } else {
            v0 = 1;
        }
        break;
    case 2:
        if (contest_competition_02249804(param0->competition->moveSelectScreen) == 1) {
            if (param0->timer > 0) {
                contest_competition_0224A0E0(param0->competition->moveSelectScreen, 0x0, 6);
            }

            param0->state = 1;
        }
        break;
    }

    if ((param3 == 1) && (v0 == 1)) {
        if (contest_competition_02249814(param0->competition->moveSelectScreen) != 0) {
            contest_competition_0224A0E0(param0->competition->moveSelectScreen, 0x0, 6);
            param0->state = 0;
        }
    }

    return v0;
}

int contest_competition_0224DD28(int param0)
{
    int v0;

    switch (param0) {
    case 0:
        v0 = 1;
        break;
    case 1:
        v0 = 2;
        break;
    case 2:
        v0 = 3;
        break;
    case 3:
        v0 = 4;
        break;
    default:
        GF_ASSERT(FALSE);
        return 0;
    }

    return v0;
}

int contest_competition_0224DD5C(int param0)
{
    int v0;

    switch (param0) {
    case 1:
        v0 = 0;
        break;
    case 2:
        v0 = 1;
        break;
    case 3:
        v0 = 2;
        break;
    case 4:
        v0 = 3;
        break;
    default:
        GF_ASSERT(FALSE);
        return 0;
    }

    return v0;
}

static void contest_competition_0224DD90(int param0, const DanceMoveScores *param1, u8 *param2, u8 *param3)
{
    if (param0 <= param1->cool) {
        *param2 = 0;
        *param3 = 0;
    } else if (param0 <= param1->beauty) {
        *param2 = 0;
        *param3 = 1;
    } else if (param0 <= param1->cute) {
        *param2 = 1;
        *param3 = 2;
    } else if (param0 <= param1->smart) {
        *param2 = 1;
        *param3 = 3;
    } else {
        *param2 = 2;
        *param3 = 4;
    }
}

static void contest_competition_0224DDE4(u32 param0, u32 param1, u32 *param2, u32 *param3)
{
    u32 v0, v1, v2, v3, v4;
    u32 v5, v6;
    u32 v7, v8;
    u32 v9;
    s64 v10;

    v1 = param0 * 10000;
    v9 = param1 / 2;
    v2 = 0;
    v7 = 0;

    for (v4 = 0; v4 < v1; v4 += v9) {
        v2 = v4;
        v7++;
    }

    v3 = v4;
    v2 = (v2 + 10000 / 2) / 10000;
    v3 = (v3 + 10000 / 2) / 10000;
    v1 /= 10000;
    v10 = v1;
    v5 = MATH_IAbs(v10 - v2);
    v6 = MATH_IAbs(v10 - v3);

    if (v5 <= v6) {
        v8 = v5;
        v7--;
    } else {
        v8 = v6;
    }

    *param2 = v8;
    *param3 = v7;
}

void contest_competition_0224DE54(int param0, int param1, u32 param2, u32 param3, const DanceMoveScores *param4, DancePacket *param5, const DancePacket *param6, int param7, int param8, int param9, int param10)
{
    int v0, v1;
    u8 v2, v3;
    u32 v4, v5, v6;
    u32 v7, v8 = 0;

    v0 = contest_competition_0224DD28(param1);

    contest_competition_0224DDE4(param2, param3, &v4, &v5);

    if (param6 != NULL) {
        v6 = v5 - contest_competition_0223F0BC(param10, 4) / 2;

        for (v7 = 0; v7 < 8; v7++) {
            if ((param6[v7].isValid == 1) && (param6[v7].moveSlot == v6)) {
                break;
            }
        }

        if (v7 == 8) {
            v4 = 0xff;
        }
    }

    contest_competition_0224DD90(v4, param4, &v2, &v3);

    if ((param6 != NULL) && (v7 != 8)) {
        switch (v2) {
        case 0:
        case 1:
            if (param6[v7].judgeID != v0) {
                v4 = 0xff;
                v3 = 4;
                v2 = 2;
                v8 = 1;
            }
            break;
        }
    }

    param5->contestantID = param0;
    param5->moveID = param2;
    param5->judgeID = v0;
    param5->score = v2;
    param5->turn = v3;
    param5->moveSlot = v5;
    param5->contestantOrder = param7;
    param5->isLastMove = (param8 >= param9 - 1) ? 1 : 0;
    param5->isCombo = v8;
    param5->isValid = 1;
}

static void contest_competition_0224DF54(DanceCompetition *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->scene.noteCount[v0] = 0;
        param0->scene.missCount[v0] = 0;
    }

    param0->scene.perfectCount = 0;
    param0->scene.goodCount = 0;
    param0->scene.badCount = 0;
}

static void contest_competition_0224DF84(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4)
{
    DanceCompetition *v0 = param1;
    return;
}

static int contest_competition_0224DF88(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224DF9C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveState *v1 = param3;
    DanceMoveTask *v2 = Heap_Alloc(HEAP_ID_23, sizeof(DanceMoveTask));
    MI_CpuClear8(v2, sizeof(DanceMoveTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->moveState = *v1;

    SysTask_Start(contest_competition_0224DFF8, v2, 30000);
}

static void contest_competition_0224DFF8(SysTask *param0, void *param1)
{
    DanceMoveTask *v0 = param1;
    int v1, v2;

    switch (v0->state) {
    case 0:
        contest_competition_0224CDB4(v0->competition, 0);
        PaletteData_StartFade(v0->competition->scene.paletteData, 0x1, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), -2, 0, 6, 0x0);

        for (v2 = 0; v2 < 4; v2++) {
            contest_competition_0224CEE4(v0->competition, v2, 0x7fff, 0x254a, 16, 4, &v0->contestantIDs[v2]);
        }

        v0->state++;
        break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(v0->competition->scene.paletteData) == 0) {
            for (v2 = 0; v2 < 4; v2++) {
                if (v0->contestantIDs[v2] == 0) {
                    break;
                }
            }

            if (v2 == 4) {
                v0->state++;
            }
        }
        break;
    case 2:
        for (v2 = 0; v2 < CONTEST_NUM_PARTICIPANTS; v2++) {
            v1 = v0->moveState.contestantIDs[v2];
            v0->contestantInfo[v1].mon = v0->competition->scene.contestData->contestMons[v1];
            v0->contestantInfo[v1].sprite = v0->competition->scene.pokemonSprites[v1];
            v0->contestantInfo[v1].photoSprite = &v0->competition->scene.photoSprites[v1];
            v0->contestantInfo[v1].duration = (v0->competition->scoreState.bonus2 / 10000) * 40 / 100;
            v0->contestantInfo[v1].contestantID = v2;

            if (v2 == 0) {
                v0->contestantInfo[v1].slot = 3;
            } else {
                v0->contestantInfo[v1].slot = v2 - 1;
            }

            SysTask_Start(contest_competition_0224E1F4, &v0->contestantInfo[v1], ((30000 + 10000) + 100));
        }

        {
            DanceMessageArgs v3;

            v3.moveSlot = v0->moveState.moveDefinition.beatCount;

            if (v0->moveState.contestantIDs[1] == v0->competition->contest->data.playerContestantID) {
                contest_competition_0224C5A0(v0->competition, 4, &v3);
            } else {
                contest_competition_0224C5A0(v0->competition, 5, &v3);
            }
        }

        Sound_PlayEffect(SEQ_SE_DP_CON_030_sseq);
        v0->state++;
        break;
    case 3:
        for (v2 = 0; v2 < 4; v2++) {
            if (v0->contestantInfo[v2].finished == 0) {
                break;
            }
        }

        if (v2 == 4) {
            v0->state++;
        }
        break;
    case 4:
        PaletteData_StartFade(v0->competition->scene.paletteData, 0x1, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), -2, 6, 0, 0x0);
        v0->state++;
        break;
    case 5:
        if (PaletteData_GetSelectedBuffersMask(v0->competition->scene.paletteData) == 0) {
            contest_competition_0224CDB4(v0->competition, 1);
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

static void contest_competition_0224E1F4(SysTask *param0, void *param1)
{
    DanceContestantInfo *v0 = param1;
    int v1, v2, v3, v4, v5, v6;
    int v7;

    switch (v0->state) {
    case 0:
        v0->currentX = v0->photoSprite->x * 0x100;
        v0->currentY = v0->photoSprite->y * 0x100;
        v0->currentZ = v0->photoSprite->z * 0x100;

        {
            v1 = contest_competition_0224A0FC(v0->contestantID) * 0x100;
            v2 = contest_competition_0224A10C(v0->contestantID) * 0x100;
            v3 = contest_competition_0224A120(v0->contestantID) * 0x100;

            if ((v0->slot == 0) || (v0->slot == 4 - 1)) {
                if (v0->slot == 0) {
                    v4 = (0 - 80) * 0x100;
                } else {
                    v4 = (256 + 100) * 0x100;
                }

                v5 = v2;
                v6 = v3;
                v0->velocityX = (v4 - v1) / (v0->duration / 2);
                v0->velocityY = (v5 - v2) / (v0->duration / 2);
                v0->velocityZ = (v6 - v3) / (v0->duration / 2);
            } else {
                v4 = contest_competition_0224A0FC(v0->slot) * 0x100;
                v5 = contest_competition_0224A10C(v0->slot) * 0x100;
                v6 = contest_competition_0224A120(v0->slot) * 0x100;
                v0->velocityX = (v4 - v1) / v0->duration;
                v0->velocityY = (v5 - v2) / v0->duration;
                v0->velocityZ = (v6 - v3) / v0->duration;
            }
        }

        v0->state++;
        break;
    case 1:
        v0->currentX += v0->velocityX;
        v0->currentY += v0->velocityY;
        v0->currentZ += v0->velocityZ;
        v0->frame++;

        if ((v0->slot == 0) || (v0->slot == 4 - 1)) {
            if (v0->frame == (v0->duration / 2)) {
                int v8;

                if (v0->slot == 0) {
                    v0->currentX = (0 - 100) * 0x100;
                    PhotoSprite_SetVisible(v0->photoSprite->photoSprite, 1);
                    PhotoSprite_AdjustPriority(v0->photoSprite->photoSprite, 100);
                } else {
                    v0->currentX = (contest_competition_0224A0FC(v0->slot) + 80) * 0x100;
                    PhotoSprite_SetVisible(v0->photoSprite->photoSprite, 0);
                    PhotoSprite_AdjustPriority(v0->photoSprite->photoSprite, -100);
                }

                v7 = Pokemon_DPSpriteYOffset(v0->mon, 2);

                v0->currentY = (contest_competition_0224A10C(v0->slot) + v7) * 0x100;
                v0->currentZ = contest_competition_0224A120(v0->slot) * 0x100;

                v4 = contest_competition_0224A0FC(v0->slot) * 0x100;
                v5 = v0->currentY;
                v6 = v0->currentZ;
                v8 = v0->duration - v0->frame - 1;

                v0->velocityX = (v4 - v0->currentX) / v8;
                v0->velocityY = (v5 - v0->currentY) / v8;
                v0->velocityZ = (v6 - v0->currentZ) / v8;
            }
        } else if (v0->currentX < contest_competition_0224A0FC(v0->slot) * 0x100) {
            v0->currentX = contest_competition_0224A0FC(v0->slot) * 0x100;
        }

        if (v0->frame >= v0->duration) {
            v7 = Pokemon_DPSpriteYOffset(v0->mon, 2);
            v0->currentX = contest_competition_0224A0FC(v0->slot) * 0x100;
            v0->currentY = (contest_competition_0224A10C(v0->slot) + v7) * 0x100;
            v0->currentZ = contest_competition_0224A120(v0->slot) * 0x100;
            v0->state++;
        }

        v0->photoSprite->x = v0->currentX / 0x100;
        v0->photoSprite->y = v0->currentY / 0x100;
        v0->photoSprite->z = v0->currentZ / 0x100;

        PhotoSprite_MoveTo(v0->photoSprite->photoSprite, v0->photoSprite->x, v0->photoSprite->y);
        contest_competition_0224B09C(v0->sprite, v0->photoSprite);
        break;
    default:
        v0->finished = 1;
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224E43C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224E450(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DancePerformanceTask *v1;
    DanceMoveState *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_23, sizeof(DancePerformanceTask));
    MI_CpuClear8(v1, sizeof(DancePerformanceTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;
    v1->moveState = *v2;

    SysTask_Start(contest_competition_0224E4A8, v1, 30000);
}

static void contest_competition_0224E4A8(SysTask *param0, void *param1)
{
    DancePerformanceTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        for (v1 = 0; v1 < 4; v1++) {
            contest_competition_0224BC68(v0->competition, v0->moveState.contestantIDs[v1], v1);
        }

        contest_competition_02249640(v0->competition->moveSelectScreen, 1, 1, NULL);
        contest_competition_0224A0E0(v0->competition->moveSelectScreen, 0x0, 6);

        v0->state++;
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);

        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224E518(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224E52C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DancePerformanceResultTask *v1;
    DanceMoveState *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_23, sizeof(DancePerformanceResultTask));
    MI_CpuClear8(v1, sizeof(DancePerformanceResultTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->packetQueue = param0;
    v1->moveState = *v2;

    SysTask_Start(contest_competition_0224E584, v1, 30000);
}

static void contest_competition_0224E584(SysTask *param0, void *param1)
{
    DancePerformanceResultTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        if (contest_competition_0224B5C8(v0->competition) == 0) {
            break;
        }

        for (v1 = 0; v1 < 4; v1++) {
            contest_competition_0224BD28(v0->competition, v1, 2);
            contest_competition_0224BD28(v0->competition, v1, 5);
        }

        v0->state++;
        break;
    case 1: {
        int v2 = 0, v3 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if (contest_competition_0224BDF0(v0->competition, v1) == 1) {
                v2++;
            }

            if (contest_competition_0224BE24(v0->competition, v1) == 1) {
                v3++;
            }
        }

        if (v2 >= 4) {
            contest_competition_0224BD00(v0->competition);
            v0->state++;
        }
    } break;
    default:
        contest_competition_02249640(v0->competition->moveSelectScreen, 0, 1, NULL);
        contest_competition_0224A0E0(v0->competition->moveSelectScreen, 0x0, 0);
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static int contest_competition_0224E648(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224E65C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveState *v1 = param3;
    DanceJudgeVoteTask *v2 = Heap_Alloc(HEAP_ID_23, sizeof(DanceJudgeVoteTask));
    MI_CpuClear8(v2, sizeof(DanceJudgeVoteTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->state;
    v2->messageArgs = v1->messageArgs;
    v2->messageID = v1->messageID;
    v2->flag = v1->flag;
    v2->delay = v1->delay;

    SysTask_Start(contest_competition_0224E6C8, v2, 30000);
}

static void contest_competition_0224E6C8(SysTask *param0, void *param1)
{
    DanceJudgeVoteTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->messageID != 0) {
            Window_DrawMessageBoxWithScrollCursor(&v0->competition->scene.windows[0], 1, 1, 14);
            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 1);

            contest_competition_0224C2CC(v0->competition, v0->messageID, &v0->messageArgs);
            v0->state++;
        } else {
            v0->state = 100;
        }
        break;
    case 1:
        if (contest_competition_0224C300(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->flag == 1) {
            v0->state++;
        } else if (v0->timer >= v0->delay) {
            Window_EraseMessageBox(&v0->competition->scene.windows[0], 1);
            Bg_ScheduleTilemapTransfer(v0->competition->scene.bgConfig, 1);
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

static int contest_competition_0224E77C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceScoreState));
    return v1;
}

static void contest_competition_0224E790(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;

    v0->scoreState = *((DanceScoreState *)param3);
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_0224E7B4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224E7C8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveState *v1 = param3;

    Sound_StopWaveOutAndSequences();
    Sound_PlayBGM(v1->moveDefinition.moveID);

    v0->flag = 1;
    v0->prevTimestamp = v0->timestamp;

    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_0224E800(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    DanceCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(DanceMoveState));
    return v1;
}

static void contest_competition_0224E814(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    DanceCompetition *v0 = param1;
    DanceMoveState *v1 = param3;
    DanceContestantScoreTask *v2 = Heap_Alloc(HEAP_ID_23, sizeof(DanceContestantScoreTask));
    MI_CpuClear8(v2, sizeof(DanceContestantScoreTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->moveState = *v1;

    SysTask_Start(contest_competition_0224E86C, v2, 30000);
}

static void contest_competition_0224E86C(SysTask *param0, void *param1)
{
    DanceContestantScoreTask *v0 = param1;

    switch (v0->state) {
    case 0:
        v0->competition->flag = 0;
        v0->state++;
        break;
    case 1:
        if (Sound_IsSequencePlaying(v0->moveState.moveDefinition.moveID) == FALSE) {
            v0->state++;
        }
        break;
    case 2:
        contest_competition_0224CE28(v0->competition);
        v0->state++;
        break;
    case 3:
        v0->score++;

        if (v0->score > 60) {
            v0->score = 0;
            v0->state++;
        }
        break;
    case 4:
        Sound_PlayBGM(CONTEST_DRESSING_ROOM_sseq);
        Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
        v0->state++;
        break;
    default:
        contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}
