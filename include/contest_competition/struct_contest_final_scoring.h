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
    Contest *contest;
    SysTask *task;
    SysTask *vBlankTask;
    G3DPipelineBuffers *g3dPipeline;
    ContestFinalScoringScene scene;
    ContestFinalScoringScores scores;
    ContestFinalScoringResults results;
    FinalScoringPayloadBuffer payloadBuffers[4];
    void *paletteFadeTask;
    u16 unused_84C;
    u16 handlerIndex;
    u8 drawSprites;
    u8 window0Left;
    u8 window0Top;
    u8 window0Right;
    u8 window0Bottom;
    u8 window1Left;
    u8 window1Top;
    u8 window1Right;
    u8 window1Bottom;
    ContestPacketQueue packetQueue;
    ContestFinalScoringTask scoringTask;
    u8 scoringDone;
    u8 photoDone;
    u8 photoTimer;
    u8 enableHBlank;
} ContestFinalScoring;

#endif // POKEPLATINUM_STRUCT_CONTEST_FINAL_SCORING_H
