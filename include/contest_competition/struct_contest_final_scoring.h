#ifndef POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_H
#define POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_H

#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_final_scoring_scores.h"
#include "contest_competition/struct_contest_final_scoring_results.h"
#include "contest_competition/struct_final_scoring_payload_buffer.h"
#include "contest_competition/struct_contest_final_scoring_task.h"
#include "contest_competition/struct_contest_final_scoring_scene.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *unk_00;
    SysTask *unk_04;
    SysTask *unk_08;
    G3DPipelineBuffers *unk_0C;
    ContestFinalScoringScene unk_10;
    ContestFinalScoringScores unk_39A;
    ContestFinalScoringResults unk_434;
    FinalScoringPayloadBuffer unk_446[4];
    void *unk_848;
    u16 unk_84C;
    u16 unk_84E;
    u8 unk_850;
    u8 unk_851;
    u8 unk_852;
    u8 unk_853;
    u8 unk_854;
    u8 unk_855;
    u8 unk_856;
    u8 unk_857;
    u8 unk_858;
    ContestPacketQueue unk_85C;
    ContestFinalScoringTask unk_1270;
    u8 unk_1278;
    u8 unk_1279;
    u8 unk_127A;
    u8 unk_127B;
} ContestFinalScoring;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_H
