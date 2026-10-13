#include "main_menu/mystery_gift_wifi.h"

#include <dwc.h>
#include <nitro.h>
#include <string.h>

#include "constants/net.h"

#include "main_menu/mystery_gift_app.h"
#include "nintendo_wfc/main.h"

#include "comm_manager.h"
#include "heap.h"
#include "network_icon.h"
#include "overlay_manager.h"
#include "system.h"
#include "comm_server_client.h"
#include "wifi_overlays.h"

static BOOL sMysteryGiftWifiNdDone;
static int sMysteryGiftWifiNdError;
static BOOL sMysteryGiftWifiCleanupDone;
static sMysteryGiftWifiExitCode;
static DWCNdFileInfo sMysteryGiftWifiFileList[10];

static void MysteryGiftWifi_NdCleanupCallback(void);

static void *MysteryGiftWifi_Alloc(DWCAllocType param0, u32 param1, int param2)
{
#pragma unused(param0, param2)
    void *v0;
    u32 *v1;

    param1 = (((param1 + sizeof(void *)) + 32) & ~31) + 32;

    v0 = Heap_Alloc(HEAP_ID_MYSTERY_GIFT_APP, param1);
    v1 = (u32 *)(((u32)v0 + 32) & ~31);

    v1--;
    *v1 = (u32)v0;
    v1++;

    return v1;
}

static void MysteryGiftWifi_Free(DWCAllocType param0, void *param1, u32 param2)
{
#pragma unused(param0, param2)
    u32 *v0;

    if (!param1) {
        return;
    }

    v0 = (u32 *)((u32)param1 - 4);
    Heap_Free((void *)*v0);
}

static volatile BOOL sMysteryGiftWifiErrored;

static int MysteryGiftWifi_HandleError(MysteryGiftAppData *param0)
{
    DWCError v0;
    DWCErrorType v1;
    int v2;

    v0 = DWC_GetLastErrorEx(&v2, &v1);

    param0->wifiCommErrorStringID = NintendoWFC_GetErrorCode(-v2, v1);
    param0->wifiCommErrorCode = -v2;
    param0->wifiCommErrorType = v1;
    param0->wifiCommErrored = 1;

    sMysteryGiftWifiErrored = 1;
    param0->dwcCallback = NULL;

    MysteryGiftApp_ToggleWaitDial(param0, 0);
    return 4111;
}

static BOOL MysteryGiftWifi_IsConnected(MysteryGiftAppData *param0)
{
    DWCApInfo v0;
    DWCError v1;
    int v2, v3;

    switch (DWC_GetInetStatus()) {
    case DWC_CONNECTINET_STATE_ERROR:
        break;
    case DWC_CONNECTINET_STATE_FATAL_ERROR:
        break;
    case DWC_CONNECTINET_STATE_CONNECTED:

        if (DWC_GetApInfo(&v0) == 1) {
            (void)0;
        } else {
            (void)0;
        }

        return 1;
        break;
    }

    return 0;
}

static void MysteryGiftWifi_SetNextState(MysteryGiftAppData *param0, int *param1, int param2)
{
    sMysteryGiftWifiNdDone = 0;
    sMysteryGiftWifiNdError = DWC_ND_ERROR_NONE;
    param0->nextState = param2;
    *param1 = 4114;
}

static void MysteryGiftWifi_CleanupAsync(MysteryGiftAppData *param0, int param1, int *param2, int param3, int param4)
{
    sMysteryGiftWifiCleanupDone = 0;
    sMysteryGiftWifiExitCode = param1;
    param0->nextState = param3;
    *param2 = 4115;

    if (!DWC_NdCleanupAsync(MysteryGiftWifi_NdCleanupCallback)) {
        *param2 = param4;
    }
}

static void MysteryGiftWifi_NdCallback(DWCNdCallbackReason param0, DWCNdError param1, int param2)
{
    switch (param0) {
    case DWC_ND_CBREASON_GETFILELISTNUM:
        break;
    case DWC_ND_CBREASON_GETFILELIST:
        break;
    case DWC_ND_CBREASON_GETFILE:
        break;
    case DWC_ND_CBREASON_INITIALIZE:
        break;
    }

    switch (param1) {
    case DWC_ND_ERROR_NONE:
        break;
    case DWC_ND_ERROR_ALLOC:
        break;
    case DWC_ND_ERROR_BUSY:
        break;
    case DWC_ND_ERROR_HTTP:
        if (param0 == DWC_ND_CBREASON_GETFILELISTNUM) {
            (void)0;
        }
        break;
    case DWC_ND_ERROR_BUFFULL:
        break;
    case DWC_ND_ERROR_DLSERVER:
        break;
    case DWC_ND_ERROR_CANCELED:
        break;
    }

    sMysteryGiftWifiNdDone = 1;
    sMysteryGiftWifiNdError = param1;
}

static void MysteryGiftWifi_NdCleanupCallback(void)
{
    switch (sMysteryGiftWifiExitCode) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    }

    sMysteryGiftWifiCleanupDone = 1;
}

static void MysteryGiftWifi_Shutdown(void)
{
    NetworkIcon_Destroy();
    CommManager_EndMysteryGiftWifi();
    Overlay_UnloadHttpOverlay();
    Overlay_UnloadWFCOverlay();
    WirelessDriver_Shutdown();
}

int MysteryGiftWifi_Main(ApplicationManager *appMan, int *param1)
{
    int v0;
    DWCNasLoginState v1;
    MysteryGiftAppData *v2 = ApplicationManager_Data(appMan);

    if (v2->dwcCallback) {
        if (v2->dwcCallback() == 1) {
            *param1 = MysteryGiftWifi_HandleError(v2);
        }
    }

    switch (*param1) {
    case 4096:
        WirelessDriver_Init();
        Overlay_LoadWFCOverlay();
        Overlay_LoadHttpOverlay();
        *param1 = 4097;
        break;
    case 4097:
        if (WirelessDriver_IsReady()) {
            DWC_SetMemFunc(MysteryGiftWifi_Alloc, MysteryGiftWifi_Free);
            CommManager_StartMysteryGiftWifi(v2->saveData);
            *param1 = 4098;
        }
        break;
    case 4098:
        DWC_InitInetEx(&v2->inetControl, DEFAULT_DWC_DMA_NUMBER, DEFAULT_DWC_POWER_MODE, DEFAULT_DWC_SSL_PRIORITY);
        DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
        DWC_ConnectInetAsync();
        NetworkIcon_Init();
        *param1 = 4099;
        v2->wifiExitRequested = 0;
        break;
    case 4099:
        DWC_ProcessInet();

        if (DWC_CheckInet() == 0) {
            (void)0;
        } else {
            if (MysteryGiftWifi_IsConnected(v2) == 1) {
                if (v2->wifiExitRequested == 1) {
                    sMysteryGiftWifiExitCode = 3;
                    *param1 = 4109;
                } else {
                    *param1 = 4100;
                }
            } else {
                *param1 = MysteryGiftWifi_HandleError(v2);
            }
        }

        if (gSystem.pressedKeys & PAD_BUTTON_B) {
            v2->wifiExitRequested = 1;
        }
        break;
    case 4100:
        if (DWC_NASLoginAsync() == 0) {
            *param1 = MysteryGiftWifi_HandleError(v2);
        } else {
            *param1 = 4101;
        }
        break;
    case 4101:
        v1 = DWC_NASLoginProcess();

        if (v1 == DWC_NASLOGIN_STATE_SUCCESS) {
            *param1 = 4102;
            v2->dwcCallback = DWC_UpdateConnection;
        } else if (v1 == DWC_NASLOGIN_STATE_ERROR) {
            *param1 = MysteryGiftWifi_HandleError(v2);
            DWC_CleanupInet();
        } else if (v1 == DWC_NASLOGIN_STATE_CANCELED) {
            sMysteryGiftWifiExitCode = 3;
            *param1 = 4109;
        }

        if (gSystem.pressedKeys & PAD_BUTTON_B) {
            DWC_NASLoginAbort();
        }
        break;
    case 4102:
        if (DWC_NdInitAsync(MysteryGiftWifi_NdCallback, "CPUE", "DwuCXmdJfPVLBnKA") == 0) {
            *param1 = MysteryGiftWifi_HandleError(v2);
            break;
        }

        MysteryGiftWifi_SetNextState(v2, param1, 4103);
        break;
    case 4103:
        if (v2->wifiExitRequested == 1) {
            MysteryGiftWifi_CleanupAsync(v2, 3, param1, 4108, 4108);
            break;
        }

        if (DWC_NdSetAttr("", "", "") == 0) {
            *param1 = MysteryGiftWifi_HandleError(v2);
            break;
        }

        *param1 = 4104;
        break;
    case 4104:
        if (DWC_NdGetFileListNumAsync(&v2->ndFileListCount) == 0) {
            *param1 = MysteryGiftWifi_HandleError(v2);
            break;
        }

        MysteryGiftWifi_SetNextState(v2, param1, 4105);
        break;
    case 4105:
        if (v2->ndFileListCount != 1) {
            MysteryGiftWifi_CleanupAsync(v2, 2, param1, 4109, 4109);
        } else {
            if (DWC_NdGetFileListAsync(sMysteryGiftWifiFileList, 0, 10) == 0) {
                *param1 = MysteryGiftWifi_HandleError(v2);
                break;
            }

            MysteryGiftWifi_SetNextState(v2, param1, 4106);
        }
        break;
    case 4106:
        if (DWC_NdGetFileAsync(&sMysteryGiftWifiFileList[0], v2->wifiDistributionBuffer, 4096) == 0) {
            *param1 = MysteryGiftWifi_HandleError(v2);
            break;
        }

        *param1 = 4107;
        v2->ndDownloadPercent = 0;
        break;
    case 4107:
        if (sMysteryGiftWifiNdDone == 0) {
            if (gSystem.pressedKeys & PAD_BUTTON_B) {
                MysteryGiftWifi_CleanupAsync(v2, 3, param1, 4108, 4108);
            } else {
                if (DWC_NdGetProgress(&v2->ndTransferredBytes, &v2->ndTotalBytes) == 1) {
                    if (v2->ndDownloadPercent != (v2->ndTransferredBytes * 100) / v2->ndTotalBytes) {
                        v2->ndDownloadPercent = (v2->ndTransferredBytes * 100) / v2->ndTotalBytes;
                    }
                }
            }
        } else {
            if (v2->wifiExitRequested == 0) {
                MysteryGiftWifi_CleanupAsync(v2, 1, param1, 4109, 4109);
            } else {
                MysteryGiftWifi_CleanupAsync(v2, 3, param1, 4109, 4109);
            }
        }
        break;
    case 4108:
        if (DWC_NdCancelAsync() == 0) {
            *param1 = 4109;
        } else {
            v2->dwcCallback = NULL;
            MysteryGiftWifi_Shutdown();
            return sMysteryGiftWifiExitCode;
        }
        break;
    case 4109:
        if (DWC_CleanupInetAsync() == 1) {
            v2->dwcCallback = NULL;
            MysteryGiftWifi_Shutdown();
            return sMysteryGiftWifiExitCode;
        }
        break;
    case 4110:
        break;
    case 4111:
        if (sMysteryGiftWifiErrored == 1) {
            MysteryGiftApp_ShowWiFiCommError(v2);

            if ((v2->wifiCommErrorType == DWC_ETYPE_SHUTDOWN_ND) || (v2->wifiCommErrorType == DWC_ETYPE_DISCONNECT)) {
                MysteryGiftWifi_CleanupAsync(v2, 3, param1, 4113, 4112);
            } else {
                *param1 = 4113;
            }
        }
        break;
    case 4113:
        DWC_CleanupInet();
        *param1 = 4112;
        break;
    case 4112:
        if (gSystem.pressedKeys & PAD_BUTTON_A) {
            v2->dwcCallback = NULL;
            DWC_ClearError();
            MysteryGiftWifi_Shutdown();

            return 4;
        }
        break;
    case 4114:
        if (sMysteryGiftWifiNdDone == 1) {
            sMysteryGiftWifiNdDone = 0;

            if (sMysteryGiftWifiNdError != DWC_ND_ERROR_NONE) {
                *param1 = MysteryGiftWifi_HandleError(v2);
            } else {
                *param1 = v2->nextState;
            }
        } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
            v2->wifiExitRequested = 1;
        }
        break;
    case 4115:
        if (sMysteryGiftWifiCleanupDone == 1) {
            sMysteryGiftWifiCleanupDone = 0;
            *param1 = v2->nextState;
        } else if (gSystem.pressedKeys & PAD_BUTTON_B) {
            v2->wifiExitRequested = 1;
        }

        break;
    }

    return 0;
}
