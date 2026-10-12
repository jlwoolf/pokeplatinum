#ifndef POKEPLATINUM_STRUCT_VISUAL_PHOTO_DROP_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_PHOTO_DROP_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    s32 x;
    s32 y;
} VisualPhotoDropTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_PHOTO_DROP_TASK_H
