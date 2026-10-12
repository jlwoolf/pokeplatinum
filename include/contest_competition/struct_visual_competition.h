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
    Contest *unk_00;
    SysTask *unk_04;
    G3DPipelineBuffers *unk_08;
    VisualCompetitionScene unk_0C;
    VisualCompetitionScores unk_D2;
    VisualContestantInfo unk_E0;
    VisualPayloadBuffer unk_F1[4];
    u16 unk_4F2;
    u16 unk_4F4;
    u8 unk_4F6;
    u8 unk_4F7;
    ContestPacketQueue unk_4F8;
    VisualCompetitionTask unk_F0C;
    u8 unk_F14;
    DancePhotoSprite unk_F18[CONTEST_NUM_PARTICIPANTS];
    u8 unk_F58;
    u8 unk_F59;
    u8 unk_F5A;
    u8 unk_F5B;
    u8 unk_F5C;
    u8 unk_F5D;
    u8 unk_F5E;
    u8 unk_F5F;
} VisualCompetition;

#endif // POKEPLATINUM_STRUCT_VISUAL_COMPETITION_H
