#ifndef POKEPLATINUM_STRUCT_DANCE_JUDGE_TASK_H
#define POKEPLATINUM_STRUCT_DANCE_JUDGE_TASK_H

#include "contest_competition/struct_dance_competition.h"

typedef struct {
    DanceCompetition *competition;
    u8 state;
    u8 timer;
} DanceJudgeTask;

#endif // POKEPLATINUM_STRUCT_DANCE_JUDGE_TASK_H
