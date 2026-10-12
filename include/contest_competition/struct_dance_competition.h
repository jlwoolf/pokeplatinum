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
    Contest *contest;
    SysTask *task;
    SysTask *vBlankTask;
    ParticleSystem *particleSystem;
    G3DPipelineBuffers *g3dPipeline;
    DanceCompetitionScene scene;
    DanceScoreState scoreState;
    DanceMoveState moveState;
    DancePayloadBuffer payloadBuffers[4];
    DanceContestant contestants[4];
    DanceContestantSprite contestantSprites[4];
    DanceSavedData savedData;
    DanceCamera camera;
    void *moveSelectScreen;
    u8 flag;
    u64 timestamp;
    u64 prevTimestamp;
    u32 frameCounter;
    u32 lastTick;
    u16 unused_1094;
    u16 handlerIndex;
    u8 flag2;
    ContestPacketQueue packetQueue;
    DancePacket contestantPackets[4];
    DancePacket movePackets[8];
    DanceCompetitionTask competitionTask;
    u8 initialized;
    u8 isReady;
    u8 contestRank;
} DanceCompetition;

#endif // POKEPLATINUM_STRUCT_DANCE_COMPETITION_H
