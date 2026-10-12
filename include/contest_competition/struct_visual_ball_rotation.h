#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_ROTATION_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_ROTATION_H

#include "battle_anim/struct_ball_rotation_decl.h"
#include "contest_competition/struct_visual_competition.h"

typedef struct {
    VisualCompetition *competition;
    BallRotation *ballRotation;
    u8 state;
    u8 done;
    u8 counter;
} VisualBallRotation;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_ROTATION_H
