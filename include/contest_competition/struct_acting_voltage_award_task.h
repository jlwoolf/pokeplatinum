#ifndef POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H

#include "contest_competition/struct_acting_voltage_gauge_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"

typedef struct {
    ActingCompetition *unk_00;
    ContestPacketHeader unk_04;
    u8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    ActingSyncPacket unk_10;
    s16 unk_EE;
    u8 unk_F0;
    u8 unk_F1;
    ActingVoltageGaugeTask *unk_F4;
} ActingVoltageAwardTask;

#endif // POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H
