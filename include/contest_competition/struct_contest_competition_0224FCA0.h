#ifndef POKEPLATINUM_STRUCT_CONTEST_COMPETITION_0224FCA0_H
#define POKEPLATINUM_STRUCT_CONTEST_COMPETITION_0224FCA0_H

#include "contest_competition/struct_contest_competition_0224F30C.h"
#include "contest_competition/struct_contest_competition_0224FCA0_sub1.h"
#include "contest_competition/struct_contest_competition_0224FCA0_sub2.h"
#include "contest_competition/struct_contest_competition_0224FCA0_sub3.h"
#include "contest_competition/struct_contest_competition_0224FECC.h"
#include "contest_competition/struct_contest_competition_022507C4.h"

#include "contest.h"
#include "g3d_pipeline.h"
#include "sys_task_manager.h"

typedef struct {
    Contest *unk_00;
    SysTask *unk_04;
    SysTask *unk_08;
    G3DPipelineBuffers *unk_0C;
    UnkStruct_contest_competition_022507C4 unk_10;
    UnkStruct_contest_competition_0224FCA0_sub1 unk_39A;
    UnkStruct_contest_competition_0224FCA0_sub2 unk_434;
    UnkStruct_contest_competition_0224FCA0_sub3 unk_446[4];
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
    UnkStruct_contest_competition_0224F30C unk_85C;
    UnkStruct_contest_competition_0224FECC unk_1270;
    u8 unk_1278;
    u8 unk_1279;
    u8 unk_127A;
    u8 unk_127B;
} UnkStruct_contest_competition_0224FCA0;

#endif // POKEPLATINUM_STRUCT_CONTEST_COMPETITION_0224FCA0_H
