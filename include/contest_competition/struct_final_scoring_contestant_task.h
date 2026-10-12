#ifndef POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H
#define POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring.h"
#include "contest_competition/struct_final_scoring_message_args.h"

typedef struct {
    ContestFinalScoring *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    FinalScoringMessageArgs unk_14;
    u8 announcerMessagesID;
    u8 unk_1B;
    u8 unk_1C;
    u8 unk_1D;
} FinalScoringContestantTask;

#endif // POKEPLATINUM_STRUCT_FINAL_SCORING_CONTESTANT_TASK_H
