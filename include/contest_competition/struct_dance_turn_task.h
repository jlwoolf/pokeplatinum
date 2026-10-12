#ifndef POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    s16 turn;
} DanceTurnTask;

#endif // POKEPLATINUM_STRUCT_DANCE_TURN_TASK_H
