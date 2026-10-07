#include "contest_competition/contest_competition_02243C28.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/move_animation.h"

#include "battle/battle_anim_battler_context.h"
#include "battle_anim/battle_anim_system.h"
#include "contest_competition/contest_competition_0223F7E4.h"
#include "contest_competition/contest_competition_022413D8.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_contest_competition_02243C28.h"
#include "contest_competition/struct_contest_competition_02243C80.h"
#include "contest_competition/struct_contest_competition_02243D34.h"
#include "contest_competition/struct_contest_competition_02243DCC.h"
#include "contest_competition/struct_contest_competition_02243F10.h"
#include "contest_competition/struct_contest_competition_02244240.h"
#include "contest_competition/struct_contest_competition_022443F8.h"
#include "contest_competition/struct_contest_competition_022444BC.h"
#include "contest_competition/struct_contest_competition_02244970.h"
#include "contest_competition/struct_contest_competition_022449B8.h"
#include "contest_competition/struct_contest_competition_02244BB0.h"
#include "contest_competition/struct_contest_competition_02244C08.h"
#include "contest_competition/struct_contest_competition_02245690.h"
#include "contest_competition/struct_contest_competition_02245C60.h"
#include "contest_competition/struct_contest_competition_02245E14.h"
#include "contest_competition/struct_contest_competition_02246F24.h"
#include "contest_competition/struct_contest_competition_02246F24_sub1.h"
#include "contest_competition/struct_contest_competition_022472F8.h"
#include "contest_competition/struct_contest_competition_0224F30C.h"
#include "contest_competition/struct_contest_competition_0224F3D8.h"
#include "contest_competition/struct_contest_competition_022539E4.h"

#include "heap.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "contest_util.h"

static int contest_competition_02243C68(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02243C80(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02243C94(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4);
static int contest_competition_02243CDC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02243CF4(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02243D34(SysTask *param0, void *param1);
static int contest_competition_02243EF8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02243F10(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02243F68(SysTask *param0, void *param1);
static int contest_competition_022440C8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_022440E0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224413C(SysTask *param0, void *param1);
static int contest_competition_02244228(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244240(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_022442AC(SysTask *param0, void *param1);
static int contest_competition_022443E0(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_022443F8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_022444BC(SysTask *param0, void *param1);
static int contest_competition_02244958(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244970(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02244BB0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int contestantID);
static void contest_competition_022449B8(SysTask *param0, void *param1);
static int contest_competition_02244BD4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244BEC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_02244BF0(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244C08(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02244C68(SysTask *param0, void *param1);
static int contest_competition_02243C98(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02243CB0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_02245DA4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245DBC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static int contest_competition_02244D20(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244D38(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02244D98(SysTask *param0, void *param1);
static int contest_competition_02244FBC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02244FD4(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02245034(SysTask *param0, void *param1);
static int contest_competition_02245124(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_0224513C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_0224519C(SysTask *param0, void *param1);
static int contest_competition_02245510(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245528(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02245588(SysTask *param0, void *param1);
static int contest_competition_02245678(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245690(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_022456E8(SysTask *param0, void *param1);
static int contest_competition_02245B48(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245B60(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02245BC8(SysTask *param0, void *param1);
static int contest_competition_02245E00(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245E14(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02245E8C(SysTask *param0, void *param1);
static int contest_competition_02245C4C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245C60(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02245CA4(SysTask *param0, void *param1);
static int contest_competition_0224595C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02245974(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_022459D4(SysTask *param0, void *param1);
static int contest_competition_02243DB4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3);
static void contest_competition_02243DCC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3);
static void contest_competition_02243E2C(SysTask *param0, void *param1);

static const UnkStruct_contest_competition_022539E4 Unk_contest_competition_022539E4[] = {
    { contest_competition_02243C68, contest_competition_02243C80, contest_competition_02243C94 },
    { contest_competition_02243C98, contest_competition_02243CB0, NULL },
    { contest_competition_02243CDC, contest_competition_02243CF4, NULL },
    { contest_competition_02243DB4, contest_competition_02243DCC, NULL },
    { contest_competition_02243EF8, contest_competition_02243F10, NULL },
    { contest_competition_022440C8, contest_competition_022440E0, NULL },
    { contest_competition_02244228, contest_competition_02244240, NULL },
    { contest_competition_022443E0, contest_competition_022443F8, NULL },
    { contest_competition_02244958, contest_competition_02244970, contest_competition_02244BB0 },
    { contest_competition_02244BD4, contest_competition_02244BEC, NULL },
    { contest_competition_02244BF0, contest_competition_02244C08, NULL },
    { contest_competition_02244D20, contest_competition_02244D38, NULL },
    { contest_competition_02244FBC, contest_competition_02244FD4, NULL },
    { contest_competition_02245124, contest_competition_0224513C, NULL },
    { contest_competition_02245510, contest_competition_02245528, NULL },
    { contest_competition_02245510, contest_competition_02245528, NULL },
    { contest_competition_02245678, contest_competition_02245690, NULL },
    { contest_competition_0224595C, contest_competition_02245974, NULL },
    { contest_competition_02245B48, contest_competition_02245B60, NULL },
    { contest_competition_02245DA4, contest_competition_02245DBC, NULL },
    { contest_competition_02245E00, contest_competition_02245E14, NULL },
    { contest_competition_02245C4C, contest_competition_02245C60, NULL }
};

void contest_competition_02243C28(UnkStruct_contest_competition_02246F24 *param0)
{
    UnkStruct_contest_competition_02243C28 v0;

    v0.unk_00 = Unk_contest_competition_022539E4;
    v0.unk_04 = NELEMS(Unk_contest_competition_022539E4);
    v0.playerContestantID = param0->unk_00->data.playerContestantID;
    v0.unk_08 = param0->unk_00->data.leaderContestantID;
    v0.isLinkContest = param0->unk_00->isLinkContest;

    contest_competition_0224F18C(&param0->unk_BF8, &v0);
}

static int contest_competition_02243C68(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243C80(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    contest_competition_0224F26C(&v0->unk_BF8, param2, NULL, 0);
}

static void contest_competition_02243C94(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int param4)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    return;
}

static int contest_competition_02243C98(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243CB0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;

    v0->unk_1614 = 1;

    if (Contest_IsPlayerLeader(v0->unk_00) == FALSE) {
        contest_competition_0224F26C(&v0->unk_BF8, param2, NULL, 0);
    }
}

static int contest_competition_02243CDC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243CF4(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02243D34 *v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02243D34));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02243D34));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;

    SysTask_Start(contest_competition_02243D34, v1, 30000);
}

static void contest_competition_02243D34(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02243D34 *v0 = param1;

    switch (v0->unk_0F) {
    case 0:
        contest_competition_022431A0(v0->unk_00, 0, 0, 70, 0, &v0->unk_0E);
        v0->unk_0F++;
        break;
    case 1:
        v0->unk_0C++;

        if (v0->unk_0C > 30) {
            v0->unk_0C = 0;
            v0->unk_0F++;
        }
        break;
    case 2:
        if (v0->unk_0E == 1) {
            v0->unk_0F++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02243DB4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02243DCC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02246F24_sub1 *v1 = param3;
    UnkStruct_contest_competition_02243DCC *v2 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02243DCC));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_02243DCC));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->actingMessagesID = v1->unk_C6.actingMessagesID;
    v2->unk_12 = v1->unk_C6.unk_00;

    SysTask_Start(contest_competition_02243E2C, v2, 30000);
}

static void contest_competition_02243E2C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02243DCC *v0 = param1;

    switch (v0->unk_0C) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->actingMessagesID, &v0->unk_12, NULL);
        }

        Sound_PlayEffect(SEQ_SE_DP_CON_032_sseq);
        v0->unk_0C++;
        break;
    case 1:
        if (v0->actingMessagesID == ACTING_COMPETITION_MESSAGE_NONE || (contest_competition_02242ECC(v0->unk_00) == 0)) {
            v0->unk_0C++;
        }
        break;
    case 2:
        v0->unk_0E++;

        if (v0->unk_0E > 30) {
            v0->unk_0E = 0;
            v0->unk_0C++;
        }
        break;
    case 3:
        contest_competition_022431A0(v0->unk_00, 0, 0, 70, 0, &v0->unk_10);
        v0->unk_0C++;
        break;
    case 4:
        if (v0->unk_10 == 1) {
            v0->unk_0C++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02243EF8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02243F10(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;
    UnkStruct_contest_competition_02243F10 *v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02243F10));

    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02243F10));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;

    contest_competition_022426E8(v0, 0, &v1->unk_16);
    SysTask_Start(contest_competition_02243F68, v1, 30000);
    contest_competition_02242DA8(v0);
}

static void contest_competition_02243F68(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02243F10 *v0 = param1;
    int contestantID = v0->contestantID;
    int v2 = Pokemon_SpriteYOffset(v0->unk_00->unk_0C.unk_00->contestMons[contestantID], 0);

    switch (v0->unk_14) {
    case 0:
        v0->unk_18++;

        if (v0->unk_18 > 10) {
            v0->unk_18 = 0;
            v0->unk_14++;
        }
        break;
    case 1: {
        int v3, v4;

        v3 = v0->contestantID;
        v4 = Pokemon_SpriteYOffset(v0->unk_00->unk_0C.unk_00->contestMons[v3], 0);

        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v3], MON_SPRITE_HIDE_2, 0);
        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v3], MON_SPRITE_HIDE, 0);
        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v3], MON_SPRITE_X_CENTER, (256 - 40) + 40);
        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v3], MON_SPRITE_Y_CENTER, ((104 + 8) + 60) + v4);

        v0->unk_0C = ((256 - 40) + 40) << 8;
        v0->unk_10 = ((104 + 8) + 60) << 8;
    }
        v0->unk_14++;
        break;

    case 2:
        if (v0->contestantID == v0->unk_00->unk_00->data.playerContestantID) {
            Sound_PlayEffect(SEQ_SE_DP_CON_031_sseq);
        }

        v0->unk_14++;

    case 3:
        v0->unk_0C -= (((((256 - 40) + 40) - (256 - 40)) << 8) / 7);
        v0->unk_10 -= (((((104 + 8) + 60) - (104 + 8)) << 8) / 7);

        if (((v0->unk_0C >> 8) <= (256 - 40)) || ((v0->unk_10 >> 8) <= (104 + 8))) {
            v0->unk_0C = (256 - 40) << 8;
            v0->unk_10 = (104 + 8) << 8;
            v0->unk_14++;
        }

        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_X_CENTER, v0->unk_0C >> 8);
        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_Y_CENTER, (v0->unk_10 >> 8) + v2);
        break;
    default:
        if (v0->unk_16 == 1) {
            contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_022440C8(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_022440E0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02243F10 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2;
    int v3;

    v2 = param3;
    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02243F10));

    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02243F10));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;

    int contestantID = v1->contestantID;
    v3 = Pokemon_SpriteYOffset(v0->unk_0C.unk_00->contestMons[contestantID], 0);

    v1->unk_0C = (256 - 40) << 8;
    v1->unk_10 = (104 + 8) << 8;

    SysTask_Start(contest_competition_0224413C, v1, 30000);
}

static void contest_competition_0224413C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02243F10 *v0 = param1;
    int contestantID = v0->contestantID;
    int v2 = Pokemon_SpriteYOffset(v0->unk_00->unk_0C.unk_00->contestMons[contestantID], 0);

    switch (v0->unk_14) {
    case 0:
        v0->unk_0C += (((((256 - 40) + 40) - (256 - 40)) << 8) / 7);
        v0->unk_10 += (((((104 + 8) + 60) - (104 + 8)) << 8) / 7);

        if (((v0->unk_0C >> 8) >= ((256 - 40) + 40)) || ((v0->unk_10 >> 8) >= ((104 + 8) + 60))) {
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[contestantID], MON_SPRITE_HIDE_2, 1);
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[contestantID], MON_SPRITE_HIDE, 1);
            v0->unk_14++;
        }

        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_X_CENTER, v0->unk_0C >> 8);
        PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_Y_CENTER, (v0->unk_10 >> 8) + v2);
        break;
    case 1:
        if (v0->unk_00->unk_1616[v0->contestantID] == 1) {
            contest_competition_02241524(&v0->unk_00->unk_0C, v0->contestantID);
            v0->unk_00->unk_1616[v0->contestantID] = 0;
        }

        v0->unk_14++;
        break;
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244228(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02244240(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244240 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244240));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244240));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_02;
    v1->actingMessagesID = v2->unk_C6.actingMessagesID;
    v1->unk_14 = v2->unk_C6.unk_00;
    v1->unk_10 = v2->unk_03;

    SysTask_Start(contest_competition_022442AC, v1, 30000);
}

static void contest_competition_022442AC(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244240 *v0 = param1;
    int v1;

    switch (v0->unk_0C) {
    case 0: {
        int v2;

        v2 = contest_competition_02243174(v0->unk_00->unk_220.unk_12[v0->contestantID]);

        if (v2 > 0) {
            contest_competition_022431A0(v0->unk_00, 0, 0, v2, 0, &v0->unk_12);
        } else {
            v0->unk_0C = 2;
            break;
        }
    }
        v0->unk_0C++;
        break;
    case 1:
        if (v0->unk_12 == 1) {
            v0->unk_0C++;
        }
        break;
    case 2:
        v0->unk_0C++;
        break;
    case 3:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->actingMessagesID, &v0->unk_14, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 5;
        }
        break;
    case 4:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 5:
        v0->unk_0C++;
        break;
    case 6:
        contest_competition_02241A8C(&v0->unk_00->unk_0C, v0->unk_0E, v0->unk_10);
        contest_competition_02241B3C(v0->unk_00, v0->unk_0E, v0->unk_10, &v0->unk_0F);
        v0->unk_0C++;
        break;
    case 7:
        if (v0->unk_0F == 1) {
            v0->unk_0C++;
        }
        break;
    case 8:
        v0->unk_11++;

        if (v0->unk_11 > 5) {
            contest_competition_02241B1C(&v0->unk_00->unk_0C);
            v0->unk_0C++;
        }
        break;

    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022443E0(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_022443F8(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_022443F8 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_022443F8));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_022443F8));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->moveID = v2->unk_10.unk_00[v2->contestantID].moveID;
    v1->actingMessagesID = v2->unk_C6.actingMessagesID;
    v1->unk_F2 = v2->unk_C6.unk_00;
    v1->actingMessagesID2 = v2->unk_C6.actingMessagesID2;
    v1->unk_FA = v2->unk_C6.unk_06;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_022444BC, v1, 5);
}

static void contest_competition_022444BC(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_022443F8 *v0 = param1;
    int v1;
    UnkStruct_contest_competition_022444BC *v2 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->state) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->actingMessagesID, &v0->unk_F2, NULL);
            v0->state++;
        } else {
            v0->state = 2;
        }
        break;
    case 1:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->state++;
        break;
    case 3:
        if (v2->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v2->unk_12, v2->unk_13, &v2->unk_0C, NULL);
            v0->state++;
        } else {
            v0->state = 5;
        }
        break;
    case 4:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->state++;
        }
        break;
    case 5:
        v0->state++;
        break;
    case 6:
        if (v0->actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->actingMessagesID2, &v0->unk_F2, NULL);
            v0->state++;
        } else {
            v0->state = 8;
        }
        break;
    case 7:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->state++;
        }
        break;
    case 8:
        v0->state++;
        break;
    case 9:
        contest_competition_022439C8(v0->unk_00->unk_00, v0->contestantID, v0->moveID, &v0->unk_104);
        v0->state++;
    case 10: {
        MoveAnimation moveAnim;
        BattleAnimBattlerContext battlerContext;
        int v5;
        int isShiny, monForm;
        int v10, v11, v12, v13;
        u32 personality, v15;

        int v16 = v0->contestantID + 1;
        if (v16 >= 4) {
            v16 = 0;
        }

        MI_CpuClear8(&moveAnim, sizeof(MoveAnimation));
        MI_CpuClear8(&battlerContext, sizeof(BattleAnimBattlerContext));

        int species = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID], MON_DATA_SPECIES, NULL);
        int gender = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID], MON_DATA_GENDER, NULL);
        isShiny = Pokemon_IsShiny(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID]);
        monForm = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID], MON_DATA_FORM, NULL);
        personality = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID], MON_DATA_PERSONALITY, NULL);

        v10 = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v16], MON_DATA_SPECIES, NULL);
        v11 = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v16], MON_DATA_GENDER, NULL);
        v12 = Pokemon_IsShiny(v0->unk_00->unk_0C.unk_00->contestMons[v16]);
        v13 = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v16], MON_DATA_FORM, NULL);
        v15 = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v16], MON_DATA_PERSONALITY, NULL);

        moveAnim.command = 0;
        moveAnim.unk_01 = 0;
        moveAnim.move = v0->unk_104.actingAnimationMoveID;
        moveAnim.damage = 1;
        moveAnim.power = 10;
        moveAnim.effectChance = v0->unk_104.unk_07;
        moveAnim.friendship = v0->unk_104.friendship;
        moveAnim.fieldConditions = 0;
        moveAnim.attacker = 0;
        moveAnim.defender = 1;
        moveAnim.terrain = 9;

        for (v5 = 0; v5 < 4; v5++) {
            moveAnim.species[v5] = species;
        }

        moveAnim.species[1] = v10;

        battlerContext.bgConfig = v0->unk_00->unk_0C.unk_24;
        battlerContext.paletteData = v0->unk_00->unk_0C.unk_50;
        battlerContext.pokemonSpriteData[0] = &v0->unk_00->unk_0C.pokemonSpriteDataArray[v0->contestantID];
        battlerContext.pokemonSpriteData[1] = &v0->unk_00->unk_0C.pokemonSpriteData;

        for (v5 = 0; v5 < 4; v5++) {
            battlerContext.battlerTypes[v5] = 0xff;
            battlerContext.battlerSpecies[v5] = species;
            battlerContext.battlerGenders[v5] = gender;
            battlerContext.battlerShinyFlags[v5] = isShiny;
            battlerContext.battlerForms[v5] = monForm;
            battlerContext.battlerPersonalities[v5] = personality;
            battlerContext.battlerMoveEffects[v5] = 0;
        }

        battlerContext.battlerMoveEffects[0] = v0->unk_104.unk_00;
        battlerContext.battlerTypes[0] = 0;
        battlerContext.battlerTypes[1] = 1;
        battlerContext.battlerSpecies[1] = v10;
        battlerContext.battlerGenders[1] = v11;
        battlerContext.battlerShinyFlags[1] = v12;
        battlerContext.battlerForms[1] = v13;
        battlerContext.battlerPersonalities[1] = v15;
        battlerContext.pokemonSprites[0] = v0->unk_00->unk_0C.unk_08[v0->contestantID];

        v1 = (v0->contestantID == 0) ? 1 : 0;

        battlerContext.pokemonSprites[1] = v0->unk_00->unk_0C.unk_08[v1];
        battlerContext.battleType = 0;
        battlerContext.moveArcID = 8;
        battlerContext.battleBgRef.narcID = 45;
        battlerContext.battleBgRef.tilesNarcMemberIdx = 1;
        battlerContext.battleBgRef.paletteNarcMemberIdx = 30;
        battlerContext.battleBgRef.tilemapNarcMemberIdx = 2;
        battlerContext.battleBgRef.paletteDestStart = 0;
        battlerContext.battleBgRef.paletteSrcSize = 3;
        battlerContext.spriteSystem = v0->unk_00->unk_0C.unk_18;
        battlerContext.chatotCry = v0->unk_00->unk_00->chatotCry[v0->contestantID];

        BattleAnimSystem_StartMove(v0->unk_00->unk_0C.unk_20, &moveAnim, v0->unk_104.actingAnimationMoveID, &battlerContext);
    }

        {
            int v17 = Pokemon_SpriteYOffset(v0->unk_00->unk_0C.unk_00->contestMons[v0->contestantID], 0);

            if (v0->unk_104.unk_00 != ((0x40 ^ 0xffffffff) & (0x80 ^ 0xffffffff) & (0x40000 ^ 0xffffffff) & (0x20000000 ^ 0xffffffff))) {
                PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_HIDE, 0);
            }

            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_HIDE_2, 0);
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_X_CENTER, 256 - 40);
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v0->contestantID], MON_SPRITE_Y_CENTER, (104 + 8) + v17);

            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v1], MON_SPRITE_HIDE_2, 1);
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v1], MON_SPRITE_X_CENTER, 80);
            PokemonSprite_SetAttribute(v0->unk_00->unk_0C.unk_08[v1], MON_SPRITE_Y_CENTER, 50 - 8);
        }

        v0->state++;
        break;
    case 11:
        BattleAnimSystem_ExecuteScript(v0->unk_00->unk_0C.unk_20);

        if (BattleAnimSystem_IsMoveActive(v0->unk_00->unk_0C.unk_20) == 0) {
            BattleAnimSystem_FreeScriptData(v0->unk_00->unk_0C.unk_20);

            if (v0->unk_104.unk_06 > 0) {
                v0->unk_104.unk_06--;
                v0->unk_104.unk_07++;

                if (v0->unk_104.unk_00 == (0x40 | 0x80 | 0x40000 | 0x20000000)) {
                    v0->unk_104.unk_00 = ((0x40 ^ 0xffffffff) & (0x80 ^ 0xffffffff) & (0x40000 ^ 0xffffffff) & (0x20000000 ^ 0xffffffff));
                }

                v0->state = 10;
            } else {
                v0->state++;
            }
        }
        break;
    case 12:
        switch (v0->unk_104.actingAnimationMoveID) {
        case MOVE_TRANSFORM:
        case MOVE_SUBSTITUTE:
            v0->unk_00->unk_1616[v0->contestantID] = 1;
            break;
        }

        v0->state++;
        break;
    case 13:
        contest_competition_022426E8(v0->unk_00, 1, &v0->unk_10);
        v0->state++;
        break;
    case 14:
        if (v0->unk_10 == 1) {
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244958(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02244970(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244970 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244970));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244970));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_0D = v0->unk_0C.unk_00->playerContestantID;

    SysTask_Start(contest_competition_022449B8, v1, 100);
}

static void contest_competition_022449B8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244970 *v0 = param1;
    int v1;

    switch (v0->unk_0C) {
    case 0:
        contest_competition_0223F9C4(v0->unk_00->unk_7E4, 1, 0, NULL);
        v0->unk_0C++;
        break;
    case 1:
        contest_competition_0223F9C4(v0->unk_00->unk_7E4, 2, 0, NULL);

        {
            u32 actingCompetitionMessageID;
            UnkStruct_contest_competition_022449B8 v3;

            if (v0->unk_00->unk_220.unk_00 + 1 == 4) {
                actingCompetitionMessageID = ACTING_COMPETITION_MESSAGE_LAST_PERFORMANCE_CHOOSE_MOVE;
            } else {
                actingCompetitionMessageID = ACTING_COMPETITION_MESSAGE_WHICH_MOVE_IS_YOUR_CHOICE;
            }

            v3.unk_04 = v0->unk_00->unk_220.unk_00 + 1;
            contest_competition_02242E5C(v0->unk_00, actingCompetitionMessageID, &v3, NULL);
        }

        if ((v0->unk_00->unk_220.unk_00 + 1 == 4) && (v0->unk_0E == 0)) {
            Sound_PlayEffect(SEQ_SE_DP_CON_029_sseq);
            v0->unk_0E++;
        }

        v0->unk_0C++;
        break;
    case 2:
        if (contest_competition_02242ECC(v0->unk_00) != 0) {
            break;
        }

        v0->unk_0C++;

    case 3:
        v1 = contest_competition_0223FAF8(v0->unk_00->unk_7E4);

        if (v1 != 0xffffffff) {
            v0->unk_10.unk_00 = Pokemon_GetValue(v0->unk_00->unk_0C.unk_00->contestMons[v0->unk_0D], MON_DATA_MOVE1 + v1, NULL);
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            v0->unk_0C++;
        }
        break;
    case 4:
        if (contest_competition_0223FBC0(v0->unk_00->unk_7E4) == 0) {
            break;
        }

        v0->unk_0C++;
    case 5:
        v0->unk_0C++;
    case 6:
        contest_competition_0223F9C4(v0->unk_00->unk_7E4, 3, 0, NULL);

        {
            UnkStruct_contest_competition_022449B8 v5;

            v5.unk_04 = v0->unk_00->unk_220.unk_00 + 1;
            contest_competition_02242E5C(v0->unk_00, ACTING_COMPETITION_MESSAGE_CHOOSE_JUDGE, &v5, NULL);
        }

        v0->unk_0C++;
        break;
    case 7:
        if (contest_competition_02242ECC(v0->unk_00) != 0) {
            break;
        }

        v0->unk_0C++;
    case 8:
        v1 = contest_competition_0223FAF8(v0->unk_00->unk_7E4);

        if (v1 != 0xffffffff) {
            v0->unk_10.unk_02 = v1;
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            v0->unk_0C++;
        }
        break;
    case 9:
        if (contest_competition_0223FBC0(v0->unk_00->unk_7E4) == 0) {
            break;
        }

        if (v0->unk_10.unk_02 == 3) {
            v0->unk_0C = 1;
            break;
        } else {
            v0->unk_0C++;
        }
    case 10:
        v0->unk_0C++;
    default:
        if (v0->unk_00->unk_00->isLinkContest == TRUE) {
            contest_competition_02242E5C(v0->unk_00, ACTING_COMPETITION_MESSAGE_COMMUNICATING_PLEASE_STAND_BY, NULL, NULL);
        }

        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, &v0->unk_10, sizeof(UnkStruct_contest_competition_02244BB0));
        contest_competition_0223F9C4(v0->unk_00->unk_7E4, 0, 0, NULL);

        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static void contest_competition_02244BB0(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, UnkStruct_contest_competition_0224F3D8 *param3, int contestantID)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244BB0 *v1 = param3->unk_00[contestantID];

    v0->unk_220.moveIDs[contestantID] = v1->unk_00;
    v0->unk_220.unk_0E[contestantID] = v1->unk_02;
}

static int contest_competition_02244BD4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02244BEC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    return;
}

static int contest_competition_02244BF0(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02244C08(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_02244C68, v1, 30000);
}

static void contest_competition_02244C68(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 1:
        v0->unk_0C++;
        break;
    case 2:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 4;
        }
        break;
    case 3:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 4:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static int contest_competition_02244D20(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02244D38(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_02244D98, v1, 30000);
}

static void contest_competition_02244D98(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 1:
        if (v1->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v1->unk_12, v1->unk_13, &v1->unk_0C, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        v0->unk_0C++;
    case 5:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 7;
        }
        break;
    case 6:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 7:
        v0->unk_0C++;
    case 8:
        if (v1->unk_28_3 == 1) {
            v0->unk_F4 = v0->unk_14.unk_10.unk_B0[v1->unk_03];
            v0->unk_10 = 0;
            v0->unk_0C++;
        } else {
            v0->unk_0C = 11;
        }
        break;
    case 9: {
        int v2 = 0, v3, v4;

        v0->unk_10++;

        for (v4 = 0; v4 < (1 + 2); v4++) {
            v3 = v0->unk_14.unk_10.unk_B0[v4] - v0->unk_10 * 10;

            if (v0->unk_14.unk_10.unk_B3[v4] <= v3) {
                v2++;
                contest_competition_022424D4(&v0->unk_00->unk_0C, v4, v3);
                Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            }
        }

        if (v2 > 0) {
            v0->unk_0C++;
        } else {
            v0->unk_0C = 11;
        }
    } break;
    case 10:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 11:
        v0->unk_0C++;
    case 12:
        v0->unk_0C++;
    case 13: {
        int v5, v6;

        for (v5 = 0; v5 < 4; v5++) {
            v6 = v0->unk_00->unk_220.unk_01[v5];

            if ((v0->unk_14.unk_10.unk_00[v6].unk_28_4 != v0->unk_14.unk_10.unk_00[v6].unk_28_8) || (v0->unk_14.unk_10.unk_00[v6].unk_28_6 != v0->unk_14.unk_10.unk_00[v6].unk_28_10)) {
                contest_competition_022430AC(&v0->unk_00->unk_0C, v5, v0->unk_14.unk_10.unk_00[v6].unk_28_6);
                Sound_PlayEffect(SEQ_SE_DP_CON_004_sseq);
            }
        }
    }
        v0->unk_0C++;
    case 14:
        v0->unk_0C++;
    case 15:
        v0->unk_0C++;
    case 16:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244FBC(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02244FD4(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_02245034, v1, 30000);
}

static void contest_competition_02245034(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 1:
        if (v1->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v1->unk_12, v1->unk_13, &v1->unk_0C, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        v0->unk_0C++;
    case 5:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 7;
        }
        break;
    case 6:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 7:
        v0->unk_0C++;
    case 8:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245124(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_0224513C(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_0224519C, v1, 30000);
}

static void contest_competition_0224519C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F4 = v0->unk_14.unk_10.unk_B0[v1->unk_03];
        v0->unk_0C++;
        break;
    case 1:
        if (v0->unk_14.unk_10.unk_B3[v1->unk_03] > v0->unk_14.unk_10.unk_B0[v1->unk_03]) {
            int v2;

            if (v0->unk_14.unk_10.unk_B3[v1->unk_03] >= (10 * 5)) {
                v2 = 3;
            } else {
                v2 = 2;
            }

            contest_competition_02241A8C(&v0->unk_00->unk_0C, v1->unk_03, v2);
            contest_competition_02241B3C(v0->unk_00, v1->unk_03, v2, &v0->unk_F8);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 3;
        }
        break;
    case 2:
        if (v0->unk_F8 == 1) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        if (v0->unk_14.unk_C6.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_14.unk_C6.actingMessagesID, &v0->unk_14.unk_C6.unk_00, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 6:
        v0->unk_0C++;
    case 7:
        if (v0->unk_14.unk_10.unk_B3[v1->unk_03] > v0->unk_14.unk_10.unk_B0[v1->unk_03]) {
            contest_competition_022431A0(v0->unk_00, v0->unk_14.unk_10.unk_B3[v1->unk_03], 0, 70, 1, &v0->unk_11);
        } else {
            v0->unk_11 = 1;
        }

        v0->unk_0C++;
        break;
    case 8:
        v0->unk_0F++;

        if (v0->unk_0F > 8) {
            v0->unk_0F = 0;
            v0->unk_0C++;
        }
        break;
    case 9:
        v0->unk_0C++;
    case 10:
        v0->unk_0C++;
    case 11:
        if (v0->unk_F4 != v0->unk_14.unk_10.unk_B3[v1->unk_03]) {
            if (v0->unk_14.unk_10.unk_B3[v1->unk_03] - v0->unk_14.unk_10.unk_B0[v1->unk_03] > 0) {
                v0->unk_F4 += 10;
                contest_competition_022424D4(&v0->unk_00->unk_0C, v1->unk_03, v0->unk_F4);
            } else {
                v0->unk_F4 -= 10;
                contest_competition_022424D4(&v0->unk_00->unk_0C, v1->unk_03, v0->unk_F4);
                Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            }

            v0->unk_0C++;
        } else {
            v0->unk_0C = 14;
        }
        break;
    case 12:
        if (contest_competition_022424A8(&v0->unk_00->unk_0C, v1->unk_03) == 1) {
            v0->unk_0C++;
        }
        break;
    case 13:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C = 11;
        }
        break;
    case 14:
        if (v0->unk_F4 >= (10 * 5)) {
            v0->unk_FC = contest_competition_0224365C(v0->unk_00, v1->unk_03);
        }

        v0->unk_0C++;
        break;
    case 15:
        if (v0->unk_14.unk_C6.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_14.unk_C6.actingMessagesID2, &v0->unk_14.unk_C6.unk_06, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 17;
        }
        break;
    case 16:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 17:
        v0->unk_0C++;
    case 18:
        if (v0->unk_F4 >= (10 * 5)) {
            contest_competition_022436D0(v0->unk_00, v0->contestantID, v0->unk_0E, v1->unk_03, &v0->unk_12);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 20;
        }
        break;
    case 19:
        if (v0->unk_12 == 0) {
            v0->unk_0C++;
        }
        break;
    case 20:
        v0->unk_0C++;
    case 21:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 22:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
            v0->unk_0C++;
        } else {
            contest_competition_02241B1C(&v0->unk_00->unk_0C);
            v0->unk_0C = 24;
        }
        break;
    case 23:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 24:
        if (v0->unk_F4 >= (10 * 5)) {
            contest_competition_02243690(v0->unk_FC);
            contest_competition_022424D4(&v0->unk_00->unk_0C, v1->unk_03, 0);
        }

        v0->unk_0C++;
        break;
    case 25:
    default:
        if (v0->unk_11 == 1) {
            contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_02245510(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245528(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_02245588, v1, 30000);
}

static void contest_competition_02245588(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 1:
        if (v1->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v1->unk_12, v1->unk_13, &v1->unk_0C, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        v0->unk_0C++;
    case 5:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
        } else {
            v0->unk_0C = 7;
        }

        v0->unk_0C++;
        break;
    case 6:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 7:
        v0->unk_0C++;
    case 8:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245678(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245690(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02245690 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02245690));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02245690));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->unk_10 = *v2;

    SysTask_Start(contest_competition_022456E8, v1, 30000);
}

static void contest_competition_022456E8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02245690 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1;
    int v2, v3, v4;

    v2 = v0->unk_10.unk_D6_val1.unk_01[v0->unk_F0];
    v3 = 0;

    if (v2 != 4) {
        v1 = &v0->unk_10.unk_10.unk_00[v2];

        for (v4 = 0; v4 < 4; v4++) {
            if (v0->unk_00->unk_220.unk_01[v4] == v2) {
                v3 = v4;
                break;
            }
        }
    } else {
        v1 = NULL;
    }

    switch (v0->unk_0C) {
    case 0:
        v0->unk_EE = v1->unk_1A;
        v0->unk_0C++;
    case 1: {
        int v5;

        if (v1->unk_09 == 0) {
            v5 = 4;
            Sound_PlayEffect(SEQ_SE_DP_CON_023_sseq);
        } else if (v1->unk_09 == 1) {
            v5 = 5;
            Sound_PlayEffect(SEQ_SE_DP_CON_022_sseq);
        } else if (v1->unk_09 == 2) {
            v5 = 6;
            Sound_PlayEffect(SEQ_SE_DP_CON_021_sseq);
        } else {
            v0->unk_0C = 3;
            Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            break;
        }

        contest_competition_02241B3C(v0->unk_00, v1->unk_03, v5, &v0->unk_F1);
    }
        v0->unk_0C++;
        break;
    case 2:
        if (v0->unk_F1 == 1) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        if (v1->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v1->unk_12, v1->unk_13, &v1->unk_0C, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 6:
        v0->unk_0C++;
    case 7:
        if (v0->unk_10.unk_C6.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_10.unk_C6.actingMessagesID, &v0->unk_10.unk_C6.unk_00, &v0->unk_10.unk_D6_val1);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 9;
        }
        break;
    case 8:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 9:
        v0->unk_0C++;
    case 10:
        if (v0->unk_10.unk_C6.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_10.unk_C6.actingMessagesID2, &v0->unk_10.unk_C6.unk_06, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 12;
        }
        break;
    case 11:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 12:
        v0->unk_0C++;
    case 13:
        v0->unk_EE = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 14:
        if (v0->unk_EE < v1->unk_18) {
            v0->unk_EE += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v2, v3, v0->unk_EE);
        } else {
            v0->unk_0C = 16;
            break;
        }

        v0->unk_0C++;
        break;
    case 15:
        v0->unk_0D++;

        if (v0->unk_0D > 2) {
            v0->unk_0D = 0;
            v0->unk_0C--;
        }
        break;
    case 16:
        v0->unk_F0++;

        if ((v0->unk_F0 < 4) && (v0->unk_10.unk_D6_val1.unk_01[v0->unk_F0] != 4)) {
            v0->unk_0C = 13;
        } else {
            v0->unk_0C++;
        }
        break;
    case 17:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224595C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245974(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v2->contestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_022459D4, v1, 30000);
}

static void contest_competition_022459D4(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0:
        v0->unk_F2 = v1->unk_1A;
        v0->unk_0C++;
        break;
    case 1:
        if (v1->unk_12 != 0) {
            contest_competition_02242E9C(v0->unk_00, v1->unk_12, v1->unk_13, &v1->unk_0C, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 3:
        v0->unk_0C++;
    case 4:
        if (v0->unk_14.unk_C6.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_14.unk_C6.actingMessagesID, &v0->unk_14.unk_C6.unk_00, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 6:
        v0->unk_0C++;
    case 7:
        if (v0->unk_14.unk_C6.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->unk_14.unk_C6.actingMessagesID2, &v0->unk_14.unk_C6.unk_06, NULL);
            v0->unk_0C++;
        } else {
            v0->unk_0C = 9;
        }
        break;
    case 8:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 9:
        v0->unk_0C++;
    case 10:
        v0->unk_0C++;
    case 11:
        if (v0->unk_F2 < v1->unk_18) {
            v0->unk_F2 += 10;
            contest_competition_02241F34(&v0->unk_00->unk_0C, v0->contestantID, v0->unk_0E, v0->unk_F2);
        } else {
            v0->unk_0C = 13;
        }

        v0->unk_0C++;
        break;
    case 12:
        v0->unk_0F++;

        if (v0->unk_0F > 2) {
            v0->unk_0F = 0;
            v0->unk_0C--;
        }
        break;
    case 13:
        v0->unk_0C++;
    case 14:
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245B48(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245B60(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02244C08 *v1;
    UnkStruct_contest_competition_02246F24_sub1 *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02244C08));
    MI_CpuClear8(v1, sizeof(UnkStruct_contest_competition_02244C08));

    v1->unk_00 = v0;
    v1->unk_04 = *param2;
    v1->contestantID = v0->unk_0C.unk_00->playerContestantID;
    v1->unk_0E = v2->unk_01;
    v1->unk_14 = *v2;

    SysTask_Start(contest_competition_02245BC8, v1, 30000);
}

static void contest_competition_02245BC8(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02244C08 *v0 = param1;
    UnkStruct_contest_competition_022444BC *v1 = &v0->unk_14.unk_10.unk_00[v0->contestantID];

    switch (v0->unk_0C) {
    case 0: {
        UnkStruct_contest_competition_022449B8 v3;

        u32 actingMessagesID = contest_competition_0224314C(v0->contestantID, v1->unk_18, &v3);
        contest_competition_02242E5C(v0->unk_00, actingMessagesID, &v3, NULL);
        v0->unk_0C++;
    } break;
    case 1:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_0C++;
        }
        break;
    case 2:
        v0->unk_0C++;
        break;
    default:
        contest_competition_0224F26C(&v0->unk_00->unk_BF8, &v0->unk_04, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245C4C(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245C60(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02246F24_sub1 *v1 = param3;
    UnkStruct_contest_competition_02245C60 *v2 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02245C60));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_02245C60));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;

    SysTask_Start(contest_competition_02245CA4, v2, 30000);
}

static void contest_competition_02245CA4(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02245C60 *v0 = param1;

    int v1, v2;

    switch (v0->unk_20) {
    case 0:
        contest_competition_022431A0(v0->unk_00, 0, 0, 70, 0, &v0->unk_27);
        v0->unk_20++;
        break;
    case 1: {
        int v3;

        for (v3 = 0; v3 < 4; v3++) {
            v0->unk_10[v3] = contest_competition_0224145C(v0->unk_00, v0->unk_00->unk_220.unk_01[v3]);
            contest_competition_0224331C(v0->unk_00, v0->unk_00->unk_220.unk_01[v3], v3, &v0->unk_23[v3], v0->unk_10[v3]);
        }
    }
        v0->unk_20++;
        break;
    case 2:
        v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if ((v0->unk_23[v1] == 0) && (contest_competition_022414BC(v0->unk_10[v1]) == 0)) {
                v2++;
            }
        }

        if (v2 == 4) {
            for (v1 = 0; v1 < 4; v1++) {
                contest_competition_02241494(v0->unk_10[v1]);
            }

            v0->unk_20++;
        }
        break;
    case 3:
    default:
        if (v0->unk_27 == 1) {
            contest_competition_0224F26C(v0->unk_0C, &v0->unk_04, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }

        break;
    }
}

static int contest_competition_02245DA4(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->unk_BF8, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_022472F8));
    return v1;
}

static void contest_competition_02245DBC(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_022472F8 *v1 = param3;
    v0->unk_220 = *v1;

    contest_competition_02241EF0(&v0->unk_0C);
    contest_competition_022430F8(&v0->unk_0C);
    contest_competition_02242FE8(v0);
    contest_competition_02241428(v0);
    contest_competition_0224F26C(&v0->unk_BF8, param2, NULL, 0);
}

static int contest_competition_02245E00(UnkStruct_contest_competition_0224F30C *param0, void *param1, int param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(UnkStruct_contest_competition_02246F24_sub1));
    return v1;
}

static void contest_competition_02245E14(UnkStruct_contest_competition_0224F30C *param0, void *param1, const UnkStruct_contest_competition_02243C80 *param2, void *param3)
{
    UnkStruct_contest_competition_02246F24 *v0 = param1;
    UnkStruct_contest_competition_02246F24_sub1 *v1 = param3;
    UnkStruct_contest_competition_02245E14 *v2 = Heap_Alloc(HEAP_ID_21, sizeof(UnkStruct_contest_competition_02245E14));
    MI_CpuClear8(v2, sizeof(UnkStruct_contest_competition_02245E14));

    v2->unk_00 = v0;
    v2->unk_04 = *param2;
    v2->unk_0C = param0;
    v2->contestantID = v1->contestantID;
    v2->unk_14 = v1->unk_C6.unk_00;
    v2->actingMessagesID = v1->unk_C6.actingMessagesID;
    v2->unk_1C = v1->unk_C6.unk_0F;
    v2->unk_1B = v1->unk_C6.unk_0E;

    SysTask_Start(contest_competition_02245E8C, v2, 30000);
}

static void contest_competition_02245E8C(SysTask *param0, void *param1)
{
    UnkStruct_contest_competition_02245E14 *v0 = param1;

    switch (v0->unk_10) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->unk_00, v0->actingMessagesID, &v0->unk_14, NULL);
            v0->unk_10++;
        } else {
            v0->unk_10 = 100;
        }
        break;
    case 1:
        if (contest_competition_02242ECC(v0->unk_00) == 0) {
            v0->unk_10++;
        }
        break;
    case 2:
        v0->unk_12++;

        if (v0->unk_1C == 1) {
            v0->unk_10++;
        } else if (v0->unk_12 >= v0->unk_1B) {
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
