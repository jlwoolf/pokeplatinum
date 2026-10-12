#include "contest_competition/contest_competition_02245F14.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_022413D8.h"
#include "contest_competition/contest_competition_02243AC4.h"
#include "contest_competition/struct_acting_performance.h"
#include "contest_competition/struct_acting_performance_messages.h"
#include "contest_competition/struct_acting_turn_state.h"
#include "contest_competition/struct_acting_competition.h"

#include "contest.h"
#include "move_table.h"
#include "contest_util.h"

typedef int (*UnkFuncPtr_contest_competition_02253AF8)(ActingCompetition *, ActingTurnState *, int, int, int);

typedef struct {
    UnkFuncPtr_contest_competition_02253AF8 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06[2];
} ContestEffectHandler;

static void contest_competition_02246540(ActingTurnState *param0);
static int contest_competition_02246578(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246668(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246774(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_022467CC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246830(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246834(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_0224687C(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_022468D4(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246918(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246960(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_022469DC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_022469FC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246A50(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246AB0(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246B74(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246BC0(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246C10(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246C4C(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246C88(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246CDC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246DA4(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246E08(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);
static int contest_competition_02246E68(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4);

__attribute__((aligned(4))) static const u8 Unk_contest_competition_02253AEC[] = {
    0xA,
    0x14,
    0x1E,
    0x28
};

static const ContestEffectHandler Unk_contest_competition_02253AF8[CONTEST_EFFECT_MAX] = {
    [CONTEST_EFFECT_NONE] = { contest_competition_02246830, 0x3, 0xFF },
    [CONTEST_EFFECT_FIRST_NEXT_TURN] = { contest_competition_02246578, 0x3, 0xFF },
    [CONTEST_EFFECT_LAST_NEXT_TURN] = { contest_competition_02246668, 0x3, 0xFF },
    [CONTEST_EFFECT_DOUBLED_JUDGE] = { contest_competition_02246774, 0x5, 0xFF },
    [CONTEST_EFFECT_2_HEARTS_WHEN_VOLTAGE_UP] = { contest_competition_022467CC, 0x3, 0xFF },
    [CONTEST_EFFECT_BASIC] = { contest_competition_02246830, 0x3, 0xFF },
    [CONTEST_EFFECT_UNIQUE_JUDGE] = { contest_competition_02246834, 0x5, 0x0 },
    [CONTEST_EFFECT_CONSECUTIVE_USE] = { contest_competition_0224687C, 0x3, 0xFF },
    [CONTEST_EFFECT_VOLTAGE] = { contest_competition_022468D4, 0x3, 0xFF },
    [CONTEST_EFFECT_ALL_SAME_JUDGE] = { contest_competition_02246918, 0x5, 0x0 },
    [CONTEST_EFFECT_LOWERS_VOLTAGE] = { contest_competition_02246960, 0x3, 0xFF },
    [CONTEST_EFFECT_DOUBLE_NEXT_TURN] = { contest_competition_022469DC, 0x3, 0xFF },
    [CONTEST_EFFECT_STEAL_VOLTAGE] = { contest_competition_02246A50, 0x3, 0xFF },
    [CONTEST_EFFECT_SUPPRESS_VOLTAGE] = { contest_competition_022469FC, 0x3, 0xFF },
    [CONTEST_EFFECT_RANDOM_ORDER] = { contest_competition_02246AB0, 0x3, 0xFF },
    [CONTEST_EFFECT_DOUBLE_FINAL_ACT] = { contest_competition_02246B74, 0x3, 0xFF },
    [CONTEST_EFFECT_LOW_VOLTAGE_ADVANTAGE] = { contest_competition_02246BC0, 0x3, 0xFF },
    [CONTEST_EFFECT_FIRST_PERFORMANCE_ADVANTAGE] = { contest_competition_02246C10, 0x3, 0xFF },
    [CONTEST_EFFECT_FINAL_PERFORMANCE_ADVANTAGE] = { contest_competition_02246C4C, 0x3, 0xFF },
    [CONTEST_EFFECT_NO_VOLTAGE_DOWN] = { contest_competition_02246C88, 0x3, 0xFF },
    [CONTEST_EFFECT_TWO_VOLTAGE_IN_A_ROW_ADVANTAGE] = { contest_competition_02246CDC, 0x3, 0xFF },
    [CONTEST_EFFECT_HIGH_SCORE_LATER_TURN] = { contest_competition_02246DA4, 0x3, 0xFF },
    [CONTEST_EFFECT_MAX_VOLTAGE_ADVANTAGE] = { contest_competition_02246E08, 0x3, 0xFF },
    [CONTEST_EFFECT_PITY_POINTS] = { contest_competition_02246E68, 0x6, 0xFF }
};

// This seems to be using 30000 as a NULL value
static void contest_competition_02245F14(ActingPerformance *param0, int contestMoveEffect, int param2, int param3, int param4, int moveID, int param6)
{
    param0->messageID = contestMoveEffect;
    param0->messageArg = param2;

    if (param3 != 30000) {
        param0->messageParams.contestantID = param3;
    }

    if (param4 != 30000) {
        param0->messageParams.moveSlot = param4;
    }

    if (moveID != 30000) {
        param0->messageParams.moveID = moveID;
    }

    if (param6 != 30000) {
        param0->messageParams.messageValue = param6;
    }
}

void contest_competition_02245F44(ActingCompetition *param0, ActingTurnState *param1)
{
    int contestantID;

    *param1 = param0->matchState.turnState;

    contest_competition_02246540(param1);
    MI_CpuClear8(param1->performances, sizeof(ActingPerformance) * 4);

    for (contestantID = 0; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
        contest_competition_02243120(param0, &param1->performances[contestantID].messageParams, contestantID);

        param1->performances[contestantID].contestantID = param0->matchState.contestantIDs[contestantID];
        param1->performances[contestantID].moveID = param0->matchState.moveIDs[contestantID];
        param1->performances[contestantID].contestMoveEffect = MoveTable_LoadParam(param1->performances[contestantID].moveID, MOVEATTRIBUTE_CONTEST_EFFECT);
        param1->performances[contestantID].judgeID = contest_competition_02243AC4(&param0->matchState, contestantID);
    }
}

void contest_competition_02245FB4(ActingCompetition *param0, ActingTurnState *param1, int contestantID)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param1->performances[v0].previousAppealState = param1->performances[v0].judgeAppealState;
        param1->performances[v0].previousAppealOrder = param1->performances[v0].appealOrder;
    }

    for (v0 = 0; v0 < (1 + 2); v0++) {
        param1->voltage[v0] = param0->matchState.appealHistory[v0];
        param1->voltageDisplay[v0] = param0->matchState.appealHistory[v0];
    }
}

void contest_competition_02246018(ActingCompetition *param0, ActingTurnState *param1, int contestantID)
{
    int v0;

    for (v0 = 0; v0 < (1 + 2); v0++) {
        param0->matchState.appealHistory[v0] = param1->voltageDisplay[v0];

        if (param0->matchState.appealHistory[v0] >= (10 * 5)) {
            param0->matchState.appealHistory[v0] = 0;
        }
    }
}

void contest_competition_02246044(ActingCompetition *param0, ActingTurnState *param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->matchState.scores[v0] += param1->performances[v0].score;
        param0->matchState.turnScores[v0] = param1->performances[v0].score;
    }

    param0->matchState.turnState = *param1;
}

static void contest_competition_02246090(ActingTurnState *param0, int contestantID)
{
    int v0;

    param0->performances[contestantID].previousScore = param0->performances[contestantID].score;
    param0->performances[contestantID].bonusScore = 0;
    param0->performances[contestantID].secondaryBonus = 0;

    for (v0 = 0; v0 < (1 + 2); v0++) {
        param0->voltage[v0] = param0->voltageDisplay[v0];
    }

    for (v0 = 0; v0 < 4; v0++) {
        param0->performances[v0].performed = 0;
        param0->performances[v0].messageID = 0;
    }
}

void contest_competition_022460C8(ActingTurnState *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->performances[v0].previousTurnScore = param0->performances[v0].score;
    }
}

void contest_competition_022460DC(ActingCompetition *param0, ActingTurnState *param1, int contestantID)
{
    u32 v0, v1;

    contest_competition_02246090(param1, contestantID);

    if (Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_05 == 0) {
        Contest_LoadContestEffectMessage(param1->performances[contestantID].contestMoveEffect, 4, &v0, &v1);

        if (v0 != 0xffff) {
            contest_competition_02245F14(&param1->performances[contestantID], param1->performances[contestantID].contestMoveEffect, 4, contestantID, 30000, 30000, 30000);
        }
    }
}

void contest_competition_02246138(ActingCompetition *param0, ActingTurnState *param1, int contestantID)
{
    contest_competition_02246090(param1, contestantID);

    param1->performances[contestantID].appealPoints = Contest_GetAppealPoints(param1->performances[contestantID].contestMoveEffect);
    param1->performances[contestantID].score = param1->performances[contestantID].appealPoints;
}

void contest_competition_02246160(ActingCompetition *param0, ActingTurnState *param1, int contestantID, int param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    if (Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_04 == 3) {
        Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_00(param0, param1, contestantID, contestantID, param3);
        param1->performances[contestantID].performed = 1;
        param1->performances[contestantID].score += param1->performances[contestantID].bonusScore + param1->performances[contestantID].secondaryBonus;
    }

    for (v0 = 0; v0 <= param3; v0++) {
        int v1 = param0->matchState.contestantOrder[v0];

        if (Unk_contest_competition_02253AF8[param1->performances[v1].contestMoveEffect].unk_04 == 2) {
            contest_competition_02246090(param1, v1);
            Unk_contest_competition_02253AF8[param1->performances[v1].contestMoveEffect].unk_00(param0, param1, contestantID, v1, param3);
            param1->performances[v1].performed = 1;
            param1->performances[v1].score += param1->performances[v1].bonusScore;
        }
    }
}

void contest_competition_02246228(ActingCompetition *param0, ActingTurnState *param1, int contestantID, int param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    if (param1->previousMoves[contestantID].contestMoveEffect != CONTEST_EFFECT_NONE) {
        v0 = param1->performances[contestantID].score;
        param1->performances[contestantID].bonusScore += v0;
        contest_competition_02245F14(&param1->performances[contestantID], param1->previousMoves[contestantID].contestMoveEffect, 0, contestantID, 30000, 30000, v0 / 10);
    }

    param1->performances[contestantID].score += param1->performances[contestantID].bonusScore + param1->performances[contestantID].secondaryBonus;
}

BOOL contest_competition_022462A4(ActingCompetition *param0, ActingTurnState *param1, int contestantID, int param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    if (Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_04 == 4) {
        Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_00(param0, param1, contestantID, contestantID, param3);
        param1->performances[contestantID].performed = 1;
        param1->performances[contestantID].score += param1->performances[contestantID].bonusScore;
        return 1;
    }

    return 0;
}

BOOL contest_competition_02246304(ActingCompetition *param0, ActingTurnState *param1, int contestantID, int param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    if (Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_04 == 5) {
        Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_00(param0, param1, contestantID, contestantID, param3);
        param1->performances[contestantID].performed = 1;
        param1->performances[contestantID].score += param1->performances[contestantID].bonusScore;
        return 1;
    }

    return 0;
}

BOOL contest_competition_02246364(ActingCompetition *param0, ActingTurnState *param1, int contestantID, int param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    if (Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_04 == 6) {
        Unk_contest_competition_02253AF8[param1->performances[contestantID].contestMoveEffect].unk_00(param0, param1, contestantID, contestantID, param3);
        param1->performances[contestantID].performed = 1;
        param1->performances[contestantID].score += param1->performances[contestantID].bonusScore;
        return 1;
    }

    return 0;
}

void contest_competition_022463C4(ActingCompetition *param0, ActingTurnState *param1, int contestantID, ActingPerformanceMessages *param3)
{
    int v0, v1, v2;

    contest_competition_02246090(param1, contestantID);

    param3->actingMessagesID = ACTING_COMPETITION_MESSAGE_NONE;
    param3->actingMessagesID2 = ACTING_COMPETITION_MESSAGE_NONE;

    v1 = param0->matchState.contestantIDs[contestantID];
    v2 = contest_competition_02243AF0(param0->contest->data.contestType, param1->performances[contestantID].moveID, v1, param0->contest->data.bonusJudgeIndex);

    if ((v2 > 0) && (param1->performances[contestantID].comboStarted == 0)) {
        param1->voltageDisplay[v1] += v2;

        if (param1->voltageDisplay[v1] >= (10 * 5)) {
            param1->voltageDisplay[v1] = (10 * 5);
        }
    } else if ((v2 < 0) && (param1->performances[contestantID].comboFailed == 0) && (param1->voltageDisplay[v1] > 0)) {
        param1->voltageDisplay[v1] += v2;

        if (param1->voltageDisplay[v1] <= 0) {
            param1->voltageDisplay[v1] = 0;
        }
    } else {
        v2 = 0;
    }

    if (param1->voltageDisplay[v1] >= (10 * 5)) {
        if (v1 == param0->contest->data.bonusJudgeIndex) {
            param1->performances[contestantID].excitement = (10 * 8);
        } else {
            param1->performances[contestantID].excitement = (10 * 5);
        }
    }

    param3->messageParams2.messageValue = param1->performances[contestantID].excitement / 10;

    if (v2 > 0) {
        param3->actingMessagesID = Contest_GetActingCompetitionMessageGoodMoveType(MoveTable_LoadParam(param1->performances[contestantID].moveID, MOVEATTRIBUTE_CONTEST_TYPE));

        switch (param1->voltageDisplay[v1] / 10) {
        case 2:
            break;
        case 3:
            break;
        case 4:
            param3->actingMessagesID2 = ACTING_COMPETITION_MESSAGE_AUDIENCE_IS_PRETTY_EXCITED;
            break;
        case 5:
            param3->actingMessagesID2 = ACTING_COMPETITION_MESSAGE_AUDIENCE_IS_GOING_WILD;
            break;
        }
    } else if (v2 < 0) {
        param3->actingMessagesID = Contest_GetActingCompetitionMessageBadMoveType(MoveTable_LoadParam(param1->performances[contestantID].moveID, MOVEATTRIBUTE_CONTEST_TYPE));

        switch (param1->voltageDisplay[v1] / 10) {
        case 3:
            break;
        case 2:
            break;
        case 1:
            break;
        case 0:
            if (param1->voltage[v1] != 0) {
                (void)0;
            }
            break;
        }
    }

    param1->performances[contestantID].score += param1->performances[contestantID].excitement;
}

void contest_competition_02246518(ActingCompetition *param0, ActingTurnState *param1, int contestantID, ActingPerformanceMessages *param3)
{
    int v0;

    contest_competition_02246090(param1, contestantID);

    v0 = contest_competition_02243AE4(param1->performances[contestantID].judgeID);
    param1->performances[contestantID].score += v0;
}

static void contest_competition_02246540(ActingTurnState *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->previousMoves[v0].moveID = MOVE_NONE;
        param0->previousMoves[v0].contestMoveEffect = param0->performances[v0].performedMoveEffect;
    }
}

static int contest_competition_02246578(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    u8 v0[4];
    int v1, v2, v3;

    v3 = 4;

    for (v1 = 0; v1 < 4; v1++) {
        if (param1->performances[v1].judgeAppealState == 0) {
            v0[v1] = 0xff;
        } else {
            if ((param1->performances[v1].judgeAppealState == 1) && (param1->performances[v1].appealOrder == 0)) {
                v3 = v1;
            }

            v0[v1] = param1->performances[v1].appealOrder;
        }
    }

    v0[param3] = 0xff;

    for (v1 = 0; v1 < 4; v1++) {
        for (v2 = 0; v2 < 4; v2++) {
            if (v0[v2] != 0xff) {
                if ((v1 == v0[v2]) && (v0[v2] == param1->performances[v2].appealOrder)) {
                    v0[v2]++;
                    break;
                }
            }
        }

        if (v2 == 4) {
            break;
        }
    }

    for (v1 = 0; v1 < 4; v1++) {
        if (v0[v1] != 0xff) {
            param1->performances[v1].appealOrder = v0[v1];
        }
    }

    param1->performances[param3].judgeAppealState = 1;
    param1->performances[param3].appealOrder = 0;

    if (v3 != 4) {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 1, param3, v3, 30000, 30000);
    } else {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
    }

    return 1;
}

static int contest_competition_02246668(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    s8 v0, v1;
    u8 v2[4];
    int v3 = 4;

    for (v0 = 0; v0 < 4; v0++) {
        if (param1->performances[v0].judgeAppealState == 0) {
            v2[v0] = 0xff;
        } else {
            if ((param1->performances[v0].judgeAppealState == 2) && (param1->performances[v0].appealOrder == 4 - 1)) {
                v3 = v0;
            }

            v2[v0] = param1->performances[v0].appealOrder;
        }
    }

    v2[param3] = 0xff;

    for (v0 = 4 - 1; v0 > -1; v0--) {
        for (v1 = 0; v1 < 4; v1++) {
            if (v2[v1] != 0xff) {
                if ((v0 == v2[v1]) && (v2[v1] == param1->performances[v1].appealOrder)) {
                    v2[v1]--;
                    break;
                }
            }
        }

        if (v1 == 4) {
            break;
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        if (v2[v0] != 0xff) {
            param1->performances[v0].appealOrder = v2[v0];
        }
    }

    param1->performances[param3].judgeAppealState = 2;
    param1->performances[param3].appealOrder = 4 - 1;

    if (v3 == 4) {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
    } else {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 1, param3, v3, 30000, 30000);
    }

    return 1;
}

static int contest_competition_02246774(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    param1->performances[param3].bonusScore += param1->performances[param3].judgeID * (10 * 2);

    switch (param1->performances[param3].judgeID) {
    case 0:
        v0 = 0;
        break;
    case 1:
        v0 = 1;
        break;
    case 2:
        v0 = 2;
        break;
    default:
        v0 = 3;
        break;
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, v0, param3, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_022467CC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;
    int v1;

    v0 = param1->performances[param3].contestantID;
    v1 = contest_competition_02243AF0(param0->contest->data.contestType, param1->performances[param3].moveID, v0, param0->contest->data.bonusJudgeIndex);

    if ((v1 > 0) && (param1->performances[param3].comboStarted == 0)) {
        param1->performances[param3].bonusScore += (10 * 2);
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, param1->performances[param3].moveID, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_02246830(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    return 1;
}

static int contest_competition_02246834(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param1->performances[param3].judgeID == 0) {
        param1->performances[param3].bonusScore += (10 * 3);
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
    } else {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 1, param3, 30000, 30000, 30000);
    }

    return 1;
}

static int contest_competition_0224687C(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param1->performances[param3].moveID != param0->matchState.previousMoveIDs[param3]) {
        param1->previousMoves[param3].moveID = param1->performances[param3].moveID;
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_022468D4(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0 = param1->performances[param3].contestantID;
    int v1 = param1->voltage[v0];
    param1->performances[param3].bonusScore += v1;
    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, v1 / 10);

    return 1;
}

static int contest_competition_02246918(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param1->performances[param3].judgeID == 4 - 1) {
        param1->performances[param3].bonusScore += (10 * 15);
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
    } else {
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 1, param3, 30000, 30000, 30000);
    }

    return 1;
}

static int contest_competition_02246960(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    if (param1->performances[param3].comboFailed == 1) {
        return 0;
    }

    for (v0 = 0; v0 < (1 + 2); v0++) {
        if (param1->voltageDisplay[v0] != 0) {
            break;
        }
    }

    if (v0 == (1 + 2)) {
        return 0;
    }

    param1->performances[param3].comboFlag = 1;

    for (v0 = 0; v0 < (1 + 2); v0++) {
        if (param1->voltageDisplay[v0] > 0) {
            param1->voltageDisplay[v0] += (-10 * 1);
        }
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_022469DC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    param1->performances[param3].performedMoveEffect = param1->performances[param3].contestMoveEffect;
    return 1;
}

static int contest_competition_022469FC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    for (v0 = param4; v0 < 4; v0++) {
        param1->performances[param0->matchState.contestantOrder[v0]].unk_28_1 = 1;
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_02246A50(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    if (param4 == 0) {
        return 0;
    }

    v0 = param0->matchState.contestantOrder[param4 - 1];

    if (param1->performances[v0].excitement == 0) {
        return 0;
    }

    param1->performances[param3].bonusScore += param1->performances[v0].excitement;
    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, v0, 30000, 30000);
    return 1;
}

static int contest_competition_02246AB0(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    s8 v0, v1;
    u8 v2[4];
    u8 v3[4];
    u8 v4, v5;

    for (v0 = 0; v0 < 4; v0++) {
        v2[v0] = v0;
        v3[v0] = v0;
    }

    for (v0 = 0; v0 < 4; v0++) {
        v4 = Contest_GetRNGNext(param0->contest) % (4 - v0);
        v5 = v4;

        for (v1 = 0; v1 < 4; v1++) {
            if (v3[v1] != 0xff) {
                if (v5 == 0) {
                    v2[v1] = v0;
                    v3[v1] = 0xff;
                    break;
                } else {
                    v5--;
                }
            }
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        param1->performances[v0].judgeAppealState = 3;
        param1->performances[v0].appealOrder = v2[v0];
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_02246B74(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param4 == 4 - 1) {
        param1->performances[param3].bonusScore += param1->performances[param3].score;
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, param1->performances[param3].score / 10);
        return 1;
    }

    return 0;
}

static int contest_competition_02246BC0(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0, v1;
    static const u8 v2[] = {
        10 * 4,
        10 * 3,
        10 * 2,
        10 * 1,
        10 * 0,
        10 * 0
    };

    v1 = param1->performances[param3].contestantID;
    v0 = param1->voltage[v1] / 10;
    param1->performances[param3].bonusScore += v2[v0];

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, v2[v0] / 10);
    return 1;
}

static int contest_competition_02246C10(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param4 == 0) {
        param1->performances[param3].bonusScore += 10 * 2;
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_02246C4C(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    if (param4 == 4 - 1) {
        param1->performances[param3].bonusScore += 10 * 2;
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_02246C88(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    for (v0 = param4; v0 < 4; v0++) {
        param1->performances[param0->matchState.contestantOrder[v0]].unk_28_2 = 1;
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, 30000, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_02246CDC(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0, v1, v2;

    if (param4 == 0) {
        return 0;
    }

    v0 = param0->matchState.contestantOrder[param4 - 1];

    if ((param1->performances[param3].comboStarted != 0) || (param1->performances[v0].comboStarted != 0)) {
        return 0;
    }

    v1 = contest_competition_02243AF0(param0->contest->data.contestType, param1->performances[param3].moveID, param1->performances[param3].contestantID, param0->contest->data.bonusJudgeIndex);
    v2 = contest_competition_02243AF0(param0->contest->data.contestType, param1->performances[v0].moveID, param1->performances[v0].contestantID, param0->contest->data.bonusJudgeIndex);

    if ((v2 > 0) && (v1 > 0)) {
        param1->performances[param3].bonusScore += (10 * 3);
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, v0, 30000, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_02246DA4(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    param1->performances[param3].bonusScore += Unk_contest_competition_02253AEC[param4];

    switch (param4) {
    case 0:
        v0 = 0;
        break;
    case 1:
        v0 = 1;
        break;
    case 2:
        v0 = 2;
        break;
    case 3:
    default:
        v0 = 3;
        break;
    }

    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, v0, param3, 30000, 30000, 30000);
    return 1;
}

static int contest_competition_02246E08(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    if (param4 == 0) {
        return 0;
    }

    v0 = param0->matchState.contestantOrder[param4 - 1];

    if ((param1->performances[v0].excitement >= (10 * 5)) || (param1->performances[v0].excitement >= (10 * 8))) {
        param1->performances[param3].bonusScore += (10 * 3);
        contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);
        return 1;
    }

    return 0;
}

static int contest_competition_02246E68(ActingCompetition *param0, ActingTurnState *param1, int param2, int param3, int param4)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (v0 == param3) {
            continue;
        }

        if (param1->performances[v0].previousScore < param1->performances[param3].previousTurnScore) {
            break;
        }
    }

    if (v0 != 4) {
        return 0;
    }

    param1->performances[param3].bonusScore += (10 * 3);
    contest_competition_02245F14(&param1->performances[param3], param1->performances[param3].contestMoveEffect, 0, param3, 30000, 30000, 30000);

    return 1;
}
