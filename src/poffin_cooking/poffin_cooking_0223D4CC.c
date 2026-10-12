#include "poffin_cooking/poffin_cooking_0223D4CC.h"

#include <nitro.h>
#include <string.h>

#include "struct_defs/comm_cmd_table.h"

#include "nintendo_wfc/main.h"

#include "comm_manager.h"
#include "communication_system.h"
#include "heap.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "comm_cmd.h"

typedef struct {
    BOOL active;
    int command;
    u8 data[38];
    int dataSize;
} PoffinCookingCommPacket;

typedef struct {
    PoffinCookingCommPacket packets[8];
    const CommCmdTable *cmdTable;
    int unused_194;
    void *context;
    SysTask *task;
} PoffinCookingCommQueue;

typedef struct PoffinCookingComm_t {
    int isOnline;
    void *queue;
} PoffinCookingComm;

static PoffinCookingCommQueue *poffin_cooking_0223D584(const CommCmdTable *param0, int param1, void *param2, enum HeapID heapID);
static void poffin_cooking_0223D5CC(SysTask *param0, void *param1);
static void poffin_cooking_0223D620(PoffinCookingCommQueue *param0);
static BOOL poffin_cooking_0223D638(PoffinCookingCommQueue *param0, int param1, const void *param2, int param3);

PoffinCookingComm *poffin_cooking_0223D4CC(const CommCmdTable *param0, int param1, void *param2, int param3, enum HeapID heapID)
{
    PoffinCookingComm *v0 = Heap_Alloc(heapID, sizeof(PoffinCookingComm));
    v0->isOnline = param3;
    v0->queue = NULL;

    if (param3 == 1) {
        CommCmd_Init(param0, param1, param2);
    } else {
        v0->queue = poffin_cooking_0223D584(param0, param1, param2, heapID);
    }

    return v0;
}

BOOL poffin_cooking_0223D508(int param0, const void *param1, int param2, PoffinCookingComm *param3)
{
    if (param3->isOnline == 1) {
        if (CommManager_GetCommType() == 29) {
            BOOL v0 = 1;

            if (CommSys_IsCmdQueued(param0)) {
                v0 = 0;
            }

            if (!NintendoWFC_HasDataQueued()) {
                v0 = 0;
            }

            if (!v0) {
                return 0;
            }
        }

        return CommSys_SendData(param0, param1, param2);
    } else {
        return poffin_cooking_0223D638(param3->queue, param0, param1, param2);
    }
}

void poffin_cooking_0223D558(PoffinCookingComm *param0)
{
    if (param0->isOnline == 0) {
        poffin_cooking_0223D620(param0->queue);
    }

    Heap_Free(param0);
}

int poffin_cooking_0223D570(PoffinCookingComm *param0)
{
    if (param0->isOnline == 1) {
        return CommSys_CurNetId();
    } else {
        return 0;
    }
}

static PoffinCookingCommQueue *poffin_cooking_0223D584(const CommCmdTable *param0, int param1, void *param2, enum HeapID heapID)
{
    PoffinCookingCommQueue *v0 = Heap_Alloc(heapID, sizeof(PoffinCookingCommQueue));
    memset(v0, 0, sizeof(PoffinCookingCommQueue));

    v0->cmdTable = param0;
    v0->unused_194 = param1;
    v0->context = param2;
    v0->task = SysTask_ExecuteAfterVBlank(poffin_cooking_0223D5CC, v0, 5000);

    return v0;
}

static void poffin_cooking_0223D5CC(SysTask *param0, void *param1)
{
    PoffinCookingCommQueue *v0 = param1;
    int v1;

    for (v1 = 0; v1 < 8; v1++) {
        if (v0->packets[v1].active == 1) {
            v0->cmdTable[v0->packets[v1].command].handler(
                0, v0->packets[v1].dataSize, v0->packets[v1].data, v0->context);

            memset(&v0->packets[v1], 0, sizeof(PoffinCookingCommPacket));
        }
    }
}

static void poffin_cooking_0223D620(PoffinCookingCommQueue *param0)
{
    SysTask_Done(param0->task);
    Heap_Free(param0);
}

static BOOL poffin_cooking_0223D638(PoffinCookingCommQueue *param0, int param1, const void *param2, int param3)
{
    int v0;
    int v1;
    PoffinCookingCommPacket *v2 = NULL;

    for (v0 = 0; v0 < 8; v0++) {
        if (param0->packets[v0].active == 0) {
            v2 = &param0->packets[v0];
            break;
        }
    }

    GF_ASSERT(v2);
    param1 -= 22;

    v1 = param0->cmdTable[param1].packetSize();

    GF_ASSERT(v1 == param3);
    GF_ASSERT(param3 < 38);

    v2->command = param1;

    if (param3 > 0) {
        memcpy(v2->data, param2, param3);
    }

    v2->dataSize = param3;
    v2->active = 1;

    return 1;
}
