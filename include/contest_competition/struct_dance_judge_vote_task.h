#ifndef POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    DanceMessageArgs unk_14;
    u8 unk_1A;
    u8 unk_1B;
    u8 unk_1C;
} DanceJudgeVoteTask;

#endif // POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H
