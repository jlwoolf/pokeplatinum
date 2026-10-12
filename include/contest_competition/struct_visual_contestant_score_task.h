#ifndef POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    s8 x;
    s8 y;
    s8 z;
    u16 score;
} VisualContestantScoreTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H
