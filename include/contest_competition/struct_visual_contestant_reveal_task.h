#ifndef POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_REVEAL_TASK_H
#define POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_REVEAL_TASK_H

#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_visual_message_args.h"
#include "contest_competition/struct_visual_competition.h"
#include "contest_competition/struct_contest_packet_queue.h"

typedef struct {
    VisualCompetition *competition;
    ContestPacketHeader header;
    ContestPacketQueue *packetQueue;
    u8 state;
    u8 contestantID;
    u8 timer;
    VisualMessageArgs messageArgs;
    u8 messageID;
    u8 delay;
    u8 flag;
} VisualContestantRevealTask;

#endif // POKEPLATINUM_STRUCT_VISUAL_CONTESTANT_REVEAL_TASK_H
