#include "global_terminal/global_terminal_0222BC4C.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "global_terminal/global_terminal_0222B008.h"
#include "global_terminal/struct_global_terminal_0222B960.h"
#include "global_terminal/struct_global_terminal_0222BC4C.h"
#include "global_terminal/struct_global_terminal_0222BC4C_1.h"
#include "global_terminal/struct_global_terminal_0222BC4C_2.h"
#include "global_terminal/struct_global_terminal_0222BC90.h"
#include "global_terminal/struct_global_terminal_0222BCD0.h"
#include "global_terminal/struct_global_terminal_0222BCF8.h"
#include "global_terminal/struct_global_terminal_0222BCF8_sub1.h"
#include "global_terminal/struct_global_terminal_0222BCF8_sub1_sub1.h"
#include "global_terminal/struct_global_terminal_0222BD64.h"
#include "global_terminal/struct_global_terminal_0222BD88.h"
#include "global_terminal/struct_global_terminal_0222BDAC.h"
#include "global_terminal/struct_global_terminal_0222BDAC_1.h"
#include "global_terminal/struct_global_terminal_0222BDC8.h"
#include "global_terminal/struct_global_terminal_0222BE00.h"
#include "global_terminal/struct_global_terminal_0222BE00_sub1.h"
#include "global_terminal/struct_global_terminal_0222BE20.h"
#include "global_terminal/struct_global_terminal_0222BEB8.h"
#include "global_terminal/struct_global_terminal_0222BED8.h"
#include "global_terminal/struct_global_terminal_0222BED8_sub1.h"
#include "overlay062/struct_ov62_02239DA4_sub1.h"
#include "overlay062/struct_ov62_0223DF10.h"

#include "gds.h"
#include "savedata.h"

int GlobalTerminalGds_HandleProfilePhoto(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalProfilePhotoResult *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalProfilePhotoResult *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_HandleProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalProfilePhotoList *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalProfilePhotoList *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_GetProfilePhotoList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalProfilePhoto **param1, int param2)
{
    GlobalTerminalGdsResponse *v0;
    GlobalTerminalProfilePhotoList *v1;
    GlobalTerminalProfilePhotoEntry *v2;
    int v3, v4;

    v0 = ov61_0222DE80();
    v1 = (GlobalTerminalProfilePhotoList *)(v0->unk_04);
    v4 = v1->unk_00;

    if (v4 > param2) {
        v4 = param2;
    }

    v2 = (GlobalTerminalProfilePhotoEntry *)(v1->unk_04);

    for (v3 = 0; v3 < v4; v3++) {
        param1[v3] = &v2[v3].unk_0C;
    }

    for (; v3 < param2; v3++) {
        param1[v3] = NULL;
    }

    return v4;
}

int GlobalTerminalGds_HandleProfileBox(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalProfileBoxResult *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalProfileBoxResult *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_HandleBox(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalBoxList *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalBoxList *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_GetBoxList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalProfileBox **param1, int param2)
{
    GlobalTerminalGdsResponse *v0;
    GlobalTerminalBoxList *v1;
    GlobalTerminalBoxEntry *v2;
    int v3, v4;

    v0 = ov61_0222DE80();
    v1 = (GlobalTerminalBoxList *)(v0->unk_04);

    v4 = v1->unk_00;

    if (v4 > param2) {
        v4 = param2;
        GF_ASSERT(FALSE);
    }

    v2 = (GlobalTerminalBoxEntry *)(v1->unk_04);

    for (v3 = 0; v3 < v4; v3++) {
        param1[v3] = &v2[v3].unk_10;
    }

    for (; v3 < param2; v3++) {
        param1[v3] = NULL;
    }

    return v4;
}

int GlobalTerminalGds_HandlePlayTime(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalPlayTimeResult *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalPlayTimeResult *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
    default:
        break;
    }

    return v1;
}

void GlobalTerminalGds_GetPlayTime(UnkStruct_ov62_022349A8 *param0, UnkStruct_ov62_0223DF10 **param1)
{
    GlobalTerminalGdsResponse *v0 = ov61_0222DE80();
    GlobalTerminalPlayTimeResult *v1 = (GlobalTerminalPlayTimeResult *)(v0->unk_04);

    *param1 = &v1->unk_00;
}

int GlobalTerminalGds_HandlePlayTimeProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalPlayTimeProfile *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalPlayTimeProfile *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
    default:
        break;
    }

    return v1;
}

void GlobalTerminalGds_GetPlayTimeProfile(UnkStruct_ov62_022349A8 *param0, GlobalTerminalPlayTimeData **param1, GlobalTerminalPlayTimeDataAlt **param2)
{
    GlobalTerminalGdsResponse *v0 = ov61_0222DE80();
    GlobalTerminalPlayTimeProfile *v1 = (GlobalTerminalPlayTimeProfile *)(v0->unk_04);

    *param1 = &v1->unk_00;
    *param2 = &v1->unk_558;
}

int GlobalTerminalGds_HandleBattleRecording(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalBattleRecordingResult *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalBattleRecordingResult *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
    default:
        break;
    case 6:
        break;
    case 7:
        break;
    }

    return v1;
}

u64 GlobalTerminalGds_GetBattleRecording(UnkStruct_ov62_022349A8 *param0)
{
    GlobalTerminalGdsResponse *v0 = ov61_0222DE80();
    GlobalTerminalBattleRecordingResult *v1 = (GlobalTerminalBattleRecordingResult *)(v0->unk_04);

    return v1->unk_00;
}

int GlobalTerminalGds_HandleRecord(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalRecordList *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalRecordList *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_GetRecordList(UnkStruct_ov62_022349A8 *param0, GlobalTerminalRecord **param1, int param2)
{
    GlobalTerminalGdsResponse *v0;
    GlobalTerminalRecordList *v1;
    GlobalTerminalRecordEntry *v2;
    int v3, v4;

    v0 = ov61_0222DE80();
    v1 = (GlobalTerminalRecordList *)(v0->unk_04);

    v4 = v1->unk_00;

    if (v4 > param2) {
        v4 = param2;
        GF_ASSERT(FALSE);
    }

    v2 = (GlobalTerminalRecordEntry *)(v1->unk_04);

    for (v3 = 0; v3 < v4; v3++) {
        param1[v3] = &v2[v3].unk_0C;

        if (v2[v3].unk_04 != param1[v3]->unk_80.unk_58) {
            param1[v3]->unk_80.unk_58 = v2[v3].unk_04;
            param1[v3]->unk_80.unk_60.unk_00 = SaveData_CalculateChecksum(param0->saveData, &param1[v3]->unk_80, sizeof(GlobalTerminalRecordAltData) - (sizeof(UnkStruct_ov62_02239DA4_sub1)) - sizeof(v2[v3].unk_04));
        }
    }

    for (; v3 < param2; v3++) {
        param1[v3] = NULL;
    }

    return v4;
}

int GlobalTerminalGds_HandleRecordAlt(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    GlobalTerminalRecordAltResult *v0;
    int v1 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = (GlobalTerminalRecordAltResult *)(param1->unk_04);
        v1 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
    default:
        break;
    }

    return v1;
}

int GlobalTerminalGds_GetRecordAlt(UnkStruct_ov62_022349A8 *param0, GlobalTerminalRecordAlt **param1)
{
    GlobalTerminalGdsResponse *v0 = ov61_0222DE80();
    GlobalTerminalRecordAltResult *v1 = (GlobalTerminalRecordAltResult *)(v0->unk_04);

    *param1 = &v1->unk_0C;

    if (v1->unk_04 != v1->unk_0C.unk_80.unk_58) {
        v1->unk_0C.unk_80.unk_58 = v1->unk_04;
        (*param1)->unk_80.unk_60.unk_00 = SaveData_CalculateChecksum(param0->saveData, &(*param1)->unk_80, sizeof(GlobalTerminalRecordAltData) - (sizeof(UnkStruct_ov62_02239DA4_sub1)) - sizeof(v1->unk_04));
    }

    return v1->unk_04;
}

int GlobalTerminalGds_HandleRecordAlt2(UnkStruct_ov62_022349A8 *param0, GlobalTerminalGdsResponse *param1)
{
    int v0 = 0;

    switch (param1->unk_02) {
    case 0:
        v0 = 1;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
    default:
        break;
    }

    return v0;
}
