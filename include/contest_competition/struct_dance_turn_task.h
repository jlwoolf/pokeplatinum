#ifndef POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11;
    s16 unk_12;
} DanceTurnTask;

#endif // POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H
