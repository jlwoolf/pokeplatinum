#ifndef POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_RESULT_H
#define POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_RESULT_H

typedef struct {
    union {
        struct {
            u32 scores[8];
            u8 ranks[8];
            u8 points[8];
        } performanceData;
        struct {
            u32 value;
            u8 score;
            u8 flag;
        } rawData;
    };
    u32 rngSeed;
    s16 delay;
    u8 moveIndex;
    u8 contestantID;
    u8 state;
    u8 contestRank;
} DancePerformanceResult;

#endif // POKEPLATINUM_STRUCT_DANCE_PERFORMANCE_RESULT_H
