#ifndef POKEPLATINUM_STRUCT_ACTING_CONTESTANT_COLOR_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_CONTESTANT_COLOR_TASK_H

#include "palette.h"
#include "sys_task_manager.h"

typedef struct {
    PaletteData *paletteData;
    SysTask *task;
    s16 targetColor;
    u8 contestantID;
    u8 colorState;
} ActingContestantColorTask;

#endif // POKEPLATINUM_STRUCT_ACTING_CONTESTANT_COLOR_TASK_H
