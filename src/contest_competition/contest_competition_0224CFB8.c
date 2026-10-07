#include "contest_competition/contest_competition_0224CFB8.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_0223DAD0.h"
#include "contest_competition/contest_competition_022492DC.h"
#include "contest_competition/contest_competition_0224A0FC.h"
#include "contest_competition/contest_competition_0224E930.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_contest_competition_0223F03C.h"
#include "contest_competition/struct_contest_competition_02243C28.h"
#include "contest_competition/struct_contest_competition_02243C80.h"
#include "contest_competition/struct_contest_competition_0224C0C0.h"
#include "contest_competition/struct_contest_competition_0224D078.h"
#include "contest_competition/struct_contest_competition_0224D240.h"
#include "contest_competition/struct_contest_competition_0224D41C.h"
#include "contest_competition/struct_contest_competition_0224D69C.h"
#include "contest_competition/struct_contest_competition_0224D710.h"
#include "contest_competition/struct_contest_competition_0224DC1C.h"
#include "contest_competition/struct_contest_competition_0224DD90.h"
#include "contest_competition/struct_contest_competition_0224DF54.h"
#include "contest_competition/struct_contest_competition_0224DF54_sub1.h"
#include "contest_competition/struct_contest_competition_0224DF54_sub2.h"
#include "contest_competition/struct_contest_competition_0224DFF8.h"
#include "contest_competition/struct_contest_competition_0224E1F4.h"
#include "contest_competition/struct_contest_competition_0224E4A8.h"
#include "contest_competition/struct_contest_competition_0224E584.h"
#include "contest_competition/struct_contest_competition_0224E6C8.h"
#include "contest_competition/struct_contest_competition_0224E86C.h"
#include "contest_competition/struct_contest_competition_0224EDE0.h"
#include "contest_competition/struct_contest_competition_0224F30C.h"
#include "contest_competition/struct_contest_competition_0224F3D8.h"
#include "contest_competition/struct_contest_competition_022539E4.h"
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

static int contest_competition_0224CFF8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D00C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224D01C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4);
static int contest_competition_0224D020(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D034(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224D078(SysTask *param0, void *param1);
static int contest_competition_0224D1D4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D1E8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224D240(SysTask *param0, void *param1);
static int contest_competition_0224DF88(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224DF9C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224DFF8(SysTask *param0, void *param1);
static void contest_competition_0224E1F4(SysTask *param0, void *param1);
static int contest_competition_0224D544(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D558(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224D710(SysTask *param0, void *param1);
static void contest_competition_0224DF84(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4);
static int contest_competition_0224D4EC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D500(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_0224DC1C(UnkStruct_contest_competition_0224DC1C *param0, int *param1, int param2, int param3);
static UnkStruct_contest_competition_0224D69C *contest_competition_0224D668(UnkStruct_contest_competition_0224DF54 *param0, int param1);
static void contest_competition_0224D69C(UnkStruct_contest_competition_0224D69C *param0);
static void contest_competition_0224D6CC(SysTask *param0, void *param1);
static int contest_competition_0224E43C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E450(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224E4A8(SysTask *param0, void *param1);
static int contest_competition_0224E518(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E52C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224E584(SysTask *param0, void *param1);
static int contest_competition_0224E648(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E65C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224E6C8(SysTask *param0, void *param1);
static int contest_competition_0224E77C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E790(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_0224E7B4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E7C8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_0224D3C4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224D3D8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224D41C(SysTask *param0, void *param1);
static void contest_competition_0224DF54(UnkStruct_contest_competition_0224DF54 *param0);
static int contest_competition_0224E800(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224E814(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224E86C(SysTask *param0, void *param1);

static const UnkStruct_contest_competition_022539E4 Unk_contest_competition_022549E4[] = {
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

void contest_competition_0224CFB8(UnkStruct_contest_competition_0224DF54 *param0)
{
    UnkStruct_contest_competition_02243C28 v0;

    v0.unk_00 = Unk_contest_competition_022549E4;
    v0.unk_04 = NELEMS(Unk_contest_competition_022549E4);
    v0.playerContestantID = param0->unk_00->data.playerContestantID;
    v0.unk_08 = param0->unk_00->data.leaderContestantID;
    v0.isLinkContest = param0->unk_00->isLinkContest;

    contest_competition_0224F18C(&param0->unk_109C, &v0);
}

static int contest_competition_0224CFF8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D00C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static void contest_competition_0224D01C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    return;
}

static int contest_competition_0224D020(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D034(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224D078 *v1 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224D078));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_0224D078));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0C = param0;

    SysTask_Start(contest_competition_0224D078, v1, 30000);
}

static void contest_competition_0224D078(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224D078 *v0 = param1;

    switch (v0->unk_10) {
    case 0:

        if (v0->unk_14 > 0) {
            v0->unk_14--;
            break;
        }

        if (v0->unk_13 > 0) {
            v0->unk_13--;
            break;
        }

        v0->unk_13 = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;

            v1 = Bg_GetTilemapBuffer(v0->unk_00->unk_14.unk_60, 2);

            for (v4 = 0; v4 < 4; v4++) {
                if (Unk_contest_competition_022549C4[v0->unk_11] + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (Unk_contest_competition_022549C4[v0->unk_11] + v4)];
                v7 = Unk_contest_competition_022549CC[v0->unk_12] + 32 * v4;
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
                if ((v0->unk_11 > 0) && (v0->unk_12 == 0)) {
                    v2 = &v1[32 * Unk_contest_competition_022549C4[v0->unk_11 - 1]];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->unk_00->unk_14.unk_60, 2);
        }

        v0->unk_12++;

        if (v0->unk_12 >= NELEMS(Unk_contest_competition_022549CC)) {
            v0->unk_12 = 0;
            v0->unk_11++;
            v0->unk_14 = 0;

            if (v0->unk_11 >= NELEMS(Unk_contest_competition_022549C4)) {
                v0->unk_10++;
            }
        }
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224D1D4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D1E8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224D240 *v1 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224D240));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_0224D240));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0C = param0;

    SysTask_Start(contest_competition_0224D240, v1, 30000);
    v0->unk_1078 = 0;
    Sound_PlayBGM(CONTEST_DRESSING_ROOM_sseq);
}

static void contest_competition_0224D240(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224D240 *v0 = param1;

    switch (v0->unk_10) {
    case 0:
        if (v0->unk_14 > 0) {
            v0->unk_14--;
            break;
        }

        if (v0->unk_13 > 0) {
            v0->unk_13--;
            break;
        }

        v0->unk_13 = 1;

        {
            u16 *v1, *v2;
            int v3, v4, v5, v6, v7;
            int v8;

            v1 = Bg_GetTilemapBuffer(v0->unk_00->unk_14.unk_60, 2);

            for (v4 = 0; v4 < 4; v4++) {
                v8 = Unk_contest_competition_022549C4[NELEMS(Unk_contest_competition_022549C4) - 1 - v0->unk_11];

                if (v8 + v4 < 0) {
                    continue;
                }

                v2 = &v1[32 * (v8 + v4)];
                v7 = Unk_contest_competition_022549CC[NELEMS(Unk_contest_competition_022549CC) - 1 - v0->unk_12] + 32 * v4;
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
                if ((v0->unk_11 > 0) && (v0->unk_12 == 0)) {
                    v8 = Unk_contest_competition_022549C4[NELEMS(Unk_contest_competition_022549C4) - 1 - v0->unk_11 + 1];
                    v8 += 4 - 1;
                    v2 = &v1[v8 * 32];

                    for (v6 = 0; v6 < 32; v6++) {
                        v2[v6] &= 0xfc00;
                        v2[v6] |= 0x200 + (v6 % 8);
                    }
                }
            }

            Bg_ScheduleTilemapTransfer(v0->unk_00->unk_14.unk_60, 2);
        }

        v0->unk_12++;

        if (v0->unk_12 >= NELEMS(Unk_contest_competition_022549CC)) {
            v0->unk_12 = 0;
            v0->unk_11++;
            v0->unk_14 = 0;

            if (v0->unk_11 >= NELEMS(Unk_contest_competition_022549C4)) {
                v0->unk_10++;
            }
        }
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224D3C4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_0224D3D8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224D41C *v1 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224D41C));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_0224D41C));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0C = param0;

    SysTask_Start(contest_competition_0224D41C, v1, 30000);
}

static void contest_competition_0224D41C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224D41C *v0 = param1;

    switch (v0->unk_10) {
    case 0:
        Sound_StopBGM(1135, 30);
        v0->unk_10++;
        break;
    case 1:
        if (Sound_IsFadeActive() == FALSE) {
            v0->unk_10++;
        }
        break;
    case 2:
        G2_BlendNone();
        contest_competition_0224C84C();
        contest_competition_0224ABDC(&v0->unk_00->unk_14, 1);
        Sound_PlayEffect(SEQ_SE_DP_CON_019_sseq);
        v0->unk_10++;
        break;
    case 3:
        v0->unk_12++;

        if (v0->unk_12 > 30) {
            v0->unk_12 = 0;
            v0->unk_10++;
        }
        break;
    case 4:
        contest_competition_0224C6B0(v0->unk_00, v0->unk_00->unk_00->data.playerContestantID, &v0->unk_11);
        v0->unk_10++;
        break;
    case 5:
        if (v0->unk_11 == 1) {
            v0->unk_10++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224D4EC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0223F03C));
    return v1;
}

static void contest_competition_0224D500(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0223F03C *v1 = param3;
    int v2;

    v0->unk_1B24 = 1;

    for (v2 = 0; v2 < 4; v2++) {
        v0->unk_00->contestantOrder[v2] = v1->unk_00[v2];
    }

    if (Contest_IsPlayerLeader(v0->unk_00) == FALSE) {
        contest_competition_0224F26C(param0, param2, NULL, 0);
    }
}

static int contest_competition_0224D544(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224D558(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224DF54_sub2 *v1 = param3;
    UnkStruct_contest_competition_0224D710 *v2;
    int contestantID, v4;

    v2 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224D710));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_0224D710));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;
    v2->unk_18 = *v1;
    v2->unk_50.unk_00 = v0;

    SysTask_Start(contest_competition_0224D710, v2, 30000);

    for (contestantID = 0; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
        if (contestantID < v0->unk_00->data.connectionCount) {
            v2->unk_140[contestantID] = contest_competition_0224D668(v0, 0);
        } else {
            v2->unk_140[contestantID] = contest_competition_0224D668(v0, 1);
        }
    }

    {
        for (v4 = 0; v4 < 4; v4++) {
            if (v2->unk_18.unk_02[v4] == v2->unk_00->unk_00->data.playerContestantID) {
                v2->unk_00->unk_14.unk_A2C = v4;
                break;
            }
        }
    }

    contest_competition_0224DF54(v0);

    for (contestantID = v0->unk_00->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
        {
            for (v4 = 0; v4 < CONTEST_NUM_PARTICIPANTS; v4++) {
                if (v2->unk_18.unk_02[v4] == contestantID) {
                    break;
                }
            }
        }
        contest_competition_0224E930(&v2->unk_58[contestantID], contestantID, v4, v1->unk_14[contestantID], v0->unk_00->data.cameraFlashVariant[contestantID]);
    }
}

static UnkStruct_contest_competition_0224D69C *contest_competition_0224D668(UnkStruct_contest_competition_0224DF54 *param0, int param1)
{
    UnkStruct_contest_competition_0224D69C *v0 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224D69C));
    MI_CpuClear8(v0, sizeof(UnkStruct_contest_competition_0224D69C));

    v0->unk_04 = param0;
    v0->unk_11 = param1;
    v0->unk_00 = SysTask_Start(contest_competition_0224D6CC, v0, (30000 + 100));

    return v0;
}

static void contest_competition_0224D69C(UnkStruct_contest_competition_0224D69C *param0)
{
    SysTask_Done(param0->unk_00);
    Heap_Free(param0);
}

void contest_competition_0224D6B0(UnkStruct_contest_competition_0224D69C *param0, const UnkStruct_contest_competition_0224EDE0 *param1)
{
    param0->unk_08 = *param1;
    param0->unk_12 = 1;
}

static void contest_competition_0224D6CC(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224D69C *v0 = param1;

    if (v0->unk_12 == 0) {
        return;
    }

    if (v0->unk_04->unk_00->isLinkContest == FALSE || v0->unk_11 == 1) {
        contest_competition_0224B20C(v0->unk_04, &v0->unk_08);
        v0->unk_12 = 0;
    } else {
        if (CommSys_SendDataFixedSize(25, &v0->unk_08) == 1) {
            v0->unk_12 = 0;
        }
    }
}

static void contest_competition_0224D710(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224D710 *v0 = param1;
    int v1, v2, v3;
    u32 v4;
    int v5;

    if (v0->unk_00->unk_00->data.playerContestantID == v0->unk_18.unk_00) {
        v2 = 0;
    } else {
        v2 = 1;
    }

    v4 = v0->unk_00->unk_107C - v0->unk_00->unk_1084;

    if (v4 < (v0->unk_18.unk_0C >> 1)) {
        v5 = 0;
    } else {
        v5 = 1;
    }

    switch (v0->unk_10) {
    case 0:
        contest_competition_0224B068(&v0->unk_00->unk_14, 0);
        contest_competition_0224BC4C(v0->unk_00);
        contest_competition_0224E990(v0->unk_00, &v0->unk_58[v0->unk_18.unk_00], v0->unk_18.unk_0C, v0->unk_18.unk_08);
        contest_competition_0224C54C(v0->unk_00->unk_14.unk_1FC, v0->unk_00->unk_A3C.unk_2F);
        contest_competition_0224C47C(&v0->unk_00->unk_14.unk_910, 1);
        contest_competition_0224C864(v0->unk_00, 0);
        contest_competition_0224C9A4(v0->unk_00);

        {
            UnkStruct_contest_competition_0224C0C0 v6;

            v6.unk_04 = v0->unk_18.unk_24.unk_05;

            if (v2 == 0) {
                contest_competition_0224C5A0(v0->unk_00, 4, &v6);
            } else {
                contest_competition_0224C5A0(v0->unk_00, 5, &v6);
            }
        }

        v0->unk_10++;
        break;
    case 1:
        if (contest_competition_0224C6A8(v0->unk_00, &(v0->unk_18.unk_24), v0->unk_18.unk_01) <= 0) {
            contest_competition_0224C640(v0->unk_00);

            v0->unk_00->unk_1084 = v0->unk_00->unk_107C + contest_competition_0224C6A8(v0->unk_00, &(v0->unk_18.unk_24), v0->unk_18.unk_01);

            if (v2 == 0) {
                contest_competition_0224C9F0(v0->unk_00, v2);
                v0->unk_11++;
            }

            contest_competition_0224CDC0(v0->unk_00, v0->unk_18.unk_00, 0);
            v0->unk_10++;
        } else {
            (void)0;
        }
        break;
    case 2: {
        contest_competition_0224A368(&v0->unk_00->unk_14, v0->unk_00->unk_107C - v0->unk_00->unk_1084, v0->unk_18.unk_0C, v0->unk_00->unk_A3C.unk_2F);
        contest_competition_0224C49C(v0->unk_00->unk_14.unk_1FC, v0->unk_00->unk_107C - v0->unk_00->unk_1084, v0->unk_18.unk_0C, v0->unk_00->unk_A3C.unk_2F);
        contest_competition_0224C434(&v0->unk_00->unk_14.unk_910, v0->unk_00->unk_107C - v0->unk_00->unk_1084, v0->unk_18.unk_0C, v0->unk_00->unk_A3C.unk_2F);
    }

        {
            if (v4 >= v0->unk_18.unk_0C) {
                v0->unk_16++;
                v0->unk_00->unk_1084 = v0->unk_00->unk_107C;
                v0->unk_11 = 0;
                v0->unk_12 = 0;

                contest_competition_0224DF54(v0->unk_00);

                v0->unk_17 = 0;

                for (int contestantID = v0->unk_00->unk_00->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
                    contest_competition_0224E958(&v0->unk_58[contestantID]);
                }

                contest_competition_0224A580(&v0->unk_00->unk_14);
                contest_competition_0224BC4C(v0->unk_00);
                contest_competition_0224E990(v0->unk_00, &v0->unk_58[v0->unk_18.unk_00], v0->unk_18.unk_0C, v0->unk_18.unk_08);
                contest_competition_0224C864(v0->unk_00, 0);

                if (v0->unk_16 >= v0->unk_18.unk_24.unk_04) {
                    contest_competition_0224CE08(v0->unk_00);
                    contest_competition_0224B068(&v0->unk_00->unk_14, 2);
                    v0->unk_10++;
                    break;
                } else {
                    contest_competition_0224CDC0(v0->unk_00, v0->unk_18.unk_00, 0);

                    if (v2 == 0) {
                        if (v0->unk_11 == 0) {
                            contest_competition_0224C9F0(v0->unk_00, v2);
                            v0->unk_11++;
                        }
                    }
                }
                break;
            }
        }

        {
            v3 = v0->unk_00->unk_14.unk_A2C;
        }

        {
            UnkStruct_contest_competition_0224EDE0 v8;
            int v9;

            if (v4 < (v0->unk_18.unk_0C >> 1)) {
                v9 = 0;
            } else {
                v9 = 1;
            }

            if (v2 == 0) {
                if ((v9 == 0) && (v0->unk_17 < v0->unk_18.unk_24.unk_05) && (v4 < v0->unk_18.unk_0C / 2 - (v0->unk_18.unk_08 / 2 / 2) / 10000)) {
                    contest_competition_0224DC1C(&v0->unk_50, &v1, 0, 0);
                } else {
                    contest_competition_0224DC1C(&v0->unk_50, &v1, 1, 1);
                }

                if (v1 != 0xffffffff) {
                    contest_competition_0224DE54(v0->unk_00->unk_00->data.playerContestantID, v1, v4, v0->unk_18.unk_08, &v0->unk_18.unk_24.unk_08, &v8, NULL, v3, v0->unk_17, v0->unk_18.unk_24.unk_05, v0->unk_00->unk_A3C.unk_2F);
                    contest_competition_0224D6B0(v0->unk_140[v0->unk_00->unk_00->data.playerContestantID], &v8);
                    v0->unk_17++;
                }
            } else {
                if ((v9 == 1) && (v0->unk_17 < v0->unk_18.unk_24.unk_05) && (v4 < v0->unk_18.unk_0C - (v0->unk_18.unk_08 / 2 / 2) / 10000)) {
                    contest_competition_0224DC1C(&v0->unk_50, &v1, 0, 0);

                    if (v0->unk_11 == 0) {
                        contest_competition_0224C9F0(v0->unk_00, v2);
                        v0->unk_11++;
                    }
                } else {
                    contest_competition_0224DC1C(&v0->unk_50, &v1, 1, 1);
                }

                if (v1 != 0xffffffff) {
                    contest_competition_0224DE54(v0->unk_00->unk_00->data.playerContestantID, v1, v4, v0->unk_18.unk_08, &v0->unk_18.unk_24.unk_08, &v8, v0->unk_00->unk_1AD4, v3, v0->unk_17, v0->unk_18.unk_24.unk_05, v0->unk_00->unk_A3C.unk_2F);
                    contest_competition_0224D6B0(v0->unk_140[v0->unk_00->unk_00->data.playerContestantID], &v8);
                    v0->unk_17++;
                }
            }
        }

        for (int contestantID = v0->unk_00->unk_00->data.connectionCount; contestantID < CONTEST_NUM_PARTICIPANTS; contestantID++) {
            contest_competition_0224ED8C(v5, v0->unk_00, &v0->unk_58[contestantID], v4, v0->unk_18.unk_0C, v0->unk_18.unk_08, &v0->unk_18.unk_24, v0->unk_140[contestantID]);
        }

        if ((v5 == 1) && (v0->unk_12 == 0)) {
            contest_competition_0224CDC0(v0->unk_00, v0->unk_18.unk_00, 1);
            v0->unk_12++;
        }

        if (v5 == 1) {
            contest_competition_0224C8E8(v0->unk_00, v4);
        }

        break;
    case 3:
        if (contest_competition_0224DC1C(&v0->unk_50, &v1, 1, 0) == 1) {
            contest_competition_0224A580(&v0->unk_00->unk_14);
            contest_competition_0224A368(&v0->unk_00->unk_14, 0, v0->unk_18.unk_0C, v0->unk_00->unk_A3C.unk_2F);
            contest_competition_0224C540(v0->unk_00->unk_14.unk_1FC);
            contest_competition_0224C47C(&v0->unk_00->unk_14.unk_910, 0);
            contest_competition_0224B068(&v0->unk_00->unk_14, 2);
            contest_competition_0224C864(v0->unk_00, 0);
            contest_competition_0224C9D4(v0->unk_00);

            if (contest_competition_02249814(v0->unk_00->unk_1074) != 0) {
                contest_competition_0224A0E0(v0->unk_00->unk_1074, 0x0, 6);
            }

            v0->unk_10++;
        }
        break;
    default:
        if (1) {
            contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);

            {
                int v11;

                for (v11 = 0; v11 < 4; v11++) {
                    contest_competition_0224D69C(v0->unk_140[v11]);
                }
            }

            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_0224DC1C(UnkStruct_contest_competition_0224DC1C *param0, int *param1, int param2, int param3)
{
    int v0 = 0;
    *param1 = 0xffffffff;

    if ((param2 == 0) && (param0->unk_05 > 0)) {
        param0->unk_05--;

        if (param0->unk_05 == 0) {
            contest_competition_0224A0E0(param0->unk_00->unk_1074, 0x0, 0);
        }
    }

    switch (param0->unk_04) {
    case 0:
        if ((param2 == 0) && (param3 == 0)) {
            param0->unk_05 = 0;

            contest_competition_0224A0E0(param0->unk_00->unk_1074, 0x0, 0);
            param0->unk_04++;
        } else {
            v0 = 1;
        }
        break;
    case 1:
        if ((param2 == 1) || (param0->unk_05 > 0)) {
            v0 = 1;
            break;
        }

        *param1 = contest_competition_02249760(param0->unk_00->unk_1074);

        if (*param1 != 0xffffffff) {
            param0->unk_05 = param0->unk_00->unk_A3C.unk_18 / 10000;
            param0->unk_05 -= 2;
            param0->unk_04++;
        } else {
            v0 = 1;
        }
        break;
    case 2:
        if (contest_competition_02249804(param0->unk_00->unk_1074) == 1) {
            if (param0->unk_05 > 0) {
                contest_competition_0224A0E0(param0->unk_00->unk_1074, 0x0, 6);
            }

            param0->unk_04 = 1;
        }
        break;
    }

    if ((param3 == 1) && (v0 == 1)) {
        if (contest_competition_02249814(param0->unk_00->unk_1074) != 0) {
            contest_competition_0224A0E0(param0->unk_00->unk_1074, 0x0, 6);
            param0->unk_04 = 0;
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

static void contest_competition_0224DD90(int param0, const UnkStruct_contest_competition_0224DD90 *param1, u8 *param2, u8 *param3)
{
    if (param0 <= param1->unk_00) {
        *param2 = 0;
        *param3 = 0;
    } else if (param0 <= param1->unk_01) {
        *param2 = 0;
        *param3 = 1;
    } else if (param0 <= param1->unk_02) {
        *param2 = 1;
        *param3 = 2;
    } else if (param0 <= param1->unk_03) {
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

void contest_competition_0224DE54(int param0, int param1, u32 param2, u32 param3, const UnkStruct_contest_competition_0224DD90 *param4, UnkStruct_contest_competition_0224EDE0 *param5, const UnkStruct_contest_competition_0224EDE0 *param6, int param7, int param8, int param9, int param10)
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
            if ((param6[v7].unk_08_2 == 1) && (param6[v7].unk_06 == v6)) {
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
            if (param6[v7].unk_03 != v0) {
                v4 = 0xff;
                v3 = 4;
                v2 = 2;
                v8 = 1;
            }
            break;
        }
    }

    param5->unk_02 = param0;
    param5->unk_00 = param2;
    param5->unk_03 = v0;
    param5->unk_04 = v2;
    param5->unk_05 = v3;
    param5->unk_06 = v5;
    param5->unk_07 = param7;
    param5->unk_08_0 = (param8 >= param9 - 1) ? 1 : 0;
    param5->unk_08_1 = v8;
    param5->unk_08_2 = 1;
}

static void contest_competition_0224DF54(UnkStruct_contest_competition_0224DF54 *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        param0->unk_14.unk_A1D[v0] = 0;
        param0->unk_14.unk_A21[v0] = 0;
    }

    param0->unk_14.unk_A25 = 0;
    param0->unk_14.unk_A26 = 0;
    param0->unk_14.unk_A27 = 0;
}

static void contest_competition_0224DF84(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    return;
}

static int contest_competition_0224DF88(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224DF9C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224DF54_sub2 *v1 = param3;
    UnkStruct_contest_competition_0224DFF8 *v2 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224DFF8));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_0224DFF8));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;
    v2->unk_C8 = *v1;

    SysTask_Start(contest_competition_0224DFF8, v2, 30000);
}

static void contest_competition_0224DFF8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224DFF8 *v0 = param1;
    int v1, v2;

    switch (v0->unk_10) {
    case 0:
        contest_competition_0224CDB4(v0->unk_00, 0);
        PaletteData_StartFade(v0->unk_00->unk_14.unk_90, 0x1, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), -2, 0, 6, 0x0);

        for (v2 = 0; v2 < 4; v2++) {
            contest_competition_0224CEE4(v0->unk_00, v2, 0x7fff, 0x254a, 16, 4, &v0->unk_11[v2]);
        }

        v0->unk_10++;
        break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(v0->unk_00->unk_14.unk_90) == 0) {
            for (v2 = 0; v2 < 4; v2++) {
                if (v0->unk_11[v2] == 0) {
                    break;
                }
            }

            if (v2 == 4) {
                v0->unk_10++;
            }
        }
        break;
    case 2:
        for (v2 = 0; v2 < CONTEST_NUM_PARTICIPANTS; v2++) {
            v1 = v0->unk_C8.unk_02[v2];
            v0->unk_18[v1].mon = v0->unk_00->unk_14.unk_00->contestMons[v1];
            v0->unk_18[v1].unk_04 = v0->unk_00->unk_14.unk_48[v1];
            v0->unk_18[v1].unk_08 = &v0->unk_00->unk_14.unk_04[v1];
            v0->unk_18[v1].unk_0E = (v0->unk_00->unk_A3C.unk_24 / 10000) * 40 / 100;
            v0->unk_18[v1].contestantID = v2;

            if (v2 == 0) {
                v0->unk_18[v1].unk_0D = 3;
            } else {
                v0->unk_18[v1].unk_0D = v2 - 1;
            }

            SysTask_Start(contest_competition_0224E1F4, &v0->unk_18[v1], ((30000 + 10000) + 100));
        }

        {
            UnkStruct_contest_competition_0224C0C0 v3;

            v3.unk_04 = v0->unk_C8.unk_24.unk_05;

            if (v0->unk_C8.unk_02[1] == v0->unk_00->unk_00->data.playerContestantID) {
                contest_competition_0224C5A0(v0->unk_00, 4, &v3);
            } else {
                contest_competition_0224C5A0(v0->unk_00, 5, &v3);
            }
        }

        Sound_PlayEffect(SEQ_SE_DP_CON_030_sseq);
        v0->unk_10++;
        break;
    case 3:
        for (v2 = 0; v2 < 4; v2++) {
            if (v0->unk_18[v2].unk_2B == 0) {
                break;
            }
        }

        if (v2 == 4) {
            v0->unk_10++;
        }
        break;
    case 4:
        PaletteData_StartFade(v0->unk_00->unk_14.unk_90, 0x1, (0x1fff ^ ((1 << 4) | (1 << 3) | (1 << 2))), -2, 6, 0, 0x0);
        v0->unk_10++;
        break;
    case 5:
        if (PaletteData_GetSelectedBuffersMask(v0->unk_00->unk_14.unk_90) == 0) {
            contest_competition_0224CDB4(v0->unk_00, 1);
            v0->unk_10++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static void contest_competition_0224E1F4(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224E1F4 *v0 = param1;
    int v1, v2, v3, v4, v5, v6;
    int v7;

    switch (v0->unk_2A) {
    case 0:
        v0->unk_10 = v0->unk_08->unk_04 * 0x100;
        v0->unk_14 = v0->unk_08->unk_08 * 0x100;
        v0->unk_18 = v0->unk_08->unk_0C * 0x100;

        {
            v1 = contest_competition_0224A0FC(v0->contestantID) * 0x100;
            v2 = contest_competition_0224A10C(v0->contestantID) * 0x100;
            v3 = contest_competition_0224A120(v0->contestantID) * 0x100;

            if ((v0->unk_0D == 0) || (v0->unk_0D == 4 - 1)) {
                if (v0->unk_0D == 0) {
                    v4 = (0 - 80) * 0x100;
                } else {
                    v4 = (256 + 100) * 0x100;
                }

                v5 = v2;
                v6 = v3;
                v0->unk_1C = (v4 - v1) / (v0->unk_0E / 2);
                v0->unk_20 = (v5 - v2) / (v0->unk_0E / 2);
                v0->unk_24 = (v6 - v3) / (v0->unk_0E / 2);
            } else {
                v4 = contest_competition_0224A0FC(v0->unk_0D) * 0x100;
                v5 = contest_competition_0224A10C(v0->unk_0D) * 0x100;
                v6 = contest_competition_0224A120(v0->unk_0D) * 0x100;
                v0->unk_1C = (v4 - v1) / v0->unk_0E;
                v0->unk_20 = (v5 - v2) / v0->unk_0E;
                v0->unk_24 = (v6 - v3) / v0->unk_0E;
            }
        }

        v0->unk_2A++;
        break;
    case 1:
        v0->unk_10 += v0->unk_1C;
        v0->unk_14 += v0->unk_20;
        v0->unk_18 += v0->unk_24;
        v0->unk_28++;

        if ((v0->unk_0D == 0) || (v0->unk_0D == 4 - 1)) {
            if (v0->unk_28 == (v0->unk_0E / 2)) {
                int v8;

                if (v0->unk_0D == 0) {
                    v0->unk_10 = (0 - 100) * 0x100;
                    PhotoSprite_SetVisible(v0->unk_08->unk_00, 1);
                    PhotoSprite_AdjustPriority(v0->unk_08->unk_00, 100);
                } else {
                    v0->unk_10 = (contest_competition_0224A0FC(v0->unk_0D) + 80) * 0x100;
                    PhotoSprite_SetVisible(v0->unk_08->unk_00, 0);
                    PhotoSprite_AdjustPriority(v0->unk_08->unk_00, -100);
                }

                v7 = Pokemon_DPSpriteYOffset(v0->mon, 2);

                v0->unk_14 = (contest_competition_0224A10C(v0->unk_0D) + v7) * 0x100;
                v0->unk_18 = contest_competition_0224A120(v0->unk_0D) * 0x100;

                v4 = contest_competition_0224A0FC(v0->unk_0D) * 0x100;
                v5 = v0->unk_14;
                v6 = v0->unk_18;
                v8 = v0->unk_0E - v0->unk_28 - 1;

                v0->unk_1C = (v4 - v0->unk_10) / v8;
                v0->unk_20 = (v5 - v0->unk_14) / v8;
                v0->unk_24 = (v6 - v0->unk_18) / v8;
            }
        } else if (v0->unk_10 < contest_competition_0224A0FC(v0->unk_0D) * 0x100) {
            v0->unk_10 = contest_competition_0224A0FC(v0->unk_0D) * 0x100;
        }

        if (v0->unk_28 >= v0->unk_0E) {
            v7 = Pokemon_DPSpriteYOffset(v0->mon, 2);
            v0->unk_10 = contest_competition_0224A0FC(v0->unk_0D) * 0x100;
            v0->unk_14 = (contest_competition_0224A10C(v0->unk_0D) + v7) * 0x100;
            v0->unk_18 = contest_competition_0224A120(v0->unk_0D) * 0x100;
            v0->unk_2A++;
        }

        v0->unk_08->unk_04 = v0->unk_10 / 0x100;
        v0->unk_08->unk_08 = v0->unk_14 / 0x100;
        v0->unk_08->unk_0C = v0->unk_18 / 0x100;

        PhotoSprite_MoveTo(v0->unk_08->unk_00, v0->unk_08->unk_04, v0->unk_08->unk_08);
        contest_competition_0224B09C(v0->unk_04, v0->unk_08);
        break;
    default:
        v0->unk_2B = 1;
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224E43C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224E450(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224E4A8 *v1;
    UnkStruct_contest_competition_0224DF54_sub2 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224E4A8));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_0224E4A8));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0C = param0;
    v1->unk_10 = *v2;

    SysTask_Start(contest_competition_0224E4A8, v1, 30000);
}

static void contest_competition_0224E4A8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224E4A8 *v0 = param1;
    int v1;

    switch (v0->unk_45) {
    case 0:
        for (v1 = 0; v1 < 4; v1++) {
            contest_competition_0224BC68(v0->unk_00, v0->unk_10.unk_02[v1], v1);
        }

        contest_competition_02249640(v0->unk_00->unk_1074, 1, 1, NULL);
        contest_competition_0224A0E0(v0->unk_00->unk_1074, 0x0, 6);

        v0->unk_45++;
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);

        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224E518(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224E52C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224E584 *v1;
    UnkStruct_contest_competition_0224DF54_sub2 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224E584));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_0224E584));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0C = param0;
    v1->unk_10 = *v2;

    SysTask_Start(contest_competition_0224E584, v1, 30000);
}

static void contest_competition_0224E584(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224E584 *v0 = param1;
    int v1;

    switch (v0->unk_45) {
    case 0:
        if (contest_competition_0224B5C8(v0->unk_00) == 0) {
            break;
        }

        for (v1 = 0; v1 < 4; v1++) {
            contest_competition_0224BD28(v0->unk_00, v1, 2);
            contest_competition_0224BD28(v0->unk_00, v1, 5);
        }

        v0->unk_45++;
        break;
    case 1: {
        int v2 = 0, v3 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if (contest_competition_0224BDF0(v0->unk_00, v1) == 1) {
                v2++;
            }

            if (contest_competition_0224BE24(v0->unk_00, v1) == 1) {
                v3++;
            }
        }

        if (v2 >= 4) {
            contest_competition_0224BD00(v0->unk_00);
            v0->unk_45++;
        }
    } break;
    default:
        contest_competition_02249640(v0->unk_00->unk_1074, 0, 1, NULL);
        contest_competition_0224A0E0(v0->unk_00->unk_1074, 0x0, 0);
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static int contest_competition_0224E648(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224E65C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224DF54_sub2 *v1 = param3;
    UnkStruct_contest_competition_0224E6C8 *v2 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224E6C8));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_0224E6C8));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;
    v2->unk_11 = v1->unk_00;
    v2->unk_14 = v1->unk_30;
    v2->unk_1A = v1->unk_36;
    v2->unk_1C = v1->unk_38;
    v2->unk_1B = v1->unk_37;

    SysTask_Start(contest_competition_0224E6C8, v2, 30000);
}

static void contest_competition_0224E6C8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224E6C8 *v0 = param1;

    switch (v0->unk_10) {
    case 0:
        if (v0->unk_1A != 0) {
            Window_DrawMessageBoxWithScrollCursor(&v0->unk_00->unk_14.unk_64[0], 1, 1, 14);
            Bg_ScheduleTilemapTransfer(v0->unk_00->unk_14.unk_60, 1);

            contest_competition_0224C2CC(v0->unk_00, v0->unk_1A, &v0->unk_14);
            v0->unk_10++;
        } else {
            v0->unk_10 = 100;
        }
        break;
    case 1:
        if (contest_competition_0224C300(v0->unk_00) == 0) {
            v0->unk_10++;
        }
        break;
    case 2:
        v0->unk_12++;

        if (v0->unk_1C == 1) {
            v0->unk_10++;
        } else if (v0->unk_12 >= v0->unk_1B) {
            Window_EraseMessageBox(&v0->unk_00->unk_14.unk_64[0], 1);
            Bg_ScheduleTilemapTransfer(v0->unk_00->unk_14.unk_60, 1);
            v0->unk_10++;
        }
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static int contest_competition_0224E77C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub1));
    return v1;
}

static void contest_competition_0224E790(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;

    v0->unk_A3C = *((UnkStruct_contest_competition_0224DF54_sub1 *)param3);
    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_0224E7B4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224E7C8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224DF54_sub2 *v1 = param3;

    Sound_StopWaveOutAndSequences();
    Sound_PlayBGM(v1->unk_24.unk_00);

    v0->unk_1078 = 1;
    v0->unk_1084 = v0->unk_107C;

    contest_competition_0224F26C(param0, param2, NULL, 0);
}

static int contest_competition_0224E800(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_0224DF54_sub2));
    return v1;
}

static void contest_competition_0224E814(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_0224DF54 *v0 = param1;
    UnkStruct_contest_competition_0224DF54_sub2 *v1 = param3;
    UnkStruct_contest_competition_0224E86C *v2 = Heap_Alloc(HEAP_ID_23, sizeof(UnkStruct_contest_competition_0224E86C));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_0224E86C));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;
    v2->unk_10 = *v1;

    SysTask_Start(contest_competition_0224E86C, v2, 30000);
}

static void contest_competition_0224E86C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_0224E86C *v0 = param1;

    switch (v0->unk_4C) {
    case 0:
        v0->unk_00->unk_1078 = 0;
        v0->unk_4C++;
        break;
    case 1:
        if (Sound_IsSequencePlaying(v0->unk_10.unk_24.unk_00) == FALSE) {
            v0->unk_4C++;
        }
        break;
    case 2:
        contest_competition_0224CE28(v0->unk_00);
        v0->unk_4C++;
        break;
    case 3:
        v0->unk_48++;

        if (v0->unk_48 > 60) {
            v0->unk_48 = 0;
            v0->unk_4C++;
        }
        break;
    case 4:
        Sound_PlayBGM(CONTEST_DRESSING_ROOM_sseq);
        Sound_PlayEffect(SEQ_SE_DP_CON_007_sseq);
        v0->unk_4C++;
        break;
    default:
        contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}
