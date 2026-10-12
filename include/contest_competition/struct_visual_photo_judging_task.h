#ifndef POKEPLATINUM_STRUCT_VISUAL_PHOTO_JUDGING_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_PHOTO_JUDGING_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 threshold1;
    u8 timer;
    u8 threshold2;
    u8 param;
    s16 prevX;
    s16 prevY;
    u8 judgingState;
    u8 flag;
} VisualPhotoJudgingTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_PHOTO_JUDGING_TASK_H
