#include "contest_competition/contest_competition_02243AC4.h"

#include <nitro.h>
#include <string.h>

#include "generated/pokemon_contest_types.h"

#include "contest_competition/struct_acting_match_state.h"

#include "move_table.h"

__attribute__((aligned(4))) static const s8 Unk_contest_competition_022539C8[CONTEST_TYPE_MAX][CONTEST_TYPE_MAX] = {
    { 0xA, 0x0, 0xFFFFFFFFFFFFFFF6, 0xFFFFFFFFFFFFFFF6, 0x0 },
    { 0x0, 0xA, 0x0, 0xFFFFFFFFFFFFFFF6, 0xFFFFFFFFFFFFFFF6 },
    { 0xFFFFFFFFFFFFFFF6, 0x0, 0xA, 0x0, 0xFFFFFFFFFFFFFFF6 },
    { 0xFFFFFFFFFFFFFFF6, 0xFFFFFFFFFFFFFFF6, 0x0, 0xA, 0x0 },
    { 0x0, 0xFFFFFFFFFFFFFFF6, 0xFFFFFFFFFFFFFFF6, 0x0, 0xA }
};

int contest_competition_02243AC4(ActingMatchState *param0, int param1)
{
    int v0, v1 = 0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->contestantIDs[v0] == param0->contestantIDs[param1]) {
            v1++;
        }
    }

    v1--;
    return v1;
}

int contest_competition_02243AE4(int param0)
{
    static const u8 v0[] = {
        3 * 10,
        2 * 10,
        1 * 10,
        0 * 10,
    };

    return v0[param0];
}

int contest_competition_02243AF0(int contestType, int moveID, int unused1, int unused2)
{
    int moveContestType;
    int v1;

    moveContestType = MoveTable_LoadParam(moveID, MOVEATTRIBUTE_CONTEST_TYPE);
    v1 = Unk_contest_competition_022539C8[contestType][moveContestType];

    return v1;
}

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022539B0[] = {
    0x7512,
    0x751C,
    0x7526,
    0x7530
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022539C0[] = {
    0xFFFFFFFFFFFF8AD0,
    0xFFFFFFFFFFFF8ADA,
    0xFFFFFFFFFFFF8AE4,
    0xFFFFFFFFFFFF8AEE
};

__attribute__((aligned(4))) static const s16 Unk_contest_competition_022539B8[] = {
    0xFFFFFFFFFFFFD8F0,
    0xFFFFFFFFFFFFFE0C,
    0x1F4,
    0x2710
};

void contest_competition_02243B0C(ActingMatchState *param0)
{
    int v0, v1, v2;
    s16 v3[4];
    u8 v4[4];
    u8 v5[4];

    for (v0 = 0; v0 < 4; v0++) {
        v3[v0] = param0->turnScores[v0];
        v4[v0] = v0;

        for (v1 = 0; v1 < 4; v1++) {
            if (v0 == param0->contestantOrder[v1]) {
                v5[v0] = v1;
                break;
            }
        }
    }

    {
        for (v0 = 0; v0 < 4; v0++) {
            switch (param0->turnState.performances[v0].judgeAppealState) {
            case 0:
            default:
                break;
            case 1:
                v3[v0] = Unk_contest_competition_022539C0[param0->turnState.performances[v0].appealOrder];
                break;
            case 2:
                v3[v0] = Unk_contest_competition_022539B0[param0->turnState.performances[v0].appealOrder];
                break;
            case 3:
                v3[v0] = Unk_contest_competition_022539B8[param0->turnState.performances[v0].appealOrder];
                break;
            }
        }
    }

    for (v0 = 0; v0 < 4 - 1; v0++) {
        for (v1 = 4 - 1; v1 > v0; v1--) {
            if ((v3[v1 - 1] > v3[v1]) || ((v3[v1 - 1] == v3[v1]) && (v5[v1 - 1] < v5[v1]))) {
                v2 = v3[v1];
                v3[v1] = v3[v1 - 1];
                v3[v1 - 1] = v2;

                v2 = v4[v1];
                v4[v1] = v4[v1 - 1];
                v4[v1 - 1] = v2;

                v2 = v5[v1];
                v5[v1] = v5[v1 - 1];
                v5[v1 - 1] = v2;
            }
        }
    }

    for (v0 = 0; v0 < 4; v0++) {
        param0->contestantOrder[v0] = v4[v0];
    }
}
