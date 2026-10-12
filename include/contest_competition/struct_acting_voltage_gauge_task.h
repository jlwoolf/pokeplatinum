#ifndef POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H

#include "contest_competition/struct_acting_competition.h"

#include "sys_task_manager.h"

typedef struct {
    ActingCompetition *unk_00;
    SysTask *unk_04;
    u8 unk_08;
} ActingVoltageGaugeTask;

#endif // POKEPLATINUM_STRUCT_ACTING_VOLTAGE_GAUGE_TASK_H
