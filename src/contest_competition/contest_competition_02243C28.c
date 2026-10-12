#include "contest_competition/contest_competition_02243C28.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/move_animation.h"

#include "battle/battle_anim_battler_context.h"
#include "battle_anim/battle_anim_system.h"
#include "contest_competition/contest_competition_0223F7E4.h"
#include "contest_competition/contest_competition_022413D8.h"
#include "contest_competition/contest_competition_0224F18C.h"
#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_pause_task.h"
#include "contest_competition/struct_acting_message_task.h"
#include "contest_competition/struct_acting_contestant_move_task.h"
#include "contest_competition/struct_acting_score_gain_task.h"
#include "contest_competition/struct_acting_move_anim_task.h"
#include "contest_competition/struct_acting_performance.h"
#include "contest_competition/struct_acting_move_choice_task.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_move_choice.h"
#include "contest_competition/struct_acting_score_update_task.h"
#include "contest_competition/struct_acting_voltage_award_task.h"
#include "contest_competition/struct_acting_score_gauge_display_task.h"
#include "contest_competition/struct_acting_message_delay_task.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"
#include "contest_competition/struct_acting_match_state.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"
#include "contest_competition/struct_contest_packet_handler.h"

#include "heap.h"
#include "pokemon.h"
#include "pokemon_sprite.h"
#include "sound_playback.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "contest_util.h"

static int contest_competition_02243C68(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02243C80(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02243C94(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4);
static int contest_competition_02243CDC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02243CF4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02243D34(SysTask *param0, void *param1);
static int contest_competition_02243EF8(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02243F10(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02243F68(SysTask *param0, void *param1);
static int contest_competition_022440C8(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022440E0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224413C(SysTask *param0, void *param1);
static int contest_competition_02244228(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244240(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022442AC(SysTask *param0, void *param1);
static int contest_competition_022443E0(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_022443F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022444BC(SysTask *param0, void *param1);
static int contest_competition_02244958(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244970(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02244BB0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int contestantID);
static void contest_competition_022449B8(SysTask *param0, void *param1);
static int contest_competition_02244BD4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244BEC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02244BF0(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244C08(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02244C68(SysTask *param0, void *param1);
static int contest_competition_02243C98(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02243CB0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02245DA4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245DBC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static int contest_competition_02244D20(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244D38(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02244D98(SysTask *param0, void *param1);
static int contest_competition_02244FBC(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02244FD4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02245034(SysTask *param0, void *param1);
static int contest_competition_02245124(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_0224513C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_0224519C(SysTask *param0, void *param1);
static int contest_competition_02245510(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245528(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02245588(SysTask *param0, void *param1);
static int contest_competition_02245678(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245690(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022456E8(SysTask *param0, void *param1);
static int contest_competition_02245B48(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245B60(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02245BC8(SysTask *param0, void *param1);
static int contest_competition_02245E00(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245E14(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02245E8C(SysTask *param0, void *param1);
static int contest_competition_02245C4C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245C60(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02245CA4(SysTask *param0, void *param1);
static int contest_competition_0224595C(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02245974(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_022459D4(SysTask *param0, void *param1);
static int contest_competition_02243DB4(ContestPacketQueue *param0, void *param1, int param2, void *param3);
static void contest_competition_02243DCC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3);
static void contest_competition_02243E2C(SysTask *param0, void *param1);

static const ContestPacketHandler Unk_contest_competition_022539E4[] = {
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

void contest_competition_02243C28(ActingCompetition *param0)
{
    ContestPacketQueueConfig v0;

    v0.handlers = Unk_contest_competition_022539E4;
    v0.handlerCount = NELEMS(Unk_contest_competition_022539E4);
    v0.playerContestantID = param0->contest->data.playerContestantID;
    v0.selfContestantID = param0->contest->data.leaderContestantID;
    v0.isLinkContest = param0->contest->isLinkContest;

    contest_competition_0224F18C(&param0->packetQueue, &v0);
}

static int contest_competition_02243C68(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243C80(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    contest_competition_0224F26C(&v0->packetQueue, param2, NULL, 0);
}

static void contest_competition_02243C94(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int param4)
{
    ActingCompetition *v0 = param1;
    return;
}

static int contest_competition_02243C98(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243CB0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;

    v0->initialized2 = 1;

    if (Contest_IsPlayerLeader(v0->contest) == FALSE) {
        contest_competition_0224F26C(&v0->packetQueue, param2, NULL, 0);
    }
}

static int contest_competition_02243CDC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02243CF4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingPauseTask *v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingPauseTask));
    MI_CpuClear8(v1, sizeof(ActingPauseTask));

    v1->competition = v0;
    v1->header = *param2;

    SysTask_Start(contest_competition_02243D34, v1, 30000);
}

static void contest_competition_02243D34(SysTask *param0, void *param1)
{
    ActingPauseTask *v0 = param1;

    switch (v0->state) {
    case 0:
        contest_competition_022431A0(v0->competition, 0, 0, 70, 0, &v0->unused_0E);
        v0->state++;
        break;
    case 1:
        v0->timer++;

        if (v0->timer > 30) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 2:
        if (v0->unused_0E == 1) {
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02243DB4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02243DCC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingSyncPacket *v1 = param3;
    ActingMessageTask *v2 = Heap_Alloc(HEAP_ID_21, sizeof(ActingMessageTask));
    MI_CpuClear8(v2, sizeof(ActingMessageTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->actingMessagesID = v1->messages.actingMessagesID;
    v2->messageParams = v1->messages.messageParams;

    SysTask_Start(contest_competition_02243E2C, v2, 30000);
}

static void contest_competition_02243E2C(SysTask *param0, void *param1)
{
    ActingMessageTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->actingMessagesID, &v0->messageParams, NULL);
        }

        Sound_PlayEffect(SEQ_SE_DP_CON_032_sseq);
        v0->state++;
        break;
    case 1:
        if (v0->actingMessagesID == ACTING_COMPETITION_MESSAGE_NONE || (contest_competition_02242ECC(v0->competition) == 0)) {
            v0->state++;
        }
        break;
    case 2:
        v0->messageID++;

        if (v0->messageID > 30) {
            v0->messageID = 0;
            v0->state++;
        }
        break;
    case 3:
        contest_competition_022431A0(v0->competition, 0, 0, 70, 0, &v0->timer);
        v0->state++;
        break;
    case 4:
        if (v0->timer == 1) {
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02243EF8(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02243F10(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingSyncPacket *v2 = param3;
    ActingContestantMoveTask *v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingContestantMoveTask));

    MI_CpuClear8(v1, sizeof(ActingContestantMoveTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;

    contest_competition_022426E8(v0, 0, &v1->messageState);
    SysTask_Start(contest_competition_02243F68, v1, 30000);
    contest_competition_02242DA8(v0);
}

static void contest_competition_02243F68(SysTask *param0, void *param1)
{
    ActingContestantMoveTask *v0 = param1;
    int contestantID = v0->contestantID;
    int v2 = Pokemon_SpriteYOffset(v0->competition->scene.contestData->contestMons[contestantID], 0);

    switch (v0->state) {
    case 0:
        v0->contestMoveEffect++;

        if (v0->contestMoveEffect > 10) {
            v0->contestMoveEffect = 0;
            v0->state++;
        }
        break;
    case 1: {
        int v3, v4;

        v3 = v0->contestantID;
        v4 = Pokemon_SpriteYOffset(v0->competition->scene.contestData->contestMons[v3], 0);

        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v3], MON_SPRITE_HIDE_2, 0);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v3], MON_SPRITE_HIDE, 0);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v3], MON_SPRITE_X_CENTER, (256 - 40) + 40);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v3], MON_SPRITE_Y_CENTER, ((104 + 8) + 60) + v4);

        v0->moveID = ((256 - 40) + 40) << 8;
        v0->timer = ((104 + 8) + 60) << 8;
    }
        v0->state++;
        break;

    case 2:
        if (v0->contestantID == v0->competition->contest->data.playerContestantID) {
            Sound_PlayEffect(SEQ_SE_DP_CON_031_sseq);
        }

        v0->state++;

    case 3:
        v0->moveID -= (((((256 - 40) + 40) - (256 - 40)) << 8) / 7);
        v0->timer -= (((((104 + 8) + 60) - (104 + 8)) << 8) / 7);

        if (((v0->moveID >> 8) <= (256 - 40)) || ((v0->timer >> 8) <= (104 + 8))) {
            v0->moveID = (256 - 40) << 8;
            v0->timer = (104 + 8) << 8;
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_X_CENTER, v0->moveID >> 8);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_Y_CENTER, (v0->timer >> 8) + v2);
        break;
    default:
        if (v0->messageState == 1) {
            contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_022440C8(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_022440E0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingContestantMoveTask *v1;
    ActingSyncPacket *v2;
    int v3;

    v2 = param3;
    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingContestantMoveTask));

    MI_CpuClear8(v1, sizeof(ActingContestantMoveTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;

    int contestantID = v1->contestantID;
    v3 = Pokemon_SpriteYOffset(v0->scene.contestData->contestMons[contestantID], 0);

    v1->moveID = (256 - 40) << 8;
    v1->timer = (104 + 8) << 8;

    SysTask_Start(contest_competition_0224413C, v1, 30000);
}

static void contest_competition_0224413C(SysTask *param0, void *param1)
{
    ActingContestantMoveTask *v0 = param1;
    int contestantID = v0->contestantID;
    int v2 = Pokemon_SpriteYOffset(v0->competition->scene.contestData->contestMons[contestantID], 0);

    switch (v0->state) {
    case 0:
        v0->moveID += (((((256 - 40) + 40) - (256 - 40)) << 8) / 7);
        v0->timer += (((((104 + 8) + 60) - (104 + 8)) << 8) / 7);

        if (((v0->moveID >> 8) >= ((256 - 40) + 40)) || ((v0->timer >> 8) >= ((104 + 8) + 60))) {
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[contestantID], MON_SPRITE_HIDE_2, 1);
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[contestantID], MON_SPRITE_HIDE, 1);
            v0->state++;
        }

        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_X_CENTER, v0->moveID >> 8);
        PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_Y_CENTER, (v0->timer >> 8) + v2);
        break;
    case 1:
        if (v0->competition->contestantReady[v0->contestantID] == 1) {
            contest_competition_02241524(&v0->competition->scene, v0->contestantID);
            v0->competition->contestantReady[v0->contestantID] = 0;
        }

        v0->state++;
        break;
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244228(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02244240(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreGainTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreGainTask));
    MI_CpuClear8(v1, sizeof(ActingScoreGainTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->judgeContestantID = v2->judgeContestantID;
    v1->actingMessagesID = v2->messages.actingMessagesID;
    v1->messageParams = v2->messages.messageParams;
    v1->isSameJudge = v2->isSameJudge;

    SysTask_Start(contest_competition_022442AC, v1, 30000);
}

static void contest_competition_022442AC(SysTask *param0, void *param1)
{
    ActingScoreGainTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0: {
        int v2;

        v2 = contest_competition_02243174(v0->competition->matchState.scores[v0->contestantID]);

        if (v2 > 0) {
            contest_competition_022431A0(v0->competition, 0, 0, v2, 0, &v0->animationDone2);
        } else {
            v0->state = 2;
            break;
        }
    }
        v0->state++;
        break;
    case 1:
        if (v0->animationDone2 == 1) {
            v0->state++;
        }
        break;
    case 2:
        v0->state++;
        break;
    case 3:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->actingMessagesID, &v0->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 5;
        }
        break;
    case 4:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 5:
        v0->state++;
        break;
    case 6:
        contest_competition_02241A8C(&v0->competition->scene, v0->judgeContestantID, v0->isSameJudge);
        contest_competition_02241B3C(v0->competition, v0->judgeContestantID, v0->isSameJudge, &v0->animationDone);
        v0->state++;
        break;
    case 7:
        if (v0->animationDone == 1) {
            v0->state++;
        }
        break;
    case 8:
        v0->timer++;

        if (v0->timer > 5) {
            contest_competition_02241B1C(&v0->competition->scene);
            v0->state++;
        }
        break;

    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_022443E0(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_022443F8(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingMoveAnimTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingMoveAnimTask));
    MI_CpuClear8(v1, sizeof(ActingMoveAnimTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->moveID = v2->turnState.performances[v2->contestantID].moveID;
    v1->actingMessagesID = v2->messages.actingMessagesID;
    v1->messageParams = v2->messages.messageParams;
    v1->actingMessagesID2 = v2->messages.actingMessagesID2;
    v1->messageParams2 = v2->messages.messageParams2;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_022444BC, v1, 5);
}

static void contest_competition_022444BC(SysTask *param0, void *param1)
{
    ActingMoveAnimTask *v0 = param1;
    int v1;
    ActingPerformance *v2 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->actingMessagesID, &v0->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 2;
        }
        break;
    case 1:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->state++;
        break;
    case 3:
        if (v2->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v2->messageID, v2->messageArg, &v2->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 5;
        }
        break;
    case 4:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 5:
        v0->state++;
        break;
    case 6:
        if (v0->actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->actingMessagesID2, &v0->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 8;
        }
        break;
    case 7:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 8:
        v0->state++;
        break;
    case 9:
        contest_competition_022439C8(v0->competition->contest, v0->contestantID, v0->moveID, &v0->animArgs);
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

        int species = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_SPECIES, NULL);
        int gender = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_GENDER, NULL);
        isShiny = Pokemon_IsShiny(v0->competition->scene.contestData->contestMons[v0->contestantID]);
        monForm = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_FORM, NULL);
        personality = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_PERSONALITY, NULL);

        v10 = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v16], MON_DATA_SPECIES, NULL);
        v11 = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v16], MON_DATA_GENDER, NULL);
        v12 = Pokemon_IsShiny(v0->competition->scene.contestData->contestMons[v16]);
        v13 = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v16], MON_DATA_FORM, NULL);
        v15 = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v16], MON_DATA_PERSONALITY, NULL);

        moveAnim.command = 0;
        moveAnim.unk_01 = 0;
        moveAnim.move = v0->animArgs.actingAnimationMoveID;
        moveAnim.damage = 1;
        moveAnim.power = 10;
        moveAnim.effectChance = v0->animArgs.hasFriendship;
        moveAnim.friendship = v0->animArgs.friendship;
        moveAnim.fieldConditions = 0;
        moveAnim.attacker = 0;
        moveAnim.defender = 1;
        moveAnim.terrain = 9;

        for (v5 = 0; v5 < 4; v5++) {
            moveAnim.species[v5] = species;
        }

        moveAnim.species[1] = v10;

        battlerContext.bgConfig = v0->competition->scene.bgConfig;
        battlerContext.paletteData = v0->competition->scene.paletteData;
        battlerContext.pokemonSpriteData[0] = &v0->competition->scene.pokemonSpriteDataArray[v0->contestantID];
        battlerContext.pokemonSpriteData[1] = &v0->competition->scene.pokemonSpriteData;

        for (v5 = 0; v5 < 4; v5++) {
            battlerContext.battlerTypes[v5] = 0xff;
            battlerContext.battlerSpecies[v5] = species;
            battlerContext.battlerGenders[v5] = gender;
            battlerContext.battlerShinyFlags[v5] = isShiny;
            battlerContext.battlerForms[v5] = monForm;
            battlerContext.battlerPersonalities[v5] = personality;
            battlerContext.battlerMoveEffects[v5] = 0;
        }

        battlerContext.battlerMoveEffects[0] = v0->animArgs.flags;
        battlerContext.battlerTypes[0] = 0;
        battlerContext.battlerTypes[1] = 1;
        battlerContext.battlerSpecies[1] = v10;
        battlerContext.battlerGenders[1] = v11;
        battlerContext.battlerShinyFlags[1] = v12;
        battlerContext.battlerForms[1] = v13;
        battlerContext.battlerPersonalities[1] = v15;
        battlerContext.pokemonSprites[0] = v0->competition->scene.pokemonSprites[v0->contestantID];

        v1 = (v0->contestantID == 0) ? 1 : 0;

        battlerContext.pokemonSprites[1] = v0->competition->scene.pokemonSprites[v1];
        battlerContext.battleType = 0;
        battlerContext.moveArcID = 8;
        battlerContext.battleBgRef.narcID = 45;
        battlerContext.battleBgRef.tilesNarcMemberIdx = 1;
        battlerContext.battleBgRef.paletteNarcMemberIdx = 30;
        battlerContext.battleBgRef.tilemapNarcMemberIdx = 2;
        battlerContext.battleBgRef.paletteDestStart = 0;
        battlerContext.battleBgRef.paletteSrcSize = 3;
        battlerContext.spriteSystem = v0->competition->scene.spriteSystem;
        battlerContext.chatotCry = v0->competition->contest->chatotCry[v0->contestantID];

        BattleAnimSystem_StartMove(v0->competition->scene.battleAnimSystem, &moveAnim, v0->animArgs.actingAnimationMoveID, &battlerContext);
    }

        {
            int v17 = Pokemon_SpriteYOffset(v0->competition->scene.contestData->contestMons[v0->contestantID], 0);

            if (v0->animArgs.flags != ((0x40 ^ 0xffffffff) & (0x80 ^ 0xffffffff) & (0x40000 ^ 0xffffffff) & (0x20000000 ^ 0xffffffff))) {
                PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_HIDE, 0);
            }

            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_HIDE_2, 0);
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_X_CENTER, 256 - 40);
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v0->contestantID], MON_SPRITE_Y_CENTER, (104 + 8) + v17);

            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v1], MON_SPRITE_HIDE_2, 1);
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v1], MON_SPRITE_X_CENTER, 80);
            PokemonSprite_SetAttribute(v0->competition->scene.pokemonSprites[v1], MON_SPRITE_Y_CENTER, 50 - 8);
        }

        v0->state++;
        break;
    case 11:
        BattleAnimSystem_ExecuteScript(v0->competition->scene.battleAnimSystem);

        if (BattleAnimSystem_IsMoveActive(v0->competition->scene.battleAnimSystem) == 0) {
            BattleAnimSystem_FreeScriptData(v0->competition->scene.battleAnimSystem);

            if (v0->animArgs.isContestant > 0) {
                v0->animArgs.isContestant--;
                v0->animArgs.hasFriendship++;

                if (v0->animArgs.flags == (0x40 | 0x80 | 0x40000 | 0x20000000)) {
                    v0->animArgs.flags = ((0x40 ^ 0xffffffff) & (0x80 ^ 0xffffffff) & (0x40000 ^ 0xffffffff) & (0x20000000 ^ 0xffffffff));
                }

                v0->state = 10;
            } else {
                v0->state++;
            }
        }
        break;
    case 12:
        switch (v0->animArgs.actingAnimationMoveID) {
        case MOVE_TRANSFORM:
        case MOVE_SUBSTITUTE:
            v0->competition->contestantReady[v0->contestantID] = 1;
            break;
        }

        v0->state++;
        break;
    case 13:
        contest_competition_022426E8(v0->competition, 1, &v0->timer);
        v0->state++;
        break;
    case 14:
        if (v0->timer == 1) {
            v0->state++;
        }
        break;
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244958(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, NULL, 0);
    return v1;
}

static void contest_competition_02244970(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingMoveChoiceTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingMoveChoiceTask));
    MI_CpuClear8(v1, sizeof(ActingMoveChoiceTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v0->scene.contestData->playerContestantID;

    SysTask_Start(contest_competition_022449B8, v1, 100);
}

static void contest_competition_022449B8(SysTask *param0, void *param1)
{
    ActingMoveChoiceTask *v0 = param1;
    int v1;

    switch (v0->state) {
    case 0:
        contest_competition_0223F9C4(v0->competition->moveMenu, 1, 0, NULL);
        v0->state++;
        break;
    case 1:
        contest_competition_0223F9C4(v0->competition->moveMenu, 2, 0, NULL);

        {
            u32 actingCompetitionMessageID;
            ActingMessageParams v3;

            if (v0->competition->matchState.turn + 1 == 4) {
                actingCompetitionMessageID = ACTING_COMPETITION_MESSAGE_LAST_PERFORMANCE_CHOOSE_MOVE;
            } else {
                actingCompetitionMessageID = ACTING_COMPETITION_MESSAGE_WHICH_MOVE_IS_YOUR_CHOICE;
            }

            v3.messageValue = v0->competition->matchState.turn + 1;
            contest_competition_02242E5C(v0->competition, actingCompetitionMessageID, &v3, NULL);
        }

        if ((v0->competition->matchState.turn + 1 == 4) && (v0->timer == 0)) {
            Sound_PlayEffect(SEQ_SE_DP_CON_029_sseq);
            v0->timer++;
        }

        v0->state++;
        break;
    case 2:
        if (contest_competition_02242ECC(v0->competition) != 0) {
            break;
        }

        v0->state++;

    case 3:
        v1 = contest_competition_0223FAF8(v0->competition->moveMenu);

        if (v1 != 0xffffffff) {
            v0->moveChoice.moveID = Pokemon_GetValue(v0->competition->scene.contestData->contestMons[v0->contestantID], MON_DATA_MOVE1 + v1, NULL);
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            v0->state++;
        }
        break;
    case 4:
        if (contest_competition_0223FBC0(v0->competition->moveMenu) == 0) {
            break;
        }

        v0->state++;
    case 5:
        v0->state++;
    case 6:
        contest_competition_0223F9C4(v0->competition->moveMenu, 3, 0, NULL);

        {
            ActingMessageParams v5;

            v5.messageValue = v0->competition->matchState.turn + 1;
            contest_competition_02242E5C(v0->competition, ACTING_COMPETITION_MESSAGE_CHOOSE_JUDGE, &v5, NULL);
        }

        v0->state++;
        break;
    case 7:
        if (contest_competition_02242ECC(v0->competition) != 0) {
            break;
        }

        v0->state++;
    case 8:
        v1 = contest_competition_0223FAF8(v0->competition->moveMenu);

        if (v1 != 0xffffffff) {
            v0->moveChoice.state = v1;
            Sound_PlayEffect(SEQ_SE_DP_DECIDE_sseq);
            v0->state++;
        }
        break;
    case 9:
        if (contest_competition_0223FBC0(v0->competition->moveMenu) == 0) {
            break;
        }

        if (v0->moveChoice.state == 3) {
            v0->state = 1;
            break;
        } else {
            v0->state++;
        }
    case 10:
        v0->state++;
    default:
        if (v0->competition->contest->isLinkContest == TRUE) {
            contest_competition_02242E5C(v0->competition, ACTING_COMPETITION_MESSAGE_COMMUNICATING_PLEASE_STAND_BY, NULL, NULL);
        }

        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, &v0->moveChoice, sizeof(ActingMoveChoice));
        contest_competition_0223F9C4(v0->competition->moveMenu, 0, 0, NULL);

        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static void contest_competition_02244BB0(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, ContestPacketPayloads *param3, int contestantID)
{
    ActingCompetition *v0 = param1;
    ActingMoveChoice *v1 = param3->payloads[contestantID];

    v0->matchState.moveIDs[contestantID] = v1->moveID;
    v0->matchState.contestantIDs[contestantID] = v1->state;
}

static int contest_competition_02244BD4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02244BEC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    return;
}

static int contest_competition_02244BF0(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02244C08(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_02244C68, v1, 30000);
}

static void contest_competition_02244C68(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 1:
        v0->state++;
        break;
    case 2:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
            v0->state++;
        } else {
            v0->state = 4;
        }
        break;
    case 3:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 4:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);

        return;
    }
}

static int contest_competition_02244D20(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02244D38(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_02244D98, v1, 30000);
}

static void contest_competition_02244D98(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 1:
        if (v1->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v1->messageID, v1->messageArg, &v1->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        v0->state++;
    case 5:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
            v0->state++;
        } else {
            v0->state = 7;
        }
        break;
    case 6:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 7:
        v0->state++;
    case 8:
        if (v1->comboFlag == 1) {
            v0->bonusScore = v0->syncPacket.turnState.voltage[v1->contestantID];
            v0->counter = 0;
            v0->state++;
        } else {
            v0->state = 11;
        }
        break;
    case 9: {
        int v2 = 0, v3, v4;

        v0->counter++;

        for (v4 = 0; v4 < (1 + 2); v4++) {
            v3 = v0->syncPacket.turnState.voltage[v4] - v0->counter * 10;

            if (v0->syncPacket.turnState.voltageDisplay[v4] <= v3) {
                v2++;
                contest_competition_022424D4(&v0->competition->scene, v4, v3);
                Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            }
        }

        if (v2 > 0) {
            v0->state++;
        } else {
            v0->state = 11;
        }
    } break;
    case 10:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 11:
        v0->state++;
    case 12:
        v0->state++;
    case 13: {
        int v5, v6;

        for (v5 = 0; v5 < 4; v5++) {
            v6 = v0->competition->matchState.contestantOrder[v5];

            if ((v0->syncPacket.turnState.performances[v6].judgeAppealState != v0->syncPacket.turnState.performances[v6].previousAppealState) || (v0->syncPacket.turnState.performances[v6].appealOrder != v0->syncPacket.turnState.performances[v6].previousAppealOrder)) {
                contest_competition_022430AC(&v0->competition->scene, v5, v0->syncPacket.turnState.performances[v6].appealOrder);
                Sound_PlayEffect(SEQ_SE_DP_CON_004_sseq);
            }
        }
    }
        v0->state++;
    case 14:
        v0->state++;
    case 15:
        v0->state++;
    case 16:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02244FBC(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02244FD4(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_02245034, v1, 30000);
}

static void contest_competition_02245034(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 1:
        if (v1->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v1->messageID, v1->messageArg, &v1->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        v0->state++;
    case 5:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
            v0->state++;
        } else {
            v0->state = 7;
        }
        break;
    case 6:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 7:
        v0->state++;
    case 8:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245124(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_0224513C(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_0224519C, v1, 30000);
}

static void contest_competition_0224519C(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->bonusScore = v0->syncPacket.turnState.voltage[v1->contestantID];
        v0->state++;
        break;
    case 1:
        if (v0->syncPacket.turnState.voltageDisplay[v1->contestantID] > v0->syncPacket.turnState.voltage[v1->contestantID]) {
            int v2;

            if (v0->syncPacket.turnState.voltageDisplay[v1->contestantID] >= (10 * 5)) {
                v2 = 3;
            } else {
                v2 = 2;
            }

            contest_competition_02241A8C(&v0->competition->scene, v1->contestantID, v2);
            contest_competition_02241B3C(v0->competition, v1->contestantID, v2, &v0->animationDone2);
            v0->state++;
        } else {
            v0->state = 3;
        }
        break;
    case 2:
        if (v0->animationDone2 == 1) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        if (v0->syncPacket.messages.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID, &v0->syncPacket.messages.messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 6:
        v0->state++;
    case 7:
        if (v0->syncPacket.turnState.voltageDisplay[v1->contestantID] > v0->syncPacket.turnState.voltage[v1->contestantID]) {
            contest_competition_022431A0(v0->competition, v0->syncPacket.turnState.voltageDisplay[v1->contestantID], 0, 70, 1, &v0->animationDone);
        } else {
            v0->animationDone = 1;
        }

        v0->state++;
        break;
    case 8:
        v0->timer++;

        if (v0->timer > 8) {
            v0->timer = 0;
            v0->state++;
        }
        break;
    case 9:
        v0->state++;
    case 10:
        v0->state++;
    case 11:
        if (v0->bonusScore != v0->syncPacket.turnState.voltageDisplay[v1->contestantID]) {
            if (v0->syncPacket.turnState.voltageDisplay[v1->contestantID] - v0->syncPacket.turnState.voltage[v1->contestantID] > 0) {
                v0->bonusScore += 10;
                contest_competition_022424D4(&v0->competition->scene, v1->contestantID, v0->bonusScore);
            } else {
                v0->bonusScore -= 10;
                contest_competition_022424D4(&v0->competition->scene, v1->contestantID, v0->bonusScore);
                Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            }

            v0->state++;
        } else {
            v0->state = 14;
        }
        break;
    case 12:
        if (contest_competition_022424A8(&v0->competition->scene, v1->contestantID) == 1) {
            v0->state++;
        }
        break;
    case 13:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state = 11;
        }
        break;
    case 14:
        if (v0->bonusScore >= (10 * 5)) {
            v0->voltageGaugeTask = contest_competition_0224365C(v0->competition, v1->contestantID);
        }

        v0->state++;
        break;
    case 15:
        if (v0->syncPacket.messages.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID2, &v0->syncPacket.messages.messageParams2, NULL);
            v0->state++;
        } else {
            v0->state = 17;
        }
        break;
    case 16:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 17:
        v0->state++;
    case 18:
        if (v0->bonusScore >= (10 * 5)) {
            contest_competition_022436D0(v0->competition, v0->contestantID, v0->contestantCount, v1->contestantID, &v0->result);
            v0->state++;
        } else {
            v0->state = 20;
        }
        break;
    case 19:
        if (v0->result == 0) {
            v0->state++;
        }
        break;
    case 20:
        v0->state++;
    case 21:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 22:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
            v0->state++;
        } else {
            contest_competition_02241B1C(&v0->competition->scene);
            v0->state = 24;
        }
        break;
    case 23:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 24:
        if (v0->bonusScore >= (10 * 5)) {
            contest_competition_02243690(v0->voltageGaugeTask);
            contest_competition_022424D4(&v0->competition->scene, v1->contestantID, 0);
        }

        v0->state++;
        break;
    case 25:
    default:
        if (v0->animationDone == 1) {
            contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }
        break;
    }
}

static int contest_competition_02245510(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245528(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_02245588, v1, 30000);
}

static void contest_competition_02245588(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 1:
        if (v1->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v1->messageID, v1->messageArg, &v1->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        v0->state++;
    case 5:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
        } else {
            v0->state = 7;
        }

        v0->state++;
        break;
    case 6:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 7:
        v0->state++;
    case 8:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245678(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245690(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingVoltageAwardTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingVoltageAwardTask));
    MI_CpuClear8(v1, sizeof(ActingVoltageAwardTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_022456E8, v1, 30000);
}

static void contest_competition_022456E8(SysTask *param0, void *param1)
{
    ActingVoltageAwardTask *v0 = param1;
    ActingPerformance *v1;
    int v2, v3, v4;

    v2 = v0->syncPacket.performanceOrder.order[v0->orderIndex];
    v3 = 0;

    if (v2 != 4) {
        v1 = &v0->syncPacket.turnState.performances[v2];

        for (v4 = 0; v4 < 4; v4++) {
            if (v0->competition->matchState.contestantOrder[v4] == v2) {
                v3 = v4;
                break;
            }
        }
    } else {
        v1 = NULL;
    }

    switch (v0->state) {
    case 0:
        v0->voltage = v1->previousScore;
        v0->state++;
    case 1: {
        int v5;

        if (v1->judgeID == 0) {
            v5 = 4;
            Sound_PlayEffect(SEQ_SE_DP_CON_023_sseq);
        } else if (v1->judgeID == 1) {
            v5 = 5;
            Sound_PlayEffect(SEQ_SE_DP_CON_022_sseq);
        } else if (v1->judgeID == 2) {
            v5 = 6;
            Sound_PlayEffect(SEQ_SE_DP_CON_021_sseq);
        } else {
            v0->state = 3;
            Sound_PlayEffect(SEQ_SE_DP_CON_001_sseq);
            break;
        }

        contest_competition_02241B3C(v0->competition, v1->contestantID, v5, &v0->animationDone);
    }
        v0->state++;
        break;
    case 2:
        if (v0->animationDone == 1) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        if (v1->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v1->messageID, v1->messageArg, &v1->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 6:
        v0->state++;
    case 7:
        if (v0->syncPacket.messages.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID, &v0->syncPacket.messages.messageParams, &v0->syncPacket.performanceOrder);
            v0->state++;
        } else {
            v0->state = 9;
        }
        break;
    case 8:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 9:
        v0->state++;
    case 10:
        if (v0->syncPacket.messages.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID2, &v0->syncPacket.messages.messageParams2, NULL);
            v0->state++;
        } else {
            v0->state = 12;
        }
        break;
    case 11:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 12:
        v0->state++;
    case 13:
        v0->voltage = v1->previousScore;
        v0->state++;
        break;
    case 14:
        if (v0->voltage < v1->score) {
            v0->voltage += 10;
            contest_competition_02241F34(&v0->competition->scene, v2, v3, v0->voltage);
        } else {
            v0->state = 16;
            break;
        }

        v0->state++;
        break;
    case 15:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 16:
        v0->orderIndex++;

        if ((v0->orderIndex < 4) && (v0->syncPacket.performanceOrder.order[v0->orderIndex] != 4)) {
            v0->state = 13;
        } else {
            v0->state++;
        }
        break;
    case 17:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_0224595C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245974(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v2->contestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_022459D4, v1, 30000);
}

static void contest_competition_022459D4(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0:
        v0->score = v1->previousScore;
        v0->state++;
        break;
    case 1:
        if (v1->messageID != 0) {
            contest_competition_02242E9C(v0->competition, v1->messageID, v1->messageArg, &v1->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 3;
        }
        break;
    case 2:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 3:
        v0->state++;
    case 4:
        if (v0->syncPacket.messages.actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID, &v0->syncPacket.messages.messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 6;
        }
        break;
    case 5:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 6:
        v0->state++;
    case 7:
        if (v0->syncPacket.messages.actingMessagesID2 != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->syncPacket.messages.actingMessagesID2, &v0->syncPacket.messages.messageParams2, NULL);
            v0->state++;
        } else {
            v0->state = 9;
        }
        break;
    case 8:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 9:
        v0->state++;
    case 10:
        v0->state++;
    case 11:
        if (v0->score < v1->score) {
            v0->score += 10;
            contest_competition_02241F34(&v0->competition->scene, v0->contestantID, v0->contestantCount, v0->score);
        } else {
            v0->state = 13;
        }

        v0->state++;
        break;
    case 12:
        v0->timer++;

        if (v0->timer > 2) {
            v0->timer = 0;
            v0->state--;
        }
        break;
    case 13:
        v0->state++;
    case 14:
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245B48(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245B60(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingScoreUpdateTask *v1;
    ActingSyncPacket *v2 = param3;

    v1 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreUpdateTask));
    MI_CpuClear8(v1, sizeof(ActingScoreUpdateTask));

    v1->competition = v0;
    v1->header = *param2;
    v1->contestantID = v0->scene.contestData->playerContestantID;
    v1->contestantCount = v2->contestantCount;
    v1->syncPacket = *v2;

    SysTask_Start(contest_competition_02245BC8, v1, 30000);
}

static void contest_competition_02245BC8(SysTask *param0, void *param1)
{
    ActingScoreUpdateTask *v0 = param1;
    ActingPerformance *v1 = &v0->syncPacket.turnState.performances[v0->contestantID];

    switch (v0->state) {
    case 0: {
        ActingMessageParams v3;

        u32 actingMessagesID = contest_competition_0224314C(v0->contestantID, v1->score, &v3);
        contest_competition_02242E5C(v0->competition, actingMessagesID, &v3, NULL);
        v0->state++;
    } break;
    case 1:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->state++;
        break;
    default:
        contest_competition_0224F26C(&v0->competition->packetQueue, &v0->header, NULL, 0);
        Heap_Free(v0);
        SysTask_Done(param0);
        return;
    }
}

static int contest_competition_02245C4C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245C60(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingSyncPacket *v1 = param3;
    ActingScoreGaugeDisplayTask *v2 = Heap_Alloc(HEAP_ID_21, sizeof(ActingScoreGaugeDisplayTask));
    MI_CpuClear8(v2, sizeof(ActingScoreGaugeDisplayTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;

    SysTask_Start(contest_competition_02245CA4, v2, 30000);
}

static void contest_competition_02245CA4(SysTask *param0, void *param1)
{
    ActingScoreGaugeDisplayTask *v0 = param1;

    int v1, v2;

    switch (v0->state) {
    case 0:
        contest_competition_022431A0(v0->competition, 0, 0, 70, 0, &v0->animationDone);
        v0->state++;
        break;
    case 1: {
        int v3;

        for (v3 = 0; v3 < 4; v3++) {
            v0->colorTasks[v3] = contest_competition_0224145C(v0->competition, v0->competition->matchState.contestantOrder[v3]);
            contest_competition_0224331C(v0->competition, v0->competition->matchState.contestantOrder[v3], v3, &v0->contestantIDs[v3], v0->colorTasks[v3]);
        }
    }
        v0->state++;
        break;
    case 2:
        v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if ((v0->contestantIDs[v1] == 0) && (contest_competition_022414BC(v0->colorTasks[v1]) == 0)) {
                v2++;
            }
        }

        if (v2 == 4) {
            for (v1 = 0; v1 < 4; v1++) {
                contest_competition_02241494(v0->colorTasks[v1]);
            }

            v0->state++;
        }
        break;
    case 3:
    default:
        if (v0->animationDone == 1) {
            contest_competition_0224F26C(v0->packetQueue, &v0->header, NULL, 0);
            Heap_Free(v0);
            SysTask_Done(param0);
            return;
        }

        break;
    }
}

static int contest_competition_02245DA4(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(&v0->packetQueue, 0xff, param2, param3, sizeof(ActingMatchState));
    return v1;
}

static void contest_competition_02245DBC(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingMatchState *v1 = param3;
    v0->matchState = *v1;

    contest_competition_02241EF0(&v0->scene);
    contest_competition_022430F8(&v0->scene);
    contest_competition_02242FE8(v0);
    contest_competition_02241428(v0);
    contest_competition_0224F26C(&v0->packetQueue, param2, NULL, 0);
}

static int contest_competition_02245E00(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    ActingCompetition *v0 = param1;
    int v1 = contest_competition_0224F1F8(param0, 0xff, param2, param3, sizeof(ActingSyncPacket));
    return v1;
}

static void contest_competition_02245E14(ContestPacketQueue *param0, void *param1, const ContestPacketHeader *param2, void *param3)
{
    ActingCompetition *v0 = param1;
    ActingSyncPacket *v1 = param3;
    ActingMessageDelayTask *v2 = Heap_Alloc(HEAP_ID_21, sizeof(ActingMessageDelayTask));
    MI_CpuClear8(v2, sizeof(ActingMessageDelayTask));

    v2->competition = v0;
    v2->header = *param2;
    v2->packetQueue = param0;
    v2->contestantID = v1->contestantID;
    v2->messageParams = v1->messages.messageParams;
    v2->actingMessagesID = v1->messages.actingMessagesID;
    v2->messageFlag = v1->messages.messageFlag;
    v2->delay = v1->messages.delay;

    SysTask_Start(contest_competition_02245E8C, v2, 30000);
}

static void contest_competition_02245E8C(SysTask *param0, void *param1)
{
    ActingMessageDelayTask *v0 = param1;

    switch (v0->state) {
    case 0:
        if (v0->actingMessagesID != ACTING_COMPETITION_MESSAGE_NONE) {
            contest_competition_02242E5C(v0->competition, v0->actingMessagesID, &v0->messageParams, NULL);
            v0->state++;
        } else {
            v0->state = 100;
        }
        break;
    case 1:
        if (contest_competition_02242ECC(v0->competition) == 0) {
            v0->state++;
        }
        break;
    case 2:
        v0->timer++;

        if (v0->messageFlag == 1) {
            v0->state++;
        } else if (v0->timer >= v0->delay) {
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
