#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_APPEAL_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_APPEAL_H

#include "contest_competition/struct_visual_competition.h"

typedef struct {
    VisualCompetition *competition;
    s32 x;
    s32 y;
    u8 state;
    u8 done;
    u8 counter;
    u8 timer;
} VisualBallAppeal;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_APPEAL_H
