#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H

#include "contest_competition/struct_acting_voltage_gauge_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u8 unk_0C;
    u8 contestantID;
    u8 unk_0E;
    s8 unk_0F;
    s8 unk_10;
    u8 unk_11;
    u8 unk_12;
    ActingSyncPacket unk_14;
    s16 unk_F2;
    s16 unk_F4;
    s16 unk_F6;
    u8 unk_F8;
    u8 unk_F9;
    ActingVoltageGaugeTask *unk_FC;
} ActingScoreUpdateTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H
