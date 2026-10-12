#ifndef POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H
#define POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H

#include "contest_competition/struct_acting_voltage_gauge_task.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_acting_competition.h"
#include "contest_competition/struct_acting_sync_packet.h"

typedef struct {
    ActingCompetition *competition;
    ContestPacketHeader header;
    u8 state;
    u8 contestantID;
    u8 contestantCount;
    s8 timer;
    s8 counter;
    u8 animationDone;
    u8 result;
    ActingSyncPacket syncPacket;
    s16 score;
    s16 bonusScore;
    s16 unused_F6;
    u8 animationDone2;
    u8 unused_F9;
    ActingVoltageGaugeTask *voltageGaugeTask;
} ActingScoreUpdateTask;

#endif // POKEPLATINUM_STRUCT_ACTING_SCORE_UPDATE_TASK_H
