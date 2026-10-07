#ifndef POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02246F24_H
#define POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02246F24_H

#include "contest_competition/struct_contest_competition_0223BCE8.h"
#include "contest_competition/struct_contest_competition_0223F88C.h"
#include "contest_competition/struct_contest_competition_02246F24_sub1.h"
#include "contest_competition/struct_contest_competition_02246F24_sub2.h"
#include "contest_competition/struct_contest_competition_022472F8.h"
#include "contest_competition/struct_contest_competition_0224F30C.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *unk_00;
    SysTask *unk_04;
    G3DPipelineBuffers *unk_08;
    UnkStruct_contest_competition_0223F88C unk_0C;
    UnkStruct_contest_competition_022472F8 unk_220;
    UnkStruct_contest_competition_02246F24_sub1 unk_304;
    UnkStruct_contest_competition_02246F24_sub2 unk_3E2[4];
    void *unk_7E4;
    u16 unk_7E8;
    u16 unk_7EA;
    u8 unk_7EC;
    u32 unk_7F0;
    u8 unk_7F4[512];
    u8 unk_9F4[512];
    u8 unk_BF4;
    u8 unk_BF5;
    UnkStruct_contest_competition_0224F30C unk_BF8;
    UnkStruct_contest_competition_0223BCE8 unk_160C;
    u8 unk_1614;
    u8 unk_1615;
    u8 unk_1616[4];
} UnkStruct_contest_competition_02246F24;

#endif // POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02246F24_H
