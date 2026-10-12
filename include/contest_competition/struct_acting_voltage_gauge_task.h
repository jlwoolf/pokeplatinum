#ifndef POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H

#include "contest_competition/struct_acting_competition.h"

#include "sys_task_manager.h"

typedef struct {
    ActingCompetition *competition;
    SysTask *task;
    u8 state;
} ActingVoltageGaugeTask;

#endif // POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H
