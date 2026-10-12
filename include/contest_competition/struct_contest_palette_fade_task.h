#ifndef POKEPLATINUM_STRUCT_CONTEST_PALETTE_FADE_TASK_H
#define POKEPLATINUM_STRUCT_CONTEST_PALETTE_FADE_TASK_H

#include "palette.h"
#include "sys_task_manager.h"

typedef struct {
    SysTask *task;
    PaletteData *paletteData;
    s32 timer;
    const u16 *durations;
    u8 stepCount;
    u8 currentStep;
    u8 repeatCount;
} ContestPaletteFadeTask;

#endif // POKEPLATINUM_STRUCT_CONTEST_PALETTE_FADE_TASK_H
