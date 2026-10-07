#ifndef POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02247A48_H
#define POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02247A48_H

#include "constants/contests.h"

#include "contest_competition/struct_contest_competition_0223D60C.h"
#include "contest_competition/struct_contest_competition_022476F8.h"
#include "contest_competition/struct_contest_competition_02247A48_sub1.h"
#include "contest_competition/struct_contest_competition_02247A48_sub2.h"
#include "contest_competition/struct_contest_competition_02249260.h"
#include "contest_competition/struct_contest_competition_0224B09C.h"
#include "contest_competition/struct_contest_competition_0224F30C.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *unk_00;
    SysTask *unk_04;
    G3DPipelineBuffers *unk_08;
    UnkStruct_contest_competition_022476F8 unk_0C;
    UnkStruct_contest_competition_02247A48_sub1 unk_D2;
    UnkStruct_contest_competition_02249260 unk_E0;
    UnkStruct_contest_competition_02247A48_sub2 unk_F1[4];
    u16 unk_4F2;
    u16 unk_4F4;
    u8 unk_4F6;
    u8 unk_4F7;
    UnkStruct_contest_competition_0224F30C unk_4F8;
    UnkStruct_contest_competition_0223D60C unk_F0C;
    u8 unk_F14;
    UnkStruct_contest_competition_0224B09C unk_F18[CONTEST_NUM_PARTICIPANTS];
    u8 unk_F58;
    u8 unk_F59;
    u8 unk_F5A;
    u8 unk_F5B;
    u8 unk_F5C;
    u8 unk_F5D;
    u8 unk_F5E;
    u8 unk_F5F;
} UnkStruct_contest_competition_02247A48;

#endif // POKEPLATINUM_STRUCT_CONTEST_COMPETITION_02247A48_H
