#ifndef POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H

#include "contest_competition/struct_acting_voltage_gauge_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    s8 timer;
    s8 unused_0E;
    ActingSyncPacket syncPacket;
    s16 voltage;
    u8 orderIndex;
    u8 animationDone;
    ActingVoltageGaugeTask *voltageGaugeTask;
} ActingVoltageAwardTask;

#endif // POKEPLATINUM_STRUCT_ACTING_VOLTAGE_AWARD_TASK_H
