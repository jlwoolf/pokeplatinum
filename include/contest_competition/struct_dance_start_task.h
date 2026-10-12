#ifndef POKEPLATINUM_STRUCT_DANCE_START_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_START_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    s8 unk_11;
    u8 unk_12;
    s8 unk_13;
    s8 unk_14;
} DanceStartTask;

#endif // POKEPLATINUM_STRUCT_DANCE_START_TASK_H
