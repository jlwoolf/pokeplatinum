#include "contest_competition/contest_competition_0224F18C.h"

#include <nitro.h>
#include <string.h>

#include "contest_competition/struct_contest_packet_queue_config.h"
#include "contest_competition/struct_contest_packet_header.h"
#include "contest_competition/struct_contest_packet_queue.h"
#include "contest_competition/struct_contest_packet_payloads.h"

#include "communication_system.h"

void contest_competition_0224F18C(ContestPacketQueue *param0, const ContestPacketQueueConfig *param1)
{
    MI_CpuClear8(param0, sizeof(ContestPacketQueue));

    param0->handlers = param1->handlers;
    param0->handlerCount = param1->handlerCount;
    param0->playerContestantID = param1->playerContestantID;
    param0->isLinkContest = param1->isLinkContest;
    param0->selfContestantID = param1->selfContestantID;
}

static int contest_competition_0224F1B4(ContestPacketQueue *param0)
{
    int v0;

    for (v0 = 0; v0 < 32; v0++) {
        if ((param0->usedSlots & (1 << v0)) == 0) {
            param0->usedSlots |= 1 << v0;
            return v0;
        }
    }

    GF_ASSERT(FALSE);
    return 0;
}

static void contest_competition_0224F1E0(ContestPacketQueue *param0, int param1)
{
    param0->usedSlots &= 0xffffffff ^ (1 << param1);
}

int contest_competition_0224F1F8(ContestPacketQueue *param0, u8 param1, u16 param2, void *param3, int param4)
{
    ContestPacketHeader v0;

    GF_ASSERT(sizeof(ContestPacketHeader) + param4 <= 512);

    MI_CpuClear8(param0->sendBuffer, 512);

    v0.targetContestantID = param1;
    v0.type = param2;
    v0.slot = contest_competition_0224F1B4(param0);
    v0.isBroadcast = 0;
    v0.size = param4 + sizeof(ContestPacketHeader);

    MI_CpuCopy32(&v0, param0->sendBuffer, sizeof(ContestPacketHeader));
    MI_CpuCopy8(param3, &param0->sendBuffer[sizeof(ContestPacketHeader)], param4);

    param0->receivedCount = 0;
    param0->packetPending = 1;

    return v0.slot;
}

void contest_competition_0224F26C(ContestPacketQueue *param0, const ContestPacketHeader *param1, void *param2, int param3)
{
    ContestPacketHeader v0;

    GF_ASSERT(sizeof(ContestPacketHeader) + param3 <= 512);

    MI_CpuClear8(param0->sendBuffer, 512);

    v0 = *param1;
    v0.targetContestantID = 0xfe;
    v0.isBroadcast = 1;
    v0.size = param3 + sizeof(ContestPacketHeader);

    MI_CpuCopy32(&v0, param0->sendBuffer, sizeof(ContestPacketHeader));

    if (param2 != NULL) {
        MI_CpuCopy8(param2, &param0->sendBuffer[sizeof(ContestPacketHeader)], param3);
    }

    param0->packetPending = 1;
}

static void contest_competition_0224F2DC(ContestPacketQueue *param0, int param1, ContestPacketHeader **param2, void **param3)
{
    *param2 = (void *)param0->receiveBuffers[param1];
    *param3 = &param0->receiveBuffers[param1][sizeof(ContestPacketHeader)];
}

static BOOL contest_competition_0224F2F8(ContestPacketQueue *param0)
{
    if (param0->packetPending == 1) {
        return 0;
    }

    if (param0->isLinkContest == 0) {
        return 1;
    }

    return 1;
}

int contest_competition_0224F30C(ContestPacketQueue *param0, void *param1, int param2, void *param3)
{
    if (contest_competition_0224F2F8(param0) == 0) {
        return 0;
    }

    GF_ASSERT(param2 < param0->handlerCount);
    param0->handlers[param2].send(param0, param1, param2, param3);
    return 1;
}

static BOOL contest_competition_0224F344(int param0, int param1, int param2)
{
    if ((param0 == param2) || (param2 == 0xff) || ((param2 == 0xfe) && (param1 == param0))) {
        return 1;
    }

    return 0;
}

BOOL contest_competition_0224F35C(ContestPacketQueue *param0)
{
    if (param0->packetPending == 0) {
        return 0;
    }

    if (param0->isLinkContest == 0) {
        MI_CpuCopy8(param0->sendBuffer, param0->receiveBuffers[param0->playerContestantID], 512);
        param0->receiveReady[param0->playerContestantID] = 1;

        MI_CpuClear8(param0->sendBuffer, 512);
        param0->packetPending = 0;
        return 1;
    } else {
        ContestPacketHeader *v0;

        v0 = (void *)param0->sendBuffer;

        if (CommSys_SendDataHuge(24, param0->sendBuffer, v0->size) == 1) {
            param0->packetPending = 0;
            return 1;
        }
    }

    return 0;
}

BOOL contest_competition_0224F3D0(ContestPacketQueue *param0)
{
    return param0->packetPending;
}

int contest_competition_0224F3D8(ContestPacketQueue *param0, void *param1)
{
    ContestPacketHeader *v0;
    void *v1;
    ContestPacketPayloads v2;
    int v3;

    MI_CpuClear8(&v2, sizeof(ContestPacketPayloads));

    if (1) {
        for (v3 = 0; v3 < 4; v3++) {
            if (param0->receiveReady[v3] == 1) {
                contest_competition_0224F2DC(param0, v3, &v0, &v1);

                if (contest_competition_0224F344(param0->playerContestantID, param0->selfContestantID, v0->targetContestantID) == 1) {
                    if (v0->type < param0->handlerCount) {
                        if (v0->isBroadcast == 0) {
                            param0->handlers[v0->type].receive(param0, param1, v0, v1);
                        } else {
                            if (param0->handlers[v0->type].receiveBroadcast != NULL) {
                                v2.payloads[v3] = v1;
                                param0->handlers[v0->type].receiveBroadcast(param0, param1, v0, &v2, v3);
                            }

                            contest_competition_0224F1E0(param0, v0->slot);

                            param0->receivedCount++;
                        }
                    } else {
                        (void)0;
                    }
                }

                param0->receiveReady[v3] = 0;
                MI_CpuClear8(param0->receiveBuffers[v3], 512);
                return 1;
            }
        }
    }

    return 0;
}

BOOL contest_competition_0224F4B8(ContestPacketQueue *param0, int connectionCount, int playerContestantID, int param3)
{
    if (playerContestantID != param3) {
        return 1;
    }

    if (param0->receivedCount >= connectionCount) {
        return 1;
    }

    return 0;
}
