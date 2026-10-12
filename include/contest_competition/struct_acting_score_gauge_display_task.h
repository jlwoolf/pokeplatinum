#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H

#include "contest_competition/struct_acting_contestant_color_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    ActingContestantColorTask *colorTasks[4];
    u8 state;
    u8 contestantCount;
    u8 unused_22;
    u8 contestantIDs[4];
    u8 animationDone;
} ActingScoreGaugeDisplayTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H
