#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_MOVEMENT_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_MOVEMENT_H

#include "contest_competition/struct_visual_competition.h"

typedef struct {
    VisualCompetition *competition;
    fx32 scaleX;
    fx32 scaleY;
    u8 state;
    u8 done;
    u8 contestantID;
} VisualBallMovement;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_MOVEMENT_H
