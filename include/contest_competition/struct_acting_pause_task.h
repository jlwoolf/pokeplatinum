#ifndef POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u16 unk_0C;
    u8 unk_0E;
    u8 unk_0F;
} ActingPauseTask;

#endif // POKEPLATINUM_STRUCT_ACTING_PAUSE_TASK_H
