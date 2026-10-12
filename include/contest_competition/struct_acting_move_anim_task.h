#ifndef POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_TASK_H

#include "contest_competition/struct_acting_move_anim_args.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_message_params.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    u8 contestantID;
    u16 moveID;
    u8 timer;
    ActingSyncPacket syncPacket;
    ActingMessageParams messageParams;
    u8 actingMessagesID;
    ActingMessageParams messageParams2;
    u8 actingMessagesID2;
    ActingMoveAnimArgs animArgs;
} ActingMoveAnimTask;

#endif // POKEPLATINUM_STRUCT_ACTING_MOVE_ANIM_TASK_H
