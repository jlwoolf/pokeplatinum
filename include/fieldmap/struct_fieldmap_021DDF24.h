#ifndef POKEPLATINUM_STRUCT_FIELDMAP_021DDF24_H
#define POKEPLATINUM_STRUCT_FIELDMAP_021DDF24_H

#include "constants/graphics.h"

#include "fieldmap/linear_interpolation_task_s32.h"

typedef struct BrightnessFadeTask {
    LinearInterpolationTaskS32 interpolationTask;
    enum DSScreen screen;
} BrightnessFadeTask;

#endif // POKEPLATINUM_STRUCT_FIELDMAP_021DDF24_H
