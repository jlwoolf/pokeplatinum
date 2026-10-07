#include "contest_competition/contest_competition_02252CEC.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/contest_competition_0224A0FC.h"
#include "contest_competition/struct_contest_competition_02246F24.h"
#include "contest_competition/struct_contest_competition_02247A48.h"
#include "contest_competition/struct_contest_competition_0224DF54.h"
#include "contest_competition/struct_contest_competition_0224EDE0.h"
#include "contest_competition/struct_contest_competition_0224F30C.h"
#include "contest_competition/struct_contest_competition_0224FCA0.h"

#include "contest.h"

void contest_competition_02252CEC(int param0, int param1, void *param2, void *param3)
{
    Contest *v0 = param3;
    UnkStruct_contest_competition_0224F30C *v1;

    if (v0->activeAppID == 0) {
        UnkStruct_contest_competition_02247A48 *v2;
        v2 = v0->appContext;
        v1 = &v2->unk_4F8;
    } else if (v0->activeAppID == 1) {
        UnkStruct_contest_competition_0224DF54 *v3;
        v3 = v0->appContext;
        v1 = &v3->unk_109C;
    } else if (v0->activeAppID == 2) {
        UnkStruct_contest_competition_02246F24 *v4;
        v4 = v0->appContext;
        v1 = &v4->unk_BF8;
    } else if (v0->activeAppID == 3) {
        UnkStruct_contest_competition_0224FCA0 *v5;
        v5 = v0->appContext;
        v1 = &v5->unk_85C;
    } else {
        GF_ASSERT(FALSE);
        return;
    }

    GF_ASSERT(param1 <= 512);
    GF_ASSERT(v1->unk_A11[param0] == 0);

    MI_CpuCopy8(param2, v1->unk_210[param0], param1);
    v1->unk_A11[param0] = 1;
}

void contest_competition_02252D7C(int param0, int param1, void *param2, void *param3)
{
    Contest *v0 = param3;
    UnkStruct_contest_competition_0224DF54 *v1 = v0->appContext;
    UnkStruct_contest_competition_0224EDE0 *v2 = param2;

    contest_competition_0224B20C(v1, v2);
}
