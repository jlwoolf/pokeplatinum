#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_SHOW_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_SHOW_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_visual_ball_capsule.h"
#include "contest_competition/struct_visual_ball_rotation.h"
#include "contest_competition/struct_visual_ball_movement.h"
#include "contest_competition/struct_visual_ball_appeal.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 state;
    u8 unk_11;
    VisualBallCapsule unk_14;
    VisualBallRotation unk_2C;
    VisualBallMovement unk_38;
    VisualBallAppeal unk_48;
} VisualBallCapsuleShowTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_SHOW_TASK_H
