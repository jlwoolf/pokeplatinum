#ifndef POKEPLATINUM_FIELDMAP_021E22B0_H
#define POKEPLATINUM_FIELDMAP_021E22B0_H

#include "fieldmap/motion_blur.h"

typedef struct FieldMotionBlur {
    MotionBlur *motionBlur;
} FieldMotionBlur;

FieldMotionBlur *FieldMotionBlur_Start(int coeffA, int coeffB);
void FieldMotionBlur_Stop(FieldMotionBlur **fieldMotionBlur);

#endif // POKEPLATINUM_FIELDMAP_021E22B0_H
