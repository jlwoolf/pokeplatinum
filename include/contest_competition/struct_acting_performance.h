#ifndef POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_H
#define POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_H

#include "contest_competition/struct_acting_message_params.h"

typedef struct {
    u16 moveID;
    u8 contestMoveEffect;
    u8 contestantID;
    u8 appealPoints;
    s16 unused_06;
    s8 excitement;
    u8 judgeID;
    u8 unused_0A;
    u8 unused_0B;
    ActingMessageParams messageParams;
    u8 messageID;
    u8 messageArg;
    u8 performed;
    s16 unused_16;
    s16 score;
    s16 previousScore;
    s16 previousTurnScore;
    s16 bonusScore;
    s16 secondaryBonus;
    u8 unused_22[4];
    u32 unused_28_0 : 1;
    u32 comboStarted : 1;
    u32 comboFailed : 1;
    u32 comboFlag : 1;
    u32 judgeAppealState : 2;
    u32 appealOrder : 2;
    u32 previousAppealState : 2;
    u32 previousAppealOrder : 2;
    u32 performedMoveEffect : 8;
    u32 : 12;
} ActingPerformance;

#endif // POKEPLATINUM_STRUCT_ACTING_PERFORMANCE_H
