#ifndef POKEPLATINUM_STRUCT_VISUAL_PHOTO_REVEAL_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_PHOTO_REVEAL_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *unk_00;
    ContestPacketHeader unk_04;
    ContestPacketQueue *unk_0C;
    u8 unk_10;
    u8 unk_11;
    s16 unk_12;
} VisualPhotoRevealTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_PHOTO_REVEAL_TASK_H
