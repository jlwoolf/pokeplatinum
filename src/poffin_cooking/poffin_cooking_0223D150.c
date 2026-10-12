#include "poffin_cooking/poffin_cooking_0223D150.h"

#include <nitro.h>
#include <string.h>

#include "poffin_cooking/poffin_cooking.h"
#include "poffin_cooking/poffin_cooking_0223D144.h"
#include "poffin_cooking/poffin_cooking_0223D4CC.h"
#include "poffin_cooking/poffin_cooking_0223F7F4.h"
#include "poffin_cooking/struct_poffin_cooking_app.h"
#include "poffin_cooking/struct_poffin_cooking_participant.h"
#include "poffin_cooking/struct_poffin_cooking_berry_packet.h"
#include "poffin_cooking/struct_poffin_cooking_berry_item.h"
#include "poffin_cooking/struct_poffin_cooking_touch_input.h"
#include "poffin_cooking/struct_poffin_cooking_blend_state.h"
#include "poffin_cooking/struct_poffin_cooking_result.h"

#include "communication_information.h"
#include "communication_system.h"
#include "trainer_info.h"

void poffin_cooking_0223D150(PoffinCookingApp *param0, TrainerInfo *param1)
{
    int v0;
    int v1;

    if (param0->isMultiplayer == 1) {
        param0->playerCount = CommSys_ConnectedCount();
    } else {
        param0->playerCount = 1;
    }

    param0->comm = poffin_cooking_0223D4CC(poffin_cooking_0223D144(), poffin_cooking_0223D14C(), param0, param0->isMultiplayer, param0->heapID);
    memset(param0->session.playerNetIDs, 4, sizeof(u8) * 4);

    if (param0->isMultiplayer == 1) {
        v0 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            param0->session.trainerInfos[v1] = CommInfo_TrainerInfo(v1);

            if (param0->session.trainerInfos[v1] != NULL) {
                param0->session.playerNetIDs[v0] = v1;
                v0++;
            }
        }
    } else {
        param0->session.playerNetIDs[0] = 0;
        param0->session.trainerInfos[0] = param1;
    }
}

void poffin_cooking_0223D1EC(PoffinCookingApp *param0)
{
    poffin_cooking_0223D558(param0->comm);
    param0->comm = NULL;
}

void poffin_cooking_0223D204(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    poffin_cooking_0223B774(v0, 3);
}

void poffin_cooking_0223D210(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    poffin_cooking_0223B77C(v0, 8);
}

void poffin_cooking_0223D21C(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;

    memcpy(&v0->session.receivedBerryPacket, param2, param1);
    v0->session.participants[0].blendState = v0->session.receivedBerryPacket.blendState;
    poffin_cooking_0223B774(v0, 5);
}

void poffin_cooking_0223D258(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    int v1;
    int v2;

    if (poffin_cooking_0223D570(v0->comm) == 0) {
        memcpy(&v0->session.peerBerries[param0], param2, param1);
        v0->session.peerBerryReceived[param0] = 1;
        v0->session.berryPacket.berries[param0] = v0->session.peerBerries[param0];
        v2 = 0;

        for (v1 = 0; v1 < 4; v1++) {
            if (v0->session.peerBerryReceived[v1] == 1) {
                v2++;
            }
        }

        if (v2 >= v0->playerCount) {
            poffin_cooking_0223FF44(&v0->simulation, &v0->session.berryPacket.blendState, v0->playerCount);
            poffin_cooking_0223D508(24, &v0->session.berryPacket, poffin_cooking_0223D4B4(), v0->comm);
        }
    }
}

void poffin_cooking_0223D2E8(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    PoffinCookingParticipant *v1;
    PoffinCookingBlendState *v2;
    BOOL v3;
    u8 v4;

    v1 = param2;
    v2 = &v1->blendState;

    if ((v0->session.participants[param0].blendState.releaseFlag == 1) && (v2->releaseFlag == 0) && (param0 == 0)) {
        v3 = 1;
        v4 = v0->session.participants[param0].blendState.direction;
    } else {
        v3 = 0;
    }

    memcpy(&v0->session.participants[param0], param2, param1);

    if (v3 == 1) {
        v0->session.participants[param0].blendState.releaseFlag = v3;
        v0->session.participants[param0].blendState.direction = v4;
    }

    v0->syncCounter++;
}

void poffin_cooking_0223D354(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    PoffinCookingBlendState *v1;
    BOOL v2;
    u8 v3;

    v1 = param2;

    if ((v0->session.participants[param0].blendState.releaseFlag == 1) && (v1->releaseFlag == 0)) {
        v2 = 1;
        v3 = v0->session.participants[param0].blendState.direction;
    } else {
        v2 = 0;
    }

    memcpy(&v0->session.participants[param0].blendState, param2, param1);

    if (v2 == 1) {
        v0->session.participants[param0].blendState.releaseFlag = v2;
        v0->session.participants[param0].blendState.direction = v3;
    }
}

void poffin_cooking_0223D3A8(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;

    memcpy(&v0->session.participants[param0].touchInput, param2, param1);
    v0->syncCounters[param0]++;
}

void poffin_cooking_0223D3D8(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;

    memcpy(&v0->session.receivedResult, param2, param1);
    poffin_cooking_0223B774(v0, 10);
}

void poffin_cooking_0223D3F8(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    memcpy(v0->session.poffin, param2, param1);
}

void poffin_cooking_0223D410(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;

    memcpy(&v0->session.leaveResult, param2, param1);
    poffin_cooking_0223B774(v0, 12);
}

void poffin_cooking_0223D430(int param0, int param1, void *param2, void *param3)
{
    PoffinCookingApp *v0 = param3;
    int v1;
    int v2;
    u8 v3;

    if (poffin_cooking_0223D570(v0->comm) == 0) {
        memcpy(&v0->session.leaveFlags[param0], param2, param1);
        v0->session.leaveFlagsReceived[param0] = 1;

        v2 = 0;
        v3 = 1;

        for (v1 = 0; v1 < 4; v1++) {
            if (v0->session.leaveFlagsReceived[v1] == 1) {
                v3 &= v0->session.leaveFlags[v1];
                v2++;
            }
        }

        if (v2 >= v0->playerCount) {
            poffin_cooking_0223D508(29, &v3, poffin_cooking_0223D4B0(), v0->comm);
        }
    }
}

int poffin_cooking_0223D4AC(void)
{
    return 0;
}

int poffin_cooking_0223D4B0(void)
{
    return 1;
}

int poffin_cooking_0223D4B4(void)
{
    return sizeof(PoffinCookingBerryPacket);
}

int poffin_cooking_0223D4B8(void)
{
    return sizeof(PoffinCookingBerryItem);
}

int poffin_cooking_0223D4BC(void)
{
    return sizeof(PoffinCookingParticipant);
}

int poffin_cooking_0223D4C0(void)
{
    return sizeof(PoffinCookingResult);
}

int poffin_cooking_0223D4C4(void)
{
    return sizeof(PoffinCookingBlendState);
}

int poffin_cooking_0223D4C8(void)
{
    return sizeof(PoffinCookingTouchInput);
}
