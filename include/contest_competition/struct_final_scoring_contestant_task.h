#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring.h"
#include "contest_competition/struct_final_scoring_message_args.h"

typedef struct {
    ContestFinalScoring *finalScoring;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 timer;
    FinalScoringMessageArgs messageArgs;
    u8 announcerMessagesID;
    u8 delay;
    u8 flag;
    u8 messageState;
} FinalScoringContestantTask;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H
