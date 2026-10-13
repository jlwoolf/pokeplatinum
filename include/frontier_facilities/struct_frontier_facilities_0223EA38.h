#ifndef POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223EA38_H
#define POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223EA38_H

// A linear scalar animation: current value, start, range, step count and
// elapsed steps.
typedef struct {
    int current;
    int start;
    int range;
    int elapsedSteps;
    int stepCount;
} FrontierFacilitiesLinearAnimation;

#endif // POKEPLATINUM_STRUCT_FRONTIER_FACILITIES_0223EA38_H
