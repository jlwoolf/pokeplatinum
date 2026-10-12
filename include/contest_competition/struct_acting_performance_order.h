#ifndef POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_ORDER_H
#define POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_ORDER_H

typedef struct {
    u8 contestantID;
    u8 order[4];
    u16 unused_06;
    u8 unused_08;
} ActingPerformanceOrder;

#endif // POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_ORDER_H
