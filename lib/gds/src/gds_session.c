#include <string.h>

#include "gds.h"
#include "gds_internal.h"

static void GlobalTerminalGds_ResetRequestState(void);

void GlobalTerminalGds_Reset(void)
{
    GlobalTerminalGds_ResetRequestState();
    memset(&sGlobalTerminalGdsSession.unk_00, 0, sizeof(VsRecorderViewerTransferConnection));
    sGlobalTerminalGdsSession.unk_138 = 0;
    sGlobalTerminalGdsSession.unk_140[0] = 0;
    sGlobalTerminalGdsSession.unk_240 = 0;
    GlobalTerminalGds_InitTiming();
    GlobalTerminalGds_ShutdownTiming();
}

BOOL GlobalTerminalGds_StartSession(char *url, int port, VsRecorderViewerTransferConnection *param2)
{
    if (param2) {
        sGlobalTerminalGdsSession.unk_00 = *param2;
        sGlobalTerminalGdsSession.unk_138 = 0;
    }

    int v0 = GlobalTerminalGds_InitTick();
    if (!v0) {
        return FALSE;
    }

    GlobalTerminalGds_InitMutex();
    strcpy(sGlobalTerminalGdsSession.unk_140, url);

    sGlobalTerminalGdsSession.unk_240 = port;
    sGlobalTerminalGdsSession.unk_258 = 0;
    sGlobalTerminalGdsSession.unk_26C = -1;
    GlobalTerminalGds_ResetRequestState();
    return TRUE;
}

static void GlobalTerminalGds_ResetRequestState(void)
{
    GlobalTerminalGds_CloseSocket();

    if (sGlobalTerminalGdsSession.unk_258) {
        GlobalTerminalGds_Free(sGlobalTerminalGdsSession.unk_258);
        sGlobalTerminalGdsSession.unk_258 = NULL;
    }

    sGlobalTerminalGdsSession.unk_244 = 15;
    sGlobalTerminalGdsSession.unk_248 = 30;
    sGlobalTerminalGdsSession.unk_24C = 30;

    sGlobalTerminalGdsSession.unk_254 = NULL;
    sGlobalTerminalGdsSession.unk_25C = 0;
    sGlobalTerminalGdsSession.unk_260 = NULL;
    sGlobalTerminalGdsSession.unk_264 = 0;
    sGlobalTerminalGdsSession.unk_268 = 0;

    sGlobalTerminalGdsSession.unk_13C = 1;
    sGlobalTerminalGdsSession.unk_250 = 0;
}

void GlobalTerminalGds_ProcessLoop(void)
{
    BOOL v0;
    int v1;

    while (TRUE) {
        v0 = FALSE;
        switch (sGlobalTerminalGdsSession.unk_13C) {
        case 0:
        case 1:
        case 7:
        case 8:
        case 9:
            v0 = TRUE;
            break;
        case 2:
            if (!GlobalTerminalGds_FetchToken()) {
                if (sGlobalTerminalGdsSession.unk_250 == 13) {
                    v1 = 7;
                } else {
                    v1 = 9;
                }

                v0 = TRUE;
            } else {
                v1 = 3;
            }

            GlobalTerminalGds_Lock();
            sGlobalTerminalGdsSession.unk_13C = v1;
            break;
        case 3:
            if (!GlobalTerminalGds_OpenSocket()) {
                if (sGlobalTerminalGdsSession.unk_250 == 13) {
                    v1 = 7;
                } else {
                    v1 = 9;
                }

                v0 = TRUE;
            } else {
                v1 = 4;
            }

            GlobalTerminalGds_Lock();
            sGlobalTerminalGdsSession.unk_13C = v1;
            break;
        case 4:
            if (!GlobalTerminalGds_ConnectSocket()) {
                if (sGlobalTerminalGdsSession.unk_250 == 13) {
                    v1 = 7;
                } else {
                    v1 = 9;
                }

                v0 = TRUE;
            } else {
                v1 = 5;
            }
            GlobalTerminalGds_Lock();
            sGlobalTerminalGdsSession.unk_13C = v1;
            break;
        case 5:
            if (!GlobalTerminalGds_SendRequest()) {
                if (sGlobalTerminalGdsSession.unk_250 == 13) {
                    v1 = 7;
                } else {
                    v1 = 9;
                }

                v0 = TRUE;
            } else {
                v1 = 6;
            }

            if (sGlobalTerminalGdsSession.unk_258 != 0) {
                GlobalTerminalGds_Free(sGlobalTerminalGdsSession.unk_258);
                sGlobalTerminalGdsSession.unk_258 = 0;
            }

            GlobalTerminalGds_Lock();
            sGlobalTerminalGdsSession.unk_13C = v1;
            break;
        case 6:
            if (!GlobalTerminalGds_ReceiveResponse()) {
                if (sGlobalTerminalGdsSession.unk_250 == 13) {
                    v1 = 7;
                } else {
                    v1 = 9;
                }
            } else {
                v1 = 8;
            }
            v0 = TRUE;
            GlobalTerminalGds_Lock();
            sGlobalTerminalGdsSession.unk_13C = v1;
            break;
        }

        if (v0) {
            break;
        }

        if (sGlobalTerminalGdsSession.unk_268 == 1) {
            sGlobalTerminalGdsSession.unk_13C = 7;
            sGlobalTerminalGdsSession.unk_250 = 13;
            break;
        }

        GlobalTerminalGds_Unlock();
        GlobalTerminalGds_Sleep(1);
    }

    GlobalTerminalGds_Unlock();
}

BOOL GlobalTerminalGds_SubmitRequest(int param0, void *param1, void *param2, int param3)
{
    GlobalTerminalGds_Lock();
    switch (sGlobalTerminalGdsSession.unk_13C) {
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        GlobalTerminalGds_Unlock();
        sGlobalTerminalGdsSession.unk_13C = 9;
        sGlobalTerminalGdsSession.unk_250 = 1;
        return FALSE;
    case 7:
    case 8:
    case 9:
        GlobalTerminalGds_ResetRequestState();
    case 1:
    default:
        GlobalTerminalGds_Unlock();
    }

    int v0 = GlobalTerminalGds_GetResponseAllocSize(param0);
    sGlobalTerminalGdsSession.unk_25C = v0;
    if (v0 == -1) {
        sGlobalTerminalGdsSession.unk_13C = 9;
        sGlobalTerminalGdsSession.unk_250 = 2;
        return FALSE;
    }

    sGlobalTerminalGdsSession.unk_260 = param2;

    int v2;
    if (param3 != -1) {
        v2 = param3 + 0x140;
    } else {
        v2 = GlobalTerminalGds_GetRequestSize(param0);
        if (v2 == -1) {
            sGlobalTerminalGdsSession.unk_13C = 9;
            sGlobalTerminalGdsSession.unk_250 = 2;
            return FALSE;
        }
    }

    void *v1 = GlobalTerminalGds_Alloc(v2);
    sGlobalTerminalGdsSession.unk_258 = v1;
    if (v1 == NULL) {
        return FALSE;
    }
    sGlobalTerminalGdsSession.unk_254 = v2;
    memcpy(v1, &v2, 4);

    GlobalTerminalGdsRequestHeader *v3 = sGlobalTerminalGdsSession.unk_258 + 4;
    v3->unk_00 = param0;
    v3->unk_04 = sGlobalTerminalGdsSession.unk_00;
    v3->unk_02 = 0;
    memcpy(&v3->unk_136, param1, v2 - 0x140);

    GlobalTerminalGds_Encrypt(sGlobalTerminalGdsSession.unk_258 + 4, sGlobalTerminalGdsSession.unk_254 - 4, sGlobalTerminalGdsSession.unk_258 + 4);
    sGlobalTerminalGdsSession.unk_13C = 2;
    GlobalTerminalGds_Lock();

    int result = GlobalTerminalGds_CreateThread();
    if (!result) {
        sGlobalTerminalGdsSession.unk_13C = 9;
        sGlobalTerminalGdsSession.unk_250 = 6;
        GlobalTerminalGds_Unlock();
        return FALSE;
    } else {
        GlobalTerminalGds_Unlock();
        return TRUE;
    }
}

int GlobalTerminalGds_GetState(void)
{
    return sGlobalTerminalGdsSession.unk_13C;
}

void *GlobalTerminalGds_GetResponseBuffer(void)
{
    GlobalTerminalGds_Lock();

    int v0 = GlobalTerminalGds_GetState();
    if (v0 != 8) {
        GlobalTerminalGds_Unlock();
        return NULL;
    }

    GlobalTerminalGds_Unlock();
    return sGlobalTerminalGdsSession.unk_260 + 4;
}

int GlobalTerminalGds_GetReceivedLength(void)
{
    GlobalTerminalGds_Lock();

    int v0 = GlobalTerminalGds_GetState();
    if (v0 != 8) {
        GlobalTerminalGds_Unlock();
        return -1;
    }

    GlobalTerminalGds_Unlock();
    return sGlobalTerminalGdsSession.unk_25C;
}

int GlobalTerminalGds_GetStatus(void)
{
    GlobalTerminalGds_Lock();

    int v0 = GlobalTerminalGds_GetState();
    if (v0 != 9) {
        GlobalTerminalGds_Unlock();
        return 0;
    }

    GlobalTerminalGds_Unlock();
    return sGlobalTerminalGdsSession.unk_250;
}
