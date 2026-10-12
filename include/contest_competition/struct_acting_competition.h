#ifndef POKEPLATINUM_STRUCT_ACTING_COMPETITION_H
#define POKEPLATINUM_STRUCT_ACTING_COMPETITION_H

#include "contest_competition/struct_acting_competition_task.h"
#include "contest_competition/struct_acting_competition_scene.h"
#include "contest_competition/struct_acting_sync_packet.h"
#include "contest_competition/struct_acting_payload_buffer.h"
#include "contest_competition/struct_acting_match_state.h"
#include "contest_competition/struct_contest_packet_queue.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *contest;
    SysTask *task;
    G3DPipelineBuffers *g3dPipeline;
    ActingCompetitionScene scene;
    ActingMatchState matchState;
    ActingSyncPacket syncPacket;
    ActingPayloadBuffer payloadBuffers[4];
    void *moveMenu;
    u16 unused_7E8;
    u16 handlerIndex;
    u8 initialized;
    u32 unused_7F0;
    u8 unused_7F4[512];
    u8 unused_9F4[512];
    u8 unused_BF4;
    u8 unused_BF5;
    ContestPacketQueue packetQueue;
    ActingCompetitionTask competitionTask;
    u8 initialized2;
    u8 unused_1615;
    u8 contestantReady[4];
} ActingCompetition;

#endif // POKEPLATINUM_STRUCT_ACTING_COMPETITION_H
