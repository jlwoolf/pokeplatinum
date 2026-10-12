#ifndef POKEPLATINUM_STRUCT_DANCE_START_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_START_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_dance_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    DanceCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    s8 row;
    u8 column;
    s8 stepDelay;
    s8 holdDelay;
} DanceStartTask;

#endif // POKEPLATINUM_STRUCT_DANCE_START_TASK_H
