#ifndef POKEPLATINUM_STRUCT_DANCE_MOVE_DATA_H
#define POKEPLATINUM_STRUCT_DANCE_MOVE_DATA_H

typedef struct {
    s32 startX;
    s32 targetY;
    s32 savedX;
    s32 currentY;
    u8 state;
    union {
        struct {
            s16 velocity;
            s16 acceleration;
        } bounce;
        struct {
            s32 velocity1;
            s32 velocity2;
        } slide;
        struct {
            u32 angle;
            int angleVelocity1;
            int angleVelocity2;
            int xVelocity;
            int yVelocity;
        } arc;
    };
} DanceMoveData;

#endif // POKEPLATINUM_STRUCT_DANCE_MOVE_DATA_H
