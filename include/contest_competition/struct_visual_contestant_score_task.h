#ifndef POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    s8 unk_11;
    s8 unk_12;
    s8 unk_13;
    u16 unk_14;
} VisualContestantScoreTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_SCORE_TASK_H
