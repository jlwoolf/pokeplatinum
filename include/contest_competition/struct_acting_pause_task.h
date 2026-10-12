#ifndef POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u16 timer;
    u8 unused_0E;
    u8 state;
} ActingPauseTask;

#endif // POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H
