#ifndef POKEPLATINUM_STRUCT_VISUAL_COMPETITION_H
#define POKEPLATINUM_STRUCT_VISUAL_COMPETITION_H

#include "constants/contests.h"

#include "contest_competition/struct_visual_competition_task.h"
#include "contest_competition/struct_visual_competition_scene.h"
#include "contest_competition/struct_visual_competition_scores.h"
#include "contest_competition/struct_visual_payload_buffer.h"
#include "contest_competition/struct_visual_contestant_info.h"
#include "contest_competition/struct_dance_photo_sprite.h"
#include "contest_competition/struct_contest_packet_queue.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *contest;
    SysTask *task;
    G3DPipelineBuffers *g3dPipeline;
    VisualCompetitionScene scene;
    VisualCompetitionScores scores;
    VisualContestantInfo contestantInfo;
    VisualPayloadBuffer payloadBuffers[4];
    u16 unused_4F2;
    u16 handlerIndex;
    u8 flag;
    u8 counter;
    ContestPacketQueue packetQueue;
    VisualCompetitionTask competitionTask;
    u8 initialized;
    DancePhotoSprite photoSprites[CONTEST_NUM_PARTICIPANTS];
    u8 window0Left;
    u8 window0Top;
    u8 window0Right;
    u8 window0Bottom;
    u8 window1Left;
    u8 window1Top;
    u8 window1Right;
    u8 window1Bottom;
} VisualCompetition;

#endif // POKEPLATINUM_STRUCT_VISUAL_COMPETITION_H
