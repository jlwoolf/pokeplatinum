#include "main_menu/mystery_gift_share.h"

#include <nitro.h>
#include <string.h>

#include "main_menu/mystery_gift_app.h"
#include "main_menu/mystery_gift_share_commands.h"

#include "comm_manager.h"
#include "communication_information.h"
#include "communication_system.h"
#include "heap.h"
#include "main.h"
#include "mystery_gift.h"
#include "overlay_manager.h"
#include "savedata.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "trainer_info.h"
#include "comm_server_client.h"
#include "comm_tool.h"

typedef void (*MysteryGiftShareStateFunc)(void);

typedef struct {
    MysteryGiftAppData *unk_00;
    MATHRandContext32 unk_04;
    SysTask *unk_1C;
    MysteryGiftShareStateFunc unk_20;
    u16 unk_24;
    u8 unk_26;
    u8 unk_27;
    TrainerInfo *unk_28[16];
    WonderCard unk_68;
    u8 unk_3C0;
    u8 unk_3C1[16];
} MysteryGiftShareContext;

static void MysteryGiftShare_Task(SysTask *param0, void *param1);
static void MysteryGiftShare_ServerStartStep(void);
static void MysteryGiftShare_ServerRecordPlayersStep(void);
static void MysteryGiftShare_ClientWaitDriverStep(void);
static void MysteryGiftShare_ServerIdleStep(void);
static void MysteryGiftShare_ClientConnectStep(void);
static void MysteryGiftShare_ClientWaitConnectStep(void);
static void MysteryGiftShare_ClientSyncStep(void);

static MysteryGiftShareContext *sMysteryGiftShare = NULL;

static void MysteryGiftShare_Init(MysteryGiftAppData *param0)
{
    void *v0;

    if (sMysteryGiftShare != NULL) {
        return;
    }

    MysteryGiftShare_InitCommands((void *)param0);

    sMysteryGiftShare = (MysteryGiftShareContext *)Heap_Alloc(HEAP_ID_COMMUNICATION, sizeof(MysteryGiftShareContext));
    MI_CpuFill8(sMysteryGiftShare, 0, sizeof(MysteryGiftShareContext));

    sMysteryGiftShare->unk_24 = 50;
    sMysteryGiftShare->unk_1C = SysTask_Start(MysteryGiftShare_Task, NULL, 10);
    sMysteryGiftShare->unk_00 = param0;

    CommSys_Seed(&sMysteryGiftShare->unk_04);
}

static void MysteryGiftShare_SetStateFunc(MysteryGiftShareStateFunc param0, int param1)
{
    sMysteryGiftShare->unk_20 = param0;
    sMysteryGiftShare->unk_24 = param1;
}

static void MysteryGiftShare_ServerStartStep(void)
{
    int v0;

    if (!CommSys_IsPlayerConnected(CommSys_CurNetId())) {
        return;
    }

    for (v0 = 0; v0 < 16; v0++) {
        sMysteryGiftShare->unk_3C1[v0] = 0;
    }

    CommInfo_SendPlayerInfo();
    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ServerRecordPlayersStep, 0);
}

static void MysteryGiftShare_ServerRecordPlayersStep(void)
{
    int v0;

    for (v0 = 0; v0 < 16; v0++) {
        if ((sMysteryGiftShare->unk_28[v0] == NULL) && (CommSys_IsPlayerConnected(v0) == 1)) {
            sMysteryGiftShare->unk_28[v0] = CommInfo_TrainerInfo(v0);

            if (sMysteryGiftShare->unk_28[v0]) {
                (void)0;
            }
        }
    }
}

static void MysteryGiftShare_ClientWaitDriverStep(void)
{
    if (!WirelessDriver_IsReady()) {
        return;
    }

    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ServerIdleStep, 0);
}

static void MysteryGiftShare_ServerIdleStep(void)
{
    (void)0;
}

static void MysteryGiftShare_ClientConnectStep(void)
{
    CommManager_ConnectBattleClient(sMysteryGiftShare->unk_27);
    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ClientWaitConnectStep, 0);
}

static void MysteryGiftShare_ClientWaitConnectStep(void)
{
    if (!CommManager_IsWaitingBattle()) {
        return;
    }

    sMysteryGiftShare->unk_3C0 = 0;

    CommInfo_SendPlayerInfo();
    CommTiming_StartSync(0xAB);

    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ClientSyncStep, 0);
}

static void MysteryGiftShare_ClientSyncStep(void)
{
    return;
}

void MysteryGiftShare_Task(SysTask *param0, void *param1)
{
    if (sMysteryGiftShare == NULL) {
        SysTask_Done(param0);
    } else {
        if (sMysteryGiftShare->unk_20 != NULL) {
            MysteryGiftShareStateFunc v0 = sMysteryGiftShare->unk_20;

            if (!sMysteryGiftShare->unk_26) {
                v0();
            }
        }
    }
}

void MysteryGiftShare_StartServer(MysteryGiftAppData *param0, SaveData *saveData, int param2)
{
    if (CommSys_IsInitialized()) {
        return;
    }

    CommManager_StartRandomBattleServer(saveData, param2);

    MysteryGiftShare_Init(param0);
    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ServerStartStep, 0);
}

void MysteryGiftShare_SendDataHuge(const void *param0, int param1)
{
    CommSys_SendDataHugeServer(22, param0, param1);
}

void MysteryGiftShare_StartClient(MysteryGiftAppData *param0, int param1)
{
    SaveData *saveData;

    if (CommSys_IsInitialized()) {
        return;
    }

    saveData = ((ApplicationArgs *)ApplicationManager_Args(MysteryGiftApp_GetApplicationManager()))->saveData;
    CommManager_StartRandomBattleClient(saveData, param1);

    MysteryGiftShare_Init(param0);
    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ClientWaitDriverStep, 0);
}

void MysteryGiftShare_ConnectToServer(int param0)
{
    sMysteryGiftShare->unk_27 = param0;
    MysteryGiftShare_SetStateFunc(MysteryGiftShare_ClientConnectStep, 0);
}

int MysteryGiftShare_FindReceivedEventData(MysteryGiftAppData *param0)
{
    int v0;
    MysteryGiftEventHeader *v1;

    for (v0 = 0; v0 < 16; v0++) {
        v1 = (MysteryGiftEventHeader *)CommServerClient_GetMysteryGiftEventData(v0);

        if (v1) {
            if (v1->id) {
                memcpy(&param0->eventData.header, v1, sizeof(MysteryGiftEventHeader));
                return v0;
            }
        }
    }

    return -1;
}

void MysteryGiftShare_OnEventDataReceived(int param0, int param1, void *param2, void *param3)
{
    if (sMysteryGiftShare->unk_27 != param0) {
        return;
    }

    sMysteryGiftShare->unk_3C0 = 1;
}

int MysteryGiftShare_HasReceivedEventData(void)
{
    return sMysteryGiftShare->unk_3C0;
}

int MysteryGiftShare_GetWonderCardSize(void)
{
    return sizeof(WonderCard);
}

u8 *MysteryGiftShare_GetWonderCardBuffer(int param0, void *param1, int param2)
{
    return (u8 *)&sMysteryGiftShare->unk_68;
}

void MysteryGiftShare_OnPlayerInfoReceived(int param0, int param1, void *param2, void *param3)
{
    sMysteryGiftShare->unk_3C1[param0] = 1;
}

void MysteryGiftShare_End(void)
{
    Heap_FreeExplicit(HEAP_ID_COMMUNICATION, sMysteryGiftShare);
    sMysteryGiftShare = NULL;
    CommManager_EndBattle();
}
