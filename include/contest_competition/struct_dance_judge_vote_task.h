#ifndef POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_message_args.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 timer;
    DanceMessageArgs messageArgs;
    u8 messageID;
    u8 delay;
    u8 flag;
} DanceJudgeVoteTask;

#endif // POKEPLATINUM_STRUCT_DANCE_JUDGE_VOTE_TASK_H
