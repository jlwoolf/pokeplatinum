#ifndef POKEPLATINUM_STRUCT_DANCE_COMPETITION_H
#define POKEPLATINUM_STRUCT_DANCE_COMPETITION_H

#include "contest_competition/struct_dance_competition_task.h"
#include "contest_competition/struct_dance_competition_scene.h"
#include "contest_competition/struct_dance_contestant.h"
#include "contest_competition/struct_dance_contestant_sprite.h"
#include "contest_competition/struct_dance_camera.h"
#include "contest_competition/struct_dance_saved_data.h"
#include "contest_competition/struct_dance_score_state.h"
#include "contest_competition/struct_dance_move_state.h"
#include "contest_competition/struct_dance_payload_buffer.h"
#include "contest_competition/struct_dance_packet.h"
#include "contest_competition/struct_contest_packet_queue.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "particle_system.h"
#include "sys_task_manager.h"

typedef struct DanceCompetition_t {
    Contest *unk_00;
    SysTask *unk_04;
    SysTask *unk_08;
    ParticleSystem *unk_0C;
    G3DPipelineBuffers *unk_10;
    DanceCompetitionScene unk_14;
    DanceScoreState unk_A3C;
    DanceMoveState unk_A6C;
    DancePayloadBuffer unk_AA1[4];
    DanceContestant unk_EA4[4];
    DanceContestantSprite unk_FC8[4];
    DanceSavedData unk_1050;
    DanceCamera unk_1064;
    void *unk_1074;
    u8 unk_1078;
    u64 unk_107C;
    u64 unk_1084;
    u32 unk_108C;
    u32 unk_1090;
    u16 unk_1094;
    u16 unk_1096;
    u8 unk_1098;
    ContestPacketQueue unk_109C;
    DancePacket unk_1AB0[4];
    DancePacket unk_1AD4[8];
    DanceCompetitionTask unk_1B1C;
    u8 unk_1B24;
    u8 unk_1B25;
    u8 unk_1B26;
} DanceCompetition;

#endif // POKEPLATINUM_STRUCT_DANCE_COMPETITION_H
