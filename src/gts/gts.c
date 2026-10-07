#include "gts/gts.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "struct_defs/struct_02089438.h"

#include "applications/title_screen.h"
#include "gts_application/networking.h"
#include "overlay065/ov65_0222DCE0.h"
#include "gts/gts_screen.h"
#include "gts/gts_email.h"
#include "gts/struct_gts.h"
#include "gts/struct_gts_menu_args.h"

#include "error_handling.h"
#include "game_overlay.h"
#include "heap.h"
#include "main.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "save_player.h"
#include "sound.h"
#include "string_gf.h"
#include "system.h"
#include "system_flags.h"
#include "email.h"
#include "comm_server_client.h"
#include "wifi_list_util.h"
#include "number_entry_app.h"
#include "vars_flags.h"
#include "wifi_overlays.h"

#include "constdata/const_020F2DBC.h"

FS_EXTERN_OVERLAY(overlay65);
FS_EXTERN_OVERLAY(game_opening);
FS_EXTERN_OVERLAY(gts_application);
FS_EXTERN_OVERLAY(gts);

typedef void *(*GTSAppNewFunc)(GTSState *);
typedef void (*GTSAppFreeFunc)(GTSState *);

static void GTS_LoadNetworking(GTSState *param0);
static void GTS_UnloadNetworking(GTSState *param0);
static void *GTS_DWCAlloc(DWCAllocType param0, u32 param1, int param2);
static void GTS_DWCFree(DWCAllocType param0, void *param1, u32 param2);
static void *GTS_NewState(GTSState *param0);
static void GTS_FreeState(GTSState *param0);
static void *GTS_NewMenuArgs(GTSState *param0);
static void GTS_FreeMenuArgs(GTSState *param0);
static void *GTS_NewEmailEntry(GTSState *param0);
static void GTS_ProcessEmailEntry(GTSState *param0);
static void *GTS_NewCodeEntry(GTSState *param0);
static void GTS_ProcessCodeEntry(GTSState *param0);
static void *GTS_NewNumberEntry(GTSState *param0);
static void GTS_ProcessNumberEntry(GTSState *param0);

static NNSFndHeapHandle sDWCHeap;

const ApplicationManagerTemplate gWiiMessageAppTemplate = {
    GTS_Init,
    GTS_Main,
    GTS_Exit,
    0xFFFFFFFF
};

static const ApplicationManagerTemplate sGTSMenuAppTemplate = {
    GTSScreen_Init,
    GTSScreen_Main,
    GTSScreen_Exit,
    0xFFFFFFFF
};

static const ApplicationManagerTemplate sOverlay65AppTemplate = {
    ov65_0222E2A8,
    ov65_0222E3FC,
    ov65_0222E548,
    FS_OVERLAY_ID(overlay65)
};

static const struct {
    GTSAppNewFunc unk_00;
    GTSAppFreeFunc unk_04;
    const ApplicationManagerTemplate *unk_08;
    int unk_0C;
} sAppTable[] = {
    { GTS_NewState, GTS_FreeState, &sGTSMenuAppTemplate, 0x0 },
    { GTS_NewEmailEntry, GTS_ProcessEmailEntry, &gNumberEntryAppTemplate, 0x0 },
    { GTS_NewCodeEntry, GTS_ProcessCodeEntry, &gNumberEntryAppTemplate, 0x0 },
    { GTS_NewNumberEntry, GTS_ProcessNumberEntry, &gNumberEntryAppTemplate, 0x0 },
    { GTS_NewNumberEntry, GTS_ProcessNumberEntry, &gNumberEntryAppTemplate, 0x0 },
    { GTS_NewMenuArgs, GTS_FreeMenuArgs, &sOverlay65AppTemplate, 0x1 }
};

int GTS_Init(ApplicationManager *appMan, int *param1)
{
    GTSState *v0;

    Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_108, 0x28000);
    Heap_Create(HEAP_ID_SYSTEM, HEAP_ID_NETWORK_ICON, HEAP_SIZE_NETWORK_ICON);

    v0 = ApplicationManager_NewData(appMan, sizeof(GTSState), HEAP_ID_108);
    MI_CpuClear8(v0, sizeof(GTSState));
    v0->saveData = ((ApplicationArgs *)ApplicationManager_Args(appMan))->saveData;
    v0->options = SaveData_GetOptions(v0->saveData);
    v0->unk_114 = String_Init(100, HEAP_ID_108);
    v0->unk_118 = String_Init(100, HEAP_ID_108);
    Sound_SetSceneAndPlayBGM(SOUND_SCENE_17, SEQ_WIFILOBBY_sseq, 1);
    v0->unk_8C = 0;

    return 1;
}

int GTS_Main(ApplicationManager *appMan, int *param1)
{
    GTSState *v0 = ApplicationManager_Data(appMan);
    BOOL v1;

    if (v0->unk_80 == 1) {
        DWC_UpdateConnection();
        GTSNetworking_ProcessCurrentRequest();
        NetworkIcon_SetStrength(WM_LINK_LEVEL_3 - DWC_GetLinkLevel());
    }

    switch (*param1) {
    case 0:
        GTS_LoadNetworking(v0);
        *param1 = 1;
        break;
    case 1:
        if (WirelessDriver_IsReady()) {
            sDWCHeap = v0->unk_10;
            DWC_SetMemFunc(GTS_DWCAlloc, GTS_DWCFree);
            v0->unk_80 = 1;
            *param1 = 2;
        }
        break;
    case 2:
        v0->appMan = ApplicationManager_New(sAppTable[v0->unk_8C].unk_08, sAppTable[v0->unk_8C].unk_00(v0), HEAP_ID_108);
        v0->unk_84 = v0->unk_8C;
        v0->unk_8C = 6;
        *param1 = 3;
        break;
    case 3:
        if (ApplicationManager_Exec(v0->appMan) == 1) {
            sAppTable[v0->unk_84].unk_04(v0);
            ApplicationManager_Free(v0->appMan);

            if (v0->unk_8C == 6) {
                *param1 = 4;
            } else {
                if (sAppTable[v0->unk_8C].unk_0C == 1) {
                    GTS_UnloadNetworking(v0);
                    *param1 = 2;
                } else if (v0->unk_80 == 1) {
                    *param1 = 2;
                } else {
                    *param1 = 0;
                }
            }
        }
        break;
    case 4:
        return 1;
    }

    return 0;
}

int GTS_Exit(ApplicationManager *appMan, int *param1)
{
    GTSState *v0 = ApplicationManager_Data(appMan);

    GTS_UnloadNetworking(v0);

    String_Free(v0->unk_118);
    String_Free(v0->unk_114);
    ApplicationManager_FreeData(appMan);
    Heap_Destroy(HEAP_ID_108);
    Heap_Destroy(HEAP_ID_NETWORK_ICON);
    EnqueueApplication(FS_OVERLAY_ID(game_opening), &gTitleScreenAppTemplate);

    return 1;
}

static void GTS_LoadNetworking(GTSState *param0)
{
    if (param0->unk_80 == 0) {
        Overlay_LoadByID(FS_OVERLAY_ID(gts_application), 2);

        param0->unk_0C = Heap_Alloc(HEAP_ID_108, 0x20000 + 32);
        param0->unk_10 = NNS_FndCreateExpHeap((void *)(((u32)param0->unk_0C + 31) / 32 * 32), 0x20000);

        Overlay_LoadWFCOverlay();
        Overlay_LoadHttpOverlay();
        WirelessDriver_Init();
        SleepUnlock(4);
    }
}

static void GTS_UnloadNetworking(GTSState *param0)
{
    if (param0->unk_80 == 1) {
        NNS_FndDestroyExpHeap(param0->unk_10);

        Heap_Free(param0->unk_0C);
        Overlay_UnloadHttpOverlay();
        Overlay_UnloadWFCOverlay();
        WirelessDriver_Shutdown();
        Overlay_UnloadByID(FS_OVERLAY_ID(gts_application));

        param0->unk_80 = 0;
    }
}

void GTS_SetNextApp(GTSState *param0, int param1, int param2)
{
    param0->unk_8C = param1;
    param0->unk_90 = param2;
}

void GTS_RequestExit(GTSState *param0)
{
    param0->unk_8C = 6;
}

void GTS_SetNextScreen(GTSState *param0, int param1)
{
    param0->unk_7E = param1;
}

int GTS_GetNextScreen(GTSState *param0)
{
    return param0->unk_7E;
}

static void *GTS_DWCAlloc(DWCAllocType param0, u32 param1, int param2)
{
#pragma unused(param0)
    void *v0;
    OSIntrMode v1;
    v1 = OS_DisableInterrupts();
    v0 = NNS_FndAllocFromExpHeapEx(sDWCHeap, param1, param2);

    OS_RestoreInterrupts(v1);

    if (v0 == NULL) {
        (void)0;
    }

    return v0;
}

static void GTS_DWCFree(DWCAllocType param0, void *param1, u32 param2)
{
#pragma unused(param0, param2)
    OSIntrMode v0;

    if (!param1) {
        return;
    }

    v0 = OS_DisableInterrupts();

    NNS_FndFreeToExpHeap(sDWCHeap, param1);
    OS_RestoreInterrupts(v0);
}

void GTS_SaveEmailString(GTSState *param0)
{
    char *v0 = Heap_Alloc(HEAP_ID_108, sizeof(char) * 100);

    GTSEmail_ConvertString(param0->unk_114, v0, HEAP_ID_108);
    Email_SetEmailString(param0->saveData, v0);
    Heap_Free(v0);
}

void GTS_SaveRegistrationValues(GTSState *param0)
{
    Email_SetValue(param0->saveData, 1, param0->unk_7C);
    Email_SetValue(param0->saveData, 2, param0->unk_10C);
}

void GTS_SaveEmailValue(GTSState *param0)
{
    Email_SetValue(param0->saveData, 3, param0->unk_108);
}

void GTS_InitTrainer(GTSState *param0)
{
    u32 v0 = WorldExchange_InitTrainer(param0->saveData, &param0->unk_9C);
    GTS_SetTrainerId(param0, v0);
}

void GTS_LoadTrainerEmail(GTSState *param0)
{
    GTSEmail_ConvertString(param0->unk_114, param0->unk_9C.email, HEAP_ID_108);
}

void GTS_SetRegistrationCode(GTSState *param0)
{
    param0->unk_9C.registrationCode = param0->unk_10C;
}

void GTS_SetTrainerId(GTSState *param0, u32 param1)
{
    param0->unk_7C = param1;
}

u32 GTS_GetRegistrationCode(GTSState *param0)
{
    return param0->unk_10C;
}

u32 GTS_GetEmailValue(GTSState *param0)
{
    return param0->unk_108;
}

void GTS_SetResult(GTSState *param0, int param1)
{
    param0->unk_110 = param1;
}

int GTS_GetResult(GTSState *param0)
{
    return param0->unk_110;
}

static void *GTS_NewState(GTSState *param0)
{
    return param0;
}

static void GTS_FreeState(GTSState *param0)
{
    return;
}

void *GTS_NewEmailEntry(GTSState *param0)
{
    int v0[4];

    v0[0] = 4;
    v0[1] = 4;
    v0[2] = 4;
    v0[3] = 4;

    param0->unk_98 = NumberEntryArgs_New(HEAP_ID_108, 16, v0, SaveData_GetOptions(param0->saveData), 4, 0);
    return param0->unk_98;
}

void GTS_ProcessEmailEntry(GTSState *param0)
{
    NumberEntryArgs *v0 = param0->unk_98;
    if (GTSEmail_IsAllZeros(v0->numberString, HEAP_ID_108)) {
        GTS_SetResult(param0, 1);
    } else if (GTS_GetResult(param0) == 2) {
        if (String_Compare(param0->unk_114, v0->numberString) != 0) {
            GTS_SetResult(param0, 3);
        } else {
            GTS_SetResult(param0, 0);
        }
    } else {
        String_Copy(param0->unk_114, v0->numberString);
        GTS_SetResult(param0, 2);
    }

    NumberEntryArgs_Free(v0);
    GTS_SetNextApp(param0, 0, 0);
}

void *GTS_NewCodeEntry(GTSState *param0)
{
    int v0[4];

    v0[0] = 3;
    v0[1] = 4;
    v0[2] = 0;
    v0[3] = 0;

    param0->unk_98 = NumberEntryArgs_NewWithPrefilled(HEAP_ID_108, 7, v0, SaveData_GetOptions(param0->saveData), 5, 1, 1, param0->unk_7C);
    return param0->unk_98;
}

void GTS_ProcessCodeEntry(GTSState *param0)
{
    NumberEntryArgs *v0 = param0->unk_98;
    BOOL v1;
    param0->unk_10C = String_AtoI(v0->numberString, &v1) % 10000;
    GF_ASSERT(v1);
    NumberEntryArgs_Free(v0);
    GTS_SetNextApp(param0, 0, 0);
}

void *GTS_NewNumberEntry(GTSState *param0)
{
    int v0[4];

    v0[0] = 4;
    v0[1] = 0;
    v0[2] = 0;
    v0[3] = 0;

    param0->unk_98 = NumberEntryArgs_New(HEAP_ID_108, 4, v0, SaveData_GetOptions(param0->saveData), 6, 0);
    return param0->unk_98;
}

void GTS_ProcessNumberEntry(GTSState *param0)
{
    NumberEntryArgs *v0 = param0->unk_98;
    BOOL v1;
    param0->unk_108 = String_AtoI(v0->numberString, &v1);
    GF_ASSERT(v1);
    NumberEntryArgs_Free(v0);
    GTS_SetNextApp(param0, 0, 0);
}

static void *GTS_NewMenuArgs(GTSState *param0)
{
    GTSMenuArgs *v0 = Heap_Alloc(HEAP_ID_108, sizeof(GTSMenuArgs));
    MI_CpuClear8(v0, sizeof(GTSMenuArgs));

    v0->saveData = param0->saveData;
    v0->unk_04 = 1;

    param0->unk_80 = 0;
    param0->unk_98 = v0;

    return param0->unk_98;
}

static void GTS_FreeMenuArgs(GTSState *param0)
{
    GTSMenuArgs *v0 = param0->unk_98;

    if (WiFiList_HasValidLogin(param0->saveData)) {
        SystemFlag_SetConnectedToWiFi(SaveData_GetVarsFlags(param0->saveData));
    }

    Heap_Free(param0->unk_98);
    GTS_SetNextApp(param0, 0, 0);
}
