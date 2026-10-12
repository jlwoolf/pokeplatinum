#ifndef POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    s8 row;
    u8 column;
    s8 stepDelay;
    s8 holdDelay;
} VisualBallCapsuleTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_BALL_CAPSULE_TASK_H
