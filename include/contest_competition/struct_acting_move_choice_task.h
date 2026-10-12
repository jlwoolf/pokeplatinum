#ifndef POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_move_choice.h"
#include "contest_competition/struct_acting_competition.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    ActingMoveChoice unk_10;
} ActingMoveChoiceTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MOVE_CHOICE_TASK_H
