#ifndef POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_move_choice.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    u8 contestantID;
    u8 timer;
    ActingMoveChoice moveChoice;
} ActingMoveChoiceTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H
