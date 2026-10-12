#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H

#include "contest_competition/struct_acting_contestant_color_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    ActingContestantColorTask *unk_10[4];
    u8 unk_20;
    u8 unk_21;
    u8 unk_22;
    u8 unk_23[4];
    u8 unk_27;
} ActingScoreGaugeDisplayTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_GAUGE_DISPLAY_TASK_H
