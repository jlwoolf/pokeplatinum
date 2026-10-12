#include "footprint_stamp/footprint_stamp_comm.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "wifi_plaza_lobby/wifi_plaza_lobby_02231428.h"
#include "wifi_plaza_lobby/wifi_plaza_lobby_022324F0.h"
#include "footprint_stamp/footprint_stamp.h"
#include "footprint_stamp/struct_footprint_stamp_add_payload.h"
#include "footprint_stamp/struct_footprint_stamp_app_decl.h"
#include "footprint_stamp/struct_footprint_stamp_comm_state.h"
#include "footprint_stamp/struct_footprint_stamp_entry.h"

static void FootprintStampComm_HandleAdd(s32 param0, const void *param1, u32 param2, void *param3);
static void FootprintStampComm_HandleRemove(s32 param0, const void *param1, u32 param2, void *param3);
static void FootprintStampComm_HandleUpdate(s32 param0, const void *param1, u32 param2, void *param3);
static BOOL FootprintStampComm_IsValid(s32 param0, FootprintStampCommState *param1);

static const WiFiPlazaLobbyNetworkMessageHandler sCommHandlers[] = {
    { FootprintStampComm_HandleAdd, sizeof(FootprintStampAddPayload) },
    { FootprintStampComm_HandleRemove, 0x0 },
    { FootprintStampComm_HandleUpdate, sizeof(FootprintStampEntry) }
};

void FootprintStampComm_Init(FootprintStampApp *param0)
{
    WiFiPlazaLobby_Network_SetSubChannelMessageHandler(sCommHandlers, (NELEMS(sCommHandlers)), param0);
}

static BOOL FootprintStampComm_IsValid(s32 param0, FootprintStampCommState *param1)
{
    if (param1->localUserId == param0) {
        return 0;
    }

    if (param1->isActive == 0) {
        return 0;
    }

    if (WiFiPlazaLobby_Network_FindSubChannelPlayerIndex(param0) == 0xffffffff) {
        return 0;
    }

    return 1;
}

BOOL FootprintStampComm_SendEntry(const FootprintStampEntry *param0)
{
    if (WiFiPlazaLobby_Time_HasWifiError() == 1) {
        return 0;
    }

    WiFiPlazaLobby_Network_SendSubChannelMessage(2, param0, sizeof(FootprintStampEntry));
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

    FootprintStamp_ClearPlayerName(v0, WiFiPlazaLobby_Network_FindSubChannelPlayerIndex(param0));
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
