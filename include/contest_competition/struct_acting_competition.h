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
    Contest *unk_00;
    SysTask *unk_04;
    G3DPipelineBuffers *unk_08;
    ActingCompetitionScene unk_0C;
    ActingMatchState unk_220;
    ActingSyncPacket unk_304;
    ActingPayloadBuffer unk_3E2[4];
    void *unk_7E4;
    u16 unk_7E8;
    u16 unk_7EA;
    u8 unk_7EC;
    u32 unk_7F0;
    u8 unk_7F4[512];
    u8 unk_9F4[512];
    u8 unk_BF4;
    u8 unk_BF5;
    ContestPacketQueue unk_BF8;
    ActingCompetitionTask unk_160C;
    u8 unk_1614;
    u8 unk_1615;
    u8 unk_1616[4];
} ActingCompetition;

#endif // POKEPLATINUM_STRUCT_ACTING_COMPETITION_H
