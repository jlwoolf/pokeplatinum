#include "contest_competition/contest_competition_0224E930.h"

#include <nitro.h>
#include <string.h>

#include "generated/pokemon_contest_ranks.h"
#include "generated/pokemon_contest_types.h"

#include "contest_competition/contest_competition_0223DAD0.h"
#include "contest_competition/contest_competition_0224CFB8.h"
#include "contest_competition/struct_dance_contestant_task.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_dance_performance_result.h"
#include "contest_competition/struct_dance_packet.h"
#include "contest_competition/struct_dance_move_definition.h"

#include "contest.h"

static int contest_competition_0224EBE0(int contestRank, int param1);
static int contest_competition_0224EC24(int contestRank, int contestType, int param2, int param3, int param4, int param5, int param6);
static int contest_competition_0224ECC4(int contestRank, int contestType, int param2, int param3, int param4, int param5, int param6, int param7);
static void contest_competition_0224EDE0(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3, u32 param4, const DanceMoveDefinition *param5, DanceContestantTask *param6);
static void contest_competition_0224EE90(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3, u32 param4, const DanceMoveDefinition *param5, DanceContestantTask *param6);

__attribute__((aligned(4))) static const s8 Unk_contest_competition_02254A80[] = {
    0x1,
    0x2,
    0x3,
    0x4
};

__attribute__((aligned(4))) static const u8 Unk_contest_competition_02254A84[] = {
    0x5A,
    0x28,
    0x0,
    0x0
};

void contest_competition_0224E930(DancePerformanceResult *param0, int contestantID, int param2, u32 param3, int param4)
{
    MI_CpuClear8(param0, sizeof(DancePerformanceResult));

    param0->contestantID = contestantID;
    param0->state = param2;
    param0->rngSeed = param3;
    param0->contestRank = param4;
}

void contest_competition_0224E958(DancePerformanceResult *param0)
{
    u32 v0;
    int v1, v2, v3;

    v0 = param0->rngSeed;
    v1 = param0->contestantID;
    v2 = param0->state;
    v3 = param0->contestRank;

    MI_CpuClear8(param0, sizeof(DancePerformanceResult));

    param0->rngSeed = v0;
    param0->contestantID = v1;
    param0->state = v2;
    param0->contestRank = v3;
}

void contest_competition_0224E990(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3)
{
    int v0, v1, v2, v3, v4;
    u8 v5[(16 * 2) / 2];
    u32 v6;
    s32 v7;
    int v8;
    u32 v9;
    int v10 = contest_competition_0223F0BC(param0->scoreState.contestRank, 4);

    if (param0->scoreState.contestRank == 0) {
        v9 = (param3 / 4 + 10000 / 2) / 10000;
    } else {
        v9 = (param3 / 6 + 10000 / 2) / 10000;
    }

    switch (param0->contest->data.contestRank) {
    case CONTEST_RANK_NORMAL:
    case CONTEST_RANK_GREAT:
        v8 = 0;
        v1 = v10 / 2 / 2;
        v6 = param3;
        break;
    default:
        v8 = 1;
        v1 = v10 / 2;
        v6 = param3 / 2;
        break;
    }

    for (v0 = 0; v0 < v10 / 2; v0++) {
        v5[v0] = 0;
    }

    v3 = 0;

    while (TRUE) {
        v2 = Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % v1;

        if (v2 == 0) {
            continue;
        }

        if (v5[v2] == 0) {
            if (v8 == 1) {
                if ((v2 == v1 - 1) && ((v5[v2 - 1]) == 1)) {
                    continue;
                } else if ((v5[v2 - 1] == 1) || (v5[v2 + 1] == 1)) {
                    continue;
                }

                if ((v2 & 1) && ((Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) & 0xff) < 128)) {
                    continue;
                }
            }

            v5[v2] = 1;
            v3++;

            if (v3 >= param0->scoreState.roundCount) {
                break;
            }
        }
    }

    v3 = 0;

    for (v0 = 0; v0 < v10 / 2; v0++) {
        if (v5[v0] == 1) {
            param1->performanceData.scores[v3] = (v0 * v6 + 10000 / 2) / 10000;
            v3++;
        }
    }

    v4 = contest_competition_0224EBE0(param0->contest->data.contestRank, param1->contestRank);

    for (v0 = 0; v0 < param0->scoreState.roundCount; v0++) {
        s32 v11;

        v11 = param1->performanceData.scores[v0] + (Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % (2 + v4)) - (1 + v4 / 2);

        if (v11 < 0) {
            v11 = 0;
        }

        if (v11 - param1->performanceData.scores[v0] >= v9) {
            v11 = param1->performanceData.scores[v0] + v9 - 1;
        }

        param1->performanceData.scores[v0] = v11;
        param1->performanceData.points[v0] = 1;
    }

    {
        int v12;

        v12 = Unk_contest_competition_02254A84[param0->contest->data.contestRank];
        param1->performanceData.ranks[0] = 0 + (Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % 4);

        for (v0 = 1; v0 < param0->scoreState.roundCount; v0++) {
            if ((v0 < param0->scoreState.roundCount - 1) && (v12 > Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % 100)) {
                param1->performanceData.ranks[v0] = param1->performanceData.ranks[v0 - 1];
            } else {
                param1->performanceData.ranks[v0] = 0 + (Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % 4);
            }
        }
    }
}

static int contest_competition_0224EBE0(int contestRank, int param1)
{
    int v0;

    GF_ASSERT(NELEMS(Unk_contest_competition_02254A80) > param1);
    v0 = Unk_contest_competition_02254A80[param1];

    switch (contestRank) {
    case CONTEST_RANK_NORMAL:
        v0 *= 2;
        break;
    case CONTEST_RANK_GREAT:
        break;
    case CONTEST_RANK_ULTRA:
        v0 /= 2;
        break;
    case CONTEST_RANK_MASTER:
    default:
        v0 /= 3;
        break;
    }

    return v0;
}

static int contest_competition_0224EC24(int contestRank, int contestType, int param2, int param3, int param4, int param5, int param6)
{
    int v0 = 0;

    GF_ASSERT(NELEMS(Unk_contest_competition_02254A80) > param2);

    if (param4 != -1) {
        if (param5 == 0) {
            if ((param3 & 1) != (param4 & 1)) {
                v0 += 3;
            }
        }

        if (param3 - param4 <= 2 * 2) {
            v0--;
        }

        if (param3 - param4 >= 4 * 2) {
            v0 += 3;
        }
    }

    v0 = Unk_contest_competition_02254A80[param2];

    switch (contestRank) {
    case CONTEST_RANK_NORMAL:
        v0 *= 2;
        break;
    case CONTEST_RANK_GREAT:
        v0 *= 2;
        break;
    case CONTEST_RANK_ULTRA:
        if ((param6 == 1) && (contestType == CONTEST_TYPE_CUTE || contestType == CONTEST_TYPE_SMART)) {
            v0 = v0 * 3;
        } else {
            v0 += v0 / 2;
        }
        break;
    case CONTEST_RANK_MASTER:
    default:
        if ((param6 == 1) && (contestType == CONTEST_TYPE_CUTE || contestType == CONTEST_TYPE_SMART)) {
            v0 = v0 * 2 + v0 / 2;
        }
        break;
    }

    if (v0 < 0) {
        v0 = 0;
    }

    return v0;
}

static int contest_competition_0224ECC4(int contestRank, int contestType, int param2, int param3, int param4, int param5, int param6, int param7)
{
    int v0 = 0;

    switch (param2) {
    case 0:
        if (param5 == 1) {
            v0 += 3;
        }
        break;
    case 1:
        if (param5 == 2) {
            v0 += 3;
        }
        break;
    case 2:
        if (param5 == 4) {
            v0 += 3;
        }
        break;
    case 3:
        if (param5 == 3) {
            v0 += 3;
        }
        break;
    }

    if (param6 != 0) {
        if (param5 != param6) {
            v0 += 8;
        }
    }

    if (param4 != -1) {
        if ((param3 & 1) != (param4 & 1)) {
            v0 += 2;
        }

        if (param3 - param4 >= 4 * 2) {
            v0 += 5;
        }
    }

    switch (contestRank) {
    case CONTEST_RANK_NORMAL:
        v0 *= 2;
        break;
    case CONTEST_RANK_GREAT:
        v0 *= 2;
        break;
    case CONTEST_RANK_ULTRA:
        if ((param7 == 1) && (contestType == CONTEST_TYPE_CUTE || contestType == CONTEST_TYPE_SMART)) {
            v0 *= 2;
        } else {
            v0 += v0 / 2;
        }
        break;
    case CONTEST_RANK_MASTER:
    default:
        if ((param7 == 1) && (contestType == CONTEST_TYPE_CUTE || contestType == CONTEST_TYPE_SMART)) {
            v0 += v0 / 2;
        }
        break;
    }

    return v0;
}

void contest_competition_0224ED8C(int param0, DanceCompetition *param1, DancePerformanceResult *param2, u32 param3, u32 param4, u32 param5, const DanceMoveDefinition *param6, DanceContestantTask *param7)
{
    if ((param2->state == 0) && (param0 == 0)) {
        contest_competition_0224EDE0(param1, param2, param3, param4, param5, param6, param7);
    } else if ((param2->state != 0) && (param0 == 1)) {
        contest_competition_0224EE90(param1, param2, param3, param4, param5, param6, param7);
    }
}

static void contest_competition_0224EDE0(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3, u32 param4, const DanceMoveDefinition *param5, DanceContestantTask *param6)
{
    DancePacket v0;
    u32 v1 = param4 / 2;

    if ((param1->state != 0) || (param1->moveIndex >= param5->beatCount)) {
        return;
    }

    if (param1->delay > 0) {
        param1->delay--;
        return;
    }

    {
        int v2;

        for (v2 = 0; v2 < 8; v2++) {
            if (param1->performanceData.points[v2] == 1) {
                break;
            }
        }

        if (v2 >= 8) {
            return;
        }

        if (param1->performanceData.scores[v2] <= param2) {
            contest_competition_0224DE54(param1->contestantID, param1->performanceData.ranks[v2], param2, param4, &param5->scores, &v0, NULL, param1->state, param1->moveIndex, param5->beatCount, param0->scoreState.contestRank);
            contest_competition_0224D6B0(param6, &v0);

            param1->performanceData.points[v2] = 0;
            param1->moveIndex++;
            param1->delay = param4 / 10000 - 2;
        }
    }
}

static void contest_competition_0224EE90(DanceCompetition *param0, DancePerformanceResult *param1, u32 param2, u32 param3, u32 param4, const DanceMoveDefinition *param5, DanceContestantTask *param6)
{
    DancePacket v0;
    DancePacket *v1;
    u32 v2, v3;

    v2 = param4 / 2;

    if ((param1->state == 0) || (param1->moveIndex >= param5->beatCount) || (param0->movePackets[param1->moveIndex].isValid == 0)) {
        return;
    }

    if (param1->delay > 0) {
        param1->delay--;
        return;
    }

    v1 = &param0->movePackets[param1->moveIndex];
    v3 = param2 - param3 / 2;

    if (param1->rawData.flag == 0) {
        u32 v4;
        s32 v5;
        int v6, v7;
        int v8, v9, v10;

        if (param1->moveIndex == 0) {
            v10 = -1;
            v9 = 0;
        } else {
            v10 = param0->movePackets[param1->moveIndex - 1].moveSlot;
            v9 = param0->movePackets[param1->moveIndex - 1].judgeID;
        }

        v6 = contest_competition_0224EC24(param0->contest->data.contestRank, param0->contest->data.contestType, param1->contestRank, v1->moveSlot, v10, param0->scoreState.contestRank, param0->contestRank);
        v7 = contest_competition_0224ECC4(param0->contest->data.contestRank, param0->contest->data.contestType, param1->contestRank, v1->moveSlot, v10, v1->judgeID, v9, param0->contestRank);
        v4 = (v1->moveSlot * v2 + 10000 / 2) / 10000;
        v5 = (Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % (2 + v6)) - (1 + v6 / 2);

        if (v5 + (s32)v4 < 0) {
            v4 = 0;
        } else {
            v4 += v5;
        }

        if ((Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % 100) < (0 + v6 + v7)) {
            do {
                v8 = 0 + (Contest_GetSeededRNGNext(param1->rngSeed, &param1->rngSeed) % 4);
            } while (contest_competition_0224DD28(v8) == v1->judgeID);
        } else {
            v8 = contest_competition_0224DD5C(v1->judgeID);
        }

        param1->rawData.value = v4;
        param1->rawData.score = v8;
        param1->rawData.flag = 1;
    }

    {
        if (param1->rawData.value <= v3) {
            contest_competition_0224DE54(param1->contestantID, param1->rawData.score, param2, param4, &param5->scores, &v0, param0->movePackets, param1->state, param1->moveIndex, param5->beatCount, param0->scoreState.contestRank);
            contest_competition_0224D6B0(param6, &v0);

            param1->rawData.flag = 0;
            param1->moveIndex++;
            param1->delay = param4 / 10000 - 2;
        }
    }
}
