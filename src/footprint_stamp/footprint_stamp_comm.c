#include "footprint_stamp/footprint_stamp_comm.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "overlay066/ov66_02231428.h"
#include "overlay066/ov66_022324F0.h"
#include "footprint_stamp/footprint_stamp.h"
#include "footprint_stamp/struct_footprint_stamp_add_payload.h"
#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_comm_state.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

static void FootprintStampComm_HandleAdd(s32 param0, const void *param1, u32 param2, void *param3);
static void FootprintStampComm_HandleRemove(s32 param0, const void *param1, u32 param2, void *param3);
static void FootprintStampComm_HandleUpdate(s32 param0, const void *param1, u32 param2, void *param3);
static BOOL FootprintStampComm_IsValid(s32 param0, FootprintStampCommState *param1);

static const UnkStruct_ov66_022589B4 sCommHandlers[] = {
    { FootprintStampComm_HandleAdd, sizeof(FootprintStampAddPayload) },
    { FootprintStampComm_HandleRemove, 0x0 },
    { FootprintStampComm_HandleUpdate, sizeof(FootprintStampEntry) }
};

void FootprintStampComm_Init(FootprintStampApp *param0)
{
    ov66_02232D60(sCommHandlers, (NELEMS(sCommHandlers)), param0);
}

static BOOL FootprintStampComm_IsValid(s32 param0, FootprintStampCommState *param1)
{
    if (param1->unk_04 == param0) {
        return 0;
    }

    if (param1->unk_00 == 0) {
        return 0;
    }

    if (ov66_02232B8C(param0) == 0xffffffff) {
        return 0;
    }

    return 1;
}

BOOL FootprintStampComm_SendEntry(const FootprintStampEntry *param0)
{
    if (ov66_02231760() == 1) {
        return 0;
    }

    ov66_02232EBC(2, param0, sizeof(FootprintStampEntry));
    return 1;
}

static void FootprintStampComm_HandleAdd(s32 param0, const void *param1, u32 param2, void *param3)
{
    FootprintStampApp *v0 = param3;
    FootprintStampCommState *v1 = FootprintStamp_GetCommState(v0);
    const FootprintStampAddPayload *v2 = param1;

    if (FootprintStampComm_IsValid(param0, v1) == 0) {
        return;
    }

    FootprintStamp_DrawPlayerName(v0, param0);
}

static void FootprintStampComm_HandleRemove(s32 param0, const void *param1, u32 param2, void *param3)
{
    FootprintStampApp *v0 = param3;
    FootprintStampCommState *v1 = FootprintStamp_GetCommState(v0);

    if (FootprintStampComm_IsValid(param0, v1) == 0) {
        return;
    }

    FootprintStamp_ClearPlayerName(v0, ov66_02232B8C(param0));
}

static void FootprintStampComm_HandleUpdate(s32 param0, const void *param1, u32 param2, void *param3)
{
    FootprintStampApp *v0 = param3;
    FootprintStampCommState *v1 = FootprintStamp_GetCommState(v0);
    const FootprintStampEntry *v2 = param1;

    if (FootprintStampComm_IsValid(param0, v1) == 0) {
        return;
    }

    FootprintStamp_AddEntry(v0, v2, param0);
}
